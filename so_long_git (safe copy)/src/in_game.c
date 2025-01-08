/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:21:01 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/08 20:56:52 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_exit_move(t_game *game, int keycode, int *new_x, int *new_y)
{
	if (game->map[*new_y][*new_x] == 'E')
	{
		if (are_collectibles_collected(game->map))
		{
			game->valid_movements++;
			ft_printf("Win! Total valid moves: %d\n", game->valid_movements);
			cleanup_game(game);
			exit(0);
		}
		else if (is_wall_behind_exit(game, *new_x, *new_y, keycode))
		{
			return (0);
		}
		update_adjacent_cell(keycode, new_x, new_y, game);
	}
	return (1);
}

int	is_wall_behind_exit(t_game *game, int x, int y, int keycode)
{
	int	behind_x;
	int	behind_y;

	behind_x = x;
	behind_y = y;
	if (keycode == KEY_UP)
		behind_y -= 1;
	else if (keycode == KEY_DOWN)
		behind_y += 1;
	else if (keycode == KEY_LEFT)
		behind_x -= 1;
	else if (keycode == KEY_RIGHT)
		behind_x += 1;
	if (game->map[behind_y][behind_x] == '1')
		return (1);
	return (0);
}

void	update_adjacent_cell(int keycode, int *new_x, int *new_y, t_game *game)
{
	int	next_x;
	int	next_y;

	next_x = *new_x;
	next_y = *new_y;
	if (keycode == KEY_UP)
		next_y -= 1;
	else if (keycode == KEY_DOWN)
		next_y += 1;
	else if (keycode == KEY_LEFT)
		next_x -= 1;
	else if (keycode == KEY_RIGHT)
		next_x += 1;
	if (is_valid_move(game, next_x, next_y))
	{
		*new_x = next_x;
		*new_y = next_y;
	}
}

void	count_valid_move(t_game *game)
{
	game->valid_movements++;
	ft_printf("Valid movement. Total valid moves: %d\n", game->valid_movements);
}
