# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfranco <gfranco@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/10 12:13:05 by gfranco           #+#    #+#              #
#    Updated: 2019/05/08 15:31:33 by gfranco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors.

ORANGE =	\033[1;33m   #It is actually Yellow, but i changed yellow to orange.

GREEN =		\033[1;32m

RED =		\033[1;31m

RES =		\033[0m

#------------------------------------------------------------------------------#

NAME = 		rtv1

SRCDIR =	./srcs

INCDIR =	./includes

OBJDIR =	./objs

SRC =		cone.c cone_check.c cone_fill.c cylinder.c cylinder_check.c        \
			cylinder_fill.c event.c extract_data.c lexer.c light_check.c       \
			light_fill.c main.c objects_check.c parser.c plane.c plane_check.c \
			plane_fill.c sphere.c sphere_check.c sphere_fill.c

INC =		rtv1.h

SRCS =		$(SRC:%=$(SRCDIR)/%)

OBJS =		$(SRC:%.c=$(OBJDIR)/%.o)

INCS =		$(INC:%=$(INCDIR)/%)

LIBDIR =	./libft

LIBNAME =	libft.a

LIB =		$(LIBDIR)/$(LIBNAME)

LIBINC =	$(LIBDIR)

#------------------------------------------------------------------------------#

CC =		clang

CFLAGS =	-Wall			\
			-Wextra			\
			-Werror			\
			-g				\

INCFLAGS =	-I $(INCDIR)			\
			-I $(LIBINC)			\
			-I /usr/local/include

LFLAGS =	-L $(LIBDIR) -l$(LIBNAME:lib%.a=%)	\
			-L /usr/local/lib -lmlx -framework OpenGL -framework AppKit	\
			-lpthread

FLAGS =		$(CFLAGS)		\
			$(INCFLAGS)

#------------------------------------------------------------------------------#
# Primary rules

all:
	@$(MAKE) -C $(LIBDIR)
	@$(MAKE) $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $@ $^ $(LFLAGS)

$(OBJS): $(INCS) $(LIB)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -o $@ -c $<

clean:
	@$(MAKE) -C $(LIBDIR) fclean
	@rm -rf $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	@$(MAKE) -C $(LIBDIR) fclean
	@rm -rf $(NAME)

re: fclean
	@$(MAKE) all

.PHONY: all clean re fclean
