/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_factories.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:23:49 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/20 17:00:40 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_point	ft_point_make(double x, double y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = 0;
	return (p);
}

t_point		*ft_point_dup(t_point src)
{
	t_point	*dup;

	dup = ft_calloc_if(sizeof(t_point), 1);
	if (!dup)
		return (0);
	ft_point_cp(src, dup);
	return (dup);
}

void	ft_swap_pts(t_point **a, t_point **b)
{
	t_point	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_point_cp(t_point from, t_point *to)
{
	to->x = from.x;
	to->y = from.y;
	to->z = from.z;
}
