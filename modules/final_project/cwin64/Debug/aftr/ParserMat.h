#pragma once

#include <string>
#include <vector>

namespace Aftr
{

   //using the Matlab v5 codes to determine which type it should be
   union MatVar
   {
      char c;//1
      unsigned char uc;//2 
      short s;//3
      unsigned short us;//4
      int i;//5
      unsigned int ui;//6
      float f;//7
      //reserved 8
      double d;//9
      //reserved 10
      //reserved 11
      long long ll;//12
      unsigned long long ull;//13
      //Matrix 14 - unsupported
   };

   enum MatVarType { mvCHAR, mvUCHAR, mvSHORT, mvUSHORT, mvINT, mvUINT, mvFLOAT, mvDOUBLE, mvLONGLONG, mvULONGLONG, mvMATRIX };

   class MatVarWrapper
   {
   public:
      MatVar mv;
      MatVarType mvt;
      std::string toString();
   };

   class ParserMat
   {
   public:
      ParserMat( const std::string& fileName );
   protected:
      std::vector< MatVarWrapper > data;
      bool bigEndian;
   };

}

