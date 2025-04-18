/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:27:52 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/18 21:37:07 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
}	t_point;

typedef struct s_vector
{
	t_point	from;
	t_point	to;
}	t_vector;

t_vector	ft_vector_add(t_vector *a, t_vector *b);
t_vector	ft_vector_make(t_point from, t_point to);
void		ft_swap_pts(t_point **a, t_point **b);
t_point		ft_point_make(double x, double y);

#endif