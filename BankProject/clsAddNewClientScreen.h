#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen
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


    //static void _AddNewClients()
    //{
    //    char AddMore = 'Y';
    //    do
    //    {
    //        cout << "Adding New Client:\n\n";

    //        _AddNewClient();
    //        cout << "\n do you want to add more clients? Y/N? ";

    //        cin >> AddMore;

    //    } while (toupper(AddMore) == 'Y');
    //}

public:
    static void ShowAddNewClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawSreenHeader("\t    Add new Client Screen");

        //-----------
        string AccountNumber = clsInputValidate::ReadWord("Please Enter Account Number? ");
        while (clsBankClient::IsClientExist(AccountNumber))
        {

            AccountNumber = clsInputValidate::ReadWord("Account Number is already use, Choose another one? ");
        }

        clsBankClient NewClient = clsBankClient::GetNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);
        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClientCard(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;
        }
        }
    }
};
