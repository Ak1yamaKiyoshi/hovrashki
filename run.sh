SFML_PATH=external/SFML
SRC_DIR=src
APP_NAME=hovrashki_app
APP_LIB_NAME=hovrashki

echo "[1/2] BUILDING"

g++ -c main.cpp -I $SFML_PATH/include  -I src
g++ main.o -o $APP_NAME -L $SFML_PATH/lib -lsfml-graphics -lsfml-window -lsfml-system

echo " > Build files: $APP_LIB_NAME.o, $APP_NAME"
echo " > Type 'export LD_LIBRARY_PATH=$SFML_PATH/lib && ./$APP_NAME' for running the app." 
echo "[2/2] RUNNING"

export LD_LIBRARY_PATH=$SFML_PATH/lib && ./$APP_NAME
