################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Source/BallTrackerImpl.cpp \
../src/Source/BallTrackerMock.cpp \
../src/Source/MotorCommunicatorImpl.cpp \
../src/Source/RowControllerImpl.cpp \
../src/Source/TableControllerImpl.cpp \
../src/Source/TableControllerMock.cpp \
../src/Source/VirtualKickerWindow.cpp 

OBJS += \
./src/Source/BallTrackerImpl.o \
./src/Source/BallTrackerMock.o \
./src/Source/MotorCommunicatorImpl.o \
./src/Source/RowControllerImpl.o \
./src/Source/TableControllerImpl.o \
./src/Source/TableControllerMock.o \
./src/Source/VirtualKickerWindow.o 

CPP_DEPS += \
./src/Source/BallTrackerImpl.d \
./src/Source/BallTrackerMock.d \
./src/Source/MotorCommunicatorImpl.d \
./src/Source/RowControllerImpl.d \
./src/Source/TableControllerImpl.d \
./src/Source/TableControllerMock.d \
./src/Source/VirtualKickerWindow.d 


# Each subdirectory must supply rules for building sources it contributes
src/Source/%.o: ../src/Source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


