/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 07:55:00 by tpotilli          #+#    #+#             */
/*   Updated: 2023/10/18 13:41:39 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_cpy(char const *s1, char const *s2, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int			lens;
	char		*str;

	if (!s1 || !s2)
		return (NULL);
	lens = ft_strlen(s1);
	str = malloc(sizeof(char) * lens + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	ft_cpy(s1, s2, str);
	return (str);
}
