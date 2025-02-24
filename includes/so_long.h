/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:36:17 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/24 01:03:44 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#ifndef WIDTH
# define WIDTH 500
#endif

#ifndef HEIGHT
# define HEIGHT 500
#endif

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>   // Para usar el tipo bool
# include <stddef.h>    // Para usar size_t
# include <errno.h>     // Para códigos de error

// Map structure
typedef struct s_map
{
    char    **grid;    // Matriz 2D de caracteres que representa el mapa (cada celda contiene '0', '1', 'P', 'C', 'E')
    size_t  width;     // Anchura del mapa
    size_t  height;    // Altura del mapa
    size_t  collectibles; // Número de coleccionables 'C'
    size_t  player_x;  // Coordenada x del jugador (P)
    size_t  player_y;  // Coordenada y del jugador (P)
    bool    exit;  // Indica si el mapa tiene una salida 'E'
} t_map;

// Main functions
int		main(int argc, char **argv);
void	print_error(char *error_explained, int error_code);
void    free_matrix(char **matrix);

// Map functions
void    initialize_map(t_map *map, char *map_file);
size_t	count_lines(char *map_file);
char	**read_map(char *map_file, size_t map_height);
size_t check_lines_length(char **map_grid);
size_t  count_collectibles(char **map_grid);
void    player_position(char **map_grid, size_t *player_x, size_t *player_y);
void	print_map(char **map_grid);
bool    has_exit(char **map_grid);

void    map_checks(t_map *map, char *map_file);
void    wall_checker(char **map_grid, size_t map_height, size_t map_width);
void    elements_checker(char **map_grid);
bool    accesibility_checker(t_map *map, char *map_file);
void    flood_fill(char **map_copy, size_t player_x, size_t player_y, t_map *map);

#endif