################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
FRT_Library/FreeRTOS/Source/%.o: ../FRT_Library/FreeRTOS/Source/%.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/ccsv6/tools/compiler/gcc-arm-none-eabi-4_8-2014q3/bin/arm-none-eabi-gcc.exe" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DPART_TM4C123GE6PM -I"C:/ti/ccsv6/tools/compiler/gcc-arm-none-eabi-4_8-2014q3/arm-none-eabi/include" -I"D:/Git/Robinson_F16_projekt/Code/C code/Code/Assignment_7/FRT_Library/FreeRTOS/Source/portable/MemMang" -I"D:/Git/Robinson_F16_projekt/Code/C code/Code/Assignment_7/FRT_Library/FreeRTOS/Source/portable/GCC/ARM_CM3" -I"D:/Git/Robinson_F16_projekt/Code/C code/Code/Assignment_7" -I"D:/Git/Robinson_F16_projekt/Code/C code/Code/Assignment_7/Modules" -I"D:/Git/Robinson_F16_projekt/Code/C code/Code/Assignment_7/FRT_Library/FreeRTOS" -I"D:/Git/Robinson_F16_projekt/Code/C code/Code/Assignment_7/FRT_Library/FreeRTOS/Source" -I"D:/Git/Robinson_F16_projekt/Code/C code/Code/Assignment_7/FRT_Library/FreeRTOS/Source/include" -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -MD -std=c99 -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


