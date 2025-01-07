/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:05:14 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 21:00:11 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* *********************************************************************
 * Starts the game and runs the main game loop.
 *********************************************************************/

int	start_game(char **map)
{
	t_game	game;

	game.player_x = find_player_x(map);
	game.player_y = find_player_y(map);
	ft_printf("Player position initialized");
	game.map = map;
	game.valid_movements = 0;
	if (!init_window(&game, map))
		return (ft_error("Error: Unable to initialize the window"));
	init_hooks(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}

int	are_collectibles_collected(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	handle_esc_key(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
    {
        cleanup_game(game);
        exit(0);
    }
    return (1);
}

int update_player_position(int keycode, t_game *game, int *new_x, int *new_y)
{
    (void)game;  // Mark the 'game' parameter as unused

    // Your logic to update position
    if (keycode == KEY_UP)
        *new_y -= 1;
    else if (keycode == KEY_DOWN)
        *new_y += 1;
    else if (keycode == KEY_LEFT)
        *new_x -= 1;
    else if (keycode == KEY_RIGHT)
        *new_x += 1;

    return (1);  // Return an appropriate value if needed
}

int	is_valid_move(t_game *game, int new_x, int new_y)
{
    if (new_x < 0 || new_x >= (int)ft_strlen(game->map[0]) || 
        new_y < 0 || new_y >= ft_strarr_len(game->map))
        return (0);  // Invalid move

    if (game->map[new_y][new_x] == '1')  // Wall
        return (0);

    return (1);
}

// Function to handle the key press and window close event
int handle_window_close(t_game *game)
{
    ft_printf("Window closed by user.\n");

    // Cleanup the game and exit
    mlx_destroy_window(game->mlx, game->win);
    cleanup_game (game);
    exit(0);  // Exit the program cleanly
    return (0);
}

void init_hooks(t_game *game)
{
    // Hook the key press events to the handle_key_press function
    mlx_key_hook(game->win, handle_key_press, game);

    // Hook for window close event (clicking the 'X' button)
    mlx_hook(game->win, 17, 1L << 17, handle_window_close, game);  // Event 17 is for window close

    // Hook for window resizing
    mlx_hook(game->win, 12, 1L << 15, handle_resize, game);  // Event 12 is for resizing the window (optional)
}

// Function to handle window resizing (optional)
int handle_resize(int width, int height)
{
    ft_printf("Window resized to: %dx%d\n", width, height);
    return (0);
}




