from mpi4py import MPI

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
#name = comm.Get_name()
print(f"Number of processes: {size}")
print(f"Process number: {rank}")
#print(f"Process name: {name}")