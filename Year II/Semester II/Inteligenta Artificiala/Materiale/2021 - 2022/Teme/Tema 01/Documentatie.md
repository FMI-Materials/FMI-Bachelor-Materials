# Documentatie

Mod de utilizare:
```
usage: main.py -i/--folder-in FILE_PATH -o/--folder-out FILE_PATH -n/--nsol INT-t/--timeout INT

optional arguments:
  -h, --help            show this help message and exit
  -i FIN, --folder-in FIN
                        Folder fisiere de input
  -o FOUT, --folder-out FOUT
                        Folder fisiere de output
  -n NSOL, --nsol NSOL  primele NSOL soluții returnate de fiecare algoritm
  -t TIMEOUT, --timeout TIMEOUT
                        Timeout algoritmi (ms)
```

Exemplu de utilizare:

```
python3 main.py -i input -o output -n 5 -t 2000
```

## Euristici folosite:

### Banală:
Euristica banală returnează distanța euclidiană până la mal

```
remaining_distance = calculate_distance((self.radius, 0)) - calculate_distance(node_info.pos)
return remaining_distance
```

### Admisibilă 1:

Pentru primul tip de euristică vom calcula greutatea maximă pe care Mormocel o poate avea, 
respectiv minimul dintre greutatea maximă susținută de frunze și numărul total de insecte de pe lac.

```
total_add_weight = sum([node.insects for node in self.nodes])
max_valid_weight = max([node.max_weight for node in self.nodes])
max_weight = min(max_valid_weight, total_add_weight)
```

După asta vom crea o funcție de generare a nodurilor pe care Mormocel poate sări dintr-o frunză de start,
ținând cont că el poate sări o distanță maximă de max_weight / 3.

```
def get_next_nodes(start_node: Node, max_jump: float):
    current_dist = calculate_distance(start_node.pos)
    next_nodes = []
    for node in self.nodes:
        dist = calculate_distance(node.pos)
        dist_diff = calculate_distance(node.pos, start_node.pos)
        if dist_diff <= max_jump and dist > current_dist:
            next_nodes.append((node, dist_diff))
    return next_nodes
```

Mai apoi, vom porni din nodul curent și cu ajurotul algoritmului bfs, vom genera toate drumurile posibile (folosind funcția de generare declarată anterior),
până când vom ajunge într-o stare finală.

```
def bfs(start_node: Node, max_weight: float):
    nodes_list = [(start_node, 0)]
    while len(nodes_list) > 0:
        current_node = nodes_list.pop(0)
        if self.test_scope(State(current_node[0], max_weight, 0)):
            return current_node[1]
        next_nodes = get_next_nodes(current_node[0], max_weight / 3)
        for node in next_nodes:
            if node not in nodes_list:
                nodes_list.append((node[0], node[1] + current_node[1]))
    return sys.maxsize

return bfs(node_info.node, max_weight)
```

Astfel maximizând distanța parcursă de Mormocel între frunze, minimizăm numărul de frunze parcurse și distanța finală până la mal.

### Admisibilă 2:

Asemănător cu prima admisibilă, pentru a doua admisibilă am simulat și scăderea în greutate a lui Mormocel astfel:

Calculăm numărul maxim de insecte pe care Mormocel le poate mânca de pe o frunză și greutatea maximă suportată de frunze.

```
max_add_weight = max([node.insects for node in self.nodes])
max_valid_weight = max([node.max_weight for node in self.nodes])
available_weight = node_info.weight
```

Pornim de la greutatea din starea curentă, iar pentru fiecare săritură vom modifica greutatea după cum urmează:

```
available_weight = min(available_weight + max_add_weight - 1, max_valid_weight)
```

Ținând cont că după fiecare săritură Mormocel mănâncă un număr maxim de insecte, distanța până la mal este mereu minimizată.

### Neadmisibilă:

Euristica neadmisibilă adună distanța dintre toate nodurile mai apropiate de mal decât nodul curent.
Astfel este creat un drum din nodul curent până la mal, ce trece prin toate celelalte frunze.

```
h = calculate_distance(self.start.pos, self.nodes[0].pos)
for i in range(1, len(self.nodes)):
    if self.nodes[i].id != self.start.node.id and remaining_distance < calculate_distance(
            (self.radius, 0)) - calculate_distance(self.nodes[i].pos):
        h += calculate_distance(self.nodes[i - 1].pos, self.nodes[i].pos)
return h
```

Pentru a demonstra că euristica noastră nu este admisibilă, vom lua drept exemplu următoarea stare:

Nod de start: pos(0, 0) weight(5)

Drum până la mal (h = 7.83)
(0,0) -> (-1, 1) -> (-3, 1) -> (-4, 0) -> (-5, 0)

Drum estimat până la mal (h' = 18.75)
(0, 0) -> (-1, 1) -> (0, 2) -> (2, 2) -> (3, 0) -> (-3, 1) -> (-4, 1) -> (-4, 0) -> (-5, 0) -> (-3, -3)

Iar cum h' > h, euristica noastră nu este admisibilă.

## Comparație algoritmi

*example.txt*

|Algoritm |Lungime drum |Cost drum |Număr maxim noduri |Număr total de noduri |
|---------|-------------|----------|-------------------|----------------------|
|UCS                 |5 |7.83 |302 |12253  |
|A* *banală*         |5 |7.83 |76  |614    |
|A* *admisibilă_1*   |5 |7.83 |237 |4874   |
|A* *admisibilă_2*   |5 |7.83 |24  |70     |
|A* OPT              |5 |7.83 |236 |4923   |
|IDA*                |5 |7.83 |16  |83856  |
|IDA* *neadmisibilă* |5 |7.83 |9   |935    |

*example_long.txt*

|Algoritm |Lungime drum |Cost drum |Număr maxim noduri |Număr total de noduri |
|---------|-------------|----------|-------------------|----------------------|
|A* *banala*       |6 |13.18 |794  |37305  |
|A* *admisibilă_1* |6 |13.18 |631  |21671  |
|A* *admisibilă_2* |6 |13.18 |71   |292    |
|A* OPT            |6 |13.18 |630  |21704  |
|IDA*              |6 |13.19 |16   |8362   |

Din cele 2 exemple, putem observa următoarele:
  - Pe al doilea exemplu, algoritmul UCS nu rulează în timp util, blocându-se la timeout
  - A 2 a euristică parcurge un număr mult mai mic de noduri decât prima, euristica simulând în plus și micșorarea greutății după fiecare săritură
  - Pentru exemplul mai mare, algoritmul IDA* parcurge cel mai mic număr total de noduri, fiind un algoritm optim pentru exemple mari
    