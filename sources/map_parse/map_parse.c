/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/04/04 20:42:12 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	check_elements(t_mlx *mlx, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (++i < mlx->map->map_height)
	{
		j = -1;
		while (++j < mlx->map->map_width)
			if (!is_valid_char(map[i][j]))
				return (0);
	}
	return (1);
}

void	fill_map(t_mlx *data, char *mp)
{
	int	file;
	int	i;
	int	lines;

	lines = count_map_lines(mp);
	i = 0;
	file = open(mp, O_RDONLY);
	data->map = malloc(sizeof(char *) * (size_t)(lines + 1));
	data->map->map = malloc(sizeof(char *) * (size_t)(lines + 1));
	data->map->map[0] = get_next_line(file);
	if (!data->map->map[0])
	{
		printf("Error\nFailed to read map\n");
		exit(EXIT_FAILURE);
	}
	data->map->map_width = ft_strlen(data->map->map[0]);
	data->map->map_height = lines;
	while (i++ < data->map->map_height)
		data->map->map[i] = get_next_line(file);
	if (!is_surrounded_by_walls(data))
		exit(EXIT_FAILURE);
	if (!check_elements(data, data->map->map))
		exit(EXIT_FAILURE);
	close(file);
}

static int	check_extention(char *map)
{
	int	i;

	i = -1;
	if (ft_strchr(map, '.') == 0)
		return (printf("Error\nInvalid map extension\n"), 0);
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

int	validate_map(t_mlx *data, char *map)
{
	if (!check_extention(map))
		return (printf("Error\nInvalid map extension\n"), 0);
	fill_map(data, map);
	printf("map is valid\n");
	return (1);
}