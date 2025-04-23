/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:36:30 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/10 18:02:45 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player_controls_internal.h"

static t_action	parse_key(int keycode)
{
	if (keycode == 65307)
		return (EXIT);
	return (NO);
}

int	close_it(void *param)
{
	return (finalize((t_mlx *)param, MSG_EXIT, 0));
}

int	handle_keyboard(int keycode, void *param)
{
	t_action	action;

	action = parse_key(keycode);
	if (action == NO)
		return (0);
	if (action == EXIT)
		close_it(param);
	return (0);
}
