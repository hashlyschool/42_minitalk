/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:31:30 by hashly            #+#    #+#             */
/*   Updated: 2021/09/15 15:31:31 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;
	size_t	j;

	if (!(*little))
		return ((char *)big);
	n = 0;
	while (little[n])
		n++;
	if (len == 0 && n != 0)
		return (NULL);
	j = 0;
	while ((*big && j < len) || !len)
	{
		i = 0;
		while (big[i] == little[i] && little[i] && big[i])
			i++;
		if (i == n && i <= len - j)
			return ((char *)big);
		big++;
		j++;
	}
	return (NULL);
}
