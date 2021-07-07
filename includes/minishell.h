/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 13:31:07 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/29 16:30:43 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colors.h"
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <signal.h>
# include "minishell_struct.h"

extern	t_glob	*g_glob;

int			lexer_build(t_lexer *lexer);
int			parse(t_lexer *lexer, t_ast **syntax_tree);

void		ast_attach_branch(t_ast *root, t_ast *left, t_ast *right);
void		ast_set_type(t_ast *node, t_nodetype nodetype);
void		ast_set_data(t_ast *node, char *data);
void		ast_delete_node(t_ast *node);

int			term(int toketype, char **bufferptr);

t_ast		*command_line();
t_ast		*command_line1();
t_ast		*command_line2();
t_ast		*command_line3();

t_ast		*job();
t_ast		*job1();
t_ast		*job2();

t_ast		*cmd();
t_ast		*cmd0();
t_ast		*cmd1();
t_ast		*cmd2();
t_ast		*cmd3();
t_ast		*cmd_red_out();
t_ast		*cmd_red_after();

t_ast		*simple_cmd();
t_ast		*simple_cmd1();

t_ast		*token_list();
t_ast		*token_list2();
t_ast		*token_list1();

void		run_tree(t_ms *ms, t_glob *g_glob);
void		execute_command_line(t_ast *node, t_cmd *cmd, t_glob *g_glob);
void		execute_job(t_ast *node, t_cmd *cmd, t_glob *g_glob);

void		cmd_add_redirect_in(t_cmd *cmd, char *path);
void		cmd_add_redirect_out(t_cmd *cmd, char *path);
void		cmd_add_redirect_after(t_cmd *cmd, char *path);
void		cmd_manage_pipe(t_cmd *cmd, int pipe_in, int pipe_out);

void		cmd_create_args(t_ast *node, t_cmd *cmd);
void		cmd_reset_values(t_cmd *cmd);
void		process_request(char *buf, t_glob *g_glob);

void		run_command(t_cmd *cmd, t_glob *g_glob);

char		*str_search_replace(char *str, char *search, char *replace, int i);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_tablen(char **tab);
void		ft_freetab(char **tab);
void		ft_print_lst(t_lst **lst);
void		get_export(t_glob *g_glob);
char		*get_exp_value(char *search, t_glob *g_glob);
void		ft_add_back(t_lst **alst, t_lst *new);
t_lst		*ft_env_new(char *str, int equal_pos);
char		*search_and_replace(char *name, t_glob *g_glob);
void		ft_cd_home(t_glob *g_glob, t_cmd *cmd);
void		error(t_cmd *cmd);
void		put_error_3(char *str1, char *str2, char *str3);

void		tok_init(t_tok *tok, int size);

void		check_env(t_lexer *lexer, t_glob *g_glob);
int			check_and_replace(t_lst *new, t_lst *new2, t_glob *g_glob);
int			is_a_path(char *path);
void		check_env_if_isenv(t_lexer *lexer, t_ce *ce);
void		check_env_isempty(t_lexer *lexer, t_ce *ce);
void		check_env_init_ce(t_lexer *lexer, t_ce *ce);
void		check_env_else(t_lexer *lexer, t_ce *ce);
void		check_env_while(t_ce *ce, t_lexer *lexer);
t_tok		*tok_forge(char *data, t_tok *next);

void		run_export(t_cmd *cmd, t_glob *g_glob);
void		run_pwd(t_cmd *cmd, t_glob *g_glob);
void		run_unset(t_cmd *cmd, t_glob *g_glob);
void		run_echo(t_cmd *cmd, t_glob *g_glob);
void		run_cd(t_cmd *cmd, t_glob *g_glob);
void		run_execve(t_cmd *cmd, t_glob *g_glob);
int			get_return(t_glob *g_glob);
void		del_lst(t_lst *lst);
void		run_tree(t_ms *ms, t_glob *g_glob);
void		execute_command_line(t_ast *node, t_cmd *cmd, t_glob *g_glob);
void		execute_job(t_ast *node, t_cmd *cmd, t_glob *g_glob);
void		execute_pipe(t_ast *node, t_cmd *cmd, t_glob *g_glob);
void		execute_command(t_ast *node, t_cmd *cmd, t_glob *g_glob);
void		execute_simple_command(t_ast *node, t_cmd *cmd, t_glob *g_glob);
void		free_command(t_cmd *cmd);

void		tok_init(t_tok *tok, int size);
char		*format_data(t_tok *tok);
int			lexer_special_case(t_lexer *l);
void		check_tokens(t_lexer *l);

void		lexer_char_null(t_lexer *l);

void		lexer_special_char(t_lexer *l);
void		lexer_char_quotes_esc_general(t_lexer *l);
int			get_char_type(char c);

void		handle_redirect(t_cmd *cmd);
char		*concat_path(char *str1, char *str2, char *str3);
int			is_a_path(char *path);
char		*try_and_get_path(t_cmd *cmd, t_glob *g_glob);
void		init_glob(t_glob *g_glob);
extern	t_tok	*g_curtok;

#endif
