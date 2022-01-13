#include "solution.h"

//完成基本搜索之输入作者名查找其发表的所有论文
int hash_find(QString str,QString* all_author)//计算哈希值
{
    QByteArray byte = str.toUtf8();
    int64_t sum = 0;
    for(int i = 0; i < str.size();i++)
    {
         sum += abs(int(byte.at(i)))*pow(10,i%8);
    }
    sum = sum%hash_len;
    int j = 0;
    while(1)
    {

        sum = (sum+int(pow(j,2)))%hash_len;
        if(all_author[sum]=="")
        {
            return -1;
        }
        else
        {
            ++j;
            if(str == all_author[sum])
            {
                return sum;
            }
        }
    }
}
QString use_author_to_search(QString* all_author, article_node* libarary,QString str,myvect*author_article)
{
    int ans = hash_find(str,all_author);//查找作者str存放的哈希位置，如不存在则返回-1
    QString x,y;
    if(ans == -1){
        x="This author can't be found!\nPlease check the button you pressed or your input.";
        return x;
    }
    else
    {
        x=str;
        int num = 0;
        x+=" has been found!\nThere are his/her articles:\n";
        for(int i = 0 ; i < author_article[ans].len;i++)
        {
           x+=libarary[((author_article[ans]).poses[i])].show();//获取对应文章的标题和年份
           x+="\n";
           ++num;
        }
        x+="\n";
        int* arra = new int[num];
        for(int i = 0 ; i <num;++i)
        {
            arra[i] = libarary[((author_article[ans]).poses[i])].filepos;//获取文章详细信息的存放位置
        }
        y+=readsome(arra,num);
        delete[]arra;
        x+=y;
        return x;
    }
}
QString readsome(int* arra, int len)//批量读取data.txt的内容
{
    QString str = "";
    for(int i = 1; i < len; i++)//插入排序，数据量较小
    {
        for(int j = i; j > 0; j--)
        {
            if(arra[j]<arra[j-1])
            {
                int temp = arra[j];
                arra[j] = arra[j-1];
                arra[j-1] = temp;
            }
            else
            {
                break;
            }
        }
    }
    int *read_array = new int[len];
    for(int i= 0; i < len;i++)
    {
        read_array[i]= arra[i];
    }
    QFile file(".\\data.txt");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!";
    }
        int counter = 0; //读取位置计数器
        int line_counter = 0;//行计数器
        QByteArray line;
        while(!file.atEnd())
        {
            line = file.readLine();
            ++line_counter;
            loop:
            if(read_array[counter] == line_counter)
            {
                if(read_array[counter]==1)
                {
                    str += QString(line);
                }
                else
                {
                    str+=QString(line).mid(10);
                }
                while(1)
                {
                    line = file.readLine();
                    ++line_counter;
                    QString ptemp(line);
                    if(ptemp.left(10)=="</article>")
                    {
                        str += ptemp.left(10);
                        str += "\n\n";
                                break;
                    }
                    else{
                        str += ptemp;
                    }
                }
                counter++;                
                if(counter == len)break;
                else
                {
                    goto loop;
                }
            }
        }
        file.close();
        delete[]read_array;
    XmlStreamReader read;
    str=read.xmlStreamReaderFile(str);//对读取的xml文本解析
    return str;
}

//完成基本搜索之输入文章名查找相关信息
article_node* bin_search(article_node* libarary,QString str, QString*all_author,int * merged, int left, int right)
{
    if(left > right)return nullptr;
    int mid = (left + right)/2;
    if(str == libarary[merged[mid]].title)
    {
        return &libarary[merged[mid]];
    }
    else if((str > libarary[merged[mid]].title))
    {
        return bin_search(libarary,str,all_author,merged,mid+1,right);
    }
    else
    {
        return bin_search(libarary,str,all_author,merged,left,mid - 1);
    }
}
void mergesort(article_node*libarary,int* merged, int left, int right)
{
    if(left>=right)return;
    else
    {
        int mid = (left+right)/2;
        mergesort(libarary,merged, left,mid);
        mergesort(libarary,merged,mid + 1, right);

        int* ptr = new int[right - left + 1];

        int lp = left; int rp = mid+1;
        int pos = 0;

        while(lp <= mid && rp <= right)
        {
            if(libarary[merged[lp]].title > libarary[merged[rp]].title)
            {
                ptr[pos++] = merged[rp++];
            }
            else
            {
                ptr[pos++] = merged[lp++];
            }
        }
        while(lp <= mid)
        {
            ptr[pos++] = merged[lp++];
        }
        while(rp <= right)
        {
            ptr[pos++] = merged[rp++];
        }

        for(int i = 0; i < pos; i++)
        {
            merged[i+left] = ptr[i];
        }
        delete[]ptr;
    }
}

//作者统计
QString find_most_authors(myvect*author_article,QString* all_author)
{
    QString yz;
    int * a = new int[3000000];
    int pos = 0;
    for(int i = 0;i < hash_len; i++)
    {
        if(all_author[i]!="")
        {
            a[pos++] = i;
        }
    }
    quicksort(a, author_article,0,pos-1);
    for(int i = 0 ; i < 100; i++)
    {
        yz+=all_author[a[i]]+"\t"+QString::number(author_article[a[i]].len)+"\n";
    }
    delete[] a;
    return yz;
}
void quicksort(int*a, myvect* author_article, int left, int right)
{
    if(left>=right)return;
    else
    {
        int mid = (left+right)/2;
        quicksort(a,author_article,left,mid);
        quicksort(a,author_article,mid+1,right);
        int *ptr = new int[right-left+1];
        int pos = 0;
        int i = left, j = mid + 1;
        while(i<=mid&&j <= right)
        {
            if(author_article[a[i]].len < author_article[a[j]].len)
            {
                ptr[pos++] = a[j++];
            }
            else
            {
                ptr[pos++] = a[i++];
            }
        }
        while(i<=mid)
        {
            ptr[pos++] = a[i++];
        }
        while(j <= right)
        {
            ptr[pos++] = a[j++];
        }
        for(int k = 0; k < pos; k++)
        {
            a[left+k] = ptr[k];
        }
        delete[]ptr;
    }

}

//相关搜索
QString related_search(QString* all_author,myvect* author_article,article_node* library,QString str)
{
    QString yz;
    article_node* ptr;
    if(hash_find(str,all_author)==-1)
    {
        yz="Can't find this author!\nPlease check your input!";
    }
    else{
    myvect* p = &author_article[hash_find(str,all_author)];
    if(p->len==0)
    {
        yz="This author don't have cooperators.";
    }else{
    QStringList authorlist;
    int t=1;
    for(int i = 0 ; i < p->len; ++i)
    {
        ptr = &library[p->poses[i]];
        yz +=library[p->poses[i]].title;
        yz +=":\n";
        for(int j = 0 ; j < ptr->len;++j)
        {
            if(all_author[ptr->authors[j]]!=str)
            {
                yz += all_author[ptr->authors[j]];
                yz +="\n";
                for(int k=0 ;k<authorlist.size(); ++k)
                {
                    if(all_author[ptr->authors[j]]==authorlist[k])
                    {
                        t=0;//去掉重复作者
                        break;
                    }
                }
                if(t)
                {
                    authorlist.append(all_author[ptr->authors[j]]);
                }
                t=1;
            }
        }
        ptr = 0;
    }

    yz+="\nHis or her all cooperators are:\n";
    for(int i=0 ;i<authorlist.size(); ++i)
    {
        yz +=authorlist[i];
        yz +="\n";
    }
  }
 }
   return yz;
}

//热点分析
QString year_select(article_node*article,int the_year,int numbers)
{
    QString yz;
    treenode* head = new treenode("m");
    for(int i = 0; i < numbers;i++)//建树
    {
        if(article[i].year != the_year)continue;
         QStringList lis = article[i].title.split(' ');
         for(int i = 0; i < lis.size();i++)
         {
             if(lis[i]!="")
             {
                if(judge_string(lis[i]))
                {
                    treeappend(head,lis[i].toLower());

                }
             }
         }
    }
    int* Numbers = new int;
    *Numbers = 0;
    treenode* anhead = new treenode[3000000];
    treeshow(head,anhead,Numbers);
    if(*Numbers < 15){return "There is not atricle in this year or you input a wrong message.Please input again!";}
    yz=heapshow(anhead,*Numbers,10);
    tree_delete(head);
    delete[]anhead;
    return yz;
}
void treeappend(treenode* h,QString s)
{
    if(h->str==s){h->number++;}
    else
    {
        if(h->str < s)
        {
            if(h->right == nullptr)
            {
                h->right = new treenode(s);
            }
            else
            {
                treeappend(h->right,s);
            }
        }
        else
        {
            if(h->left == nullptr)
            {
                h->left = new treenode(s);
            }
            else
            {
                treeappend(h->left,s);
            }
        }
    }
}
treenode* treefind(treenode* h,QString s)
{
    if(h == nullptr)return nullptr;
    if(h->str == s)return h;
    if(s > h->str)return treefind(h->right,s);
    else return treefind(h->left,s);
}
void tree_delete(treenode* h)
{
    if(h->left)
    {
        tree_delete(h->left);
        h->left = 0;
    }
    if(h->right)
    {
        tree_delete(h->right);
        h->right = 0;
    }
    delete h;
}
void treeshow(treenode* p,treenode* anhead, int* Numbers)//堆构建函数
{
    if(p->left){
        treeshow(p->left,anhead,Numbers);
    }
    if(p->right){
        treeshow(p->right,anhead,Numbers);
    }
    anhead[*Numbers].copy(p->number,p->str);
    heapturn(anhead,*Numbers);//建堆
    (*Numbers)++;
}
void treeswap(treenode*p,int left,int right)
{
    treenode k;
    k.copy(p[left].number,p[left].str);
    p[left].copy(p[right].number,p[right].str);
    p[right].copy(k.number,k.str);
}
void heapturn(treenode* p, int num)
{
    while(1)
    {
        if(num==0)return;
        int pos = (num-1)/2;
        if(p[num].number > p[pos].number)
        {
            treeswap(p,num,pos);
            num = pos;
        }
        else
        {
            return;
        }
    }
}
QString heapshow(treenode*p,int number,int len = 10)
{
    QString yz;
    int k = number-1;
    while(len--)
    {
        yz+=p[0].str+"\t"+QString::number(p[0].number)+"\n";
        treeswap(p,0,k);
        --k;
        int j = 0;
        while(1)
        {
            int nextpos;
            if (2*j>=k)break;
            if(p[2*j+1].number>p[2*j+2].number)
            {
                nextpos = 2*j+1;
            }
            else
            {
                nextpos = 2*j+2;
            }
            if(p[nextpos].number>p[j].number)treeswap(p,j,nextpos);
            else break;
            j = nextpos;
        }
    }
    return yz;
}

//部分匹配
QString partselect(article_node* libarary,int numbers,QString str)
{
       QString ans;
       ACnode* root = new ACnode;
       QStringList strs = str.split('/');
       int num = strs.size();
       for(int i = 0 ; i < num ; ++i)
       {
           if(strs[i].length()<=2)
           {
               ans="This is an invalid input, please input again!";
               return ans;
           }
       }
       for(int i = 0 ; i < num ; ++i)
       {
           ACinsert(strs[i].toLower(),root,i+1);
       }
       buildfail(root);
       int k = 0;
       for(int i = 0; i < numbers; ++i)
       {

           if(ACsearch(libarary[i].title.toLower(),root,num))
           {
               ans+=QString::number(k+1) + ".\n"+libarary[i].title+"\n\n";//输出找到的标题
               ++k;
           }
       }
      ACtrash(root);
      if(ans=="") return "Can't find anything! Please input again!";
      else return ans;
}
int judge_string(QString& match_str)
{
    match_str.replace(QString(","),QString(""));
    match_str.replace(QString("."),QString(""));
    match_str.replace(QString("!"),QString(""));
    match_str.replace(QString("\""),QString(""));
    match_str.replace(QString(":"),QString(""));
    if (match_str.size() <= 3) { return 0; }
    if (match_str == "the" || match_str == "and" ||
            match_str == "for" || match_str == "und" ||
            match_str == "von" || match_str == "der" ||
            match_str == "from" || match_str == "zur" ||
            match_str == "with" || match_str == "fur" ||
            match_str == "its" || match_str == "all" ||
            match_str == "about" || match_str == "als" ||
            match_str == "aus" || match_str == "auf" ||
            match_str == "des" || match_str == "based" ||
            match_str == "eine" || match_str == "using" ||
            match_str == "das" || match_str == "ein" ||
            match_str == "den" || match_str == "using" ||
            match_str == "some" || match_str == "two" ||
            match_str == "einer") { return 0; }    return 1;
}
bool ACinsert(QString str,ACnode*root, int tiga)
{
    ACnode* p = root;
    for(int i = 0 ; i < str.size(); ++i)
    {
        char temp = str[i].toLatin1();
        bool bo = true;
        for(int j = 0 ;  j < p->len; ++j)
        {
            if(p->next[j]->ch == temp&&bo)
            {
                p = p->next[j];
                bo = false;
                break;
            }
        }
        if(bo)
        {
            int jkl = p->len;
            p->len++;
            p->next[jkl] = new ACnode(temp);
             p = p->next[jkl];
        }
    }
    p->count = tiga;
    return true;
}
bool buildfail(ACnode* root)
{
    ACnode** queue = new ACnode*[1000];
    for(int i = 0 ; i < 1000; ++i)
    {
        queue[i] = nullptr;
    }
    int head = 0 ; int tail = 0;
    root->fail = nullptr;
    queue[head++] = root;
    while(head!=tail)
    {
        ACnode* temp = queue[tail++];
        for(int i = 0 ; i < temp->len; i++)
        {
            queue[head++] = temp->next[i];
            ACnode* ptr = nullptr;
            if(temp==root)
            {
                temp->next[i]->fail = root;
            }
            else
            {
                ptr = temp->fail;
                 bool sele = false;
                while(ptr != nullptr)
                {
                    for(int j = 0 ; j < ptr->len; ++j)
                    {
                        if(ptr->next[j]->ch==temp->next[i]->ch)
                        {
                            temp->next[i]->fail = ptr->next[i];
                            sele = true;
                        }
                    }
                    if(sele)break;
                    ptr = ptr->fail;
                }
                if(ptr == nullptr)
                {
                    temp->next[i]->fail = root;
                }
            }

        }

    }
    delete[] queue;
    return true;
}
bool ACsearch(QString str,ACnode* root,int tiga)
{
    bool* arra = new bool[tiga]{false};
    ACnode*p = root;               //行动指针
    for(int i = 0; i < str.size(); ++i)
    {
        char ch = str[i].toLatin1();
        while(p != nullptr)
        {
            ACnode *temp=p;
    while(temp!=root )
                {
                    if(temp->count!=0)
                    {
                        arra[temp->count-1] = 1;
                    }
                    temp=temp->fail;
                }
            ACnode* ptr = p;
            for(int j = 0 ;  j < ptr->len; ++j)
            {
                if(ptr->next[j]->ch == ch)
                {
                    p = ptr->next[j];
                }
            }
            if(p == ptr)
            {
                p = p->fail;
            }
            else
            {
                break;
            }

        }
        if(p==nullptr)
        {
            p = root;
        }
    }

    for(int i = 0 ; i < tiga; ++i)
    {
        if(!arra[i])
        {
            delete[]arra;
            return false;
        }
    }
    delete[]arra;
    return true;
}
void ACtrash(ACnode* root)
{
    for(int i = 0 ; i < root->len; ++i)
    {
        ACtrash(root->next[i]);
    }
    delete root;
}
