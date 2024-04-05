
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <lua.h>



#include <SDL.h>


void rectangle(lua_State* L);
void circle(lua_State* L);
void point(lua_State* L);

void setColor(lua_State* L);

int newImage(lua_State* L);
void drawImage(lua_State* L);

#endif // !GRAPHICS_H_

