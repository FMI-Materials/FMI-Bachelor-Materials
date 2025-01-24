//Analiza de sentiment bazată pe cuvinte
//Utilizează MapReduce pentru a clasifica documentele ca având ton pozitiv, negativ sau neutru. În faza Map, fiecare cuvânt este asociat cu un scor (+1 pentru //cuvinte pozitive, -1 pentru cuvinte negative, 0 pentru neutre). În faza Reduce, calculează scorul total al fiecărui document.

package main

import (
	"fmt"
	"net"
	"strings"
	"sync"
	"encoding/json"
)

// KeyValue is a structure to hold a key-value pair
type KeyValue struct {
	Key   string
	Value int
}

// Map function: Splits a string into words and assigns sentiment scores
func Map(document string, sentiment map[string]int) []KeyValue {
	// Convert the document to lowercase and split it into words
	words := strings.Fields(strings.ToLower(document))
	// Initialize a slice to hold key-value pairs
	keyValues := make([]KeyValue, 0)

	// Iterate through each word and assign sentiment score
	for _, word := range words {
		if score, exists := sentiment[word]; exists {
			keyValues = append(keyValues, KeyValue{Key: word, Value: score})
		}
	}

	return keyValues
}

// Reduce function: Aggregates sentiment scores for a document
func Reduce(values []int) int {
	sum := 0
	// Sum all the values
	for _, value := range values {
		sum += value
	}
	return sum
}

// Server function to handle map requests
func server(address string, documents []string, sentiment map[string]int) {
	ln, err := net.Listen("tcp", address)
	if err != nil {
		fmt.Println("Error starting server:", err)
		return
	}
	defer ln.Close()
	fmt.Println("Server is running on", address)

	for {
		conn, err := ln.Accept()
		if err != nil {
			fmt.Println("Connection error:", err)
			continue
		}
		go handleConnection(conn, documents, sentiment)
	}
}

func handleConnection(conn net.Conn, documents []string, sentiment map[string]int) {
	defer conn.Close()

	mapResults := make([]KeyValue, 0)
	for _, doc := range documents {
		result := Map(doc, sentiment)
		mapResults = append(mapResults, result...)
	}

	data, err := json.Marshal(mapResults)
	if err != nil {
		fmt.Println("Error marshaling data:", err)
		return
	}
	conn.Write(data)
}

// Client function to send map requests
func client(address string) []KeyValue {
	conn, err := net.Dial("tcp", address)
	if err != nil {
		fmt.Println("Error connecting to server:", err)
		return nil
	}
	defer conn.Close()

	buffer := make([]byte, 4096)
	n, err := conn.Read(buffer)
	if err != nil {
		fmt.Println("Error reading data from server:", err)
		return nil
	}

	var mapResults []KeyValue
	err = json.Unmarshal(buffer[:n], &mapResults)
	if err != nil {
		fmt.Println("Error unmarshaling data:", err)
		return nil
	}

	return mapResults
}

func main() {
	documents := []string{
		"The product is amazing and excellent.",
		"The service was terrible and disappointing.",
		"The experience was okay, neither good nor bad.",
	}

	// Define sentiment scores for words
	sentiment := map[string]int{
		"amazing": 1, "excellent": 1, "great": 1,
		"terrible": -1, "disappointing": -1, "bad": -1,
		"okay": 0, "neutral": 0,
	}

	// Start server in a separate goroutine
	serverAddress := "localhost:8080"
	go server(serverAddress, documents, sentiment)

	// Allow server to start
	var wg sync.WaitGroup
	wg.Add(1)
	go func() {
		defer wg.Done()
		clientResults := client(serverAddress)

		// Phase 2: Shuffle and reduce
		groupedResults := make(map[string][]int) // Map to group values by document
		for _, kv := range clientResults {
			groupedResults[kv.Key] = append(groupedResults[kv.Key], kv.Value)
		}

		totalScores := make(map[string]int)
		for doc, scores := range groupedResults {
			totalScores[doc] = Reduce(scores)
		}

		// Print sentiment analysis results
		fmt.Println("Sentiment analysis results:")
		for doc, score := range totalScores {
			fmt.Printf("%s: Sentiment Score = %d\n", doc, score)
		}
	}()

	wg.Wait()
}
