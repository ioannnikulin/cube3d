/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:28:51 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/26 12:22:16 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_vector_move(t_vector *a, double b)
{
	t_vector	res;
	t_point		dir;
	t_point		mov;

	dir = ft_point_sub(&a->to, &a->from);
	dir = ft_point_norm(&dir);
	mov = ft_point_scale(&dir, b);
	res.from = ft_point_add(&a->from, &mov);
	res.to = ft_point_add(&a->to, &mov);
	return (res);
}

t_vector	ft_vector_rot_z(t_vector *a, double b)
{
	t_point		dir;
	t_vector	res;

	dir = ft_point_sub(&a->to, &a->from);
	dir = ft_point_rot_z(&dir, b);
	res.from = a->from;
	res.to = ft_point_add(&a->from, &dir);
	return (res);
}

t_vector	ft_vector_rot(t_vector *a, double b)
{
	return (ft_vector_rot_z(a, b));
}

bool	ft_vector_eq(t_vector *a, t_vector *b, double epsilon)
{
	return (ft_point_eq(&a->from, &b->from, epsilon)
		&& ft_point_eq(&a->to, &b->to, epsilon));
}
