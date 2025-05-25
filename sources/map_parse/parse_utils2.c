/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:24:56 by iverniho          #+#    #+#             */
/*   Updated: 2025/05/25 17:45:24 by ivanverniho      ###   ########.fr       */
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

void	free_map_exit(t_mlx **data, char *msg)
{
	free_map((*data)->map.map);
	exit_error(msg);
}

char	**allocate_instructions_array(int total_lines)
{
	char	**instructions_arr;

	instructions_arr = ft_calloc_if(sizeof(char *) * (size_t)(total_lines + 1), 1);
	if (!instructions_arr)
		exit_error("Error: Cannot allocate memory for instructions buffer");
	return (instructions_arr);
}