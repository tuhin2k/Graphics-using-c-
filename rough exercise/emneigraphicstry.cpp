#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>

using namespace std;


const int window_W=800, window_H=600;
typedef pair<int,int> pii;

pii convertPixel(int x, int y)
{
    x=x+window_W/2;

    y=-y;

    y=y+window_H/2;

    return make_pair(x,y);
}

void drawPixel(int x,int y, int col)
{
    pii p=convertPixel(x,y);
    putpixel(p.first,p.second,col);
}



void drawAxis(){

    for(int i=0; i<window_H ; i++)
    {
//        delay(5);
        putpixel(window_W/2,i,YELLOW);
    }

    for(int i=0; i<window_W ; i++)
    {
//        delay(5);
        putpixel(i,window_H/2,YELLOW);
    }

}

int main()
{
    initwindow(window_W,window_H);
    drawAxis();

//    int x=100;
//    int y=200;
//    convertPixel(x,y)

//    putpixel(x,y,YELLOW);

//    convertPixel(x,y);
//
//    putpixel(x,y,YELLOW);


//    for(int i=0;i<200;i++)
//    {
////        int x=i, y=-i;
//        pii p=convertPixel(i,i);
//        putpixel(p.first,p.second,YELLOW);
//    }

    for(int i=0;i<150;i++)
    {
        drawPixel(i,i,YELLOW);
    }





    getchar();

}
