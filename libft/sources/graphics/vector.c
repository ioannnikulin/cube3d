/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:28:51 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/18 21:37:34 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	ft_vector_make(t_point from, t_point to)
{
	t_vector	res;

	res.from = from;
	res.to = to;
	return (res);
}

t_vector	ft_vector_add(t_vector *a, t_vector *b)
{
	t_vector	res;

	res.from.x = a->from.x;
	res.from.y = a->from.y;
	res.to.x = a->to.x + b->to.x - b->from.x;
	res.to.y = a->to.y + b->to.y - b->from.y;
	return (res);
}
