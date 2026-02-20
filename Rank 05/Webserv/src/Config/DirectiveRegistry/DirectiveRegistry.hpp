#pragma once

#include "FileUtils.hpp"

class DirectiveRegistry
{
  private:
	vector_string _directiveTypes;

	void handleDirectiveLine(const string &line);
	void loadTypesFile(const string &fileName);

  public:
	DirectiveRegistry();
	~DirectiveRegistry();

	void load();
	const vector_string &getDirectiveTypes() const;
};
