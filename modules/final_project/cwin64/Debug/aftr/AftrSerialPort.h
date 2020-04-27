#pragma once
#include "AftrConfig.h"
#ifdef AFTR_CONFIG_USE_BOOST
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <queue>

namespace boost
{ class thread; }

//website that has some nice code samples
//http://www.webalice.it/fede.tft/serial_port/serial_port.html

namespace Aftr
{

class AftrSerialPort
{
public:
   virtual ~AftrSerialPort() = 0;

   virtual bool open( const std::string& comPort = "COM1", 
                      unsigned int baudRate = 1200,
                      boost::asio::serial_port_base::character_size charSize = boost::asio::serial_port_base::character_size( 8 ),
                      boost::asio::serial_port_base::parity::type parity = boost::asio::serial_port_base::parity::none,
                      boost::asio::serial_port_base::flow_control::type flowControl = boost::asio::serial_port_base::flow_control::none,
                      boost::asio::serial_port_base::stop_bits::type stopBits = boost::asio::serial_port_base::stop_bits::one );
   
   
   boost::asio::serial_port& getSerialPort() { return *this->serialPort; }

   virtual void sendDataAsync( const std::string& str );
   virtual void sendDataAsync( const std::vector< char >& data );
   ///Sends data asynchronously, the in passed data becomes owned by this instance and is free'd
   ///after the send is complete.
   virtual void sendDataAsync( char* sentData, unsigned int length );

   virtual bool isOpen();

protected:
   AftrSerialPort();
   virtual void onCreate();

   virtual void start() = 0;
   virtual void onRecvData( const boost::system::error_code& error, size_t bytesReceived );
   virtual void onSendData( char* binDat, const boost::system::error_code& error );

   boost::asio::serial_port* serialPort = nullptr; ///< Boost's cross platform serial port interface
   std::string comPort; ///< Serial port used by this connection "COM1" or "/dev/ttyUSB0"
   unsigned int baudRate = 1200; ///< Baud rate of this connection

   //Receive variables
   //sample input '#AL +00550T+58E1'
   char* recvBuf = nullptr;
   unsigned int maxRecvBufLen = 0; ///< 16 KB buffer to read from Serial COM PORT
   unsigned int msgLen = 0; //length in bytes message of a message

   //Send variables
   char* sendBuf = nullptr; ///< Binary chunk of memory used to send data
   unsigned int maxSendBufLen = 0; ///< size of sendBuf's chunk of continuous memory
   boost::mutex sendQMutex;
   std::queue< std::pair< char*, unsigned int > > sendQ; ///< Q which stores data to send

};

class AftrSerialPortSingleton
{
public:
   static void init();
   static void shutdown();
   static AftrSerialPort* createSerialPort();
   static boost::asio::io_context& getIOService();
   static void addRef( AftrSerialPort* newSerialPort );
   static void decRef( AftrSerialPort* newSerialPort );

protected:
   static int refCountSerialPort; ///< Number of currently active serial ports using this ioService
   static bool hasBeenInitialized;
   static boost::asio::io_context* ioService; ///< Boost's cross platform interface with OS networking / com port
   static boost::thread* ioServiceThread; ///< Thread which handles async io with com port
   static boost::asio::io_context::work* work; ///< Keeps the ioServiceThread from exiting if it has no work to do
};

} //namespace Aftr

#endif
