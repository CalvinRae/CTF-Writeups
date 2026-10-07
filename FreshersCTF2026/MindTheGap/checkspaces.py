message = open("message.txt", "r")
text = message.read()
message.close()

currentspaces=0
binary=""
counter=0
for i in range(len(text)):
	if text[i] == " ":
		currentspaces+=1
	else:
		if currentspaces>0:
			counter+=1
			binary = binary + str(currentspaces-1)
			if counter % 8 == 0:
				binary = binary +" "
			currentspaces=0
print(binary)
