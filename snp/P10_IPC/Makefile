
# Define explicit Linux-style paths for WSL compatibility
CURDIR_WSL := $(shell wsl pwd)
ifeq ($(CURDIR_WSL),)
  # Fallback if wsl command doesn't work in the build context
  CURDIR_WSL := /mnt/c/Users/sheng/git_repos/miscellaneous-temporary-repo/snp/P10_IPC
endif

# Convert Windows paths to WSL paths for better compatibility
SNP_SHARED_MAKEFILE_WSL := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),$(CURDIR_WSL)/../../shared.mk)
SNP_TESTLIB_WSL := $(if $(SNP_TESTLIB),$(SNP_TESTLIB),$(CURDIR_WSL)/../../testlib)
SNP_DOXYFILE_WSL := $(if $(SNP_DOXYFILE),$(SNP_DOXYFILE),$(CURDIR_WSL)/../../Doxyfile)

# Define path variables for Windows compatibility
SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),../../shared.mk)
SNP_TESTLIB := $(if $(SNP_TESTLIB),$(SNP_TESTLIB),../../testlib)
SNP_DOXYFILE := $(if $(SNP_DOXYFILE),$(SNP_DOXYFILE),../../Doxyfile)

# Include the shared makefile after defining variables
-include $(SNP_SHARED_MAKEFILE)
# Also include WSL version as a fallback if we're running in WSL
-include $(SNP_SHARED_MAKEFILE_WSL)


# Define the TARGET for the shared makefile (needed for tests)
TARGET          := bin/person_server
# Add SOURCES variable required by shared.mk
SOURCES         := $(SERVER_SOURCES)

# Define C compiler flags
CFLAGS          += -Wall -pedantic -std=c99
CPPFLAGS        += -Isrc -I$(SNP_TESTLIB)/include

SERVER_SOURCES    := src/person_server.c src/tcp_server.c src/snp_error_handler.c src/person.c src/list.c
SERVER_HEADERS    := $(SERVER_SOURCES:%.c=%.h)
SERVER_OBJECTS    := $(SERVER_SOURCES:%.c=%.o)    # list of gcc -c  ... produced *.o files

CLIENT_SOURCES    := src/person_client.c src/tcp_client.c src/snp_error_handler.c src/person.c
CLIENT_HEADERS    := $(CLIENT_SOURCES:%.c=%.h)
CLIENT_OBJECTS    := $(CLIENT_SOURCES:%.c=%.o)    # list of gcc -c  ... produced *.o files

TCP_CLIENT_SOURCES    := src/test_tcp_client.c src/tcp_client.c src/snp_error_handler.c src/person.c
TCP_CLIENT_HEADERS    := $(TCP_CLIENT_SOURCES:%.c=%.h)
TCP_CLIENT_OBJECTS    := $(TCP_CLIENT_SOURCES:%.c=%.o)    # list of gcc -c  ... produced *.o files

TCP_SERVER_SOURCES    := src/test_tcp_server.c src/tcp_server.c src/snp_error_handler.c src/person.c
TCP_SERVER_HEADERS    := $(TCP_SERVER_SOURCES:%.c=%.h)
TCP_SERVER_OBJECTS    := $(TCP_SERVER_SOURCES:%.c=%.o)    # list of gcc -c  ... produced *.o files

DEPS              := $(SERVER_SOURCES:%.c=%.d) $(CLIENT_SOURCES:%.c=%.d)    # list of gcc -MD ... produced *.d files
# Add dependencies for the test files
TSTDEPS          := $(TSTSOURCES:%.c=%.d)

CREATEDIRS    := bin doc tests

TSTSOURCES        := tests/tests.c

default: all
	@echo "#### $@ is $< ####"

.PHONY: default all clean mkdir test

# directories to create (and remove upon cleanup)

all: mkdir bin/person_client bin/person_server bin/tcp_server bin/tcp_client
	@echo "#### $@ built ####"
	
# Define variables needed for testing
TSTTARGET ?= tests/runtest
TSTOBJECTS ?= $(TSTSOURCES:.c=.o)
TSTLIBDIR ?= $(SNP_TESTLIB)/lib
TSTINCDIR ?= $(SNP_TESTLIB)/include

# Define our own test target to work in both Windows and WSL
test: mkdir
	@echo "Running tests for P10_IPC"
	@mkdir -p tests
	
	# Direct approach - compile and run tests
	cd tests && \
		export SNP_TESTLIB=/mnt/c/Users/sheng/git_repos/miscellaneous-temporary-repo/snp/testlib && \
		gcc -Wall -pedantic -std=c99 -I../src -I$$SNP_TESTLIB/include tests.c -o runtest -L$$SNP_TESTLIB/lib -lcunit -lsnptest && \
		./runtest
	@echo "#### Tests executed ####"

$(TSTTARGET): $(TARGET) $(TSTOBJECTS)
	@mkdir -p tests
	$(LINK.c) -o $@ $(TSTOBJECTS) -L$(TSTLIBDIR) -lsnptest
  
bin/person_server: $(SERVER_OBJECTS)
	gcc -o $@ $^ 

bin/person_client: $(CLIENT_OBJECTS)
	gcc -o $@ $^ 

bin/tcp_server: $(TCP_SERVER_OBJECTS)
	gcc -o $@ $^ 

bin/tcp_client: $(TCP_CLIENT_OBJECTS)
	gcc -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	
# Compile rule for test objects to ensure proper include paths
tests/%.o: tests/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I/mnt/c/Users/sheng/git_repos/miscellaneous-temporary-repo/snp/testlib/include -c -o $@ $<

# create needed directories (ignoring any error)
mkdir:
	mkdir -p $(CREATEDIRS)

clean:
	$(RM) $(SERVER_OBJECTS) $(CLIENT_OBJECTS) $(TCP_SERVER_OBJECTS) $(TCP_CLIENT_OBJECTS) $(DEPS) $(TSTDEPS) tests/*.o tests/runtest
	$(RM) -r $(CREATEDIRS)
	@echo "#### $@ done ####"






