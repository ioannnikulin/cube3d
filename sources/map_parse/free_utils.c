/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:13:46 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/27 20:03:45 by iverniho         ###   ########.fr       */
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

void	free_texture_parts(char **parts)
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
	free_img(data, &data->assets.wall_north);
	free_img(data, &data->assets.wall_south);
	free_img(data, &data->assets.wall_east);
	free_img(data, &data->assets.wall_west);
}
