#pragma once
#include <iostream>
#include "Global.h"
#include "clsUser.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:
    static void _DrawSreenHeader(string Title, string SubTitle = "")
    {

        cout << "\n\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        if(Title != "\t   Program Ends :-)"){
        cout << "\t\t\t\t\t\tUser: " << CurrentUser.GetUserName() << endl;
        cout << "\t\t\t\t\t\tDate: " << clsDate::GetSystemDate().DateToString() << endl;
        }


    }

    static bool CheckAccessRights(clsUser::enPermissions Permissions) {
        if (!CurrentUser.CheckAccessPermission(Permissions)) {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else {
            return true;
        }
    }
};
