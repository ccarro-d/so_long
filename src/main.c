/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/26 18:23:09 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return ;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		print_error("> Correct usage: /so_long <map_file.ber>\n", 1);
	initialize_map(&game.map, argv[1]);
	game.mlx = mlx_init(game.map.width * 64, game.map.height * 64, "so_long",
			true);
	if (!game.mlx)
		print_error("> MLX42 initialization failed", 1);
	load_textures(&game.textures, game.mlx);
	render_map(game.map, &game.textures, game.mlx);
	game.movements = 0;
	game.moves_text = NULL;
	mlx_key_hook(game.mlx, handle_input, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
