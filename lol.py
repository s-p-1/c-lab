import string
def int_to_str(n):
    result = []
    while n > 0:
        n -= 1
        result.append(chr(n % 26 + ord('A')))
        n //= 26
    return ''.join(result[::-1])


def generate_lines_equal():
    lines = ["disable_output\n"]
    for j in range(1, 100):
        print(j)
        for i in range(1, 999):
            lines.append(f'{int_to_str(j)}{i}={int_to_str(j)}{i+1}')
        lines.append(f'{int_to_str(j)}999={int_to_str(j+1)}1')
    lines.append("enable_output\n")
    
    return lines

def generate_lines_Sum():
    lines = ["disable_output"]
    for j in range(1, 2):
        print(j)
        for i in range(1, 100):
            lines.append(f'{int_to_str(j)}{i}=SUM({int_to_str(j)}{i+1}:ZZZ999)')
        lines.append(f'{int_to_str(j)}999={int_to_str(j+1)}1')
    lines.append("enable_output\nq\n")
    
    return lines

def generate_lines_Max():
    lines = ["disable_output"]
    for j in range(1, 5):
        print(j)
        for i in range(1, 999):
            lines.append(f'{int_to_str(j)}{i}=MAX({int_to_str(j)}{i+1}:ZZZ999)')
        lines.append(f'{int_to_str(j)}999={int_to_str(j+1)}1')
    lines.append("enable_output\nq\n")
    
    return lines

def generate_small_sums():
    lines = ["disable_output"]
    for j in range(1, 2):
        print(j)
        for i in range(1, 100):
            lines.append(f'{int_to_str(j)}{i}=SUM({int_to_str(j)}{i+1}:ZZ{i+100})')
        lines.append(f'{int_to_str(j)}999={int_to_str(j+1)}1')
    lines.append("enable_output\nq\n")
    return lines

lines = generate_lines_equal()
with open('test.txt', 'w') as f:
    for line in lines:
        f.write(line + '\n')