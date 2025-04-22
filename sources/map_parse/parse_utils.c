/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:44:18 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/04/22 23:40:19 by ivanverniho      ###   ########.fr       */
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

int	is_valid_char(char c, int *player_already_parsed)
{
	if (ft_strchr("01NSEW \n", c))
	{
		if (ft_strchr("NSEW", c) && *player_already_parsed == 0 && c != 0)
			return (*player_already_parsed = 1, 1);
		else if (ft_strchr("NSEW", c) && c != 0)
		{
			if (*player_already_parsed == 1)
				return (printf("Error\nInvalid number of players\n"), 0);
		}
		return (1);
	}
	printf("Error\nInvalid character: %c\n", c);
	return (0);
}

int	count_map_lines(char *map)
{
	int file;
	int lines;
	char *temp;

	lines = 0;
	file = open(map, O_RDONLY);
	if (file == -1)
		return (printf("Error\nFailed to open map\n"), 0);
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