/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:59:28 by tpotillion        #+#    #+#             */
/*   Updated: 2023/10/12 18:21:47 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	This function takes as parameters:
**	
**	const char *big -> the string where we search the occurence
**	const char *little -> the string you want to use to search the occurence
**	size_t len -> the size you want to use
**
**	==========================================================================
**	
**	This function will search the first occurence in big with little
**	He will use len for the limit of the where you want to search
*/

#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (len == 0 && (!big || !little))
		return (NULL);
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && (len > i))
	{
		while (big[i + j] == little[j] && (i + j < len))
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
		j = 0;
	}
	return (NULL);
}
