#include <iostream>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "defs.h"
#include "graphics.h"
#include "logic.h"
using namespace std;

void cuon (ScrollingBackground &background1, ScrollingBackground &background2, ScrollingBackground &background3, Graphics &graphics, int _y)
{

    background1.scroll(_y);
    graphics.scrolling(background1, 630-background1.height);

    background2.scroll(SCROLLINGBACKGROUND2);
    graphics.scrolling(background2, 630 - background1.height - background2.height);

    background3.scroll(SCROLLINGBACKGROUND3);
    graphics.scrolling(background3, 0 );


}

int changeX ( int _x )
{
    int x= (_x-SCROLLINGBACKGROUND1);
    if (x<= -SCROLLINGBACKGROUND1){
        x= SCREEN_WIDTH;
    }
    return x;
}

int Distance (pair<int, int> TDnpc, pair <int, int> TDboss)
{

    int kc= sqrt(pow(TDboss.first- TDnpc.first, 2) + pow(TDboss.second - TDnpc.second,2));
    return kc;

}
void endLv1 (int x_girl, Sprite& girl, Graphics& graphics,ScrollingBackground& background1,ScrollingBackground& background2,ScrollingBackground& background3 )
{
    while (x_girl > -w_girl){
        girl.tick();
        cuon(background1, background2, background3, graphics);
        x_girl-= SCROLLINGBACKGROUND1;
        graphics.render (x_girl, 500, girl);
        graphics.presentScene();
        SDL_Delay(50);
    }
}

bool checkAttack (int x_bullet, int x_boss)
{
    if (x_bullet >= x_boss and x_bullet <= x_boss + w_boss) return true;
    return false;
}

void printBullet (vector<int>& v, Graphics& graphics,Sprite& win, SDL_Texture* bullet, int x_boy, int x_boss, int &bloodBoss, bool& bossAttack)
{

    for (int i=0; i< v.size(); i++){
        if (checkAttack(x_boy + v[i]*bulletSpeed, x_boss)){
            v.erase(v.begin()+i);
            bloodBoss--;
            i--;
            if (bloodBoss % skillBoss== 0){
                bossAttack = true;
                win.tick();

            }
        }
        graphics.renderTexture(bullet, x_boy + w_boy+ v[i]*bulletSpeed, 514);
        v[i]++;

    }
}
