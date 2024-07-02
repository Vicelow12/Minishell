/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:11:24 by tcharbon          #+#    #+#             */
/*   Updated: 2024/07/02 13:11:24 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
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