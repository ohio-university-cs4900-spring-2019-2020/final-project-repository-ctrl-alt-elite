#pragma once

namespace Aftr
{

   class WGS84
   {
   public:
      static double getMajorSemiaxisInMeters() { return 6378137; }
      static double getMinorSemiaxisInMeters() { return 6356752.314140; }
      static double getRecipricalOfFlattening() { return 298.257223563; }
      static double getFlattening() { return 1 / getRecipricalOfFlattening(); }
   };

   //used by NAD83
   class GRS80
   {
   public:
      static double getMajorSemiaxisInMeters() { return 6378137; }
      static double getMinorSemiaxisInMeters() { return  6356752.314140; }
      static double getRecipricalOfFlattening() { return 298.25722210088; }
      static double getFlattening() { return 1 / getRecipricalOfFlattening(); }
      static double getEccentricitySquarred() { return .0066943800229034; }
   };

   



};

