/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:24:56 by iverniho          #+#    #+#             */
/*   Updated: 2025/04/26 15:34:48 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	is_map_row_valid(char *row)
{
	int	len;

	if (!row)
		return (printf("Error\nEmpty row\n"), 0);
	len = (int)ft_strlen(row);
	if (!len)
		return (printf("Error\nEmpty row\n"), 0);
	return (1);
}

void	free_map(char **map)
{
	int	i;

	i = -1;
	if (map)
	{
		while (map[++i])
			free(map[i]);
		free(map);
	}
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
