/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:33:11 by dridolfo          #+#    #+#             */
/*   Updated: 2022/01/19 20:12:28 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && j < dstsize)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
}

static char	*ft_formatting(char *s1, char*s2)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	tmp = (char *) malloc(ft_strlen(s2) + ft_strlen(s1) + 1);
	i = 0;
	while (s1[i] != '\0')
	{
		tmp[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		tmp[i] = s2[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

static char	*ft_recover(char *s)
{
	size_t	i;
	char	*out;

	i = ft_strlen(s);
	out = (char *) malloc(i + 1);
	i = 0;
	while (s[i] != '\0')
	{
		out[i] = s[i];
		i++;
	}
	return (out);
}

static int	ft_find_nl(char *s)
{
	size_t	ind;

	ind = 0;
	while (s[ind] != '\0')
	{
		if (s[ind] == '\n')
			break ;
		ind++;
	}
	return (ind);
}

static char	*ft_take_it(int fd, char *buff)
{
	size_t	i;
	size_t	j;
	size_t	f;
	char	*stor;
	char	*cac;

	printf("take_it\n");
	fflush(stdout);
	f = read(fd, buff, BUFFER_SIZE);
	if (f > 0)
	{
		printf("take_it2\n");
		fflush(stdout);
		i = ft_find_nl(buff);
		printf("%d - %c\n", i, buff[i]);
		fflush(stdout);
		j = i;
		while (buff[i] != '\n' && fd > 0)
		{
			printf("take_it_buff\n");
			fflush(stdout);
			cac = (char *) malloc(j + 1);
			if (stor)
			{
				printf("take_it_1strlcat\n");
				fflush(stdout);
				ft_strlcat(cac, stor, j + 1);
				free(stor);
				stor = (char *) malloc(j + i + 1);
				printf("take_it_2strlcat\n");
				fflush(stdout);
				ft_strlcat(stor, cac, j + 1);
				free(cac);
			}
			else
				stor = (char *) malloc(j + 1);
			printf("take_it_3strlcat\n");
			fflush(stdout);
			ft_strlcat(stor, buff, i + j + 1);
			j += i;
			f = read(fd, buff, BUFFER_SIZE);
			i = ft_find_nl(buff);
		}
		printf("take_it_3\n");
		fflush(stdout);
		if (!stor)
		{
			stor = (char *) malloc(j);
			ft_strlcat(stor, buff, i + j);
		}
		else
		{
			cac = (char *) malloc(j);
			ft_strlcat(cac, stor, j);
			stor = (char *) malloc(i + j);
			ft_strlcat(stor, cac, j);
			ft_strlcat(stor, buff, i + j);
			free(cac);
		}
	}
	return (stor);
}

char	*get_next_line(int fd)
{
	static int		line = 0;
	static char		*buff;
	char			*out;

	printf("ppp\n");
	fflush(stdout);
	if (buff)
		out = ft_recover(buff);
	printf("ppp2\n");
	fflush(stdout);
	buff = (char *) malloc(BUFFER_SIZE + 1);
	if (out)
		out = ft_formatting(out, ft_take_it(fd, buff));
	else
	{
		out = ft_take_it(fd, buff);
		if (out[ft_strlen(out)] != '\0')
			out[ft_strlen(out)] = '\0';
	}
	return (out);
}

int	main(void)
{
	int		fd;
	int		con;
	char	*out;

	con = 0;
	fd = open("test.txt", O_RDONLY);
	printf("Hello\n");
	fflush(stdout);
	while (con < 6)
	{
		printf("%d :", con);
		fflush(stdout);
		out = get_next_line(fd);
		printf("$%s$\n", out);
		fflush(stdout);
		free(out);
		con++;
	}
	close(fd);
	printf("Finished.\n");
	fflush(stdout);
	return (0);
}
