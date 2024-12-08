/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:41:49 by ledio             #+#    #+#             */
/*   Updated: 2024/12/08 17:18:52 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/**
 * g_signal_recevied - A global flag to track signal reception.
 * 
 * This `volatile` variable of type `sig_atomic_t` ensures safe and 
 * consistent access during signal handling. It is set to 1 by the 
 * signal handler when a signal (SIGUSR1 or SIGUSR2) is received. 
 * The client uses this flag to wait for acknowledgment from the server 
 * before sending the next bit of data.
 * */

static volatile sig_atomic_t		g_signal_recevied = 0;

/**
 * print_client - Displays a styled client banner with the PID.
 * @pid: The process ID of the client to display.
 * 
 * This function prints a visually formatted banner using colors and 
 * decorations, followed by the client's process ID, providing an 
 * aesthetic representation of the client information.
 */

void	print_client(int pid)
{
	ft_printf("\n\t%s ▊▊▊▊▊▊╗  ▊▊╗	▊▊╗▊▊▊▊▊▊╗▊▊▊╗    ▊▊╗▊▊▊▊▊▊╗%s\n", CYAN, END);
	ft_printf("\t%s▊▊╔════╝  ▊▊║	▊▊║▊▊╔═══╝▊▊▊▊╗   ▊▊║  ▊▊║%s\n", MAGENTA, END);
	ft_printf("\t%s▊▊║       ▊▊║   ▊▊║▊▊▊▊▊▊║▊▊╔▊▊╗  ▊▊║  ▊▊║%s\n", RED, END);
	ft_printf("\t%s▊▊║       ▊▊║   ▊▊║▊▊║    ▊▊║╚▊▊╗ ▊▊║  ▊▊║%s\n", GRAY, END);
	ft_printf("\t%s ▊▊▊▊▊▊╗  ▊▊▊▊▊╗▊▊║▊▊▊▊▊▊╗▊▊║  ╚▊▊▊▊║  ▊▊║%s\n", CYAN, END);
	ft_printf("\t ╚═════╝ ╚════╝╚═╝╚═════╝╚═════════╝  ╚═╝%s\n", END);
	ft_printf("%s\n\t\tPID: %d%s\t\t%sClient Banner%s\n", MAGENTA, pid,
		END, RED, END);
	ft_printf("\t────────────────────────────────────────────\n\n");
}

/**
 * signal_handler - Handles incoming signals for acknowledgment.
 * @signal: The signal number received (SIGUSR1 or SIGUSR2).
 * 
 * This function sets the global flag `g_signal_recevied` to 1 when 
 * a signal is received, indicating that the server has acknowledged 
 * the last transmitted bit.
 */

void	signal_handler(int signal)
{
	(void)signal;
	g_signal_recevied = 1;
}

/**
 * send_bits - Sends a character bit by bit to the server.
 * @pid: The process ID of the server to send bits to.
 * @c: The character to transmit.
 * 
 * This function iterates over the bits of a character, sending a 
 * SIGUSR1 for '1' and SIGUSR2 for '0'. It waits for acknowledgment 
 * from the server before sending the next bit.
 */

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

/**
 * send_str - Sends a string to the server character by character.
 * @pid: The process ID of the server to send the string to.
 * @str: The string to transmit.
 * 
 * This function iterates over the characters in the string, calling 
 * `send_bits` to transmit each character, including a null terminator 
 * to mark the end of the message.
 */

void	send_str(int pid, char *str)
{
	while (*str)
	{
		send_bits(pid, *str);
		str++;
	}
	send_bits(pid, '\0');
}

/**
 * main - Entry point for the client program.
 * @argc: The number of command-line arguments.
 * @argv: The array of command-line arguments.
 * 
 * This function validates the input, sets up the signal handler for 
 * acknowledgment, and sends the provided message to the server using 
 * its PID. If the arguments are invalid or an error occurs, it outputs 
 * appropriate error messages.
 * 
 * Return: 0 on success, 1 or 2 on error.
 */

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
	sa.sa_flags = 0;
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
