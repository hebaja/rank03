#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

int	ft_putchar_len(char c)
{
	int	len;

	len = write(1, &c, 1);
	return (len);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while(*str)
	{
		len++;
		str++;
	}
	return (len);
}

void	ft_putstr_len(char *str, int *len)
{
	while (*str)
	{
		(*len) += ft_putchar_len(*str);
		str++;
	}
}

void	ft_putnbr_len(int nbr, int *len)
{
	if (nbr == -2147483648)
	{
		nbr = 147483648;
		ft_putstr_len("-2", len);
	}
	if (nbr < 0)
	{
		nbr *= -1;
		(*len) += ft_putchar_len('-');
	}
	if (nbr < 10)
	{
		(*len) += ft_putchar_len(nbr + 48);
		return ;
	}
	ft_putnbr_len(nbr / 10, len);
	ft_putnbr_len(nbr % 10, len);
}

void	ft_puthex_len(unsigned int nbr, int *len)
{
	char	hex[] = "0123456789abcdef";

	if (nbr < 16)
	{
		(*len) += ft_putchar_len(hex[nbr]);
		return ;
	}
	ft_puthex_len(nbr / 16, len);
	ft_puthex_len(nbr % 16, len);
}

int	ft_printf(const char *str, ...)
{
	int	len;
	char	*s;
	int		n;
	unsigned int	ui;
	va_list	arg;

	len = 0;
	if (str == NULL)
		return (-1);
	va_start(arg, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str == 's')
			{
				s = va_arg(arg, char *);
				if (s == NULL)
					ft_putstr_len("(null)", &len);
				else
					ft_putstr_len(s, &len);
				str++;
			}
			if (*str == 'd')
			{
				n = va_arg(arg, int);
				ft_putnbr_len(n, &len);
				str++;
			}
			if (*str == 'x')
			{
				ui = va_arg(arg, unsigned int);
				ft_puthex_len(ui, &len);
				str++;
			}
		}
		else
		{
			len += ft_putchar_len(*str);
			str++;
		}
	}
	va_end(arg);
	return (len);
}

int	main()
{
	int	len;
	int	l = 0;

	len = ft_printf(" %d ", INT_MIN);
	// len = ft_printf("%s %d %d %x %x\n", "Turtles", 123, -123, 123, -123);
	ft_putnbr_len(len, &l);
	return (0);
}
