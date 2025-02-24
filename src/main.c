/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/24 00:12:27 by cesar            ###   ########.fr       */
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

int main(int argc, char **argv)
{
    t_map   map;
    
    if (argc != 2)
        print_error("Error > Correct usage: /so_long <map_file.ber>\n", 1);
    initialize_map(&map, argv[1]);
    return (0);
}
