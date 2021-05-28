PATH_TO_BIN=../../llvm-src/build/bin

LLVM_CONFIG=$(PATH_TO_BIN)/llvm-config

CXX=`$(LLVM_CONFIG) --bindir`/clang
CXXFLAGS=`$(LLVM_CONFIG) --cppflags` -fPIC -fno-rtti
LDFLAGS=`$(LLVM_CONFIG) --ldflags`

all: constSplit.so

constSplit.so: constSplit.o
	$(CXX) -shared constSplit.o -o constSplit.so $(LDFLAGS) -fPIC

constSplit.o: constSplit.cpp
	$(CXX) -c constSplit.cpp -o constSplit.o $(CXXFLAGS)

clean:
	rm -f *.o constSplit.so