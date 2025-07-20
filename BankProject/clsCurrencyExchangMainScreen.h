#pragma once
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
//#include "clsUpdateCurrencyRate.h"
//#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangMainScreen : protected clsScreen
{
private:
    enum enCurrencyMenueOptions {
        eListCurrencies = 1,
        eFindCurrency = 2,
        eUpdateCurrency = 3,
        eCurrencyCalculator = 4,
        eMainMenue = 5

    };

    static short _ReadCurrencyExhangeMenueOption() {

        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _GoBackToCurrenciesMenue() {

        cout << setw(37) << left << "\n\tPress any key to go back to Currencies Menue...\n";

        system("pause>0");
        ShowCurrenciesMenue();
    }

    static void _ShowListCurrenciesScreen() {
        clsCurrenciesListScreen::ShowCurrenciesList();
    }
    static void _ShowCurrencyCalculatorScreen() {
        cout << "Show Currency Calculator Screen will be here..\n";
        //clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }
    static void _ShowFindCurrencyScreen() {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    static void _ShowUpdateCurrencyScreen() {
         cout << "Show Update Currency Screen will be here..\n";
       // clsUpdateCurrencyRate::ShowUpdateCurrencyScreen();
    }

    static void _PerfromCurrencyMenuOption(enCurrencyMenueOptions CurrencyMenueOption)
    {
        switch (CurrencyMenueOption)
        {
        case enCurrencyMenueOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenue();
            break;

        case enCurrencyMenueOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenue();
            break;

        case enCurrencyMenueOptions::eListCurrencies:

            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrenciesMenue();
            break;

        case enCurrencyMenueOptions::eUpdateCurrency:
            system("cls");
            _ShowUpdateCurrencyScreen();
            _GoBackToCurrenciesMenue();
            break;

        case enCurrencyMenueOptions::eMainMenue:
            //do nothing here the main screen will handle it :-) ;
            break;


        }
    }

public:
    static void ShowCurrenciesMenue() {
        system("cls");

        _DrawSreenHeader("   Currecny Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t  Currecny Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";

        cout << setw(37) << left << "" << "\t[1 ] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2 ] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3 ] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4 ] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5 ] Main Menue.\n";

        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromCurrencyMenuOption((enCurrencyMenueOptions)_ReadCurrencyExhangeMenueOption());
    }

};

