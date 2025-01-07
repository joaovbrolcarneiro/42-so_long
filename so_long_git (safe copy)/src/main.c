/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:59:02 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 18:37:53 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
    char **map;
    t_game game;
    char **visited;
    t_validation validation;

    // Parse map
    map = parse_arguments_and_load_map(argc, argv);
    if (!map)
    {
        ft_printf("Error: Map loading failed\n");
        return (1);
    }

    game.map_state.map_width = ft_strlen(map[0]);
    game.map_state.map_height = ft_strarr_len(map);

    // Validate map structure
    if (!validate_map_structure(map))
    {
        ft_printf("Debug: Invalid map structure\n");
        terminate_program(NULL, map, game.map_state.map_height, "Error! Invalid map structure.");
    }

    // Validate player position and other checks
    if (!validate_map_struct_and_plyr_pos(map, &game.player_x, &game.player_y))
    {
        ft_printf("Debug: Invalid player position\n");
        terminate_program(NULL, map, game.map_state.map_height, "Error! Invalid player position.");
    }

    // Initialize state and visited map
    init_st(&game.map_state, map);
    visited = i_vm(game.map_state.map_width, game.map_state.map_height);
    if (!visited)
    {
        ft_printf("Debug: Failed to allocate visited map\n");
        terminate_program(NULL, map, game.map_state.map_height, "Error! Allocation failure.");
    }

    // Setup validation
    validation.game = &game;
    validation.map = map;
    validation.state = &game.map_state;
    validation.visited = visited;

    // Check map validity
    if (!check_map_validity(&validation))
    {
        ft_printf("Debug: Map validity check failed\n");
        terminate_program(visited, map, game.map_state.map_height, "Error! Map validity failed.");
    }

    // Clean up visited map
    clean_up_visited_map(visited, game.map_state.map_height);

    // Start game
    ft_printf("Debug: All checks passed, starting game...\n");
    start_game(map);
    return (0);
}



void	terminate_program(char **visited, char **map, int map_height, const char *error_message)
{
	if (error_message)
		ft_printf("%s\n", error_message);
	if (visited)
		clean_up_visited_map(visited, map_height);
	if (map)
		free_map(map, map_height);
	exit(1); // Immediately terminate program
}


int check_map_validity(t_validation *validation)
{
    ft_printf("Debug: Validating map...\n");

    // Call validate_map with the validation struct
    if (!validate_map(validation->map, validation->game->player_x,
            validation->game->player_y, validation))
    {
        ft_printf("Debug: Map failed main validation\n");
        return (0);
    }

    if (validation->state->collectibles == 0)
    {
        ft_printf("Debug: No collectibles found\n");
        return (0);
    }

    if (validation->state->exit_found == 0)
    {
        ft_printf("Debug: No exit found\n");
        return (0);
    }

    // Ensure only one exit exists
    int exit_count = 0;
    for (int y = 0; y < validation->state->map_height; y++) {
        for (int x = 0; x < validation->state->map_width; x++) {
            if (validation->map[y][x] == 'E') {
                exit_count++;
            }
        }
    }
    if (exit_count != 1) {
        ft_printf("Error: Multiple exits detected\n");
        return (0);
    }

    ft_printf("Debug: Map validated successfully\n");
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