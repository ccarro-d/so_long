/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:10:13 by ccarro-d          #+#    #+#             */
/*   Updated: 2025/02/17 19:14:07 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

size_t count_lines(char *map_file)
{
    int     fd;
    size_t  lines;
    char    buf[BUFFER_SIZE];
    char    prev;
    
    fd = open(map_file, O_RDONLY);
    lines = 0;
    while (read(fd, buf, BUFFER_SIZE) > 0)
    {
        if (buf[0] == '\n' && buf[0] != prev)
            lines++;
        prev = buf[0];
    }
    close (fd);
    return (lines + 1);
}

char    **read_map(char *map_file, size_t *map_height)
{
    int     fd;
    char    **grid;
    int     i;
    char    *line;

    fd = open(map_file, O_RDONLY);
    grid = (char **)ft_calloc(sizeof(char *), *map_height);
    if (fd < 0 || !grid)
        return (NULL);
    i = 0;
    while ((line = get_next_line(fd)))
        grid[i++] = line;
    close(fd);
    return (grid);
}

size_t check_lines_length(char **map_grid)
{
    int     i;
    size_t  length;

    i = 0;
    while (map_grid[i])
    {
        length = ft_strlen(map_grid[i]);
        i++;
    }
}

void    print_map(char **map_grid)
{
    int i;

    i = 0;
    while (map_grid[i])
    {
        write(1, map_grid[i], ft_strlen(map_grid[i]));
        i++;
    }
}

void    initialize_map(t_map *map, char *map_file)
{
    map->height = count_lines(map_file);
    map->grid = read_map(map_file, map->height);
    if (!map->grid)
        print_error("Error > Map could not be read", 1);
    map->width = check_lines_length(map->grid);
    if (!map->width)
        print_error("Error > Map must be a square or rectangle", 1);
}