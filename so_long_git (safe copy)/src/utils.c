/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:14:26 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/03 16:42:05 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_error(const char *message)
{
	ft_printf("%s\n", message);
	return (1);
}

int	is_wall(const char *line)
{
	while (*line)
	{
		if (*line != '1')
			return (0);
		line++;
	}
	return (1);
}

void get_map_dimensions(char **map, int *width, int *height)
{
    *height = 0;
    *width = ft_strlen(map[0]);  // Get width from the first row

    while (map[*height] != NULL)  // Count the height (rows)
    {
        (*height)++;
    }
}

int find_player_x(char **map)
{
    int x = 0;
    while (map[x]) // Iterate through all rows
    {
        int y = 0;
        while (map[x][y])  // Iterate through each column in the row
        {
            if (map[x][y] == 'P')  // Found the player
                return y;
            y++;
        }
        x++;
    }
    return -1;  // Return -1 if player is not found
}

int find_player_y(char **map)
{
    int y = 0;
    while (map[y])  // Iterate through all rows
    {
        int x = 0;
        while (map[y][x])  // Iterate through each column in the row
        {
            if (map[y][x] == 'P')  // Found the player
                return y;
            x++;
        }
        y++;
    }
    return -1;  // Return -1 if player is not found
}


int ft_strarr_len(char **arr)
{
    int len = 0;
    while (arr[len])
        len++;
    return len;
}
