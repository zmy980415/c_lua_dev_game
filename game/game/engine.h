
#ifndef ENGINE_H_
#define ENGINE_H_
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "graphics.h"
/*
	��ʼ��lua
	1. ��ȡ���lua�ļ�
	2. ���û���⣬���ر����ú�����ָ��ṹ��
*/

typedef struct Engine {
	int id;
	lua_State* L;
	void (*funInit)(lua_State* L);
	void (*funUpdate)(lua_State* L,float dt);
	void (*funDraw)(lua_State* L);
	struct Engine_Config* engineConfig;
} Engine;



//�����ļ��ṹ
typedef struct Engine_Config {
	int width;
	int height;
	char *title;
}Engine_Config;

/*******************���õ�ģ����******************/


//ע��Ļ���ģ�麯��
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
/********************����ģ����********************/

//LUALIB_API int luaopen_griphics(lua_State* L);

/******************��ʼ������**********************/
//����֧��lua������ָ��ṹ��
Engine * init();

#endif // ENGINE_H_
