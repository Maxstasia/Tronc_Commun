/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:23:44 by mstasiak          #+#    #+#             */
/*   Updated: 2025/01/13 16:56:04 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc < 2) || ((ft_strcmp(argv[1], "julia") == 0) && (argc < 4 || argc > 5)))
		return (clean_up(&data), MLX_ERROR);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (clean_up(&data), MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Fractol");
	if (data.win_ptr == NULL)
		return (clean_up(&data), MLX_ERROR);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data.img.mlx_img == NULL)
		return (clean_up(&data), MLX_ERROR);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.l_len, &data.img.endian);
	if (data.img.addr == NULL)
		return (clean_up(&data), MLX_ERROR);
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		data.color_palette = ft_atoi(argv[2]);
		data.min_x = -3.0;
		data.max_x = 2.0;
		data.min_y = -2.0;
		data.max_y = 2.0;
		mandelbrot_wrapper(&data);
	}
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		data.color_palette = ft_atoi(argv[4]);
		data.min_x = -1.5;
		data.max_x = 1.5;
		data.min_y = -1.5;
		data.max_y = 1.5;
		data.c_re = ft_atof(argv[2]);
		data.c_im = ft_atof(argv[3]);
		julia_wrapper(&data);
	}
	else
		return (clean_up(&data), MLX_ERROR);
	print_command();
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, NoEventMask, &handle_destroy, &data);
	mlx_mouse_hook(data.win_ptr, &handle_scroll, &data);
	mlx_loop(data.mlx_ptr);
	clean_up(&data);
	return (0);
}

/*
Commande :
	Fol All :

	- Button 5 (mouse scroll) : zoom;
	- Button 4 (mouse scroll) : unzoom;
	- Space, Enter and Return : change color;

	For Julia :
	- Keybord 'e' or 'q': change value/parameter;
	- Keybord 'a' : change value/parameter automatically;
*/

/*
Pour générer des fractales intéressantes avec Julia, tu peux proposer à l'utilisateur des valeurs spécifiques pour les constantes \( c_{re} \) et \( c_{im} \). Ces valeurs influencent directement la forme de la fractale générée. Voici quelques exemples :

---

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

### Valeurs personnalisées :
Tu peux aussi permettre à l'utilisateur d'explorer librement en modifiant légèrement les valeurs :
- \( c_{re} \) entre \(-2.0\) et \(2.0\).
- \( c_{im} \) entre \(-2.0\) et \(2.0\).
*/
