/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:23:13 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/09 16:07:53 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_internal.h"
#include <math.h>

double	flr(double c)
{
	return ((int)c);
}

double	fpart(double c)
{
	return (c - flr(c));
}

double	rfpart(double c)
{
	return (1.0 - fpart(c));
}

double	rnd(double c)
{
	return (flr(c + 0.5));
}
