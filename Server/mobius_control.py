from mobius_script import *
from mobius_route import *

# init product
product = {}

# init route
init_direction()
init()
route = {}

while(True):
    # 주문시
    if(get_cin_json('app1', app1_aei, 'user1/order')['order'] == '0'):
        product = get_cin_json('app1', app1_aei, 'user1/product')
        create_cin_xml('app1', app1_aei, 'user1/order', 1)
        
    # 주문 처리중
    if(get_cin_json('app1', app1_aei, 'order')['order'] == '1'):
        if(get_cin_xml('cart1', cart1_aei, 'status') == 'get_route'):
            starting = get_cin_xml('cart1', cart1_aei, 'staring')
            loc 