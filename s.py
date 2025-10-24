def encode(string, shift):
    string = string.upper()
    encoded = []
    for char in string:
        match char:
            case " ":
                encoded.append(" ")
            case _:
                code = ord(char) - 65
                shifted = (code + shift) % 26
                newChar = chr(shifted + 65)
                encoded.append(newChar)
    return ''.join(encoded)

def decode(string, shift):
    return encode(string, -shift)

running = True
while(running):
    shift = 0
    action = True

    invalid = True
    while(invalid):
        print("Encode or Decode? (E/D) ")
        inp = input().upper()

        match inp:
            case "E":
                action = True
                print("Encode selected")
                invalid = False
                break
            case "D":
                action = False
                print("Decode selected")
                invalid = False
                break
            case _:
                continue

    while(True):
        print("Encode or Decode? (E/D) ")
        inp = input()

        if inp.isdigit():
            shift = inp
            print("Shift amount confirmed: ")
            break
        else:
            continue
    
    print("String to " + "Encode" if action else "Decode")
    string = input()
        

    match action:
        case True:
            print("Encoded: " + encode(string, shift))
        case False:
            print("Decoded " + decode(string, shift))
    
