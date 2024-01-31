import socket


class Subnet:

    def __init__(self, subnet: str, dims: list):
        subnet = subnet.split("/")
        self.ip = subnet[0]
        self.cidr = int(subnet[1])
        self.dims = []
        for i in range(len(dims)):
            self.dims.append((dims[i], i + 1))
        self.dims.sort(key=lambda dim: dim[0], reverse=True)

    def requiredBits(self, dim):
        allowed = 32 - self.cidr
        for p in range(0, allowed):
            if 2 ** p >= dim + 3:
                return 2 ** p
        return None

    def subnetMask(self, dim):
        bits = int(''.join(['0'] * 32), 2)
        max_bits = int(''.join(['1'] * 32), 2)
        required = self.requiredBits(dim) - 1
        if required is None:
            return None
        return format(max_bits - (bits | required), '08b')

    @staticmethod
    def computeBroadcast(a, b):
        res = ""
        for i in range(32):
            res += str(int(a[i]) | (int(b[i]) ^ 1))
        return res

    def calculateCIDR(self, broadcast):
        diff = broadcast[self.cidr:32]
        return 32 - diff.count('1')

    @staticmethod
    def ipToBin(ip: str):
        ip_bytes = socket.inet_aton(ip)
        ip_bin = ""
        for i in range(4):
            ip_bin += format(ip_bytes[i], '08b')
        return ip_bin

    @staticmethod
    def binToIp(ip_bin: str):
        b = bytearray()
        for i in range(0, 32, 8):
            b.append(int(ip_bin[i:i + 8], 2))
        return bytes(b)

    def partition(self):
        if self.cidr == 0:
            return None
        ip_bin = self.ipToBin(self.ip)
        lans = dict()
        last_assigned = ''.join(['0'] * self.cidr)
        for dim in self.dims:
            # Get subnet mask
            sm = self.subnetMask(dim[0])
            if sm is None:
                return None
            # Compute broadcast
            broadcast = self.computeBroadcast(ip_bin, sm)
            broadcast_unassigned = broadcast[:self.cidr] + last_assigned
            # Save last assigned
            last_assigned = format(int(last_assigned, 2) + int(broadcast[self.cidr:], 2) + 1, '08b')
            # Check if there is enough space in address
            if int(last_assigned, 2) > 2 ** (32 - self.cidr):
                return None
            # Save lan
            lans[
                f"LAN{dim[1]}"] = f"{socket.inet_ntoa(self.binToIp(broadcast_unassigned))}/{self.calculateCIDR(broadcast)}"
        return lans
