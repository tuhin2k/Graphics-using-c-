#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>

using namespace std;

const int window_W=1200, window_H=1000;
struct PT
{
    double x,y;
    PT(){}
    PT(double a,double b)
    {
        x=a;
        y=b;
    }
};

PT convertPixel(PT p)
{
    p.x = p.x + window_W/2;

    p.y = -p.y;

    p.y = p.y + window_H/2;

    return p;
}

void drawPixel(PT p, int col)
{
    delay(.2);
    p = convertPixel(p);
    putpixel((int)(p.x+0.5),(int)(p.y+0.5),col);
}


void floodFill(PT curpoint,int fillcolor,int oldcolor)
{
    PT temp=convertPixel(curpoint);
    int curcolor=getpixel(temp.x,temp.y);
    if(curcolor!=oldcolor)
    {
        return;
    }

    drawPixel(curpoint,fillcolor);

    floodFill(PT(curpoint.x, curpoint.y+1), fillcolor,oldcolor);
    floodFill(PT(curpoint.x, curpoint.y-1), fillcolor,oldcolor);
    floodFill(PT(curpoint.x+1, curpoint.y), fillcolor,oldcolor);
    floodFill(PT(curpoint.x-1, curpoint.y), fillcolor,oldcolor);

}

int main()
{
//    DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
//    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
//    initwindow(screenWidth, screenHeight, "",-3,-3);

    initwindow(window_W,window_H);

    int rectPosX = 100, cirlposX = 200 , cir2posX = 500 , speed = 10;
    int page=0;
    while(1)
    {
//        setactivepage(page);
//        setvisualpage(1-page);


        setcolor(RED);
        for(int i=0; i <=19 ; i++) rectangle(rectPosX-i,300-i,rectPosX+500+i,511+i);

        setcolor(BLUE);
        for(int i=50; i <= 69; i++)
        {
            circle(cirlposX,600,i);
            circle(cir2posX,600,i);
        }
        setcolor(GREEN);

        for(int i=670;i<=680;i++)
        {
            line(0,i,window_W,i);
        }

        if(GetAsyncKeyState(VK_LEFT))
        {
            rectPosX -= speed;
            cirlposX -= speed;
            cir2posX -= speed;
        }
        else if(GetAsyncKeyState(VK_RIGHT))
        {
            rectPosX += speed;
            cirlposX += speed;
            cir2posX += speed;
        }

//        page = 1 - page;
        delay(5);
        cleardevice();
}


}
