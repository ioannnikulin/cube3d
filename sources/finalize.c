/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:38:28 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/27 20:15:08 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_img(t_mlx *mlx, t_img *img)
{
	if (img)
	{
		if (img->path)
			free(img->path);
		if (img->img)
			mlx_destroy_image(mlx->mlx, img->img);
		img->img = 0;
		img->path = 0;
	}
}

int	finalize(t_mlx *mlx, char *msg, int ret)
{
	if (mlx)
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		if (mlx->map.map)
			free_map(mlx->map.map);
		free_img(mlx->mlx, &mlx->assets.wall_east);
		free_img(mlx->mlx, &mlx->assets.wall_west);
		free_img(mlx->mlx, &mlx->assets.wall_north);
		free_img(mlx->mlx, &mlx->assets.wall_south);
		if (mlx->frame.imgs)
		{
			int	i;

			i = -1;
			while (++i < FRAMES_BUFFER)
			{
				if (mlx->frame.imgs[i])
					free(mlx->frame.imgs[i]);
			}
			free(mlx->frame.imgs);
			i = -1;
			while (++i < FRAMES_BUFFER)
			{
				if (mlx->frame.imgs_data[i])
					free(mlx->frame.imgs_data[i]);
			}
			free(mlx->frame.imgs_data);

		}
		if (mlx->mlx && mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		if (mlx->mlx)
			mlx_destroy_display(mlx->mlx);
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
