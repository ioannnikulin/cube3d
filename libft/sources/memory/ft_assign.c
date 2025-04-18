/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:58:25 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/19 00:19:42 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_assign_i(int *where, int what, int retval)
{
	if (where)
		*where = what;
	return (retval);
}

char	*ft_assign_i_pc(int *where, int what, char *retval)
{
	if (where)
		*where = what;
	return (retval);
}

int	ft_assign_pc(char **where, char *what, int retval)
{
	if (where)
		*where = what;
	return (retval);
}

int	ft_assign_sz(size_t *where, size_t what, int retval)
{
	if (where)
		*where = what;
	return (retval);
}

int	ft_assign_d(double *where, double what, int retval)
{
	if (where)
		*where = what;
	return (retval);
}
