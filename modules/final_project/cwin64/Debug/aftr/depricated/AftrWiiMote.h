//------------------------------------------------------------------------
//
// File: SteamieWiiMote
// Author: Mitchell Leitch
//
// A struct holding the SteamieWiiMote data needed to hold the data of the 
// WiiMote
//
//------------------------------------------------------------------------
#pragma once


namespace Steamie
{

/**
   \struct SteamieWiiMote
   \author Mitchell Leitch
   A struct holding the SteamieWiiMote data needed to hold the data of the WiiMote
   \{
   */

struct SteamieWiiMote
{
   /**
      The orientation of the WiiMote
      */
   /**
      The roll orientation of the WiiMote
      */
   float roll;
   /**
      The pitch orientation of the WiiMote
      */
   float pitch;
   /**
      The yaw orientation of the WiiMote
      */
   float yaw;

   /**
      The screen coordinates using the infrared device
      */
   /**   
      The x screen coordinates using the infrared device
      */
   unsigned short screenX;
   /**
      The y screen coordinates using the infrared device
      */
   unsigned short screenY;
   /**
      The estimated/calculated distance the wiimote is from the
      screen, based on the infrared dots on the screen
      */
   float distanceFromScreen;

   /**
      The current buttons that have been pressed on this wiimote event
      */
   unsigned short btnsPressed;
   /**
      The current buttons that are being held down on this wiimote event
      */
   unsigned short btnsHeld;
   /**
      The current buttons that have been released on this wiimote event
      */
   unsigned short btnsReleased;
   /**
      this is the id for the wiimote, this should correspond to the id assigned in wiiuse library
      */
   unsigned int id;

};



} //namespace Steamie


