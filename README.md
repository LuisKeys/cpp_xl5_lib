# Fireball XL5 Algorithm Library
#### Author: **Luis Paradela**
#### Current supported OS: **Linux**
However it is developed in standard C++ and compiled with make hence it can be easily ported to MacOS or Windows

Library name is a tribute to Gerry Anderson Fireball XL5 TV show

#### How to build?
Open a Linux terminal:

1) Clone the follwing repo:
https://github.com/LuisKeys/cpp_xl_lib.git
```
git clone https://github.com/LuisKeys/cpp_xl_lib.git
```
2) Move inside the new project folder:
```
cd cpp_xl_lib
```

3) Remove __build__ folder and its content
```
rm -rf build
```

4) Re create __build__ folder:
```
mkdir build
```

5) Move inside __build__ folder:
```
cd build
```

6) Regenerate make files:
```
cmake ../
```

7) Move one level up to project root folder
(to check if you are inside __cpp_xl_lib__ type __pwd__ command)) :
```
cd ..
```

8) Execute __run.sh__ script:
```
./run.sh
```

From now simply repeat step 8 to rebuild and run the project.
