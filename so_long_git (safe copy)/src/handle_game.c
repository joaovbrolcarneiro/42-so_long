/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:27:14 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/08 21:41:44 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_collectible_move(t_game *game, int new_x, int new_y)
{
	(void) game;
	if (game->map[new_y][new_x] == 'C')
	{
		game->map[new_y][new_x] = '0';
	}
	return (1);
}

int	handle_key_press(int keycode, t_game *game)
{
	t_player_pos	pos;

	init_player_positions(&pos, game);
	render_game(game, game->map);
	if (!handle_esc_key(keycode, game))
		return (0);
	if (!update_player_posit(keycode, game, &pos.new_x, &pos.new_y))
		return (0);
	if (!is_valid_move(game, pos.new_x, pos.new_y))
		return (0);
	if (pos.previous_x == pos.new_x && pos.previous_y == pos.new_y)
		return (0);
	if (!check_exit_move(game, keycode, &pos.new_x, &pos.new_y))
		return (0);
	game->valid_movements++;
	ft_printf("Valid movement. Total valid moves: %d\n", game->valid_movements);
	if (!handle_collectible_move(game, pos.new_x, pos.new_y))
		return (0);
	game->player_x = pos.new_x;
	game->player_y = pos.new_y;
	update_map_position(game->map, game->player_x, game->player_y);
	render_game(game, game->map);
	return (0);
}

int	handle_window_close(t_game *game)
{
	ft_printf("Window closed by user.\n");
	cleanup_game(game);
	exit(0);
	return (0);
}

int	handle_resize(int width, int height)
{
	(void)width;
	(void)height;
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
