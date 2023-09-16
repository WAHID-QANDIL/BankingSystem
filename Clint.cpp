#include "Clint.h"
#include<string>
//Clint::Clint()
//{
//	//set initial value to each property once the object have been created
//	this->clientName = "";
//	this->accountNumber = "";
//	this->clientEmail = "";
//	this->clientName = "";
//	this->phonrNumber = 0;
//	this->balance = 0;
//}
void Client::setAccountNumber(string number)
{
	this->accountNumber = number;
	return;
}
void Client::setClientBalance(long long  balance)
{
	this->balance = balance;
}
void Client::setClientName(string name)
{
	this->clientName = name;
}
void Client::setClientphone(string phone)
{
	this->phoneNumber = phone;
}
void Client::setClientEmail(string email)
{
	this->clientEmail = email;
}
void Client::setPinCode(int pinCode)
{
	this->pinCode = pinCode;
}
long long  Client::getBalance() {
	return this->balance;
}
int Client::getPinCode() {
	return this->pinCode;
}
string Client::getAccountNumber() {
	return this->accountNumber;
}
string Client::getClientName() {
	return this->clientName;
}
string Client::getPhoneNumber() {
	return this->phoneNumber;
}
string Client::getClientEmail() {
	return this->clientEmail;
}