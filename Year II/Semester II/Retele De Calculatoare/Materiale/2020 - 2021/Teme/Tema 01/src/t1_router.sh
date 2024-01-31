#!/bin/bash

# we need to drop the kernel reset of hand-coded tcp connections
# https://stackoverflow.com/a/8578541
# and redirect incoming traffic
# https://my.esecuredata.com/index.php?/knowledgebase/article/49/how-to-redirect-an-incoming-connection-to-a-different-ip-address-on-a-specific-port-using-iptables/
iptables -A OUTPUT -p tcp --tcp-flags RST RST -j DROP && \
iptables -t nat -A POSTROUTING -j MASQUERADE 


tc qdisc add dev eth0 root netem delay 100ms 10ms 25% loss 5% 25% corrupt 10% reorder 25% 50% && \

echo "restrictions have been set on eth0: " && \
tc qdisc show dev eth0 && \
echo "restrictions have been set on eth1: " && \
tc qdisc show dev eth1 && \

sleep infinity

#remove restrictions with
# tc qdisc del dev eth0 root || tc qdisc del dev eth1 root
#
