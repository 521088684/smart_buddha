#include<stdio.h>

//该为迭代版本
int My_Add(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    int ans;
    while(b)
    {
        ans = a^b;
        b = (a&b)<<1;
        a = ans;
    }
    return ans;
}

//求a的相反数：将各位取反加一
int My_Neg(int a)     //get -a
{
    return My_Add(~a, 1);
}

int My_Min(int a, int b)
{
    return My_Add(a, My_Neg(b));
}

//正数乘法
int Multi(int a, int b)
{
    int ans = 0;
    while(b)
    {
        if(b&1)
            ans = My_Add(ans, a);
        a = a << 1;
        b = b >> 1;
    }
    return ans;
}

//正数除法
int Divide(int a, int b)
{
    int coun = 0;
    while(a >= b)
    {
        a = My_Min(a, b);
        coun = My_Add(coun, 1);
    }
    return coun;
}

//判断是否是负数，0，正数
int isneg(int a)
{
    return a & 0x8000;
}
int iszero(int a)
{
    return !(a & 0xFFFF);
}
int ispos(int a)
{
    return (a&0xFFFF) && !(a&0x8000);
}

//处理负数的乘法和除法
int My_Mul(int a, int b)
{
    if(iszero(a) || iszero(b))
        return 0;
    if(isneg(a))
    {
        if(isneg(b))
            return Multi(My_Neg(a), My_Neg(b));
        else
            return My_Neg(Multi(My_Neg(a), b));
    }else if(isneg(b))
        return My_Neg(Multi(a, My_Neg(b)));
    else
        return Multi(a, b);
}

int My_Div(int a, int b)
{
    if(iszero(b))
    {
        printf("[ERROR] Divide 0");
        return 1;
    }
    if(iszero(a))
        return 0;
    if(isneg(a))
    {
        if(isneg(b))
            return Divide(My_Neg(a), My_Neg(b));
        else
            return My_Neg(Divide(My_Neg(a), b));
    }else if(isneg(b))
        return My_Neg(Divide(a, My_Neg(b)));
    else
        return Divide(a, b);

}

double My_Sqrt(double a) {
    double x,y;
    x=0.0;
    y=a/2;
    while(x!=y)
    {
        x=y;
        y=(x+a/x)/2;
    }
    return x;
}
