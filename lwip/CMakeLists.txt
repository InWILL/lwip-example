cmake_minimum_required(VERSION 3.10)

project(lwip)

set(LWIP_DIR ${PROJECT_SOURCE_DIR})

# The minimum set of files needed for lwIP.
set(lwipcore_SRCS
    ${LWIP_DIR}/core/init.c
    ${LWIP_DIR}/core/def.c
    # ${LWIP_DIR}/core/dns.c
    ${LWIP_DIR}/core/inet_chksum.c
    ${LWIP_DIR}/core/ip.c
    ${LWIP_DIR}/core/mem.c
    ${LWIP_DIR}/core/memp.c
    ${LWIP_DIR}/core/netif.c
    ${LWIP_DIR}/core/pbuf.c
    ${LWIP_DIR}/core/raw.c
    # ${LWIP_DIR}/core/stats.c
    # ${LWIP_DIR}/core/sys.c
    # ${LWIP_DIR}/core/altcp.c
    # ${LWIP_DIR}/core/altcp_alloc.c
    # ${LWIP_DIR}/core/altcp_tcp.c
    ${LWIP_DIR}/core/tcp.c
    ${LWIP_DIR}/core/tcp_in.c
    ${LWIP_DIR}/core/tcp_out.c
    ${LWIP_DIR}/core/timeouts.c
    ${LWIP_DIR}/core/udp.c
)
set(lwipcore4_SRCS
    # ${LWIP_DIR}/core/ipv4/autoip.c
    # ${LWIP_DIR}/core/ipv4/dhcp.c
    # ${LWIP_DIR}/core/ipv4/etharp.c
    ${LWIP_DIR}/core/ipv4/icmp.c
    # ${LWIP_DIR}/core/ipv4/igmp.c
    ${LWIP_DIR}/core/ipv4/ip4_frag.c
    ${LWIP_DIR}/core/ipv4/ip4.c
    ${LWIP_DIR}/core/ipv4/ip4_addr.c
)
set(lwipcore6_SRCS
    # ${LWIP_DIR}/core/ipv6/dhcp6.c
    # ${LWIP_DIR}/core/ipv6/ethip6.c
    ${LWIP_DIR}/core/ipv6/icmp6.c
    # ${LWIP_DIR}/core/ipv6/inet6.c
    ${LWIP_DIR}/core/ipv6/ip6.c
    ${LWIP_DIR}/core/ipv6/ip6_addr.c
    ${LWIP_DIR}/core/ipv6/ip6_frag.c
    # ${LWIP_DIR}/core/ipv6/mld6.c
    ${LWIP_DIR}/core/ipv6/nd6.c
)
set(lwipapi_SRCS
    ${LWIP_DIR}/api/api_lib.c 
    ${LWIP_DIR}/api/api_msg.c 
    ${LWIP_DIR}/api/err.c 
    ${LWIP_DIR}/api/if_api.c 
    ${LWIP_DIR}/api/netbuf.c 
    ${LWIP_DIR}/api/netdb.c 
    ${LWIP_DIR}/api/netifapi.c 
    ${LWIP_DIR}/api/sockets.c 
    ${LWIP_DIR}/api/tcpip.c
)

set(lwipcustom_SRCS
    ${LWIP_DIR}/custom/sys_arch.c
)

set (LWIP_INCLUDE_DIRS
    ${LWIP_DIR}/include
    ${LWIP_DIR}/custom
)

# All LWIP files without apps
set(lwipnoapps_SRCS
    ${lwipcore_SRCS}
    ${lwipcore4_SRCS}
    ${lwipcore6_SRCS}
    ${lwipapi_SRCS}
    ${lwipcustom_SRCS}
)

# lwIP libraries
add_library(lwipcore STATIC ${lwipnoapps_SRCS})
target_include_directories(lwipcore PUBLIC ${LWIP_INCLUDE_DIRS})
