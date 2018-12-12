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

Once that is done, run the following command to build Boost and install the necessary files:

```bash
./b2 install
```

You can then proceed to open the project in CLion. To do this select open and then select the craftworld folder. To be able to build the project you need CMake and a toolchain (MinGW is preferred if you use windows).

To run the server, you will need to add an environment variable to the run configuration so that the MPI libraries can be found. To do so, in cLion, go to `Run -> Edit configurations... -> CraftWorld-Server` and click the icon at the right of `Environment variables`.
Then, add a new entry with `LD_LIBRARY_PATH` as name and `/usr/local/lib` as value.

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
