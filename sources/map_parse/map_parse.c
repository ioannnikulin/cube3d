/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/13 19:33:38 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"
#include "inner.h"

static int	parse_texture_line(t_mlx *data, char *line);
static int	parse_color_line(t_mlx *data, char *line);
static int	is_map_line(char *line);
static void	free_instructions(char **instructions, int count);

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
			return (printf(ERR_MAP_EMPTY_ROW), 0);
		if (mlx->map.map_width <= 0)
		{
			printf("Error\nInvalid map width in check_elements\n");
			return (0);
		}
		while (++j < mlx->map.map_width && map[i][j] != '\0')
		{
			if (map[i][j] == '\0')
				break ;
			if (!is_valid_char(map[i][j], &player_already_parsed))
				return (0);
		}
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

static void	init_map(t_mlx **data, char *file, int lines)
{
	int	i;
	int	fd;

	lines = (count_map_lines(file));
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error(ERR_MAP_OPEN);
	(*data)->map.map = ft_calloc_if(sizeof(char *) * (size_t)(lines + 1), 1);
	if (!(*data)->map.map)
		exit_error(ERR_MALLOC_MAP);
	(*data)->map.map[0] = get_next_line(fd);
	if (!(*data)->map.map[0])
		free_map_exit(&(*data), ERR_MALLOC_MAP);
	while (++i < lines)
	{
		(*data)->map.map[i] = get_next_line(fd);
		if (!(*data)->map.map[i])
			free_map_exit(&(*data), ERR_MALLOC_MAP);
	}
	close(fd);
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

// int	check_extension(char *map)
// {
// 	int	len;

// 	len = ft_strlen(map);
// 	if (len < 4)
// 		return (printf("Error\nInvalid map file name (too short)\n"), 0);
// 	if (ft_strcmp(map + len - 4, ".cub") == 0)
// 		return (1);
// 	else
// 		return (printf("Error\nInvalid map extension (must be .cub)\n"), 0);
// }

static void	free_instructions(char **instructions, int count)
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

static int	set_texture_target(t_mlx *data, char *id, void ***target_path_ptr, char *path)
{
	if (ft_strcmp(id, "NO") == 0)
	{
		*target_path_ptr = &data->assets.wall_north.img;
		data->assets.wall_north.path = path;
	}
	else if (ft_strcmp(id, "SO") == 0)
	{
		*target_path_ptr = &data->assets.wall_south.img;
		data->assets.wall_south.path = path;
	}
	else if (ft_strcmp(id, "WE") == 0)
	{
		*target_path_ptr = &data->assets.wall_west.img;
		data->assets.wall_west.path = path;
	}
	else if (ft_strcmp(id, "EA") == 0)
	{
		*target_path_ptr = &data->assets.wall_east.img;
		data->assets.wall_east.path = path;
	}
	else
		return (-1);
	return (0);
}

static void	free_parts(char **parts)
{
	int	k;

	k = 0;
	if (parts)
	{
		while (parts[k])
		{
			free(parts[k]);
			k++;
		}
		free(parts);
	}
}

static int	parse_texture_line(t_mlx *data, char *line)
{
	char	**parts;
	char	*trimmed_line;
	void	**target_path_ptr;
	int		fd_texture;

	trimmed_line = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed_line)
		exit_error("Error: Memory allocation failed for trimmed_line in texture parsing");
	if (trimmed_line[0] == '\0')
		return (free(trimmed_line), 0);
	parts = ft_split(trimmed_line, ' ', 0);
	if (!parts)
	{
		free(trimmed_line);
		exit_error("Error: Memory allocation failed for parts in texture parsing");
	}
	if (!parts[0] || !parts[1] || parts[2] != NULL)
	{
		free_parts(parts);
		free(trimmed_line);
		return (0);
	}
	if (set_texture_target(data, parts[0], &target_path_ptr, parts[1]) == -1)
	{
		free_parts(parts);
		free(trimmed_line);
		return (0);
	}
	if (*target_path_ptr != NULL)
	{
		free_parts(parts);
		free(trimmed_line);
		exit_error("Error: Duplicate texture definition");
	}
	if (parts[1][0] == '\0')
	{
		free_parts(parts);
		free(trimmed_line);
		exit_error("Error: Empty texture path provided");
	}
	*target_path_ptr = ft_strdup(parts[1]);
	if (!*target_path_ptr)
	{
		free_parts(parts);
		free(trimmed_line);
		exit_error("Error: Failed to duplicate texture path");
	}
	fd_texture = open((char *)(*target_path_ptr), O_RDONLY);
	if (fd_texture == -1)
	{
		ft_putstr_fd("Error\nCannot open or read texture file: ", STDERR_FILENO);
		ft_putstr_fd((char *)(*target_path_ptr), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(*target_path_ptr);
		*target_path_ptr = NULL;
		free_parts(parts);
		free(trimmed_line);
		exit_error("Invalid texture file path or permissions.");
	}
	close(fd_texture);
	free_parts(parts);
	free(trimmed_line);
	return (1);
}

static int	validate_rgb_values(int r, int g, int b, char *trimmed_line)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free(trimmed_line);
		exit_error("Error: RGB color value out of range (0-255)");
		return (0);
	}
	return (1);
}

static int	parse_color_line(t_mlx *data, char *line)
{
	char	id;
	char	*trimmed_line;
	char	**rgb_parts;
	int		r;
	int		g;
	int		b;
	t_color	*target_color;
	int		result;
	int		ok_r;
	int		ok_g;
	int		ok_b;

	printf("inside parse_color_line\n");

	ok_r = 1;
	ok_g = 1;
	ok_b = 1;
	trimmed_line = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed_line || trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (0);
	}
	id = trimmed_line[0];
	if (!((id == 'F' || id == 'C') && trimmed_line[1] == ' '))
	{
		free(trimmed_line);
		return (0);
	}
	if (trimmed_line[2] == '\0')
	{
		free(trimmed_line);
		exit_error("Error: Missing RGB values");
		return (0);
	}
	rgb_parts = ft_split(trimmed_line + 2, ',', 0);
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2]
		|| rgb_parts[3])
	{
		free(trimmed_line);
		exit_error("Error: Invalid RGB color format (must be R,G,B)");
		return (0);
	}
	r = ft_atoi(rgb_parts[0], &ok_r);
	g = ft_atoi(rgb_parts[1], &ok_g);
	b = ft_atoi(rgb_parts[2], &ok_b);
	if (!validate_rgb_values(r, g, b, trimmed_line))
		return (0);
	if (id == 'F')
		target_color = &data->map.floor.color;
	else
		target_color = &data->map.ceiling.color;
	target_color->r = (unsigned char)r;
	target_color->g = (unsigned char)g;
	target_color->b = (unsigned char)b;
	result = 1;
	free_parts(rgb_parts);
	free(trimmed_line);
	return (result);
}

static int	is_map_line(char *line)
{
	char	*start;
	int		i;

	printf("inside is_map_line\n");

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

static void	init_parse_data(t_mlx *data)
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

static void	free_assets(t_mlx *data)
{
	free(data->assets.wall_north.img);
	free(data->assets.wall_south.img);
	free(data->assets.wall_west.img);
	free(data->assets.wall_east.img);
}

static int	process_line(t_mlx *data, char *line, int *elements_found,
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

static int	read_instructions( char *file, char ***instructions)
{
	int	fd;
	int	lines_read;
	int	total_lines;

	total_lines = count_map_lines(file);
	if (total_lines <= 6)
		exit_error("Error: Map file too short or missing elements/map");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error("Error: Cannot open map file");
	*instructions = ft_calloc_if(sizeof(char *) * (size_t)(total_lines + 1), 1);
	if (!*instructions)
	{
		close(fd);
		exit_error("Error: Cannot allocate memory for instructions buffer");
	}
	lines_read = 0;
	while (lines_read < total_lines
		&& ((*instructions)[lines_read] = get_next_line(fd)) != NULL)
		lines_read++;
	(*instructions)[lines_read] = NULL;
	close(fd);
	if (lines_read != total_lines)
	{
		free_instructions(*instructions, lines_read);
		exit_error("Error: Mismatch between counted lines and lines read");
	}
	return (total_lines);
}

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

void	parse_instructions(t_mlx *data, char *file)
{
	char	**instructions;
	int		total_lines;
	int		i;
	int		map_start_index;
	int		elements_found;
	int		map_height;
	int		map_elements_ok;
	int		map_surrounded_ok;

	init_parse_data(data);
	elements_found = 0;
	map_start_index = -1;
	total_lines = read_instructions(file, &instructions);
	i = 0;
	while (instructions[i] != NULL && map_start_index == -1)
	{
		if (process_line(data, instructions[i], &elements_found,
				&map_start_index, i) == -1)
		{
			free_instructions(instructions, total_lines);
			free_assets(data);
			exit_error("Error: Invalid configuration line in map file");
		}
		i++;
	}
	if (elements_found != 6 || map_start_index == -1)
	{
		free_instructions(instructions, total_lines);
		free_assets(data);
		if (elements_found != 6)
			exit_error("Error: Missing or duplicate map elements");
		else
			exit_error("Error: Map grid definition not found after elements");
	}
	map_height = total_lines - map_start_index;
	if (map_height <= 0)
	{
		free_instructions(instructions, total_lines);
		free_assets(data);
		exit_error("Error: No map data found after configuration elements");
	}
	data->map.map_height = map_height;
	data->map.map = ft_calloc_if(sizeof(char *) * (map_height + 1), 1);
	if (!data->map.map)
	{
		free_instructions(instructions, total_lines);
		free_assets(data);
		exit_error("Error: Cannot allocate memory for map storage");
	}
	copy_map_data(data, instructions, map_start_index, map_height);
	free_instructions(instructions, total_lines);
	data->map.map_width = longest_line(data->map.map);
	map_elements_ok = check_elements(data, data->map.map);
	map_surrounded_ok = is_surrounded_by_walls(data);
	if (!is_map_valid(data->map.map_width, map_elements_ok))
		return (free_map(data->map.map));
	if (map_surrounded_ok == 0)
		return (free_map(data->map.map));
	printf("Instructions parsed successfully.\n");
	printf("F: %d,%d,%d\n", data->map.floor.color.r,
		data->map.floor.color.g, data->map.floor.color.b);
	printf("C: %d,%d,%d\n", data->map.ceiling.color.r,
		data->map.ceiling.color.g, data->map.ceiling.color.b);
	print_map(data->map.map);
}

void print_allElements(t_mlx *data)
{
	printf("\n\n\n//////////////////////////////\n");
	printf("Texture North: %s\n", data->assets.wall_north.path);
	printf("Texture South: %s\n", data->assets.wall_south.path);
	printf("Texture East: %s\n", data->assets.wall_east.path);
	printf("Texture West: %s\n", data->assets.wall_west.path);
	printf("F: %d,%d,%d\n", data->map.floor.color.r,
		data->map.floor.color.g, data->map.floor.color.b);
	printf("C: %d,%d,%d\n", data->map.ceiling.color.r,
		data->map.ceiling.color.g, data->map.ceiling.color.b);
	print_map(data->map.map);
}

int	validate_map(t_mlx *data, char *map_file)
{
	if (!check_extension(map_file))
		return (0);
	parse_instructions(data, map_file);
	print_allElements(data);
	if (!fill_map(data, map_file))
		return (0);
	printf("\nMap '%s' is valid and loaded.\n", map_file);
	return (1);
}
