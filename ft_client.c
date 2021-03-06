/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@students.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:15:30 by hashly            #+#    #+#             */
/*   Updated: 2021/09/20 12:49:35 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/includes/libft.h"
#include "ft_minitalk.h"

static void	put_str_in_color(char *color, char *str)
{
	ft_putstr_fd(color, 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(DEFAULT, 1);
}

static void	ft_sigaction(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
		++received;
	else if (sig == SIGUSR2)
	{
		put_str_in_color(GREEN, "Server received\t");
		ft_putnbr_fd(received, 1);
		put_str_in_color(GREEN, " bytes\n");
		exit(0);
	}
}

/*
send SIGUSER2 - if bit == 1;
send SIGUSER1 - if bit == 0;
*/
static void	ft_kill_signal(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(SLEEP_MICROSECOND);
		}
		usleep(SLEEP_MICROSECOND);
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(SLEEP_MICROSECOND);
	}
	usleep(SLEEP_MICROSECOND);
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;

	if (argc != 3 || ft_strlen(argv[2]) == 0)
		return (1);
	put_str_in_color(GREEN, "You\tsent\t");
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	put_str_in_color(GREEN, " bytes\n");
	s_sigaction.sa_handler = ft_sigaction;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sigaction.sa_mask);
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	ft_kill_signal(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
