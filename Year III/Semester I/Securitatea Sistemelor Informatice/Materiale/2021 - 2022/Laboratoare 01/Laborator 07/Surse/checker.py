with open("output_test.txt", "r") as rt:
    test_lines = [x.replace("\n", "") for x in rt.readlines()][1:]
    test_lines = [x.split("::::: ")[1] for x in test_lines]

with open("output.txt", "r") as r:
    lines = [x.replace("\n", "") for x in r.readlines()][1:]
    lines = [x.split("::::: ")[1] for x in lines]

used = set()
has_collisions = False
idx = 0
for line in lines:
    # print("verified line "+str(idx))
    if line in used:
       has_collisions = True
       print(line + " has a collision")
    used.add(line)
    idx += 1
if has_collisions:
    print("Collisions found")
else:
    print("No collisions found")
