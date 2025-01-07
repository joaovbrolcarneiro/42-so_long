/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:21:11 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 17:51:41 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int validate_map_structure(char **map)
{
    size_t row_length = ft_strlen(map[0]);

    // Check if all rows are of the same length
    if (!check_row_length(map, row_length))
    {
        ft_printf("Error: Row lengths are inconsistent\n");
        return (0);  // Return early on error
    }

    // Check top boundary
    if (!check_top_boundary(map))
    {
        ft_printf("Error: Top boundary is invalid\n");
        return (0);  // Return early on error
    }

    // Check bottom boundary
    if (!check_bottom_boundary(map, row_length))
    {
        ft_printf("Error: Bottom boundary is invalid\n");
        return (0);  // Return early on error
    }

    // Check side boundaries
    if (!check_side_boundaries(map, row_length))
    {
        ft_printf("Error: Side boundaries are invalid\n");
        return (0);  // Return early on error
    }

    // Check player and exit validity (make sure player and exit exist)
    if (!check_player_and_exit(map))
    {
        ft_printf("Error: Player or exit is not placed correctly\n");
        return (0);  // Return early on error
    }

    return (1);  // All checks passed
}



int	validate_map_struct_and_plyr_pos(char **map, int *player_x, int *player_y)
{
    int player_count = 0;

    // Count occurrences of 'P' for player
    for (int i = 0; map[i] != NULL; i++) {
        for (int j = 0; map[i][j] != '\0'; j++) {
            if (map[i][j] == 'P') {
                player_count++;
                if (player_count > 1) {
                    ft_printf("Error: More than one player found on the map\n");
                    return (0);  // More than one player
                }
                *player_x = j;
                *player_y = i;
            }
        }
    }

    if (player_count == 0) {
        ft_printf("Error: No player found on the map\n");
        return (0);  // No player found
    }

    return (1);  // Exactly one player found
}


int check_side_boundaries(char **map, size_t row_length)
{
    int i;

    // Check left and right boundaries for each row
    i = 0;
    while (map[i] != NULL)
    {
        if (map[i][0] != '1' || map[i][row_length - 1] != '1')
        {
            ft_printf("Error: Left or right boundary is not a wall at row %d\n", i);
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
	int	player_count = 0;
	int	exit_count = 0;

	ft_printf("Debug: Checking player and exit...\n");

	// Count player and exit occurrences
	count_player_and_exit(map, &player_count, &exit_count);

	ft_printf("Debug: Player count: %d, Exit count: %d\n", player_count, exit_count);

	// Ensure only one player and one exit exists
	if (player_count != 1)
	{
		ft_printf("Error: Invalid player count: %d\n", player_count);
		return (0);
	}
	if (exit_count != 1)
	{
		ft_printf("Error: Invalid exit count: %d\n", exit_count);
		return (0);
	}

	ft_printf("Debug: Player and exit validation passed\n");
	return (1);
}

