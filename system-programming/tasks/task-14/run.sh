make clean
make mkdir

echo "#---------------------------------------------------#"
echo "# Build"
echo "#---------------------------------------------------#"

make compile

echo "#---------------------------------------------------#"
echo "# Run"
echo "#---------------------------------------------------#"

./bin/main ./tests/hello.as ./tests/world.as