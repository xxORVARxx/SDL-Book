
/* To compile use: 
 *   $ g++ -std=c++11 -o test *.cpp -lSDL2 -lSDL2_image
 *
 * To check if packages/liberys are installed:  
 *   $ dpkg -l | grep THE-PACKAGE-NAME
 * To see available packages/liberys:  
 *   $ apt-cache search THE-PACKAGE-NAME
 *
 * Needed Liberys:
 *   libsdl2-dev
 *   libsdl2-image-dev
 *   libglm-dev
 *  
 * Other good Liberys:
 *   libglew-dev
 *   libsdl2-ttf-dev
 *   libsdl2-mixer-dev
 *   libsdl2-net-dev
 *   libsdl2-gfx-dev
 *   libfreetype6-dev
 */

#ifndef INIT_H
#define INIT_H



#define GLM_FORCE_CXX11 
#include <glm/glm.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <xml/parser>
#include <xml/serializer>

#include <iostream>
#include <algorithm>
#include <functional>

#include <string>
#include <vector>
#include <map>

#include <memory>
#include <assert.h> 

#include "The_xx_namespace.h"
#include "xx_Exceptions.h"
#include "xx_String_cast.h"



using byte_t = signed char;
using integer_t = long int;
using real_t = double;
using string_t = xx::String_cast;



enum class Type_e
{
    VOID = 0,
    BYTE,
    INTEGER,
    REAL,
    STRING
};



template< typename T > 
Type_e What_type();



#endif

/* Open GL:
GLboolean   1+

GLbyte      8
GLubyte     8

GLshort     16
GLushort    16

GLint       32
GLuint      32

GLint64     64
GLuint64    64
*/

/* SDL:
Uint8
Uint16
Uint32

Sint32
*/
