# -*- coding:utf-8 -*-
from mobius_script import *

def init():
    create_cin_xml('cart1', 's', 'status', 'waiting')
    ss()

def tl():
    create_cin_xml('cart1', 's', 'direction', 'LFT')
    create_cin_xml('cart1', 's', 'status', 'moving')
    
def tr():
    create_cin_xml('cart1', 's', 'direction', 'RGT')
    create_cin_xml('cart1', 's', 'status', 'moving')
    
def ts():
    create_cin_xml('cart1', 's', 'direction', 'STR')
    create_cin_xml('cart1', 's', 'status', 'moving')
    
def s1():
    create_cin_xml('stand1', 's', 'rail', "{'state' : 'run', 'quantity' : '1'}")
    
def s2():
    create_cin_xml('stand2', 's', 'rail', "{'state' : 'run', 'quantity' : '1'}")
    
def ss():
    create_cin_xml('stand1', 's', 'rail', "{'state' : 'stop'}")
    create_cin_xml('stand2', 's', 'rail', "{'state' : 'stop'}")
    
def cs():
    get_cin('cart1', 's', 'status')
    
def dn():
    init()
    create_cin_xml('app1', 's', 'user1/order', '{"order":2}')