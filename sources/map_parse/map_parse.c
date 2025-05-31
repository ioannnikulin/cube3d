/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/31 17:35:11 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static int	check_extension(char *map)
{
	int	i;

	i = -1;
	if (ft_strchr(map, '.') == 0)
		return (0);
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

static int	check_xpm_size(char *trimmed_line, char *line, int fd)
{
	char	**splitted_line;

	splitted_line = ft_split(trimmed_line, ' ', NULL);
	if (dd_array_length(splitted_line) != 4)
	{
		free_2d_array(splitted_line);
		free(line);
		free(trimmed_line);
		close(fd);
		printf (ERR_WRONG_XPM_SIZE);
		return (0);
	}
	free_2d_array(splitted_line);
	return (1);
}

int	is_xpm_size_valid(char *file)
{
	int		fd;
	char	*line;
	int		is_all_numbers;
	int		i;
	char	*trimmed_line;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	is_all_numbers = 0;
	while (i++ < 6)
	{
		line = get_next_line(fd);
		trimmed_line = ft_strtrim(line, "\" \t\n ,");
		is_all_numbers = is_number_parse(trimmed_line);
		if (is_all_numbers)
			if (check_xpm_size(trimmed_line, line, fd) == 0)
				return (0);
		free(line);
		free(trimmed_line);
	}
	close(fd);
	return (1);
}

int	check_xpm(t_mlx *data)
{
	if (!is_xpm_size_valid(data->assets.wall_north.path))
		finalize(data, "", 1);
	if (!is_xpm_size_valid(data->assets.wall_south.path))
		finalize(data, "", 1);
	if (!is_xpm_size_valid(data->assets.wall_west.path))
		finalize(data, "", 1);
	if (!is_xpm_size_valid(data->assets.wall_east.path))
		finalize(data, "", 1);
	return (1);
}

int	validate_map(t_mlx *data, char *map_file)
{
	if (!check_extension(map_file))
		finalize(data, ERR_MAP_EXT, 1);
	parse_instructions(data, map_file);
	if (!check_xpm(data))
		finalize(data, ERR_WRONG_XPM_SIZE, 1);
	return (1);
}
