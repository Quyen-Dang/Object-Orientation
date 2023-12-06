#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <iostream>
using namespace std;

const int ALPHABET_SIZE = 26;
const string DICTIONARY_FILE = "dictionary.txt";

void countLetters(string word, int* count)
{
    int i;
    
    for(i = 0; i < ALPHABET_SIZE; i++)
    {
        count[i] = 0;
    } 
    for(i = 0; i < word.length(); i++)
    {
        if(isalpha(word.at(i)))
            count[(tolower(word.at(i))-'a')]++;
    }
    
}

bool isJumble(string word1, string word2)
{
    int countWord1[ALPHABET_SIZE];
    int countWord2[ALPHABET_SIZE];

    countLetters(word1, countWord1);
    countLetters(word2, countWord2);

    if(word1.size() == word2.size())
    {
        for(int i = 0; i < ALPHABET_SIZE; i++)
        {
            if(countWord1[i] != countWord2[i])
            return false;
        }
    }
    else return false;
    return true;
}

vector<string> findMatches(string word, vector<string> vec)
{
    vector<string> matchWords;
    for(int i = 0; i < vec.size(); i++)
    {
        if(isJumble(word, vec.at(i)) == true) 
            matchWords.push_back(vec.at(i));
    }
    return matchWords;
}

int main()
{
    ifstream dictionary;
    string userWord;
    string words;
    vector<string> dictionaryWords;
    vector<string> anagram;

    dictionary.open(DICTIONARY_FILE);
    if(!dictionary.is_open())
    {
        cout << "Could not open file dictionary.txt" << endl;
        return 1;
    }

    while (!dictionary.eof())
    {
        dictionary >> words;
        dictionaryWords.push_back(words);
    }
    dictionary.close(); 
    
    cin >> userWord;
    while (userWord != "quit")
    {
        anagram = findMatches(userWord, dictionaryWords);
        if (anagram.size() == 0) cout << "No match!" << endl;
        else
        {
            for(int i = 0; i < anagram.size(); i++)
            {
                cout << anagram.at(i) << endl;
            }  
        }
        cin >> userWord;
    }
    
    return 0;   

}