package main

import (
	"encoding/csv"
	"fmt"
	"math/rand"
	"os"
	"sync"
	"time"
)

// Role defines the role of a node in the RAFT algorithm
// It can be Follower, Candidate, or Leader
type Role int

const (
	Follower Role = iota // Follower role
	Candidate            // Candidate role
	Leader               // Leader role
)

// Node represents a single node in the RAFT cluster
type Node struct {
	id         int          // Unique ID of the node
	role       Role         // Current role of the node (Follower, Candidate, Leader)
	term       int          // Current term number
	votes      int          // Number of votes received in an election
	leader     int          // ID of the current leader
	peers      []*Node      // List of peer nodes in the cluster
	timer      *time.Timer  // Timer to track election timeout
	mu         sync.Mutex   // Mutex to synchronize access to the node's state
	electionCh chan bool    // Channel to signal election-related events
	voteCh     chan bool    // Channel to signal vote-related events
}

// NewNode creates and initializes a new node with the given ID
func NewNode(id int) *Node {
	return &Node{
		id:         id,
		role:       Follower,     // Nodes start as Followers
		term:       0,            // Initial term is 0
		votes:      0,            // No votes initially
		leader:     -1,           // No leader initially
		electionCh: make(chan bool), // Channel for election events
		voteCh:    make(chan bool),  // Channel for vote events
	}
}

// resetTimer resets the election timer with a randomized timeout
func (n *Node) resetTimer() {
	n.timer = time.NewTimer(time.Duration(150+rand.Intn(150)) * time.Millisecond)
}

// run starts the main loop for the node, handling its behavior based on its role
func (n *Node) run() {
	for {
		n.resetTimer() // Reset the election timer
		select {
		case <-n.timer.C:
			// Election timeout occurred, start a new election
			n.startElection()
		case <-n.electionCh:
			// Heartbeat received, remain a Follower
			fmt.Printf("Node %d: Received heartbeat, staying Follower\n", n.id)
		case <-n.voteCh:
			// Vote granted to a candidate
			fmt.Printf("Node %d: Granted vote\n", n.id)
		}
	}
}

// startElection transitions the node to Candidate and initiates an election
func (n *Node) startElection() {
	n.mu.Lock()
	n.role = Candidate // Become a Candidate
	n.term++           // Increment the term
	n.votes = 1        // Vote for itself
	fmt.Printf("Node %d: Starting election for term %d\n", n.id, n.term)
	n.mu.Unlock()

	// Request votes from peers
	for _, peer := range n.peers {
		go func(peer *Node) {
			peer.vote(n.id, n.term)
		}(peer)
	}

	n.resetTimer() // Reset the election timer
	// Export votes to CSV
	exportVotesToCSV(n.id, n.term, n.votes)
}

// vote handles a vote request from a Candidate
func (n *Node) vote(candidateID, term int) {
	n.mu.Lock()
	defer n.mu.Unlock()
	if term > n.term { // Grant vote if the term is higher
		n.term = term    // Update term
		n.role = Follower // Revert to Follower
		n.leader = -1     // Clear the leader
		n.voteCh <- true  // Signal vote granted
		fmt.Printf("Node %d: Voted for Node %d in term %d\n", n.id, candidateID, term)
	}
}

// exportVotesToCSV exports the votes to a CSV file
func exportVotesToCSV(nodeID, term, votes int) {
	file, err := os.OpenFile("votes.csv", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		fmt.Printf("Error opening CSV file: %v\n", err)
		return
	}
	defer file.Close()

	writer := csv.NewWriter(file)
	defer writer.Flush()

	record := []string{fmt.Sprintf("%d", nodeID), fmt.Sprintf("%d", term), fmt.Sprintf("%d", votes)}
	if err := writer.Write(record); err != nil {
		fmt.Printf("Error writing to CSV file: %v\n", err)
	}
}

func main() {
	// Create nodes
	n1 := NewNode(1)
	n2 := NewNode(2)
	n3 := NewNode(3)
	n4 := NewNode(4)
	n5 := NewNode(5)

	// Set up peers for each node
	n1.peers = []*Node{n2, n3, n4, n5}
	n2.peers = []*Node{n1, n3, n4, n5}
	n3.peers = []*Node{n1, n2, n4, n5}
	n4.peers = []*Node{n1, n2, n3, n5}
	n5.peers = []*Node{n1, n2, n3, n4}

	// Run each node in a separate goroutine
	go n1.run()
	go n2.run()
	go n3.run()
	go n4.run()
	go n5.run()

	// Block the main function to keep the program running
	select {}
}
