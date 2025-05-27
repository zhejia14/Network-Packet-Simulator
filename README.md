# Network Packet Simulation Framework in C++

A **C++-based network packet simulator** designed to simulate packet routing, transmission, and event handling across multiple nodes. This project is ideal for learning network simulation, object-oriented design, and event-driven programming.

This is a project from Object-Oriented Programming (OOP) course at National Chung Cheng University (CCU).
---

## Project Overview

This simulation framework models how packets are generated, transmitted, and processed in a network environment. It includes:

- Multiple types of **nodes**
- Various **packet types** (e.g., data, control)
- Event-based execution with scheduling
- Routing logic and forwarding tables
- Support for broadcasting and unicast communication

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


---

## 📝 Notes

- The code uses **polymorphism**, **factories**, and **event queues** to allow extensibility.
- You can easily extend the system by adding new packet types, headers, or payloads.
- All events are scheduled and executed based on their priority and trigger time.
- This is an educational simulation; not suitable for real-time systems without modification.

---

## Educational Use

This project is particularly useful for:

- Learning **object-oriented design patterns**
- Understanding **network protocol stacks**
- Practicing **event-driven programming**
- Exploring **routing algorithms** and **forwarding tables**
