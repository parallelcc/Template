//求两圆相交的面积
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define esp 1e-8

using namespace std;

struct Circle{
    double x,y;
    double r;
};

double calArea(Circle c1, Circle c2)
{
    double d;
    double s,s1,s2,s3,angle1,angle2,temp;

    d=sqrt((c1.x-c2.x)*(c1.x-c2.x)+(c1.y-c2.y)*(c1.y-c2.y));
    if(d>=(c1.r+c2.r))//两圆相离
        return 0;
    if((c1.r-c2.r)>=d)//两圆内含,c1大
        return acos(-1.0)*c2.r*c2.r;
    if((c2.r-c1.r)>=d)//两圆内含,c2大
        return acos(-1.0)*c1.r*c1.r;

    angle1=acos((c1.r*c1.r+d*d-c2.r*c2.r)/(2*c1.r*d));
    angle2=acos((c2.r*c2.r+d*d-c1.r*c1.r)/(2*c2.r*d));

    s1=angle1*c1.r*c1.r;s2=angle2*c2.r*c2.r;
    s3=c1.r*d*sin(angle1);
    s=s1+s2-s3;

    return s;
}
