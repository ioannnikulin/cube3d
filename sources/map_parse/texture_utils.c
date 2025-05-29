/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:22:37 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/29 15:01:09 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

void	set_direction(t_mlx *game, int to_x, int to_y)
{
	game->player.coords.to.x = to_x;
	game->player.coords.to.y = to_y;
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	set_texture_target(t_mlx *data, char *id, \
		void ***target_path_ptr, char *path)
{
	if (ft_strcmp(id, "NO") == 0)
		initialize_texture_asset(data, &data->assets.wall_north, \
				path, target_path_ptr);
	else if (ft_strcmp(id, "SO") == 0)
		initialize_texture_asset(data, &data->assets.wall_south, \
				path, target_path_ptr);
	else if (ft_strcmp(id, "WE") == 0)
		initialize_texture_asset(data, &data->assets.wall_west, \
				path, target_path_ptr);
	else if (ft_strcmp(id, "EA") == 0)
		initialize_texture_asset(data, &data->assets.wall_east, \
			path, target_path_ptr);
	else
		return (-1);
	return (0);
}

void	handle_configure_error(t_mlx *data, char **parts, char *trimmed_line, \
									char *error_message)
{
	free_2d_array(parts);
	free(trimmed_line);
	if (error_message)
		finalize(data, error_message, 1);
	finalize(data, "", 1);
}

void	initialize_texture_asset(t_mlx *data, t_img *asset, char *path_str, \
									void ***img_ptr_target)
{
	*img_ptr_target = &asset->img;
	asset->path = ft_strdup(path_str);
	if (!asset->path)
		finalize(data, ERR_MALLOC_TEXTURE, 1);
	asset->width = MAP_TEXTURE_WIDTH;
	asset->height = MAP_TEXTURE_HEIGHT;
}
