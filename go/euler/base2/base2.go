// Project Euler
// base2.go
package base2

type Base2 []byte

// New returns the binary sequence of x with a minimum amount of bits. If
// bits is zero, the sequence's length is automatically decided.
// Otherwise, the result is left-padded with zeros to satisfy the
// requested amount of bits.
// e.g.
// New(5,0) -> {101}
// New(5,7) -> {0000101}
func New(x, bits int) Base2 {
	if x == 0 {
		return Base2{0}
	} else if bits < Len(x) {
		bits = Len(x)
	}
	
	bin := make(Base2, bits)
	i := bits-1
	for x > 0 {
		if x%2 != 0 {
			bin[i] = 1
		}
		x = x >> 1
		i--
	}
	return bin
}

// Int returns b as a decimal integer.
func (b Base2) Int() int {
	x := 0
	m := 1
	for i:=len(b)-1; i>=0; i-- {
		x += int(b[i])*m
		m *= 2
	}
	return x
}

// Byte returns b as a decimal byte.
func (b Base2) Byte() byte {
	var x byte
	var m byte = 1
	for i:=len(b)-1; i>=0; i-- {
		x += b[i]*m
		m *= 2
	}
	return x
}


// Len returns the minimum amount of bits needed to represent x in
// binary.
func Len(x int) int {
	bits := 0
	y := x
	for y > 0 {
		y = y >> 1
		bits++
	}
	return bits
}


// Xor performs a XOR b and returns the result. Note that a and b don't
// have to have the same length.
func (b Base2) Xor(a Base2) Base2 {
	c := make(Base2, max(len(a), len(b)))
	i := len(a)-1 					// a's index
	j := len(b)-1 					// b's index
	k := len(c)-1 					// c's index
	for k >= 0 {
		if i >= 0 && j >= 0 {		// in both bins
			if a[i] != b[j] {
				c[k] = 1
			}
		} else if i >= 0 && j < 0 {	// still in a
			if a[i] == 1 {
				c[k] = 1
			}
		} else if i < 0 && j >= 0 {	// still in b
			if b[j] == 1 {
				c[k] = 1
			}
		}
		i--
		j--
		k--
	}
	return c
}


// max returns the higher of two integers.
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
