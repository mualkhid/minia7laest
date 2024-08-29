# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/20 18:51:49 by mualkhid          #+#    #+#              #
#    Updated: 2024/08/29 12:30:39 by mualkhid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
SRC		= minishell.c\
		bonus/logical_operators.c\
        bonus/wildcards.c\
        bonus/wildcards2.c\
        builtin/builtin_functions.c\
        builtin/cd_cmd.c\
        builtin/echo_cmd.c\
        builtin/env_cmd.c\
        builtin/exit_cmd.c\
        builtin/export_cmd.c\
        builtin/export_utils.c\
        builtin/pwd_cmd.c\
        builtin/unset_cmd.c\
        execution/transformation.c\
        execution/cmd_init.c\
        execution/exec_redirections.c\
        execution/execute_cmd.c\
        execution/execute_child.c\
        execution/path_finder.c\
        execution/get_cmd.c\
        execution/redir_in.c\
        execution/redir_out.c\
        parsing/validate_cmd.c\
        parsing/parse_cmd.c\
        parsing/strdup_utils.c\
        parsing/strjoin_utils.c\
        parsing/expand_vars.c\
        parsing/preprocessing_cmd.c\
        parsing/split_utils.c\
        parsing/parse_redir.c\
        signals/signal.c\
        signals/signal_heredoc.c\
        utils/shlvl.c\
        utils/utils.c\
        utils/utils_str.c\
        utils/utils_aos.c\
        header.c\

SRCBONUS= bonus.c

OBJ		= $(patsubst %.c, %.o, $(SRC))

OBJS		= $(addprefix ${OBJDIR}, ${OBJ})

SRCDIR	= src/
OBJDIR	= obj/
LIBDIR	= includes
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
LFLAGS	= -lreadline

OBJDIRS = $(OBJDIR) $(OBJDIR)/bonus $(OBJDIR)/builtin $(OBJDIR)/execution $(OBJDIR)/parsing $(OBJDIR)/signals

all: $(OBJDIRS) $(NAME)

$(OBJDIRS):
	@mkdir -p $@

$(NAME): libft/libft.a $(OBJS)
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@printf "%-16s" "Linking "
	@tput sgr0
	@tput setaf 6
	@echo "${@}"
	@$(CC) -o $(NAME) $(addprefix $(OBJDIR),$(OBJ)) libft/libft.a $(LFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@make print_name --no-print-directory
	@mkdir -p $(dir $@)
	@tput bold
	@tput setaf 2
	@printf "%-16s" "Compiling "
	@tput sgr0
	@tput setaf 6
	@echo "${@}"
	@$(CC) $(LFLAGS) $(CFLAGS) -c -I $(LIBDIR) -o $@ $<

clean:
	@/bin/rm -f $(addprefix $(OBJDIR),$(OBJ))
	@/bin/rm -f $(addprefix $(OBJDIR),$(OBJBONUS))
	@/bin/rm -rf $(OBJDIR)
	@make clean -C ./libft --no-print-directory
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@echo "clean done"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C ./libft --no-print-directory
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@echo "fclean done"


libft/libft.a:
	@make bonus -C ./libft --no-print-directory

print_name:
	@tput bold
	@tput setaf 208
	@printf "%-10s " $(NAME)

bonus: all

re: fclean all

.PHONY: all clean fclean re bonus print_name
