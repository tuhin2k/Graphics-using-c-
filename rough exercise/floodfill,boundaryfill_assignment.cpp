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

const int WINDOW_W=800, WINDOW_H=600;
PT convertPixel(PT p)
{
    p.x += WINDOW_W/2;
    p.y=-p.y;
    p.y += WINDOW_H/2;

    return p;
}

void drawPixel(PT p, int color)
{
    delay(.6);
    p = convertPixel(p);
    putpixel((int)(p.x+0.5), (int)(p.y+0.5), color);
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
        double m=(b.y-a.y) / (b.x-a.x);
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

    for(int i=0; i<WINDOW_H ; i++)
    {
        putpixel(WINDOW_W/2,i,WHITE);
    }

    for(int i=0; i<WINDOW_W ; i++)
    {
        putpixel(i,WINDOW_H/2,WHITE);
    }

}

void drawPolygon_for_floodfill(vector<PT> points)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {
        int color;
        if(i%3 ==0) color = YELLOW;
        else if(i%3 == 1) color = GREEN;
        else color = RED;

        drawLine(points[i], points[(i+1)%n],color);
    }
}

void drawPolygon_for_boundaryfill(vector<PT> points)
{
    int n = points.size();
    int color= GREEN;
    for(int i=0; i<n; i++)
    {
        drawLine(points[i], points[(i+1)%n],color);
    }
}


void boundaryFill(PT CurPixel,int boundcolor,int fillcolor)
{
    PT temp=convertPixel(CurPixel);
    int pixel=getpixel(temp.x,temp.y);
    if(pixel==boundcolor || pixel==fillcolor)
    {
        return;
    }

    drawPixel(CurPixel,fillcolor);

    boundaryFill(PT(CurPixel.x, CurPixel.y+1), boundcolor, fillcolor);
    boundaryFill(PT(CurPixel.x, CurPixel.y-1), boundcolor, fillcolor);
    boundaryFill(PT(CurPixel.x+1, CurPixel.y), boundcolor, fillcolor);
    boundaryFill(PT(CurPixel.x-1, CurPixel.y), boundcolor, fillcolor);

}

void floodFill(PT CurPixel,int fillcolor,int oldcolor)
{
    PT temp=convertPixel(CurPixel);
    int pixel=getpixel(temp.x,temp.y);
    if(pixel!=oldcolor)
    {
        return;
    }

    drawPixel(CurPixel,fillcolor);

    floodFill(PT(CurPixel.x, CurPixel.y+1), fillcolor,oldcolor);
    floodFill(PT(CurPixel.x, CurPixel.y-1), fillcolor,oldcolor);
    floodFill(PT(CurPixel.x+1, CurPixel.y), fillcolor,oldcolor);
    floodFill(PT(CurPixel.x-1, CurPixel.y), fillcolor,oldcolor);

}




int main()
{
    initwindow(WINDOW_W,WINDOW_H);
//    drawAxis();


    vector<PT> polygon;
    polygon.push_back(PT(40,35));
    polygon.push_back(PT(100,70));
    polygon.push_back(PT(45,140));
    polygon.push_back(PT(50,180));
    polygon.push_back(PT(-60,100));
    polygon.push_back(PT(-30,-100));




    drawPolygon_for_floodfill(polygon);

    PT temp=convertPixel(PT(5,5));
    int pixel=getpixel(temp.x,temp.y);

    floodFill(PT(5, 5),BLUE,pixel);


    vector<PT> poly;
    poly.push_back(PT(110, 0));
    poly.push_back(PT(210, 0));
    poly.push_back(PT(210, 100));
    poly.push_back(PT(150, 120));
    poly.push_back(PT(110, 100));

    drawPolygon_for_boundaryfill(poly);

    boundaryFill(PT(150,50),GREEN,RED);








    getchar();
    return 0;

}


