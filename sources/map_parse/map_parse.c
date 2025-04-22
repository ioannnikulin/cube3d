/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/04/23 00:34:30 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	check_elements(t_mlx *mlx, char **map)
{
	int	i;
	int	j;
	int	player_already_parsed;

	i = -1;
	player_already_parsed = 0;
	while (++i < mlx->map->map_height)
	{
		j = -1;
		while (++j < mlx->map->map_width)
			if (!is_valid_char(map[i][j], &player_already_parsed))
				return (0);
	}
	if (player_already_parsed == 0)
		return (printf("Error\nNo player found\n"), 0);
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
		if ((int)ft_strlen(map[i]) > max)
			max = (int)ft_strlen(map[i]);
	}
	return (max);
}

void	exit_error(char *message)
{
	printf("Error: %s\n", message);
	exit(EXIT_FAILURE);
}

void	fill_map(t_mlx *data, char *mp)
{
	int	file;
	int	lines;
	int	i;

	lines = (i = 0, file = open(mp, O_RDONLY), count_map_lines(mp));
	if (file == -1)
		exit_error("Error: Cannot open map file");
	data->map = ft_calloc_if(sizeof(t_map), 1);
	if (!data->map)
		exit_error("Error: Cannot allocate memory for map");
	data->map->map = ft_calloc_if(sizeof(char *) * (size_t)(lines + 1), 1);
	if (!data->map->map)
		exit_error("Error: Cannot allocate memory for map");
	data->map->map[0] = get_next_line(file);
	while (++i < lines)
		data->map->map[i] = get_next_line(file);
	close(file);
	data->map->map_height = lines;
	data->map->map_width = longest_line(data->map->map);
	if (!check_elements(data, data->map->map))
		exit(EXIT_FAILURE);
	if (!is_surrounded_by_walls(data))
		exit(EXIT_FAILURE);
}

static int	check_extension(char *map)
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
	if (!check_extension(map))
		return (printf("Error\nInvalid map extension\n"), 0);
	fill_map(data, map);
	printf("map is valid\n");
	return (1);
}