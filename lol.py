import string

def int_to_str(n):
    result = []
    while n > 0:
        n -= 1
        result.append(chr(n % 26 + ord('A')))
        n //= 26
    return ''.join(result[::-1])


def generate_lines():
    lines = ["disable_output\n"]
    for j in range(1, 10):
        print(j)
        for i in range(1, 999):
            lines.append(f'{int_to_str(j)}{i}={int_to_str(j)}{i+1}')
        lines.append(f'{int_to_str(j)}999={int_to_str(j+1)}1')
    lines.append("enable_output\n")
    
    return lines

lines = generate_lines()
with open('test.txt', 'w') as f:
    for line in lines:
        f.write(line + '\n')