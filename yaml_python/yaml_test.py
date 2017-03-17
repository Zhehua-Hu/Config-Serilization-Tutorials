import yaml
f = open('test.yaml')
x = yaml.load(f)

print type(x)
print x

print(x['age'])
print(x['spouse']['name'])