#include <iostream>
#include <exception>

class Account
{
public:
	Account(float balance) : m_balance(balance) {
	}

	void setAltSystem(Account *a) {
		m_successor = a;
	}

	void pay(float amount) {
		if (canPay(amount)) {
			std::cout << "Paid " << amount << " using " << getSystemName() << "\n";
		} else if (m_successor) {
			std::cout << "Cannot pay using " << getSystemName() << ". Proceeding...\n";
			m_successor->pay(amount);
		} else {
			throw "None of the accounts have enough balance.";
		}
	}

	virtual std::string getSystemName() {
		return "Account";
	}

private:
	bool canPay(float amount) {
		return (m_balance >= amount);
	}

private:
	Account *m_successor;
	float m_balance;
};

class Bank : public Account
{ 
public:
	Bank(float balance) : Account(balance) {
	}

	std::string getSystemName() {
		return "Bank";
	}
};

class PayPal : public Account
{
public:
	PayPal(float balance) : Account(balance) {
	}

	std::string getSystemName() {
		return "PayPal";
	}
};

class Bitcoin : public Account
{
public:
	Bitcoin(float balance) : Account(balance) {
	}

	std::string getSystemName() {
		return "Bitcoin";
	}
};

int main(void)
{
	Bank bank(100);
	PayPal payPal(200);
	Bitcoin bitcoin(300);

	bank.setAltSystem(&payPal);
	payPal.setAltSystem(&bitcoin);

	bank.pay(250);
	
	return 0;
}
