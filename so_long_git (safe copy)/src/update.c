/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:19:10 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 22:19:12 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_player_pos(char **map, int player_x, int player_y)
{
	int	y;
	int	x;

	y = 0;
	while (y < ft_strarr_len(map))
	{
		x = 0;
		while (x < (int)ft_strlen(map[y]))
		{
			if (map[y][x] == 'P')
				map[y][x] = '0';
			if (x == player_x && y == player_y)
				map[y][x] = 'P';
			x++;
		}
		y++;
	}
}

void	print_updated_map(char **map)
{
	int	y;

	y = 0;
	while (y < ft_strarr_len(map))
	{
		ft_printf("Row %d: %s\n", y, map[y]);
		y++;
	}
}

void	update_map_position(char **map, int player_x, int player_y)
{
	update_player_pos(map, player_x, player_y);
	print_updated_map(map);
}
