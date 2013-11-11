/*
Name:        register.h
Date:        2011-05-03
Author:      Yifan Pi
Description: The .h file for Register , RegisterList , Flag and FlagList.
*/

#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>
#include <string>
#include "general.h"
using namespace std;

class Register
{
      unsigned char h,l;
      char id;
      
      public:
             Register(char c):id(c),h(0),l(0){}
             void OperateLowDigit(char, int);
             void OperateHighDigit(char, int);
             void Operate(char, int);
             void ModifyLowDigit(int);
             void ModifyHighDigit(int);
             void Modify(int);
             int Read() {return (int(h)<<8)+int(l);}
             char ReadId() {return id;}
};

class RegisterList
{
      Register* reg;
      int size;
      private:
             int Find(char);
      public:
             RegisterList(Register* p, int s):reg(p),size(s){}
             void Operate(char, string, string);
             void Operate(char, string, int);
             void Modify(string, string);
             void Modify(string, int);
             int Read(string);
             void Show();
             void Clear();
};

extern Register regs[4];
extern RegisterList reg;

class Flag
{
      string nam;
      protected: int num;
      public:
             Flag(string s, int x=0):nam(s), num(x){}
             virtual void Upd(int)=0;
             string ReadNam() {return nam;}
             int ReadNum() {return num;}
};

class ZF : public Flag
{
      public:
             ZF():Flag("zf"){}
             void Upd(int x)
             {
                  num=(x==0);
             }
};

class SF : public Flag
{
      public:
             SF():Flag("sf"){}
             void Upd(int x)
             {
                  num=(x<0);
             }
};

class FlagList
{
      Flag** flg;
      int size;
      int Find(string);
      public:
             FlagList(Flag** p, int s):flg(p), size(s){}
             void Upd(int);
             int Read(string);
}; 

extern Flag* flgs[2];
extern FlagList flg;

#endif
