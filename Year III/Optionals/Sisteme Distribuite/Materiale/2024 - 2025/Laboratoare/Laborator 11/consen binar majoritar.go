package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

// Node reprezintă un nod distribuit care votează.
type Node struct {
	ID       int    // Identificator unic
	Vote     int    // Votul curent (0 sau 1)
	IsDecided bool  // Indică dacă nodul a ajuns la consens
}

// Cluster reprezintă un grup de noduri distribuite.
type Cluster struct {
	Nodes []*Node
	mu    sync.Mutex // Mutex pentru operațiuni concurente
}

// NewNode creează un nou nod cu un vot aleator.
func NewNode(id int) *Node {
	rand.Seed(time.Now().UnixNano() + int64(id))
	return &Node{
		ID:   id,
		Vote: rand.Intn(2), // Valoarea inițială a votului (0 sau 1)
	}
}

// NewCluster creează un cluster cu noduri distribuite.
func NewCluster(size int) *Cluster {
	cluster := &Cluster{}
	for i := 1; i <= size; i++ {
		cluster.Nodes = append(cluster.Nodes, NewNode(i))
	}
	return cluster
}

// ConductVoting efectuează votul binar majoritar.
func (c *Cluster) ConductVoting() {
	c.mu.Lock()
	defer c.mu.Unlock()

	votes := map[int]int{
		0: 0,
		1: 0,
	}

	// Numărăm voturile fiecărui nod
	for _, node := range c.Nodes {
		fmt.Printf("Nodul %d votează: %d\n", node.ID, node.Vote)
		votes[node.Vote]++
	}

	// Determinăm valoarea majoritară
	var majorityValue int
	if votes[1] > votes[0] {
		majorityValue = 1
	} else {
		majorityValue = 0
	}

	// Actualizăm nodurile pentru consens
	for _, node := range c.Nodes {
		node.Vote = majorityValue
		node.IsDecided = true
	}

	fmt.Printf("Consens obținut: %d (0: %d voturi, 1: %d voturi)\n", majorityValue, votes[0], votes[1])
}

// PrintClusterStatus afișează starea actuală a clusterului.
func (c *Cluster) PrintClusterStatus() {
	c.mu.Lock()
	defer c.mu.Unlock()

	fmt.Println("Starea clusterului:")
	for _, node := range c.Nodes {
		consensus := "Nu"
		if node.IsDecided {
			consensus = "Da"
		}
		fmt.Printf("Nod %d - Vot: %d, Consens: %s\n", node.ID, node.Vote, consensus)
	}
}

func main() {
	// Inițializăm un cluster cu 5 noduri
	cluster := NewCluster(5)

	fmt.Println("Starea inițială a voturilor:")
	cluster.PrintClusterStatus()

	fmt.Println("\n=== Începerea procesului de vot ===")
	cluster.ConductVoting()

	fmt.Println("\nStarea finală a clusterului după consens:")
	cluster.PrintClusterStatus()
}
