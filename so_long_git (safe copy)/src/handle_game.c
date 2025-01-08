/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:27:14 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/08 15:57:40 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_collectible_move(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->map[new_y][new_x] = '0';
		count_valid_move(game);
	}
	return (1);
}

int	handle_key_press(int keycode, t_game *game)
{
	int	new_player_x;
	int	new_player_y;

	new_player_x = game->player_x;
	new_player_y = game->player_y;
	if (!handle_esc_key(keycode, game))
		return (0);
	if (!update_player_posit(keycode, game, &new_player_x, &new_player_y))
		return (0);
	if (!is_valid_move(game, new_player_x, new_player_y))
		return (0);
	if (!check_exit_move(game, keycode, &new_player_x, &new_player_y))
		return (0);
	if (!handle_collectible_move(game, new_player_x, new_player_y))
		return (0);
	game->player_x = new_player_x;
	game->player_y = new_player_y;
	update_map_position(game->map, game->player_x, game->player_y);
	render_game(game, game->map);
	return (0);
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
