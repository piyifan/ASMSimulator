/*
Name:        label.h
Date:        2011-05-03
Author:      Yifan Pi
Description: The .h file for Label and LabelList.
*/

#ifndef LABEL_H
#define LABEL_H

#include "general.h"
#include <vector>
#include <string>
using namespace std;

class Label
{
      string nam;
      int num;
      public:
             Label(string s, int n):nam(s), num(n){};
             string ReturnNam() {return nam;}
             int ReturnNum() {return num;}
};

class LabelList
{
      vector <Label> lb;
      public:
             LabelList(){lb.clear();}
             bool Insert(string s, int h);
             int Find(string);
             void Clear() {lb.clear();}
};

extern LabelList lbl;

#endif
