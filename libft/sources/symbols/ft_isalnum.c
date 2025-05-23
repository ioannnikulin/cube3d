/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikulin <inikulin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:54:38 by inikulin          #+#    #+#             */
/*   Updated: 2025/04/10 18:30:17 by inikulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	c = (unsigned char)c;
	return ((c > 47 && c < 58)
		|| (c > 64 && c < 91) || (c > 96 && c < 123));
}
