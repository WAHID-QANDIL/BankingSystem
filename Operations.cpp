#include"Operations.h"
#include"Database.h"
#include"Clint.h"
#include<vector>
#include<iomanip>
//Create dataStorage list

int OP::readMenueNumber()
{
	int number = 0;
	do
	{
		cout << "Enter number between 1 : 6 >>" << endl;
		cin >> number;

		if (cin.fail())
		{
			cin.clear(number);
			cin.ignore(std::numeric_limits<std::streamsize>::max());
			number = 0;
		}
	} while (number < 1 || number > 6);
	return number;
}
int OP::printStartMenue() {
	system("cls");
	cout << "==========================================================" << endl
		<< "\t\t****** Main Mune Screen  ******" << endl
		<< "==========================================================" << endl
		<< "(1) Show Client List." << endl
		<< "(2) Add New Client." << endl
		<< "(3) Delet Client." << endl
		<< "(4) Update Client Information." << endl
		<< "(5) Find Client." << endl
		<< "(6) Exit." << endl;
	int number = OP::readMenueNumber();
	return number;
}
void OP::CreateClient() {
	Client client;
	string clientName;
	string clientEmail;
	string accountNumber;
	string phoneNumber;
	long long balance;
	int pinCode;

	accountNumber = readString("Enter Account Number:");
	clientName = readString("Enter client name:");
	phoneNumber = readString("Enter phone Number:");
	clientEmail = readEmail(readString("Enter client Email:"));
	balance = readInteger("Enter client balance:");
	pinCode = readInteger("Enter client pincode:");

	TrimString(clientName);
	TrimString(clientEmail);
	UpperFirstLetter(clientName);
	ToupperString(accountNumber);

	client.setAccountNumber(accountNumber);
	client.setClientName(clientName);
	client.setClientEmail(clientEmail);
	client.setClientphone(phoneNumber);
	client.setPinCode(pinCode);
	client.setClientBalance(balance);
	Database::Data.push_back(client);
}
void OP::showClintList() {
	system("cls");
	cout << setw(90) << "Client List " << Database::Data.size() << " Client(s)" << endl
		<< "\t--------------------------------------------------------------------------------------------------------------------------------------------------" << endl
		<< setw(25) << "| Account Number"
		<< setw(20) << "| Pin Code"
		<< setw(24) << "| Client Name"
		<< setw(30) << "| Phone "
		<< setw(20) << "| Balance"
		<< setw(30) << "| Client Email" << endl
		<< "\t--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (Client& cl : Database::Data)
	{
		cout << setw(20) << cl.getAccountNumber()
			<< setw(25) << cl.getPinCode()
			<< setw(24) << cl.getClientName()
			<< setw(30) << cl.getPhoneNumber()
			<< setw(20) << cl.getBalance()
			<< setw(30) << cl.getClientEmail() << endl;
	}
	cout << "\t--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}
void OP::showClintInfo(Client client)
{
	cout << "===== Client Info ======" << endl
		<< "========================" << endl
		<< "Account number is " << client.getAccountNumber() << endl
		<< "Client name is " << client.getClientName() << endl
		<< "PinCode is " << client.getPinCode() << endl
		<< "Account balance is " << client.getBalance() << endl
		<< "Client email is " << client.getClientEmail() << endl
		<< "Client phone is " << client.getPhoneNumber()
		<< endl << "========================" << endl;
}
void OP::TrimString(string& str)
{
	int CHposition = 0;
	for (int i = 0; i < str.size(); ++i)//trim left
	{
		if (validChar(str.at(i))) { break; }
		CHposition++;
	}
	str = str.substr(CHposition, str.size());
	for (int i = str.size() - 1; i > 1; --i)//trim right
	{
		if (validChar(str.at(i)))
		{
			str = str.substr(0, i + 1);
			break;
		}
	}
}
bool OP::validChar(char ch)
{
	return((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90));
}
bool OP::EmailValidation(string str)
{
	for (char& i : str)
	{
		if (i == '@')return true;
	}
	return false;
}
string OP::readEmail(string email)
{
	while (!OP::EmailValidation(email))//Check email containes '@'
	{
		cout << "Endter a valid email" << endl;
		cin >> email;
	}
	return email;
}
void OP::UpperFirstLetter(string& str)
{
	bool isfirst = true;
	char space = 32;
	for (int i = 0; i < str.size(); ++i) {
		if (str.at(i) != space && isfirst)
		{
			if (str.at(i) > 96)str.at(i) -= 32;
		}
		isfirst = (str.at(i) == space);
	}
}
string OP::readString(string message)
{
	string str;
	cout << message << endl;
	getline(cin >> ws, str);
	return str;
}
long long OP::readInteger(string message)
{
	long long number;
	cout << message << endl;
	while (1)
	{
		try
		{
			cin >> number;
			break;
		}
		catch (const std::exception& e)
		{
			cout << &e << endl;
			cout << "Enter a valid number:" << endl;
		}
	}
	return number;
}
void OP::ToupperString(string& str)
{
	for (char& i : str)
	{
		if (OP::validChar(i) && i > 96)i -= 32;
	}
}
void OP::deleteClient(string str)
{
	vector<Client>Data;
	OP::ToupperString(str);
	OP::TrimString(str);
	bool isfound = false;
	for (Client& client : Database::Data)
	{
		if (client.getAccountNumber() == str) {
			isfound = true;
			showClintInfo(client);
		}
		if (client.getAccountNumber() != str)Data.push_back(client);
	}
	if (isfound)
	{
		Database::Data = Data;
		cout << "Client Deleted succesfully :)" << endl;
		//Database::Data.resize(0,(position-1)+)
	}
	else
	{
		cout << "Client with this account number dosen't exist :(" << endl;
	}
}
void OP::UpdateClientInfo(string str) {
	OP::ToupperString(str);
	OP::TrimString(str);
	bool isFound = false;
	for (Client& client : Database::Data)
	{
		if (client.getAccountNumber() == str)
		{
			system("cls");
			isFound = true;

			string clientName;
			string clientEmail;
			string accountNumber;
			string phoneNumber;
			long long balance;
			int pinCode;

			cout << "Now you editing data for client with acount number : " << client.getAccountNumber() << endl;

			accountNumber = OP::readString("Enter Account Number:");
			clientName = OP::readString("Enter client name:");
			phoneNumber = OP::readString("Enter phone Number:");
			clientEmail = OP::readEmail(OP::readString("Enter client Email:"));
			balance = OP::readInteger("Enter client balance:");
			pinCode = OP::readInteger("Enter client pincode:");

			OP::TrimString(clientName);
			OP::TrimString(clientEmail);
			OP::UpperFirstLetter(clientName);
			OP::ToupperString(accountNumber);

			client.setClientName(clientName);
			client.setClientEmail(clientEmail);
			client.setClientphone(phoneNumber);
			client.setPinCode(pinCode);
			client.setAccountNumber(accountNumber);
			client.setClientBalance(balance);
			break;
		}
	}
	(isFound) ? (cout << "Client information has been updated :)" << endl)
		: (cout << "Client with this account number dosen't exist :(" << endl);
}
void OP::findClient(string str)
{
	bool isFound = false;
	OP::TrimString(str);
	OP::ToupperString(str);

	for (Client client : Database::Data)
	{
		if (client.getAccountNumber() == str)
		{
			OP::showClintInfo(client);
			isFound = true; break;
		}
	}
	if (!isFound)cout << "Client with this account number dosen't exist :(" << endl;
}
void OP::endSystem()
{
	system("cls");
	cout << "\t\t===================================="
		<< "\t\t\t Program Finished, Thanks for using our services :)"
		<< "\t\t====================================" << endl;
	system("exit");
}
void OP::startProgram()
{
homeScreen:
	int selectedNumber = OP::printStartMenue();
	switch (selectedNumber)
	{
	case 1:
		OP::showClintList();
		break;
	case 2:
		OP::CreateClient();
		break;
	case 3:
		OP::deleteClient(OP::readString("Enter the account number for specific client : "));
		break;
	case 4:
		OP::UpdateClientInfo(OP::readString("Enter the account number for specific client : "));
		break;
	case 5:
		OP::findClient(OP::readString("Enter the account number for specific client : "));
		break;
	case 6:
		OP::endSystem();
		break;
	default:
		break;
	}
	if (selectedNumber != 6)
	{
		cout << "Enter any key to go back to home screen :)" << endl;
		system("pause");
		goto homeScreen;
	}
	system("pause");
}