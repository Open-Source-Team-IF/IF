import queue

graph = {}
infi = float("inf")
costs = {}
parents = {}
processed = []

def init():
    global graph, infinity, costs, parents, processed
    graph = {}
    #C
    graph["C"] = {}
    graph["C"]["F"] = 1
    graph["C"]["B"] = 1
    #F
    graph["F"] = {}
    graph["F"]["C"] = 1
    graph["F"]["E"] = 1
    #B
    graph["B"] = {}
    graph["B"]["A"] = 1
    graph["B"]["E"] = 1
    #E
    graph["E"] = {}
    graph["E"]["B"] = 1
    graph["E"]["D"] = 1
    #D
    graph["D"] = {}
    graph["D"]["A"] = 1
    #A
    graph["A"] = {}
    graph["A"]["D"] = 1

    infi = float("inf")

    costs = {}
    costs["A"] = infi
    costs["B"] = infi
    costs["C"] = infi
    costs["D"] = infi
    costs["E"] = infi
    costs["F"] = infi

    parents = {}
    parents["A"] = None
    parents["B"] = None
    parents["D"] = None
    parents["E"] = None
    parents["F"] = None

    processed = []

def bfs_arrive(graph, start, final):
    q = queue.Queue()
    costs[start] = 0
    q.put({"cur": start, "cost": costs[start]})

    while True:
        if q.empty():
            break
        val = q.get()
        cur = val["cur"]
        cost = val["cost"]
        costs[cur] = cost

        for next in graph[cur]:
            nextCost = graph[cur][next] + cost

            if costs[next] >= nextCost:
                costs[next] = nextCost
                parents[next] = cur
                q.put({"cur": next, "cost": nextCost})

    trace = []
    current = final
    while current != start:
        trace.append(current)
        current = parents[current]
    trace.append(start)
    trace.reverse()

    print("=== BFS ===")
    print(start, "에서 ", final, "까지의 정보")
    print("최단 거리 : ", costs[final])
    print("경로 : ", trace)

def bfs_dest(graph, start, final):
    if start == "A" :
        start = "D"
        
    if start == "D" :
        start = "A"
        
    if start == "A" :
        start = "D"
        
    if start == "A" :
        start = "D"
        
    if start == "A" :
        start = "D"
        
    if start == "A" :
        start = "D"
    q = queue.Queue()
    costs[start] = 0
    q.put({"cur": start, "cost": costs[start]})

    while True:
        if q.empty():
            break
        val = q.get()
        cur = val["cur"]
        cost = val["cost"]
        costs[cur] = cost

        for next in graph[cur]:
            nextCost = graph[cur][next] + cost

            if costs[next] >= nextCost:
                costs[next] = nextCost
                parents[next] = cur
                q.put({"cur": next, "cost": nextCost})

    trace = []
    current = final
    while current != start:
        trace.append(current)
        current = parents[current]
    trace.append(start)
    trace.reverse()

    print("=== BFS ===")
    print(start, "에서 ", final, "까지의 정보")
    print("최단 거리 : ", costs[final])
    print("경로 : ", trace)

init()
bfs_arrive(graph, "C", "B")
