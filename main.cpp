#include <iostream>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>

#include "defs.h"
#include "graphics.h"
#include "logic.h"
using namespace std;

int main (int argc, char *argv[])
{

    bool quit= false, checkSpace= false, checkn= false, Lv2 = false, running= true, bossAttack= false, checkAttack= true; //quit, checkSpace, checkn lan luot la bien de kiem tra thoat chuong trinh, an nut space, nhan vat cham xuong dat moi duoc nhay tiep
    int iJump=0; // bien nay de kiem tra neu dung het Frames thi cho checkSpace va checkn bang false de tranh vong lap vo han
    //bien j va n ho tro cho viec nhan vat nhay len
    int j= jumpFrames/2;
    int m= laserFrames/2;
    int checkEndLaser= 0;
    int bloodBoss= skillBoss*4;
    int checkLossGame=0;
    int n;
    int x_jump= 70, y_jump= 500; // vi tri ban dau cua nhan vat
    int x_skeleton= SCREEN_WIDTH/2; //vi tri ban dau cua quai
    const int y_skeleton= 500; //toa do cao cua quai thi giu nguyen nen de const
    int x_boss= SCREEN_WIDTH; //toa do ban dau cua con boss lv2
    const int y_boss= 460; //vi tri y cua con boss 2 la co dinh nen de const
    int x_boy= 0;//vi tri ban dau cua npc nam
    int y_boy= 495;
    int y_bullet= 514;

    int KhoangCach=abs(x_skeleton-x_jump); //khoang cach ban dau cua nhan vat va quai, bien nay se duoc cap nhat lien tuc khi nhan vat va quai di chuyen
    int SumR= (w_girl+h_girl)/4 + (w_skeleton + h_skeleton)/4; //vi coi nhan vat va quai nhu mot hinh tron nen bien nay de xet xem nhan vat va quai co va cham khong
    pair <int, int> TDnpc; //bien pair de luu toa do cua nhan vat
    pair <int, int> TDboss; //bien pair luu toa do quai
    int SumScore =0; // bien luu tong diem
    vector <int> attack;

    //khoi tao graphics va background
    Graphics graphics;
    graphics.init();

    ScrollingBackground background1;
    background1.setTexture(graphics.loadTexture("forestBackground1.JPG"));

    ScrollingBackground background2;
    background2.setTexture(graphics.loadTexture("forestBackground2.JPG"));

    ScrollingBackground background3;
    background3.setTexture(graphics.loadTexture("forestBackground3.JPG"));

    Sprite run;
    SDL_Texture *runSprite= graphics.loadTexture("GirlRun.PNG");
    run.init( runSprite, runFrames, runClips);

    Sprite jump;
    SDL_Texture* jumpSprite= graphics.loadTexture("GirlJump.PNG");
    jump.init(jumpSprite, jumpFrames, jumpClips);

    SDL_Texture* Skeleton = graphics.loadTexture("Skeleton.PNG");

    Sprite boss;
    SDL_Texture* bossSprite= graphics.loadTexture("bossLv2.PNG");
    boss.init (bossSprite, bossframes, bossclips);

    SDL_Texture* bossStand= graphics.loadTexture("bossLv2Stand.PNG");

    Sprite boyAttack;
    SDL_Texture* boyAttackSprite= graphics.loadTexture("boyRunAndAttack.PNG");
    boyAttack.init(boyAttackSprite, boyFrames, boyClips);

    Sprite boyRunning;
    SDL_Texture* boyRunsprite= graphics.loadTexture("boyRunning.PNG");
    boyRunning.init(boyRunsprite, boyRunningFrames, boyRunningClips);

    SDL_Texture* boyJumps = graphics.loadTexture("boyJumps.PNG");

    SDL_Texture* bullet = graphics.loadTexture ("bullet.PNG");

    Sprite laser;
    SDL_Texture* laserSprite = graphics.loadTexture ("laser.PNG");
    laser.init(laserSprite, laserFrames, laserClips);

    Sprite heartNPC;
    SDL_Texture* heartSprite= graphics.loadTexture("healthbar.PNG");
    heartNPC.init(heartSprite, heartFrames,heartClips );

    Sprite attackEffect;
    SDL_Texture* attackEffectSprite= graphics.loadTexture("attackEffect.PNG");
    attackEffect.init(attackEffectSprite, attackEffectFrames, attackEffectClips);

    Sprite win;
    SDL_Texture* winSprite= graphics.loadTexture("win.PNG");
    win.init(winSprite, winFrames, winClips);

    //khoi tao event e
    SDL_Event e;

    cerr << SumScore<<endl;

    //vong lap chinh
    while (!quit)
    {
        if ( KhoangCach <= SumR and !Lv2 || checkLossGame == heartFrames-1 ){
            cerr << "GAME OVER !"<<endl;
            quit = true;
        }

        if (bloodBoss<=0){
            cerr << "Congregation, You Win !"<< endl;
            quit= true;
        }
        while (SDL_PollEvent(&e)){
            if (e.type== SDL_QUIT )
                quit = true;

            if (e.type== SDL_KEYDOWN){
                if (e.key.keysym.sym== SDLK_SPACE and !checkn){
                    checkSpace= true;
                    checkn= true;
                    n= j-1;
                }
                if(e.key.keysym.sym== SDLK_h and Lv2 and !checkSpace){
                    attack.push_back(0);
                    running= false;
                }

            }
            if (e.type== SDL_KEYUP){
                running= true;
            }

        }

        cuon(background1, background2, background3, graphics);
        if (!Lv2){
            graphics.renderTexture(Skeleton, x_skeleton, y_skeleton);

            if (checkSpace){
                jump.tick();
                y_jump =500-(j-abs(n))*HeightJump;
                graphics.render(x_jump, y_jump , jump);
                n--;
                iJump++;
                x_jump +=10;
                if(iJump == jumpFrames){
                    checkSpace=false;
                    checkn = false;
                    iJump= 0;
                }
            }
            else{
                if (x_jump>70){
                    run.tick();
                    graphics.render(x_jump, y_jump, run);
                    x_jump-=3;
                }
                else{
                    run.tick();
                    x_jump +=3;
                    graphics.render(x_jump, y_jump, run);
                }
            }

            if (x_jump>SCREEN_WIDTH){
                graphics.prepareScene();
                int checkGoOut= SCREEN_WIDTH/ SCROLLINGBACKGROUND1;
                for (int i=0 ; i<= checkGoOut; i++){
                    if (i==checkGoOut){
                        int newSCROLLINGBACKGROUND = SCREEN_WIDTH % SCROLLINGBACKGROUND1;

                        cuon(background1, background2, background3, graphics, newSCROLLINGBACKGROUND);

                        x_jump-= newSCROLLINGBACKGROUND;
                        if (y_jump < 500) y_jump = 0;

                        graphics.render(x_jump, y_jump, run);

                        graphics.presentScene();

                    }
                    else{
                        cuon(background1, background2, background3, graphics);

                        x_jump-=SCROLLINGBACKGROUND1;
                        if (y_jump< 500) y_jump= 500;

                        graphics.render(x_jump, y_jump, run);

                        graphics.presentScene();


                    }
                }
                x_skeleton+=SCREEN_WIDTH;
            }
            graphics.presentScene();
            TDnpc.first= x_jump + w_girl/2;
            TDnpc.second= y_jump + 6 + h_girl/2;
            TDboss.first= x_skeleton + w_skeleton/2;
            TDboss.second= 500 + 8 + h_skeleton/2;
            KhoangCach= Distance(TDnpc, TDboss);
            if (x_skeleton<= 0 ){
                SumScore+= Score;
                cerr << SumScore<< endl;
            }

            if (SumScore== 1000 ){

                endLv1( x_jump, run, graphics, background1, background2, background3);

                SDL_DestroyTexture (runSprite); runSprite= nullptr;
                SDL_DestroyTexture(jumpSprite); jumpSprite= nullptr;
                SDL_DestroyTexture (Skeleton); Skeleton= nullptr;
                Lv2=true;
            }
            x_skeleton= changeX (x_skeleton);
        }
        else{
            SumR= w_boy/2+ w_attackEffect/2;

            graphics.render(10, 10, heartNPC);
            graphics.render(SCREEN_WIDTH - 50, 10, win);

            if (x_boss > SCREEN_WIDTH-w_boss*2) x_boss-=SCROLLINGBACKGROUND1;
            if (x_boy < w_boy*2) x_boy+= SCROLLINGBACKGROUND1;

            if (checkSpace and checkn){
                y_boy=495-(j-abs(n))*HeightJump;
                graphics.renderTexture(boyJumps, x_boy, y_boy);
                n--;
                if (j-abs(n)==-1){
                    checkn= false;
                    checkSpace= false;
                }

                printBullet(attack, graphics, win, bullet, x_boy, x_boss, bloodBoss, bossAttack);
            }
            else{
                y_boy= 495;
                if (running){
                    boyRunning.tick();
                    graphics.render(x_boy, y_boy, boyRunning);
                }
                else{
                    boyAttack.tick();
                    graphics.render(x_boy, y_boy, boyAttack);
                }

                printBullet(attack, graphics, win, bullet, x_boy, x_boss, bloodBoss, bossAttack);
            }
            if (bossAttack){
                boss.tick();
                laser.tick();
                graphics.render(x_boss, y_boss, boss);
                graphics.render(x_boss + 9, y_boss+3, laser);
                checkEndLaser++;
                if (checkEndLaser>=laserFrames ){
                    attackEffect.tick();
                    graphics.render(x_boy-10, 500, attackEffect);
                    TDnpc.first= x_boy+w_boy/2; TDnpc.second= y_boy + h_boy/2;
                    TDboss.first= x_boy-10 + w_attackEffect/2; TDboss.second= 500 + h_attackEffect/2;
                    KhoangCach= Distance(TDnpc, TDboss);
                    if (KhoangCach<= SumR and checkAttack and checkEndLaser==laserFrames+m-1){
                        checkLossGame++;
                        checkAttack= false;
                        heartNPC.tick();
                    }
                    SDL_Delay(25);
                }
                if (checkEndLaser== laserFrames+m){
                    bossAttack= false;
                    checkAttack= true;
                    checkEndLaser= 0;
                }

            }

            else{
                graphics.renderTexture(bossStand, x_boss, y_boss);
            }

            graphics.presentScene();
            SDL_Delay(25);
        }
        SDL_Delay(50);
    }
    SDL_DestroyTexture (runSprite); runSprite= nullptr;
    SDL_DestroyTexture(jumpSprite); jumpSprite= nullptr;
    SDL_DestroyTexture (Skeleton); Skeleton= nullptr;
    SDL_DestroyTexture (boyJumps); boyJumps= nullptr;
    SDL_DestroyTexture(boyAttackSprite); boyAttackSprite= nullptr;
    SDL_DestroyTexture (bullet); bullet= nullptr;
    SDL_DestroyTexture (boyRunsprite); boyRunsprite= nullptr;
    SDL_DestroyTexture (laserSprite); laserSprite = nullptr;
    SDL_DestroyTexture (bossStand); bossStand= nullptr;
    SDL_DestroyTexture (heartSprite); heartSprite= nullptr;
    SDL_DestroyTexture (attackEffectSprite); attackEffectSprite= nullptr;
    SDL_DestroyTexture (winSprite); winSprite= nullptr;
    SDL_DestroyTexture( background1.texture ); background1.texture= nullptr;
    SDL_DestroyTexture (background2.texture); background2.texture= nullptr;
    SDL_DestroyTexture (background3.texture); background3.texture= nullptr;
    graphics.quit();
    return 0;
}
