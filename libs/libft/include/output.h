/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:47:08 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/02 21:35:27 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(OUTPUT_H)
# define OUTPUT_H

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif // OUTPUT_H
