import re
import string

def DisplayAllItems():
    print("Python display all items")
    file = open("InputFile.txt", "r") #open input file

    #prints error message if file can't be opened
    if not file:
        print("No File")
    else:
        text = file.read() #read file
        itemList = text.split("\n") #split data for each item to store in a list
        quantity = {} # declaring dictionary to store item and quantity

        for item in itemList:
            quantity[item] = quantity.get(item, 0)+1 #calculate quantity of items in the list

        outputList = ""
        for item,qty in quantity.items():
            outputList+= item + " " + str(qty) + '\n'
        print(outputList)

def SearchItem(itemName):
    file = open("InputFile.txt", "r") #open input file

    #prints error message if file can't be opened
    if not file:
        print("No File")
    else:
        text = file.read() #read file
        itemList = text.split("\n") #split data for each item to store in a list
        quantity = {} # declaring dictionary to store item and quantity

        for item in itemList:
            quantity[item] = quantity.get(item, 0)+1 #calculate quantity of items in the list
        if itemName in quantity:
            return quantity[itemName]
        else:
            return "No items"

def OutputHistogram():
    file = open("InputFile.txt", "r") #open input file

    #prints error message if file can't be opened
    if not file:
        print("No File")
    else:
        text = file.read() #read file
        itemList = text.split("\n") #split data for each item to store in a list
        quantity = {} # declaring dictionary to store item and quantity

        for item in itemList:
            quantity[item] = quantity.get(item, 0)+1 #calculate quantity of items in the list

        file2 = open("frequency.dat", "w")
        outputList = ""
        for item,qty in quantity.items():
            outputList+= item + " " + str(qty) + '\n'
        file2.write(outputList)
