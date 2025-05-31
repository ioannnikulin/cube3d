/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_if_trapped.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:01:40 by inikulin          #+#    #+#             */
/*   Updated: 2025/05/29 15:58:40 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../sources/memory/memory.h"

typedef struct s_calloc_trap
{
	int	cur;
	int	tgt;
}	t_calloc_trap;

t_calloc_trap	trap = (t_calloc_trap){0, 0};

void	ft_calloc_if_trap_setup(int tgt)
{
	trap.tgt = tgt;
}

// starts from 1
void	*ft_calloc_if(size_t size, int choice)
{
	if (++ trap.cur == trap.tgt || !choice)
		return (0);
	return (ft_calloc(size, 1));
}

void	ft_calloc_if_trap_count()
{
	FT_PRINTF("Total ft_calloc_if calls: %i\n", trap.cur);
}
