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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BowlerSampleProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/BowlerSampleProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/main.c ../Platform/src/pic32/Bowler_UART_HAL.c ../Platform/src/pic32/Bowler_USB_HAL.c ../Platform/src/pic32/LED.c ../Platform/src/pic32/Tick.c ../Platform/src/pic32/Delay.c ../Platform/src/pic32/HAL_P32.c ../Platform/src/pic32/ADC.c ../Platform/src/pic32/UART.c ../Platform/src/pic32/FlashStorage.c ../Platform/src/pic32/usb/usb_interrupt.c ../Platform/src/pic32/usb/usb_device.c ../Platform/src/pic32/usb/usb_fifo.c ../Platform/src/pic32/usb/usb_descriptors.c ../Platform/src/pic32/usb/usb_callback.c ../Platform/src/pic32/usb/usb_function_cdc.c ../BowlerStack/src/Namespace_bcs_rpc.c ../BowlerStack/src/Bowler_RPC_Process.c ../BowlerStack/src/AbstractPID.c ../BowlerStack/src/Scheduler.c ../BowlerStack/src/Namespace_bcs_core.c ../BowlerStack/src/Bowler_Transport.c ../BowlerStack/src/Bowler_Server.c ../BowlerStack/src/FIFO.c ../BowlerStack/src/Debug.c ../BowlerStack/src/Bowler_Stack_Callback.c ../BowlerStack/src/Namespace_bcs_pid.c ../BowlerStack/src/Bowler_Helper.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o ${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o ${OBJECTDIR}/_ext/126603185/LED.o ${OBJECTDIR}/_ext/126603185/Tick.o ${OBJECTDIR}/_ext/126603185/Delay.o ${OBJECTDIR}/_ext/126603185/HAL_P32.o ${OBJECTDIR}/_ext/126603185/ADC.o ${OBJECTDIR}/_ext/126603185/UART.o ${OBJECTDIR}/_ext/126603185/FlashStorage.o ${OBJECTDIR}/_ext/1193168346/usb_interrupt.o ${OBJECTDIR}/_ext/1193168346/usb_device.o ${OBJECTDIR}/_ext/1193168346/usb_fifo.o ${OBJECTDIR}/_ext/1193168346/usb_descriptors.o ${OBJECTDIR}/_ext/1193168346/usb_callback.o ${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o ${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o ${OBJECTDIR}/_ext/681034721/AbstractPID.o ${OBJECTDIR}/_ext/681034721/Scheduler.o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o ${OBJECTDIR}/_ext/681034721/Bowler_Transport.o ${OBJECTDIR}/_ext/681034721/Bowler_Server.o ${OBJECTDIR}/_ext/681034721/FIFO.o ${OBJECTDIR}/_ext/681034721/Debug.o ${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o ${OBJECTDIR}/_ext/681034721/Bowler_Helper.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o.d ${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o.d ${OBJECTDIR}/_ext/126603185/LED.o.d ${OBJECTDIR}/_ext/126603185/Tick.o.d ${OBJECTDIR}/_ext/126603185/Delay.o.d ${OBJECTDIR}/_ext/126603185/HAL_P32.o.d ${OBJECTDIR}/_ext/126603185/ADC.o.d ${OBJECTDIR}/_ext/126603185/UART.o.d ${OBJECTDIR}/_ext/126603185/FlashStorage.o.d ${OBJECTDIR}/_ext/1193168346/usb_interrupt.o.d ${OBJECTDIR}/_ext/1193168346/usb_device.o.d ${OBJECTDIR}/_ext/1193168346/usb_fifo.o.d ${OBJECTDIR}/_ext/1193168346/usb_descriptors.o.d ${OBJECTDIR}/_ext/1193168346/usb_callback.o.d ${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o.d ${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o.d ${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o.d ${OBJECTDIR}/_ext/681034721/AbstractPID.o.d ${OBJECTDIR}/_ext/681034721/Scheduler.o.d ${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o.d ${OBJECTDIR}/_ext/681034721/Bowler_Transport.o.d ${OBJECTDIR}/_ext/681034721/Bowler_Server.o.d ${OBJECTDIR}/_ext/681034721/FIFO.o.d ${OBJECTDIR}/_ext/681034721/Debug.o.d ${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o.d ${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o.d ${OBJECTDIR}/_ext/681034721/Bowler_Helper.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o ${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o ${OBJECTDIR}/_ext/126603185/LED.o ${OBJECTDIR}/_ext/126603185/Tick.o ${OBJECTDIR}/_ext/126603185/Delay.o ${OBJECTDIR}/_ext/126603185/HAL_P32.o ${OBJECTDIR}/_ext/126603185/ADC.o ${OBJECTDIR}/_ext/126603185/UART.o ${OBJECTDIR}/_ext/126603185/FlashStorage.o ${OBJECTDIR}/_ext/1193168346/usb_interrupt.o ${OBJECTDIR}/_ext/1193168346/usb_device.o ${OBJECTDIR}/_ext/1193168346/usb_fifo.o ${OBJECTDIR}/_ext/1193168346/usb_descriptors.o ${OBJECTDIR}/_ext/1193168346/usb_callback.o ${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o ${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o ${OBJECTDIR}/_ext/681034721/AbstractPID.o ${OBJECTDIR}/_ext/681034721/Scheduler.o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o ${OBJECTDIR}/_ext/681034721/Bowler_Transport.o ${OBJECTDIR}/_ext/681034721/Bowler_Server.o ${OBJECTDIR}/_ext/681034721/FIFO.o ${OBJECTDIR}/_ext/681034721/Debug.o ${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o ${OBJECTDIR}/_ext/681034721/Bowler_Helper.o

# Source Files
SOURCEFILES=../src/main.c ../Platform/src/pic32/Bowler_UART_HAL.c ../Platform/src/pic32/Bowler_USB_HAL.c ../Platform/src/pic32/LED.c ../Platform/src/pic32/Tick.c ../Platform/src/pic32/Delay.c ../Platform/src/pic32/HAL_P32.c ../Platform/src/pic32/ADC.c ../Platform/src/pic32/UART.c ../Platform/src/pic32/FlashStorage.c ../Platform/src/pic32/usb/usb_interrupt.c ../Platform/src/pic32/usb/usb_device.c ../Platform/src/pic32/usb/usb_fifo.c ../Platform/src/pic32/usb/usb_descriptors.c ../Platform/src/pic32/usb/usb_callback.c ../Platform/src/pic32/usb/usb_function_cdc.c ../BowlerStack/src/Namespace_bcs_rpc.c ../BowlerStack/src/Bowler_RPC_Process.c ../BowlerStack/src/AbstractPID.c ../BowlerStack/src/Scheduler.c ../BowlerStack/src/Namespace_bcs_core.c ../BowlerStack/src/Bowler_Transport.c ../BowlerStack/src/Bowler_Server.c ../BowlerStack/src/FIFO.c ../BowlerStack/src/Debug.c ../BowlerStack/src/Bowler_Stack_Callback.c ../BowlerStack/src/Namespace_bcs_pid.c ../BowlerStack/src/Bowler_Helper.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/BowlerSampleProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
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
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o: ../Platform/src/pic32/Bowler_UART_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o.d" -o ${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o ../Platform/src/pic32/Bowler_UART_HAL.c   
	
${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o: ../Platform/src/pic32/Bowler_USB_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o.d" -o ${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o ../Platform/src/pic32/Bowler_USB_HAL.c   
	
${OBJECTDIR}/_ext/126603185/LED.o: ../Platform/src/pic32/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/LED.o.d" -o ${OBJECTDIR}/_ext/126603185/LED.o ../Platform/src/pic32/LED.c   
	
${OBJECTDIR}/_ext/126603185/Tick.o: ../Platform/src/pic32/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/Tick.o.d" -o ${OBJECTDIR}/_ext/126603185/Tick.o ../Platform/src/pic32/Tick.c   
	
${OBJECTDIR}/_ext/126603185/Delay.o: ../Platform/src/pic32/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/Delay.o.d" -o ${OBJECTDIR}/_ext/126603185/Delay.o ../Platform/src/pic32/Delay.c   
	
${OBJECTDIR}/_ext/126603185/HAL_P32.o: ../Platform/src/pic32/HAL_P32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/HAL_P32.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/HAL_P32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/HAL_P32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/HAL_P32.o.d" -o ${OBJECTDIR}/_ext/126603185/HAL_P32.o ../Platform/src/pic32/HAL_P32.c   
	
${OBJECTDIR}/_ext/126603185/ADC.o: ../Platform/src/pic32/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/ADC.o.d" -o ${OBJECTDIR}/_ext/126603185/ADC.o ../Platform/src/pic32/ADC.c   
	
${OBJECTDIR}/_ext/126603185/UART.o: ../Platform/src/pic32/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/UART.o.d" -o ${OBJECTDIR}/_ext/126603185/UART.o ../Platform/src/pic32/UART.c   
	
${OBJECTDIR}/_ext/126603185/FlashStorage.o: ../Platform/src/pic32/FlashStorage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/FlashStorage.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/FlashStorage.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/FlashStorage.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/FlashStorage.o.d" -o ${OBJECTDIR}/_ext/126603185/FlashStorage.o ../Platform/src/pic32/FlashStorage.c   
	
${OBJECTDIR}/_ext/1193168346/usb_interrupt.o: ../Platform/src/pic32/usb/usb_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_interrupt.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_interrupt.o ../Platform/src/pic32/usb/usb_interrupt.c   
	
${OBJECTDIR}/_ext/1193168346/usb_device.o: ../Platform/src/pic32/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_device.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_device.o ../Platform/src/pic32/usb/usb_device.c   
	
${OBJECTDIR}/_ext/1193168346/usb_fifo.o: ../Platform/src/pic32/usb/usb_fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_fifo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_fifo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_fifo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_fifo.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_fifo.o ../Platform/src/pic32/usb/usb_fifo.c   
	
${OBJECTDIR}/_ext/1193168346/usb_descriptors.o: ../Platform/src/pic32/usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_descriptors.o ../Platform/src/pic32/usb/usb_descriptors.c   
	
${OBJECTDIR}/_ext/1193168346/usb_callback.o: ../Platform/src/pic32/usb/usb_callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_callback.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_callback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_callback.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_callback.o ../Platform/src/pic32/usb/usb_callback.c   
	
${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o: ../Platform/src/pic32/usb/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o ../Platform/src/pic32/usb/usb_function_cdc.c   
	
${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o: ../BowlerStack/src/Namespace_bcs_rpc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o.d" -o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o ../BowlerStack/src/Namespace_bcs_rpc.c   
	
${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o: ../BowlerStack/src/Bowler_RPC_Process.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o.d" -o ${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o ../BowlerStack/src/Bowler_RPC_Process.c   
	
${OBJECTDIR}/_ext/681034721/AbstractPID.o: ../BowlerStack/src/AbstractPID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/AbstractPID.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/AbstractPID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/AbstractPID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/AbstractPID.o.d" -o ${OBJECTDIR}/_ext/681034721/AbstractPID.o ../BowlerStack/src/AbstractPID.c   
	
${OBJECTDIR}/_ext/681034721/Scheduler.o: ../BowlerStack/src/Scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Scheduler.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Scheduler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Scheduler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Scheduler.o.d" -o ${OBJECTDIR}/_ext/681034721/Scheduler.o ../BowlerStack/src/Scheduler.c   
	
${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o: ../BowlerStack/src/Namespace_bcs_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o.d" -o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o ../BowlerStack/src/Namespace_bcs_core.c   
	
${OBJECTDIR}/_ext/681034721/Bowler_Transport.o: ../BowlerStack/src/Bowler_Transport.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Transport.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Transport.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Bowler_Transport.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Bowler_Transport.o.d" -o ${OBJECTDIR}/_ext/681034721/Bowler_Transport.o ../BowlerStack/src/Bowler_Transport.c   
	
${OBJECTDIR}/_ext/681034721/Bowler_Server.o: ../BowlerStack/src/Bowler_Server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Server.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Server.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Bowler_Server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Bowler_Server.o.d" -o ${OBJECTDIR}/_ext/681034721/Bowler_Server.o ../BowlerStack/src/Bowler_Server.c   
	
${OBJECTDIR}/_ext/681034721/FIFO.o: ../BowlerStack/src/FIFO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/FIFO.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/FIFO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/FIFO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/FIFO.o.d" -o ${OBJECTDIR}/_ext/681034721/FIFO.o ../BowlerStack/src/FIFO.c   
	
${OBJECTDIR}/_ext/681034721/Debug.o: ../BowlerStack/src/Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Debug.o.d" -o ${OBJECTDIR}/_ext/681034721/Debug.o ../BowlerStack/src/Debug.c   
	
${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o: ../BowlerStack/src/Bowler_Stack_Callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o.d" -o ${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o ../BowlerStack/src/Bowler_Stack_Callback.c   
	
${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o: ../BowlerStack/src/Namespace_bcs_pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o.d" -o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o ../BowlerStack/src/Namespace_bcs_pid.c   
	
${OBJECTDIR}/_ext/681034721/Bowler_Helper.o: ../BowlerStack/src/Bowler_Helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Helper.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Helper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Bowler_Helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Bowler_Helper.o.d" -o ${OBJECTDIR}/_ext/681034721/Bowler_Helper.o ../BowlerStack/src/Bowler_Helper.c   
	
else
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360937237 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c   
	
${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o: ../Platform/src/pic32/Bowler_UART_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o.d" -o ${OBJECTDIR}/_ext/126603185/Bowler_UART_HAL.o ../Platform/src/pic32/Bowler_UART_HAL.c   
	
${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o: ../Platform/src/pic32/Bowler_USB_HAL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o.d" -o ${OBJECTDIR}/_ext/126603185/Bowler_USB_HAL.o ../Platform/src/pic32/Bowler_USB_HAL.c   
	
${OBJECTDIR}/_ext/126603185/LED.o: ../Platform/src/pic32/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/LED.o.d" -o ${OBJECTDIR}/_ext/126603185/LED.o ../Platform/src/pic32/LED.c   
	
${OBJECTDIR}/_ext/126603185/Tick.o: ../Platform/src/pic32/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/Tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/Tick.o.d" -o ${OBJECTDIR}/_ext/126603185/Tick.o ../Platform/src/pic32/Tick.c   
	
${OBJECTDIR}/_ext/126603185/Delay.o: ../Platform/src/pic32/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/Delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/Delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/Delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/Delay.o.d" -o ${OBJECTDIR}/_ext/126603185/Delay.o ../Platform/src/pic32/Delay.c   
	
${OBJECTDIR}/_ext/126603185/HAL_P32.o: ../Platform/src/pic32/HAL_P32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/HAL_P32.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/HAL_P32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/HAL_P32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/HAL_P32.o.d" -o ${OBJECTDIR}/_ext/126603185/HAL_P32.o ../Platform/src/pic32/HAL_P32.c   
	
${OBJECTDIR}/_ext/126603185/ADC.o: ../Platform/src/pic32/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/ADC.o.d" -o ${OBJECTDIR}/_ext/126603185/ADC.o ../Platform/src/pic32/ADC.c   
	
${OBJECTDIR}/_ext/126603185/UART.o: ../Platform/src/pic32/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/UART.o.d" -o ${OBJECTDIR}/_ext/126603185/UART.o ../Platform/src/pic32/UART.c   
	
${OBJECTDIR}/_ext/126603185/FlashStorage.o: ../Platform/src/pic32/FlashStorage.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/126603185 
	@${RM} ${OBJECTDIR}/_ext/126603185/FlashStorage.o.d 
	@${RM} ${OBJECTDIR}/_ext/126603185/FlashStorage.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/126603185/FlashStorage.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/126603185/FlashStorage.o.d" -o ${OBJECTDIR}/_ext/126603185/FlashStorage.o ../Platform/src/pic32/FlashStorage.c   
	
${OBJECTDIR}/_ext/1193168346/usb_interrupt.o: ../Platform/src/pic32/usb/usb_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_interrupt.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_interrupt.o ../Platform/src/pic32/usb/usb_interrupt.c   
	
${OBJECTDIR}/_ext/1193168346/usb_device.o: ../Platform/src/pic32/usb/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_device.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_device.o ../Platform/src/pic32/usb/usb_device.c   
	
${OBJECTDIR}/_ext/1193168346/usb_fifo.o: ../Platform/src/pic32/usb/usb_fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_fifo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_fifo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_fifo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_fifo.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_fifo.o ../Platform/src/pic32/usb/usb_fifo.c   
	
${OBJECTDIR}/_ext/1193168346/usb_descriptors.o: ../Platform/src/pic32/usb/usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_descriptors.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_descriptors.o ../Platform/src/pic32/usb/usb_descriptors.c   
	
${OBJECTDIR}/_ext/1193168346/usb_callback.o: ../Platform/src/pic32/usb/usb_callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_callback.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_callback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_callback.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_callback.o ../Platform/src/pic32/usb/usb_callback.c   
	
${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o: ../Platform/src/pic32/usb/usb_function_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1193168346 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o.d" -o ${OBJECTDIR}/_ext/1193168346/usb_function_cdc.o ../Platform/src/pic32/usb/usb_function_cdc.c   
	
${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o: ../BowlerStack/src/Namespace_bcs_rpc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o.d" -o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_rpc.o ../BowlerStack/src/Namespace_bcs_rpc.c   
	
${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o: ../BowlerStack/src/Bowler_RPC_Process.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o.d" -o ${OBJECTDIR}/_ext/681034721/Bowler_RPC_Process.o ../BowlerStack/src/Bowler_RPC_Process.c   
	
${OBJECTDIR}/_ext/681034721/AbstractPID.o: ../BowlerStack/src/AbstractPID.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/AbstractPID.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/AbstractPID.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/AbstractPID.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/AbstractPID.o.d" -o ${OBJECTDIR}/_ext/681034721/AbstractPID.o ../BowlerStack/src/AbstractPID.c   
	
${OBJECTDIR}/_ext/681034721/Scheduler.o: ../BowlerStack/src/Scheduler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Scheduler.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Scheduler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Scheduler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Scheduler.o.d" -o ${OBJECTDIR}/_ext/681034721/Scheduler.o ../BowlerStack/src/Scheduler.c   
	
${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o: ../BowlerStack/src/Namespace_bcs_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o.d" -o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_core.o ../BowlerStack/src/Namespace_bcs_core.c   
	
${OBJECTDIR}/_ext/681034721/Bowler_Transport.o: ../BowlerStack/src/Bowler_Transport.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Transport.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Transport.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Bowler_Transport.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Bowler_Transport.o.d" -o ${OBJECTDIR}/_ext/681034721/Bowler_Transport.o ../BowlerStack/src/Bowler_Transport.c   
	
${OBJECTDIR}/_ext/681034721/Bowler_Server.o: ../BowlerStack/src/Bowler_Server.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Server.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Server.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Bowler_Server.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Bowler_Server.o.d" -o ${OBJECTDIR}/_ext/681034721/Bowler_Server.o ../BowlerStack/src/Bowler_Server.c   
	
${OBJECTDIR}/_ext/681034721/FIFO.o: ../BowlerStack/src/FIFO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/FIFO.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/FIFO.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/FIFO.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/FIFO.o.d" -o ${OBJECTDIR}/_ext/681034721/FIFO.o ../BowlerStack/src/FIFO.c   
	
${OBJECTDIR}/_ext/681034721/Debug.o: ../BowlerStack/src/Debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Debug.o.d" -o ${OBJECTDIR}/_ext/681034721/Debug.o ../BowlerStack/src/Debug.c   
	
${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o: ../BowlerStack/src/Bowler_Stack_Callback.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o.d" -o ${OBJECTDIR}/_ext/681034721/Bowler_Stack_Callback.o ../BowlerStack/src/Bowler_Stack_Callback.c   
	
${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o: ../BowlerStack/src/Namespace_bcs_pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o.d" -o ${OBJECTDIR}/_ext/681034721/Namespace_bcs_pid.o ../BowlerStack/src/Namespace_bcs_pid.c   
	
${OBJECTDIR}/_ext/681034721/Bowler_Helper.o: ../BowlerStack/src/Bowler_Helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/681034721 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Helper.o.d 
	@${RM} ${OBJECTDIR}/_ext/681034721/Bowler_Helper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/681034721/Bowler_Helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../BowlerStack/include" -I"../src" -I"../Platform/include" -MMD -MF "${OBJECTDIR}/_ext/681034721/Bowler_Helper.o.d" -o ${OBJECTDIR}/_ext/681034721/Bowler_Helper.o ../BowlerStack/src/Bowler_Helper.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/BowlerSampleProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/BowlerSampleProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/BowlerSampleProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/BowlerSampleProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/BowlerSampleProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

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
