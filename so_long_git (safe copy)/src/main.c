/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:59:02 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/06 22:28:15 by jbrol-ca         ###   ########.fr       */
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



int check_map_validity(t_validation *validation)
{
    if (!validate_map(validation->map, validation->game->player_x, validation->game->player_y, validation->state, validation->visited))
        return (print_error_and_return(validation->visited, validation->state->map_height));
    if (validation->state->collectibles == 0 || validation->state->exit_found == 0)
        return (print_error_and_return(validation->visited, validation->state->map_height));
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

static char	**handle_empty_file(char **map, int fd)
{
	ft_printf("Error: File is empty or no valid lines found.\n");
	free(map);
	close(fd);
	return (NULL);
}

char	**load_map_from_file(const char *filename)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error: Failed to open file %s\n", filename), NULL);
	map = malloc(sizeof(char *) * MAX_MAP_ROWS);
	if (!map)
		return (ft_printf("Error: Memory allocation failed for map.\n"),
			close(fd), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		strip_newline(line);
		map[i++] = line;
		line = get_next_line(fd);
	}
	if (i == 0)
		return (handle_empty_file(map, fd));
	map[i] = NULL;
	close(fd);
	return (map);
}

int	validate_row_lengths(char **map)
{
	int		i;
	size_t	row_length;

	row_length = ft_strlen(map[0]);
	i = 1;
	while (map[i] != NULL)
	{
		if (ft_strlen(map[i]) != row_length)
		{
			ft_printf("Error: Inconsistent row lengths.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	validate_boundaries(char **map)
{
	int		i;
	size_t	row_length;

	row_length = ft_strlen(map[0]);
	i = 0;
	while (map[i] != NULL)
	{
		if (map[i][0] != '1' || map[i][row_length - 1] != '1')
		{
			ft_printf("Error!\n");
			return (0);
		}
		if (i == 0 && map[i][i] != '1')
		{
			ft_printf("Error!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int validate_map_structure(char **map)
{
    int i;
    int j;
    size_t row_length;

    row_length = ft_strlen(map[0]);

    for (i = 1; map[i] != NULL; i++)
    {
        if (ft_strlen(map[i]) != row_length)
        {
            ft_printf("Error: Inconsistent row lengths.\n");
            return (0);
        }
    }

    for (i = 0; map[0][i] != '\0'; i++)
    {
        if (map[0][i] != '1')
        {
            ft_printf("Error: Top boundary is not properly walled.\n");
            return (0);
        }
    }

    for (i = 0; map[i] != NULL; i++)
    {
        if (map[i][row_length - 1] != '1')
        {
            ft_printf("Error: Bottom boundary is not properly walled.\n");
            return (0);
        }
    }

    for (i = 0; map[i] != NULL; i++)
    {
        if (map[i][0] != '1' || map[i][row_length - 1] != '1')
        {
            ft_printf("Error: Side boundaries are not properly walled.\n");
            return (0);
        }
    }

    int player_count = 0;
    int exit_count = 0;

    for (i = 0; map[i] != NULL; i++)
    {
        for (j = 0; map[i][j] != '\0'; j++)
        {
            if (map[i][j] == 'P')
                player_count++;
            if (map[i][j] == 'E')
                exit_count++;
        }
    }

    if (player_count != 1 || exit_count != 1)
    {
        ft_printf("Error: There should be exactly one player (P) and one exit (E).\n");
        return (0);
    }

    return (1);
}

char **append_line_to_map(char **map, char *line)
{
    char **new_map;
    int i;

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

void strip_newline(char *line)
{
    int len;

    if (!line)
        return;

    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
}
