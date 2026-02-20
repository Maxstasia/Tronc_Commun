#pragma once

#include "FileUtils.hpp"

class Validator
{
  private:
	const vector_string &_directiveTypes;
	const list_pair_str_int &_tokens;
	int _braceCount;

	void checkBraceBalance() const;
	void validateSection(lst_iterator it, lst_iterator next) const;
	void validateUrl(lst_iterator it, lst_iterator next) const;
	void validateDirective(lst_iterator it, lst_iterator next) const;
	void validateEmptyBlock(lst_iterator it, lst_iterator next, lst_iterator end) const;
	void validateStartToken(const list_pair_str_int &lst) const;
	bool isDirectiveAllowed(const string &key) const;

  public:
	Validator(const vector_string &directiveTypes, const list_pair_str_int &tokens, int braceCount);
	~Validator();

	void validate();

	// Static validation methods for semantic validation
	static void validateIPAddress(const string &host);
	static void validatePath(const string &path, const string &directive_name);
	static void validatePort(int port);
	static void validateHTTPMethod(const string &method);
};
