/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:59:02 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/08 15:20:17 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char			**map;
	t_game			game;
	char			**visited;
	t_validation	validation;

	map = parse_args_and_load_map(argc, argv);
	if (!map || !check_map(map))
		return (1);
	game.map_state.map_width = ft_strlen(map[0]);
	game.map_state.map_height = ft_strarr_len(map);
	if (!vms(map) || !vmsnpp(map, &game.player_x, &game.player_y))
		tr(NULL, map, game.map_state.map_height);
	init_st(&game.map_state, map);
	visited = i_vm(game.map_state.map_width, game.map_state.map_height);
	if (!visited)
		tr(NULL, map, game.map_state.map_height);
	validation.game = &game;
	validation.map = map;
	validation.state = &game.map_state;
	validation.visited = visited;
	if (!check_map_validity(&validation))
		tr(visited, map, game.map_state.map_height);
	clean_up_visited_map(visited, game.map_state.map_height);
	start_game(map);
	return (0);
}

char	**check_map(char **map)
{
	if (!map)
		return (ft_printf("Error!\n"), NULL);
	return (map);
}

int	check_map_validity(t_validation *validation)
{
	int	y;
	int	x;
	int	exit_count;

	if (!validate_map(validation->map, validation->game->player_x,
			validation->game->player_y, validation))
		return (0);
	if (validation->state->collectibles == 0 || validation->state->ex_fnd == 0)
		return (0);
	exit_count = 0;
	y = 0;
	while (y < validation->state->map_height)
	{
		x = 0;
		while (x < validation->state->map_width)
		{
			if (validation->map[y][x] == 'E')
				exit_count++;
			x++;
		}
		y++;
	}
	if (exit_count != 1)
		return (0);
	return (1);
}
