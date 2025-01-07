/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_visited.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:16:48 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 01:37:08 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_st(t_map_state *state, char **map)
{
	state->collectibles = count_collectibles(map, state);
	state->exit_found = 0;
}

char	**i_vm(int map_width, int map_height)
{
	char	**visited;
	int		i;
	int		j;

	visited = (char **)malloc(sizeof(char *) * map_height);
	if (!visited)
		return (ft_printf("Error: Failed to allocate visited map\n"), NULL);
	i = 0;
	while (i < map_height)
	{
		visited[i] = (char *)malloc(sizeof(char) * map_width);
		if (!visited[i])
			return (free(visited), ft_printf("Error!\n"), NULL);
		j = 0;
		while (j < map_width)
			visited[i][j++] = 0;
		i++;
	}
	return (visited);
}

void	clean_up_visited_map(char **visited, int map_height)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < map_height)
	{
		if (visited[i])
		{
			free(visited[i]);
			visited[i] = NULL;
		}
		i++;
	}
	free(visited);
	visited = NULL;
}
