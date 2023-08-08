import jieba

source_text = "万里长城是中国古代劳动人民血汗的结晶和中国古代文化的象征和中华民族的骄傲"
messages = jieba.cut(source_text, cut_all=False) #精确模式
print(f"Source: {source_text}")
print ( '【精确模式下的分词:】' + "/ ".join(messages)) 

messages = jieba.cut("万里长城是中国古代劳动人民血汗的结晶和中国古代文化的象征和中华民族的骄傲", cut_all=True) #全模式
print ( '【全模式下的分词:】'+"/ ".join(messages)) 

source_text = "Follow your heart. It will tell you where you should go."
print("/ ".join(jieba.cut(source_text, cut_all=False)))

source_text = "星巴克java"
print("/ ".join(jieba.cut(source_text, cut_all=False)))
