#include "Intern.hpp"

// Constructors
Intern::Intern()
{
	std::cout << "Intern default constructor called" << std::endl;
}

Intern::Intern(Intern const &src)
{
	(void)src;
	std::cout << "Intern copy constructor called" << std::endl;
}

// Destructor
Intern::~Intern()
{
	std::cout << "Intern destructed" << std::endl;
}

// Operator overload
Intern	&Intern::operator=(Intern const &rhs)
{
	(void)rhs;
	return (*this);
}

// Methods
AForm	*Intern::makeForm(std::string const &formName, std::string const &target)
{
	std::string formNames[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	AForm	*forms[3] = {
		new ShrubberyCreationForm(target),
		new RobotomyRequestForm(target),
		new PresidentialPardonForm(target)
	};

	int i;
	for (i = 0; i < 3; i++)
	{
		if (formName == formNames[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			// Delete the forms we didn't use
			for (int j = 0; j < 3; j++)
			{
				if (j != i)
					delete forms[j];
			}
			return (forms[i]);
		}
	}

	// If no match found, delete all forms and return NULL
	for (int j = 0; j < 3; j++)
		delete forms[j];
	
	std::cout << "Error: Form name \"" << formName << "\" is unknown" << std::endl;
	return (NULL);
}
