/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/26 18:29:52 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	count_collectibles(char **map_grid) // Para saber si hay coleccionables
{
	int	i;
	int	j;
	int	collectibles;

	i = 0;
	collectibles = 0;
	while (map_grid[i])
	{
		j = 0;
		while (map_grid[i][j])
		{
			if (map_grid[i][j] == 'C')
				collectibles++;
			j++;
		}
		i++;
	}
	return (collectibles);
}

// Para comprobar la posición del jugador y si solo hay uno
void	player_position(char **map_grid, size_t *player_x, size_t *player_y)
{
	int	players;
	int	i;
	int	j;

	i = 0;
	players = 0;
	while (map_grid[i])
	{
		j = 0;
		while (map_grid[i][j])
		{
			// printf("player_position=%c\n", map_grid[*player_y][*player_x]);
			if (map_grid[i][j] == 'P')
			{
				*player_x = j;
				*player_y = i;
				players++;
			}
			if (players > 1)
				print_error("> Only one playable character is allowed", 255);
			j++;
		}
		i++;
	}
	return ;
}

void	exit_position(char **map_grid, size_t *exit_x, size_t *exit_y)
{
	int	exits;
	int	i;
	int	j;

	i = 0;
	exits = 0;
	while (map_grid[i])
	{
		j = 0;
		while (map_grid[i][j])
		{
			// printf("exit_position=%c\n", map_grid[*exit_y][*exit_x]);
			if (map_grid[i][j] == 'E')
			{
				*exit_x = j;
				*exit_y = i;
				exits++;
			}
			if (exits > 1)
				print_error("> Only one exit is allowed", 255);
			j++;
		}
		i++;
	}
	return ;
}
