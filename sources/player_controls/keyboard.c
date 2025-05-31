/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:36:30 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/31 15:31:06 by inikulin         ###   ########.fr       */
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
		return (STEP_LEFT);
	if (keycode == 100 || keycode == 2)
		return (STEP_RIGHT);
	if (keycode == 65361)
		return (TURN_CCW);
	if (keycode == 65363)
		return (TURN_CW);
	if (keycode == 109)
		return (MINIMAP);
	return (NO);
}

static void	side_step(t_mlx *mlx)
{
	t_point	dir;

	dir = ft_point_sub(&mlx->player.coords.to, &mlx->player.coords.from);
	dir = ft_point_norm(&dir);
	if (mlx->player.gamepad.step_left_pressed
		&& mlx->player.to_wall_left > MIN_DISTANCE_TO_WALL)
	{
		dir = ft_point_rot_z(&dir, -M_PI / 2);
		dir = ft_point_scale(&dir, STEP_LENGTH);
		ft_vector_translate_here(&mlx->player.coords, &dir);
	}
	else if (mlx->player.gamepad.step_right_pressed
		&& mlx->player.to_wall_right > MIN_DISTANCE_TO_WALL)
	{
		dir = ft_point_rot_z(&dir, M_PI / 2);
		dir = ft_point_scale(&dir, STEP_LENGTH);
		ft_vector_translate_here(&mlx->player.coords, &dir);
	}
	else if (mlx->player.gamepad.step_right_pressed)
	{
		dir = ft_point_rot_z(&dir, -M_PI / 2);
		dir = ft_point_scale(&dir, STEP_LENGTH);
		ft_vector_translate_here(&mlx->player.coords, &dir);
	}
}

static double	f_b_step(t_mlx *mlx, double suggest)
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
		ft_vector_move_here(&mlx->player.coords, f_b_step(mlx, STEP_LENGTH));
	if (mlx->player.gamepad.back_pressed)
		ft_vector_move_here(&mlx->player.coords, f_b_step(mlx, -STEP_LENGTH));
	if (mlx->player.gamepad.step_left_pressed
		|| mlx->player.gamepad.step_right_pressed)
		side_step(mlx);
	if (mlx->player.gamepad.turn_cw_pressed)
		ft_vector_rot_here(&mlx->player.coords, rot_angle());
	if (mlx->player.gamepad.turn_ccw_pressed)
		ft_vector_rot_here(&mlx->player.coords, -rot_angle());
	render_frame(mlx);
	if (mlx->dbg & DBG_PLAYER_MOVE)
		printf("player at %f %f, facing %f %f, \
free space ahead: %f, behind: %f, left: %f, right: %f\n",
			mlx->player.coords.from.x, mlx->player.coords.from.y,
			mlx->player.coords.to.x, mlx->player.coords.to.y,
			mlx->player.to_wall_ahead, mlx->player.to_wall_behind,
			mlx->player.to_wall_left, mlx->player.to_wall_right);
	return (0);
}

int	key_pressed(int keycode, void *param)
{
	t_mlx		*mlx;
	t_action	action;

	mlx = param;
	if (mlx->dbg & KEY_PRESSED)
		printf("key pressed: %d\n", keycode);
	action = parse_key(keycode);
	if (action == FWD)
		mlx->player.gamepad.fwd_pressed = 1;
	if (action == BACK)
		mlx->player.gamepad.back_pressed = 1;
	if (action == STEP_LEFT)
		mlx->player.gamepad.step_left_pressed = 1;
	if (action == STEP_RIGHT)
		mlx->player.gamepad.step_right_pressed = 1;
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
		return (finalize(param, "", 0));
	if (action == FWD)
		mlx->player.gamepad.fwd_pressed = 0;
	if (action == BACK)
		mlx->player.gamepad.back_pressed = 0;
	if (action == STEP_LEFT)
		mlx->player.gamepad.step_left_pressed = 0;
	if (action == STEP_RIGHT)
		mlx->player.gamepad.step_right_pressed = 0;
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
