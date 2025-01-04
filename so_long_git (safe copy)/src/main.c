/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:59:02 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/04 18:11:50 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* WITH DEBUGGING

int main(int argc, char **argv)
{
    char        **map;
    t_map_state state;
    int         i;
    int         map_width = 0;
    int         map_height = 0;
    int         player_x, player_y;

    state.collectibles = 0;
    state.exit_found = 0;

    if (argc != 2)
        return (ft_printf("Usage: ./so_long <map_file>\n"));

    // Load the map from the file
    map = load_map_from_file(argv[1]);

    // Debug log: Check the map contents
    if (map)
    {
        ft_printf("Loaded map:\n");
        for (i = 0; map[i]; i++) // Iterate through each row
        {
            ft_printf("Row %d: %s\n", i, map[i]);
        }

        // Set map dimensions
        map_width = ft_strlen(map[0]);  // Assuming all rows have the same width
        map_height = i;  // The height is the number of rows in the map

        // Debug: Print map dimensions
        ft_printf("Map dimensions: Width = %d, Height = %d\n", map_width, map_height);
    }
    else
    {
        ft_printf("Error: Failed to load map.\n");
        return 1;
    }

    // Validate map structure
    if (!map || !validate_map_structure(map))
        return (ft_printf("Error: Invalid map structure\n"));

    // Find the player's starting position
    player_x = find_player_x(map);
    player_y = find_player_y(map);

    // Debug log: Check the player's starting position
    ft_printf("Player starting position: x=%d, y=%d\n", player_x, player_y);

    // Initialize map state with map dimensions
    state.map_width = map_width;
    state.map_height = map_height;

    // Count the collectibles before validating the map
    state.collectibles = count_collectibles(map, &state);

    // We pass 'V' as the visit flag to start marking visited cells
    char visit_flag = 'V'; // This is the flag we'll use for visited cells

    // Validate map configuration using player position and map state
    if (!validate_map(map, player_x, player_y, &state, visit_flag))
        return (ft_printf("Error: Invalid map configuration\n"));

    // Check for reachable collectibles and exit
    ft_printf("Collectibles: %d, Exit Found: %d\n", state.collectibles, state.exit_found);
    if (state.collectibles == 0 || state.exit_found == 0)
        return (ft_printf("Error: Unreachable collectibles or exit\n"));
    
    ft_printf("Sucess: validation complete. Game will start:\n");

    // Start the game
    start_game(map);
    return (0);
}
*/

/*int main(int argc, char **argv)
{
    char        **map;
    t_map_state state;
    int         map_width = 0;
    int         map_height = 0;
    int         player_x, player_y;

    state.collectibles = 0;
    state.exit_found = 0;

    if (argc != 2)
        return (ft_printf("Usage: ./so_long <map_file>\n"));

    // Load the map from the file
    map = load_map_from_file(argv[1]);

    if (!map)
    {
        ft_printf("Error: Failed to load map.\n");
        return 1;
    }

    // Set map dimensions
    map_width = ft_strlen(map[0]);  // Assuming all rows have the same width
    map_height = ft_strarr_len(map);  // The height is the number of rows in the map

    // Validate map structure
    if (!map || !validate_map_structure(map))
        return (ft_printf("Error: Invalid map structure\n"));

    // Find the player's starting position
    player_x = find_player_x(map);
    player_y = find_player_y(map);

    // Initialize map state with map dimensions
    state.map_width = map_width;
    state.map_height = map_height;

    // Count the collectibles before validating the map
    state.collectibles = count_collectibles(map, &state);

    // Allocate and initialize the visited map
    char **visited = (char **)malloc(sizeof(char *) * map_height);
    if (!visited)
    {
        ft_printf("Error: Failed to allocate visited map\n");
        return 1;
    }
    for (int i = 0; i < map_height; i++) {
        visited[i] = (char *)malloc(sizeof(char) * map_width);
        if (!visited[i]) {
            ft_printf("Error: Failed to allocate visited map row\n");
            return 1;
        }
        // Initialize all cells as not visited (0)
        for (int j = 0; j < map_width; j++) {
            visited[i][j] = 0;
        }
    }

    // Validate map configuration using player position and map state
    if (!validate_map(map, player_x, player_y, &state, visited))
    {
        ft_printf("Error: Invalid map configuration\n");

        // Free visited map if validation fails
        for (int i = 0; i < map_height; i++) {
            free(visited[i]);
        }
        free(visited);
        return 1;
    }

    // Check for reachable collectibles and exit
    if (state.collectibles == 0 || state.exit_found == 0)
    {
        ft_printf("Error: Unreachable collectibles or exit\n");

        // Free visited map if validation fails
        for (int i = 0; i < map_height; i++) {
            free(visited[i]);
        }
        free(visited);
        return 1;
    }
    
    ft_printf("Success: validation complete. Game will start:\n");

    // Free the visited map after successful validation
    for (int i = 0; i < map_height; i++) {
        free(visited[i]);
    }
    free(visited);

    // Start the game
    start_game(map);

    return (0);
}
*/

int main(int argc, char **argv)
{
    char        **map;
    t_map_state state;
    int         map_width = 0;
    int         map_height = 0;
    int         player_x, player_y;

    state.collectibles = 0;
    state.exit_found = 0;

    map = parse_arguments_and_load_map(argc, argv);
    if (!map)
        return 1;

    map_width = ft_strlen(map[0]);
    map_height = ft_strarr_len(map);

    if (!validate_map_structure_and_player_position(map, &state, map_width, map_height, &player_x, &player_y))
        return 1;

    state.map_width = map_width;
    state.map_height = map_height;

    state.collectibles = count_collectibles(map, &state);

    char **visited = initialize_visited_map(map_width, map_height);
    if (!visited)
        return 1;

    if (!validate_map(map, player_x, player_y, &state, visited))
    {
        ft_printf("Error: Invalid map configuration\n");
        clean_up_visited_map(visited, map_height);
        return 1;
    }

    if (state.collectibles == 0 || state.exit_found == 0)
    {
        ft_printf("Error: Unreachable collectibles or exit\n");
        clean_up_visited_map(visited, map_height);
        return 1;
    }

    ft_printf("Success: validation complete. Game will start:\n");

    clean_up_visited_map(visited, map_height);
    start_game(map);

    return 0;
}

char **parse_arguments_and_load_map(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("Usage: ./so_long <map_file>\n");
        return NULL;
    }

    char **map = load_map_from_file(argv[1]);
    if (!map)
    {
        ft_printf("Error: Failed to load map.\n");
        return NULL;
    }
    return map;
}

int validate_map_structure_and_player_position(char **map, t_map_state *state, int map_width, int map_height, int *player_x, int *player_y)
{
    (void)state;
    (void)map_width;
    (void)map_height;

    if (!map || !validate_map_structure(map))
    {
        ft_printf("Error: Invalid map structure\n");
        return 0;
    }

    *player_x = find_player_x(map);
    *player_y = find_player_y(map);

    return 1;
}

char **initialize_visited_map(int map_width, int map_height)
{
    char **visited = (char **)malloc(sizeof(char *) * map_height);
    if (!visited)
    {
        ft_printf("Error: Failed to allocate visited map\n");
        return NULL;
    }

    for (int i = 0; i < map_height; i++) {
        visited[i] = (char *)malloc(sizeof(char) * map_width);
        if (!visited[i]) {
            ft_printf("Error: Failed to allocate visited map row\n");
            free(visited);
            return NULL;
        }
        // Initialize all cells as not visited (0)
        for (int j = 0; j < map_width; j++) {
            visited[i][j] = 0;
        }
    }

    return visited;
}

void clean_up_visited_map(char **visited, int map_height)
{
    for (int i = 0; i < map_height; i++) {
        free(visited[i]);
    }
    free(visited);
}

