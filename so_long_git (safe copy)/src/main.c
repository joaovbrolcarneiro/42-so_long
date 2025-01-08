/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:59:02 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/08 15:03:22 by jbrol-ca         ###   ########.fr       */
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

void	tr(char **visited, char **map, int map_height)
{
	terminate_program(visited, map, map_height, "Error!");
}

void	terminate_program(char **visited, char **map, \
int map_height, const char *error_message)
{
	if (error_message)
		ft_printf("%s\n", error_message);
	if (visited)
		clean_up_visited_map(visited, map_height);
	if (map)
		free_map(map, map_height);
	exit(EXIT_FAILURE);
}

int	check_map_validity(t_validation *validation)
{
	int	y;
	int	x;
	int	exit_count;

	if (!validate_map(validation->map, validation->game->player_x,
			validation->game->player_y, validation))
		return (0);
	if (validation->state->collectibles == 0 || validation->state->exit_found == 0)
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

int	print_error_and_return(char **visited, int map_height)
{
	ft_printf("Error!\n");
	if (visited)
		clean_up_visited_map(visited, map_height);
	exit(1); // Terminate program
}

void	free_map(char **map, int map_height)
{
	int	i;

	if (!map)
		return;

	i = 0;
	while (i < map_height)
	{
		if (map[i])
		{
			free(map[i]);
			map[i] = NULL;
		}
		i++;
	}

	free(map);
	map = NULL;
}