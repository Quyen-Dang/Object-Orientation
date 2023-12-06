#include <iostream>
#include <fstream>
#include <string>
#include "story.h"
#include "storytokenizer.cpp"
using namespace std;

// STORY CLASS FUNCTION
Story :: Story(string file_input)
{
    file = file_input;   
}

void Story:: print()
{
    string line;
    ifstream in(file);
    if (!in.is_open())
    {
        cout << "Couldn't open " << file << " for reading!\n";
        return;
    }
//Read in the story from if.html
    getline(in, line);
    while (in && line != "</html>")
    {
        story += line + '\n';
        getline(in, line);
    }
    //Construct the StoryTokenizer object
  StoryTokenizer st(story);
  //Iterate through all of the passages in the story
  while (st.hasNextPassage())
  {
    //Use the PassageToken to construct a PassageTokenizer
    PassageToken ptok = st.nextPassage();
    PassageTokenizer pt(ptok.getText());

    //Iterate through all of the parts of the passage
    cout << "Passage " << ptok.getName() << ":  " << endl;
    while (pt.hasNextPart())
    {
      PartToken stok = pt.nextPart();
      string text = stok.getText();
      switch (stok.getType())
      {
        case LINK:
        {
            cout << "Link: ";
            Link value;
            value.setDisplay(text);
            value.setTarget(text);
            value.print();
        }
        break;
        case SET:
        {
            cout << "Set: ";
            Set var;
            var.setVar(text);
            var.setVal(text);
            var.print();
        }
        break;
        case GOTO:
        {
            cout << "Go-to: ";
            GoTo val;
            val.setValue(text);
            val.print();
        }
        break;
        case IF:
        {
            cout << "If: ";
            If var;
            var.setVar(text);
            var.setVal(text);
            var.print();
        }
        break;
        case ELSEIF:
        {
            cout << "Else-if: " << endl;
            If var;
            var.setVar(text);
            var.setVal(text);
            var.print();
        }
        break;
        case ELSE:
            cout << "Else" << endl;
        break;
        case TEXT:
            cout << "Text: " << "\"" << text << "\"" << endl;
        break;
        case BLOCK:
        {
            cout << "START BLOCK" << endl;
            Block blockPart(text);
            while(blockPart.hasNextToken())
            {
                PartToken pt = blockPart.nextToken();
                string textBlock = pt.getText();
                switch (pt.getType())
                {
                case TEXT:
                {
                    cout << "Text: \"" << textBlock << "\""<< endl;    
                }
                break;
                case LINK:
                {
                    cout << "Link: ";
                    Link value;
                    value.setDisplay(textBlock);
                    value.setTarget(textBlock);
                    value.print();   
                }
                break;
                case SET:
                {
                    cout << "Set: ";
                    Set var;
                    var.setVar(textBlock);
                    var.setVal(textBlock);
                    var.print();
                }
                break;
                case GOTO:
                {
                    cout << "Go-to: ";
                    GoTo val;
                    val.setValue(textBlock);
                    val.print();
                }
                break;
                case IF:
                {
                    cout << "If: ";
                    If var;
                    var.setVar(textBlock);
                    var.setVal(textBlock);
                    var.print();
                }
                break;
                case ELSEIF:
                {
                    cout << "Else-if: ";
                    If var;
                    var.setVar(textBlock);
                    var.setVal(textBlock);
                    var.print();
                }
                break;
                case ELSE:
                {
                    cout << "Else" << endl;    
                }
                break;
                case BLOCK:
                {
                    cout << textBlock << endl;
                }
                break;
                default:
                    cout << "Unknown token:  " << endl;
                }
            }
        }
        break;
        default:
            cout << "Unknown token:  " << endl;
      }
    }
  } 
}   
// IF class for If/ElseIf
If :: If()
{
    var = "var";
    value = "value";
    posIf = 0;
}
void If::setVar(string text)
{
    textIf = text;
    size_t foundVar = textIf.find("$", posIf);
    size_t foundVal = textIf.find("is ", posIf);
    foundVal +=2;
    var = textIf.substr(foundVar, foundVal - foundVar - 3);
    //posIf = foundVal;
}
void If::setVal(string text)
{
    
    textIf = text;
    size_t foundVal = textIf.find("is ", posIf);
    foundVal +=3;
    size_t to_pos = textIf.find(")", posIf);
    value = textIf.substr(foundVal, to_pos - foundVal);
    //posIf = to_pos;
}
void If::print()
{
    cout << "var=" << var << ", value=" << value << endl;
}
//Set class
Set :: Set()
{
    var = "var";
    value = "value";
    posSet = 0;
}
void Set::setVar(string text)
{
    textIf = text;
    size_t foundVar = textIf.find("$", posSet);
    size_t foundVal = textIf.find("to ", posSet);
    foundVal +=2;
    var = textIf.substr(foundVar, foundVal - foundVar - 3);
    //posIf = foundVal;
}
void Set::setVal(string text)
{
    
    textIf = text;
    size_t foundVal = textIf.find("to ", posSet);
    foundVal +=3;
    size_t to_pos = textIf.find(")", posSet);
    value = textIf.substr(foundVal, to_pos - foundVal);
    //posIf = to_pos;
}
void Set::print()
{
    cout << "var=" << var << ", value=" << value << endl;
}
//Goto class
GoTo::GoTo()
{
    target = "goto";
    posGoTo = 0;
}
void GoTo :: setValue(string text)
{
    textGoTo = text;
    size_t foundStart = textGoTo.find("&quot;", posGoTo);
    foundStart += 6;
    size_t foundEnd = textGoTo.find("&quot;)", posGoTo);
    target = textGoTo.substr(foundStart, foundEnd - foundStart);
           
}
void GoTo:: print()
{
     cout << "target=" << target << endl;
}
//Link class
Link::Link()
{
    display = "display";
    target = "target";
    posLink = 0;
}
void Link::setDisplay(string text)
{
    textLink = text;
    size_t foundTarget = text.find("-&gt;", posLink);
    size_t to_pos = text.find("]]", posLink);
    if(foundTarget != string::npos)
    {
        to_pos = foundTarget;
        display = textLink.substr(posLink + 2, to_pos - posLink - 2);
    }
    display = textLink.substr(posLink + 2, to_pos - posLink - 2);
}
void Link:: setTarget(string text)
{
    textLink = text;
    size_t foundTarget = text.find("-&gt;", posLink);
    size_t to_pos = text.find("]]", posLink);
    if(foundTarget != string::npos)
    {
        target = textLink.substr(foundTarget + 5, to_pos - foundTarget - 5);
    }
    else
        target = textLink.substr(posLink + 2, to_pos - posLink - 2);

}
void Link:: print()
{
    cout << "display=" << display << ", target=" << target << endl;
}
//Block class
Block::Block(string text)
{
    textBlock = text;
    posBlock = 0;
} 
bool Block::hasNextToken()
{
    return posBlock < textBlock.length();
}
PartToken Block:: nextToken()
{
    size_t foundLink, foundComm, foundNextBlock, foundEndBlock;
    size_t foundCommSet, foundCommGoto, foundCommIf, foundCommElseIf, foundCommElse;
    size_t toPos;
    foundLink = textBlock.find("[[", posBlock);
    foundComm = textBlock.find("(", posBlock);
    foundNextBlock = textBlock.find("[", posBlock);
    foundEndBlock = textBlock.find("]", posBlock);
    foundCommSet = textBlock.find("(set:", posBlock);
    foundCommGoto = textBlock.find("(go-to:", posBlock);
    foundCommIf = textBlock.find("(if:", posBlock);
    foundCommElseIf = textBlock.find("(else-if:", posBlock);
    foundCommElse = textBlock.find("(else:", posBlock);
    string text;
    typeToken type;       
    //the part in block not start by link, command, nor block
    if(foundLink != posBlock && foundComm != posBlock && foundNextBlock != posBlock && foundEndBlock != posBlock)
    {
        //Link found before Command
        if(foundLink < foundComm)
        {
            text = textBlock.substr(posBlock, foundLink - posBlock);
            posBlock = foundLink;
            type = TEXT;
        }
        //Command found before Link
        else if (foundLink > foundComm)
        {
        text = textBlock.substr(posBlock, foundComm - posBlock);
        posBlock = foundComm;  
        type = TEXT;             
        } 
        //Block not contain link nor commands, all text in the block
        else 
        {
            text = textBlock.substr(posBlock, foundEndBlock - posBlock);
            posBlock = foundEndBlock;  
            type = TEXT;
        } 
    }
    //the next part is a Link
    else if(foundLink == posBlock)
    {
        toPos = textBlock.find("]]", posBlock);
        toPos += 2;
        text = textBlock.substr(posBlock, toPos - posBlock);
        posBlock = toPos;
        type = LINK;
    }
    //the next part is a Command
    else if(foundComm == posBlock)
    {
        toPos = textBlock.find(")", posBlock);
        toPos += 1;
        text = textBlock.substr(foundComm, toPos - foundComm);
        posBlock = toPos;
        if(foundComm == foundCommSet) type = SET;
        if(foundComm == foundCommGoto) type = GOTO;
        if(foundComm == foundCommIf) type = IF;
        if(foundComm == foundCommElseIf) type = ELSEIF;
        if(foundComm == foundCommElse) type = ELSE;            
    }  
    else if(foundNextBlock == posBlock)
    {
        type = BLOCK;
        text = "START BLOCK";
        posBlock += 1;
    } 
    else if (foundEndBlock = posBlock)
    {
        type = BLOCK;
        text = "END BLOCK";
        posBlock += 1;
    }    
    return PartToken (type, text); 
}