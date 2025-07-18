#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

#include "clsInputValidate.h"
class clsFindClientScreen : protected clsScreen
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

public:
    static void ShowFindClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;// this will exit the function and it will not continue
        }


        _DrawSreenHeader("\t   Find Client Screen");


        string AccountNumber = clsInputValidate::ReadWord("Please Enter Account Number? ");
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadWord("\nAccount number is not found, choose another one: ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (!Client.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
            _PrintClientCard(Client);


        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }



    }

};

