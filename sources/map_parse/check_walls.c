/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:36:45 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/28 20:53:07 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static void	calculate_player_coords(t_mlx *game, \
		int col, int row, char direction)
{
	game->player.coords.from.x = col * \
		MINIMAP_BLOCK_SIZE + MINIMAP_BLOCK_SIZE / 2;
	game->player.coords.from.y = row * \
		MINIMAP_BLOCK_SIZE + MINIMAP_BLOCK_SIZE / 2;
	if (direction == 'S')
		set_direction(game, game->player.coords.from.x, \
			game->player.coords.from.y + MINIMAP_BLOCK_SIZE);
	else if (direction == 'N')
		set_direction(game, game->player.coords.from.x, \
			game->player.coords.from.y - MINIMAP_BLOCK_SIZE);
	else if (direction == 'E')
		set_direction(game, game->player.coords.from.x + MINIMAP_BLOCK_SIZE, \
			game->player.coords.from.y);
	else if (direction == 'W')
		set_direction(game, game->player.coords.from.x - MINIMAP_BLOCK_SIZE, \
			game->player.coords.from.y);
}

static void	find_player_pos(t_mlx *game, int i, int *col, int *row)
{
	int	j;

	j = 0;
	while (game->map.map[i][j])
	{
		if (ft_strchr("NSEW", game->map.map[i][j]))
		{
			*row = i;
			*col = j;
			calculate_player_coords(game, *col, *row, game->map.map[i][j]);
			return ;
		}
		j++;
	}
}

//floodfill algorithm to check if the map is enclosed by walls
static void	floodfill(t_mlx *game, int row, int col, int **passed)
{
	if (row < 0 || col < 0 || row >= game->map.map_height)
		return ;
	if (!game->map.map[row] || col >= (int)ft_strlen(game->map.map[row]))
		return ;
	if (game->map.map[row][col] == '1' || game->map.map[row][col] == '2'
		|| passed[row][col])
		return ;
	if (game->map.map[row][col] == ' ' || game->map.map[row][col] == '\0')
	{
		game->map.is_enclosed = 0;
		return ;
	}
	if (col == 0 || row == 0 || row == game->map.map_height - 1
		|| col >= (int)ft_strlen(game->map.map[row]) - 1)
	{
		game->map.is_enclosed = 0;
		return ;
	}
	passed[row][col] = 1;
	floodfill(game, row + 1, col, passed);
	floodfill(game, row - 1, col, passed);
	floodfill(game, row, col + 1, passed);
	floodfill(game, row, col - 1, passed);
}

static void	process_not_enclosed(t_mlx *data, int **passed, int height)
{
	free_passed_array(passed, height);
	printf(ERR_MAP_ENCLOSED);
	finalize(data, "Error: Map is not enclosed by walls", 0);
}

int	is_surrounded_by_walls(t_mlx *data)
{
	int	i;
	int	row;
	int	col;
	int	**passed;

	data->map.is_enclosed = 1;
	i = -1;
	passed = ft_calloc_if(sizeof(int *) * data->map.map_height, 1);
	if (!passed)
		return (printf(ERR_MALLOC), 0);
	while (++i < data->map.map_height)
	{
		passed[i] = ft_calloc_if(sizeof(int) * data->map.map_width, 1);
		if (!passed[i])
			return (free_passed_array(passed, i), 0);
	}
	i = -1;
	while (data->map.map[++i])
		find_player_pos(data, i, &col, &row);
	floodfill(data, row, col, passed);
	if (data->map.is_enclosed == 0)
		return (process_not_enclosed(data, passed, data->map.map_height), 0);
	return (free_passed_array(passed, data->map.map_height), 1);
}
