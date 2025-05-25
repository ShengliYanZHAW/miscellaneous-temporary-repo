# Author	M. Thaler
# Version	v.fs20

CMP=		gcc -std=gnu99
CMPFLAGS=	-Wall -g
LIB=		-pthread
EXENAME1=	startApp.e

INCLS=		commonDefs.h
FILES=		startApp.o coffeeTeller.o customer.o

doit:		
		@make --no-print-directory clean
		@make --no-print-directory coffeeTeller	

coffeeTeller:	$(FILES)
		$(CMP) $(CMPFLAGS) $(FILES) $(LIB) -o $(EXENAME1)

# use pattern rules instead of suffix rules to allow header dependencies
%.o: %.c $(INCLS)
	$(CMP) -c $(CMPFLAGS) $<

%.o: %.cc $(INCLS)
	$(CMP) -c $(CMPFLAGS) $<

all:
		@make clean
		make doit

clean:		
		@rm -f *.e *.o

purge:
		@make clean
