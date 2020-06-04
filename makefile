
all: lib/libapc.a

CXXFLAGS="-Iinclude"

lib/libapc.a: lib/libapc.a(bin/apc_init.o) lib/libapc.a(bin/apc_terminar.o) \
	lib/libapc.a(bin/apc_activarseccion.o) lib/libapc.a(bin/apc_desactivarseccion.o) \
	lib/libapc.a(bin/apc_conectarseccion.o) lib/libapc.a(bin/apc_desconectarseccion.o) \
	lib/libapc.a(bin/apc_enviar.o) lib/libapc.a(bin/apc_recibir.o)

bin/apc_init.o: src/apc_init.cpp include/apc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/apc_terminar.o: src/apc_terminar.cpp include/apc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/apc_activarseccion.o: src/apc_activarseccion.cpp include/apc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/apc_desactivarseccion.o: src/apc_desactivarseccion.cpp include/apc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/apc_conectarseccion.o: src/apc_conectarseccion.cpp include/apc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/apc_desconectarseccion.o: src/apc_desconectarseccion.cpp include/apc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/apc_enviar.o: src/apc_enviar.cpp include/apc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin/apc_recibir.o: src/apc_recibir.cpp include/apc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<


clean:
	rm -f lib/libapc.a
	rm -f bin/*.o
	rm -f src/*.*~
