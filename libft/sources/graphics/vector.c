/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:28:51 by inikulin          #+#    #+#             */
/*   Updated: 2025/03/24 19:41:52 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	vector_add(t_vector *a, t_vector *b)
{
	t_vector	res;

	res.from.x = a->from.x;
	res.from.y = a->from.y;
	res.to.x = a->to.x + b->to.x - b->from.x;
	res.to.y = a->to.y + b->to.y - b->from.y;
	return (res);
}
