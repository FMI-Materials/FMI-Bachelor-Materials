package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

// Proposal represents a proposal in the Paxos algorithm
// It includes a unique proposal number and a proposed value
type Proposal struct {
	Number int    // Unique proposal number
	Value  string // Proposed value
}

// Message represents a message exchanged between Proposers and Acceptors
// It includes the proposal and the type of the message (Prepare, Promise, Accept, Accepted)
type Message struct {
	Proposal Proposal
	Type     string // "Prepare", "Promise", "Accept", "Accepted"
}

// Acceptor represents a Paxos acceptor
// It stores the highest promised proposal number and the most recently accepted proposal
type Acceptor struct {
	mu             sync.Mutex    // Mutex to synchronize access to the state
	promisedNumber int           // Highest promised proposal number
	acceptedProposal Proposal    // Most recently accepted proposal
}

// Proposer represents a Paxos proposer
// It initiates the consensus process by sending Prepare and Accept messages
type Proposer struct {
	mu          sync.Mutex   // Mutex to synchronize access to the state
	majority    int          // Number of acceptors required for majority
	proposalNum int          // Current proposal number
	value       string       // Proposed value
	acceptors   []*Acceptor  // List of acceptors in the system
}

// Learner represents a Paxos learner
// It learns the agreed-upon value once consensus is reached
type Learner struct {
	mu       sync.Mutex        // Mutex to synchronize access to the state
	learned  map[string]bool   // Map to store learned values
}

// NewAcceptor creates a new Acceptor instance
func NewAcceptor() *Acceptor {
	return &Acceptor{}
}

// NewProposer creates a new Proposer instance
func NewProposer(majority int, value string, acceptors []*Acceptor) *Proposer {
	return &Proposer{
		majority:  majority, // Number of acceptors required for majority
		value:     value,    // Initial value to propose
		acceptors: acceptors, // List of acceptors
	}
}

// NewLearner creates a new Learner instance
func NewLearner() *Learner {
	return &Learner{learned: make(map[string]bool)}
}

// HandleMessage processes messages sent to an Acceptor
// It responds to Prepare and Accept messages
func (a *Acceptor) HandleMessage(msg Message) Message {
	a.mu.Lock()
	defer a.mu.Unlock()

	switch msg.Type {
	case "Prepare":
		// If the proposal number is greater than the highest promised number
		if msg.Proposal.Number > a.promisedNumber {
			a.promisedNumber = msg.Proposal.Number // Update promised number
			return Message{Proposal: Proposal{Number: a.promisedNumber}, Type: "Promise"} // Send a Promise
		}
	case "Accept":
		// If the proposal number is at least as large as the promised number
		if msg.Proposal.Number >= a.promisedNumber {
			a.promisedNumber = msg.Proposal.Number // Update promised number
			a.acceptedProposal = msg.Proposal      // Accept the proposal
			return Message{Proposal: a.acceptedProposal, Type: "Accepted"} // Send Accepted
		}
	}
	return Message{} // No response if conditions are not met
}

// Propose initiates the Paxos consensus process
// It sends Prepare and Accept messages to the Acceptors
func (p *Proposer) Propose() {
	p.mu.Lock()
	p.proposalNum++ // Increment the proposal number
	proposal := Proposal{Number: p.proposalNum, Value: p.value} // Create a new proposal
	p.mu.Unlock()

	promiseCount := 0
	for _, acceptor := range p.acceptors {
		// Send Prepare messages to all acceptors
		response := acceptor.HandleMessage(Message{Proposal: proposal, Type: "Prepare"})
		if response.Type == "Promise" {
			promiseCount++ // Count promises received
		}
	}

	// If a majority of promises is received, send Accept messages
	if promiseCount >= p.majority {
		acceptCount := 0
		for _, acceptor := range p.acceptors {
			response := acceptor.HandleMessage(Message{Proposal: proposal, Type: "Accept"})
			if response.Type == "Accepted" {
				acceptCount++ // Count acceptances received
			}
		}

		// If a majority of acceptances is received, consensus is reached
		if acceptCount >= p.majority {
			fmt.Printf("Consensus reached on value: %s\n", proposal.Value)
		}
	}
}

func main() {
	rand.Seed(time.Now().UnixNano()) // Initialize random seed

	// Create a list of acceptors
	acceptors := []*Acceptor{
		NewAcceptor(),
		NewAcceptor(),
		NewAcceptor(),
		NewAcceptor(),
		NewAcceptor(),
	}

	// Create a proposer with a majority of acceptors and an initial value
	majority := (len(acceptors) / 2) + 1
	proposer := NewProposer(majority, "ValueA", acceptors)
	proposer.Propose() // Start the proposal process
}
