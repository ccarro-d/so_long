/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/26 19:04:47 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	load_textures(t_images *textures, mlx_t *mlx)
{
	textures->collectible_texture = mlx_load_png("./textures/collectible.png");
	textures->exit_texture = mlx_load_png("./textures/exit.png");
	textures->floor_texture = mlx_load_png("./textures/floor.png");
	textures->player_texture = mlx_load_png("./textures/player.png");
	textures->wall_texture = mlx_load_png("./textures/wall.png");
	if (!textures->collectible_texture || !textures->exit_texture
		|| !textures->floor_texture || !textures->player_texture
		|| !textures->wall_texture)
		print_error("> Textures could not be loaded\n", 1);
	textures->collectible_image = mlx_texture_to_image(mlx,
			textures->collectible_texture);
	textures->exit_image = mlx_texture_to_image(mlx, textures->exit_texture);
	textures->floor_image = mlx_texture_to_image(mlx, textures->floor_texture);
	textures->player_image = mlx_texture_to_image(mlx,
			textures->player_texture);
	textures->wall_image = mlx_texture_to_image(mlx, textures->wall_texture);
	if (!textures->collectible_image || !textures->exit_image
		|| !textures->floor_image || !textures->player_image
		|| !textures->wall_image)
		print_error("> Images could not be loaded\n", 1);
	mlx_delete_texture(textures->collectible_texture);
	mlx_delete_texture(textures->exit_texture);
	mlx_delete_texture(textures->floor_texture);
	mlx_delete_texture(textures->player_texture);
	mlx_delete_texture(textures->wall_texture);
}

void	render_map(t_map map, t_images *textures, mlx_t *mlx)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.grid[y][x] == '1')
				mlx_image_to_window(mlx, textures->wall_image, x * 64, y * 64);
			else
				mlx_image_to_window(mlx, textures->floor_image, x * 64, y * 64);
			if (map.grid[y][x] == 'E')
				mlx_image_to_window(mlx, textures->exit_image, x * 64, y * 64);
			x++;
		}
		y++;
	}
	render_player_collectibles(map, textures, mlx);
	return ;
}

void	move_player(t_game *game, size_t new_y, size_t new_x)
{
	char	c;

	c = game->map.grid[new_y][new_x];
	if (c != '1')
	{
		print_moves(++game->movements, game->mlx, game->map, &game->moves_text);
		game->map.grid[new_y][new_x] = 'P';
		if (game->map.player_x == game->map.exit_x
			&& game->map.player_y == game->map.exit_y)
			game->map.grid[game->map.player_y][game->map.player_x] = 'E';
		else
			game->map.grid[game->map.player_y][game->map.player_x] = '0';
		update_player_collectibles(game->map, &game->textures, game->mlx);
		if (c == 'C')
			print_collectibles(--game->map.collectibles);
		if (c == 'E' && game->map.collectibles == 0)
		{
			game->map.grid[game->map.player_y][game->map.player_x] = '0';
			ft_putstr_fd("You won! 🎉\n", STDOUT_FILENO);
			exit(0);
		}
		game->map.player_y = new_y;
		game->map.player_x = new_x;
	}
}

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			move_player(game, game->map.player_y - 1, game->map.player_x);
		else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			move_player(game, game->map.player_y + 1, game->map.player_x);
		else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
			move_player(game, game->map.player_y, game->map.player_x - 1);
		else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
			move_player(game, game->map.player_y, game->map.player_x + 1);
		else if (keydata.key == MLX_KEY_ESCAPE)
			exit(0);
		else
			return ;
	}
	return ;
}
