/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:55:59 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/29 19:43:31 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"
#include "rays_internal.h"

static int	ray_horizontal(t_ray_arg *arg)
{
	arg->hor_isect.x = ft_if_d(arg->ray.from.x < arg->ray.to.x,
			arg->mlx->map.map_width * BLOCK_SIZE, 0);
	arg->hor_isect.y = arg->ray.from.y;
	arg->lvl_iter = arg->mlx->map.map_height;
	return (0);
}

static int	ray_up(t_ray_arg *arg)
{
	arg->hor_isect.y = (((int)arg->ray.from.y) / BLOCK_SIZE) * BLOCK_SIZE;
	arg->hor_isect.x = (arg->hor_isect.y - arg->ray.from.y)
		* ft_vector_x(&arg->ray) / ft_vector_y(&arg->ray) + arg->ray.from.x;
	arg->y_offset = -BLOCK_SIZE;
	arg->x_offset = BLOCK_SIZE * ft_vector_x(&arg->ray)
		/ fabs(ft_vector_y(&arg->ray));
	if (ft_vector_y(&arg->ray) == 0)
		arg->x_offset = 0;
	return (0);
}

static int	ray_down(t_ray_arg *arg)
{
	arg->hor_isect.y = (((int)arg->ray.from.y) / BLOCK_SIZE + 1) * (BLOCK_SIZE);
	arg->hor_isect.x = (arg->hor_isect.y - arg->ray.from.y)
		* ft_vector_x(&arg->ray) / ft_vector_y(&arg->ray) + arg->ray.from.x;
	arg->y_offset = BLOCK_SIZE;
	arg->x_offset = BLOCK_SIZE * ft_vector_x(&arg->ray)
		/ ft_vector_y(&arg->ray);
	if (ft_vector_y(&arg->ray) == 0)
		arg->x_offset = 0;
	return (0);
}

static int out_of_bounds(t_ray_arg *arg)
{
	if (arg->hor_isect.x < 0
		|| arg->hor_isect.x >= arg->mlx->map.map_width * BLOCK_SIZE
		|| arg->hor_isect.y < 0
		|| arg->hor_isect.y >= arg->mlx->map.map_height * BLOCK_SIZE)
		return (1);
	return (0);
}

/*
 * hor_isect - intersection of the ray with the next horizontal line
 */
static int	cast_ray(t_ray_arg *arg)
{
	if (fabs(ft_vector_y(&arg->ray)) < EPSILON)
		ray_horizontal(arg);
	else if (arg->ray.to.y < arg->ray.from.y)
		ray_up(arg);
	else if (arg->ray.to.y > arg->ray.from.y)
		ray_down(arg);
	while (arg->lvl_iter < arg->mlx->map.map_height)
	{
		arg->map_x = (int)arg->hor_isect.x / BLOCK_SIZE;
		arg->map_y = (int)arg->hor_isect.y / BLOCK_SIZE;
		if (out_of_bounds(arg))
			break ;
		if (arg->mlx->map.map[arg->map_y][arg->map_x] == '1')
			break ;
		arg->hor_isect.x += arg->x_offset;
		arg->hor_isect.y += arg->y_offset;
		arg->lvl_iter ++;
	}
	line(arg->mlx, &arg->ray.from, &arg->hor_isect);
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
	arg.x_offset = 0;
	arg.y_offset = 0;
	arg.lvl_iter = 0;
	arg.map_x = 0;
	arg.map_y = 0;
	arg.mlx = mlx;
	return (arg);
}
