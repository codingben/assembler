make clean
make mkdir

echo "#---------------------------------------------------#"
echo "# Build Assembler"
echo "#---------------------------------------------------#"

make compile

echo "#---------------------------------------------------#"
echo "# Run Assembler"
echo "#---------------------------------------------------#"

./bin/assembler ./tests/hello.as ./tests/world.as