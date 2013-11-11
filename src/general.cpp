/*
Name:        general.cpp
Date:        2011-05-02
Author:      Yifan Pi
Description: The .cpp file for General operations.
*/

#include "general.h"
#include <string>
#include <iostream>
using namespace std;

int atoh(string str)
{
    int len=str.length();
    int sum=0;
    for (int i=0;i<len;i++) {
        sum<<=4;
        if (isdigit(str[i])) sum+=str[i]-'0';
        else
        if (str[i]>='A'&&str[i]<='F') sum+=str[i]-'A'+10;
        else
            sum+=str[i]-'a'+10;
    }
    return sum;
}

string htoa(int num)
{
    if (num==0) return "0";
    string str="";
    for (;num;num>>=4)
    {
        int x=num&15;
        if (x>=10) str=char('A'+char(x-10))+str;
        else str=char('0'+x)+str;
    }
    return str;
}

bool IsHex(string s)
{
     if (s.length()<1) return 0;
     for (int i=0;i<s.length();i++)
     {
         if (s[i]>='0'&&s[i]<='9') continue;
         if (s[i]>='a'&&s[i]<='f') continue;
         if (s[i]>='A'&&s[i]<='F') continue;
         return 0;
     }
     return 1;
}
