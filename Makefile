# Compiler and compiler flags.
CXX = g++-6
CXXFLAGS = -Wall -Wextra -Wreorder -L /lib64 -l pthread -l boost_system -I${INCLUDEDIR} -DDEBUG -g

# Directory hierarchy.
OUTDIR = bin
DEBUGDIR = debug
RELEASEDIR = release
INCLUDEDIR = includes
INDIR = src

# CPP files within their respective folders.


MAIN = main stdafx
BOOT = Icarus
COMMUNICATION_STREAMS = Request Response
MANAGERS_SESSION = Session SessionManager
NETWORK = NetworkServer NetworkConnection

# Relative paths to the Makefile for all of the CPP files.
STEMS = ${MAIN} ${BOOT:%=boot/%} ${COMMUNICATION_STREAMS:%=communication/streams/%} ${MANAGERS_SESSION:%=managers/session/%} ${NETWORK:%=network/%}

# List of object files (targets) and source files (dependencies).
OBJECTS = ${STEMS:%=${OUTDIR}/${DEBUGDIR}/%.o}
SOURCES = ${STEMS:%=${INDIR}/%.cpp}

# Executable.
EXEC = icarus_server

.phony: all dirData clean

# Target for linking the main executable.
all: ${OBJECTS} dirData
	@echo -n Linking project to ${EXEC}...
	@mkdir -p ${OUTDIR}/${RELEASEDIR}
	@${CXX} ${CXXFLAGS} ${OBJECTS} -o ${OUTDIR}/${RELEASEDIR}/${EXEC}
	@echo done!

# Target for compiling the individual object files.
${OUTDIR}/${DEBUGDIR}/%.o: ${INDIR}/%.cpp
	@echo -n Compiling ${<}...
	@mkdir -p ${@D}
	@${CXX} ${CXXFLAGS} -c ${<} -o ${@}
	@echo done!

# Target for making the directory structure in release.
dirData:
	@echo -n Making files directory in ${OUTDIR}/${RELEASEDIR}...
	@mkdir -p ${OUTDIR}/${RELEASEDIR}/files
	@echo done!
	@echo -n Copying files over...
	@cp files/* ${OUTDIR}/${RELEASEDIR}/files/.
	@echo done!

# Target for cleaning the environment.
clean:
	@echo -n Removing the ${OUTDIR} directory...
	@rm -r -f ${OUTDIR}
	@echo done!