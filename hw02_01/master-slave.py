from mpi4py import MPI

WORKTAG = 0
EXITTAG = 1

received = 0
exit = False

comm = MPI.COMM_WORLD
message = "Message"
number_of_processes = comm.Get_size()
current_process = comm.Get_rank()

if current_process == 0:
    status = MPI.Status()
    for process in range(1, number_of_processes):
        comm.send(message, dest=process, tag=WORKTAG)
        print(f"Master has sent a message to process {process}")
    while received < number_of_processes - 1:
        comm.recv(source=MPI.ANY_SOURCE, status=status)
        print(f"Master has received a message from process {received+1}")
        comm.send(0, dest=status.Get_source(), tag=EXITTAG)
        received += 1
else:
    status = MPI.Status()
    while not exit:
        comm.recv(source=0, status=status)
        if (status.Get_tag() == EXITTAG):
            exit = True
            print(f"Slave {current_process} has left")
        else:
            comm.send(message, dest=0, tag=WORKTAG)
            print(f"Slave {current_process} has sent a message to master")
