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

func generate_random_number_string(size int) string {
	var str string = ""
	for i := 0; i < size; i++ {
		str += strconv.Itoa(rand.Intn(10))
	}
	return str
}

func split_string(str string) *[]string {
	var size int = int(math.Ceil(float64((len(str) - 1) / 3)))
	var return_value []string = make([]string, size+1)
	for i := 0; i < int(math.Floor(float64(len(str)/3))); i++ {
		x := string(str[i*3 : (i+1)*3])
		return_value[i] = x
	}
	if len(str)%3 != 0 {
		return_value[size] = str[int(math.Floor(float64(len(str)/3)))*3:]
	}
	return &return_value
}

func transform_blocks(split_string *[]string) *[]string {
	for index, element := range *split_string {
		if element[0:1] == "0" {
			if index != 0 && len((*split_string)[index-1]) > 2 && (*split_string)[index-1][2:3] != "0" {
				var x string = (*split_string)[index-1][2:3]
				(*split_string)[index] = x + (*split_string)[index]
				(*split_string)[index-1] = (*split_string)[index-1][0:2]
			} else if index != 0 && len((*split_string)[index-1]) <= 3 && len((*split_string)[index-1]) > 2 && len((*split_string)[index]) > 2 && (*split_string)[index-1][2:3] == "0" {
				var x string
				x = (*split_string)[index][0:1]
				(*split_string)[index-1] = (*split_string)[index-1] + x
				(*split_string)[index] = (*split_string)[index][1:]
			}
		}
	}
	return split_string
}

func finish_up(split_string *[]string) *[]string{
	if len((*split_string)[len(*split_string)-1]) < 2 && len((*split_string)[len(*split_string)-2]) < 4{
		(*split_string)[len(*split_string)-2] += (*split_string)[len(*split_string)-1];
		(*split_string) = (*split_string)[0:len(*split_string)-1]
	} else if len((*split_string)[len(*split_string)-2]) > 2 && len((*split_string)[len(*split_string)-1]) < 2{
		str_length := len((*split_string)[len(*split_string)-2])
		(*split_string)[len(*split_string)-1] = (*split_string)[len(*split_string)-2][str_length-1:str_length] + (*split_string)[len(*split_string)-1];
		(*split_string)[len(*split_string)-2] = (*split_string)[len(*split_string)-2][0:str_length-1]
	}
	return split_string;
}

func count_zeros(strlist *[]string) int {
	var return_value int = 0
	for _, element := range *strlist {
		if element[0:1] == "0" {
			return_value++
		}
	}
	return return_value
}

func request_examples() string {
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
	var split_str []string
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("What kind of test do you want to run (website, random , manual): ")
	text, _ := reader.ReadString('\n')
	if text == "website\n" {
		fmt.Println("Pulling content from the BWINF website ...")
		split_str = strings.Split(request_examples(), "\n")
		split_str = split_str[0 : len(split_str)-1]

	} else if text == "random\n" {
		fmt.Print("Generating number with 1000 digits")
		split_str = make([]string, 1)
		split_str[0] = generate_random_number_string(1000)
	} else if text == "manual\n" {
		reader := bufio.NewReader(os.Stdin)
		fmt.Print("Your Number: ")
		text, _ := reader.ReadString('\n')
		split_str = make([]string, 1)
		split_str[0] = text[0 : len(text)-2]
	}

	var return_value, split *[]string;

	for index, num := range split_str {
		fmt.Println(" *** Number", index, " *** ")
		split = split_string(num)
		fmt.Println("String has ", count_zeros(split), " at the beginning of a block")
		return_value = transform_blocks(split)
		return_value = finish_up(return_value);
		fmt.Println("After transformation only ", count_zeros(return_value))
		fmt.Println(return_value, "\n =======================================================")
	}
}