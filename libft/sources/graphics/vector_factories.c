/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_factories.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:28:51 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/25 19:44:29 by inikulin         ###   ########.fr       */
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

t_vector	*ft_vector_dup(t_vector src)
{
	t_vector	*res;

	res = ft_calloc_if(sizeof(t_vector), 1);
	if (!res)
		return (0);
	ft_vector_cp(src, res);
	return (res);
}

void	ft_vector_cp(t_vector from, t_vector *to)
{
	to->from = from.from;
	to->to = from.to;
}
