#include "Loader.hpp"
#include "Validator.hpp"

Loader::~Loader(){}

Loader::Loader(){}

Loader::Loader(const string &configFile)
{
	try
	{
		_configFile = configFile;
		_tokenizer = Tokenizer(configFile);
		Validator validator(_directiveRegistry.getDirectiveTypes(),
			_tokenizer.getTokens(), 0);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Loader: " << e.what() << std::endl;
		throw;
	}
}

Loader::Loader(const Loader &other)
{
	*this = other;
}
Loader &Loader::operator=(const Loader &other)
{
	if (this != &other)
	{
		_configFile = other._configFile;
		_directiveRegistry = other._directiveRegistry;
		_tokenizer = other._tokenizer;
		_mimeRegistry = other._mimeRegistry;
	}
	return (*this);
}
