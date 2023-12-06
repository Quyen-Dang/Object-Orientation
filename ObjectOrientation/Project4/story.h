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
};

class If
{
private:
    string var;
    string value;
    string textIf;
    int posIf;
public:
    If();
    void setVar(string);
    void setVal(string);
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
    void setVal(string);
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
