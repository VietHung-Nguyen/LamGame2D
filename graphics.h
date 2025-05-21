#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "defs.h"

struct Sprite
{
    SDL_Texture* texture;
    std::vector <SDL_Rect> clips;
    int currentFrame =0;

    void init (SDL_Texture *_texture, int frames, const int _clips[][4]);
    void tick();
    const SDL_Rect *getCurrentClip()const;

};

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
	void prepareScene();
    void presentScene();
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
    void quit();
    void scrolling (const ScrollingBackground& bgr, int y_background);
    void render(int x, int y, const Sprite& sprite);

};
#endif // _GRAPHICS__H
