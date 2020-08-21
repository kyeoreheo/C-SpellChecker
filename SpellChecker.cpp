//  Created by Kyeo re, Heo on 10/18/19.
#include "SpellChecker.hpp"
#include <iostream>
#include <fstream>
#include <locale>
#include <chrono>

SpellChecker::SpellChecker()
{
    std::cout<<"Default Constroctor"<<std::endl;
};

SpellChecker::SpellChecker(const std::string& inputDictionary)
{
    myInputDictionaryFile_ = inputDictionary;
}


SpellChecker::~SpellChecker()
{std::cout<<"Deconstroctor"<<std::endl;};

//------------------------Vector-----------------------------------

void SpellChecker::CheckWithVector(const std::string& inputFile)
{
    duration_ = 0.0f;
    auto myStart = std::chrono::high_resolution_clock::now();
    SetDictionaryWithVector();
    SetIgnoreWordsWithVector();
    ReadFileWithVector(inputFile);
    auto myEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> myDuration = myEnd - myStart;
    duration_ = myDuration.count()*1000.0f;
    CreateFileWithVector();
}

void SpellChecker::SetIgnoreWordsWithVector()
{
    for(int i = 33; i < 127;)
    {
        char myChar = i;
        vectorIgnoreWords.push_back(myChar);
        i ++;
        if(i == 48) i = 58;
        if(i == 65) i = 91;
        if(i== 97) i = 123;
    }
}

void SpellChecker::SetDictionaryWithVector()
{
    std::ifstream myFile;
    myFile.open(myInputDictionaryFile_);
    if(myFile.is_open())
    {
        std::string myWord;
        while(myFile >> myWord)
        { vectorDictionary.push_back(cleanWordWithVector(myWord)); }
    }
    else
        std::cout<<"Error"<<std::endl;
}

void SpellChecker::ReadFileWithVector(const std::string& inputFile)
{
    strTextOutcome="";
    std::ifstream myFile;
    myFile.open(inputFile);
    if(myFile.is_open())
    {
        std::string myWord;
        while(myFile >> myWord)
        {
            if(isWrongWordWithVector(myWord))
            {
                GetTheAnswersWithVector(cleanWordWithVector(myWord));
                if(vectorAnswers.size()>0)
                {
                    strTextOutcome += myWord + "(";
                    std::vector<std::string>::iterator element;
                    std::vector<std::string>::iterator lastPtr = vectorAnswers.end();
                    std::vector<std::string>::iterator myPtr = prev(lastPtr, 1);
                    for(element = vectorAnswers.begin(); element!= vectorAnswers.end(); element++)
                    {
                        if(element == myPtr)
                            strTextOutcome+=*element+") ";
                        else
                            strTextOutcome+=*element+", ";
                    }
                }
                else
                    strTextOutcome += myWord + "(Cannot Find the suggestion) ";
            }
            else
                strTextOutcome += myWord + " ";
        }
    }
    else
        std::cout<<"Error"<<std::endl;
}
bool SpellChecker::isWrongWordWithVector(const std::string& inputWord)
{
    std::vector<std::string>::iterator searchElement;
    searchElement = std::find(vectorDictionary.begin(), vectorDictionary.end(), cleanWordWithVector( inputWord));
    if(searchElement == vectorDictionary.end())
    {
        return true;
    }
    return false;
}

void SpellChecker::GetTheAnswersWithVector(const std::string &inputWord)
{
    vectorAnswers.clear();
    InsertToFindWithVector(inputWord);
    RemoveToFindWithVector(inputWord);
    SwitchToFindWithVector(inputWord);
    ReplaceToFindWithVector(inputWord);
}

std::string SpellChecker::cleanWordWithVector(const std::string& inputString)
{
    std::string result = "";
    for(int i = 0; i < inputString.length();)
    {
        result += std::tolower(inputString[i]);
        i++;
        for(int j = 0; j < vectorIgnoreWords.size(); j++)
        {
            if(inputString[i] == vectorIgnoreWords[j])
                i++;
        }
    }
    return result;
}

void SpellChecker::InsertToFindWithVector(const std::string& inputWord)
{
    std::vector<std::string>::iterator dictionaryElement;
    for (dictionaryElement = vectorDictionary.begin(); dictionaryElement != vectorDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == 1)
        {
            if(itContains(*dictionaryElement, inputWord))
            {
                vectorAnswers.push_back(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Insert: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}
void SpellChecker::RemoveToFindWithVector(const std::string& inputWord)
{
    std::vector<std::string>::iterator dictionaryElement;
    for (dictionaryElement = vectorDictionary.begin(); dictionaryElement != vectorDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == -1)
        {
            if(itContains(inputWord, *dictionaryElement))
            {
                vectorAnswers.push_back(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Remove: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}

void SpellChecker::SwitchToFindWithVector(const std::string& inputWord)
{
    std::vector<std::string>::iterator dictionaryElement;
    for (dictionaryElement = vectorDictionary.begin(); dictionaryElement != vectorDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == 0)
        {
            if(reArrangeWord(*dictionaryElement, inputWord))
            {
                vectorAnswers.push_back(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Switch: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}

void SpellChecker::ReplaceToFindWithVector(const std::string& inputWord)
{
    std::vector<std::string>::iterator dictionaryElement;
    for (dictionaryElement = vectorDictionary.begin(); dictionaryElement != vectorDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == 0)
        {
            if(reAssembleWord(*dictionaryElement, inputWord))
            {
                vectorAnswers.push_back(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Replace: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}

void SpellChecker::CreateFileWithVector()
{
    std::ofstream myfile ("KyeoreHeo_SpellChekcer_Vector.txt");
    if (myfile.is_open())
    {
      myfile << "Kyeore Heo 91kyoheo@gmail.com \n";
      myfile << "Created file with Vector container \n";
      myfile << strTextOutcome;
      myfile << "It took "<<duration_<<"ms to compute \n";
      myfile.close();
    }
    else
        std::cout << "Error";
}

//------------------------Set-----------------------------------
void SpellChecker::CheckWithSet(const std::string& inputFile)
{
    duration_ = 0.0f;
    auto myStart = std::chrono::high_resolution_clock::now();
    SetDictionaryWithSet();
    SetIgnoreWordsWithSet();
    ReadFileWithSet(inputFile);
    auto myEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> myDuration = myEnd - myStart;
    duration_ = myDuration.count()*1000.0f;
    CreateFileWithSet();
}

void SpellChecker::SetIgnoreWordsWithSet()
{
    for(int i = 33; i < 127;)
    {
        char myChar = i;
        setIgnoreWords.insert(myChar);
        i ++;
        if(i == 48) i = 58;
        if(i == 65) i = 91;
        if(i== 97) i = 123;
    }
}

void SpellChecker::SetDictionaryWithSet()
{
    std::ifstream myFile;
    myFile.open(myInputDictionaryFile_);
    if(myFile.is_open())
    {
        std::string myWord;
        while(myFile >> myWord)
        { setDictionary.insert(cleanWordWithSet(myWord)); }
    }
    else
    { std::cout<<"Error"<<std::endl; }
}

void SpellChecker::ReadFileWithSet(const std::string& inputFile)
{
    strTextOutcome="";
    std::ifstream myFile;
    myFile.open(inputFile);
    if(myFile.is_open())
    {
        std::string myWord;
        while(myFile >> myWord)
        {
            if(isWrongWordWithSet(myWord))
            {
                GetTheAnswersWithSet(cleanWordWithSet(myWord));
                if(setAnswers.size()>0)
                {
                    strTextOutcome += myWord + "(";
                    std::set<std::string>::iterator element;
                    std::set<std::string>::iterator lastPtr = setAnswers.end();
                    std::set<std::string>::iterator myPtr = prev(lastPtr, 1);
                    for(element = setAnswers.begin(); element!= setAnswers.end(); element++)
                    {
                        if(element == myPtr)
                            strTextOutcome+=*element+") ";
                        else
                            strTextOutcome+=*element+", ";
                    }
                }
                else
                    strTextOutcome += myWord + "(Cannot Find the suggestion) ";
            }
            else
                strTextOutcome += myWord + " ";
        }
    }
    else
        std::cout<<"Error"<<std::endl;
}
bool SpellChecker::isWrongWordWithSet(const std::string& inputWord)
{
    std::set<std::string>::iterator searchElement;
    searchElement = std::find(setDictionary.begin(), setDictionary.end(), cleanWordWithSet( inputWord));
    if(searchElement == setDictionary.end())
    {
        return true;
    }
    return false;
}

void SpellChecker::GetTheAnswersWithSet(const std::string &inputWord)
{
    setAnswers.clear();
    InsertToFindWithSet(inputWord);
    RemoveToFindWithSet(inputWord);
    SwitchToFindWithSet(inputWord);
    ReplaceToFindWithSet(inputWord);
}

std::string SpellChecker::cleanWordWithSet(const std::string& inputString)
{
    std::string result = "";
    for(int i = 0; i < inputString.length();)
    {
        result += std::tolower(inputString[i]);
        i++;
        std::set<char>::iterator element;
        for(element = setIgnoreWords.begin(); element != setIgnoreWords.end(); element++)
        {
            if(inputString[i] == *element)
                i++;
        }
    }
    return result;
}

void SpellChecker::InsertToFindWithSet(const std::string& inputWord)
{
    std::set<std::string>::iterator dictionaryElement;
    for (dictionaryElement = setDictionary.begin(); dictionaryElement != setDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == 1)
        {
            if(itContains(*dictionaryElement, inputWord))
            {
                setAnswers.insert(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Insert: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}
void SpellChecker::RemoveToFindWithSet(const std::string& inputWord)
{
    std::set<std::string>::iterator dictionaryElement;
    for (dictionaryElement = setDictionary.begin(); dictionaryElement != setDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == -1)
        {
            if(itContains(inputWord, *dictionaryElement))
            {
                setAnswers.insert(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Remove: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}

void SpellChecker::SwitchToFindWithSet(const std::string& inputWord)
{
    std::set<std::string>::iterator dictionaryElement;
    for (dictionaryElement = setDictionary.begin(); dictionaryElement != setDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == 0)
        {
            if(reArrangeWord(*dictionaryElement, inputWord))
            {
                setAnswers.insert(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Switch: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}

void SpellChecker::ReplaceToFindWithSet(const std::string& inputWord)
{
    std::set<std::string>::iterator dictionaryElement;
    for (dictionaryElement = setDictionary.begin(); dictionaryElement != setDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == 0)
        {
            if(reAssembleWord(*dictionaryElement, inputWord))
            {
                setAnswers.insert(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Replace: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}

void SpellChecker::CreateFileWithSet()
{
    std::ofstream myfile ("KyeoreHeo_SpellChekcer_Set.txt");
    if (myfile.is_open())
    {
      myfile << "Kyeore Heo CSCI335 C++ class Homeworkd spellchecker \n";
      myfile<< "Created file with Set container \n";
      myfile << strTextOutcome;
      myfile << "It took "<<duration_<<"ms to compute \n";
      myfile.close();
    }
    else
        std::cout << "Error";
}


//------------------------UnorderedSet-----------------------------------

void SpellChecker::CheckWithUnorderedset(const std::string& inputFile)
{
    duration_ = 0.0f;
    auto myStart = std::chrono::high_resolution_clock::now();
    SetDictionaryWithUnorderedset();
    SetIgnoreWordsWithUnorderedset();
    ReadFileWithUnorderedset(inputFile);
    auto myEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> myDuration = myEnd - myStart;
    duration_ = myDuration.count()*1000.0f;
    CreateFileWithUnorderedset();
}

void SpellChecker::SetIgnoreWordsWithUnorderedset()
{
    for(int i = 33; i < 127;)
    {
        char myChar = i;
        unorderedIgnoreWords.insert(myChar);
        i ++;
        if(i == 48) i = 58;
        if(i == 65) i = 91;
        if(i== 97) i = 123;
    }
}

void SpellChecker::SetDictionaryWithUnorderedset()
{
    std::ifstream myFile;
    myFile.open(myInputDictionaryFile_);

    if(myFile.is_open())
    {
        std::string myWord;
        while(myFile >> myWord)
        { unorderedDictionary.insert(cleanWordWithUnorderedset(myWord)); }
    }
    else
    { std::cout<<"Error"<<std::endl; }
}

void SpellChecker::ReadFileWithUnorderedset(const std::string& inputFile)
{
    strTextOutcome="";
    std::ifstream myFile;
    myFile.open(inputFile);
    if(myFile.is_open())
    {
        std::string myWord;
        while(myFile >> myWord)
        {
            if(isWrongWordWithUnorderedset(myWord))
            {
                GetTheAnswersWithUnorderedset(cleanWordWithUnorderedset(myWord));
                if(unorderedAnswers.size()>0)
                {
                    strTextOutcome += myWord + "(";
                    std::unordered_set<std::string>::iterator element;
                   // std::unordered_set<std::string>::iterator lastPtr = unorderedAnswers.end();
                    //std::unordered_set<std::string>::iterator myPtr = prev(lastPtr, 1);
                    for(element = unorderedAnswers.begin(); element!= unorderedAnswers.end(); element++)
                    {
                            //strTextOutcome+=*element+") ";
                        strTextOutcome+=*element+", ";
                    }
                    strTextOutcome.erase(strTextOutcome.size()-2, 2);
                    strTextOutcome +=") ";
                }
                else
                    strTextOutcome += myWord + "(Cannot Find the suggestion) ";
            }
            else
                strTextOutcome += myWord + " ";
        }
    }
    else
    { std::cout<<"Error"<<std::endl; }
}
bool SpellChecker::isWrongWordWithUnorderedset(const std::string& inputWord)
{
    std::unordered_set<std::string>::iterator searchElement;
    searchElement = std::find(unorderedDictionary.begin(), unorderedDictionary.end(), cleanWordWithUnorderedset( inputWord));
    if(searchElement == unorderedDictionary.end())
    {
        return true;
    }
    return false;
}

void SpellChecker::GetTheAnswersWithUnorderedset(const std::string &inputWord)
{
    unorderedAnswers.clear();
    InsertToFindWithUnorderedset(inputWord);
    RemoveToFindWithUnorderedset(inputWord);
    SwitchToFindWithUnorderedset(inputWord);
    ReplaceToFindWithUnorderedset(inputWord);
}


std::string SpellChecker::cleanWordWithUnorderedset(const std::string& inputString)
{
    std::string result = "";
    for(int i = 0; i < inputString.length();)
    {
        result += std::tolower(inputString[i]);
        i++;
        std::unordered_set<char>::iterator element;
        for(element = unorderedIgnoreWords.begin(); element != unorderedIgnoreWords.end(); element++)
        {
            if(inputString[i] == *element)
                i++;
        }
    }
    return result;
}

void SpellChecker::InsertToFindWithUnorderedset(const std::string& inputWord)
{
    std::unordered_set<std::string>::iterator dictionaryElement;
    for (dictionaryElement = unorderedDictionary.begin(); dictionaryElement != unorderedDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == 1)
        {
            if(itContains(*dictionaryElement, inputWord))
            {
                unorderedAnswers.insert(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Insert: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}
void SpellChecker::RemoveToFindWithUnorderedset(const std::string& inputWord)
{
    std::unordered_set<std::string>::iterator dictionaryElement;
    for (dictionaryElement = unorderedDictionary.begin(); dictionaryElement != unorderedDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == -1)
        {
            if(itContains(inputWord, *dictionaryElement))
            {
                unorderedAnswers.insert(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Remove: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}

void SpellChecker::SwitchToFindWithUnorderedset(const std::string& inputWord)
{
    std::unordered_set<std::string>::iterator dictionaryElement;
    for (dictionaryElement = unorderedDictionary.begin(); dictionaryElement != unorderedDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == 0)
        {
            if(reArrangeWord(*dictionaryElement, inputWord))
            {
                unorderedAnswers.insert(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Switch: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}

void SpellChecker::ReplaceToFindWithUnorderedset(const std::string& inputWord)
{
    std::unordered_set<std::string>::iterator dictionaryElement;
    for (dictionaryElement = unorderedDictionary.begin(); dictionaryElement != unorderedDictionary.end(); dictionaryElement++)
    {
        if(lengthDifferenceOfWord(*dictionaryElement, inputWord) == 0)
        {
            if(reAssembleWord(*dictionaryElement, inputWord))
            {
                unorderedAnswers.insert(*dictionaryElement);
                //std::cout<<"wrong word: "<<inputWord<<" by Replace: "<<*dictionaryElement<<std::endl;
            }
        }
    }
}

void SpellChecker::CreateFileWithUnorderedset()
{
    std::cout<<"Insideof Create:"<<duration_<<std::endl;

    std::ofstream myfile ("KyeoreHeo_SpellChekcer_Unorderedset.txt");
    if (myfile.is_open())
    {
      myfile << "Kyeore Heo CSCI335 C++ class Homeworkd spellchecker \n";
      myfile<< "Created file with Unorderedset container \n";
      myfile << strTextOutcome;
      myfile << "It took "<<duration_<<"ms to compute \n";
      myfile.close();
    }
    else
        std::cout << "Error";
}

int SpellChecker::lengthDifferenceOfWord(const std::string& inputDictionaryWord, const std::string& inputWord)
{
    return (int)inputDictionaryWord.size() - (int)inputWord.size();
}

bool SpellChecker::reAssembleWord(const std::string &inputDictionaryWord, const std::string &inputWord)
{
    bool result = false;
    std::string tmpString;
    std::string myInputWord = inputWord;
    for(int i = 0; i <inputWord.size(); i ++)
    {
        myInputWord.erase(i,1);
        tmpString = myInputWord;
        for(int j = 97; j < 123; j++)//a~z
        {
            char tmpChar = j;
            std::string alphabet;
            alphabet += tmpChar;
            myInputWord.insert(i, alphabet);
            if(myInputWord == inputDictionaryWord)
                result = true;
            myInputWord.erase(i,1);
        }
        myInputWord = inputWord;
    }
    return result;
}

bool SpellChecker::reArrangeWord(const std::string& inputDictionaryWord, const std::string& inputWord)
{
    bool result = false;
    if(hasSameElements(inputDictionaryWord, inputWord))
    {
        std::string charHolder;
        std::string tmpString;
        std::string myInputWord = inputWord;
        for(int i = 0; i <inputWord.size(); i ++)
        {
            charHolder = inputWord[i];
            myInputWord.erase(i,1);
            tmpString = myInputWord;
            for(int j=0; j < tmpString.size(); j++)
            {
                tmpString.insert(j,charHolder);
                if(tmpString == inputDictionaryWord)
                    result =  true;
                tmpString.erase(j,1);
            }
            myInputWord = inputWord;
        }
    }
    return result;
}
//
bool SpellChecker::itContains(const std::string& inputDictionaryWord, const std::string& inputWord)
{
    bool result = false;
    std::string myDictionaryWord = inputDictionaryWord;
    std::string myWord = inputWord;
    for(int dicW = 0; dicW < myDictionaryWord.size(); dicW++)
    {
        for(int mW = 0; mW < myWord.size(); mW++)
        {
            if(myDictionaryWord[dicW] == myWord[mW])
            {
                myDictionaryWord.erase(dicW,1);
                myWord.erase(mW,1);
                dicW--;
                mW = (int)myWord.size();
            }
        }
    }
    if(myWord.size() == 0) result = true;
    if(result)
    {
        std::string temp;
        for(int i = 0; i < inputDictionaryWord.size(); i ++)
        {
            if(inputDictionaryWord[i] != myDictionaryWord[0])
                temp += inputDictionaryWord[i];
        }
        if(temp == inputWord)
            result =  true;
        else
            result = false;
    }
    return result;
}
//
//
bool SpellChecker::hasSameElements(const std::string &inputDictionaryWord, const std::string &inputWord)
{
    bool result = false;
    std::string myDictionaryWord = inputDictionaryWord;
    std::string myWord = inputWord;
    for(int dicW = 0; dicW < myDictionaryWord.size(); dicW++)
    {
        for(int mW = 0; mW < myWord.size(); mW++)
        {
            if(myDictionaryWord[dicW] == myWord[mW])
            {
                myDictionaryWord.erase(dicW,1);
                myWord.erase(mW,1);
                dicW--;
                mW = (int)myWord.size();
            }
        }
    }
    if(myWord.size() == 0)
        result = true;
    return result;
}
