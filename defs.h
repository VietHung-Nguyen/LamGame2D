#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH= 1000;
const int SCREEN_HEIGHT= 700;

#define WINDOW_TITLE "MY GAME"
#define HeightJump 30
#define bulletSpeed 21
#define SCROLLINGBACKGROUND1 7
#define SCROLLINGBACKGROUND2 3
#define SCROLLINGBACKGROUND3 2
#define skillBoss 25

const int Score = 100;

const int w_girl= 25;
const int h_girl= 29;

const int w_skeleton= 23;
const int h_skeleton= 24;

const int w_boss= 72;
const int h_boss= 75;

const int w_boy= 35;
const int h_boy= 40;

const int w_bullet= 22;

const int w_lazer= 13;
const int h_lazer= 11;

const int w_attackEffect= 48;
const int h_attackEffect= 50;

const int runClips [][4]={
    {0   , 0, 40, 35},
    {71  , 0, 40, 35},
    {141 , 0, 40, 35},
    {208 , 0, 40, 35},
    {279 , 0, 40, 35},
    {349 , 0, 40, 35}

};
const int runFrames = sizeof (runClips)/sizeof (int)/4;

const int jumpClips [][4]={
    {0   , 0, 40, 35},
    {71  , 0, 40, 35},
    {141 , 0, 40, 35},
    {208 , 0, 40, 35},
    {279 , 0, 40, 35},
    {349 , 0, 40, 35}
};
const int jumpFrames= sizeof (jumpClips)/sizeof(int)/4;

const int bossclips[][4]= {
    {54 , 0, 72, 75},
    {194, 0, 72, 75},
    {334, 0, 72, 75},
    {474, 0, 72, 75},
    {614, 0, 72, 75},
    {754, 0, 72, 75}
};
const int bossframes= sizeof (bossclips)/ sizeof (int)/4;

const int boyClips[][4]= {
    {2  , 0, 35, 40},
    {50 , 0, 35, 40},
    {99 , 0, 35, 40},
    {146, 0, 35, 40},
    {193, 0, 35, 40},
    {243, 0, 35, 40}
};
const int boyFrames = sizeof (boyClips)/ sizeof(int)/4;

const int boyRunningClips [][4]= {
    {0  , 0, 32, 40},
    {32 , 0, 32, 40},
    {64 , 0, 32, 40},
    {96 , 0, 32, 40},
    {128, 0, 32, 40},
    {160, 0, 32, 40}
};
const int boyRunningFrames= sizeof (boyRunningClips)/sizeof (int)/4;

const int laserClips[][4]= {
    {0  , 7, 27, 23},
    {61 , 7, 27, 23},
    {122, 7, 27, 23},
    {183, 7, 27, 23},
    {244, 7, 27, 23},
    {305, 7, 27, 23},
    {366, 7, 27, 23},
    {427, 7, 27, 23}
};
const int laserFrames = sizeof (laserClips)/ sizeof (int)/4;

const int heartClips[][4]= {
    {0 , 0, 17, 17},

    {34, 0, 17, 17},

    {68, 0, 17, 17}
};
const int heartFrames= sizeof (heartClips)/ sizeof (int)/4;

const int attackEffectClips [][4]= {
    {0  , 0, 48, 50},
    {48 , 0, 48, 50},
    {100, 0, 48, 50},
    {150, 0, 48, 50}
};
const int attackEffectFrames= sizeof (attackEffectClips) / sizeof (int)/4;

const int winClips[][4]= {
    {0  , 0, 18, 17},
    {32 , 0, 18, 17},
    {64 , 0, 18, 17},
    {96 , 0, 18, 17},
    {128, 0, 18, 17}
};
const int winFrames= sizeof (winClips)/ sizeof (int)/4;
#endif // _DEFS__H
