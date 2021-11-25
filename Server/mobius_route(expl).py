import queue

#기본 값 초기화

graph = {}
costs = {}
parents = {}
direction = {}
infi = float('inf')

#이동 방향 설정
#LFT = left , STR = straight, RGT = right
def init_direction():
    #A
    direction['A'] = {}
    direction['A']['1'] = {}
    direction['A']['1']['D'] = 'LFT'
    direction['A']['1']['2'] = 'STR'
    direction['A']['2'] = {}
    direction['A']['2']['1'] = 'STR'
    direction['A']['2']['D'] = 'RGT'
    direction['A']['D'] = {}
    direction['A']['D']['1'] = 'RGT'
    direction['A']['D']['2'] = 'LFT'
    #B
    direction['B'] = {}
    direction['B']['2'] = {}
    direction['B']['2']['3'] = 'STR'
    direction['B']['2']['E'] = 'LFT'
    direction['B']['3'] = {}
    direction['B']['3']['2'] = 'STR'
    direction['B']['3']['E'] = 'RGT'
    direction['B']['E'] = {}
    direction['B']['E']['2'] = 'RGT'
    direction['B']['E']['3'] = 'LFT'
    #C
    direction['C'] = {}
    direction['C']['START'] = {}
    direction['C']['START']['3'] = 'STR'
    direction['C']['START']['F'] = 'RGT'
    direction['C']['3'] = {}
    direction['C']['3']['START'] = 'STR'
    direction['C']['3']['F'] = 'LFT'
    direction['C']['F'] = {}
    direction['C']['F']['START'] = 'LFT'
    direction['C']['F']['3'] = 'RGT'
    #D
    direction['D'] = {}
    direction['D']['4'] = {}
    direction['D']['4']['5'] = 'STR'
    direction['D']['4']['A'] = 'RGT'
    direction['D']['5'] = {}
    direction['D']['5']['4'] = 'STR'
    direction['D']['5']['A'] = 'LFT'
    direction['D']['A'] = {}
    direction['D']['A']['4'] = 'LFT'
    direction['D']['A']['5'] = 'RGT'
    #E
    direction['E'] = {}
    direction['E']['5'] = {}
    direction['E']['5']['6'] = 'STR'
    direction['E']['5']['B'] = 'RGT'
    direction['E']['6'] = {}
    direction['E']['6']['5'] = 'STR'
    direction['E']['6']['B'] = 'LFT'
    direction['E']['B'] = {}
    direction['E']['B']['5'] = 'LFT'
    direction['E']['B']['6'] = 'RGT'
    #F
    direction['F'] = {}
    direction['F']['6'] = {}
    direction['F']['6']['END'] = 'STR'
    direction['F']['6']['C'] = 'RGT'
    direction['F']['END'] = {}
    direction['F']['END']['C'] = 'LFT'
    direction['F']['END']['6'] = 'STR'
    direction['F']['C'] = {}
    direction['F']['C']['6'] = 'LFT'
    direction['F']['C']['END'] = 'RGT'

#그래프(카트가 이동가능한 경로) 설정
def init_graph():
    #START
    graph['START'] = {}
    graph['START']['C'] = 1
    #END
    graph['END'] = {}
    graph['END']['F'] = 1

    #A
    graph['A'] = {}
    graph['A']['1'] = 1
    graph['A']['2'] = 1
    graph['A']['D'] = 1
    #B
    graph['B'] = {}
    graph['B']['2'] = 1
    graph['B']['3'] = 1
    graph['B']['E'] = 1
    #C
    graph['C'] = {}
    graph['C']['3'] = 1
    graph['C']['START'] = 1
    graph['C']['F'] = 1
    #D
    graph['D'] = {}
    graph['D']['4'] = 1
    graph['D']['5'] = 1
    graph['D']['A'] = 1
    #E
    graph['E'] = {}
    graph['E']['B'] = 1
    graph['E']['5'] = 1
    graph['E']['6'] = 1
    #F
    graph['F'] = {}
    graph['F']['END'] = 1
    graph['F']['C'] = 1
    graph['F']['6'] = 1
    
    #1
    graph['1'] = {}
    graph['1']['4'] = 1
    graph['1']['A'] = 1
    #2
    graph['2'] = {}
    graph['2']['A'] = 1
    graph['2']['B'] = 1
    #3
    graph['3'] = {}
    graph['3']['B'] = 1
    graph['3']['C'] = 1
    #4
    graph['4'] = {}
    graph['4']['1'] = 1
    graph['4']['D'] = 1
    #5
    graph['5'] = {}
    graph['5']['D'] = 1
    graph['5']['E'] = 1
    #6
    graph['6'] = {}
    graph['6']['E'] = 1
    graph['6']['F'] = 1

#간선 및 카트가 들릴 수 있는 곳의 값 설정
def init_costs():
    #init costs
    costs['A'] = infi
    costs['B'] = infi
    costs['C'] = infi
    costs['D'] = infi
    costs['E'] = infi
    costs['F'] = infi
    costs['START'] = infi
    costs['END'] = infi
    costs['1'] = infi
    costs['2'] = infi
    costs['3'] = infi
    costs['4'] = infi
    costs['5'] = infi
    costs['6'] = infi

#부모노드는 사용하지 않도록 초기화
def init_parents():
    #init parents
    parents['A'] = None
    parents['B'] = None
    parents['C'] = None
    parents['D'] = None
    parents['E'] = None
    parents['F'] = None
    parents['START'] = None
    parents['END'] = None
    parents['1'] = None
    parents['2'] = None
    parents['3'] = None
    parents['4'] = None
    parents['5'] = None
    parents['6'] = None

#그래프, 간선, 부모노드 초기화    
def init():
    # init_direction()
    init_graph()
    init_costs()
    init_parents()

#특정 업무로 인해 카트가 해당 경로를 이용할 수 없을때
#간선값에 500 가중치를 줘서 나중순위로 미룸
def close_node(node):
    for i in graph[node]:
        graph[node][i] = 500
        graph[i][node] = 500

#노드값에 500 가중치를 줘서 나중순위로 미룸
def close_line(node1, node2):
    graph[node1][node2] = 500
    graph[node2][node1] = 500

#방향 파악    
def get_direction(n, s, d):
    if n in ['A', 'B', 'C', 'D', 'E', 'F']:
        return direction[n][s][d]
    else:
        return 'STR'

#메인함수(start - final 이동 시 최종 카트 이동경로 반환)
def get_route(start, final):
    q = queue.Queue()
    costs[start] = 0
    q.put({'cur': start, 'cost': costs[start]})

    while True:
        if q.empty():
            break
        val = q.get()
        cur = val['cur']
        cost = val['cost']
        costs[cur] = cost

        for next in graph[cur]:
            nextCost = graph[cur][next] + cost

            if costs[next] >= nextCost:
                costs[next] = nextCost
                parents[next] = cur
                q.put({'cur': next, 'cost': nextCost})

    trace = []
    current = final
    while current != start:
        trace.append(current)
        current = parents[current]
    trace.append(start)
    trace.reverse()

    return trace, costs[final]
