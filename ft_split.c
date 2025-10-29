/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluis <aluis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 06:51:00 by aluis             #+#    #+#             */
/*   Updated: 2025/10/29 13:57:04 by aluis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_wrd(const char *s, char c)
{
	int	count;
	int	in_wrd;

	count = 0;
	in_wrd = 0;
	while (*s)
	{
		if (*s != c && !in_wrd)
		{
			in_wrd = 1;
			count ++;
		}
		else if (*s == c)
			in_wrd = 0;
		s ++;
	}
	return (count);
}

static char	*get_nxt_wrd(const char **s, char c)
{
	char		*wrd;
	const char	*start;
	int			len;

	while (**s == c)
		(*s)++;
	start = *s;
	while (**s != c && **s)
		(*s)++;
	len = *s - start;
	wrd = (char *) malloc(sizeof(char) * (len + 1));
	if (!wrd)
		return (NULL);
	wrd[len] = '\0';
	while (len --)
		wrd[len] = start[len];
	return (wrd);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		wrds;
	int		i;

	wrds = count_wrd(s, c);
	array = (char **) malloc(sizeof(char *) * (wrds + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (i < wrds)
	{
		array[i] = get_nxt_wrd(&s, c);
		if (!array[i])
		{
			while (i > 0)
				free(array[-- i]);
			free(array);
		}
		i ++;
	}
	array[i] = NULL;
	return (array);
}
