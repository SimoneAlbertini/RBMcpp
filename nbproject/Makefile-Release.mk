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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/RBMcpp/RBM.o \
	${OBJECTDIR}/RBMcpp/RBMbb.o \
	${OBJECTDIR}/RBMcpp/RBMglu.o \
	${OBJECTDIR}/RBMcpp/rbmUtils.o \
	${OBJECTDIR}/demo.o \
	${OBJECTDIR}/utils/ConfusionMatrix.o \
	${OBJECTDIR}/utils/FileInfo.o \
	${OBJECTDIR}/utils/SVM.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rbmcpp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rbmcpp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rbmcpp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/RBMcpp/RBM.o: RBMcpp/RBM.cpp 
	${MKDIR} -p ${OBJECTDIR}/RBMcpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RBMcpp/RBM.o RBMcpp/RBM.cpp

${OBJECTDIR}/RBMcpp/RBMbb.o: RBMcpp/RBMbb.cpp 
	${MKDIR} -p ${OBJECTDIR}/RBMcpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RBMcpp/RBMbb.o RBMcpp/RBMbb.cpp

${OBJECTDIR}/RBMcpp/RBMglu.o: RBMcpp/RBMglu.cpp 
	${MKDIR} -p ${OBJECTDIR}/RBMcpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RBMcpp/RBMglu.o RBMcpp/RBMglu.cpp

${OBJECTDIR}/RBMcpp/rbmUtils.o: RBMcpp/rbmUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/RBMcpp
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RBMcpp/rbmUtils.o RBMcpp/rbmUtils.cpp

${OBJECTDIR}/demo.o: demo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/demo.o demo.cpp

${OBJECTDIR}/utils/ConfusionMatrix.o: utils/ConfusionMatrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/ConfusionMatrix.o utils/ConfusionMatrix.cpp

${OBJECTDIR}/utils/FileInfo.o: utils/FileInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/FileInfo.o utils/FileInfo.cpp

${OBJECTDIR}/utils/SVM.o: utils/SVM.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/SVM.o utils/SVM.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rbmcpp

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
