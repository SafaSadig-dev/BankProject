#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsBankClient.h"

using namespace std;

class clsClientListScreen : protected clsScreen
{
private:
    static void _PrintClientRecordLine(clsBankClient Client)
    {
      
        cout << setw(8) <<"" << "| " << left << setw(15) << Client.GetAccoutNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(12) << Client.Phone();
        cout << "| " << left << setw(20) << Client.Email();
        cout << "| " << left << setw(10) << Client.GetPinCode();
        cout << "| " << left << setw(12) << Client.GetAccoutBalance();
    }

public:
    static void ShowClientsList()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pListClients))
        {
            return;// this will exit the function and it will not continue
        }

        vector<clsBankClient> vClients = clsBankClient::GetClinetsList();

        string Title = "\t   Client List Screen";
        string SubTitle = "\t  (" + to_string(vClients.size()) + ") Client(s).";

        _DrawSreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
            << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
            << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient& Client : vClients)
            {

                _PrintClientRecordLine(Client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
            << endl;
    }
};