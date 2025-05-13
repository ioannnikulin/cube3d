/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:13:28 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/13 19:22:14 by ivanverniho      ###   ########.fr       */
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

static t_color	clr(unsigned char r, unsigned char g, unsigned char b, double a)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.alpha = a;
	return (color);
}

static void	palette_init(t_palette *palette)
{
	palette->black = clr(0, 0, 0, 0);
	palette->white = clr(255, 255, 255, 0);
	palette->red = clr(255, 0, 0, 0);
	palette->green = clr(0, 255, 0, 0);
	palette->blue = clr(0, 0, 255, 0);
	palette->yellow = clr(255, 255, 0, 0);
	palette->cyan = clr(0, 255, 255, 0);
	palette->magenta = clr(255, 0, 255, 0);
}

int	pre(t_mlx *mlx)
{
	
	// ft_bzero((void *)mlx, sizeof(t_mlx));
	mlx->dbg = 1;
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
	palette_init(&mlx->assets.palette);
	return (0);
}
