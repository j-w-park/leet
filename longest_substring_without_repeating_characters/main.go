package main

import (
	"fmt"
)

func lengthOfLongestSubstring(s string) int {
	l := len(s)
	if l < 2 {
		return l
	}
	maxLength := 0
	queue := make([]rune, 0, l)
	countTable := make(map[rune]int, l)
	for _, r := range s {
		queue = append(queue, r)
		if count, ok := countTable[r]; ok {
			countTable[r] = count + 1
		} else {
			countTable[r] = 1
		}
		for countTable[r] > 1 {
			head := queue[0]
			queue = queue[1:]
			countTable[head]--
			if countTable[head] == 0 {
				delete(countTable, head)
			}
		}
		if maxLength < len(countTable) {
			maxLength = len(countTable)
		}
	}
	return maxLength
}

// func lengthOfLongestSubstring(s string) int {
// 	res, start, visited := 0, 0, map[rune]int{}
// 	for end, char := range s {
// 		if idx, ok := visited[char]; ok && idx+1 > start {
// 			start = idx + 1
// 		}
// 		if res < end-start+1 {
// 			res = (end + 1) - start
// 		}
// 		visited[char] = end
// 	}
// 	return res
// }

func main() {
	fmt.Printf("length: %d\n", lengthOfLongestSubstring("abcaacbc"))
}
