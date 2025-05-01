/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:16:05 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/01 16:11:24 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_INTERNAL_H
# define RAYS_INTERNAL_H
# include "../../cube3d.h"

typedef struct s_ray_arg
{
	t_vector	ray;
	t_point		hor_isect;
	t_point		ver_isect;
	t_point		tgt_isect;
	double		x_offset;
	double		y_offset;
	int			lvl_iter;
	int			map_x;
	int			map_y;
	t_mlx		*mlx;
}	t_ray_arg;

t_ray_arg	ray_arg(t_mlx *mlx);
int 	hor_isect(t_ray_arg *arg);
int 	ver_isect(t_ray_arg *arg);
#endif