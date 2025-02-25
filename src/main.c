/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/25 01:24:54 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	print_error(char *error_explained, int error_code)
{
	ft_putstr_fd(error_explained, STDERR_FILENO);
	exit(error_code);
}

void    free_matrix(char **matrix)
{
    int i;
    
    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
    return;
}

void    load_textures(t_images *textures, mlx_t *mlx)
{
    textures->collectible_texture = mlx_load_png("./textures/collectible.png");
    textures->exit_texture = mlx_load_png("./textures/exit.png");
    textures->floor_texture = mlx_load_png("./textures/floor.png");
    textures->player_texture = mlx_load_png("./textures/player.png");
    textures->wall_texture = mlx_load_png("./textures/wall.png");
    if (!textures->collectible_texture || !textures->exit_texture || !textures->floor_texture || !textures->player_texture || !textures->wall_texture)
        print_error("Error > Textures could not be loaded\n", 1);
    textures->collectible_image = mlx_texture_to_image(mlx, textures->collectible_texture);
    textures->exit_image = mlx_texture_to_image(mlx, textures->exit_texture);
    textures->floor_image = mlx_texture_to_image(mlx, textures->floor_texture);
    textures->player_image = mlx_texture_to_image(mlx, textures->player_texture);
    textures->wall_image = mlx_texture_to_image(mlx, textures->wall_texture);
    if (!textures->collectible_image || !textures->exit_image || !textures->floor_image || !textures->player_image || !textures->wall_image)
        print_error("Error > Images could not be loaded\n", 1);
    mlx_delete_texture(textures->collectible_texture);
    mlx_delete_texture(textures->exit_texture);
    mlx_delete_texture(textures->floor_texture);
    mlx_delete_texture(textures->player_texture);
    mlx_delete_texture(textures->wall_texture);
    return ;
}

void    render_map(t_map *map, t_images *textures, mlx_t *mlx)
{
    size_t  y;
    size_t  x;

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->grid[y][x] == '1')
                mlx_image_to_window(mlx, textures->wall_image, x * 64, y * 64);
            else
                mlx_image_to_window(mlx, textures->floor_image, x * 64, y * 64);
            if (map->grid[y][x] == 'P')
                mlx_image_to_window(mlx, textures->player_image, x * 64, y * 64);
            if (map->grid[y][x] == 'C')
                mlx_image_to_window(mlx, textures->collectible_image, x * 64, y * 64);
            if (map->grid[y][x] == 'E')
                mlx_image_to_window(mlx, textures->exit_image, x * 64, y * 64);
            x++;
        }
        y++;
    }
    return ;
}

int main(int argc, char **argv)
{
    t_game   game;
    
    if (argc != 2)
        print_error("Error > Correct usage: /so_long <map_file.ber>\n", 1);
    initialize_map(&game.map, argv[1]);
    game.mlx = mlx_init(game.map.width * 64, game.map.height *64, "so_long", false);
    if (!game.mlx)
        print_error("Error > MLX42 initialization failed", 1);
    load_textures(&game.textures, game.mlx);
    render_map(&game.map, &game.textures, game.mlx);
    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
    return (0);
}
