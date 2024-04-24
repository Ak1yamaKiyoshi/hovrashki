SFML_PATH=external/SFML

g++ -c main.cpp -I $SFML_PATH/include
g++ main.o -o sfml-app -L $SFML_PATH/lib -lsfml-graphics -lsfml-window -lsfml-system
export LD_LIBRARY_PATH=$SFML_PATH/lib && ./sfml-app
