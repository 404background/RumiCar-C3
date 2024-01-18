import sys

if(len(sys.argv) == 1):
    fileName = "controller.html"
else:
    fileName = sys.argv[1]

f = open(fileName, 'r')
htmlRead = f.readlines()
htmlWrite = ""

for i in htmlRead:
    htmlWrite += i.replace("\n", "").replace("\"", "\\\"") + '\\\n' 
print(htmlWrite)

f.close()

f = open(fileName + ".tmp", 'w')
f.write(htmlWrite)
f.close()
