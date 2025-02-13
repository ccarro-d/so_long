/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarro-d <ccarro-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/13 21:59:20 by ccarro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Prototipo de función para dibujar letras simuladas en la imagen
void draw_text(mlx_image_t *image, int x, int y, const char *text, uint32_t color)
{
    int i = 0;
    while (text[i])
    {
        for (int px = 0; px < 8; ++px)
        {
            for (int py = 0; py < 10; ++py)
            {
                if ((px + py) % 3 == 0)  // Patrón simple para simular letras
                    mlx_put_pixel(image, x + px + (i * 10), y + py, color);
            }
        }
        i++;
    }
}

void	loop_function(void *param)
{
	(void)param;
	// Aquí puedes agregar lógica futura, por ahora está vacío.
}

void close_window(mlx_t *mlx)
{
    mlx_terminate(mlx); // Cierra la ventana y libera recursos
    exit(0);
}

int main(void)
{
    mlx_t *mlx;
    mlx_image_t *img;
    int y, x;

    mlx = mlx_init(WIDTH, HEIGHT, "My window", true);  // Inicializa la ventana
    if (!mlx)
        return (1);

    // Crea una nueva imagen (buffer de píxeles) de tamaño WIDTH x HEIGHT
    img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!img)
    {
        mlx_terminate(mlx);
        return (1);
    }

    // Dibuja píxeles en el buffer de la imagen
    y = HEIGHT * 0.1;
    while (y < HEIGHT * 0.9)
    {
        x = WIDTH * 0.1;
        while (x < WIDTH * 0.9)
        {
            mlx_put_pixel(img, x, y, rand() % 0x1000000);  // Coloca un píxel de color aleatorio
            x++;
        }
        y++;
    }

    // Coloca la imagen (con los píxeles dibujados) en la ventana
    mlx_image_to_window(mlx, img, 0, 0);

	mlx_put_string(mlx, "My draw", WIDTH * 0.8, HEIGHT * 0.95); // escribe solamente en blanco

	 // Función para escribir texto en otro color, como el verde (0x00FF00FF)
    draw_text(img, WIDTH * 0.1, HEIGHT * 0.8, "My draw", 0x00FF00FF);

    // Hook para cerrar la ventana cuando se presiona el aspa de cierre
	mlx_loop_hook(mlx, loop_function, NULL);  // El loop function mantiene el proceso vivo

    // Mantiene el bucle de eventos para que la ventana no se cierre
    mlx_loop(mlx);

    // Libera recursos (nunca llega aquí porque se llama en close_window)
    mlx_terminate(mlx);
    return (0);
}