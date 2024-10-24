# Philosophers - Multithreading with Mutexes

## Project Overview

**Philosophers** is a project that simulates the classic "Dining Philosophers" problem, demonstrating the challenges of synchronization in multithreading. In this project, multiple philosophers are seated around a table, alternating between eating, thinking, and sleeping. They require two forks to eat, which introduces the need for proper resource management to avoid deadlocks and starvation.

This project provided hands-on experience with threading, mutexes, and concurrent programming in C, while emphasizing the importance of avoiding data races and ensuring proper synchronization between threads.

---

## Key Features

- **Program Name**: `philo`
- **Core Functionality**:
  - Simulates a dining philosophers problem where philosophers eat, think, and sleep in a loop.
  - Each philosopher requires two forks to eat, shared with their neighbors.
  - The simulation ensures that philosophers do not starve and properly manage shared resources (forks).

- **Arguments**:
  - `number_of_philosophers`: The number of philosophers (and forks).
  - `time_to_die`: Time (in milliseconds) a philosopher can go without eating before dying.
  - `time_to_eat`: Time (in milliseconds) a philosopher spends eating.
  - `time_to_sleep`: Time (in milliseconds) a philosopher spends sleeping.
  - `number_of_times_each_philosopher_must_eat` (optional): The simulation ends when all philosophers have eaten this many times.

---

## Technical Details

- **Multithreading**: Each philosopher is represented by a separate thread, allowing for concurrent execution.
- **Mutexes**: Used to prevent race conditions by ensuring that only one philosopher can pick up a given fork at a time.
- **System Calls**:
  - `pthread_create`, `pthread_join`: For creating and managing threads.
  - `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`: For managing access to shared resources (forks).
  - `usleep`, `gettimeofday`: For handling time and delays in the simulation.

### Simulation Rules:
- **Philosopher Actions**: Each philosopher alternates between eating, thinking, and sleeping. A philosopher must acquire both forks (left and right) before eating.
- **Fork Management**: Philosophers share forks with their neighbors. Fork availability is managed through mutexes to ensure proper synchronization.
- **Stopping Condition**: The simulation stops if a philosopher dies (doesn't eat within the `time_to_die`) or if all philosophers have eaten the required number of times.

---

## Skills Demonstrated

- **Multithreading and Synchronization**: Gained hands-on experience with thread creation and management, as well as synchronization using mutexes to prevent race conditions.
- **Concurrency Challenges**: Implemented solutions to avoid common concurrency problems like deadlocks and starvation in a multithreaded environment.
- **Processes and Semaphores (Bonus)**: Developed an alternative approach using processes and semaphores to manage shared resources, extending the core project with an additional concurrency model.
- **Error Handling and Edge Cases**: Ensured proper handling of edge cases such as philosophers dying or failing to acquire forks in time.

---

## Conclusion

The **Philosophers** project provided a deep understanding of multithreading, mutexes, and resource synchronization. By simulating the dining philosophers problem, I was able to demonstrate skills in concurrent programming, ensuring that shared resources are properly managed in a multithreaded environment without race conditions or deadlocks. The bonus part further extended these concepts by introducing processes and semaphores for resource control.
