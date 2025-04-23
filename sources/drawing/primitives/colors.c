/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:43:48 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/19 01:00:08 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../drawing.h"

t_color	clr_black(void)
{
	t_color	clr;

	clr.r = 0;
	clr.g = 0;
	clr.b = 0;
	clr.alpha = 0;
	return (clr);
}

t_color	clr_white(void)
{
	t_color	clr;

	clr.r = 255;
	clr.g = 255;
	clr.b = 255;
	clr.alpha = 0;
	return (clr);
}
