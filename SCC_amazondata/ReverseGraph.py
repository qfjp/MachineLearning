# Yiying Wang 10-9-2015
# Function: create a reverse graph for a directed graph 
# Input: amazon0302.txt
# Output: amazon0302.adjacencyList.reverse.txt



def EdgeToAdjencyList(edge, n): # edge is a list of list
    AdjencyList = {}
    for i in range(0,n+1):
        AdjencyList[i] = []
    
    for i in range(0, len(edge)):
        AdjencyList[edge[i][0]].append(edge[i][1])
    return AdjencyList


text_file = open('amazon0302.txt', 'r')
lines = text_file.readlines()
edge = []
n = 262110
for i in range(0, len(lines)):
	new_line = lines[i].strip().split()
	tail = int(new_line[1])
	head = int(new_line[0])
	edge.append([tail, head])
graph = EdgeToAdjencyList(edge, n+1)
for i in range(0,n+1):
	print i,
	for item in graph[i]:
		print item,
	print \