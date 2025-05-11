/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:36:30 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/11 15:53:06 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player_controls_internal.h"

static t_action	parse_key(int keycode)
{
	if (keycode == 65307 || keycode == 53)
		return (EXIT);
	if (keycode == 119 || keycode == 13)
		return (FWD);
	if (keycode == 115 || keycode == 1)
		return (BACK);
	if (keycode == 97 || keycode == 0)
		return (TURN_CCW);
	if (keycode == 100 || keycode == 2)
		return (TURN_CW);
	if (keycode == 109)
		return (MINIMAP);
	return (NO);
}

static double	step(t_mlx *mlx, double suggest)
{
	if (suggest > 0 && mlx->player.to_wall_ahead - suggest
		< MIN_DISTANCE_TO_WALL)
		return (mlx->player.to_wall_ahead - MIN_DISTANCE_TO_WALL);
	if (suggest < 0 && mlx->player.to_wall_behind + suggest
		< MIN_DISTANCE_TO_WALL)
		return (-mlx->player.to_wall_behind + MIN_DISTANCE_TO_WALL);
	return (suggest);
}

static int	handle_keyboard_event(t_mlx *mlx)
{
	if (mlx->player.gamepad.fwd_pressed)
		ft_vector_move_here(&mlx->player.coords, step(mlx, STEP_LENGTH));
	if (mlx->player.gamepad.back_pressed)
		ft_vector_move_here(&mlx->player.coords, step(mlx, -STEP_LENGTH));
	if (mlx->player.gamepad.turn_cw_pressed)
		ft_vector_rot_here(&mlx->player.coords, rot_angle());
	if (mlx->player.gamepad.turn_ccw_pressed)
		ft_vector_rot_here(&mlx->player.coords, -rot_angle());
	render_frame(mlx);
	if (mlx->dbg & DBG_PLAYER_MOVE)
		printf("player at %f %f, facing %f %f, \
free space ahead: %f, behind: %f\n",
			mlx->player.coords.from.x, mlx->player.coords.from.y,
			mlx->player.coords.to.x, mlx->player.coords.to.y,
			mlx->player.to_wall_ahead, mlx->player.to_wall_behind);
	return (0);
}

int	key_pressed(int keycode, void *param)
{
	t_mlx		*mlx;
	t_action	action;

	mlx = param;
	action = parse_key(keycode);
	if (action == FWD)
		mlx->player.gamepad.fwd_pressed = 1;
	if (action == BACK)
		mlx->player.gamepad.back_pressed = 1;
	if (action == TURN_CCW)
		mlx->player.gamepad.turn_ccw_pressed = 1;
	if (action == TURN_CW)
		mlx->player.gamepad.turn_cw_pressed = 1;
	handle_keyboard_event(mlx);
	return (0);
}

int	key_released(int keycode, void *param)
{
	t_mlx		*mlx;
	t_action	action;

	mlx = param;
	action = parse_key(keycode);
	if (action == EXIT)
		return (finalize(param, MSG_EXIT, 0));
	if (action == FWD)
		mlx->player.gamepad.fwd_pressed = 0;
	if (action == BACK)
		mlx->player.gamepad.back_pressed = 0;
	if (action == TURN_CCW)
		mlx->player.gamepad.turn_ccw_pressed = 0;
	if (action == TURN_CW)
		mlx->player.gamepad.turn_cw_pressed = 0;
	if (action == MINIMAP)
	{
		mlx->map.minimap_show = !mlx->map.minimap_show;
		render_frame(mlx);
	}
	return (0);
}
