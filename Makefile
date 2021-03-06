#
# Created by gmakemake (Ubuntu Sep  7 2011) on Tue May 22 17:02:30 2012
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CXXFLAGS=-O3 -DNDEBUG

########## End of flags from header.mak


CPP_FILES =	count_colorings.cpp graph.cpp sample.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	graph.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	graph.o 

#
# Main targets
#

all:	count_colorings sample 

count_colorings:	count_colorings.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o count_colorings count_colorings.o $(OBJFILES) $(CCLIBFLAGS)

sample:	sample.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o sample sample.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

count_colorings.o:	graph.h
graph.o:	graph.h
sample.o:	graph.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) count_colorings.o sample.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf count_colorings sample 
