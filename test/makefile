include ~/make/plat.mak
INCDIR = -I../ -I../include
TARGET = lele_test_mutex
OBJECTS = lele_test_mutex.o Thread.o Mutex.o
ALL : clean $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@  -pthread

lele_test_mutex.o : lele_test_mutex.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCDIR)

Thread.o : ../thread/Thread.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I../thread/ -I../include/

Mutex.o : ../mutex/Mutex.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I../mutex/ -I../include/

#$(OBJECTS) : %.o : %.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCDIR)

.PHONY : clean
clean:
	$(RM) $(OBJECTS)
	$(RM) $(TARGET)
