package main

import (
	"fmt"
	"time"
)

func ex1() {
	channel := make(chan string)

	go func() {
		channel <- "salut"
	}()

	message := <-channel
	fmt.Println(message)
}

func ex2() {
	channel := make(chan string)

	go func() {
		channel <- "primu mesaj"
		channel <- "al doilea mesaj"
	}()

	var message string
	message += <-channel
	message += " " + <-channel
	fmt.Println(message)

}

func ex3() {
	channel := make(chan bool)

	go func() {
		time.Sleep(1 * time.Second)
		channel <- true
	}()

	success := <-channel
	if success {
		fmt.Println("a mers!")
	}
}

func ex4() {
	input_channel := make(chan string)
	output_channel := make(chan string)

	go func() {
		input_channel <- "mesajul dat"

	}()

	go func() {
		message := <-input_channel

		output_channel <- "am primit: " + message

	}()

	message := <-output_channel
	fmt.Println(message)
}

func ex5() {
	c1 := make(chan string)
	c2 := make(chan string)

	go func() {
		time.Sleep(1 * time.Second)
		c1 <- "Timpul e: " + time.Now().String()
	}()

	go func() {
		time.Sleep(2 * time.Second)
		c2 <- "Iar acum timpul e: " + time.Now().String()
	}()

	for i := 0; i < 2; i++ {
		select {
		case msg1 := <-c1:
			fmt.Println(msg1)
		case msg2 := <-c2:
			fmt.Println(msg2)
		}
	}
}
func addition(a, b int, channel chan int) {
	time.Sleep(2 * time.Second)
	channel <- a + b
}
func ex6() {
	channel := make(chan int)
	go addition(2, 3, channel)

	res := <-channel
	fmt.Println(res)
}

func main() {
	// ex1()
	// ex2()
	// ex3()
	// ex4()
	// ex5()
	ex6()
}
