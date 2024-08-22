/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:34:42 by tcharbon          #+#    #+#             */
/*   Updated: 2024/08/05 17:34:42 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int     ft_strcmp(unsigned char *str1, unsigned char *str2)
{
    int     i;

    i = 0;
    while (str1[i] != '\0' || str2[i] != '\0')
    {
        if (str1[i] == str2[i])
            i++;
        else
            return (0);
    }
    return (1);
}
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	char		*cpy;

	cpy = (char *)big;
	i = 0;
	j = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (cpy[i] && i < len)
	{
		while (cpy[i] == little[j] && i < len && cpy[i])
		{
			i++;
			j++;
		}
		if (j == ft_strlen(little))
			return (cpy + (i - j));
		else if (j != 0)
			i = i - j;
		j = 0;
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (i < (int)ft_strlen(s1))
	{
		join[i] = s1[i];
		i++;
	}
	while (i < (int)ft_strlen(s1) + (int)ft_strlen(s2))
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}
char	*ft_join_free_s1(char *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (free (s1), NULL);
	i = 0;
	j = 0;
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (free (s1), NULL);
	while (i < (int)ft_strlen(s1))
	{
		join[i] = s1[i];
		i++;
	}
	while (i < (int)ft_strlen(s1) + (int)ft_strlen(s2))
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
}

static	int	count_word(char const *s, char c)
{
	int	count;
	int	i;
	int	fl;

	i = 0;
	count = 0;
	fl = 1;
	while (s[i])
	{
		if (s[i] == c && !fl)
			fl = 1;
		else if (c != s[i] && fl)
		{
			fl = 0;
			count++;
		}
		i++;
	}
	return (count);
}

static	void	*secure_malloc(char **tab, int i)
{
	while (i > 0)
	{
		i--;
		if (tab[i] != NULL)
			free(tab[i]);
	}
	free(tab);
	return ((void *)0);
}

static	char	*malloc_str(char const *s, char c, int *step)
{
	int		nb_letter;
	char	*str;

	nb_letter = 0;
	while (s[*step] == c)
		*step = *step + 1;
	while (s[*step] != c && s[*step])
	{
		nb_letter++;
		*step = *step +1;
	}
	str = malloc(sizeof(char) * (nb_letter + 1));
	if (!str)
		return (NULL);
	return (str);
}

static	void	tab_fill(const char *s, char c, int *step, char *strfill)
{
	int	i;

	i = 0;
	while (s[*step] == c)
		*step = *step + 1;
	while (s[*step] != c && s[*step])
	{
		strfill[i] = s[*step];
		i++;
		*step = *step + 1;
	}
	strfill[i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		step;

	if (!s)
		return (NULL);
	i = 0;
	step = 0;
	tab = malloc(sizeof(char *) * ((count_word(s, c) + 1)));
	if (!tab)
		return (NULL);
	while (i < count_word(s, c))
	{
		j = step;
		tab[i] = malloc_str(s, c, &step);
		if (!tab[i])
			return (secure_malloc(tab, i));
		step = j;
		tab_fill(s, c, &step, tab[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static	int	strlenght(const char *src)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * strlenght (s) + 1);
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}