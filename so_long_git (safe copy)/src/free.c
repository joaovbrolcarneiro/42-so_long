/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:18:39 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 22:19:30 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_images(t_game *game)
{
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->collectible_img)
		mlx_destroy_image(game->mlx, game->collectible_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
}

void	free_window_and_mlx(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	free_map_from_game(t_game *game)
{
	int	map_height;
	int	i;

	if (!game->map)
		return ;
	map_height = 0;
	while (game->map[map_height] != NULL)
		map_height++;
	i = 0;
	while (i < map_height)
	{
		if (game->map[i])
		{
			free(game->map[i]);
			game->map[i] = NULL;
		}
		i++;
	}
	free(game->map);
	game->map = NULL;
}

void	cleanup_game(t_game *game)
{
	free_images(game);
	free_map_from_game(game);
	free_window_and_mlx(game);
}
