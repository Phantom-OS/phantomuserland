# Phantom OS Genode port

This repository contains a port of Phantom OS to Genode OS framework.

## Intro

It is a new effort of developing Phantom OS. Porting Phantom OS to Genode should make it more stable, secure, portable. The main goal of this project is to make Phantom OS suitable for real-life applications and future research.

Phantom OS is an `orthogonally persistent` `managed code` general-purpose operating system.
- `Orthogonally persistent`. In short, it implies that all data objects in the system are stored in a big virtual memory the content of which is not erased between restarts (even unexpected ones).
- `Managed code`. In our case, all userspace programs are executed in bytecode inside a language virtual machine. 

Orthogonal persistence is an old concept and research on this topic almost stopped in the early 2000s. We believe that with the modern hardware (and, possibly, future hardware like Intel Optane) this concept might become relevant again. With this project, we would like to provide a foundation for testing the OP hypothesis in the modern environment. Moreover, we believe that a persistent operating system based on microkernels together with managed code userspace might become a platform suitable for industrial applications and might attract the attention of researchers and developers.

Potentially, this operating system can be used in a wide range of use cases. However, currently, we are focusing on IoT so that embedded programmers will be able to focus more on business logic.

> This section is lacking details intentionally to make it simpler. If you want to learn more about orthogonal persistence and our hypotheses, the corresponding paper will be published soon!

> Also if you want to learn more about Phantom OS refer to its official documentation https://phantomdox.readthedocs.io/en/latest/

## Current status

What is done:

- [x] Phantom Virtual Machine is able to work on Genode in 64 bits
- [x] The subset of kernel sources required to run PVM in a persistent environment
- [x] Adapters from Genode to Phantom OS low-level interfaces are implemented

What is in progress:

- [ ] The debugging and testing of adapters is in progress

What are the future plans:

- [ ] Finish the port
  - [ ] Make PVM work in persistent environment
  - [ ] Rework driver system
  - [ ] Rework and enable networking
  - [ ] Rework and enable graphics
- [ ] Add support to more languages using a WebAssembly runtime

### Project layout

For now, this repository contains a lot of unused old code since the porting process is still in progress. Directories containing sources that are actually used are:

- `/include` - contains Phantom OS headers
- `/include/genode-amd64` - contains architecture specific headers
- `/include/genode-libc` - contains Genode's libc headers
- `/phantom/isomem` - the set of sources from the old kernel that implement persistent memory layer
  - `/phantom/isomem/genode_*.cc` - source files containing stubs for interfaces that should be implemented in Genode. Some of them are disabled using conditional compilation with `PHANTOM_THREADS_STUB` macro
- `/genode_env` - adapters to Genode that are implementing Phantom OS low-level interfaces
- `/phantom/vm` - Phantom Virtual Machine

and PVM dependencies (graphics subsystem):

- `/phantom/libfreetype`
- `/phantom/gl`
- `/phantom/libwin`

> The detailed description of the adapters will be added soon

## How to contribute?

This project requires both research and development. Several ideas for research topics and development tasks are described in this section. If you are interested in any of them, feel free to contact us.

### Research

During this work we identified several interesting research topics:

- *Persistent errors and how to deal with them*. Since every object is allowed to live as long as it wants to, errors within them will live as well. The best case is when we can restore from one of the previous snapshots, however, we might encounter the situation when this fault is recurring. 
- *Connection between persistent and transient (non-persistent) worlds*. One of the main OP issues is that it is some sort of "closed" system where communications to other systems and even hardware devices should not affect the consistency of the persistent state.
- *Distributed persistent space*. The idea is to connect several instances of Phantom OS that would share a single global address space. In this scenario mechanisms for accessing, migrating objects should be researched as well as situations when some of the peers go offline.
- *Formal verification*. In a persistent system, the model of accessing data as well as the model of communication between other devices or systems are different. All data is assumed to be located in single-level persistent memory space and communication should be performed using special interfaces or protocols that would minimize side effects. We assume that those two factors might make formal verification of the programs easier.
- *Real-time*. We assume that the concept of Phantom OS is capable to be at least soft real-time. However, we have not researched this topic in-depth yet.

### Development

We assume that several tasks mentioned earlier as our plans can be done in parallel:

- Graphics system
- Driver system
- Networking

Also, if you want to participate in any of the current tasks feel free to contact us!

## Contacts

a.antonov@innopolis.ru - Anton Antonov, author of the port
dz@dz.ru - Dmitry Zavalishin, author of Phantom OS