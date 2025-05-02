/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controls.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:37:26 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/21 20:59:30 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_CONTROLS_H
# define PLAYER_CONTROLS_H
# include "../cube3d.h"

int		handle_keyboard(int keycode, void *param);
int		close_it(void *param);
double	rot_angle(void);
#endif