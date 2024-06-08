# -*- coding: utf-8 -*-
# 引入依赖包
# pip install alibabacloud_imagerecog20190930

import os
import io
from urllib.request import urlopen
from alibabacloud_imagerecog20190930.client import Client
from alibabacloud_imagerecog20190930.models import ClassifyingRubbishAdvanceRequest
from alibabacloud_tea_openapi.models import Config
from alibabacloud_tea_util.models import RuntimeOptions

config = Config(
  # 创建AccessKey ID和AccessKey Secret，请参考https://help.aliyun.com/document_detail/175144.html。
  # 如果您用的是RAM用户的AccessKey，还需要为RAM用户授予权限AliyunVIAPIFullAccess，请参考https://help.aliyun.com/document_detail/145025.html
  # 从环境变量读取配置的AccessKey ID和AccessKey Secret。运行代码示例前必须先配置环境变量。
  access_key_id=os.environ.get('ALIBABA_CLOUD_ACCESS_KEY_ID'),
  access_key_secret=os.environ.get('ALIBABA_CLOUD_ACCESS_KEY_SECRET'),
  # 访问的域名
  endpoint='imagerecog.cn-shanghai.aliyuncs.com',
  # 访问的域名对应的region
  region_id='cn-shanghai'
)

def image_identification():     # 图像识别函数
    #场景一：文件在本地
    img = open(r'../image/lj.jpg', 'rb')
    #img = open(r'/tmp/ClassifyingRubbish1.jpg', 'rb')  # 系统的本地路径及图片
    #场景二：使用任意可访问的url
    #url = 'https://viapi-test-bj.oss-cn-beijing.aliyuncs.com/viapi-3.0domepic/imagerecog/ClassifyingRubbish/ClassifyingRubbish1.jpg'
    #img = io.BytesIO(urlopen(url).read())
    classifying_rubbish_request = ClassifyingRubbishAdvanceRequest()
    classifying_rubbish_request.image_urlobject = img
    runtime = RuntimeOptions()
    try:
      # 初始化Client
      client = Client(config)
      response = client.classifying_rubbish_advance(classifying_rubbish_request, runtime)
      # 获取整体结果
#      print(response.body)
#      print(type(response.body))
#      print(type(response.body.to_map()))
#      print(response.body.to_map())     # class 调用函数
#      print("类别:"+response.body.to_map()['Data']['Elements'][0]['Category'])
#      print("名称:"+response.body.to_map()['Data']['Elements'][0]['Rubbish'])
      print(response.body.to_map()['Data']['Elements'][0]['Category']+response.body.to_map()['Data']['Elements'][0]['Rubbish'])
      return response.body.to_map()['Data']['Elements'][0]['Category']	# 最好只返回一个值
#      return (response.body.to_map()['Data']['Elements'][0]['Category']+response.body.to_map()['Data']['Elements'][0]['Rubbish'])
    except Exception as error:
      return "物品识别失败"
if __name__ == "__main__":      # main函数
    image_identification()      # 调用图像识别函数
