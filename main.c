#include <lwip/sockets.h>
#include <lwip/tcpip.h>

static int tunFd;

err_t output(struct netif *netif, struct pbuf *p, const ip4_addr_t *ipaddr) 
{
	char buf[1500];
	u16_t bufLen = pbuf_copy_partial(p, buf, p->tot_len, 0);
	(void)(write(tunFd, buf, bufLen) + 1);
	return ERR_OK;
}

int mylwip_init() {
	tcpip_init(NULL, NULL);
	netif_list->mtu = 1500;
	netif_list->output = output;
	int tcp_sock = lwip_socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = lwip_htons(80);
	lwip_inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	lwip_bind(tcp_sock, (struct sockaddr *)&addr, sizeof(addr));
	lwip_listen(tcp_sock, 512);
	return tcp_sock;
}
void tcp_thread(void *arg) {
	struct sockaddr_in addr, _addr;
	socklen_t socklen = sizeof(struct sockaddr_in);
	int connFd = lwip_accept(*(int *)arg, (struct sockaddr *)&addr, &socklen);

	char buffer[1024];
	int len = lwip_recv(connFd, buffer, sizeof(buffer), 0);
		printf("%s", buffer);
}

int main()
{
	int tcp_sock = mylwip_init();
	sys_thread_new(
		"tcp", 
		(void *)&tcp_thread, 
		&tcp_sock,
		DEFAULT_THREAD_STACKSIZE, 
		DEFAULT_THREAD_PRIO
	);

	int client = lwip_socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = lwip_htons(80);
	lwip_inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	lwip_connect(client, (struct sockaddr *)&addr, sizeof(addr));
	char *buffer = "Hello";
	lwip_send(client, buffer, sizeof(buffer), 0);
	return 0;
}