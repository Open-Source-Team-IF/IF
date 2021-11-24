from mobius_script import *
from mobius_route import *
import time

for i in range(1, 7):

# init product
product = []
stand_list = {'당근' : '4', '코카콜라' : '3'}

# init aei
app1_aei = get_ae('app1', 'S')['m2m:ae']['aei']
cart1_aei = get_ae('cart1', 'S')['m2m:ae']['aei']
stand_aei = {}
for i in range(1, 7):
    stand_aei[str(i)] = get_ae('stand'+str(i), 'S')['m2m:ae']['aei']

# init route
init_direction()
init()
route = []

# init status
app1_status = 2
cart1_status = 'waiting'
stand_status = {}
for i in range(1, 7):
    stand_status[str(i)] = 'waiting'

create_cin_xml('app1', app1_aei, 'user1/order', '{"order":0}')
create_cin_xml('cart1', cart1_aei, 'status', 'waiting')
for i in range(1, 7):
    create_cin_xml('stand1', stand_aei[str(i)], 'rail', '0')

while(True):
    time.sleep(0.3)
    print("Looping...")
    
    get_app1_order = get_cin('app1', app1_aei, 'user1/order')['order']
    
    # 주문시
    if(get_app1_order == 0 and app1_status != '0'):
        print('Order Accepted...')
        app1_status = 0
    
        # 주문시 최초 한번만 설정 되어야 함
        # 따라서 현재 상태를 저장하는 변수를 만들어 이 변수가 바뀔 때만 아래 코드가 작동되도록 하여야 함
        # if(app1_status != '0'):
            # app1_status = '0'
        
        prd = get_cin('app1', app1_aei, 'user1/product')
        product.append(prd['product'])
        product.append(prd['product2'])
        
        create_cin_xml('app1', app1_aei, 'user1/order', '{"order":1}')
        
        init()
        route, d = get_route('START', 'C')
        # create_cin_xml('cart1', cart1_aei, 'starting', 'START')
        create_cin_xml('cart1', cart1_aei, 'status', 'moving')
        create_cin_xml('cart1', cart1_aei, 'direction', 'STR')
        
    # 주문 처리중
    if(get_app1_order == 1):
        app1_status = 1
        print('Order Proccessing...')
        
        get_cart1_status = get_cin('cart1', cart1_aei, 'status')
        
        # 카트 이동중
        if(get_cart1_status == 'moving' and cart1_status != 'moving'):
            print('Cart Moving...')
            cart1_status = 'moving'
        
        # 교차로 정차시
        if(get_cart1_status == 'get_route' and cart1_status != 'get_route'):
            print('Cart Get route...')
            cart1_status = 'get_route'
            # starting = get_cin('cart1', cart1_aei, 'starting')
            starting = route[0] # 이렇게 해도 되지 않나?
            current = route[1]
            print('Current...', current)
            
            # 장애물 파악
            closed = get_cin('server1', 'server1_aei', 'closed')
            closed_list = []
            for b in closed:
                if b == 'closed':
                    closed_list.append(b)
            
            # 경로 탐색
            M = 500
            for p in product:
                init()
                for b in closed_list:
                    close_node(b)
                    close_line(current, starting)
                
                r, d = get_route(current, stand_list[p])
                
                if(d <= M):
                    M = d
                    route = r
            print(route)
                    
            # 카트 방향 설정
            create_cin_xml('cart1', cart1_aei, 'direction', get_direction(current, starting, route[1]))
            
            # 카트 출발지 갱신
            # create_cin_xml('cart1', cart1_aei, 'starting', current)
            
            # 카트 출발
            create_cin_xml('cart1', cart1_aei, 'status', 'moving')
                
        # 진열대 정차시
        if(get_cart1_status == 'stand' and cart1_status != 'stand'):
            print('Cart Standing...')
            cart1_status = 'stand'
        
            # starting = get_cin('cart1', cart1_aei, 'starting')
            starting = route[0] # 이렇게 해도 되지 않나?
            current = route[1]
            print('Current...', current)
                
            # 장애물 파악 해야 하는가
            # 진열대에 도착한 순간 앞의 경로에 장애물이 있는지 파악해서
            # 있다면 장애물이 없어질 때 까지 정차해야 하는 코드가 필요한가?
                
            route = route[1:]
            print(route)
                
            # 목적지 도착 시
            if(len(route) == 1 and current == route[-1]):
                # END 도착 시
                if(current == 'END'):
                    # 주문 완료 알림
                    print('Order Complete...')
                    create_cin_xml('app1', app1_aei, 'user1/order', '2')
                    app1_status = 2
                    break
                    
                # 진열대에 물품 적재 신호 보냄
                create_cin_xml('cart1', cart1_aei, 'status', 'loading')
                    
                    
            # 목적지 아니면
            else:
                
                # 카트 방향 설정
                create_cin_xml('cart1', cart1_aei, 'direction', 'STR')
                
                # 카트 출발지 갱신
                # create_cin_xml('cart1', cart1_aei, 'starting', current)
                
                # 카트 출발
                create_cin_xml('cart1', cart1_aei, 'status', 'moving')
                
                
        # 진열대에서 물품 적재 대기
        if(get_cart1_status == 'loading'):
            print('Cart Loading...')
            if(cart1_status != 'loading'):
                cart1_status = 'loading'
                
                # 진열대 작동
                if(stand_status[current] != 'loading'):
                    stand_status[current] = 'loading'
                    create_cin_xml('stand'+current, stand_aei[current], 'rail', '1')
                
                # 진열대 물품 적재 완료시
                if(get_cin('stand'+current, stand_aei[current], 'rail') == '2' and status_status[current] != 'waiting'):
                    stand_status[current] = 'waiting'
                    create_cin_xml('stand'+current, stand_aei[current], 'rail', '0')
                    
                    # 장애물 파악
                    closed = get_cin('server1', 'server1_aei', 'closed')
                    closed_list = []
                    for b in closed:
                        if b == 'closed':
                            closed_list.append(b)
                    
                    # 경로 탐색
                    M = 0
                    for p in product:
                        init()
                        for b in closed_list:
                            close_node(b)
                            close_line(current, starting)
                        
                        r, d = get_route(current, stand_list[p])
                        
                        if(d >= M):
                            M = d
                            route = r
                    
                    # 카트 출발시킴
                    # 카트 방향 설정
                    create_cin_xml('cart1', cart1_aei, 'direction', 'STR')
                    # 카트 출발지 갱신
                    # create_cin_xml('cart1', cart1_aei, 'starting', current)
                    # 카트 출발
                    create_cin_xml('cart1', cart1_aei, 'status', 'moving')
               
