/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:36:45 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/04/06 19:22:03 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
			game->player = malloc(sizeof(t_player));
			game->player->x = i;
			game->player->y = j;
			break ;
		}
		j++;
	}
}

//floodfill algorithm to check if the map is enclosed by walls
void	floodfill(t_mlx *game, int row, int col, int **passed)
{
	if (row < 0 || col < 0 || row >= game->map->map_height
		|| col >= game->map->map_width)
		return ;
	if (game->map->map[row][col] == '1' || game->map->map[row][col] == '2'
		|| passed[row][col])
		return ;
	if (game->map->map[row][col] == ' ')
	{
		game->map->is_enclosed = 0;
		return ;
	}
	if (col == 0 || col == game->map->map_width - 1 || row == 0
		|| row == game->map->map_height - 1)
	{
		game->map->is_enclosed = 0;
		return ;
	}
	passed[row][col] = 2;
	floodfill(game, row + 1, col, passed);
	floodfill(game, row - 1, col, passed);
	floodfill(game, row, col + 1, passed);
	floodfill(game, row, col - 1, passed);
}

int	is_surrounded_by_walls(t_mlx *data)
{
	int i;
	int row;
	int col;
	int **passed;

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
	i = passed[row][col] && passed[data->map->map_height
		- 1][data->map->map_width - 1];
	return (1);
}