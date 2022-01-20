/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:56:50 by dridolfo          #+#    #+#             */
/*   Updated: 2022/01/20 17:58:26 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strmerge(char *buff, char *tmp_buff)
{
	size_t	i;
	size_t	j;
	char	*s;

	if (!buff)
	{
		buff = (char *) malloc(1);
		buff[0] = '\0';
	}
	if (!buff || !tmp_buff)
		return (NULL);
	s = malloc((ft_strlen(buff) + ft_strlen(tmp_buff)) + 1);
	if (!s)
		return (NULL);
	i = -1;
	j = 0;
	if (buff)
		while (buff[++i] != '\0')
			s[i] = buff[i];
	while (tmp_buff[j] != '\0')
		s[i++] = tmp_buff[j++];
	s[i] = '\0';
	free(buff);
	return (s);
}

int	ft_find_line(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_return_line(char *buff)
{
	int		i;
	char	*s;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	s = (char *)malloc(i + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		s[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
	{
		s[i] = buff[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_prepare_next(char *buff)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	s = (char *)malloc((ft_strlen(buff) - i + 1));
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (buff[i])
		s[j++] = buff[i++];
	s[j] = '\0';
	free(buff);
	return (s);
}
