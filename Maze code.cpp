#include"time.h"
#include <windows.h>
#include"conio.h"
#include"stdio.h"
#include"string.h"

#define MAXSIZE 800
#define ROW 20
#define COLUMN 40
int tx;
int ty;

typedef struct part{    //记录坐标
	int x;
	int y;
	int k;
}part;
typedef struct stack{   
	part *stack;
	int top;
}stack;
stack s;
typedef struct quene {
	int top;
	int base;
	part *quene;
}quene;
quene q;

void delay(void);//延时，产生动画效果
void build(int a[][COLUMN]);//建立一个迷宫
void print(int a[][COLUMN]);//将迷宫输出
void run(void);//显示路径的动画效果
void set(int x,int y);//定位光标的坐标
bool chack(int a[][COLUMN],int b[][COLUMN],int x,int y);//广度搜索，找出最短路径
void save(int a[][COLUMN],int b[][COLUMN],int x,int y);//将最短路径记录在栈中
int main()
{
	int a[ROW][COLUMN];
	build(a);
	print(a);
	run();
}

void build(int a[][COLUMN])
{
	srand((unsigned)time(NULL));
	int b[ROW][COLUMN],x,y;
	while(1)
	{
		memset(a,0,ROW*COLUMN*sizeof(int));
		for(int i=ROW*COLUMN/4;i>0;i--)
		{
			x=rand()%ROW;
			y=rand()%COLUMN;
			if(a[x][y]==0)  a[x][y]=1;
			else i++;
		}
		a[rand()%ROW][rand()%COLUMN]=8;
		tx=rand()%ROW;
		ty=rand()%COLUMN;
		a[tx][ty]=7;
		int b[ROW][COLUMN];
		memset(b,0,ROW*COLUMN*sizeof(int));
		if(chack(a,b,tx,ty)==true)	break;
	}
}

bool chack(int a[][COLUMN],int b[][COLUMN],int x,int y)
{
	q.quene=(part *)malloc(MAXSIZE*sizeof(part));
	q.top=q.base=0;
	part t,r;
	t.x=x;
	t.y=y;
	q.quene[0]=t;
	q.top++;
	int n[4][2]={1,0,-1,0,0,1,0,-1};
	while(q.base!=q.top)
	{
		int i=q.top;
		for(;q.base!=i;q.base++)
		{
			if(q.base>=MAXSIZE) q.base%=MAXSIZE;
			t=q.quene[q.base];
			for(int j=1;j<5;j++)
			{
				x=t.x+n[j-1][0];
				y=t.y+n[j-1][1];
				if(x<20&&x>=0&&y<40&&y>=0&&(a[x][y]==0||a[x][y]==8)&&b[x][y]==0)
				{
					b[x][y]=j;
					if(a[x][y]==8)
					{
						save(a,b,x,y);
						return true;
					}
					r.x=x;
					r.y=y;
					if(q.top>=MAXSIZE) q.top%=MAXSIZE;
					q.quene[q.top]=r;
					q.top++;			
				}
				else if(x<20&&x>=0&&y<40&&y>=0&&a[x][y]==1)
					b[x][y]=5;
			}
		}
	}
	return false;
}

void save(int a[][COLUMN],int b[][COLUMN],int x,int y)
{
	part t;
	s.stack=(part *)malloc(MAXSIZE*sizeof(part));
	s.top=0;
	int m,n=0;
	while(a[x][y]!=7)
	{
		t.x=x;
		t.y=y;
		if(b[x][y]==1)
		{
			x-=1;
			m=2;
		}
		else if(b[x][y]==2)
		{
			x+=1;
			m=8;
		}
		else if(b[x][y]==3)
		{
			y-=1;
			m=6;
		}
		else if(b[x][y]==4)
		{
			y+=1;
			m=4;
		}
		t.k=n;
		n=m;
		s.stack[s.top]=t;
		s.top++;
	}
}

void print(int a[][COLUMN])
{
	for(int i=0;i<ROW;i++)
	{
		for(int j=0;j<COLUMN;j++)
		{
			if(a[i][j]==7)	printf("¡î");
			else if(a[i][j]==8) printf("¡ï");
			else if(a[i][j]==0)  printf("¡õ");
			else printf("¨€");
		}
		printf("¨€\n");
	}
	for(int i=0;i<41;i++)
		printf("¨€");
}

void set(int x,int y)
{
	HANDLE hout;
	COORD coord;
	coord.X=x;
	coord.Y=y;
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,coord);
}

void run(void)
{
	part N;
	s.top--;
	N=s.stack[s.top];
	int m,n;
	while(s.top!=0)
	{
		if(N.k==8)
		{
			set(s.stack[s.top].y*2,s.stack[s.top].x);
			putchar(24);
		}
		else if(N.k==2)
		{
			set(s.stack[s.top].y*2,s.stack[s.top].x);
			putchar(25);
		}
		else if(N.k==4)
		{
			set(s.stack[s.top].y*2,s.stack[s.top].x);
			putchar(27);
		}
		else if(N.k==6)
		{
			set(s.stack[s.top].y*2,s.stack[s.top].x);
			putchar(26);
		}
		s.top--;
		N=s.stack[s.top];
		delay();
	}
	set(2*COLUMN,ROW);
}

void delay(void)
{
	int i,j;
	for(i=0;i<10000;i++)
		for(j=0;j<10000;j++);
}











