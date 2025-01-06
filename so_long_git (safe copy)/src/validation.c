/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:21:11 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/06 23:21:18 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map_structure(char **map)
{
	size_t	row_length;

	row_length = ft_strlen(map[0]);
	if (!check_row_length(map, row_length))
		return (0);
	if (!check_top_boundary(map))
		return (0);
	if (!check_bottom_boundary(map, row_length))
		return (0);
	if (!check_side_boundaries(map, row_length))
		return (0);
	if (!check_player_and_exit(map))
		return (0);
	return (1);
}

int	validate_map_struct_and_plyr_pos(char **map, int *player_x, int *player_y)
{
	if (!map || !(map))
	{
		ft_printf("Error: Invalid map structure\n");
		return (0);
	}
	*player_x = find_player_x(map);
	*player_y = find_player_y(map);
	return (1);
}

int	check_side_boundaries(char **map, size_t row_length)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (map[i][0] != '1' || map[i][row_length - 1] != '1')
		{
			ft_printf("Error!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	count_player_and_exit(char **map, int *player_count, int *exit_count)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'P')
				(*player_count)++;
			if (map[i][j] == 'E')
				(*exit_count)++;
			j++;
		}
		i++;
	}
	return (1);
}

int	check_player_and_exit(char **map)
{
	int	player_count;
	int	exit_count;

	player_count = 0;
	exit_count = 0;
	if (!count_player_and_exit(map, &player_count, &exit_count))
		return (0);
	if (player_count != 1)
	{
		ft_printf("Error!\n");
		return (0);
	}
	if (exit_count != 1)
	{
		ft_printf("Error!\n");
		return (0);
	}
	return (1);
}
