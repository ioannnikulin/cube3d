/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:56:14 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/29 20:15:20 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static int	read_lines_into_array(int fd,
		char **instructions_arr, int total_lines)
{
	int		lines_read;

	lines_read = 0;
	while (lines_read < total_lines)
	{
		instructions_arr[lines_read] = get_next_line(fd);
		if (instructions_arr[lines_read] == NULL)
			break ;
		lines_read++;
	}
	instructions_arr[lines_read] = NULL;
	close(fd);
	return (lines_read);
}

static char	**read_instructions_and_count_lines(t_mlx *data, char *file,
		int *total_lines_out)
{
	int		fd;
	int		lines_read;
	char	**instructions_arr;
	int		loc_total_lines;

	fd = open_map_file_and_get_fd(data, file, &loc_total_lines);
	instructions_arr = allocate_instructions_array(data, loc_total_lines);
	lines_read = read_lines_into_array(fd, instructions_arr, loc_total_lines);
	if (lines_read != loc_total_lines)
	{
		free_2d_array(instructions_arr);
		finalize(data, ERR_PARSE_INSTRUCTIONS, 1);
	}
	*total_lines_out = loc_total_lines;
	return (instructions_arr);
}

static int	setup_map_data_and_free_instructions(t_mlx *data,
		char **instructions,
		int total_lines, int map_start_index)
{
	int	map_height;

	map_height = total_lines - map_start_index;
	if (map_height <= 0)
	{
		free_2d_array(instructions);
		free_assets(data);
		finalize(data, ERR_ABSENT_MAP, 0);
	}
	data->map.map_height = map_height;
	data->map.map = ft_calloc_if(sizeof(char *)
			* (data->map.map_height + 1), 1);
	if (!data->map.map)
	{
		free_2d_array(instructions);
		free_assets(data);
		finalize(data, ERR_MALLOC_MAP, 0);
	}
	copy_map_data(data, instructions, map_start_index, data->map.map_height);
	free_2d_array(instructions);
	data->map.map_width = longest_line(data->map.map);
	if (data->map.map_width <= 0)
		finalize(data, "", 0);
	return (0);
}

static int	perform_final_map_validation(t_mlx *data)
{
	int	map_elements_ok;
	int	map_surrounded_ok;

	map_elements_ok = check_elements(data, data->map.map);
	if (!map_elements_ok)
		return (1);
	map_surrounded_ok = is_surrounded_by_walls(data);
	if (data->errno)
		return (2);
	if (!is_map_valid(data->map.map_width, map_elements_ok))
		return (finalize(data, ERR_MAP_INVALID, 3));
	if (map_surrounded_ok == 0)
		return (finalize(data, ERR_MAP_ENCLOSED, 4));
	printf("Instructions parsed successfully.\n");
	return (0);
}

int	parse_instructions(t_mlx *data, char *file)
{
	char	**instructions;
	int		total_lines;
	int		elements_found;
	int		map_start_index;

	init_parse_data(data);
	total_lines = 0;
	elements_found = 0;
	map_start_index = -1;
	instructions = read_instructions_and_count_lines(data, file, &total_lines);
	if (find_elements_and_map_start(data, instructions, &elements_found,
			&map_start_index))
		return (1);
	if (elements_found != 6 || map_start_index == -1)
	{
		free_assets(data);
		free_2d_array(instructions);
		finalize(data, ERR_MAP_INVALID, 1);
	}
	if (setup_map_data_and_free_instructions(data, instructions, total_lines,
			map_start_index) == -1)
		finalize(data, ERR_PARSE_MAP, 0);
	return (perform_final_map_validation(data));
}
