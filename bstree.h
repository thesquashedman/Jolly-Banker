#ifndef BS_TREE_H_
#define BS_TREE_H_

#include "account.h"

class BSTree
{
public:
	BSTree();
	~BSTree();

	bool Insert(Account* account);
	bool Retrieve(const int& id, Account*& account);

	void Display() const;
	void Empty();
	bool isEmpty() const;
private:
	
	struct Node
	{
		Account* pAccount;
		Node* right;
		Node* left;
	};
	Node* root;

	void RecursiveDisplay(Node* current_node) const;
	void RecursiveEmpty(Node* current_node);

};
#endif 

