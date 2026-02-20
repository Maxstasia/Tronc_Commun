#pragma once

#include "FileUtils.hpp"

class MimeTypeRegistry
{
  private:
	vector_pair_string _mimeTypes;

	void handleMimeLine(const string &line);
	void loadTypesFile(const string &fileName);

  public:
	MimeTypeRegistry();
	~MimeTypeRegistry();

	void load();
	const vector_pair_string &getMimeTypes() const;
};
