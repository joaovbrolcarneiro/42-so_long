/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:05:14 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/04 23:04:52 by jbrol-ca         ###   ########.fr       */
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
        return (0);
    }

    // Check if the destination is a wall ('1')
    if (game->map[new_player_y][new_player_x] == '1')
    {
        ft_printf("Hit a wall. Player cannot move.\n");
        return (0);
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



