#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	std::cout << "=== Test 1: Valid Form Creation ===" << std::endl;
	try
	{
		Form form1("TaxForm", 50, 25);
		std::cout << form1 << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 2: Form with grade too high ===" << std::endl;
	try
	{
		Form form2("InvalidForm", 0, 25);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 3: Form with grade too low ===" << std::endl;
	try
	{
		Form form3("InvalidForm", 50, 151);
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 4: Bureaucrat can sign form ===" << std::endl;
	try
	{
		Bureaucrat alice("Alice", 30);
		Form form4("PermitForm", 50, 25);
		std::cout << form4 << std::endl;
		alice.signForm(form4);
		std::cout << form4 << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 5: Bureaucrat cannot sign form (grade too low) ===" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 100);
		Form form5("TopSecretForm", 50, 25);
		std::cout << form5 << std::endl;
		bob.signForm(form5);
		std::cout << form5 << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n=== Test 6: Multiple signatures ===" << std::endl;
	try
	{
		Bureaucrat charlie("Charlie", 1);
		Form form6("ImportantForm", 10, 5);
		charlie.signForm(form6);
		charlie.signForm(form6); // Already signed
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return (0);
}
