/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:42:25 by ledio             #+#    #+#             */
/*   Updated: 2024/12/08 17:15:32 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * print_server - Displays a styled server banner with the PID.
 * @pid: The process ID of the server to display.
 * 
 * This function prints a visually formatted banner using colors and
 * decorations, followed by the server's process ID, providing a 
 * clear and aesthetic representation of the server information.
 */

void	print_server(int pid)
{
	ft_printf("\n\t%s ▊▊▊▊▊▊╗  ▊▊▊▊▊▊╗▊▊▊▊▊▊▊▊▊╗▊▊╗       ▊▊╗▊▊▊▊▊▊╗▊▊▊▊▊▊▊▊▊╗%s\n", GREEN, END);
	ft_printf("\t%s▊▊╔════╝  ▊▊╔═══╝▊▊     ▊▊║ ▊▊║     ▊▊║ ▊▊╔═══╝▊▊     ▊▊║%s\n", YELLOW, END);
	ft_printf("\t%s▊▊▊▊▊▊╗   ▊▊▊▊▊▊╗▊▊▊▊▊▊▊▊║   ▊▊║   ▊▊║  ▊▊▊▊▊▊╗▊▊▊▊▊▊▊▊║%s\n", DARK_BLUE, END);
	ft_printf("\t%s╚════▊║   ▊▊╔═══╝▊▊ ▊▊═══╝    ▊▊║ ▊▊║   ▊▊╔═══╝▊▊ ▊▊═══╝%s\n", WHITE, END);
	ft_printf("\t%s▊▊▊▊▊▊║   ▊▊▊▊▊▊╗▊▊  ▊▊╗        ▊▊╗     ▊▊▊▊▊▊╗▊▊  ▊▊╗%s\n", GREEN, END);
	ft_printf("\t ╚══════╝   ╚═════╝╚═════╝       ╚══╝     ╚═════╝╚═════╝\n");
	ft_printf("%s\n\t\tPID: %d%s\t\t%sServer Banner%s\n", YELLOW, pid, END, DARK_BLUE, END);
	ft_printf("\t────────────────────────────────────────────\n\n");
}

/**
 * convert_bits - Converts a binary string to a character.
 * @buffer: Array of '0' and '1' characters representing binary data.
 * 
 * This function processes an 8-character binary string, converting it 
 * into its equivalent ASCII character by shifting bits appropriately.
 * 
 * Return: The ASCII character corresponding to the binary string.
 */

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

/**
 * process_bits - Handles a received character from the client.
 * @client_pid: Pointer to the client's process ID.
 * @c: The received character to process.
 * 
 * If the character is the null terminator, it signals the client
 * that the transmission is complete. Otherwise, it prints the character
 * to standard output.
 */

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

/**
 * signal_handler - Handles incoming signals to process binary data.
 * @signal: The signal number received (SIGUSR1 or SIGUSR2).
 * @info: Pointer to a siginfo_t struct with sender information.
 * @context: Context pointer (unused in this implementation).
 * 
 * This function processes signals as binary input ('1' for SIGUSR1, 
 * '0' for SIGUSR2), builds characters from 8 bits, and handles them 
 * 
 * */

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

/**
 * main - Entry point for the server program.
 * 
 * Sets up the signal handlers for SIGUSR1 and SIGUSR2, displays the 
 * server banner, and enters an infinite loop to wait for signals.
 * 
 * Return: Always 0 (success).
 */

int	main(void)
{
	struct sigaction		sa;

	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
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
