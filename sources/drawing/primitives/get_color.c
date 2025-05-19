/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:17:23 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/19 06:12:52 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../drawing.h"

static t_color	impl(char *data_addr, int offset, int endian)
{
	t_color	color;

	if (endian == 0)
	{
		color.b = (unsigned char)data_addr[offset];
		color.g = (unsigned char)data_addr[offset + 1];
		color.r = (unsigned char)data_addr[offset + 2];
	}
	else
	{
		color.r = (unsigned char)data_addr[offset];
		color.g = (unsigned char)data_addr[offset + 1];
		color.b = (unsigned char)data_addr[offset + 2];
	}
	return (color);
}

t_color	get_pixel_color(void *img, int x, int y)
{
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		offset;

	data_addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	offset = (y * size_line) + (x * (bpp / 8));
	return (impl(data_addr, offset, endian));
}
