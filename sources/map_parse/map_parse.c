/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanvernihora <ivanvernihora@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 22:25:54 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/03/29 22:51:27 by ivanverniho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"




static int	check_extention(char *map)
{
	int	i;

	i = 0;
	if (ft_strchr(map, '.') == 0)
		return (printf("Error\nInvalid map extension\n"), 0);
	while (map[i])
	{
		if (map[i] == '.')
		{
			if (!(map[i + 1] == 'c' && map[i + 2] == 'u' \
			&& map[i + 3] == 'b' && !(map[i + 4])))
				return (printf("Error\nInvalid map extension\n"), 0);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int parse_map(char *map)
{
    int res;
    res = check_extention(map);
	if (res == 0)
		return (printf("Error\nInvalid map extension\n"), 0);
    else
        return (printf("Success\n"),1);
	
}