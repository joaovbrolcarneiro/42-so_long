/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:17:26 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 20:16:00 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**parse_arguments_and_load_map(int argc, char **argv)
{
	char	**map;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long <map_file>\n");
		return (NULL);
	}
	map = load_map_from_file(argv[1]);
	if (!map)
	{
		ft_printf("Error: Failed to load map.\n");
		return (NULL);
	}
	return (map);
}

void	strip_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	check_player_and_exit(char **map)
{
	int	player_count;
	int	exit_count;

	player_count = 0;
	exit_count = 0;
	ft_printf("Debug: Checking player and exit...\n");
	count_player_and_exit(map, &player_count, &exit_count);
	if (player_count != 1)
	{
		ft_printf("Error: Invalid player count: %d\n", player_count);
		return (0);
	}
	if (exit_count != 1)
	{
		ft_printf("Error: Invalid exit count: %d\n", exit_count);
		return (0);
	}
	ft_printf("Debug: Player and exit validation passed\n");
	return (1);
}
