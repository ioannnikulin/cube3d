/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:24:56 by iverniho          #+#    #+#             */
/*   Updated: 2025/05/29 15:40:52 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

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

char	**allocate_instructions_array(t_mlx *data, int total_lines)
{
	char	**instructions_arr;

	instructions_arr = ft_calloc_if(sizeof(char *)
			* (size_t)(total_lines + 1), 1);
	if (!instructions_arr)
		finalize(data, ERR_MALLOC_INSTRUCTIONS, 1);
	return (instructions_arr);
}
