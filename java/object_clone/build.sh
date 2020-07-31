mkdir -p ./classes

javac -d ./classes Program.java CloneMe.java


java -cp ./classes Program

echo "build.sh is done."