#what compiler to use (just a var)
CXX = g++
#what compiler flags to use (just a var)
CXXFLAGS = -Wall


#what linker/libraries to use (just a var) [folder: usr/lib or /lib] removes lib at start of file
LDFLAGS = 

#what target to build 
TARGET = main.out
#Specify main file as this file no need object and header file 
MAIN = main.cpp
#Get all cpp files in here, but exclude the main file
SOURCES = $(filter-out $(MAIN), $(wildcard *.cpp))

#Get all missing header files, so convert all cpp files to .h but exclude all existing header file, what is left is cpp files without header
MISSING_HEADERS = $(filter-out $(wildcard *.h), $(SOURCES:.cpp=.h))
OBJECTS = $(SOURCES:.cpp=.o)

#look to see if there is any missing header files
#if not equal, so if contains anything, strip removes the whitespace that is generated between files
ifneq ($(strip $(MISSING_HEADERS)),)
#throw error printing all the missing headers
$(error Missing header file(s): $(MISSING_HEADERS))
endif

#default target, this runs when calling make
all: $(TARGET)
	@echo "Build complete"
	@echo "Running code:"
	@echo "_______________________________________"
	@echo 
	@echo 
	@./$(TARGET)

#make new executable(TARGET), if main or dependenci(dependencies) have changed, also make dependencies if not availerble
$(TARGET): $(MAIN) $(OBJECTS)
	#command
	@echo "Linking $^ into $@"
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ 

#make dependicies
%.o: %.cpp
	@echo "Compiling $< into $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

#clean up generated files
clean:
	@echo "Cleaning up your mess"
	rm -f $(OBJECTS) $(TARGET)