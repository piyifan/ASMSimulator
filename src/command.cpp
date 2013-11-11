/*
Name:        command.cpp
Date:        2011-05-03
Author:      Yifan Pi
Description: The .cpp file for Command and CommandList.
*/

#include "command.h"

MOV MOV_O;
ADD ADD_O;
SUB SUB_O;
INC INC_O;
DEC DEC_O;
INT INT_O;
LOOP LOOP_O;
JMP JMP_O;
JZ JZ_O;
JE JE_O;
JNZ JNZ_O;
JNE JNE_O;
JL JL_O;
JG JG_O;

Command* cmds[14]={&MOV_O,&ADD_O,&SUB_O,&INC_O,&DEC_O,&INT_O,&LOOP_O,
                  &JMP_O,&JZ_O, &JE_O,&JNZ_O,&JNE_O,&JL_O,&JG_O};
CommandList cmd(cmds,14);

int CommandList::Run(string op, string arg1, string arg2)
{
    for (int i=0;i<size;i++)
        if (cmd[i]->ReturnName()==op)
            return cmd[i]->Run(arg1, arg2);
    return 0;
}

bool CommandList::Check(string op, string arg1, string arg2)
{
    for (int i=0;i<size;i++)
        if (cmd[i]->ReturnName()==op)
            return cmd[i]->Check(arg1, arg2);
    return 0;
}

int MOV::Run(string arg1, string arg2)
{
    if (isdigit(arg2[0])||(arg2[0]>='A'&&arg2[0]<='F'))
        reg.Modify(arg1, arg2);
    else
        reg.Modify(arg1, reg.Read(arg2));
    return 0;
}

int ADD::Run(string arg1, string arg2)
{
    if (isdigit(arg2[0])||(arg2[0]>='A'&&arg2[0]<='F'))
        reg.Operate('+', arg1, arg2);
    else
        reg.Operate('+', arg1, reg.Read(arg2));
    return 0;
}

int SUB::Run(string arg1, string arg2)
{
    if (isdigit(arg2[0])||(arg2[0]>='A'&&arg2[0]<='F'))
        reg.Operate('-', arg1, arg2);
    else
        reg.Operate('-', arg1, reg.Read(arg2));
    return 0;
}

int INC::Run(string arg1, string arg2)
{
    reg.Operate('+', arg1, 1);
    return 0;
}

int DEC::Run(string arg1, string arg2)
{
    reg.Operate('-', arg1, 1);
    return 0;
}

int INT::Run(string arg1, string arg2)
{
    if (arg1=="21")
    {
        int p=reg.Read("ah");
        string s;
        switch (p)
        {
            case 1: 
               cin>>s;
               reg.Modify("dl",s);
               break;
            case 2: cout<<char(reg.Read("dl")); break;
            case 3: cout<<htoa(reg.Read("dl")); break;
        }
    }
    return 0;
}

int JMP::Run(string arg1, string arg2)
{
    return lbl.Find(arg1);
}

int LOOP::Run(string arg1, string arg2)
{
    if (reg.Read("cx")>0)
    {
        reg.Operate('-', "cx", 1);
        return lbl.Find(arg1);
    }
    else return 0;
}
        
int JZ::Run(string arg1, string arg2)
{
    if (flg.Read("zf")==1) 
       return lbl.Find(arg1);
    else
       return 0;
}

int JE::Run(string arg1, string arg2)
{
    if (flg.Read("zf")==1) 
       return lbl.Find(arg1);
    else
       return 0;
}

int JNZ::Run(string arg1, string arg2)
{
    if (flg.Read("zf")==0)
       return lbl.Find(arg1);
    else
       return 0;
}

int JNE::Run(string arg1, string arg2)
{
    if (flg.Read("zf")==0) 
       return lbl.Find(arg1);
    else
       return 0;
}

int JL::Run(string arg1, string arg2)
{
    if (flg.Read("zf")==0&&flg.Read("sf")==1) 
       return lbl.Find(arg1);
    else
       return 0;
}

int JG::Run(string arg1, string arg2)
{
    if (flg.Read("zf")==0&&flg.Read("sf")==0) 
       return lbl.Find(arg1);
    else
       return 0;
}

//===================================================//

bool MOV::Check(string arg1, string arg2)
{
    if (reg.Read(arg1)==-1) return 0;
    if (reg.Read(arg2)==-1&&!IsHex(arg2)) return 0;
    return 1;
}

bool ADD::Check(string arg1, string arg2)
{
    if (reg.Read(arg1)==-1) return 0;
    if (reg.Read(arg2)==-1&&!IsHex(arg2)) return 0;
    return 1;
}

bool SUB::Check(string arg1, string arg2)
{
    if (reg.Read(arg1)==-1) return 0;
    if (reg.Read(arg2)==-1&&!IsHex(arg2)) return 0;
    return 1;
}

bool INC::Check(string arg1, string arg2)
{
    if (arg2!="") return 0;
    if (reg.Read(arg1)==-1) return 0;
    return 1;
}

bool DEC::Check(string arg1, string arg2)
{
    if (arg2!="") return 0;
    if (reg.Read(arg1)==-1) return 0;
    return 1;
}

bool INT::Check(string arg1, string arg2)
{
    if (arg2!="") return 0;
    if (arg1!="20"&&arg1!="21") return 0;
    return 1;
}

bool JMP::Check(string arg1, string arg2)
{
    if (arg2!="") return 0;
    if (lbl.Find(arg1)==-1) return 0;
    return 1;
}

bool LOOP::Check(string arg1, string arg2)
{
    if (arg2!="") return 0;
    if (lbl.Find(arg1)==-1) return 0;
    return 1;
}
        
bool JZ::Check(string arg1, string arg2)
{
    if (arg2!="") return 0;
    if (lbl.Find(arg1)==-1) return 0;
    return 1;
}

bool JE::Check(string arg1, string arg2)
{
    if (arg2!="") return 0;
    if (lbl.Find(arg1)==-1) return 0;
    return 1;
}

bool JNZ::Check(string arg1, string arg2)
{
    if (arg2!="") return 0;
    if (lbl.Find(arg1)==-1) return 0;
    return 1;
}

bool JNE::Check(string arg1, string arg2)
{
    if (arg2!="") return 0;
    if (lbl.Find(arg1)==-1) return 0;
    return 1;
}

bool JL::Check(string arg1, string arg2)
{
    if (arg2!="") return 0;
    if (lbl.Find(arg1)==-1) return 0;
    return 1;
}

bool JG::Check(string arg1, string arg2)
{
    if (arg2!="") return 0;
    if (lbl.Find(arg1)==-1) return 0;
    return 1;
}

