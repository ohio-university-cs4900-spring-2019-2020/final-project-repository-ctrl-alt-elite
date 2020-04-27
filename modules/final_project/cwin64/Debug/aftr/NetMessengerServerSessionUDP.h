#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST

#include "NetMessengerMessageQueue.h"
#include <iostream>
#include <cstdint>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

namespace Aftr
{


/// This can only send messages UP TO the maximum size of a UDP payload. No fragmentation occurs. If the payload
/// is larger than UDP payload, a boost error (typically system: 1784) will result.
class NetMessengerServerSessionUDP
{
public:

   //This constructor is used by the NetMessengerServerListener to establish a new session between an initiating
   //remote client and this server.
   NetMessengerServerSessionUDP( boost::asio::io_context& io_context, NetMessengerMessageQueue* servListenerRecvQueue );
   
   //This constructor can be used by a user to establish a session to a remote NetMessengerServerListener (a remote
   //instance of the AftrBurner engine running.
   NetMessengerServerSessionUDP( const std::string& host, const std::string& port, boost::asio::io_context& io_context,
                              NetMessengerMessageQueue* recvQueue );
   
   ~NetMessengerServerSessionUDP();
   boost::asio::ip::udp::socket& getSocket();
   bool isStarted() { return this->IsStarted; }

   //Ownership is transferred to the NetMessengerServerSessionUDP, the message will be destroyed by this instance.
   bool enqueueMsgToSend( std::shared_ptr<NetMsg> msg );

   void start();
   bool connectSessionToHost( const std::string& host, const std::string& port );
   bool reConnectSessionToHost();

   std::string toString() const;

   //When doing async sending and receiving, notifying the user of a send/recv error is not possible
   //as the time the user queues the request to send or recv. What we do instead, if an send or recv
   //error occurs, we set these values to non-null. The user can then check these flags to see if an
   //error has occurred and choose to take action at that point, such as by trying to reconnect to the
   //endpoint.
   //These two get Error msgs will return the latest error and THEN reset the error_code back to none.
   boost::system::error_code getLastSendError();
   boost::system::error_code getLastRecvError();

private:

   bool isValidHeader( unsigned int headerCode ) const;

   //host and port are only used for the second constructor when the session is used to initiate a new connection (SYN)
   //versus serving as receiver of a new connection (the remote endpoint (SYN ACK)).
   std::string host{ "127.0.0.1" };
   std::string port{ "12683" };

   boost::asio::ip::udp::socket sock;
   static const unsigned int HEADER_LEN_BYTES = 8; ///< Header length of a message in bytes (32-bits)
   std::vector< char > recvBuff;
   std::array<char, HEADER_LEN_BYTES> recvHeader{ 0 };

   void onRecvHeader( const boost::system::error_code& error, size_t bytesReceived );
   void onRecvBody( const boost::system::error_code& error, size_t bytesReceived );
   
   //This method is only execute inside asio handler via this->strand executor.
   //This method adds msg to sendQueue. If no existing messages are being sent, it will
   //begin an writing within the strand's asio context.
   void enqueueMsgHandler( std::shared_ptr<NetMsg> msg );
   
   //This method is only execute inside asio handler via this->strand executor.
   //This method is called by enqueueMsgHandler only to begin writing queued messages within
   //the strand's asio context. This will repeatedly invoke until the send queue is empty.
   void sendMsgHandler();
   void onSentMsg( char* binDat, const boost::system::error_code& error, size_t bytes_transferred );

   bool IsStarted = false; ///< Initially set to false, gets set to True once this->start() has been invoked and async operations have begun

   unsigned int currHeaderCode = 0; ///< Set by onRecvHeader, read by onRecvBody, indicates NetMsg subclass to instantiate
   unsigned int currMsgLenBytes = 0; ///< Set by onRecvHeader, read by onRecvBody, indicates length of binary data for the current message

   boost::asio::io_context::strand writeStrand; // A strand guarantees that no two handlers execute concurrently.

   //Thread safe queue of pending messages to send to endpoint associated with this session
   //Only thread safe when the user calls lock() prior to using it and unlock after using it.
   NetMessengerMessageQueueT< std::shared_ptr<NetMsg> > sendQueue;

   /**
      Pointer to corresponding NetMessengerServerListener's queue, which holds all newly
      received (and fully instantiated) messages until the engine processes their 
      callbacks (NetMsg::onMessageArrived()). The callback is invoked when then engine
      calls NetMessengerServer::onUpdate(), which is typically in the GLView::onUpdateWorld().
      This recvQueue is NOT owned by this instance, do not delete. This queue is actually
      owned by the corresponding NetMessengerServerListener which spawned this session's existence.
   */
   NetMessengerMessageQueue* recvQueue = nullptr;

   boost::system::error_code lastSendError;
   boost::system::error_code lastRecvError;
};

} //namespace Aftr

#endif


////----------------------------------------------------------------------
//
//class chat_room
//{
//public:
//   void join(chat_participant_ptr participant)
//   {
//      participants_.insert(participant);
//      std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
//         boost::bind(&chat_participant::deliver, participant, _1));
//   }
//
//   void leave(chat_participant_ptr participant)
//   {
//      participants_.erase(participant);
//   }
//
//   void deliver(const chat_message& msg)
//   {
//      recent_msgs_.push_back(msg);
//      while (recent_msgs_.size() > max_recent_msgs)
//         recent_msgs_.pop_front();
//
//      std::for_each(participants_.begin(), participants_.end(),
//         boost::bind(&chat_participant::deliver, _1, boost::ref(msg)));
//   }
//
//private:
//   std::set<chat_participant_ptr> participants_;
//   enum { max_recent_msgs = 100 };
//   chat_message_queue recent_msgs_;
//};

////----------------------------------------------------------------------
//
//class chat_session
//   : public chat_participant,
//   public boost::enable_shared_from_this<chat_session>
//{
//public:
//   chat_session(boost::asio::io_context& io_context, chat_room& room)
//      : socket_(io_context),
//      room_(room)
//   {
//   }
//
//   tcp::socket& socket()
//   {
//      return socket_;
//   }
//
//   void start()
//   {
//      room_.join(shared_from_this());
//      boost::asio::async_read(socket_,
//         boost::asio::buffer(read_msg_.data(), chat_message::header_length),
//         boost::bind(
//         &chat_session::handle_read_header, shared_from_this(),
//         boost::asio::placeholders::error));
//   }
//
//   void deliver(const chat_message& msg)
//   {
//      bool write_in_progress = !write_msgs_.empty();
//      write_msgs_.push_back(msg);
//      if (!write_in_progress)
//      {
//         boost::asio::async_write(socket_,
//            boost::asio::buffer(write_msgs_.front().data(),
//            write_msgs_.front().length()),
//            boost::bind(&chat_session::handle_write, shared_from_this(),
//            boost::asio::placeholders::error));
//      }
//   }
//
//   void handle_read_header(const boost::system::error_code& error)
//   {
//      if (!error && read_msg_.decode_header())
//      {
//         boost::asio::async_read(socket_,
//            boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
//            boost::bind(&chat_session::handle_read_body, shared_from_this(),
//            boost::asio::placeholders::error));
//      }
//      else
//      {
//         room_.leave(shared_from_this());
//      }
//   }
//
//   void handle_read_body(const boost::system::error_code& error)
//   {
//      if (!error)
//      {
//         room_.deliver(read_msg_);
//         boost::asio::async_read(socket_,
//            boost::asio::buffer(read_msg_.data(), chat_message::header_length),
//            boost::bind(&chat_session::handle_read_header, shared_from_this(),
//            boost::asio::placeholders::error));
//      }
//      else
//      {
//         room_.leave(shared_from_this());
//      }
//   }
//
//   void handle_write(const boost::system::error_code& error)
//   {
//      if (!error)
//      {
//         write_msgs_.pop_front();
//         if (!write_msgs_.empty())
//         {
//            boost::asio::async_write(socket_,
//               boost::asio::buffer(write_msgs_.front().data(),
//               write_msgs_.front().length()),
//               boost::bind(&chat_session::handle_write, shared_from_this(),
//               boost::asio::placeholders::error));
//         }
//      }
//      else
//      {
//         room_.leave(shared_from_this());
//      }
//   }
//
//private:
//   tcp::socket socket_;
//   chat_room& room_;
//   chat_message read_msg_;
//   chat_message_queue write_msgs_;
//};
//
//typedef boost::shared_ptr<chat_session> chat_session_ptr;
//
////----------------------------------------------------------------------
