/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:44:18 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/30 15:40:08 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

int	is_map_valid(int map_width, int valid_elements)
{
	if (map_width == 0 || valid_elements == 0)
		return (0);
	return (1);
}

int	count_map_lines(char *map)
{
	char	*temp;
	int		file;
	int		lines;

	lines = 0;
	file = open(map, O_RDONLY);
	if (file == -1)
		return (0);
	temp = get_next_line(file);
	while (temp)
	{
		lines++;
		free(temp);
		temp = get_next_line(file);
	}
	if (temp)
		free(temp);
	close(file);
	return (lines);
}

int	is_valid_char(t_mlx *data, char c, int *player_already_parsed)
{
	if (ft_strchr("01NSEW \n", c))
	{
		if (ft_strchr("NSEW", c) && *player_already_parsed == 0 && c != 0)
			return (*player_already_parsed = 1, 1);
		else if (ft_strchr("NSEW", c) && c != 0)
		{
			if (*player_already_parsed == 1)
				finalize(data, ERR_PLAYERS_NUMBER, 0);
		}
		return (1);
	}
	finalize(data, ERR_INVALID_CHAR, 0);
	return (0);
}
