#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsListUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

//TODO: add Screen

class clsManageUsersScreen : protected clsScreen
{
private:
    enum enMangeUserMenueOptions
    {
        eListUsers = 1,
        eAddUser = 2,
        eFindUser = 5,
        eUpdateUser = 4,
        eDeleteUser = 3,
        eMainMenue = 6,
    };

    static short _ReadMangeUserOption()
    {

        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _GoBackToManageUsersMenue()
    {
        cout << "\n\nPress any key to go back to Manage Users Menue...";
        system("pause>0");
        ShowMangeUsersScreen();
    }

    static void _ShowAllUsersScreen()
    {
        //cout << "\nShow All Users Screen Will be here...\n";
        clsListUserScreen::ShowUsersList();

        
    }

    static void _ShowAddNewUsersScreen()
    {
        //TODO: FIX STUBS
        //cout << "\nShow Add New User Screen Will be here...\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
       

    }

    static void _ShowDeleteUserScreen()
    {
       // cout << "\n_Show Delete User Screen Will be here...\n";
        clsDeleteUserScreen::ShowDeleteUserScreen();

    }

    static void _ShowUpdateUserScreen()
    {

      // cout << "\nShow Update User Screen Will be here...\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();

    }

    static void _ShowFindUserScreen()
    {
           
        //cout << "\nShow Find User Screen Will be here...\n";
        clsFindUserScreen::ShowFindUserScreen();

    }



    static void _PerfromManageUserOption(enMangeUserMenueOptions MangeUserMenueOption)
    {
        switch (MangeUserMenueOption)
        {
        case enMangeUserMenueOptions::eListUsers:
        {
            system("cls");
            _ShowAllUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        }
        case enMangeUserMenueOptions::eAddUser:
            system("cls");
            _ShowAddNewUsersScreen();
            _GoBackToManageUsersMenue();
            break;

        case enMangeUserMenueOptions::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enMangeUserMenueOptions::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enMangeUserMenueOptions::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enMangeUserMenueOptions::eMainMenue:
            //do nothing here the main screen will handle it :-) ;
            break;
        }
    }
public:

	static void ShowMangeUsersScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;// this will exit the function and it will not continue
        }

        system("cls");
        _DrawSreenHeader("\t    Mange Users Screen");

        cout <<setw(37) <<left <<"" << "===========================================\n";
        cout <<setw(37) <<left <<"" <<"\t\t  Mange User Menue\n";
        cout <<setw(37) <<left <<"" <<"===========================================\n";
        cout <<setw(37) <<left <<"" <<"\t[1] List users.\n";
        cout <<setw(37) <<left <<"" <<"\t[2] Add New user.\n";
        cout <<setw(37) <<left <<"" <<"\t[3] Delete user.\n";
        cout <<setw(37) <<left <<"" <<"\t[4] Update user.\n";
        cout <<setw(37) <<left <<"" <<"\t[5] Find User.\n";
        cout <<setw(37) <<left <<"" <<"\t[6] Main Menue.\n";
        cout <<setw(37) <<left <<"" <<"===========================================\n";

        _PerfromManageUserOption(((enMangeUserMenueOptions)_ReadMangeUserOption()));


	}

};
