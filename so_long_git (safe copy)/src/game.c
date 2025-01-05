/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:05:14 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/05 17:43:50 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* *********************************************************************
 * Starts the game and runs the main game loop.
 *********************************************************************/

int start_game(char **map)
{
    t_game game;

    // Set player position
    game.player_x = find_player_x(map);
    game.player_y = find_player_y(map);
    ft_printf("Player position initialized: x=%d, y=%d\n", game.player_x, game.player_y);

    // Assign the map to the game structure
    game.map = map;

    // Initialize the valid movements counter
    game.valid_movements = 0;

    // Initialize the window
    if (!init_window(&game, map))
        return (ft_error("Error: Unable to initialize the window"));

    // Initialize the key event hooks
    init_hooks(&game);

    // Main game loop
    mlx_loop(game.mlx);  // Start the event loop to process key presses and render the game

    cleanup_game(&game);  // Cleanup after the game loop ends
    return (0);
}


/* *********************************************************************
 * Checks if the game is still running (window is open).
 *********************************************************************/

int game_is_running(t_game *game)
{
    if (game->win == NULL)
        return (0);
    return (1);
}

/* *********************************************************************
 * This function is called when a key is pressed.
 * It handles key events like ESC and player movement.
 *********************************************************************/



// Function to handle key press and check for "You Win"
// Function to check if all collectibles are collected
// Function to check if all collectibles are collected
int are_collectibles_collected(char **map)
{
    for (int y = 0; map[y] != NULL; y++)
    {
        for (int x = 0; map[y][x] != '\0'; x++)
        {
            if (map[y][x] == 'C')  // If a collectible is found, return false
                return 0;
        }
    }
    return 1;  // All collectibles have been collected
}

// Function to handle key press and check for "You Win"
// Function to handle key press and check for valid movements
int handle_key_press(int keycode, t_game *game)
{
    ft_printf("Key pressed: %d\n", keycode);  // Debugging print

    // ESC key: Exit the game
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(game->mlx, game->win);
        game->win = NULL;
        exit(0);
    }

    // Store the current position to check later
    int new_player_x = game->player_x;
    int new_player_y = game->player_y;

    // Player movement handling
    if (keycode == KEY_UP)
    {
        ft_printf("Moving UP\n");
        new_player_y -= 1;
    }
    else if (keycode == KEY_DOWN)
    {
        ft_printf("Moving DOWN\n");
        new_player_y += 1;
    }
    else if (keycode == KEY_LEFT)
    {
        ft_printf("Moving LEFT\n");
        new_player_x -= 1;
    }
    else if (keycode == KEY_RIGHT)
    {
        ft_printf("Moving RIGHT\n");
        new_player_x += 1;
    }

    // Check if the new position is within the boundaries of the map
    if (new_player_x < 0 || new_player_x >= (int)ft_strlen(game->map[0]) || new_player_y < 0 || new_player_y >= ft_strarr_len(game->map))
    {
        ft_printf("Out of bounds. Player cannot move.\n");
        return (0);  // Invalid move
    }

    // Check if the destination is a wall ('1')
    if (game->map[new_player_y][new_player_x] == '1')
    {
        ft_printf("Hit a wall. Player cannot move.\n");
        return (0);  // Invalid move
    }

    // If the player is moving over the exit ('E'), check adjacent cell and "jump" over it
    if (game->map[new_player_y][new_player_x] == 'E')
    {
        // Check if all collectibles are collected
        int all_collectibles_collected = are_collectibles_collected(game->map);

        // If all collectibles are collected, allow the player to "collect" the exit and end the game
        if (all_collectibles_collected)
        {
            ft_printf("You Win! All collectibles collected.\n");
            mlx_destroy_window(game->mlx, game->win);
            game->win = NULL;
            exit(0);  // Exit the game
        }
        else
        {
            ft_printf("Player is jumping over the exit at (%d, %d)\n", new_player_x, new_player_y);

            // Check adjacent cell depending on movement direction
            int next_x = new_player_x;
            int next_y = new_player_y;

            // Determine the adjacent cell based on the movement direction
            if (keycode == KEY_UP)
                next_y -= 1;
            else if (keycode == KEY_DOWN)
                next_y += 1;
            else if (keycode == KEY_LEFT)
                next_x -= 1;
            else if (keycode == KEY_RIGHT)
                next_x += 1;

            // Ensure the next cell is a valid space ('0') or within bounds
            if (next_x < 0 || next_x >= (int)ft_strlen(game->map[0]) || next_y < 0 || next_y >= ft_strarr_len(game->map) ||
                game->map[next_y][next_x] == '1')  // Wall or out of bounds
            {
                ft_printf("Cannot jump over the exit. Blocked by wall or out of bounds.\n");
                return (0);  // Block the movement, invalid
            }

            // If adjacent cell is valid (floor), update position to the next cell
            new_player_x = next_x;
            new_player_y = next_y;
        }
    }

    // Check if player is moving to a valid tile (floor '0') or jumping over exit
    if (game->map[new_player_y][new_player_x] == '0' || game->map[new_player_y][new_player_x] == 'E')
    {
        count_valid_move(game);  // Increment valid movement counter
    }

    // Update player position if valid
    game->player_x = new_player_x;
    game->player_y = new_player_y;

    // Update map with new player position
    update_map_position(game->map, game->player_x, game->player_y);

    ft_printf("Player position updated to: (%d, %d)\n", game->player_x, game->player_y);
    render_game(game, game->map);  // Render the updated game state after movement

    return (0);
}

// Function to increment valid movements counter
void count_valid_move(t_game *game)
{
    game->valid_movements++;
    ft_printf("Valid movement. Total valid moves: %d\n", game->valid_movements);
}











/* *********************************************************************
 * This function sets up the key hooks using mlx_key_hook.
 *********************************************************************/

void init_hooks(t_game *game)
{
    // Hook the key press events to the handle_key_press function
    mlx_key_hook(game->win, handle_key_press, game);
}

/*int is_valid_move(t_game *game, int new_x, int new_y)
{
    // Check if the new position is within the bounds of the map
    if (new_x < 0 || new_x >= game->map_state.map_width || new_y < 0 || new_y >= game->map_state.map_height)
        return 0;  // Invalid move (out of bounds)
    
    // Check if the new position is a wall (1)
    if (game->map[new_y][new_x] == '1')
        return 0;  // Invalid move (wall)

    return 1;  // Valid move
}
*/



