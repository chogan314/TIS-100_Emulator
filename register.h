#ifndef REGISTER_H
#define REGISTER_H

typedef int(*GetFunc)(int &regVal);
typedef void(*SetFunc)(int &regVal, int value);

class Register
{
public:
	Register(GetFunc onGet, SetFunc onSet);
	int GetValue();
	void SetValue(int value);
private:
	int val;
	GetFunc onGet;
	SetFunc onSet;
};

Register GenNonvolatileRegister();
Register GenVolatileRegister();

#endif