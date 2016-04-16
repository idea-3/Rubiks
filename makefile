all:
	g++ rubiks.cpp -o rubiks -m32 glut32.lib -lopengl32 -lglu32
