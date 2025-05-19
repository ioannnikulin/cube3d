/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:38:28 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/19 06:22:19 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	finalize(t_mlx *mlx, char *msg, int ret)
{
	if (mlx)
	{
		if (mlx->map.map)
			free_map(mlx->map.map);
		if (mlx->mlx && mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		free(mlx->mlx);
		mlx->mlx = 0;
		mlx->map.map = 0;
	}
	printf("%s", msg);
	exit(ret);
	return (ret);
}

int	close_it(void *param)
{
	return (finalize((t_mlx *)param, MSG_EXIT, 0));
}

void	free_map(char **map)
{
	int	i;

	if (map)
	{
		i = -1;
		while (map[++i])
			free(map[i]);
		free(map);
	}
}
