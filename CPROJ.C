#include<stdio.h>
#include<conio.h>
#include<bios.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#include<dos.h>
#include<time.h>

#define PI 3.147
int maxx,maxy,flag=0;
//global variables to be used in several funtions.

void starti(); //function declaration to be used later.

//function to display the front page specifying name of project.
void welcomepage()
{
  int gd=DETECT,gm,stangle;
  clrscr();
  initgraph(&gd, &gm,"C:\\TURBOC3\\BGI"); //graphics connection
  setcolor(8);
  ellipse(320,240,0,360,300,150);
  settextstyle(10,0,2);
  settextjustify(1,1);
  setcolor(5);
  outtextxy(320,170,"REAL-TIME WATCH");
  delay(250);
  settextstyle(4,0,4);
  setcolor(20);
  outtextxy(320,240,"Presented By:");
  delay(250);
  setcolor(9);
  settextstyle(10,0,4);
  outtextxy(320,315,"SOURAV");
  setcolor(2);
  // for loop used for dynamic look of the ellipse.
  for (stangle=0;!kbhit();stangle++)
  {
    setcolor(7);
    ellipse(320,240,stangle,stangle+20,300,160);
    ellipse(320,240,stangle+180,stangle+200,300,160);
    delay(9);
    setcolor(8);
    ellipse(320,240,stangle-1,stangle+19,300,160);
    ellipse(320,240,stangle-1+180,stangle+199,300,160);
  }
  closegraph();
  getch();
}

//function to display the main menu.
void display(int n)
{
  int i=0;
  char menu[7][40]={"select using enter:"," 1. ANALOG CLOCK" , " 2. DIGITAL" ," 3. STOP WATCH"," 4. ABOUT", " 5. EXIT","use arrow keys to move up and down"};
  for(i=0;i<7;i++)
  {
    if(i==n)
    {
      //textbackground and textcolor are changed to highlight the text on current cursor postion.
      textbackground(WHITE);
      textcolor(RED);
      gotoxy(1,i+1);
      cprintf("%s\n",menu[i]);
      textbackground(BLACK);
      textcolor(WHITE);
    }
    else
    {
      gotoxy(1,i+1);
      textbackground(BLACK);
      textcolor(WHITE);
      cprintf("%s\n",menu[i]);
    }
  }
}

//function to make the basic structure of the analog clock.
void clockLayout()
{
  int i,x,y,r;
  float j;
  maxx=getmaxx();
  maxy=getmaxy();

  for(i=1;i<5;i++)
  {
    /* printing a round ring with outer radius of 5 pixel */
    setcolor(YELLOW);
    circle(maxx/2,maxy/2,120-i);
  }

  pieslice(maxx/2,maxy/2,0,360,5);    /* displaying a circle in the middle of clock */
  x=maxx/2+100;y=maxy/2;
  r=100;
  setcolor(BLUE);

  for(j=PI/6;j<=(2*PI);j+=(PI/6))
  {
    /* marking the hours for every 30 degrees */
    pieslice(x,y,0,360,4);
    x=(maxx/2)+r*cos(j);
    y=(maxy/2)+r*sin(j);
  }

  x=maxx/2+100;y=maxy/2;
  r=100;
  setcolor(RED);

  for(j=PI/30;j<=(2*PI);j+=(PI/30))
  {
    /* marking the minutes for every 6 degrees */
    pieslice(x,y,0,360,2);
    x=(maxx/2)+r*cos(j);
    y=(maxy/2)+r*sin(j);
  }
  setcolor(WHITE);
  outtextxy(getmaxx()/2-25, getmaxy()/3, "SOURAV");
  outtextxy(210,380,"press \"esc\" to go to main menu");
}

//function to change the second hand in accord with the system time.
void secHand()
{
  struct time t;
  int r=90,x=maxx/2,y=maxy/2,sec;
  float O;

  maxx=getmaxx();maxy=getmaxy();
  gettime(&t);
  /*getting the seconds in system clock */
  sec=t.ti_sec;
  /* determining the angle of the line with respect to vertical */
  O=sec*(PI/30)-(PI/2);
  setcolor(GREEN);
  line(maxx/2,maxy/2,x+r*cos(O),y+r*sin(O));
}

//function to change the hour hand in accord with the system time.
void hrHand()
{
 int r=60,hr,min;
 int x,y;
 struct time t;
 float O;
 maxx=getmaxx();
 maxy=getmaxy();
 x=maxx/2,y=maxy/2;
 gettime(&t);
 /*getting the hours  in system clock */
 hr=t.ti_hour;
 min=t.ti_min;

 /* determining the angle of the line with respect to vertical */
 if(hr<=12)O=(hr*(PI/6)-(PI/2))+((min/12)*(PI/30));
 if(hr>12) O=((hr-12)*(PI/6)-(PI/2))+((min/12)*(PI/30));
 setcolor(BLUE);
 line(maxx/2,maxy/2,x+r*cos(O),y+r*sin(O));
}

//function to change the minute hand in accord with the system time.
void minHand()
{
 int r=85,min;
 int x,y;
 float O;
 struct time t;
 maxx=getmaxx();
 maxy=getmaxy();
 x=maxx/2;
 y=maxy/2;
 gettime(&t);
 /*getting the seconds in system clock */
 min=t.ti_min;
 /* determining the angle of the line with respect to vertical */
 O=(min*(PI/30)-(PI/2));
 setcolor(RED);
 line(maxx/2,maxy/2,x+r*cos(O),y+r*sin(O));
}

//function used to display the first page of stopwatch.
int start()
{
  int gd=DETECT,gm,sec,min,hour,first=0,second=0;
  char s1[3],s2[3],s3[3],s[9];
  int y;
  initgraph(&gd,&gm,"..\\bgi"); // graphics initiation.
  min=0;
  sec=0;
  hour=0;

  //itoa is used to change integer value to string.
  itoa(hour,s1,10);
  itoa(min,s2,10);
  itoa(sec,s3,10);

  //strcpy is used to copy a string to another string.
  strcpy(s,s1);

  //strcat is used to concatenate two strings.
  strcat(s,":");
  strcat(s,s2);
  strcat(s,":");
  strcat(s,s3);
  settextstyle(6,0,4);
  outtextxy(280,130,s);
  rectangle(270,230,370,270);

  //used to fill the rectangle with the specific color annd fill style.
  setfillstyle(1,CYAN);
  floodfill(271,231,WHITE);
  settextstyle(3,0,4);
  outtextxy(276,227,"START");
  rectangle(270,290,370,330);
  outtextxy(292,288,"EXIT");

  //bioskey is used to use the keys which are not having ascii value e.g. arrows, enter.
  while((y=bioskey(0))!=75)
  {
    //20480 is used for up arrow.
    if(y==20480)
    {
      second++;
      first=0;
      cleardevice();
      settextstyle(6,0,4);
      outtextxy(280, 130, s);
      rectangle(270,230,370,270);
      settextstyle(3,0,4);
      outtextxy(276,227,"START");
      rectangle(270,290,370,330);
      setfillstyle(1,CYAN);
      floodfill(271, 300, WHITE);
      outtextxy(292,288,"EXIT");
    }

    //18432 is used for down arrow key.
    else if(y==18432)
    {
      first++;
      second=0;
      cleardevice();
      settextstyle(6,0,4);
      outtextxy(280, 130, s);
      rectangle(270,230,370,270);
      setfillstyle(1,CYAN);
      floodfill(271,232, WHITE);
      settextstyle(3,0,4);
      outtextxy(276,227,"START");
      rectangle(270,290,370,330);
      outtextxy(292,288,"EXIT");
    }

    //7181 is used for enter key
    else if(y==7181)
    {
      //if start is selected.
      if(second==0)
      {
	starti();
      }

      //if exit is selected.
      else
      {
	flag++;
	cleardevice();
	closegraph();
	main();
      }
    }
    else
	return 0;
  }
  getch();
  closegraph();
  return 0;
}

//function used to display the second page of stopwatch.
void starti()
{
  int sec=0,min=0,hour=0,first=0,second=0;
  char s1[3],s2[3],s3[3],s[9];

  //initializing the variables with their respective ascii value.
  int escape=27;
  int space=32;

  //loop continues till any key is pressed.
  while(!kbhit())
  {
    cleardevice();
    itoa(hour,s1,10);
    itoa(min,s2,10);
    itoa(sec,s3,10);
    strcpy(s,s1);
    strcat(s,":");
    strcat(s,s2);
    strcat(s,":");
    strcat(s,s3);
    settextstyle(6,0,4);
    outtextxy(280,130,s);
    settextstyle(3,0,2);
    outtextxy(150,190,"press SPACE to stop stopwatch...");
    sleep(1);
    sec++;
    settextstyle(6,0,4);
    outtextxy(280, 130, s);

    if(sec==60)
    {
      sec=0;
      min++;
    }
    if(min==60)
    {
      min=0;
      hour++;
    }
  }

  //if space is pressed.
  if(space==getch())
  {
    cleardevice();
    outtextxy(280,130,s);
    settextstyle(3,0,2);
    outtextxy(150,190,"press ESC to restart stopwatch...");
    settextstyle(6,0,4);
    if(escape==getch())
	start();
  }
}

//function to display the text at the center of screen using graphics.
void centre(char s[])
{
  int midx,midy;
  midx=getmaxx()/2;
  midy=getmaxy()/2;
  settextstyle(3,0,6);
  outtextxy(midx-100,midy-35,s);
}

//function to display the about information of the project.
void about()
{
  int gd=DETECT,gm;
  clrscr();
  initgraph(&gd,&gm,"..\\bgi");
  settextstyle(3,0,2);
  setbkcolor(1);
  outtextxy(1,41,"   THE NAME \"REAL-TIME CLOCK\" HAS BEEN GIVEN TO THIS");
  outtextxy(1,66,"   PROJECT. THE KEY FEATURES OF THIS PROJECT ARE :");
  outtextxy(1,111,"   -> AN ANALOG CLOCK SHOWING REAL TIME.");
  outtextxy(1,136,"   -> A DIGITAL CLOCK SHOWING REAL TIME.");
  outtextxy(1,161,"   -> A STOPWATCH FOR KEEPING THE TRACK OF TIME.");
  outtextxy(1,186,"   -> EASY TO USE INTERFACE.");
  outtextxy(1,231,"   THE MAJOR CONCEPT USED FOR BUILDING THIS PROJECT IS");
  outtextxy(1,256,"   GRAPHICS. THE TARGET AREA OF THIS PROJECT IS PEOPLE");
  outtextxy(1,281,"   WHO ARE JOB SEEKERS AND STUDENTS , WHO OFTEN GET");
  outtextxy(1,306,"   LATE FOR THEIR DAILY ROUTINE TASKS/DUTIES. NOWADAYS,");
  outtextxy(1,331,"   LAPTOPS /COMPUTERS ARE QUITE COMMON. THE WATCHES");
  outtextxy(1,356,"   HAVE BEEN OUT OF TRENDS NOW. SO, THE BASIC PURPOSE");
  outtextxy(1,381,"   OF THIS PROJECT IS TO TAKE THE TIME FROM WATCHES TO");
  outtextxy(1,406,"   LAPTOPS/COMPUTERS.");
  getch();
  closegraph();
}

int main()
{
  int x,i=2;

  //flag=0 is used to display the welcome page only for the first time.
  if(flag==0)
    welcomepage();

//g is label.
g:
  clrscr();
  display(i-1);
  gotoxy(1,i);
  while((x=bioskey(0))!=75)
  {
    if(x==20480)
    {
      if(i<=5)
      {
	gotoxy(1,i+1);
	i++;
	display(i-1);//added
      }
    }
    else if(x==18432)
    {
      if(i!=2)
      {
	gotoxy(1,i-1);
	i--;
	display(i-1);
      }
    }
    else if(x==7181)
    {
      clrscr();

      //it means second line and first option of analog clock is selected.
      if(i==2)
      {
	int gdriver=DETECT,gmode,error;
	initgraph(&gdriver,&gmode,"..\\bgi");
	error=graphresult();
	if(error!=grOk)
	{
	  printf("Error in graphics, code= %d",grapherrormsg(error));
	  exit(0);
	}

	while(!kbhit())
	{
	  clockLayout();
	  secHand();
	  minHand();
	  hrHand();
	  sleep(1);                /* pausing the outputscreen for 1 sec */
	  cleardevice();           /* clearing the previous picture of clock */
	}
	closegraph();
	goto g;
      }

      //it means third line and second option of digital clock is selected.
      else if(i==3)
      {
	struct time t;
	int sec,min,hour,gd=DETECT,gm;
	char s1[3],s2[3],s3[3],s[10];
	clrscr();
	initgraph(&gd,&gm,"..\\bgi");
	gettime(&t);
	sec=t.ti_sec;
	min=t.ti_min;
	hour=t.ti_hour;
	while(!kbhit())
	{
	  itoa(hour,s1,10);
	  itoa(min,s2,10);
	  itoa(sec,s3,10);
	  strcpy(s,s1);
	  strcat(s,":");
	  strcat(s,s2);
	  strcat(s,":");
	  strcat(s,s3);
	  centre(s);
	  settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	  outtextxy(200,300,"press \"esc\" to go to main menu");
	  sec++;
	  sleep(1);
	  clrscr();
	  if(sec==60)
	  {
	    sec=0;
	    min++;
	  }
	  if(min==60)
	  {
	    min=0;
	    hour++;
	  }
	  if(hour==13)
	    hour=1;
	  cleardevice();
	}
	closegraph();
	goto g;
      }

      //it means fourth line and third option of stopwatch is selected.
      else if(i==4)
      {
	start();
	closegraph();
	goto g;
      }

      //it means fifth line and fourth option of about information is selected.
      else if(i==5)
      {
	about();
	goto g;
      }

      //it means if last option of exit is selected.
      else
      {
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"..\\bgi");
	centre("THANK YOU");
	getch();
	closegraph();
	exit(1);
      }
    }

    //for moving up and down multiple times without pressing enter.
    else
    {
      display(i-1);
      gotoxy(1,i);
    }
  }
  return 0;
}