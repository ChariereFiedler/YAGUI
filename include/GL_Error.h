#ifndef INCLUDEGL_H
#define	INCLUDEGL_H



#ifndef GL_CHECK_ERROR

		#define GL_CHECK_ERROR { GLuint glError = glGetError(); \
			assert(glError != 0x0500 && "INVALID_ENUM");		\
			assert(glError != 0x0501 && "INVALID_VALUE");		\
			assert(glError != 0x0502 && "INVALID_OPERATION");	\
			assert(!glError); }
		/* Errors
			#define GL_NO_ERROR 				0
			#define GL_INVALID_ENUM				0x0500
			#define GL_INVALID_VALUE			0x0501
			#define GL_INVALID_OPERATION		0x0502
			#define GL_STACK_OVERFLOW			0x0503
			#define GL_STACK_UNDERFLOW			0x0504
			#define GL_OUT_OF_MEMORY			0x0505
		 */
#endif

#endif	/* INCLUDEGL_H */
