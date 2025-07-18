#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsCurrency.h"

class clsFindCurrencyScreen : clsScreen
{
    
private:
    enum enFindBy {
        eByCode=1,
        eByCountry = 2
    };
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
    static void _ShowResults(clsCurrency Currency1) {
        if (Currency1.IsEmpty())
        {
            cout << "\nCurrency Is Not Found!\n";
        }
        else
        {
            cout << "\nCurrency Is  Found :-)\n";
            _PrintCurrency(Currency1);
        }
    }

    

public:
	static void ShowFindCurrencyScreen() {
		_DrawSreenHeader("\t Find Currency Screen");

        cout << "Find By: [1] Code or [2] Country ? ";
        short Answer = clsInputValidate::ReadIntNumberBetween(1, 2);

        bool CurrencyFoud = false;
        
        if (Answer == enFindBy::eByCode) {
            string CurrencyCode = clsInputValidate::ReadWord("\nPlease Enter Currency Code : ");
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else {
            string Country = clsInputValidate::ReadWord("\nPlease Enter Country : ");
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);
         

        }
       
       

       



	}
};

