/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/24 18:57:05 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void    wall_checker(char **map_grid, size_t map_height, size_t map_width)
{
    size_t  i;
    size_t  j;
    
    i = 0;
    while (i < map_width - 1)
    {
        if (map_grid[0][i] != '1')
            print_error("Map is not surrounded by walls", 255);
        i++;
    }
    j = 1;
    while (j < map_height - 1)
    {
        if (map_grid[j][0] != '1' || map_grid[j][map_width - 1] != '1')
            print_error("Map is not surrounded by walls", 255);
        j++;
    }
    i = 0;
    while (i < map_width - 1)
    {
        if (map_grid[j][i] != '1')
            print_error("Error > Map is not surrounded by walls", 255);
        i++;
    }
    return ;
}

void    elements_checker(char **map_grid)
{
    int i;
    int j;

    i = 0;
    while (map_grid[i])
    {
        j = 0;
        while (map_grid[i][j])
        {
            if (map_grid[i][j] != '1' && map_grid[i][j] != '0' && map_grid[i][j] != 'P' && map_grid[i][j] != 'C' && map_grid[i][j] != 'E' && map_grid[i][j] != '\n')
            {
                ft_putstr_fd("y = ", 2);
                ft_putnbr_fd(i, 2);
                ft_putstr_fd("; x = ", 2);
                ft_putnbr_fd(j, 2);
                ft_putstr_fd("; element = ", 2);
                ft_putchar_fd(map_grid[i][j], 2);
                ft_putchar_fd('\n', 2);
                print_error("Error > Invalid element found in the map", 255);
            }    
            j++;
        }
        i++;
    }
    return;
}

void    flood_fill(char **map_copy, size_t player_x, size_t player_y, t_map *map)
{
    // Dentro del mapa
    if (player_x < 0 || player_x >= map->width || player_y < 0 || player_y >= map->height)
        return ;
    // Espacio válido
    if (map_copy[player_y][player_x] == '1' || map_copy[player_y][player_x] == 'V')
        return ;
    // Marcar celda como visitada
    map_copy[player_y][player_x] = 'V';
    // Recursividad
    flood_fill(map_copy, player_x + 1, player_y, map); // Derecha
    flood_fill(map_copy, player_x - 1, player_y, map); // Izquierda
    flood_fill(map_copy, player_x, player_y + 1, map); // Abajo
    flood_fill(map_copy, player_x, player_y - 1, map); // Arriba
    return;
}

bool    accesibility_checker(t_map *map, char *map_file)
{
    char    **map_grid_copy;
    size_t  i;
    size_t  j;

    map_grid_copy = read_map(map_file, map->height);
    if (!map_grid_copy)
        print_error("Error > Map could not be read", 1);
    flood_fill(map_grid_copy, map->player_x, map->player_y, map);
    //print_map(map_grid_copy); // Para revisar flood_fill()
    i = 0;
    while (map_grid_copy[i])
    {
        j = 0;
        while (map_grid_copy[i][j])
        {
            if (map_grid_copy[i][j] == 'C' || map_grid_copy[i][j] == 'E')
            {
                free_matrix(map_grid_copy);
                return (false);
            } 
            j++;
        }
        i++;
    }
    free_matrix(map_grid_copy);
    return (true);
}

void    map_checks(t_map *map, char *map_file)
{
    wall_checker(map->grid, map->height, map->width);
    //printf("Walls properly checked\n");
    elements_checker(map->grid);
    //printf("Map elements properly checked\n");
    if (accesibility_checker(map, map_file) == false)
        print_error("Collectibles or exit are not accesible", 255);
    /*else
        printf("Collectibles and exit accesibility checked\n");*/
    return ;
}
