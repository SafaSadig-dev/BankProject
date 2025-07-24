#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsCurrency.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

    static void _PrintCurrencyCard(clsCurrency Currency, string Title)
    {
        cout << "\n"<< Title <<"\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }

    static void _PrintResult(float Amount, float AmountAfterConvert, string CurrencyCode1, string CurrencyCode2) {
        cout<<endl << Amount << " " << CurrencyCode1 << " = " << AmountAfterConvert
            << " " << CurrencyCode2 << endl;
    }


    static clsCurrency _GetCurrency(string msg) {
        string CurrencyCode = clsInputValidate::ReadWord(msg);

        while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
            cout << "Invalid Currency code ";
            CurrencyCode = clsInputValidate::ReadWord("Choose another one ? ");
        }

        return clsCurrency::FindByCode(CurrencyCode);
    }

    static void _PrintCaculationResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
    {
        _PrintCurrencyCard(CurrencyFrom, "Convert From :");

        if (CurrencyFrom.CurrencyCode() == CurrencyTo.CurrencyCode()) // sdg to sdg
        {
            _PrintResult(Amount, Amount, CurrencyFrom.CurrencyCode(), CurrencyTo.CurrencyCode());

        }

        float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);
        _PrintResult(Amount, AmountInUSD, CurrencyFrom.CurrencyCode(), "USD");


        if (CurrencyTo.CurrencyCode() == "USD") {
            return;
        }

        cout << "\nConverting USD to \n";
        _PrintCurrencyCard(CurrencyTo, "To :");
       float  AmountInCurrency2 = CurrencyFrom.ConvertToOtherCurrency(Amount,CurrencyTo);
        _PrintResult(Amount, AmountInCurrency2, CurrencyFrom.CurrencyCode(), CurrencyTo.CurrencyCode());



    }
public:
	static void ShowCurrencyCalculatorScreen() {
        char Countinue = 'n';

        do {

            system("cls");
            _DrawSreenHeader("\t Currnecy Calculator Screen");


            clsCurrency CurrencyFrom = _GetCurrency("Please Enter Currency1 Code :\n");
            clsCurrency CurrencyTo = _GetCurrency("Please Enter Currency2 Code :\n");

            cout << "\nEnter Amount to exchange : ";
            float Amount = clsInputValidate::ReadFloatNumber();
            float AmountAfterConvert = 0;

            _PrintCaculationResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\nDo You want to perform another Opreation? (Y/N) ? ";
            cin >> Countinue;
        }
        while (Countinue == 'y' || Countinue == 'Y');

       

	}
};

