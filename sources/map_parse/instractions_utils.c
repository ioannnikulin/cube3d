/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instractions_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:46:37 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/24 15:07:02 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

void	free_assets(t_mlx *data)
{
	free(data->assets.wall_north.img);
	free(data->assets.wall_south.img);
	free(data->assets.wall_west.img);
	free(data->assets.wall_east.img);
}

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

void	free_instructions(char **instructions, int count)
{
	int	i;

	i = 0;
	if (!instructions)
		return ;
	while (i < count && instructions[i] != NULL)
	{
		free(instructions[i]);
		i++;
	}
	while (instructions[i] != NULL)
	{
		free(instructions[i]);
		i++;
	}
	free(instructions);
}

int	process_line(t_mlx *data, char *line, int *elements_found,
		int *map_start_index, int current_line_idx)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed || trimmed[0] == '\0')
		return (free(trimmed), 0);
	if (parse_texture_line(data, trimmed))
		(*elements_found)++;
	else if (parse_color_line(data, trimmed))
		(*elements_found)++;
	else if (is_map_line(trimmed))
		*map_start_index = current_line_idx;
	else
		return (free(trimmed), -1);
	free(trimmed);
	return (0);
}