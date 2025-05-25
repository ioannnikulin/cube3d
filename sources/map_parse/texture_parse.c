/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:03:11 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/25 15:04:35 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"


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

int	set_texture_target(t_mlx *data, char *id, void ***target_path_ptr, char *path)
{
	if (ft_strcmp(id, "NO") == 0)
	{
		*target_path_ptr = &data->assets.wall_north.img;
		data->assets.wall_north.path = ft_strdup(path);
		data->assets.wall_north.width = 300;
		data->assets.wall_north.height = 300;
	}
	else if (ft_strcmp(id, "SO") == 0)
	{
		*target_path_ptr = &data->assets.wall_south.img;
		data->assets.wall_south.path = ft_strdup(path);
		data->assets.wall_south.width = 300;
		data->assets.wall_south.height = 300;
	}
	else if (ft_strcmp(id, "WE") == 0)
	{
		*target_path_ptr = &data->assets.wall_west.img;
		data->assets.wall_west.path = ft_strdup(path);
		data->assets.wall_west.width = 300;
		data->assets.wall_west.height = 300;
	}
	else if (ft_strcmp(id, "EA") == 0)
	{
		*target_path_ptr = &data->assets.wall_east.img;
		data->assets.wall_east.path = ft_strdup(path);
		data->assets.wall_east.width = 300;
		data->assets.wall_east.height = 300;
	}
	else
		return (-1);
	return (0);
}

static char	*trim_and_validate_raw_line(char *line, int *should_continue)
{
	char	*trimmed_line;

	*should_continue = 0;
	trimmed_line = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed_line)
		exit_error("Error: Memory allocation failed for trimmed_line");
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (NULL);
	}
	*should_continue = 1;
	return (trimmed_line);
}

static char	**split_trimmed_line(char *trimmed_line, int *should_continue)
{
	char	**parts;

	*should_continue = 0;
	parts = ft_split(trimmed_line, ' ', 0);
	if (!parts)
	{
		free(trimmed_line);
		exit_error("Error: Memory allocation failed for parts");
	}
	if (!parts[0] || !parts[1] || parts[2] != NULL)
	{
		free_parts(parts);
		free(trimmed_line);
		return (NULL);
	}
	*should_continue = 1;
	return (parts);
}

static void	**configure_texture_asset(t_mlx *data, char **parts, \
									char *trimmed_line, int *should_continue)
{
	void	**img_field_ptr;

	*should_continue = 0;
	if (set_texture_target(data, parts[0], &img_field_ptr, parts[1]) == -1)
	{
		free_parts(parts);
		free(trimmed_line);
		return (NULL);
	}
	if (*img_field_ptr != NULL)
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
	*img_field_ptr = ft_strdup(parts[1]);
	if (!*img_field_ptr)
	{
		free_parts(parts);
		free(trimmed_line);
		exit_error("Error: Failed to duplicate texture path");
	}
	*should_continue = 1;
	return (img_field_ptr);
}

static void	verify_texture_file_accessibility(void **img_field_ptr, \
											char **parts, char *trimmed_line)
{
	int	fd_texture;

	fd_texture = open((char *)(*img_field_ptr), O_RDONLY);
	if (fd_texture == -1)
	{
		ft_putstr_fd("Error\nCannot open or read texture file: ", STDERR_FILENO);
		ft_putstr_fd((char *)(*img_field_ptr), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(*img_field_ptr);
		*img_field_ptr = NULL;
		free_parts(parts);
		free(trimmed_line);
		exit_error("Invalid texture file path or permissions.");
	}
	close(fd_texture);
}

int	parse_texture_line(t_mlx *data, char *line)
{
	char	*trimmed_line;
	char	**parts;
	void	**img_field_ptr;
	int		should_continue;

	trimmed_line = trim_and_validate_raw_line(line, &should_continue);
	if (!should_continue)
		return (0);
	parts = split_trimmed_line(trimmed_line, &should_continue);
	if (!should_continue)
		return (0);
	img_field_ptr = configure_texture_asset(data, parts, trimmed_line, \
											&should_continue);
	if (!should_continue)
		return (0);
	verify_texture_file_accessibility(img_field_ptr, parts, trimmed_line);
	free_parts(parts);
	free(trimmed_line);
	return (1);
}