/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharbon <tcharbon@stud42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:06:09 by tcharbon          #+#    #+#             */
/*   Updated: 2024/07/10 18:06:09 by tcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int     size_cmd(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}