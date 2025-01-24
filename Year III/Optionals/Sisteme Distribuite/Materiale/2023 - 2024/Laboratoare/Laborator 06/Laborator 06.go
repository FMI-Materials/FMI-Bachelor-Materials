package main

import (
	"encoding/csv"
	"fmt"
	"os"
	"os/exec"
	"runtime"
	"time"

	"github.com/shirou/gopsutil/process"
)

func handleError(err error){
	if err != nil {
		fmt.Println("Error:", err)
		os.Exit(1)
	}
}

func part1(){

	csvFile, err := os.Create("timezones.csv")
	handleError(err)
	csvwriter := csv.NewWriter(csvFile)

	zones := []string{"America/Los_Angeles", "America/New_York", "Europe/Bucharest", "Europe/London", "Asia/Tokyo", "Australia/Sydney"}

	for _, timezone := range zones {
		time := time.Now().In(time.FixedZone(timezone, 0))
		_ = csvwriter.Write([]string{timezone, time.String()})
	}
	csvwriter.Flush()
	csvFile.Close()

}


func sumArray(nums...float64) float64 {
	sum := 0.0
	for _, n := range nums {
		sum += n
	}
	return sum
}

func part2() {
	numCores := float64(runtime.NumCPU())
	for {
		processes, _ := process.Processes()

		var procUsage []float64
		var memUsage []float64
		for _, p := range processes {
			c, _ := p.CPUPercent()
			pp, _ := p.MemoryPercent()
			m := float64(pp)
			procUsage = append(procUsage, c/numCores)
			memUsage = append(memUsage, m)
		}

		fmt.Println("CPU Usage: ", sumArray(procUsage...))
		fmt.Println("Memory Usage: ", sumArray(memUsage...))
		time.Sleep(3 * time.Second)
		c := exec.Command("clear")
		c.Stdout = os.Stdout
		c.Run()
	}
}


func main(){
	// part1()
	part2()
}
