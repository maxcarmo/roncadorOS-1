def check(num):
    binary = bin(num)[2:][::-1]
    for idx, bit in enumerate(binary):
        if bit == '1':
            print(idx)

text = input("Numero: ")
base = 16
check(int(text, base))