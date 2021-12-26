#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Transaction
{
public:
	Transaction();
	//For deposit and withdrawal
	Transaction(char type, int id, int fund, int ammount);
	//For transfer
	Transaction(char type, int id1, int fund1, int id2, int fund2, int ammount);
	//For transaction history
	Transaction(char type, int id);
	//For fund transaction history
	Transaction(char type, int id, int fund);
	//For opening account
	Transaction(char type, int id, string name);

	//Getters
	char type();
	int id();
	int id1();
	int id2();
	int fund();
	int fund1();
	int fund2();
	int ammount();
	string name();
	bool success();
	bool transfer();

	//setters
	void setType(char type);
	void setID(int id);
	void setID1(int id1);
	void setID2(int id2);
	void setFund(int fund);
	void setFund1(int fund1);
	void setFund2(int fund2);
	void setAmmount(int ammount);
	void setName(string name);
	void setSuccess(bool success);
	void setTransfer(bool transfer);


	friend ostream& operator<<(ostream& stream, const Transaction& account);
	friend istream& operator>>(istream& stream, Transaction& transaction);


private:
	char type_;
	int id_;
	int id1_;
	int id2_;
	int fund_;
	int fund1_;
	int fund2_;
	int ammount_;
	string name_;
	bool success_;
	bool transfer_;
};
#endif