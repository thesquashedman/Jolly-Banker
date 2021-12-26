#include "manager.h"

Manager::Manager()
{
	
}

void Manager::AddToQueue(string file_name)
{
	ifstream in_file;
	in_file.open(file_name);
	while (!in_file.eof())
	{
		Transaction* t = new Transaction();
		
		in_file >> *t;
		//cout << *t << endl;
		transaction_queue.push(*t);
		
	}
	in_file.close();
}

void Manager::PopQueue()
{
	while (!transaction_queue.empty())
	{
		Transaction* current_transaction = &transaction_queue.front();
		if (current_transaction->type() == 'O')
		{
			Account* temp;
			if (account_list_.Retrieve(current_transaction->id(), temp))
			{
				cerr << "ERROR: Account " << current_transaction->id() << " is already open.Transaction refused." << endl;
			}
			else
			{
				Account* insert_account = new Account(*current_transaction);
				account_list_.Insert(insert_account);
			}
		}
		else if (current_transaction->type() == 'W')
		{
			Account* temp;
			if (!account_list_.Retrieve(current_transaction->id(), temp))
			{
				cerr << "ERROR: Account " << current_transaction->id() <<" not found. Withdrawal refused." << endl;
			}
			else
			{
				if (!temp->Transact(*current_transaction))
				{
					cerr << "ERROR: Not enough funds to withdraw " << current_transaction->ammount() << " from fund " <<current_transaction->fund() <<  " of account #" << current_transaction->id() << "." << endl;
				}
			}
		}
		else if (current_transaction->type() == 'D')
		{
			Account* temp;
			if (!account_list_.Retrieve(current_transaction->id(), temp))
			{
				cerr << "ERROR: Account " << current_transaction->id() << " not found. Deposit refused." << endl;
			}
			else
			{
				temp->Transact(*current_transaction);
			}
		}
		else if (current_transaction->type() == 'T')
		{
			Account* temp1;
			Account* temp2;
			
			
			if (!account_list_.Retrieve(current_transaction->id1(), temp1))
			{
				cerr << "ERROR: Account " << current_transaction->id1() << " not found. Transfer refused." << endl;
			}
			else if (!account_list_.Retrieve(current_transaction->id2(), temp2))
			{
					cerr << "ERROR: Account " << current_transaction->id2() << " not found. Transfer refused." << endl;
			}
			else
			{
				if (!temp1->Transact(*current_transaction))
				{
					cerr << "ERROR: Not enough funds to transfer " << current_transaction->ammount() << " from fund " << current_transaction->fund1() << " of account #" << current_transaction->id1() << "." << endl;
				}
				temp2->Transact(*current_transaction);
			}
			
		}
		else
		{
			Account* temp;
			if (!account_list_.Retrieve(current_transaction->id(), temp))
			{
				cerr << "ERROR: Account " << current_transaction->id() << " not found. History refused." << endl;
			}
			else
			{
				temp->Transact(*current_transaction);
			}
		}
		transaction_queue.pop();
	}
	cout << "FINAL BALANCES:" << endl;
	account_list_.Display();
}
