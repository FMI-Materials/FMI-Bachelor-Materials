//Explicație cod:
//    Faza Map:
//        Funcția Map primește un document și îl împarte în cuvinte.
//        Returnează o listă de perechi cheie-valoare, unde cheia este cuvântul și valoarea este 1.
//
//    Faza Shuffle: Se grupează rezultatele mapării pe baza cheilor (cuvintelor).
//
//    Faza Reduce: Funcția Reduce agregă valorile (sumele) pentru fiecare cuvânt.
//
//    Concurență:
//        Se folosește un sync.WaitGroup pentru a asigura că toate operațiunile de mapare se finalizează.
//        Se folosește un sync.Mutex pentru a proteja resursele partajate în timpul accesului concurent.
//
//    Rezultatul final: Este afișat un tabel cu frecvența fiecărui cuvânt din documente.


//Implementarea fundamentală a algoritmului MapReduce în limbajul de programare Go. 
//Aceasta implementează conceptul de bază în care se împart datele pentru procesare (map), se grupează rezultatele și se reduc (reduce).

package main

import (
	"fmt"
	"strings"
	"sync"
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

func main() {
	// Input documents to process
	documents := []string{
		"MapReduce is a programming model for processing large data sets.",
		"This model simplifies processing by distributing tasks.",
		"Go is a great language for implementing MapReduce.",
	}

	// Phase 1: Map phase
	mapResults := make([]KeyValue, 0) // Slice to store results of the Map phase
	var wg sync.WaitGroup             // WaitGroup to synchronize goroutines
	var mutex sync.Mutex              // Mutex to prevent race conditions

	// Process each document concurrently
	for _, doc := range documents {
		wg.Add(1) // Increment the WaitGroup counter
		go func(document string) {
			defer wg.Done() // Decrement the counter when the goroutine completes
			result := Map(document) // Perform the map operation
			mutex.Lock()            // Lock the mutex before accessing shared resource
			mapResults = append(mapResults, result...)
			mutex.Unlock()          // Unlock the mutex after modification
		}(doc)
	}

	// Wait for all goroutines to finish
	wg.Wait()

	// Phase 2: Shuffle phase
	groupedResults := make(map[string][]int) // Map to group values by key

	// Group values by their keys
	for _, kv := range mapResults {
		groupedResults[kv.Key] = append(groupedResults[kv.Key], kv.Value)
	}

	// Phase 3: Reduce phase
	finalResults := make(map[string]int) // Map to store the final results
	for key, values := range groupedResults {
		// Apply the Reduce function to aggregate values for each key
		finalResults[key] = Reduce(key, values)
	}

	// Print the final results
	fmt.Println("Word counts:")
	for word, count := range finalResults {
		fmt.Printf("%s: %d\n", word, count)
	}
}
