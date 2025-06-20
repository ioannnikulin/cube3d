/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:03:11 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/30 15:38:34 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static char	*trim_and_valid_line(t_mlx *data, char *line, int *errno,
										char **instructions)
{
	char	*trimmed_line;

	*errno = 1;
	trimmed_line = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed_line)
	{
		free(line);
		free_2d_array(instructions);
		finalize(data, ERR_MALLOC_INSTRUCTIONS, 1);
	}
	if (trimmed_line[0] == '\0')
	{
		free(line);
		free_2d_array(instructions);
		free(trimmed_line);
		finalize(data, ERR_INVALID_TEXTURE, 1);
	}
	*errno = 0;
	return (trimmed_line);
}

static char	**split_trimmed_line(t_mlx *data, char *trimmed_line, int *errno)
{
	char	**parts;

	*errno = 1;
	parts = ft_split(trimmed_line, ' ', 0);
	if (!parts)
	{
		free(trimmed_line);
		finalize(data, ERR_MALLOC_INSTRUCTIONS, 1);
	}
	*errno = 0;
	if (!parts[0] || !parts[1] || parts[2] != NULL)
	{
		free_2d_array(parts);
		free(trimmed_line);
		return (NULL);
	}
	return (parts);
}

static void	**configure_texture_asset(t_mlx *data, char **parts,
									char *trimmed_line)
{
	void	**img_field_ptr;

	data->errno = 1;
	if (set_texture_target(data, parts[0], &img_field_ptr, parts[1]) == -1)
		return (handle_configure_error(data, parts, trimmed_line, NULL), NULL);
	if (*img_field_ptr != NULL)
		return (handle_configure_error(data, parts, trimmed_line,
				ERR_DUPLICATE_TEXTURE), NULL);
	if (parts[1][0] == '\0')
		return (handle_configure_error(data, parts, trimmed_line,
				ERR_EMPTY_TEXTURE), NULL);
	data->errno = 0;
	return (img_field_ptr);
}

static int	check_texture_side(char *part)
{
	if ((ft_strcmp(part, "NO") != 0
			&& ft_strcmp(part, "SO") != 0
			&& ft_strcmp(part, "WE") != 0
			&& ft_strcmp(part, "EA") != 0))
		return (0);
	return (1);
}

int	parse_texture_line(t_mlx *data, char *line, char **instructions)
{
	char	*trimmed_line;
	char	**parts;

	trimmed_line = trim_and_valid_line(data, line, &data->errno, instructions);
	if (data->errno)
		return (free(trimmed_line), 0);
	parts = split_trimmed_line(data, trimmed_line, &data->errno);
	if (data->errno)
		return (free(trimmed_line), 0);
	if (!parts || !check_texture_side(parts[0]))
	{
		if (parts && parts[0])
			if (ft_strcmp(parts[0], "C") != 0 || ft_strcmp(parts[0], "F") != 0)
				free(trimmed_line);
		return (free_2d_array(parts), -1);
	}
	verify_texture_file_accessibility(data, parts);
	if (data->errno)
	{
		free_2d_array(parts);
		return (free(trimmed_line), 0);
	}
	configure_texture_asset(data, parts, trimmed_line);
	free_2d_array(parts);
	return (free(trimmed_line), 1);
}
