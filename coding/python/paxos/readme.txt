Overview

Essential Paxos provides basic implementations of the Paxos algorithm. The distinguishing characteristic of this implementation, as compared to other freely available and open-source implementations, is that this library is independent of application domains and networking infrastructures. Whereas most Paxos implementations are deeply and inextricably embedded within application-specific logic, this implementation focuses on encapsulating the Paxos algorithm within opaque and easily re-usable classes.

This library provides an algorithmically correct Paxos implementation that may be used for educational purposes in addition to direct use in networked applications. This implementation is specifically designed to facilitate understanding of both the essential Paxos algorithm as well as the practical considerations that must be taken into account for real-world use.

Implementations in both Python and Java are provided.

Python Installation

$ easy_install essential-paxos
Implementations

Python

essential.py

This module provides a direct and minimal implementation of the essential Paxos algorithm. The primary purpose of this module is educational as it allows for easy contrast between the implementation of the pure algorithm and that of the one enhanced for practicality.

practical.py

This module enhances the essential Paxos algorithm and adds support for such things as leadership tracking, NACKs, and state persistence.

functional.py

This module provides a fully-functional Paxos implementation that employs a simple heartbeating mechanism to detect leadership failure and initiate recovery.

external.py

This module provides an enhanced version of practical.py that supports the use of external failure detectors to drive leadership management. This module does not provide a fully-functional solution to leadership management, as does functional.py. However, it may serve as the basis for much more flexible, application-specific leadership management.

durable.py

Correct implementations of the Paxos algorithm require saving Acceptor state to persistent media prior to sending Promise and Accepted messages over the network. This is necessary to ensure that promises made to external entities will never be reneged upon should the application crash and recover at an inopportune time. This module implements a very simple mechanism for efficiently saving application state to disk.