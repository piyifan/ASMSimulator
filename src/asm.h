/*
Name:        asm.h
Date:        2011-05-03
Author:      Yifan Pi
Description: The .h file for Asm.
*/

/*#include "general.h"
#include "register.h"
#include "label.h"
#include "command.h"*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef ASM_H
#define ASM_H

class Statement
{
      string op,arg1,arg2;
      int Line;
      public:
             Statement(string s1, string s2, string s3, int l):op(s1),arg1(s2),arg2(s3),Line(l){}
             string ReadOp() {return op;}
             string ReadArg1() {return arg1;}
             string ReadArg2() {return arg2;}
             int ReadLine() {return Line;}
};

class Asm
{
      vector<Statement> st;
      public:
             Asm(){st.clear();}
             bool ReadSrc(char*);
             void RunCode();
};

#endif
