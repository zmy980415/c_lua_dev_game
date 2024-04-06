#include <stdio.h>
#include <SDL_image.h>
#include "graphics.h"
#include "SDL_utils.h"
#include "image.h"

#define GLOBAL_IMAGES_SIZE 10000

SDL_Renderer *global_renderer = NULL;
IMAGE *global_images[GLOBAL_IMAGES_SIZE] = {NULL};
int global_image_index = 0;
//绘制矩形
void rectangle(lua_State *L)
{
	// printf("len: %d", lua_gettop(L));
	size_t len;
	char *mode = lua_tolstring(L, 1, &len);
	int x = (int)lua_tonumber(L, 2);
	int y = (int)lua_tonumber(L, 3);
	int w = (int)lua_tonumber(L, 4);
	int h = (int)lua_tonumber(L, 5);

	SDL_Rect *rect = newRect(x, y, w, h);
	if ("fill" == mode) {
		SDL_RenderFillRect(global_renderer, rect);
	}
	else {

		SDL_RenderDrawRect(global_renderer, rect);
	}
}
//绘制圆形
void circle(lua_State *L)
{
	/*printf("circle\n");
	printf("len: %d", lua_gettop(L));*/
	size_t len;
	char *mode = lua_tolstring(L, 1, &len);
	int x = (int)lua_tonumber(L, 2);
	int y = (int)lua_tonumber(L, 3);
	int radius = (int)lua_tonumber(L, 4);
	
	drawCircle(global_renderer, x, y, radius);
}
//绘制点
void point(lua_State *L)
{
	int x = (int)lua_tonumber(L, 1);
	int y = (int)lua_tonumber(L, 2);
	SDL_RenderDrawPoint(global_renderer, x, y);
}

void setColor(lua_State* L)
{
	int r = (int)lua_tonumber(L, 1);
	int g = (int)lua_tonumber(L, 2);
	int b = (int)lua_tonumber(L, 3);
	int a = (int)lua_tonumber(L, 4);
	SDL_SetRenderDrawColor(global_renderer, r, g, b, a);
}

int newImage(lua_State* L)
{
	if (GLOBAL_IMAGES_SIZE <= global_image_index)
	{
		fprintf(stderr, "you only can load %d image", GLOBAL_IMAGES_SIZE);
		return 0;
	}
	size_t len;
	const char *filePath = lua_tolstring(L, 1,&len);
	printf("new image path is: %s\n", filePath);
	IMAGE* img = (IMAGE*)malloc(sizeof(IMAGE));
	if (img) {
		SDL_Texture *texture = IMG_LoadTexture(global_renderer, filePath);
		fprintf(stderr, "Texture creation failed: %s\n", SDL_GetError());
		if (texture == NULL) {
			fprintf(stderr, "Texture creation failed: %s\n", SDL_GetError());
		}
		int code = SDL_QueryTexture(texture, NULL, NULL, &img->width, &img->height);
		printf("%d,%d\n", img->width, img->height);
		if (code != 0) {
			fprintf(stderr, "query texture info:%s\n", SDL_GetError());
		}
		lua_newtable(L);
		lua_pushinteger(L, img->width);
		lua_setfield(L, -2, "width");

		lua_pushinteger(L, img->height);
		lua_setfield(L, -2, "height");
		global_images[global_image_index] = texture;
		img->texture = global_image_index++;
		lua_pushinteger(L, img->texture);
		lua_setfield(L,-2, "texture");
		/*lua_pushlightuserdata(L, img->texture);
		lua_pushstring(L, "texture");
		lua_settable(L, -3);*/
	}
	return 1;
	//SDL_Surface* IMG_Load(const char* file);
}

void drawImage(lua_State* L)
{
	int width, height;
	int texture = (int)lua_tonumber(L, 1);

	int code = SDL_QueryTexture(global_images[texture], NULL, NULL, &width, &height);

	int x = (int)lua_tonumber(L, 2);
	int y = (int)lua_tonumber(L, 3);
	int isTable = lua_istable(L, 4);
	double rotate = 0;
	SDL_Rect quadRect = { 0,0,width,width };
	SDL_Rect posRect = { x,y,width,width };
	SDL_Point *centPos = NULL;
	int flip = 0;
	if (isTable)
	{
		lua_rawgeti(L, 4, 1);
		int qx = (int)lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_rawgeti(L, 4, 2);
		int qy = (int)lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_rawgeti(L, 4, 3);
		int qw = (int)lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_rawgeti(L, 4, 4);
		int qh = (int)lua_tonumber(L, -1);
		lua_pop(L, 1);
		quadRect.x = qx;
		quadRect.y = qy;
		quadRect.w = qw;
		quadRect.h = qh;
		posRect.w = qw;
		posRect.h = qh;
		
		if (lua_isnumber(L, 5))
		{
			rotate = lua_tonumber(L, 5);
			if (lua_istable(L, 6))
			{
				lua_rawgeti(L,6, 1);
				int centX = (int)lua_tonumber(L, -1);
				lua_rawgeti(L,6, 2);
				int centy = (int)lua_tonumber(L, -1);
				centPos = (SDL_Point*)malloc(sizeof(SDL_Point));
				if (centPos != NULL)
				{
					centPos->x = centX;
					centPos->y = centy;
				}
				if (lua_isboolean(L, 7))
				{
					flip = lua_toboolean(L, 7);
				}
			}
		}
		
	}
	//SDL_RenderCopy(global_renderer, global_images[texture], &quadRect, &posRect);
	SDL_RenderCopyEx(global_renderer, global_images[texture], &quadRect, &posRect, rotate, centPos, flip);
}
