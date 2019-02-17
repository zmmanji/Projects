/**********************************************************************
 * file:  sr_router.c
 * date:  Mon Feb 18 12:50:42 PST 2002
 * Contact: casado@stanford.edu
 *
 * Description:
 *
 * This file contains all the functions that interact directly
 * with the routing table, as well as the main entry method
 * for routing.
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

#include "sr_if.h"
#include "sr_rt.h"
#include "sr_router.h"
#include "sr_protocol.h"
#include "sr_arpcache.h"
#include "sr_utils.h"

/*@todo: delete late*/
void printMyIp(uint32_t ip) {
  uint32_t curOctet = ip >> 24;
  fprintf(stderr, "%d.", curOctet);
  curOctet = (ip << 8) >> 24;
  fprintf(stderr, "%d.", curOctet);
  curOctet = (ip << 16) >> 24;
  fprintf(stderr, "%d.", curOctet);
  curOctet = (ip << 24) >> 24;
  fprintf(stderr, "%d\n", curOctet);
}

/* TODO: Add constant definitions here... */

/* TODO: Add helper functions here... */

/* See pseudo-code in sr_arpcache.h */

void send_host_unreachableICMP(struct sr_instance* sr,struct sr_packet * pkt){

 /* extract the ethernet header from the current packet */
 sr_ethernet_hdr_t* currentPacketEthernetHeader = (sr_ethernet_hdr_t *) (pkt->buf);

 /* extract the ip header from the current packet */
 sr_ip_hdr_t* currentPacketIPHeader = (sr_ip_hdr_t *) (pkt->buf + sizeof(sr_ethernet_hdr_t));
 
/*new ICMP header */
 sr_icmp_hdr_t * icmpHeader= malloc(sizeof(sr_icmp_hdr_t));
 icmpHeader->icmp_type=3;
 icmpHeader->icmp_code=0;
 icmpHeader->icmp_sum=0;

/* new IP HEADER */
 sr_ip_hdr_t * ipHeader= malloc(sizeof(sr_ip_hdr_t));
 ipHeader->ip_tos=htonl(0);
 ipHeader->ip_off=0;
 ipHeader->ip_p=1;
 ipHeader->ip_hl=4;
 ipHeader->ip_len=htons(sizeof(sr_ip_hdr_t)+sizeof(sr_icmp_t3_hdr_t));
 ipHeader->ip_v=4;
 ipHeader->ip_ttl=255;
 ipHeader->ip_src=sr_get_interface(sr, pkt->iface)->ip; /* will call sr_interface */
 ipHeader->ip_dst = currentPacketIPHeader->ip_src; 
 ipHeader->ip_sum=cksum(ipHeader,20); /* checksum of icmp header */


 /* new Ethernet header */
 sr_ethernet_hdr_t * ethernetHeader=malloc(sizeof(sr_ethernet_hdr_t));
 memcpy(ethernetHeader->ether_dhost, currentPacketEthernetHeader->ether_shost, ETHER_ADDR_LEN);
 memcpy(ethernetHeader->ether_shost, sr_get_interface(sr, pkt->iface)->addr, ETHER_ADDR_LEN);
 ethernetHeader->ether_type=ntohs(ethertype_ip);

 /* compose the entire ethernet frame to be sent: the frame is serialized as a buffer */ 
 int buffLen = sizeof(sr_ethernet_hdr_t) + sizeof(sr_ip_hdr_t) + sizeof(sr_icmp_hdr_t);
 uint8_t * ethernetFrame = calloc(buffLen,sizeof(uint8_t));

 /* 1. copy the ethernet header into the buff */
 memcpy(ethernetFrame, ethernetHeader, sizeof(sr_ethernet_hdr_t));
 memcpy(ethernetFrame + sizeof(sr_ethernet_hdr_t), ipHeader, sizeof(sr_ip_hdr_t));
 memcpy(ethernetFrame + sizeof(sr_ethernet_hdr_t) + sizeof(sr_icmp_hdr_t), icmpHeader, sizeof(sr_icmp_hdr_t));

 /* now send the complete ethernet frame */
 sr_send_packet(sr, ethernetFrame, buffLen, pkt->iface);
}



void handle_arpreq(struct sr_instance* sr, struct sr_arpreq *req){
	/*printf("\t>>>handle_arpreq() running...\n");*/

	time_t currentTime;
	time(&currentTime);

	if (difftime(currentTime, req->sent)>1){
		/*printf("\t\t>>One second since request was queued\n");*/

		if(req->times_sent>=5){
			/*printf("\t\t>>Request has been send too many times\t");*/

			struct sr_packet* packetlist = req->packets;
			while (packetlist!=NULL){
				
			     /* send icmp host unreachable for packet */
				send_host_unreachableICMP(sr, packetlist);
				packetlist = packetlist->next;
				
			}
			sr_arpreq_destroy(&(sr->cache),req);
		}
		else {
			/*printf("\t\t>>broadcast request\n");*/
            /*
            @summary: broadcast an arp request frame to every host connected to this router.
            The idea is to construct an arp packet and send it out every interface in this router.
            */

            /* arp_req = [<ethernet_header>|<arp_header>] */
            uint8_t* arp_req = calloc(sizeof(sr_ethernet_hdr_t) + sizeof(sr_arp_hdr_t), sizeof(uint8_t));
            sr_ethernet_hdr_t* req_eth_hdr = (sr_ethernet_hdr_t *) arp_req;
            sr_arp_hdr_t* req_arp_hdr = (sr_arp_hdr_t *) (arp_req + sizeof(sr_ethernet_hdr_t));

            /* 
            - identify this frame as an arp_request 
            - use ntohs if reading a packet (from the network) into the host, 
            - the data is not converted, it is not touched because it is meant for the application to decide, only the header will be converted.
            */
            /* use ntohs if writing a value into a packet that would be sent to the network */
            unsigned long bcastAddr = 0xFFFFFFFFFFFF;

            req_eth_hdr->ether_type = ntohs(ethertype_arp); /* why not htons(ethertype_arp) */
            memcpy(req_eth_hdr->ether_dhost, &bcastAddr, ETHER_ADDR_LEN);

            /* set fields in the arp_hdr portion of the arp_req */
            req_arp_hdr->ar_hrd = ntohs(arp_hrd_ethernet);
            req_arp_hdr->ar_pro = ntohs(ethertype_ip);
            req_arp_hdr->ar_hln = ETHER_ADDR_LEN;
            req_arp_hdr->ar_pln = 4;
            req_arp_hdr->ar_op = ntohs(arp_op_request);
            req_arp_hdr->ar_tip = req->ip;
            /* since this is an arp_req, the dst MAC addr is the broadcast addr FF:FF:FF:FF:FF:FF */
            memcpy(req_arp_hdr->ar_tha, &bcastAddr, ETHER_ADDR_LEN);

            /* broadcast the arp request: for each interface in the router, send the constructed frame */
            struct sr_if* sr_iface_list = sr->if_list;
            while (sr_iface_list != NULL) {
                /* the sender-MAC-addr of this frame's ethernet header = MAC Addr of this outgoing interface */
                memcpy(req_eth_hdr->ether_shost, sr_iface_list->addr, ETHER_ADDR_LEN);
                /* the sender-hardware-addr of this frame's arp header = MAC Addr of this outgoing interface */
                memcpy(req_arp_hdr->ar_sha, sr_iface_list->addr, ETHER_ADDR_LEN);
                /* the sender-ip-addr of this frame's arp header = IP Addr of this outgoing interface */
                req_arp_hdr->ar_sip = sr_iface_list->ip;
                /* now send the frame out the interface */
                sr_send_packet(sr, arp_req, sizeof(sr_ethernet_hdr_t) + sizeof(sr_arp_hdr_t), sr_iface_list->name);
                /*printf("=========== BROADCASTING ARP REQ TO INTERFACE (%s) ===========\n", sr_iface_list->name);*/
                /*print_hdrs(arp_req, sizeof(sr_ethernet_hdr_t) + sizeof(sr_arp_hdr_t));*/
                sr_iface_list = sr_iface_list->next;
            }

            /* update request statistics */
			req->sent=currentTime;
			req->times_sent++;
			
		}
	}
}

/*---------------------------------------------------------------------
 * Method: sr_init(void)
 * Scope:  Global
 *
 * Initialize the routing subsystem
 *
 *---------------------------------------------------------------------*/

void sr_init(struct sr_instance* sr)
{
    /* REQUIRES */
    assert(sr);

    /* Initialize cache and cache cleanup thread */
    sr_arpcache_init(&(sr->cache));

    pthread_attr_init(&(sr->attr));
    pthread_attr_setdetachstate(&(sr->attr), PTHREAD_CREATE_JOINABLE);
    pthread_attr_setscope(&(sr->attr), PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&(sr->attr), PTHREAD_SCOPE_SYSTEM);
    pthread_t thread;

    pthread_create(&thread, &(sr->attr), sr_arpcache_timeout, sr);
    
    /* TODO: (opt) Add initialization code here */

} /* -- sr_init -- */

/*---------------------------------------------------------------------
 * Method: sr_handlepacket(uint8_t* p,char* interface)
 * Scope:  Global
 *
 * This method is called each time the router receives a packet on the
 * interface.  The packet buffer, the packet length and the receiving
 * interface are passed in as parameters. The packet is complete with
 * ethernet headers.
 *
 * Note: Both the packet buffer and the character's memory are handled
 * by sr_vns_comm.c that means do NOT free either (signified by "lent" comment).  
 * Make a copy of the
 * packet instead if you intend to keep it around beyond the scope of
 * the method call.
 *
 *---------------------------------------------------------------------*/

/* Check the packet length  SANITY CHECK*/ 

bool isValidLength(uint8_t* packet, unsigned int len){
    /*sr_ethernet_hdr_t * ethernetHeader= (sr_ethernet_hdr_t *)packet*/
    bool result=true;
    if (len< sizeof(sr_ethernet_hdr_t)){
	result=false;
	
    }
    return result;
    
}

/* Create a new Arp Packet */
uint8_t * createArpPacket(unsigned short arp_op, unsigned char* ar_sha, uint32_t ar_sip, unsigned char* ar_tha, uint32_t ar_tip){       
	/* Create The Packet */
	uint8_t * packet = malloc(sizeof(sr_arp_hdr_t)+ sizeof(sr_ethernet_hdr_t)); 
	
	/* Create the Ethernet Header */
	sr_ethernet_hdr_t * ethernetHeader = (sr_ethernet_hdr_t *)(packet);
	ethernetHeader->ether_type = htons(ethertype_arp);
	memcpy(ethernetHeader->ether_dhost, ar_tha, ETHER_ADDR_LEN);
    memcpy(ethernetHeader->ether_shost, ar_sha, ETHER_ADDR_LEN);
	
	/* Create ARP Header */
	
	sr_arp_hdr_t * arpHeader= (sr_arp_hdr_t *)(packet +sizeof(sr_ethernet_hdr_t));
	arpHeader->ar_hrd = htons(arp_hrd_ethernet);
	arpHeader->ar_pro = htons(ethertype_ip);
	arpHeader->ar_hln = ETHER_ADDR_LEN;
	arpHeader->ar_pln = 4;
	arpHeader->ar_op = htons(arp_op);
	arpHeader->ar_sip = ar_sip;
	arpHeader->ar_tip = ar_tip;
	memcpy(arpHeader->ar_sha, ar_sha, ETHER_ADDR_LEN);
	memcpy(arpHeader->ar_tha, ar_sha, ETHER_ADDR_LEN);

	/*  After Inserting all the Values Return the Packet */
	return packet;
	
}

/*Handle ARP Packet */

void handleArpPacket(struct sr_instance* sr, sr_arp_hdr_t * arpHeader, unsigned int hdrLen, struct sr_if* iface){
	/*printf(">>>handleArpPacket() running...\n");*/

	/* Checking if it's a Request or Reply 1 for REQUEST AND 2 FOR REPLY*/
	/*If ARP is Request */
	if(arpHeader->ar_op == htons(arp_op_request)){ 
		/*printf("\t>>>ARP packet is a Request\n");*/
		/* If Destination is Router */
		if( arpHeader->ar_tip== iface->ip){ 
			/*printf("\t\t>>>ARP request is destined for router: creating and sending ARP reply...\n");*/
			uint8_t* arpReplyFrame = createArpPacket(arp_op_reply, iface->addr, arpHeader->ar_tip, arpHeader->ar_sha, arpHeader->ar_sip);      
			sr_send_packet(sr, arpReplyFrame, sizeof(sr_ethernet_hdr_t) + sizeof(sr_arp_hdr_t), iface->name);
			/*print_hdrs(arpReplyFrame, sizeof(sr_ethernet_hdr_t) + sizeof(sr_arp_hdr_t));*/
			free(arpReplyFrame);			
		}
		else{
			/*fprintf(stderr, "\t\t>>>ARP Request Packet Discarded because not destined for Router ");*/
		}	
	}
	/*If ARP is Reply */
	else if (arpHeader->ar_op==htons(2)) {
		/*printf("\t>>>ARP packet is a Reply\n");*/
		struct sr_arpreq * newArpEntryRequest= sr_arpcache_insert(&sr->cache, arpHeader->ar_sha, arpHeader->ar_sip);
		/* If they are pending packets */
		if (newArpEntryRequest!=NULL){
			/*printf("\t\t>>>There are packets waiting for this reply: modifying eth headers and sending packets\n");*/
			struct sr_packet * PacketList= newArpEntryRequest->packets;
			while ( PacketList!=NULL) {
				sr_ethernet_hdr_t * packetEthHeader = (sr_ethernet_hdr_t *) PacketList->buf;
				memcpy(packetEthHeader->ether_shost, arpHeader->ar_tha, ETHER_ADDR_LEN);
				memcpy(packetEthHeader->ether_dhost, arpHeader->ar_sha, ETHER_ADDR_LEN);
				sr_send_packet(sr, PacketList->buf, PacketList->len, iface->name);
				PacketList=PacketList->next;
			}
		} else {
			/*fprintf(stderr, "\t\t>>>No Packets Queued for Newly discovered host\n");*/
		}
		
	}
	else{
		/*fprintf(stderr, "\t>>>ARP PACKET DISCARDED DUE TO UNKNOWN OP_CODE\n");*/
	}



}

bool isDestinedForRouter(struct sr_instance* router, sr_ip_hdr_t* frameIpHeader) {
	bool result = false;
	struct sr_if* iface_list = router->if_list; /* not sure */
	/* check all router interfaces to see if any matches the ip */
	while (iface_list != NULL) {
		if (iface_list->ip == frameIpHeader->ip_dst) {
			result = true;
			break;
		}
		iface_list = iface_list->next;
	}
	return result;
}

/*
uint8_t* createICMPpacket(uint8_t icmp_type, uint8_t icmp_code) {

	int frameLen = sizeof(sr_ethernet_hdr_t) + sizeof(sr_ip_hdr_t) + sizeof(sr_icmp_hdr_t);
	uint8_t* frame = calloc(frameLen, sizeof(uint8_t));

	sr_icmp_hdr_t* icmpHdr = (sr_icmp_hdr_t *) frame + sizeof(sr_ethernet_hdr_t) + sizeof(sr_ip_hdr_t);
	icmpHdr->icmp_type = htons(icmp_type);
	icmpHdr->icmp_code = htons(icmp_code);
	icmpHdr->icmp_sum = cksum(icmpHdr, sizeof(sr_icmp_hdr_t));
	
	return frame;
}
*/

uint8_t* createICMP3Packet(unsigned char* src_mac, unsigned char* dst_mac, uint32_t src_ip, uint32_t dst_ip, uint8_t icmp_type, uint8_t icmp_code, uint8_t* payload) {
	/* @todo: construct and return a frame containing an icmp type 3 packet */
	
	/* memory allocation for headers */
	int len_eth = sizeof(sr_ethernet_hdr_t);
	int len_ip = sizeof(sr_ip_hdr_t);
	int len_icmp = sizeof(sr_icmp_t3_hdr_t);
	uint8_t* frame = calloc(len_eth + len_ip + len_icmp, sizeof(uint8_t));
	sr_ethernet_hdr_t* ethHeader = (sr_ethernet_hdr_t *) frame;
	sr_ip_hdr_t* ipHeader = (sr_ip_hdr_t *) (frame + len_eth);
	sr_icmp_t3_hdr_t* icmpHeader = (sr_icmp_t3_hdr_t *) (frame + len_eth + len_ip);

	/* setup ethernet header */
	memcpy(ethHeader->ether_shost, src_mac, ETHER_ADDR_LEN);
	memcpy(ethHeader->ether_dhost, dst_mac, ETHER_ADDR_LEN);
	ethHeader->ether_type = htons(ethertype_ip);

	/* setup ip header */
	ipHeader->ip_v = 4;
	ipHeader->ip_hl = 5;
	ipHeader->ip_tos = 0;
	ipHeader->ip_len = htons(len_ip + len_icmp);
	ipHeader->ip_id = htons(0);
	ipHeader->ip_off = htons(0);
	ipHeader->ip_ttl = 64;
	ipHeader->ip_p = 1;
	ipHeader->ip_sum = 0;
	ipHeader->ip_src = src_ip; 
	ipHeader->ip_dst = dst_ip;
	ipHeader->ip_sum = cksum(ipHeader,20);

	/* setup icmp header */
	icmpHeader->icmp_type = icmp_type;
	icmpHeader->icmp_code = icmp_code;
	icmpHeader->icmp_sum = 0;
	icmpHeader->unused = 0;
	icmpHeader->next_mtu = htons(1500);
	memcpy(icmpHeader->data, payload + len_eth, ICMP_DATA_SIZE);
	icmpHeader->icmp_sum = cksum(icmpHeader, len_icmp);

	return frame;
}

/* this function handles IP packets */

void handleIpPacket(struct sr_instance* sr, uint8_t* frame, uint8_t frameLen, struct sr_if* interface) {

	/*printf("\t>>>handleIpPacket() running...\n");*/

	struct sr_ethernet_hdr* ethernetHeader = (sr_ethernet_hdr_t *) frame;
	struct sr_ip_hdr* ipHeader = (sr_ip_hdr_t *) (frame + sizeof(sr_ethernet_hdr_t));

	/*printf("\t\t>>>performing sanity checks...\n");*/
	/* sanity check on the ethernet header */
	uint16_t chksum = ipHeader->ip_sum;
	ipHeader->ip_sum = 0;
	if (chksum != cksum((uint8_t*) frame + sizeof(sr_ethernet_hdr_t), 20)) {
		/*printf("\t\t>>packet is invalid: checksum failure, dropped packet\n");*/
		return;
	}
	
	/* if frame contains an icmp packet and destined for router */
	if (ipHeader->ip_p == htons(ip_protocol_icmp) && isDestinedForRouter(sr, ipHeader)) {
		/*printf("\t\t\t>>>frame contains an icmp packet and it is destined for router\n");*/

		struct sr_icmp_hdr* icmpHeader = (struct sr_icmp_hdr*) frame + sizeof(sr_ethernet_hdr_t) + sizeof(sr_ip_hdr_t);
		
		/* handle only icmp request-type packets */
		if (icmpHeader->icmp_type == htons(1)) {
			/*printf("\t\t\t>>>frame is an ICMP request frame\n");*/

			/* check if ttl of packet is still valid */
			if (ipHeader->ip_ttl <= htons(0)) { /* packet has expired */
				/*printf("\t\t\t>>>frame has expired: ttl = 0\n");*/

				/* get icmp portion of frame and modify it to work as an icmp_reply header */
				sr_icmp_hdr_t* icmpHdr = (sr_icmp_hdr_t *) frame + sizeof(sr_ethernet_hdr_t) + sizeof(sr_ip_hdr_t);
				icmpHdr->icmp_type = htons(11);
				icmpHdr->icmp_code = htons(0); /* not sure */
				icmpHdr->icmp_sum = htons(0);
				icmpHdr->icmp_sum = cksum(icmpHdr, sizeof(sr_icmp_hdr_t));

				/* modify ip hdr portion of frame */
				uint32_t temp = ipHeader->ip_src;
				ipHeader->ip_src = interface->ip;
				ipHeader->ip_dst = temp;

				/* modify ethernet header part of the frame: swap src & dst MAC addresses */
				uint8_t tmpAddr[ETHER_ADDR_LEN];
				memcpy(tmpAddr, ethernetHeader->ether_shost, ETHER_ADDR_LEN);
				memcpy(ethernetHeader->ether_shost, ethernetHeader->ether_dhost, ETHER_ADDR_LEN);
				memcpy(ethernetHeader->ether_dhost, tmpAddr, ETHER_ADDR_LEN);

				/* send the packet */
				sr_send_packet(sr, frame, frameLen, interface->name);
				
			} else { /* packet is not expired */
				/*printf("\t\t\t>>>frame is still alive: ttl is > 0\n");*/

				/* get icmp portion of frame and modify it to work as an icmp_reply header */
				sr_icmp_hdr_t* icmpHdr = (sr_icmp_hdr_t *) frame + sizeof(sr_ethernet_hdr_t) + sizeof(sr_ip_hdr_t);
				icmpHdr->icmp_type = htons(0);
				icmpHdr->icmp_code = htons(0); /* not sure */
				icmpHdr->icmp_sum = htons(0);
				icmpHdr->icmp_sum = cksum(icmpHdr, sizeof(sr_icmp_hdr_t));

				/* modify ip hdr portion of frame */
				uint32_t temp = ipHeader->ip_src;
				ipHeader->ip_src = interface->ip;
				ipHeader->ip_dst = temp;

				/* modify ethernet header part of the frame: swap src & dst MAC addresses */
				uint8_t tmpAddr[ETHER_ADDR_LEN];
				memcpy(tmpAddr, ethernetHeader->ether_shost, ETHER_ADDR_LEN);
				memcpy(ethernetHeader->ether_shost, ethernetHeader->ether_dhost, ETHER_ADDR_LEN);
				memcpy(ethernetHeader->ether_dhost, tmpAddr, ETHER_ADDR_LEN);

				/* send the packet */
				sr_send_packet(sr, frame, frameLen, interface->name);
			}
		} else {
			/*fprintf(stderr, "\t\t\t>>>Discarded ICMP packet because router does not handle any other types");*/
		}
	} else {
		/*printf("\t\t>>>Frame does not contain an ICMP packet OR packet is not destined for router\n");*/
		/* search the routing table for a suitable interface to be used for sending this packet.
		We do this by iterating over every entry in the routing table, and for each entry, we apply
		the longest-matching-prefix algorithm to determine the interface to be used. */
		
		char* sendingIfaceName = NULL;
		int prefixLength = 0;
		struct sr_rt* routingTable = sr->routing_table;

		/*print_hdr_ip(frame+sizeof(sr_ethernet_hdr_t));*/
		/*printf("***===***\n");*/	
		/*printMyIp(ipHeader->ip_dst);*/

		/* @todo: understand this codeblock to the bit-level, for now it is a blackbox. */
		while (routingTable != NULL)
		{
			
			if((routingTable->mask.s_addr & ipHeader->ip_dst) == (routingTable->mask.s_addr & routingTable->dest.s_addr)) {       
				long currentMask = routingTable->mask.s_addr;

				unsigned int i;
				for (i = 0; currentMask; i++) {
					currentMask &=  currentMask - 1;
				}

				if (i > prefixLength) {
					sendingIfaceName = routingTable->interface;
					prefixLength = i;
				}
			}

			routingTable = routingTable->next;
		}

		/* if we failed, i.e, we could not find a match in the routing table */
		if (sendingIfaceName == NULL) {
			/* create a frame containing an ICMP type=3 payload */
			/* @question: why are we not using the receiving interface's mac addr as src_mac for the icmp3Frame? */
			uint8_t* icmp3Frame = createICMP3Packet(interface->addr, ethernetHeader->ether_shost, interface->ip, ipHeader->ip_src, 3, 0, frame);
			/*print_hdrs(icmp3Frame, sizeof(sr_ethernet_hdr_t) + sizeof(sr_ip_hdr_t) + sizeof(sr_icmp_t3_hdr_t));*/
			/* send the icmp frame to the host who sent us the packet, i.e, send the packet via the interface it came from */
			sr_send_packet(sr, icmp3Frame, sizeof(sr_ethernet_hdr_t) + sizeof(sr_ip_hdr_t) + sizeof(sr_icmp_t3_hdr_t), interface->name);       
		} else {
			/* if we could find a matching interface, send the packet throught that interface */
			struct sr_if* sendingIface = sr_get_interface(sr, sendingIfaceName);
			
			/* update the packet's ttl and checksum */
			 /* consider using a more dynamic value instead of 20 */
			
			/* But wait! If ttl becomes 0, then the packet has expired, so we should not forward it */
			if ((ipHeader->ip_ttl - 1) == 0) {
				/* create a frame containing an icmp type=11 packet, then send it through the expired packet's 
					receiving interface to notify the sending host */
				uint8_t* ttlIcmpFrame = createICMP3Packet(interface->addr, ethernetHeader->ether_shost, interface->ip, ipHeader->ip_src, 11, 0, frame);
				sr_send_packet(sr, ttlIcmpFrame, sizeof(sr_ethernet_hdr_t) + sizeof(sr_ip_hdr_t) + sizeof(sr_icmp_t3_hdr_t), interface->name);       
		
			} else {
				ipHeader->ip_ttl -= 1;
				ipHeader->ip_sum = cksum(ipHeader, 20);

				/* the packet is still valid (i.e not expired): send it through the appropriate interface we 
					found in the routing table */
				
				/* now we need to find the mac addr of the next-hop*/
				
				/* get the ip addr of the interface from which this packet was received */
				uint32_t rcvIP = ntohl(interface->ip);
				/* find the MAC addr corresponding to that ip in the arp-cache table */
				struct sr_arpentry* arpEntry = sr_arpcache_lookup(&sr->cache, rcvIP);
				
				/* if the arp cache contains an entry for the packet's dst ip, 
					then update the packet's ethernet header dst MAC addr with the next hop MAC addr in the arp entry */
				if (arpEntry != NULL) {
					memcpy(ethernetHeader->ether_dhost, arpEntry->mac, ETHER_ADDR_LEN);					
					memcpy(ethernetHeader->ether_shost, sendingIface->addr, ETHER_ADDR_LEN);
					sr_send_packet(sr, frame, frameLen, sendingIface->name);
					free(arpEntry);
				} else {
					/* we could not find the next-hop mac addr, so, queue the packet and broadcast an arp request */
					struct sr_arpreq* arpReq = sr_arpcache_queuereq(&(sr->cache), ipHeader->ip_dst, frame, frameLen, sendingIface->name);
					handle_arpreq(sr, arpReq);
				}
			} 
		}
		
	}
}



void sr_handlepacket(struct sr_instance* sr,
    uint8_t * packet/* lent */,
    unsigned int len,
    char* interface/* lent */){

	/* REQUIRES */
	assert(sr);
	assert(packet);
	assert(interface);

		
	/* fill in code here */
    /*print_hdrs(packet, len);*/

    sr_ethernet_hdr_t* ethernetHeader = (sr_ethernet_hdr_t*) packet;
    if(len < sizeof(sr_ethernet_hdr_t)) {
		return;
	}

    struct sr_if* newInterface = sr_get_interface(sr, interface);

	/* if frame contains an ARP packet */
    if(ethertype(packet) == ethertype_arp) {
		handleArpPacket(sr, (sr_arp_hdr_t* )(packet+sizeof(sr_ethernet_hdr_t)), len-sizeof(sr_ethernet_hdr_t), newInterface);
    }
	/* if frame contains an IP Packet */
    else if(ethertype(packet) == ethertype_ip) {
		
		/* check if the dst mac addr of the frame is same as mac addr of receiving interface.
			if it is, then frame is destined for router, else, it is not. */
        
        const uint8_t * destinationMAC = ethernetHeader->ether_dhost; 
        const uint8_t * myMAC= newInterface->addr;

		bool destIsRouter = true;
		int i=0;
        while(i != ETHER_ADDR_LEN) {
            if (*destinationMAC != *myMAC) {
                destIsRouter = false;
                break;
            }
            ++destinationMAC;
            ++myMAC;
            i++;
        }

		/* if frame is destined for us */
        if(destIsRouter) {
			handleIpPacket(sr, packet, len, newInterface);
        } else {
        }
    }
    else {
    }
}/* -- sr_handlepacket -- */
