/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:15:46 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 16:24:57 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <string>
# include "contact.hpp"
# include <iostream>
# include <iomanip>
# include <cstdlib>

class PhoneBook {
private:
	Contact contacts[8];
	int contactCount;
	int oldestIndex;

	std::string truncateField(const std::string& field) const;

public:
	PhoneBook();
	void addContact();
	void searchContact() const;
};

#endif
