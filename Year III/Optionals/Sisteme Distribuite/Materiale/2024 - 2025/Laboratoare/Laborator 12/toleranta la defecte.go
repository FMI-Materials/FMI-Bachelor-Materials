package main

import (
	"fmt"
	"math/rand"
	"sync"
)

// Node reprezintă un nod din sistemul distribuit.
type Node struct {
	id       int        // ID unic al nodului
	value    int        // Valoarea curentă propusă
	faulty   bool       // Indică dacă nodul este defect
	mutex    sync.Mutex // Mutex pentru sincronizare
}

// System reprezintă sistemul distribuit.
type System struct {
	nodes      []*Node // Lista de noduri
	majority   int     // Pragul de consens
	numFaulty  int     // Numărul de noduri defecte
	numRounds  int     // Numărul de runde pentru consens
}

// NewSystem creează un sistem distribuit cu `n` noduri și `f` noduri defecte.
func NewSystem(n, f, rounds int) *System {
	nodes := make([]*Node, n)
	for i := 0; i < n; i++ {
		nodes[i] = &Node{
			id:    i,
			value: rand.Intn(100), // Valoare inițială aleatoare
			faulty: false,         // Implicit, nodurile nu sunt defecte
		}
	}

	// Marcăm aleator `f` noduri ca fiind defecte.
	for i := 0; i < f; i++ {
		index := rand.Intn(n)
		nodes[index].faulty = true
	}

	return &System{
		nodes:     nodes,
		majority:  (n - f), // Majoritate necesară pentru consens
		numFaulty: f,
		numRounds: rounds,
	}
}

// broadcastValue trimite valoarea unui nod către toate celelalte noduri.
func (n *Node) broadcastValue(system *System) []int {
	n.mutex.Lock()
	defer n.mutex.Unlock()

	// Dacă nodul este defect, trimite valori aleatoare.
	if n.faulty {
		fmt.Printf("Node %d is faulty and broadcasting random values.\n", n.id)
		values := make([]int, len(system.nodes))
		for i := range values {
			values[i] = rand.Intn(100)
		}
		return values
	}

	// Dacă nodul este corect, trimite propria valoare.
	values := make([]int, len(system.nodes))
	for i := range values {
		values[i] = n.value
	}
	fmt.Printf("Node %d broadcasts its value: %d.\n", n.id, n.value)
	return values
}

// collectValues colectează valorile primite de la toate nodurile.
func (s *System) collectValues() [][]int {
	var wg sync.WaitGroup
	receivedValues := make([][]int, len(s.nodes))

	for i, node := range s.nodes {
		wg.Add(1)
		go func(i int, node *Node) {
			defer wg.Done()
			receivedValues[i] = node.broadcastValue(s)
		}(i, node)
	}

	wg.Wait()
	return receivedValues
}

// calculateConsensus determină consensul pe baza valorilor primite.
func (s *System) calculateConsensus(receivedValues [][]int) {
	for _, node := range s.nodes {
		if node.faulty {
			continue // Nodurile defecte nu iau parte la consens.
		}

		node.mutex.Lock()

		// Calculăm frecvența valorilor primite.
		valueCounts := make(map[int]int)
		for _, values := range receivedValues {
			valueCounts[values[node.id]]++
		}

		// Selectăm valoarea cu cea mai mare frecvență.
		consensusValue := -1
		maxCount := 0
		for value, count := range valueCounts {
			if count > maxCount {
				consensusValue = value
				maxCount = count
			}
		}

		// Actualizăm valoarea nodului.
		node.value = consensusValue
		node.mutex.Unlock()

		fmt.Printf("Node %d updates its value to: %d.\n", node.id, consensusValue)
	}
}

// runConsensus execută algoritmul de consens asincron tolerant la defecte.
func (s *System) runConsensus() {
	for round := 1; round <= s.numRounds; round++ {
		fmt.Printf("\nRound %d:\n", round)

		// Colectăm valorile transmise de noduri.
		receivedValues := s.collectValues()

		// Calculăm consensul pentru nodurile corecte.
		s.calculateConsensus(receivedValues)
	}
}

// printValues afișează valorile curente ale nodurilor.
func (s *System) printValues() {
	fmt.Println("Node Values:")
	for _, node := range s.nodes {
		status := "Correct"
		if node.faulty {
			status = "Faulty"
		}
		fmt.Printf("Node %d: Value = %d (%s)\n", node.id, node.value, status)
	}
	fmt.Println()
}

func main() {
	// Inițializăm sistemul cu 7 noduri, 2 noduri defecte și 5 runde de consens.
	system := NewSystem(7, 2, 5)

	// Afișăm valorile inițiale ale nodurilor.
	fmt.Println("Initial Node Values:")
	system.printValues()

	// Rulăm algoritmul de consens tolerant la defecte.
	fmt.Println("Starting Fault-Tolerant Consensus...")
	system.runConsensus()

	// Afișăm valorile finale ale nodurilor.
	fmt.Println("\nFinal Node Values:")
	system.printValues()
}
