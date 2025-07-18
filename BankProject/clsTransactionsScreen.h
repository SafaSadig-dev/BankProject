#pragma once
#include "clsScreen.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
class clsTransactionsScreen : protected clsScreen
{
private:

    enum enTransactionsMenueOptions
    {
        eDeposit = 1,
        eWithdraw = 2,
        eShowTotalBalance = 3,
        eTransfer = 4,
        eTransferLog = 5,
        eShowMainMenue = 6


    };

    static short _ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _ShowTotalBalancesScreen() {
       //cout << "\nShow Total Balances Screen Will be here...\n";
        clsTotalBalancesScreen::ShowTotalBalancesScreen();

    }

    static void _ShowDepositScreen() {
        //cout << "\nShow Deposit Screen Will be here...\n";
        clsDepositScreen::ShowDepositScreen();

    }

    static void _ShowWithDrawScreen() {
       // cout << "\nShow WithDraw Screen Will be here...\n";
        clsWithdrawScreen::ShowWithdrawScreen();

    }

    static void _GoBackToTransactionsMenue()
    {
        cout << setw(37) << left << "\n\tPress any key to go back to Transactions Menue...\n";

        system("pause>0");
        ShowTransactionsMenue();
    }
    static void _ShowTransferScreen() {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferLogScreen() {
        clsTransferLogScreen::ShowTransferLogScreen();
    }



    static void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
    {
        switch (TransactionMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw:
        {
            system("cls");
            _ShowWithDrawScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowTotalBalance:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;


        case enTransactionsMenueOptions::eTransferLog:
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
        case enTransactionsMenueOptions::eShowMainMenue:
        {
            
           //do nothing here the main screen will handle it :-) ;
            // if you do this , you will get error : 
            // clsMainScreen::ShowMainMenue();


        }
        }
    }

public:
	static void ShowTransactionsMenue() {

        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;// this will exit the function and it will not continue
        }
        system("cls");
		_DrawSreenHeader("\t   Transactions Screen");

        cout<< setw(37) << left << ""<< "===========================================\n";
        cout<< setw(37) << left << ""<< "\t\tTransactions Menue Screen\n";
        cout<< setw(37) << left << ""<< "===========================================\n";
        cout<< setw(37) << left << ""<< "\t[1] Deposit.\n";
        cout<< setw(37) << left << ""<< "\t[2] Withdraw.\n";
        cout<< setw(37) << left << ""<< "\t[3] Total Balances.\n";
        cout<< setw(37) << left << ""<< "\t[4] Transfer.\n";
        cout << setw(37)<< left<< ""<< "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";


        cout<< setw(37) << left << ""<< "===========================================\n";

        PerfromTranactionsMenueOption((enTransactionsMenueOptions)_ReadTransactionsMenueOption());

	}
};

