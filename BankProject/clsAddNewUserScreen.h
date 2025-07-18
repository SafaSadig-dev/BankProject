#pragma once
#include "clsScreen.h"
#include "clsUser.h"

class clsAddNewUserScreen : protected clsScreen
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
            int Permmison = 0;

            cout << "Do You want to give Full Access ? (Y/N) ? ";
            cin >> Answer;
            if (tolower(Answer) == 'y')
            {
                return -1;
            }
            
                
            cout << "\nDo you want to give access: \n";

            cout << "Mange Users ? (Y/N) ? ";
            cin >> Answer;
            if (Answer == 'Y' || Answer == 'y') {
                Permmison += clsUser::enPermissions::pManageUsers;
            }

            cout << "Find Client ? (Y/N) ? ";
            cin >> Answer;
            if (Answer == 'Y' || Answer == 'y') {
                Permmison += clsUser::enPermissions::pFindClient;
            }

            cout << "Transaction ? (Y/N) ? ";
            cin >> Answer;
            if (Answer == 'Y' || Answer == 'y') {
                Permmison += clsUser::enPermissions::pTranactions;
            }

            cout << "Show Client List ? (Y/N) ? ";
            cin >> Answer;
            if (Answer == 'Y' || Answer == 'y') {
                Permmison += clsUser::enPermissions::pListClients;
            }

            cout << "Add new Client ? (Y / N) ? ";
            cin >> Answer;
            if (Answer == 'Y' || Answer == 'y') {
                Permmison += clsUser::enPermissions::pAddNewClient;
            }

            cout << "Delete Client ? (Y/N) ? ";
            cin >> Answer;
            if (Answer == 'Y' || Answer == 'y') {
                Permmison += clsUser::enPermissions::pDeleteClient;
            }

            cout << "Update Client ? (Y/N) ? ";
            cin >> Answer;
            if (Answer == 'Y' || Answer == 'y') {
                Permmison += clsUser::enPermissions::pUpdateClients;
            }

            cout << "Login Register ? (Y/N) ? ";
            cin >> Answer;
            if (Answer == 'Y' || Answer == 'y') {
                Permmison += clsUser::enPermissions::pShowLoginRegister;
            }
            return Permmison;
        }
	
	public:

        static void ShowAddNewUserScreen() {
            _DrawSreenHeader("\t   Add New User Screen");

            //-----------
            string UserName = clsInputValidate::ReadWord("Please Enter User Name? ");
            while (clsUser::IsUserExist(UserName))
            {

                UserName = clsInputValidate::ReadWord("User Name is already use, Choose another one? ");
            }

            clsUser NewUser = clsUser::GetNewUserObject(UserName);

            _ReadUserInfo(NewUser);

            clsUser::enSaveResults SaveResult = NewUser.Save();

            switch (SaveResult)
            {
            case  clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nUser Addeded Successfully :-)\n";
                _PrintUser(NewUser);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;

            }
            case clsUser::enSaveResults::svFaildUserExists:
            {
                cout << "\nError User was not saved because UserName is used!\n";
                break;

            }
            }
        }
};

