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
ifeq "$(wildcard nbproject/Makefile-local-pic32mz_ef_sk_int_dyn.mk)" "nbproject/Makefile-local-pic32mz_ef_sk_int_dyn.mk"
include nbproject/Makefile-local-pic32mz_ef_sk_int_dyn.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=pic32mz_ef_sk_int_dyn
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/hid_keyboard.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/hid_keyboard.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/pic32mz_ef_sk_int_dyn/bsp/bsp.c ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/clk/src/sys_clk_pic32mz.c ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon.c ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_pic32mz.c ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_cache_pic32mz.S ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mz_ef_sk_int_dyn/system_init.c ../src/system_config/pic32mz_ef_sk_int_dyn/system_interrupt.c ../src/system_config/pic32mz_ef_sk_int_dyn/system_exceptions.c ../src/system_config/pic32mz_ef_sk_int_dyn/system_tasks.c ../src/app.c ../src/main.c ../src/keyboard.c ../../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/system/tmr/src/sys_tmr.c ../../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../../framework/usb/src/dynamic/usb_device_hid.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1530581680/bsp.o ${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o ${OBJECTDIR}/_ext/2102544990/sys_devcon.o ${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o ${OBJECTDIR}/_ext/1337871079/sys_ports_static.o ${OBJECTDIR}/_ext/2118682880/system_init.o ${OBJECTDIR}/_ext/2118682880/system_interrupt.o ${OBJECTDIR}/_ext/2118682880/system_exceptions.o ${OBJECTDIR}/_ext/2118682880/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/keyboard.o ${OBJECTDIR}/_ext/1152366776/drv_tmr.o ${OBJECTDIR}/_ext/1698770803/drv_usbhs.o ${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/430974239/sys_tmr.o ${OBJECTDIR}/_ext/692885480/usb_device.o ${OBJECTDIR}/_ext/692885480/usb_device_hid.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1530581680/bsp.o.d ${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o.d ${OBJECTDIR}/_ext/2102544990/sys_devcon.o.d ${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o.d ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.d ${OBJECTDIR}/_ext/1337871079/sys_ports_static.o.d ${OBJECTDIR}/_ext/2118682880/system_init.o.d ${OBJECTDIR}/_ext/2118682880/system_interrupt.o.d ${OBJECTDIR}/_ext/2118682880/system_exceptions.o.d ${OBJECTDIR}/_ext/2118682880/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/keyboard.o.d ${OBJECTDIR}/_ext/1152366776/drv_tmr.o.d ${OBJECTDIR}/_ext/1698770803/drv_usbhs.o.d ${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o.d ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d ${OBJECTDIR}/_ext/430974239/sys_tmr.o.d ${OBJECTDIR}/_ext/692885480/usb_device.o.d ${OBJECTDIR}/_ext/692885480/usb_device_hid.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1530581680/bsp.o ${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o ${OBJECTDIR}/_ext/2102544990/sys_devcon.o ${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o ${OBJECTDIR}/_ext/1337871079/sys_ports_static.o ${OBJECTDIR}/_ext/2118682880/system_init.o ${OBJECTDIR}/_ext/2118682880/system_interrupt.o ${OBJECTDIR}/_ext/2118682880/system_exceptions.o ${OBJECTDIR}/_ext/2118682880/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/keyboard.o ${OBJECTDIR}/_ext/1152366776/drv_tmr.o ${OBJECTDIR}/_ext/1698770803/drv_usbhs.o ${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ${OBJECTDIR}/_ext/430974239/sys_tmr.o ${OBJECTDIR}/_ext/692885480/usb_device.o ${OBJECTDIR}/_ext/692885480/usb_device_hid.o

# Source Files
SOURCEFILES=../src/system_config/pic32mz_ef_sk_int_dyn/bsp/bsp.c ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/clk/src/sys_clk_pic32mz.c ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon.c ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_pic32mz.c ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_cache_pic32mz.S ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/ports/src/sys_ports_static.c ../src/system_config/pic32mz_ef_sk_int_dyn/system_init.c ../src/system_config/pic32mz_ef_sk_int_dyn/system_interrupt.c ../src/system_config/pic32mz_ef_sk_int_dyn/system_exceptions.c ../src/system_config/pic32mz_ef_sk_int_dyn/system_tasks.c ../src/app.c ../src/main.c ../src/keyboard.c ../../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c ../../../../../../framework/system/int/src/sys_int_pic32.c ../../../../../../framework/system/tmr/src/sys_tmr.c ../../../../../../framework/usb/src/dynamic/usb_device.c ../../../../../../framework/usb/src/dynamic/usb_device_hid.c


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
	${MAKE}  -f nbproject/Makefile-pic32mz_ef_sk_int_dyn.mk dist/${CND_CONF}/${IMAGE_TYPE}/hid_keyboard.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ2048EFH144
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o: ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2102544990" 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.ok ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.d" "${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.d"  -o ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
else
${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o: ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2102544990" 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.ok ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.d" "${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.d"  -o ${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/2102544990/sys_devcon_cache_pic32mz.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1530581680/bsp.o: ../src/system_config/pic32mz_ef_sk_int_dyn/bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1530581680" 
	@${RM} ${OBJECTDIR}/_ext/1530581680/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1530581680/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1530581680/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1530581680/bsp.o.d" -o ${OBJECTDIR}/_ext/1530581680/bsp.o ../src/system_config/pic32mz_ef_sk_int_dyn/bsp/bsp.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o: ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/clk/src/sys_clk_pic32mz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/283087881" 
	@${RM} ${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o.d" -o ${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/clk/src/sys_clk_pic32mz.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2102544990/sys_devcon.o: ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2102544990" 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2102544990/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2102544990/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/2102544990/sys_devcon.o ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o: ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_pic32mz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2102544990" 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o.d" -o ${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_pic32mz.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1337871079/sys_ports_static.o: ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1337871079" 
	@${RM} ${OBJECTDIR}/_ext/1337871079/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1337871079/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1337871079/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1337871079/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/1337871079/sys_ports_static.o ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/ports/src/sys_ports_static.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2118682880/system_init.o: ../src/system_config/pic32mz_ef_sk_int_dyn/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118682880" 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118682880/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2118682880/system_init.o.d" -o ${OBJECTDIR}/_ext/2118682880/system_init.o ../src/system_config/pic32mz_ef_sk_int_dyn/system_init.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2118682880/system_interrupt.o: ../src/system_config/pic32mz_ef_sk_int_dyn/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118682880" 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118682880/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2118682880/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/2118682880/system_interrupt.o ../src/system_config/pic32mz_ef_sk_int_dyn/system_interrupt.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2118682880/system_exceptions.o: ../src/system_config/pic32mz_ef_sk_int_dyn/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118682880" 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118682880/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2118682880/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/2118682880/system_exceptions.o ../src/system_config/pic32mz_ef_sk_int_dyn/system_exceptions.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2118682880/system_tasks.o: ../src/system_config/pic32mz_ef_sk_int_dyn/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118682880" 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118682880/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2118682880/system_tasks.o.d" -o ${OBJECTDIR}/_ext/2118682880/system_tasks.o ../src/system_config/pic32mz_ef_sk_int_dyn/system_tasks.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/keyboard.o: ../src/keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/keyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/keyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/keyboard.o.d" -o ${OBJECTDIR}/_ext/1360937237/keyboard.o ../src/keyboard.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1152366776/drv_tmr.o: ../../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1152366776" 
	@${RM} ${OBJECTDIR}/_ext/1152366776/drv_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1152366776/drv_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1152366776/drv_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1152366776/drv_tmr.o.d" -o ${OBJECTDIR}/_ext/1152366776/drv_tmr.o ../../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1698770803/drv_usbhs.o: ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1698770803" 
	@${RM} ${OBJECTDIR}/_ext/1698770803/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1698770803/drv_usbhs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1698770803/drv_usbhs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1698770803/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/1698770803/drv_usbhs.o ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o: ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1698770803" 
	@${RM} ${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/711155467/sys_int_pic32.o: ../../../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/711155467" 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ../../../../../../framework/system/int/src/sys_int_pic32.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/430974239/sys_tmr.o: ../../../../../../framework/system/tmr/src/sys_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/430974239" 
	@${RM} ${OBJECTDIR}/_ext/430974239/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/430974239/sys_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/430974239/sys_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/430974239/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/430974239/sys_tmr.o ../../../../../../framework/system/tmr/src/sys_tmr.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/692885480/usb_device.o: ../../../../../../framework/usb/src/dynamic/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/692885480/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device.o ../../../../../../framework/usb/src/dynamic/usb_device.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/692885480/usb_device_hid.o: ../../../../../../framework/usb/src/dynamic/usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/692885480/usb_device_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_hid.o ../../../../../../framework/usb/src/dynamic/usb_device_hid.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1530581680/bsp.o: ../src/system_config/pic32mz_ef_sk_int_dyn/bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1530581680" 
	@${RM} ${OBJECTDIR}/_ext/1530581680/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1530581680/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1530581680/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1530581680/bsp.o.d" -o ${OBJECTDIR}/_ext/1530581680/bsp.o ../src/system_config/pic32mz_ef_sk_int_dyn/bsp/bsp.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o: ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/clk/src/sys_clk_pic32mz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/283087881" 
	@${RM} ${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o.d" -o ${OBJECTDIR}/_ext/283087881/sys_clk_pic32mz.o ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/clk/src/sys_clk_pic32mz.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2102544990/sys_devcon.o: ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2102544990" 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2102544990/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2102544990/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/2102544990/sys_devcon.o ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o: ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_pic32mz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2102544990" 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o.d" -o ${OBJECTDIR}/_ext/2102544990/sys_devcon_pic32mz.o ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/devcon/src/sys_devcon_pic32mz.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1337871079/sys_ports_static.o: ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1337871079" 
	@${RM} ${OBJECTDIR}/_ext/1337871079/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1337871079/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1337871079/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1337871079/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/1337871079/sys_ports_static.o ../src/system_config/pic32mz_ef_sk_int_dyn/framework/system/ports/src/sys_ports_static.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2118682880/system_init.o: ../src/system_config/pic32mz_ef_sk_int_dyn/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118682880" 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118682880/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2118682880/system_init.o.d" -o ${OBJECTDIR}/_ext/2118682880/system_init.o ../src/system_config/pic32mz_ef_sk_int_dyn/system_init.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2118682880/system_interrupt.o: ../src/system_config/pic32mz_ef_sk_int_dyn/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118682880" 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118682880/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2118682880/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/2118682880/system_interrupt.o ../src/system_config/pic32mz_ef_sk_int_dyn/system_interrupt.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2118682880/system_exceptions.o: ../src/system_config/pic32mz_ef_sk_int_dyn/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118682880" 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118682880/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2118682880/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/2118682880/system_exceptions.o ../src/system_config/pic32mz_ef_sk_int_dyn/system_exceptions.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2118682880/system_tasks.o: ../src/system_config/pic32mz_ef_sk_int_dyn/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2118682880" 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/2118682880/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2118682880/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/2118682880/system_tasks.o.d" -o ${OBJECTDIR}/_ext/2118682880/system_tasks.o ../src/system_config/pic32mz_ef_sk_int_dyn/system_tasks.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/keyboard.o: ../src/keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/keyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/keyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/keyboard.o.d" -o ${OBJECTDIR}/_ext/1360937237/keyboard.o ../src/keyboard.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1152366776/drv_tmr.o: ../../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1152366776" 
	@${RM} ${OBJECTDIR}/_ext/1152366776/drv_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1152366776/drv_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1152366776/drv_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1152366776/drv_tmr.o.d" -o ${OBJECTDIR}/_ext/1152366776/drv_tmr.o ../../../../../../framework/driver/tmr/src/dynamic/drv_tmr.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1698770803/drv_usbhs.o: ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1698770803" 
	@${RM} ${OBJECTDIR}/_ext/1698770803/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1698770803/drv_usbhs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1698770803/drv_usbhs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1698770803/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/1698770803/drv_usbhs.o ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o: ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1698770803" 
	@${RM} ${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/1698770803/drv_usbhs_device.o ../../../../../../framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/711155467/sys_int_pic32.o: ../../../../../../framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/711155467" 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/711155467/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/711155467/sys_int_pic32.o ../../../../../../framework/system/int/src/sys_int_pic32.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/430974239/sys_tmr.o: ../../../../../../framework/system/tmr/src/sys_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/430974239" 
	@${RM} ${OBJECTDIR}/_ext/430974239/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/430974239/sys_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/430974239/sys_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/430974239/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/430974239/sys_tmr.o ../../../../../../framework/system/tmr/src/sys_tmr.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/692885480/usb_device.o: ../../../../../../framework/usb/src/dynamic/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/692885480/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device.o ../../../../../../framework/usb/src/dynamic/usb_device.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/692885480/usb_device_hid.o: ../../../../../../framework/usb/src/dynamic/usb_device_hid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/692885480" 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/692885480/usb_device_hid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/692885480/usb_device_hid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/pic32mz_ef_sk_int_dyn" -I"../src/pic32mz_ef_sk_int_dyn" -I"../../../../../../framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/framework" -I"../src/system_config/pic32mz_ef_sk_int_dyn/bsp" -MMD -MF "${OBJECTDIR}/_ext/692885480/usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/692885480/usb_device_hid.o ../../../../../../framework/usb/src/dynamic/usb_device_hid.c    -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/hid_keyboard.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../bin/framework/peripheral/PIC32MZ2048EFM144_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/hid_keyboard.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\bin\framework\peripheral\PIC32MZ2048EFM144_peripherals.a      -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/hid_keyboard.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../bin/framework/peripheral/PIC32MZ2048EFM144_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/hid_keyboard.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\bin\framework\peripheral\PIC32MZ2048EFM144_peripherals.a      -DXPRJ_pic32mz_ef_sk_int_dyn=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/hid_keyboard.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/pic32mz_ef_sk_int_dyn
	${RM} -r dist/pic32mz_ef_sk_int_dyn

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
