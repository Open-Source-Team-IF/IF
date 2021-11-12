import requests
import json

server = "http://146.56.166.36:7579/Mobius"

# AE 생성 (xml) -- 작동 잘 되는거 확인 했음
def create_ae_xml(ae_name, aei, api):
    request_headers = {}
    request_headers['Content-Type'] = "application/vnd.onem2m-res+xml;ty=2"
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = aei
    
    request_xml = ""
    request_xml += "<m2m:ae xmlns:m2m=\"http://www.onem2m.org/xml/protocols\" rn=\"" + ae_name + "\">\n"
    request_xml += "<api>" + api + "</api>\n"
    request_xml += "<rr>false</rr>\n"
    request_xml += "</m2m:ae>"
    
    res = requests.post(server, headers=request_headers, data=request_xml)
    
    res_data = json.loads(res.text)
    
    print("Resource Code", " :: ", res.status_code)
    print(json.dumps(res_data, indent=2))
    if(res.status_code == 201):
        print("Create OK")
 
# AE 조회 (xml)
def get_ae_xml(ae_name, aei):
    request_headers = {}
    # request_headers['Accept'] = "application/json"
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = aei
    
    res = requests.get(server+'/'+ae_name, headers=request_headers)
    
    res_data = json.loads(res.text)
    
    print("Resource Code", " :: ", res.status_code)
    print(json.dumps(res_data, indent=2))
    
    return res_data
 
# AE 삭제 (xml)
def delete_ae_xml(ae_name, aei):
    request_headers = {}
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = aei
    
    res = requests.delete(server+'/'+aei, headers=request_headers)
    
    res_data = json.loads(res.text)
    
    print("Resource Code", " :: ", res.status_code)
    print(json.dumps(res_data, indent=2))
    if(res.status_code == 200):
        print("Delete OK")
