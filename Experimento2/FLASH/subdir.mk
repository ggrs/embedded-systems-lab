################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../anotacoes_exp02.c" \

C_SRCS += \
../anotacoes_exp02.c \

OBJS += \
./anotacoes_exp02.o \

C_DEPS += \
./anotacoes_exp02.d \

OBJS_QUOTED += \
"./anotacoes_exp02.o" \

C_DEPS_QUOTED += \
"./anotacoes_exp02.d" \

OBJS_OS_FORMAT += \
./anotacoes_exp02.o \


# Each subdirectory must supply rules for building sources it contributes
anotacoes_exp02.o: ../anotacoes_exp02.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"anotacoes_exp02.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"./anotacoes_exp02.o"
	@echo 'Finished building: $<'
	@echo ' '


