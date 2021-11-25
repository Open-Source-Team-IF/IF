from sys import stdin
N, M = 6, 2
# matrix 배열
matrix = [stdin.readline().rstrip() for _ in range(N)]
# 방문경로 배열
visited = [[0]*M for _ in range(N)]
# 좌/우/위/아래 방향 이동
dx, dy = [-1, 1, 0, 0], [0, 0, -1, 1]

# BFS 경로 탐색
# queue 방식 사용
dest_x = int(input("Dest : x "))
dest_y = int(input("Dest : y "))

queue = [(5,0)]
visited[5][0] = 1

while queue:
    x, y = queue.pop(0)

    if x == dest_x and y == dest_y:
        # 최종 경로 도착
        print(visited[x][y])
        break

    for i in range(4):
        nx = x - dx[i]
        ny = y + dy[i]
        if 0 <= nx < N and 0 <= ny < M:
            if visited[nx][ny] == 0 and matrix[nx][ny] == '1':
                visited[nx][ny] = visited[x][y] + 1
                print("x = %d, y = %d"%(nx,ny))
                queue.append((nx,ny))
