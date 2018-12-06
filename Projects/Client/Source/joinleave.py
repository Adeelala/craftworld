# Via de command line kan het aantal clients worden meegegeven, als er niks wordt meegegeven dan
# worden er 10 clients gestart. Als een client gestart is dan stuurt het steeds "i am playing craftworld"
# naar de server totdat de speeltijd voorbij is en de client/speler de server/ het spel verlaat. De clients
# worden soortvan tegelijk opgestart met processen. Elk client is 1 proces. 

# port en max_playtime zijn hardcoded in de create client functie ingevoerd.

import socket, time, sys
from multiprocessing import Process, Pool
import random

class generateclient():

	def __init__(self, port):
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

		try:
			self.socket.connect(('localhost', port))
		except:
			"Could not connect"

		self.client_socklist = []
		self.client_socklist.append(self.socket);

def create_client():	
# Generate client and repeatedly send 
# message to show the client is running
	
	# max. speelsessie = 16.7 minuten voor nu, verander indien nodig
	max_playtime = 1000
	random_gametime = random.randint(0, max_playtime)

	port = 9997
	client =  generateclient(port)

	start_time = time.time()
	end_time = 0

	while  end_time < start_time + random_gametime:

		# ---------------------------------------------------------------------------------
		client.socket.send("I'm playing craftworld\n")

		data = client.socket.recv(512)

		print data
		# ---------------------------------------------------------------------------------

		end_time = time.time()

		print "playing craftworld.." + str(end_time) + " gametime: " + str(random_gametime)

	client.socket.close()

def do_processes(n):
# Create 1 process for each client

	for i in range(0, n):
		try:
			p = Process(target=create_client)
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
