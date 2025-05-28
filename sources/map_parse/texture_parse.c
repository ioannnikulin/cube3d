/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:03:11 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/28 20:58:09 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static char	*trim_and_validate_raw_line(t_mlx *data, char *line, int *errno)
{
	char	*trimmed_line;

	*errno = 1;
	trimmed_line = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed_line)
		finalize(data, "Error: Memory allocation failed for trimmed_line", 1);
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (NULL);
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
		finalize(data, "Error: Memory allocation failed for parts", 1);
	}
	*errno = 0;
	if (!parts[0] || !parts[1] || parts[2] != NULL)
	{
		free_texture_parts(parts);
		free(trimmed_line);
		return (NULL);
	}
	return (parts);
}

static void	**configure_texture_asset(t_mlx *data, char **parts, \
									char *trimmed_line)
{
	void	**img_field_ptr;

	data->errno = 1;
	if (set_texture_target(data, parts[0], &img_field_ptr, parts[1]) == -1)
		return (handle_configure_error(data, parts, trimmed_line, NULL), NULL);
	if (*img_field_ptr != NULL)
		return (handle_configure_error(data, parts, trimmed_line, \
		"Error: Duplicate texture definition"), NULL);
	if (parts[1][0] == '\0')
		return (handle_configure_error(data, parts, trimmed_line, \
		"Error: Empty texture path provided"), NULL);
	data->errno = 0;
	return (img_field_ptr);
}

static void	verify_texture_file_accessibility(t_mlx *data, \
		char **parts, char *trimmed_line)
{
	int	fd_texture;

	fd_texture = open(parts[1], O_RDONLY);
	if (fd_texture == -1)
	{
		free_texture_parts(parts);
		free(trimmed_line);
		close(fd_texture);
		finalize(data, "Invalid texture file path or permissions.", 1);
	}
	close(fd_texture);
}

int	parse_texture_line(t_mlx *data, char *line)
{
	char	*trimmed_line;
	char	**parts;

	trimmed_line = trim_and_validate_raw_line(data, line, &data->errno);
	if (data->errno)
		return (free(trimmed_line), 0);
	parts = split_trimmed_line(data, trimmed_line, &data->errno);
	if (data->errno)
		return (free(trimmed_line), 0);
	if (!parts || (ft_strcmp(parts[0], "NO") != 0 && \
		ft_strcmp(parts[0], "SO") != 0 && \
		ft_strcmp(parts[0], "WE") != 0 && \
		ft_strcmp(parts[0], "EA") != 0))
	{
		if (parts && parts[0])
			if (ft_strcmp(parts[0], "C") != 0 || ft_strcmp(parts[0], "F") != 0)
				free(trimmed_line);
		return (free_texture_parts(parts), -1);
	}
	configure_texture_asset(data, parts, trimmed_line);
	if (data->errno)
		return (free(trimmed_line), 0);
	verify_texture_file_accessibility(data, parts, trimmed_line);
	free_texture_parts(parts);
	return (free(trimmed_line), 1);
}
