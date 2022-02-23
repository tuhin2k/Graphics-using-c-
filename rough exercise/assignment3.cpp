#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>

using namespace std;

struct PT
{
    int x,y;
    PT(){}
    PT(int a,int b)
    {
        x=a;
        y=b;
    }
};


const int window_W=800, window_H=600;
//typedef pair<int,int> pii;

PT convertPixel(PT p)
{
    p.x=p.x+window_W/2;

    p.y=-p.y;

    p.y=p.y+window_H/2;

    return p;
}

void drawPixel(PT p, int col)
{
    delay(2);
    p=convertPixel(p);
    putpixel(p.x,p.y,col);
}


void drawLine(PT a,PT b)
{
    if(a.x > b.x)
    {
        swap(a,b); // assuming x-coordinate of a is always greater than the x-coordinate of b
    }

    //special case-horizontal line
    if(a.y==b.y)
    {
        for(int x=a.x;x<=b.x;x++)
        {
            drawPixel(PT(x,b.y),YELLOW);
        }
    }
    //special case-horizontal line
    else if(a.x==b.x)
    {
        if(a.y>b.y)
        {
            swap(a,b);
        }
        for(int y=a.y;y<=b.y;y++)
        {
            drawPixel(PT(b.x,y),YELLOW);
        }
    }

    else
    {
        ///y=mx +c
        double m= double(b.y-a.y) / double(b.x-a.x); //both x and y coordinate of b is greater than a point
        double c= (double)b.y - m*(double)b.x;

        for(int x=a.x;x<=b.x;x++)
        {
            ///y = mx + c
            double temp = m * double(x) + c;
            int y = (int) (temp+0.5);
//            int y =round(temp);
            drawPixel(PT(x,y),YELLOW);
        }

    }
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

void drawPolygon(vector<PT> points)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {
        drawLine(points[i], points[(i+1)%n]);
    }
}

void boundaryFill(PT curpoint,int boundcolor,int fillcolor)
{
    PT temp= convertPixel(curpoint);
    int curcolor=getpixel(temp.x,temp.y);
    if(curcolor==boundcolor || curcolor==fillcolor)
    {
        return;
    }

    drawPixel(curpoint,fillcolor);

    boundaryFill(PT(curpoint.x,curpoint.y+1),boundcolor,fillcolor);
    boundaryFill(PT(curpoint.x,curpoint.y-1),boundcolor,fillcolor);
    boundaryFill(PT(curpoint.x+1,curpoint.y),boundcolor,fillcolor);
    boundaryFill(PT(curpoint.x-1,curpoint.y),boundcolor,fillcolor);

}




int main()
{
    initwindow(window_W,window_H);
    drawAxis();


    vector<PT> polygon;
    polygon.push_back(PT(0,0));
    polygon.push_back(PT(100,-40));
    polygon.push_back(PT(150,150));
    polygon.push_back(PT(100,200));
    polygon.push_back(PT(0,200));
    polygon.push_back(PT(-150,-150));

//    polygon.push_back(PT(0, 0));
//    polygon.push_back(PT(100, 0));
//    polygon.push_back(PT(100, 100));
//    polygon.push_back(PT(0, 100));



    drawPolygon(polygon);


//    boundaryFill(PT(10,5),YELLOW,RED);



    getchar();
    return 0;

}
