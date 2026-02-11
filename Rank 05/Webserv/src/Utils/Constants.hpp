/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/09 17:14:22 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>
#include <list>
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <poll.h>

// Config paths
#define SERV_CONF "serv.conf"
#define PATH_CONF "src/config/"

//PARS
#define DENINE_DOUBLON "listen", "server_name", "root", "index"
// HTTP methods
#define VALID_HTTP_METHODS "GET", "POST", "DELETE", "HEAD", "PUT"
#define VALID_HTTP_METHODS_COUNT 5

// Network / Epoll
#define EPOLL_MAX_EVENTS 128
#define EPOLL_TIMEOUT_MS 1000
#define SOCKET_BUFFER_SIZE 4096
#define CLIENT_TIMEOUT_SEC 60

// Token types
enum {
	SECTION,
	URL,
	DIRECTIVE,
	VALUE,
	COMMENT,
	CURLY_BRACKET_OPEN,
	CURLY_BRACKET_CLOSED
};

// TypeDef
typedef unsigned int u_int;
typedef std::string string;
typedef std::vector<int> vect_int;
typedef std::string::size_type size_type;
typedef std::pair<string, string> pair_string;
typedef std::pair<string, int> pair_str_int;
typedef std::vector<string> vector_string;
typedef std::vector<pair_string> vector_pair_string;
typedef std::vector<pair_str_int>::const_iterator vec_iterator;
typedef std::map<int, string> map_int_string;
typedef std::ofstream ofstream;
typedef std::ifstream ifstream;
typedef std::size_t size_t;
typedef std::list<pair_string> list_pair;
typedef std::list<pair_str_int> list_pair_str_int;
typedef list_pair_str_int::const_iterator lst_iterator;
typedef std::map<std::string, std::string>::iterator map_str_str_iterator;
typedef std::stringstream stringstream;
typedef std::map<std::string, std::string> map_str_str;
typedef std::istringstream istringstream;
