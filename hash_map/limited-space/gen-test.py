import os
import random
import subprocess

# fixed seed for reproducibility
random.seed(42)

tests_root = "tests"
exe = "./result"   # temporary executable
cpp_file = "output_gen.cpp"

capacity = 8

# test folders and number of commands
random_tests = {
    "test5": 100,
    "test6": 200,
    "test7": 500,
    "test8": 1000,
}

hardcoded_tests = {
    "test1": [
        "fifo",
        "3",
        "INS,a,1",
        "INS,b,2",
        "INS,c,3",
        "INS,d,4"
    ],
    "test2": [
        "lru",
        "3",
        "INS,a,1",
        "INS,b,2",
        "INS,c,3",
        "FIND,a",
        "INS,d,4"
    ],
    "test3": [
        "fifo",
        "5",
        "INS,a,1",
        "FIND,a",
        "INS,b,2",
        "FIND,b",
        "INS,c,3",
        "INS,d,4",
        "INS,e,5",
        "INS,f,6"
    ],
    "test4": [
        "lru",
        "5",
        "DEL,f",
        "INS,a,1",
        "INS,b,2",
        "INS,a,5",
        "INS,c,3",
        "INS,d,4"
    ]
}


def gen_commands(n):
    cmds = []
    keys = [chr(i) for i in range(97, 123)]  # a-z
    inserted = set()

    # First 50%: guaranteed inserts
    for _ in range(n // 2):
        key = random.choice(keys)
        value = random.randint(1, 1000)
        cmds.append(f"INS,{key},{value}")
        inserted.add(key)

    # Remaining 50%: random mix
    for _ in range(n - n // 2):
        cmd_type = random.choice(["INS", "DEL", "FIND"])
        key = random.choice(keys)

        if cmd_type == "INS":
            value = random.randint(1, 1000)
            cmds.append(f"INS,{key},{value}")
            inserted.add(key)

        elif cmd_type == "DEL":
            if inserted:
                k = random.choice(list(inserted))
                cmds.append(f"DEL,{k}")
                inserted.discard(k)
            else:
                # fallback: insert instead
                value = random.randint(1, 1000)
                cmds.append(f"INS,{key},{value}")
                inserted.add(key)

        elif cmd_type == "FIND":
            if inserted:
                k = random.choice(list(inserted))
                cmds.append(f"FIND,{k}")
            else:
                cmds.append(f"FIND,{key}")

    return cmds


def main():
    # 1. Hardcoded tests (test1..test4)
    for folder, lines in hardcoded_tests.items():
        test_dir = os.path.join(tests_root, folder)
        os.makedirs(test_dir, exist_ok=True)

        input_path = os.path.join(test_dir, "input.txt")
        with open(input_path, "w") as f:
            for line in lines:
                f.write(line + "\n")

        #print(f"Created hardcoded {input_path}")

    # 2. Random tests (test5..test8)
    for folder, ncmds in random_tests.items():
        test_dir = os.path.join(tests_root, folder)
        os.makedirs(test_dir, exist_ok=True)

        input_path = os.path.join(test_dir, "input.txt")

        # randomly choose policy
        policy = random.choice(["fifo", "lru"])

        with open(input_path, "w") as f:
            f.write(policy + "\n")
            f.write(str(capacity) + "\n")
            for cmd in gen_commands(ncmds):
                f.write(cmd + "\n")

        #print(f"Generated {ncmds} commands in {input_path} with policy={policy}")

    # 3. Compile result.cpp
    #print("Compiling result.cpp...")
    compile_result = subprocess.run(
        ["g++", "-std=c++17", cpp_file, "-o", exe]
    )
    if compile_result.returncode != 0:
        print("❌ Compilation failed")
        return

    # 4. Run executable (writes all output.txt files)
    subprocess.run([exe])

    # 5. Delete the executable after use
    os.remove(exe)
    print("Generated Test Cases")


if __name__ == "__main__":
    main()

