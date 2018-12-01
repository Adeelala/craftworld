# Getting started

First we need to get Boost up and running. To do so, after cloning this repository, open a bash shell in the root directory and execute the following command:

```bash
git submodule update --init --recursive
```

This will download the Boost libraries from the official git repository. Next, execute the following commands to build and install Boost:

```bash
cd ./Libraries/boost
./boostrap.sh --prefix=./
./b2 install
```

# Connecting to the DAS-4

To connect to the DAS-4, first ssh into the VU proxy using this command:

```bash
ssh ss{VUnetID}@ssh.data.vu.nl
```

Then, once connected, use this command to connect to the DAS-4:

```bash
ssh dsys1804@fs0.das4.cs.vu.nl
```

Then use the password:

```
8qMyv9pQ
```
