#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsDeleteClientScreen : protected clsScreen
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
	static void ShowDeleteClientScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;// this will exit the function and it will not continue
        }
		_DrawSreenHeader("\t   Delete Client Screen");

        //-----------------
        string AccoutNumber = clsInputValidate::ReadWord("Please Enter Account Number ? ");
        while (!clsBankClient::IsClientExist(AccoutNumber))
        {
            AccoutNumber = clsInputValidate::ReadWord("\nAccount number is not found, choose another one: ");
        }

        clsBankClient Client = clsBankClient::Find(AccoutNumber);
        _PrintClientCard(Client);

        char Answer = 'N';
        Answer = clsInputValidate::ReadChar("\nAre you sure you want to delete this client? (Y/N) ? ");
        if (tolower(Answer) == 'y')
        {
            if (Client.Delete())
            {
                cout << "\nClient delete successfuly.\n";
                _PrintClientCard(Client);
            }
            else
            {
                cout << "\nErorr client was not deleted.\n";
            }
        }
        else {
            cout << "\nOperation was cancelled.\n";

        }
	}

}; 

