#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsString.h"

using namespace std;

class clsUtil
{
public:
    enum enCharType
    {
        SmallLetter = 1,
        CapitalLetter = 2,
        Digit = 3,
        MixChars = 4,
        SpecialCharacter = 5,

    };

    static void Srand()
    {
        // Seeds The random number generator in C++, called only once.
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int From, int To)
    {
        int RandomNum = rand() % (To - From + 1) + From;
        return RandomNum;
    }

    static char GetRandomCharacter(enCharType CharacterType)
    {
        // updated this method to accept mixchars
        if (CharacterType == MixChars)
        {
            // Capital/Samll/Digits only
            CharacterType = (enCharType)RandomNumber(1, 3);
        }

        switch (CharacterType)
        {
        case enCharType::SmallLetter:
            return char(RandomNumber(97, 122));

        case enCharType::CapitalLetter:
            return char(RandomNumber(65, 90));

        case enCharType::SpecialCharacter:
            return char(RandomNumber(33, 47));

        case enCharType::Digit:
            return char(RandomNumber(48, 57));
        default:
            return char(RandomNumber(65, 90));
        }
    }

    static string GenerateWord(enCharType CharType, int Length)
    {
        string Word = "";

        for (int i = 0; i < Length; i++)
        {
            Word += GetRandomCharacter(CharType);
        }

        return Word;
    }

    static string GenerateKey(enCharType Type = enCharType::CapitalLetter)
    {
        string key = "";

        key += GenerateWord(Type, 4) + "-";
        key += GenerateWord(Type, 4) + "-";
        key += GenerateWord(Type, 4) + "-";
        key += GenerateWord(Type, 4);

        return key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType Type = enCharType::CapitalLetter)
    {
        for (int i = 0; i < NumberOfKeys; i++)
        {
            cout << "Key[" << i << "] = " << GenerateKey(Type) << endl;
        }
    }

    static void Swap(int& num1, int& num2)
    {
        int Temp = num1;
        num1 = num2;
        num2 = Temp;
    }

    static void Swap(double& num1, double& num2)
    {
        double Temp = num1;
        num1 = num2;
        num2 = Temp;
    }
    static void Swap(string& S1, string& S2)
    {
        string Temp = S1;
        S1 = S2;
        S2 = Temp;
    }

    static void Swap(clsDate& Date1, clsDate& Date2)
    {
        clsDate Temp = Date1;
        Date1 = Date2;
        Date2 = Temp;
    }

    static void ShuffleArray(int Array[100], int ArrayLength)
    {
        for (int i = 0; i < ArrayLength; i++)
        {
            Swap(Array[RandomNumber(1, ArrayLength) - 1], Array[RandomNumber(1, ArrayLength) - 1]);
        }
    }

    static void ShuffleArray(string Array[100], int ArrayLength)
    {
        for (int i = 0; i < ArrayLength; i++)
        {
            Swap(Array[RandomNumber(1, ArrayLength) - 1], Array[RandomNumber(1, ArrayLength) - 1]);
        }
    }
    static void FillArrayWithRandomNumbers(int arr[100], int ArrayLength, int From, int To)
    {

        for (int i = 0; i < ArrayLength; i++)
        {
            arr[i] = RandomNumber(From, To);
        }
    }

    static void FillArrayWithRandomWords(string arr[100], int ArrayLength, enCharType Type, int WordLength)
    {

        for (int i = 0; i < ArrayLength; i++)
        {
            arr[i] = GenerateWord(Type, WordLength);
        }
    }

    static void FillArrayWithRandomKeys(string arr[100], int ArrayLength, enCharType Type)
    {

        for (int i = 0; i < ArrayLength; i++)
        {
            arr[i] = GenerateKey(Type);
        }
    }

    static string Tabs(int Length)
    {
        string Result = "";
        for (int i = 0; i < Length; i++)
        {
            Result += "\t";
        }

        return Result;
    }

    static string EncryptText(string Text, short EncryptionKey = 2)
    {

        for (int i = 0; i < Text.length(); i++)
        {

            Text[i] = char((int)Text[i] + EncryptionKey);
        }
        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey = 2)
    {
        for (int i = 0; i < Text.length(); i++)
        {

            Text[i] = char((int)Text[i] - EncryptionKey);
        }
        return Text;
    }
    static string NumberToText(int Number)
    {
        if (Number == 0)
        {
            return "";
        }
        else if (Number > 0 && Number < 20)
        {
            string arr[] = {
                "",
                "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

            return arr[Number] + " ";
        }

        else if (Number > 20 && Number < 99)
        {
            string arr[] = {
                "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

            return arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        else if (Number > 99 && Number < 200)
        {
            return "One Hunderd " + NumberToText(Number % 100);
        }

        else if (Number > 200 && Number < 1000)
        {
            return NumberToText(Number / 100) + " Hunderds " + NumberToText(Number % 100);
        }

        else if (Number > 999 && Number < 2000)
        {
            return "One Thousend " + NumberToText(Number % 1000);
        }

        else if (Number >= 2000 && Number <= 999999)

        {
            return NumberToText(Number / 1000) + "Thousends " + NumberToText(Number % 1000);
        }

        else if (Number >= 1000000 && Number <= 1999999)
        {
            return "One Million " + NumberToText(Number % 1000000);
        }

        else if (Number >= 2000000 && Number <= 999999999)
        {
            return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }
        else if (Number >= 1000000000 && Number <= 1999999999)
        {
            return "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }
    }
};