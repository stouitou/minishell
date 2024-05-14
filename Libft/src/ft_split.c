/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:37:57 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 12:18:28 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wlen(const char *s, char *charset)
{
	int	len;

	len = 0;
	while (s[len] && !ft_ischarset(s[len], charset))
		len++;
	return (len);
}

static char	*ft_dup_n_char(const char *s, char *charset)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (ft_wlen(s, charset) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < ft_wlen(s, charset))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**ft_freesplit(char **split, size_t j)
{
	if (split[j] == NULL)
	{
		while (j > 0)
		{
			free(split[j]);
			j--;
		}
		free(split);
		return (NULL);
	}
	return (split);
}

static char	**ft_fill_split(char **split, int i, char const *s, char *charset)
{
	size_t	j;

	j = 0;
	while (j < ft_count_words(s, charset))
	{
		split[j] = ft_dup_n_char(&s[i], charset);
		if (ft_freesplit(split, j) == NULL)
			return (NULL);
		while (s[i] && !ft_ischarset(s[i], charset))
			i++;
		while (ft_ischarset(s[i], charset))
			i++;
		j++;
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char const *s, char *charset)
{
	char	**split;
	size_t	i;

	if (s == NULL)
		return (NULL);
	split = (char **)malloc((ft_count_words(s, charset) + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (ft_ischarset(s[i], charset) && !ft_ischarset('\0', charset))
		i++;
	if (ft_fill_split(split, i, s, charset) == NULL)
		return (NULL);
	return (split);
}
