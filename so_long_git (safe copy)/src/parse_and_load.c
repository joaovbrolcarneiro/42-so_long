/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_load.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrol-ca <jbrol-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:17:26 by jbrol-ca          #+#    #+#             */
/*   Updated: 2025/01/07 00:01:49 by jbrol-ca         ###   ########.fr       */
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