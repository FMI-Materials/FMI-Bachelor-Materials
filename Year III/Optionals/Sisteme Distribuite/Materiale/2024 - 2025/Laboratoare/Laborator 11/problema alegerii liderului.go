package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

// Node reprezintă un nod într-un sistem distribuit.
type Node struct {
	ID      int    // Identificator unic pentru nod
	IsAlive bool   // Indică dacă nodul este activ
	IsLeader bool  // Indică dacă nodul este lider
}

// Cluster reprezintă un grup de noduri.
type Cluster struct {
	Nodes []*Node
	mu    sync.Mutex // Mutex pentru operațiuni concurente
}

// NewCluster inițializează un cluster cu noduri.
func NewCluster(size int) *Cluster {
	nodes := make([]*Node, size)
	for i := 0; i < size; i++ {
		nodes[i] = &Node{ID: i + 1, IsAlive: true, IsLeader: false}
	}
	return &Cluster{Nodes: nodes}
}

// ElectLeader implementează algoritmul de alegere a liderului folosind Bully.
func (c *Cluster) ElectLeader() {
	c.mu.Lock()
	defer c.mu.Unlock()

	// Filtrăm nodurile active
	var activeNodes []*Node
	for _, node := range c.Nodes {
		if node.IsAlive {
			activeNodes = append(activeNodes, node)
		}
	}

	if len(activeNodes) == 0 {
		fmt.Println("Nu există noduri active în cluster.")
		return
	}

	// Alegem liderul cu cel mai mare ID
	leader := activeNodes[0]
	for _, node := range activeNodes {
		if node.ID > leader.ID {
			leader = node
		}
	}

	// Marcăm nodul ca lider
	for _, node := range c.Nodes {
		node.IsLeader = (node.ID == leader.ID)
	}

	fmt.Printf("Nodul %d a fost ales lider.\n", leader.ID)
}

// FailNode marchează un nod ca fiind inactiv.
func (c *Cluster) FailNode(nodeID int) {
	c.mu.Lock()
	defer c.mu.Unlock()

	for _, node := range c.Nodes {
		if node.ID == nodeID {
			node.IsAlive = false
			fmt.Printf("Nodul %d a fost dezactivat.\n", node.ID)
			break
		}
	}
}

// PrintStatus afișează starea actuală a clusterului.
func (c *Cluster) PrintStatus() {
	c.mu.Lock()
	defer c.mu.Unlock()

	fmt.Println("Starea clusterului:")
	for _, node := range c.Nodes {
		status := "inactiv"
		if node.IsAlive {
			status = "activ"
		}
		role := ""
		if node.IsLeader {
			role = "(Lider)"
		}
		fmt.Printf("Nod %d: %s %s\n", node.ID, status, role)
	}
}

func main() {
	// Inițializăm clusterul cu 5 noduri
	cluster := NewCluster(5)

	// Alegem liderul inițial
	cluster.ElectLeader()
	cluster.PrintStatus()

	// Simulăm eșecul unui nod
	time.Sleep(2 * time.Second)
	cluster.FailNode(5)

	// Alegem din nou liderul
	time.Sleep(2 * time.Second)
	cluster.ElectLeader()
	cluster.PrintStatus()

	// Adăugăm latențe aleatorii pentru a simula un mediu distribuit
	rand.Seed(time.Now().UnixNano())
	time.Sleep(time.Duration(rand.Intn(3000)) * time.Millisecond)
}
