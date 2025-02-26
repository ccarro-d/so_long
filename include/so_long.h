/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:36:17 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/26 18:57:25 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef WIDTH
#  define WIDTH 500
# endif

# ifndef HEIGHT
#  define HEIGHT 500
# endif

# include "../MLX42/include/MLX42/MLX42.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include <errno.h>   // Para códigos de error
# include <stdbool.h> // Para usar el tipo bool
# include <stddef.h>  // Para usar size_t

// Structures
typedef struct s_map
{
	char	**grid; // Matriz 2D de caracteres que representa el mapa
	size_t	width; // Anchura del mapa
	size_t	height; // Altura del mapa
	int		collectibles; // Número de coleccionables 'C'
	size_t	player_x; // Coordenada x del jugador (P)
	size_t	player_y; // Coordenada y del jugador (P)
	size_t	exit_x; // Coordenada x de la salida (E)
	size_t	exit_y; // Coordenada y de la salida (E)
}					t_map;

typedef struct s_images
{
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*floor_texture;
	mlx_texture_t	*player_texture;
	mlx_texture_t	*collectible_texture;
	mlx_texture_t	*exit_texture;
	mlx_image_t		*wall_image;
	mlx_image_t		*floor_image;
	mlx_image_t		*player_image;
	mlx_image_t		*collectible_image;
	mlx_image_t		*exit_image;
}					t_images;

typedef struct s_game
{
	t_map		map; // Datos del mapa
	t_images	textures; // Imágenes asociadas
	mlx_t		*mlx; // Conexión con MLX42
	mlx_image_t	*img; // Imagen principal para renderizar
	int			movements;
	mlx_image_t	*moves_text;
}					t_game;

// main.c function
void				free_matrix(char **matrix);
int					main(int argc, char **argv);

// prints.c functions
void				print_error(char *error_explained, int error_code);
void				print_map(char **map_grid);
void    			print_invalid_element(int y, int x, char invalid_element);
void				print_moves(int movements, mlx_t *mlx, t_map map,
						mlx_image_t **moves_text);
void				print_collectibles(int map_collectibles);

// map_init.c functions
void				initialize_map(t_map *map, char *map_file);
size_t				count_lines(char *map_file);
char				**read_map(char *map_file, size_t map_height);
size_t				check_lines_length(char **map_grid);

// map_elements.c functions
int					count_collectibles(char **map_grid);
void				player_position(char **map_grid, size_t *player_x,
						size_t *player_y);
void				exit_position(char **map_grid, size_t *exit_x,
						size_t *exit_y);

// map_check.c functions
void				map_checks(t_map *map, char *map_file);
void				wall_checker(char **map_grid, size_t map_height,
						size_t map_width);
void				elements_checker(char **map_grid);
bool				accesibility_checker(t_map *map, char *map_file);
void				flood_fill(char **map_copy, size_t player_x,
						size_t player_y, t_map *map);

// so_long.c functions
void				load_textures(t_images *textures, mlx_t *mlx);
void				render_map(t_map map, t_images *textures, mlx_t *mlx);
void				move_player(t_game *game, size_t new_y, size_t new_x);
void				handle_input(mlx_key_data_t keydata, void *param);

// player_collectibles.c functions
void				remove_player_collectibles(mlx_t *mlx,
						mlx_image_t *player_img, mlx_image_t *collectible_img);
void				render_player_collectibles(t_map map, t_images *textures,
						mlx_t *mlx);
void				update_player_collectibles(t_map map, t_images *textures,
						mlx_t *mlx);

#endif