#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dyioMplab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dyioMplab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/Application/CartesianController.c ../src/Application/PID.c ../src/BowlerCallbacks/InitializationCallbacks.c ../src/BowlerCallbacks/AsyncManager.c ../src/BowlerCallbacks/UpstreamPackets.c ../src/BowlerCallbacks/DownStreamPackets.c ../src/Drivers/dma/UartDMARx.c ../src/Drivers/CoProcCom.c ../src/Drivers/SPI.c ../src/Drivers/Switches.c ../src/Drivers/PPMReader.c ../src/Drivers/EEPROMMannager.c ../src/Drivers/Counter.c ../src/Drivers/SerialPassThrough.c ../src/Drivers/ADC.c ../src/Drivers/DyIODataTableManager.c ../../common/src/dyio/PinFunctions.c ../src/DyIO/ChannelMode.c ../src/DyIO/ChannelValues.c ../src/DyIO/ChannelConfig.c ../../common/src/Namespace_bcs_io/Namespace_bcs_io.c ../../common/src/Namespace_bcs_io/Abstract_bcs_io.c ../../common/src/Namespace_bcs_io/Debug_DyIO.c ../../common/src/Namespace_bcs_io/Bcs_IO_AdvancedAsync.c ../../common/src/Namespace_bcs_io_setmode/Abstract_bcs_io_setmode.c ../../common/src/Namespace_bcs_io_setmode/Namespace_bcs_io_setmode.c ../src/Namespace_bcs_safe/Abstract_bsc_safe.c ../src/Namespace_bcs_safe/Namespace_bcs_safe.c ../src/Namespace_dyio/Namespace_neuronrobotics_dyio.c ../src/Namespace_dyio/Namespace_bcs_pid_dypid.c ../src/Main.c ../src/DyIOMain.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1825615050/CartesianController.o ${OBJECTDIR}/_ext/1825615050/PID.o ${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o ${OBJECTDIR}/_ext/1978776677/AsyncManager.o ${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o ${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o ${OBJECTDIR}/_ext/2110062566/UartDMARx.o ${OBJECTDIR}/_ext/990863823/CoProcCom.o ${OBJECTDIR}/_ext/990863823/SPI.o ${OBJECTDIR}/_ext/990863823/Switches.o ${OBJECTDIR}/_ext/990863823/PPMReader.o ${OBJECTDIR}/_ext/990863823/EEPROMMannager.o ${OBJECTDIR}/_ext/990863823/Counter.o ${OBJECTDIR}/_ext/990863823/SerialPassThrough.o ${OBJECTDIR}/_ext/990863823/ADC.o ${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o ${OBJECTDIR}/_ext/108654538/PinFunctions.o ${OBJECTDIR}/_ext/1020318379/ChannelMode.o ${OBJECTDIR}/_ext/1020318379/ChannelValues.o ${OBJECTDIR}/_ext/1020318379/ChannelConfig.o ${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o ${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o ${OBJECTDIR}/_ext/805493626/Debug_DyIO.o ${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o ${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o ${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o ${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o ${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o ${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o ${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o ${OBJECTDIR}/_ext/1360937237/Main.o ${OBJECTDIR}/_ext/1360937237/DyIOMain.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1825615050/CartesianController.o.d ${OBJECTDIR}/_ext/1825615050/PID.o.d ${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o.d ${OBJECTDIR}/_ext/1978776677/AsyncManager.o.d ${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o.d ${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o.d ${OBJECTDIR}/_ext/2110062566/UartDMARx.o.d ${OBJECTDIR}/_ext/990863823/CoProcCom.o.d ${OBJECTDIR}/_ext/990863823/SPI.o.d ${OBJECTDIR}/_ext/990863823/Switches.o.d ${OBJECTDIR}/_ext/990863823/PPMReader.o.d ${OBJECTDIR}/_ext/990863823/EEPROMMannager.o.d ${OBJECTDIR}/_ext/990863823/Counter.o.d ${OBJECTDIR}/_ext/990863823/SerialPassThrough.o.d ${OBJECTDIR}/_ext/990863823/ADC.o.d ${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o.d ${OBJECTDIR}/_ext/108654538/PinFunctions.o.d ${OBJECTDIR}/_ext/1020318379/ChannelMode.o.d ${OBJECTDIR}/_ext/1020318379/ChannelValues.o.d ${OBJECTDIR}/_ext/1020318379/ChannelConfig.o.d ${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o.d ${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o.d ${OBJECTDIR}/_ext/805493626/Debug_DyIO.o.d ${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o.d ${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o.d ${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o.d ${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o.d ${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o.d ${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o.d ${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o.d ${OBJECTDIR}/_ext/1360937237/Main.o.d ${OBJECTDIR}/_ext/1360937237/DyIOMain.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1825615050/CartesianController.o ${OBJECTDIR}/_ext/1825615050/PID.o ${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o ${OBJECTDIR}/_ext/1978776677/AsyncManager.o ${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o ${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o ${OBJECTDIR}/_ext/2110062566/UartDMARx.o ${OBJECTDIR}/_ext/990863823/CoProcCom.o ${OBJECTDIR}/_ext/990863823/SPI.o ${OBJECTDIR}/_ext/990863823/Switches.o ${OBJECTDIR}/_ext/990863823/PPMReader.o ${OBJECTDIR}/_ext/990863823/EEPROMMannager.o ${OBJECTDIR}/_ext/990863823/Counter.o ${OBJECTDIR}/_ext/990863823/SerialPassThrough.o ${OBJECTDIR}/_ext/990863823/ADC.o ${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o ${OBJECTDIR}/_ext/108654538/PinFunctions.o ${OBJECTDIR}/_ext/1020318379/ChannelMode.o ${OBJECTDIR}/_ext/1020318379/ChannelValues.o ${OBJECTDIR}/_ext/1020318379/ChannelConfig.o ${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o ${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o ${OBJECTDIR}/_ext/805493626/Debug_DyIO.o ${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o ${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o ${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o ${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o ${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o ${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o ${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o ${OBJECTDIR}/_ext/1360937237/Main.o ${OBJECTDIR}/_ext/1360937237/DyIOMain.o

# Source Files
SOURCEFILES=../src/Application/CartesianController.c ../src/Application/PID.c ../src/BowlerCallbacks/InitializationCallbacks.c ../src/BowlerCallbacks/AsyncManager.c ../src/BowlerCallbacks/UpstreamPackets.c ../src/BowlerCallbacks/DownStreamPackets.c ../src/Drivers/dma/UartDMARx.c ../src/Drivers/CoProcCom.c ../src/Drivers/SPI.c ../src/Drivers/Switches.c ../src/Drivers/PPMReader.c ../src/Drivers/EEPROMMannager.c ../src/Drivers/Counter.c ../src/Drivers/SerialPassThrough.c ../src/Drivers/ADC.c ../src/Drivers/DyIODataTableManager.c ../../common/src/dyio/PinFunctions.c ../src/DyIO/ChannelMode.c ../src/DyIO/ChannelValues.c ../src/DyIO/ChannelConfig.c ../../common/src/Namespace_bcs_io/Namespace_bcs_io.c ../../common/src/Namespace_bcs_io/Abstract_bcs_io.c ../../common/src/Namespace_bcs_io/Debug_DyIO.c ../../common/src/Namespace_bcs_io/Bcs_IO_AdvancedAsync.c ../../common/src/Namespace_bcs_io_setmode/Abstract_bcs_io_setmode.c ../../common/src/Namespace_bcs_io_setmode/Namespace_bcs_io_setmode.c ../src/Namespace_bcs_safe/Abstract_bsc_safe.c ../src/Namespace_bcs_safe/Namespace_bcs_safe.c ../src/Namespace_dyio/Namespace_neuronrobotics_dyio.c ../src/Namespace_dyio/Namespace_bcs_pid_dypid.c ../src/Main.c ../src/DyIOMain.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/dyioMplab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX440F128H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1825615050/CartesianController.o: ../src/Application/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825615050 
	@${RM} ${OBJECTDIR}/_ext/1825615050/CartesianController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825615050/CartesianController.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825615050/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1825615050/CartesianController.o.d" -o ${OBJECTDIR}/_ext/1825615050/CartesianController.o ../src/Application/CartesianController.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1825615050/PID.o: ../src/Application/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825615050 
	@${RM} ${OBJECTDIR}/_ext/1825615050/PID.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825615050/PID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825615050/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1825615050/PID.o.d" -o ${OBJECTDIR}/_ext/1825615050/PID.o ../src/Application/PID.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o: ../src/BowlerCallbacks/InitializationCallbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1978776677 
	@${RM} ${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o.d" -o ${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o ../src/BowlerCallbacks/InitializationCallbacks.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1978776677/AsyncManager.o: ../src/BowlerCallbacks/AsyncManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1978776677 
	@${RM} ${OBJECTDIR}/_ext/1978776677/AsyncManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1978776677/AsyncManager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1978776677/AsyncManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1978776677/AsyncManager.o.d" -o ${OBJECTDIR}/_ext/1978776677/AsyncManager.o ../src/BowlerCallbacks/AsyncManager.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o: ../src/BowlerCallbacks/UpstreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1978776677 
	@${RM} ${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o.d 
	@${RM} ${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o.d" -o ${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o ../src/BowlerCallbacks/UpstreamPackets.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o: ../src/BowlerCallbacks/DownStreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1978776677 
	@${RM} ${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o.d 
	@${RM} ${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o.d" -o ${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o ../src/BowlerCallbacks/DownStreamPackets.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/2110062566/UartDMARx.o: ../src/Drivers/dma/UartDMARx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2110062566 
	@${RM} ${OBJECTDIR}/_ext/2110062566/UartDMARx.o.d 
	@${RM} ${OBJECTDIR}/_ext/2110062566/UartDMARx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2110062566/UartDMARx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2110062566/UartDMARx.o.d" -o ${OBJECTDIR}/_ext/2110062566/UartDMARx.o ../src/Drivers/dma/UartDMARx.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/CoProcCom.o: ../src/Drivers/CoProcCom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/CoProcCom.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/CoProcCom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/CoProcCom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/CoProcCom.o.d" -o ${OBJECTDIR}/_ext/990863823/CoProcCom.o ../src/Drivers/CoProcCom.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/SPI.o: ../src/Drivers/SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/SPI.o.d" -o ${OBJECTDIR}/_ext/990863823/SPI.o ../src/Drivers/SPI.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/Switches.o: ../src/Drivers/Switches.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/Switches.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/Switches.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/Switches.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/Switches.o.d" -o ${OBJECTDIR}/_ext/990863823/Switches.o ../src/Drivers/Switches.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/PPMReader.o: ../src/Drivers/PPMReader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/PPMReader.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/PPMReader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/PPMReader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/PPMReader.o.d" -o ${OBJECTDIR}/_ext/990863823/PPMReader.o ../src/Drivers/PPMReader.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/EEPROMMannager.o: ../src/Drivers/EEPROMMannager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/EEPROMMannager.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/EEPROMMannager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/EEPROMMannager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/EEPROMMannager.o.d" -o ${OBJECTDIR}/_ext/990863823/EEPROMMannager.o ../src/Drivers/EEPROMMannager.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/Counter.o: ../src/Drivers/Counter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/Counter.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/Counter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/Counter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/Counter.o.d" -o ${OBJECTDIR}/_ext/990863823/Counter.o ../src/Drivers/Counter.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/SerialPassThrough.o: ../src/Drivers/SerialPassThrough.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/SerialPassThrough.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/SerialPassThrough.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/SerialPassThrough.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/SerialPassThrough.o.d" -o ${OBJECTDIR}/_ext/990863823/SerialPassThrough.o ../src/Drivers/SerialPassThrough.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/ADC.o: ../src/Drivers/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/ADC.o.d" -o ${OBJECTDIR}/_ext/990863823/ADC.o ../src/Drivers/ADC.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o: ../src/Drivers/DyIODataTableManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o.d" -o ${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o ../src/Drivers/DyIODataTableManager.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/108654538/PinFunctions.o: ../../common/src/dyio/PinFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/108654538 
	@${RM} ${OBJECTDIR}/_ext/108654538/PinFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/108654538/PinFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/108654538/PinFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/108654538/PinFunctions.o.d" -o ${OBJECTDIR}/_ext/108654538/PinFunctions.o ../../common/src/dyio/PinFunctions.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1020318379/ChannelMode.o: ../src/DyIO/ChannelMode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1020318379 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelMode.o.d 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelMode.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1020318379/ChannelMode.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1020318379/ChannelMode.o.d" -o ${OBJECTDIR}/_ext/1020318379/ChannelMode.o ../src/DyIO/ChannelMode.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1020318379/ChannelValues.o: ../src/DyIO/ChannelValues.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1020318379 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelValues.o.d 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelValues.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1020318379/ChannelValues.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1020318379/ChannelValues.o.d" -o ${OBJECTDIR}/_ext/1020318379/ChannelValues.o ../src/DyIO/ChannelValues.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1020318379/ChannelConfig.o: ../src/DyIO/ChannelConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1020318379 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelConfig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelConfig.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1020318379/ChannelConfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1020318379/ChannelConfig.o.d" -o ${OBJECTDIR}/_ext/1020318379/ChannelConfig.o ../src/DyIO/ChannelConfig.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o: ../../common/src/Namespace_bcs_io/Namespace_bcs_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/805493626 
	@${RM} ${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o.d 
	@${RM} ${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o.d" -o ${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o ../../common/src/Namespace_bcs_io/Namespace_bcs_io.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o: ../../common/src/Namespace_bcs_io/Abstract_bcs_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/805493626 
	@${RM} ${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o.d 
	@${RM} ${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o.d" -o ${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o ../../common/src/Namespace_bcs_io/Abstract_bcs_io.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/805493626/Debug_DyIO.o: ../../common/src/Namespace_bcs_io/Debug_DyIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/805493626 
	@${RM} ${OBJECTDIR}/_ext/805493626/Debug_DyIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/805493626/Debug_DyIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/805493626/Debug_DyIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/805493626/Debug_DyIO.o.d" -o ${OBJECTDIR}/_ext/805493626/Debug_DyIO.o ../../common/src/Namespace_bcs_io/Debug_DyIO.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o: ../../common/src/Namespace_bcs_io/Bcs_IO_AdvancedAsync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/805493626 
	@${RM} ${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o.d 
	@${RM} ${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o.d" -o ${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o ../../common/src/Namespace_bcs_io/Bcs_IO_AdvancedAsync.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o: ../../common/src/Namespace_bcs_io_setmode/Abstract_bcs_io_setmode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1051272628 
	@${RM} ${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o.d 
	@${RM} ${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o.d" -o ${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o ../../common/src/Namespace_bcs_io_setmode/Abstract_bcs_io_setmode.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o: ../../common/src/Namespace_bcs_io_setmode/Namespace_bcs_io_setmode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1051272628 
	@${RM} ${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o.d 
	@${RM} ${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o.d" -o ${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o ../../common/src/Namespace_bcs_io_setmode/Namespace_bcs_io_setmode.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o: ../src/Namespace_bcs_safe/Abstract_bsc_safe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1281821416 
	@${RM} ${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o.d 
	@${RM} ${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o.d" -o ${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o ../src/Namespace_bcs_safe/Abstract_bsc_safe.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o: ../src/Namespace_bcs_safe/Namespace_bcs_safe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1281821416 
	@${RM} ${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o.d 
	@${RM} ${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o.d" -o ${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o ../src/Namespace_bcs_safe/Namespace_bcs_safe.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o: ../src/Namespace_dyio/Namespace_neuronrobotics_dyio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/321196743 
	@${RM} ${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o.d 
	@${RM} ${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o.d" -o ${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o ../src/Namespace_dyio/Namespace_neuronrobotics_dyio.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o: ../src/Namespace_dyio/Namespace_bcs_pid_dypid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/321196743 
	@${RM} ${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o.d 
	@${RM} ${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o.d" -o ${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o ../src/Namespace_dyio/Namespace_bcs_pid_dypid.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1360937237/Main.o: ../src/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/Main.o.d" -o ${OBJECTDIR}/_ext/1360937237/Main.o ../src/Main.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1360937237/DyIOMain.o: ../src/DyIOMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DyIOMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DyIOMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/DyIOMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/DyIOMain.o.d" -o ${OBJECTDIR}/_ext/1360937237/DyIOMain.o ../src/DyIOMain.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
else
${OBJECTDIR}/_ext/1825615050/CartesianController.o: ../src/Application/CartesianController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825615050 
	@${RM} ${OBJECTDIR}/_ext/1825615050/CartesianController.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825615050/CartesianController.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825615050/CartesianController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1825615050/CartesianController.o.d" -o ${OBJECTDIR}/_ext/1825615050/CartesianController.o ../src/Application/CartesianController.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1825615050/PID.o: ../src/Application/PID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1825615050 
	@${RM} ${OBJECTDIR}/_ext/1825615050/PID.o.d 
	@${RM} ${OBJECTDIR}/_ext/1825615050/PID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1825615050/PID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1825615050/PID.o.d" -o ${OBJECTDIR}/_ext/1825615050/PID.o ../src/Application/PID.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o: ../src/BowlerCallbacks/InitializationCallbacks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1978776677 
	@${RM} ${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o.d" -o ${OBJECTDIR}/_ext/1978776677/InitializationCallbacks.o ../src/BowlerCallbacks/InitializationCallbacks.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1978776677/AsyncManager.o: ../src/BowlerCallbacks/AsyncManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1978776677 
	@${RM} ${OBJECTDIR}/_ext/1978776677/AsyncManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1978776677/AsyncManager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1978776677/AsyncManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1978776677/AsyncManager.o.d" -o ${OBJECTDIR}/_ext/1978776677/AsyncManager.o ../src/BowlerCallbacks/AsyncManager.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o: ../src/BowlerCallbacks/UpstreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1978776677 
	@${RM} ${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o.d 
	@${RM} ${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o.d" -o ${OBJECTDIR}/_ext/1978776677/UpstreamPackets.o ../src/BowlerCallbacks/UpstreamPackets.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o: ../src/BowlerCallbacks/DownStreamPackets.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1978776677 
	@${RM} ${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o.d 
	@${RM} ${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o.d" -o ${OBJECTDIR}/_ext/1978776677/DownStreamPackets.o ../src/BowlerCallbacks/DownStreamPackets.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/2110062566/UartDMARx.o: ../src/Drivers/dma/UartDMARx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2110062566 
	@${RM} ${OBJECTDIR}/_ext/2110062566/UartDMARx.o.d 
	@${RM} ${OBJECTDIR}/_ext/2110062566/UartDMARx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2110062566/UartDMARx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2110062566/UartDMARx.o.d" -o ${OBJECTDIR}/_ext/2110062566/UartDMARx.o ../src/Drivers/dma/UartDMARx.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/CoProcCom.o: ../src/Drivers/CoProcCom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/CoProcCom.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/CoProcCom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/CoProcCom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/CoProcCom.o.d" -o ${OBJECTDIR}/_ext/990863823/CoProcCom.o ../src/Drivers/CoProcCom.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/SPI.o: ../src/Drivers/SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/SPI.o.d" -o ${OBJECTDIR}/_ext/990863823/SPI.o ../src/Drivers/SPI.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/Switches.o: ../src/Drivers/Switches.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/Switches.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/Switches.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/Switches.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/Switches.o.d" -o ${OBJECTDIR}/_ext/990863823/Switches.o ../src/Drivers/Switches.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/PPMReader.o: ../src/Drivers/PPMReader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/PPMReader.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/PPMReader.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/PPMReader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/PPMReader.o.d" -o ${OBJECTDIR}/_ext/990863823/PPMReader.o ../src/Drivers/PPMReader.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/EEPROMMannager.o: ../src/Drivers/EEPROMMannager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/EEPROMMannager.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/EEPROMMannager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/EEPROMMannager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/EEPROMMannager.o.d" -o ${OBJECTDIR}/_ext/990863823/EEPROMMannager.o ../src/Drivers/EEPROMMannager.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/Counter.o: ../src/Drivers/Counter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/Counter.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/Counter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/Counter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/Counter.o.d" -o ${OBJECTDIR}/_ext/990863823/Counter.o ../src/Drivers/Counter.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/SerialPassThrough.o: ../src/Drivers/SerialPassThrough.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/SerialPassThrough.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/SerialPassThrough.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/SerialPassThrough.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/SerialPassThrough.o.d" -o ${OBJECTDIR}/_ext/990863823/SerialPassThrough.o ../src/Drivers/SerialPassThrough.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/ADC.o: ../src/Drivers/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/ADC.o.d" -o ${OBJECTDIR}/_ext/990863823/ADC.o ../src/Drivers/ADC.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o: ../src/Drivers/DyIODataTableManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/990863823 
	@${RM} ${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o.d" -o ${OBJECTDIR}/_ext/990863823/DyIODataTableManager.o ../src/Drivers/DyIODataTableManager.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/108654538/PinFunctions.o: ../../common/src/dyio/PinFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/108654538 
	@${RM} ${OBJECTDIR}/_ext/108654538/PinFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/108654538/PinFunctions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/108654538/PinFunctions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/108654538/PinFunctions.o.d" -o ${OBJECTDIR}/_ext/108654538/PinFunctions.o ../../common/src/dyio/PinFunctions.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1020318379/ChannelMode.o: ../src/DyIO/ChannelMode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1020318379 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelMode.o.d 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelMode.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1020318379/ChannelMode.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1020318379/ChannelMode.o.d" -o ${OBJECTDIR}/_ext/1020318379/ChannelMode.o ../src/DyIO/ChannelMode.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1020318379/ChannelValues.o: ../src/DyIO/ChannelValues.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1020318379 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelValues.o.d 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelValues.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1020318379/ChannelValues.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1020318379/ChannelValues.o.d" -o ${OBJECTDIR}/_ext/1020318379/ChannelValues.o ../src/DyIO/ChannelValues.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1020318379/ChannelConfig.o: ../src/DyIO/ChannelConfig.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1020318379 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelConfig.o.d 
	@${RM} ${OBJECTDIR}/_ext/1020318379/ChannelConfig.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1020318379/ChannelConfig.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1020318379/ChannelConfig.o.d" -o ${OBJECTDIR}/_ext/1020318379/ChannelConfig.o ../src/DyIO/ChannelConfig.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o: ../../common/src/Namespace_bcs_io/Namespace_bcs_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/805493626 
	@${RM} ${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o.d 
	@${RM} ${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o.d" -o ${OBJECTDIR}/_ext/805493626/Namespace_bcs_io.o ../../common/src/Namespace_bcs_io/Namespace_bcs_io.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o: ../../common/src/Namespace_bcs_io/Abstract_bcs_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/805493626 
	@${RM} ${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o.d 
	@${RM} ${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o.d" -o ${OBJECTDIR}/_ext/805493626/Abstract_bcs_io.o ../../common/src/Namespace_bcs_io/Abstract_bcs_io.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/805493626/Debug_DyIO.o: ../../common/src/Namespace_bcs_io/Debug_DyIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/805493626 
	@${RM} ${OBJECTDIR}/_ext/805493626/Debug_DyIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/805493626/Debug_DyIO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/805493626/Debug_DyIO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/805493626/Debug_DyIO.o.d" -o ${OBJECTDIR}/_ext/805493626/Debug_DyIO.o ../../common/src/Namespace_bcs_io/Debug_DyIO.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o: ../../common/src/Namespace_bcs_io/Bcs_IO_AdvancedAsync.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/805493626 
	@${RM} ${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o.d 
	@${RM} ${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o.d" -o ${OBJECTDIR}/_ext/805493626/Bcs_IO_AdvancedAsync.o ../../common/src/Namespace_bcs_io/Bcs_IO_AdvancedAsync.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o: ../../common/src/Namespace_bcs_io_setmode/Abstract_bcs_io_setmode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1051272628 
	@${RM} ${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o.d 
	@${RM} ${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o.d" -o ${OBJECTDIR}/_ext/1051272628/Abstract_bcs_io_setmode.o ../../common/src/Namespace_bcs_io_setmode/Abstract_bcs_io_setmode.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o: ../../common/src/Namespace_bcs_io_setmode/Namespace_bcs_io_setmode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1051272628 
	@${RM} ${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o.d 
	@${RM} ${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o.d" -o ${OBJECTDIR}/_ext/1051272628/Namespace_bcs_io_setmode.o ../../common/src/Namespace_bcs_io_setmode/Namespace_bcs_io_setmode.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o: ../src/Namespace_bcs_safe/Abstract_bsc_safe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1281821416 
	@${RM} ${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o.d 
	@${RM} ${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o.d" -o ${OBJECTDIR}/_ext/1281821416/Abstract_bsc_safe.o ../src/Namespace_bcs_safe/Abstract_bsc_safe.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o: ../src/Namespace_bcs_safe/Namespace_bcs_safe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1281821416 
	@${RM} ${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o.d 
	@${RM} ${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o.d" -o ${OBJECTDIR}/_ext/1281821416/Namespace_bcs_safe.o ../src/Namespace_bcs_safe/Namespace_bcs_safe.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o: ../src/Namespace_dyio/Namespace_neuronrobotics_dyio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/321196743 
	@${RM} ${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o.d 
	@${RM} ${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o.d" -o ${OBJECTDIR}/_ext/321196743/Namespace_neuronrobotics_dyio.o ../src/Namespace_dyio/Namespace_neuronrobotics_dyio.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o: ../src/Namespace_dyio/Namespace_bcs_pid_dypid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/321196743 
	@${RM} ${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o.d 
	@${RM} ${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o.d" -o ${OBJECTDIR}/_ext/321196743/Namespace_bcs_pid_dypid.o ../src/Namespace_dyio/Namespace_bcs_pid_dypid.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1360937237/Main.o: ../src/Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/Main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/Main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/Main.o.d" -o ${OBJECTDIR}/_ext/1360937237/Main.o ../src/Main.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
${OBJECTDIR}/_ext/1360937237/DyIOMain.o: ../src/DyIOMain.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DyIOMain.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/DyIOMain.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/DyIOMain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -O1 -I"../include" -I"../../common/include" -I"../../../c-bowler/BowlerStack/include" -I"../../../c-bowler/Platform/include" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/DyIOMain.o.d" -o ${OBJECTDIR}/_ext/1360937237/DyIOMain.o ../src/DyIOMain.c    -DPROGRAMMER_DEBUG -DMAJOR_REV=3 -DMINOR_REV=11 -DFIRMWARE_VERSION=1 -D_SUPPRESS_PLIB_WARNING
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/dyioMplab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../c-bowler/c-bowler.X/dist/default/debug/c-bowler.X.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dyioMplab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ../../../c-bowler/c-bowler.X/dist/default/debug/c-bowler.X.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--warn-section-align
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/dyioMplab.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../c-bowler/c-bowler.X/dist/default/production/c-bowler.X.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dyioMplab.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ../../../c-bowler/c-bowler.X/dist/default/production/c-bowler.X.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--cref,--warn-section-align
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/dyioMplab.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:
	cd ../../../c-bowler/c-bowler.X && ${MAKE}  -f Makefile CONF=default


# Subprojects
.clean-subprojects:
	cd ../../../c-bowler/c-bowler.X && rm -rf "build/default" "dist/default"

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
