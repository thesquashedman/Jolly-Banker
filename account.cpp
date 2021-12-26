#include "account.h"

Account::Account(Transaction t)
{
	name_ = t.name();
	id_ = t.id();
	head_ = nullptr;
	last_ = nullptr;
	for (int i = 0; i < 8; i++)
	{
		fund_ammounts_.push_back(0);
		funds_head_.push_back(nullptr);
		funds_last_.push_back(nullptr);
	}
}

Account::~Account()
{
	
}


bool Account::Transact(Transaction& transaction)
{
	if (transaction.type() == 'D')
	{
		fund_ammounts_[transaction.fund()] += transaction.ammount();
		AddToHistory(transaction);
		return true;
	}
	else if (transaction.type() == 'W')
	{
		if (transaction.ammount() > fund_ammounts_[transaction.fund()])
		{
			if (transaction.fund() == 0 || transaction.fund() == 2)
			{
				
				if (transaction.ammount() - fund_ammounts_[transaction.fund()] <= fund_ammounts_[transaction.fund() + 1])
				{
					
					Transaction* t = new Transaction('T', id_, transaction.fund() + 1, id_, transaction.fund(), transaction.ammount() - fund_ammounts_[transaction.fund()]);
					fund_ammounts_[transaction.fund() + 1] -= (transaction.ammount() - fund_ammounts_[transaction.fund()]);
					fund_ammounts_[transaction.fund()] = 0;
					AddToHistory(*t);
					AddToHistory(transaction);
					return true;
				}
			}
			else if (transaction.fund() == 1 || transaction.fund() == 3)
			{
				
				if (transaction.ammount() - fund_ammounts_[transaction.fund()] <= fund_ammounts_[transaction.fund() + 1])
				{
					
					Transaction* t = new Transaction('T', id_, transaction.fund() - 1, id_, transaction.fund(), transaction.ammount() - fund_ammounts_[transaction.fund()]);
					fund_ammounts_[transaction.fund() - 1] -= (transaction.ammount() - fund_ammounts_[transaction.fund()]);
					fund_ammounts_[transaction.fund()] = 0;
					AddToHistory(*t);
					AddToHistory(transaction);
					return true;
				}
			}
			transaction.setSuccess(false);
			AddToHistory(transaction);
			return false;
		}
		else
		{
			fund_ammounts_[transaction.fund()] -= transaction.ammount();
			AddToHistory(transaction);
			return true;
		}
	}
	else if (transaction.type() == 'T')
	{
		//If the ids and the funds are the same, do nothing. Don't even create a history for it.
		if (transaction.id1() == transaction.id2() && transaction.fund1() == transaction.fund2())
		{
			return true;
		}
		if (transaction.transfer() == false)
		{
			if (transaction.ammount() > fund_ammounts_[transaction.fund1()])
			{
				
				if (transaction.fund1() == 0 || transaction.fund1() == 2)
				{
					
					if (transaction.ammount() - fund_ammounts_[transaction.fund1()] <= fund_ammounts_[transaction.fund1() + 1])
					{
						
						Transaction* t = new Transaction('T', id_, transaction.fund1() + 1, id_, transaction.fund1(), transaction.ammount() - fund_ammounts_[transaction.fund1()]);
						fund_ammounts_[transaction.fund1() + 1] -= (transaction.ammount() - fund_ammounts_[transaction.fund1()]);
						fund_ammounts_[transaction.fund1()] = 0;
						transaction.setTransfer(true);
						AddToHistory(*t);
						AddToHistory(transaction);
						return true;
					}
				}
				else if (transaction.fund1() == 1 || transaction.fund1() == 3)
				{
					if (transaction.ammount() - fund_ammounts_[transaction.fund1()] <= fund_ammounts_[transaction.fund1() + 1])
					{

						Transaction* t = new Transaction('T', id_, transaction.fund1() - 1, id_, transaction.fund1(), transaction.ammount() - fund_ammounts_[transaction.fund1()]);
						fund_ammounts_[transaction.fund1() - 1] -= (transaction.ammount() - fund_ammounts_[transaction.fund1()]);
						fund_ammounts_[transaction.fund1()] = 0;
						transaction.setTransfer(true);
						AddToHistory(*t);
						AddToHistory(transaction);
						return true;
					}
				}
				transaction.setSuccess(false);
				transaction.setTransfer(true);
				AddToHistory(transaction);
				return false;
			}
			else
			{
				fund_ammounts_[transaction.fund1()] -= transaction.ammount();
				transaction.setTransfer(true);
				AddToHistory(transaction);
				return true;
			}
		}
		else
		{
			if (transaction.success() == false)
			{
				if (transaction.id1() != transaction.id2())
				{
					AddToHistory(transaction);
				}
				return false;
			}
			else
			{
				//cout << transaction.ammount() << endl;
				fund_ammounts_[transaction.fund2()] += transaction.ammount();
				if (transaction.id1() != transaction.id2())
				{
					AddToHistory(transaction);
				}
				return true;
			}
		}
	}
	else if (transaction.type() == 'A')
	{
		cout << "Transaction History for " << name_ << "." << endl;
		Node* ptr = head_;
		while (ptr != nullptr)
		{
			cout << *ptr->pTransaction;
			ptr = ptr->next;
			
		}
		//cout << endl;
	}
	else if (transaction.type() == 'F')
	{
		cout << "Transaction History for " << name_ << " fund #" << transaction.fund() << ": $" << fund_ammounts_[transaction.fund()] << endl;
		Node* ptr = funds_head_[transaction.fund()];
		while (ptr != nullptr)
		{
			cout << *ptr->pTransaction;
			ptr = ptr->next_fund;
		}
	}
	cout << endl;
	
}

int Account::id() const
{
	return id_;
}

bool Account::operator==(const Account& other_account)
{
	if (id_ == other_account.id_)
	{
		return true;
	}
	return false;
}

bool Account::operator<(const Account& other_account)
{
	if (id_ < other_account.id_)
	{
		return true;
	}
	return false;
}

bool Account::operator>(const Account& other_account)
{
	if (id_ > other_account.id_)
	{
		return true;
	}
	return false;
}

void Account::AddToHistory(Transaction& transaction)
{
	//cout << "adding to history: " << transaction << endl;
	Node* new_node = new Node;
	new_node->pTransaction = &transaction;
	new_node->next = nullptr;
	new_node->next_fund = nullptr;
	
	if (head_ == nullptr)
	{
		//cout << "head is nullptr" << endl;
		head_ = new_node;
		last_ = new_node;
		if (transaction.type() == 'T')
		{
			if (transaction.id1() == transaction.id2())
			{
				Node* second_node = new Node;
				second_node->pTransaction = &transaction;
				second_node->next = nullptr;
				second_node->next_fund = nullptr;
				funds_head_[transaction.fund1()] = new_node;
				funds_head_[transaction.fund2()] = second_node;
				funds_last_[transaction.fund1()] = new_node;
				funds_last_[transaction.fund2()] = second_node;
			}
			else if (id_ == transaction.id1())
			{
				funds_head_[transaction.fund1()] == new_node;
				funds_last_[transaction.fund1()] == new_node;
			}
			else if (id_ == transaction.id2())
			{
				funds_head_[transaction.fund2()] = new_node;
				funds_last_[transaction.fund2()] = new_node;
			}
		}
		else
		{
			funds_head_[transaction.fund()] = new_node;
			funds_last_[transaction.fund()] = new_node;
			
		}
	}
	else
	{
		last_->next = new_node;
		last_ = new_node;
		//cout << *last_->pTransaction << endl;
		if (transaction.type() == 'T')
		{
			if (transaction.id1() == transaction.id2())
			{
				Node* second_node = new Node;
				second_node->pTransaction = &transaction;
				second_node->next == nullptr;
				second_node->next_fund == nullptr;
				if (funds_head_[transaction.fund1()] == nullptr && funds_head_[transaction.fund2()] == nullptr)
				{
					funds_head_[transaction.fund1()] = new_node;
					funds_head_[transaction.fund2()] = second_node;
					funds_last_[transaction.fund1()] = new_node;
					funds_last_[transaction.fund2()] = second_node;
				}
				else if (funds_head_[transaction.fund1()] == nullptr)
				{
					funds_head_[transaction.fund1()] = new_node;
					funds_last_[transaction.fund1()] = new_node;
					funds_last_[transaction.fund2()]->next_fund = second_node;
					funds_last_[transaction.fund2()] = second_node;
				}
				else if (funds_head_[transaction.fund2()] == nullptr)
				{
					funds_head_[transaction.fund2()] = new_node;
					funds_last_[transaction.fund2()] = new_node;
					funds_last_[transaction.fund1()]->next_fund = second_node;
					funds_last_[transaction.fund1()] = second_node;
				}
				else
				{
					funds_last_[transaction.fund1()]->next_fund = new_node;
					funds_last_[transaction.fund1()] = new_node;
					funds_last_[transaction.fund2()]->next_fund = second_node;
					funds_last_[transaction.fund2()] = second_node;
				}

			}
			else if (id_ == transaction.id1())
			{
				if (funds_head_[transaction.fund1()] == nullptr)
				{
					funds_head_[transaction.fund1()] = new_node;
					funds_last_[transaction.fund1()] = new_node;
				}
				else
				{
					funds_last_[transaction.fund1()]->next_fund = new_node;
					funds_last_[transaction.fund1()] = new_node;
				}
			}
			else if (id_ == transaction.id2())
			{
				if (funds_head_[transaction.fund2()] == nullptr)
				{
					funds_head_[transaction.fund2()] = new_node;
					funds_last_[transaction.fund2()] = new_node;
				}
				else
				{
					funds_last_[transaction.fund2()]->next = new_node;
					funds_last_[transaction.fund2()] = new_node;
				}
			}
		}
		else
		{
			if (funds_head_[transaction.fund()] == nullptr)
			{
				funds_head_[transaction.fund()] = new_node;
				funds_last_[transaction.fund()] = new_node;
			}
			else
			{
				funds_last_[transaction.fund()]->next_fund = new_node;
				funds_last_[transaction.fund()] = new_node;
			}
		}
	}
	/*
	cout << "Account history" << endl;
	Node* ptr = head_;
	while (ptr != nullptr)
	{
		cout << *ptr->pTransaction << endl;
		ptr = ptr->next;

	}
	*/
	
}

ostream& operator<<(ostream& stream, const Account& account)
{
	stream << account.name_ << " Account ID: " << account.id_ << endl;
	stream << "    Money Market: " << account.fund_ammounts_[0] << endl;
	stream << "    Prime Money Market: " << account.fund_ammounts_[1] << endl;
	stream << "    Long-Term Bond: " << account.fund_ammounts_[2] << endl;
	stream << "    Short-Term Bond: " << account.fund_ammounts_[3] << endl;
	stream << "    500 Index Fund: " << account.fund_ammounts_[4] << endl;
	stream << "    Capital Value Fund: " << account.fund_ammounts_[5] << endl;
	stream << "    Growth Equity Fund: " << account.fund_ammounts_[6] << endl;
	stream << "    Growth Index Fund: " << account.fund_ammounts_[7] << endl;
	return stream;
}
