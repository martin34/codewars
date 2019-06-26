s =   "seeyouatnoon"
key = "spyspyspyspyspy"
res = ""

for i,e in enumerate(s):
    small_letters_ascii_offset = 97
    number_in_alphabet = ord(e) - small_letters_ascii_offset
    k_number_in_alphabet = ord(key[i]) - small_letters_ascii_offset
    v = (number_in_alphabet + k_number_in_alphabet) % 26
    print("v: {}, k: {} = {}".format(number_in_alphabet, k_number_in_alphabet, v))
    encoded_ascii = v + small_letters_ascii_offset
    res += str(chr(encoded_ascii))

print(res)
