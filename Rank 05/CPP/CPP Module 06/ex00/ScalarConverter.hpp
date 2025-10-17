#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>
# include <iostream>
# include <sstream>
# include <limits>
# include <cmath>
# include <cerrno>
# include <cstdlib>

class ScalarConverter
{
	private:
		ScalarConverter();
		ScalarConverter(ScalarConverter const &src);
		~ScalarConverter();
		ScalarConverter &operator=(ScalarConverter const &rhs);

		enum Type {
			CHAR,
			INT,
			FLOAT,
			DOUBLE,
			INVALID
		};

		static Type detectType(std::string const &literal);
		static bool isPseudoLiteral(std::string const &literal);
		static void convertChar(std::string const &literal);
		static void convertInt(std::string const &literal);
		static void convertFloat(std::string const &literal);
		static void convertDouble(std::string const &literal);
		static void convertPseudoLiteral(std::string const &literal);

	public:
		static void convert(std::string const &literal);
};

#endif
