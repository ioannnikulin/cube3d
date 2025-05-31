/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:58:29 by iverniho          #+#    #+#             */
/*   Updated: 2025/05/31 17:10:55 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

int	dd_array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	set_direction(t_mlx *game, int to_x, int to_y)
{
	game->player.coords.to.x = to_x;
	game->player.coords.to.y = to_y;
}

int	is_number_parse(char *str)
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

int	is_number(char *str)
{
	int		i;
	int		is_already_trimmed;
	int		out_len;
	int		input_len;
	char	*trimmed_str;

	i = 0;
	out_len = 0;
	is_already_trimmed = 0;
	trimmed_str = ft_strtrim(str, " \t\n\v\f\r");
	input_len = (int)ft_strlen(trimmed_str);
	while (str[i])
	{
		while (ft_strchr(" \t\n\v\f\r", str[i]) && !is_already_trimmed)
			i++;
		is_already_trimmed = 1;
		if (!ft_isdigit(str[i]))
			return (free(trimmed_str), 0);
		out_len++;
		i++;
	}
	free(trimmed_str);
	if (out_len != input_len)
		return (0);
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
