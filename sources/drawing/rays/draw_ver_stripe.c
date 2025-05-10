/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ver_stripe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:26:58 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/10 13:04:47 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rays_internal.h"

static void	ceiling(int i, t_ray_arg *arg)
{
	arg->cast.col[0] = ft_point_make(arg->cast.bigmap_left_top.x
			+ BIGMAP_COL_WIDTH * i, 0);
	arg->cast.col[1] = ft_point_make(arg->cast.bigmap_left_top.x
			+ BIGMAP_COL_WIDTH * (i + 1), 0);
	arg->cast.col[2] = ft_point_make(arg->cast.bigmap_left_top.x
			+ BIGMAP_COL_WIDTH * (i + 1), arg->cast.wall_ver_offset);
	arg->cast.col[3] = ft_point_make(arg->cast.bigmap_left_top.x
			+ BIGMAP_COL_WIDTH * i, arg->cast.wall_ver_offset);
	arg->cast.color = arg->mlx->map.ceiling.color;
	quadrangle(arg->mlx,
		quadrangle_vertices(&arg->cast.col[0], &arg->cast.col[1],
			&arg->cast.col[2], &arg->cast.col[3]),
		&arg->cast.color, true);
}

static void	wall(t_ray_arg *arg)
{
	arg->cast.col[0].y = arg->cast.wall_ver_offset;
	arg->cast.col[1].y = arg->cast.wall_ver_offset;
	arg->cast.col[2].y += arg->cast.wall_height;
	arg->cast.col[3].y += arg->cast.wall_height;
	arg->cast.color = arg->mlx->assets.palette.red;
	if (ft_point_dist(&arg->tgt_isect, &arg->hor_isect) < EPSILON)
		arg->cast.color = arg->mlx->assets.palette.dark_red;
	quadrangle(arg->mlx,
		quadrangle_vertices(&arg->cast.col[0], &arg->cast.col[1],
			&arg->cast.col[2], &arg->cast.col[3]),
		&arg->cast.color, true);
}

static void	flr(t_ray_arg *arg)
{
	arg->cast.col[0].y += arg->cast.wall_height;
	arg->cast.col[1].y += arg->cast.wall_height;
	arg->cast.col[2].y = WINDOW_HEIGHT;
	arg->cast.col[3].y = WINDOW_HEIGHT;
	arg->cast.color = arg->mlx->map.floor.color;
	quadrangle(arg->mlx,
		quadrangle_vertices(&arg->cast.col[0], &arg->cast.col[1],
			&arg->cast.col[2], &arg->cast.col[3]),
		&arg->cast.color, true);
}

void	draw_ver_stripe(int i, t_ray_arg *arg)
{
	arg->cast.angle_dif = arg->angle_delta * abs(RAYS_COUNT / 2 - i);
	arg->cast.tgt_isect_dist = ft_point_dist(&arg->ray.from, &arg->tgt_isect)
		* cos(arg->cast.angle_dif);
	arg->cast.wall_height = arg->mlx->map.map_height * arg->mlx->map.map_width
		* MAX_WALL_HEIGHT / arg->cast.tgt_isect_dist;
	if (arg->cast.wall_height > MAX_WALL_HEIGHT)
		arg->cast.wall_height = MAX_WALL_HEIGHT;
	arg->cast.wall_ver_offset = (WINDOW_HEIGHT - arg->cast.wall_height) / 2.0;
	ceiling(i, arg);
	wall(arg);
	flr(arg);
}
