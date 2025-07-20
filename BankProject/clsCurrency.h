#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "clsString.h"
using namespace std;

class clsCurrency
{
private:
	enum enMode {
		eEmptyMode = 0,
		eUpdateMode = 1
	};
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _GetEmptyCurrency() {
		return clsCurrency(enMode::eEmptyMode, "", "", "", 0);
	}
	static clsCurrency _ConvertLineToCurrencyObject(string CurrencyLine, string Delim = "#//#") {
		vector<string> vCurrecyLine = clsString::Split(CurrencyLine, Delim);

		return clsCurrency(enMode::eUpdateMode, vCurrecyLine[0], vCurrecyLine[1],
			vCurrecyLine[2], stof(vCurrecyLine[3]));
	}
	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Delim = "#//#") {
		string CurrencyRecord = Currency._Country + Delim;
		CurrencyRecord += Currency._CurrencyCode + Delim;
		CurrencyRecord += Currency._CurrencyName + Delim;
		CurrencyRecord += to_string(Currency._Rate);

		return CurrencyRecord;
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency> VCurrncies) {
		string Line = "";
		string FileName = "Currencies.txt";
		fstream MyFile;

		MyFile.open(FileName, (ios::out));// override mode
		if (MyFile.is_open()) {
			for (clsCurrency& C : VCurrncies) {
				Line = _ConvertCurrencyObjectToLine(C);
				MyFile << Line << endl;
			}

			MyFile.close();
		}
		else {
			cout << "ERROR !\nFile not Found.\n";
			system("pause>0");
		}

	}
	static vector<clsCurrency> _LoadCurrencyDataFromFile() {
		vector<clsCurrency> VCurrncies;
		string FileName = "Currencies.txt";
		fstream MyFile;

		MyFile.open(FileName, ios::in);// ReadOnly mode
		string Line = "";
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				if (Line != "") {
					clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
					VCurrncies.push_back(Currency);
				}
			}
			MyFile.close();
		}

		else {
			cout << "ERROR !\nFile not Found.\n";
			system("pause>0");
		}

		return VCurrncies;
	}
	void _Update() {
		vector<clsCurrency> VCurrncies = _LoadCurrencyDataFromFile();
		for (clsCurrency& C : VCurrncies) {
			if (this->_CurrencyCode == C.CurrencyCode()) {
				C = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(VCurrncies);

	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	bool IsEmpty() {
		return (_Mode == enMode::eEmptyMode);
	}
	string Country() {
		return _Country;
	}
	string CurrencyName() {
		return _CurrencyName;
	}
	string CurrencyCode() {
		return _CurrencyCode;
	}
	float Rate() {
		return _Rate;
	}

	void UpdateRate(float NewRate) {
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency FindByCode(string CurrencyCode) {
		//	vector<clsCurrency> VCurrncies = _LoadCurrencyDataFromFile(); preformance !!
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		string FileName = "Currencies.txt";
		fstream MyFile;

		MyFile.open(FileName, ios::in);// ReadOnly mode
		string Line = "";
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				if (Line != "") {
					clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
					if (Currency.CurrencyCode() == CurrencyCode) {
						MyFile.close();
						return Currency;
					}
				}
			}

			MyFile.close();
		}
		else {
			cout << "File Not Found !!\n";
			system("pause>0");
		}

		return _GetEmptyCurrency();

	}

	static clsCurrency FindByCountry(string Country) {
		//vector<clsCurrency> VCurrncies = _LoadCurrencyDataFromFile();
		Country = clsString::UpperAllString(Country);
		string FileName = "Currencies.txt";
		fstream MyFile;

		MyFile.open(FileName, ios::in);// ReadOnly mode
		string Line = "";
		if (MyFile.is_open()) {
			while (getline(MyFile, Line)) {
				if (Line != "") {
					clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
					if (clsString::UpperAllString(Currency.Country()) == Country) {
						MyFile.close();
						return Currency;
					}
				}
			}

			MyFile.close();
		}
		else {
			cout << "File Not Found !!\n";
			system("pause>0");
		}

		return _GetEmptyCurrency();

	}

	static vector<clsCurrency>  GetCurrenciesList() {
		return _LoadCurrencyDataFromFile();
	}

	static bool IsCurrencyExist(string CurrncyCode) {

		clsCurrency Currency = FindByCode(CurrncyCode);

		return (!Currency.IsEmpty());
	}

	float ConvertToUSD(float Amount) {
		return(Amount / _Rate);
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) {
		//return(Amount * _Rate);
		float AmountInUSD = ConvertToUSD(Amount);
		if (Currency2.CurrencyCode() == "USD") {
			return AmountInUSD;
		}

		// convert from jod to sdg, 
		// frist from jod to usd 
		// second from usd to sdg
		return(AmountInUSD * Currency2._Rate);

	}

};

