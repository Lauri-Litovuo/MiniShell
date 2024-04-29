/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:10:11 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/23 16:45:40 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	init_vectors(t_vec *larg, t_shell *sh, char *buf)
{
	static char		*temp;

	while (buf[sh->i])
	{
		if (buf[sh->i] == '|')
			sh->i++;
		while (buf[sh->i] && (buf[sh->i] == ' ' || buf[sh->i] == '\t' || buf[sh->i] == '\n'))
			sh->i++;
		sh->j = sh->i;
		while (buf[sh->i] && buf[sh->i] != '|')
			sh->i++;
		temp = ft_substr(buf, sh->j, sh->i - sh->j);
		if (temp == NULL)
			return(error_msg_free(1, SUBSTR, NULL, larg));
		if (vec_push(larg, &temp) < 0)
			return (error_msg_free(1, VECPUSH, NULL, larg));
		free(temp);
		printf("larg[%zu]: %s\n", sh->k, *(char **)vec_get(larg, sh->k));
		sh->k++;
		sh->i++;
	}
	init_index(sh);
	return (1);
}

int	parse_input(t_vec *larg, t_shell *sh, char *buf)
{
	if (check_syntax(sh, buf) == -1)
		return(-1);
	if (vec_new(larg, 50, sizeof(t_vec *)) < 0)
		return (error_msg(1, VECNEW, NULL));
	while (buf[sh->i] == ' ' || buf[sh->i] == '\t' || buf[sh->i] == '\n')
		sh->i++;
	if (buf[sh->i] == '|')
		return (error_msg_free(2, SYNTX, "`|'\n", larg));
	if (init_vectors(larg, sh, &buf[sh->i]) == -1)
		return (-1);
	return (1);
}
