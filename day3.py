def solve1(nums, n, m):
    ones = [0]*n
    for num in nums:
        for i in range(n):
            ones[i] += (num >> i)&1

    gamma = 0
    epsilon = 0
    for i, ct in enumerate(reversed(ones)):
        gamma *= 2
        epsilon *= 2
        if 2*ct > m:
            gamma += 1
        else:
            epsilon += 1 

    print(gamma)
    print(epsilon)
    print(gamma * epsilon)

def solve2(nums, n):
    o2 = nums[:]
    co2 = nums[:]
    for i in reversed(range(n)):
        if len(o2) == 1:
            break
        n_ones = 0
        for num in o2:
            n_ones += (num >> i)&1
        if 2*n_ones >= len(o2):
            o2 = list(filter(lambda x: (x >> i)&1 == 1, o2))
        else:
            o2 = list(filter(lambda x: (x >> i)&1 == 0 , o2))

    for i in reversed(range(n)):
        if len(co2) == 1:
            break
        n_ones = 0
        for num in co2:
            n_ones += (num >> i)&1
        if 2*n_ones >= len(co2):
            co2 = list(filter(lambda x: (x >> i)&1 == 0, co2))
        else:
            co2 = list(filter(lambda x: (x >> i)&1 == 1, co2))

    print(o2[0]*co2[0])

if __name__ == "__main__":
    with open("input3.txt",'r') as f:
        lines = f.readlines() 
        n = len(lines[0])-1
        m = len(lines)
    nums = [ int( l.strip('\n'), 2) for l in lines ]

    solve2(nums, n)
