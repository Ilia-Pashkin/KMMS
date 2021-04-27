from mpi4py import MPI

message = "Message"
comm = MPI.COMM_WORLD
number_of_processes = comm.Get_size()
current = comm.Get_rank()

status = MPI.Status()

for i in range(number_of_processes):
    for j in range(number_of_processes):
        if current == i:
            if i == j:
                comm.isend(message, dest=j)
                #print(f"From {i} to {j}")
            else:
                comm.send(message, dest=j)
                #print(f"From {i} to {j}")
        if current == j:
            comm.recv(source=i)
            print(f"Got from {i} to {j}")