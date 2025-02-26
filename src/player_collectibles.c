/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/26 17:14:09 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void    remove_player_collectibles(mlx_t* mlx, mlx_image_t* player_img, mlx_image_t* collectible_img)
{
    mlx_delete_image(mlx, player_img);
    mlx_delete_image(mlx, collectible_img);
    return ;
}

void    render_player_collectibles(t_map *map, t_images *textures, mlx_t *mlx)
{
    size_t  y;
    size_t  x;
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->grid[y][x] == 'P')
                mlx_image_to_window(mlx, textures->player_image, x * 64, y * 64);
            if (map->grid[y][x] == 'C')
                mlx_image_to_window(mlx, textures->collectible_image, x * 64, y * 64);
            x++;
        }
        y++;
    }
    return ;
}

void    update_player_collectibles(t_map *map, t_images *textures, mlx_t *mlx)
{
    remove_player_collectibles(mlx, textures->player_image, textures->collectible_image);
    textures->collectible_texture = mlx_load_png("./textures/collectible.png");
    textures->player_texture = mlx_load_png("./textures/player.png");
    if (!textures->collectible_texture || !textures->player_texture)
        print_error("> Error updating graphics\n", 1);
    textures->collectible_image = mlx_texture_to_image(mlx, textures->collectible_texture);
    textures->player_image = mlx_texture_to_image(mlx, textures->player_texture);
    if (!textures->collectible_image || !textures->player_image)
        print_error("> Error updating graphics\n", 1);
    mlx_delete_texture(textures->collectible_texture);
    mlx_delete_texture(textures->player_texture);
    render_player_collectibles(map, textures, mlx);
    return ;
}
