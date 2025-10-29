/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluis <aluis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 07:08:11 by aluis             #+#    #+#             */
/*   Updated: 2025/10/29 13:58:40 by aluis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	i = ft_strlen(s);
	ptr = (char *) malloc(sizeof(const char) * (i + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s, (i));
	*(ptr + i) = '\0';
	return (ptr);
}
