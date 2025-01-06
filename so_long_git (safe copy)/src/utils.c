/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:14:26 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/06 23:25:16 by jbrol-ca         ###   ########.fr       */
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
