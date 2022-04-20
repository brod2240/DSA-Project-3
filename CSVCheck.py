from itertools import zip_longest
import numpy as np
import pandas as pd
import os as os
import names
import random
import csv

numArtist = set()
numList = []
randomName = set()


def loadCSV():
    dir_path = r'/Users/mayasingh/PycharmProjects/CSVCheck/CSV'
    count = 0
    # Iterate directory
    for path in os.listdir(dir_path):
        # check if current path is a file
        if os.path.isfile(os.path.join(dir_path, path)):
            count += 1

    print(count)

    for i in range(count):
        data = pd.read_csv(r'/Users/mayasingh/PycharmProjects/CSVCheck/CSV/file'+str(i) + '.csv', delimiter=',', usecols=["From Artist", "To Artist"])
        for x in data["From Artist"]:
            numArtist.add(x)
            numList.append(x)
        for y in data["To Artist"]:
            numArtist.add(y)
            numList.append(y)


def makeCSV():
    print("CSV")
    while len(randomName) != (100000 - len(numArtist)):
        randomName.add(names.get_full_name())
        print(len(randomName))

    column_size = int(len(randomName)/2)

    # initialize the middle index with the length of first half
    middle_index = int((len(randomName)/2 - 1))

    randomList = list(randomName)

    # Split the list from starting index upto middle index in first half
    from_column = randomList[:middle_index]

    # Split the list from middle index index upto the last index in second half
    to_column = randomList[middle_index:]

    weight_column = []
    for i in range(column_size):
        weight_column.append(random.randint(0, 100))

    d = [from_column, to_column, weight_column]
    export_data = zip_longest(*d, fillvalue='')

    with open('supplement.csv', 'w', encoding='UTF8', newline='') as f:
        csv.register_dialect("custom", delimiter=",", skipinitialspace=True)
        wr = csv.writer(f, dialect="custom")
        wr.writerow(('From Artist', 'To Artist', 'Weight'))
        wr.writerows(export_data)


def main():
    loadCSV()
    makeCSV()
    print(len(numArtist))
    print(len(numList))


main()
