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
AForm *Intern::makeForm(std::string formName, std::string target)
{
    std::string formNames[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    // Trouve l'index AVANT de créer
    for (int i = 0; i < 3; i++)
    {
        if (formName == formNames[i])
        {
            std::cout << "Intern creates " << formName << std::endl;
            
            // Crée SEULEMENT le bon formulaire
            if (i == 0)
                return new ShrubberyCreationForm(target);
            else if (i == 1)
                return new RobotomyRequestForm(target);
            else
                return new PresidentialPardonForm(target);
        }
    }
    
    std::cout << "Error: Form \"" << formName << "\" unknown" << std::endl;
    return NULL;
}
