/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:57:11 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/04 15:38:39 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "so_long.h"

/*int validate_map(char **map, int x, int y, t_map_state *state) {
    // Check for bounds, invalid cells, or already visited cells
    if (x < 0 || y < 0 || x >= state->map_width || y >= state->map_height || map[y][x] == '1' || map[y][x] == 'V') {
        return 0; // Out of bounds, wall ('1'), or already visited cell ('V')
    }

    // If a collectible ('C') is found, increment the collectibles count before marking the cell as visited
    if (map[y][x] == 'C') {
        state->collectibles++;
        ft_printf("Collectible found at (%d, %d)\n", x, y);
        ft_printf("Collectibles incremented: %d\n", state->collectibles);
    }

    // If the exit ('E') is found, mark it and set the exit flag to true
    if (map[y][x] == 'E' && !state->exit_found) {
        state->exit_found = 1;
        ft_printf("Exit found at (%d, %d)\n", x, y);
    }

    // Mark as visited before exploring further (to avoid revisiting this cell)
    char original_cell = map[y][x];  // Store the original cell value
    map[y][x] = 'V';  // Mark cell as visited

    // Debug: Print the current position before any action
    ft_printf("Visiting: (%d, %d), Cell: %c\n", x, y, map[y][x]);

    // Debug: Show the state after visiting the current cell
    ft_printf("Current state after visiting (%d, %d): Collectibles = %d, Exit Found = %d\n", x, y, state->collectibles, state->exit_found);

    // Recursive calls to check adjacent cells (right, left, down, up)
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];
        ft_printf("Exploring (%d, %d)\n", new_x, new_y); // Debug direction
        validate_map(map, new_x, new_y, state);
    }

    // Restore the original cell value after exploring all directions
    map[y][x] = original_cell;

    // Debug: Print state after recursion
    ft_printf("Returning from (%d, %d): Collectibles = %d, Exit Found = %d\n", x, y, state->collectibles, state->exit_found);

    return 1;
}*/


int count_collectibles(char **map, t_map_state *state) {
    int collectibles = 0;

    // Iterate over the entire map and count collectibles ('C')
    for (int y = 0; y < state->map_height; y++) {
        for (int x = 0; x < state->map_width; x++) {
            if (map[y][x] == 'C') {
                collectibles++;
            }
        }
    }

    ft_printf("Total collectibles found: %d\n", collectibles);
    return collectibles;
}

/* WITH DEBUGGING LOGS
int validate_map(char **map, int x, int y, t_map_state *state) {
    // Check for bounds, invalid cells, or already visited cells
    if (x < 0 || y < 0 || x >= state->map_width || y >= state->map_height || map[y][x] == '1' || map[y][x] == 'V') {
        return 0; // Out of bounds, wall ('1'), or already visited cell ('V')
    }

    // If the exit ('E') is found, mark it and set the exit flag to true
    if (map[y][x] == 'E' && !state->exit_found) {
        state->exit_found = 1;
        ft_printf("Exit found at (%d, %d)\n", x, y);
    }

    // Mark as visited before exploring further (to avoid revisiting this cell)
    char original_cell = map[y][x];  // Store the original cell value
    map[y][x] = 'V';  // Mark cell as visited

    // Debug: Print the current position before any action
    ft_printf("Visiting: (%d, %d), Cell: %c\n", x, y, map[y][x]);

    // Debug: Show the state after visiting the current cell
    ft_printf("Current state after visiting (%d, %d): Collectibles = %d, Exit Found = %d\n", x, y, state->collectibles, state->exit_found);

    // Recursive calls to check adjacent cells (right, left, down, up)
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];
        ft_printf("Exploring (%d, %d)\n", new_x, new_y); // Debug direction
        validate_map(map, new_x, new_y, state);
    }

    // Restore the original cell value after exploring all directions
    map[y][x] = original_cell;

    // Debug: Print state after recursion
    ft_printf("Returning from (%d, %d): Collectibles = %d, Exit Found = %d\n", x, y, state->collectibles, state->exit_found);

    return 1;
}*/

int validate_map(char **map, int x, int y, t_map_state *state, char **visited)
{
    // Check for bounds, invalid cells, or already visited cells
    if (x < 0 || y < 0 || x >= state->map_width || y >= state->map_height || map[y][x] == '1' || visited[y][x])
        return 0; // Out of bounds, wall ('1'), or already visited cell

    // Mark the current cell as visited in the visited map
    visited[y][x] = 1;

    // Update state if an exit or collectible is found
    if (map[y][x] == 'E') {
        state->exit_found = 1;
        ft_printf("Exit found at (%d, %d)\n", x, y);
    } else if (map[y][x] == 'C') {
        ft_printf("Collectible found at (%d, %d)\n", x, y);
    }

    // Recursive calls to check adjacent cells (right, left, down, up)
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int i = 0; i < 4; i++) {
        validate_map(map, x + directions[i][0], y + directions[i][1], state, visited);
    }

    return 1;
}
































