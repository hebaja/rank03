#include <stdio.h>
#include <stdlib.h>

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
	// free(s1);
	ptr[i] = '\0';
	return (ptr);
}

int	main()
{
	char	*p;

	p = ft_strjoin("banana", "rama");
	printf("%s", p);
	free(p);
	return (0);
}
