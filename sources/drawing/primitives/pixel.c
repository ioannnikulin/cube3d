/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/10 14:17:15 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_internal.h"

t_color	color(t_color *clr, double alpha)
{
	t_color	res;

	res.r = clr->r * alpha;
	res.g = clr->g * alpha;
	res.b = clr->b * alpha;
	res.alpha = alpha;
	return (res);
}

void	pixel(t_mlx *mlx, int x, int y, t_color clr)
{
	int		tgt;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return ;
	tgt = y * mlx->frame.linesz + x * mlx->frame.bpp / 8;
	(*next_img_data(mlx))[tgt + mlx->frame.red_offset] = clr.r;
	(*next_img_data(mlx))[tgt + mlx->frame.green_offset] = clr.g;
	(*next_img_data(mlx))[tgt + mlx->frame.blue_offset] = clr.b;
}