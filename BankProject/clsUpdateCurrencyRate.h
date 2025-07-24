#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsCurrency.h"
class clsUpdateCurrencyRate : protected clsScreen
{
private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }
    static float _ReadRate() {
        cout << "Enter New Rate : ";
        float NewRate = clsInputValidate::ReadFloatNumber();
        return NewRate;
    }
public:
	static void ShowUpdateCurrencyScreen() {
        _DrawSreenHeader("\t  Update Currency Screen");

        string CurrencyCode = clsInputValidate::ReadWord("Please Enter Currncy Code ? ");

        while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
            cout << "Invalid Currency code ";
            CurrencyCode = clsInputValidate::ReadWord("Choose another one ? ");
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintCurrency(Currency);

        cout << "\n\nAre you want to update the rate of this currency? (Y/N)? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y') {
            cout << "\n\nUpdate Currency Rate:\n__________________\n";
           
            Currency.UpdateRate(_ReadRate());
            cout << "Currecy Rate Updated successfuly :-)\n\n";
            _PrintCurrency(Currency);

        }
        else {
            cout << "\n\nOpreation cancelled.\n";
        }

	}
};

