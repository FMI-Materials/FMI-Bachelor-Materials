package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

// Node reprezintă un nod distribuit.
type Node struct {
	ID      int    // Identificator unic
	IsAlive bool   // Indică dacă nodul este funcțional
	Value   int    // Valoare asociată nodului
	mu      sync.Mutex
}

// Cluster reprezintă un grup de noduri distribuite.
type Cluster struct {
	Nodes []*Node
	mu    sync.Mutex // Mutex pentru operațiuni concurente
}

// NewNode creează un nod funcțional cu o valoare aleatorie.
func NewNode(id int) *Node {
	rand.Seed(time.Now().UnixNano() + int64(id))
	return &Node{
		ID:      id,
		IsAlive: true,
		Value:   rand.Intn(100), // Valoare între 0 și 99
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

// SimulateFailure simulează defectarea unui nod după un timp aleator.
func (n *Node) SimulateFailure() {
	time.Sleep(time.Duration(rand.Intn(5)+1) * time.Second)
	n.mu.Lock()
	n.IsAlive = false
	n.mu.Unlock()
	fmt.Printf("Nodul %d a căzut!\n", n.ID)
}

// MonitorCluster detectează nodurile defecte și le elimină din cluster.
func (c *Cluster) MonitorCluster() {
	for {
		time.Sleep(2 * time.Second) // Monitorizare periodică
		c.mu.Lock()

		for i := 0; i < len(c.Nodes); i++ {
			node := c.Nodes[i]
			node.mu.Lock()
			if !node.IsAlive {
				fmt.Printf("Monitorizare: Eliminăm nodul %d din cluster.\n", node.ID)
				c.Nodes = append(c.Nodes[:i], c.Nodes[i+1:]...) // Eliminăm nodul
				i-- // Ajustăm indexul
			}
			node.mu.Unlock()
		}

		c.mu.Unlock()
	}
}

// PerformTask efectuează o sarcină de calcul pe nodurile funcționale.
func (c *Cluster) PerformTask() {
	c.mu.Lock()
	defer c.mu.Unlock()

	fmt.Println("Efectuăm calculul pe nodurile funcționale:")
	sum := 0
	activeNodes := 0
	for _, node := range c.Nodes {
		node.mu.Lock()
		if node.IsAlive {
			fmt.Printf("Nod %d (Valoare: %d) participă la calcul.\n", node.ID, node.Value)
			sum += node.Value
			activeNodes++
		}
		node.mu.Unlock()
	}

	if activeNodes > 0 {
		fmt.Printf("Suma totală: %d, Media: %.2f\n", sum, float64(sum)/float64(activeNodes))
	} else {
		fmt.Println("Nu există noduri active pentru a efectua calculul.")
	}
}

func main() {
	// Inițializăm un cluster cu 5 noduri
	cluster := NewCluster(5)

	// Pornim monitorizarea nodurilor în fundal
	go cluster.MonitorCluster()

	// Simulăm defectarea nodurilor
	for _, node := range cluster.Nodes {
		go node.SimulateFailure()
	}

	// Efectuăm calcule periodic
	for i := 0; i < 5; i++ {
		time.Sleep(3 * time.Second)
		cluster.PerformTask()
	}
}
