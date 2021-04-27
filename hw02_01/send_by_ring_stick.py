from mpi4py import MPI

comm = MPI.COMM_WORLD
message = "Message"
number_of_processes = comm.Get_size()
current_process = comm.Get_rank()

next_process = (current_process + 1) % number_of_processes
previous_process = (current_process - 1) % number_of_processes

if current_process == 0:
    comm.send(message, dest=next_process)
    print(f"Process {current_process} has sent a message to process {next_process}")

    comm.recv(source=previous_process)
    print(f"Process {current_process} has received a message from process {previous_process}")
else:
    comm.recv(source=previous_process)
    print(f"Process {current_process} has received a message from process {previous_process}")

    comm.send(message, dest=next_process)
    print(f"Process {current_process} has sent a message to process {next_process}")