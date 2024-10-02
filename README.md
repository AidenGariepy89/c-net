# The Goal: Custom Transport-Level Protocol

This is my journey to learning c programming and network programming.

## ChatGPT's sage wisdom on getting better at C

To build your C skills to a level where you can comfortably create a custom transport protocol, here are some progressively challenging project ideas that will help you improve your understanding of systems programming and networking:
1. Basic Network Programming (Start Small)

    Project: Simple TCP/UDP Chat Application
    Create a simple command-line chat application using TCP and UDP. You'll get familiar with socket programming, including creating sockets, binding them, connecting, and managing data transmission.
    Key Skills: Sockets API, handling multiple clients (basic concurrency).

2. Raw Socket Programming (Intermediate Level)

    Project: Raw Packet Sniffer
    Build a basic packet sniffer that captures and inspects raw network packets. You’ll use raw sockets to capture IP packets and parse different headers (Ethernet, IP, TCP/UDP).
    Key Skills: Understanding packet structures, parsing headers, working with raw sockets.

3. Multithreading and Concurrency (Critical Skill)

    Project: Multithreaded Web Server
    Develop a simple web server that serves HTTP requests, capable of handling multiple concurrent clients. Implement it with thread pools or an event-driven model using select/epoll.
    Key Skills: Thread synchronization (mutexes, semaphores), select/epoll system calls, performance optimization.

4. Protocol Implementation (Custom Protocol Logic)

    Project: Reliable Data Transfer Protocol over UDP
    Implement a reliable transport protocol on top of UDP. This would include features like connection establishment, acknowledgment of packets, packet loss detection and retransmission, and congestion control.
    Key Skills: Error handling, reliability mechanisms (acknowledgment, timeouts, retransmission), flow control.

5. Custom Networking Stack (Advanced)

    Project: Custom Transport Layer Protocol
    Develop a minimal custom transport protocol over IP using raw sockets, managing everything from packet creation to ensuring delivery. Implement custom headers, packet segmentation, and reassembly.
    Key Skills: Raw IP packet manipulation, packet reassembly, understanding TCP/IP stack in detail, custom header formats.

6. Kernel-Level Programming (Optional but Deep Dive)

    Project: Linux Kernel Module for Packet Filtering
    If you're interested in going deeper, write a simple Linux kernel module that intercepts and filters network packets. This would involve interfacing directly with the Linux kernel networking stack.
    Key Skills: Linux kernel development, Netfilter/iptables, working in kernel space.

These projects will progressively build your understanding of networking, systems programming, and advanced C concepts. Along the way, you'll become more familiar with Linux APIs and the intricacies of network protocols, which will eventually prepare you to build your own transport-level protocol.
