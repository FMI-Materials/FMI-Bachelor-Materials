package main

import (
	"encoding/json"
	"fmt"
	"net/http"
	"os"
)

type FruitWeights map[string]float64

var fruitData FruitWeights

func main() {
	fileData, err := os.ReadFile("cantitati_fructe.json")
	if err != nil {
		fmt.Println("Error reading the JSON file:", err)
		return
	}

	err = json.Unmarshal(fileData, &fruitData)
	if err != nil {
		fmt.Println("Eroare parsare JSON:", err)
		return
	}

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		fruitName := r.URL.Query().Get("fruit")
		weight, found := fruitData[fruitName]

		if found {
			fmt.Fprintf(w, "%.2fkg de %s", weight, fruitName)
		} else {
			fmt.Fprint(w, "404 - Fruit Not Found")
		}
	})

	http.ListenAndServe(":8080", nil)
}
