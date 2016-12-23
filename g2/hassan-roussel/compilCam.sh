echo "Compilation du programme en cours ..."
g++ $1 -o $2 -I/usr/local/include/ `pkg-config --libs opencv`
echo "Compilation du programme termin√e avec succ√s"
