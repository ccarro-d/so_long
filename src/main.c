/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/26 02:57:52 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	print_error(char *error_explained, int error_code)
{
    ft_putstr_fd("Error\n", STDERR_FILENO);
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
        print_error("> Textures could not be loaded\n", 1);
    textures->collectible_image = mlx_texture_to_image(mlx, textures->collectible_texture);
    textures->exit_image = mlx_texture_to_image(mlx, textures->exit_texture);
    textures->floor_image = mlx_texture_to_image(mlx, textures->floor_texture);
    textures->player_image = mlx_texture_to_image(mlx, textures->player_texture);
    textures->wall_image = mlx_texture_to_image(mlx, textures->wall_texture);
    if (!textures->collectible_image || !textures->exit_image || !textures->floor_image || !textures->player_image || !textures->wall_image)
        print_error("> Images could not be loaded\n", 1);
    mlx_delete_texture(textures->collectible_texture);
    mlx_delete_texture(textures->exit_texture);
    mlx_delete_texture(textures->floor_texture);
    mlx_delete_texture(textures->player_texture);
    mlx_delete_texture(textures->wall_texture);
    return ;
}

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
            if (map->grid[y][x] == 'E')
                mlx_image_to_window(mlx, textures->exit_image, x * 64, y * 64);
            x++;
        }
        y++;
    }
    render_player_collectibles(map, textures, mlx);
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

void    print_moves(int movements, mlx_t *mlx, size_t map_height, size_t map_width, mlx_image_t **moves_text)
{
    char    *movements_str;
    char    *concat_string;
    
    ft_putstr_fd("Movements made = ", STDOUT_FILENO);
    ft_putnbr_fd(movements, STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
    movements_str = ft_itoa(movements);
    concat_string = ft_strjoin("Movements made = ", movements_str);
    if (*moves_text)
        mlx_delete_image(mlx, *moves_text);
    *moves_text = mlx_put_string(mlx, concat_string, (int)(map_width * 64 * 0.5), (int)(map_height * 64 * 0.9));
    free(concat_string);
}

void    print_collectibles(int  map_collectibles)
{
    if (map_collectibles > 0)
    {
        ft_putstr_fd("You picked up a collectible. ", STDOUT_FILENO);
        ft_putstr_fd("Still ", STDOUT_FILENO);
        ft_putnbr_fd(map_collectibles, STDOUT_FILENO);
        ft_putstr_fd(" left\n", STDOUT_FILENO);   
    }
    else
        ft_putstr_fd("That was the last collectible. ", STDOUT_FILENO);  
        ft_putstr_fd("Go to the exit now\n", STDOUT_FILENO);   
 
    return ;
}

void    move_player(t_game *game, size_t new_y, size_t new_x)
{
    char    c;
    
    c = game->map.grid[new_y][new_x];
    if (c != '1')
    {
        print_moves(++game->movements, game->mlx, game->map.height, game->map.width, &game->moves_text);
        game->map.grid[new_y][new_x] = 'P';
        if (game->map.player_x == game->map.exit_x && game->map.player_y == game->map.exit_y)
            game->map.grid[game->map.player_y][game->map.player_x] = 'E';
        else
            game->map.grid[game->map.player_y][game->map.player_x] = '0';
        update_player_collectibles(&game->map, &game->textures, game->mlx);
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

void handle_input(mlx_key_data_t keydata, void *param)
{
    t_game  *game;
    
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

int main(int argc, char **argv)
{
    t_game   game;
    
    if (argc != 2)
        print_error("> Correct usage: /so_long <map_file.ber>\n", 1);
    initialize_map(&game.map, argv[1]);
    game.mlx = mlx_init(game.map.width * 64, game.map.height * 64, "so_long", true);
    if (!game.mlx)
        print_error("> MLX42 initialization failed", 1);
    load_textures(&game.textures, game.mlx);
    render_map(&game.map, &game.textures, game.mlx);
    game.movements = 0;
    game.moves_text = NULL;
    mlx_key_hook(game.mlx, handle_input, &game);
    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
    return (0);
}
