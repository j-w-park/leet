package main

import "fmt"

func expandRecursive(str string, start, end int) (int, int) {
	rStart, rEnd := start, end
	if start == end && end < len(str)-1 && str[start] == str[end+1] {
		if s, e := expandRecursive(str, start, end+1); e-s > rEnd-rStart {
			rStart, rEnd = s, e
		}
	}
	if 0 < start && end < len(str)-1 && str[start-1] == str[end+1] {
		if s, e := expandRecursive(str, start-1, end+1); e-s > rEnd-rStart {
			rStart, rEnd = s, e
		}
	}
	return rStart, rEnd
}

func findLongestPalindrome(s string) string {
	start, end := 0, 0
	for i := 0; i < len(s); i++ {
		if s, e := expandRecursive(s, i, i); e-s > end-start {
			start, end = s, e
		}
	}
	return s[start : end+1]
}

func main() {
	fmt.Println(findLongestPalindrome("acaa"))
}
