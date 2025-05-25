/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:56:14 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/25 16:17:47 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static void	copy_map_data(t_mlx *data, char **instructions, int map_start_index,
		int map_height)
{
	int	j;
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


static int	check_elements(t_mlx *mlx, char **map)
{
	int	i;
	int	j;
	int	player_already_parsed;

	i = -1;
	player_already_parsed = 0;
	if (!map || mlx->map.map_height <= 0)
	{
		printf("Error\nInvalid map dimensions or map pointer in check_elements\n");
		return (0);
	}
	while (++i < mlx->map.map_height)
	{
		j = -1;
		if (!map[i])
		{
			printf("Error\nNULL row found in map at index %d\n", i);
			return (0);
		}
		if (map[i][0] == '\n')
			return (finalize(mlx, ERR_MAP_EMPTY_ROW, 0), 0);
		if (mlx->map.map_width <= 0)
		{
			printf("Error\nInvalid map width in check_elements\n");
			return (0);
		}
		while (++j < mlx->map.map_width && map[i][j] != '\0')
		{
			if (map[i][j] == '\0')
				break ;
			if (!is_valid_char(mlx, map[i][j], &player_already_parsed))
				return (0);
		}
	}
	if (player_already_parsed == 0)
		return (finalize(mlx, "Error: No player found", 0));
	return (1);
}

static char	**read_instructions_and_count_lines(char *file, int *total_lines_out)
{
	int		fd;
	int		lines_read;
	char	**instructions_arr;
	int		loc_total_lines;

	loc_total_lines = count_map_lines(file);
	if (loc_total_lines <= 6)
		exit_error("Error: Map file too short or missing elements/map");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error("Error: Cannot open map file");
	instructions_arr = ft_calloc_if(sizeof(char *) * (size_t)(loc_total_lines + 1), 1);
	if (!instructions_arr)
	{
		close(fd);
		exit_error("Error: Cannot allocate memory for instructions buffer");
	}
	lines_read = 0;
	while (lines_read < loc_total_lines
		&& (instructions_arr[lines_read] = get_next_line(fd)) != NULL)
		lines_read++;
	instructions_arr[lines_read] = NULL;
	close(fd);
	if (lines_read != loc_total_lines)
	{
		free_instructions(instructions_arr, lines_read);
		exit_error("Error: Mismatch between counted lines and lines read");
	}
	*total_lines_out = loc_total_lines;
	return (instructions_arr);
}

static void	find_elements_and_map_start(t_mlx *data, char **instructions,
		int *elements_found_out, int *map_start_idx_out)
{
	int i;

	i = 0;
	*elements_found_out = 0;
	*map_start_idx_out = -1;
	while (instructions[i] != NULL && *map_start_idx_out == -1)
	{
        process_line(data, instructions[i], elements_found_out,
						 map_start_idx_out, i);
		i++;
	}
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
