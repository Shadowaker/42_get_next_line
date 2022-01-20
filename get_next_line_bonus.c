/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:41:56 by dridolfo          #+#    #+#             */
/*   Updated: 2022/01/20 21:37:04 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line_bonus.h"

t_clist	*ft_cr_clist(void)
{
	t_clist	*first;

	first = malloc(sizeof(t_clist));
	first->first = first;
	first->buff = NULL;
	first->fd = (int *) -2;
	first->next = NULL;
	return (first);
}

void	ft_newclist(t_clist *dic, int *fd, char *buff)
{
	t_clist	*elem;

	while (dic->next != NULL)
		dic = dic->next;
	elem = malloc(sizeof(t_clist));
	dic->next = elem;
	elem->first = dic->first;
	elem->buff = buff;
	elem->fd = fd;
}

void	ft_editlist(t_clist *dic, int *fd, char *buff)
{
	t_clist	*elem;

	elem = malloc(sizeof(t_clist));
	while (dic->fd != fd)
		dic = dic->next;
	dic->buff = buff;
}

void	*ft_handler(t_clist *dic, int *fd, char *buff, char meth)
{
	if (meth == 'r')
	{
		/*p = (char *) malloc(1);
		p[0] = '\0';*/
		while (dic->next != NULL)
		{
			if (fd == dic->fd)
				return (dic->buff);
			dic = dic->next;
		}
		return ((char *) 0);
	}
	else if (meth == 'c')
		ft_newclist(dic, fd, buff);
	else
		ft_editlist(dic, fd, buff);
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
	if (!dic)
		dic = ft_cr_clist();
	buff = ft_handler(dic, &fd, "", 'r');
	if (buff == (char *) 0)
		ft_newclist(dic, &fd, buff);
	buff = ft_recover(fd, buff);
	if (!buff)
		return (NULL);
	line = ft_return_line(buff);
	ft_editlist(dic, &fd, ft_prepare_next(buff));
	return (line);
}
