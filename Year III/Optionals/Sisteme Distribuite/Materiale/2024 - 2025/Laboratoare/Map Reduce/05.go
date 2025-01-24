//Determinarea frecvenței celor mai frecvente cuvinte
//Extinde codul pentru a afișa doar primele 5 cele mai frecvente cuvinte dintr-un set de documente. Sortează rezultatele după frecvență înainte de afișare.

package main

import (
	"fmt"
	"net"
	"strings"
	"sync"
	"encoding/json"
	"sort"
)

// KeyValue is a structure to hold a key-value pair
type KeyValue struct {
	Key   string
	Value int
}

// Map function: Splits a string into words and counts occurrences
func Map(document string) []KeyValue {
	// Convert the document to lowercase and split it into words
	words := strings.Fields(strings.ToLower(document))
	// Initialize a slice to hold key-value pairs
	keyValues := make([]KeyValue, 0)

	// Iterate through each word and create a KeyValue pair with count 1
	for _, word := range words {
		keyValues = append(keyValues, KeyValue{Key: word, Value: 1})
	}

	return keyValues
}

// Reduce function: Aggregates counts for each word
func Reduce(key string, values []int) int {
	sum := 0
	// Sum all the values associated with a key
	for _, value := range values {
		sum += value
	}
	return sum
}

// Server function to handle map requests
func server(address string, documents []string) {
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
		go handleConnection(conn, documents)
	}
}

func handleConnection(conn net.Conn, documents []string) {
	defer conn.Close()
	
	mapResults := make([]KeyValue, 0)
	for _, doc := range documents {
		result := Map(doc)
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
		"MapReduce is a programming model for processing large data sets.",
		"This model simplifies processing by distributing tasks.",
		"Go is a great language for implementing MapReduce.",
	}

	// Start server in a separate goroutine
	serverAddress := "localhost:8080"
	go server(serverAddress, documents)

	// Allow server to start
	var wg sync.WaitGroup
	wg.Add(1)
	go func() {
		defer wg.Done()
		clientResults := client(serverAddress)

		// Phase 2: Shuffle phase
		groupedResults := make(map[string][]int) // Map to group values by key
		for _, kv := range clientResults {
			groupedResults[kv.Key] = append(groupedResults[kv.Key], kv.Value)
		}

		// Phase 3: Reduce phase
		finalResults := make(map[string]int) // Map to store the final results
		for key, values := range groupedResults {
			// Apply the Reduce function to aggregate values for each key
			finalResults[key] = Reduce(key, values)
		}

		// Extract and sort the results by frequency
		sortedResults := make([]KeyValue, 0, len(finalResults))
		for key, value := range finalResults {
			sortedResults = append(sortedResults, KeyValue{Key: key, Value: value})
		}
		sort.Slice(sortedResults, func(i, j int) bool {
			return sortedResults[i].Value > sortedResults[j].Value
		})

		// Print the top 5 most frequent words
		fmt.Println("Top 5 most frequent words:")
		for i, kv := range sortedResults {
			if i >= 5 {
				break
			}
			fmt.Printf("%s: %d\n", kv.Key, kv.Value)
		}
	}()

	wg.Wait()
}
