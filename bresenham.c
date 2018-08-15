#include <curses.h>

void putpixel(int x,int y)
{
	move(y,x);
	printw("8");
}

int iabs(int arg)
{
	return arg>0?arg:-arg;
}

void swapvar(int *a,int *b)
{
	int c=*a;
	*a=*b;
	*b=c;
}

void vertline(int x0,int y0,int y1)
{
	int i;
	if(y1<y0)swapvar(&y0,&y1);
	for(i=y0;i<=y1;i++)putpixel(x0,i);
}

void horline(int x0,int x1,int y0)
{
	int i;
	if(x1<x0)swapvar(&x0,&x1);
	for(i=x0;i<=x1;i++)putpixel(i,y0);
}

int dx,dy,two_dx,two_dy;

void bresenham_bigy(int x0,int y0,int x1,int y1)
{
	int eps,error=-dy;
	if(x1<x0)
	{
		swapvar(&x0,&x1);
		swapvar(&y0,&y1);
	}
	if(y0<y1)eps=1;
	else eps=-1;
	while(iabs(y1-y0)>=2)
	{
		putpixel(x0,y0);
		putpixel(x1,y1);
		error+=two_dx;
		if(error>=0)
		{
			error-=two_dy;
			x0++;
			x1--;
		}
		y0+=eps;
		y1-=eps;
	}
	putpixel(x0,y0);
	if(y0!=y1)putpixel(x1,y1);
}

void bresenham_bigx(int x0,int y0,int x1,int y1)
{
	int eps,error=-dx;
	if(y1<y0)
	{
		swapvar(&x0,&x1);
		swapvar(&y0,&y1);
	}
	if(x0<x1)eps=1;
	else eps=-1;
	while(iabs(x1-x0)>=2)
	{
		putpixel(x0,y0);
		putpixel(x1,y1);
		error+=two_dy;
		if(error>=0)
		{
			error-=two_dx;
			y0++;
			y1--;
		}
		x0+=eps;
		x1-=eps;
	}
	putpixel(x0,y0);
	if(x0!=x1)putpixel(x1,y1);
}

void line(int x0,int y0,int x1,int y1)
{
	if(x0==x1)vertline(x0,y0,y1);
	else if(y0==y1)horline(x0,x1,y0);
	else
	{
		dx=iabs(x1-x0);
		dy=iabs(y1-y0);
		two_dx=2*dx;
		two_dy=2*dy;
		if(dx<=dy)bresenham_bigy(x0,y0,x1,y1);
		else bresenham_bigx(x0,y0,x1,y1);
	}
}
