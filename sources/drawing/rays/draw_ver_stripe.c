/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ver_stripe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:26:58 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/10 19:35:45 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rays_internal.h"

static void	ceiling(int col, t_ray_arg *arg)
{
	arg->cast.col[0] = ft_point_make(arg->cast.bigmap_left_top.x
			+ BIGMAP_COL_WIDTH * col, 0);
	arg->cast.col[1] = ft_point_make(arg->cast.bigmap_left_top.x
			+ BIGMAP_COL_WIDTH * (col + 1), 0);
	arg->cast.col[2] = ft_point_make(arg->cast.bigmap_left_top.x
			+ BIGMAP_COL_WIDTH * (col + 1), arg->cast.wall_ver_offset);
	arg->cast.col[3] = ft_point_make(arg->cast.bigmap_left_top.x
			+ BIGMAP_COL_WIDTH * col, arg->cast.wall_ver_offset);
	arg->cast.color = arg->mlx->map.ceiling.color;
	quadrangle(arg->mlx,
		quadrangle_vertices(&arg->cast.col[0], &arg->cast.col[1],
			&arg->cast.col[2], &arg->cast.col[3]),
		&arg->cast.color, true);
	ft_point_cp(arg->cast.col[3], &arg->cast.wall_from[0]);
	ft_point_cp(arg->cast.col[3], &arg->cast.wall_to[0]);
	arg->cast.wall_to[0].y += arg->cast.wall_height;
	ft_point_cp(arg->cast.col[2], &arg->cast.wall_from[1]);
	ft_point_cp(arg->cast.col[2], &arg->cast.wall_to[1]);
	arg->cast.wall_to[1].y += arg->cast.wall_height;
}

static void	texture_coord(t_ray_arg *arg)
{
	arg->cast.tex_row = arg->cast.tex_offset * arg->cast.tex_row_step;
	if (ft_point_dist(&arg->tgt_isect, &arg->hor_isect) < EPSILON)
	{
		if (arg->mlx->player.coords.from.y < arg->tgt_isect.y)
			arg->cast.tgt_tex = &arg->mlx->assets.wall_south;
		else
			arg->cast.tgt_tex = &arg->mlx->assets.wall_north;
	}
	else
	{
		if (arg->mlx->player.coords.from.x < arg->tgt_isect.x)
			arg->cast.tgt_tex = &arg->mlx->assets.wall_east;
		else
			arg->cast.tgt_tex = &arg->mlx->assets.wall_west;
	}
	if (ft_point_dist(&arg->tgt_isect, &arg->hor_isect) < EPSILON)
		arg->cast.tex_col = (int)(arg->tgt_isect.x)
			% arg->cast.tgt_tex->width;
	else
		arg->cast.tex_col = (int)(arg->tgt_isect.y)
			% arg->cast.tgt_tex->width;
}

static void	wall(t_ray_arg *arg)
{
	int	row;

	arg->cast.col[0].y = arg->cast.wall_from[0].y;
	arg->cast.col[1].y = arg->cast.wall_from[1].y;
	arg->cast.col[2].y = arg->cast.col[1].y + 1;
	arg->cast.col[3].y = arg->cast.col[0].y + 1;
	texture_coord(arg);
	row = -1;
	while (++row < arg->cast.wall_height)
	{
		arg->cast.color = get_pixel_color(arg->cast.tgt_tex->img,
				arg->cast.tex_col, arg->cast.tex_row);
		quadrangle(arg->mlx,
			quadrangle_vertices(&arg->cast.col[0], &arg->cast.col[1],
				&arg->cast.col[2], &arg->cast.col[3]),
			&arg->cast.color, true);
		arg->cast.col[0].y += 1;
		arg->cast.col[1].y += 1;
		arg->cast.col[2].y += 1;
		arg->cast.col[3].y += 1;
		arg->cast.tex_row += arg->cast.tex_row_step;
	}
}

static void	flr(t_ray_arg *arg)
{
	arg->cast.col[0].y = arg->cast.wall_to[0].y;
	arg->cast.col[1].y = arg->cast.wall_to[1].y;
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
	arg->cast.tex_row_step = ((double)arg->mlx->assets.wall_north.height)
		/ arg->cast.wall_height;
	arg->cast.tex_offset = 0;
	if (arg->cast.wall_height > MAX_WALL_HEIGHT)
	{
		arg->cast.tex_offset = (arg->cast.wall_height - MAX_WALL_HEIGHT) / 2.0;
		arg->cast.wall_height = MAX_WALL_HEIGHT;
	}
	arg->cast.wall_ver_offset = (WINDOW_HEIGHT - arg->cast.wall_height) / 2.0;
	ceiling(i, arg);
	wall(arg);
	flr(arg);
}
