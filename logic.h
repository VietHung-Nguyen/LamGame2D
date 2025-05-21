#ifndef LOGIC_H
#define LOGIC_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "defs.h"
#include "graphics.h"

using namespace std;

void cuon(ScrollingBackground &background1, ScrollingBackground &background2, ScrollingBackground &background3, Graphics &graphics, int _y=SCROLLINGBACKGROUND1);
int changeX (int _x);
int Distance (pair<int, int> TDnpc, pair <int, int> TDboss);
void endLv1 ( int x_girl, Sprite& girl, Graphics& graphics,ScrollingBackground& background1,ScrollingBackground& background2,ScrollingBackground& background3);
void printBullet (vector<int>& v, Graphics& graphics, Sprite& win, SDL_Texture* bullet, int x_boy, int x_boss, int &bloodBoss, bool& bossAttack);
bool checkAttack (int x_bullet, int x_boss);

#endif
