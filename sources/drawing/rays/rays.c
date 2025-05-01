/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:55:59 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/01 16:16:16 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rays_internal.h"

static int	cast_ray(t_ray_arg *arg)
{
	hor_isect(arg);
	ver_isect(arg);
	if (ft_point_dist(&arg->ray.from, &arg->hor_isect)
		> ft_point_dist(&arg->ray.from, &arg->ver_isect))
		line(arg->mlx, &arg->ray.from, &arg->ver_isect, &arg->mlx->assets.palette.green);
	else
		line(arg->mlx, &arg->ray.from, &arg->hor_isect, &arg->mlx->assets.palette.green);
	return (0);
}

int	cast_rays(t_mlx *mlx)
{
	t_ray_arg	arg;
	int			i;

	i = -1;
	arg = ray_arg(mlx);
	arg.ray = mlx->player.coords;
	printf("player at %f %f, facing %f %f\n", arg.ray.from.x, arg.ray.from.y,
		arg.ray.to.x, arg.ray.to.y);
	while (++ i < RAYS_COUNT)
		cast_ray(&arg);
	return (0);
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
	arg.mlx = mlx;
	return (arg);
}
