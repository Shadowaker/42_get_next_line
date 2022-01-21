/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:41:56 by dridolfo          #+#    #+#             */
/*   Updated: 2022/01/21 20:57:06 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line_bonus.h"

t_clist	*ft_newclist(t_clist *dic, int fd, char *buff)
{
	t_clist	*elem;

	if (dic != NULL)
	{
		while (dic->next != NULL)
			dic = dic->next;
		elem = malloc(sizeof(t_clist));
		if (!elem)
			return (NULL);
		elem->first = dic->first;
		elem->buff = buff;
		elem->fd = fd;
		dic->next = elem;
	}
	else
	{
		elem = malloc(sizeof(t_clist));
		if (!elem)
			return (NULL);
		elem->first = elem;
		elem->buff = buff;
		elem->fd = fd;
		elem->next = NULL;
	}
	return (elem);
}

void	*ft_handler(t_clist *dic, int fd, char *buff, char meth)
{
	if (meth == 'r')
	{
		if (dic == NULL)
			return (NULL);
		dic = dic->first;
		while (dic->next != NULL)
		{
			if (fd == dic->fd)
				return (dic->buff);
			dic = dic->next;
		}
		return (NULL);
	}
	else if (meth == 'c')
		ft_newclist(dic, fd, buff);
	else
	{
		dic = dic->first;
		while (dic->fd != fd && dic->next != NULL)
			dic = dic->next;
		if (dic->fd == fd)
			dic->buff = buff;
	}
	return (NULL);
}

char	*ft_recover(int fd, char *buff)
{
	char	*tmp_buff;
	int		f;

	tmp_buff = (char *) malloc(BUFFER_SIZE + 1);
	if (!tmp_buff)
		return (NULL);
	f = 1;
	while ((ft_find_line(buff) == 0) && f != 0)
	{
		f = read(fd, tmp_buff, BUFFER_SIZE);
		if (f == -1)
		{
			free(tmp_buff);
			return (NULL);
		}
		tmp_buff[f] = '\0';
		buff = ft_strmerge(buff, tmp_buff);
	}
	free(tmp_buff);
	return (buff);
}

char	*get_next_line(int fd)
{
	char			*line;
	static t_clist	*dic;
	char			*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = ft_handler(dic, fd, "\0", 'r');
	if (buff == NULL)
		dic = ft_newclist(NULL, fd, buff);
	buff = ft_recover(fd, buff);
	if (!buff)
		return (NULL);
	line = ft_return_line(buff);
	ft_handler(dic, fd, ft_prepare_next(buff), 'e');
	return (line);
}
