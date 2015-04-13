#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;


struct Words {
    string word;
    int counts = 1;
    bool topTen = false;
};

struct Line{
    Words commonWords[50];
    int lineLength;
};

Line findWords(string output)
{
    string word;
    Line sentence;
    sentence.lineLength = 0;
    istringstream iss (output);
    while(iss >> word)
    {
        sentence.commonWords[sentence.lineLength].word = word;

        sentence.lineLength++;
    }
    return sentence;
}

Words* DoubleArray(Words pastArray[], int arraySize)
{
    Words *newArray = new Words[arraySize * 2];
    for(int i = 0; i< arraySize*2;i++)
    {
        if(i< arraySize)
            {
                newArray[i] = pastArray[i];
            }
    }
    delete[] pastArray;
    pastArray = newArray;
    return pastArray;
}

bool checkCommonWords(string wordList[], Words NewWord)
{
    bool isUnique = true;
    for(int i = 0; i<50;i++)
    {
        if(NewWord.word == wordList[i])
        {
            isUnique = false;
        }
    }
    return isUnique;
}

bool checkUniqueWords(Words nonCommonWords[], int NumberOfUniqueWords, Words NewWord)
{
    bool isUnique = true;
    for(int i=0;i<NumberOfUniqueWords;i++)
    {
        if(nonCommonWords[i].word == NewWord.word)
        {
            isUnique = false;
            nonCommonWords[i].counts++;
        }
    }
    return isUnique;
}



int main(int argc,char* argv[])
{
    string MostCommonWords[] = {"the", "you", "one", "be", "do", "all", "to", "at", "would", "of",

"this", "there", "and", "but", "their", "a", "his", "what", "in", "by", "so", "that",

"from", "up", "have", "they", "out", "i", "we", "if", "it", "say", "about", "for", "her",

"who", "not", "she", "get", "on", "or", "which", "with", "an", "go", "he", "will", "me", "as",

"my"};
    //string token;
    string line;
    string word;
    int doubled = 0;
    int NumberOfUniqueWords = 0;
    int sizeOf = 100;
    int topTen = atoi(argv[2]);
   // int topTen = 10;
    Words *uniqueWordList = new Words[sizeOf];
    ifstream myFile(argv[1]);
    //ifstream myFile("Hemingway_edit.txt");
    if(myFile.is_open())
    {
        while(getline(myFile, line))
        {
            Line SplitSentence = findWords(line);
            for (int i=0;i<SplitSentence.lineLength;i++)
            {
                if((checkUniqueWords(uniqueWordList,NumberOfUniqueWords,SplitSentence.commonWords[i]))==true)
                {
                    uniqueWordList[NumberOfUniqueWords] = SplitSentence.commonWords[i];
                    NumberOfUniqueWords++;
                    if(NumberOfUniqueWords == sizeOf)
                    {
                        uniqueWordList = DoubleArray(uniqueWordList,sizeOf);
                        doubled++;
                        sizeOf = sizeOf * 2;

                    }
                }
            }
        }
        myFile.close();

    }
   // myFile.close;

    Words maximumOccurences[topTen];
    int locationOfUnique[topTen];

    for(int i = 0; i< topTen;i++)
    {
        for(int j =0;j<NumberOfUniqueWords;j++)
        {
            if(uniqueWordList[j].counts > maximumOccurences[i].counts)
            {
                if(checkCommonWords(MostCommonWords, uniqueWordList[j]) == true)
                {
                    if(uniqueWordList[j].topTen == false)
                    {
                        maximumOccurences[i] = uniqueWordList[j];
                        locationOfUnique[i] = j;
                    }
                }
            }
        }
        uniqueWordList[locationOfUnique[i]].topTen = true;
    }
    int totalUncommonWords = 0;
    int NumberOfUnCommonwords = 0;
    for(int i=0;i < topTen;i++)
    {
        cout << maximumOccurences[i].counts << " - " << maximumOccurences[i].word << endl;
    }

    cout << '#' <<endl;
    cout << "Array doubled: " << doubled <<endl;
    cout << '#' << endl;
    for(int i=0; i<NumberOfUniqueWords;i++)
    {
        if(checkCommonWords(MostCommonWords, uniqueWordList[i])==true)
        {
            NumberOfUnCommonwords++;
            totalUncommonWords = totalUncommonWords + uniqueWordList[i].counts;
        }
    }


   // cout << "Unique non-common words: " << NumberOfUniqueWords <<endl;
  // cout << '#' << endl;
    cout << "Unique non-common words: " << NumberOfUnCommonwords << endl;
    cout << '#' << endl;
    cout << "Total non-common words: " << totalUncommonWords << endl;

   /* for(int i =0;i<200;i++)
    {
        cout << uniqueWordList[i].word << " " << uniqueWordList[i].counts << endl;
    }
*/













   /* ifstream myFile("Hemingway_edit.txt");
    //ifstream myFile(argv[1]);
    string Output;
    Words uniqueWords[100]; //unique words array
    string commonWords[] = {"the", "and"};
    int len = 0; //counter
    int arrSize = 100; //array size variable


    if (myFile.is_open())
    {
        while (getline(myFile,Output))
        {

            istringstream iss(Output); //variable used for the getline to split file.
            Words currentWord; //New struct variable to store file data.
            string token;

            while (getline(iss, token, ' '))
            {
                //token = currentWord.word;
                currentWord.word = token;
                //still counting \n as word

                bool foundWord = false;

                for(int i=0;i<len;i++)
                {
                    if(currentWord.word == uniqueWords[i].word)
                    {//check if word is in array
                        //cout << "hello" << endl;
                        uniqueWords[i].counts++; //increase count of that word
                        foundWord = true;
                    }
                }

                if(foundWord == false) {
                        //cout << "hello" << endl;
                    uniqueWords[len] = currentWord;
                    len++;
                }

                if(len == arrSize)// see if you need to double array
                {  //double array
                   // *ArrayDynamicAllocation(uniqueWords[arrSize], arrSize, 1);
                    arrSize = arrSize * 2;
                }

            }

        }
    }
    else
        cout << "unable to open file" << endl;


        //for output don't include first 50 array points to get rid of common words so for i>50
    return 0;

    //printing
    /*for(int i =0;i<len;i++)
    {
        bool canPrint = true;

        for(int j=0;j<50;j++)
        {
            if(uniqueWords[i].word == commonWords[j])
                canPrint = false;
        }
        if(canPrint)
            cout << uniqueWords[i].word << " ";
    }
    cout << endl;*/

}



