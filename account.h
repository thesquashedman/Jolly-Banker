#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <iostream>
#include <vector>
#include "transaction.h"
class Account
{
public:
	
	
	Account(Transaction t);
	~Account();

	//Handles transaction logic for the different kinds of transactions.
	bool Transact(Transaction& transaction);
	int id() const;


	bool operator==(const Account& other_account);
	bool operator<(const Account& other_account);
	bool operator>(const Account& other_account);

	friend ostream& operator<<(ostream& stream, const Account& account);

private:
	Account();
	void AddToHistory(Transaction& transaction);
	int id_;
	string name_;
	vector<int> fund_ammounts_;


	//Node for LinkedList holding transaction history. Does not include history
	//next corresponds to the transaction that's next in history
	//next_fund corresponds to the transaction that's next in each fund's history.
	//success corresponds to whether the transaction was complete or not.
	struct Node
	{
		Transaction* pTransaction;
		Node* next;
		Node* next_fund;
	};
	//First transaction in transaction history, should always be the transaction that opened the account.
	Node* head_;
	//First transaction in specific fund, is nullptr if empty
	vector<Node*> funds_head_;
	//Last transaction in transaction history, for appending transactions to end of list
	Node* last_;
	//Last transaction in each fund's transaction history, for appending transactions to end of fund's list
	vector<Node*> funds_last_;
	
};
#endif

