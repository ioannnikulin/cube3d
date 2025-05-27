/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:22:37 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/27 17:43:16 by inikulin         ###   ########.fr       */
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
		initialize_texture_asset(&data->assets.wall_north, \
				path, target_path_ptr);
	else if (ft_strcmp(id, "SO") == 0)
		initialize_texture_asset(&data->assets.wall_south, \
				path, target_path_ptr);
	else if (ft_strcmp(id, "WE") == 0)
		initialize_texture_asset(&data->assets.wall_west, \
				path, target_path_ptr);
	else if (ft_strcmp(id, "EA") == 0)
		initialize_texture_asset(&data->assets.wall_east, \
			path, target_path_ptr);
	else
		return (-1);
	return (0);
}

void	handle_configure_error(char **parts, char *trimmed_line, \
									const char *error_message)
{
	ft_free_ss_uptonull((void **)parts);
	free(trimmed_line);
	if (error_message)
		exit_error((char *)error_message);
		// finalize?
}

void	initialize_texture_asset(t_img *asset, char *path_str, \
									void ***img_ptr_target)
{
	*img_ptr_target = &asset->img;
	asset->path = ft_strdup(path_str);
	if (!asset->path)
		exit_error("Error: Memory allocation failed for texture path");
		// finalize?
	asset->width = MAP_TEXTURE_WIDTH; // not necessarily, it can be defined on per texture basis
	asset->height = MAP_TEXTURE_HEIGHT;
}
