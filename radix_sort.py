# fire radix sort with demo print
# doesn't support signed integers
# don't try it
# it will (not) support it soon (never)

def digit(num, exp, base = 10):
    digit = (num // exp) % base; return digit

def counting_sort(arr, exp, base=10):
    n = len(arr)
    if n == 0:
        return arr

    output = [0] * n
    count = [0] * base

    # count digit frequencies
    for x in arr:
        d = digit(x, exp, base)
        count[d] += 1

    # convert to prefix sums
    for i in range(1, base):
        count[i] += count[i - 1]

    # build output
    for i in range(n - 1, -1, -1):
        x = arr[i]
        d = digit(x, exp, base)
        output[count[d] - 1] = x; count[d] -= 1

    return output

def radix_sort(arr, base = 10):
    if not arr: return []
    max_val = max(arr)
    exp = 1

    while(max_val // exp > 0):
        arr = counting_sort(arr, exp, base)
        exp *= base

    return arr

def main():
    lst = [__import__('random').randint(0 if d==1 else 10**(d-1), 10**d - 1) for d in __import__('random').choices([1,2,3,4,5,6,7,8,9,10], weights=[30,20,20,15,30,40,60,80,120,300], k=100)]

    print("UNSORTED: ")
    print(lst)
    print("\nSORTED: ")
    print(radix_sort(lst))


main()