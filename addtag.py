import os

postPath = "D:\\blog\\frostbyte134.github.io\\_posts"
tagPath = "D:\\blog\\frostbyte134.github.io\\tags"
posts = os.listdir(postPath)

for post in posts:
    with open(os.path.join(postPath, post), "r", encoding='UTF8') as f:
        print("what ", os.path.join(postPath, post))
        lines = f.readlines()
        for line in lines:
            if line[:4] == "tags":
                tags = line[line.find(":"):].split(" ")
                print("tags = ", tags)
                if len(tags) > 1:
                    tags = list(map(lambda p : p.strip("\n"), tags[1:]))
                    for tag in tags:
                        str = "---\nlayout: tagpage\ntitle: \"Tag: {0}\"\ntag: {0}\n---".format(tag)
                        with open(os.path.join(tagPath, "{}.md".format(tag)), "wt") as f:
                            f.write(str)


                break

