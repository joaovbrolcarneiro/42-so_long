/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:18:53 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 22:18:54 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_tile(t_game *game, char tile, int x, int y)
{
	if (tile == '0')
		mlx_put_image_to_window(game->mlx, game->win,
			game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->wall_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'P')
	{
		ft_printf("Rendering player at: (%d, %d)\n", x, y);
		mlx_put_image_to_window(game->mlx, game->win,
			game->player_img, x * TILE_SIZE, y * TILE_SIZE);
	}
	else if (tile == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->collectible_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->exit_img, x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map_row(t_game *game, char *row, int y)
{
	int	x;

	x = 0;
	while (x < (int)ft_strlen(row))
	{
		render_tile(game, row[x], x, y);
		x++;
	}
}

void	render_game(t_game *game, char **map)
{
	int	y;

	y = 0;
	while (y < ft_strarr_len(map))
	{
		render_map_row(game, map[y], y);
		y++;
	}
}
