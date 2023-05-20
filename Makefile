default: programc programcpp programzig programrust programjava

CC = clang
CXX = clang++
CFLAGS = -O2 -lm

RR = cargo build
RFLAGS = --release

ZZ = zig build
ZFLAGS = -Doptimize=ReleaseFast

programc:
	${CC} ./c/main.c ${CFLAGS} -o programc

programcpp:
	${CXX} ./cpp/main.cpp ${CFLAGS} -o programcpp

programrust:
	cd ./rust && ${RR} ${RFLAGS} && cd .. && mv ./rust/target/release/programrust ./programrust

programzig:
	cd ./zig &&	${ZZ} ${ZFLAGS} && cd .. && mv ./zig/zig-out/bin/programzig ./programzig 

programjava:
	cd java;\
	javac ./jmain.java ./Account.java;\
	jar cfe jmain.jar jmain jmain.class;\
	jar uf jmain.jar ./*.class;\
	cd ..;\
	mv ./java/jmain.jar ./programjava
