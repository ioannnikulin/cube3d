/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:14:38 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/29 15:41:40 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static char	*trim_and_get_identifier(t_mlx *data, char *line, char *out_id)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed)
		return (NULL);
	if (trimmed[0] == '\0')
		return (free(trimmed), NULL);
	*out_id = trimmed[0];
	if (!((*out_id == 'F' || *out_id == 'C') && trimmed[1] == ' '))
		return (free(trimmed), NULL);
	if (trimmed[2] == '\0')
	{
		free(trimmed);
		finalize(data, ERR_INVALID_RGB, 1);
	}
	return (trimmed);
}

static char	**split_rgb_values(const char *rgb_data_str)
{
	char	**rgb_parts;

	rgb_parts = ft_split(rgb_data_str, ',', 0);
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2]
		|| rgb_parts[3])
	{
		if (rgb_parts)
			free_2d_array(rgb_parts);
		return (NULL);
	}
	return (rgb_parts);
}

static int	parse_individual_rgb_components(char **rgb_parts, int *rgb_values)
{
	int	ok_r;
	int	ok_g;
	int	ok_b;

	ok_r = is_number(rgb_parts[0]);
	ok_g = is_number(rgb_parts[1]);
	ok_b = is_number(rgb_parts[2]);
	rgb_values[0] = ft_atoi(rgb_parts[0], &ok_r);
	rgb_values[1] = ft_atoi(rgb_parts[1], &ok_g);
	rgb_values[2] = ft_atoi(rgb_parts[2], &ok_b);
	if (ok_r == 1 || !is_number(rgb_parts[0]) || ok_g == 1
		|| !is_number(rgb_parts[1]) || ok_b == 1 || !is_number(rgb_parts[2]))
		return (0);
	if (rgb_values[0] < 0 || rgb_values[0] > 255 || rgb_values[1] < 0
		|| rgb_values[1] > 255 || rgb_values[2] < 0 || rgb_values[2] > 255)
		return (0);
	return (1);
}

static void	set_color_in_data(t_mlx *data, char id, int *rgb)
{
	t_color	*target_color;

	if (id == 'F')
		target_color = &data->map.floor.color;
	else
		target_color = &data->map.ceiling.color;
	target_color->r = (unsigned char)rgb[0];
	target_color->g = (unsigned char)rgb[1];
	target_color->b = (unsigned char)rgb[2];
}

int	parse_color_line(t_mlx *data, char *line, char **instructions)
{
	char	id;
	char	*trimmed_line;
	char	**rgb_parts;
	int		rgb[3];

	trimmed_line = trim_and_get_identifier(data, line, &id);
	if (!trimmed_line)
		return (0);
	rgb_parts = split_rgb_values(trimmed_line + 2);
	if (!rgb_parts || !parse_individual_rgb_components(rgb_parts, rgb))
	{
		free(trimmed_line);
		free_2d_array(rgb_parts);
		free_2d_array(instructions);
		free(line);
		finalize(data, ERR_INVALID_RGB, 1);
	}
	set_color_in_data(data, id, rgb);
	free_2d_array(rgb_parts);
	free(trimmed_line);
	return (1);
}
