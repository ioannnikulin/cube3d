/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_ops_w.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:28:43 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/20 16:34:04 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"


void	ft_point_add_here(t_point *a, t_point *b)
{
	return (ft_point_cp(ft_point_add(a, b), a));
}

void	ft_point_sub_here(t_point *a, t_point *b)
{
	return (ft_point_cp(ft_point_sub(a, b), a));
}

void	ft_point_scale_here(t_point *a, double b)
{
	return (ft_point_cp(ft_point_scale(a, b), a));
}

void	ft_point_norm_here(t_point *a)
{
	return (ft_point_cp(ft_point_norm(a), a));
}
