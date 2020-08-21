//  main.cpp
//  SpellCheck
//
//  Created by Kyo on 10/18/19.
//  Copyright © 2019 Kyo. All rights reserved.
#include <iostream>
#include "SpellChecker.hpp"
using namespace std;
int main()
{
    std::string strDictionary = "dictionary.txt";
    std::string strText = "Check_it.txt";
    SpellChecker mySpellChecker(strDictionary);
    mySpellChecker.CheckWithVector(strText);      //it will create textfile
    //mySpellChecker.CheckWithSet(strText);         //it will create textfile
    //mySpellChecker.CheckWithUnorderedset(strText);//it will create textfile
    return 0;
}
