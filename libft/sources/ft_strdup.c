/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:31:18 by hashly            #+#    #+#             */
/*   Updated: 2021/09/15 15:31:20 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	char	*ptr;

	len = ft_strlen(src);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == (void *)0)
		return ((void *)0);
	ft_strlcpy(ptr, src, len + 1);
	return (ptr);
}
