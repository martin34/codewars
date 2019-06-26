# Cryptography

" the art of writing or solving codes"

Goals of modern cryptography:

* Data integrity, authentication, protocols, ...
* The public-key setting
* Foundations e. g. number theory to systems e. g. distributed e-cash

Examples for usages:

* password (hashing)
* secure credit-card transations
* ecripted WiFi
* digitally signed software updates
* Bitcoins

Book recommendation: Introduction to Modern Cryptography (ISBN-13: 978-1466570269)

## Content:

1. Introduction and Classical Cryptography
1. Computational Secrecy and Principles of Modern Cryptography
1. Private-Key Encryption
1. Message Authentication Codes
1. Number Theory
1. Key Exchange and Public-Key Encryption
1. Digital Signatures

## Introduction and Classical Cryptography

Historically focused on secure communication.
Based on exchangeing a secret key in advance 
--> Private-key cryptography (also secret-key, shared-key, symmetric-key) 

Two users share secret key in advance. 
Senser encryptes message using the key before sending. 
Receiver can decode the message with the key.

Goal: Nobaody shall be able to see content, without the key.

Also applicable for encrypthing hard drive and so on.

Method needs three fundamental algorithms:

1. Generate key (Gen k)
1. Encrypte c <-- Enc<sub>k</sub>(m)
1. Decrypte m := Dec<sub>k</sub>(c)

<-- Output may be influenced by random values
:=  Deterministic output

For every encryptions Dec<sub>k</sub>(Enc<sub>k</sub>(m)) = m needs to be true

25 = 35 mod 10; 25 mod 10 = 5 = 35 mod 10

25 ≠ [35 mod 10]; 5 = [35 mod 10]

### Formal definition of simple code

Shift each letter in the alphabet by k (wrap around at the end).
--> Enc<sub>1</sub>(abc) --> bcd

* Gen: choose uniform k ∈ {0, ..., 25}
* Enc<sub>k</sub>(m<sub>1</sub>...m<sub>t</sub>): output c<sub>1</sub>...c<sub>t</sub>, where c<sub>i</sub> := [m<sub>i</sub> + k mod 26]
* Dec<sub>k</sub>(c<sub>1</sub>...c<sub>t</sub>): output m<sub>1</sub>...m<sub>t</sub> := [c<sub>i</sub> - k mod 26]

 Is this secure?
There are 26 possibilities --> easily possible to try all and choose the one, which results in proper text
If the attacker knows the encryption method. This should be always assumed.
--> The only secret is the key --> the key must be chosen random, to keep the secret **(Kerckoff's principle)**

Lession learned:
Key space must be large enough to prevent brute force attacks

We increase the key space by using an string as an key:
```
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
```
Now we have a very large key space e. g. with 14 character key 26<sup>14</sup> about 2<sup>66</sup>
But if we look at every 14th character and combine this with the plaintext letter frequencies, we can find the key. For example the most common character in the encrypted text most likely corresponds with the most frequently occouring carracter in the encrypted text. 

Lession learned:
Key space is not enough to withstand clever attacks
--> It would be nice to prove, that a code is secure
