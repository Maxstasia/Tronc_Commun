#ifndef DATA_HPP
# define DATA_HPP

# include <string>

struct Data
{
	std::string	name;
	int			value;
	
	Data();
	Data(std::string name, int value);
	Data(Data const &src);
	~Data();
	Data &operator=(Data const &rhs);
};

#endif
