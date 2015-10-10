# Yiying Wang 10-9-2015
# Given a directed graph, find all the strongly connected components

import sys 
import resource
 
#set rescursion limit and stack size limit
sys.setrecursionlimit(10 ** 6)
resource.setrlimit(resource.RLIMIT_STACK, (2 ** 29, 2 ** 30))

def read_graph(filename):
    text_file = open(filename,'r')
    graph_dict = {}
    for line in text_file:
        line = line.split()
        key = int(line[0])
        value = []
        for i in range(1, len(line)):
            value.append(int(line[i]))
        graph_dict[key] = value
    return graph_dict

graph = read_graph('amazon0302.adjacencyList.txt')
Rgraph = read_graph('amazon0302.adjacencyList.reverse.txt')


class Stack:
	def __init__(self):
		self.items = []
	def is_empty(self):
		return self.items == []
	def push(self, item):
		self.items.append(item)
	def pop(self):
		return self.items.pop()
	def peek(self):
		return self.items[len(self.items) - 1]
	def size(self):
		return len(self.items)

# the first pass to find the finishing times for each node. store in f dict
unexplored = {}
for key in Rgraph.keys():
    unexplored[key] = 1
f = {}
stack = Stack()
n = len(Rgraph)
t = 0


def DFS_Loop1(Rgraph):# calculating finishing time
    for i in range(n-1, -1,-1):
        if unexplored[i] == 1:
            DFS1(Rgraph, i)
def DFS1(Rgraph,i):
    unexplored[i] = 0
    stack.push(i)
    if len(Rgraph[i]) > 0:
        for node2 in Rgraph[i]:
            if unexplored[node2] == 1:
                DFS1(Rgraph,node2)
    global t
    t += 1
    f[t] = stack.pop()

DFS_Loop1(Rgraph)

unexplored2 = {}
for key in graph.keys():
    unexplored2[key] = 1
leader = {}
stack = Stack()
n = len(graph)
s = n
def DFS_Loop2(graph):# calculating finishing time
    for i in range(n,0,-1):
        if unexplored2[f[i]] == 1:
            global s
            s = f[i]
            DFS2(graph, s)
def DFS2(graph,v):
    unexplored2[v] = 0
    global s

    stack.push(v)
    if len(graph[v]) > 0:
        for node2 in graph[v]:
            if unexplored2[node2] == 1:
                DFS2(graph,node2)

    leader[stack.pop()] = s
            
DFS_Loop2(graph)

scc = {}
for i in range(0, n):
	if leader[i] not in scc.keys():
		scc[leader[i]] = [i]
	else:
		scc[leader[i]].append(i)
for item in scc.values():
	for number in item:
		print number,
	print ''



