/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:05:14 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/08 15:57:36 by jbrol-ca         ###   ########.fr       */
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

int	update_player_posit(int keycode, t_game *game, int *new_x, int *new_y)
{
	(void)game;
	if (keycode == KEY_UP)
		*new_y -= 1;
	else if (keycode == KEY_DOWN)
		*new_y += 1;
	else if (keycode == KEY_LEFT)
		*new_x -= 1;
	else if (keycode == KEY_RIGHT)
		*new_x += 1;
	return (1);
}

int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= (int)ft_strlen(game->map[0]))
	{
		return (0);
	}
	if (new_y < 0 || new_y >= ft_strarr_len(game->map))
	{
		return (0);
	}
	if (game->map[new_y][new_x] == '1')
	{
		return (0);
	}
	return (1);
}

void	init_hooks(t_game *game)
{
	mlx_key_hook(game->win, handle_key_press, game);
	mlx_hook(game->win, 17, 1L << 17, handle_window_close, game);
	mlx_hook(game->win, 12, 1L << 15, handle_resize, game);
}
