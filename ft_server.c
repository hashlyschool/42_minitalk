/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@students.21-school.ru>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 09:35:23 by hashly            #+#    #+#             */
/*   Updated: 2021/09/20 12:54:25 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/includes/libft.h"
#include "ft_minitalk.h"

static void	ft_sigaction(int sig, siginfo_t *siginfo, void *context)
{
	static int				i = 0;
	static pid_t			client_pid = 0;
	static unsigned char	c = 0;

	context = 0;
	if (client_pid == 0)
		client_pid = siginfo->si_pid;
	c = c | (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(client_pid, SIGUSR2);
			usleep(SLEEP_MICROSECOND);
			client_pid = 0;
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(client_pid, SIGUSR1);
		usleep(SLEEP_MICROSECOND);
	}
	else
		c <<= 1;
}

static	void	str_in_color(char *color, char *str)
{
	ft_putstr_fd(color, 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(DEFAULT, 1);
}

static void	ft_putnead(int pid)
{
	str_in_color(GREEN, "\t\t\tGood day!\n");
	str_in_color(GREEN, "It is minitalk by hashly\n");
	str_in_color(GREEN, "You have launched the server side of the project.\n");
	str_in_color(GREEN, "Process id:\t");
	ft_putnbr_fd(pid, 1);
	str_in_color(GREEN, "\nTo use the server, you need to run the command:\n\t");
	str_in_color(GREEN, " `./client [PID server] [message]`\n");
	str_in_color(GREEN, "=============================");
	str_in_color(GREEN, "=============================\n");
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putnead(getpid());
	s_sigaction.sa_sigaction = ft_sigaction;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
