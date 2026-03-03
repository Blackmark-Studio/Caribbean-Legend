// Арчибальд Колхаун
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir şeye ihtiyacın var mı?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "portroyal":
			dialog.text = "Ha, Mösyö de Maure!  Port Royal'a hoş geldiniz!  Hâlâ beni hatırlıyor musunuz?";
			link.l1 = "Hmm... Siz r. Calhoun'sunuz, değil mi? Henry Calhoun?";
			link.l1.go = "portroyal_1";
		break;
		
		case "portroyal_1":
			dialog.text = "Neredeyse... Archibald Calhoun.";
			link.l1 = "Affedersiniz, Mösyö. Evet, sizi hatırlıyorum. Cape Catoche'da, koyda tanışmıştık. Kaptanınız da yanınızdaydı, William Patterson. Onun filosunu tanıdım.";
			link.l1.go = "portroyal_2";
		break;
		
		case "portroyal_2":
			dialog.text = "Kesinlikle doğru! Lütfen kaptanımı bağışlayın. Tanımadığı insanlara karşı her zaman kaba olur. Diego de Montoya'nın kalesini yıldırım gibi ele geçirmen harikaydı, biz de orada pençelerimizi bilemiş olduk...";
			link.l1 = "Adalet uğruna olduğunu da eklemeliyim; kaptanınızın önceden yaptığı hazırlıklar olmasaydı, İspanyol toplarının ateşi altında ödüle koşabileceğimden bile şüpheliyim. Komutanınız aradığını bulabildi mi?";
			link.l1.go = "portroyal_3";
		break;
		
		case "portroyal_3":
			dialog.text = "Evet. Kalede, surların altındaki mahzenlere epey derin inip bir tür arşiv bulmuş. Görülmemiş bir memnuniyet içindeydi. Bu arada, sormamda sakınca yoksa, seni o ormandaki kaleye saldırmaya iten neydi?";
			link.l1 = "Saint-Pierre'de bana yenildikten sonra Don Diego entrikalar çevirmeye başladı ve sonunda Küba'ya açık bir saldırı başlattı. Sonra çatışmayı bırakıp anakaraya doğru dağlara kaçtı. Ben de bu korkak köpeği sonsuza dek ortadan kaldırmaya karar verdim, bir daha Fransızların adını lekelemesin diye.";
			link.l1.go = "portroyal_4";
		break;
		
		case "portroyal_4":
			dialog.text = "Evet, Kaptan Charles de Maure'un kahramanlıkları hakkında epeyce efsanevi hikaye duymuştum. Şimdi ise kendi gözlerimle gördüm...";
			link.l1 = "Evet, William Paterson'ın cesareti hakkında birkaç şey duydum ben de. Onun gibi bir kaptana sahip olduğun için şanslısın.";
			link.l1.go = "portroyal_5";
		break;
		
		case "portroyal_5":
			dialog.text = "Şanslıyım, doğru. Gerçi o artık öyle önemli bir adam oldu ki, yüksek sosyete, davetler, balolar, geçit törenleri ve özel partiler... Port Royal'e her geldiğimizde onu vali sarayından dışarı çıkarmak mümkün değil. Aslında, şu anda da yine orada.\nKaptan Charles de Maure, bir İskoç sarhoşuna iyilik yapar mısın? Bana katıl da biraz sohbet edelim! Hep aynı yüzleri görmekten bıktım, sen de konuşması keyifli birine benziyorsun. Gel bana, rahatlayalım ve bir fıçı nefis viski içelim. Benden!";
			link.l1 = "Hm... Cazip, ama...";
			link.l1.go = "portroyal_6";
		break;
		
		case "portroyal_6":
			dialog.text = "Ah kaptan, yeter artık, senin de bazen dinlenmen gerek. Bu arada, yerel tüccarın dükkanından taptaze mezelerim var. Dükkanın hemen üst katında bir oda kiraladım. Ne zaman bir şeyler yemek ya da içmek istersen, aşağı inmen yeterli, her şey hazır, haha! Kolaylık, değil mi? Hadi, gidelim!";
			link.l1 = "Beni ikna ettin!";
			link.l1.go = "portroyal_7";
		break;
		
		case "portroyal_7":
			dialog.text = "Harika. Beni takip et!";
			link.l1 = "...";
			link.l1.go = "portroyal_8";
		break;
		
		case "portroyal_8":
			DialogExit();
			NextDiag.CurrentNode = "portroyal_9";
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6_back", "PortRoyal_store", "goto", "goto2", "GuardOT_ArchyIntoStore", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "portroyal_9":
			LAi_SetSitType(Pchar);
			dialog.text = "Bak, burada ne kadar güzel, değil mi? Serin ve ferah... İşte burada biraz viski fıçısı var! Şerefe, Kaptan!";
			link.l1 = "Pekâlâ, bu şanslı karşılaşmamıza ve hoş tanışıklığımıza içelim!";
			link.l1.go = "portroyal_10";
		break;
		
		case "portroyal_10":
			dialog.text = "Memnun oldum!... Ah! Karayipler'e yeni geldiniz, değil mi, Mösyö de Maure?";
			link.l1 = "Oldukça yakın bir zamanda... ya da belki o kadar da yakın değil. Nasıl anlatacağımı tam olarak bilmiyorum. Sanki hayatımın yarısını burada geçirmişim gibi hissediyorum.";
			link.l1.go = "portroyal_11";
		break;
		
		case "portroyal_11":
			dialog.text = "Ah, o duyguyu iyi bilirim... Gerçi ben de burada epey zamandır yaşıyorum. Ve o lanet adaya ilk ayak bastığımda, William beni oradan kurtarana kadar... Ohoo, sanki orada hayatımın yarısına veda etmişim gibi hissettim.";
			link.l1 = "İlginç! Hangi adadaydı bu?";
			link.l1.go = "portroyal_12";
		break;
		
		case "portroyal_12":
			dialog.text = "Willy benim eski dostumdur, birbirimizi hâlâ İskoçya'nın temiz havasını soluduğum zamanlardan tanırız... Güzel günlerdi. O kadar aptaldım ki, o lanet papazlarla ve Engizitör'ün kendisiyle dalaştım, o da bana suikast düzenledi. O zamanlar tüccardım, kendi flütüm vardı. Ah, o lanet günde gemime korsan kılığında İspanyollar saldırdı. Cesurca savaştık, ama bizi fare gibi köşeye sıkıştırdılar! Ama o zaman bile, yaşlı Colhaun soğukkanlılığını kaybetmedi, bir varil su ve birkaç tahta parçasıyla denize atladı. Ben de karanlıktan faydalanıp askerler görmeden gemimden yüzerek uzaklaştım. Hayatta kalma şansım pek yoktu, ama gemide kalmak hiç şansımın olmaması demekti. İki gün sonra, ıssız bir adanın kıyısına vurmuştum. O zamana kadar Karayipler'de bir süredir yaşıyordum ama orayı daha önce hiç duymamıştım! Küçük ve tamamen ıssız bir yerdi... ve orada iki yıl geçirdim, bana bir ömür gibi geldi. Nasıl aklımı yitirmeden kaldım, hâlâ bilmiyorum.";
			link.l1 = "İki yıl boyunca ıssız bir adada mı yaşadın?";
			link.l1.go = "portroyal_13";
		break;
		
		case "portroyal_13":
			dialog.text = "Yemin ederim, lanetli bir yerdi! Neyse ki tatlı su vardı. Yengeç, midye, balık ve kuşlarla hayatta kaldım. O yüzden oraya Yengeç Adası adını verdim. Hiç silahım yoktu, o yüzden yabani gibi zıpkın, mızrak ve ok kullanmayı öğrendim! Ohoo! İç, iç Kaptan! Benim de boğazımı ıslatmamda bir sakınca yok...";
			link.l1 = "Evet... Sana hiç imrenmiyorum.";
			link.l1.go = "portroyal_14";
		break;
		
		case "portroyal_14":
			dialog.text = "Al işte! O koca kum yığınının kıyısına ilk adım attığımda tam olarak bunu söyledim: 'Vay be Archy, halin pek iç açıcı değil ama umutsuz da sayılmaz!' Ve biliyor musun, Kaptan, beni hayatta tutan neydi?";
			link.l1 = "Adanın yanından geçen bir gemi mi?";
			link.l1.go = "portroyal_15";
		break;
		
		case "portroyal_15":
			dialog.text = "Hayır! Beni kurtaran sıkı çalışmaktı! Emek, inanç ve yaşama isteği! Adanın her köşesini gezdim, her yerini araştırdım ve karşılığında marangoz aletleriyle, yazı malzemeleriyle ve başka küçük şeylerle dolu bir sandık buldum. O anda kendime ne dedim biliyor musun? Daha fazla koy, Kaptan, doldur!\nDedim ki: Archie, aklını sağlam tutmak için çalışmalısın ve Tanrı sana başlamak için gereken her şeyi verdi. Bak şimdi! Körfezin yanında bir ev inşa etmeye başladım, biliyor musun? Bu beni karanlık düşüncelerden kurtardı ve yaşamak için bir sebep verdi!";
			link.l1 = "Gerçekten ilham verici birisiniz, Bay Calhoun. O durumda çoğu insan hiçbir şey yapamazdı, ya da pek azını başarabilirdi...";
			link.l1.go = "portroyal_16";
		break;
		
		case "portroyal_16":
			dialog.text = "Evet, yaşlı Calhaun'un İskoçya'da doğmasının bir sebebi var! Aynen öyle! Biz dağların oğullarıyız – güçlü, cesur ve dayanıklıyız, o bataklıkta yaşayan cılızlardan çok daha iyiyiz. Biraz daha doldur... Neydi, ne anlatıyordum? Ha, evet! Çok çalıştım ve kendime düzgün bir ev yaptım. Bir de başıma gelen talihsizlikleri yazmak için günlük tutmaya başladım. Günlüğümü Willy beni kurtardığında yanıma almıştım. Şimdi burada, bu masada tutuyorum ve Port Royal'de her konakladığımızda sıcak, yumuşak yatağımda tekrar tekrar okuyorum. İçine başıma gelen her şeyi yazdım, oraya gitmeden önce ve sonra olan her şeyi. Hâlâ aklımı kaybetmemiş olmamın sebeplerinden biri de bu.";
			link.l1 = "Demek Bay Paterson seni adadan aldı? Ama orayı nasıl bulmuş olabilir? Sen demiştin ki...";
			link.l1.go = "portroyal_17";
		break;
		
		case "portroyal_17":
			dialog.text = "Evet, evet, ada hiçbir haritada işaretli değil. Ama Willy, o eski Willy! O her şeyi yapar! Ve o lanet adayı buldu, beni kurtardı, bunun için hayatımın sonuna kadar minnettar olacağım. Evet...";
			link.l1 = "Bay Paterson'a hizmet etmekten hoşlanıyor musun? Kendi imkanlarınla tekrar yola çıkmak ister misin?";
			link.l1.go = "portroyal_18";
		break;
		
		case "portroyal_18":
			dialog.text = "Bağımsız olmaktan bıktım artık. Willy genç ve başarılı, üstelik ben de onun eski dostuyum. Daha ne isterim ki? Yok, ben Willy'yle ömrümün sonuna kadar kalacağım, ya da en azından bir dahaki sefere sarhoş olup kovulana kadar, haha! Madem lafı açıldı, hadi doldur bakalım!";
			link.l1 = "Akh...(içiyor) Söyle bana Bay Calhoun. Duyduğuma göre bir zamanlar hazine avcısıymışsın. Doğru mu bu, yoksa sadece palavra mı?";
			link.l1.go = "portroyal_19";
		break;
		
		case "portroyal_19":
			dialog.text = "Who told you that? Well, there's no sense in trying to hide it. I used to be one. It didn't turn out well though; it was treasure hunting that led me to those blasted Jesuits and the island. The holy fathers tortured a man to death because of me, and I myself... oh, let's keep the past in the past.\nI have paid enough for my sins, and I hope never to repeat them in the future. No, Willy won't let that happen, I'm sure!";
			link.l1 = "Dinle, Archibald. Miguel Dichoso adında bir adamı hiç duydun mu?";
			link.l1.go = "portroyal_20";
		break;
		
		case "portroyal_20":
			dialog.text = "Bu ismi daha önce hiç duymadım. Kim o?";
			link.l1 = "Ah, ilginç biri değil... sadece macera ve hazine peşinde koşmayı seven bir adam. Ama madem duymadın, ondan bahsetmeyelim.";
			link.l1.go = "portroyal_21";
		break;
		
		case "portroyal_21":
			dialog.text = "Evet, konuşmayalım! Onun yerine eski Avrupa'dan bahsedelim! Yirmi yıl önce İskoçya'da olduğumu hatırlıyorum...";
			link.l1 = "...";
			link.l1.go = "portroyal_22";
		break;
		
		case "portroyal_22":
			DialogExit();
			AddDialogExitQuest("GuardOT_MCOutFromArchyRoom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
