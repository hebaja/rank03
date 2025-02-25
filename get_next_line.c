#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 10
# endif

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while(*str)
	{
		len++;
		str++;
	}
	return (len);
}

char	*ft_strchr(char *str, int c)
{
	int	i;
	unsigned char uc;

	i = 0;
	uc = c;
	while (*str)
	{
		if (*str == uc)
			return (str);
		str++;
	}
	return (0);
}

char	*ft_strdup(char *str)
{
	int	i;
	size_t	len;
	char	*ptr;

	i = 0;
	len = ft_strlen(str);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*ptr;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (ptr == NULL)
		return (NULL);
	while (i < len1)
	{
		ptr[i] = s1[i];
		i++;
	}
	while (i < (len1 + len2))
	{
		ptr[i] = s2[i - len1];
		i++;
	}
	free(s1);
	ptr[i] = '\0';
	return (ptr);
}

char	*populate_line(int fd, char *str)
{
	int		bytes;
	char	*buffer;
	char	*tmp;

	bytes = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (bytes)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			if (str)
				free(str);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		if (!str)
			str = ft_strdup("");
		str = ft_strjoin(str, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

char	*store_rest(char *line)
{
	char	*br_pos;
	char	*rest;

	if (line == NULL || *line == '\0')
		return (NULL);
	br_pos = ft_strchr(line, '\n');
	if (br_pos == NULL)
		return (NULL);
	rest = ft_strdup(++br_pos);
	if (*rest == '\0')
	{
		free(rest);
		return (NULL);
	}
		return (NULL);
	*br_pos = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	line = populate_line(fd, rest);
	if (!line)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	rest = store_rest(line);
	return (line);
}

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		line = get_next_line(fd);
		while (line != NULL)
		{
			printf("%s", line);
			free(line);
			line = get_next_line(fd);
		}
		free(line);
		close(fd);
	}
	return (0);
}
