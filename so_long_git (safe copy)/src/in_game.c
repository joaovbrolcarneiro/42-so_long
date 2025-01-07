#include "so_long.h"

int	check_exit_move(t_game *game, int keycode, int *new_x, int *new_y)
{
    if (game->map[*new_y][*new_x] == 'E')
    {
        if (are_collectibles_collected(game->map))
        {
            cleanup_game(game);
            exit(0);  // Exit the game
        }
        update_adjacent_cell(keycode, new_x, new_y, game);
    }
    return (1);
}

void	update_adjacent_cell(int keycode, int *new_x, int *new_y, t_game *game)
{
    int next_x = *new_x;
    int next_y = *new_y;

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

int	handle_collectible_move(t_game *game, int new_x, int new_y)
{
    if (game->map[new_y][new_x] == 'C')
    {
        game->map[new_y][new_x] = '0';
        count_valid_move(game);  // Increment valid movements counter
    }
    return (1);
}

int	handle_key_press(int keycode, t_game *game)
{
    int new_player_x = game->player_x;
    int new_player_y = game->player_y;

    if (!handle_esc_key(keycode, game))
        return (0);

    if (!update_player_position(keycode, game, &new_player_x, &new_player_y))
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


// Function to increment valid movements counter
void count_valid_move(t_game *game)
{
    game->valid_movements++;
    ft_printf("Valid movement. Total valid moves: %d\n", game->valid_movements);
}
