/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:57:56 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 22:18:00 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* *********************************************************************
 * Initializes the window for the game.
 *********************************************************************/

int	init_mlx_and_window(t_game *game, char **map)
{
	int	map_width;
	int	map_height;

	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error_and_return(NULL, 0));
	map_width = ft_strlen(map[0]) * TILE_SIZE;
	map_height = ft_strarr_len(map) * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, map_width, map_height, "So Long");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		return (print_error_and_return(NULL, 0));
	}
	return (1);
}

int	load_textures(t_game *game, char *path, void **img)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!(*img))
		return (print_error_and_return(NULL, 0));
	return (1);
}

int	init_textures(t_game *game)
{
	if (!load_textures(game, "textures/wall.xpm",
			(void **)&game->wall_img))
		return (0);
	if (!load_textures(game, "textures/player.xpm",
			(void **)&game->player_img))
		return (0);
	if (!load_textures(game, "textures/collectible.xpm",
			(void **)&game->collectible_img))
		return (0);
	if (!load_textures(game, "textures/floor.xpm",
			(void **)&game->floor_img))
		return (0);
	if (!load_textures(game, "textures/exit.xpm",
			(void **)&game->exit_img))
		return (0);
	return (1);
}

int	init_window(t_game *game, char **map)
{
	if (!init_mlx_and_window(game, map))
		return (0);
	if (!init_textures(game))
		return (0);
	return (1);
}
