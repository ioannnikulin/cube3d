/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/19 06:18:06 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_internal.h"

// used only for line
t_color	prealpha(t_color *clr, double alpha)
{
	t_color	res;

	res.r = clr->r * alpha;
	res.g = clr->g * alpha;
	res.b = clr->b * alpha;
	res.alpha = alpha;
	return (res);
}

void	pixel(t_mlx *mlx, int x, int y, t_color *clr)
{
	int		tgt;
	t_color	tmp;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return ;
	tgt = y * mlx->frame.linesz + x * mlx->frame.bpp / 8;
	tmp = get_pixel_color(mlx->frame.imgs[mlx->frame.next_frame_idx], x, y);
	tmp.r = (clr->r * clr->alpha + tmp.r * (1 - clr->alpha));
	tmp.g = (clr->g * clr->alpha + tmp.g * (1 - clr->alpha));
	tmp.b = (clr->b * clr->alpha + tmp.b * (1 - clr->alpha));
	(*next_img_data(mlx))[tgt + mlx->frame.red_offset] = tmp.r;
	(*next_img_data(mlx))[tgt + mlx->frame.green_offset] = tmp.g;
	(*next_img_data(mlx))[tgt + mlx->frame.blue_offset] = tmp.b;
}
