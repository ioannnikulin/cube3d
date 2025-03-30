/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/03/30 21:19:10 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int is_valid_char(char c)
{
	if (c == EMPTY || c == WALL || c == NORTH || c == SOUTH || c == EAST || c == WEST || c == '\n')
		return (1);
	return (0);
}

int	check_elements(t_mlx *mlx, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (++i < mlx->map->map_height)
	{
		j = -1;
		while (++j < mlx->map->map_width)
		{
			if (!is_valid_char(map[i][j]))
				return (printf("Error\nInvalid map character\n"), 0);
		}
	}
	return (1);
}

int	count_lines(char *map)
{
	int		file;
	int		lines;
	char	*temp;

	lines = 0;
	file = open(map, O_RDONLY);
	temp = get_next_line(file);
	while (temp)
	{
		lines++;
		free(temp);
		temp = get_next_line(file);
	}
	close(file);
	return (lines);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		printf("%s", map[i++]);
}

void	fill_map(t_mlx *data, char *mp)
{
	int	file;
	int	i;
	int	lines;

	lines = count_lines(mp);
	i = 0;
	file = open(mp, O_RDONLY);
	data->map = malloc(sizeof(char *) * (size_t)(lines + 1));
	data->map->map = malloc(sizeof(char *) * (size_t)(lines + 1));
	data->map->map[0] = get_next_line(file);
	if (!data->map->map[0])
	{
		printf("Error\nFailed to read map\n");
		return;
	}
	data->map->map_width = ft_strlen(data->map->map[0]);
	data->map->map_height = lines;
	while (i++ < data->map->map_height)
		data->map->map[i] = get_next_line(file);
	print_map(data->map->map);
	
	if (!check_elements(data, data->map->map) )
		{ 
			printf("Error\nFailed to read map\n");
			return;
		}
	close(file);
}


static int	check_extention(char *map)
{
	int	i;

	i = 0;
	if (ft_strchr(map, '.') == 0)
		return (printf("Error\nInvalid map extension\n"), 0);
	while (map[i])
	{
		if (map[i] == '.')
		{
			if (!(map[i + 1] == 'c' && map[i + 2] == 'u' \
			&& map[i + 3] == 'b' && !(map[i + 4])))
				return (printf("Error\nInvalid map extension\n"), 0);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int validate_map(t_mlx *data, char *map)
{
    int res;

    res = check_extention(map);
	fill_map(data, map);
	if (res == 0)
		return (printf("Error\nInvalid map extension\n"), 0);
    else
        return (printf("Success\n"),1);
}