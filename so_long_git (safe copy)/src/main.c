/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:59:02 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/06 23:09:00 by jbrol-ca         ###   ########.fr       */
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
	clean_up_visited_map(visited, game.map_state.map_height);
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

void	init_st(t_map_state *state, char **map)
{
	state->collectibles = count_collectibles(map, state);
	state->exit_found = 0;
}

int	print_error_and_return(char **visited, int map_height)
{
	ft_printf("Error!\n");
	clean_up_visited_map(visited, map_height);
	return (1);
}

char	**parse_arguments_and_load_map(int argc, char **argv)
{
	char	**map;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long <map_file>\n");
		return (NULL);
	}
	map = load_map_from_file(argv[1]);
	if (!map)
	{
		ft_printf("Error: Failed to load map.\n");
		return (NULL);
	}
	return (map);
}

char	**i_vm(int map_width, int map_height)
{
	char	**visited;
	int		i;
	int		j;

	visited = (char **)malloc(sizeof(char *) * map_height);
	if (!visited)
		return (ft_printf("Error: Failed to allocate visited map\n"), NULL);
	i = 0;
	while (i < map_height)
	{
		visited[i] = (char *)malloc(sizeof(char) * map_width);
		if (!visited[i])
			return (free(visited), ft_printf("Error!\n"), NULL);
		j = 0;
		while (j < map_width)
			visited[i][j++] = 0;
		i++;
	}
	return (visited);
}

void	clean_up_visited_map(char **visited, int map_height)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

char	**append_line_to_map(char **map, char *line)
{
	char	**new_map;
	int		i;

	if (!line)
		return (map);
	i = 0;
	while (map && map[i])
		i++;
	new_map = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map && map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(map);
	return (new_map);
}

void	strip_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}
