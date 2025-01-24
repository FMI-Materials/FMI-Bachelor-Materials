package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"os"
	"regexp"
	"strconv"
	"strings"
)

func check(err error, m string) {
	if err != nil {
		panic(m + err.Error())
	}
}

func part1() {
	filePath := "test.txt"
	_, err := os.Stat(filePath)
	check(err, "Eroare la verificarea fișierului")

	actualFilePath, err := os.ReadFile(filePath)
	check(err, "Eroare la citirea fișierului")

	file, err := os.Open(string(actualFilePath))
	check(err, "Eroare la deschiderea fisierului 2")
	defer file.Close()
	scanner := bufio.NewScanner(file)
	var lines []string

	for scanner.Scan() {
		line := scanner.Text()
		lines = append(lines, line)
	}

	err = scanner.Err()
	check(err, "Eroare la citirea fisierului 2")

	for i, line := range lines {
		fmt.Printf("Line %d: %s\n", i+1, line)
	}

	err = os.WriteFile("output.txt", []byte(strings.Join(lines, "")), 0644)
	check(err, "Eroare la scrierea noului fisier")
}

func part2() {
	regex := regexp.MustCompile(`[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\s`)
	text := `Avem urmatoarele emailuri:
john.doe@example.com
jane.doe@example.org
peter.smith@example.co.uk
Comandă cel puțin o dată în timpul săptămânii, iar duminică, la o pizza de 30 cm comandată, îți oferim o pizza Classica 30 cm gratis.
mary.jones@example.edu
info@example.net
john.doe@example
jane.doe@example.c
peter.smith@example.com.
info@example.
`
	emails := regex.FindAllString(text, -1)
	fmt.Println("Emailuri:")
	for _, email := range emails {
		fmt.Println(email)
	}
}

type Book struct {
	Title  string `json:"title"`
	Author string `json:"author"`
}

func part3() {
	book := Book{
		Title:  "The Hobbit",
		Author: "J. R. R. Tolkien",
	}

	jsonData, err := json.Marshal(book)
	check(err, "Eroare la codificarea în JSON:")
	fmt.Println("Datele JSON:\n" + string(jsonData))
}

func hello(w http.ResponseWriter, req *http.Request) {
	fmt.Fprintf(w, "hello!\n")
}

func part4() {
	url := "https://sima.zapto.org/"
	resp, err := http.Get(url)
	check(err, "Eroare la efectuarea requestului HTTP")
	defer resp.Body.Close()

	body, err := io.ReadAll(resp.Body)
	check(err, "Eroare la citirea răspunsului HTTP")

	fmt.Println(string(body))

	http.HandleFunc("/hello", hello)
	http.ListenAndServe(":8090", nil)
	// http://localhost:8090/hello
}

func main() {
	if len(os.Args) != 2 {
		fmt.Println("Usage: go run myprogram.go [x]\n x should be in {1,2,3,4}")
		return
	}

	x, err := strconv.Atoi(os.Args[1])
	if err != nil || (x < 1 || x > 4) {
		fmt.Println("x should be a valid integer in the range [1, 2, 3, 4].")
		return
	}

	switch x {
	case 1:
		part1()
	case 2:
		part2()
	case 3:
		part3()
	case 4:
		part4()
	}
}
