/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:15:46 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/30 14:08:28 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

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
