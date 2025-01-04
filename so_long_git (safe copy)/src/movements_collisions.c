/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_collisions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:10:08 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/02 18:35:41 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Moves the player on the map and updates their position
void move_player(t_game *game, int new_x, int new_y)
{
    if (game->map[new_y][new_x] != '1')  // Check if the new position is not a wall
    {
        game->map[game->player_y][game->player_x] = '0';  // Set old position to empty
        game->player_x = new_x;  // Update the player's X position
        game->player_y = new_y;  // Update the player's Y position
        game->map[new_y][new_x] = 'P';  // Place the player in the new position
    }
}

// Checks if the player's new position collides with collectibles or the exit
void check_for_collisions(t_game *game, int new_x, int new_y)
{
    if (game->map[new_y][new_x] == 'C')  // Collectible found
    {
        game->collectibles--;  // Decrease the collectible count
        game->map[new_y][new_x] = '0';  // Remove the collectible from the map
    }
    else if (game->map[new_y][new_x] == 'E')  // Exit found
    {
        if (game->collectibles == 0)  // Check if all collectibles have been collected
        {
            ft_printf("You win!\n");
            mlx_destroy_window(game->mlx, game->win);  // Close the window
            game->win = NULL;
        }
    }
}
