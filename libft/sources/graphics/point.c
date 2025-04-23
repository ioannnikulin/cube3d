/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:23:49 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/18 21:27:31 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_point	ft_point_make(double x, double y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = 0;
	return (p);
}

void	ft_swap_pts(t_point **a, t_point **b)
{
	t_point	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
