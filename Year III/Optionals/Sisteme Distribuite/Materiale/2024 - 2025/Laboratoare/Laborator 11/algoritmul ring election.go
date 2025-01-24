package main

import (
	"fmt"
	"sync"
	"time"
)

// Node reprezintă un nod într-un sistem distribuit.
type Node struct {
	ID       int       // Identificator unic
	IsLeader bool      // Indică dacă nodul este lider
	Next     *Node     // Referință către următorul nod din inel
	mu       sync.Mutex
}

// Cluster reprezintă un inel logic format din noduri.
type Cluster struct {
	Nodes []*Node
	mu    sync.Mutex
}

// NewNode creează un nou nod.
func NewNode(id int) *Node {
	return &Node{
		ID:       id,
		IsLeader: false,
	}
}

// NewCluster creează un cluster cu noduri aranjate în inel.
func NewCluster(size int) *Cluster {
	cluster := &Cluster{}
	for i := 1; i <= size; i++ {
		cluster.Nodes = append(cluster.Nodes, NewNode(i))
	}
	// Conectăm nodurile în inel
	for i := 0; i < size; i++ {
		cluster.Nodes[i].Next = cluster.Nodes[(i+1)%size]
	}
	return cluster
}

// StartElection inițiază alegerea liderului folosind algoritmul Ring Election.
func (n *Node) StartElection() {
	fmt.Printf("Nodul %d inițiază alegerea.\n", n.ID)
	proposedID := n.ID
	n.PropagateMessage(proposedID)
}

// PropagateMessage propagă un mesaj cu ID-ul propus către următorul nod din inel.
func (n *Node) PropagateMessage(proposedID int) {
	time.Sleep(1 * time.Second) // Simulează o latență în comunicare
	n.Next.mu.Lock()
	defer n.Next.mu.Unlock()

	fmt.Printf("Nodul %d primește mesajul cu ID-ul propus: %d.\n", n.Next.ID, proposedID)

	if n.Next.ID == n.ID {
		// Mesajul s-a întors la inițiator
		fmt.Printf("Nodul %d finalizează alegerea. Liderul este nodul cu ID-ul: %d.\n", n.ID, proposedID)
		n.DeclareLeader(proposedID)
		return
	}

	// Propagăm ID-ul maxim
	if proposedID > n.Next.ID {
		n.Next.PropagateMessage(proposedID)
	} else {
		n.Next.PropagateMessage(n.Next.ID)
	}
}

// DeclareLeader declară liderul pentru toate nodurile din inel.
func (n *Node) DeclareLeader(leaderID int) {
	current := n
	for {
		current.mu.Lock()
		current.IsLeader = (current.ID == leaderID)
		current.mu.Unlock()

		if current.Next.ID == n.ID {
			break
		}
		current = current.Next
	}
	fmt.Printf("Liderul a fost ales: Nodul %d.\n", leaderID)
}

// PrintClusterStatus afișează starea actuală a clusterului.
func (c *Cluster) PrintClusterStatus() {
	fmt.Println("Starea clusterului:")
	for _, node := range c.Nodes {
		role := "Participă"
		if node.IsLeader {
			role = "Lider"
		}
		fmt.Printf("Nod %d: %s\n", node.ID, role)
	}
}

func main() {
	// Creăm un cluster cu 5 noduri
	cluster := NewCluster(5)

	// Afișăm starea inițială a clusterului
	cluster.PrintClusterStatus()

	// Inițiem procesul de alegere de la un nod
	time.Sleep(1 * time.Second)
	go cluster.Nodes[2].StartElection()

	// Așteptăm câteva secunde pentru ca alegerea să fie completă
	time.Sleep(10 * time.Second)

	// Afișăm starea finală a clusterului
	cluster.PrintClusterStatus()
}
