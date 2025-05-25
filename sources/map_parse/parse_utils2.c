/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:24:56 by iverniho          #+#    #+#             */
/*   Updated: 2025/05/25 16:36:44 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

void	free_map_exit(t_mlx **data, char *msg)
{
	free_map((*data)->map.map);
	exit_error(msg);
}

int	is_row_valid(char *row)
{
	int	row_length;

	if (row == NULL)
		return (0);
	row_length = ft_strlen(row);
	if (row_length < 3)
		return (0);
	return (1);
}

int	check_extension(char *map)
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

int	is_map_row_valid(char *row)
{
	int	len;

	if (!row)
		return (printf(ERR_MAP_EMPTY_ROW), 0);
	len = (int)ft_strlen(row);
	if (!len)
		return (printf(ERR_MAP_EMPTY_ROW), 0);
	return (1);
}

int	longest_line(char **map)
{
	int	i;
	int	max;

	i = -1;
	max = 0;
	while (map[++i])
	{
		if (!is_map_row_valid(map[i]))
			return (0);
		if ((int)ft_strlen(map[i]) > max)
			max = (int)ft_strlen(map[i]);
	}
	return (max);
}
