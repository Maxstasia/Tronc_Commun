/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:56 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 12:16:14 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/Point.hpp"

int main(void) {
	Point a(0, 0);
	Point b(5, 0);
	Point c(0, 5);
	Point point1(1, 1); // Inside the triangle
	Point point2(6, 6); // Outside the triangle
	Point point3(0, 3); // Outside the triangle (Point sur la ligne)
	
	if (bsp(a, b, c, point1)) {
		std::cout << "Point 1 is inside the triangle." << std::endl;
	} 
	else {
		std::cout << "Point 1 is outside the triangle." << std::endl;
	}

	if (bsp(a, b, c, point2)) {
		std::cout << "Point 2 is inside the triangle." << std::endl;
	} 
	else {
		std::cout << "Point 2 is outside the triangle." << std::endl;
	}

	if (bsp(a, b, c, point3)) {
		std::cout << "Point 3 is inside the triangle." << std::endl;
	}
	else {
		std::cout << "Point 3 is outside the triangle." << std::endl;
	}
	return 0;
}
