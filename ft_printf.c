/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 23:23:12 by psergio-          #+#    #+#             */
/*   Updated: 2021/08/14 23:23:12 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

size_t	_flex(char *s, int c, int regina, int size)
{
	if (regina == 0)
	{	
		while (s[size])
			size++;
		return (size);
	}
	else if (regina == 1)
	{
		while (*s)
		{
			if (*s++ == (char)c)
				return (1);
		}
		return (0);
	}
	if (!s)
		return (write(1, "(null)", 6));
	while (s[size])
		write(1, &s[size++], 1);
	return (size);
}

size_t	putnbr_base_int(int nb, char *base, int base_len)
{
	int		len;
	int		i;
	char	str[30];

	i = 0;
	len = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
		len++;
	}
	if (nb == 0)
		return (write(1, base, 1));
	while (nb != 0)
	{
		str[i++] = base[nb % base_len];
		nb /= base_len;
		len++;
	}
	while (i--)
		write(1, &str[i], 1);
	return (len);
}

size_t	putnbr_base(size_t nb, char *base, int base_len, char format)
{
	int		len;
	int		i;
	char	str[30];

	i = 0;
	len = 0;
	if (_flex("uxX", format, 1, 42))
		nb = (unsigned int) nb;
	if (nb == 0)
		return (write(1, base, 1));
	while (nb != 0)
	{
		str[i++] = base[nb % base_len];
		nb /= base_len;
		len++;
	}
	while (i--)
		write(1, &str[i], 1);
	return (len);
}

int	_specifiers(char format, va_list args, int i[])
{
	if (format == 'c')
		return (write(1, &(i[2]), 1));
	else if (format == 'd' || format == 'i')
		return (putnbr_base_int(i[2], "0123456789", 10));
	else if (format == 'u')
		return (putnbr_base(i[2], "0123456789", 10, 'u'));
	else if (format == 'x')
		return (putnbr_base(i[2], "0123456789abcdef", 16, 'x'));
	else if (format == 'X')
		return (putnbr_base(i[2], "0123456789ABCDEF", 16, 'X'));
	else if (format == 'p')
	{
		write(1, "0x", 2);
		return (putnbr_base(va_arg(args, size_t),
				"0123456789abcdef", 16, 'p') + 2);
	}
	else if (format == 's')
		return (_flex(va_arg(args, char *), 42, 3, 0));
	else
		return (write(1, "%", 1));
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i[3];
	char	*input;

	i[0] = 0;
	i[1] = 0;
	input = (char *)s;
	va_start(args, s);
	while (input[i[0]])
	{
		if (input[i[0]] == '%' && _flex("cspdiuxX%", input[i[0] + 1], 1, 0))
		{
			if (_flex("cdi", input[i[0] + 1], 1, 42))
				i[2] = va_arg(args, int);
			if (_flex("uxX", input[i[0] + 1], 1, 42))
				i[2] = va_arg(args, unsigned int);
			i[1] += _specifiers(input[i[0] + 1], args, i);
			i[0] += 2;
		}
		else
			i[1] += write(1, &input[i[0]++], 1);
	}
	va_end(args);
	return (i[1]);
}
