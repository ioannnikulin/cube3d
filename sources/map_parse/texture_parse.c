/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:03:11 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/27 20:58:13 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static char	*trim_and_validate_raw_line(char *line, int *errno)
{
	char	*trimmed_line;

	*errno = 1;
	trimmed_line = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed_line)
		exit_error("Error: Memory allocation failed for trimmed_line");
		// finalize?
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (NULL);
	}
	*errno = 0;
	return (trimmed_line);
}

static char	**split_trimmed_line(char *trimmed_line, int *errno)
{
	char	**parts;

	*errno = 1;
	parts = ft_split(trimmed_line, ' ', 0);
	if (!parts)
	{
		free(trimmed_line);
		exit_error("Error: Memory allocation failed for parts");
		// finalize?
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
		return (handle_configure_error(parts, trimmed_line, NULL), NULL);
	if (*img_field_ptr != NULL)
		return (handle_configure_error(parts, trimmed_line, \
		"Error: Duplicate texture definition"), NULL);
	if (parts[1][0] == '\0')
		return (handle_configure_error(parts, trimmed_line, \
		"Error: Empty texture path provided"), NULL);
	// *img_field_ptr = ft_strdup(parts[1]); // you had the pointer to where the texture should be stored here. now you've lost it. why this strdup? you have the path in another field anyway
	*img_field_ptr = parts[1];
	if (!*img_field_ptr)
		return (handle_configure_error(parts, trimmed_line, \
		"Error: Failed to duplicate texture path"), NULL);
	data->errno = 0;
	return (img_field_ptr);
}

static void	verify_texture_file_accessibility(char **parts, char *trimmed_line)
{
	int	fd_texture;

	fd_texture = open(parts[1], O_RDONLY);
	if (fd_texture == -1)
	{
		free_texture_parts(parts);
		free(trimmed_line);
		exit_error("Invalid texture file path or permissions.");
		// finalize?

	}
	close(fd_texture);
}

int	parse_texture_line(t_mlx *data, char *line)
{
	char	*trimmed_line;
	char	**parts;
	// void	**img_field_ptr;

	trimmed_line = trim_and_validate_raw_line(line, &data->errno);
	if (data->errno) {
		// free(trimmed_line);
		return (0);
	}
	parts = split_trimmed_line(trimmed_line, &data->errno);
	if (data->errno) {
		// free(trimmed_line);
		return (0);
	}
	if (!parts || (ft_strcmp(parts[0], "NO") != 0 && \
		ft_strcmp(parts[0], "SO") != 0 && \
		ft_strcmp(parts[0], "WE") != 0 && \
		ft_strcmp(parts[0], "EA") != 0))
	{
		return (-1);
	}
	configure_texture_asset(data, parts, trimmed_line);
	if (data->errno) {
		// free_texture_parts(parts);

		// free(trimmed_line);
		return (0);
	}
	verify_texture_file_accessibility( parts, trimmed_line);
	// convert_texture_to_image(data);
	free_texture_parts(parts);
	free(trimmed_line);
	return (1);
}
