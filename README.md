# Benchmarks
- `run_naive`: insert random numbers into a set until it reaches the correct size
- `run_vec`: push the range into a vector and shuffle it
- `run_vec_prealloc`: same as `run_vec` but only shuffle (for cases were a dedicated vector is initialized once and reused)
- `run_nunnu`: use the nunnu algorithm
- `run_nunnuOLD`: use an old version of the nunnu algorithm
