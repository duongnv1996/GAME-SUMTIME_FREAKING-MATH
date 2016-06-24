#include<iostream>
#include<windows.h>
#include<conio.h>
#include<ctime>
#include<cstdlib>
#include <process.h>
#include<string>
#include<fstream>
#include"graphics.h"
#include<stdlib.h>
#pragma comment(lib, "graphics.lib")
void menuGame(bool);
void showBestScore();
void showAbout();
#define HEIGHT  600
#define WIDTH  400
#define FONTTEXT 4
#define SIZETEXT 40
#define CODE_RANK 1;
#define CODE_PLAY 1;
#define CODE_ABOUT 1;

using namespace std;
struct Point
{
	int x,y;
}mouse;
int numberA;
int numberB;
int n_operator; 
char *c_operator= new char;
int colorBG ;
int ListColorBG[]={2,3,5,6,9,12,13};
int result;
int numberOfFalse = 0;
int numberOfTrue = 0;
bool isTrue =false;
fstream dataFile;
int _bestScore = 0;
int score =0;
bool isLocked =false;
	// 
int fileScore(int s,int &sc)
{
	fstream fileScore;
	//Mo file de luu gia tri diem so hien tai kieu nhi phan
	fileScore.open("Score.txt",ios::out | ios::binary); 
	fileScore.write(reinterpret_cast<char *>(&s),sizeof(s));
	fileScore.close();
	//Mo file de lay gia tri diem so gan vao bien sc
	return 0;
}

//get best score
void bestScore(int &sc)
{
	fstream fileScore;
	fileScore.open("Score.txt",ios::in | ios:: binary);
	{fileScore.read(reinterpret_cast<char *>(&sc),sizeof(sc));
	}
	fileScore.close();
	//cout<<"Best: ";
	//cout<<sc;
}
int getRandom(int a, int b,int c){
	int randNumber;
	do{
		randNumber= ( rand() % b + a) ;
	}while (randNumber ==c);
	return  randNumber;
}
void showText(char *c,int posX,int posY,int color){
	setbkcolor(colorBG);
	setcolor(color);
	settextjustify(1,1);
	settextstyle(FONTTEXT,0,SIZETEXT);
	outtextxy(posX,posY,c);
}
int showText(char *c,int posX,int posY,int color,int font,int size){
	setbkcolor(colorBG);
	setcolor(color);
	settextjustify(1,1);			// can le
	settextstyle(font,0,size);
	outtextxy(posX,posY,c);
	setcolor(WHITE);
	return textwidth(c);
}
int showTextLeft(char *c,int posX,int posY,int color,int font,int size){
	setbkcolor(colorBG);
	setcolor(color);
	settextjustify(0,0);			// can le
	settextstyle(font,0,size);
	outtextxy(posX,posY,c);
	setcolor(WHITE);
	return textwidth(c);
}
char* getQuestion (){
	char* quest = new char[10];
	numberA= getRandom(1,9,-1);
	numberB =getRandom(1,9,-1);
	n_operator= getRandom(0,2,-1);
	switch (n_operator)
	{
	case 1:{
		c_operator=" + ";
		result=numberA+numberB;
		break;
		   }
	case 0:{
		c_operator=" - ";
		result=numberA-numberB;
		break;
		   }
	}
	char *cnumberA = new char[2];
	char *cnumberB = new char[2];
	itoa(numberA,cnumberA,16);
	itoa(numberB,cnumberB,16);
	quest=cnumberA;
	strcat(quest,c_operator);
	strcat(quest,cnumberB);
	return quest;
}
char* getResult(int result){
	int range = getRandom(-1,2,3);
	if(numberOfFalse>1) range =0;
	if(numberOfTrue>1) range = getRandom(-1,2,0);
	if(range == 0 ) {
		isTrue=true;
		numberOfFalse=0;
		numberOfTrue++;
	}
	else{
		numberOfFalse++;
		isTrue= false;
		numberOfTrue=0;
	}
	result+=range;

	char *op =new char [20];
	char * c_result = new char[4];
	strcpy(op," = ");
	itoa(result,c_result,10);
	strcat(op,c_result);
	//cout<<"Is true = "<<isTrue << "  numberOfFalse  = "<<numberOfFalse<< "  numberOfTrue  = "<<numberOfTrue<<"DAP AN IN = "<<op<<endl ; 
	return op;
}
void showTrueFalse(){

	setfillstyle(1,WHITE) ;
	bar(30,400,180,550);		//true
	bar(220,400,370,550);		//false
	setcolor(BLUE);
	setbkcolor(WHITE);
	settextjustify(1,1);
	settextstyle(FONTTEXT,0,SIZETEXT);
	outtextxy(105,490,"T");
	setcolor(RED);
	outtextxy(295,490,"F");
}
void showTrueClicked(){

	setfillstyle(1,LIGHTGRAY) ;
	bar(30,400,180,550);		//true

	setcolor(BLUE);
	setbkcolor(LIGHTGRAY);
	settextjustify(1,1);
	settextstyle(FONTTEXT,0,SIZETEXT);
	outtextxy(105,490,"T");
	setcolor(RED);
	
}
void showFalseClicked(){

	setfillstyle(1,LIGHTGRAY) ;

		bar(220,400,370,550);		
	setcolor(BLUE);
	setbkcolor(LIGHTGRAY);
	settextjustify(1,1);
	settextstyle(FONTTEXT,0,SIZETEXT);
	
	setcolor(RED);
	outtextxy(295,490,"F");
}
void drawBar(int type,int color,int posX1,int posY1,int posX2,int posY2){
	setfillstyle(type,color) ;
	bar(posX1,posY1,posX2,posY2);
}
void initWindow(){
	//setcolor(3);
	colorBG=ListColorBG[getRandom(0,7,-1)];
	drawBar(1,colorBG,0,10,400,600);			// game screen
	drawBar(1,WHITE,0,0,400,10);		// time bar
	showTrueFalse();					// true false
}
void showView(int score){
	char * c_score = new char[1000];
	drawBar(1,colorBG,0,150,400,300);	// clear old question
	showText(getQuestion(),200,200,WHITE);		//question
	showText(getResult(result),200,200+2*SIZETEXT,WHITE);	//result
	settextstyle(FONTTEXT,0,70);
	outtextxy(350,50,itoa(score,c_score,10));		//score
}
void updateData(int &score , bool &isCorrectAnswer,int &increaseTimer){
	score++;
	isCorrectAnswer=true;
	increaseTimer=0;
	drawBar(1,WHITE,0,0,400,10);	
	PlaySound(TEXT("passed.wav"), NULL, SND_FILENAME);
}
bool onClickMouse(Point mouse){
	if(mouse.x >=30 && mouse.x< 180 && mouse.y>=400 && mouse.y<550){
		return true;
	}else if(mouse.x >=220 && mouse.x< 370 && mouse.y>=400 && mouse.y<550){
		return false;
	}
	return false;
}
void falseAnswer(int score,int best){
	char * c_score = new char[1000];
	PlaySound(TEXT("fail.wav"), NULL, SND_FILENAME);
	if(score>best){
		fileScore(score,best);
		bestScore(_bestScore);
	}
	delay(1000);
	menuGame(false);
}
void showGameControl(){
	
	bool isCorrectAnswer =true;
	srand (time(NULL));
	char key;
	int increaseBar =0;
	initWindow();
	int mouneX,mouneY;
	bool _isAnswer;
	int decreaseTime = 30;
	score = 0;
	while(true){
		if(isCorrectAnswer) showView(score);		// show next question
		isCorrectAnswer=false;
		drawBar(1,colorBG,0,0,increaseBar,10);	//increase time bar
		delay(decreaseTime);	//30

		// bat key tu ban phim
		/*if(kbhit()){		
			key= getch();
			if(key=='t'){
				if(isTrue){
					updateData(score,isCorrectAnswer,decreaseTime);
					PlaySound(TEXT("passed.wav"), NULL, SND_FILENAME);
					continue;
				}	else{
					PlaySound(TEXT("fail.wav"), NULL, SND_FILENAME);
					break;
				}			
			}
			if(key=='f'){
				if(!isTrue){
					updateData(score,isCorrectAnswer,decreaseTime);
					PlaySound(TEXT("passed.wav"), NULL, SND_FILENAME);
					continue;
				}	else{
					PlaySound(TEXT("fail.wav"), NULL, SND_FILENAME);
					break;
				}			
			}

		}*/
		if(ismouseclick(513)){
			mouse.x=mousex();
			mouse.y=(mousey());
			clearmouseclick(513);

			if(mouse.x >=30 && mouse.x< 180 && mouse.y>=400 && mouse.y<550){
				//cout<<"Chon True"<<endl;
				showTrueClicked ();
				delay (150);
				showTrueFalse ();
				//showTrueFalse ();
				if(isTrue){
					updateData(score,isCorrectAnswer,increaseBar);
					if(score%10==0 && score !=0)
						decreaseTime--;	
					//cout<<"Time Delay"<<decreaseTime<<endl ;
					continue;
				}	else{
					falseAnswer(score,_bestScore);
					break;
				}			
			}else if(mouse.x >=220 && mouse.x< 370 && mouse.y>=400 && mouse.y<550){
				//cout<<"Chon False"<<endl;
				showFalseClicked ();
				delay (150);
				setbkcolor(WHITE);
				showTrueFalse ();
				if(!isTrue){
					updateData(score,isCorrectAnswer,increaseBar);
					if(score%10==0 && score !=0)
						decreaseTime--;	
					//cout<<"Time Delay"<<decreaseTime<<endl ;
					continue;
				}	else{
					falseAnswer(score,_bestScore);

					break;
				}			
			}
		}
		increaseBar+=10;
		if(increaseBar==400) {
			falseAnswer(score,_bestScore);
			break;
		}
		/*if(score%10==0 && score !=0)
			decreaseTime--;	
		//cout<<"Time Delay"<<decreaseTime<<endl ;*/
	}
}

void menuGame(bool isFisrtTime){
	PlaySound("background.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	Point mouseClickMenu;	
	colorBG=3;
	setbkcolor(colorBG);
	cleardevice();
	if(isFisrtTime){
		int increase =0;
		int t;
		while(true){
			t = showText(" Sum",90,increase,WHITE,BOLD_FONT,7);		
			delay(3);
			increase++;
			if((130) == increase){
				break;
			}else {
				showText(" Sum",90,increase,WHITE,BOLD_FONT,7);
			}
		}
		delay(10);
		increase=400;
		while(true){
			showText("Time",increase,130,WHITE,BOLD_FONT,7);

			delay(3);

			increase--;
			if((90+t) == increase){
				break;
			}else {
				showText("Time",increase,130,3,BOLD_FONT,7);
			}
		}
		delay(10);
	}else{
		int t;
		t = showText(" Sum",90,130,WHITE,BOLD_FONT,7);		
		showText("Time",90+t,130,WHITE,BOLD_FONT,7);
	}
	colorBG=15;
	//show button play
	drawBar(1,colorBG,145,320,245,370);			// 100x50 
	//setbkcolor(colorBG);
	showText("Play",195,350,4,BOLD_FONT,2);
	//show button rank
	drawBar(1,colorBG,45,390,145,440);			// 100x50 
	showText("Rank",95,420,2,BOLD_FONT,2);
	//show button about
	drawBar(1,colorBG,245,390,345,440);			// 100x50 
	showText("About",295,420,8,BOLD_FONT,2);
	//show button icon
	


	// show text duongkk
	colorBG=3;
	showText("©2016 DuongKaKa",200,580,WHITE,8,40);
	while(true){
		//PlaySound(TEXT("background.wav"), NULL, SND_FILENAME);
		
		mouseClickMenu.x=mousex();
		mouseClickMenu.y=mousey();
		//cout<<"Click : "<<mouseClickMenu.x <<"\t"<<mouseClickMenu.y<<endl;
		
		if(ismouseclick(513)){
			Point mouseClickMenu;
			mouseClickMenu.x=mousex();
			mouseClickMenu.y=mousey();
			//cout<<"Click : "<<mouseClickMenu.x <<"\t"<<mouseClickMenu.y<<endl;
			clearmouseclick(513);
			if(mouseClickMenu.x>=145 && mouseClickMenu.x<245 && mouseClickMenu.y>=320 && mouseClickMenu.y<370 && isLocked == false){
				PlaySound(TEXT("click.wav"), NULL, SND_ASYNC|SND_FILENAME);
				colorBG=LIGHTGRAY;
				drawBar(1,colorBG,145,320,245,370);			// 100x50 
				showText("Play",195,350,4,BOLD_FONT,2);
				delay(150);
				colorBG=15;
				drawBar(1,colorBG,145,320,245,370);			// 100x50 
				showText("Play",195,350,4,BOLD_FONT,2);
				showGameControl();
				break;
			}
			if(mouseClickMenu.x>=45&& mouseClickMenu.x<145 && mouseClickMenu.y>=390 &&mouseClickMenu.y<440){	
				isLocked=true;
				PlaySound(TEXT("click.wav"), NULL,  SND_ASYNC|SND_FILENAME);
				colorBG=LIGHTGRAY;
				drawBar(1,colorBG,45,390,145,440);			// 100x50 
				showText("Rank",95,420,2,BOLD_FONT,2);
				delay(150);
				colorBG=15;
				drawBar(1,colorBG,45,390,145,440);			// 100x50 
				showText("Rank",95,420,2,BOLD_FONT,2);
				showBestScore();
				
				//break;
			}
			if(mouseClickMenu.x>=245&& mouseClickMenu.x<345 && mouseClickMenu.y>=390 &&mouseClickMenu.y<440){	
				PlaySound(TEXT("click.wav"), NULL,  SND_ASYNC|SND_FILENAME);
				colorBG=LIGHTGRAY;
				drawBar(1,LIGHTGRAY,245,390,345,440);			// 100x50 
				showText("About",295,420,8,BOLD_FONT,2);
				delay(150);
				colorBG=15;
				drawBar(1,colorBG,245,390,345,440);			// 100x50 
				showText("About",295,420,8,BOLD_FONT,2);
	
				isLocked=true;
				
				showAbout();

				//break;

			}
		}
		
	}
	
}
#define PI 3.14159265359
void sao(int x0,int y0,int m)
{
    int x[5], y[5],j;
    int R=40;
	float d=0, a=144*PI/180;   // xac dinh goc ban dau
	for (int i=0; i<5; i++)		// xac dinh toa do 5 dinh ngoi sao
        {
            x[i] = x0 + (int)(R*sin(d));
            y[i] = y0 - (int)(R*cos(d));
            d+=a;
        }
	for (int i=0; i<5; i++)	// Ve cac duong thang noi canh ngoi sao
        {
            if (i==4) j=0; else j=i+1;
			setcolor(m);
            line(x[i],y[i],x[j],y[j]);
        }
	 setfillstyle(SOLID_FILL,m);
	 floodfill( x0          , y0           , m);		// to mau vung giua
	 floodfill( x0          , y0 - R/3     , m);		// to mau canh tren
	 floodfill( x0 - R/3 - 1, y0           , m);		// to mau canh trai
	 floodfill( x0 + R/3 + 1, y0           , m);		// to mau canh phai
	 floodfill( x0 - R/3    , y0 + R/3     , m);        // to mau canh trai duoi
	 floodfill( x0 + R/3    , y0 + R/3     , m);	    // to mau canh phai duoi

}
void showAbout(){
	colorBG=DARKGRAY;
	drawBar(1,colorBG,80,200,320,400);
	char best[10],sc[10];
	itoa(_bestScore,best,10);
	itoa(score,sc,10);
	showTextLeft("MaSV: 1481310014" ,90,280,WHITE,BOLD_FONT,18);
	//showText(sc ,240,300,WHITE,BOLD_FONT,20);
	showTextLeft("SV: Nguyen Van Duong" ,90,310,WHITE,BOLD_FONT,18);
/*	showText(best ,240,350,YELLOW,BOLD_FONT,20);*/
	showTextLeft("Lop: D9CNPM" ,90,340,WHITE,BOLD_FONT,18);
		showTextLeft("GV: Ngo Ngoc Thanh" ,90,370,WHITE,BOLD_FONT,18);
	sao(200,200,YELLOW);
	while (true)
	{
		if(ismouseclick(513)){
			isLocked=false;
			menuGame(false);
			break;
		}
	}
}
void showBestScore(){
	colorBG=DARKGRAY;
	drawBar(1,colorBG,80,200,320,400);
	char best[10],sc[10];
	itoa(_bestScore,best,10);
	itoa(score,sc,10);
	showText("New  =" ,190,300,WHITE,BOLD_FONT,20);
	showText(sc ,240,300,WHITE,BOLD_FONT,20);
	showText("Best =" ,190,350,YELLOW,BOLD_FONT,20);
	showText(best ,240,350,YELLOW,BOLD_FONT,20);
	sao(200,200,YELLOW);
	while (true)
	{
		if(ismouseclick(513)){
			isLocked=false;
			menuGame(false);
			break;
		}
	}
}

int main()
{

	bestScore(_bestScore);
	initwindow(WIDTH,HEIGHT,"Game SumTime");
	menuGame(true);

	//gameControl();
	closegraph();
//	dataFile.close();
	getch();
	return 0;
}
