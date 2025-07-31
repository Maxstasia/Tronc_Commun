/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:19:30 by mstasiak          #+#    #+#             */
/*   Updated: 2025/07/31 13:19:35 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/phonebook.hpp"

PhoneBook::PhoneBook() : contactCount(0), oldestIndex(0) {}

std::string PhoneBook::truncateField(const std::string& field) const {
	if (field.length() > 10)
		return field.substr(0, 9) + ".";
	return field;
}

void PhoneBook::addContact() {
	std::string first, last, nick, phone, secret;

	std::cout << "Enter first name: ";
	std::getline(std::cin, first);
	if (first.empty()) {
		std::cout << "First name cannot be empty!" << std::endl;
		return;
	}

	std::cout << "Enter last name: ";
	std::getline(std::cin, last);
	if (last.empty()) {
		std::cout << "Last name cannot be empty!" << std::endl;
		return;
	}

	std::cout << "Enter nickname: ";
	std::getline(std::cin, nick);
	if (nick.empty()) {
		std::cout << "Nickname cannot be empty!" << std::endl;
		return;
	}

	std::cout << "Enter phone number: ";
	std::getline(std::cin, phone);
	if (phone.empty()) {
		std::cout << "Phone number cannot be empty!" << std::endl;
		return;
	}

	std::cout << "Enter darkest secret: ";
	std::getline(std::cin, secret);
	if (secret.empty()) {
		std::cout << "Darkest secret cannot be empty!" << std::endl;
		return;
	}

	contacts[oldestIndex].setContact(first, last, nick, phone, secret);
	if (contactCount < 8)
		contactCount++;
	oldestIndex = (oldestIndex + 1) % 8;

	std::cout << "Contact added successfully!" << std::endl;
}

void PhoneBook::searchContact() const {
	if (contactCount == 0) {
		std::cout << "PhoneBook is empty!" << std::endl;
		return;
	}

	std::cout << std::setw(10) << std::right << "Index" << "|"
			  << std::setw(10) << std::right << "First Name" << "|"
			  << std::setw(10) << std::right << "Last Name" << "|"
			  << std::setw(10) << std::right << "Nickname" << std::endl;
	std::cout << "-------------------------------------------" << std::endl;

	for (int i = 0; i < contactCount; ++i) {
		std::cout << std::setw(10) << std::right << i << "|"
				  << std::setw(10) << std::right << truncateField(contacts[i].getFirstName()) << "|"
				  << std::setw(10) << std::right << truncateField(contacts[i].getLastName()) << "|"
				  << std::setw(10) << std::right << truncateField(contacts[i].getNickname()) << std::endl;
	}

	std::string input;
	std::cout << "Enter contact index: ";
	std::getline(std::cin, input);

	int index;
	bool valid = true;
	for (size_t i = 0; i < input.length(); ++i) {
		if (!std::isdigit(input[i])) {
			valid = false;
			break;
		}
	}

	if (valid)
		index = std::atoi(input.c_str());
	else {
		std::cout << "Invalid index format!" << std::endl;
		return;
	}

	if (index < 0 || index >= contactCount) {
		std::cout << "Index out of range!" << std::endl;
		return;
	}

	std::cout << "First Name: " << contacts[index].getFirstName() << std::endl;
	std::cout << "Last Name: " << contacts[index].getLastName() << std::endl;
	std::cout << "Nickname: " << contacts[index].getNickname() << std::endl;
	std::cout << "Phone Number: " << contacts[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << contacts[index].getDarkestSecret() << std::endl;
}
