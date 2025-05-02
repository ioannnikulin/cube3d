/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_rotations_w.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:28:43 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/20 16:34:13 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	ft_point_rot_x_here(t_point *a, double angle)
{
	return (ft_point_cp(ft_point_rot_x(a, angle), a));
}

void	ft_point_rot_y_here(t_point *a, double angle)
{
	return (ft_point_cp(ft_point_rot_y(a, angle), a));
}

void	ft_point_rot_z_here(t_point *a, double angle)
{
	return (ft_point_cp(ft_point_rot_z(a, angle), a));
}

void	ft_point_rot_here(t_point *a, double angle)
{
	return (ft_point_cp(ft_point_rot(a, angle), a));
}
