/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:22:45 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/08 16:02:30 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_error_and_return(char **visited, int map_height)
{
	ft_printf("Error!\n");
	if (visited)
		clean_up_visited_map(visited, map_height);
	exit(1);
}

void	free_map(char **map, int map_height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < map_height)
	{
		if (map[i])
		{
			free(map[i]);
			map[i] = NULL;
		}
		i++;
	}
	free(map);
	map = NULL;
}

void	tr(char **visited, char **map, int map_height)
{
	trmnt_prg(visited, map, map_height, "Error!");
}

void	trmnt_prg(char **visited, char **map, int map_height,
		const char *msg)
{
	if (msg)
		ft_printf("%s\n", msg);
	if (visited)
		clean_up_visited_map(visited, map_height);
	if (map)
		free_map(map, map_height);
	exit(1);
}
