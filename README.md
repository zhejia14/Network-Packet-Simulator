
# Network Packet Simulator  

This is a **C++-based network packet simulator** developed as part of the homework assignments for the **Object-Oriented Programming (OOP)** course at **National Chung Cheng University (CCU)**.

This project includes multiple homework submissions, including:

- **Homework 1**: Implementation of shortest path routing and traffic distribution logic
- **Homework 2**: Basic packet and node structure with event-driven simulation
- **Homework 3**: Routing logic and forwarding table implementation
- **Homework 4**: Event-based simulation with SDN controller and traffic matrix support

The goal of this series is to understand and apply object-oriented programming concepts such as inheritance, polymorphism, event scheduling, and modular design in the context of network simulation.

---

## Project Overview

This simulation framework models how packets are generated, transmitted, and processed across a network of nodes. It uses an **event-driven architecture**, allowing users to simulate complex network behavior by defining events and handling them in chronological order.

Each homework builds on top of the previous one, adding new features like routing tables, SDN control packets, and dynamic path selection.

---

## Key Components

| Component | Description |
|---------|-------------|
| `node` | Represents a network node capable of sending and receiving packets |
| `packet` | Base class for different types of network packets |
| `header` | Stores metadata such as source ID, destination ID, next hop |
| `payload` | Contains the actual data carried by a packet |
| `event` | Encapsulates actions like packet reception or transmission |
| `link` | Simulates delay and latency between nodes |

These components form the core of the system and are extended in each homework assignment.

---

## Notes

- Each homework adds new features to the system:
  - **Homework 1**: Initial setup of routing logic using Dijkstra’s algorithm and traffic distribution
  - **Homework 2**: Introduction of packet/event/node classes with virtual functions and polymorphism
  - **Homework 3**: Implementation of routing tables and shortest path selection
  - **Homework 4**: Supporting SDN controllers, dynamic traffic distribution, and broadcasting
- The use of `dynamic_cast`, virtual functions, and factory methods demonstrates advanced OOP techniques.
- All events are scheduled and executed based on their trigger time and priority.
