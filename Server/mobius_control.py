from mobius_script import *
from mobius_route import *

# init product
product = []
stand_list = {'당근' : '4', '콜라' : '2'}

# init aei
app1_aei = get_ae('app1', 'S')['m2m:ae']['aei']
cart1_aei = get_ae('cart1', 'S')['m2m:ae']['aei']
stand_aei = {}

# init route
init_direction()
init()
route = []

# init status
app1_status = '2'
cart1_status = 'waiting'
stand_status = {}
stand_status['2'] = 'waiting'
stand_status['4'] = 'waiting'
# stand2_status = 'waiting'
# stand4_status = 'waiting'

while(True):
    # 주문시
    if(get_cin('app1', app1_aei, 'user1/order')['order'] == '0' and app1_status != '0'):
        app1_status = '0'
    
        # 주문시 최초 한번만 설정 되어야 함
        # 따라서 현재 상태를 저장하는 변수를 만들어 이 변수가 바뀔 때만 아래 코드가 작동되도록 하여야 함
        # if(app1_status != '0'):
            # app1_status = '0'
        print('Order Accepted...')
        prd = get_cin('app1', app1_aei, 'user1/product')
        product.append(prd['product'])
        product.append(prd['product2'])
        
        create_cin_xml('app1', app1_aei, 'user1/order', '1')
        
        init()
        route = get_route('START', 'C')
        # create_cin_xml('cart1', cart1_aei, 'starting', 'START')
        create_cin_xml('cart1', cart1_aei, 'direction', 'STR')
        
    # 주문 처리중
    if(get_cin('app1', app1_aei, 'order')['order'] == '1' and app1_status != '1'):
        print('Order Proccessing...')
        app1_status = '1'
        
        # 카트 이동중
        if(get_cin('cart1', cart1_aei, 'status') == 'moving' and cart1_status != 'moving'):
            cart1_status = 'moving'
        
        # 교차로 정차시
        if(get_cin('cart1', cart1_aei, 'status') == 'get_route' and cart1_status != 'get_route'):
            cart1_status = 'get_route'
            # starting = get_cin('cart1', cart1_aei, 'starting')
            starting = route[0] # 이렇게 해도 되지 않나?
            current = route[1]
            print('Current...', current)
            
            # 장애물 파악
            # 장애물 = get_cin('server1', 'server1_aei', '장애물')
            # busy_list = []
            # for b in 장애물:
                # if b == 'busy':
                # busy_list.append(b)
            
            # 경로 탐색
            M = 0
            for p in product:
                init()
                for b in busy_list:
                    close_node(b)
                
                r, d = get_route(current, stand_list[p])
                
                if(d >= M):
                    M = d
                    route = r
                    
            # 카트 방향 설정
            create_cin_xml('cart1', cart1_aei, 'direction', get_direction(current, starting, route[1]))
            
            # 카트 출발지 갱신
            # create_cin_xml('cart1', cart1_aei, 'starting', current)
            
            # 카트 출발
            create_cin_xml('cart1', cart1_aei, 'status', 'moving')
                
        # 진열대 정차시
        if(get_cin('cart1', cart1_aei, 'status') == 'stand' and cart1_status != stand):
            cart1_status = 'stand'
        
            # starting = get_cin('cart1', cart1_aei, 'starting')
            starting = route[0] # 이렇게 해도 되지 않나?
            current = route[1]
            print('Current...', current)
                
            # 장애물 파악 해야 하는가
            # 진열대에 도착한 순간 앞의 경로에 장애물이 있는지 파악해서
            # 있다면 장애물이 없어질 때 까지 정차해야 하는 코드가 필요한가?
                
            route = route[1:]
                
            # 목적지 도착 시
            if(len(route) == 1 and current == route[-1]):
                # END 도착 시
                if(current == 'END'):
                    # 주문 완료 알림
                    print('Order Complete...')
                    create_cin_xml('app1', app1_aei, 'user1/order', '2')
                    app1_status = '2'
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
        if(get_cin('cart1', cart1_aei, 'status') == 'loading'):
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
                    
                    # 경로 재계산
                    
                    
                    # 카트 출발시킴
                    # 카트 방향 설정
                    create_cin_xml('cart1', cart1_aei, 'direction', 'STR')
                    # 카트 출발지 갱신
                    # create_cin_xml('cart1', cart1_aei, 'starting', current)
                    # 카트 출발
                    create_cin_xml('cart1', cart1_aei, 'status', 'moving')
                
                
                
            
