/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:38:28 by inikulin          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/11 14:37:24 by inikulin         ###   ########.fr       */
=======
/*   Updated: 2025/05/10 20:01:17 by inikulin         ###   ########.fr       */
>>>>>>> 13_textures
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

<<<<<<< HEAD
int	close_it(void *param)
{
	return (finalize((t_mlx *)param, MSG_EXIT, 0));
=======
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
>>>>>>> 13_textures
}
