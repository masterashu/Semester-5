import bs4
import requests

base = 'https://www.2power3.com/rajendra/'

html = open('list.html').read()

soup = bs4.BeautifulSoup(html, 'html.parser')

links = list(map(lambda x: x.attrs['href'], soup.find_all('a')))

links = list(filter(lambda x: x.endswith('.pdf'), links))

for link in links:
    open(link.rsplit('/',1)[-1], 'wb').write(requests.get(base+link, headers={"User-Agent": 'Mozilla/5.0 (Linux; Android 7.0; SM-G930VC Build/NRD90M; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/58.0.3029.83 Mobile Safari/537.36' }).content)
