# AsyncTaskProgram

AsyncTaskProgram is an executable allowing user to create, pause, resume or stop asynchronous tasks. 
It uses the library AsyncTaskLib for such propose.

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

- Cmake version 3.22 is required. If you don't have it, replace the minimum cmake requirement in CMakeLists.txt files and cross your fingers :)
- Qt version 5.X installed on your computer and findable by cmake. Version 5.11 or above should work.

# Improvements

With more time and if I'd have to do it again, I would work on these points: To be discussed during the technical interview.

1. Thread synchronisation. I did not dig much the potential of conditional waiting. It would have been more interesting I guess to exploit Qt slots/signal in certain cases. Writing Unit test revealed that some actions were performed in the main thread while tasks still not initialized. Sleeping the main thread works but isn't a very robust approach. My concern is that it would be the main thing to improve. 
2. With more time given, I'd have made a strong improvement. It would be great for the user of the library, to be able to create its own tasks by inheriting AsynchronousTask. Users should only have to implement a job function and a type function somehow. It is not possible with the current implementation, but minimal changes would allow it. That, coupled with the Thread pool would allow a user to define its own task and then to use the library to manipulate its task safely.
3. Job management: It would have been interesting to have different types of jobs doing different things. It would actually have driven the implementation of the ASynchronousTask and it's job() function. The current functions are really dependant of the architecture (and vice-versa), and that would be interesting to break that interdependency and improve the design.
4. Correctly manage the classes & functions exposition. That might be interesting not to expose the AsynchronousTask to oblige any user to use the ThreadPool, except if 2. is done.
5. Robustness of the code. Still can be improved
6. So much more, but it's infinite
