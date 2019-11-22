package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"math"
	"net/http"
	"os"
	"strconv"
	"strings"
)
import "math/rand"

func generateRandomNumberString(size int) string {
	var str = ""
	for i := 0; i < size; i++ {
		str += strconv.Itoa(rand.Intn(10))
	}
	return str
}

func splitString(str string) *[]string {
	var size = int(math.Ceil(float64((len(str) - 1) / 3)))
	var returnValue = make([]string, size+1)
	for i := 0; i < int(math.Floor(float64(len(str)/3))); i++ {
		x := str[i*3 : (i+1)*3]
		returnValue[i] = x
	}
	if len(str)%3 != 0 {
		returnValue[size] = str[int(math.Floor(float64(len(str)/3)))*3:]
	}
	return &returnValue
}

func transformBlocks(splitString *[]string) *[]string {
	for index, element := range *splitString {
		if element[0:1] == "0" {
			if index != 0 && len((*splitString)[index-1]) > 2 && (*splitString)[index-1][2:3] != "0" {
				var x = (*splitString)[index-1][2:3]
				(*splitString)[index] = x + (*splitString)[index]
				(*splitString)[index-1] = (*splitString)[index-1][0:2]
			} else if index != 0 && len((*splitString)[index-1]) <= 3 && len((*splitString)[index-1]) > 2 && len((*splitString)[index]) > 2 && (*splitString)[index-1][2:3] == "0" {
				var x string
				x = (*splitString)[index][0:1]
				(*splitString)[index-1] = (*splitString)[index-1] + x
				(*splitString)[index] = (*splitString)[index][1:]
			}
		}
	}
	return splitString
}

func finishUp(splitString *[]string) *[]string {
	if len((*splitString)[len(*splitString)-1]) < 2 && len((*splitString)[len(*splitString)-2]) < 4 {
		(*splitString)[len(*splitString)-2] += (*splitString)[len(*splitString)-1]
		*splitString = (*splitString)[0 : len(*splitString)-1]
	} else if len((*splitString)[len(*splitString)-2]) > 2 && len((*splitString)[len(*splitString)-1]) < 2 {
		strLength := len((*splitString)[len(*splitString)-2])
		(*splitString)[len(*splitString)-1] = (*splitString)[len(*splitString)-2][strLength-1:strLength] + (*splitString)[len(*splitString)-1]
		(*splitString)[len(*splitString)-2] = (*splitString)[len(*splitString)-2][0 : strLength-1]
	}
	return splitString
}

func countZeros(strlist *[]string) int {
	var returnValue = 0
	for _, element := range *strlist {
		if element[0:1] == "0" {
			returnValue++
		}
	}
	return returnValue
}

func requestExamples() string {
	url := "https://bwinf.de/fileadmin/user_upload/BwInf/2019/38/1._Runde/Material/A2/nummern.txt"
	resp, err := http.Get(url)
	if err != nil {
		panic(err)
	}
	examples, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		panic(err)
	}
	return string(examples)
}

func main() {
	fmt.Println("===== Nummernmerker =====")
	var splitStr []string
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("What kind of test do you want to run (website, random , manual): ")
	text, _ := reader.ReadString('\n')
	if text == "website\n" {
		fmt.Println("Pulling content from the BWINF website ...")
		splitStr = strings.Split(requestExamples(), "\n")
		splitStr = splitStr[0 : len(splitStr)-1]

	} else if text == "random\n" {
		fmt.Print("Generating number with 1000 digits")
		splitStr = make([]string, 1)
		splitStr[0] = generateRandomNumberString(1000)
	} else if text == "manual\n" {
		reader := bufio.NewReader(os.Stdin)
		fmt.Print("Your Number: ")
		text, _ := reader.ReadString('\n')
		splitStr = make([]string, 1)
		splitStr[0] = text[0 : len(text)-2]
	}

	var returnValue, split *[]string

	for index, num := range splitStr {
		fmt.Println(" *** Number", index, " *** ")
		split = splitString(num)
		fmt.Println("String has ", countZeros(split), " at the beginning of a block")
		returnValue = transformBlocks(split)
		returnValue = finishUp(returnValue)
		fmt.Println("After transformation only ", countZeros(returnValue))
		fmt.Println(returnValue, "\n =======================================================")
	}
}
