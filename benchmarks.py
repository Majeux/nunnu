#!/bin/python3
from subprocess import Popen
from multiprocessing import Process, Value
from typing import List
from datetime import datetime

N_BOUND = range(1, 1000, 1)
MAX_BOUND = range(1, 10000, 1000)
EXEC  = "./bench"
SAMPLES = 100 # how many times to run each algorithm to average results over

def loop(samples: int, params: List):
    s = "-s" # -s prints result field names and values 

    date_string = datetime.now().strftime("%d-%m-%Y_%H:%M:%S")
    with open("./results/{}.result".format(date_string), 'a') as results:
        # results.write("# Sampling = {}\n".format(samples))

        for (n, m) in params:
            # Can interrupt with C-c, kills subprocess
            call = [
                EXEC,
                s,
                "-r", "{}".format(SAMPLES),
                "-n", "{}".format(n),
                "-m", "{}".format(m)]

            process = Popen(call, stdout=results)

            s = "-S" # -S only prints result values
            process.wait()

if __name__ == "__main__":
    print("Executing Unnu benchmarks")

    params = [ (n, max) for n in N_BOUND for max in MAX_BOUND if n <= max ]

    loop(SAMPLES, params)

