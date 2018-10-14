import binascii
import hashlib
import sys

def privateKey_to_WIF(pk): #wallet import format ==> pra importar nas carteiras

    privWIF1 = hashlib.sha256(binascii.unhexlify('ef' + pk)).hexdigest()
    privWIF2 = hashlib.sha256(binascii.unhexlify(privWIF1)).hexdigest()
    privWIF3 = 'ef' + pk + privWIF2[:8]

    pubnum = int(privWIF3, 16)
    pubnumlist = []
    while pubnum != 0: pubnumlist.append(pubnum % 58); pubnum /= 58
    WIF = ''
    for l in ['123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'[x] for x in pubnumlist]:
        WIF = l + WIF
    #print(WIF)
    return WIF

k = sys.argv[1]
rs =  privateKey_to_WIF(k)
print(rs)