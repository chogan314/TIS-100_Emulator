#ifndef REGISTER_H
#define REGISTER_H

typedef int(*GetFunc)(int &regVal, bool &hasValue);
typedef void(*SetFunc)(int &regVal, bool &hasValue, bool &requestingInput, int value);

class Register
{
public:
	Register(bool hasValue, GetFunc onGet, SetFunc onSet);
	int GetValue();
	void SetValue(int value);
	bool HasValue();
	bool IsRequestingInput();
	void RequestInput();
private:
	int val;
	bool hasValue;
	bool requestingInput = false;
	GetFunc onGet;
	SetFunc onSet;
};

Register GenNonvolatileRegister();
Register GenVolatileRegister();

#endif