/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:33:54 by tpotilli          #+#    #+#             */
/*   Updated: 2023/10/05 08:43:41 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_letter(char const *s, char c, int i)
{
	int	letter;

	letter = 0;
	while (s[i] != c && s[i])
	{
		letter++;
		i++;
	}
	return (letter + 1);
}

char	**ft_free(char **split, int index_word)
{
	while (index_word > 0)
	{
		free (split[index_word]);
		index_word--;
	}
	free (split);
	return (NULL);
}

int	ft_word(char const *s, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 1;
	while (s && s[i] && s[i] == c)
		i++;
	if (s[i] == '\0')
		return (1);
	else if (c == '\0')
		return (word + 1);
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] != '\0')
				word++;
		}
		else
			i++;
	}
	return (word + 1);
}

char	**ft_copy(char const *s, char c, char **split, int i)
{
	int	index_word;
	int	index_letter;

	index_word = 0;
	index_letter = 0;
	while (s[i])
	{
		split[index_word] = malloc(sizeof(char) * ft_letter(s, c, i));
		if (!split[index_word])
			ft_free(split, index_word);
		while (s[i] != c && s[i])
		{
			split[index_word][index_letter] = s[i];
			index_letter++;
			i++;
		}
		split[index_word][index_letter] = '\0';
		index_letter = 0;
		index_word++;
		while (s[i] == c && s[i])
			i++;
	}
	split[index_word] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_word(s, c);
	if (len == 1 || s[0] == 0)
	{
		split = malloc(sizeof(char *));
		if (!(split))
			return (NULL);
		split[0] = NULL;
		return (split);
	}
	split = malloc(sizeof(char *) * len);
	if (!(split))
		return (NULL);
	i = 0;
	while (s[i] == c)
		i++;
	ft_copy(s, c, split, i);
	return (split);
}
