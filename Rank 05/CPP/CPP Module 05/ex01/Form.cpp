#include "Form.hpp"

// Constructors
Form::Form() : _name("Default"), _isSigned(false), _signGrade(150), _execGrade(150)
{
	std::cout << "Form default constructor called" << std::endl;
}

Form::Form(std::string const &name, int signGrade, int execGrade) 
	: _name(name), _isSigned(false), _signGrade(signGrade), _execGrade(execGrade)
{
	if (signGrade < 1 || execGrade < 1)
		throw Form::GradeTooHighException();
	if (signGrade > 150 || execGrade > 150)
		throw Form::GradeTooLowException();
	std::cout << "Form " << this->_name << ", unsigned, sign grade " << this->_signGrade 
			  << ", exec grade " << this->_execGrade << " constructed" << std::endl;
}

Form::Form(Form const &src) 
	: _name(src._name), _isSigned(src._isSigned), _signGrade(src._signGrade), _execGrade(src._execGrade)
{
	std::cout << "Form copy constructor called" << std::endl;
}

// Destructor
Form::~Form()
{
	std::cout << "Form " << this->_name << " destructed" << std::endl;
}

// Operator overload
Form	&Form::operator=(Form const &rhs)
{
	if (this != &rhs)
		this->_isSigned = rhs._isSigned;
	return (*this);
}

// Getters
std::string const	&Form::getName() const
{
	return (this->_name);
}

bool	Form::getIsSigned() const
{
	return (this->_isSigned);
}

int	Form::getSignGrade() const
{
	return (this->_signGrade);
}

int	Form::getExecGrade() const
{
	return (this->_execGrade);
}

// Methods
void	Form::beSigned(Bureaucrat const &bureaucrat)
{
	if (bureaucrat.getGrade() > this->_signGrade)
		throw Form::GradeTooLowException();
	this->_isSigned = true;
}

// Exceptions
const char	*Form::GradeTooHighException::what() const throw()
{
	return ("Grade is too high!");
}

const char	*Form::GradeTooLowException::what() const throw()
{
	return ("Grade is too low!");
}

// Operator overload
std::ostream	&operator<<(std::ostream &o, Form const &rhs)
{
	o << "Form " << rhs.getName() << ", " 
	  << (rhs.getIsSigned() ? "signed" : "unsigned") 
	  << ", sign grade " << rhs.getSignGrade() 
	  << ", exec grade " << rhs.getExecGrade();
	return (o);
}
