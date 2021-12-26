#include "bstree.h"

BSTree::BSTree()
{
	Node* top = new Node;
	top->pAccount = nullptr;
	top->left = nullptr;
	top->right = nullptr;
	root = top;
}

BSTree::~BSTree()
{
	Empty();
	delete root;
}

bool BSTree::Insert(Account* account)
{
	if (isEmpty())
	{
		root->pAccount = account;
		return true;
	}
	if (*account == *root->pAccount)
	{
		return false;
	}

	Node* ptr = root;
	while (true)
	{
		
		if (*account == *ptr->pAccount)
		{
			return false;

		}
		if (*account < *ptr->pAccount)
		{
			if (ptr->left == nullptr)
			{
				Node* insert_node = new Node;
				insert_node->pAccount = account;
				insert_node->left = nullptr;
				insert_node->right = nullptr;
				ptr->left = insert_node;
				return true;
			}
			else
			{
				ptr = ptr->left;
			}
		}
		else if (*account > *ptr->pAccount)
		{
			if (ptr->right == nullptr)
			{
				Node* insert_node = new Node;
				insert_node->pAccount = account;
				insert_node->left = nullptr;
				insert_node->right = nullptr;
				ptr->right = insert_node;
				return true;
			}
			else
			{
				ptr = ptr->right;
			}
		}

	}
		
	

}

bool BSTree::Retrieve(const int& id, Account*& account)
{
	if (isEmpty())
	{
		return false;
	}
	if (id == root->pAccount->id())
	{
		
		account = root->pAccount;
		return true;
	}
	Node* ptr = root;
	while (true)
	{
		if (id == ptr->pAccount->id())
		{

			account = ptr->pAccount;
			return true;
		}
		if (id < ptr->pAccount->id())
		{
			if (ptr->left == nullptr)
			{
				return false;
			}
			ptr = ptr->left;
		}
		else if (id > ptr->pAccount->id())
		{
			if (ptr->right == nullptr)
			{
				return false;
			}
			ptr = ptr->right;
		}
	}
}

void BSTree::Display() const
{
	if (isEmpty())
	{
		cout << "No account" << endl;
	}
	else
	{
		if (root->left != nullptr)
		{
			RecursiveDisplay(root->left);
		}
		cout << *root->pAccount << endl;
		if (root->right != nullptr)
		{
			RecursiveDisplay(root->right);
		}
	}
}

void BSTree::Empty()
{
	
	if (root->left != nullptr)
	{
		RecursiveEmpty(root->left);
	}
	if (root->right != nullptr)
	{
		RecursiveEmpty(root->right);
	}
	delete root->pAccount;
	root->pAccount = nullptr;
	root->left = nullptr;
	root->right = nullptr;
}

bool BSTree::isEmpty() const
{
	if (root->pAccount == nullptr)
	{
		return true;
	}
	return false;
}

void BSTree::RecursiveDisplay(Node* current_node) const
{
	if (current_node->left != nullptr)
	{
		RecursiveDisplay(current_node->left);
	}
	cout << *current_node->pAccount << endl;
	if (current_node->right != nullptr)
	{
		RecursiveDisplay(current_node->right);
	}
}

void BSTree::RecursiveEmpty(Node* current_node)
{
	
	if (current_node->left != nullptr)
	{
		RecursiveEmpty(current_node->left);
	}
	if (current_node->right != nullptr)
	{
		RecursiveEmpty(current_node->right);
	}
	delete current_node->pAccount;
	delete current_node;

}
