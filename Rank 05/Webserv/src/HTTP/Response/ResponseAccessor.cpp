/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseAccessor.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcini-ha <rcini-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:00:00 by rcini-ha          #+#    #+#             */
/*   Updated: 2026/02/03 00:00:00 by rcini-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

const string &Response::getFinalResponse() const {
	return _finalResponse;
}

const map_str_str &Response::getHeaders() const {
	return _headers;
}

string Response::getBody() const {
	return _body;
}

int Response::getStatus() const {
	return _status;
}

string Response::getStatusMessage() const {
	return _statusMessage;
}

string Response::getHttpVersion() const {
	return _httpVersion;
}
