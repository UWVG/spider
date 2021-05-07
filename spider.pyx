from urllib import request
from urllib import parse
from urllib import error
from bs4 import BeautifulSoup
cdef public struct Signal:
        int status
        int Noise
        int SNR
        int RSSI
cdef public void spider(char* ip,Signal* signal):
        Request_URL = "http://"+str(ip,encoding="utf-8")+"/cgi-bin/webif/system-info.sh"
        Header = {}
        Header['User-Agent'] = 'Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/27.0.1453.94 Safari/537.36'
        Header['Authorization']='Basic YWRtaW46YWRtaW4='
        try:
                req = request.Request(Request_URL,headers=Header)
                response = request.urlopen(req)
                html = response.read().decode('utf-8')
                soup = BeautifulSoup(html,'html.parser')
                content = soup.find_all("div",class_ = 'settings')
                soup = BeautifulSoup(str(content[1]),'html.parser')
                content = soup.find_all("table",attrs={'summary':'Settings'})
                if content.__len__() < 3 :
                        signal.status = 2
                else:
                        soup = BeautifulSoup(str(content[2]),'html.parser')
                        Noise = int(str(soup.table.contents[5].contents[5].string))
                        SNR   = int(str(soup.table.contents[5].contents[7].string))
                        RSSI  = int(str(soup.table.contents[5].contents[9].string))
                        signal.status= 0
                        signal.Noise = Noise
                        signal.SNR   = SNR
                        signal.RSSI  = RSSI
        except error.HTTPError as e:
                signal.status = 1