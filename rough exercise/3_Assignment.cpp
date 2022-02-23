#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>

using namespace std;

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
    delay(.2);
    p=convertPixel(p);
    putpixel((int)(p.x+0.5),(int)(p.y+0.5),col);
}


void drawLine(PT a,PT b)
{

    //special case-horizontal line
    if(a.y == b.y)
    {
        if(a.x > b.x)
        {
            swap(a,b);
        }
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
            drawPixel(PT(a.x,y),YELLOW);
        }
    }

    else
    {
        double m= (b.y-a.y)/(b.x-a.x); //both x and y coordinate of b is greater than a point
        double inverse_m= 1.0/m;

        if(fabs(m) <= 1.0) //increase x and cal y
        {
            if(a.x > b.x)
            {
                swap(a,b);
            }
            while(a.x<=b.x)
            {
                drawPixel(a,YELLOW);
                a.x = a.x + 1;
                a.y = a.y + m;
            }
        }
        else
        {
            if(a.y > b.y)
            {
                swap(a,b);
            }
            while(a.y<=b.y)
            {
                drawPixel(a,YELLOW);
                a.y = a.y + 1;
                a.x = a.x + inverse_m;
            }
        }


    }
}





void drawAxis(){

    for(int i=0; i<window_H ; i++)
    {
//        delay(5);
        putpixel(window_W/2,i,WHITE);
    }

    for(int i=0; i<window_W ; i++)
    {
//        delay(5);
        putpixel(i,window_H/2,WHITE);
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

//    polygon.push_back(PT(0,0));
//    polygon.push_back(PT(100,-40));
//    polygon.push_back(PT(150,150));
//    polygon.push_back(PT(100,200));
//    polygon.push_back(PT(0,200));
//    polygon.push_back(PT(-150,-150));

//    polygon.push_back(PT(0, 0));
//    polygon.push_back(PT(100, 0));
//    polygon.push_back(PT(100, 100));
//    polygon.push_back(PT(0, 100));

    polygon.push_back(PT(40,35));
    polygon.push_back(PT(100,70));
    polygon.push_back(PT(45,140));
    polygon.push_back(PT(50,180));
    polygon.push_back(PT(-60,100));
    polygon.push_back(PT(-30,-100));



    drawPolygon(polygon);


    boundaryFill(PT(0,0),YELLOW,RED);



    getchar();
    return 0;

}

