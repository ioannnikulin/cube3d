/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ver_isect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:55:59 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/11 14:46:03 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rays_internal.h"

static int	ray_vertical(t_ray_arg *arg)
{
	arg->ver_isect.y = ft_if_d(arg->ray.from.y < arg->ray.to.y,
			arg->mlx->map.map_height * MINIMAP_BLOCK_SIZE, 0);
	arg->ver_isect.x = arg->ray.from.x;
	arg->lvl_iter = arg->mlx->map.map_width;
	return (0);
}

static int	ray_left(t_ray_arg *arg)
{
	arg->ver_isect.x = (((int)arg->ray.from.x) / MINIMAP_BLOCK_SIZE)
		* MINIMAP_BLOCK_SIZE - 0.0001;
	arg->ver_isect.y = (arg->ver_isect.x - arg->ray.from.x)
		* ft_vector_y(&arg->ray) / ft_vector_x(&arg->ray) + arg->ray.from.y;
	arg->x_offset = -MINIMAP_BLOCK_SIZE;
	arg->y_offset = MINIMAP_BLOCK_SIZE * ft_vector_y(&arg->ray)
		/ fabs(ft_vector_x(&arg->ray));
	if (ft_vector_x(&arg->ray) == 0)
		arg->y_offset = 0;
	return (0);
}

static int	ray_right(t_ray_arg *arg)
{
	arg->ver_isect.x = (((int)arg->ray.from.x) / MINIMAP_BLOCK_SIZE + 1) * (MINIMAP_BLOCK_SIZE);
	arg->ver_isect.y = (arg->ver_isect.x - arg->ray.from.x)
		* ft_vector_y(&arg->ray) / ft_vector_x(&arg->ray) + arg->ray.from.y;
	arg->x_offset = MINIMAP_BLOCK_SIZE;
	arg->y_offset = MINIMAP_BLOCK_SIZE * ft_vector_y(&arg->ray)
		/ ft_vector_x(&arg->ray);
	if (ft_vector_x(&arg->ray) == 0)
		arg->y_offset = 0;
	return (0);
}

static int	out_of_bounds(t_ray_arg *arg)
{
	if (arg->ver_isect.x < 0
		|| arg->ver_isect.x >= arg->mlx->map.map_width * MINIMAP_BLOCK_SIZE
		|| arg->ver_isect.y < 0
		|| arg->ver_isect.y >= arg->mlx->map.map_height * MINIMAP_BLOCK_SIZE)
		return (1);
	return (0);
}

/*
 * intersection of the ray with the next vertical line
 */
int	ver_isect(t_ray_arg *arg)
{
	arg->lvl_iter = 0;
	if (fabs(ft_vector_x(&arg->ray)) < EPSILON)
		ray_vertical(arg);
	else if (arg->ray.to.x < arg->ray.from.x)
		ray_left(arg);
	else if (arg->ray.to.x > arg->ray.from.x)
		ray_right(arg);
	while (arg->lvl_iter < arg->mlx->map.map_width)
	{
		if (out_of_bounds(arg))
			break ;
		arg->map_x = (int)arg->ver_isect.x / MINIMAP_BLOCK_SIZE;
		arg->map_y = (int)arg->ver_isect.y / MINIMAP_BLOCK_SIZE;
		if (arg->mlx->map.map[arg->map_y][arg->map_x] == '1')
			break ;
		arg->ver_isect.x += arg->x_offset;
		arg->ver_isect.y += arg->y_offset;
		arg->lvl_iter ++;
	}
	return (0);
}
