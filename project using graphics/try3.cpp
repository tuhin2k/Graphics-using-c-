#include<bits/stdc++.h>
#include<graphics.h>
#include<windows.h>

using namespace std;

/*
RegNo: 2017331101
Name: Asif Idris Tuhin
*/


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


const int window_W=1200, window_H=1000;
int rectPosx=100;


PT convertPixel(PT p)
{
    p.x = p.x + window_W/2;

    p.y = -p.y;

    p.y = p.y + window_H/2;

    return p;
}
PT convertPixel1(PT p)
{
    p.x = p.x - window_W/2;

//    p.y = -p.y;

    p.y = p.y - window_H/2;
    p.y = -p.y;

    return p;
}

void drawPixel(PT p, int col)
{
    delay(.2);
    p = convertPixel(p);
    putpixel((int)(p.x+0.5),(int)(p.y+0.5),col);
}


void drawLine(PT a,PT b, int color)
{
    ///special case-horizontal line
    if(a.y == b.y)
    {
        if(a.x > b.x)
        {
            swap(a,b);
        }
        for(int x=a.x; x<=b.x; x++)
        {
            drawPixel(PT(x,a.y),color);
        }
    }

    ///special case-Vertical line
    else if(a.x==b.x)
    {
        if(a.y > b.y)
        {
            swap(a,b);
        }
        for(int y=a.y; y<=b.y; y++)
        {
            drawPixel(PT(a.x,y),color);
        }
    }

    else
    {
        double m=(b.y-a.y) / (b.x-a.x); //both x and y coordinate of b is greater than a point
        double m_inverse = 1.0/m;
        if(fabs(m) <= 1.0) //increase x and cal y
        {
            if(a.x > b.x)
            {
                swap(a,b);
            }
            while(a.x <= b.x)
            {
                drawPixel(a,color);
                a.x = a.x + 1;
                a.y = a.y + m;
            }
        }
        else //increase y and cal x
        {
            if(a.y > b.y)
            {
                swap(a,b);
            }
                while(a.y <= b.y)
                {
                    drawPixel(a, color);
                    a.x = a.x + m_inverse;
                    a.y = a.y + 1;
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
//    printf("hello world");
//    cout << curpoint.x << curpoint.y << boundcolor << fillcolor <<endl;

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

void drawPolygon_with_Unique_boundaryColor(vector<PT> points)
{
    int n = points.size();
    int col=YELLOW;
    for(int i=0; i<n; i++)
    {
        drawLine(points[i], points[(i+1)%n],col);
    }
}

void click_handler(int x, int y)
{
    printf("%d %d\n",x,y);

    int x1=rectPosx;
    x1 = x1 + window_W/2; // amader coordinate k default e nilam


    printf("rectposx =%d and mouseclick x= %d\n",x1,x);

    int y1 = -300 + window_H/2;


    if((x >= x1 && x <= x1 + 300) && (y >= y1 && y <= window_H /2 ))
    {
//        printf("%d %d\n",x,y);
        double a = double(x);
        double b = double(y);
        PT tmp=convertPixel1(PT(a,b)); // amader coordinate e nilam abar
//        printf("%lf %lf\n",temp.x,temp.y);

        cout << a << "   " << b <<endl;
        cout << tmp.x << "   " << tmp.y <<endl;
        boundaryFill(tmp,YELLOW,CYAN);

    }
    else
    {
        printf("Click on the area of the polygon\n");
    }
}






int main()
{
    initwindow(window_W,window_H);
    drawAxis();




    int speed=10;
    int page = 0;


    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();


        vector<PT> polygon2;

        polygon2.push_back(PT(rectPosx,300));
        polygon2.push_back(PT(rectPosx,0));
        polygon2.push_back(PT(rectPosx+300, 0));
        polygon2.push_back(PT(rectPosx+300, 300));

        drawPolygon_with_Unique_boundaryColor(polygon2);

        //    polygon2.push_back(PT(-100, 150));
        //    polygon2.push_back(PT(-170, 100));


        if(GetAsyncKeyState(VK_LEFT))
        {
            rectPosx -= speed;
        //            cirlposX -= speed;
        //            cir2posX -= speed;
        }
        else if(GetAsyncKeyState(VK_RIGHT))
        {
            rectPosx += speed;
        //            cirlposX += speed;
        //            cir2posX += speed;
        }


        page = 1 - page;
        delay(5);




        registermousehandler(WM_LBUTTONDOWN, click_handler);

    }


//    boundaryFill(PT(-100,50),YELLOW,GREEN);





    getchar();
    return 0;

}



