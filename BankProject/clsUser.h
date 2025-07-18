#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Global.h"

using namespace std;

class clsUser : public clsPerson
{
    struct stLoginRegisterRecord;
   
private:
	//enum enPermison
    enum enMode
{
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 3,
};


   
    enMode _Mode;
    
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkForDelete = false;
    
    static clsUser _GetEmptyUserObject() {
        return clsUser(enMode::EmptyMode,"","", "", "", "", "", 0);
    }
    bool MarkForDeleted()
    {
        return _MarkForDelete;
    }
    
    string _PrepareLogInRecord(string Delim = "#//#") {

        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Delim;
        LoginRecord += this->_UserName + Delim;
        LoginRecord += clsUtil::EncryptText(this->_Password) + Delim;
        LoginRecord += to_string(this->_Permissions);

        return LoginRecord;
         
    }
    
    static clsUser _ConvertLineToUserObject(string LineData, string Seperator = "#//#") {
        vector <string> sUserData = clsString::Split(LineData, Seperator);
    
        return clsUser(enMode::UpdateMode, sUserData[0], sUserData[1], sUserData[2], sUserData[3],
            sUserData[4], clsUtil::DecryptText(sUserData[5]),stoi(sUserData[6]));
    }

    static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string UserRecord = User.FristName() + Seperator + User.LastName() + Seperator + User.Email() + Seperator +
            User.Phone() + Seperator + User.GetUserName() + Seperator + clsUtil ::EncryptText(User._Password) + Seperator + to_string(User._Permissions);
        return UserRecord;
    }

    void _SaveUsersDataToFile(vector<clsUser> vUsers)
    {
        string FileName = "Users.txt";
        fstream MyFile;

        string DataLine = "";
        MyFile.open(FileName, (ios::out));
        if (MyFile.is_open())
        {
            for (clsUser & U : vUsers)
            {
                if (U.MarkForDeleted() == false)
                {
                    DataLine = _ConvertUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }
    static stLoginRegisterRecord  _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#") {
        vector<string>  LoginRegisterDataLine = clsString::Split(Line, Seperator);

        stLoginRegisterRecord Record;
        Record.DateTime = LoginRegisterDataLine[0];
        Record.UserName = LoginRegisterDataLine[1];
        Record.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
        Record.Permissions = stoi(LoginRegisterDataLine[3]);

        return Record;

    }

    static vector<clsUser::stLoginRegisterRecord> _LoadLoginRecordsFromFile() {
        vector<clsUser::stLoginRegisterRecord> vRecords;
        string FileName = "LoginRegister.txt";
        stLoginRegisterRecord Record;

        fstream MyFile;
        MyFile.open(FileName, ios::in);

        string Line = "";
        if (MyFile.is_open()) {
            while (getline(MyFile, Line)) {
                if (Line != "") {
                    Record = _ConvertLoginRegisterLineToRecord(Line);
                    vRecords.push_back(Record);
                }
            }

            MyFile.close();
        }
        else {
            cout << "File not Found!\n";
            system("pause>0");
        }

        return vRecords;
    }
    static vector<clsUser> _LoadUsersDataFromFile()
    {
        vector<clsUser> vUsers;
        string FileName = "Users.txt";
        fstream MyFile;

        MyFile.open(FileName, ios::in); // read only
        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    clsUser User = _ConvertLineToUserObject(Line);
                    vUsers.push_back(User);
                }
            }

            MyFile.close();
        }
        else {
            cout << "Not found!\n";

        }

        return vUsers;
    }

    void _AddDataLineToFile(string DataLine)
    {
        string FileName = "Users.txt";
        fstream MyFile;

        MyFile.open(FileName, (ios::out | ios::app));
        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;

            MyFile.close();
        }
        else {
            cout << "Not Found !!" << endl;
        }
    }

    void _Update()
    {
        vector<clsUser> vUsers = _LoadUsersDataFromFile();
        for (clsUser& U: vUsers)
        {
            if (U._UserName == this->GetUserName())
            {
                U = *this;
                break;
            }
        }
        // string Line = _ConvertClientObjectToLine();
        _SaveUsersDataToFile(vUsers);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }
    public:
    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
    {
        
        _Mode = Mode;
        
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pShowLoginRegister = 128
    };

    struct stLoginRegisterRecord {
        string DateTime = "";
        string UserName = "";
        string Password = "";
        int Permissions = 0;

    };
    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildUserExists = 2,

    };

    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    }

   
    void SetPermission(int Permissions) {
        _Permissions = Permissions;
    }

    void SetUserName(string UserName) {
        _UserName = UserName;
    }

    void SetPassword(string Password) {
        _Password = Password;
    }

    string GetUserName() {
        return _UserName;
    }

    string GetPassword() {
        return _Password;
    }
    int GetPermissions() {
        return _Permissions;
    }

    static clsUser Find(string UserName)
    {
        string FileName = "Users.txt";
        fstream MyFile;

        MyFile.open(FileName, ios::in);
        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    clsUser User = _ConvertLineToUserObject(Line);
                    if (User._UserName == UserName)
                    {
                        MyFile.close();
                        return User;
                    }
                }
            }

            MyFile.close();
        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {
        string FileName = "Users.txt";
        fstream MyFile;

        MyFile.open(FileName, ios::in);
        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    clsUser User = _ConvertLineToUserObject(Line);
                    if (User._UserName == UserName && User._Password == Password)
                    {
                        MyFile.close();
                        return User;
                    }
                }
            }

            MyFile.close();
        }

        return _GetEmptyUserObject();
    }

    static bool IsUserExist(string UserName)
    {
        clsUser User = Find(UserName);
        return !(User.IsEmpty());
    }

    static clsUser GetNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }
    }

    bool Delete()
    {
        vector<clsUser> vUsers = _LoadUsersDataFromFile();
        for (clsUser& U : vUsers)
        {
            if (U.GetUserName() == this->_UserName)
            {
                U._MarkForDelete = true;
                break;
            }
        }

        _SaveUsersDataToFile(vUsers);

        *this = _GetEmptyUserObject();
        return true;
    }

    static vector<clsUser> GetCUsersList()
    {
        return _LoadUsersDataFromFile();
    }


     bool CheckAccessPermission(enPermissions Permissions) {
        if (this->_Permissions == clsUser::enPermissions::eAll) {
            return true;
        }

        if ((this->_Permissions & Permissions) == Permissions) {
            return true;
        }
        else
        {
            return false;
        }
    }

     void RegisterLogIn() {
         string FileName = "LoginRegister.txt";
         string stDataLine = _PrepareLogInRecord();
         fstream MyFile;

         MyFile.open(FileName, (ios::out | ios::app));
         if (MyFile.is_open()) {
             MyFile << stDataLine << endl;
             MyFile.close();
         }
         else {
             cout << "File Register Login not Found !\n";
             system("Pause > 0");
         }
     }

     static vector<clsUser::stLoginRegisterRecord> GetLoginRegisterList() {
         return _LoadLoginRecordsFromFile();
     }

    



};

