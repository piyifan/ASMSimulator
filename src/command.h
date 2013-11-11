/*
Name:        command.h
Date:        2011-05-03
Author:      Yifan Pi
Description: The .h file for Command and CommandList.
*/

#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include "general.h"
#include "register.h"
#include "label.h"
using namespace std;

class Command
{
      string id;
      public:
             Command(string s):id(s){}
             string ReturnName() {return id;}
             virtual int Run(string arg1, string arg2)=0;
             virtual bool Check(string, string)=0;
};

class CommandList
{
      Command** cmd;
      int size;
      public:
             CommandList(Command** p, int s):cmd(p),size(s){}
             int Run(string, string, string);
             bool Check(string, string, string);
};

class MOV : public Command   
{                             
      public:                           
             MOV():Command("mov"){}     
             int Run(string, string);
             bool Check(string, string);
};

class ADD : public Command   
{                             
      public:                           
             ADD():Command("add"){}     
             int Run(string, string); 
             bool Check(string, string);
};

class SUB : public Command   
{                             
      public:                           
             SUB():Command("sub"){}     
             int Run(string, string); 
             bool Check(string, string);
};

class INC : public Command   
{                             
      public:                           
             INC():Command("inc"){}     
             int Run(string, string); 
             bool Check(string, string);
};

class DEC : public Command   
{                             
      public:                           
             DEC():Command("dec"){}     
             int Run(string, string);
             bool Check(string, string); 
};

class INT : public Command   
{                             
      public:                           
             INT():Command("int"){}     
             int Run(string, string);
             bool Check(string, string);
};

class JMP : public Command   
{                             
      public:                           
             JMP():Command("jmp"){}     
             int Run(string, string);
             bool Check(string, string);
};

class LOOP : public Command
{
      public:
             LOOP():Command("loop"){}
             int Run(string, string);
             bool Check(string, string);
};

//JZ, JE, JNZ, JNE, JL, JG

class JZ : public Command   
{                             
      public:                           
             JZ():Command("jz"){}     
             int Run(string, string);
             bool Check(string, string);
};

class JE : public Command   
{                             
      public:                           
             JE():Command("je"){}     
             int Run(string, string); 
             bool Check(string, string);
};

class JNZ : public Command   
{                             
      public:                           
             JNZ():Command("jnz"){}     
             int Run(string, string);
             bool Check(string, string); 
};

class JNE : public Command   
{                             
      public:                           
             JNE():Command("jne"){}     
             int Run(string, string);
             bool Check(string, string); 
};

class JL : public Command   
{                             
      public:                           
             JL():Command("jl"){}     
             int Run(string, string);
             bool Check(string, string);
};

class JG : public Command   
{                             
      public:                           
             JG():Command( "jg" ){}     
             int Run(string, string);
             bool Check(string, string);
};

extern Command* cmds[14];
extern CommandList cmd;

#endif
