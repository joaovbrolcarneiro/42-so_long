/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:48:23 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/03 19:36:23 by jbrol-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
char	**load_map_from_file(const char *filename)
{
	char	**map;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = NULL;
	while ((line = get_next_line(fd)))
	{
		strip_newline(line); // Call strip_newline here
		map = append_line_to_map(map, line);
		free(line);
	}
	close(fd);
	return (map);
}
*/
char **load_map_from_file(const char *filename)
{
    char **map;
    char *line;
    int fd;
    int i;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        ft_printf("Error: Failed to open file %s\n", filename);
        return (NULL);
    }

    // Allocate memory for the map
    map = malloc(sizeof(char *) * MAX_MAP_ROWS); // Adjust MAX_MAP_ROWS as needed
    if (!map)
    {
        ft_printf("Error: Memory allocation failed for map.\n");
        close(fd);
        return (NULL);
    }

    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        ft_printf("Read line %d: %s\n", i, line);
        strip_newline(line);  // Strip the newline character after reading
        map[i++] = line;      // Add the line to the map
    }

    map[i] = NULL;  // Null-terminate the map

    if (i == 0)
    {
        ft_printf("Error: File is empty or no valid lines found.\n");
        free(map);
        close(fd);
        return (NULL);
    }

    close(fd);
    return (map);
}


/*
int	validate_map_structure(char **map)
{
	int	i;
	int	len;

	len = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != len)
			return (0);
		if (map[i][0] != '1' || map[i][len - 1] != '1')
			return (0);
		i++;
	}
	if (!is_wall(map[0]) || !is_wall(map[i - 1]))
		return (0);
	return (1);
}
*/

int validate_map_structure(char **map)
{
    int i, j;
    size_t row_length = ft_strlen(map[0]);

    // Check if all rows are the same length
    for (i = 1; map[i] != NULL; i++)
    {
        if (ft_strlen(map[i]) != row_length)
        {
            ft_printf("Error: Inconsistent row lengths.\n");
            return 0;
        }
    }

    // Check for boundary walls
    for (i = 0; map[0][i] != '\0'; i++)  // Top row
    {
        if (map[0][i] != '1')
        {
            ft_printf("Error: Top boundary is not properly walled.\n");
            return 0;
        }
    }

    for (i = 0; map[i] != NULL; i++)  // Bottom row
    {
        if (map[i][row_length - 1] != '1')
        {
            ft_printf("Error: Bottom boundary is not properly walled.\n");
            return 0;
        }
    }

    for (i = 0; map[i] != NULL; i++)  // Check first and last column of each row
    {
        if (map[i][0] != '1' || map[i][row_length - 1] != '1')
        {
            ft_printf("Error: Side boundaries are not properly walled.\n");
            return 0;
        }
    }

    // Check for exactly one player and one exit
    int player_count = 0, exit_count = 0;
    for (i = 0; map[i] != NULL; i++)
    {
        for (j = 0; map[i][j] != '\0'; j++)
        {
            if (map[i][j] == 'P')
                player_count++;
            if (map[i][j] == 'E')
                exit_count++;
        }
    }

    if (player_count != 1 || exit_count != 1)
    {
        ft_printf("Error: There should be exactly one player (P) and one exit (E).\n");
        return 0;
    }

    return 1;  // Map structure is valid
}

char	**append_line_to_map(char **map, char *line)
{
	char	**new_map;
	int		i;

	if (!line)
		return (map);
	i = 0;
	while (map && map[i])
		i++;
	new_map = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map && map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(map);
	return (new_map);
}

void	strip_newline(char *line)
{
	int	len;

	if (!line)
		return;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

