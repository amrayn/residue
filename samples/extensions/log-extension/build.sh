darwin=1
if [ "$darwin" = "1" ];then
    g++ -dynamiclib -flat_namespace -std=c++11 -I../../../src/ ../../../src/extensions/extension.cc ../../../src/extensions/log-extension.cc simple.cc -o simple.dylib -DRESIDUE_EXTENSION_LIB
else
    g++ -fPIC -shared -std=c++11 -I../../../src/ ../../../src/extensions/extension.cc ../../../src/extensions/log-extension.cc simple.cc -o simple.so -DRESIDUE_EXTENSION_LIB
fi