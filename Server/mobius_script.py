import requests
import json

server = "http://146.56.166.36:7579/Mobius"

# AE 생성 (xml) -- 작동 잘 되는거 확인 했음
def create_ae_xml(ae, aei, api):
    request_headers = {}
    request_headers['Content-Type'] = "application/vnd.onem2m-res+xml;ty=2"
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = aei
    
    request_xml = ""
    request_xml += "<m2m:ae xmlns:m2m=\"http://www.onem2m.org/xml/protocols\" rn=\"" + ae + "\">\n"
    request_xml += "<api>" + api + "</api>\n"
    request_xml += "<rr>false</rr>\n"
    request_xml += "</m2m:ae>"
    
    res = requests.post(server, headers=request_headers, data=request_xml)
    
    res_data = json.loads(res.text)
    
    print("Resource Code", " :: ", res.status_code)
    print(json.dumps(res_data, indent=2))
    if(res.status_code == 201):
        print("Create OK")
 
# AE 조회
def get_ae(ae, aei):
    request_headers = {}
    # request_headers['Accept'] = "application/json"
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = aei
    
    res = requests.get(server+'/'+ae, headers=request_headers)
    
    res_data = json.loads(res.text)
    
    print("Resource Code", " :: ", res.status_code)
    print(json.dumps(res_data, indent=2))
    
    return res_data
 
# AE 삭제 (xml)
def delete_ae_xml(ae, aei):
    request_headers = {}
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = aei
    
    res = requests.delete(server+'/'+ae, headers=request_headers)
    
    res_data = json.loads(res.text)
    
    print("Resource Code", " :: ", res.status_code)
    print(json.dumps(res_data, indent=2))
    if(res.status_code == 200):
        print("Delete OK")
    
# CNT 생성 (xml)    
def create_cnt_xml(ae, aei, cnt):
    request_headers = {}
    request_headers['Content-Type'] = "application/vnd.onem2m-res+xml;ty=3"
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = aei
    
    request_xml = ""
    request_xml += "<m2m:cnt xmlns:m2m=\"http://www.onem2m.org/xml/protocols\" rn=\"" + cnt + "\">"
    request_xml += "</m2m:cnt>"
    
    res = requests.post(server+'/'+ae, headers=request_headers, data=request_xml)
    
    res_data = json.loads(res.text)
    
    print("Resource Code", " :: ", res.status_code)
    print(json.dumps(res_data, indent=2))
    if(res.status_code == 201):
        print("Create OK")   

# CNT 조회
def get_cnt(ae, aei, cnt):
    request_headers = {}
    # request_headers['Accept'] = "application/json"
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = aei
    
    res = requests.get(server+'/'+ae+'/'+cnt, headers=request_headers)
    
    res_data = json.loads(res.text)
    
    print("Resource Code", " :: ", res.status_code)
    print(json.dumps(res_data, indent=2))
    
    return res_data        
        
# CNT 삭제 (xml)
def delete_cnt_xml(ae, aei, cnt):
    request_headers = {}
    request_headers['locale'] = "ko"
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = aei
    
    res = requests.delete(server+'/'+ae+'/'+cnt, headers=request_headers)
    
    res_data = json.loads(res.text)
    
    print("Resource Code", " :: ", res.status_code)
    print(json.dumps(res_data, indent=2))
    if(res.status_code == 200):
        print("Delete OK")
        
# cin 생성 (xml)
def create_cin_xml(ae, aei, cnt, data):
    request_headers = {}
    request_headers['Content-Type'] = "application/vnd.onem2m-res+xml;ty=4"
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = aei
    
    request_xml = ""
    request_xml += "<m2m:cin xmlns:m2m=\"http://www.onem2m.org/xml/protocols\">"
    request_xml += "<con>" + data + "</con>"
    request_xml += "</m2m:cin>"
    
    res = requests.post(server+'/'+ae+'/'+cnt, headers=request_headers, data=request_xml)
    
    res_data = json.loads(res.text)
    
    print("Resource Code", " :: ", res.status_code)
    print(json.dumps(res_data, indent=2))
    if(res.status_code == 201):
        print("Create OK")   

# cin 조회
def get_cin(ae, aei, cnt):
    request_headers = {}
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = aei
    
    res = requests.get(server+'/'+ae+'/'+cnt+'/la', headers=request_headers)
    
    res_data = json.loads(res.text)
    
    print("Resource Code", " :: ", res.status_code)
    print("Con", " :: ", res_data['m2m:cin']['con'])
    # print(json.dumps(res_data, indent=2))
    
    return res_data['m2m:cin']['con']
