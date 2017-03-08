## ========================================================================== ##
## --------------------------- DIRECTORIES ---------------------------------- ##
## ========================================================================== ##

## ------------------------------ COMMON ------------------------------------ ##
PROJECT_ROOT		?= ${PWD}

OUTPUT_DIR			?= ${PROJECT_ROOT}/.output
APP_DIR				?= ${PROJECT_ROOT}/app
PLATFORM_DIR		?= ${PROJECT_ROOT}/platform

SYSTEM_DIR			?= ${PLATFORM_DIR}/system
HAL_DIR				?= ${PLATFORM_DIR}/hal
COMMON_DIR			?= ${PLATFORM_DIR}/common

OBJ_DIR				?= ${OUTPUT_DIR}/obj

CMSIS_DIR			?= ${SYSTEM_DIR}/cmsis
STARTUP_DIR			?= ${SYSTEM_DIR}/startup

## ----------------------------- SOURCE ------------------------------------- ##
## APP
VPATH				:= ${APP_DIR}/src
## CMSIS
VPATH				+= ${CMSIS_DIR}/src
## STARTUP
VPATH				+= ${STARTUP_DIR}/src
## HAL
VPATH				+= ${HAL_DIR}/src
## COMMON
VPATH				+= ${COMMON_DIR}/src

## ========================================================================== ##
## ------------------------------ FILES ------------------------------------- ##
## ========================================================================== ##
PROJECT_NAME		= oscilloscope
## LINKER
LD_FILE				:= ${PROJECT_ROOT}/stm32_flash.ld
## IMAGE
IMAGE_FILE			:= ${OUTPUT_DIR}/${PROJECT_NAME}.elf
## BINARY
BIN_FILE			:= ${OUTPUT_DIR}/${PROJECT_NAME}.bin
## HEX
HEX_FILE			:= ${OUTPUT_DIR}/${PROJECT_NAME}.hex

## ----------------------------- OBJECT ------------------------------------- ##
## APP
OBJ_FILES			:= ${OBJ_DIR}/main.o
## CMSIS
OBJ_FILES			+= ${OBJ_DIR}/system_stm32f4xx.o
## STARTUP
OBJ_FILES			+= ${OBJ_DIR}/startup_stm32f4xx.o
## HAL
OBJ_FILES			+= ${OBJ_DIR}/misc.o
OBJ_FILES			+= ${OBJ_DIR}/stm32f4xx_gpio.o
OBJ_FILES			+= ${OBJ_DIR}/stm32f4xx_rcc.o
OBJ_FILES			+= ${OBJ_DIR}/stm32f4xx_usart.o

## ========================================================================== ##
## ------------------------------ FLAGS ------------------------------------- ##
## ========================================================================== ##

## ---------------------------- COMPILER ------------------------------------ ##
CC					= arm-none-eabi-gcc
OBJCOPY				= arm-none-eabi-objcopy
SIZE				= arm-none-eabi-size

## ------------------------------ MACRO ------------------------------------- ##

## ---------------------------- INCLUSION ----------------------------------- ##
## APP
CFLAGS_INC			:= -I ${APP_DIR}/include
## CMSIS
CFLAGS_INC			+= -I ${CMSIS_DIR}/include
## STARTUP
CFLAGS_INC			+= -I ${STARTUP_DIR}/include
## HAL
CFLAGS_INC			+= -I ${HAL_DIR}/include
## COMMON
CFLAGS_INC			+= -I ${COMMON_DIR}/include

## ------------------------- COMPILER OPTIONS ------------------------------- ##
CFLAGS				= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS				+= -std=gnu99 -O3 -g3 -mthumb -mlittle-endian
CFLAGS				+= -fsigned-char -ffunction-sections -fdata-sections
CFLAGS				+= -fno-move-loop-invariants
CFLAGS				+= -Werror -Wunused -Wuninitialized -Wall
CFLAGS				+= -Wmissing-declarations
CFLAGS				+= -Wpointer-arith -Wshadow -Wlogical-op
CFLAGS				+= -Waggregate-return -Wfloat-equal
CFLAGS				+= -Wmissing-prototypes -Wstrict-prototypes
#CFLAGS				+= -Wbad-function-cast -Wextra -Wconversion -Wpadded
CFLAGS				+= ${CFLAGS_INC} -MD -MP

AFLAGS				= ${CFLAGS} -x assembler

## ----------------------------- LINKER ------------------------------------- ##
LDFLAGS				= ${CFLAGS} -T${LD_FILE}
LDFLAGS				+= --specs=rdimon.specs
LDFLAGS				+= -Wl,--gc-sections

## ========================================================================== ##
## ----------------------------- TARGETS ------------------------------------ ##
## ========================================================================== ##
all: ${IMAGE_FILE} ${BIN_FILE} ${HEX_FILE}
	@$(SIZE) ${IMAGE_FILE}

clean:
	@${RM} -r ${OUTPUT_DIR}

${OBJ_DIR}/%.o: %.s
	@mkdir -p ${OBJ_DIR}
	@echo "  AC   ${<}"
	@${CC} ${AFLAGS} -o "${@}" -c "${<}"

${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	@echo "  CC   ${<}"
	@${CC} ${CFLAGS} -o "${@}" -c "${<}"

${IMAGE_FILE}: ${OBJ_FILES}
	@echo "  LD   ${@}"
	@${CC} ${LDFLAGS} -o "${@}" ${OBJ_FILES}

${BIN_FILE}: ${IMAGE_FILE}
	@$(OBJCOPY) -O binary ${<} ${@}

${HEX_FILE}: ${IMAGE_FILE}
	@$(OBJCOPY) -O ihex ${<} ${@}

.PHONY:

## Debugging targets
gdb: all
	arm-none-eabi-gdb ${IMAGE_FILE}

openocd: 
	openocd -f board/stm32f4discovery.cfg 


# Include the automatically generated dependency files
sinclude ${wildcard ${OBJ_DIR}/*.d}

