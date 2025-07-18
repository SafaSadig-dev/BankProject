#pragma once
#include "clsDate.h"
#include "clsString.h"
#include "clsUtil.h"

class clsPerson
{
private:
    string _FristName = "";
    string _LastName = "";
    string _Email = "";
    string _Phone = "";

public:
    clsPerson(string FristName, string LastName,
        string Email, string Phone)
    {
        _FristName = FristName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }
    void SetFristName(string FristName)
    {
        _FristName = FristName;
    }

    void SetLastName(string LastName)
    {
        _LastName = LastName;
    }
    void SetPhone(string Phone)
    {
        _Phone = Phone;
    }
    void SetEmail(string Email)
    {
        _Email = Email;
    }

    //-----------Getter------------
    string FristName()
    {
        return _FristName;
    }

    string LastName()
    {
        return _LastName;
    }
    string Phone()
    {
        return _Phone;
    }
    string Email()
    {
        return _Email;
    }

    string FullName()
    {
        return _FristName + " " + _LastName;
    }
};