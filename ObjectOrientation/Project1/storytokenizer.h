#ifndef STORY_TOKENIZER_H
#define STORY_TOKENIZER_H
#include<string>
#include<iostream>
using namespace std;

class PassageToken
{
private:
    string name;
    string text;
public:
    PassageToken();
    PassageToken(string passageName, string passageText);
    string getName();
    string getText();
};

class StoryTokenizer
{
private:
    string passages;
    string startPassageTag = "<tw-passagedata";
    string endPassageTag = "</tw-passagedata>";
    int pos = 0;

public:    
    StoryTokenizer(string input);
    PassageToken nextPassage();
    bool hasNextPassage();
};

#endif