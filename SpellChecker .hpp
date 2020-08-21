//
//  SpellCheck.hpp
//  SpellCheck
//
//  Created by Kyo on 10/18/19.
//  Copyright © 2019 Kyo. All rights reserved.
//

#ifndef SpellChecker_hpp
#define SpellChecker_hpp
#include <string>
#include <unordered_set>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
class SpellChecker
{
    public:
    SpellChecker(); //Default
    SpellChecker(const std::string& inputDictionary);
    ~SpellChecker(); //Destroctor
    void CheckWithVector(const std::string& inputText);
    void CheckWithSet(const std::string& inputText);
    void CheckWithUnorderedset(const std::string& inputText);
    
    private:
    
    int lengthDifferenceOfWord(const std::string& inputDictionaryWord, const std::string& inputWord);
    bool itContains(const std::string& inputDictionaryWord, const std::string& inputWord);
    bool reArrangeWord(const std::string& inputDictionaryWord,const std::string& inputWord);
    bool hasSameElements(const std::string& inputDictionaryWord,const std::string& inputWord);
    bool reAssembleWord(const std::string& inputDictionaryWord,const std::string& inputWord);
    

    //

    //----checkWithVector-------------
    std::vector<std::string> vectorDictionary;
    std::vector<std::string> vectorInputText;
    std::vector<std::string> vectorWrongWords;
    std::vector<char> vectorIgnoreWords;
    std::vector<std::string> vectorAnswers;
    bool isWrongWordWithVector(const std::string& inputWord);
    void SetIgnoreWordsWithVector();
    void SetDictionaryWithVector();
    void ReadFileWithVector(const std::string& inputFile);
    std::string cleanWordWithVector(const std::string& inputString); //take off the special chars, make everything to lowcase
    void InsertToFindWithVector(const std::string& inputWord);         //add a letter
    void SwitchToFindWithVector(const std::string& inputWord);         //switch the existing letters
    void RemoveToFindWithVector(const std::string& inputWord);         //remove a letter
    void ReplaceToFindWithVector(const std::string& inputWord);        //replace a letter
    void GetTheAnswersWithVector(const std::string& inputWord);
    void CreateFileWithVector();
    
    //--------------------------------
    //----checkWithSet-------------
    std::set<std::string> setDictionary;
    std::set<std::string> setInputText;
    std::set<std::string> setWrongWords;
    std::set<char> setIgnoreWords;
    std::set<std::string> setAnswers;
    bool isWrongWordWithSet(const std::string& inputWord);
    void SetIgnoreWordsWithSet();
    void SetDictionaryWithSet();
    void ReadFileWithSet(const std::string& inputFile);
    std::string cleanWordWithSet(const std::string& inputString); //take off the special chars, make everything to lowcase
    void InsertToFindWithSet(const std::string& inputWord);         //add a letter
    void SwitchToFindWithSet(const std::string& inputWord);         //switch the existing letters
    void RemoveToFindWithSet(const std::string& inputWord);         //remove a letter
    void ReplaceToFindWithSet(const std::string& inputWord);        //replace a letter
    void GetTheAnswersWithSet(const std::string& inputWord);
    void CreateFileWithSet();

    //--------------------------------
    //----checkWithUnorderedset-------------
    std::unordered_set<std::string> unorderedDictionary;
    std::unordered_set<std::string> unorderedInputText;
    std::unordered_set<std::string> unorderedWrongWords;
    std::unordered_set<char> unorderedIgnoreWords;
    std::unordered_set<std::string> unorderedAnswers;
    bool isWrongWordWithUnorderedset(const std::string& inputWord);
    void SetIgnoreWordsWithUnorderedset();
    void SetDictionaryWithUnorderedset();
    void ReadFileWithUnorderedset(const std::string& inputFile);
    std::string cleanWordWithUnorderedset(const std::string& inputString); //take off the special chars, make everything to lowcase
    void InsertToFindWithUnorderedset(const std::string& inputWord);         //add a letter
    void SwitchToFindWithUnorderedset(const std::string& inputWord);         //switch the existing letters
    void RemoveToFindWithUnorderedset(const std::string& inputWord);         //remove a letter
    void ReplaceToFindWithUnorderedset(const std::string& inputWord);        //replace a letter
    void GetTheAnswersWithUnorderedset(const std::string& inputWord);
    void CreateFileWithUnorderedset();

    //--------------------------------
    
    std::string myInputDictionaryFile_;
    std::string strTextOutcome;
    float duration_;
};

#include "SpellChecker.cpp"
#endif /* SpellCheck_hpp */
