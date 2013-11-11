/*
Name:        label.h
Date:        2011-05-03
Author:      Yifan Pi
Description: The .cpp file for Label and LabelList.
*/


#include "label.h"

LabelList lbl;

int LabelList::Find(string s)
{
    for (int i=0;i<lb.size();i++)
        if (s==lb[i].ReturnNam())
           return lb[i].ReturnNum();
    return -1;
}

bool LabelList::Insert(string s, int h)
{
     if (Find(s)!=-1) return 0;
     lb.push_back(Label(s,h));
     return 1;
}
