#include "storytokenizer.h"
#include <string>
using namespace std;

PassageToken :: PassageToken()
{
    name = "";
    text = "";
}
PassageToken :: PassageToken(string passageName, string passageText)
{
    name = passageName;
    text = passageText;
}

string PassageToken :: getName()
{
    return name;  
}
string PassageToken :: getText()
{
    return text;
}
StoryTokenizer :: StoryTokenizer(string input)
{
    passages = input;
    pos = 1;
}

bool StoryTokenizer :: hasNextPassage ()
{
    return passages.find(startPassageTag, pos) != string :: npos;
}

PassageToken StoryTokenizer :: nextPassage()
{
    size_t fromPos, toPos;
    string token;
    string nameTag = "name=\"";
    
    //Get the whole one passage to another string
    fromPos = passages.find(startPassageTag, pos);
    toPos = passages.find(endPassageTag, pos);
    toPos += endPassageTag.length();
    if(fromPos != string::npos && toPos != string::npos)
        token = passages.substr(fromPos, toPos-fromPos);
    
    //Find the name from the passage and get to the string name
    size_t startNameIdx = token.find(nameTag);
    startNameIdx += nameTag.length();
    size_t endNameIdx = token.find_first_of("\"", startNameIdx);
    string name = token.substr(startNameIdx, endNameIdx - startNameIdx);
    
    //Find the body text from the passage and get to the string text
    size_t startTextIdx = token.find(">", startNameIdx);
    size_t endTextIdx = token.find(endPassageTag, startTextIdx);
    string text = token.substr(startTextIdx+1, endTextIdx - startTextIdx-1);
    
    pos = toPos;//update the position of pos
    return PassageToken(name, text);
}

