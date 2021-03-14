#include <string>

using namespace std;

class INotifier {
public:
	virtual void Notify(const string& message) = 0;
};

class SmsNotifier : public INotifier {
	string phoneNumber;
public:
	SmsNotifier(const string& _phoneNumber): phoneNumber(_phoneNumber) {};
	void Notify(const string& message) override {
		SendSms(phoneNumber, message);
	};
};

class EmailNotifier : public INotifier {
	string emailAddress;
public:
	EmailNotifier(const string& _emailAddress) : emailAddress(_emailAddress) {};
	void Notify(const string& message) override {
		SendEmail(emailAddress, message);
	};
};