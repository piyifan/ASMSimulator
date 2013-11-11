/*
Name:        asm.cpp
Date:        2011-05-03
Author:      Yifan Pi
Description: The .cpp file for Asm.
*/

#include "general.h"
#include "register.h"
#include "label.h"
#include "command.h"
#include "asm.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int find_space(string& s)
{
    for (int i=0;i<s.length();i++)
        if (s[i]==' ') return i;
    return s.length();
}

bool Asm::ReadSrc(char* InFile)
{
     ifstream f(InFile);
     if (!f)
     {
          cout<<"Can not find '"<<InFile<<"'.\n";
          return 0;
     }
     
     lbl.Clear();
     
     string s;
     int Line=0;
     bool HaveEnd=0;
     
     while (getline(f,s))
     {
           Line++;
           while (s.length()&&s[0]==' ') s.erase(0,1);
           while (s.length()&&s[s.length()-1]==' ') s.erase(s.length()-1,1);
          
           if (s[0]==';'||s=="") continue;
           
           if (s[s.length()-1]==':')
           {
               s.erase(s.length()-1,1);
               if (!lbl.Insert(s,st.size()))
               {
                   f.close();
                   cout<<"CE: Line "<<Line<<": The same label "<<s<<" occured.\n";
                   return 0;
               }
               continue;
           }
           string s1="",s2="",s3="";
           
           int p=find_space(s);
           s1=s.substr(0,p);
           s.erase(0,p+1);
           if (s.length())
           {
               p=find_space(s);
               s2=s.substr(0,p);
               s.erase(0,p+1);
               if (s.length()) 
               {
                   p=find_space(s);      
                   s3=s.substr(0,p);
                   s.erase(0,p+1);
               }
           }
           if (s.length())
           {
                f.close();
                cout<<"CE: Line "<<Line<<": Too many arguments(>2).\n";
                return 0;
           }
           st.push_back(Statement(s1,s2,s3,Line));
           if (s1=="int"&&s2=="20") HaveEnd=1;
     }
     f.close();
     if (!HaveEnd)
     {
         cout<<"CE: The program has no 'int 20' command.\n";
         return 0;
     }
     for (int i=0;i<st.size();i++)
         if (!cmd.Check(st[i].ReadOp(),st[i].ReadArg1(),st[i].ReadArg2()))
         {
              cout<<"CE: Line "<<st[i].ReadLine()<<": The statement: ' "<<
              st[i].ReadOp()<<' '<<st[i].ReadArg1()<<' '<<st[i].ReadArg2()<<
              "' is invaild.\n";
              return 0;
         }
     return 1;
}

void Asm::RunCode()
{
     reg.Clear();
     int p=0;
     while (p<st.size())
     {
           string op=st[p].ReadOp(),arg1=st[p].ReadArg1(),arg2=st[p].ReadArg2();
           if (op=="int"&&arg1=="20") return;
           int r=cmd.Run(op,arg1,arg2);
           if (r) p=r;
           else p++;
     }
}
