#include <curses.h>
#include <math.h>

#include "bresenham.h"

#define PI	3.141592654
#define X0	-10*PI
#define X1	10*PI
#define MAX_X	79
#define MAX_Y	15

double f(double arg)
{
	return arg*sin(arg);
}

char flag;
double mx=(X1-X0)/(double)MAX_X,my,Y0;

double fi(int i)
{
	return flag*f(X0+mx*i);
}

double find_extr()
{
	double result=fi(0);
	int i;
	for(i=1;i<=MAX_X;i++)
	{
		double val=fi(i);
		if(val>result)result=val;
	}
	return result;
}

void initvars()
{
	flag=-1;
	Y0=-find_extr();

	flag=1;
	my=MAX_Y/(find_extr()-Y0);
}

int px,py;

void setpoint(int i)
{
	px=i;
	py=MAX_Y-(float)floor(my*(fi(i)-Y0));
}

main()
{
	int i;

	initvars();

	initscr();
	cbreak();

	setpoint(0);
	for(i=1;i<=MAX_X;i++)
	{
		int buf_x=px,buf_y=py;
		setpoint(i);
		line(buf_x,buf_y,px,py);
	}

	getch();
	endwin();
}
