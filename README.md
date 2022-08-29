# Philosophers

Synchronise threads with multiple methods.

Each project works on the same principle: There are not enough forks for all
the Philosophers to eat at the same time, so they have to share their resources.

The first project works with mutexes inside threads (forks represent mutexes,
and each Philosopher is inside a thread).

The seconds project works with semaphores, also inside threads.

The third project works with semaphores as well, but inside forks.

This project taught me the basis of multi-threading.
