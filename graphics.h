#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
struct ScrollingBackground
{
    SDL_Texture *texture;
    int scrollingOffset=0;
    int width, height;
    void setTexture( SDL_Texture *_texture){
        texture= _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    }
    void scroll(int distance)
    {
        scrollingOffset-= distance;
        if (scrollingOffset<0 ){
            scrollingOffset= width;
        }
    }
};

struct Graphics
{
    SDL_Renderer *renderer;
	SDL_Window *window;


	void logErrorAndExit(const char* msg, const char* error);
	void init();
	void prepareScene(SDL_Texture * background);
    void presentScene();
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
    void quit();
    void scrolling (const ScrollingBackground& bgr);

};
#endif // _GRAPHICS__H
