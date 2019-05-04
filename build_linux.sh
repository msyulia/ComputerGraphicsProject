echo 'Clearing build directories...'

if [ -d "./bin" ]; then
    rm -r ./bin
fi

if [ -d "./bin-int" ]; then
    rm -r ./bin-int
fi


./vendor/Premake/Linux/premake5 gmake
make 