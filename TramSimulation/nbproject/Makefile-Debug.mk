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
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/simulation/entities/TramStop.o \
	${OBJECTDIR}/src/simulation/Field.o \
	${OBJECTDIR}/src/app/Exceptions.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/simulation/entities/Entity.o \
	${OBJECTDIR}/src/tinyxml/tinyxmlparser.o \
	${OBJECTDIR}/src/simulation/Board.o \
	${OBJECTDIR}/src/simulation/entities/Tram.o \
	${OBJECTDIR}/src/tinyxml/tinyxml.o \
	${OBJECTDIR}/src/simulation/TimeSpan.o \
	${OBJECTDIR}/src/app/Application.o \
	${OBJECTDIR}/src/app/Surface.o \
	${OBJECTDIR}/src/app/Events.o \
	${OBJECTDIR}/src/simulation/entities/Vehicle.o \
	${OBJECTDIR}/src/tinyxml/tinystr.o \
	${OBJECTDIR}/src/app/Font.o \
	${OBJECTDIR}/src/simulation/Time.o \
	${OBJECTDIR}/src/simulation/entities/Car.o \
	${OBJECTDIR}/src/tinyxml/tinyxmlerror.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lSDL -lSDL_image -lSDL_ttf -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/tramsimulation

dist/Debug/GNU-Linux-x86/tramsimulation: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tramsimulation ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/simulation/entities/TramStop.o: src/simulation/entities/TramStop.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/simulation/entities
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/simulation/entities/TramStop.o src/simulation/entities/TramStop.cpp

${OBJECTDIR}/src/simulation/Field.o: src/simulation/Field.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/simulation
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/simulation/Field.o src/simulation/Field.cpp

${OBJECTDIR}/src/app/Exceptions.o: src/app/Exceptions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/app
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/app/Exceptions.o src/app/Exceptions.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/simulation/entities/Entity.o: src/simulation/entities/Entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/simulation/entities
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/simulation/entities/Entity.o src/simulation/entities/Entity.cpp

${OBJECTDIR}/src/tinyxml/tinyxmlparser.o: src/tinyxml/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tinyxml
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tinyxml/tinyxmlparser.o src/tinyxml/tinyxmlparser.cpp

${OBJECTDIR}/src/simulation/Board.o: src/simulation/Board.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/simulation
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/simulation/Board.o src/simulation/Board.cpp

${OBJECTDIR}/src/simulation/entities/Tram.o: src/simulation/entities/Tram.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/simulation/entities
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/simulation/entities/Tram.o src/simulation/entities/Tram.cpp

${OBJECTDIR}/src/tinyxml/tinyxml.o: src/tinyxml/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tinyxml
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tinyxml/tinyxml.o src/tinyxml/tinyxml.cpp

${OBJECTDIR}/src/simulation/TimeSpan.o: src/simulation/TimeSpan.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/simulation
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/simulation/TimeSpan.o src/simulation/TimeSpan.cpp

${OBJECTDIR}/src/app/Application.o: src/app/Application.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/app
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/app/Application.o src/app/Application.cpp

${OBJECTDIR}/src/app/Surface.o: src/app/Surface.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/app
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/app/Surface.o src/app/Surface.cpp

${OBJECTDIR}/src/app/Events.o: src/app/Events.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/app
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/app/Events.o src/app/Events.cpp

${OBJECTDIR}/src/simulation/entities/Vehicle.o: src/simulation/entities/Vehicle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/simulation/entities
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/simulation/entities/Vehicle.o src/simulation/entities/Vehicle.cpp

${OBJECTDIR}/src/tinyxml/tinystr.o: src/tinyxml/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tinyxml
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tinyxml/tinystr.o src/tinyxml/tinystr.cpp

${OBJECTDIR}/src/app/Font.o: src/app/Font.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/app
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/app/Font.o src/app/Font.cpp

${OBJECTDIR}/src/simulation/Time.o: src/simulation/Time.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/simulation
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/simulation/Time.o src/simulation/Time.cpp

${OBJECTDIR}/src/simulation/entities/Car.o: src/simulation/entities/Car.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/simulation/entities
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/simulation/entities/Car.o src/simulation/entities/Car.cpp

${OBJECTDIR}/src/tinyxml/tinyxmlerror.o: src/tinyxml/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tinyxml
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/tinyxml/tinyxmlerror.o src/tinyxml/tinyxmlerror.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/tramsimulation

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
