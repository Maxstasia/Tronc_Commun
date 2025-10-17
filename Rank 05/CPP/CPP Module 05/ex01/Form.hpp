#ifndef FORM_HPP
# define FORM_HPP

# include <string>
# include <iostream>
# include <exception>
# include "Bureaucrat.hpp"

class Form
{
	private:
		std::string const	_name;
		bool				_isSigned;
		int const			_signGrade;
		int const			_execGrade;

	public:
		// Orthodox Canonical Form
		Form();
		Form(std::string const &name, int signGrade, int execGrade);
		Form(Form const &src);
		~Form();
		Form &operator=(Form const &rhs);

		// Getters
		std::string const	&getName() const;
		bool				getIsSigned() const;
		int					getSignGrade() const;
		int					getExecGrade() const;

		// Methods
		void	beSigned(Bureaucrat const &bureaucrat);

		// Exceptions
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

// Operator overload
std::ostream	&operator<<(std::ostream &o, Form const &rhs);

#endif
