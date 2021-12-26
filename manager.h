#ifndef MANAGER_H_
#define MANAGER_H_

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include "transaction.h"
#include "account.h"
#include "bstree.h"
class Manager
{
public:
	Manager();


	//creates transaction and adds it to queue.
	void AddToQueue(string file_name);
	//Gets transactions, finds/creates account/s based off transaction type and id, and pushes transaction into account/s for processing
	//If account is created, also gets put into BSTree.
	void PopQueue();
	
	

private:
	BSTree account_list_;
	queue<Transaction> transaction_queue;
};
#endif

