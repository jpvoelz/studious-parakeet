import math

# recursively implements Karatsuba multiplication
def karatsuba(x: int, y: int) -> int:
    if x < 10 or y < 10:
        return x * y
    else:
        n = math.floor(math.log10(x)) + 1
        n_2 = math.ceil(n/2)
        a = int(x/10**n_2)
        b = x - 10**n_2*a
        c = int(y/10**n_2)
        d = y - 10**n_2*c

        one = karatsuba(a, c)
        two = karatsuba(b, d)
        three = karatsuba(a + b, c + d) - one - two
        return (10**(2*n_2) * one) + (10**n_2 * three) + two
    

num1 = 3141592653589793238462643383279502884197169399375105820974944592
num2 = 2718281828459045235360287471352662497757247093699959574966967627

print(karatsuba(num1, num2))