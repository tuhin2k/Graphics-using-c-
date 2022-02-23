#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
using namespace std;

struct PT
{
    int x, y;
    PT(){}
    PT(int a, int b)
    {
        x = a;
        y = b;
    }
};

const int WINDOW_W = 800, WINDOW_H = 600;

void drawAxis()
{
    for(int i=0; i<WINDOW_H; i++) putpixel(WINDOW_W/2, i, WHITE);
    for(int i=0; i<WINDOW_W; i++) putpixel(i, WINDOW_H/2, WHITE);
}

PT convertPixel(PT p)
{
    p.x += WINDOW_W/2;
    p.y = -p.y;
    p.y += WINDOW_H/2;

    return p;
}

void drawPixel(PT p, int color)
{
    delay(0.1);
    p = convertPixel(p);
    putpixel(p.x, p.y, color);
}

void drawLine(PT a, PT b)
{
    if(a.x > b.x) swap(a, b);

    ///horizontal

    if(a.y == b.y)
    {
        for(int x = a.x; x <= b.x; x++)
        {
            drawPixel(PT(x, a.y), YELLOW);
        }
    }

    ///vertical

    else if(a.x == b.x)
    {
        if(a.y > b.y) swap(a, b);
        for(int y = a.y; y <= b.y; y++)
        {
            drawPixel(PT(a.x, y), YELLOW);
        }
    }

    else
    {
        double m = (double)(b.y-a.y)/(double)(b.x-a.x);
        double c = (double)a.y - m*(double)a.x;
        for(int x = a.x; x <= b.x; x++)
        {
            int y = round(m*(double)x + c);

            drawPixel(PT(x, y), YELLOW);
        }
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
void BoundaryFill(PT currPixel, int boundaryColor, int fillColor)
{
    PT pixel = convertPixel(currPixel);
    int currColor = getpixel(pixel.x, pixel.y);
    if(currColor == boundaryColor || currColor == fillColor)
    {
        return;
    }

    drawPixel(currPixel, fillColor);

    BoundaryFill(PT(currPixel.x, currPixel.y+1), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x, currPixel.y-1), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x+1, currPixel.y), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x-1, currPixel.y), boundaryColor, fillColor);
}

int main()
{
    initwindow(WINDOW_W, WINDOW_H);
    drawAxis();

    vector<PT> polygon;
    polygon.push_back(PT(0,0));
    polygon.push_back(PT(100,0));
    polygon.push_back(PT(150,150));
    polygon.push_back(PT(100,200));
    polygon.push_back(PT(0,200));
    polygon.push_back(PT(-150,-150));

    drawPolygon(polygon);

    drawPolygon(polygon);




    getchar();

    return 0;
}

