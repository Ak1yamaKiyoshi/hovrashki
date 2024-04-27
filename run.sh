SFML_PATH=external/SFML
SRC_DIR=src

g++ -c main.cpp -I $SFML_PATH/include  -I src
g++ main.o -o sfml-app -L $SFML_PATH/lib -lsfml-graphics -lsfml-window -lsfml-system
export LD_LIBRARY_PATH=$SFML_PATH/lib && ./sfml-app
