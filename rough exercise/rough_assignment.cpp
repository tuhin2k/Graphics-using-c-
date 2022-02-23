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

PT convertPixel(PT p)
{
    p.x += window_W/2;

    p.y=-p.y;

    p.y += window_H/2;

    return p;
}

void drawPixel(PT p, int col)
{
    delay(.2);
    p = convertPixel(p);
    putpixel((int)(p.x+0.5), (int)(p.y+0.5), col);
}


void drawLine(PT a,PT b, int color)
{
    if(a.y == b.y)
    {
        if(a.x > b.x)
        {
            swap(a, b);
        }
        for(int x = a.x; x<= b.x; x++)
        {
            drawPixel(PT(x, a.y),color);
        }
    }

    else if(a.x==b.x)
    {
        if(a.y > b.y)
        {
            swap(a,b);
        }
        for(int y = a.y; y <= b.y; y++)
        {
            drawPixel(PT(a.x, y),color);
        }
    }

    else
    {
        double m=(b.y-a.y) / (b.x-a.x); //both x and y coordinate of b is greater than a point
        double m_inv = 1.0/m;
        if(fabs(m) <= 1.0)
        {
            if(a.x > b.x)
            {
                swap(a, b);
            }
            while(a.x <= b.x)
            {
                drawPixel(a,color);
                a.x += 1;
                a.y += m;
            }
        }
        else
        {
            if(a.y > b.y)
            {
                swap(a, b);
            }
                while(a.y <= b.y)
                {
                    drawPixel(a, color);
                    a.x += m_inv;
                    a.y += 1;
                }

        }
    }
}





void drawAxis()
{

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



void boundaryFill(PT curpoint,int boundcolor,int fillcolor)
{
    PT temp=convertPixel(curpoint);
    int curcolor=getpixel(temp.x,temp.y);
    if(curcolor==boundcolor || curcolor==fillcolor)
    {
        return;
    }

    drawPixel(curpoint,fillcolor);

    boundaryFill(PT(curpoint.x, curpoint.y+1), boundcolor, fillcolor);
    boundaryFill(PT(curpoint.x, curpoint.y-1), boundcolor, fillcolor);
    boundaryFill(PT(curpoint.x+1, curpoint.y), boundcolor, fillcolor);
    boundaryFill(PT(curpoint.x-1, curpoint.y), boundcolor, fillcolor);

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

void drawPolygon_with_diff_boundaryColor(vector<PT> points)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {
        int col;
        if(i%3 ==0)
        {
            col = YELLOW;
        }
        else if(i%3 == 1)
        {
            col = GREEN;
        }
        else
        {
            col = BLUE;
        }

        drawLine(points[i], points[(i+1)%n],col);
    }
}

void drawPolygon_with_Unique_boundaryColor(vector<PT> points)
{
    int n = points.size();
    int col=YELLOW;
    for(int i=0; i<n; i++)
    {
        drawLine(points[i], points[(i+1)%n],col);
    }
}






int main()
{
    initwindow(window_W,window_H);
    drawAxis();


    vector<PT> polygon;

    polygon.push_back(PT(100,70));
    polygon.push_back(PT(45,140));
    polygon.push_back(PT(50,180));
    polygon.push_back(PT(150,200));
    polygon.push_back(PT(250,110));

    drawPolygon_with_diff_boundaryColor(polygon);

    PT temp=convertPixel(PT(100,100));
    int curcolor=getpixel(temp.x,temp.y);

    floodFill(PT(100,100),RED,curcolor);




    vector<PT> poly;

    poly.push_back(PT(-170,0));
    poly.push_back(PT(-70, 0));
    poly.push_back(PT(-70, 100));
    poly.push_back(PT(-100, 150));
    poly.push_back(PT(-170, 100));

    drawPolygon_with_Unique_boundaryColor(poly);

    boundaryFill(PT(-100,50),YELLOW,GREEN);




    getchar();
    return 0;

}

