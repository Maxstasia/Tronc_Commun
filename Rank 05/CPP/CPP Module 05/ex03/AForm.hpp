#ifndef AFORM_HPP
# define AFORM_HPP

# include <string>
# include <iostream>
# include <exception>
# include "Bureaucrat.hpp"

class AForm
{
	private:
		std::string const	_name;
		bool				_isSigned;
		int const			_signGrade;
		int const			_execGrade;

	public:
		// Orthodox Canonical Form
		AForm();
		AForm(std::string const &name, int signGrade, int execGrade);
		AForm(AForm const &src);
		virtual ~AForm();
		AForm &operator=(AForm const &rhs);

		// Getters
		std::string const	&getName() const;
		bool				getIsSigned() const;
		int					getSignGrade() const;
		int					getExecGrade() const;

		// Methods
		void			beSigned(Bureaucrat const &bureaucrat);
		void			execute(Bureaucrat const &executor) const;
		virtual void	executeAction() const = 0;

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

		class FormNotSignedException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

// Operator overload
std::ostream	&operator<<(std::ostream &o, AForm const &rhs);

#endif
