package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

// Node reprezintă un nod într-un sistem distribuit.
type Node struct {
	ID       int     // Identificator unic
	Value    float64 // Valoarea curentă a nodului
	Neighbors []*Node // Vecinii nodului
	mu       sync.Mutex
}

// Cluster reprezintă un grup de noduri distribuite.
type Cluster struct {
	Nodes []*Node
	mu    sync.Mutex
}

// NewNode creează un nod cu o valoare inițială aleatorie.
func NewNode(id int) *Node {
	rand.Seed(time.Now().UnixNano() + int64(id))
	return &Node{
		ID:       id,
		Value:    rand.Float64() * 100, // Valoare inițială între 0 și 100
		Neighbors: []*Node{},
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

// ConnectNodes stabilește conexiuni între noduri, simulând o rețea distribuită.
func (c *Cluster) ConnectNodes() {
	for _, node := range c.Nodes {
		for _, neighbor := range c.Nodes {
			if node.ID != neighbor.ID {
				node.Neighbors = append(node.Neighbors, neighbor)
			}
		}
	}
}

// UpdateValue calculează noua valoare a nodului bazată pe valorile vecinilor.
func (n *Node) UpdateValue() {
	n.mu.Lock()
	defer n.mu.Unlock()

	sum := n.Value
	count := 1

	for _, neighbor := range n.Neighbors {
		neighbor.mu.Lock()
		sum += neighbor.Value
		count++
		neighbor.mu.Unlock()
	}

	newValue := sum / float64(count)
	n.Value = newValue
}

// PerformConsensus execută iterativ actualizările pentru a ajunge la consens.
func (c *Cluster) PerformConsensus(iterations int) {
	for i := 0; i < iterations; i++ {
		fmt.Printf("\n=== Iterația %d ===\n", i+1)
		var wg sync.WaitGroup

		// Actualizăm valoarea fiecărui nod concurent
		for _, node := range c.Nodes {
			wg.Add(1)
			go func(n *Node) {
				defer wg.Done()
				n.UpdateValue()
			}(node)
		}

		wg.Wait()

		// Afișăm valorile actualizate ale nodurilor
		c.PrintClusterStatus()
	}
}

// PrintClusterStatus afișează valorile curente ale nodurilor din cluster.
func (c *Cluster) PrintClusterStatus() {
	c.mu.Lock()
	defer c.mu.Unlock()

	fmt.Println("Valori noduri:")
	for _, node := range c.Nodes {
		fmt.Printf("Nod %d: %.2f\n", node.ID, node.Value)
	}
}

func main() {
	// Inițializăm un cluster cu 5 noduri
	cluster := NewCluster(5)

	// Conectăm nodurile între ele
	cluster.ConnectNodes()

	// Afișăm valorile inițiale ale nodurilor
	fmt.Println("Valori inițiale ale nodurilor:")
	cluster.PrintClusterStatus()

	// Executăm consensul timp de 10 iterări
	fmt.Println("\n=== Începerea consensului ===")
	cluster.PerformConsensus(10)
}
