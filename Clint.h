#pragma once
#include<string>
using namespace std;
class Client
{
private:
	string clientName;
	string clientEmail;
	string accountNumber;
	string phoneNumber;
	long long balance;
	int pinCode;

public:
	Client() {};
	~Client() {};

	void setClientName(string);
	void setClientEmail(string);
	void setAccountNumber(string);
	void setClientBalance(long long);
	void setClientphone(string);
	void setPinCode(int);
	int getPinCode();
	long long getBalance();
	string getPhoneNumber();
	string getAccountNumber();
	string getClientName();
	string getClientEmail();
};
