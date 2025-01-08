/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_visited.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:16:48 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/08 15:09:37 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_st(t_map_state *state, char **map)
{
	state->collectibles = count_collectibles(map, state);
	state->ex_fnd = 0;
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
			return (clean_up_visited_on_error(visited, i), NULL);
		j = 0;
		while (j < map_width)
			visited[i][j++] = 0;
		i++;
	}
	return (visited);
}

void	clean_up_visited_on_error(char **visited, int i)
{
	while (--i >= 0)
		free(visited[i]);
	free(visited);
	ft_printf("Error: Failed to allocate visited row\n");
}

void	clean_up_visited_map(char **visited, int map_height)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < map_height)
	{
		free(visited[i]);
		visited[i] = NULL;
		i++;
	}
	free(visited);
	visited = NULL;
}
