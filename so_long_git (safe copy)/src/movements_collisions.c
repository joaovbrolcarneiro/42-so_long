/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_collisions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:10:08 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 01:43:40 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Moves the player on the map and updates their position
void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] != '1')
	{
		game->map[game->player_y][game->player_x] = '0';
		game->player_x = new_x;
		game->player_y = new_y;
		game->map[new_y][new_x] = 'P';
	}
}

void	check_for_collisions(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
	{
		game->collectibles--;
		game->map[new_y][new_x] = '0';
	}
	else if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
	{
		ft_printf("You win!\n");
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
}
