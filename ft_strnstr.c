/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluis <aluis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 00:16:33 by aluis             #+#    #+#             */
/*   Updated: 2025/10/29 13:58:58 by aluis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l_len;

	if (*little == '\0')
		return ((char *) big);
	l_len = ft_strlen(little);
	while ((len > 0) && *big)
	{
		if (*big == *little && (ft_memcmp(big, little, l_len) == 0))
			if (len >= l_len)
				return ((char *) big);
		big ++;
		len --;
	}
	return ((char *) NULL);
}
