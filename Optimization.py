import cProfile
import pstats
from io import StringIO
import numpy as np

"""# Step 1: Initial Profiling and Analysis
def simulate_physical_system(n):
    A = np.random.rand(n, n)
    B = np.random.rand(n, n)
    C = np.random.rand(n, n)

    # Perform matrix multiplication
    D = np.dot(A, B)

    # Element-wise operations
    E = D * C

    # Solve a linear system
    x = np.linalg.solve(E, np.ones(n))

    return x

# Profiling
pr = cProfile.Profile()
pr.enable()

# Test the function with a large input size
result = simulate_physical_system(1000)

pr.disable()
s = StringIO()
ps = pstats.Stats(pr, stream=s).sort_stats('cumulative')
ps.print_stats()
print(s.getvalue())"""




# Step 2: Optimization
"""def simulate_physical_system(n):
    # Use float32 to reduce memory usage
    A = np.random.rand(n, n).astype(np.float32)
    B = np.random.rand(n, n).astype(np.float32)
    C = np.random.rand(n, n).astype(np.float32)

    # Perform matrix multiplication
    D = np.dot(A, B)

    # Element-wise operations
    E = D * C

    # Solve a linear system
    x = np.linalg.solve(E, np.ones(n, dtype=np.float32))  # Ensure the right dtype here as well

    return x


# Profiling
pr = cProfile.Profile()
pr.enable()

# Test the function with a large input size
result = simulate_physical_system(1000)

pr.disable()
s = StringIO()
ps = pstats.Stats(pr, stream=s).sort_stats('cumulative')
ps.print_stats()
print(s.getvalue())"""


# Step 3 and 4: Parallelization using multiprocessing and testing the code
from joblib import Parallel, delayed

def elementwise_operation(D, C):
    return D * C

def simulate_physical_system(n):
    A = np.random.rand(n, n).astype(np.float32)
    B = np.random.rand(n, n).astype(np.float32)
    C = np.random.rand(n, n).astype(np.float32)

    # Perform matrix multiplication
    D = np.dot(A, B)

    # Parallel element-wise operations
    E = Parallel(n_jobs=-1)(delayed(elementwise_operation)(D[i, :], C[i, :]) for i in range(n))

    # Convert list of arrays back to a numpy array
    E = np.array(E)

    # Solve a linear system
    x = np.linalg.solve(E, np.ones(n, dtype=np.float32))

    return x

# Profiling
pr = cProfile.Profile()
pr.enable()

# Test the function with a large input size
result = simulate_physical_system(1000)

pr.disable()
s = StringIO()
ps = pstats.Stats(pr, stream=s).sort_stats('cumulative')
ps.print_stats()
print(s.getvalue())


import time

# Measure performance
start_time = time.time()
result = simulate_physical_system(1000)
execution_time = time.time() - start_time
print(f"Execution time: {execution_time:.4f} seconds")