/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/04/01 21:41:48 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"


void	print_map1(int **map)
{
	int	i;
	int	j;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		printf("\n");
	}
}

void	determine_player_position(t_mlx *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (++i < game->map->map_height)
	{
		while (++j < game->map->map_width)
		{
			if (game->map->map[i][j] == 'N' || game->map->map[i][j] == 'S' \
			|| game->map->map[i][j] == 'E' || game->map->map[i][j] == 'W')
			{
				if (game->player)
					free(game->player);
				game->player = malloc(sizeof(t_player));
				if (!game->player)
					return ;
				if (!game->player)
					return ;
				game->player->x = j;
				game->player->y = i;
				printf("Player position: %d, %d\n", game->player->x, game->player->y);
				return ;
			}
		}
		j = 0;
	}
}

void	free_passed(int **passed, t_mlx *game)
{
	int	i;

	i = 0;
	determine_player_position(game);
	while (i < game->map->map_height)
	{
		free(passed[i]);
		i++;
	}
	free(passed);
}

int	is_move_valid(t_mlx *game, int **passed, int row, int col)
{
	// print_map1(passed);
	printf("passed[row][col]: %d\n", passed[row][col]);
	return (((game->map->map[row][col] == '1' ) && passed[row][col] == '2') || (ft_strchr("NSWE", game->map->map[row][col])));
}

void	floodfill(t_mlx *game, int row, int col, int **passed)
{
	// Check if we're out of bounds
	if (row < 0 || col < 0 || row >= game->map->map_height || col >= game->map->map_width)
		return;

	// If we hit a wall or already visited cell, stop here
	if (game->map->map[row][col] == '1' || game->map->map[row][col] == '2' || passed[row][col])
		return;

	// Check if we've reached a space character - this means the map is not enclosed
	if (game->map->map[row][col] == ' ')
	{
		printf("map[%d][%d]: %c\n", row, col, game->map->map[row][col]);
		game->map->is_enclosed = 0; // Add this flag to your map struct
		return ;
	}

	// Check if we're at the edge of the map - if we can reach here with a non-wall character,
	// the map is not properly enclosed
	if (col == 0 || col == game->map->map_width - 1 || row == 0 || row == game->map->map_height - 1)
	{
		printf("map[%d][%d]: %c\n", row, col, game->map->map[row][col]);
		game->map->is_enclosed = 0; // Map is not enclosed by walls
		return;
	}

	// Mark as visited
	passed[row][col] = 2;
	
	// Continue flood fill in all four directions
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
		if (game->map->map[i][j] == 'N' || game->map->map[i][j] == 'S' \
		|| game->map->map[i][j] == 'E' || game->map->map[i][j] == 'W')
		{
			*row = i;
			*col = j;
			break ;
			printf("player position: %d, %d\n", *row, *col);
		}
		j++;
	}
}

int	is_valid_path(t_mlx *data)
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
	printf(" player row: %d, col: %d\n", row, col);
	floodfill(data, row, col, passed);
	if (data->map->is_enclosed == 0)
		return (printf("Error\nMap is not enclosed by walls\n"), 0);
	i = passed[row][col] && passed[data->map->map_height - 1][data->map->map_width - 1];
	
	return (1);
}

int first_or_last_line(char **map, int map_width, int map_height)
{
	int	j;

	j = -1;
	while (++j < map_width)
	{
		if ((map[0][j] == WALL || map[0][j] == ' ' || map[0][j] == 32 || map[0][j] == '\n') \
			|| (map[map_height - 1][j] == WALL || map[map_height - 1][j] == ' ' \
			|| map[map_height - 1][j] == 32 || map[map_height - 1][j] == '\n'))
			continue;
		else
			return (0);
	}
	return (1);
}

int is_surrounded_by_walls(char **map, int map_width, int map_height, t_mlx *data)
{
	// int	i;
	// int	j;

	// i = -1;
	// if (!first_or_last_line(map, map_width, map_height))
	// 	printf("Error\nMap is not surrounded by walls on first or last line\n");

	(void)map;
	(void)map_width;
	(void)map_height;
	if (!is_valid_path(data))
		return (0);
	// while (++i < map_height)
	// {
	// 	j = -1;
	// 	while (++j < map_width)
	// 	{
	// 		if (map[i][j] == '0')
	// 		{
	// 			if (i == 0 || i == map_height - 1 || j == 0 || j == map_width - 1)
	// 				return (0);
	// 		}
	// 	}
	// }

	return (1);
}


int is_valid_char(char c)
{
	if (c == EMPTY || c == WALL || c == NORTH || c == SOUTH \
	|| c == EAST || c == WEST || c == '\n' || c == ' ' || c == '\0')
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
			{
				printf("map[%d][%d] = %d\n", i, j, map[i][j]);
				printf("Error\nInvalid map character\n");
				return (0);
			}
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
	if (!is_surrounded_by_walls(data->map->map, data->map->map_width, data->map->map_height, data))
	{
		printf("Error\nMap is not surrounded by walls\n");
		exit(EXIT_FAILURE);
	}
	print_map(data->map->map);
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
	return (1);
}