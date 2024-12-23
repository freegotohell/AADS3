import matplotlib.pyplot as plt


sizes = [1000, 2000, 3000, 4000, 5000, 10000, 25000, 50000]
insert_comparisons = [253223, 996764, 2228650, 3954760, 6171380, 25031700, 155687000, 618293000]
insert_copies = [253223, 996764, 2228650, 3954760, 6171380, 25031700, 155687000, 618293000]

comb_comparisons = [47381, 102724, 166054, 237387, 316735, 653400, 1883410, 3766740]
comb_copies = [8826, 18429, 26736, 36702, 45507, 91656, 231483, 461634]

heap_comparisons = [25774, 55310, 86838, 118486, 151874, 323638, 874732, 1848970]
heap_copies = [35661, 76965, 121257, 165729, 212811, 455457, 1237100, 2623460]


plt.figure(figsize=(12, 6))
plt.plot(sizes, insert_comparisons, label="Insert Sort (Comparisons)", marker='o')
plt.plot(sizes, comb_comparisons, label="Comb Sort (Comparisons)", marker='o')
plt.plot(sizes, heap_comparisons, label="Heap Sort (Comparisons)", marker='o')
plt.title("Number of Comparisons")
plt.xlabel("Array Size")
plt.ylabel("Comparisons")
plt.legend()
plt.grid(True)
plt.show()


plt.figure(figsize=(12, 6))
plt.plot(sizes, insert_copies, label="Insert Sort (Copies)", marker='o')
plt.plot(sizes, comb_copies, label="Comb Sort (Copies)", marker='o')
plt.plot(sizes, heap_copies, label="Heap Sort (Copies)", marker='o')
plt.title("Number of Copies")
plt.xlabel("Array Size")
plt.ylabel("Copies")
plt.legend()
plt.grid(True)
plt.show()
