# Getting started

First we need to get Boost up and running. To do so, after cloning this repository, open a bash shell in the root directory and execute the following command:

```bash
git submodule update --init --recursive
```

This will download the Boost libraries from the official git repository. Next, execute the following commands to prepare Boost for installation:

```bash
cd ./Libraries/boost
./bootstrap.sh --prefix=./
```

This will create a `project-config.jam` file in the current folder. Open this file in any text editor, and add the following line to the bottom:

```
using mpi ;
```

You will also need to have an MPI implementation installed on the system that will compile and run the server. OpenMPI is a good implementation and can be found here: <https://www.open-mpi.org/>. Instructions on how to install OpenMPI are available here: <https://www.open-mpi.org/faq/?category=building#easy-build>.

There is currently a bug in Boost.MPI that has been fixed less than a week ago but is still in the development branch of boost.
To get the bugfix into the local copy of boost, execute the following commands to fast forward to its commit:

```bash
cd ./libs/mpi
git checkout develop
git pull
git checkout master
git merge dd03e959d7914eba4edcd9d03067cb620a7c43cf
```

Once that is done, run the following command to build Boost and install the necessary files:

```bash
cd ../..
./b2 install
```
Or run 
```bash
./b2 install --address-model=64
```
To install it in 64 bit.

You can then proceed to open the project in CLion. To do this select open and then select the craftworld folder. To be able to build the project you need CMake and a toolchain (MinGW is preferred if you use windows).

If you have problems running your executables (Client and Server alike) due to an error that the dynamic libraries weren't linked correctly, go to `Run -> Edit configurations... -> CraftWorld-Server` and click the icon at the right of `Environemnt variables`.
Then, add a new entry with `DYLD_LIBRARY_PATH` as name and the absolute path to the boost library lib folder, so something like `{pathToProject}/Libraries/boost/lib`. Do the same for CraftWorld-Client.

# Running the server

To run the server, you will need to add an environment variable to the run configuration so that the MPI libraries can be found. To do so, in CLion, go to `Run -> Edit configurations... -> CraftWorld-Server` and click the icon at the right of `Environment variables`.
Then, add a new entry with `LD_LIBRARY_PATH` as name and `/usr/local/lib` as value (if you installed the MPI library somewhere else, use that location as the value).

If you can't build the server due to the program not being able to find mpi.h try the following. Locate mpi.h on your computer, often this file can be found in the folder `/usr/local/include`. Then open the CMakeLists.txt file in the folder `{projectRoot}/Projects/Server`. In this file at the following line above the other include_directories or change the existing line when it is already there to:
```
include_directories({absolute path to mpi.h})
```
This should tell CMake where to find mpi.h.

Once you have added the variable and you can build the server project, open up a terminal and navigate to the folder where the server's build files are located.
Usually this is at `{projectRoot}/cmake-build-debug/Projects/Server`. This folder should contain the server executable, with the name `CraftWorld-Server`.

To run the executable, use the following command:

```bash
mpirun --oversubscribe -n {nodeCount} ./CraftWorld-Server {matchmakerCount} {matchmakerBasePort} {xChunks} {yChunks} {zChunks} {xBlocks} {yBlocks} {zBlocks}
```

Replace `{nodeCount}` with the amount of server nodes you want to run. One of these will be the matchmaker and the others will be the slaves.
The `--oversubscribe` flag is necessary if the system has fewer processing units than the amount of nodes you want to use.

# Connecting to the DAS-4

To connect to the DAS-4, first ssh into the VU proxy using this command:

```bash
ssh {VUnetID}@ssh.data.vu.nl
```

Then, once connected, use this command to connect to the DAS-4:

```bash
ssh dsys1804@fs0.das4.cs.vu.nl
```

Then use the password:

```
8qMyv9pQ
```
