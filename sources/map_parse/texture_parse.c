/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:03:11 by ivanverniho       #+#    #+#             */
/*   Updated: 2025/05/27 17:45:20 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inner.h"

static char	*trim_and_validate_raw_line(char *line, int *should_continue)
{
	char	*trimmed_line;

	*should_continue = 0;
	trimmed_line = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed_line)
		exit_error("Error: Memory allocation failed for trimmed_line");
		// finalize?
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (NULL);
	}
	*should_continue = 1;
	return (trimmed_line);
}

static char	**split_trimmed_line(char *trimmed_line, int *should_continue)
{
	char	**parts;

	*should_continue = 0;
	parts = ft_split(trimmed_line, ' ', 0);
	if (!parts)
	{
		free(trimmed_line);
		exit_error("Error: Memory allocation failed for parts");
		// finalize?
	}
	if (!parts[0] || !parts[1] || parts[2] != NULL)
	{
		ft_free_ss_uptonull((void **)parts);
		free(trimmed_line);
		return (NULL);
	}
	*should_continue = 1;
	return (parts);
}

static void	**configure_texture_asset(t_mlx *data, char **parts, \
									char *trimmed_line, int *should_continue)
{
	void	**img_field_ptr;

	*should_continue = 0;
	if (set_texture_target(data, parts[0], &img_field_ptr, parts[1]) == -1)
		return (handle_configure_error(parts, trimmed_line, NULL), NULL);
	if (*img_field_ptr != NULL)
		return (handle_configure_error(parts, trimmed_line, \
		"Error: Duplicate texture definition"), NULL);
	if (parts[1][0] == '\0')
		return (handle_configure_error(parts, trimmed_line, \
		"Error: Empty texture path provided"), NULL);
	*img_field_ptr = ft_strdup(parts[1]); // you had the pointer to where the texture should be stored here. now you've lost it. why this strdup? you have the path in another field anyway
	if (!*img_field_ptr)
		return (handle_configure_error(parts, trimmed_line, \
		"Error: Failed to duplicate texture path"), NULL);
	*should_continue = 1; // mlx->errno?
	return (img_field_ptr);
}

static void	verify_texture_file_accessibility(void **img_field_ptr, \
											char **parts, char *trimmed_line)
{
	int	fd_texture;

	fd_texture = open((char *)(*img_field_ptr), O_RDONLY);
	if (fd_texture == -1)
	{
		free(*img_field_ptr);
		*img_field_ptr = NULL;
		ft_free_ss_uptonull((void **)parts);
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
	void	**img_field_ptr;
	int		should_continue;

	trimmed_line = trim_and_validate_raw_line(line, &should_continue);
	if (!should_continue) {
		free(trimmed_line);
		return (0);
	}
	parts = split_trimmed_line(trimmed_line, &should_continue);
	if (!should_continue) {
		ft_free_ss_uptonull((void **)parts);
		free(trimmed_line);
		return (0);
	}
	img_field_ptr = configure_texture_asset(data, parts, trimmed_line, \
											&should_continue);
	if (!should_continue) {
		ft_free_ss_uptonull((void **)parts);
		free(trimmed_line);
		return (0);
	}
	verify_texture_file_accessibility(img_field_ptr, parts, trimmed_line);
	convert_texture_to_image(data);
	ft_free_ss_uptonull((void **)parts);
	free(trimmed_line);
	return (1);
}
