INCLUDES = -Iinclude -I../ffmpeg/builds/3gs -I../ffmpeg
##### Change the following for your environment: 
COMPILE_OPTS =          $(INCLUDES) -I. $(EXTRA_LDFLAGS) -DBSD=1 -O2 -DSOCKLEN_T=socklen_t -DHAVE_SOCKADDR_LEN=1 -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -fPIC -arch armv7 --sysroot=/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.2.sdk
C =                     c
C_COMPILER =            /Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/gcc
C_FLAGS =               $(COMPILE_OPTS)
CPP =                   cpp
CPLUSPLUS_COMPILER =    /Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/g++
CPLUSPLUS_FLAGS =       $(COMPILE_OPTS) -Wall
OBJ =                   o
LINK =                  /Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/g++ -o 
LINK_OPTS =             -L. -arch armv7 --sysroot=/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS4.2.sdk
CONSOLE_LINK_OPTS =     $(LINK_OPTS)
LIBRARY_LINK =          ar cr 
LIBRARY_LINK_OPTS =
LIB_SUFFIX =            a
LIBS_FOR_CONSOLE_APPLICATION =
LIBS_FOR_GUI_APPLICATION =
EXE =
##### End of variables to change


LIB = libFfmpegWrapper.$(LIB_SUFFIX)
ALL = $(LIB)
all:	$(ALL)

OBJS = libFfmpegWrapper.$(OBJ) 

libFfmpegWrapper.$(LIB_SUFFIX): $(OBJS)
	$(LIBRARY_LINK)$@ $(LIBRARY_LINK_OPTS) \
		$(OBJS)

.$(C).$(OBJ):
	$(C_COMPILER) -c $(C_FLAGS) $<       

.$(CPP).$(OBJ):
	$(CPLUSPLUS_COMPILER) -c $(CPLUSPLUS_FLAGS) $<

libFfmpegWrapper.$(CPP):	include/FfmpegWrapper.h

clean:
	-rm -rf *.$(OBJ) $(ALL) core *.core *~ include/*~

##### Any additional, platform-specific rules come here:
