/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:55:59 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/10 19:19:21 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rays_internal.h"

static int	calc_ray(t_ray_arg *arg)
{
	hor_isect(arg);
	ver_isect(arg);
	if (ft_point_dist(&arg->ray.from, &arg->hor_isect)
		> ft_point_dist(&arg->ray.from, &arg->ver_isect))
		arg->tgt_isect = arg->ver_isect;
	else
		arg->tgt_isect = arg->hor_isect;
	ft_vector_rot_z_here(&arg->ray, arg->angle_delta);
	return (0);
}

int	cast_rays(t_mlx *mlx)
{
	t_ray_arg	arg;
	int			i;

	i = -1;
	arg = ray_arg(mlx);
	arg.ray = mlx->player.coords;
	calc_ray(&arg);
	mlx->player.to_wall_ahead = ft_point_dist(&arg.ray.from, &arg.tgt_isect);
	ft_vector_rot_z_here(&arg.ray, M_PI);
	calc_ray(&arg);
	mlx->player.to_wall_behind = ft_point_dist(&arg.ray.from, &arg.tgt_isect);
	arg.angle_delta = VIEWFIELD / RAYS_COUNT * DEGREE;
	ft_vector_rot_z_here(&arg.ray, M_PI + arg.angle);
	while (++ i < RAYS_COUNT)
	{
		calc_ray(&arg);
		if (i % MINIMAP_SHOW_EACH_TH_RAY == 0)
			line(arg.mlx, &arg.ray.from, &arg.tgt_isect,
				&arg.mlx->assets.palette.green);
		draw_ver_stripe(i, &arg);
	}
	return (0);
}

static void	cast_arg(t_mlx *mlx, t_ray_arg *arg)
{
	arg->cast.bigmap_left_top = ft_point_make(mlx->map.map_width * BLOCK_SIZE,
			0);
	arg->cast.tgt_isect_dist = 0;
	arg->cast.wall_height = 0;
	arg->cast.wall_ver_offset = 0;
	arg->cast.color = mlx->assets.palette.red;
	arg->cast.wall_from[0] = ft_point_make(0, 0);
	arg->cast.wall_from[1] = ft_point_make(0, 0);
	arg->cast.wall_to[0] = ft_point_make(0, 0);
	arg->cast.wall_to[1] = ft_point_make(0, 0);
	arg->cast.tex_row_step = 0;
	arg->cast.tex_row = 0;
	arg->cast.tex_col = 0;
	arg->cast.tex_offset = 0;
	arg->cast.tgt_tex = mlx->assets.wall_north.img;
}

t_ray_arg	ray_arg(t_mlx *mlx)
{
	t_ray_arg	arg;

	arg.ray = ft_vector_make(ft_point_make(0, 0), ft_point_make(0, 0));
	arg.hor_isect = ft_point_make(0, 0);
	arg.ver_isect = ft_point_make(0, 0);
	arg.tgt_isect = ft_point_make(0, 0);
	arg.x_offset = 0;
	arg.y_offset = 0;
	arg.lvl_iter = 0;
	arg.map_x = 0;
	arg.map_y = 0;
	arg.angle = -VIEWFIELD / 2 * DEGREE;
	arg.angle_delta = 0;
	arg.mlx = mlx;
	cast_arg(mlx, &arg);
	return (arg);
}
