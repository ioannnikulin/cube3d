/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:27:52 by inikulin          #+#    #+#             */
/*   Updated: 2025/03/24 19:35:09 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

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

t_vector	vector_add(t_vector *a, t_vector *b);

#endif