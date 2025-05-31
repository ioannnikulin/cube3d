/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:58:29 by iverniho          #+#    #+#             */
/*   Updated: 2025/05/31 12:54:40 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

void	set_direction(t_mlx *game, int to_x, int to_y)
{
	game->player.coords.to.x = to_x;
	game->player.coords.to.y = to_y;
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	verify_texture_file_accessibility(t_mlx *data, char **parts)
{
	int		fd_texture;
	char	*line;

	fd_texture = open(parts[1], O_RDONLY);
	line = get_next_line(fd_texture);
	if (!line)
	{
		free(line);
		data->errno = 1;
		return ;
	}
	free(line);
	if (fd_texture == -1)
	{
		data->errno = 1;
		return ;
	}
	close(fd_texture);
}
