import requests

server = "http://146.56.166.36:7579/Mobius"

# AE 생성 (xml) -- 작동 잘 되는거 확인 했음
def create_ae_xml(resource_name, api):
    request_headers = {}
    request_headers['Content-Type'] = "application/vnd.onem2m-res+xml;ty=2"
    request_headers['X-M2M-RI'] = "12345"
    request_headers['X-M2M-Origin'] = resource_name
    
    request_xml = ""
    request_xml += "<m2m:ae xmlns:m2m=\"http://www.onem2m.org/xml/protocols\" rn=\"" + resource_name + "\">\n"
    request_xml += "<api>" + api + "</api>\n"
    request_xml += "<rr>false</rr>\n"
    request_xml += "</m2m:ae>"
    
    res = requests.post(server, headers=request_headers, data=request_xml)
    
    print(res.status_code)
    print(res.text)
