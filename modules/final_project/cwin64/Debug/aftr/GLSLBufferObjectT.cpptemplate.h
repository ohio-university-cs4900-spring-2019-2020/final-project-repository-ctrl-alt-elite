#pragma once

Aftr::GLSLBufferObjectT::GLSLBufferObjectT( GLenum target, GLuint bufferObjectBindingLoc, GLuint programShaderHandle )
{
   this->bufferBindingLoc = bufferObjectBindingLoc;
   this->target = target;

   glGenBuffers( 1, &this->bufferObjectHandle );
   printOpenGLErrors( 0, NULL, AFTR_FILE_LINE_STR );

   //this->previousShaderPreserverHandle = UINT_MAX;
}

//Aftr::GLSLBufferObjectT::GLSLBufferObjectT( const GLSLBufferObjectT& toCopy )
//{
//   (*this) = toCopy;
//}

//Aftr::GLSLBufferObjectT& GLSLBufferObjectT::GLSLBufferObjectT =( const GLSLBufferObjectT& u )
//{
//   if( this != &u )
//   {
//      std::cout << "GLSLBufferObjectT:: operator = NOT DONE..." << std::endl;
//   }
//   return *this;
//}

Aftr::GLSLBufferObjectT::~GLSLBufferObjectT()
{
   glUnmapBuffer( this->target );
   glDeleteBuffers( 1, &this->bufferObjectHandle );
   printOpenGLErrors( 0, NULL, AFTR_FILE_LINE_STR );
}

void Aftr::GLSLBufferObjectT::bind()
{
   //glBindBuffer( this->target, this->bufferObjectHandle );
   glBindBufferBase( this->target, this->bufferBindingLoc, this->bufferObjectHandle );
}

void Aftr::GLSLBufferObjectT::unbind()
{
   glBindBufferBase( this->target, 0, this->bufferObjectHandle );
}

