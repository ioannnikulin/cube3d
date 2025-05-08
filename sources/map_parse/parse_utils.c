/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:44:18 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/08 17:12:51 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	exit_error(char *message)
{
	printf("Error: %s\n", message);
	exit(EXIT_FAILURE);
}

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
				return (printf(ERR_PLAYERS_NUMBER), 0);
		}
		return (1);
	}
	printf("%s %c \n", ERR_INVALID_CHAR, c);
	return (0);
}

int	count_map_lines(char *map)
{
	char	*temp;
	int		file;
	int		lines;

	lines = 0;
	file = open(map, O_RDONLY);
	if (file == -1)
		return (printf(ERR_MAP_OPEN), 0);
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

void	free_exit(t_mlx *data)
{
	if (data->map.map)
		free_map(data->map.map);
	exit(EXIT_FAILURE);
}
