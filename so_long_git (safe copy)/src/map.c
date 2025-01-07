/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:17:08 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 01:42:04 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**load_map_from_file(const char *filename)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error: Failed to open file %s\n", filename), NULL);
	map = malloc(sizeof(char *) * MAX_MAP_ROWS);
	if (!map)
		return (ft_printf("Error: Map memory allocation \n"), close(fd), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		map[i++] = line;
		line = get_next_line(fd);
	}
	if (i == 0)
		return (handle_empty_file(map, fd));
	map[i] = NULL;
	close(fd);
	return (map);
}

char	**handle_empty_file(char **map, int fd)
{
	ft_printf("Error: File is empty or no valid lines found.\n");
	free(map);
	close(fd);
	return (NULL);
}

int	check_row_length(char **map, size_t row_length)
{
	int	i;

	i = 1;
	while (map[i] != NULL)
	{
		if (ft_strlen(map[i]) != row_length)
		{
			ft_printf("Error!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_top_boundary(char **map)
{
	int	i;

	i = 0;
	while (map[0][i] != '\0')
	{
		if (map[0][i] != '1')
		{
			ft_printf("Error!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_bottom_boundary(char **map, size_t row_length)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (map[i][row_length - 1] != '1')
		{
			ft_printf("Error!\n");
			return (0);
		}
		i++;
	}
	return (1);
}
