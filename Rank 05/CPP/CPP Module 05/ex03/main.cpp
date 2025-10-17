#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
	std::cout << "=== Test 1: Intern creates ShrubberyCreationForm ===" << std::endl;
	{
		Intern someRandomIntern;
		AForm *form;
		
		form = someRandomIntern.makeForm("shrubbery creation", "home");
		if (form)
		{
			Bureaucrat bob("Bob", 1);
			bob.signForm(*form);
			bob.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n=== Test 2: Intern creates RobotomyRequestForm ===" << std::endl;
	{
		Intern someRandomIntern;
		AForm *form;
		
		form = someRandomIntern.makeForm("robotomy request", "Bender");
		if (form)
		{
			Bureaucrat alice("Alice", 1);
			alice.signForm(*form);
			alice.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n=== Test 3: Intern creates PresidentialPardonForm ===" << std::endl;
	{
		Intern someRandomIntern;
		AForm *form;
		
		form = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
		if (form)
		{
			Bureaucrat charlie("Charlie", 1);
			charlie.signForm(*form);
			charlie.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n=== Test 4: Intern tries to create unknown form ===" << std::endl;
	{
		Intern someRandomIntern;
		AForm *form;
		
		form = someRandomIntern.makeForm("unknown form", "target");
		if (form)
			delete form;
		else
			std::cout << "Form creation failed as expected" << std::endl;
	}

	std::cout << "\n=== Test 5: Multiple forms created by same intern ===" << std::endl;
	{
		Intern someRandomIntern;
		Bureaucrat admin("Admin", 1);
		
		AForm *form1 = someRandomIntern.makeForm("shrubbery creation", "garden");
		AForm *form2 = someRandomIntern.makeForm("robotomy request", "R2D2");
		AForm *form3 = someRandomIntern.makeForm("presidential pardon", "Ford Prefect");
		
		if (form1)
		{
			admin.signForm(*form1);
			admin.executeForm(*form1);
			delete form1;
		}
		
		if (form2)
		{
			admin.signForm(*form2);
			admin.executeForm(*form2);
			delete form2;
		}
		
		if (form3)
		{
			admin.signForm(*form3);
			admin.executeForm(*form3);
			delete form3;
		}
	}

	return (0);
}
