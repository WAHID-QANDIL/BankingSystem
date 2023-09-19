#pragma once
#include<iostream>
#include"Database.h"
using namespace std;
namespace OP {
	const string fileName = "BankingClientsData.txt";
	const string seperator = "//";
	int printStartMenue();
	void showClintList(vector<Client>);
	int readMenueNumber();
	string readString(string);
	string streingValidation(string);
	void CreateClient(string, string);
	void showClintInfo(Client);
	void TrimString(string&);
	bool validChar(char);
	bool EmailValidation(string);
	void UpperFirstLetter(string&);
	void ToupperString(string&);
	string readString(string);
	long long readInteger(string);
	string readEmail(string);
	void deleteClient(string, vector<Client>, string, string);
	void UpdateClientInfo(string, vector<Client>, string, string);
	void findClient(string, vector<Client>);
	void endSystem();
	void startProgram();
	bool isExistonFile(string, string, string);
	vector<Client> convertFromfileTovector(string, string);
	Client convertFromStringToRecord(string, string);
	string convertFromRecordTostring(Client client, string seperator);
	void writeONfile(Client, string, string);
	void showTrasactionScreen();
	void deposite(string, string, string);
	void withDraw(string, string, string);
	void transactionMenue(string, string);
	void printWithdrawScreen();
	void printDepositScreen();
	short readTransactionMenueNumber(string message);
};