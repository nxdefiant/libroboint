AM_CPPFLAGS = -I$(srcdir)/../lib

# try to avoid trouble on OS-X
if DARWIN_API
else
bin_PROGRAMS = example
example_SOURCES = test.c
example_LDADD = -L$(srcdir)/../lib -lft
noinst_PROGRAMS = example
endif

