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

char	*ft_find_line(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n';
			return (1);
		i++;
	}
	return (0);
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
	return (str);
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
		str[j++] = buff[i++];
	str[j] = '\0';
	free(buff);
	return (s);
}

char	*ft_recover(int fd, char *buff)
{
	char	*tmp_buff;
	int		f;

	tmp_buff = (char *) malloc(BUFFER_SIZE + 1);
	if (!tmp_buff)
		return (NULL);
	f = 1;
	while (!ft_find_line(buff) && f != 0)
	{
		f = read(fd, buff, BUFFER_SIZE);
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
	char	    *line;
	static char *buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = ft_recover(fd, buff);
	if (!buff)
		return (NULL);
	line = ft_return_line(buff);
	buff = ft_prepare_next(buff);
	return (line);
}

// TEST ENV --------------------------------------------------------------------------------------------------------------------------

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("tests/test.txt", O_RDONLY);
	i = 1;
	while (i < 6)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}