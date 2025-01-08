/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:44:57 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/08 19:58:00 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define MAX_MAP_ROWS 100
# define TILE_SIZE 32
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_map_state
{
	int	collectibles;
	int	ex_fnd;
	int	map_width;
	int	map_height;
	int	collectible_visited;
}	t_map_state;

typedef struct s_game
{
	int			valid_movements;
	int			player_x;
	int			player_y;
	void		*mlx;
	void		*win;
	void		*wall_img;
	void		*player_img;
	void		*collectible_img;
	void		*floor_img;
	void		*exit_img;
	int			collectibles;
	t_map_state	map_state;
	char		**map;
}	t_game;

typedef struct s_validation
{
	char		**map;
	t_game		*game;
	t_map_state	*state;
	char		**visited;
}	t_validation;

/* *********************************************************************
 *                         Function Prototypes
 *********************************************************************/

int		is_wall_behind_exit(t_game *game, int x, int y, int keycode);
char	**check_map(char **map);
void	tr(char **visited, char **map, int map_height);
void	update_player_pos(char **map, int player_x, int player_y);
void	print_updated_map(char **map);
void	free_map_from_game(t_game *game);
void	free_images(t_game *game);
void	free_window_and_mlx(t_game *game);
void	render_tile(t_game *game, char tile, int x, int y);
void	render_map_row(t_game *game, char *row, int y);
int		load_textures(t_game *game, char *path, void **img);
int		init_textures(t_game *game);
int		init_window(t_game *game, char **map);
int		print_error_and_return(char **visited, int map_height);
int		handle_esc_key(int keycode, t_game *game);
int		update_player_posit(int keycode, t_game *game, int *new_x, int *new_y);
int		is_valid_move(t_game *game, int new_x, int new_y);
int		check_exit_move(t_game *game, int keycode, int *new_x, int *new_y);
void	update_adjacent_cell(int keycode, int *new_x, int *new_y, t_game *game);
int		handle_collectible_move(t_game *game, int new_x, int new_y);
int		print_map_error(void);
void	clean_up_visited_on_error(char **visited, int i);
char	**handle_empty_file(char **map, int fd);
int		count_player_and_exit(char **map, int *player_count, int *exit_count);
int		check_row_length(char **map, size_t row_length);
int		check_top_boundary(char **map);
int		check_bottom_boundary(char **map, size_t row_length);
int		check_side_boundaries(char **map, size_t row_length);
int		check_player_and_exit(char **map);
int		vms(char **map);
int		check_map_validity(t_validation *validation);
void	init_st(t_map_state *state, char **map);
int		print_error_and_return(char **visited, int map_height);
int		cnt_rechble(char **map, int x, int y, t_validation *validation);
int		cs_rchbl(char **map, int player_x, int player_y, t_map_state *state);
int		is_valid_character(char **map, int map_width, int map_height);
void	count_valid_move(t_game *game);
int		are_collectibles_collected(char **map);
char	**parse_args_and_load_map(int argc, char **argv);
int		vmsnpp(char **map, int *player_x, int *player_y);
char	**i_vm(int map_width, int map_height);
void	clean_up_visited_map(char **visited, int map_height);
void	update_map_position(char **map, int player_x, int player_y);
int		count_collectibles(char **map, t_map_state *state);
int		ft_strarr_len(char **arr);
void	move_player(t_game *game, int new_x, int new_y);
void	check_for_collisions(t_game *game, int player_x, int player_y);
int		main(int argc, char **argv);
char	**load_map_from_file(const char *filename);
int		validate_map(char **map, int x, int y, t_validation *validation);
int		check_map_validity(t_validation *validation);
int		validate_map_structure(char **map);
int		ft_error(const char *message);
int		is_wall(const char *line);
int		ft_printf(const char *format, ...);
int		start_game(char **map);
int		init_window(t_game *game, char **map);
void	render_game(t_game *game, char **map);
void	cleanup_game(t_game *game);
int		find_player_x(char **map);
int		find_player_y(char **map);
int		handle_key_press(int keycode, t_game *game);
void	init_hooks(t_game *game);
int		handle_window_close(t_game *game);
void	strip_newline(char *line);
int		handle_resize(int width, int height);
int		init_window(t_game *game, char **map);
void	trmnt_prg(char **visited, char **map, int map_height, const char *msg);
void	free_map(char **map, int map_height);

#endif
