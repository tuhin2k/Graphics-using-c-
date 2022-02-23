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

    bool operator < (const PT &p)const
    {
        return x < p.x;
    }

};


struct EDGE
{
    double y_min, y_max, x_with_y_min, m_inverse;
    EDGE(){}
    EDGE(double a,double b, double c, double d)
    {
        y_min = a;
        y_max = b;
        x_with_y_min = c;
        m_inverse = d;
    }

    bool operator < (const EDGE &p)const
    {
        return y_min < p.y_min;
    }
};


const int window_W=1200, window_H=1000;
int rectPosx=100;

vector<PT> polygon2;


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








void scanLine(vector<PT> points, int color)
{


    ///edge list

    vector<EDGE> edges;
    int n = points.size();
    double startpoint = 1e15 , endpoint = -1e15;

    unordered_map<double,int> mp;

    for(int i=0; i<n ; i++)
    {
        PT a = points[i];
        PT b = points[(i+1)%n];

        if(a.y == b.y)
        {
            continue;
        }

        EDGE temp;
        temp.y_min = min(a.y, b.y);
        temp.y_max = max(a.y, b.y);

        if(a.y< b.y)
        {
            temp.x_with_y_min = a.x;
        }
        else
        {
            temp.x_with_y_min = b.x;
        }

        temp.m_inverse=(b.x-a.x)/(b.y-a.y);

        startpoint = min(startpoint,temp.y_min);
        endpoint = max(endpoint,temp.y_max);

        mp[temp.y_min]=1;

        edges.push_back(temp);

    }

    n=edges.size();


    ///sort edge list
    sort(edges.begin(),edges.end());


    for(int i=0;i<n;i++)
    {
        if(mp[edges[i].y_max])
        {
            edges[i].y_max--;
        }

    }

    ///loop on y

    for(double y=startpoint;y<=endpoint;y++)
    {
        ///intersecting point calculation
        vector<PT> intersecting_points;
        for(int i=0; i<n ; i++)
        {
            if(y >= edges[i].y_min && y <= edges[i].y_max) //finding intersecting points after checking active edge
            {
                PT tmp;
                tmp.x=edges[i].x_with_y_min;
                tmp.y=y;

                edges[i].x_with_y_min += edges[i].m_inverse;

                intersecting_points.push_back(tmp);
            }
        }

        ///sort intersecting points
        sort(intersecting_points.begin(),intersecting_points.end()); // sorting intersecting points on the basis of x


        ///line draw between alternating intersecting points
        for(int i=0; i<intersecting_points.size()-1 ; i+=2)
        {
            drawLine(intersecting_points[i], intersecting_points[i+1], color);
        }
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


int XX1,YY1;


bool tmpp=false;


void click_handler(int x, int y)
{
//    printf("%d %d\n",x,y);
    XX1 = x;
    YY1 = y;
    tmpp = false;


//    int x1=rectPosx;
//    x1 = x1 + window_W/2; // amader coordinate k default e nilam


//    printf("rectposx =%d and mouseclick x= %d\n",x1,x);
//
//    int y1 = -300 + window_H/2;
//
//
//    if((x >= x1 && x <= x1 + 300) && (y >= y1 && y <= window_H /2 ))
//    {
////        printf("%d %d\n",x,y);
////        double a = double(x);
////        double b = double(y);
////        PT tmp=convertPixel1(PT(a,b)); // amader coordinate e nilam abar
//////        printf("%lf %lf\n",temp.x,temp.y);
////
////        cout << a << "   " << b <<endl;
////        cout << tmp.x << "   " << tmp.y <<endl;
////        boundaryFill(tmp,YELLOW,CYAN);
////        scanLine(polygon2, GREEN);
//        printf("draw hoise?");
//
//
//    }
//    else
//    {
//        printf("Click on the area of the polygon\n");
//    }
}







int main()
{
    initwindow(window_W,window_H);
//    drawAxis();




    int speed=10;
    int page = 0;


    while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();



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
        delay(2);




        registermousehandler(WM_LBUTTONDOWN, click_handler);

        int xx1=rectPosx + (window_W/2) ;
        int yy1 = -300 + (window_H/2);



        if((XX1 >= xx1 && XX1 <= xx1 + 300) && (YY1 >= yy1 && YY1 <= window_H /2 ))
        {
            scanLine(polygon2, GREEN);
            printf("XX1 = %d , YY1 = %d , xx1 = %d , yy1 = %d\n",XX1,YY1,xx1,yy1);
        }


//        else
//        {
//            printf("Click on the area of the polygon\n");
//        }

        polygon2.clear();
//        tmpp = false;
//        XX1=-1;
//        YY1=-1;

    }


//    boundaryFill(PT(-100,50),YELLOW,GREEN);





    getchar();
    return 0;

}





