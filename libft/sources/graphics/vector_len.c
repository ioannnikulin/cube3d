/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:09:45 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/21 12:10:24 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

double		ft_vector_len(t_vector *a)
{
	double		len;
	t_point		dir;

	dir = ft_point_sub(&a->to, &a->from);
	len = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
	return (len);
}

double		ft_vector_x(t_vector *a)
{
	t_point		dir;

	dir = ft_point_sub(&a->to, &a->from);
	return (dir.x);
}

double		ft_vector_y(t_vector *a)
{
	t_point		dir;

	dir = ft_point_sub(&a->to, &a->from);
	return (dir.y);
}

double		ft_vector_z(t_vector *a)
{
	t_point		dir;

	dir = ft_point_sub(&a->to, &a->from);
	return (dir.z);
}