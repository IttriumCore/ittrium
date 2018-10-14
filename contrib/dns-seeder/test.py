import socket

seeders = [
    'xitseed.mempool.pw',
    'xitseed1.ittrium.io',
    'xitseed2.ittrium.io',
    'xitseed3.ittrium.io',
    'xitseed4.ittrium.io',
    'xitseed5.ittrium.io',
    'xitseed1.ittriumcrypto.site',
    'xitseed2.ittriumcrypto.site',
    'xitseed3.ittriumcrypto.site',
    'xitseed4.ittriumcrypto.site',
    'xitseed5.ittriumcrypto.site'
]

for seeder in seeders:
    try:
        ais = socket.getaddrinfo(seeder, 0)
    except socket.gaierror:
        ais = []
    
    # Prevent duplicates, need to update to check
    # for ports, can have multiple nodes on 1 ip.
    addrs = []
    for a in ais:
        addr = a[4][0]
        if addrs.count(addr) == 0:
            addrs.append(addr)
    
    print(seeder + ' = ' + str(len(addrs)))
