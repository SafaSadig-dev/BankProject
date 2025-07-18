#pragma warning(disable : 4996)
#pragma once

#include <iostream>
#include "clsDate.h"
#include "clsString.h"
#include <limits>

using namespace std;
class clsInputValidate
{
public:
    static string ReadWord(string msg = "Please Enter a word ? ")
    {

        string Word = "";
        cout << msg;

        // getline(cin >> ws, Word); this line == 2 lines below

        cin >> ws; // delete white space in cin
        getline(cin, Word);

        return Word;
    }

    static char ReadChar(string msg = "Please Enter a char ? ")
    {
        char character = ' ';
        cout << msg;
        cin >> character;

        return character;
    }
    static bool IsNumberBetween(int num, int From, int To)
    {
        return (num >= From && num <= To);
    }

    static bool IsNumberBetween(short num, short From, short To)
    {
        return (num >= From && num <= To);
    }

    static bool IsNumberBetween(double num, double From, double To)
    {
        return (num >= From && num <= To);
    }

    static bool IsNumberBetween(float num, float From, float To)
    {
        return (num >= From && num <= To);
    }

    static bool IsDateBetween(clsDate Date, clsDate Date1, clsDate Date2)
    {
        clsDate::enDateCompare compare = clsDate::CompareDates(Date1, Date2);
        if ((compare == clsDate::enDateCompare::Before) || (compare == clsDate::enDateCompare::Equal))
        {
            return (clsDate::CompareDates(Date1, Date) != clsDate::Before) && ((clsDate::CompareDates(Date, Date2) != clsDate::After));
        }
        else
        {
            return (clsDate::CompareDates(Date2, Date) != clsDate::Before) && ((clsDate::CompareDates(Date, Date1) != clsDate::After));
        }
    }

    static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
    {
        int Number = 0;
        cin >> ws;
        cin >> Number;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << ErrorMessage;
            cin >> Number;
        }

        return Number;
    }

    static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
    {
        double Number = 0;
        cin >> Number;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << ErrorMessage;
            cin >> Number;
        }

        return Number;
    }

    static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
    {
        float Number = 0;
        cin >> Number;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << ErrorMessage;
            cin >> Number;
        }

        return Number;
    }

    static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
    {
        short Number = 0;
        cin >> Number;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << ErrorMessage;
            cin >> Number;
        }

        return Number;
    }

    static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, enter again:\n")
    {
        int Number = ReadIntNumber("Invalid Number, Enter again:\n");
        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadIntNumber("Invalid Number, Enter again:\n");
        }

        return Number;
    }

    static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, enter again:\n")
    {
        short Number = ReadIntNumber("Invalid Number, Enter again:\n");
        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadIntNumber("Invalid Number, Enter again:\n");
        }

        return Number;
    }

    static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, enter again:\n")
    {
        double Number = ReadDblNumber("Invalid Number, Enter again:\n");
        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadIntNumber("Invalid Number, Enter again:\n");
        }

        return Number;
    }

    static bool IsValidDate(clsDate Date)
    {
        return clsDate::IsValidDate(Date);
    }
};