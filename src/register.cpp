/*
Name:        register.cpp
Date:        2011-05-03
Author:      Yifan Pi
Description: The .cpp file for Register and RegisterList.
*/


#include "register.h"

#define HighOne 65280
//65280(Dec)=1111111100000000(Bin)
#define LowOne 255
//255(Dec)=0000000011111111(Bin)

SF SF_O; ZF ZF_O;

Flag* flgs[2]={&SF_O, &ZF_O};
FlagList flg(flgs, 2);
Register regs[4]={Register('a'), Register('b'), Register('c'), Register('d')};
RegisterList reg(regs,4);

void Register::OperateLowDigit(char op, int num)
{
     switch (op)
     {
            case '+': flg.Upd(int(l)+num); l+=num; break;
            case '-': flg.Upd(int(l)-num); l-=num; break;
     }
}

void Register::OperateHighDigit(char op,int num)
{
     switch (op)
     {
            case '+': flg.Upd(int(h)+num); h+=num; break;
            case '-': flg.Upd(int(h)-num); h-=num; break;
     }
}

void Register::Operate(char op, int num)
{
     
     switch (op)
     {
            case '+': flg.Upd(Read()+num); Modify(Read()+num); break;
            case '-': flg.Upd(Read()-num); Modify(Read()-num); break;
     }
}     

void Register::ModifyLowDigit(int num)
{
     l=num;
}

void Register::ModifyHighDigit(int num)
{
     h=num;
}

void Register::Modify(int num)
{
     unsigned short x=num;
     h=x>>8;
     l=x&LowOne;
}

//=======================================================//

int RegisterList::Find(char ch)
{
    for (int i=0;i<size;i++)
        if (reg[i].ReadId()==ch) return i;
    return -1;
}

void RegisterList::Operate(char cmd, string op, string num)
{
    int p=Find(op[0]);
    int x=atoh(num);
    switch (op[1])
    {
           case 'l': reg[p].OperateLowDigit(cmd, x); break;
           case 'h': reg[p].OperateHighDigit(cmd, x); break;
           case 'x': reg[p].Operate(cmd, x); break;
    }
}

void RegisterList::Operate(char cmd, string op, int num)
{
    int p=Find(op[0]);
    switch (op[1])
    {
           case 'l': reg[p].OperateLowDigit(cmd, num); break;
           case 'h': reg[p].OperateHighDigit(cmd, num); break;
           case 'x': reg[p].Operate(cmd, num); break;
    }
}

void RegisterList::Modify(string op, string num)
{
    int p=Find(op[0]);
    int x=atoh(num);
    switch (op[1])
    {
           case 'l': reg[p].ModifyLowDigit(x); break;
           case 'h': reg[p].ModifyHighDigit(x); break;
           case 'x': reg[p].Modify(x); break;
    }
}

void RegisterList::Modify(string op, int num)
{
    int p=Find(op[0]);
    switch (op[1])
    {
           case 'l': reg[p].ModifyLowDigit(num); break;
           case 'h': reg[p].ModifyHighDigit(num); break;
           case 'x': reg[p].Modify(num); break;
    }
}

int RegisterList::Read(string op)
{
    if (op.length()>2) return -1;
    if ((op[1]!='h'&&op[1]!='l'&&op[1]!='x')||Find(op[0])==-1) return -1;
    int p=reg[Find(op[0])].Read();
    switch (op[1])
    {
           case 'l': return p&LowOne; break;
           case 'h': return (p&HighOne)>>8; break;
           case 'x': return p; break;
    }
}

void RegisterList::Show()
{
     for (int i=0;i<size;i++)
     {
         string s="";
         s=s+reg[i].ReadId();
         cout<<s+"x"<<" = "<<Read(s+"x")<<' ';
         cout<<s+"h"<<" = "<<Read(s+"h")<<' ';
         cout<<s+"l"<<" = "<<Read(s+"l")<<' ';
         cout<<endl;
     }
}

void RegisterList::Clear()
{
     for (int i=0;i<size;i++)
         reg[i].Modify(0);
}

//=====================================================//

int FlagList::Find(string s)
{
    for (int i=0;i<size;i++)
        if (flg[i]->ReadNam()==s)
           return i;
  //  RunTimeError(1);
}

void FlagList::Upd(int x)
{
     for (int i=0;i<size;i++)
         flg[i]->Upd(x);
}

int FlagList::Read(string s)
{
     return flg[Find(s)]->ReadNum();
}
