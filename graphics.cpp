#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "graphics.h"

void Sprite :: init(SDL_Texture *_texture, int frames, const int _clips[][4])
{
    texture= _texture;

    SDL_Rect clip;
    for (int i=0; i< frames ; i++)
    {
        clip.x= _clips[i][0];
        clip.y= _clips[i][1];
        clip.w= _clips[i][2];
        clip.h= _clips [i][3];
        clips.push_back(clip);
    }
}

void Sprite :: tick ()
{
    currentFrame= (currentFrame +1 )%clips.size();

}

const SDL_Rect* Sprite :: getCurrentClip ()const
{
    return &(clips[currentFrame]);
}


void Graphics::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}
void Graphics :: init ()
{
    if (SDL_Init(SDL_INIT_EVERYTHING)){
        logErrorAndExit ("SDL_Init", SDL_GetError());

    }
     window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
        logErrorAndExit("SDL_Init", SDL_GetError());
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit("SDL_image error: ", IMG_GetError());
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if (renderer == nullptr)\
        logErrorAndExit("CreateRenderer", SDL_GetError());
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

}
void Graphics :: prepareScene ()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
void Graphics :: presentScene ()
{
    SDL_RenderPresent(renderer);

}
SDL_Texture * Graphics :: loadTexture (const char * filename)
{
    SDL_LogMessage (SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    SDL_Texture *texture = IMG_LoadTexture (renderer, filename);
    if (texture == nullptr)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
    return texture;

}
void Graphics :: renderTexture (SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;

    dest.x= x;
    dest.y= y;
    SDL_QueryTexture (texture, NULL , NULL, &dest.w, &dest.h );

    SDL_RenderCopy (renderer, texture, NULL, &dest);
}
void Graphics :: blitRect (SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
    SDL_Rect dest;

    dest.x= x;
    dest.y= y;
    dest.w= src-> w;
    dest.h= src-> h;

    SDL_RenderCopy (renderer, texture, src, &dest);
}
void Graphics:: quit ()
{
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow (window);
    SDL_Quit();

}
void Graphics :: scrolling( const ScrollingBackground& bgr, int y_background )
{

    renderTexture(bgr.texture, bgr.scrollingOffset, y_background);
    renderTexture (bgr.texture, bgr.scrollingOffset-bgr.width, y_background);

}

void Graphics::render(int x, int y,const Sprite& sprite)
{
    const SDL_Rect* clip = sprite.getCurrentClip();
    SDL_Rect copyRect = {x, y, clip-> w, clip->h};
    SDL_RenderCopy(renderer, sprite.texture, clip, &copyRect);
}
