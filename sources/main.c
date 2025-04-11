/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:01:39 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/10 18:02:20 by inikulin         ###   ########.fr       */
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

static int	pre(t_mlx *mlx)
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

static int	make_image(t_mlx *mlx)
{
	t_point	p1;
	t_point	p2;

	free(*next_img(mlx));
	*next_img(mlx) = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!*next_img(mlx))
		return (finalize(mlx, ERR_MLX_IMG, 4));
	free(*next_img_data(mlx));
	*next_img_data(mlx) = mlx_get_data_addr(*next_img(mlx), &(mlx->frame.bpp),
		&(mlx->frame.linesz), &(mlx->frame.endian));
	if (!*next_img_data(mlx))
		return (finalize(mlx, ERR_MLX_GETADDR, 5));
	p1 = point(0, 0);
	p2 = point(100, 100);
	line(mlx, &p1, &p2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	(void)argv;
	if (argc != 2)
		return (finalize(NULL, USAGE, 1));
	if (pre(&mlx))
		return (2);
	if (make_image(&mlx))
		return (3);
	mlx_put_image_to_window(mlx.mlx, mlx.win, *next_img(&mlx), 0, 0);
	mlx_key_hook(mlx.win, handle_keyboard, &mlx);
	mlx_hook(mlx.win, 17, 0, close_it, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
