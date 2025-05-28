/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:38:28 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/28 20:49:23 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int	finalize(t_mlx *mlx, char *msg, int ret)
{
	int	i;

	i = -1;
	if (mlx->mlx && mlx->win)
		mlx_clear_window(mlx->mlx, mlx->win);
	if (mlx->map.map)
	{
		free_map(mlx->map.map);
		mlx->map.map = NULL;
	}
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
		if (mlx->frame.imgs_data)
		{
			free(mlx->frame.imgs_data);
			mlx->frame.imgs_data = NULL;
		}
		if (mlx->win)
		{
			mlx_destroy_window(mlx->mlx, mlx->win);
			mlx->win = NULL;
		}
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		mlx->mlx = NULL;
	}
	if (msg)
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
