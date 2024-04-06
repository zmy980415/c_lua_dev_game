#include "SDL_utils.h"


SDL_Rect* newRect(int x, int y, int width, int height)
{
	SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	if (rect == NULL)
	{
		printf("system error, new rect fail.");
		return NULL;
	}
	rect->x = x;
	rect->y = y;
	rect->w = width;
	rect->h = height;
	return rect;
}


void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius)
{
	//const SDL_Point *points = 
	
	for (int w = 0; w < radius * 2; ++w)
	{
		for (int h = 0; h < radius * 2; ++h)
		{
			int dx = radius - w;
			int dy = radius - h;
			if (dx * dx + dy * dy <= radius * radius)
			{
				SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
			}
		}
	}
	//SDL_RenderDrawPoints(renderer,)
}



