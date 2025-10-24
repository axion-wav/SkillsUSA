def encode(string, shift):
    string = string.upper()
    encoded = []
    for char in string:
        if char.isalpha():
            code = ord(char) - 65
            shifted = (code + shift) % 26
            newChar = chr(shifted + 65)
            encoded.append(newChar)
        else:
            encoded.append(char)
    return ''.join(encoded)

def decode(string, shift):
    return encode(string, -shift)

running = True
while(running):
    shift = 0
    action = True

    while(True):
        print("Encode or Decode? (E/D) ")
        inp = input().upper()

        match inp:
            case "E":
                action = True
                print("Encode selected")
                break
            case "D":
                action = False
                print("Decode selected")
                break
            case _:
                continue

    while(True):
        print("Shift amount (same when decoded/encoded)")
        inp = input()

        try:
            inp = int(inp)
            shift = inp
            print("Shift amount confirmed: " + str(inp))
            break
        except ValueError:
            print("Invalid input. Please enter an integer.")
    
    print("String to encode:" if action else "String to decode:")
    string = input()
        

    match action:
        case True:
            print("Encoded: " + encode(string, shift))
        case False:
            print("Decoded: " + decode(string, shift))

    # Ask to continue or stop
    print("More? (Enter to continue, N to stop)")
    inp = input().upper()
    if inp == "N":
        running = False
    else:
        continue