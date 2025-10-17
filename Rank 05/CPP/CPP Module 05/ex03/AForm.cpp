#include "AForm.hpp"

// Constructors
AForm::AForm() : _name("Default"), _isSigned(false), _signGrade(150), _execGrade(150)
{
	std::cout << "AForm default constructor called" << std::endl;
}

AForm::AForm(std::string const &name, int signGrade, int execGrade) 
	: _name(name), _isSigned(false), _signGrade(signGrade), _execGrade(execGrade)
{
	if (signGrade < 1 || execGrade < 1)
		throw AForm::GradeTooHighException();
	if (signGrade > 150 || execGrade > 150)
		throw AForm::GradeTooLowException();
}

AForm::AForm(AForm const &src) 
	: _name(src._name), _isSigned(src._isSigned), _signGrade(src._signGrade), _execGrade(src._execGrade)
{
	std::cout << "AForm copy constructor called" << std::endl;
}

// Destructor
AForm::~AForm()
{
	std::cout << "AForm " << this->_name << " destructed" << std::endl;
}

// Operator overload
AForm	&AForm::operator=(AForm const &rhs)
{
	if (this != &rhs)
		this->_isSigned = rhs._isSigned;
	return (*this);
}

// Getters
std::string const	&AForm::getName() const
{
	return (this->_name);
}

bool	AForm::getIsSigned() const
{
	return (this->_isSigned);
}

int	AForm::getSignGrade() const
{
	return (this->_signGrade);
}

int	AForm::getExecGrade() const
{
	return (this->_execGrade);
}

// Methods
void	AForm::beSigned(Bureaucrat const &bureaucrat)
{
	if (bureaucrat.getGrade() > this->_signGrade)
		throw AForm::GradeTooLowException();
	this->_isSigned = true;
}

void	AForm::execute(Bureaucrat const &executor) const
{
	if (!this->_isSigned)
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > this->_execGrade)
		throw AForm::GradeTooLowException();
	this->executeAction();
}

// Exceptions
const char	*AForm::GradeTooHighException::what() const throw()
{
	return ("Grade is too high!");
}

const char	*AForm::GradeTooLowException::what() const throw()
{
	return ("Grade is too low!");
}

const char	*AForm::FormNotSignedException::what() const throw()
{
	return ("Form is not signed!");
}

// Operator overload
std::ostream	&operator<<(std::ostream &o, AForm const &rhs)
{
	o << "Form " << rhs.getName() << ", " 
	  << (rhs.getIsSigned() ? "signed" : "unsigned") 
	  << ", sign grade " << rhs.getSignGrade() 
	  << ", exec grade " << rhs.getExecGrade();
	return (o);
}
