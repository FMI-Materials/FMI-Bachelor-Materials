def input_int(out):
    while True:
        try:
            return int(input(out))
        except Exception:
            print("Input invalid")

