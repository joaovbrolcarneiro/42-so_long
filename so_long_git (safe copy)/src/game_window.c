/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:57:56 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 21:41:59 by jbrol-ca         ###   ########.fr       */
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
	if (!load_textures(game, "textures/wall.xpm", (void **)&game->wall_img) ||
		!load_textures(game, "textures/player.xpm", (void **)&game->player_img) ||
		!load_textures(game, "textures/collectible.xpm", (void **)&game->collectible_img) ||
		!load_textures(game, "textures/floor.xpm", (void **)&game->floor_img) ||
		!load_textures(game, "textures/exit.xpm", (void **)&game->exit_img))
		return (0);
	return (1);
}

int	init_window(t_game *game, char **map)
{
	if (!init_mlx_and_window(game, map) || !init_textures(game))
		return (0);
	return (1);
}


/* *********************************************************************
 * Renders the game (map and objects like player, collectibles, etc.)
 *********************************************************************/

void render_game(t_game *game, char **map)
{
    int x, y;

    y = 0;
    while (y < ft_strarr_len(map))
    {
        x = 0;
        while (x < (int)ft_strlen(map[y]))
        {

            // Render floor tiles (0)
            if (map[y][x] == '0')
                mlx_put_image_to_window(game->mlx, game->win, game->floor_img, x * TILE_SIZE, y * TILE_SIZE);
         
            // Render walls (1)
            if (map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall_img, x * TILE_SIZE, y * TILE_SIZE);

            // Render player (P)
            if (map[y][x] == 'P')
            {
                ft_printf("Rendering player at: (%d, %d)\n", x, y);  // Debug print
                mlx_put_image_to_window(game->mlx, game->win, game->player_img, x * TILE_SIZE, y * TILE_SIZE);
            }

            // Render collectibles (C)
            if (map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->collectible_img, x * TILE_SIZE, y * TILE_SIZE);

            // Render exit (E)
            if (map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->exit_img, x * TILE_SIZE, y * TILE_SIZE);

            x++;
        }
        y++;
    }
}



/* *********************************************************************
 * Cleans up the game window and MLX resources.
 *********************************************************************/

void cleanup_game(t_game *game)
{
    // Free images (textures) if they exist
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

    // Free the window
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);

    // Free the map array
    if (game->map)
    {
        for (int i = 0; game->map[i] != NULL; i++)
            free(game->map[i]);
        free(game->map);
        game->map = NULL;
    }

    // Clean up MinilibX
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx); // Destroy display connection
        free(game->mlx);               // Free MinilibX context
        game->mlx = NULL;
    }
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




