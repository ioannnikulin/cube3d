/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/10 18:22:13 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"
#include "inner.h"

static int	check_elements(t_mlx *mlx, char **map)
{
	int	i;
	int	j;
	int	player_already_parsed;

	i = -1;
	player_already_parsed = 0;
	while (++i < mlx->map.map_height)
	{
		j = -1;
		if (map[i][0] == '\n')
			return (printf(ERR_MAP_EMPTY_ROW), 0);
		while (++j < mlx->map.map_width && map[i][j] != '\0')
			if (!is_valid_char(map[i][j], &player_already_parsed))
				return (0);
	}
	if (player_already_parsed == 0)
		return (printf(ERR_NO_PLAYER), 0);
	return (1);
}

static int	calc_map_width(t_mlx **data, char *mp, int lines)
{
	int	i;
	int	file;
	int	width;

	file = open(mp, O_RDONLY);
	i = -1;
	width = 0;
	if (file == -1)
		exit_error(ERR_MAP_OPEN);
	(*data)->map.map = ft_calloc_if(sizeof(char *) * (size_t)(lines + 1), 1);
	if (!(*data)->map.map)
		exit_error(ERR_MALLOC_MAP);
	while (++i < lines)
	{
		(*data)->map.map[i] = get_next_line(file);
		if (!is_row_valid((*data)->map.map[i]))
			free_map_exit(&(*data), ERR_MAP_EMPTY_ROW);
		width = ft_strlen((*data)->map.map[i]);
		if ((*data)->map.map_width < width)
			(*data)->map.map_width = width;
		if (!(*data)->map.map[i])
			free_map_exit(&(*data), ERR_MALLOC_MAP);
	}
	close(file);
	return (free_map((*data)->map.map), width);
}

static void	init_map(t_mlx **data, char *mp, int lines)
{
	int	i;
	int	file;

	i = 0;
	file = open(mp, O_RDONLY);
	if (file == -1)
		exit_error(ERR_MAP_OPEN);
	(*data)->map.map = ft_calloc_if(sizeof(char *) * (size_t)(lines + 1), 1);
	if (!(*data)->map.map)
		exit_error(ERR_MALLOC_MAP);
	(*data)->map.map[0] = get_next_line(file);
	if (!(*data)->map.map[0])
		free_map_exit(&(*data), ERR_MALLOC_MAP);
	while (++i < lines)
	{
		(*data)->map.map[i] = get_next_line(file);
		if (!(*data)->map.map[i])
			free_map_exit(&(*data), ERR_MALLOC_MAP);
	}
	close(file);
}

static int	fill_map(t_mlx *data, char *mp)
{
	int	lines;
	int	is_valid;

	lines = (count_map_lines(mp));
	data->map.map_height = lines;
	data->map.map_width = 0;
	calc_map_width(&data, mp, lines);
	init_map(&data, mp, lines);
	data->map.map_width = longest_line(data->map.map);
	is_valid = is_map_valid(data->map.map_width, check_elements
			(data, data->map.map));
	if (!is_valid)
		return (free_map(data->map.map), 0);
	is_valid = is_surrounded_by_walls(data);
	if (!is_valid)
		return (free_map(data->map.map), 0);
	return (1);
}

int	validate_map(t_mlx *data, char *map)
{
	if (!check_extension(map))
		return (printf(ERR_MAP_EXT), 0);
	if (!fill_map(data, map))
		return (0);
	printf("map is valid\n");
	return (1);
}
