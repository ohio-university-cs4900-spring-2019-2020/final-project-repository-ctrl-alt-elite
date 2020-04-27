#pragma once

#include "AftrConfig.h"
#include "MatrixFwd.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cmath>
#include <algorithm>
#ifdef AFTR_CONFIG_USE_ALGLIB
#include "ap.h"  //ALGLIB data structure declarations
#include "qr.h"  //QR Factorization functions
#include "inv.h" //MatrixT inversion functions
#endif
#include "MatrixInverseCUDA_GPUGausSeidel.h" //CUDA-based GPU MatrixT inverse functions
#include "ManagerCUDA.h"
#include "Vector.h"
#include <fstream>

#ifdef AFTR_CONFIG_USE_BOOST
#pragma warning( push )
#pragma warning( disable: 4127 ) //ignore warning inside of boost code
//https://stackoverflow.com/questions/46152716/disable-warning-log-in-boostublas
#define BOOST_UBLAS_TYPE_CHECK 0
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/storage.hpp>
#include "Storage_Adaptors_Matrix.h" //enables make_matrix_from_pointer function
#undef BOOST_UBLAS_TYPE_CHECK
#endif

#ifdef AFTR_CONFIG_USE_CUDA
//#include "cublas.h"
#endif

#include <string>
#include <vector>

namespace Aftr
{

/**
   Author: Scott Nykl
   \brief A MatrixT Class.
   This MatrixT class gives standard MatrixT operations. If AFTR_CONFIG_USE_CUDA is defined
   in AftrConfig.h, then the GPU will be used to acceleration such methods as MatrixT
   multiplication and QR Decomposition.

   Internally, these matrices are stored column-major.
*/
template< typename T >
class MatrixT
{
public:
   MatrixT();
   MatrixT( unsigned int numRows, unsigned int numCols );
   MatrixT( std::vector< std::vector< T > >& m );
   MatrixT( std::vector< VectorT<T>* >* m );
   MatrixT( const MatrixT& m );
   //takes ownership of colMajor2DArray, will crash if an automatic (e.g. float x[16]) is passed in when it leaves scope.
   MatrixT( T* colMajor2DArray, unsigned int numRows, unsigned int numCols );
   ~MatrixT();

   T* releaseOwnershipOfInternalColumnMajorData( unsigned int& outNumRows, unsigned int& outNumCols );

   MatrixT& operator=( const MatrixT& m );
   T& operator()( unsigned int row, unsigned int col );
   T operator()( unsigned int row, unsigned int col ) const;

   T& at( unsigned int row, unsigned int col );
   T at( unsigned int row, unsigned int col ) const;

   #ifdef AFTR_CONFIG_USE_CUDA
      MatrixT multCUDA( const MatrixT& m );
   #endif

   MatrixT multCPU( const MatrixT& m );
   
   #ifdef AFTR_CONFIG_USE_BOOST
      MatrixT multCPUBoostLIB( const MatrixT& m );
   #endif

   MatrixT operator*( const MatrixT& m );
   MatrixT operator*=( const MatrixT& m );
   MatrixT operator*( T scalar );
   MatrixT operator*=( T scalar );
   MatrixT multiply( const MatrixT& m );
   MatrixT operator+( const MatrixT& m );
   MatrixT operator+=( const MatrixT& m );
   MatrixT operator-( const MatrixT& m );
   MatrixT operator-=( const MatrixT& m );
   MatrixT operator/( T scalar );
   MatrixT operator/=( T scalar );
   MatrixT transpose() const;
   bool equals( const MatrixT& m, T epsilon = .00001f );

   //-------------------------------------------------------------------------
   // Insertion operator enabling a VectorT to be read in std::cout << myVec.
   //-------------------------------------------------------------------------
   friend std::ostream& operator <<( std::ostream& out, const MatrixT& m )
   {
      out << m.toString();
      return out;
   }

   /**
      If this MatrixT is MxM (square) and non-singular, the inverse will be
      returned. The optional parameter isInvertable is set to true, if the
      MatrixT was inverted; false, otherwise. If the MatrixT is singular (not
      invertible), the Identity MatrixT is returned of size MxM and
      isInvertable is set to false.
   */
   MatrixT inverse();

   MatrixT inverseCPU();

   #ifdef AFTR_CONFIG_USE_CUDA
      MatrixT inverseCUDA();
   #endif

   /**
      Returns true iff this MatrixT is invertable; false, otherwise. If the
      MatrixT is invertible, parameter invertedMatrixT is set to the inverse.
      If the MatrixT is not invertible, parameter invertedMatrixT is unchanged.
   */
   bool isInvertable( MatrixT& invertedMatrixT );

   /**
      Perform Gauss-Jordan elimination with row-pivoting to obtain the 
      solution to the system of linear equations
      A * X = B

      A is the the MatrixT of coefficients, B is the product of A*X,
      and X is the MatrixT being solved.

      Returns true if x contains the solution; returns false if MatrixT A is
      not linearly independent (and therefore singular (has a determinite of zero)).
      If true is returned, MatrixT x is overwritten to contain the solution.
      If false is returned, MatrixT x is not touched.

      This method invokes the gaussianJordanElimination function from 
      AftrUtilities.h for the actual computation.
   */
   bool gaussianJordanElimination( const MatrixT& a, MatrixT& x, const MatrixT& b );

   MatrixT* appendRowToTopRetMatrixPtr( T initialVal );
   MatrixT* appendRowToBottomRetMatrixPtr( T initialVal );
   MatrixT* appendColToLeftRetMatrixPtr( T initialVal );
   MatrixT* appendColToRightRetMatrixPtr( T initialVal );

   void appendRowToTop( T initialVal );
   void appendRowToBottom( T initialVal );
   void appendColToLeft( T initialVal );
   void appendColToRight( T initialVal );

   /**
      Resizes this array to numRows by numCols. A resize only takes place
      if this MatrixT is of a different dimension.
   */
   void resize( unsigned int numRows, unsigned int numCols );


   void setMatrixToZeros();
   void setMatrixToOnes();
   void setMatrixTo( T value );
   void setMatrixToIdentity();
   void setMatrixToColumnMajor2DArray( T* colMajor2DArray, unsigned int numRows, unsigned int numCols );

   MatrixT getColumnVector( unsigned int col );
   MatrixT getRowVector( unsigned int row );
   MatrixT getSubMatrix( unsigned int row, unsigned int numRows,
                        unsigned int col, unsigned int numCols );

   MatrixT sumColumns();
   MatrixT componentWiseDivide(MatrixT& m);

   MatrixT normalizeEachRow() const;
   void normalizeMeEachRow();
   T getMagnitudeOfRow( unsigned int row ) const;
   T getMagnitudeSquaredOfRow( unsigned int row ) const;

   MatrixT normalizeEachColumn() const;
   void normalizeMeEachColumn();
   T getMagnitudeOfColumn( unsigned int col ) const;
   T getMagnitudeSquaredOfColumn( unsigned int col ) const;

   /**
      Computes the QR Decomposition of this MatrixT (via Householder Reflections).
      M = number of rows of this MatrixT, N = number of cols of this MatrixT.
      A = QR, where A is this current MatrixT, Q is an MxM orthonormal MatrixT,
      and R is an upper triangular (or upper trapezoidal) MxN MatrixT.
      Q is an OUT only MatrixT reference. Q is an orthogonal MatrixT of size MxM.
      R is an OUT only MatrixT reference. R is an upper triangular (or upper trapezoid) MatrixT of size MxN. 
      By definition, the current MatrixT, A = QR.
   */
   void getQRDecomposition( MatrixT& Q, MatrixT& R );

   /// \return Number of rows in this MatrixT
   unsigned int rows() const { return this->numRows; }

   /// \return Number of columns in this MatrixT
   unsigned int cols() const { return this->numCols; }

   std::string toString( unsigned int width = 4 ) const;
   void toFile( const std::string& filename );
   void fromFile( const std::string& filename );
   T* getInternalMatrixPtr();

   /**
      Returns a column major MatrixT that is expanded such that the number
      of rows and columns are grown to their nearest multiple of byteAlignment.
      The original contents remain unchanged; the additional new padding elements,
      if any, are set to zeros.
   */
   MatrixT alignWithCUDAHalfWarp( unsigned int byteAlignment = 16 );
   
   /**
      Returns true iff both the number of rows and number of columns are
      multiples of byteAlignment.
   */
   bool isAlignedWithCUDAHalfWarp( unsigned int byteAlignment = 16 );
   
   /**
      Only valid after invocation to
      MatrixT<T>::alignWithCUDAHalfWarp().
      This is the number of rows before being expanded to the
      nearest multiple of byteAlignment via most recent call to
      MatrixT<T>::alignWithCUDAHalfWarp().
   */
   unsigned int getOriginalRowSize() { return this->originalRowSize; }
   
   /**
      Only valid after invocation to MatrixT<T>::alignWithCUDAHalfWarp().
      This is the number of columns before being expanded to the
      nearest multiple of byteAlignment via most recent call to
      MatrixT<T>::alignWithCUDAHalfWarp().
   */
   unsigned int getOriginalColSize() { return this->originalColSize; }

protected:
   T* m;
   unsigned int numRows;
   unsigned int numCols;

   /**
      Only valid after invocation to MatrixT<T>::alignWithCUDAHalfWarp().
      This is the number of rows before being expanded to the
      nearest multiple of byteAlignment via most recent call to
      MatrixT<T>::alignWithCUDAHalfWarp().
   */
   unsigned int originalRowSize;

   /**
      Only valid after invocation to MatrixT<T>::alignWithCUDAHalfWarp().
      This is the number of columns before being expanded to the
      nearest multiple of byteAlignment via most recent call to
      MatrixT<T>::alignWithCUDAHalfWarp().
   */
   unsigned int originalColSize;

};

} //namespace Aftr

#include "Matrix.cpptemplate.h"
#include "AftrUtilities.h" //access Gaussian Jordan Elimination operations

#ifdef AFTR_CONFIG_USE_BOOST
#pragma warning( push )
#pragma warning( disable: 4127 ) //ignore warning inside of boost code
#endif