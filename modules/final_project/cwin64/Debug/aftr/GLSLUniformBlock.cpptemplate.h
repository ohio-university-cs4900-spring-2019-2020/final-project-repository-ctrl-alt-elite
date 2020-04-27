#pragma  once

template <class UNIFORM_BLOCK_STRUCT>
Aftr::GLSLUniformBlockT<UNIFORM_BLOCK_STRUCT>::GLSLUniformBlockT( const std::string& uniformBlockName, GLuint uniformBlockBinding ) : uniformBlockName( uniformBlockName ),
                                                                                                                   uniformBlockBinding( uniformBlockBinding )
{
   //A few helpful Links:
   //http://www.arcsynthesis.org/gltut/Positioning/Tut07%20Shared%20Uniforms.html
   //http://www.opentk.com/node/2926

   glGenBuffers( 1, &this->uboHandle );
   glBindBuffer( GL_UNIFORM_BUFFER, this->uboHandle );
   glBufferData( GL_UNIFORM_BUFFER, sizeof( this->buffer ), (const GLvoid*)&this->buffer, GL_DYNAMIC_DRAW );
   glBindBufferBase( GL_UNIFORM_BUFFER, this->uniformBlockBinding, this->uboHandle ); // associate Buffer Object with Uniform Block
   glBindBuffer( GL_UNIFORM_BUFFER, 0 );
}

template< class UNIFORM_BLOCK_STRUCT >
Aftr::GLSLUniformBlockT<UNIFORM_BLOCK_STRUCT>::~GLSLUniformBlockT()
{
   glDeleteBuffers( 1, &this->uboHandle );
   this->uboHandle = 0;
}

template< class UNIFORM_BLOCK_STRUCT >
void Aftr::GLSLUniformBlockT<UNIFORM_BLOCK_STRUCT>::sendUniformBlockToGL()
{
   glBindBuffer( GL_UNIFORM_BUFFER, this->uboHandle );
   glBindBufferBase( GL_UNIFORM_BUFFER, this->uniformBlockBinding, this->uboHandle ); //ensure this->uboHandle (buffer handle) uses idx at block binding point
   glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeof( this->buffer ), (const GLvoid*)&this->buffer );
   glBindBuffer( GL_UNIFORM_BUFFER, 0 );   
}
