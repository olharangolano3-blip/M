/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 07:51:32 by dalde-ol          #+#    #+#             */
/*   Updated: 2025/06/19 10:41:58 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	while (len_s >= 0)
	{
		if (s[len_s] == (char)c)
			return ((char *)&s[len_s]);
		len_s--;
	}
	return (NULL);
}
