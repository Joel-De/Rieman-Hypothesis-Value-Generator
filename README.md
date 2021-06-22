# Rieman-Hypothesis-Value-Generator

The following is a program that generates values from the Rieman hypothesis, a conjecture that is yet to be solved. This program is not to be viewed as a mathamatical solution as the methods it utilizes are primitive, but as an application of performance implications of multithreading parallel workloads. Currently there are 3 approaches, single threaded, multi-threaded, and GPU acceleration with CUDA. Included is both a directory with visual studio project files, and an independent folder with source code. The number of summations is flexible for the cpu compute functions, but is dependent on your hardware for CUDA, since if the process takes too long a watchdog violation is called and the kernel terminates, this is mostly in part to this implementation not being fully parallel in nature.

Creates a map of the complex values that the Riemann Zeta function outputs for a given complex input in the critical strip (complex numbers with real value 0.5 and imaginary part within a range). This information can then be used for further analysis in another framework preventing the need to constantly regenerate the data.

The output is in CSV file, a sample of this is provided and available for download.


The code was compiled with nvcc for CUDA 11.3.109 and tested on a GPU (K2200) with compute capability 50
The CPU used in the CPU tests is a Xeon 1620 v3

The following are the results:

Single Thread: 5:07
Multithread: 0:53
Cuda Acceleration : 0:38

