#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
using namespace std;

struct point{
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


void DDALine(point a, point b, int color){
    point current_point;

    double m;
    m=(double)(b.y-a.y)/(double)(b.x-a.x);
    double m_inverse= 1.0/m;

    if(fabs(m)<=1){
        if(a.x>b.x){
            swap(a,b);
        }
        current_point=a;
        double new_y=current_point.y;
        for(int i=a.x;i<=b.x;i++){
            drawPixel(current_point,color);
            new_y+=m;
            current_point.x++;
            current_point.y=round(new_y);
        }
    }
    else{

        if(a.y>b.y)
        {
            swap(a,b);
        }

        current_point=a;
        double new_x=current_point.x;

        for(int i=a.y;i<=b.y;i++)
        {
            drawPixel(current_point,color);

            new_x = new_x + m_inverse;

            current_point.y++;

            current_point.x=round(new_x);
        }
    }
}

void BressenhamsLine(point a, point b, int color)
{    /// 0<m<=1
    if(a.x>b.x)
    {
        swap(a,b);
    }

    point current_point=a;

    int rem_x = abs(a.x-b.x);
    int rem_y = abs(a.y-b.y);
    int RMV = (rem_y<<1) - rem_x;

    for(int i=a.x;i<=b.x;i++)
    {
        if(RMV>0)
        {
            current_point.y++;
            RMV+=((rem_y-rem_x)<<1);
        }
        else
        {
            RMV+=(rem_y<<1);
        }
        drawPixel(current_point,color);
        current_point.x++;
    }
}

int main(){

    initwindow(window_W,window_H);

    drawAxis();

    point a,b,c,d,e;
    a.x=70;
    a.y=20;

    b.x=310;
    b.y=80;

    c.x=130;
    c.y=210;

    d.x=40;
    d.y=-20;

    e.x=350;
    e.y=50;

    DDALine(a,b,LIGHTCYAN);
    DDALine(a,c,LIGHTCYAN);

    BressenhamsLine(d,e,LIGHTGREEN);

    getchar();
    return 0;
}
