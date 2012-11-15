#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/EndCurrentPathRequest.o \
	${OBJECTDIR}/OwnershipRequest.o \
	${OBJECTDIR}/InputData.o \
	${OBJECTDIR}/Point.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/Painter.o \
	${OBJECTDIR}/RedoRequest.o \
	${OBJECTDIR}/NewPathRequest.o \
	${OBJECTDIR}/LoginRequest.o \
	${OBJECTDIR}/DeletePathRequest.o \
	${OBJECTDIR}/AddPointsToPathRequest.o \
	${OBJECTDIR}/Color.o \
	${OBJECTDIR}/Receiver.o \
	${OBJECTDIR}/UndoRequest.o \
	${OBJECTDIR}/PalmRejection.o \
	${OBJECTDIR}/Request.o \
	${OBJECTDIR}/FileListAvailableRequest.o \
	${OBJECTDIR}/Path.o \
	${OBJECTDIR}/ScreenAreas.o \
	${OBJECTDIR}/Sender.o \
	${OBJECTDIR}/ScribbleArea.o \
	${OBJECTDIR}/LogoutRequest.o \
	${OBJECTDIR}/UI.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lglut -lGL -lGLU -lboost_thread-mt
CXXFLAGS=-lglut -lGL -lGLU -lboost_thread-mt

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/scribble_gl

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/scribble_gl: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/scribble_gl ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/EndCurrentPathRequest.o: EndCurrentPathRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/EndCurrentPathRequest.o EndCurrentPathRequest.cpp

${OBJECTDIR}/OwnershipRequest.o: OwnershipRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/OwnershipRequest.o OwnershipRequest.cpp

${OBJECTDIR}/InputData.o: InputData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/InputData.o InputData.cpp

${OBJECTDIR}/Point.o: Point.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/Point.o Point.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/Painter.o: Painter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/Painter.o Painter.cpp

${OBJECTDIR}/RedoRequest.o: RedoRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/RedoRequest.o RedoRequest.cpp

${OBJECTDIR}/NewPathRequest.o: NewPathRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/NewPathRequest.o NewPathRequest.cpp

${OBJECTDIR}/LoginRequest.o: LoginRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/LoginRequest.o LoginRequest.cpp

${OBJECTDIR}/DeletePathRequest.o: DeletePathRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/DeletePathRequest.o DeletePathRequest.cpp

${OBJECTDIR}/AddPointsToPathRequest.o: AddPointsToPathRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/AddPointsToPathRequest.o AddPointsToPathRequest.cpp

${OBJECTDIR}/Color.o: Color.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/Color.o Color.cpp

${OBJECTDIR}/Receiver.o: Receiver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/Receiver.o Receiver.cpp

${OBJECTDIR}/UndoRequest.o: UndoRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/UndoRequest.o UndoRequest.cpp

${OBJECTDIR}/PalmRejection.o: PalmRejection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/PalmRejection.o PalmRejection.cpp

${OBJECTDIR}/Request.o: Request.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/Request.o Request.cpp

${OBJECTDIR}/FileListAvailableRequest.o: FileListAvailableRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/FileListAvailableRequest.o FileListAvailableRequest.cpp

${OBJECTDIR}/Path.o: Path.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/Path.o Path.cpp

${OBJECTDIR}/ScreenAreas.o: ScreenAreas.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/ScreenAreas.o ScreenAreas.cpp

${OBJECTDIR}/Sender.o: Sender.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/Sender.o Sender.cpp

${OBJECTDIR}/ScribbleArea.o: ScribbleArea.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/ScribbleArea.o ScribbleArea.cpp

${OBJECTDIR}/LogoutRequest.o: LogoutRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/LogoutRequest.o LogoutRequest.cpp

${OBJECTDIR}/UI.o: UI.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -MMD -MP -MF $@.d -o ${OBJECTDIR}/UI.o UI.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/scribble_gl

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
