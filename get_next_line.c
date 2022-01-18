/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:16:09 by dridolfo          #+#    #+#             */
/*   Updated: 2022/01/18 19:38:16 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

size_t	ft_strnlen(char *s, size_t i)
{
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_strlcat(char *s1, char *s2, int j, size_t len)
{
	size_t	i;

	i = 0;
	if (len == -1)
	{
		while (s2[2] != '\0')
		{
			s1[i] = s2[j];
			i++;
			j++;
		}
	}
	else
	{
		while (len > i)
		{
			s1[i] = s2[j];
			i++;
			j++;
		}
	}
	s1[i] = '\0';
}

static size_t	get_line(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (i + 1);
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static int			line = 0;
	static char			*o;
	char				*s;
	size_t				f;
	size_t				i;

	if (o != NULL)
	{
		i = ft_strnlen(o, (size_t) line);
		s = (char *) malloc(i + 1);
		ft_strlcat(s, o, line, -1);
		free(o);
	}
	o = (char *) malloc(BUFFER_SIZE);
	if (s == NULL)

	f = read(fd, o, BUFFER_SIZE);
	i = get_line(o, line);
	s = (char *) malloc(i + 1);
	ft_strlcat(s, o, line, i);
	free(o);
	printf("%d\n", line);
	line = (int) i;
	return (s);
}

int	main(void)
{
	int		fd;
	int		con;
	char	*out;

	con = 0;
	fd = open("test.txt", O_RDONLY);
	while (con < 6)
	{
		printf("%d :", con);
		out = get_next_line(fd);
		printf("%s\n", out);
		free(out);
		con++;
	}
	close(fd);
	printf("Finished.\n");
	return (0);
}
