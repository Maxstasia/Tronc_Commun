#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(ScalarConverter const &src)
{
	(void)src;
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &rhs)
{
	(void)rhs;
	return (*this);
}

bool ScalarConverter::isPseudoLiteral(std::string const &literal)
{
	return (literal == "nan" || literal == "nanf" ||
			literal == "+inf" || literal == "-inf" ||
			literal == "+inff" || literal == "-inff" ||
			literal == "inf" || literal == "inff");
}

ScalarConverter::Type ScalarConverter::detectType(std::string const &literal)
{
	if (literal.empty())
		return INVALID;

	if (isPseudoLiteral(literal))
		return DOUBLE;

	// Check for char
	if (literal.length() == 1 && !std::isdigit(literal[0]))
		return CHAR;

	// Check for single quoted char
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
		return CHAR;

	// Check for float (ends with 'f')
	if (literal[literal.length() - 1] == 'f')
		return FLOAT;

	// Check if it contains a decimal point
	bool hasDecimal = literal.find('.') != std::string::npos;

	// Try to parse as int
	char *end;
	errno = 0;
	long val = std::strtol(literal.c_str(), &end, 10);
	if (errno == 0 && *end == '\0' && val >= std::numeric_limits<int>::min() 
		&& val <= std::numeric_limits<int>::max())
		return INT;

	// If it has a decimal point, it's a double
	if (hasDecimal)
		return DOUBLE;

	return INVALID;
}

void ScalarConverter::convertChar(std::string const &literal)
{
	char c;
	
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
		c = literal[1];
	else
		c = literal[0];

	// Print char
	std::cout << "char: '" << c << "'" << std::endl;

	// Print int
	std::cout << "int: " << static_cast<int>(c) << std::endl;

	// Print float
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;

	// Print double
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void ScalarConverter::convertInt(std::string const &literal)
{
	char *end;
	errno = 0;
	long val = std::strtol(literal.c_str(), &end, 10);

	if (errno != 0 || *end != '\0')
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	int i = static_cast<int>(val);

	// Print char
	if (val < 0 || val > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<char>(i)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;

	// Print int
	std::cout << "int: " << i << std::endl;

	// Print float
	float f = static_cast<float>(i);
	std::cout << "float: " << f;
	if (f == static_cast<int>(f))
		std::cout << ".0";
	std::cout << "f" << std::endl;

	// Print double
	double d = static_cast<double>(i);
	std::cout << "double: " << d;
	if (d == static_cast<int>(d))
		std::cout << ".0";
	std::cout << std::endl;
}

void ScalarConverter::convertFloat(std::string const &literal)
{
	std::string str = literal.substr(0, literal.length() - 1);
	char *end;
	errno = 0;
	float f = std::strtof(str.c_str(), &end);

	if (errno != 0 || *end != '\0')
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	// Print char
	if (std::isnan(f) || std::isinf(f) || f < 0 || f > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<char>(f)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;

	// Print int
	if (std::isnan(f) || std::isinf(f) || f < std::numeric_limits<int>::min() 
		|| f > std::numeric_limits<int>::max())
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(f) << std::endl;

	// Print float
	std::cout << "float: " << f;
	if (!std::isnan(f) && !std::isinf(f) && f == static_cast<int>(f))
		std::cout << ".0";
	std::cout << "f" << std::endl;

	// Print double
	double d = static_cast<double>(f);
	std::cout << "double: " << d;
	if (!std::isnan(d) && !std::isinf(d) && d == static_cast<int>(d))
		std::cout << ".0";
	std::cout << std::endl;
}

void ScalarConverter::convertDouble(std::string const &literal)
{
	char *end;
	errno = 0;
	double d = std::strtod(literal.c_str(), &end);

	if (errno != 0 || *end != '\0')
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	// Print char
	if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<char>(d)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;

	// Print int
	if (std::isnan(d) || std::isinf(d) || d < std::numeric_limits<int>::min() 
		|| d > std::numeric_limits<int>::max())
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;

	// Print float
	float f = static_cast<float>(d);
	std::cout << "float: " << f;
	if (!std::isnan(f) && !std::isinf(f) && f == static_cast<int>(f))
		std::cout << ".0";
	std::cout << "f" << std::endl;

	// Print double
	std::cout << "double: " << d;
	if (!std::isnan(d) && !std::isinf(d) && d == static_cast<int>(d))
		std::cout << ".0";
	std::cout << std::endl;
}

void ScalarConverter::convertPseudoLiteral(std::string const &literal)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;

	if (literal == "nanf" || literal == "+inff" || literal == "-inff" || literal == "inff")
	{
		std::cout << "float: " << literal << std::endl;
		std::string dLiteral = literal.substr(0, literal.length() - 1);
		std::cout << "double: " << dLiteral << std::endl;
	}
	else
	{
		std::cout << "float: " << literal << "f" << std::endl;
		std::cout << "double: " << literal << std::endl;
	}
}

void ScalarConverter::convert(std::string const &literal)
{
	if (isPseudoLiteral(literal))
	{
		convertPseudoLiteral(literal);
		return;
	}

	Type type = detectType(literal);

	switch (type)
	{
		case CHAR:
			convertChar(literal);
			break;
		case INT:
			convertInt(literal);
			break;
		case FLOAT:
			convertFloat(literal);
			break;
		case DOUBLE:
			convertDouble(literal);
			break;
		default:
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			break;
	}
}
