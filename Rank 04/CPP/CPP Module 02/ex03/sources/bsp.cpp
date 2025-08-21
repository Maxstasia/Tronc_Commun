/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:11:49 by mstasiak          #+#    #+#             */
/*   Updated: 2025/08/21 11:50:15 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Point.hpp"

// Fonction helper pour calculer le produit vectoriel (cross product) en 2D
// Retourne un Fixed représentant le signe du produit vectoriel
static Fixed crossProduct(Fixed ax, Fixed ay, Fixed bx, Fixed by, Fixed cx, Fixed cy) {
	// Vecteur AB = (bx - ax, by - ay)
	// Vecteur AC = (cx - ax, cy - ay)
	// Produit vectoriel AB x AC = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax)
	return ((bx - ax) * (cy - ay) - (by - ay) * (cx - ax));
}

bool bsp( Point const a, Point const b, Point const c, Point const point) {
	Fixed Xa = a.getX();
	Fixed Ya = a.getY();
	Fixed Xb = b.getX();
	Fixed Yb = b.getY();
	Fixed Xc = c.getX();
	Fixed Yc = c.getY();
	Fixed Xp = point.getX();
	Fixed Yp = point.getY();

	// Calculer les produits vectoriels pour chaque arête du triangle
	// Pour l'arête AB, on regarde si P et C sont du même côté
	Fixed d1 = crossProduct(Xa, Ya, Xb, Yb, Xp, Yp);
	Fixed d2 = crossProduct(Xa, Ya, Xb, Yb, Xc, Yc);
	
	// Pour l'arête BC, on regarde si P et A sont du même côté
	Fixed d3 = crossProduct(Xb, Yb, Xc, Yc, Xp, Yp);
	Fixed d4 = crossProduct(Xb, Yb, Xc, Yc, Xa, Ya);
	
	// Pour l'arête CA, on regarde si P et B sont du même côté
	Fixed d5 = crossProduct(Xc, Yc, Xa, Ya, Xp, Yp);
	Fixed d6 = crossProduct(Xc, Yc, Xa, Ya, Xb, Yb);

	// Vérifier si P est du même côté que le troisième sommet pour chaque arête
	// Le point est à l'intérieur si tous les signes correspondent ET qu'aucun n'est sur une arête (= 0)
	bool sameSide1 = (d1.getRawBits() > 0 && d2.getRawBits() > 0) || (d1.getRawBits() < 0 && d2.getRawBits() < 0);
	bool sameSide2 = (d3.getRawBits() > 0 && d4.getRawBits() > 0) || (d3.getRawBits() < 0 && d4.getRawBits() < 0);
	bool sameSide3 = (d5.getRawBits() > 0 && d6.getRawBits() > 0) || (d5.getRawBits() < 0 && d6.getRawBits() < 0);
	
	// Le point est strictement à l'intérieur si il est du même côté pour toutes les arêtes
	// ET qu'il n'est sur aucune arête (d1, d3, d5 != 0)
	return (sameSide1 && sameSide2 && sameSide3 && 
		   d1.getRawBits() != 0 && d3.getRawBits() != 0 && d5.getRawBits() != 0);
}
