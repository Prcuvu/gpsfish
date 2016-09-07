GPSSHOGI_HOME = ../../gpsshogi
ifdef PROFILE
RELEASE = true
endif

-include makefile.local
include $(GPSSHOGI_HOME)/makefile.conf


.deps/%.cpp.d: %.cpp
	if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi; 
	$(GXX) -MM $(CXX_CPP_FLAGS) $< \
		| sed 's/\(.*\.o\)[ :]*/$(subst /,\/,$(patsubst .deps/%.cpp.d,%.o,$@)) $(subst /,\/,$@) : /g' > $@
	grep $< $@ > /dev/null 2>&1 || (rm -f $@; false)

# INCLUDES += -I../lib
LOADLIBES += -lboost_thread$(BOOST_POSTFIX_MT) -lboost_program_options$(BOOST_POSTFIX) -lpthread

## #gcc
OTHERFLAGS = -pipe $(CPUOPTION)
ifdef DEBUG
CXXOPTFLAGS = -O
OTHERFLAGS += -g -DDEBUG 
else
CXXOPTFLAGS = $(RELEASE_CXX_OPTFLAGS)
WARNING_FLAGS += $(WARN_INLINE)
ifdef RELEASE
OTHERFLAGS +=  -DNDEBUG
endif
ifndef PROF
CXXOPTFLAGS += -fomit-frame-pointer
endif
endif

OTHERFLAGS += -DGPSFISH -DPROMOTE_AS_CAPTURE

# prefetch
OTHERFLAGS += -msse
# no prefetch
# OTHERFLAGS += -DNO_PREFETCH

CXXOPTFLAGS += -std=c++0x
# INCLUDES += -I../lib
CXXFLAGS = $(PROF) $(OTHERFLAGS) $(CXXOPTFLAGS) $(WARNING_FLAGS) $(INCLUDES)

SRCS = benchmark.cpp misc.cpp timeman.cpp evaluate.cpp move.cpp position.cpp tt.cpp main.cpp movegen.cpp search.cpp uci.cpp book.cpp movepick.cpp thread.cpp ucioption.cpp
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
OSL_HOME_FLAGS = -DOSL_HOME=\"$(shell dirname `dirname \`pwd\``)/osl\"
CC = $(CXX)

all: 
	$(MAKE) programs RELEASE=t

programs : gpsfish

gpsfish: $(OBJS) $(FILE_OSL_ALL)
	$(CXX) -o $@ $(CXXFLAGS) $(PROFILE_USE) $(LDFLAGS) $(OBJS) $(FILE_OSL_ALL) $(LDLIBS) $(LOADLIBES) -lbz2

gpsfishoneprof: mainone.cc
	$(CXX) -o $@ $(CXXFLAGS) $(OSL_HOME_FLAGS) $(PROFILE_GENERATE) $(LDFLAGS) $< $(LDLIBS) $(LOADLIBES) -lbz2

gpsfishone: mainone.cc mainone.gcda gpsfishoneprof
	$(CXX) -o $@ $(CXXFLAGS) $(OSL_HOME_FLAGS) $(PROFILE_USE) $(LDFLAGS) $< $(LDLIBS) $(LOADLIBES) -lbz2

update-gpsfishone:
	-rm gpsfishone gpsfishoneprof
	$(MAKE) gpsfishoneprof RELEASE=t
	$(MAKE) run-profile
	$(MAKE) gpsfishone RELEASE=t

run-profile: gpsfishoneprof
	./gpsfishoneprof bench 32 1 12 default depth

clean:
	-rm *.o $(PROGRAM)
	-rm -rf .deps

light-clean:
	-rm -rf .deps .objs .gch 

-include $(patsubst %.cpp,.deps/%.cpp.d,$(SRCS))

.PHONY: all clean light-clean run-profile update-gpsusione
