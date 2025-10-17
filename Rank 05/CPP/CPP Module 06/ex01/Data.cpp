#include "Data.hpp"

Data::Data() : name("default"), value(0)
{
}

Data::Data(std::string name, int value) : name(name), value(value)
{
}

Data::Data(Data const &src) : name(src.name), value(src.value)
{
}

Data::~Data()
{
}

Data &Data::operator=(Data const &rhs)
{
	if (this != &rhs)
	{
		this->name = rhs.name;
		this->value = rhs.value;
	}
	return (*this);
}
