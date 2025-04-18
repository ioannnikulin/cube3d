/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/11 19:42:06 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_internal.h"

/* 
* leftover from fdf
* not sure if we need it
*/
static int	higher(t_color a, t_color b)
{
	if (b.r == 0 && b.g == 0 && b.b == 0)
		return (1);
	if (a.r == 0 && a.g == 0 && a.b == 0)
		return (0);
	if (*ft_max_dbl(&a.clr, &b.clr) == a.clr
		&& *ft_max_dbl(&a.clr, &b.clr) != b.clr)
		return (1);
	return (0);
}

/*
 * red to white gradient from fdf
 */
t_color	color(double clr, double alpha)
{
	t_color	res;

	res.r = 255 * alpha;
	res.g = 255 * (1 - clr) * alpha;
	res.b = res.g;
	res.clr = clr;
	res.alpha = alpha;
	return (res);
}

void	pixel(t_mlx *mlx, int x, int y, t_color clr)
{
	int		tgt;
	t_color	cur;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return ;
	tgt = y * mlx->frame.linesz + x * mlx->frame.bpp / 8;
	cur.r = (*next_img_data(mlx))[tgt + mlx->frame.red_offset];
	cur.g = (*next_img_data(mlx))[tgt + mlx->frame.green_offset];
	cur.b = (*next_img_data(mlx))[tgt + mlx->frame.blue_offset];
	if (higher(clr, cur))
	{
		(*next_img_data(mlx))[tgt + mlx->frame.red_offset] = clr.r;
		(*next_img_data(mlx))[tgt + mlx->frame.green_offset] = clr.g;
		(*next_img_data(mlx))[tgt + mlx->frame.blue_offset] = clr.b;
	}
}
