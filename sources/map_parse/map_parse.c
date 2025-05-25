/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/25 17:29:27 by ivanverniho      ###   ########.fr       */
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

static int	check_extension(char *map)
{
	int	i;

	i = -1;
	if (ft_strchr(map, '.') == 0)
		return (0);
	while (map[++i])
	{
		if (map[i] == '.')
		{
			if (!(map[i + 1] == 'c' && map[i + 2] == 'u' && map[i + 3] == 'b'
					&& !(map[i + 4])))
				return (0);
			else
				return (1);
		}
	}
	return (0);
}

int	validate_map(t_mlx *data, char *map_file)
{
	if (!check_extension(map_file))
		finalize(data, ERR_MAP_EXT, 1);
	parse_instructions(data, map_file);
	printf("\nMap '%s' is valid and loaded.\n", map_file);
	return (1);
}
