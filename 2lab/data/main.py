import random
import datetime

def generate_record():
    type_room = random.choice(["primary", "secondary"])
    address = ''.join(random.choices("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", k=5))
    square = random.randint(50, 20000)  
    rooms_quantity = random.randint(1, 10)  
    square_cost = random.randint(10, 1000)  
    if type_room == "primary":
        trim = random.choice([0, 1]) 
        return f"{type_room} {address} {square} {rooms_quantity} {square_cost} {trim}"
    else:
        build_year = datetime.date(random.randint(1900, 2023), random.randint(1, 12), random.randint(1, 28)).strftime("%d.%m.%Y")
        prev_owners = random.randint(1, 1000)  
        pets = random.choice([0, 1]) 
        return f"{type_room} {address} {square} {rooms_quantity} {square_cost} {build_year} {prev_owners} {pets}"

def generate_records(count):
    return [generate_record() for _ in range(count)]

def save_to_file(filename, records):
    with open(filename, "w") as f:
        for record in records:
            f.write(record + "\n")

sizes = [10, 100, 250, 500, 1000]

for size in sizes:
    records = generate_records(size)
    save_to_file(f"records_{size}.txt", records)

print("Генерация записей завершена.")