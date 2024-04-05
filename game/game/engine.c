
#include "engine.h"
#include <stdio.h>
#include <stdlib.h>

//============================
//配置文件
Engine_Config* engineConfig = NULL;
Engine_Config *init_config(lua_State* L)
{
	printf("-------");
	engineConfig = (Engine_Config*)malloc(sizeof(Engine_Config));
	if (!engineConfig)
	{
		printf("init config error.");
		exit(-1);
	}
	engineConfig->height = 600;
	engineConfig->width = 800;
	engineConfig->title = "game title";
	char *confFileName = "conf.lua";
	char* mode = "r";

	FILE* fp = fopen(confFileName, mode);
	if (fp != NULL)
	{
		printf("init conf.lua");
		fclose(fp);
		int code  = luaL_dofile(L, confFileName);
		printf("code =%d\n", code);
		if (code != LUA_OK) {
			lua_close(L);
			return NULL;
		}
		// 将全局变量conf压入栈顶
		lua_getglobal(L, "conf");
		// 检查栈顶元素是不是一个表（Lua中的对象）
		if (lua_istable(L, -1)) {
			// 假设Lua脚本中有一个名为 'config' 的table，并且我们想获取它的 'field' 字段
			lua_getfield(L, -1, "width"); // 获取table的 'width' 字段，并将其值压入堆栈
			int width = lua_tonumber(L, -1);
			lua_getfield(L, -2, "height"); // 获取table的 'height' 字段，并将其值压入堆栈
			int height = lua_tonumber(L, -1);
			lua_getfield(L, -3, "title"); // 获取table的 'title' 字段，并将其值压入堆栈
			const char* title = lua_tostring(L, -1);
			printf("title:%s,width:%d,height:%d\n", title, width, height);
			engineConfig->height = height;
			engineConfig->title = title;
			engineConfig->width = width;
		}
		else {
			// 错误处理：conf不是一个表
			printf("==s\n");
		}

	}
	return engineConfig;
}

//============================






void zmy_init(lua_State* L)
{
	lua_getglobal(L, "init");
	//printf("zmy.init\n");
	// 虚拟机，参数个数，返回值个数，错误处理函数
	lua_pcall(L, 0, 0, 0);
}
void zmy_update(lua_State* L,float dt)
{
	lua_getglobal(L, "update");
	// 虚拟机，参数个数，返回值个数，错误处理函数
	lua_pushnumber(L, dt);
	lua_pcall(L, 1, 0, 0);
}
void zmy_draw(lua_State* L)
{
	lua_getglobal(L, "draw");
	lua_pcall(L, 0, 0, 0);
}


LUALIB_API int luaopen_graphics(lua_State* L)
{
	luaL_newlib(L, griphics);
	return 1;
}
void append(char* s1, char* s2) {
	strcat(s1, s2);
}
void registerLib(lua_State* L)
{
	luaL_requiref(L, "graphics", luaopen_graphics, 1);
	// 因为不知道怎么把表注册到表中，所以采用取巧的方法
	luaL_dostring(L, "zmy = {} \n zmy.graphics = graphics \n graphics=nil");
}

Engine * init()
{
	lua_State* L = luaL_newstate();
	// 载入所有函数库
	luaL_openlibs(L);

	// 注册到全局
	registerLib(L);
	

	Engine* engine = (Engine*)malloc(sizeof(Engine));
	if (engine == NULL)
	{
		printf("init fail for game engine\n");
		exit(-1);
	}
	Engine_Config *engineConfig = init_config(L);
	engine->engineConfig = engineConfig;
	engine->funInit = zmy_init;
	engine->funUpdate = zmy_update;
	engine->funDraw = zmy_draw;
	engine->L = L;

	char* mainFileName = "main.lua";
	char* mode = "r";
	FILE * fp = fopen(mainFileName, mode);
	if (fp != NULL)
	{
		printf("init... exist main.lua");
		fclose(fp);

		int mainCode = luaL_dofile(L, mainFileName);

	}
	else
	{
		printf("init... no main.lua");
	}
	
	return engine;

}