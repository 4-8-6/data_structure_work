#include "XmlStreamReader.h"

XmlStreamReader::XmlStreamReader()
{
}

XmlStreamReader::~XmlStreamReader()
{
}

QString XmlStreamReader::xmlStreamReaderFile(QString fileName)
{
    QString yz,temp;
    QString x="<dblp>"+fileName+"</dblp>";
    if(true == x.isEmpty() || 0 == x.length())
    {
        qDebug()<<"Error: fileName is empty .";
    }

    //定义要给QXmlStreamReader对象，同时将file作为QXmlStreamReader的输入设备
    QXmlStreamReader reader(x);

    //从输入流中读取下一个记号
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isStartElement())
        {
            if("dblp" == reader.name())
            {
                //若标签为dblp,则继续读取下一个记号
                reader.readNext();
                //读取文件的主体部分
                while(!reader.atEnd())
                {
                    //如果读取到了关闭标签,即</dblp>,则结束
                    if(reader.isEndElement())
                    {
                        reader.readNext();
                        break;
                    }
                    //读取到新的顶级索引<article>开始标签
                    if(reader.isStartElement())
                    {
                        //若为<article>开启标签,则读取条目文本数据
                        if("article" == reader.name())
                        {
                            temp="";

                            /*++++++++++++++++++ 获取标签属性 +++++++++++++++++++*/
                            //获取属性:mdate和key
                            QXmlStreamAttributes attributes = reader.attributes();
                            if(attributes.hasAttribute("mdate"))
                            {
                                temp+="mdate: "+attributes.value("mdate").toString()+"\n";
                            }
                            if(attributes.hasAttribute("key"))
                            {
                                temp+="key: "+attributes.value("key").toString()+"\n";
                            }
                            /*++++++++++++++++++++++++++++++++++++++++++++++++++*/

                            reader.readNext();
                            while(!reader.atEnd())
                            {
                                //若是关闭标签,则跳过该标签,同时跳出循环
                                if(reader.isEndElement())
                                {
                                    temp+="\n";
                                    yz+=temp;
                                    reader.readNext();
                                    break;
                                }

                                //若为开始标签,则可能情况有:正常情况和其他未知错误
                                if(reader.isStartElement())
                                {
                                    //若该记号为一个开始标签
                                   if("author" ==  reader.name()){
                                        QString author = reader.readElementText();
                                        temp+="author: "+author+"\n";
                                        reader.readNext();
                                    }else if("title" ==  reader.name()){
                                       QString title = reader.readElementText(QXmlStreamReader::IncludeChildElements);
                                       temp="title: "+title+"\n"+temp;
                                       reader.readNext();
                                   }else if("journal" ==  reader.name()){
                                       QString journal = reader.readElementText();
                                       temp+="journal: "+journal+"\n";
                                       reader.readNext();
                                   }else if("volume" ==  reader.name()){
                                       QString volume = reader.readElementText();
                                       temp+="volume: "+volume+"\n";
                                       reader.readNext();
                                   }else if("month" ==  reader.name()){
                                       QString month = reader.readElementText();
                                       temp+="month: "+month+"\n";
                                       reader.readNext();
                                   }else if("year" ==  reader.name()){
                                       QString year = reader.readElementText();
                                       temp+="year: "+year+"\n";
                                       reader.readNext();
                                   }else if("cdrom" ==  reader.name()){
                                       QString cdrom = reader.readElementText();
                                       temp+="cdrom: "+cdrom+"\n";
                                       reader.readNext();
                                   }else if("ee" ==  reader.name()){
                                       QString ee = reader.readElementText();
                                       temp+="ee: "+ee+"\n";
                                       reader.readNext();
                                   }else{
                                       //对不需要读取的标签内容忽略，例如<url>...</url>
                                       reader.readNext();
                                       reader.readNext();
                                       reader.readNext();
                                    }
                                }else {
                                    reader.readNext();
                                }
                            }       //1.while

                        }else{
                            //忽略不能识别的标签，例如把book剔除
                                 reader.readNext();
                                 while(!reader.atEnd())
                                 {
                                     //若是关闭标签</book>,则跳过该标签,同时跳出循环
                                     if(reader.isEndElement())
                                     {
                                         reader.readNext();
                                         break;
                                     }
                                     //如果是开始标签，继续略过直到</book>之前的最后一个关闭标签
                                 if(reader.isStartElement())
                                 {
                                     reader.readNext();
                                     reader.readNext();
                                     reader.readNext();
                                 }else{
                                     reader.readNext();
                                   }
                                 }
                            }//剔除到此为止
                    }else {
                        reader.readNext();
                    }
                 }
              }else{
                reader.raiseError(QObject::tr("Not a dblp file"));
                break;//读取的标签不是dblp，结束xml读取
            }
        }else{
            reader.readNext();//忽略不能识别的标签
        }

    }
    return yz;
}
