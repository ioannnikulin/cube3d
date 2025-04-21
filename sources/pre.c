/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:13:28 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/21 12:39:05 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	endian_offsets(t_mlx *mlx)
{
	mlx->frame.red_offset = 0;
	mlx->frame.green_offset = 1;
	mlx->frame.blue_offset = 2;
	if (mlx->frame.endian == 0)
	{
		mlx->frame.red_offset = 2;
		mlx->frame.green_offset = 1;
		mlx->frame.blue_offset = 0;
	}
}

int	pre(t_mlx *mlx)
{
	ft_bzero((void *)mlx, sizeof(t_mlx));
	mlx->map.zmax = 1;
	mlx->map.zmin = 0;
	mlx->mlx = mlx_init();
	if (!mlx)
		return (finalize(mlx, ERR_MLX_INIT, 2));
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_TITLE);
	if (!mlx->win)
		return (finalize(mlx, ERR_MLX_WIN, 3));
	endian_offsets(mlx);
	mlx->frame.imgs = ft_calloc_if(sizeof(void *) * FRAMES_BUFFER, 1);
	mlx->frame.imgs_data = ft_calloc_if(sizeof(char *) * FRAMES_BUFFER, 1);
	if (!mlx->frame.imgs || !mlx->frame.imgs_data)
		return (finalize(mlx, ERR_MALLOC, 4));
	return (0);
}