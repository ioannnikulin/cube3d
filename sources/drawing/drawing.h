/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:10:20 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/09 18:21:16 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# include "../cube3d.h"

typedef struct s_mlx	t_mlx;

void	line(t_mlx *s, t_point *f, t_point *t);

#endif