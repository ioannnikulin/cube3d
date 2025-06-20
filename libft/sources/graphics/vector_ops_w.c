/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops_w.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:54:57 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/31 15:15:54 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	ft_vector_translate_here(t_vector *a, t_point *b)
{
	return (ft_vector_cp(ft_vector_translate(a, b), a));
}

void	ft_vector_move_here(t_vector *a, double b)
{
	return (ft_vector_cp(ft_vector_move(a, b), a));
}

void	ft_vector_rot_here(t_vector *a, double b)
{
	return (ft_vector_rot_z_here(a, b));
}

void	ft_vector_rot_z_here(t_vector *a, double b)
{
	return (ft_vector_cp(ft_vector_rot_z(a, b), a));
}
