#include"Operations.h"
#include"Database.h"
#include"Clint.h"
#include<vector>
#include<iomanip>
#include<fstream>
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
void OP::CreateClient(string fileName, string seperator) {
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

	client.setClientName(clientName);
	client.setClientEmail(clientEmail);
	client.setClientphone(phoneNumber);
	client.setPinCode(pinCode);
	client.setClientBalance(balance);
	while (isExistonFile(accountNumber, fileName, seperator))
	{
		cout << "Client with this account number is exist " << endl
			<< "Please enter different account number" << endl;
		cin >> accountNumber;
		ToupperString(accountNumber);
	}

	client.setAccountNumber(accountNumber);
	writeONfile(client, fileName, seperator);
}
bool OP::isExistonFile(string accountNumber, string fileName, string seperator)
{
	fstream file;
	file.open(fileName, ios::in);
	vector<Client> client = convertFromfileTovector(fileName, seperator);
	for (Client& client : client)
	{
		if (client.getAccountNumber() == accountNumber)
		{
			return true;
		}
	}
	return false;
}

void OP::showClintList(vector<Client> clients) {
	system("cls");
	cout << right << "\t\t\t\t\t\t\t" << "Client List " << clients.size() << " Client(s)" << endl
		<< "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl
		<< "| " << left << setw(15) << "Account Number"
		<< "| " << left << setw(10) << "Pin Code"
		<< "| " << left << setw(40) << "Client Name"
		<< "| " << left << setw(15) << "Phone "
		<< "| " << left << setw(15) << "Balance"
		<< "| " << left << setw(30) << "Client Email" << endl
		<< "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (Client& cl : clients)
	{
		cout << "| " << setw(15) << left << cl.getAccountNumber()
			<< "| " << setw(10) << left << cl.getPinCode()
			<< "| " << setw(40) << left << cl.getClientName()
			<< "| " << setw(15) << left << cl.getPhoneNumber()
			<< "| " << setw(15) << left << cl.getBalance()
			<< "| " << setw(30) << left << cl.getClientEmail()
			<< endl;
	}
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
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
void OP::deleteClient(string str, vector<Client> Data, string fileName, string seperator)
{
	vector<Client>data;
	OP::ToupperString(str);
	OP::TrimString(str);
	bool isfound = false;
	for (Client& client : Data)
	{
		if (client.getAccountNumber() == str) {
			isfound = true;
			showClintInfo(client);
		}
		if (client.getAccountNumber() != str)data.push_back(client);
	}
	if (isfound)
	{
		fstream file;
		file.open(fileName, ios::out);
		if (file.is_open())
		{
			for (Client client : data)
			{
				file << "\n" << convertFromRecordTostring(client, seperator);
			}
			file.close();
		}

		cout << "Client Deleted succesfully :)" << endl;
		//Database::Data.resize(0,(position-1)+)
	}
	else
	{
		cout << "Client with this account number dosen't exist :(" << endl;
	}
}
void OP::UpdateClientInfo(string str, vector<Client> Data, string fileName, string seperator) {
	OP::ToupperString(str);
	OP::TrimString(str);
	bool isFound = false;
	for (Client& client : Data)
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
			showClintInfo(client);

			cout << "Now you editing data for client with acount number : " << client.getAccountNumber() << endl;

			accountNumber = OP::readString("Enter new Account Number:");
			clientName = OP::readString("Enter new client name:");
			phoneNumber = OP::readString("Enter new phone Number:");
			clientEmail = OP::readEmail(OP::readString("Enter new client Email:"));
			balance = OP::readInteger("Enter new client balance:");
			pinCode = OP::readInteger("Enter new client pincode:");

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
	if (isFound)
	{
		fstream file;
		file.open(fileName, ios::out);

		if (file.is_open())
		{
			for (Client clien : Data)
			{
				file << convertFromRecordTostring(clien, seperator);
				file << "\n";
			}
			file.close();
		}
		cout << "Client information has been updated :)" << endl;
	}
	else
	{
		cout << "Client with this account number dosen't exist :(" << endl;
	}

	/*(isFound) ? (cout << "Client information has been updated :)" << endl)
		: (cout << "Client with this account number dosen't exist :(" << endl);*/
}
void OP::findClient(string str, vector<Client> Data)
{
	bool isFound = false;
	OP::TrimString(str);
	OP::ToupperString(str);

	for (Client client : Data)
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
	//vector<Client> clients = convertFromfileTovector(fileName, seperator);
	int selectedNumber = OP::printStartMenue();
	switch (selectedNumber)
	{
	case 1:
		OP::showClintList(convertFromfileTovector(fileName, seperator));
		break;
	case 2:
		OP::CreateClient(fileName, seperator);
		break;
	case 3:
		OP::deleteClient(OP::readString("Enter the account number for specific client : "), convertFromfileTovector(fileName, seperator), fileName, seperator);
		break;
	case 4:
		OP::UpdateClientInfo(OP::readString("Enter the account number for specific client : "), convertFromfileTovector(fileName, seperator), fileName, seperator);
		break;
	case 5:
		OP::findClient(OP::readString("Enter the account number for specific client : "), convertFromfileTovector(fileName, seperator));
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

string OP::convertFromRecordTostring(Client client, string seperator)
{
	string line;
	line += client.getAccountNumber() + seperator;
	line += client.getClientName() + seperator;
	line += to_string(client.getPinCode()) + seperator;
	line += (client.getPhoneNumber()) + seperator;
	line += to_string(client.getBalance()) + seperator;
	line += (client.getClientEmail()) + seperator;
	return line;
}

Client OP::convertFromStringToRecord(string line, string seperator)
{
	Client client;
	int pos = 0;
	vector<string> vclient;
	while (pos != std::string::npos)
	{
		pos = line.find(seperator);
		vclient.push_back(line.substr(0, pos));
		line.erase(0, pos + seperator.size());
	}

	client.setAccountNumber(vclient.at(0));
	client.setClientName(vclient.at(1));
	client.setPinCode(stoll(vclient.at(2)));
	client.setClientphone(vclient.at(3));
	client.setClientBalance(stoll(vclient.at(4)));
	client.setClientEmail(vclient.at(5));

	return client;
}
vector<Client> OP::convertFromfileTovector(string filename, string seperator)//read strings from file then convert them into client opject(record)
{
	fstream file;
	file.open(filename, ios::in);
	vector<Client> fileData;
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			if (line != "")
			{
				fileData.push_back(convertFromStringToRecord(line, seperator));
			}
		}
		file.close();
	}
	return fileData;
}
void OP::writeONfile(Client client, string fileName, string seperator)
{
	cout << client.getAccountNumber();
	fstream file;
	file.open(fileName, ios::app);
	if (file.is_open())
	{
		file << "\n";
		file << convertFromRecordTostring(client, seperator);
		file.close();
	}
}