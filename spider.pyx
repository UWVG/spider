from urllib import request
from urllib import error
from urllib import parse

TEXT_TO_SAY = 'Hello from Python!'

cdef public int spider() except -1:
    Request_URL = 'http://www.baidu.com'
    Form_Data = {}
    Form_Data['DdtcType'] = '1'
    data = parse.urlencode(Form_Data).encode('utf-8')
    response = request.urlopen(Request_URL, data, 0.1)
    html = response.read().decode('utf-8')
    print(html)
    a = 78
    return a