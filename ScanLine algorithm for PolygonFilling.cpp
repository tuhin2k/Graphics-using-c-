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
        x = a;
        y = b;
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


const int window_W=800, window_H=600;

PT convertPixel(PT p)
{
    p.x = p.x + window_W/2;

    p.y = -p.y;

    p.y = p.y + window_H/2;

    return p;
}

void drawPixel(PT p, int color)
{
    delay(.2);
    p = convertPixel(p);
    putpixel((int)(p.x+0.5), (int)(p.y+0.5), color);
}


void drawLine(PT a,PT b,int color)
{
    ///special case-horizontal line
    if(a.y == b.y)
    {
        if(a.x > b.x)
        {
            swap(a,b);
        }
        for(int x = a.x ; x<= b.x ; x++)
        {
            drawPixel(PT(x,a.y),color);
        }
    }

    ///special case-Vertical line
    else if(a.x == b.x)
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
        double m = (b.y-a.y) / (b.x-a.x); //both x and y coordinate of b is greater than a point
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

    for(int i=0 ; i<window_H ; i++)
    {
//        delay(5);
        putpixel(window_W/2,i,WHITE);
    }

    for(int i=0 ; i<window_W ; i++)
    {
//        delay(5);
        putpixel(i,window_H/2,WHITE);
    }

}

void drawPolygon(vector<PT> points,int color)
{
    int n = points.size();
    for(int i=0; i<n; i++)
    {
        drawLine(points[i], points[(i+1)%n],color);
    }
}

void scanLine(vector<PT> points, int color)
{
    ///we will cover the following subtask for scaneline algo::
    //edge list
    //sort edge list
    //loop on y
    //intersecting point calculation
    //sort intersecting points
    //line draw between alternating intersecting points


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



int main()
{
    initwindow(window_W,window_H);
    drawAxis();


    vector<PT> polygon;

    polygon.push_back(PT(0,0));
    polygon.push_back(PT(100,-40));
    polygon.push_back(PT(150,150));
    polygon.push_back(PT(100,200));
    polygon.push_back(PT(-80,275));
    polygon.push_back(PT(-175,200));
    polygon.push_back(PT(-150,-150));



    drawPolygon(polygon,YELLOW);

    scanLine(polygon, GREEN);



    getchar();
    return 0;

}



