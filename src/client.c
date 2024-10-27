/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:41:49 by ledio             #+#    #+#             */
/*   Updated: 2024/10/27 23:07:30 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t		g_signal_recevied = 0;

void	print_client(int pid)
{
	ft_printf("\n\t%s ▊▊▊▊▊▊╗  ▊▊╗	▊▊╗▊▊▊▊▊▊╗▊▊▊╗    ▊▊╗▊▊▊▊▊▊╗%s\n", CYAN, END);
	ft_printf("\t%s▊▊╔════╝  ▊▊║	▊▊║▊▊╔═══╝▊▊▊▊╗   ▊▊║  ▊▊║%s\n", MAGENTA, END);
	ft_printf("\t%s▊▊║       ▊▊║   ▊▊║▊▊▊▊▊▊╗▊▊╔▊▊╗  ▊▊║  ▊▊║%s\n", RED, END);
	ft_printf("\t%s▊▊║       ▊▊║   ▊▊║▊▊╔══╝ ▊▊║╚▊▊╗ ▊▊║  ▊▊║%s\n", GRAY, END);
	ft_printf("\t%s ▊▊▊▊▊▊╗  ▊▊▊▊▊╗▊▊║▊▊▊▊▊▊╗▊▊║  ╚▊▊▊▊║  ▊▊║%s\n", CYAN, END);
	ft_printf("\t ╚═════╝ ╚════╝╚═╝╚═════╝╚═════════╝  ╚═╝%s\n", END);
	ft_printf("%s\n\t\tPID: %d%s\t\t%sClient Banner%s\n", MAGENTA, pid,
		END, RED, END);
	ft_printf("\t────────────────────────────────────────────\n\n");
}

void	signal_handler(int signal)
{
	(void)signal;
	g_signal_recevied = 1;
}

void	send_bits(int pid, unsigned char c)
{
	int			i;

	i = 7;
	while (i >= 0)
	{
		g_signal_recevied = 0;
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_putstr_fd("Error sending SIGUSR1\n", 2);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_putstr_fd("Error sending SIGUSR2\n", 2);
		}
		while (!g_signal_recevied)
			usleep(500);
		i--;
	}
}

void	send_str(int pid, char *str)
{
	while (*str)
	{
		send_bits(pid, *str);
		str++;
	}
	send_bits(pid, '\0');
}

int	main(int argc, char **argv)
{
	int					pid;
	char				*str;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_putstr_fd("Usage of ./client <server_pid> <message>\n", 2);
		return (1);
	}
	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (ft_putstr_fd("Error sending the signal to SIGUSR1", 2), 2);
	pid = ft_atoi(argv[1]);
	print_client(pid);
	if (pid <= 0)
	{
		ft_putstr_fd("The pid should be positive\n", 2);
		return (1);
	}
	str = argv[2];
	send_str(pid, str);
	usleep(120);
}
