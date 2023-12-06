#ifndef STORY_H
#define STORY_H
#include<string>
#include<iostream>
using namespace std;
#include "storytokenizer.h"

class Story
{
private:
    string file, story;
public:
    Story (string);
    void print();
    void play();
    string getPassage(string);
    void printPassage(string);
    void printLinks(string);
};

class If
{
private:
    string var;
    string value;
    string textBlock;
    string textIf;
    int posIf;
public:
    If();
    void setVar(string);
    void setVal(string);
    string getVar() {return var;};
    string getVal() {return value;};
    string getTextBlock(string);
    void print();

};
class Set
{
    string var;
    string value;
    string textIf;
    int posSet;
public:
    Set();
    void setVar(string);
    string getVar() {return var;};
    void setVal(string);
    string getVal(){return value;};
    void print();
};

class GoTo
{
private:
    string textGoTo;
    string target;
    int posGoTo;
public:
    GoTo();
    void setValue(string);
    string getValue();
    void print();

};
class Link
{
private:
    string target;
    string display;
    string textLink;
    int posLink;
public:
    Link();
    void setTarget(string);
    void setDisplay(string);
    void print();
    string getDisplay();
    string getTarget() {return target;};

};
class Block
{
private:
    string textBlock;
    int posBlock;
public:
    Block(string);
    PartToken nextToken();
    bool hasNextToken();
};
#endif
