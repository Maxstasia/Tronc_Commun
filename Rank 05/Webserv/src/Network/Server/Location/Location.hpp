/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/01/10 13:00:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "FileUtils.hpp"

class Location
{
	private:
		string			_path;
		string			_root;
		string			_index;
		bool			_autoindex;
		vector_string	_allow_methods;
		string			_return;
		string			_upload_path;

	public:
		Location();
		Location &operator=(const Location &other);
		Location (const  Location &other);
		~Location();

		const string &getPath() const;
		const string &getRoot() const;
		const string &getIndex() const;
		bool getAutoindex() const;
		const vector_string &getAllowMethods() const;
		const string &getReturn() const;
		const string &getUploadPath() const;

		string getEffectiveRoot(const string &serverRoot) const;
		string getEffectiveIndex(const string &serverIndex) const;
		string getEffectiveUploadPath(const string &serverRoot) const;

		void setPath(const string &path);
		void setRoot(const string &root);
		void setIndex(const string &index);
		void setAutoindex(bool autoindex);
		void setAllowMethods(const vector_string &methods);
		void setReturn(const string &ret);
		void setUploadPath(const string &path);

};


