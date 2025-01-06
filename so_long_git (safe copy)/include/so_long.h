#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../GetNextLine/get_next_line.h"
# include "../mlx/mlx.h"

/* *********************************************************************
 *                         Structures
 *********************************************************************/

#define MAX_MAP_ROWS 100
#define TILE_SIZE 32
#define KEY_ESC 65307
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

typedef struct s_map_state {
    int collectibles;
    int exit_found;
    int map_width;
    int map_height;
    int collectible_visited;
} t_map_state;

typedef struct s_game
{
    int     valid_movements;
    int     player_x;
    int     player_y;
    void    *mlx;
    void    *win;
    void    *wall_img;
    void    *player_img;
    void    *collectible_img;
    void    *floor_img;
    void    *exit_img;  // Add texture for the exit
    int     collectibles;
    t_map_state map_state; // Include map state struct for dimensions
    char    **map; // Add map member
}   t_game;

/* *********************************************************************
 *                         Function Prototypes
 *********************************************************************/

int check_map_validity(char **map, int player_x, int player_y,
                        t_map_state *state, char **visited);
void	init_st(t_map_state *state, int map_width, int map_height, char **map);
int print_error_and_return(char **visited, int map_height);
int count_reachable_collectibles(char **map, int x, int y, t_map_state *state, char **visited);
int are_all_collectibles_reachable(char **map, int player_x, int player_y, t_map_state *state);
int is_valid_character(char **map, int map_width, int map_height);
void count_valid_move(t_game *game);
int are_collectibles_collected(char **map);
char    **parse_arguments_and_load_map(int argc, char **argv);
int	validate_map_struct_and_plyr_pos(char **map, int *player_x, int *player_y);
char    **initialize_visited_map(int map_width, int map_height);
void    clean_up_visited_map(char **visited, int map_height);
void update_map_position(char **map, int player_x, int player_y);
int is_valid_move(t_game *game, int new_x, int new_y);
void restore_map(char **map);
int count_collectibles(char **map, t_map_state *state);
void    strip_newline(char *line);
int 	ft_strarr_len(char **arr);
void    move_player(t_game *game, int new_x, int new_y);
void    check_for_collisions(t_game *game, int player_x, int player_y);
int     main(int argc, char **argv);
char    **load_map_from_file(const char *filename);
int     validate_map(char **map, int x, int y, t_map_state *state, char **visited);
int     validate_map_structure(char **map);
int     ft_error(const char *message);
int     is_wall(const char *line);
int     ft_printf(const char *format, ...);
int     start_game(char **map);   // Game-related function prototypes
int     init_window(t_game *game, char **map);
int     game_is_running(t_game *game);
void    handle_input(t_game *game);
void    render_game(t_game *game, char **map);
void    cleanup_game(t_game *game);
int     find_player_x(char **map);
int     find_player_y(char **map);
char    **append_line_to_map(char **map, char *line);
int		handle_key_press(int key, t_game *game);
void init_hooks(t_game *game);
void get_map_dimensions(char **map, int *width, int *height);
// Function to handle the window close event (clicking the 'X' button)
int handle_window_close(t_game *game);

// Function to handle the window resize event (optional, if you want to track window resizing)
int handle_resize(int width, int height);
// Function to initialize the window and maximize it to the screen size (if you want)
int init_window(t_game *game, char **map);

#endif /* SO_LONG_H */

