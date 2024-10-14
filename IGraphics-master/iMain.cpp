# include "iGraphics.h"

#include<math.h>
#include<time.h>

//window variables
int window_width = 1200 ;
int window_hight = 800;

//iText(window_width - 400, 100, "Press F to Restart...",GLUT_BITMAP_TIMES_ROMAN_24);

//Menu screen
bool gameStarted = false ;
char OpenScreen[4][20] = {"opening1.bmp" , "open2.bmp","inst.bmp","planetoptions.bmp" };
int opening_index = 0;

//play button ( 450,400) and how to play button (350, 100) on menu2
char Menu[2][20]={"play.bmp","instructions.bmp"};

//destination defination
int initial_index = 2; //ccc
int destination_index ;

//On game frames
char frame[10][20] ={"space.bmp","space.bmp","space.bmp","space.bmp","space.bmp","space.bmp","space.bmp","space.bmp","space.bmp","space.bmp"};
int frame_index = 2;
int frame_index_initial = 2;
bool exceed ;

//spaceship images
int ship_index ; //ccc
bool isDestroyed= false ;
char ship[3][30] = {"spaceship1.bmp" ,"flipped_spaceship1.bmp", "spaceship2.bmp"};
int shipX = (window_width-200)/2 ;//right nmotion
int shipY = 300;
int shipDx = 5 ;
int shipDy = 10;
int shipX1 = (window_width-200)/2; //left motion

// at frame 2 (earth)
bool isPaused = true ;

//game over menus
//you lost,you won
char game_over[5][20]={"gem_over1.bmp","end_gem2.bmp","end_gem2.bmp","yo.bmp"};
int end_index = 0;
bool isOver = false;

//placing the planet
char pic_planet[8][20]={"planet5.bmp", "planet5.bmp","planet3.bmp","planet5.bmp","planet5.bmp","planet5.bmp","planet5.bmp","planet5.bmp"};
struct Planet
{
    int x;
    int y;
    bool isVisible ;
}planet[8];
int planet_index  ;


//meteors setup 120/64px
struct meteor
{
    int x;
    int y;
    bool isVisible ;
}meteor;
char meteor_image[2][20]={"meteor1.bmp", "meteor2.bmp"};
int meteorDx = 25 ;
int meteorDy = 25 ;
int meteor_index = 0;


//blackhole setup
struct blackhole
{
    int x;
    int y;
    bool isVisible ;
}blackhole[8];
char blackhole_image[1][20]={"blackhole.bmp"};


//gravity variables ;
double d , GravityDx , GravityDy ;

//gravity for blackhole
double GravityBx , GravityBy , r ;

//lost or won
bool isLost , isWon ;


//nitro power
int nitro = 20 ;

//time variable
int t ;
int final_t;
char str_time[10];

//file pointer
FILE *fp , *fp1;
char str_name[100];
int name_index= 0 ;
int h_score;
bool isHigh = false;


//space stones
char stone_img[3][20]={"stone.bmp","stone.bmp","stone.bmp"};

struct stone
{
    int x;
    int y;
}stone[8][3];


/*
	function iDraw() is called again and again by the system.
*/



void iDraw()
{
    //place your drawing codes here
    iClear();
    if (!gameStarted){
        if(opening_index == 0)
            iShowBMP(0,0,OpenScreen[opening_index]);
        else if(opening_index == 1) {
            iShowBMP(0,0,OpenScreen[opening_index]);
            iShowBMP2(450,400,Menu[0],255);
            iShowBMP2(448,300,Menu[1], 0);
        }
        else{
            iShowBMP(0,0,OpenScreen[opening_index]);
        }
    }
    else if(gameStarted){
        if(destination_index > frame_index_initial && frame_index<= destination_index && !isDestroyed){
                iShowBMP(0,0,frame[frame_index]);
                if(frame_index== frame_index_initial)
                {
                    iSetColor(0,255,0);
                    iText(300,700,"->Press P to start",GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(300,650,"->Press N to accelerate",GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(300,600,"->Use UP-DOWN arrows to move vertically",GLUT_BITMAP_TIMES_ROMAN_24);
                }
                iShowBMP2(planet[frame_index].x , planet[frame_index].y, pic_planet[frame_index],0);
                iShowBMP2(meteor.x, meteor.y , meteor_image[meteor_index], 0);
                if(frame_index != frame_index_initial)
                    iShowBMP2(blackhole[frame_index].x, blackhole[frame_index].y,blackhole_image[0],0);

                if(frame_index == destination_index)
                    iText(planet[frame_index].x+20,planet[frame_index].y-25,"Land Here Safely!",GLUT_BITMAP_TIMES_ROMAN_24);

                if(frame_index != frame_index_initial)
                {
                    for(int i=0 ; i<2 ;i++)
                        iShowBMP2(stone[frame_index][i].x,stone[frame_index][i].y,stone_img[i],0);
                }

                iShowBMP2(shipX , shipY , ship[ship_index], 255);
        }

        else if(destination_index < frame_index_initial && frame_index >= destination_index && !isDestroyed){
                iShowBMP(0,0,frame[frame_index]);

                if(frame_index== frame_index_initial)
                {
                    iSetColor(0,255,0);
                    iText(300,700,"->Press P to start",GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(300,650,"->Press N to accelerate",GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(300,600,"->Use UP-DOWN arrows to move vertically",GLUT_BITMAP_TIMES_ROMAN_24);
                }


                iShowBMP2(planet[frame_index].x , planet[frame_index].y, pic_planet[frame_index],0);
                iShowBMP2(meteor.x, meteor.y , meteor_image[meteor_index], 0);
                if(frame_index != frame_index_initial)
                    iShowBMP2(blackhole[frame_index].x+20, blackhole[frame_index].y,blackhole_image[0],0);

                if(frame_index == destination_index)
                    iText(planet[frame_index].x,planet[frame_index].y-25,"Land Here Safely!",GLUT_BITMAP_TIMES_ROMAN_24);

                 if(frame_index != frame_index_initial)
                {
                    for(int i=0 ; i<2 ;i++)
                        iShowBMP2(stone[frame_index][i].x,stone[frame_index][i].y,stone_img[i],0);
                }

                iShowBMP2(shipX1 , shipY , ship[ship_index], 255);
        }

        else if(isDestroyed && isOver==false && isLost==true && exceed == true && (frame_index == destination_index+1 || frame_index == destination_index-1))
        {
            iShowBMP(0,0,frame[2]);
            iSetColor(0,255,0);
                iText(905 , 150 , "MISSION FAILED!" , GLUT_BITMAP_TIMES_ROMAN_24);
                iText(900 , 100 , "Press F to continue..." , GLUT_BITMAP_TIMES_ROMAN_24);

        }



        else if(isDestroyed && isOver==false && isLost==true && exceed == false ){

                iShowBMP(0,0,frame[frame_index]);
                iShowBMP2(planet[frame_index].x , planet[frame_index].y, pic_planet[frame_index],0);

                if(frame_index != frame_index_initial)
                    iShowBMP2(blackhole[frame_index].x, blackhole[frame_index].y,blackhole_image[0],0);

                if(destination_index>frame_index_initial)
                    iShowBMP2(shipX,shipY,ship[ship_index],0);
                else
                    iShowBMP2(shipX1,shipY,ship[ship_index],0);

                iSetColor(0,255,0);
                iText(905 , 150 , "MISSION FAILED!" , GLUT_BITMAP_TIMES_ROMAN_24);
                iText(900 , 100 , "Press F to continue..." , GLUT_BITMAP_TIMES_ROMAN_24);

        }

        else if(isDestroyed && isOver==false && isWon==true && exceed == false){
            iShowBMP(0,0,frame[frame_index]);
            iShowBMP2(planet[frame_index].x , planet[frame_index].y, pic_planet[frame_index],0);

            if(frame_index != frame_index_initial)
                    iShowBMP2(blackhole[frame_index].x, blackhole[frame_index].y,blackhole_image[0],0);

            if(destination_index>frame_index_initial)
                iShowBMP2(shipX,shipY,ship[ship_index],255);
            else
                iShowBMP2(shipX1,shipY,ship[ship_index],255);

            iSetColor(0,255,0);
            iText(902 , 150 , "MISSION ACCOMPLISHED!" , GLUT_BITMAP_TIMES_ROMAN_24);
            iText(900 , 100 , "Press F to continue..." , GLUT_BITMAP_TIMES_ROMAN_24);
        }


        else if(isOver && isWon && end_index==0){

                iShowBMP(0,0,game_over[end_index]);


                itoa(final_t , str_time , 10);

                iSetColor(0,0,0);

                iShowBMP(325, 175 ,"bb1.bmp");

                iText(450,498,"Your Score :", GLUT_BITMAP_TIMES_ROMAN_24 );

                iText(640,498,str_time, GLUT_BITMAP_TIMES_ROMAN_24);

                iText(700,498,"mili-seconds",GLUT_BITMAP_TIMES_ROMAN_24);



                fp = fopen("score.txt","r");
                fscanf(fp,"%d",&h_score);
                fclose(fp);


                if(final_t<h_score)
                {
                    fp = fopen("score.txt","w");
                    fprintf(fp,"%d",final_t);

                    fclose(fp);

                    isHigh = true ;
                    //iText(530,250,str_name,GLUT_BITMAP_TIMES_ROMAN_24);

                }
                if(isHigh)
                {

                    iText(400,400,"Congratulations! You have set new High Score!",GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(400,350,"Enter Your name : ",GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(600,350,str_name,GLUT_BITMAP_TIMES_ROMAN_24);
                }
                else
                {
                    iText(400,400,"Congratulations! You have finished the mission!",GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(400,300,"Looks like someone has a better time record ;) ",GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(470,260,"Better luck next time :)..",GLUT_BITMAP_TIMES_ROMAN_24);
                }


        }

        else if(isOver &&  end_index==1 )
        {
            iShowBMP(0,0,game_over[end_index]);
            iShowBMP2(475,450,"quit.bmp",0);
            iShowBMP2(450,250,"highS.bmp",0);

            if(strlen(str_name) > 0){
              fp=fopen("names.txt","w");
              fprintf(fp, "%s",  str_name);
              fclose(fp);
            }
        }

        else if(isOver &&  end_index==2)
        {
            iShowBMP(0,0,game_over[end_index]);
            iSetColor(0,0,255);
            iText(495 ,400 ,"HIGH SCORE : ",GLUT_BITMAP_TIMES_ROMAN_24);

            fp=fopen("score.txt","r");
            int buffer;
            fscanf(fp,"%d",&buffer);
            fclose(fp);
            fp1 = fopen("names.txt","r");
            char temp[100];
            fgets(temp,30,fp);
            fclose(fp1);

            itoa(buffer, str_time , 10);
            iSetColor(0,255,0);

            iText(392 ,326,"Name :",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(475 ,326,temp,GLUT_BITMAP_TIMES_ROMAN_24);

            iText(392 ,290,"score :",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(475 ,290,str_time,GLUT_BITMAP_TIMES_ROMAN_24);

            iText(570 ,290,"mili-seconds",GLUT_BITMAP_TIMES_ROMAN_24);

            iText(900 , 100 , "Press B to go back..." , GLUT_BITMAP_TIMES_ROMAN_24);

        }
        else if(isOver && isLost && end_index == 3)
        {
            iShowBMP(0,0,game_over[end_index]);
            iText(900 , 100 , "Press N to continue..." , GLUT_BITMAP_TIMES_ROMAN_24);
        }

        }


    }




/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && opening_index==1)
    {
        if (mx >= 450+25 && mx<= 750 -25 && my >= 500 && my <=600)
            opening_index += 2 ; // detect play game


        if (mx >= 448 && mx<= 448+300 && my >= 300 && my <=396)
            opening_index++ ; //detect instruction
            //PlaySound("click.wav", NULL, SND_ASYNC);}
    }

    if(opening_index == 3){
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

            if(mx>=250 && mx <= 350 && my>=500 && my<=600-10)
                {destination_index = 0;
                gameStarted = true ;
                PlaySound(0, 0, 0);
                ship_index=1;}
            if(mx>=250 && mx <= 350 && my>=375 && my<=470)
                {destination_index = 1;
                gameStarted = true ;
                PlaySound(0, 0, 0);
                ship_index=1;}
            if(mx>=250 && mx <= 350 && my>=250 && my<=350-5)
                {destination_index = 3;
                gameStarted = true ;
                PlaySound(0, 0, 0);
                ship_index=0;}
            if(mx>=250 && mx <= 350 && my>=125 && my<=220)
                {destination_index = 4;
                gameStarted = true ;
                PlaySound(0, 0, 0);
                ship_index=0;}
            if(mx>=655 && mx <= 745 && my>=455 && my<=545)
                {destination_index = 5;
                gameStarted = true ;
                PlaySound(0, 0, 0);}
            if(mx>=655 && mx <= 745 && my>=325 && my<=415)
                {destination_index = 6;
                gameStarted = true ;
                PlaySound(0, 0, 0);
                ship_index=0;}
            if(mx>=655 && mx <= 745 && my>=180 && my<=270)
                {destination_index = 7;
                gameStarted = true ;
                PlaySound(0, 0, 0);
                ship_index=0;}



        }

        if(isOver && (isWon || isLost) && end_index==1)
        {
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                if(mx>476 && mx <475+723 && my>451 && my<450+600)
                {
                    PlaySound("click.wav", NULL, SND_ASYNC);
                    exit(0);
                }
                if(mx>451 && mx<451+695 && my>201 && my<200+493)
                {
                    PlaySound("click.wav", NULL, SND_ASYNC);
                    end_index ++ ;
                }
            }

        }
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == 'p')
    {
        isPaused = false;

    }

    if (key == 'c' && opening_index == 0)
        opening_index ++ ;

    if (key == 'b' && opening_index == 2)
        opening_index = 1;


    if(isDestroyed && isOver==false && key == 'f' && isWon)
        {
            isOver = true ;
        }


    if(isDestroyed && isOver==false && isLost && key == 'f')
        {
            isOver = true ;
            end_index=3 ;
        }
    if(isOver==true && isLost && end_index==3 && key=='n')
    {
         end_index = 1 ;
    }

    if( key == 'n')
    {
        if(!isPaused && gameStarted && !isDestroyed && nitro >0  )
           {
                shipDx += 1 ;
                nitro--;
           }

    }
    if(isOver && isWon && end_index==0 && isHigh)
    {
        if(key != '\b')
        {
            str_name[name_index] = key ;
            str_name[name_index + 1]='\0';
            name_index++;
        }
        else
        {
                str_name[name_index]='\0';
                name_index--;
                if(name_index<0)
                    name_index=0;

        }
    }
    if(isOver  && end_index==2)
    {
        if(key=='b')
            end_index = 1;
    }


    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_UP && gameStarted==true && !isDestroyed)
    {
        if(shipY <= 700-20)
            shipY += shipDy;
    }
    if(key == GLUT_KEY_DOWN && gameStarted==true && !isDestroyed)
    {   if(shipY >=10)
            shipY -= shipDy;
    }
    if(key == GLUT_KEY_F1 && isOver && isWon && end_index==0)
    {
            end_index++;
    }
    //place your codes for other keys here
}

// gravity for planets
double distance(struct Planet s, int a , int b)
{
    double d = sqrt(pow(s.x+125 - (a+100), 2)+pow(s.y+125-(b+75),2));
    return d;
}

double vectorX(struct Planet s, int x , double d)
{
    double GravityDx = ((s.x+125 - (x+100))/d )*4.9 ;
    return GravityDx;
}

double vectorY(struct Planet s,int y, double d)
{
    double GravityDy = ((s.y+125 - (y+75))/d)*4.9 ;
    return GravityDy ;
}

double distanceB(struct blackhole b , int x , int y)
{
    double d = sqrt(pow(b.x+100-(x+100),2)+ pow(b.y+100-(y+75),2) );
    return d;
}

double vectorX_blackhole(struct blackhole b, int x , double d)
{
    double GravityDx = ((b.x+100 - (x+100))/d )* 20 ;
    return GravityDx;
}

double vectorY_blackhole(struct blackhole b, int y , double d)
{
    double GravityDy = ((b.y+100 - (y+75))/d)*20;
    return GravityDy ;
}

void meteorSetup()
{
    if(destination_index>frame_index_initial)
    {
        meteor.x = 500+ rand()%300 ;
        meteor.y = rand()%800;
    }
    if(destination_index<frame_index_initial)
    {
        meteor.x = rand()%600;
        meteor.y = rand()%800 ;
    }
}


void shipMotion(){

    if(gameStarted && !isPaused && !isDestroyed)
        t++ ;


    if (gameStarted && destination_index>2 && !isPaused && !isDestroyed){
        shipX += shipDx ;
        if(frame_index < destination_index+1 ){
                if(shipX > window_width){
                    frame_index++ ;
                    meteorSetup();
                    shipX = 0;
                }
        if(frame_index == destination_index+1 )
        {
           exceed = true ;
           isLost = true ;
           isDestroyed = true ;
        }

        }

        }
    else if(gameStarted && destination_index<2 && !isPaused && !isDestroyed){
        shipX1 -= shipDx ;
        if(frame_index > destination_index -1 ){
            if(shipX1 < -25){
                frame_index--;
                meteorSetup();
                if( frame_index<destination_index)
                    {
                         exceed = true ;
                         isLost = true ;
                         isDestroyed = true ;
                    }
                if(frame_index<0)
                {
                    isLost = true ;
                    exceed = true ;
                    isDestroyed = true ;
                }
                shipX1 = 1050;
            }
        }

    }

  //collision check with the planet
    if(frame_index != frame_index_initial && !isDestroyed && frame_index != destination_index)
    {
        if(destination_index> frame_index_initial)
        {
            if((shipX+200-50)> planet[frame_index].x+50 && (shipX+20)<(planet[frame_index].x + 250 -50) && (shipY+150-50)>planet[frame_index].y +50 && (shipY+50)< (planet[frame_index].y + 250 -50))
            {

             ship_index += 2;
             isDestroyed = true;
             isLost = true ;
             PlaySound("explosion.wav", NULL, SND_ASYNC);

            }
        }
        else
        {
            if((shipX1+200-50)> planet[frame_index].x+50 && (shipX1+20)<(planet[frame_index].x + 250-50) && (shipY+150-50)>planet[frame_index].y+50 && (shipY+50)< (planet[frame_index].y + 250-50))
            {

             ship_index += 1;
             isDestroyed = true;
             isLost = true ;
             PlaySound("explosion.wav", NULL, SND_ASYNC);

            }
        }
    }

    //collision with destination planet

     if(frame_index != frame_index_initial && !isDestroyed && frame_index == destination_index)
     {
         if(destination_index> frame_index_initial)
        {
            if((shipX+200-50)> planet[frame_index].x+25 && (shipX+20)<(planet[frame_index].x + 250 -25) && (shipY+150-50)>planet[frame_index].y +30 && (shipY+40)< (planet[frame_index].y + 250 -30))
            {

             shipDx = 0 ;
             shipDy = 0;
            if( distance(planet[frame_index],shipX,shipY)<50 )

                 isDestroyed = true ;
                 isWon = true ;
                 final_t = (t*50)/(destination_index-frame_index_initial) ;

            }
        }
        else
        {
            if((shipX1+200-50)> planet[frame_index].x+25 && (shipX1+20)<(planet[frame_index].x + 250-25) && (shipY+150-50)>planet[frame_index].y+30 && (shipY+40)< (planet[frame_index].y + 250-30))
            {


             shipDx = 0 ;
             shipDy = 0;
             if( distance(planet[frame_index],shipX1,shipY)<50 ){

                 isDestroyed = true ;
                 isWon = true ;
                 final_t = (t*50)/(-destination_index+frame_index_initial) ;

            }

            }
        }
     }



    //collision with meteor
    if( gameStarted && !isDestroyed)
    {

        if(destination_index> frame_index_initial && shipX+100<window_width)
        {
            if((shipX+200-50)> meteor.x && (shipX+20)<(meteor.x + 120) && (shipY+150-50)>meteor.y && (shipY+40)< (meteor.y + 64))
            {

             ship_index += 2;
             isDestroyed = true;
             isLost = true ;
             PlaySound("explosion.wav", NULL, SND_ASYNC);

            }
        }
        else if(destination_index<frame_index_initial && shipX1>0)
        {
            if((shipX1+200-50)> meteor.x && ((shipX1+20)<meteor.x + 120) && (shipY+150-50)>meteor.y && ((shipY+40)< meteor.y + 64))
            {

             ship_index += 1;
             isDestroyed = true;
             isLost = true ;
             PlaySound("explosion.wav", NULL, SND_ASYNC);

            }
        }
    }

    //check for gravity of planet range
    if(gameStarted && !isDestroyed && !isPaused && frame_index != frame_index_initial)
    {
        if(destination_index > frame_index_initial)
        {
            d = distance(planet[frame_index] , shipX , shipY);
            if(d < 600){

                GravityDx = vectorX(planet[frame_index] , shipX , d);
                GravityDy = vectorY(planet[frame_index] , shipY , d);

                shipX += GravityDx ;
                shipY += GravityDy ;
            }
        }

        if(destination_index < frame_index_initial)
        {
            d = distance(planet[frame_index] , shipX1 , shipY);
            if(d < 600){

                GravityDx = vectorX(planet[frame_index] , shipX1 , d);
                GravityDy = vectorY(planet[frame_index] , shipY , d);

                shipX1 += GravityDx ;
                shipY += GravityDy ;
            }
        }



    }

    //check gravity for blackhole
    if(gameStarted && !isDestroyed && frame_index != frame_index_initial)
    {
         if(destination_index > frame_index_initial)
        {
            r = distanceB(blackhole[frame_index] , shipX , shipY);
            if(r < 200){

                GravityBx = vectorX_blackhole(blackhole[frame_index] , shipX , r);
                GravityBy = vectorY_blackhole(blackhole[frame_index] , shipY , r);

                shipX += GravityBx ;
                shipY += GravityBy ;
            }
        }
        else if(destination_index < frame_index_initial)
        {
            r = distanceB(blackhole[frame_index] , shipX1 , shipY);
            if(r < 200){

                GravityBx = vectorX_blackhole(blackhole[frame_index] , shipX1 , r);
                GravityBy = vectorY_blackhole(blackhole[frame_index] , shipY , r);

                shipX1 += GravityBx ;
                shipY += GravityBy ;
            }
        }
    }

    //collision with blackhole

    if(!isPaused && gameStarted && !isDestroyed)
    {
        if(destination_index>frame_index_initial)
        {
            if(blackhole[frame_index].x+50 < (shipX+200-50) && blackhole[frame_index].x+150 > (shipX+30) && shipY+120 > blackhole[frame_index].y+50 && (shipY+30)<blackhole[frame_index].y+150)
            {
                ship_index += 2;
                isDestroyed = true;
                isLost = true ;
                PlaySound("explosion.wav", NULL, SND_ASYNC);
            }
        }
        else
        {
            if(blackhole[frame_index].x+50 < (shipX1+200-50) && blackhole[frame_index].x+150 > (shipX1+30) && shipY+120 > blackhole[frame_index].y+50 && (shipY+30)<blackhole[frame_index].y+150)
            {
                ship_index += 1;
                isDestroyed = true;
                isLost = true ;
                PlaySound("explosion.wav", NULL, SND_ASYNC);
            }

        }

    }

    //collision with stone

    if(!isPaused && gameStarted && !isDestroyed)
    {
        if(destination_index>frame_index_initial)
        {
            for(int k=0 ; k<2 ; k++)
            {
                if(stone[frame_index][k].x+10 < shipX+200-50  && stone[frame_index][k].x+65> shipX+40 && shipY+120>stone[frame_index][k].y+10 && shipY+40< stone[frame_index][k].y+65)
                {
                    ship_index += 2;
                    isDestroyed = true;
                    isLost = true ;
                    PlaySound("explosion.wav", NULL, SND_ASYNC);
                }
            }
        }
        else
        {
            for(int k=0 ; k<2 ; k++)
            {
                if(stone[frame_index][k].x+10 < shipX1+200-50  && stone[frame_index][k].x+65> shipX1+40 && shipY+120>stone[frame_index][k].y+10 && shipY+40< stone[frame_index][k].y+65)
                {
                    ship_index += 1;
                    isDestroyed = true;
                    isLost = true ;
                    PlaySound("explosion.wav", NULL, SND_ASYNC);
                }
            }
        }
    }


}
 // if((mit[j].x + 75 )>=shipX+20 && mit[j].x <= shipX+150-20 && mit[j].y < shipY+200-30 && mit[j].y+75 > shipY+30


/*double check_distance(struct str, int x , int y)
{
    double r = sqrt(pow((str.x - x),2) + pow((str.y - y),2)) ;
    return r ;
}
*/



void planetSetup()
{
    for(int i=3 ; i<8 ; i++)
    {
         planet[i].x = 700+ rand()%250;
         planet[i].y = 400 + rand()%150 ;

    }

    for(int j=0 ; j<2 ; j++)
    {
        planet[j].x = 0+ rand()%250;
        planet[j].y = 400 + rand()%150 ;

    }
     planet[2].x = (window_width - 250)/2 ;
     planet[2].y = (window_hight-250)/2;
}



void meteor_motion()
{
    if(gameStarted && !isPaused && !isDestroyed)
    {
      meteor.x += meteorDx ;
      meteor.y += meteorDy ;

      if(meteor.x > window_width +170  || meteor.x< -170)
        meteorDx *= -1 ;
      if(meteor.y > window_hight +170 || meteor.y< -170)
        meteorDy *= -1 ;

      //meteor_index++ ;
      //if(meteor_index > 1)
       // meteor_index = 0;
    }
}



void blackholeSetup()
{
    for(int i=3 ; i<8 ; i++)
    {
        blackhole[i].x = 300 + rand()%200 ;
        blackhole[i].y = rand()%50 ;
        /*if( i != frame_index_initial && destination_index>frame_index_initial)
        {
            blackhole[i].x = 200 + rand()%800 ;
            blackhole[i].y = 0 ;
        }
        else if( i!= frame_index_initial && destination_index<frame_index_initial)
        {
            blackhole[i].x = 200 + rand()%800 ;
            blackhole[i].y = 0 ;
        }*/

    }
    for(int j = 0; j<2 ;j++)
    {
         blackhole[j].x = 250 + rand()%200 ;
         blackhole[j].y = rand()%50 ;
    }
}


void stoneSetup()
{
    for(int i=3 ;  i<8 ;i++)
    {
            stone[i][0].x = 250 + rand()%125 ;
            stone[i][0].y = 500 + rand()%125;
    }
    for(int i=3 ;  i<8 ;i++)
    {
            stone[i][1].x = 500 + rand()%125 ;
            stone[i][1].y = 400+ rand()%125 ;
    }
    for(int i=0 ; i<2 ;i++)
    {
            stone[i][0].x = 400 + rand()%125 ;
            stone[i][0].y = 500 + rand()%125 ;
    }
    for(int i=0 ; i<2 ;i++)
    {
            stone[i][1].x = 650 + rand()%125 ;
            stone[i][1].y = 375 + rand()%125 ;
    }
}


int main()
{
    iSetTimer(50, shipMotion); //ship motion control

    planetSetup();// planet construction

     // meteor constructuion

    iSetTimer(50, meteor_motion); //mootion of  met

    blackholeSetup(); // setup blackhole

    if(gameStarted == false)
        PlaySound("menusong.wav", NULL, SND_ASYNC);

    stoneSetup();

    //place your own initialization codes here.
    iInitialize(window_width, window_hight, "Galaxy TraveL") ;






    return 0;
}
