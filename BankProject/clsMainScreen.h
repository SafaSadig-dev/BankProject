#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsAddNewClientScreen.h"
#include "clsClientListScreen.h"
#include "clsInputValidate.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen .h"
#include "clsLoginRegisterScreen.h"
#include "Global.h"
#include "clsCurrencyExchangMainScreen.h"


using namespace std;
class clsMainScreen : protected clsScreen
{
private:

    enum enMainMenueOptions
    {
        eListClients = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eShowTransactionsMenue = 6,
        eManageUsers = 7,
        eLoginRegister= 8,
        eCurrencyExchange =9 ,
        eLogout = 10,
        eExit = 11
    };

    static short _ReadMainMenueOption()
    {

        cout << setw(37) << left <<"" << "Choose what do you want to do? [1 to 11]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 11, "Enter Number between 1 to 11? ");
        return Choice;
    }

    static void _ShowAddNewClientsScreen()
    {
        //cout << "\nAdd New Client Screen Will be here...\n";

        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
       // cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        //cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        //cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        //cout << "\nTransactions Menue Will be here...\n";
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::ShowMangeUsersScreen();
    }

   /* static void _ShowEndScreen()
    {
        cout << "\nEnd Screen Will be here...\n";
    }*/
    static void _Logout() {
        CurrentUser = clsUser::Find("", "");

        // if you write this code : Circular Refernce will appear
        //clsLoginScreen::ShowLoginScreen();  

        // then it will go back to main function
    }
    static void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        //  cout << "\nClient List Screen Will be here...\n";
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowLoginRegisterScreen() {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }
    static  void _ShowEndScreen()
    {
       _DrawSreenHeader("\t   Program Ends :-)");
        exit(0);
    }
    static void _ShowCurrencyMainScreen() {
        //cout << "\nCurrency Main Screen Will be here...\n";
        clsCurrencyExchangMainScreen::ShowCurrenciesMenue();
    }

    static void
        _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eExit:
            system("cls");
            _Logout();
            _ShowEndScreen();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _GoBackToMainMenue();
            break;
        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eLogout:
            system("cls");
            //_ShowEndScreen();
            _Logout();
            break;

        case enMainMenueOptions::eLoginRegister:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();

            break;

        case enMainMenueOptions::eCurrencyExchange:
            system("cls");
            _ShowCurrencyMainScreen();
             _GoBackToMainMenue();
            break;
                

        }
    }

public:
    static void ShowMainMenue()
    {
        system("cls");
        _DrawSreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";

        cout << setw(37) << left << "" << "\t[1 ] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2 ] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3 ] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4 ] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5 ] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6 ] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7 ] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8 ] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9 ] Currency Exchange.\n";

        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "\t[11] Exist.\n";

        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }
};
