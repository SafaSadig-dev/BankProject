#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen
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

    static void _ReadUserInfo(clsUser& User) {



        User.SetFristName(clsInputValidate::ReadWord("\nEnter FirstName: "));
        User.SetLastName(clsInputValidate::ReadWord("\nEnter LastName: "));
        User.SetEmail(clsInputValidate::ReadWord("\nEnter Email: "));
        User.SetPhone(clsInputValidate::ReadWord("\nEnter Phone: "));
        User.SetPassword(clsInputValidate::ReadWord("\nEnter Password: "));

        cout << "Enter Permissions : \n";
        User.SetPermission(_ReadPermissionToSet());
    }

    static int _ReadPermissionToSet() {
        char Answer = 'n';
        int Permission = 0;

        cout << "Do You want to give Full Access ? (Y/N) ? ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
            return -1;
        }


        cout << "\nDo you want to give access: \n";

        cout << "\nMange Users ? (Y/N) ? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y') {
            Permission += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nFind Client ? (Y/N) ? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y') {
            Permission += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransaction ? (Y/N) ? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y') {
            Permission += clsUser::enPermissions::pTranactions;
        }

        cout << "\nShow Client List ? (Y/N) ? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y') {
            Permission += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd new Client ? (Y / N) ? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y') {
            Permission += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client ? (Y/N) ? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y') {
            Permission += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client ? (Y/N) ? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y') {
            Permission += clsUser::enPermissions::pUpdateClients;
        }

        cout << "Login Register ? (Y/N) ? ";
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y') {
            Permission += clsUser::enPermissions::pShowLoginRegister;
        }
        return Permission;
    }
public:
	static void ShowUpdateUserScreen() {
        _DrawSreenHeader("\t   Update User Screen");

        string UserName = clsInputValidate::ReadWord("Please Enter User Name ? ");
        while (!clsUser::IsUserExist(UserName))
        {
            UserName = clsInputValidate::ReadWord("\nUser Name is not found, choose another one: ");
        }

        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);

        char Answer = 'N';
        Answer = clsInputValidate::ReadChar("Are you sure you want to update this user? (Y/N) ? ");
        if (tolower(Answer) == 'y')
        {


            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";

            _ReadUserInfo(User);

            clsUser::enSaveResults SaveResult = User.Save();

            switch (SaveResult)
            {
            case clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nUser Updated Successfully :-)\n";
                _PrintUser(User);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;

            }
      
            }
        }
        else {
            cout << "Operation cancelled.";
        }
	}
};

