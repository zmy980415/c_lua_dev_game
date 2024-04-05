
#ifndef ENGINE_H_
#define ENGINE_H_
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "graphics.h"
/*
	初始化lua
	1. 获取入口lua文件
	2. 如果没问题，返回被调用函数的指针结构体
*/

typedef struct Engine {
	int id;
	lua_State* L;
	void (*funInit)(lua_State* L);
	void (*funUpdate)(lua_State* L,float dt);
	void (*funDraw)(lua_State* L);
	struct Engine_Config* engineConfig;
} Engine;



//配置文件结构
typedef struct Engine_Config {
	int width;
	int height;
	char *title;
}Engine_Config;

/*******************内置的模块上******************/


//注册的绘制模块函数
static const struct luaL_Reg griphics[] = {
	{"rectangle",rectangle},
	{"circle",circle},
	{"point",point},
	{"setColor",setColor},
	{"newImage",newImage},
	{"drawImage",drawImage},
	{NULL,NULL}
};



static const struct luaL_Reg zmy[] = {
	{"griphics",griphics},
	{NULL,NULL}
};
/********************内置模块下********************/

//LUALIB_API int luaopen_griphics(lua_State* L);

/******************初始化方法**********************/
//返回支持lua操作的指针结构体
Engine * init();

#endif // ENGINE_H_
