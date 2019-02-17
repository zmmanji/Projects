Group Members:
=======================

Zeeshaan Manji 301228629

Uzziah Eyee 301240256


-Note: In this Assignment we worked together and parallel coded through major parts of this assignment. We created 5 milestones which completed the assignment.

Work and Responsibilities:
==========================

The two group members Zeeshaan and Uzziah pair-coded the entire assignment, all logic, functions, and debugging were jointly done by the two developers. Consequently, no person was left to single-handedly implement any part.

Break down of solution:
========================

The entire solution was broken down into 4 modular units:

1. ARP Queue Handling:
	- We implemented a function called handle_arpreq() that periodically scans all the periodically scans the queue of packets waiting for an arp reply, then it resends an arp request if no reply is gotten for a specific period of time. This function also removes packets from the queue if a certain number of retries have been made.

2. IP Packet Handling:
	- We implemented the IP handling logic according to the pseudocode provided by the TA in class (which is too detailed to outline here). The summary however, is that this function gets called when an IP-type packet is received by the router: if the ip packet is an ICMP echo request to the router, it sends back an ICMP echo reply, however, if the IP packet is not destined for the router, it does some forwarding logic etc.

3. ARP Packet Handling:
	- handleArpPacket(...): This function is called when the router receives an ARP packet. If the ARP packet is a request directed to the router, an ARP reply is sent back, however if it is a response, then that response is queued in the router's arp cache...and any queued packets waiting on it are forwarded to the appropriate destination.

4. Utility Helper Functions:
	- createArpPacket(...): Creates and returns an ethernet frame that encapsulates an arp header. The details are passed in as function arguments.
	- isDestinedForRouter(...): returns true if a given ip address matches any of the router's interface IP address (else returns false)
	- createICMP3Packet(...): Creates and returns an icmp_t3 packet (i.e the icmp header type that carries a payload). Details like icmp_type and icmp_code, are passed in as arguments.
	- isValidLength(...) Checks if an ethernet header size matches the predifined size of the ethernet header struct.
	- send_host_unreachableICMP(...): sends an icmp "host-unreachable" message. The destination, source, and other details are passed in as arguments.

Known Bugs/Issues:
====================

-wget does not work completely: the intial connection is established but the ensuing file transfer doesn't terminate.
For example, the following mininet command will not work.
	mininet> client wget http://192.168.2.2

