#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
using namespace std;

/*
RegNo: 2017331101
Name: Asif Idris Tuhin
*/





struct point
{
    int x;
    int y;
};

int window_W=800,window_H=600;



void drawAxis()
{
        for(int i=0;i<=window_W;i++)
        {
            putpixel(i,window_H/2,WHITE);
        }

        for(int i=0;i<=window_H;i++)
        {
            putpixel(window_W/2,i,WHITE);
        }
}

void drawPixel(point p, int color)
{
    int x=window_W/2,y=window_H/2;
    x = x + p.x;
    y = y - p.y;
    putpixel(x,y,color);
}

void circle_pixel_drawer(point center, point our_point,int color)
{   /// 8 pixel drawn by 1 pixel
    point new_point;


    /// above x axis
    new_point.x = our_point.x + center.x;
    new_point.y = our_point.y + center.y;
    drawPixel(new_point,color);

    new_point.x = our_point.y + center.x;
    new_point.y = our_point.x + center.y;
    drawPixel(new_point,color);

    new_point.x=-our_point.x + center.x;
    new_point.y=our_point.y + center.y;
    drawPixel(new_point,color);

    new_point.x=-our_point.y+center.x;
    new_point.y=our_point.x+center.y;
    drawPixel(new_point,color);

    ///below x axis
    new_point.x=our_point.x+center.x;
    new_point.y=-our_point.y+center.y;
    drawPixel(new_point,color);
    new_point.x=our_point.y+center.x;
    new_point.y=-our_point.x+center.y;
    drawPixel(new_point,color);
    new_point.x=-our_point.x+center.x;
    new_point.y=-our_point.y+center.y;
    drawPixel(new_point,color);
    new_point.x=-our_point.y+center.x;
    new_point.y=-our_point.x+center.y;
    drawPixel(new_point,color);
}

void BressenhamsCircle(point center, int radius, int color)
{
    drawPixel(center,LIGHTCYAN);
    int DP=3-(radius<<1);
    int start=0;
    int end=round((double)radius/sqrt(2));
    point current_point;
    current_point.x=0;
    current_point.y=radius;
    for(int i=start;i<=end;i++)
    {
        if(DP>=0)
        {
            DP+=((current_point.x<<2)-(current_point.y<<2)+10);
            current_point.y--;
        }
        else
        {
            DP+=((current_point.x<<2)+6);
        }
        circle_pixel_drawer(center,current_point,color);
        current_point.x++;
    }
}

void MidPointCircle(point center, int radius, int color)
{
    drawPixel(center,LIGHTCYAN);
    double DP=(double)5/(double)4-(double)radius;
    int start=0;
    int end=round((double)radius/sqrt(2));
    point current_point;
    current_point.x=0;
    current_point.y=radius;
    for(int i=start;i<=end;i++)
    {
        if(DP>=0)
        {
            DP+=((current_point.x<<1)-(current_point.y<<1)+5);
            current_point.y--;
        }
        else
        {
            DP+=((current_point.x<<1)+3);
        }
        circle_pixel_drawer(center, current_point, color);
        current_point.x++;
    }
}


int main()
{

    initwindow(window_W,window_H);
    drawAxis();

    point center1;
    center1.x=50;
    center1.y=60;
    BressenhamsCircle(center1,120,LIGHTGREEN);//center , radius , color



    point center2;
    center2.x=-150;
    center2.y=-125;
    MidPointCircle(center2,80,LIGHTRED);//center , radius , color



    getchar();
    return 0;
}
