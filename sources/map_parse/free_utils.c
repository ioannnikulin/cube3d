/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:13:46 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/27 17:23:11 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

// probably ft_free can be reused instead of some custom functions

void	free_passed_array(int **passed, int height)
{
	int	i;

	i = -1;
	while (++i < height)
		free(passed[i]);
	free(passed);
}

void	free_color_parts(char **parts)
{
	int	k;

	k = 0;
	if (parts)
	{
		while (parts[k])
		{
			free(parts[k]);
			k++;
		}
		free(parts);
	}
}

void	free_instructions(char **instructions, int count)
{
	int	i;

	i = 0;
	if (!instructions)
		return ;
	while (i < count && instructions[i] != NULL)
	{
		free(instructions[i]);
		i++;
	}
	while (instructions[i] != NULL)
	{
		free(instructions[i]);
		i++;
	}
	free(instructions);
}

void	free_assets(t_mlx *data)
{
	free(data->assets.wall_north.img);
	free(data->assets.wall_south.img);
	free(data->assets.wall_west.img);
	free(data->assets.wall_east.img);
}