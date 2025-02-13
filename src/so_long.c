/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/13 00:40:06 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/so_long.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);  // Salimos del programa
	return (0);
}

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;
	int		y;
	int		x;

	mlx_connection = mlx_init(); // inicializa la conexión con el servidor gráfico y devuelve un puntero a la conexión
	if (mlx_connection == NULL)
		return (1);
	mlx_window = mlx_new_window(mlx_connection, WIDTH, HEIGHT, "My window"); // crea una ventana y devuelve un puntero
	if (mlx_window == NULL)
	{
		mlx_destroy_display(mlx_connection);
		free(mlx_connection);
		return (1);
	}
	y = HEIGHT * 0.1;
	while (y < HEIGHT * 0.9)
	{
		x = WIDTH * 0.1;
		while (x < WIDTH * 0.9)
		{
			mlx_pixel_put(mlx_connection, mlx_window, x, y, rand() % 0x1000000);
			x++;
		}
		mlx_pixel_put(mlx_connection, mlx_window, x, y, rand() % 0x1000000);
		y++; 	
	}
	mlx_string_put(mlx_connection, mlx_window, WIDTH * 0.8, HEIGHT * 0.95, rand() % 0x1000000, "My draw");
	mlx_hook(mlx_window, 17, 0, close_window, NULL); // Hook para el cierre de la ventana
	mlx_loop(mlx_connection); // mantiene el proceso vivo para que no se cierre la ventana. Va al final
}