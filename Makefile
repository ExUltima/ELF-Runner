SOURCES=handle.cpp main.cpp process.cpp
OUTPUT=elf-runner.exe

CPPFLAGS=/EHsc /D_AMD64_

all : $(OUTPUT)

clean :
    -del *.obj 2> nul
    -del $(OUTPUT) 2> nul

$(OUTPUT) : $(SOURCES:.cpp=.obj)
    LINK /OUT:"$@" $**
