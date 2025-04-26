/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:23:49 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/26 12:38:20 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#define EPSILON 1e-6

t_point	ft_point_add(t_point *a, t_point *b)
{
	t_point	res;

	res.x = a->x + b->x;
	res.y = a->y + b->y;
	res.z = a->z + b->z;
	return (res);
}

t_point	ft_point_sub(t_point *a, t_point *b)
{
	t_point	res;

	res.x = a->x - b->x;
	res.y = a->y - b->y;
	res.z = a->z - b->z;
	return (res);
}

t_point	ft_point_scale(t_point *a, double b)
{
	t_point	res;

	res.x = a->x * b;
	res.y = a->y * b;
	res.z = a->z * b;
	return (res);
}

t_point	ft_point_norm(t_point *a)
{
	double	mag;
	t_point	res;

	mag = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	if (fabs(mag) < EPSILON)
		mag = 0;
	res.x = ft_if_d(mag == 0, 0, a->x / mag);
	res.y = ft_if_d(mag == 0, 0, a->y / mag);
	res.z = ft_if_d(mag == 0, 0, a->z / mag);
	return (res);
}

bool	ft_point_eq(t_point *a, t_point *b, double epsilon)
{
	bool	eq[3];

	eq[0] = fabs(a->x - b->x) < epsilon;
	eq[1] = fabs(a->y - b->y) < epsilon;
	eq[2] = fabs(a->z - b->z) < epsilon;
	return (eq[0] && eq[1] && eq[2]);
}
