make clean
make mkdir
echo "-------------------------------- Build --------------------------------\n"
make compile
echo "\n-------------------------------- Run --------------------------------\n"
./bin/main ./tests/hello.as ./tests/world.as