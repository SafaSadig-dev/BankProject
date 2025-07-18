#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>

class clsListUserScreen : protected clsScreen
{
private:

    static void _PrintUserRecordLine(clsUser User)
    {

        cout << setw(8) << "" << "| " << left << setw(15) << User.GetUserName();
        cout << "| " << left << setw(20) << User.FullName();
        cout << "| " << left << setw(12) << User.Phone();
        cout << "| " << left << setw(20) << User.Email();
        cout << "| " << left << setw(10) << User.GetPassword();
        cout << "| " << left << setw(12) << User.GetPermissions();
    }

public:
	static void ShowUsersList() {

        vector<clsUser> vUsers = clsUser::GetCUsersList();
        string Title = "\t    Users List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawSreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________________\n"
            << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________________";
        cout << "_________________________________________\n"
            << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser& U : vUsers)
            {

                _PrintUserRecordLine(U);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________________";
        cout << "_________________________________________\n"
            << endl;
    
	}
};

