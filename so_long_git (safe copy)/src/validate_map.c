/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:57:11 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/08 15:24:40 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "so_long.h"

int	count_collectibles(char **map, t_map_state *state)
{
	int	collectibles;
	int	x;
	int	y;

	collectibles = 0;
	y = 0;
	while (y < state->map_height)
	{
		x = 0;
		while (x < state->map_width)
		{
			if (map[y][x] == 'C')
				collectibles++;
			x++;
		}
		y++;
	}
	ft_printf("Total collectibles found: %d\n", collectibles);
	return (collectibles);
}

int	validate_map(char **map, int x, int y, t_validation *validation)
{
	if (!is_valid_character(map, validation->state->map_width,
			validation->state->map_height)
		|| x < 0 || y < 0 || x >= validation->state->map_width
		|| y >= validation->state->map_height || map[y][x] == '1'
		|| validation->visited[y][x])
	{
		return (0);
	}
	validation->visited[y][x] = 1;
	if (map[y][x] == 'E')
		validation->state->ex_fnd = 1;
	validate_map(map, x + 1, y, validation);
	validate_map(map, x - 1, y, validation);
	validate_map(map, x, y + 1, validation);
	validate_map(map, x, y - 1, validation);
	if (!clctbls_rchble(map, x, y, validation->state))
	{
		ft_printf("Error: Not all collectibles are reachable by the player\n");
		return (0);
	}
	return (1);
}

int	clctbls_rchble(char **map, int player_x, int player_y, t_map_state *state)
{
	t_validation	validation;
	int				reachable_collectibles;

	validation.state = state;
	validation.visited = i_vm(state->map_width, state->map_height);
	if (!validation.visited)
		return (0);
	reachable_collectibles = cnt_rechble(map, player_x, player_y, &validation);
	clean_up_visited_map(validation.visited, state->map_height);
	if (reachable_collectibles == state->collectibles)
		return (1);
	return (0);
}

int	cnt_rechble(char **map, int x, int y, t_validation *validation)
{
	int	count;

	if (x < 0)
		return (0);
	if (y < 0)
		return (0);
	if (x >= validation->state->map_width)
		return (0);
	if (y >= validation->state->map_height)
		return (0);
	if (map[y][x] == '1')
		return (0);
	if (validation->visited[y][x])
		return (0);
	validation->visited[y][x] = 1;
	count = 0;
	if (map[y][x] == 'C')
		count++;
	count += cnt_rechble(map, x + 1, y, validation);
	count += cnt_rechble(map, x - 1, y, validation);
	count += cnt_rechble(map, x, y + 1, validation);
	count += cnt_rechble(map, x, y - 1, validation);
	return (count);
}

int	is_valid_character(char **map, int map_width, int map_height)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_height)
	{
		j = 0;
		while (j < map_width)
		{
			if (map[i][j] != 'P' && map[i][j] != 'C' && map[i][j] != '0' &&
				map[i][j] != '1' && map[i][j] != 'E')
			{
				ft_printf("Error: Invalid character found.");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
