/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:27:14 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/08 18:17:45 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_collectible_move(t_game *game, int new_x, int new_y)
{
	(void) game;
	if (game->map[new_y][new_x] == 'C')
	{
		game->map[new_y][new_x] = '0';
		//count_valid_move(game);
	}
	return (1);
}

int	handle_key_press(int keycode, t_game *game)
{
	int	new_player_x;
	int	new_player_y;
	int	previous_x;
	int	previous_y;

	// Store the current player position
	previous_x = game->player_x;
	previous_y = game->player_y;
	new_player_x = game->player_x;
	new_player_y = game->player_y;

	// Render the game immediately, even before checking the move validity
	render_game(game, game->map);

	// Check for exit key press (Esc)
	if (!handle_esc_key(keycode, game))
		return (0);

	// Update the player position based on key press
	if (!update_player_posit(keycode, game, &new_player_x, &new_player_y))
		return (0);

	// Only proceed if the move is valid (not into a wall or out of bounds)
	if (!is_valid_move(game, new_player_x, new_player_y))
		return (0);

	// Ensure that the player is not in the same position (i.e., no actual movement)
	if (previous_x == new_player_x && previous_y == new_player_y)
		return (0); // No movement, so do not count as valid move

	// Check for exit condition (whether the player reaches the exit and has collected all items)
	if (!check_exit_move(game, keycode, &new_player_x, &new_player_y))
		return (0);

	// Count valid movement (if the player actually moved to a valid location)
	game->valid_movements++;  // Increment valid movement count
	ft_printf("Valid movement. Total valid moves: %d\n", game->valid_movements);  // Print total valid moves

	// Handle collectible move (if applicable)
	if (!handle_collectible_move(game, new_player_x, new_player_y))
		return (0);

	// Update player's position after a valid move
	game->player_x = new_player_x;
	game->player_y = new_player_y;

	// Update the map with the new player position
	update_map_position(game->map, game->player_x, game->player_y);
	render_game(game, game->map);

	return (0);  // End of function
}

int	handle_window_close(t_game *game)
{
	ft_printf("Window closed by user.\n");
	mlx_destroy_window(game->mlx, game->win);
	cleanup_game(game);
	exit(0);
	return (0);
}

int	handle_resize(int width, int height)
{
	ft_printf("Window resized to: %dx%d\n", width, height);
	return (0);
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
