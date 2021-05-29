PATH_TO_BIN=../../llvm-src/build/bin

LLVM_CONFIG=$(PATH_TO_BIN)/llvm-config

CXX=`$(LLVM_CONFIG) --bindir`/clang
CXXFLAGS=`$(LLVM_CONFIG) --cppflags` -fPIC -fno-rtti
LDFLAGS=`$(LLVM_CONFIG) --ldflags`

TARGET=constSplit.so replaceTest.so  dependTest.so# interleaving.so

TARGETOBJ=$(patsubst %.so, %.o, $(TARGET))

all: $(TARGET) littleClean

%.so: %.o
	$(CXX) -shared $< -o $@ $(LDFLAGS) -fPIC

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(TARGETOBJ) $(TARGET)

littleClean:
	rm -f $(TARGETOBJ)