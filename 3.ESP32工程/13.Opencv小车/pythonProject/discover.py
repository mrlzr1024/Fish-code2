# made by LZR
import requests  # 导入requests包

switch = 0


def is_Chinese(ch):
    global switch
    if '\u4e00' <= ch <= '\u9fff' or ch == '，' or ch == '。' or ch == '、':
        return True


url = 'https://lenovo.ilive.cn/?f=stle'
strHtml = requests.get(url)  # Get方式获取网页数据
html = strHtml.text
html = html.replace('>', ">\n")
# html1=str(html.split('>')).split('<')
html1 = html.replace('</', '\n</')
# del (html)
j=' '
# for i in html1:
#     if is_Chinese(i) or i.isdigit():
#         if j == '\n':
#             print('')
#         print(i, end='')
#     j = i

print(html1)
