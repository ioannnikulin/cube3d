/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:38:28 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/31 14:22:39 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_2d_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_img(t_mlx *mlx, t_img *img)
{
	if (!img || !mlx || !mlx->mlx)
		return ;
	if (img->img && img->img != (void *) - 1)
	{
		mlx_destroy_image(mlx->mlx, img->img);
		img->img = NULL;
	}
	if (img->path)
	{
		free(img->path);
		img->path = NULL;
	}
}

void	free_mlx_assets(t_mlx *mlx)
{
	int	i;

	i = -1;
	if (mlx->mlx)
	{
		free_img(mlx, &mlx->assets.wall_east);
		free_img(mlx, &mlx->assets.wall_west);
		free_img(mlx, &mlx->assets.wall_north);
		free_img(mlx, &mlx->assets.wall_south);
		if (mlx->frame.imgs)
		{
			while (++i < FRAMES_BUFFER)
			{
				if (mlx->frame.imgs[i])
				{
					mlx_destroy_image(mlx->mlx, mlx->frame.imgs[i]);
					mlx->frame.imgs[i] = NULL;
				}
			}
			free(mlx->frame.imgs);
			mlx->frame.imgs = NULL;
		}
	}
}

int	finalize(t_mlx *mlx, char *msg, int ret)
{
	if (mlx->mlx && mlx->win)
		mlx_clear_window(mlx->mlx, mlx->win);
	if (mlx->map.map)
	{
		free_map(mlx->map.map);
		mlx->map.map = NULL;
	}
	if (mlx->mlx)
	{
		free_mlx_assets(mlx);
		if (mlx->frame.imgs_data)
			free(mlx->frame.imgs_data);
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		mlx->mlx = NULL;
	}
	if (msg)
		printf("%s", msg);
	exit(ret);
}

int	close_it(void *param)
{
	return (finalize((t_mlx *)param, "", 0));
}
