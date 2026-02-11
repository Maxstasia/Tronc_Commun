/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/10 13:00:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location() : _path(""), _root(""), _index(""), _autoindex(false), _return(""), _upload_path("")
{}

Location::Location(const Location &other)
{
	*this = other;
}

Location &Location::operator=(const Location &other)
{
	if (this != &other)
	{
		_path = other._path;
		_root = other._root;
		_index = other._index;
		_autoindex = other._autoindex;
		_allow_methods = other._allow_methods;
		_return = other._return;
		_upload_path = other._upload_path;
	}
	return *this;
}

Location::~Location()
{}

const string &Location::getPath() const { return _path; }
const string &Location::getRoot() const { return _root; }
const string &Location::getIndex() const { return _index; }
bool Location::getAutoindex() const { return _autoindex; }
const vector_string &Location::getAllowMethods() const { return _allow_methods; }
const string &Location::getReturn() const { return _return; }
const string &Location::getUploadPath() const { return _upload_path; }

string Location::getEffectiveRoot(const string &serverRoot) const
{
	return _root.empty() ? serverRoot : _root;
}

string Location::getEffectiveIndex(const string &serverIndex) const
{
	return _index.empty() ? serverIndex : _index;
}

string Location::getEffectiveUploadPath(const string &serverRoot) const
{
	return _upload_path.empty() ? serverRoot : _upload_path;
}

void Location::setPath(const string &path) { _path = path; }
void Location::setRoot(const string &root) { _root = root; }
void Location::setIndex(const string &index) { _index = index; }
void Location::setAutoindex(bool autoindex) { _autoindex = autoindex; }
void Location::setAllowMethods(const vector_string &methods) { _allow_methods = methods; }
void Location::setReturn(const string &ret) { _return = ret; }
void Location::setUploadPath(const string &path) { _upload_path = path; }
