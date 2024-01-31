def frecvente(string):
    d = {}
    for c in string:
        if c not in d:
            d[c] = string.count(c)
    return d

class Node:
    def __init__(self, left = None, right = None):
        self.left = left
        self.right = right

    def children(self):
        return (self.left, self.right)

    def nodes(self):
        return (self.left, self.right)

def tree(frecv):
    nodes = frecv
    while len(nodes) > 1:
        (key1, c1) = nodes[-1]
        (key2, c2) = nodes[-2]
        nodes = nodes[:-2]
        node = Node(key1, key2)
        nodes.append((node, c1 + c2))
        nodes = sorted(nodes, key=lambda x: x[1], reverse=True)

    return nodes

def huffman_code_tree(node, left=True, emptyString=''):
    if type(node) is str:
        return {node: emptyString}
    (l, r) = node.children()
    d = dict()
    d.update(huffman_code_tree(l, True, emptyString + '1'))
    d.update(huffman_code_tree(r, False, emptyString + '0'))

    return d

def codificare(huffmanCode, string):
    stringCodificat = ""
    for c in string:
        stringCodificat = stringCodificat + huffmanCode[c]

    return stringCodificat

def decodificare(huff, cod):
    string = ""

    while cod:
        c = cod[0]
        cod = cod[1:]
        while c not in huff:
            c = c + cod[0]
            cod = cod[1:]
        string = string + huff[c]

    return string

#
# main entry
#
f = open("huffman.in")
# g = open("shakespeare_out.txt", "w")
string = f.read()
frecv = frecvente(string)

# ordonam caractere descrescator dupa frecventa
frecv = sorted(frecv.items(), key = lambda item: item[1], reverse = True)

nodes = tree(frecv)
huffmanCode = huffman_code_tree(nodes[0][0])
# g.write(codificare(huffmanCode, string))
cod = codificare(huffmanCode, string)

huffmanCodeInvers = {v: k for k, v in huffmanCode.items()}
string = decodificare(huffmanCodeInvers, cod)
print(string)

# g.close()
f.close()


