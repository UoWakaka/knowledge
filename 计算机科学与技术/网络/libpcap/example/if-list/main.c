#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pcap/pcap.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_if_t *it;
  int r;

  r = pcap_findalldevs(&it, errbuf);
  if (r == -1)
  {
    printf("err:%s\n", errbuf);
    exit(-1);
  }

  while (it)
  {
    printf(":%s\n", it->name);
    it = it->next;
  }
}