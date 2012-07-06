##
## Makefile
##
## Fiahil
## Fri Mar 16 2012
##

NAME	=	drone

ML	=	socket.ml	\
		bridge.ml	\
		fsm.ml		\
		fsmBase.ml	\
		main.ml

MLI	=	socket.mli	\
		bridge.mli	\
		fsmBase.mli

CMO	=	$(ML:.ml=.cmo)

CMI	=	$(MLI:.mli=.cmi)

CMX	=	$(ML:.ml=.cmx)

FLAGS	=	-w Aelz

CC	=	ocamlopt

INC	=	unix.cma str.cma

INCX	=	unix.cmxa str.cmxa

%.cmx: %.ml
	$(CC) $(INCX) -o $@		-c $<	$(FLAGS)

%.cmo: %.ml
	$(CC) $(INCX) -o $@		-c $<	$(FLAGS)

%.cmi: %.mli
	$(CC) $(INCX) -o $@		-c $<	$(FLAGS)

all:	.dep $(CMI) $(NAME)

$(NAME):	$(CMX)
	$(CC) $(INCX) -o $(NAME) $(CMX)

byte:	CC = ocamlc
byte:	INCX = $(INC)
byte:	clean $(CMI) $(CMO)
	$(CC) $(INC) -o $(NAME) $(CMO)

clean:
	@rm -f $(CMO) $(CMX) $(CMI) *.o *.cmi *.cmo *.cmx && echo "clean done"

fclean:	clean
	@rm -f $(NAME) && echo "fclean done"

re:	fclean all

.dep:
	@rm -f .depend
	@ocamldep $(MLI) $(ML) > .depend

-include .depend
