package main

import (
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: go run client.go <fruit_name>")
		return
	}

	fruitName := os.Args[1]

	resp, err := http.Get("http://localhost:8080/?fruit=" + fruitName)
	if err != nil {
		log.Fatal("Error making the request:", err)
	}

	defer resp.Body.Close()

	if resp.StatusCode == http.StatusOK {
		body, err := io.ReadAll(resp.Body)
		if err != nil {
			log.Fatal("Error reading the response:", err)
		}

		fmt.Println(string(body))
	} else {
		fmt.Println("Error: Request failed with status code", resp.Status)
	}
}
