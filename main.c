#include "acllib.h"
#include <stdio.h>
#include <time.h>

#define DefaultLength  1000
#define DefaultWidth 671

typedef struct character{
	int length;
	int width;
	ACL_Image image;
} CHARACTER;

typedef struct music{
	int times;
	ACL_Sound id;
} MUSIC;

int postion;
int Player_Blood = 100;
int AI_Blood = 100;
int Player_Energy = 0;
int AI_Energy = 0;
int count = 0;
int locate = 0;
int ind;
int player;
int chargeup;
int chargedown;

CHARACTER AI_Rock = {200, 200};
CHARACTER AI_Scissors = {200, 200};
CHARACTER AI_Paper = {200, 200};
CHARACTER Player_Rock = {200, 200};
CHARACTER Player_Paper = {200, 200};
CHARACTER Player_Scissors = {200, 200};
CHARACTER win_picture = {400, 400};
CHARACTER lose_picture = {400, 400};
CHARACTER Clap_picture = {200, 200};
CHARACTER Shield = {200, 200};
CHARACTER Player_Attack = {200, 200};
CHARACTER AI_Attack = {200, 200};
CHARACTER Player = {100, 100};
CHARACTER WuJing = {100, 100};
CHARACTER AI = {100, 100};
MUSIC clapmusic = {5};
MUSIC zoomusic = {5};
MUSIC sleevemusic = {5};

void PaintMenu (void);
void MouseListener (int x, int y, int button, int event);
void Rock_Paper_Scissors (void);
void Clap_Game (void);
void PutClap (void);
void PutShield (void);
void PutAttack (void);
void Sleeve (void);
void UpBlock (void);
void DownBlock (void);
void UpDie (int a);
void DownDie (int a);
void PutRock (void);
void PutScissors (void);
void PutPaper (void);
void ChargeClap (int a);
void Win (int a);
void Lose (int a);
void Hand (int a);
void Back_Game1 (int a);
void Back_Game2 (int a);
void Back_Game3 (int a);

int Setup()
{
	srand((unsigned)time(NULL));
	initWindow ("3in1 Game~", DEFAULT, DEFAULT, DefaultLength, DefaultWidth);
	PaintMenu();

	return 0;
}

void PaintMenu ()
{
	for (int i = 0; i < 50; i++)
	{
		stopSound (zoomusic.id);
	    stopSound (clapmusic.id);
	    stopSound (sleevemusic.id);
	}

	postion = 0;
	Player_Blood = 100;
	AI_Blood = 100;
	Player_Energy = 0;
	AI_Energy = 0;
	ind = 0;
	locate = 0;
	beginPaint();

	setPenColor(EMPTY);
	setBrushColor(RGB(255, 234, 0));
	rectangle (0, 0, DefaultLength, DefaultWidth);

	setTextColor(RGB(66, 188, 172));
	setTextBkColor(RGB(255,234,0));
	setTextFont("Brush Script MT");
	setTextSize(200);
	paintText(370, 40, "3in1");
	setTextSize(100);
	paintText(400, 231, "ZOO");
	paintText(350, 371, "Clap Game");
	paintText(350, 521, "Sleeve Fish");

    endPaint();

	registerMouseEvent(MouseListener);
}

void MouseListener (int x, int y, int button, int event)
{
	if (postion == 0)// means in the menu.
	{
	    if (x >= 175 && x <= 825 && y >= 225 && y <= 325 && button == 1 && event == 0)
	    {
		    Rock_Paper_Scissors ();
	    }
	    if (x >= 350 && x <= 670 && y >= 370 && y <= 470 && button == 1 && event == 0)
	    {
	    	Clap_Game ();
		}
		if (x >= 350 && x <= 670 && y >= 520 && y <= 620 && button == 1 && event == 0)
		{
			Sleeve ();
		}
    }
    
    else if (postion == 1)//means in the Rock_Paper_Scissors.
    {
		if(x <= 100 && y <= 50 && button == 1 && event == 0)
		{
			PaintMenu ();
		}
		if (x >= 100 && x <= 300 && y >= 450 && y <= 650 && button == 1 && event == 0)
		{
			PutRock ();
		}
		if (x >= 400 && x <= 600 && y >= 450 && y <= 650 && button == 1 && event == 0)
		{
			PutScissors ();
		}
		if (x >= 700 && x <= 900 && y >= 450 && y <= 650 && button == 1 && event == 0)
		{
			PutPaper ();
		}
    }

	else if (postion == 2)//means in the Clap_Game.
	{
		if(x <= 100 && y <= 50 && button == 1 && event == 0)
		{
			PaintMenu ();
		}
		if (x >= 100 && x <= 300 && y >= 450 && y <= 650 && button == 1 && event == 0
		    && Player_Blood > 0 && AI_Blood > 0)
		{
			PutClap ();
		}
		if (x >= 400 && x <= 600 && y >= 450 && y <= 650 && button == 1 && event == 0 
		    && Player_Blood > 0 && AI_Blood > 0)
		{
			PutShield ();
		}
		if (x >= 700 && x <= 900 && y >= 450 && y <= 650 && button == 1 && event == 0 && 
		    Player_Blood > 0 && AI_Blood > 0)
		{
			PutAttack ();
		}
	}

	else if (postion == 3 && ind != 4)//means in the Sleeve.
	{
		if(x <= 100 && y <= 50 && button == 1 && event == 0)
		{
			PaintMenu ();
		}
		if (x >= 700 && x <= 800 && y >= 210 && y <= 310 && button == 1 && event == 0)
		{
			UpBlock ();
		}
		if (x >= 700 && x <= 800 && y >= 360 && y <= 460 && button == 1 && event == 0)
		{
			DownBlock ();
		}
	}
}

void Rock_Paper_Scissors ()
{
	postion = 1;
	beginPaint();

	setBrushColor(RGB(255, 234, 0));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextBkColor(RGB(255,234,0));
	setTextColor(RGB(66, 188, 172));
	setTextSize(50);
	paintText(0, 0, "MENU");
	
	loadImage("picture\\Rock-Paper-Scissors\\AI-Rock.jpg", &AI_Rock.image);
    loadImage("picture\\Rock-Paper-Scissors\\AI-Paper.jpg", &AI_Paper.image);
    loadImage("picture\\Rock-Paper-Scissors\\AI-Scissors.jpg", &AI_Scissors.image);
    loadImage("picture\\Rock-Paper-Scissors\\Player-Rock.jpg", &Player_Rock.image);
    loadImage("picture\\Rock-Paper-Scissors\\Player-Paper.jpg", &Player_Paper.image);
    loadImage("picture\\Rock-Paper-Scissors\\Player-Scissors.jpg", &Player_Scissors.image);

	putImageScale(&Player_Rock.image, 100, 450, Player_Rock.length, Player_Rock.width);
	putImageScale(&Player_Scissors.image, 400, 450, Player_Scissors.length, Player_Scissors.width);
	putImageScale(&Player_Paper.image, 700, 450, Player_Paper.length, Player_Paper.width);

	endPaint();

	loadSound("music\\zoomusic.mp3", &zoomusic.id);
	playSound(zoomusic.id, 5);//???????????????????????????????????????????????????zoo????????????????????????????????????????????????
	
	registerMouseEvent(MouseListener);
}

void PutRock ()
{
	postion = 10;
	beginPaint();

	setBrushColor(RGB(255, 234, 0));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextBkColor(RGB(255,234,0));
	setTextColor(RGB(66, 188, 172));
	setTextSize(50);
	paintText(0, 0, "MENU");
	
	putImageScale(&Player_Rock.image, 100, 100, 300, 300);

	int lilAI = rand() % 3;
	if (lilAI == 0)
	{
		putImageScale (&AI_Rock.image, 600, 100, 300, 300);
		endPaint();
		registerTimerEvent (Hand);
		startTimer (0, 2000);
	}
	if (lilAI == 1)
	{
		putImageScale(&AI_Scissors.image, 600, 100, 300, 300);
		endPaint();
		registerTimerEvent (Win);
		startTimer (1, 2000);
	}
	if (lilAI == 2)
	{
		putImageScale(&AI_Paper.image, 600, 100, 300, 300);
		endPaint();
		registerTimerEvent (Lose);
		startTimer (2, 2000);
	}

	registerMouseEvent(MouseListener);
}

void PutScissors ()
{
	postion = 10;
	beginPaint();

	setBrushColor(RGB(255, 234, 0));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextBkColor(RGB(255,234,0));
	setTextColor(RGB(66, 188, 172));
	setTextSize(50);
	paintText(0, 0, "MENU");
	

	putImageScale(&Player_Scissors.image, 100, 100, 300, 300);

	int lilAI = rand() % 3;
	if (lilAI == 0)
	{
		putImageScale (&AI_Rock.image, 600, 100, 300, 300);
		endPaint();
		registerTimerEvent (Lose);
		startTimer (2, 2000);
	}
	if (lilAI == 1)
	{
		putImageScale(&AI_Scissors.image, 600, 100, 300, 300);
		endPaint();
		registerTimerEvent (Hand);
		startTimer (0, 2000);
	}
	if (lilAI == 2)
	{
		putImageScale(&AI_Paper.image, 600, 100, 300, 300);
		endPaint();
		registerTimerEvent (Win);
		startTimer (1, 2000);
	}

	registerMouseEvent(MouseListener);
}

void PutPaper ()
{
	postion = 10;
	beginPaint();

	setBrushColor(RGB(255, 234, 0));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextBkColor(RGB(255,234,0));
	setTextColor(RGB(66, 188, 172));
	setTextSize(50);
	paintText(0, 0, "MENU");

	putImageScale(&Player_Paper.image, 100, 100, 300, 300);

	int lilAI = rand() % 3;
	if (lilAI == 0)
	{
		putImageScale (&AI_Rock.image, 600, 100, 300, 300);
		endPaint();
		registerTimerEvent (Win);
		startTimer (1, 2000);
	}
	if (lilAI == 1)
	{
		putImageScale(&AI_Scissors.image, 600, 100, 300, 300);
		endPaint();
		registerTimerEvent (Lose);
		startTimer (2, 2000);
	}
	if (lilAI == 2)
	{
		putImageScale(&AI_Paper.image, 600, 100, 300, 300);
		endPaint();
		registerTimerEvent (Hand);
		startTimer (0, 2000);
	}

	registerMouseEvent(MouseListener);
}

void Clap_Game ()
{
	postion = 2;
	beginPaint();

	setBrushColor(RGB(66, 188, 172));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setBrushColor(WHITE);
	rectangle(0, 0, 100, 50);
	setTextSize(50);
	setTextBkColor(RGB(66, 188, 172));
	setTextColor(RGB(255, 234, 0));
	paintText(0, 0, "MENU");
	
	loadImage("picture\\Clap-Game\\Clap.jpg", &Clap_picture.image);
    loadImage("picture\\Clap-Game\\Shield.jpg", &Shield.image);
    loadImage("picture\\Clap-Game\\AI_Attack.jpg", &AI_Attack.image);
    loadImage("picture\\Clap-Game\\Player_Attack.jpg", &Player_Attack.image);

	putImageScale(&Clap_picture.image, 100, 450, Clap_picture.length, Clap_picture.width);
	putImageScale(&Shield.image, 400, 450, Shield.length, Shield.width);
	putImageScale(&Player_Attack.image, 700, 450, Player_Attack.length, Player_Attack.width);

	if (ind == 0)
	{
		player = rand() % 3;
		if (player == 0) loadImage ("picture\\Clap-Game\\Super_Huaqiang.jpg", &Player.image);
		else loadImage ("picture\\Clap-Game\\Huaqiang.jpg", &Player.image);
	}
	loadImage ("picture\\Clap-Game\\Boss.jpg", &AI.image);

	putImageScale(&Player.image, 100, 100, 300, 300);
	putImageScale(&AI.image, 600, 100, 300, 300);

	setBrushColor (RED);
	rectangle (0, 50, Player_Blood * 2, 100);
	rectangle (1000 - AI_Blood * 2, 50, 1000, 100);
	setBrushColor (BLUE);
	rectangle (0, 100, Player_Energy * 2, 150);
	rectangle (1000 - AI_Energy * 2, 100, 1000, 150);

	endPaint();

	registerTimerEvent (ChargeClap);
	startTimer (4, 1000);

	// loadSound("music\\clap.mp3", &clapmusic.id);
	// if (ind == 0) playSound(clapmusic.id, 5);
	
	registerMouseEvent (MouseListener);
}

void PutClap ()
{
	ind ++;
	beginPaint();

	setBrushColor(RGB(66, 188, 172));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextBkColor(RGB(66, 188, 172));
	setTextColor(RGB(255, 234, 0));
	setTextSize(50);
	paintText(0, 0, "MENU");

	putImageScale(&Clap_picture.image, 100, 100, 300, 300);

	if (Player_Energy > 80) Player_Energy = 100;
	else Player_Energy += 20;

	int lilAI = rand() % 3;
	if (AI_Energy == 0) lilAI = lilAI % 2;
	if (AI_Energy == 100) lilAI = lilAI % 2 + 1;
	if (lilAI == 0)
	{
		putImageScale (&Clap_picture.image, 600, 100, 300, 300);
		if (AI_Energy > 80) AI_Energy = 100;
		else AI_Energy += 20;
	}
	if (lilAI == 1)
	{
		putImageScale(&Shield.image, 600, 100, 300, 300);
	}
	if (lilAI == 2)
	{
		putImageScale(&AI_Attack.image, 600, 100, 300, 300);
		if (player != 0) Player_Blood -= AI_Energy;
		AI_Energy = 0;
	}

	endPaint();

	registerTimerEvent(Back_Game2);
	startTimer (5, 1500);
}

void PutShield ()
{
	ind ++;
	beginPaint();

	setBrushColor(RGB(66, 188, 172));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextBkColor(RGB(66, 188, 172));
	setTextColor(RGB(255, 234, 0));
	setTextSize(50);
	paintText(0, 0, "MENU");

	putImageScale(&Shield.image, 100, 100, 300, 300);

	int lilAI = rand() % 3;
	if (AI_Energy == 0) lilAI = lilAI % 2;
	if (AI_Energy == 100) lilAI = lilAI % 2 + 1;
	if (lilAI == 0)
	{
		putImageScale (&Clap_picture.image, 600, 100, 300, 300);
		if (AI_Energy > 80) AI_Energy = 100;
		else AI_Energy += 20;
	}
	if (lilAI == 1)
	{
		putImageScale(&Shield.image, 600, 100, 300, 300);
	}
	if (lilAI == 2)
	{
		putImageScale(&AI_Attack.image, 600, 100, 300, 300);\
		AI_Energy = 0;
	}

	endPaint();

	registerTimerEvent(Back_Game2);
	startTimer (5, 1500);
}

void PutAttack ()
{
	ind ++;
	beginPaint();

	setBrushColor(RGB(66, 188, 172));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextBkColor(RGB(66, 188, 172));
	setTextColor(RGB(255, 234, 0));
	setTextSize(50);
	paintText(0, 0, "MENU");

	putImageScale(&Player_Attack.image, 100, 100, 300, 300);

	int lilAI = rand() % 3;
	if (AI_Energy == 0) lilAI = lilAI % 2;
	if (AI_Energy == 100) lilAI = lilAI % 2 + 1;
	if (lilAI == 0)
	{
		putImageScale (&Clap_picture.image, 600, 100, 300, 300);
		if (AI_Energy > 80) AI_Energy = 100;
		else AI_Energy += 20;
		AI_Blood -= Player_Energy;
		Player_Energy = 0;
	}
	if (lilAI == 1)
	{
		putImageScale(&Shield.image, 600, 100, 300, 300);
		if (player == 0) AI_Blood -= Player_Energy;
		Player_Energy = 0;
	}
	if (lilAI == 2)
	{
		putImageScale(&AI_Attack.image, 600, 100, 300, 300);
		AI_Blood -= Player_Energy;
		if (player != 0) Player_Blood -= AI_Energy;
		Player_Energy = 0;
		AI_Energy = 0;
	}

	endPaint();

    registerTimerEvent(Back_Game2);
	startTimer (5, 1500);
}

void ChargeClap (int a)
{
	cancelTimer (a);
	if (Player_Blood <= 0 && AI_Blood > 0)
	{
		Player_Blood = 100;
		AI_Blood = 100;
		Player_Energy = 0;
		AI_Energy = 0;
		Lose (2);
	}

	else if (Player_Blood > 0 && AI_Blood <= 0)
	{
		Player_Blood = 100;
		AI_Blood = 100;
		Player_Energy = 0;
		AI_Energy = 0;
		Win (1);
	}

	else if (Player_Blood <= 0 && AI_Blood <= 0)
	{
		Player_Blood = 100;
		AI_Blood = 100;
		Player_Energy = 0;
		AI_Energy = 0;
		Hand (0);
	}
}

void Sleeve()
{
	postion = 3;

	if (ind == 4)
	{
		registerTimerEvent (Win);
		startTimer (1, 2000);
	}

	beginPaint();

	setBrushColor(RGB(222, 67, 165));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextSize(50);
	setTextBkColor(RGB(222, 67, 165));
	paintText(0, 0, "MENU");

	setBrushColor (RGB(129, 99, 189));
	setPenColor (RGB(255, 234, 0));
	for (int i = 100 + ind * 200; i <= 700; i += 200)
	{
		rectangle (i, 210, i + 100, 310);
		rectangle (i, 360, i + 100, 460);
	}

	if (ind == 0)
	{
		player = rand() % 3;
		if (player == 0) loadImage ("picture\\Sleeve_Fish\\WuJing.jpg", &Player.image);
		else loadImage ("picture\\Sleeve_Fish\\Player.jpg", &Player.image);
	}

	switch (locate)
	{
		case 0:
			putImageScale (&Player.image, 900, 285, 100, 100);
			break;
		case 1:
			rectangle (900, 210, 1000, 310);
			rectangle (900, 360, 1000, 460);
			putImageScale (&Player.image, 900, 210, 100, 100);
			break;
		case 2:
			rectangle (900, 210, 1000, 310);
			rectangle (900, 360, 1000, 460);
			putImageScale (&Player.image, 900, 360, 100, 100);
	}
	
	endPaint ();

	// loadSound("music\\sleeve.mp3", &sleevemusic.id);
	// if(ind == 0) playSound(sleevemusic.id, 5);

	registerMouseEvent (MouseListener);
}

void UpBlock ()
{
	chargeup = rand() % 2;
	count = 100;
	locate = 1;
	beginPaint();

	setBrushColor(RGB(222, 67, 165));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextSize(50);
	setTextBkColor(RGB(222, 67, 165));
	paintText(0, 0, "MENU");

	setBrushColor (RGB(129, 99, 189));
	setPenColor (RGB(255, 234, 0));
	for (int i = 100 + ind * 200; i <= 500; i += 200)
	{
		rectangle (i, 210, i + 100, 310);
		rectangle (i, 360, i + 100, 460);
	}
	rectangle (700, 360 ,800, 460);

	if (chargeup == 0) 
	{
		for (int i = 0; i < 50; i++)
		{
			stopSound (zoomusic.id);
			stopSound (clapmusic.id);
			stopSound (sleevemusic.id);
		}
		endPaint ();
		registerTimerEvent (UpDie);
		startTimer (6, 250);
	}
	else if (chargeup == 1)
	{
		if (ind == 3)
		{
			for (int i = 0; i < 50; i++)
			{
				stopSound (zoomusic.id);
				stopSound (clapmusic.id);
				stopSound (sleevemusic.id);
			}
		}
		putImageScale (&Player.image, 700, 210, 100, 100);
		endPaint ();
		ind ++;
		registerTimerEvent (Back_Game3);
		startTimer (8, 1000);
	}
}

void UpDie (int a)
{
	for (int i = 0; i < 50; i++)
	{
		stopSound (zoomusic.id);
	    stopSound (clapmusic.id);
	    stopSound (sleevemusic.id);
	}
	beginPaint();

	setBrushColor(RGB(222, 67, 165));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextSize(50);
	setTextBkColor(RGB(222, 67, 165));
	paintText(0, 0, "MENU");

	setBrushColor (RGB(129, 99, 189));
	setPenColor (RGB(255, 234, 0));
	for (int i = 100 + ind * 200; i <= 500; i += 200)
	{
		rectangle (i, 210, i + 100, 310);
		rectangle (i, 360, i + 100, 460);
	}
	rectangle (700, 360 ,800, 460);

	rectangle (700 + (100 - count) / 2, 210 + (100 - count) / 2, 
			  800 - (100 - count) / 2, 310 - (100 - count) / 2);
	if (player != 0) putImageScale (&Player.image, 700 + (100 - count) / 2, 210 + (100 - count) / 2, 
				count, count);
	else if (player == 0) putImageScale (&Player.image, 700, 210, 100, 100);
	endPaint ();
	if (count == 0 && player != 0)
	{
		Lose (2);
		cancelTimer (a);
	}
	if (count == 0 && player == 0)
	{
		ind ++;
		registerTimerEvent (Back_Game3);
		startTimer (8, 1500);
		cancelTimer (a);
	}
	count -= 10;
}

void DownBlock ()
{
	count = 100;
	locate = 2;
	beginPaint();

	setBrushColor(RGB(222, 67, 165));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextSize(50);
	setTextBkColor(RGB(222, 67, 165));
	paintText(0, 0, "MENU");

	setBrushColor (RGB(129, 99, 189));
	setPenColor (RGB(255, 234, 0));
	for (int i = 100 + ind * 200; i <= 500; i += 200)
	{
		rectangle (i, 210, i + 100, 310);
		rectangle (i, 360, i + 100, 460);
	}
	rectangle (700, 210 ,800, 310);

	int chargedown = rand() % 2;

	if (chargedown == 0) 
	{
		for (int i = 0; i < 50; i++)
		{
			stopSound (zoomusic.id);
			stopSound (clapmusic.id);
			stopSound (sleevemusic.id);
		}
		endPaint ();
		registerTimerEvent (DownDie);
		startTimer (6, 250);
	}
	else if (chargedown == 1)
	{
		if (ind == 3)
		{
			for (int i = 0; i < 50; i++)
			{
				stopSound (zoomusic.id);
				stopSound (clapmusic.id);
				stopSound (sleevemusic.id);
			}
		}
		putImageScale (&Player.image, 700, 360, 100, 100);
		endPaint ();
		ind ++;
		registerTimerEvent (Back_Game3);
		startTimer (8, 1000);
	}
}

void DownDie (int a)
{
	for (int i = 0; i < 50; i++)
	{
		stopSound (zoomusic.id);
	    stopSound (clapmusic.id);
	    stopSound (sleevemusic.id);
	}
	beginPaint();

	setBrushColor(RGB(222, 67, 165));
	rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextSize(50);
	setTextBkColor(RGB(222, 67, 165));
	paintText(0, 0, "MENU");

	setBrushColor (RGB(129, 99, 189));
	setPenColor (RGB(255, 234, 0));
	for (int i = 100 + ind * 200; i <= 500; i += 200)
	{
		rectangle (i, 210, i + 100, 310);
		rectangle (i, 360, i + 100, 460);
	}
	rectangle (700, 210 ,800, 310);

	rectangle (700 + (100 - count) / 2, 360 + (100 - count) / 2, 
			  800 - (100 - count) / 2, 460 - (100 - count) / 2);
	if (player != 0) putImageScale (&Player.image, 700 + (100 - count) / 2, 360 + (100 - count) / 2, 
				count, count);
	else if (player == 0) putImageScale (&Player.image, 700, 360, 100, 100);
	endPaint ();
	if (count == 0 && player != 0)
	{
		Lose (2);
		cancelTimer (a);
	}
	if (count == 0 && player == 0)
	{
		ind ++;
		registerTimerEvent (Back_Game3);
		startTimer (8, 1500);
		cancelTimer (a);
	}
	count -= 10;
}

void Win (int b)
{
	for (int i = 0; i < 50; i++)
	{
		stopSound (zoomusic.id);
	    stopSound (clapmusic.id);
	    stopSound (sleevemusic.id);
	}
	ind = 0;
	locate = 0;
	cancelTimer (b);
	beginPaint ();
	loadImage("picture\\win_picture.jpg", &win_picture.image);
	setBrushColor (RGB(255, 43, 5));
    rectangle (0, 0, DefaultLength, DefaultWidth);
	putImage (&win_picture.image, 300, 150);
	endPaint ();
	switch (postion)
	{
		case 10:
		registerTimerEvent(Back_Game1);
		startTimer(3, 1500);
		break;
		case 2:
		registerTimerEvent(Back_Game2);
		startTimer (5, 1500);
		break;
		case 3:
		registerTimerEvent(Back_Game3);
		startTimer (8, 1500);
		break;
	}
}

void Lose (int b)
{
	for (int i = 0; i < 50; i++)
	{
		stopSound (zoomusic.id);
	    stopSound (clapmusic.id);
	    stopSound (sleevemusic.id);
	}
	printf("%d", postion);
	ind = 0;
	locate = 0;
	cancelTimer (b);
	beginPaint ();
	setBrushColor (RGB(255, 43, 5));
	loadImage("picture\\lose_picture.jpg", &lose_picture.image);
    rectangle (0, 0, DefaultLength, DefaultWidth);
	putImageScale (&lose_picture.image, 300, 150, 400, 312);
	endPaint ();
	switch (postion)
	{
		case 10:
		registerTimerEvent(Back_Game1);
		startTimer(3, 1500);
		break;
		case 2:
		registerTimerEvent(Back_Game2);
		startTimer (5, 1500);
		break;
		case 3:
		registerTimerEvent(Back_Game3);
		startTimer (8, 1500);
		break;
	}
}

void Hand (int b)
{
	for (int i = 0; i < 50; i++)
	{
		stopSound (zoomusic.id);
	    stopSound (clapmusic.id);
	    stopSound (sleevemusic.id);
	}
	printf("%d", postion);
	cancelTimer (b);
	beginPaint ();
	setBrushColor (RED);
    rectangle (0, 0, DefaultLength, DefaultWidth);
	setTextBkColor (RED);
	setTextColor (GREEN);
	setTextSize (200);
	paintText (230, 150, "StandOff");
	endPaint ();
	switch (postion)
	{
		case 10:
		stopSound (zoomusic.id);
		registerTimerEvent(Back_Game1);
		startTimer(3, 1500);
		break;
		case 2:
		stopSound (clapmusic.id);
		registerTimerEvent(Back_Game2);
		startTimer (5, 1500);
		break;
	}
}

void Back_Game1 (int a)
{
	cancelTimer (a);
	Rock_Paper_Scissors ();
}

void Back_Game2 (int a)
{
	cancelTimer (a);
	Clap_Game ();
}

void Back_Game3 (int a)
{
	cancelTimer (a);
	Sleeve ();
}
