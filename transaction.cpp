#include "transaction.h"

Transaction::Transaction()
{
	success_ = true;
	transfer_ = false;
}

Transaction::Transaction(char type, int id, int fund, int ammount)
{
	type_ = type;
	id_ = id;
	fund_ = fund;
	ammount_ = ammount;
	success_ = true;

}

Transaction::Transaction(char type, int id1, int fund1, int id2, int fund2, int ammount)
{
	type_ = type;
	id1_ = id1;
	fund1_ = fund1;
	id2_ = id2;
	fund2_ = fund2;
	ammount_ = ammount;
	success_ = true;
	transfer_ = false;
}

Transaction::Transaction(char type, int id)
{
	type_ = type;
	id_ = id;
	success_ = true;
}

Transaction::Transaction(char type, int id, int fund)
{
	type_ = type;
	id_ = id;
	fund_ = fund;
	success_ = true;
}

Transaction::Transaction(char type, int id, string name)
{
	type_ = type;
	id_ = id;
	name_ = name;
	success_ = true;
}

char Transaction::type()
{
	return type_;
}

int Transaction::id()
{
	return id_;
}

int Transaction::id1()
{
	return id1_;
}

int Transaction::id2()
{
	return id2_;
}

int Transaction::fund()
{
	return fund_;
}

int Transaction::fund1()
{
	return fund1_;
}

int Transaction::fund2()
{
	return fund2_;
}

int Transaction::ammount()
{
	return ammount_;
}

string Transaction::name()
{
	return name_;
}

bool Transaction::success()
{
	return success_;
}

bool Transaction::transfer()
{
	return transfer_;
}

void Transaction::setType(char type)
{
	type_ = type;
}

void Transaction::setID(int id)
{
	id_ = id;
}

void Transaction::setID1(int id1)
{
	id1_ = id1;
}

void Transaction::setID2(int id2)
{
	id2_ = id2;
}

void Transaction::setFund(int fund)
{
	fund_ = fund;
}

void Transaction::setFund1(int fund1)
{
	fund1_ = fund1;
}

void Transaction::setFund2(int fund2)
{
	fund2_ = fund2;
}

void Transaction::setAmmount(int ammount)
{
	ammount_ = ammount;
}

void Transaction::setName(string name)
{
	name_ = name;
}

void Transaction::setSuccess(bool success)
{
	success_ = success;
}

void Transaction::setTransfer(bool transfer)
{
	transfer_ = transfer;
}

ostream& operator<<(ostream& stream, const Transaction& transaction)
{
	if (transaction.type_ == 'O')
	{
		stream << "  " << transaction.type_ << " " << transaction.id_ << " " << transaction.name_;
		if (transaction.success_ == false)
		{
			stream << " (Failed)";
		}
		stream << endl;
		return stream;
	}
	if (transaction.type_ == 'W' || transaction.type_ == 'D')
	{
		stream << "  " << transaction.type_ << " " << transaction.id_ << " " << transaction.fund_ << " " << transaction.ammount_;
		if (transaction.success_ == false)
		{
			stream << " (Failed)";
		}
		stream << endl;
		return stream;
	}
	if (transaction.type_ == 'A')
	{
		stream << "  " << transaction.type_ << " " << transaction.id_;
		if (transaction.success_ == false)
		{
			stream << " (Failed)";
		}
		stream << endl;
		return stream;
	}
	if (transaction.type_ == 'F')
	{
		stream << "  " << transaction.type_ << " " << transaction.id_ << " " << transaction.fund_;
		if (transaction.success_ == false)
		{
			stream << " (Failed)";
		}
		stream << endl;
		return stream;
	}
	if (transaction.type_ == 'T')
	{
		stream << "  " << transaction.type_ << " " << transaction.id1_ << " " << transaction.fund1_ << " " << transaction.id2_ << " " << transaction.fund2_ << " " << transaction.ammount_;
		if (transaction.success_ == false)
		{
			stream << " (Failed)";
		}
		stream << endl;
		return stream;
	}
	stream << "Bad Transaction" << endl;
	return stream;




}

istream& operator>>(istream& stream, Transaction& transaction)
{
	char type;
	//int id = 1;
	//string name = "billy";
	stream >> type;
	transaction.setType(type);
	
	if (type == 'W' || type == 'D')
	{
		int id;
		int fund;
		int ammount;
		stream >> id >> fund >> ammount;
		transaction.setID(id);
		transaction.setFund(fund);
		transaction.setAmmount(ammount);
		return stream;
	}
	else if (type == 'O')
	{
		int id;
		string name1;
		string name2;
		stream >> id >> name1 >> name2;
		transaction.setID(id);
		name2 += " " + name1;
		transaction.setName(name2);
		return stream;
	}
	else if (type == 'A')
	{
		int id;
		stream >> id;
		transaction.setID(id);
		return stream;
	}
	else if (type == 'F')
	{
		int id;
		int fund;
		stream >> id >> fund;
		transaction.setID(id);
		transaction.setFund(fund);
		return stream;
	}
	else if (type == 'T')
	{
		int id1;
		int fund1;
		int id2;
		int fund2;
		int ammount;
		stream >> id1 >> fund1 >> id2 >> fund2 >> ammount;
		transaction.setID1(id1);
		transaction.setFund1(fund1);
		transaction.setID2(id2);
		transaction.setFund2(fund2);
		transaction.setAmmount(ammount);
		return stream;
	}
	
	cout << "Cannot Read File" << endl;
	return stream;
	
	
	
}
