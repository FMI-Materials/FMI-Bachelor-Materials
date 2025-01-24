package main

import (
	"fmt"
	"sync"
	"time"
)

// Node reprezintă un nod dintr-un sistem distribuit, care utilizează un ceas logic.
type Node struct {
	ID      int           // Identificator unic pentru nod
	Clock   int           // Ceasul logic al nodului
	Channel chan Message  // Canal pentru a primi mesaje
	mu      sync.Mutex    // Mutex pentru sincronizare
}

// Message reprezintă un mesaj trimis între noduri.
type Message struct {
	SenderID int // ID-ul nodului care a trimis mesajul
	Clock    int // Valoarea ceasului logic la momentul trimiterii
	Content  string
}

// NewNode creează un nou nod distribuit.
func NewNode(id int) *Node {
	return &Node{
		ID:      id,
		Clock:   0,
		Channel: make(chan Message, 10),
	}
}

// IncrementClock incrementează ceasul logic al nodului.
func (n *Node) IncrementClock() {
	n.mu.Lock()
	defer n.mu.Unlock()
	n.Clock++
}

// UpdateClock actualizează ceasul logic pe baza ceasului primit.
func (n *Node) UpdateClock(receivedClock int) {
	n.mu.Lock()
	defer n.mu.Unlock()
	if n.Clock < receivedClock {
		n.Clock = receivedClock
	}
	n.Clock++ // Incrementăm ceasul pentru evenimentul curent.
}

// SendMessage trimite un mesaj către un alt nod.
func (n *Node) SendMessage(target *Node, content string) {
	n.IncrementClock() // Incrementăm ceasul înainte de a trimite mesajul.
	msg := Message{
		SenderID: n.ID,
		Clock:    n.Clock,
		Content:  content,
	}
	fmt.Printf("Nodul %d trimite mesaj: '%s' (ceas: %d) către nodul %d\n", n.ID, content, n.Clock, target.ID)
	target.Channel <- msg
}

// ReceiveMessage procesează mesajele primite.
func (n *Node) ReceiveMessage() {
	for msg := range n.Channel {
		fmt.Printf("Nodul %d primește mesaj: '%s' (ceas: %d) de la nodul %d\n", n.ID, msg.Content, msg.Clock, msg.SenderID)
		n.UpdateClock(msg.Clock) // Actualizăm ceasul logic pe baza mesajului primit.
		fmt.Printf("Ceasul actualizat al nodului %d: %d\n", n.ID, n.Clock)
	}
}

func main() {
	// Creăm două noduri
	nodeA := NewNode(1)
	nodeB := NewNode(2)

	// Pornim procesul de primire a mesajelor în goroutines separate.
	go nodeA.ReceiveMessage()
	go nodeB.ReceiveMessage()

	// Simulăm trimiterea mesajelor.
	time.Sleep(1 * time.Second) // Pauză pentru a permite inițializarea.

	nodeA.SendMessage(nodeB, "Salut de la A!")
	time.Sleep(500 * time.Millisecond) // Pauză pentru a simula latență.

	nodeB.SendMessage(nodeA, "Salut de la B!")
	time.Sleep(500 * time.Millisecond)

	nodeA.SendMessage(nodeB, "Cum merge?")
	time.Sleep(500 * time.Millisecond)

	nodeB.SendMessage(nodeA, "Bine, tu?")
	time.Sleep(500 * time.Millisecond)

	// Închidem canalele după ce toate mesajele au fost procesate.
	close(nodeA.Channel)
	close(nodeB.Channel)
}
