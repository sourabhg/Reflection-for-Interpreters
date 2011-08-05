.PHONY: all
all: tinyinterp codegen # libA.so libB.so

##########################################

#
# tinyinterp
#

TinyInterpSrcs := \
	MetaInfo.cpp \
	main.cpp \
	Node.cpp \
	ParseContext.cpp \
	Parser.tab.cc \
    Reflection.cpp \
	Token.cpp \
	Value.cpp \

TinyInterpObjs := $(TinyInterpSrcs:.cpp=.o)
TinyInterpObjs := $(TinyInterpObjs:.cc=.o)

#
# codegen
#

CodegenSrcs := \
	codegen.cpp \
	Emitter.cpp \

CodegenObjs := $(CodegenSrcs:.cpp=.o)

#######################################

Srcs := $(TinyInterpSrcs) $(CodegenSrcs) $(LibASrcs) $(LibBSrcs)
Deps := $(patsubst %,.%.do,$(basename $(Srcs)))

CPPFLAGS = -MMD -MF $(basename .$(@F)).do -I/usr/include/libxml2
CXXFLAGS := -Wall -Wno-unused -Wno-parentheses -g -Wl,-E

#######################################

tinyinterp: $(TinyInterpObjs) Parser.tab.o
	g++ -$(CXXFLAGS) -o tinyinterp $(TinyInterpObjs) -ldl

$(TinyInterpObjs): Parser.tab.hh

Parser.tab.cc Parser.tab.hh: Parser.yy
	bison Parser.yy

codegen: $(CodegenObjs)
	g++ -g -o codegen $(CodegenObjs) -lxml2

-include $(Deps)

.PHONY: clean
clean:
	rm -f .*.do Parser.tab.cc Parser.tab.hh location.hh position.hh stack.hh *_meta.* *.o *.so *.xml tinyinterp codegen core.* core vgcore.*
