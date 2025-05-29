/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:22:37 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/29 18:03:41 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

int	set_texture_target(t_mlx *data, char *id,
		void ***target_path_ptr, char *path)
{
	if (ft_strcmp(id, "NO") == 0)
		initialize_texture_asset(data, &data->assets.wall_north,
			path, target_path_ptr);
	else if (ft_strcmp(id, "SO") == 0)
		initialize_texture_asset(data, &data->assets.wall_south,
			path, target_path_ptr);
	else if (ft_strcmp(id, "WE") == 0)
		initialize_texture_asset(data, &data->assets.wall_west,
			path, target_path_ptr);
	else if (ft_strcmp(id, "EA") == 0)
		initialize_texture_asset(data, &data->assets.wall_east,
			path, target_path_ptr);
	else
		return (-1);
	return (0);
}

void	handle_configure_error(t_mlx *data, char **parts, char *trimmed_line,
									char *error_message)
{
	free_2d_array(parts);
	free(trimmed_line);
	if (error_message)
		finalize(data, error_message, 1);
	finalize(data, "", 1);
}

void	set_xpm_size(t_mlx *data, t_img *asset,
		char *trimmed_line, int is_all_numbers)
{
	char	**splitted_line;

	splitted_line = ft_split(trimmed_line, ' ', NULL);
	if (!splitted_line)
	{
		free(trimmed_line);
		finalize(data, ERR_MALLOC_TEXTURE, 1);
	}
	asset->width = ft_atoi(splitted_line[0], &is_all_numbers);
	asset->height = ft_atoi(splitted_line[1], &is_all_numbers);
	free(trimmed_line);
	free_2d_array(splitted_line);
}

void	parse_xpm_size(t_mlx *data, t_img *asset)
{
	int		fd;
	char	*line;
	char	*trimmed_line;
	int		i;
	int		is_all_numbers;

	i = 0;
	fd = open(asset->path, O_RDONLY);
	if (fd < 0)
		finalize(data, ERR_OPEN_TEXTURE, 1);
	while (i++ < 10)
	{
		line = get_next_line(fd);
		trimmed_line = ft_strtrim(line, "\" \t\n ,");
		is_all_numbers = is_number(trimmed_line);
		if (is_all_numbers)
		{
			set_xpm_size(data, asset, trimmed_line, is_all_numbers);
			return (free(line));
		}
		free(line);
		free(trimmed_line);
	}
	close(fd);
	finalize(data, ERR_OPEN_TEXTURE, 1);
}

void	initialize_texture_asset(t_mlx *data, t_img *asset, char *path_str,
									void ***img_ptr_target)
{
	*img_ptr_target = &asset->img;
	asset->path = ft_strdup(path_str);
	if (!asset->path)
		finalize(data, ERR_MALLOC_TEXTURE, 1);
	parse_xpm_size(data, asset);
}
