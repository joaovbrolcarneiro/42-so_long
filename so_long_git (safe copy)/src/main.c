/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:59:02 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 00:16:52 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char			**map;
	t_game			game;
	char			**visited;
	t_validation	validation;

	map = parse_arguments_and_load_map(argc, argv);
	if (!map)
		return (1);
	game.map_state.map_width = ft_strlen(map[0]);
	game.map_state.map_height = ft_strarr_len(map);
	if (!validate_map_struct_and_plyr_pos(map, &game.player_x, &game.player_y))
		return (1);
	init_st(&game.map_state, map);
	visited = i_vm(game.map_state.map_width, game.map_state.map_height);
	if (!visited)
		return (1);
	validation.game = &game;
	validation.map = map;
	validation.state = &game.map_state;
	validation.visited = visited;
	if (!check_map_validity(&validation))
		return (1);
	//clean_up_visited_map(visited, game.map_state.map_height);
	start_game(map);
	return (0);
}

int	check_map_validity(t_validation *validation)
{
	if (!validate_map(validation->map, validation->game->player_x,
			validation->game->player_y, validation->state,
			validation->visited))
		return (print_error_and_return(validation->visited,
				validation->state->map_height));
	if (validation->state->collectibles == 0)
		return (print_error_and_return(validation->visited,
				validation->state->map_height));
	if (validation->state->exit_found == 0)
		return (print_error_and_return(validation->visited,
				validation->state->map_height));
	return (1);
}

int	print_error_and_return(char **visited, int map_height)
{
	ft_printf("Error!\n");
	clean_up_visited_map(visited, map_height);
	return (1);
}
