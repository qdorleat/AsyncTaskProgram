# AsyncTaskProgram

AsyncTaskProgram is an executable allowing user to create, pause, resume or stop a asynchronous task. 
It uses the library AsyncTaskLib for such propose

## Build

To build the AsyncTaskProgram program, unzip it and open it and then, create a build directory, run cmake on the target, then make:
```
mkdir build
cd build
cmake ..
make
```
It will build the program, the AsyncTaskLib dependent static library, as well as the tests of the program the ones of the library. 

## Run

Run the program simply, by running
```
./AsyncTaskProgram
```

## Run the tests

Once you have built the project. (It will build the AsyncTaskLib and the tests at the same time), in the build directory, you can run the test, by doing

```
cd tests
ctest -R unit_CommandParser
```

## Help and program instructions

Run the program help, by running:
```
./AsyncTaskProgram --help
```

## Requirements

Cmake version 3.22 is required. If you don't have it, replace the minimum cmake requirement in CMakeLists.txt files and cross your fingers :)

# Improvements

Many things can also be improved, and here is a list. 

1. Thread synchronisation. I did not dig much the potential of conditional waiting. It would have been more interesting I guess to exploit Qt slots/signal in certain cases. Writing Unit test revealed that some actions were performed in the main thread while tasks still not initialized. Sleeping the main thread works but isn't a very robust approach. My concern is that it would be the main thing to improve. 

2. Probably more tests. I tried to test the pieces of code were to logic was. It doesn't cover everything, but tests can always be improve of course.

3. Robustness of the code. Still can be improved.