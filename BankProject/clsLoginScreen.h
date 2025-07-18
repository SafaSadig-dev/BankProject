#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private:
	/*static void _Login() {
		bool LoginFaild = false;
		string UserName, Password;
		short counter = 3;
		do {

			if (LoginFaild) {
				cout << "\nInvalid userName/Password!\n";
				cout << "You have " << counter << " Trails to Login.\n\n";

			}

			UserName = clsInputValidate::ReadWord("Please Enter UserName ? ");
			Password = clsInputValidate::ReadWord("Please Enter Password ? ");

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();
			counter--;
		

		} while (LoginFaild && counter > 0);

		if (!LoginFaild) {
			clsMainScreen::ShowMainMenue();
		}
		else {
			cout << "You are looked after 3 trails failed!\n\n";
			exit(0);

		}
	}*/

	/*static void _LoginRegister() {
		string FileName = "LoginRegister.txt";
		fstream MyFile;
		MyFile.open(FileName, (ios::out | ios::app));

		if (MyFile.is_open()) {
			
			MyFile << CurrentUser.UserInfo()<<endl;
			MyFile.close();
		}
		else {
			cout << "File does not exist! \n";
			system("pause > 0");
		}

	}*/
	static bool _Login() {
		bool LoginFaild = false;
		string UserName, Password;
		short FaildLoginCount = 0;
		do {

			if (LoginFaild) {
				FaildLoginCount++;

				cout << "\nInvalid userName/Password!\n";
				cout << "You have " << (3 - FaildLoginCount) << " Trail(s) to Login.\n\n";

			}

			if (FaildLoginCount == 3) {
				cout << "You are looked after 3 trails failed!\n\n";
				return false;
			}

			UserName = clsInputValidate::ReadWord("Please Enter UserName ? ");
			Password = clsInputValidate::ReadWord("Please Enter Password ? ");

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

			


		} while (LoginFaild );


		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}
public:
	static bool ShowLoginScreen() {
		system("cls");
		_DrawSreenHeader("\t   Login Screen");

		return _Login();

	}

};

