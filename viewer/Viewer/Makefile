

# LINUX
#---------------------------------------------------------------------

# définition des répertoires d'inclusion des bibliothèques .h
INCLUDE= -I /usr/include/GL

# définition des librairies à utiliser lors de l'étape d'édition de liens
LIB=  -lpthread -lglut -lGLU -lGL  -lm 

# définition du compilateur à utiliser 
CC=g++

# définition des options de compilation à utiliser
# -g : en vue d'autoriser l'utilisation du débugger
# -Wall : afficher le maximum de messages d'erreurs
OPT= -std=c++11 -g -Wall

OBJ=./Obj
SRC=./Src

# définition des cibles de compilation

#viewer:	$(OBJ)/viewer.o $(OBJ)/graphique.o $(OBJ)/touches.o   
#	$(CC) -o viewer $(OBJ)/viewer.o $(OBJ)/graphique.o $(OBJ)/touches.o  $(OPT)  $(LIB)
viewer:	$(OBJ)/viewer.o $(OBJ)/graphique.o $(OBJ)/touches.o  $(OBJ)/OBJReader.o $(OBJ)/CRay.o $(OBJ)/CIntersection.o $(OBJ)/OBJMaterial.o $(OBJ)/OBJGroup.o $(OBJ)/OBJGroupList.o $(OBJ)/OBJTriangle.o  $(OBJ)/OBJLight.o $(OBJ)/Cpoint.o $(OBJ)/Cvector.o $(OBJ)/OBJVertex.o
	$(CC) -o viewer $(OBJ)/viewer.o $(OBJ)/graphique.o $(OBJ)/touches.o  $(OBJ)/OBJReader.o $(OBJ)/CRay.o $(OBJ)/CIntersection.o $(OBJ)/OBJMaterial.o $(OBJ)/OBJGroup.o $(OBJ)/OBJGroupList.o $(OBJ)/OBJTriangle.o  $(OBJ)/OBJLight.o $(OBJ)/Cpoint.o $(OBJ)/Cvector.o $(OBJ)/OBJVertex.o $(OPT)  $(LIB)

$(OBJ)/viewer.o:	$(SRC)/viewer.cpp
	$(CC) -c $(SRC)/viewer.cpp -o $(OBJ)/viewer.o   $(OPT) $(INCLUDE)  $(OPT)


$(OBJ)/CRay.o:	$(SRC)/Obj/CRay.cpp $(SRC)/Obj/CRay.hpp
	g++ -c $(SRC)/Obj/CRay.cpp -o $(OBJ)/CRay.o $(OPT)


$(OBJ)/CIntersection.o:	$(SRC)/Obj/CIntersection.cpp $(SRC)/Obj/CIntersection.hpp
	g++ -c $(SRC)/Obj/CIntersection.cpp -o $(OBJ)/CIntersection.o $(OPT)


$(OBJ)/graphique.o:	$(SRC)/graphique.c
	$(CC) -c $(SRC)/graphique.c -o $(OBJ)/graphique.o $(OPT) $(INCLUDE)  $(OPT)


$(OBJ)/touches.o:	$(SRC)/touches.c
	$(CC) -c  $(SRC)/touches.c -o $(OBJ)/touches.o $(OPT) $(INCLUDE) $(OPT)



$(OBJ)/OBJMaterial.o:	$(SRC)/Obj/OBJMaterial.cpp $(SRC)/Obj/OBJMaterial.hpp
	g++ -c $(SRC)/Obj/OBJMaterial.cpp -o $(OBJ)/OBJMaterial.o    $(OPT)

$(OBJ)/OBJGroup.o:	$(SRC)/Obj/OBJGroup.cpp $(SRC)/Obj/OBJGroup.hpp
	g++ -c $(SRC)/Obj/OBJGroup.cpp -o $(OBJ)/OBJGroup.o     $(OPT)

$(OBJ)/OBJGroupList.o:	$(SRC)/Obj/OBJGroupList.cpp $(SRC)/Obj/OBJGroupList.hpp
	g++ -c $(SRC)/Obj/OBJGroupList.cpp -o $(OBJ)/OBJGroupList.o    $(OPT)

$(OBJ)/OBJTriangle.o:	$(SRC)/Obj/OBJTriangle.cpp $(SRC)/Obj/OBJTriangle.hpp
	g++ -c $(SRC)/Obj/OBJTriangle.cpp -o $(OBJ)/OBJTriangle.o	$(OPT) $(INCLUDE) $(OPT)


$(OBJ)/OBJLight.o:	$(SRC)/Obj/OBJLight.cpp $(SRC)/Obj/OBJLight.hpp
	g++ -c $(SRC)/Obj/OBJLight.cpp -o $(OBJ)/OBJLight.o     $(OPT)

$(OBJ)/Cpoint.o:	$(SRC)/Cpoint.cpp $(SRC)/Cpoint.hpp
	g++ -c $(SRC)/Cpoint.cpp -o $(OBJ)/Cpoint.o     $(OPT)

$(OBJ)/Cvector.o:	$(SRC)/Cvector.cpp $(SRC)/Cvector.hpp
	g++ -c $(SRC)/Cvector.cpp -o $(OBJ)/Cvector.o $(OPT)

$(OBJ)/OBJVertex.o:	$(SRC)/Obj/OBJVertex.cpp $(SRC)/Obj/OBJVertex.hpp
	g++ -c $(SRC)/Obj/OBJVertex.cpp -o $(OBJ)/OBJVertex.o    $(OPT)

$(OBJ)/OBJReader.o:	$(SRC)/Obj/OBJReader.cpp $(SRC)/Obj/OBJReader.hpp $(SRC)/Obj/OBJMaterial.hpp  $(SRC)/Obj/OBJGroupList.hpp  $(SRC)/Obj/OBJGroup.hpp
	g++ -c $(SRC)/Obj/OBJReader.cpp -o $(OBJ)/OBJReader.o $(OPT) $(INCLUDE)  $(OPT)

# cible d'effacement des fichiers objets et de l'exécutable

clean:
	rm -f $(OBJ)/*.o viewer

