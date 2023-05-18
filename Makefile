default: programc programcpp programzig programrust

CC = clang
CXX = clang++
CFLAGS = -O2 -lm

ZZ = zig build
ZFLAGS = -Doptimize=ReleaseFast

RR = cargo build
RFLAGS = --release

programc:
	${CC} ./c/main.c ${CFLAGS} -o programc

programcpp:
	${CXX} ./cpp/main.cpp ${CFLAGS} -o programcpp

programzig:
	cd ./zig &&	${ZZ} ${ZFLAGS} && cd .. && mv ./zig/zig-out/bin/programzig ./programzig 

programrust:
	cd ./rust && ${RR} ${RFLAGS} && cd .. && mv ./rust/target/release/programrust ./programrust