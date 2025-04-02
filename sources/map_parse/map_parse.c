/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/04/02 20:35:20 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

//floodfill algorithm to check if the map is enclosed by walls
void	floodfill(t_mlx *game, int row, int col, int **passed)
{
	if (row < 0 || col < 0 || row >= game->map->map_height || col >= game->map->map_width)
		return;
	if (game->map->map[row][col] == '1' || game->map->map[row][col] == '2' || passed[row][col])
		return;
	if (game->map->map[row][col] == ' ')
	{
		game->map->is_enclosed = 0;
		return ;
	}
	if (col == 0 || col == game->map->map_width - 1 || row == 0 || row == game->map->map_height - 1)
	{
		game->map->is_enclosed = 0;
		return;
	}
	passed[row][col] = 2;
	floodfill(game, row + 1, col, passed);
	floodfill(game, row - 1, col, passed);
	floodfill(game, row, col + 1, passed);
	floodfill(game, row, col - 1, passed);
}

void	find_player_pos(t_mlx *game, int i, int *col, int *row)
{
	int	j;

	j = 0;
	while (game->map->map[i][j])
	{
		if (ft_strchr("NSEW", game->map->map[i][j]))
		{
			*row = i;
			*col = j;
			break ;
		}
		j++;
	}
}

int is_surrounded_by_walls(t_mlx *data)
{
	int	i;
	int	row;
	int	col;
	int	**passed;

	data->map->is_enclosed = 1;

	passed = ft_calloc(data->map->map_height, sizeof(int *));
	i = -1;
	while (++i < data->map->map_height)
		passed[i] = ft_calloc(data->map->map_width, sizeof(int *));
	i = -1;
	while (data->map->map[++i])
		find_player_pos(data, i, &col, &row);
	floodfill(data, row, col, passed);
	if (data->map->is_enclosed == 0)
		return (printf("Error\nMap is not enclosed by walls\n"), 0);
	i = passed[row][col] && passed[data->map->map_height - 1][data->map->map_width - 1];
	
	return (1);
}


int is_valid_char(char c)
{
	if (ft_strchr("01NSEW \n", c))
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
			if (!is_valid_char(map[i][j]))
				return (0);
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

	i = -1;
	while (map[++i])
		printf("%s", map[i]);
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
		exit(EXIT_FAILURE);
	}
	data->map->map_width = ft_strlen(data->map->map[0]);
	data->map->map_height = lines;
	while (i++ < data->map->map_height)
		data->map->map[i] = get_next_line(file);
	if (!is_surrounded_by_walls(data))
		exit(EXIT_FAILURE);
	if (!check_elements(data, data->map->map) )
			exit(EXIT_FAILURE);
	close(file);
}


static int	check_extention(char *map)
{
	int	i;

	i = -1;
	if (ft_strchr(map, '.') == 0)
		return (printf("Error\nInvalid map extension\n"), 0);
	while (map[++i])
	{
		if (map[i] == '.')
		{
			if (!(map[i + 1] == 'c' && map[i + 2] == 'u' \
			&& map[i + 3] == 'b' && !(map[i + 4])))
				return (0);
			else
				return (1);
		}
	}
	return (0);
}

int validate_map(t_mlx *data, char *map)
{
	if (!check_extention(map))
		return (printf("Error\nInvalid map extension\n"), 0);
	fill_map(data, map);
	printf("map is valid\n");
	return (1);
}