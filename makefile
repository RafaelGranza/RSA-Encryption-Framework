all: 
	-g++ -c */*.h */*.cpp -O2
	-mkdir .compiled
	-mv */*.gch .compiled/
	-mv *.o .compiled/
	-g++ main.cpp -o main -O2
	-g++ break.cpp -o break -O2

.PHONY: clean

clean:
	-rm -f -r .compiled
	-rm -f main
	-rm -f break
