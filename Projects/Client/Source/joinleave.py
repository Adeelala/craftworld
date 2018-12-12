import socket, time, sys, subprocess
from multiprocessing import Process, Pool
import random

filename = "Main.cpp"

def run_client():
	subprocess.call(["g++", filename])
	subprocess.call("./a.out")

def do_processes(n):
# Create 1 process for each client

	for i in range(0, n):
		try:
			p = Process(target=run_client)
			p.start()
		except Exception as e:
			print(e)
	p.join()

if __name__ == '__main__':
# get user input for n clients or use 10 by default

	if len(sys.argv) >= 2:
		n_clients = int(sys.argv[1])
	else:
		n_clients = 10

	do_processes(n_clients)
