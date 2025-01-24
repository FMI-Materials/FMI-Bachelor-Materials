package main

import (
	"fmt"
	"sync"
	"time"
)

// Node reprezintă un nod într-un sistem distribuit.
type Node struct {
	ID        int       // Identificator unic
	IsAlive   bool      // Indică dacă nodul este activ
	IsLeader  bool      // Indică dacă nodul este lider
	Cluster   *Cluster  // Referință către cluster
	mu        sync.Mutex
	ElectionOngoing bool // Flag pentru a preveni multiple alegeri simultane
}

// Cluster reprezintă un grup de noduri.
type Cluster struct {
	Nodes []*Node
	mu    sync.Mutex
}

// NewNode creează un nou nod activ.
func NewNode(id int, cluster *Cluster) *Node {
	return &Node{
		ID:      id,
		IsAlive: true,
		Cluster: cluster,
	}
}

// NewCluster creează un cluster cu noduri distribuite.
func NewCluster(size int) *Cluster {
	cluster := &Cluster{}
	for i := 1; i <= size; i++ {
		cluster.Nodes = append(cluster.Nodes, NewNode(i, cluster))
	}
	return cluster
}

// StartElection inițiază procesul de alegere a liderului.
func (n *Node) StartElection() {
	n.mu.Lock()
	if n.ElectionOngoing {
		n.mu.Unlock()
		return // O alegere este deja în desfășurare
	}
	n.ElectionOngoing = true
	n.mu.Unlock()

	fmt.Printf("Nodul %d inițiază o alegere.\n", n.ID)

	highestID := n.ID
	for _, node := range n.Cluster.Nodes {
		if node.ID > n.ID && node.IsAlive {
			fmt.Printf("Nodul %d notifică nodul %d despre alegere.\n", n.ID, node.ID)
			highestID = node.ID
			node.StartElection()
		}
	}

	if highestID == n.ID {
		n.BecomeLeader()
	}
}

// BecomeLeader setează nodul curent ca lider.
func (n *Node) BecomeLeader() {
	n.mu.Lock()
	defer n.mu.Unlock()

	fmt.Printf("Nodul %d devine lider.\n", n.ID)

	for _, node := range n.Cluster.Nodes {
		node.mu.Lock()
		node.IsLeader = false
		node.mu.Unlock()
	}

	n.IsLeader = true
	n.ElectionOngoing = false
}

// SimulateFailure simulează defectarea unui nod.
func (n *Node) SimulateFailure() {
	n.mu.Lock()
	n.IsAlive = false
	n.IsLeader = false
	n.mu.Unlock()
	fmt.Printf("Nodul %d a căzut!\n", n.ID)
}

// MonitorCluster detectează dacă liderul cade și inițiază o nouă alegere.
func (c *Cluster) MonitorCluster() {
	for {
		time.Sleep(2 * time.Second) // Monitorizare periodică
		c.mu.Lock()

		var leaderExists bool
		for _, node := range c.Nodes {
			node.mu.Lock()
			if node.IsLeader && node.IsAlive {
				leaderExists = true
			}
			node.mu.Unlock()
		}

		if !leaderExists {
			fmt.Println("Liderul a căzut. Inițierea unei noi alegeri.")
			for _, node := range c.Nodes {
				node.mu.Lock()
				if node.IsAlive {
					go node.StartElection()
					node.mu.Unlock()
					break
				}
				node.mu.Unlock()
			}
		}

		c.mu.Unlock()
	}
}

func main() {
	// Creăm un cluster cu 5 noduri
	cluster := NewCluster(5)

	// Pornim monitorizarea clusterului
	go cluster.MonitorCluster()

	// Pornim procesul inițial de alegere
	cluster.Nodes[0].StartElection()

	// Simulăm defectarea liderului
	time.Sleep(5 * time.Second)
	for _, node := range cluster.Nodes {
		node.mu.Lock()
		if node.IsLeader {
			go node.SimulateFailure()
		}
		node.mu.Unlock()
	}

	// Așteptăm câteva secunde pentru a permite clusterului să proceseze
	time.Sleep(10 * time.Second)
}
