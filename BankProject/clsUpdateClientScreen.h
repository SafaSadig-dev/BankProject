#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _PrintClientCard(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FristName();
        cout << "\nLastName    : " << Client.LastName();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email();
        cout << "\nPhone       : " << Client.Phone();
        cout << "\nAcc. Number : " << Client.GetAccoutNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccoutBalance();
        cout << "\n___________________\n";
    }

    static void _ReadClientInfo(clsBankClient& Client)
    {
        Client.SetFristName(clsInputValidate::ReadWord("\nEnter FirstName: "));

        Client.SetLastName(clsInputValidate::ReadWord("\nEnter LastName: "));

        Client.SetEmail(clsInputValidate::ReadWord("\nEnter Email: "));

        Client.SetPhone(clsInputValidate::ReadWord("\nEnter Phone: "));

        Client.SetPinCode(clsInputValidate::ReadWord("\nEnter PinCode: "));

        cout << "\nEnter Account Balance: ";
        Client.SetAccoutBalance(clsInputValidate::ReadFloatNumber());
    }


public :
    static void ShowUpdateClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)) {
            return; // this will exit the function and it will not continue
        }

        _DrawSreenHeader("\t   Update Client Screen");

        string AccountNumber = clsInputValidate::ReadWord("\nPlease Enter client Account Number: ");
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadWord("\nAccount number is not found, choose another one: ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client);

        cout << "\nAre you sure you want to update this client y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";
            _ReadClientInfo(Client);
            clsBankClient::enSaveResults SaveResult = Client.Save();
            switch (SaveResult)
            {
            case clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClientCard(Client);
                break;
            }
            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            }

        }
    }
};

