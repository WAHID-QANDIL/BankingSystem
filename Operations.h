#pragma once
#include<iostream>
#include"Database.h"
using namespace std;

namespace OP {
	int printStartMenue();
	void showClintList();
	int readMenueNumber();
	string readString();
	string streingValidation(string);
	int clienCount();
	void CreateClient();
	void showClintInfo(Client);
	void TrimString(string&);
	bool validChar(char);
	bool EmailValidation(string);
	void UpperFirstLetter(string&);
	void ToupperString(string&);
	string readString(string);
	long long readInteger(string);
	string readEmail(string);
	void deleteClient(string);
	void UpdateClientInfo(string);
	void findClient(string);
	void endSystem();
	void startProgram();
};