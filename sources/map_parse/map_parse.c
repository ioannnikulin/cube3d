/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/29 16:16:53 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static int	check_extension(char *map)
{
	int	i;

	i = -1;
	if (ft_strchr(map, '.') == 0)
		return (0);
	while (map[++i])
	{
		if (map[i] == '.')
		{
			if (!(map[i + 1] == 'c' && map[i + 2] == 'u' && map[i + 3] == 'b'
					&& !(map[i + 4])))
				return (0);
			else
				return (1);
		}
	}
	return (0);
}

int	validate_map(t_mlx *data, char *map_file)
{
	if (!check_extension(map_file))
		finalize(data, ERR_MAP_EXT, 1);
	parse_instructions(data, map_file);
	return (1);
}
