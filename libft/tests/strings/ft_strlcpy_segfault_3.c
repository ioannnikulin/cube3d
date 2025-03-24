/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy_segfault_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:56:03 by inikulin          #+#    #+#             */
/*   Updated: 2023/11/17 14:23:19 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	main(void)
{
	char *s = calloc(1, 1);
	if (!s)
		return (bad_alloc(1));
	char *d = 0;
	ft_strlcpy(s, d, (0));
	return (segfault_expected(1));
}
