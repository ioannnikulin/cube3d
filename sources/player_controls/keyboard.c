/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:36:30 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/21 21:01:05 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player_controls_internal.h"

static t_action	parse_key(int keycode)
{
	if (keycode == 65307)
		return (EXIT);
	if (keycode == 119)
		return (FWD);
	if (keycode == 115)
		return (BACK);
	if (keycode == 97)
		return (TURN_CCW);
	if (keycode == 100)
		return (TURN_CW);
	return (NO);
}

int	close_it(void *param)
{
	return (finalize((t_mlx *)param, MSG_EXIT, 0));
}

int	handle_keyboard(int keycode, void *param)
{
	t_action	action;
	t_mlx		*mlx;

	action = parse_key(keycode);
	if (action == NO)
		return (0);
	if (action == EXIT)
		close_it(param);
	mlx = param;
	if (action == FWD)
		ft_vector_move_here(&mlx->player.coords, STEP_LENGTH);
	if (action == BACK)
		ft_vector_move_here(&mlx->player.coords, -STEP_LENGTH);
	if (action == TURN_CW)
		ft_vector_rot_here(&mlx->player.coords, rot_angle());
	if (action == TURN_CCW)
		ft_vector_rot_here(&mlx->player.coords, -rot_angle());
	if (DBG_LVL & DBG_PLAYER_MOVE)
		printf("player at %f %f, facing %f %f\n",
			mlx->player.coords.from.x, mlx->player.coords.from.y,
			mlx->player.coords.to.x, mlx->player.coords.to.y);
	render_frame(mlx);
	return (0);
}
