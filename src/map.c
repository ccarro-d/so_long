/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/25 17:15:02 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

size_t	count_lines(char *map_file) // Para saber el alto del mapa
{
	int fd;
	size_t lines;
	char buf[BUFFER_SIZE];
	char prev;

	fd = open(map_file, O_RDONLY);
	lines = 0;
	while (read(fd, buf, BUFFER_SIZE) > 0)
	{
		if (buf[0] == '\n' && buf[0] != prev)
			lines++;
		prev = buf[0];
	}
	close(fd);
	return (lines + 1);
}

char	**read_map(char *map_file, size_t map_height) // Matriz con el mapa
{
	int fd;
	char **grid;
	int i;
	char *line;

	fd = open(map_file, O_RDONLY);
	grid = (char **)ft_calloc(sizeof(char *), map_height + 1);
	if (fd < 0 || !grid)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)))
		grid[i++] = line;
	grid[i] = NULL;
	close(fd);
	return (grid);
}

void	print_map(char **map_grid) // Verificamos el contenido del mapa
{
	int i;

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

size_t	check_lines_length(char **map_grid)
		// Para saber si todas las filas son de igual longitud
{
	int i;
	size_t current;
	size_t previous;

	i = 0;
	if (!map_grid[i])
		return (0);
	current = ft_strlen(map_grid[i]);
	if (map_grid[i][current - 1] == '\n')
		current--;
	while (map_grid[i])
	{
		previous = current;
		current = ft_strlen(map_grid[i]);
		if (current > 0 && map_grid[i][current - 1] == '\n')
			current--;
		if (current != previous)
			return (0);
		i++;
	}
	return (current);
}

size_t	count_collectibles(char **map_grid) // Para saber si hay coleccionables
{
	int i;
	int j;
	size_t collectibles;

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

bool	has_exit(char **map_grid)
		// Para comprobar si hay salida y si solo es una
{
	int i;
	int j;
	int exits;

	i = 0;
	exits = 0;

	while (map_grid[i])
	{
		j = 0;
		while (map_grid[i][j])
		{
			if (map_grid[i][j] == 'E')
				exits++;
			j++;
		}
		i++;
	}
	if (exits == 1)
		return (true);
	else if (exits == 0)
		return (false);
	else
		print_error("> Only one exit is allowed", 255);
	return (false);
}

void	initialize_map(t_map *map, char *map_file)
{
	map->height = count_lines(map_file);
	// printf("map->height = %zu\n", map->height);
	if (map->height <= 2)
		print_error("> Map smaller than allowed", 1);
	map->grid = read_map(map_file, map->height);
	// print_map(map->grid);
	if (!map->grid)
		print_error("> Map could not be read", 1);
	map->width = check_lines_length(map->grid);
	// printf("\nmap->width = %zu\n", map->width);
	if (!map->width)
		print_error("> Map must be a square or rectangle", 1);
	map->collectibles = count_collectibles(map->grid);
	// printf("\nmap->collectibles = %zu\n", map->collectibles);
	if (!map->collectibles)
		print_error("> At least one collectible is needed", 1);
	map->player_x = 0;
	map->player_y = 0;
	player_position(map->grid, &map->player_x, &map->player_y);
	// printf("player position x=%zu & y=%zu\n",map->player_x, map->player_y);
	if (!map->player_x && !map->player_y)
		print_error("> No playable character found", 1);
	map->exit = has_exit(map->grid);
	// printf("has exit = %d\n", map->exit);
	if (!map->exit)
		print_error("> No exits were found", 1);
	map_checks(map, map_file);
	return ;
}
