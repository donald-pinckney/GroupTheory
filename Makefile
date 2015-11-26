example.out : example.o DihedralIsometry.o CommonGroups.o Permutation.o 
	g++ -Wall -O3 -o example.out example.o DihedralIsometry.o CommonGroups.o Permutation.o  

example.o : Group.cpp Group.h Set.cpp Set.h Subgroup.cpp Subgroup.h example.cpp
	g++ -Wall -O3 -c example.cpp -o example.o

DihedralIsometry.o : DihedralIsometry.h DihedralIsometry.cpp 
	g++ -Wall -O3 -c DihedralIsometry.cpp

CommonGroups.o : CommonGroups.h CommonGroups.cpp 
	g++ -Wall -O3 -c CommonGroups.cpp

Permutation.o : Permutation.h Permutation.cpp 
	g++ -Wall -O3 -c Permutation.cpp

clean : 
	rm -f *.out *.o  
