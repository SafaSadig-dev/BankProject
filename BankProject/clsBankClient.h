#pragma once

#include <fstream>
#include "clsPerson.h"
#include "iostream"
#include "clsDate.h"
#include "clsString.h"
#include <filesystem> // C++17 ··Õ’Ê· ⁄·Ï «·„”«— «·ﬂ«„·
#include "Global.h"
using namespace std;

class clsBankClient : public clsPerson
{
public :
    struct stTransferLog;
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 3,
    };
    enMode _Mode;

    string _PinCode = "";
    string _AccountNumber = "";
    float _AccountBalance = 0;
    bool _MarkForDelete = false;

    static stTransferLog _ConvertLineToRegisterLog(string Line, string Delim = "#//#") {
        vector<string> sData = clsString::Split(Line, Delim);

        stTransferLog Record;
        Record.DateTime = sData[0];
        Record.SourceAccountNumber = sData[1];
        Record.DestinationAccountNumber = sData[2];
        Record.Amount = stof(sData[3]);
        Record.SourceBalanceAfterTransfer = stof(sData[4]);
        Record.DestinationBalanceAfterTransfer = stof(sData[5]);
        Record.UserName = sData[6];
      
        return Record;
    }
    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> sClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, sClientData[0], sClientData[1], sClientData[2],
            sClientData[3], sClientData[4], sClientData[5], stof(sClientData[6]));
    }

    static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {
        string ClientRecord = Client.FristName() + Seperator + Client.LastName() + Seperator + Client.Email() + Seperator +
            Client.Phone() + Seperator + Client._AccountNumber + Seperator + Client._PinCode + Seperator + to_string(Client._AccountBalance);
        return ClientRecord;
    }

    void _SaveCleintsDataToFile(vector<clsBankClient> vClients)
    {
        string FileName = "Clients.txt";
        fstream MyFile;

        string DataLine = "";
        MyFile.open(FileName, (ios::out));
        if (MyFile.is_open())
        {
            for (clsBankClient& c : vClients)
            {
                if (c.MarkForDeleted() == false)
                {
                    DataLine = _ConvertClientObjectToLine(c);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;
        string FileName = "Clients.txt";
        fstream MyFile;

        MyFile.open(FileName, ios::in); // read only
        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    clsBankClient Client = _ConvertLineToClientObject(Line);
                    vClients.push_back(Client);
                }
            }

            MyFile.close();
        }
        else {
            cout << "Not found!\n";
            cout << "File not found. Creating new file..." << endl;

            // ≈‰‘«¡ «·„·›
            MyFile.open(FileName, ios::out);
            if (MyFile.is_open())
            {
                MyFile.close();

                cout << "File created : "<< endl;
            }
            else
            {
                cout << "Error: Could not create the file!" << endl;
            }

        }

        return vClients;
    }

    void _AddDataLineToFile(string DataLine)
    {
        string FileName = "Clients.txt";
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
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : vClients)
        {
            if (C._AccountNumber == this->GetAccoutNumber())
            {
                C = *this;
                break;
            }
        }
        // string Line = _ConvertClientObjectToLine();
        _SaveCleintsDataToFile(vClients);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    string _PrepareTransferLog(float Amount,clsBankClient DestintionClient, string Delim = "#//#") {
        string TransferRecord = clsDate::GetSystemDateTimeString() + Delim;
        TransferRecord += this->_AccountNumber + Delim;
        TransferRecord += DestintionClient.GetAccoutNumber() + Delim;
        TransferRecord += to_string(Amount) + Delim;
        TransferRecord += to_string(this->GetAccoutBalance()) + Delim;
        TransferRecord += to_string(DestintionClient.GetAccoutBalance()) + Delim;
        TransferRecord += CurrentUser.GetUserName();

        return TransferRecord;

    }

    void _RegisterTransferLogToFile(string DataLine) {
        string FileName = "TransferLog.txt";
        fstream MyFile;
        string LogLine = "";

        MyFile.open(FileName, (ios::out | ios::app));
        if (MyFile.is_open()) {
            MyFile << DataLine << endl;

            MyFile.close();
        }
        else {
            cout << "Transfer Log File not found!\n";
            system("pause>0");

        }
    }


public:
    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _PinCode = PinCode;
        _AccountNumber = AccountNumber;
        _AccountBalance = AccountBalance;
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildAccountNumberExists = 2,

    };

    struct  stTransferLog {
        string DateTime = "";
        string SourceAccountNumber = "";
        string DestinationAccountNumber = "";
        float Amount = 0;
        float SourceBalanceAfterTransfer = 0;
        float DestinationBalanceAfterTransfer = 0;
        string UserName = "";
    };

    //---Setter&Getter--------

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    void SetAccoutBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    string GetPinCode()
    {
        return _PinCode;
    }

    string GetAccoutNumber()
    {
        return _AccountNumber;
    }

    float GetAccoutBalance()
    {
        return _AccountBalance;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkForDeleted()
    {
        return _MarkForDelete;
    }

    // you must sparete ui and data
    //void Print()
    //{
    //    cout << "\nClient Card:";
    //    cout << "\n___________________";
    //    cout << "\nFirstName   : " << FristName();
    //    cout << "\nLastName    : " << LastName();
    //    cout << "\nFull Name   : " << FullName();
    //    cout << "\nEmail       : " << Email();
    //    cout << "\nPhone       : " << Phone();
    //    cout << "\nAcc. Number : " << _AccountNumber;
    //    cout << "\nPassword    : " << _PinCode;
    //    cout << "\nBalance     : " << _AccountBalance;
    //    cout << "\n___________________\n";
    //}
    static clsBankClient Find(string AccountuNumber)
    {
        string FileName = "Clients.txt";
        fstream MyFile;

        MyFile.open(FileName, ios::in);
        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                if (Line != "\n")
                {
                    clsBankClient Client = _ConvertLineToClientObject(Line);
                    if (Client._AccountNumber == AccountuNumber)
                    {
                        MyFile.close();
                        return Client;
                    }
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountuNumber, string PinCode)
    {
        string FileName = "Clients.txt";
        fstream MyFile;

        MyFile.open(FileName, ios::in);
        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                if (Line != "")
                {
                    clsBankClient Client = _ConvertLineToClientObject(Line);
                    if (Client._AccountNumber == AccountuNumber && Client._PinCode == PinCode)
                    {
                        MyFile.close();
                        return Client;
                    }
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client = Find(AccountNumber);
        return !(Client.IsEmpty());
    }

    static clsBankClient GetNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveResults::svFaildEmptyObject;

        case enMode::UpdateMode:
            _Update();
            return enSaveResults::svSucceeded;

        case enMode::AddNewMode:

            if (IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();
                // we need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        }
    }

    bool Delete()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : vClients)
        {
            if (C.GetAccoutNumber() == _AccountNumber)
            {
                C._MarkForDelete = true;
                break;
            }
        }

        _SaveCleintsDataToFile(vClients);

        *this = _GetEmptyClientObject();
        return true;
    }

    static vector<clsBankClient> GetClinetsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances()
    {
        vector<clsBankClient> vClients = GetClinetsList();
        double TotalBalances = 0;

        for (clsBankClient& C : vClients)
        {
            TotalBalances += C.GetAccoutBalance();
        }

        return TotalBalances;
    }

    void Deposit(float Amount) {
        _AccountBalance += Amount;
        Save();
    }
    bool Withdraw(float Amount) {
        if (Amount > _AccountBalance) {
            return false;
        }
        else {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }

   
    bool Transfer(float Amount, clsBankClient& DestinationClient) {
        if (Amount > this->_AccountBalance) {
            return false;
        }
        Withdraw(Amount);
        DestinationClient.Deposit(Amount);


        string sTransferData = _PrepareTransferLog(Amount, DestinationClient);
        _RegisterTransferLogToFile(sTransferData);

        return true;
    }


    static vector<stTransferLog> GetTransferRegisterList() {
        vector<stTransferLog> vTransferLogs;
        string FileName = "TransferLog.txt";
        stTransferLog stRegisterLog;
        string Line;
        fstream MyFile;

        MyFile.open(FileName, ios::in);//Read Only
        if (MyFile.is_open()) {
            while (getline(MyFile, Line)) {
                if (Line != "") {
                    stRegisterLog = _ConvertLineToRegisterLog(Line);
                    vTransferLogs.push_back(stRegisterLog);
                }
            }
        }

        return vTransferLogs;

    }
};
