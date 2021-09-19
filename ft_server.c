/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 09:35:23 by hashly            #+#    #+#             */
/*   Updated: 2021/09/17 14:41:31 by hashly           ###   ########.fr       */
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

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = ft_sigaction;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sigaction.sa_mask);
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
