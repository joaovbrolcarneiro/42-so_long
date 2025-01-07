/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:57:56 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 22:07:05 by jbrol-ca         ###   ########.fr       */
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
		return;
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

void update_map_position(char **map, int player_x, int player_y)
{
    for (int y = 0; y < ft_strarr_len(map); y++) {
        for (size_t x = 0; x < ft_strlen(map[y]); x++) {
            if (map[y][x] == 'P')
                map[y][x] = '0';  // Replace previous player position with empty floor

            if ((size_t)x == (size_t)player_x && (size_t)y == (size_t)player_y)  // Cast player_x and player_y to size_t
                map[y][x] = 'P';  // Place player at new position
        }
    }
    // Debugging: Print the updated map
    for (int y = 0; y < ft_strarr_len(map); y++) {
        ft_printf("Row %d: %s\n", y, map[y]);
    }
}




