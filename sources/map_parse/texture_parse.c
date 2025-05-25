/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:03:11 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/25 17:07:49 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static void	initialize_texture_asset(t_img *asset, char *path_str, \
									void ***img_ptr_target)
{
	*img_ptr_target = &asset->img;
	asset->path = ft_strdup(path_str);
	if (!asset->path)
		exit_error("Error: Memory allocation failed for texture path");
	asset->width = MAP_TEXTURE_WIDTH;
	asset->height = MAP_TEXTURE_HEIGHT;
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

int	set_texture_target(t_mlx *data, char *id, void ***target_path_ptr, char *path)
{
	if (ft_strcmp(id, "NO") == 0)
		initialize_texture_asset(&data->assets.wall_north, path, target_path_ptr);
	else if (ft_strcmp(id, "SO") == 0)
		initialize_texture_asset(&data->assets.wall_south, path, target_path_ptr);
	else if (ft_strcmp(id, "WE") == 0)
		initialize_texture_asset(&data->assets.wall_west, path, target_path_ptr);
	else if (ft_strcmp(id, "EA") == 0)
		initialize_texture_asset(&data->assets.wall_east, path, target_path_ptr);
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

static void	handle_configure_error(char **parts, char *trimmed_line, \
									const char *error_message)
{
	free_parts(parts);
	free(trimmed_line);
	if (error_message)
		exit_error((char *)error_message);
}

static void	**configure_texture_asset(t_mlx *data, char **parts, \
									char *trimmed_line, int *should_continue)
{
	void	**img_field_ptr;

	*should_continue = 0;
	if (set_texture_target(data, parts[0], &img_field_ptr, parts[1]) == -1)
		return (handle_configure_error(parts, trimmed_line, NULL), NULL);
	if (*img_field_ptr != NULL)
		return (handle_configure_error(parts, trimmed_line, \
		"Error: Duplicate texture definition"), NULL);
	if (parts[1][0] == '\0')
		return (handle_configure_error(parts, trimmed_line, \
		"Error: Empty texture path provided"), NULL);
	*img_field_ptr = ft_strdup(parts[1]);
	if (!*img_field_ptr)
		return (handle_configure_error(parts, trimmed_line, \
		"Error: Failed to duplicate texture path"), NULL);
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
		free(*img_field_ptr);
		*img_field_ptr = NULL;
		free_parts(parts);
		free(trimmed_line);
		exit_error("Invalid texture file path or permissions.");
	}
	close(fd_texture);
}

static void	convert_texture_to_image(t_mlx *mlx)
{
	mlx->assets.wall_north.img = mlx_xpm_file_to_image(mlx->mlx,
			mlx->assets.wall_north.path, &mlx->assets.wall_north.width,
			&mlx->assets.wall_north.height);
	mlx->assets.wall_south.img = mlx_xpm_file_to_image(mlx->mlx,
			mlx->assets.wall_south.path, &mlx->assets.wall_south.width,
			&mlx->assets.wall_south.height);
	mlx->assets.wall_west.img = mlx_xpm_file_to_image(mlx->mlx,
			mlx->assets.wall_west.path, &mlx->assets.wall_west.width,
			&mlx->assets.wall_west.height);
	mlx->assets.wall_east.img = mlx_xpm_file_to_image(mlx->mlx,
			mlx->assets.wall_east.path, &mlx->assets.wall_east.width,
			&mlx->assets.wall_east.height);
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
	convert_texture_to_image(data);
	free_parts(parts);
	free(trimmed_line);
	return (1);
}