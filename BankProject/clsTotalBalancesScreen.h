#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsTotalBalancesScreen : protected clsScreen
{
private:
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {

        cout <<left<<setw(25)<<"" << "| " << setw(15) << left << Client.GetAccoutNumber();
        cout << "| " << setw(40) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.GetAccoutBalance();
    }

public:

	static void ShowTotalBalancesScreen() {


        vector<clsBankClient> vClients = clsBankClient::GetClinetsList();

        string Title = "\t  Total Balances";
        string SubTitle = "\t  (" + to_string(vClients.size()) + ") Client(s).";

		_DrawSreenHeader(Title, SubTitle);

        double TotalBalances = 0;

        cout << endl;
        cout << left << setw(25) << "" <<"_______________________________________________________";
        cout << "_____________\n"
            << endl;

        cout << left << setw(25) << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n" << left << setw(25) << "" << "_______________________________________________________";
        cout << "_____________\n"
            << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
        {
            TotalBalances = clsBankClient::GetTotalBalances();
            for (clsBankClient& C : vClients)
            {
                _PrintClientRecordBalanceLine(C);
                cout << endl;
            }
        }
       
  cout << "\n" << left << setw(25) << "" << "_______________________________________________________";
        cout << "_____________\n";

        
            cout <<"\n" << setw(8) << left << "" << "\t\t\t\t\t     Total Balances = " << TotalBalances << endl;
        cout << setw(8) << left << "" << "\t\t\t\t  ( " << clsUtil::NumberToText(TotalBalances) << ")" << endl;

	}

};

