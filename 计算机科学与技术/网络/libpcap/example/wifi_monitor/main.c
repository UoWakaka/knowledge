#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pcap/pcap.h>
#include <arpa/inet.h>

static inline const char *getdev()
{
    return "en0";
}

static void pack_handle(u_char *args, const struct pcap_pkthdr *pack_header, const u_char *pack_data)
{
    int *count = (int *)args;
    *count = *count + 1;

    printf("Count : %d\n", *count);
    printf("Packet length : %d\n", pack_header->len);
    printf("Number of bytes : %d\n", pack_header->caplen);
    printf("Received time : %s\n", ctime((const time_t *)&pack_header->ts.tv_sec));

    for (int i = 0; i < pack_header->caplen; i++)
    {
        if (i >= 16 * 4)
        {
            printf(" ...");
            break;
        }
        printf(" %02x", pack_data[i]);
        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
    }

    printf("\n\n");
}

int main(int argc, char **argv)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    const char *dev = getdev();

    int mode = 0;
    pcap_t *pcap_handle = NULL;

    if (mode == 1)
    {
        // 该方法无法设置监听模式
        pcap_handle = pcap_open_live(dev, 65535, 1, 0, errbuf);
        if (pcap_handle == NULL)
        {
            printf("failed to pcap_open_live: %s\n", errbuf);
            return 1;
        }
    }
    else
    {
        pcap_handle = pcap_create(dev, errbuf);
        if (pcap_handle == NULL)
        {
            printf("failed to pcap_create: %s\n", errbuf);
            return 1;
        }
        // 设置监听模式
        printf("pcap_set_rfmon: %d\n", pcap_set_rfmon(pcap_handle, 1));
        pcap_set_snaplen(pcap_handle, 65535); // 包缓存
        pcap_set_promisc(pcap_handle, 0); // 关闭混杂模式
        if (pcap_activate(pcap_handle) < 0)
        {
            printf("failed to pcap_activate: %s\n", pcap_geterr(pcap_handle));
        }
    }

    printf("success to open : %s\n", dev);
    if (pcap_set_datalink(pcap_handle, DLT_IEEE802_11_RADIO) == -1)
    {
        printf("couldn't set datalink type %s: %s\n", dev, pcap_geterr(pcap_handle));
    }

    int count = 0;
    if (pcap_loop(pcap_handle, 3, pack_handle, (u_char *)&count) < 0)
    {
        printf("failed to pcap_loop\n");
        return 1;
    }

    pcap_close(pcap_handle);
    return 0;
}