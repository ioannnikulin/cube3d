/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:33:17 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/29 15:44:21 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static int	iterate_and_validate_row_chars(t_mlx *mlx, char *row,
											int *player_already_parsed)
{
	int	j;

	j = -1;
	while (++j < mlx->map.map_width && row[j] != '\0')
	{
		if (row[j] == '\0')
			break ;
		if (!is_valid_char(mlx, row[j], player_already_parsed))
			return (0);
	}
	return (1);
}

int	validate_map_input(t_mlx *mlx, char **map)
{
	if (!map || mlx->map.map_height <= 0)
		return (finalize(mlx, ERR_MAP_EMPTY_ROW, 0));
	return (1);
}

int	validate_row_properties(t_mlx *mlx, char *row)
{
	if (!row)
		return (finalize(mlx, ERR_MAP_EMPTY_ROW, 0));
	if (row[0] == '\n')
		finalize(mlx, ERR_MAP_EMPTY_ROW, 0);
	if (mlx->map.map_width <= 0)
		return (finalize(mlx, EER_MAP_INVALID, 0));
	return (1);
}

int	check_elements(t_mlx *mlx, char **map)
{
	int	i;
	int	player_already_parsed;

	i = -1;
	player_already_parsed = 0;
	if (!validate_map_input(mlx, map))
		return (0);
	while (++i < mlx->map.map_height)
	{
		if (!validate_row_properties(mlx, map[i]))
			return (0);
		if (!iterate_and_validate_row_chars(mlx, map[i],
				&player_already_parsed))
			return (0);
	}
	if (player_already_parsed == 0)
		return (finalize(mlx, ERR_NO_PLAYER, 0));
	return (1);
}

int	open_map_file_and_get_fd(t_mlx *data, char *file, int *total_lines_out)
{
	int	fd;
	int	loc_total_lines;

	loc_total_lines = count_map_lines(file);
	if (loc_total_lines <= 6)
		finalize(data, EER_MAP_INVALID, 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		finalize(data, ERR_MAP_OPEN, 0);
	*total_lines_out = loc_total_lines;
	return (fd);
}
