
#include "engine.h"
#include <stdio.h>
#include <stdlib.h>

//============================
//�����ļ�
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
		// ��ȫ�ֱ���confѹ��ջ��
		lua_getglobal(L, "conf");
		// ���ջ��Ԫ���ǲ���һ����Lua�еĶ���
		if (lua_istable(L, -1)) {
			// ����Lua�ű�����һ����Ϊ 'config' ��table�������������ȡ���� 'field' �ֶ�
			lua_getfield(L, -1, "width"); // ��ȡtable�� 'width' �ֶΣ�������ֵѹ���ջ
			int width = lua_tonumber(L, -1);
			lua_getfield(L, -2, "height"); // ��ȡtable�� 'height' �ֶΣ�������ֵѹ���ջ
			int height = lua_tonumber(L, -1);
			lua_getfield(L, -3, "title"); // ��ȡtable�� 'title' �ֶΣ�������ֵѹ���ջ
			const char* title = lua_tostring(L, -1);
			printf("title:%s,width:%d,height:%d\n", title, width, height);
			engineConfig->height = height;
			engineConfig->title = title;
			engineConfig->width = width;
		}
		else {
			// ������conf����һ����
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
	// ���������������������ֵ��������������
	lua_pcall(L, 0, 0, 0);
}
void zmy_update(lua_State* L,float dt)
{
	lua_getglobal(L, "update");
	// ���������������������ֵ��������������
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
	// ��Ϊ��֪����ô�ѱ�ע�ᵽ���У����Բ���ȡ�ɵķ���
	luaL_dostring(L, "zmy = {} \n zmy.graphics = graphics \n graphics=nil");
}

Engine * init()
{
	lua_State* L = luaL_newstate();
	// �������к�����
	luaL_openlibs(L);

	// ע�ᵽȫ��
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