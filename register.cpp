#include "register.h"

Register::Register(bool hasValue, GetFunc onGet = nullptr, SetFunc onSet = nullptr) :
	hasValue(hasValue),
	onGet(onGet),
	onSet(onSet),
	val(0)
{ }

int Register::GetValue()
{
	if (onGet)
	{
		return onGet(val, hasValue);
	}

	return val;
}

void Register::SetValue(int value)
{
	if (onSet)
	{
		onSet(val, hasValue, requestingInput, value);
		return;
	}

	val = value;
}

bool Register::HasValue()
{
	return hasValue;
}

void Register::RequestInput()
{
	requestingInput = true;
}

bool Register::IsRequestingInput()
{
	return requestingInput;
}

Register GenNonvolatileRegister()
{
	return Register(true);
}

Register GenVolatileRegister()
{
	auto onGet = [](int &val, bool &hasValue)
	{
		int temp = val;
		val = 0;
		hasValue = false;
		return temp;
	};

	auto onSet = [](int &val, bool &hasValue, bool &requestingInput, int value)
	{
		val = value;
		hasValue = true;
		requestingInput = false;
	};

	return Register(false, onGet, onSet);
}