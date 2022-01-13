from bs4 import BeautifulSoup as BS
file1 = open('author.txt','w',encoding='utf-8')
file2 = open('data.txt','w',encoding='utf-8')
group=''
strs=''
i = 0#data文件对应内容的行数计数
with open('dblp.xml','r',encoding='utf-8')as f:
    for s in f:
        if s[:10]!='</article>':
            group+=s
        else:
            soup = BS(group,"html.parser")
            st = str(soup.find('article'))
            strs+=str(soup.find('article').find('year').string)#找到年份
            strs+='\t'#加入制表符控制格式
            strs+=str(soup.find('article').find('title').string)#找到标题
            strs+='\t'#加入制表符控制格式
            tag=True
            for author in soup.find('article').find_all('author'):#遍历所有作者
                if tag:
                    tag=False
                else:
                    strs+=','#加入逗号对不同作者分割
                strs+=str(author.string)
            strs+='\t'
            strs+=str(i)
            i+=len(st)
            strs+='\n'
            file1.write(strs)#把年份标题作者和data文件中行数写入author文件
            file2.write(st)#把全部article的xml文本保存在data文件中
            strs=''
            group=s[10:]


file1.close()
f.close()
