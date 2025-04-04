/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:44:18 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/04/04 20:41:54 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	print_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		printf("%s", map[i]);
}

int	is_valid_char(char c)
{
	if (ft_strchr("01NSEW \n", c))
		return (1);
	return (0);
}

int	count_map_lines(char *map)
{
	int file;
	int lines;
	char *temp;

	lines = 0;
	file = open(map, O_RDONLY);
	temp = get_next_line(file);
	while (temp)
	{
		lines++;
		free(temp);
		temp = get_next_line(file);
	}
	close(file);
	return (lines);
}