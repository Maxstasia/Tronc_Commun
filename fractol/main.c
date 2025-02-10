/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:23:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/02/10 11:28:33 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc < 2)
		|| ((ft_strcmp(argv[1], (char *)"julia") == 0)
			&& (argc < 4 || argc > 5))
		|| ((ft_strcmp(argv[1], (char *)"julia") != 0)
			&& argc > 3))
		return (print_usage(), MLX_ERROR);
	init_main(argv, &data);
	loop(&data);
	return (0);
}

/*
### 1. **Spirale complexe**
- Commande :  
  ```bash
  ./fractol julia -0.8 0.156
  ```
- Description :  
  Produit une fractale avec des spirales complexes et des motifs très détaillés.

---

### 2. **Motifs floraux**
- Commande :  
  ```bash
  ./fractol julia 0.285 0.01
  ```
- Description :  
  Crée des motifs ressemblant à des pétales de fleurs, doux et symétriques.

---

### 3. **Effet électrique**
- Commande :  
  ```bash
  ./fractol julia -0.70176 -0.3842
  ```
- Description :  
  Génère une fractale qui ressemble à des éclairs ou des circuits électriques.

---

### 4. **Cœur fractal**
- Commande :  
  ```bash
  ./fractol julia -0.4 0.6
  ```
- Description :  
  Ressemble à une structure en forme de cœur avec des détails internes complexes.

---

### 5. **Effet vortex**
- Commande :  
  ```bash
  ./fractol julia 0.355 0.355
  ```
- Description :  
  Crée des motifs en spirale avec un aspect hypnotique.

---

### 6. **Déformation ondulée**
- Commande :  
  ```bash
  ./fractol julia -0.75 0.11
  ```
- Description :  
  Produit des motifs fluides avec des lignes ondulées qui se croisent.

---

### 7. **Structure en "toile d'araignée"**
- Commande :  
  ```bash
  ./fractol julia 0.37 -0.1
  ```
- Description :  
  Ressemble à une toile d'araignée en expansion avec des détails captivants.

---
*/
