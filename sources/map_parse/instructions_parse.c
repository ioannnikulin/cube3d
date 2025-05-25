/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:56:14 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/25 17:45:45 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static int	read_lines_into_array(int fd, char **instructions_arr, int total_lines)
{
	int	lines_read;

	lines_read = 0;
	while (lines_read < total_lines
		&& (instructions_arr[lines_read] = get_next_line(fd)) != NULL)
		lines_read++;
	instructions_arr[lines_read] = NULL;
	close(fd);
	return (lines_read);
}

static char	**read_instructions_and_count_lines(char *file, int *total_lines_out)
{
	int		fd;
	int		lines_read;
	char	**instructions_arr;
	int		loc_total_lines;

	fd = open_map_file_and_get_fd(file, &loc_total_lines);
	instructions_arr = allocate_instructions_array(loc_total_lines);
	lines_read = read_lines_into_array(fd, instructions_arr, loc_total_lines);

	if (lines_read != loc_total_lines)
	{
		free_instructions(instructions_arr, lines_read);
		exit_error("Error: Mismatch between counted lines and lines read");
	}
	*total_lines_out = loc_total_lines;
	return (instructions_arr);
}

static int	setup_map_data_and_free_instructions(t_mlx *data, char **instructions,
		int total_lines, int map_start_index)
{
	int map_height;

	map_height = total_lines - map_start_index;
	if (map_height <= 0)
	{
		free_instructions(instructions, total_lines);
		free_assets(data);
		exit_error("Error: No map data found after configuration elements");
	}
	data->map.map_height = map_height;
	data->map.map = ft_calloc_if(sizeof(char *) * (data->map.map_height + 1), 1);
	if (!data->map.map)
	{
		free_instructions(instructions, total_lines);
		free_assets(data);
		exit_error("Error: Cannot allocate memory for map storage");
	}
	copy_map_data(data, instructions, map_start_index, data->map.map_height);
	free_instructions(instructions, total_lines);
	data->map.map_width = longest_line(data->map.map);
	if (data->map.map_width <= 0)
		finalize(data, "Error: Map has no width or is invalid after copy", 0);
	return (0);
}

static void	perform_final_map_validation(t_mlx *data)
{
	int	map_elements_ok;
	int	map_surrounded_ok;

	map_elements_ok = check_elements(data, data->map.map);
	map_surrounded_ok = is_surrounded_by_walls(data);
	if (!is_map_valid(data->map.map_width, map_elements_ok))
	{
		free_map(data->map.map);
		data->map.map = NULL;
		return;
	}
	if (map_surrounded_ok == 0)
	{
		free_map(data->map.map);
		data->map.map = NULL;
		return;
	}
	printf("Instructions parsed successfully.\n");
}

void	parse_instructions(t_mlx *data, char *file)
{
	char	**instructions;
	int		total_lines;
	int		elements_found;
	int		map_start_index;

	init_parse_data(data);
	total_lines = 0;
	elements_found = 0;
	map_start_index = -1;
	instructions = read_instructions_and_count_lines(file, &total_lines);
	find_elements_and_map_start(data, instructions, &elements_found, &map_start_index);

	if (elements_found != 6 || map_start_index == -1)
	{
		free_instructions(instructions, total_lines);
		free_assets(data);
		if (elements_found != 6)
			exit_error("Error: Missing or duplicate map elements");
		else
			exit_error("Error: Map grid definition not found after elements");
	}
	if (setup_map_data_and_free_instructions(data, instructions, total_lines,
									   map_start_index) == -1)
		return;
	perform_final_map_validation(data);
}
