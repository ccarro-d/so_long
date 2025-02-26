/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/26 21:38:53 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Salida cuando se produce un error
void	print_error(char *error_explained, int error_code)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(error_explained, STDERR_FILENO);
	exit(error_code);
}

// Verifica el contenido del mapa
void	print_map(char **map_grid)
{
	int	i;

	i = 0;
	write(1, "\n", 1); // borrar
	while (map_grid[i])
	{
		write(1, map_grid[i], ft_strlen(map_grid[i]));
		i++;
	}
	write(1, "\n", 1); // borrar
	return ;
}

void	print_invalid_element(int y, int x, char invalid_element)
{
	ft_putstr_fd("y = ", STDERR_FILENO);
	ft_putnbr_fd(y, STDERR_FILENO);
	ft_putstr_fd("; x = ", STDERR_FILENO);
	ft_putnbr_fd(x, STDERR_FILENO);
	ft_putstr_fd("; element = ", STDERR_FILENO);
	ft_putchar_fd(invalid_element, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	print_error("> Invalid element found in the map", 1);
	return ;
}

// Imprime el número de movimientos en terminal y ventana
void	print_moves(int movements, mlx_t *mlx, t_map map,
		mlx_image_t **moves_text)
{
	char	*movements_str;
	char	*concat_string;

	ft_putstr_fd("Movements made = ", STDOUT_FILENO);
	ft_putnbr_fd(movements, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	movements_str = ft_itoa(movements);
	concat_string = ft_strjoin("Movements made = ", movements_str);
	free(movements_str);
	if (*moves_text)
		mlx_delete_image(mlx, *moves_text);
	*moves_text = mlx_put_string(mlx, concat_string, (int)(map.width * 64
				* 0.5), (int)(map.height * 64 * 0.9));
	free(concat_string);
	return ;
}

// Imprime mensaje al recoger coleccionable
void	print_collectibles(int map_collectibles)
{
	if (map_collectibles > 0)
	{
		ft_putstr_fd("You picked up a collectible. ", STDOUT_FILENO);
		ft_putnbr_fd(map_collectibles, STDOUT_FILENO);
		ft_putstr_fd(" still left.\n", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd("That was the last collectible. ", STDOUT_FILENO);
		ft_putstr_fd("Go to the exit now!\n", STDOUT_FILENO);
	}
	return ;
}
