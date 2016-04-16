all:
	g++ rubiks.cpp -o rubiks -m32 glut32.lib -lopengl32 -lglu32

rubiks2:
	g++ rubiks2.cpp -o rubiks2 -m32 glut32.lib -lopengl32 -lglu32 -std=c++11