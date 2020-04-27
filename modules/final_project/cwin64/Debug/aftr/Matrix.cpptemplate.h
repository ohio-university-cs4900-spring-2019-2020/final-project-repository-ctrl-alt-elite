#pragma  once

namespace Aftr
{

template< typename T>
MatrixT<T>::MatrixT()
{
   this->numRows = 1;
   this->numCols = 1;
   this->m = new T[ this->numRows * this->numCols ];
   this->setMatrixToZeros();
   this->originalRowSize = 0;
   this->originalColSize = 0;
}

template< typename T>
MatrixT<T>::MatrixT( unsigned int numRows, unsigned int numCols )
{
   if( numRows == 0 || numCols == 0 )
   {
      std::cout << "ERROR: MatrixT must have at least 1 row and 1 column\n"
         << "User tried to create matrix with " << numRows << " rows and "
         << numCols << " cols\n..."
         << "Press ENTER to exit...\n";
      std::cin.get();
      exit(-1);
   }

   this->numRows = numRows;
   this->numCols = numCols;
   this->m = new T[numRows * numCols];
   this->setMatrixToZeros();
   this->originalRowSize = 0;
   this->originalColSize = 0;
}

template< typename T>
MatrixT<T>::MatrixT( std::vector< std::vector< T > >& m )
{
   this->numRows = (unsigned int) m.size();
   this->numCols = (unsigned int) m[0].size();
   this->m = new T[numRows * numCols];

   for(size_t c = 0; c < m.size(); c++)
      for(size_t r = 0; r < m[c].size(); r++)
         this->at((unsigned int) r,(unsigned int) c) = m[r][c];

   this->originalRowSize = 0;
   this->originalColSize = 0;
}

template< typename T>
MatrixT<T>::MatrixT( std::vector< VectorT<T>* >* m )
{
   this->numRows = (unsigned int) m->size();
   this->numCols = 3;
   this->m = new T[numRows * numCols];

   for(size_t i = 0; i < m->size(); i++)
      for(int j = 0; j < 3; j++)
         this->at((unsigned int) i,j) = m->at((unsigned int ) i)->operator[](j);

   this->originalRowSize = 0;
   this->originalColSize = 0;
}

template< typename T>
MatrixT<T>::MatrixT( T* colMajor2DArray, unsigned int numRows, unsigned int numCols )
{
   this->m = colMajor2DArray;
   this->numRows = numRows;
   this->numCols = numCols;

   this->originalRowSize = numRows;
   this->originalColSize = numCols;
}

template< typename T>
MatrixT<T>::MatrixT( const MatrixT& m )
{
   this->m = NULL;
   this->numRows = 0;
   this->numCols = 0;
   *this = m;
}

template< typename T>
MatrixT<T>::~MatrixT()
{
   if( this->m != NULL ) { delete [] m; m = NULL; }
}

template< typename T>
T* MatrixT<T>::releaseOwnershipOfInternalColumnMajorData( unsigned int& outNumRows, unsigned int& outNumCols )
{
   T* ret = m;

   m = NULL;
   outNumRows = this->numRows;
   outNumCols = this->numCols;

   return ret;
}

template< typename T>
MatrixT<T>& MatrixT<T>::operator=( const MatrixT& m )
{
   if( this != &m )
   {
      this->resize( m.rows(), m.cols() );
      this->originalRowSize = m.originalRowSize;
      this->originalColSize = m.originalColSize;

      for( unsigned int c = 0; c < m.cols(); ++c )
         for( unsigned int r = 0; r < m.rows(); ++r )
            this->at(r,c) = m(r,c);
   }
   return *this;
}

template< typename T>
T& MatrixT<T>::operator()( unsigned int row, unsigned int col )
{
   return this->m[ col * numRows + row ];
}

template< typename T>
T MatrixT<T>::operator()( unsigned int row, unsigned int col ) const
{
   return this->m[ col * numRows + row ];
}

template< typename T>
T& MatrixT<T>::at( unsigned int row, unsigned int col )
{
   return this->m[ col * numRows + row ];
}

template< typename T>
T MatrixT<T>::at( unsigned int row, unsigned int col ) const
{
   return this->m[ col * numRows + row ];
}

#ifdef AFTR_CONFIG_USE_CUDA
template< typename T>
MatrixT<T> MatrixT<T>::multCUDA( const MatrixT& m )
   {
      // 2x3 * 3x2 matrix... 3==3 so resultant matrix will be 2x2
      // 2x5 * 5x4 matrix... 5==5 so resultant matrix will be 2x4

      if( this->cols() != m.rows() )
      {
         std::cout << "ERROR: MatrixT muliplication dimensions do not match.\n"
            << "EX: 2x3 matrix * 3x2 matrix... 3==3 so resultant matrix will be 2x2\n"
            << "EX: 2x5 matrix * 5x4 matrix... 5==5 so resultant matrix will be 2x4\n"
            << "Columns of first matrix must match rows of second matrix\n"
            << "Resultant matrix will have dimension of first matrix's rows\n"
            << "by second matrix's columns.\n"
            << "Press ENTER to exit...\n";
         std::cin.get();
         exit(-1);
      }

      T* dA = NULL; //this matrix
      T* dB = NULL; //matrix m (in passed variable)
      T* dC = NULL; //result

      //cudaError_t cudaMalloc(void** devPtr, size_t count)


      /* Allocate device memory for the matrices */
      //cublasStatus s0 = cublasAlloc( this->numRows * this->numCols, 
      //   sizeof(T), (void**)&dA );
      //cublasStatus s1 = cublasAlloc( m.numRows * m.numCols, 
      //   sizeof(T), (void**)&dB );
      //cublasStatus s2 = cublasAlloc( this->numRows * m.numCols, 
      //                               sizeof(T), (void**)&dC );

      //if( s0 != CUBLAS_STATUS_SUCCESS ||
      //    s1 != CUBLAS_STATUS_SUCCESS || 
      //    s2 != CUBLAS_STATUS_SUCCESS  )
      //{
      //   std::cout << "ERROR in MatrixT Class: CUDA BLAS: Failed to allocate memory on graphics hardware...\n";
      //   std::cout << "s0 - " << ManagerCUDA::toStringCublasStatus(s0) << std::endl;
      //   std::cout << "s1 - " << ManagerCUDA::toStringCublasStatus(s1) << std::endl;
      //   std::cout << "s2 - " << ManagerCUDA::toStringCublasStatus(s2) << std::endl;
      //   std::cout << "Press ENTER to exit...\n";
      //   std::cin.get();
      //   exit(-1);
      //}
      ////std::cout << "Allocated all graphics-side memory...\n";

      ///* Initialize the device matrices with the host matrices */
      //s0 = cublasSetVector( this->numRows * this->numCols, sizeof( T ),
      //                      this->m, 1, dA, 1 );
      //s1 = cublasSetVector( m.numRows * m.numCols, sizeof( T ),
      //                      m.m, 1, dB, 1 );

      ////cublasStatus
      ////cublasSetMatrix (int rows, int cols, int elemSize,
      ////const void *A, int lda, void *B,
      ////int ldb)
      ////s0 = cublasSetMatrix( this->numRows, this->numCols, sizeof( T ), this->m, this->numRows, dA, this->numRows );
      ////s1 = cublasSetMatrix( m.rows(), m.cols(), sizeof( T ), m.m, m.rows(), dB, m.rows() );

      //if ( s0 != CUBLAS_STATUS_SUCCESS ||
      //     s1 != CUBLAS_STATUS_SUCCESS )
      //{
      //   std::cout << "ERROR in MatrixT Class: CUDA BLAS: Failed to transfer main memory matrix to graphics memory...\n";
      //   std::cout << "s0 - " << ManagerCUDA::toStringCublasStatus(s0) << std::endl;
      //   std::cout << "s1 - " << ManagerCUDA::toStringCublasStatus(s1) << std::endl;
      //   std::cout << "Press ENTER to exit...\n";
      //   std::cin.get();
      //   exit(-1);
      //}

      ////std::cout << "Set matrices on graphics-side memory...\n";

      ////void cublasSgemm (char transa, char transb, int m, int n,
      ////                  int k, T alpha, const T *A, int lda,
      ////                  const T *B, int ldb, T beta,
      ////                  T *C, int ldc)

      ////op(A) is m x k matrix
      ////op(B) is k x n matrix
      ////C is m x n matrix
      ////lda,ldb,ldc are leading dimension of two-dimensional array (for column major format
      ////this is the number of rows in the corresponding matrix).
      //cublasSgemm( 'n', 'n', this->numRows, m.numCols, m.numRows, 1.0f, 
      //             dA, this->numRows,
      //             dB, m.numRows, 0, dC, this->numRows );
      ////std::cout << "cublasSgemm result is " << ManagerCUDA::toStringCublasStatus( cublasGetError() ) << "...\n";


      //MatrixT p( this->numRows, m.numCols );

      ///* Read the result back */
      //s0 = cublasGetVector( this->numRows * m.cols(), sizeof( T ),
      //                      dC, 1, p.m, 1 );

      //////cublasGetMatrix (int rows, int cols, int elemSize,
      //////const void *A, int lda, void *B,
      //////int ldb)
      ////s0 = cublasGetMatrix( this->numRows, m.numCols, sizeof( T ), dA, this->numRows, p.m, this->numRows );

      //if( s0 != CUBLAS_STATUS_SUCCESS )
      //{
      //   std::cout << "ERROR in MatrixT Class: CUDA BLAS: Failed to retrieve matrix product from graphics memory...\n";
      //   std::cout << "s0 - " << ManagerCUDA::toStringCublasStatus(s0) << std::endl;
      //   std::cout << "Press ENTER to exit...\n";
      //   std::cin.get();
      //   exit(-1);
      //}

      //s0 = cublasFree( dA );
      //s1 = cublasFree( dB );
      //s2 = cublasFree( dC );

      //if( s0 != CUBLAS_STATUS_SUCCESS ||
      //    s1 != CUBLAS_STATUS_SUCCESS || 
      //    s2 != CUBLAS_STATUS_SUCCESS  )
      //{
      //   std::cout << "ERROR in MatrixT Class: CUDA BLAS: Failed to free allocated graphics memory\n";
      //   std::cout << "s0 - " << ManagerCUDA::toStringCublasStatus(s0) << std::endl;
      //   std::cout << "s1 - " << ManagerCUDA::toStringCublasStatus(s1) << std::endl;
      //   std::cout << "s2 - " << ManagerCUDA::toStringCublasStatus(s2) << std::endl;
      //   std::cout << "Press ENTER to exit...\n";
      //   std::cin.get();
      //   exit(-1);
      //}

MatrixT p;
      return p;
   }
#endif

template< typename T>
MatrixT<T> MatrixT<T>::operator*( const MatrixT& m )
{
   #ifdef AFTR_CONFIG_USE_CUDA
      return this->multCUDA( m );
   #elif defined AFTR_CONFIG_USE_BOOST
      return this->multCPUBoostLIB( m );
   #else
      return this->multCPU( m );
   #endif
}

#ifdef AFTR_CONFIG_USE_BOOST
template< typename T>
MatrixT<T> MatrixT<T>::multCPUBoostLIB( const MatrixT& m )
   {
      using namespace boost::numeric::ublas;
      matrix< T > ma( this->numRows, this->numCols );
      matrix< T > mb( m.numRows, m.numCols );
      matrix< T > mz( this->numRows, m.numCols );

      for( unsigned int c = 0; c < this->numCols; ++c )
         for( unsigned int r = 0; r < this->numRows; ++r )
            ma( (size_t)r, (size_t)c ) = this->at( r, c );

      for( unsigned int c = 0; c < m.numCols; ++c )
         for( unsigned int r = 0; r < m.numRows; ++r )
            mb( (size_t)r, (size_t)c ) = m.at( r, c );

      mz = boost::numeric::ublas::prod( ma, mb );
      ma.clear(); mb.clear();
      MatrixT ret( this->numRows, m.numCols );

      for( unsigned int c = 0; c < m.numCols; ++c )
         for( unsigned int r = 0; r < this->numRows; ++r )
            ret( r, c ) = mz( (size_t)r, (size_t)c );

      mz.clear();

      return ret;
   }
#endif

template< typename T>
MatrixT<T> MatrixT<T>::multCPU( const MatrixT& m )
{
   // 2x3 * 3x2 matrix... 3==3 so resultant matrix will be 2x2
   // 2x5 * 5x4 matrix... 5==5 so resultant matrix will be 2x4

   if( this->cols() != m.rows() )
   {
      std::cout << "ERROR: MatrixT multiplication dimensions do not match.\n"
         << "EX: 2x3 matrix * 3x2 matrix... 3==3 so resultant matrix will be 2x2\n"
         << "EX: 2x5 matrix * 5x4 matrix... 5==5 so resultant matrix will be 2x4\n"
         << "Columns of first matrix must match rows of second matrix\n"
         << "Resultant matrix will have dimension of first matrix's rows\n"
         << "by second matrix's columns.\n"
         << "Press ENTER to exit...\n";
      std::cin.get();
      exit(-1);
   }

   unsigned int pRows = this->rows();
   unsigned int pCols = m.cols();
   MatrixT p( pRows, pCols );
   p.setMatrixToZeros();

   for( unsigned int c = 0; c < pCols; ++c )
      for( unsigned int r = 0; r < pRows; ++r )
         for( unsigned int i = 0; i < this->numCols; ++i )
               p(r,c) += this->at(r,i) * m(i,c);
   return p;
}

template< typename T>
MatrixT<T> MatrixT<T>::operator*=( const MatrixT& m )
{
   (*this) = (*this) * m;
   return *this;
}

template< typename T>
MatrixT<T> MatrixT<T>::operator*( T scalar )
{
   MatrixT p( this->numRows, this->numCols );

   for( unsigned int c = 0; c < this->numCols; ++c )
      for( unsigned int r = 0; r < this->numRows; ++r )
         p(r,c) = this->at(r,c) * scalar;

   return p;
}

template< typename T>
MatrixT<T> MatrixT<T>::operator*=( T scalar )
{
   for( unsigned int c = 0; c < this->numCols; ++c )
      for( unsigned int r = 0; r < this->numRows; ++r )
         this->at(r,c) *= scalar;

   return *this;
}

template< typename T>
MatrixT<T> MatrixT<T>::multiply( const MatrixT& m )
{
   return (*this) * m;
}

template< typename T>
MatrixT<T> MatrixT<T>::operator+( const MatrixT& m )
{   
   if(this->numCols == m.numCols && this->numRows == m.numRows)
   {
      MatrixT tmp(numRows, numCols);

      for(unsigned int c = 0; c < numCols; c++)
         for(unsigned int r = 0; r < numRows; r++)
            tmp.at(r,c) = this->at(r,c) + m.at(r,c);

      return tmp;
   }
   else
   {
      std::cout << "Error, trying to + matrices of mismatch dimensions." << std::endl
                << "Exiting." << std::endl;
      std::cin.get();
      exit(-1);
   }
}

template< typename T>
MatrixT<T> MatrixT<T>::operator+=( const MatrixT& m )
{
   if( this->numRows == m.numRows && this->numCols == m.numCols )
   {
      for( unsigned int c = 0; c < this->numCols; ++c )
         for( unsigned int r = 0; r < this->numRows; ++r )
            this->at(r,c) = this->at(r,c) + m.at(r,c);
      return *this;
   }
   else
   {
      std::cout << "MatrixT<T>::operator+= ERROR: Cannot add two matrices of\n"
                << "different dimensions...\nExiting";
      std::cin.get();
      exit(-1);
   }
}

template< typename T>
MatrixT<T> MatrixT<T>::operator-( const MatrixT& m )
{
   if(this->numCols == m.numCols && this->numRows == m.numRows)
   {
      MatrixT p(this->numRows, this->numCols);

      for(unsigned int c = 0; c < this->numCols; c++)
         for(unsigned int r = 0; r < this->numRows; r++)
            p(r,c) = this->at(r,c) - m(r,c);

      return p;
   }
   else
   {
      std::cout << "ERROR: MatrixT operator-... The two matrices have mismatched dimensions." << std::endl
                << "Exiting." << std::endl;
      std::cin.get();
      exit(-1);
   }
}

template< typename T>
MatrixT<T> MatrixT<T>::operator-=( const MatrixT& m )
{
   if( this->numRows == m.numRows && this->numCols == m.numCols )
   {
      for( unsigned int c = 0; c < this->numCols; ++c )
         for( unsigned int r = 0; r < this->numRows; ++r )
            this->at(r,c) = this->at(r,c) - m.at(r,c);
      return *this;
   }
   else
   {
      std::cout << "MatrixT<T>::operator-= ERROR: Cannot subtract two matrices of\n"
                << "different dimensions...\nExiting";
      std::cin.get();
      exit(-1);
   }
}

template< typename T>
MatrixT<T> MatrixT<T>::operator/( T s )
{
   MatrixT p( this->numRows, this->numCols );
   
   for( unsigned int c = 0; c < this->numCols; ++c )
      for( unsigned int r = 0; r < this->numRows; ++r )
         p.at(r,c) = this->at(r,c) / s;

   return p;
}

template< typename T>
MatrixT<T> MatrixT<T>::operator/=( T s )
{
   for( unsigned int c = 0; c < this->numCols; ++c )
      for( unsigned int r = 0; r < this->numRows; ++r )
         this->at(r,c) /= s;

   return *this;
}

template< typename T>
MatrixT<T> MatrixT<T>::transpose() const
{
   MatrixT p( this->numCols, this->numRows );

   for( unsigned int c = 0; c < this->numCols; ++c )
      for( unsigned int r = 0; r < this->numRows; ++r )
         p(c,r) = this->at(r,c);

   return p;
}

template< typename T>
bool MatrixT<T>::equals( const MatrixT& m, T epsilon )
{
   if( this != &m )
   {
      if( this->numRows == m.numRows && this->numCols == m.numCols )
      {
         for( unsigned int c = 0; c < this->numCols; ++c )
         {
            for( unsigned int r = 0; r < this->numRows; ++r )
            {
               if( fabs( this->at(r,c) - m.at(r,c) ) > epsilon )
                  return false;
            }
         }
      }
      else
         return false;
   }
   return true; //this matrix == this matrix
}

template< typename T>
MatrixT<T> MatrixT<T>::inverse()
{
#ifdef AFTR_CONFIG_USE_CUDA
   //if( this->numCols >= 128 )
   return this->inverseCUDA();
#endif
   return this->inverseCPU();
}

template< typename T>
MatrixT<T> MatrixT<T>::inverseCPU()
{
   if( this->numRows != this->numCols )
   {
      std::cout << "ERROR:template< typename T> MatrixT<T>::inverse(). Can only find inverse\n"
         << "of a MxM non-singular matrix. This matrix is not MxM\n"
         << "Press ENTER to exit...\n";
      std::cin.get();
      exit( -1 );
   }      

   MatrixT<T> inverseMat( this->numRows, this->numCols );
   if( this->isInvertable( inverseMat ) )
   {
      return inverseMat;
   }
   else
   {
      std::cout << "MatrixT<T>::inverse(). This MatrixT is singular\n"
         << "Cannot invert a singular matrix. Use MatrixT<T>::isInvertable()\n"
         << "to test if the matrix is invertible.\n"
         << "Press ENTER to exit...\n";
      std::cin.get();
      exit( -1 );
      inverseMat.setMatrixToIdentity();
      return inverseMat;
   }
}


template< typename T>
bool MatrixT<T>::isInvertable( MatrixT& invertedMatrix )
{
   //perform LU factorization followed by lu substitution to find inverse of 'this' matrix

   using namespace boost::numeric::ublas;
   matrix<T, column_major > A = make_matrix_from_pointer<column_major>( this->numRows, this->numCols, this->m ); // create a boost matrix based off internal matrix data of this instance
   permutation_matrix pm( A.size1() ); //permutation matrix populated during lu_factorization,

   // perform LU-factorization
   size_t res = lu_factorize( A, pm );
   if( res != 0 )         
      return false; //singular matrix, not invertible. Matrix A makes a copy of the data passed to it; therefore, 'this' matrix is unaltered and no leaks occur      

   // create identity matrix of "inverse"
   matrix< T, column_major > matInv = identity_matrix<T, column_major>( A.size1() );
   //inverse.assign(ublas::identity_matrix<T>(A.size1()));

   // back substitute to get the inverse
   lu_substitute( A, pm, matInv );

   invertedMatrix.resize( this->numRows, this->numCols );
   std::copy( matInv.data().begin(), matInv.data().end(), invertedMatrix.getInternalMatrixPtr() );
   return true;
}

#ifdef AFTR_CONFIG_USE_CUDA
template< typename T>
MatrixT<T> MatrixT<T>::inverseCUDA()
{
   if( this->numRows != this->numCols )
   {
      std::cout << "ERROR:template< typename T>  MatrixT<T>::inverse(). Can only find inverse\n"
         << "of a MxM non-singular matrix. This matrix is not MxM\n"
         << "Press ENTER to exit...\n";
      std::cin.get();
      exit( -1 );
   }

   //The CUDA-based algorithm excepts that the matrix is a square matrix
   //that is a square multiple of BLOCKSIZE, as defined in
   //MatrixInverseCUDA_GPUGausSeidel.h.
   //Therefore we have to pad the input to the nearest multiple of BLOCKSIZE
   //greater than or equal to numCols*numCols.

   //Find nearest multiple of BLOCKSIZE
   unsigned int numBlocks = (unsigned int)( this->numCols / BLOCKSIZE );
   if( this->numCols % BLOCKSIZE > 0 ) //if not evenly divisible, we need another block
      ++numBlocks;

   unsigned int dim = numBlocks*BLOCKSIZE;
   T* rowMajor = new T[dim * dim];
   memset( rowMajor, 0, sizeof( T ) * dim * dim );

   for( unsigned int i = 0; i < dim; ++i )
      rowMajor[i * dim + i] = 1.0f; //set the diagonal to be 1's initially


   //The GPU implementation expects a single array in row-major form...
   //Convert this matrix into a single row-major matrix
   for( unsigned int r = 0; r < this->numRows; ++r )
      for( unsigned int c = 0; c < this->numCols; ++c )
         rowMajor[r * dim + c] = this->at( r, c );

   //////std::cout << "Row Major TO GPU is (" << dim << "x" << dim << "):\n";
   //////for( unsigned int i = 0; i < dim*dim; ++i )
   //////{
   //////   if( i % dim == 0 )
   //////      std::cout << "\n";
   //////   std::cout << rowMajor[i] << " ";
   //////}
   //////std::cout << "\n\n";

   GPUGausSeidel( rowMajor, rowMajor, dim );

   //////std::cout << "Output FROM GPU is:\n";
   //////for( unsigned int i = 0; i < dim * dim; ++i )
   //////   std::cout << rowMajor[i] << " ";
   //////std::cout << "\n\n";

   //The result is in row major format.
   //Place the inverse in the result matrix; ensure the data is
   //internally stored column major.
   MatrixT ret( this->numRows, this->numCols );
   for( unsigned int r = 0; r < this->numRows; ++r )
      for( unsigned int c = 0; c < this->numCols; ++c )
         ret( r, c ) = rowMajor[r * dim + c];

   delete[] rowMajor; rowMajor = NULL;

   return ret;
}
#endif


template< typename T>
bool MatrixT<T>::gaussianJordanElimination( const MatrixT& a, MatrixT& x, const MatrixT& b )
{

   //unsigned int rows = 3;
   //unsigned int cols = 3;
   //double** lhs = new double*[rows];//(double**)malloc(sizeof(double*)* rows * cols );
   //for( size_t i = 0; i < cols; ++i )
   //   lhs[i] = new double[cols];

   //lhs[0][0] = a.x; lhs[0][1] = a.y; lhs[0][2] = a.z;
   //lhs[1][0] = b.x; lhs[1][1] = b.y; lhs[1][2] = b.z;
   //lhs[2][0] = c.x; lhs[2][1] = c.y; lhs[2][2] = c.z;

   double** lhs = new double*[ a.rows() ];
   for( unsigned int i = 0; i < a.rows(); ++i )
      lhs[i] = new double[ a.cols() ];

   for( unsigned int i = 0; i < a.rows(); ++i )
      for( unsigned int j = 0; j < a.cols(); ++j )
         lhs[i][j] = a( i, j );

   
   double** rhs = new double*[ b.rows() ];
   for( unsigned int i = 0; i < b.rows(); ++i )
      rhs[i] = new double[ b.cols() ];

   for( unsigned int i = 0; i < b.rows(); ++i )
      for( unsigned int j = 0; j < b.cols(); ++j )
         rhs[i][j] = b( i, j );

   if( Aftr::AftrUtilities::gaussianJordanElimination( lhs, rhs, a.rows(), b.cols() ) )
   {
      x.resize( b.rows(), b.cols() );

      for( unsigned int i = 0; i < x.rows(); ++i )
         for( unsigned int j = 0; j < x.cols(); ++j )
            x(i,j) = (T) rhs[i][j];
      return true;
   }
   
   return false;
}

template< typename T>
MatrixT<T>* MatrixT<T>::appendRowToTopRetMatrixPtr( T initialVal )
{
   MatrixT* x = new MatrixT( this->numRows + 1, this->numCols );
   
   //create new top row set to initial value
   for( unsigned int i = 0; i < x->cols(); ++i )
      x->at(0,i) = initialVal;

   //copy rest of matrix
   for( unsigned int c = 0; c < x->cols(); ++c )
      for( unsigned int r = 1; r < x->rows(); ++r )
         x->at(r,c) = this->m[ c * this->numRows + (r-1) ];

   return x;
}

template< typename T>
void MatrixT<T>::appendRowToTop( T initialVal )
{
   T* old = this->m;
   this->m = NULL;
   this->resize( this->numRows + 1, this->numCols );

   for( unsigned int i = 0; i < this->cols(); ++i )
      this->at(0,i) = initialVal;

   for( unsigned int c = 0; c < this->numCols; ++c )
      for( unsigned int r = 1; r < this->numRows; ++r )
         this->at(r,c) = old[ c * (this->numRows-1) + (r-1) ];

   delete [] old; old = NULL;
}

template< typename T>
MatrixT<T>* MatrixT<T>::appendRowToBottomRetMatrixPtr( T initialVal )
{
   MatrixT* x = new MatrixT( this->numRows + 1, this->numCols );

   //create new bottom row set to initial value
   for( unsigned int i = 0; i < x->cols(); ++i )
      x->at( x->rows()-1, i ) = initialVal;

   //copy rest of matrix
   for( unsigned int c = 0; c < x->cols(); ++c )
      for( unsigned int r = 0; r < x->rows()-1; ++r )
         x->at(r,c) = this->m[ c * (this->numRows) + r ];

   return x;
}

template< typename T>
void MatrixT<T>::appendRowToBottom( T initialVal )
{
   T* old = this->m;
   this->m = NULL;
   this->resize( this->numRows + 1, this->numCols );

   //create new bottom row set to initial value
   for( unsigned int i = 0; i < this->cols(); ++i )
      this->at( this->rows()-1, i ) = initialVal;

   //copy rest of matrix
   for( unsigned int c = 0; c < this->cols(); ++c )
      for( unsigned int r = 0; r < this->rows()-1; ++r )
         this->at(r,c) = old[ c * (this->numRows-1) + r ];

   delete [] old; old = NULL;
}

template< typename T>
MatrixT<T>* MatrixT<T>::appendColToLeftRetMatrixPtr( T initialVal )
{
   MatrixT* x = new MatrixT( this->numRows, this->numCols + 1 );

   //copy original matrix to x not touching first column
   for( unsigned int c = 1; c < x->cols(); ++c )
      for( unsigned int r = 0; r < x->rows(); ++r )
         x->at(r,c) = this->m[ (c-1) * this->numRows + r ];

   //set new column on left to initial value
   for( unsigned int i = 0; i < x->rows(); ++i )
      x->at(i,0) = initialVal;

   return x;
}

template< typename T>
void MatrixT<T>::appendColToLeft( T initialVal )
{
   T* old = this->m;
   this->m = NULL;
   this->resize( this->numRows, this->numCols + 1 );

   //copy original matrithis to this not touching first column
   for( unsigned int c = 1; c < this->cols(); ++c )
      for( unsigned int r = 0; r < this->rows(); ++r )
         this->at(r,c) = old[ (c-1) * (this->numRows) + r ];

   //set new column on left to initial value
   for( unsigned int i = 0; i < this->rows(); ++i )
      this->at(i,0) = initialVal;

   delete [] old; old = NULL;
}

template< typename T>
MatrixT<T>* MatrixT<T>::appendColToRightRetMatrixPtr( T initialVal )
{
   MatrixT* x = new MatrixT( this->numRows, this->numCols + 1 );

   //copy original matrix to x not touching last column
   for( unsigned int c = 0; c < x->cols(); ++c )
      for( unsigned int r = 0; r < x->rows(); ++r )
         x->at(r,c) = this->m[ c * this->numRows + r ];

   //set new column on right to initial value
   for( unsigned int i = 0; i < x->rows(); ++i )
      x->at(i, x->cols()-1) = initialVal;

   return x;
}

template< typename T>
void MatrixT<T>::appendColToRight( T initialVal )
{
   T* old = this->m;
   this->m = NULL;
   this->resize( this->numRows, this->numCols + 1 );

   //copy original matrithis to this not touching last column
   for( unsigned int c = 0; c < this->cols()-1; ++c )
      for( unsigned int r = 0; r < this->rows(); ++r )
         this->at(r,c) = old[ c * this->numRows + r ];

   //set new column on right to initial value
   for( unsigned int i = 0; i < this->rows(); ++i )
      this->at(i, this->cols()-1) = initialVal;

   delete [] old; old = NULL;
}

template< typename T>
void MatrixT<T>::resize( unsigned int numRows, unsigned int numCols )
{
   if( this->numRows == numRows && this->numCols == numCols )
      return;

   this->numRows = numRows;
   this->numCols = numCols;
   if( m != NULL ) { delete [] this->m; this->m = NULL; }
   this->m = new T[ this->numRows * this->numCols ];
}

template< typename T>
void MatrixT<T>::setMatrixToZeros()
{
   this->setMatrixTo( 0 );
}

template< typename T>
void MatrixT<T>::setMatrixToOnes()
{
   this->setMatrixTo( 1 );
}

template< typename T>
void MatrixT<T>::setMatrixTo( T value )
{
   for( unsigned int r = 0; r < this->numRows; ++r )
      for( unsigned int c = 0; c < this->numCols; ++c )
         this->at(r,c) = value;
}

template< typename T>
void MatrixT<T>::setMatrixToIdentity()
{
   this->setMatrixToZeros();

   unsigned int c = std::min( this->rows(), this->cols() );
   for( unsigned int i = 0; i < c; ++i )
      this->at(i,i) = 1.0f;
}

template< typename T>
void MatrixT<T>::setMatrixToColumnMajor2DArray( T* colMajor2DArray, unsigned int numRows, unsigned int numCols )
{
   if( this->m != NULL ) { delete [] this->m; this->m = NULL; }

   this->m = colMajor2DArray;
   this->numRows = numRows;
   this->numCols = numCols;
}

template< typename T>
MatrixT<T> MatrixT<T>::getColumnVector( unsigned int col )
{
   if( col >= this->numCols )
   {
      std::cout << "ERROR:  MatrixT<T>::getColumnVector...\n"
         << "MatrixT has " << this->numCols << " columns.\n"
         << "User attempted to access column " << col << ".\n"
         << "This index is outside of the matrix...\n"
         << "Press ENTER to exit...\n";
      std::cin.get();
      exit(-1);
   }

   MatrixT p( this->numRows, 1 );

   for( unsigned int r = 0; r < this->numRows; ++r )
      p(r,0) = this->at(r,col);

   return p;
}

template< typename T>
MatrixT<T> MatrixT<T>::getRowVector( unsigned int row )
{
   if( row >= this->numRows )
   {
      std::cout << "ERROR: MatrixT<T>::getRowVector...\n"
         << "MatrixT has " << this->numRows << " rows.\n"
         << "User attempted to access row " << row << ".\n"
         << "This index is outside of the matrix...\n"
         << "Press ENTER to exit...\n";
      std::cin.get();
      exit(-1);
   }

   MatrixT p( 1, this->numCols );

   for( unsigned int c = 0; c < this->numCols; ++c )
      p(0,c) = this->at(row,c);

   return p;
}

template< typename T>
MatrixT<T> MatrixT<T>::getSubMatrix( unsigned int row, unsigned int numRows, unsigned int col, unsigned int numCols )
{
   if( row+numRows > this->numRows )
   {
      std::cout << "ERROR: MatrixT<T>::getSubMatrix...\n"
         << "MatrixT has " << this->numRows << " rows.\n"
         << "User attempted to access row " << row+numRows << ".\n"
         << "This is outside of the matrix...\n"
         << "Press ENTER to exit...\n";
      std::cin.get();
      exit(-1);
   }
   else if( col+numCols > this->numCols )
   {
      std::cout << "ERROR: MatrixT<T>::getSubMatrix...\n"
         << "MatrixT has " << this->numCols << " columns.\n"
         << "User attempted to access column " << col+numCols << ".\n"
         << "This is outside of the matrix...\n"
         << "Press ENTER to exit...\n";
      std::cin.get();
      exit(-1);
   }
   else if( numRows <= 0 || numCols <= 0 )
   {
      std::cout << "ERROR: MatrixT<T>::getSubMatrix...\n"
         << "numRows to be retrieved must be at least 1\n"
         << "numCols to be retrieved must be at least 1\n"
         << "Press ENTER to exit...\n";
      std::cin.get();
      exit(-1);
   }

   MatrixT p( numRows, numCols );

   for( unsigned int r = row; r < row + numRows; ++r )
      for( unsigned int c = col; c < col + numCols; ++c )
         p(r-row,c-col) = this->at(r,c);

   return p;
}


template< typename T>
void MatrixT<T>::getQRDecomposition( MatrixT& Q, MatrixT& R )
{
#ifdef AFTR_CONFIG_USE_ALGLIB_2_0_0
   ap::real_2d_array b;
   ap::real_1d_array taub;
   ap::real_2d_array q;
   ap::real_2d_array r;
   ap::real_2d_array q2;

   //Populate alglib matrix 'b' with this matrix's data
   b.setbounds( 0, this->numRows, 0, this->numCols );
   for( unsigned int r = 0; r < this->numRows; ++r )
      for( unsigned int c = 0; c < this->numCols; ++c )
         b(r,c) = this->at(r,c);

   //makeacopy(a, m, n, b);
   rmatrixqr(b, this->numRows, this->numCols, taub);
   rmatrixqrunpackq(b, this->numRows, this->numCols, taub, this->numRows, q);
   rmatrixqrunpackr(b, this->numRows, this->numCols, r);

   //Q is an orthogonal matrix of size MxM (M are rows, N are cols).
   //R is an upper triangular (or upper trapezoid) matrix of size MxN.
   Q.resize( this->numRows, this->numRows );
   R.resize( this->numRows, this->numCols );

   for( unsigned int r = 0; r < this->numRows; ++r )
      for( unsigned int k = 0; k < this->numRows; ++k )
         Q(r,k) = (T) q(r,k);

   for( unsigned int row = 0; row < this->numRows; ++row )
      for( unsigned int c = 0; c < this->numCols; ++c )
         R(row,c) = (T) r(row,c);
#else
   std::cout << "WARNING: AFTR_CONFIG_USE_ALGLIB_2_0_0 is NOT DEFINED. NO QR Decomposition\n"
      << "   is supported in MatrixT class! Recompile engine with AFTR_CONFIG_USE_ALGLIB_2_0_0\n"
      << "   defined for MatrixT<T>::getQRDecomposition(...) support...\n"
      << " NOT touching MatrixT<T>& Q or MatrixT<T>& R and returning now...\n";
#endif
}

template< typename T>
std::string MatrixT<T>::toString( unsigned int width ) const
{
   char str[1024];
   std::stringstream strWidth;
   strWidth << width;

   std::string format = "%.";
   format.append( strWidth.str() );
   format.append( "f" );

   std::stringstream ss;

   for( unsigned int r = 0; r < this->numRows; ++r )
   {
      for( unsigned int c = 0; c < this->numCols; ++c )
      {
         sprintf( str, format.c_str(), this->at(r,c) );
         ss << str << " ";
      }
      ss << "\n";
   }

   std::string s = ss.str();
   return s;
}

template< typename T>
MatrixT<T> MatrixT<T>::sumColumns()
{
   MatrixT temp(1, numCols);

   for(unsigned int i = 0; i < numCols; i++)
      for(unsigned int j = 0; j < numRows; j++)
      {
         temp.at(0, i) += this->at(j,i);
      }

   return temp;
}

template< typename T>
MatrixT<T> MatrixT<T>::componentWiseDivide(MatrixT& m)
{
   if(numRows != m.rows() || numCols != m.cols())
   {
      std::cout << "mismatched matrix dimensions, exiting!" << std::endl;
      exit(187);
   }

   MatrixT temp(this->numRows, this->numCols);

   for(unsigned int i = 0; i < numRows; i++)
      for(unsigned int j = 0; j < numCols; j++)
         temp(i,j) = this->at(i,j) / m.at(i,j);

   return temp;
}

template< typename T>
MatrixT<T> MatrixT<T>::normalizeEachRow() const
{
   MatrixT ret( *this );
   for( unsigned int r = 0; r < ret.numRows; ++r )
   {
      T mag = ret.getMagnitudeOfRow( r );
      for( unsigned int c = 0; c < ret.numCols; ++c )
         ret.at(r,c) /= mag;
   }
   return ret;
}

template< typename T>
void MatrixT<T>::normalizeMeEachRow()
{
   for( unsigned int r = 0; r < this->numRows; ++r )
   {
      T mag = this->getMagnitudeOfRow( r );
      for( unsigned int c = 0; c < this->numCols; ++c )
         this->at(r,c) /= mag;
   }
}

template< typename T>
T MatrixT<T>::getMagnitudeOfRow( unsigned int row ) const
{
   return sqrt( this->getMagnitudeSquaredOfRow( row ) );
}

template< typename T>
T MatrixT<T>::getMagnitudeSquaredOfRow( unsigned int row ) const
{
   T magSq = 0;
   for( unsigned int c = 0; c < this->numCols; ++c )
      magSq += this->at( row, c ) * this->at( row, c );
   return magSq;
}

template< typename T>
MatrixT<T> MatrixT<T>::normalizeEachColumn() const
{
   MatrixT ret( *this );
   for( unsigned int c = 0; c < ret.numCols; ++c )
   {
      T mag = ret.getMagnitudeOfColumn( c );
      for( unsigned int r = 0; r < ret.numRows; ++r )
         ret.at(r,c) /= mag;
   }
   return ret;
}

template< typename T>
void MatrixT<T>::normalizeMeEachColumn()
{
   for( unsigned int c = 0; c < this->numCols; ++c )
   {
      T mag = this->getMagnitudeOfColumn( c );
      for( unsigned int r = 0; r < this->numRows; ++r )
         this->at(r,c) /= mag;
   }
}

template< typename T>
T MatrixT<T>::getMagnitudeOfColumn( unsigned int col ) const
{
   return sqrt( this->getMagnitudeSquaredOfColumn( col ) );
}

template< typename T>
T MatrixT<T>::getMagnitudeSquaredOfColumn( unsigned int col ) const
{
   T magSq = 0;
   for( unsigned int r = 0; r < this->numRows; ++r )
      magSq += this->at( r, col ) * this->at( r, col );
   return magSq;
}

template< typename T>
void MatrixT<T>::toFile( const std::string& filename)
{
   std::ofstream fout;
   fout.open(filename.c_str());
   if(fout.fail())
   {
      std::cout << "Error opening file: " << filename << std::endl;
      std::cout << "Not writing to file." << std::endl;
      std::cin.get();
   }
   else
   {
      for(unsigned int i = 0; i < this->rows(); i++)
      {
         for(unsigned int j = 0; j < this->cols(); j++)
         {
            fout << at(i,j);
            if(j != this->cols() - 1)
               fout << ",";
         }
         fout << std::endl;
      }
   }
}

template< typename T>
void MatrixT<T>::fromFile( const std::string& filename )
{
   std::ifstream fin;
   fin.open(filename.c_str());
   T x;
   if(fin.fail())
   {
      std::cout << "Error opening file: " << filename << std::endl;
      std::cout << "Exiting program." << std::endl;
      std::cin.get();
      exit(123);
   }
   else
   {
      fin >> x;
      std::vector< std::vector< T > > outer;
      std::vector< T > inner;
      while(!fin.eof())
      {
         inner.push_back(x);
         if(fin.peek() == ',')
            fin.get();
         else
         {
            outer.push_back(inner);
            inner.clear();
            fin.get();
         }
         fin >> x;
      }

      this->resize((unsigned int ) outer.size(), (unsigned int) outer[0].size());
      for(size_t i = 0; i < outer.size(); i++)
         for(size_t j = 0; j < outer[i].size(); j++)
            this->at((unsigned int) i, (unsigned int) j) = outer[i][j];
   }
}

template< typename T>
T* MatrixT<T>::getInternalMatrixPtr()
{
   return this->m;
}

template< typename T>
MatrixT<T> MatrixT<T>::alignWithCUDAHalfWarp( unsigned int byteAlignment )
{
   //Grow dimensions to the nearest half-warp boundary sizes of the
   //rows and columns

   unsigned int quotient = this->numRows / byteAlignment;
   unsigned int remainder = this->numRows % byteAlignment;
   if( remainder > 0 )
      ++quotient;
   quotient *= byteAlignment;
   unsigned int newRowSize = quotient;

   quotient = this->numCols / byteAlignment;
   remainder = this->numCols % byteAlignment;
   if( remainder > 0 )
      ++quotient;
   quotient *= byteAlignment;
   unsigned int newColSize = quotient;

   MatrixT a;
   a.originalRowSize = this->numRows;
   a.originalColSize = this->numCols;
   a.resize( newRowSize, newColSize );
   a.setMatrixToZeros();

   for( unsigned int c = 0; c < this->numCols; ++c )
      for( unsigned int r = 0; r < this->numRows; ++r )
         a(r,c) = this->at(r,c);

   return a;
}

} //namespace Aftr
