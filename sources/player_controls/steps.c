/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:35:01 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/31 15:47:19 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player_controls_internal.h"

void	side_step(t_mlx *mlx)
{
	t_point	dir;

	dir = ft_point_sub(&mlx->player.coords.to, &mlx->player.coords.from);
	dir = ft_point_norm(&dir);
	if (mlx->player.gamepad.step_left_pressed
		&& mlx->player.to_wall_left - STEP_LENGTH > MIN_DISTANCE_TO_WALL)
	{
		dir = ft_point_rot_z(&dir, -M_PI / 2);
		dir = ft_point_scale(&dir, STEP_LENGTH);
		ft_vector_translate_here(&mlx->player.coords, &dir);
	}
	else if (mlx->player.gamepad.step_right_pressed
		&& mlx->player.to_wall_right - STEP_LENGTH > MIN_DISTANCE_TO_WALL)
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

double	f_b_step(t_mlx *mlx, double suggest)
{
	if (suggest > 0 && mlx->player.to_wall_ahead - suggest
		< MIN_DISTANCE_TO_WALL)
		return (mlx->player.to_wall_ahead - MIN_DISTANCE_TO_WALL);
	if (suggest < 0 && mlx->player.to_wall_behind + suggest
		< MIN_DISTANCE_TO_WALL)
		return (-mlx->player.to_wall_behind + MIN_DISTANCE_TO_WALL);
	return (suggest);
}
