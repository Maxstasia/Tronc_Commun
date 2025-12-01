#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	std::cout << "=== Test 1: ShrubberyCreationForm ===" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 137);
		ShrubberyCreationForm form1("home");
		
		std::cout << form1 << std::endl;
		alice.signForm(form1);
		alice.executeForm(form1);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: RobotomyRequestForm ===" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 45);
		RobotomyRequestForm form2("Bender");
		
		std::cout << form2 << std::endl;
		bob.signForm(form2);
		bob.executeForm(form2);
		bob.executeForm(form2);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: PresidentialPardonForm ===" << std::endl;
	try
	{
		Bureaucrat charlie("Charlie", 5);
		PresidentialPardonForm form3("Arthur Dent");
		
		std::cout << form3 << std::endl;
		charlie.signForm(form3);
		charlie.executeForm(form3);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Execute without signing ===" << std::endl;
	try
	{
		Bureaucrat dave("Dave", 1);
		PresidentialPardonForm form4("Nobody");
		
		dave.executeForm(form4); // Not signed yet
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Grade too low to execute ===" << std::endl;
	try
	{
		Bureaucrat eve("Eve", 50);
		PresidentialPardonForm form5("Someone");
		
		Bureaucrat signer("Signer", 1);
		signer.signForm(form5);
		eve.executeForm(form5); // Grade too low to execute
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 6: Multiple forms ===" << std::endl;
	try
	{
		Bureaucrat admin("Admin", 1);
		
		ShrubberyCreationForm shrub("garden");
		RobotomyRequestForm robot("R2D2");
		PresidentialPardonForm pardon("Ford Prefect");
		
		admin.signForm(shrub);
		admin.signForm(robot);
		admin.signForm(pardon);
		
		admin.executeForm(shrub);
		admin.executeForm(robot);
		admin.executeForm(pardon);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return (0);
}
