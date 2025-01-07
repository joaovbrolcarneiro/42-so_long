/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:21:11 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 20:14:31 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_map_error(void)
{
	ft_printf("Error!\n");
	return (0);
}

int	validate_map_structure(char **map)
{
	size_t	row_length;

	row_length = ft_strlen(map[0]);
	if (!check_row_length(map, row_length))
		return (print_map_error());
	if (!check_top_boundary(map))
		return (print_map_error());
	if (!check_bottom_boundary(map, row_length))
		return (print_map_error());
	if (!check_side_boundaries(map, row_length))
		return (print_map_error());
	if (!check_player_and_exit(map))
		return (print_map_error());
	return (1);
}

int	validate_map_struct_and_plyr_pos(char **map, int *player_x, int *player_y)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = -1;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] == 'P')
			{
				player_count++;
				if (player_count > 1)
					return (print_map_error());
				*player_x = j;
				*player_y = i;
			}
		}
	}
	if (player_count == 0)
		return (print_map_error());
	return (1);
}

int	check_side_boundaries(char **map, size_t row_length)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (map[i][0] != '1' || map[i][row_length - 1] != '1')
			return (print_map_error());
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
