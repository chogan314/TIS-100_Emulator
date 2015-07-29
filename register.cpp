#include "register.h"

Register::Register(GetFunc onGet = nullptr, SetFunc onSet = nullptr) :
	onGet(onGet),
	onSet(onSet),
	val(0)
{ }

int Register::GetValue()
{
	if (onGet)
	{
		return onGet(val);
	}

	return val;
}

void Register::SetValue(int value)
{
	if (onSet)
	{
		onSet(val, value);
		return;
	}

	val = value;
}

Register GenNonvolatileRegister()
{
	return Register();
}

Register GenVolatileRegister()
{
	auto onGet = [](int &val)
	{
		int temp = val;
		val = 0;
		return temp;
	};

	return Register(onGet);
}