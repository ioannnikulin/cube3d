/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:38:28 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/10 15:37:23 by iverniho         ###   ########.fr       */
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

void	free_map(char **map)
{
	int	i;

	i = -1;
	if (map)
	{
		while (map[++i])
			free(map[i]);
		free(map);
	}
}
