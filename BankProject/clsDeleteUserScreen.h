#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User) {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FristName();
        cout << "\nLastName    : " << User.LastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email();
        cout << "\nPhone       : " << User.Phone();
        cout << "\nUser Name   : " << User.GetUserName();
        cout << "\nPassword    : " << User.GetPassword();
        cout << "\nPermissions : " << User.GetPermissions();
        cout << "\n___________________\n";
    }

public:
	static void ShowDeleteUserScreen() {
        _DrawSreenHeader("\t   Delete User Screen");

        //-----------------
        string UserName = clsInputValidate::ReadWord("Please Enter User Name ? ");
        while (!clsUser::IsUserExist(UserName))
        {
            UserName = clsInputValidate::ReadWord("\nUser Name is not found, choose another one: ");
        }

        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);

        char Answer = 'N';
        Answer = clsInputValidate::ReadChar("Are you sure you want to delete this user? (Y/N) ? ");
        if (tolower(Answer) == 'y')
        {
            if (User.Delete())
            {
                cout << "\nUser delete successfuly.\n";
                _PrintUser(User);
            }
            else
            {
                cout << "\nErorr user was not deleted.\n";
            }
        }
        else {
            cout << "Operation cancelled.";
        }
    }
	
};

