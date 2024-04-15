def bytes2matrix(text):
    return [list(text[i:i+4]) for i in range(0, len(text), 4)]
def matrix2bytes(matrix):
    return "".join([chr(n) for lst in matrix for n in lst])
matrix = [
    [99, 114, 121, 112],
    [116, 111, 123, 105],
    [110, 109, 97, 116],
    [114, 105, 120, 125],
]
print(matrix2bytes(matrix))
