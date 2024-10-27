/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:42:25 by ledio             #+#    #+#             */
/*   Updated: 2024/10/27 23:38:50 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_server(int pid)
{
	ft_printf("\n\t%s ▊▊▊▊▊▊╗  ▊▊▊▊▊▊╗▊▊▊▊▊▊▊▊▊╗▊▊╗       ▊▊╗▊▊▊▊▊▊╗▊▊▊▊▊▊▊▊▊╗%s\n", GREEN, END);
	ft_printf("\t%s▊▊╔════╝  ▊▊╔═══╝▊▊     ▊▊║ ▊▊║     ▊▊║ ▊▊╔═══╝▊▊     ▊▊║%s\n", YELLOW, END);
	ft_printf("\t%s▊▊▊▊▊▊╗   ▊▊▊▊▊▊╗▊▊▊▊▊▊▊▊║   ▊▊║   ▊▊║  ▊▊▊▊▊▊╗▊▊▊▊▊▊▊▊║%s\n", DARK_BLUE, END);
	ft_printf("\t%s╚════▊║   ▊▊╔═══╝▊▊ ▊▊═══╝    ▊▊║ ▊▊║   ▊▊╔═══╝▊▊ ▊▊═══╝%s\n", WHITE, END);
	ft_printf("\t%s▊▊▊▊▊▊║   ▊▊▊▊▊▊╗▊▊  ▊▊╗        ▊▊╗     ▊▊▊▊▊▊╗▊▊  ▊▊╗%s\n", GREEN, END);
	ft_printf("\t╚═════╝   ╚═════╝╚═════╝       ╚══╝     ╚═════╝╚═════╝\n");
	ft_printf("%s\n\t\tPID: %d%s\t\t%sServer Banner%s\n", YELLOW, pid, END, DARK_BLUE, END);
	ft_printf("\t────────────────────────────────────────────\n\n");
}

char	convert_bits(char buffer[])
{
	int			i;
	char		c;

	i = 0;
	c = 0;
	while (i < 8)
	{
		if (buffer[i] == '1')
			c |= 1 << (7 - i);
		i++;
	}
	return (c);
}

void	proccess_bits(__pid_t *client_pid, char c)
{
	if (c == '\0')
	{
		write(1, "\n", 1);
		kill(*client_pid, SIGUSR1);
		*client_pid = 0;
		return ;
	}
	else
		write(1, &c, 1);
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static char			c;
	static int			bits = 0;
	static char			buffer[9];
	static __pid_t		client_pid = 0;

	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (signal == SIGUSR1)
		buffer[bits] = '1';
	else if (signal == SIGUSR2)
		buffer[bits] = '0';
	bits++;
	if (bits == 8)
	{
		c = convert_bits(buffer);
		proccess_bits(&client_pid, c);
		c = 0;
		bits = 0;
	}
	if (client_pid != 0)
		kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction		sa;

	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	print_server(getpid());
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error sending the signals\n", 2);
		exit(1);
	}
	while (1)
		pause();
}
