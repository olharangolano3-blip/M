/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:13:26 by dalde-ol          #+#    #+#             */
/*   Updated: 2025/06/18 16:44:10 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	tam_dst;
	size_t	tam_src;
	size_t	i;

	if (!dst || !src)
		return (0);
	tam_dst = ft_strlen(dst);
	tam_src = ft_strlen(src);
	if (size <= tam_dst)
		return (size + tam_src);
	i = 0;
	while (src[i] && (tam_dst + i < size - 1))
	{
		dst[tam_dst + i] = src[i];
		i++;
	}
	dst[tam_dst + i] = '\0';
	return (tam_dst + tam_src);
}
