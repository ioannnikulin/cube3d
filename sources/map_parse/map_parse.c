/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/25 16:36:33 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"
#include "inner.h"




void	print_allElements(t_mlx *data)
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
	{
		finalize(data, ERR_MAP_EXT, 1);
		return (0);
	}
	parse_instructions(data, map_file);
	printf("\nMap '%s' is valid and loaded.\n", map_file);
	return (1);
}
