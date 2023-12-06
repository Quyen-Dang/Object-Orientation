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
//start project part 2:
PartToken :: PartToken (typeToken tokenType, string tokenText)
{
    text = tokenText;
    type = tokenType;
}

typeToken PartToken :: getType()
{
    return type;   
}

string PartToken :: getText()
{
    return text;
}
PassageTokenizer :: PassageTokenizer(string passage)
{
    token = passage;
    posPart = 0;
}

bool PassageTokenizer :: hasNextPart()
{
    return (posPart < token.length());
}

PartToken PassageTokenizer :: nextPart()
{
    size_t foundLink, foundComm, foundBlock;
    size_t foundCommSet, foundCommGoto, foundCommIf, foundCommElseIf, foundCommElse;
    size_t toPos;
    foundLink = token.find("[[", posPart);
    foundComm = token.find("(", posPart);
    foundCommSet = token.find("(set:", posPart);
    foundCommGoto = token.find("(go-to:", posPart);
    foundCommIf = token.find("(if:", posPart);
    foundCommElseIf = token.find("(else-if:", posPart);
    foundCommElse = token.find("(else:", posPart);
    foundBlock = token.find("[", posPart);
    string text;
    typeToken type;

    //if link or command or is not the next part, 
    //the text has type TEXT, and the text would be from the begining to the found
    if(foundLink != posPart && foundComm != posPart && foundBlock != posPart)
    {
        //Link found before Command
        if(foundLink < foundComm)
        {
            text = token.substr(posPart, foundLink - posPart);
            posPart = foundLink;
            type = TEXT;
        }
        //Command found before Link
        else
        {
            text = token.substr(posPart, foundComm - posPart);
            posPart = foundComm;  
            type = TEXT;             
        }   
    }
    //the next part is a Link
    else if(foundLink == posPart)
    {
        toPos = token.find("]]", posPart);
        toPos += 2;
        text = token.substr(posPart, toPos - posPart);
        posPart = toPos;
        type = LINK;
    }
    //the next part is a Command
    else if(foundComm == posPart)
    {
        toPos = token.find(")", posPart);
        toPos += 1;
        text = token.substr(foundComm, toPos - foundComm);
        posPart = toPos;
        if(foundComm == foundCommSet) type = SET;
        if(foundComm == foundCommGoto) type = GOTO;
        if(foundComm == foundCommIf) type = IF;
        if(foundComm == foundCommElseIf) type = ELSEIF;
        if(foundComm == foundCommElse) type = ELSE;            
    }
    //the next part is a Block
    else if (foundBlock == posPart)
    {
        toPos = token.find("]", posPart);
        int count = 1;
        size_t foundNextBlock = token.find("[", posPart + 1);
        // if the block contain other token
        if(foundNextBlock < toPos)
        {
            for (posPart + 1; posPart < toPos; posPart++)
            {
                if(foundNextBlock != string::npos)
                    count++;
            }
            toPos += count;
            text = token.substr(foundBlock, toPos - foundBlock);
            posPart = toPos;
            type = BLOCK;
        }
        //the block is only 1 level (no contain other token)
        else 
        {
            toPos += count;
            text = token.substr(foundBlock, toPos - foundBlock);
            posPart = toPos;
            type = BLOCK;
        }   
    }
    return PartToken (type, text);        
}

