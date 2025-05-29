/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instractions_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:46:37 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/29 13:12:49 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

void	init_parse_data(t_mlx *data)
{
	data->assets.wall_north.img = NULL;
	data->assets.wall_south.img = NULL;
	data->assets.wall_east.img = NULL;
	data->assets.wall_west.img = NULL;
	data->map.map = NULL;
	data->map.map_height = 0;
	data->map.map_width = 0;
	data->map.floor.color.r = 0;
	data->map.floor.color.g = 0;
	data->map.floor.color.b = 0;
	data->map.ceiling.color.r = 0;
	data->map.ceiling.color.g = 0;
	data->map.ceiling.color.b = 0;
}

int	is_map_line(char *line)
{
	char	*start;
	int		i;

	start = line;
	while (*start == ' ')
		start++;
	if (*start == '\0' || *start == '\n')
		return (0);
	if (!ft_strchr("01", *start))
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01NSEW ", line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	find_elements_and_map_start(t_mlx *data, char **instructions,
		int *elements_found_out, int *map_start_idx_out)
{
	int		i;
	char	*trimmed;

	i = 0;
	*elements_found_out = 0;
	*map_start_idx_out = -1;
	while (instructions[i] != NULL && *map_start_idx_out == -1)
	{
		trimmed = ft_strtrim(instructions[i], " \t\n\v\f\r");
		if (trimmed && trimmed[0] != '\0')
		{
			if (parse_texture_line(data, trimmed, instructions) == 1)
				(*elements_found_out)++;
			else if (parse_color_line(data, trimmed, instructions) == 1)
				(*elements_found_out)++;
			else if (is_map_line(trimmed) == 1)
				*map_start_idx_out = i;
			if (data->errno)
			{
				free(trimmed); // TODO:
				free_2d_array(instructions);
				free_assets(data);
				finalize(data, "Error: Failed to parse instructions", 0);
			}
		}
		free(trimmed);
		i++;
	}
}

void	copy_map_data(t_mlx *data, char **instructions, int map_start_index,
		int map_height)
{
	int		j;
	char	*nl;

	j = 0;
	while (j < map_height)
	{
		data->map.map[j] = ft_strdup(instructions[map_start_index + j]);
		if (!data->map.map[j])
		{
			data->map.map_height = j;
			free_map(data->map.map);
			data->map.map = NULL;
			free_instructions(instructions, map_height);
			free_assets(data);
			exit_error("Error: Failed to duplicate map line during copy");
		}
		nl = ft_strrchr(data->map.map[j], '\n');
		if (nl)
			*nl = '\0';
		j++;
	}
	data->map.map[j] = NULL;
}
