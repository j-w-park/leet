package main

import (
	"fmt"
	"math"
	"math/rand"
	"sort"
)

func generateIntegers(maxLength int) []int {
	bound := int(math.Pow10(2))
	l := rand.Intn(maxLength)
	res := make([]int, 0, l)
	for i := 0; i < l; i++ {
		res = append(res, rand.Intn(1+2*bound)-bound)
	}
	sort.Slice(res, func(i, j int) bool { return res[i] < res[j] })
	return res
}

func getMedian(nums []int) float64 {
	l := len(nums)
	if l == 0 {
		return 0
	}
	if l%2 == 0 {
		return float64(nums[l/2-1]+nums[l/2]) / 2
	} else {
		return float64(nums[l/2])
	}
}

func merge(nums1 []int, nums2 []int) []int {
	merged := make([]int, 0, len(nums1)+len(nums2))
	for len(nums1)+len(nums2) > 0 {
		var (
			n1 *int
			n2 *int
		)
		if len(nums1) > 0 {
			n1 = &nums1[0]
		}
		if len(nums2) > 0 {
			n2 = &nums2[0]
		}
		if n1 == nil {
			merged = append(merged, *n2)
			nums2 = nums2[1:]
		} else if n2 == nil {
			merged = append(merged, *n1)
			nums1 = nums1[1:]
		} else if *n1 < *n2 {
			merged = append(merged, *n1)
			nums1 = nums1[1:]
		} else {
			merged = append(merged, *n2)
			nums2 = nums2[1:]
		}
	}
	return merged
}

// func findMergedIndex(v float64, nums []int) int {
// 	if len(nums) == 0 {
// 		return 0
// 	}
// 	var i int
// 	start, end := 0, len(nums)
// 	for start < end {
// 		i = start + rand.Intn(end-start)
// 		if float64(nums[i]) < v {
// 			start = i + 1
// 		} else {
// 			end = i
// 		}
// 	}
// 	return start
// }

func findMergedIndex(i int, from, to []int) int {
	if len(to) == 0 {
		return 0
	}
	var j int
	start, end := 0, len(to)
	for start < end {
		j = start + rand.Intn(end-start)
		if to[j] < from[i] {
			start = j + 1
		} else {
			end = j
		}
	}
	return start
}

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	if len(nums1) > len(nums2) {
		nums1, nums2 = nums2, nums1 // n1 <= n2
	}
	for start, end := 0, len(nums1); // 0 <= s <= n1, 0 <= e <= n1
	start <= end; {

		// [0, i), [i, n1)
		// [0, j), [j, n2)
		// i + j = (n1 - i) + (n2 - j)
		// -> 2*i + 2*j = n1 + n2
		// -> j = (n1 + n2)/2 - i
		// -> 0 <= (n2 - n1)/2 <= j <= (n1 + n2)/2 <= n2

		i := (start + end) / 2             // 0 <= i <= n1
		j := (len(nums1)+len(nums2))/2 - i // 0 <= j <= n2

		l1 := math.MinInt
		if 0 < i {
			l1 = nums1[i-1]
		}
		r1 := math.MaxInt
		if i < len(nums1) {
			r1 = nums1[i]
		}
		l2 := math.MinInt
		if 0 < j {
			l2 = nums2[j-1]
		}
		r2 := math.MaxInt
		if j < len(nums2) {
			r2 = nums2[j]
		}

		// fmt.Printf("i, j: %v, %v\n", i, j)
		// fmt.Printf("l1: %v\n", l1)
		// fmt.Printf("r1: %v\n", r1)
		// fmt.Printf("l2: %v\n", l2)
		// fmt.Printf("r2: %v\n", r2)

		if l1 <= r2 && l2 <= r1 {
			if (len(nums1)+len(nums2))%2 == 0 {
				return float64(max(l1, l2)+min(r1, r2)) / 2
			} else {
				return float64(min(r1, r2))
			}
		} else if l1 > r2 {
			end = i
		} else {
			start = i + 1
		}
	}
	fmt.Printf("invalid argument: %v, %v", nums1, nums2)
	return math.NaN()
}

func main() {
	success := true
	for i := 0; i < 100000; i++ {
		nums1, nums2 := generateIntegers(100), generateIntegers(100)
		if len(nums1)+len(nums2) == 0 {
			i--
			continue
		}
		merged := merge(nums1, nums2)
		ans := findMedianSortedArrays(nums1, nums2)
		expected := getMedian(merged)
		if expected != ans {
			fmt.Printf("failed: answered %v, expected %v\n", ans, expected)
			fmt.Printf("nums1: %v\n", nums1)
			fmt.Printf("nums2: %v\n", nums2)
			fmt.Printf("ans: %v\n", ans)
			success = false
			break
		}
	}

	if success {
		fmt.Println("all case passed!")
	}

	// nums1, nums2 :=
	// 	[]int{-73, -50, -37, -24, -13, 2, 7, 8, 52, 74},
	// 	[]int{-63}
	// ans := findMedianSortedArrays(nums1, nums2)
	// fmt.Printf("ans: %v\n", ans)
}

/*

a={-84, -6} 2
b={-75, -39, -25, -21, -10, -2, 2, 6, 25, 28, 37, 46, 50, 85} 15


i=(s+e)/2, j=(n(a)+n(b))/2 - i
i=0 => {}, {-84, -6}	=> {-75, -39, -25, -21, -10, -2, 2, 6}, {25, 28, 37, 46, 50, 85}	=> j=8
i=1 => {-84}, {-6}		=> {-75, -39, -25, -21, -10, -2, 2}, {6, 25, 28, 37, 46, 50, 85}	=> j=7
i=2 => {-84, -6}, {}	=> {-75, -39, -25, -21, -10, -2}, {2, 6, 25, 28, 37, 46, 50, 85}	=> j=6

s=0, e=2
i=1, j=7
{-84}, {-6}
{-75, -39, -25, -21, -10, -2, 2}, {6, 25, 28, 37, 46, 50, 85}
(l1, r1)=(a[i-1], a[i])=(-84, -6)
(l2, r2)=(b[j-1], b[j])=(2, 6)
l1 <= r2	-->	-84 <= 6	--> true
l2 <= r1	-->	2 <= -6		--> false
=> s <- i+1=2

s=2, e=2
i=2, j=6
{-84, -6}, {}
{-75, -39, -25, -21, -10, -2}, {2, 6, 25, 28, 37, 46, 50, 85}
(l1, r1)=(a[i-1], a[i])=(-6, nil)
(l2, r2)=(b[j-1], b[j])=(-2, 2)
l1 <= r2 --> -6 <= 2 --> true
l2 <= r1 --> skip
=> (max(l1, l2) + r2)/2 = (-2 + 2)/2 = 0
---


*/
