/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_rotations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:23:49 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/25 19:41:57 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_point	ft_point_rot_x(t_point *a, double angle)
{
	t_point	res;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	res.x = a->x;
	res.y = a->y * cos_a - a->z * sin_a;
	res.z = a->y * sin_a + a->z * cos_a;
	return (res);
}

t_point	ft_point_rot_y(t_point *a, double angle)
{
	t_point	res;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	res.x = a->x * cos_a + a->z * sin_a;
	res.y = a->y;
	res.z = -a->x * sin_a + a->z * cos_a;
	return (res);
}

t_point	ft_point_rot_z(t_point *a, double angle)
{
	t_point	res;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	res.x = a->x * cos_a - a->y * sin_a;
	res.y = a->x * sin_a + a->y * cos_a;
	res.z = a->z;
	return (res);
}

t_point	ft_point_rot(t_point *a, double angle)
{
	return (ft_point_rot_z(a, angle));
}
