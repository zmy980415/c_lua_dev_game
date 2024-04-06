
#include "engine.h"
#include <stdio.h>
#include <stdlib.h>

//============================
//配置文件
Engine_Config* engineConfig = NULL;
Engine_Config *init_config(lua_State* L)
{
	//printf("-------");
	engineConfig = (Engine_Config*)malloc(sizeof(Engine_Config));
	if (!engineConfig)
	{
		printf("init config error.\n");
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
		//printf("init conf.lua");
		fclose(fp);
		int code  = luaL_dofile(L, confFileName);
		//printf("code =%d\n", code);
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
			//printf("title:%s,width:%d,height:%d\n", title, width, height);
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
	lua_pcall(L, 0, 0, 0);
}
void zmy_update(lua_State* L,float dt)
{
	lua_getglobal(L, "update");
	lua_pushnumber(L, dt);
	lua_pcall(L, 1, 0, 0);
}
void zmy_draw(lua_State* L)
{
	lua_getglobal(L, "draw");
	lua_pcall(L, 0, 0, 0);
}
void zmy_keyDown(lua_State* L,int keyCode)
{
	lua_getglobal(L, "keyDown");
	lua_pushinteger(L, keyCode);
	lua_pcall(L, 1, 0, 0);
}

void init_keys_to_lua(lua_State* L)
{
	luaL_dostring(L, "keys = {\
        key_UNKNOWN = 0;\
        key_FIRST = 0;\
        key_BACKSPACE = 8;\
        key_TAB = 9;\
        key_CLEAR = 12;\
        key_RETURN = 13;\
        key_PAUSE = 19;\
        key_ESCAPE = 27;\
        key_SPACE = 32;\
        key_EXCLAIM = 33;\
        key_QUOTEDBL = 34;\
        key_HASH = 35;\
        key_DOLLAR = 36;\
        key_AMPERSAND = 38;\
        key_QUOTE = 39;\
        key_LEFTPAREN = 40;\
        key_RIGHTPAREN = 41;\
        key_ASTERISK = 42;\
        key_PLUS = 43;\
        key_COMMA = 44;\
        key_MINUS = 45;\
        key_PERIOD = 46;\
        key_SLASH = 47;\
        key_0 = 48;\
        key_1 = 49;\
        key_2 = 50;\
        key_3 = 51;\
        key_4 = 52;\
        key_5 = 53;\
        key_6 = 54;\
        key_7 = 55;\
        key_8 = 56;\
        key_9 = 57;\
        key_COLON = 58;\
        key_SEMICOLON = 59;\
        key_LESS = 60;\
        key_EQUALS = 61;\
        key_GREATER = 62;\
        key_QUESTION = 63;\
        key_AT = 64;\
        key_LEFTBRACKET = 91;\
        key_BACKSLASH = 92;\
        key_RIGHTBRACKET = 93;\
        key_CARET = 94;\
        key_UNDERSCORE = 95;\
        key_BACKQUOTE = 96;\
        key_a = 97;\
        key_b = 98;\
        key_c = 99;\
        key_d = 100;\
        key_e = 101;\
        key_f = 102;\
        key_g = 103;\
        key_h = 104;\
        key_i = 105;\
        key_j = 106;\
        key_k = 107;\
        key_l = 108;\
        key_m = 109;\
        key_n = 110;\
        key_o = 111;\
        key_p = 112;\
        key_q = 113;\
        key_r = 114;\
        key_s = 115;\
        key_t = 116;\
        key_u = 117;\
        key_v = 118;\
        key_w = 119;\
        key_x = 120;\
        key_y = 121;\
        key_z = 122;\
        key_DELETE = 127;\
        key_WORLD_0 = 160;\
        key_WORLD_1 = 161;\
        key_WORLD_2 = 162;\
        key_WORLD_3 = 163;\
        key_WORLD_4 = 164;\
        key_WORLD_5 = 165;\
        key_WORLD_6 = 166;\
        key_WORLD_7 = 167;\
        key_WORLD_8 = 168;\
        key_WORLD_9 = 169;\
        key_WORLD_10 = 170;\
        key_WORLD_11 = 171;\
        key_WORLD_12 = 172;\
        key_WORLD_13 = 173;\
        key_WORLD_14 = 174;\
        key_WORLD_15 = 175;\
        key_WORLD_16 = 176;\
        key_WORLD_17 = 177;\
        key_WORLD_18 = 178;\
        key_WORLD_19 = 179;\
        key_WORLD_20 = 180;\
        key_WORLD_21 = 181;\
        key_WORLD_22 = 182;\
        key_WORLD_23 = 183;\
        key_WORLD_24 = 184;\
        key_WORLD_25 = 185;\
        key_WORLD_26 = 186;\
        key_WORLD_27 = 187;\
        key_WORLD_28 = 188;\
        key_WORLD_29 = 189;\
        key_WORLD_30 = 190;\
        key_WORLD_31 = 191;\
        key_WORLD_32 = 192;\
        key_WORLD_33 = 193;\
        key_WORLD_34 = 194;\
        key_WORLD_35 = 195;\
        key_WORLD_36 = 196;\
        key_WORLD_37 = 197;\
        key_WORLD_38 = 198;\
        key_WORLD_39 = 199;\
        key_WORLD_40 = 200;\
        key_WORLD_41 = 201;\
        key_WORLD_42 = 202;\
        key_WORLD_43 = 203;\
        key_WORLD_44 = 204;\
        key_WORLD_45 = 205;\
        key_WORLD_46 = 206;\
        key_WORLD_47 = 207;\
        key_WORLD_48 = 208;\
        key_WORLD_49 = 209;\
        key_WORLD_50 = 210;\
        key_WORLD_51 = 211;\
        key_WORLD_52 = 212;\
        key_WORLD_53 = 213;\
        key_WORLD_54 = 214;\
        key_WORLD_55 = 215;\
        key_WORLD_56 = 216;\
        key_WORLD_57 = 217;\
        key_WORLD_58 = 218;\
        key_WORLD_59 = 219;\
        key_WORLD_60 = 220;\
        key_WORLD_61 = 221;\
        key_WORLD_62 = 222;\
        key_WORLD_63 = 223;\
        key_WORLD_64 = 224;\
        key_WORLD_65 = 225;\
        key_WORLD_66 = 226;\
        key_WORLD_67 = 227;\
        key_WORLD_68 = 228;\
        key_WORLD_69 = 229;\
        key_WORLD_70 = 230;\
        key_WORLD_71 = 231;\
        key_WORLD_72 = 232;\
        key_WORLD_73 = 233;\
        key_WORLD_74 = 234;\
        key_WORLD_75 = 235;\
        key_WORLD_76 = 236;\
        key_WORLD_77 = 237;\
        key_WORLD_78 = 238;\
        key_WORLD_79 = 239;\
        key_WORLD_80 = 240;\
        key_WORLD_81 = 241;\
        key_WORLD_82 = 242;\
        key_WORLD_83 = 243;\
        key_WORLD_84 = 244;\
        key_WORLD_85 = 245;\
        key_WORLD_86 = 246;\
        key_WORLD_87 = 247;\
        key_WORLD_88 = 248;\
        key_WORLD_89 = 249;\
        key_WORLD_90 = 250;\
        key_WORLD_91 = 251;\
        key_WORLD_92 = 252;\
        key_WORLD_93 = 253;\
        key_WORLD_94 = 254;\
        key_WORLD_95 = 255;\
        key_KP0 = 256;\
        key_KP1 = 257;\
        key_KP2 = 258;\
        key_KP3 = 259;\
        key_KP4 = 260;\
        key_KP5 = 261;\
        key_KP6 = 262;\
        key_KP7 = 263;\
        key_KP8 = 264;\
        key_KP9 = 265;\
        key_KP_PERIOD = 266;\
        key_KP_DIVIDE = 267;\
        key_KP_MULTIPLY = 268;\
        key_KP_MINUS = 269;\
        key_KP_PLUS = 270;\
        key_KP_ENTER = 271;\
        key_KP_EQUALS = 272;\
        key_UP = 273;\
        key_DOWN = 274;\
        key_RIGHT = 275;\
        key_LEFT = 276;\
        key_INSERT = 277;\
        key_HOME = 278;\
        key_END = 279;\
        key_PAGEUP = 280;\
        key_PAGEDOWN = 281;\
        key_F1 = 282;\
        key_F2 = 283;\
        key_F3 = 284;\
        key_F4 = 285;\
        key_F5 = 286;\
        key_F6 = 287;\
        key_F7 = 288;\
        key_F8 = 289;\
        key_F9 = 290;\
        key_F10 = 291;\
        key_F11 = 292;\
        key_F12 = 293;\
        key_F13 = 294;\
        key_F14 = 295;\
        key_F15 = 296;\
        key_NUMLOCK = 300;\
        key_CAPSLOCK = 301;\
        key_SCROLLOCK = 302;\
        key_RSHIFT = 303;\
        key_LSHIFT = 304;\
        key_RCTRL = 305;\
        key_LCTRL = 306;\
        key_RALT = 307;\
        key_LALT = 308;\
        key_RMETA = 309;\
        key_LMETA = 310;\
        key_LSUPER = 311;\
        key_RSUPER = 312;\
        key_MODE = 313;\
        key_COMPOSE = 314;\
        key_HELP = 315;\
        key_PRINT = 316;\
        key_SYSREQ = 317;\
        key_BREAK = 318;\
        key_MENU = 319;\
        key_POWER = 320;\
        key_EURO = 321;\
        key_UNDO = 322;\
    }");
	
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
	
    init_keys_to_lua(L);
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
	engine->funkeyDown = zmy_keyDown;
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

void destroy(Engine* engine)
{

}
