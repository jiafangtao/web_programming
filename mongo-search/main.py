import pymongo
import jieba
import pprint

server = 'localhost'
port = 27017


def tokenize_chinese(s):
	return ' '.join(jieba.cut(s, cut_all=False))


client = pymongo.MongoClient(server, port)
db = client.stores
print(db.name)

db.stores.drop()

ret = db.stores.insert_many(
    [
      { "uid": 1, "name": "Java Hut", "description": "Coffee and cakes" },
      { "uid": 2, "name": "Burger Buns", "description": "Gourmet hamburgers" },
      { "uid": 3, "name": "Coffee Shop", "description": "Just coffee" },
      { "uid": 4, "name": "Clothes Clothes Clothes", "description": "Discount clothing", "additions": "free coffee" },
      { "uid": 5, "name": "Java Shopping", "description": "Indonesian goods" },
      { "uid": 6, "name": "星巴克java中文", "description": "测试中文的搜索", "_tr": { "name": [], "description": []}},
      { "uid": 7, "name": "星巴克是卖糖水的地产公司", "description": "如果没有空格也没有分词搜索不出来", "_tr": { "name": [], "description": []}},
      { "uid": 8, "name": "星巴克 是卖糖水的 地产公司", "description": "如果有空格, 没有分词那就碰巧能够搜出来", "_tr": { "name": [], "description": []}}
    ]   
)

print(f"insert many:: {ret}")

ret = db.stores.insert_one({"uid": 999, "name": "Thinking in JAVA", "revision": 2, "description": "A great JAVA programming book by Bruce Eckel", "price": 49.99})
print(f"insert_one: {ret}")

db.stores.insert_one({"name": "Thinking in C++", "revision": 2, "description": "A great C++ programming book by Bruce Eckel. sister of thinking in java", "price": 49.99})
db.stores.insert_one({"name": "PS Pet Shop", "openning": ["Monday", "Tuesday", "Friday"]})

# A typical case is that user knows which fields to index. e.g.
# Create a 'text' index for field 'description'
#ret =db.stores.create_index( [("description", pymongo.TEXT), ("name", pymongo.TEXT), ("_tr.name", pymongo.TEXT)])
#print(f"index is created: {ret}")

# In our case we need to index all fields - 
# Create a 'text' index for all fields (wildcard index)
db.stores.create_index([("$**", pymongo.TEXT)])

# search for an exact phrase
ret = db.stores.find( { "$text": { "$search": "\"coffee shop\"" } } )
print("\n>>>>>>>>>>>>>>> Search result for phrase - [\"coffee shop\"]")
for store in ret:
	pprint.pprint(store)

# search for non-exact phrase
ret = db.stores.find( { "$text": { "$search": "coffee shop" } } )
print("\n>>>>>>>>>>>>>>> Search result for phrase - [coffee OR shop]")
for store in ret:
	pprint.pprint(store)

# exclude one with minus operator (-)
ret = db.stores.find( { "$text": { "$search": "java shop -coffee" } } )
print("\n>>>>>>>>>>>>>>> Search result for phrase - [java shop -coffee]")
for store in ret:
	pprint.pprint(store)


# Update reserved fields to save tokenized Chinese fields 
store = db.stores.find_one({"uid": 6})
print("============= store =============")
print(store["name"])
print(tokenize_chinese(store["name"]))
print(store["description"])
print(tokenize_chinese(store["description"]))

db.stores.update_one({"uid": 6}, {
	"$set": { "_tr": {"name": tokenize_chinese(store["name"]), "description": tokenize_chinese(store["description"]) }}
})

ret = db.stores.find( { "$text": { "$search": "中文" } } )
print("\n>>>>>>>>>>>>>>> Search result for phrase - [中文]")
for store in ret:
	pprint.pprint(store)

ret = db.stores.find( { "$text": { "$search": "星巴克" } } )
print("\n>>>>>>>>>>>>>>> Search result for phrase - [星巴克]")
for store in ret:
	pprint.pprint(store)

ret = db.stores.find( { "$text": { "$search": "公司" } } )
print("\n>>>>>>>>>>>>>>> Search result for phrase - [公司]")
for store in ret:
	pprint.pprint(store)

ret = db.stores.find( { "$text": { "$search": "地产公司" } } )
print("\n>>>>>>>>>>>>>>> Search result for phrase - [地产公司]")
for store in ret:
	pprint.pprint(store)


# TODO: sort by relevance score
#
#db.stores.find(
#   { "$text": { "$search": "java coffee shop" } },
#   { "score": { "$meta": "textScore" } }
#).sort( { "score": { "$meta": "textScore" } } )
#
