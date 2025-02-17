/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/17 18:53:21 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	print_error(char *error_explained, int error_code)
{
	ft_putstr_fd(error_explained, STDERR_FILENO);
	exit(error_code);
}

int main(int argc, char **argv)
{
    t_map   map; //TODO: ¿Función para inicializar?
    
    if (argc != 2)
        print_error("Error > Correct usage: /so_long <map_file.ber>\n", 1);
    initialize_map(&map, argv[1]);
    print_map(map.grid); // Verificamos el contenido del mapa
    return (0);
}
