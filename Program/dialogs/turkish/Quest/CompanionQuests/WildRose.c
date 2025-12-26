void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		// =================================================================
		// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+"Hey, buraya bak!";
			link.l1 = "Sessiz ol, "+npchar.name+", burada yalnız olmayabiliriz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = ""+pchar.name+"!";
			link.l1 = ""+npchar.name+"? Beni buraya kadar mı takip ettin, di mi?";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "Ve sanırım haklıymışım, tamam mı! Burada ne oldu?";
			link.l1 = "Bunu bilseydim, "+npchar.name+", keşke bilseydim...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "Aman Tanrım...";
			link.l1 = "Evet, zavallı canı çekişmiş ölmeden önce. Hiç kimse böyle bir sona layık değil...";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "Ve şu karşıdaki adam onun kocası mı? Ne halt ediyorlardı ormanda?! Kaçak köleleri duymadılar mı?";
			link.l1 = "Artık o soruya cevap veremeyeceklerinden korkuyorum...";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "Sence bunu yapan hâlâ buralarda bir yerde mi, di mi?";
			link.l1 = "Gayet mümkün. O yüzden sessiz olalım – onları görmeden önce bizi görmemeleri lazım, tamam mı?";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "Çok geç, "+pchar.name+" .  Görünüşe bakılırsa çoktan fark edildik. Şuraya bak.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Vay vay, çocuklar, şuna bir bakın. Burası tam bir âşıklar köşesi olmuş, değil mi, heh-heh. İki sevdalı daha yeni pes etmişken, hemen yerlerine başka bir çift çıkageliyor...";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "Çok akıllıca. Ama saymayı bilmiyor musun? O zavallıların aksine, burada yalnız değiliz.";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "Bize gelince işler biraz daha karışık olacak, bana güvenebilirsin...";
				link.l1.go = "Naemnik_4";
			}
		break;
		
		case "Naemnik_2":
			dialog.text = "Sana onların hepsinden daha akıllı olduğunu söylemek isterdim – ama bu düpedüz bir yalan olurdu. Sayınız fazla olsa bile o alçakları alt edemezdiniz. Ve o güzel kızın da, ayaklarının dibinde yatan şu zavallıdan farksız olurdu...";
			link.l1 = "Kaçak kölelerden mi bahsediyorsun? Bu onlardan biri mi? Yani, Bishop’un adamlarından mısın?";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "Hepsine evet, tamam mı? İki günden fazla süre boyunca askerlerle birlikte onları adanın dört bir yanında kovaladık. Sonra o alçaklar ikiye ayrıldı. Bir kısmı mağaraya doğru çekildi, peşlerinden muhafızlar gitti, kalanlar ise körfeze kaçtı. Bize buradan yarım mil batıda pusu kurdular ve birkaç adamımızı kaybettik. Yeniden toparlanıp ne yapacağımızı düşünürken, onlar... o aptal kıza istediklerini yaptılar...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		
		case "Naemnik_4":
			dialog.text = "Kürdanını kendine sakla, süslü—benim de çocukların da sinirini bozma. Körfezde yere serdiğimiz o heriflerden bir düzineyle çevrilmiş olsan ne yapardın, görmek isterdim. İçlerinden sadece biri şanslı çıktı—ama o da uzun sürmedi... O herif Bishop’un eline geçtiği an...";
			link.l1 = "Yani onun paralı askerleri siz misiniz, di mi?";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "Açıkçası garnizon askerleri değil. O aylaklar olmasaydı, o alçakları dün yakalardık—ve o aptal adamla karısı hâlâ hayatta olurdu...";
			link.l1 = "Yani, bu senin işin değil...";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Bizi kim sanıyorsun, ha? Tamam, melek değiliz ama canımız isterse geneleve gideriz, başka yere değil...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "Yalan söylüyor, hem de göz göre göre – o pis herif! Onu dinleme, "+GetAddress_Form(NPChar)+"! O zavallı insanlara bir fiske bile vurmadık, tamam mı!";
			link.l1 = "Gerçekten mi? Peki, neden sana inanalım da ona inanmayalım, ha?";
			link.l1.go = "Naemnik_8";
			link.l2 = "Tamam mı? Yoksa aslında yalan söyleyen sen misin? Bana pek aziz gibi görünmüyorsun.";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "Ya, bir düşün kendin için, Allah aşkına! O canavar Bishop’tan kaçıyorduk, iki gün boyunca ormanda dolandık, izlerimizi gizledik – peki neden? Şimdi zavallı bir kadına kötülük yapıp o kan emicilerin bize yetişmesine izin vermek için mi?! Arkadaşlarım o sahile ayaklarını zor sürüdüler, "+GetAddress_Form(NPChar)+"! Tüfeklerimizi ateşleyecek halimiz bile yoktu, yoksa o alçaklara asla pis işlerini yaptırmazdık... Her şeyi onlar yaptı, gözlerimizle gördük!.. ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "Ya, bir düşün hele kendin için, Allah aşkına! O canavar Bishop’tan kaçıyorduk, iki gün boyunca ormanda izimizi kaybettik – neden? Şimdi zavallı bir kadını utandırıp o kan emicilerin peşimize düşmesine izin vermek için mi?! Arkadaşlarım o sahile zar zor ayak bastı, "+GetAddress_Form(NPChar)+"! Tüfeklerimizi ateşleyecek halimiz bile yoktu, yoksa o alçaklara asla pis işlerini yaptırmazdık... Her şeyi onlar yaptı, gözümüzle gördük!.. ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "Kapa çeneni, Casper, seni pis köpek!";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "Ne dedin?!";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "Sağır mısın, bayan? Ona çenesini kapamasını söyledim. Bizim Jerry saatlerce hikaye anlatabilir – bu konuda gerçekten yetenekli! Bishop dilini kesip ona yedirmek istedi, ama sonra acıdı. Bana sorarsan yazık oldu!";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "Ama... Ona Casper dedin, di mi...";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "Dinle dostum, sevgiline açıkla, insanlar, şu serseri gibi pislikler bile, sadece bir isimden fazlasına sahip. Güzel kadınların bazen mantıksız olabileceğini duydum ama lanet olsun...";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "Bunların hesabını vereceksin, tamam mı!";
			link.l1 = "Mary, bekle! Bunu kendim halledeceğim. Silahını indir. Hemen şimdi.";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "Vay canına, demek burada gerçek bir centilmenimiz var. Senin davranışların o küçük solucanın cıyaklamasından çok daha yerinde, doğrusu. Karısından bile daha çok bağırıyordu – o kadar ki, şu tepenin arkasından bile duyuluyordu sesi. Açıkçası, bize biraz da yardımcı oldu – o sayede o alçakların izini bulduk...";
			link.l1 = "Burada Karayipler'de, asalet pek rastlanan bir şey değil. Şimdi, derin bir nefes alalım—şu anda burada ölüp gitmekte hiç asil bir taraf yok.";
			link.l1.go = "Naemnik_17";
			link.l2 = "Buradaki tek alçaklar sizlersiniz. Hemen Mary'den özür dileyin, belki o zaman kan dökülmeden bu işi halledebiliriz.";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "Buna karşı çıkmak zor. Ama önce, biraz sakin ol...";
			link.l1 = "Adı Mary Casper. Sanırım bu, çoğu şeyi açıklıyor.";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "Casper? O onun kızı falan mı, ha-ha?";
			link.l1 = "Bundan ciddi şekilde şüpheliyim. Ama umarım artık anladın ve sözlerini geri alırsın.";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "Geri mi geldin? Yoksa ne? Bana düello mu teklif edeceksin? Hadi bakalım... Eğer o kıymetli sevgilini ormanın ortasında tek başına bırakmaya cesaretin varsa tabii, heh-heh. Çocuklar ve ben böylesi bir gelişmeden çook memnun olurduk.";
			link.l1 = "Bak işte, gerçek yüzünü gösteriyorsun. Masken uzun sürmedi, tamam mı?";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_22":
			dialog.text = "Sen, bayım, tam bir çelişkisin – bir yandan huzurlu, öte yandan tam bir hödük. Ve söyle bakalım, ben neden bu kızıl saçlı deli için af dileyecekmişim, ha?";
			link.l1 = "Adı Mary Casper, ve...";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "Casper? Vay canına! Jerry, bu senin küçük kızın olabilir mi, ha? Ha-ha-ha-ha! Kulaklarıma inanamıyorum! Kim tahmin edebilirdi ki!";
			link.l1 = "Gül bakalım, ne kadar sürecek. Senin gibiler - laf çok, terbiye yok - kadınları hiçe sayar, bunu da eğlence sanır. Ahırda doğmuş, çakalların elinde büyümüşsün sanki - görgün ondan böyle. Ama kafan samanla doluysa, nezakete yer kalmaz tabii.";
			link.l1.go = "Naemnik_24";
		break;
		
		case "Naemnik_24":
			dialog.text = "Vay vay... Ne arsız bir küçük solucan. Söylesene dostum, senin kız hamakta iyi midir?  Gerçi, şüphelerim var... ama kendim öğrenmekten memnuniyet duyarım.";
			link.l1 = "Bak işte, gerçek yüzünü gösteriyorsun. Masken uzun sürmedi, tamam mı?";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "Onlara gerçekten iyi bir ders verdin, "+GetAddress_Form(NPChar)+", - o alçaklar. Cehennemde yansınlar! Keşke sana zamanında yardım edebilseydim. Buraya gelirken gördüğüm tüfek çok uzaktaydı. Kaçarken bizden biri düşürmüş galiba. Keşke o pislik Primer'ı kendim vurabilseydim.";
			link.l1 = "Primer seni bayağı zorluyordu galiba, geri dönmeye karar verdiğine göre.";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "Az bile söyledin. O köpek yüzünden sırtımda izler var. En kötüsü de, canı ne zaman isterse bize su vermemeyi seçebiliyordu.";
			link.l1 = "Ne yazık ki o alçaklardan bir tanesi bile sağ kalmadı. Onu askerlere teslim edebilirdik, eminim yakında burada olacaklar.";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "Nedenini tam olarak bilmiyorum, şey, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Bak şimdi... Komutan ondan zorla itiraf alırdı, böylece senin adını—ve ölen arkadaşlarının adını—temize çıkarırdı.";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "Ha-ha, tabii, tabii. Sonra da William Bishop kendi derimi yüzermiş. Bunu tarladaki siyahi bir adamdan duydum... Bishop için siyah ya da beyaz olman fark etmiyor - kaçaklarla aynı hızda ilgileniyor, hiç ayırt etmez. ";
			link.l1 = "Korkarım, bir şekilde plantasyona geri dönmek zorunda kalacaksın...";
			link.l1.go = "Djerry_5";
			link.l2 = "Yani plantasyona geri dönmeyecek misin?";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "Sen tam bir şakacısın – sana bunu daha önce söyleyen oldu mu, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Şaka yok, "+npchar.name+". Buraya tesadüfen mi düştüğümü sanıyorsun? Senin o küçük grubunu bulmak için ormana girdim, hepinizi plantasyona geri sürükleyip biraz altın kazanacaktım. Ama geriye bir tek sen kaldın. Tek başına pek bir değerin yok, belki de seni bırakırım. Ama söyle bakalım, ne düşünüyordun? Yalnızsın. Diğerleri öldü. Ne umuyorsun, Allah kahretsin? Dağlarda, çalılıklarda saklanıp bir kurşun seni bulana, ya da sıtmadan ölene ya da bir jaguar tarafından yenene kadar böyle mi devam edeceksin?";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Djerry_6":
			dialog.text = "Sen tam bir şakacısın – sana bunu daha önce söyleyen oldu mu, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Şaka yok, "+npchar.name+". Buraya tesadüfen mi düştüğümü sanıyorsun? Senin o küçük grubunu bulmak için ormana girdim, hepinizi plantasyona geri sürükleyip biraz altın kazanacaktım. Ama geriye bir tek sen kaldın. Tek başına pek bir değerin yok, belki de seni bırakırım. Ama söyle bakalım, ne düşünüyordun? Yalnızsın. Diğerleri öldü. Neyin peşindesin, Allah kahretsin? Dağlarda, çalılıklarda saklanıp bir kurşun seni bulana, ya da sıtmadan ölünceye, ya da bir jaguar seni yiyene kadar böyle mi devam edeceksin?";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "Böylesi daha iyi, Tanrı bilir, "+GetAddress_Form(NPChar)+" - Bana sorarsan, bu, Bishop'un bana hazırladığı işkencelerden ölmekten çok daha iyi bir kader. Ama dürüst olmak gerekirse, o kadar da kötü değil – Ragged Point yakınlarında yelkenli bir tekne sakladım.";
			link.l1 = "Barbados'a en yakın topraklar, yerlileriyle Dominika ve İspanyolların olduğu Tobago. Hangisinin senin için daha kötü olduğunu bile söyleyemem...";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "Bence şansımı donlarla deneyeceğim – kaçakçılar ve korsanlar sık sık Tobago'ya demir atar. Ah, o onaylamayan bakışı görüyorum, "+GetAddress_Form(NPChar)+". Ama ülkeme sadakatle hizmet ettim. Beni taş ocaklarına attığında ne yapmam gerekiyordu, söylesene?";
			link.l1 = "Yargılamıyorum, "+npchar.name+". Herkesin kendi yolu var. Şimdi biraz daha barut ve mermi al, git. Askerler gelmeden önce.";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "Teşekkür ederim, "+GetAddress_Form(NPChar)+". Ve sen, genç hanım, ıı, Mary. (eğilir). Tabii ki akraba değiliz, ama böyle bir, ıı, durumda aynı soyadı taşıyan biriyle karşılaşmak... oldukça beklenmedik ve...";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "Sanırım öyle, tamam mı? Ve şimdi, elveda, Jerry.";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", bir şey mi canını sıkıyor? Adaşına pek çabuk veda ettin, di mi?";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "Bir an önce o adamın yanından kurtulmak istedim... Anlattıkları baştan sona delik deşik, tamam mı?";
			link.l1 = "Ne diyorsun, sevgilim?";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "Bishop’un uşağından duyduklarımızdan sonra, o zavallıların onun elinden öldüğüne hiç şüphem yok. Ama ondan önce... Casper – onun söylediklerine dikkat ettin mi, di mi?";
			link.l1 = "Peki, ne içini rahatsız etti, canım?";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "Sahilde gizlenmiş bir tekne olduğunu söylüyor. Ama plantasyondan yirmiden fazla kişi kaçtı. O zaman tekne bayağı büyük olmalı, değil mi? Jerry donanmadan firar etmiş biri, tek başına büyük bir tekneyi idare etmenin hiç de kolay olmadığını çok iyi biliyor, tamam mı...";
			link.l1 = "Tek yapması gereken yelkeni açıp rotayı tutmak – gerisini rüzgar halleder. Elbette, büyük bir risk alıyor, ama belki de denizde ölmek, bir plantasyon celladının elinde ölmekten gerçekten daha iyidir.";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "Belki. Ama şimdi fark ettim ki başka bir şey daha var, kafama yatmıyor... Ona göre, o ve arkadaşları uzaktan izleyip paralı askerlerin o zavallı kıza yaptıklarını seyretmişler...";
			link.l1 = "Teknelerine deli gibi koşmak yerine... Tamam mı, nereye varmak istediğini anlıyorum, "+npchar.name+". Belki Bay Casper'a birkaç soru daha sormalıyız, tamam mı?...";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = " Hey, "+npchar.name+", eski dostum! Bir dakika bekle...";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = " Kahretsin!!! Mary, dikkat et!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "Alçak herif! Onun hayatını kurtardık, o ise! Yani bu ne demek oluyor, "+pchar.name+"Tamam mı? Demek ki öyleymiş...";
			link.l1 = "Eyvah, "+npchar.name+", burada ne olduğunu bilen hayatta kimse kalmadı artık...";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "Buradan gitmeliyiz, "+pchar.name+". Eğer askerler bizi burada bulursa, başımız belaya girer, tamam mı?";
			link.l1 = "Haklısın, Mary. Hadi gidelim...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "Biliyor musun, "+pchar.name+", bunca şeyden sonra, gerçekten güzel bir içkiye ihtiyacım var, tamam mı.";
			link.l1 = "Orada sana katılıyorum, sevgilim. Benim de bir içkiye ihtiyacım var. ‘Irish Cuckold’a uğrayalım.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "Uyandırdığım için üzgünüm, Kaptan...";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Pekâlâ, en azından kapıyı çaldın, bu da bir şey. Şimdi söyle bakalım—benden ne istiyorsun?";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "Kapıyı çalman iyi olmuş, dostum. Pat diye dalsaydın, şimdi merdivenlerden yuvarlanıyor olurdun.\nNe bakıyorsun öyle? Söylesene—neden kendini buraya attın?";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "Kasabalılardan biri seninle görüşmek istiyor – Lewis Gernon. Seninle konuşmak istediği önemli bir şey olduğunu söylüyor.";
			link.l1 = "Bu ismi daha önce hiç duymadım. Umarım gerçekten önemli bir şeyi vardır da... beni böyle bir işten alıkoymaya değiyordur. İçeri alın onu...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "Merhaba, bayım "+pchar.lastname+". Bayan... Casper.";
			link.l1 = ""+TimeGreeting()+", bayım "+npchar.lastname+". Daha önce tanıştığımızı hatırlamıyorum. Peki bizi nereden tanıyorsun?";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "Hatırlamıyor musun? Ah, anladım... Yüzüm kan ve toz içindeydi, birkaç saat önce aynada kendimi gördüğümde ben bile dehşete kapıldım...";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "Sen... sen o adamsın, tamam mı, seni bulduk ve...";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "Ve benim Susan'ım. Zavallı Suzie'm...";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "Öldüğünü sandık. Ve... O senin karındı, tamam mı?";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "Evet hanımefendi. O benim karımdı ve ben korkudan donup kalmıştım... hiçbir şey yapamadım. Tanrım, Tanrım...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "(hıçkırarak) Beni dövdüler ve izlememi sağladılar...";
			link.l1 = "Kalk, "+GetAddress_Form(NPChar)+". Suç sende değil. Kimse bu kadar katile karşı tek başına duramazdı.";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "O kadar çok vardılar, o kadar çok... Ama yine de, ben...";
			link.l1 = "Ama yine de hayatta kaldın ve karının katilleri cehennemde yanıyor. Küçük bir teselli belki, ama yine de bir şey, Bay "+npchar.lastname+" . Ama sana sormak istediğim bir şey vardı...";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "Tamam mı, bayım "+pchar.lastname+"?";
			link.l1 = "Bunlar kimdi? Piskoposun paralı askerleri mi yoksa kaçak köleler mi?";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "Jeremy Casper ve diğer kaçaklardı. Bruce Primer ve adamları hakkında yanılmışsın.";
			link.l1 = "Piskopos'un paralı askerleri mi?";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "Evet. Bruce kesinlikle bir alçaktı ve Bishop için birçok pis iş yaptı, ama tecavüzcü değildi";
			link.l1 = "O anda bana öyle gelmemişti. Ama seninle tartışmayacağım, "+npchar.name+". Ama, bilincin yerindeydi ve her şeyi gördün, ayağa kalkıp...";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "Beni affet, "+GetAddress_Form(NPChar)+".   Bana zavallı bir korkak diyebilirsin – ama gerçekten kıpırdayamadım, o kadar korkmuştum ki. O alçaklar Suzie’yle benim yolumuzu kestiğinde, önce var gücümle çığlık attım, belki biri yardıma gelir diye umarak.";
			link.l1 = "Ve seni dövdüler.";
			link.l1.go = "Lewis_13";
		break;
		
		case "Lewis_13":
			dialog.text = "Jerry tüfeğinin dipçiğiyle bana vurdu, sonra da Susan'ın gözleri önünde beni parça parça edeceğini söyledi. Ben... Bunu itiraf etmekten utanıyorum ama, sanırım korkudan birkaç saniyeliğine bayıldım bile. Ve o sırada...";
			link.l1 = "Sizi anlıyorum, beyefendi "+npchar.lastname+". Yaptıklarında utanılacak hiçbir şey yok. Senin yaşadıklarını herkes kaldıramazdı. Keşke müdahale etseydin – ama olan oldu artık. Yine de, en azından karının katillerinden birini öteki tarafa gönderebildiğimize seviniyorum – neredeyse bizi kandıracaktı ama.";
			link.l1.go = "Lewis_14";
			link.l2 = "Yani neredeyse Bishop’un paralı askerleriyle dövüşürken öldürülüyorduk – sırf korktuğun için, öyle mi? Ne hoş bir bahane, "+npchar.name+". Sonunda işleri çözebildiğimiz iyi oldu, biraz geç olsa da...";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "Tamam mı, "+GetAddress_Form(NPChar)+". Bunun için sana teşekkür etmeye geldim. İlk başta ona inanmış olsan bile...";
			link.l1 = "Bruce Primer bunun olması için elinden geleni yaptı, kahretsin onu. Keşke biraz diline sahip olsaydı...";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "Tamam mı, "+GetAddress_Form(NPChar)+". Bunun için sana teşekkür etmeye geldim. İlk başta ona inanmış olsan bile...";
			link.l1 = "Bruce Primer bunu olması için elinden geleni yaptı, kahretsin onu. Keşke biraz diline hakim olsaydı...";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "Ne yazık ki, o gün hepimiz hata yaptık... Susan'la ben Ragged Point'ta yürüyüşe çıkmamalıydık, Bruce dilini tutmalıydı... Ve sen de Jeremy'ye güvenmemeliydin. Ama Casper Hanım sayesinde adalet yerini buldu.";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "Bence bana ne soracağını biliyorum, bayım "+sld.lastname+". Ama o adamla hiçbir alakam yok.";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "Biliyorum, hanımefendi. Bu odaya adım attığım anda fark ettim. Sizinle onun arasında en ufak bir benzerlik yok. Ama yine de, Susan... o, bu dünyada hiçbir şeyin tesadüf olmadığından emindi.";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "Karın haklıydı. Bunu kendim de birden fazla kez gördüm, tamam mı. Ve aynı şekilde "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "Çok doğru. Ama bence şimdi felsefi konuşmaların zamanı değil. Sana faydası olacağını sanmıyorum, "+npchar.name+" . Böyle şeylerde ancak zaman yardımcı olabilir.";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "Belki de haklısın, beyefendi "+pchar.lastname+". Peki, tekrar teşekkür ederim ve hoşça kalın. Size ve Bayan Casper'a dua edeceğim.";
			link.l1 = "Kendine iyi bak, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Biliyorum, sevgilim, neredeyse o herifi serbest bırakacaktım...";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "Jerry Casper adında bir piç.";
			link.l1 = "Evet... Bekle... Yani, sen şimdi onun...";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "Biliyorum, çok aptalca geliyor...";
			link.l1 = "Kesinlikle! Peki ya soyadın Smith ya da Jones olsaydı? O isimlerle sokaklarda dolaşan sayısız insan var – ve içlerinden bazıları kesin bir kötülük yapacaktır... O Jerry yok mu, cehennem ateşlerinde yansın – belki de o hiç Casper bile değildir...";
			link.l1.go = "Mary_34";
			link.l2 = "Aynen öyle, canım. Bildiğimiz kadarıyla, o Jerry bile olmayabilir - rahatlıkla sahte bir isim kullanmış olabilir.";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "Ve yine de... Beni anlamadığını biliyorum ama bir düşün, onun soyadı seninki olsaydı ne hissederdin, hayal etsene "+pchar.lastname+".";
			link.l1 = "Aynı şey değil, Mary. "+pchar.lastname+" – asil bir aile soyadı, ve...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "Ve yine de... Beni anlamadığını biliyorum, ama bir düşün, onun senin soyadını taşıdığını hayal etsen ne hissederdin? "+pchar.lastname+".";
			link.l1 = "Aynı şey değil, Mary. "+pchar.lastname+" - soylu bir aile adı, ve...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "Ve Casperlar, şey, biz sadece isimsiz, ailesiz insanlarız, değil mi? Sanırım senin beni fark ettiğine, hem de öyle burnu havada birini değil de beni gördüğüne her gün Tanrı'ya şükretmem gerek...";
			link.l1 = ""+npchar.name+", ben hiç de öyle demek istemedim – bunu anlıyorsun, değil mi? Soylu bir ailenin üyeleri kan bağıyla bağlıdır – bu, sadece birisiyle aynı soyadını paylaşmaktan çok farklı bir şey. Ki dediğim gibi, birisi o soyadını kendine kolayca almış olabilir...";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "Sadece bununla ilgili değil, "+pchar.name+"...";
			link.l1 = "Tatlım, uzun ve zorlu bir gün geçirdik. Kilometrelerce ormanda yürüdük, ölümden döndük... sonra da neredeyse hiç uyuyamadık. Kafanda tuhaf düşünceler olması normal. İkimizin de tek ihtiyacı güzel bir uyku, tamam mı?";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "Bence bunda hiç garip bir şey yok, ama tamam mı... yarın konuşalım.";
			link.l1 = "Kafamız berrakken, her şeyi çok daha çabuk hallederiz. Uzan biraz, sevgilim, bu günü geride bırakmamız lazım.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "İyi misin, "+GetAddress_Form(NPChar)+"? Garip görünüyorsun, sanki bir hayalet görmüşsün gibi. Biraz rom ister misin? Ya da şarap? Harika bir seçimimiz var, biraz rahatlamana iyi gelir, di mi?";
			link.l1 = "İçki cehenneme gitsin. Ben bir kızı arıyorum...";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "O zaman yanlış yere geldiniz, Kaptan. Burası bir meyhane, genelev değil. Dışarı çıkarsanız, tam karşıda göreceksiniz...";
			link.l1 = "Dinle, şaka yapacak havamda değilim. Kırmızı ceketli, kızıl saçlı bir kızı arıyorum, silahlı. Adı Mary Casper.";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "Pekala, şaka yapmıyorsak, sana anlatacak bir şeyim yok. Vardiyam bir saat önce başladı ve burada kırmızı paltolu kızıl saçlı birini görmedim.";
			link.l1 = "Yani gece vakti gitmiş... Ama nereye gitmiş olabilir ki?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "Günaydın, sevgilim! Oldukça uzun uyudun...";
			link.l2 = "Beni gerçekten endişelendirdin orada, "+npchar.name+". Bir daha böyle ortadan kaybolma, haber vermeden...";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "Seni uyandırmak istemedim. Hem bazen sen de böyle sessizce kayboluyorsun, hiç haber vermeden...";
			link.l1 = "Bana aynı şekilde karşılık vermeye mi karar verdin?";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "Açıkçası, sadece biraz kendi başıma kalıp düşünmek istedim, tamam mı. Endişelenmeni istemedim.";
			link.l1 = "Bir şey mi canını sıkıyor?";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "Dün yaptığımız konuşma. Soyadları, kan bağları hakkında...";
			link.l1 = "Yani, sonunda gerçekten bana kızgınsın, öyle mi...";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "Hiç de öyle değil, canım, demek istediğim bu değildi. Sadece birdenbire fark ettim ki kendi ailem hakkında hiçbir şey bilmiyorum. Mesela sen – soylu bir ailenin oğlusun. Gemideki çocuklar da arada sırada aileleriyle ilgili bir iki hikaye anlatıyorlar. Ama ben – anlatacak hiçbir şeyim yok. Anne babamı hiç tanımadım. Hatta nerede doğduğumu bile bilmiyorum...";
			link.l1 = "Adalet Adası'nda değil miydi?";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "Eric, beni büyüten adam, hep böyle derdi. Ama eğer bu doğruysa, neden Adada kimse ailemden hiç bahsetmedi? Bir kelime bile, öylesine bir laf bile yok. Bir keresinde Donald Greenspen’e sordum, ama bana net bir cevap veremedi.";
			link.l1 = "Ya da belki de istemedi.";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "Kesinlikle! Ben de aynı şeyi düşündüm, tamam mı? Biliyor musun, eskiden hayatımı pek düşünmeden yaşardım. Ama dün o herif Jerry’yle karşılaştığımızda... Kendime sordum—kimdi benim babam? Annem? Neden kimse bana onlardan hiç bahsetmedi, sanki hiç var olmamışlar gibi? Ya babam da o Jerry kadar alçak biriyse?";
			link.l1 = "Hiç önemi yok, "+npchar.name+". Başkaları tarafından büyütüldün – ve harika bir iş çıkardılar.";
			link.l1.go = "Mary_50";
			link.l1 = "Bunun böyle olduğundan şüpheliyim. Ve neden önemli olduğunu da pek anlamıyorum, çünkü daha önce hiç umursamış gibi görünmedin.";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "Ama bana önemli, "+pchar.name+", tamam mı? Ben de istiyorum, benim de hakkım var, kim olduklarını bilmeye. Sence de öyle değil mi?";
			link.l1 = "Elbette katılıyorum, hiç şüphem yok. Ama babanla annen hakkında bir şeyler öğreneceksek, bunu ancak Adalet Adası’nda yapabiliriz. Sonuçta, isimlerini bile bilmiyorsun, değil mi?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "Ama bu benim için önemli, "+pchar.name+"Evet, tamam mı? Bilmek istiyorum, kim olduğumu, anne babamın kim olduğunu öğrenmeye hakkım var. Sence de öyle değil mi?";
			link.l1 = "Elbette, kesinlikle katılıyorum, hiç şüphem yok. Ama eğer annenle baban hakkında bir şeyler öğreneceksek, bunu ancak Adalet Adası’nda yapabiliriz. Sonuçta, isimlerini bile bilmiyorsun, di mi?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "Hayır, canım. İsimlerini hiç duymadım ki, tamam mı.";
			link.l1 = "O zaman sömürge arşivlerine gitmek için henüz erken. Önce o gemi mezarlığına dönüp orada atalarına dair bir iz bulmaya çalışmamız gerekecek.";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "Beni anladığına sevindim, "+pchar.name+". Teşekkür ederim.";
			link.l1 = ""+npchar.name+", gerçekten beni şaşırtıyorsun, biliyor musun. Bu, senin için yapabileceğim en az şey, aşkım.";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "Nasıl olduysa, neredeyse yirmi yıl boyunca onlar hakkında hiçbir şey bilmeden yaşamayı başardım...";
			// dialog.text = "Sonuçta, yirmi yıldan fazla bir süredir beni hiç rahatsız etmedi...";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "Yani, biraz daha bekleyebilirim.";
			link.l1 = "Bunun senin için önemli olduğunu görüyorum, "+npchar.name+". O yüzden seni fazla bekletmemeye çalışacağım, sevgilim. Şimdi hadi gidelim, gemiye dönmemiz lazım. En azından orada olduğunu bilmek bana iyi gelecek.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "Evimizin kıyıları... Biliyor musun, "+pchar.name+", on yıl sonra buraya geri gelsek bile her şey yine şu anki gibi olurmuş gibi hissediyorum, tamam mı.";
			link.l1 = "Belki, "+npchar.name+", belki. İç halkadaki gemiler su üstünde kalacak, ama burada yaşayan insanlar farklı olacak.";
			link.l1.go = "Mary_62";
			link.l2 = "Bundan çok şüpheliyim. Buradaki her şey zaten pamuk ipliğine bağlı. Bir tamircinin dehası sayesinde.";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "Ve on ya da on beş yıl önce bu batıklarda yaşayanları zar zor hatırlıyorum. Sadece bana en yakın olanları—Alan, Eric...";
			link.l1 = "Sanırım hayat böyle işliyor. Her şeyi ve herkesi hatırlamak mümkün değil. Benim de hafızamdan isimler ve yüzler siliniyor – hem Paris günlerimden, hem de Gascony’den. Oysa bunun sadece yaşlılara özgü olduğunu sanırdım.";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "Ve on beş, on yıl önce bu enkazlarda yaşayanları zar zor hatırlıyorum artık. Sadece bana en yakın olanları – Alan, Eric...";
			link.l1 = "Sanırım bu böyle oluyor. Her şeyi ve herkesi hatırlayamazsın. Ben bile Paris'teki günlerimden isimleri ve yüzleri unutuyorum—Gascony'yi hiç saymıyorum bile. Bir de bunun sadece yaşlılara olduğunu sanırdım.";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = "Ama burası... Bambaşka bir dünya gibi, di mi? Düşünsene, buraya yakın zamanda gelenlerden bazıları, burada zamanın Anakaraya göre neredeyse üç kat daha hızlı aktığını söylüyorlar...";
			link.l1 = "Ha-ha, peki bu seni kaç yaşında yapıyor, di mi?";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "Ciddiydim, "+pchar.name+", tamam mı!";
			link.l1 = "Ciddi olacaksak, artık işe koyulma zamanı. Narwhal’lar arasında Greenspen’den daha yaşlı biri var mı, tamam mı?";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "Mmm, hayır, sanmıyorum. Ama zaten sorduğumda bana hiçbir şey söylemedi, bunu sana söylemiştim.";
			link.l1 = "Yine de, yirmi yıl önce ne olduğunu anlamamıza kim yardımcı olabilir, başka bir fikrim yok. En azından, şimdilik. O yüzden, rotamızı 'Esmeralda'ya çeviriyoruz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "Ah, "+pchar.name+" ve Mary, ne sürpriz ama! İkinizi de... sağ salim görmek güzel, heh-heh. Sadece geçen ay dış halkada iki ya da üç gemi battı - deniz bu aralar fena halde huzursuz. Ve bak, kilitli kapılara dalmayın sakın - lanet olası kilidi kıracaksınız, sonra yine ben tamir edeceğim. Donald’ı görmeye geldiniz, değil mi?";
			link.l1 = "Sana da iyi günler, dostum. Onu bizzat görmeye geldik. Ama kapı kilitli olduğuna göre ya başka bir gemiye taşındı ya da eski dostlarını görmek istemiyor.";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "Hiçbiri, haha. Greenspen şu anda dış halkada, antrenman yapıyor.";
			link.l1 = "Talimler mi? Gerçekten mi? Rivados'la yeni bir savaşa mı hazırlanıyor?";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "Savaş aslında hiç bitmedi, "+pchar.name+". Son zamanlarda eskisi kadar kavga çıkmıyor, tamam mı? Ama yine de, Sancho'nun meyhanesinde arada bir birinin suratına yumruk iner... bazen de bıçak çekilir, hani.";
			link.l1 = "Hmm, eskiden klan üyeleri meyhaneye pek uğramazdı, di mi?";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "Şey, sen Adalet Adası'ndan ayrıldığından beri birkaç şey değişti. Donald ve Eddie insanları şimdilik idare ediyorlar. Ama yarın ne olur, kim bilir? İşte bu yüzden yaşlı Donny bütün bunları başlattı...";
			link.l1 = "Bütün o zahmete Adada bir katliamı durdurmak için girdim, sadece sen burada tekrar askercilik oynayasın diye mi? Ve o dış halkada ne zamandır dolanıp duruyor?";
			link.l1.go = "Schmidt_5";
			link.l2 = "Tatbikatlar iyi hoş da, zaten pamuk ipliğine bağlı olan ateşkesi riske atmaz mı? Hem Greenspen çocuklara ne zamandır talim yaptırıyor, biliyor musun?";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "Üç gündür ortada yok. Yarın öğlene kadar dönmesi gerekiyordu. Şuradaki tüfekleri öyle bir ovalıyorlar ki, sabaha kadar ateşleyecek bir şeyleri kalmayacak! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Schmidt_6":
			dialog.text = "Üç gündür yok. Yarın öğlene kadar dönmüş olur. Şuradaki tüfekleri öyle bir ovalıyorlar ki, yarına kadar ellerinde ateşleyecek bir şey kalmayacak! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "'Ceres Smithy'deki kamarım hâlâ boş mu? Yoksa birisi çoktan yerleşti mi?";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "Her şey orada en son gittiğinde nasılsa yine öyle. Kapıyı bile açmadık. Doğrusunu istersen, bu süre boyunca ne temizledik ne de kilide yağ sürdük. Yani, kırman gerekirse, sadece söylemen yeterli.";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "Tabii ki. Teşekkür ederim, Jurgen.";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "Ve gerçekten, her şey olduğu gibi duruyor. Eşyalarım bıraktığım yerde – sanki hiç gitmemişim gibi... Seninle ilk burada tanışmıştık, "+pchar.name+" . Hatırlıyor musun?";
			link.l1 = "Tabii ki! O ikisini öyle güzel hallettin ki, O ikisini öyle güzel hallettin ki, ben de doğranırım diye korktum.";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "Hiç de öyle değildi, tamam mı! Beni resmen ölümün pençesinden çekip aldın!";
			link.l1 = "Sanki kader beni buraya, sana getirdi.";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "Gerçekten öyle mi düşünüyorsun, sevgilim?";
			link.l1 = "Elbette, sevgilim. O günden beri de, beni doğrudan 'Ceres Demirhanesi'ne getirdiği için her gün şükrediyorum.";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"... Söylesene, beni ilk gördüğünde ne düşündün?";
			link.l1 = "Şey... Hatırladığım tek şey, o an olduğunda kalbim göğsümden fırlayacak gibi hissetti. Sen öyle...";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "Ne?";
			link.l1 = "Şimdiye kadar tanıdığım hiç kimseye benzemiyorsun. Zarafetin, sesin... ve o kırmızı ceket. Sana karşı hiç şansım olmadı. Biliyor musun, hep merak etmişimdir: Neden kırmızı bir ceket, elbise ya da korse değil?";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "Dokuz yaşındayken buldum onu, dış halkada. O zamanlar orada dolaşmaya bayılırdım—her yeni şeyi keşfetmek, adada bulamayacağın şeyleri bulmak, özellikle de kitapları. Onu denemek için can atıyordum ama o zamanlar üstüme giysem beni tamamen yutardı. Ben de onu diğer tüm hazinelerimi sakladığım yere gizledim—sudan çıkan karga yuvalarından birine.";
			link.l1 = "Ve ona alışınca, gidip onu geri mi aldın?";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "Birkaç yıl önce, kırmızı ceketli cesur bir deniz kaptanıyla ilgili bir kitap buldum. Hiçbir şeyden korkmazdı – hayatının aşkı için yüzlerce düşmanla yüzleşmişti. O zaman ilk kez bu ceketimi denemiştim. Beni cesur hissettiriyor.";
			link.l1 = "Ve o karşı konulmaz çekiciliğin, canım! Ama biliyor musun? Şu anda tek istediğim bir şey var... onu üzerinden çıkarmak...";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "Peki neyi bekliyorsun, cesur kaptanım?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "Günaydın, sevgilim. Narwhal'lar az önce 'Esmeralda'ya ve 'San Gabriel'e döndüler, Donald da onlarla birlikte. Onu sandallardan birinde gördüm, tamam mı.";
			link.l1 = "Günaydın, günaydın... Açıkçası, böyle bir geceden sonra öğlene kadar uyurdum, ama sen çoktan ayaktasın, etrafta dolanıp duruyorsun.";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "Dün, ceket ve karga yuvasından bahsetmiştik, oraya sakladığım yerden... Ve birden, o günlere karşı öyle bir özlem bastı ki içimi, hani herkesten gizlenip, sadece o geniş dünyayı anlatan kitapları huzurla okumak için oraya tırmandığım günlere... Kendimi tutamadım, oraya yelken açtım. Eskiden saatlerce orada kalırdım, ama bugün... Sadece gün doğumunu izledim. Ve anladım ki: dünyadaki her şeyden çok, senin yanında olmak istiyorum.";
			link.l1 = "Ve ben de senin yanında, "+npchar.name+". Ee, Donald’a gidelim mi? Konuşacak çok şeyimiz olacak.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+"Mary, seni görmek ne güzel! Dün buraya geldiğini bana çoktan söylediler. Aslında ben de ‘Ceres Demirhanesi’ne uğramayı düşünüyordum ama sen bu yaşlı adamdan hızlı çıktın. Ah, keşke ben de senin yaşında olsaydım...";
			link.l1 = "Senin de kendi enerjin bol, gördük zaten. Alıştırmalar nasıl geçti?";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "Beklediğimden daha iyiydi. Düşman gemilerine çıkma, kamaraları basma alıştırmaları yaptık... Sonuç olarak, iyi iş çıkardık. Tabii, çocukları biraz zorladım ama onlara iyi geldi. Uzun zamandır bacaklarını bu kadar açmamışlardı, ah, bayağı oldu, ha-ha.";
			link.l1 = "Peki, ne ilham verdi sana böyle şeyler yapmaya? Adalet Adası fazla sessiz mi geldi sana?";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "Hmm, sesinde bir hoşnutsuzluk tonu duyabiliyorum, "+pchar.name+". Sanırım buna hakkın var...";
			link.l1 = "Gerçekten, "+npchar.name+"?";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "Birbirimizin boğazını kesmemek için şu çürük gemi enkazlarının arasında epey koşturmak zorunda kaldın – bunu unutmadım. Kimse unutmadı.";
			link.l1 = "Ve çabalarımın karşılığı bu mu şimdi? Demek ki doğruymuş derler ya – gerçek bir savaşçıyı barış ağır gelir.";
			link.l1.go = "Grinspy_5";
			link.l2 = "Ve şunu da söylemeliyim, korsanlara ya da Rivados'a kıyasla senin sağduyuna çok daha fazla güveniyordum.";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "Bitirmeme izin ver. Evet, barışı korumayı başardık, ama aramızdaki farklar hâlâ duruyor. En azından o kara derili kafirlerle öyle. Geçen hafta Narwhal'lardan biri meyhanede çıkan bir kavgada öldürüldü. Ama biz de borcumuzu ödedik...";
			link.l1 = "Evet, evet - hep böyle başlar, di mi?";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = " Bırak bitireyim. Evet, barışı korumayı başardık, ama aramızdaki farklar hâlâ duruyor. En azından o siyah derili kafirlerle aramızda. Geçen hafta Narwhal'lardan biri meyhanede çıkan bir kavgada öldürüldü. Ama biz de borcumuzu ödedik...";
			link.l1 = "Tamam mı, işte her şey tam da böyle başlar.";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "İki konuda yanılıyorsun, "+pchar.name+"Öncelikle, bu bir başlangıç değil, bir devam. Eğer safça bunun sona ereceğini sandıysan, yanıldın. Ve ikincisi, ben öyle öteki yanağını dönecek azizlerden değilim. Zenciler yine kontrolden çıktı, ve bu hiç hoşuma gitmiyor. Bu arada, Dexter'ın da hoşuna gitmiyor ama kendini büyük bir siyasetçi sanıyor ve olayların dışında kalmayı tercih ediyor. Yani, biraz düşündükten sonra, kırılgan barışı korumanın en... acısız yolunu seçtim.";
			link.l1 = " Rivados'u küçük numaralarınla korkutmaya mı karar verdin?";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "Birkaç hafta önce, askeri yük taşıyan bir İngiliz kalyonu dış halkaya vurdu – içinde ne olduğunu duysan inanmazsın... Ama esas mesele, elli tane yepyeni tüfek ve birinci sınıf barut vardı. Sandallar da cabası... Üzerlerindeki boya bile daha kurumamıştı! Eskiler dökülüyordu zaten, fırtınalardan sonra sağlam kalan sandal da pek kalmadı, söyleyeyim...";
			link.l1 = "Ve bütün bunlar Narwhal'ların malı mı oldu?";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "Belki Amiral’le paylaşırdım, ama kendini etraftaki en akıllı kişi sanıyor ya, ben de aptal gibi görünmek istemem. Hem, ne dersen de, planım işe yaradı.";
			link.l1 = "Sana bir mektup gönderip adamlarını doğramayı bırakacağına dair söz mü verdi Kara Eddie?";
			link.l1.go = "Grinspy_10";
		break;
		
		case "Grinspy_10":
			dialog.text = "Black Eddie, zencilerine sessiz olmalarını emretti. Ben yokken daha da cesaretlenirler diye endişelenmiştim—ama tam tersi oldu: Rivadolar uslu uslu oturuyor, hem tayfamdan hem de eskiden arada sırada rahatsız ettikleri kasaba halkından uzak duruyorlar. Zenciler zencidir—güçten anlarlar. Alan hep böyle derdi, ve eğer yanılıyorsa, bu gemi hemen şimdi denizin dibini boylasın!";
			link.l1 = "Peki ya bir süre sonra yine başlarına buyruk davranmaya başlarlarsa, onları yola getirmek için yeni misket tüfeklerinle Fury ve Protector’a kurşun yağdıracak mısın, ha?";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "Fikir cesur ve biraz da pervasız, ama bence o noktaya gelmeyecek. Belki de sadece onların gemilerine baskın yapacakmışız gibi davranırız – sonra da Layton nihayet cesaretini toplar ve devreye girer. Adam biraz burnu havada oldu, doğru, ama kör değil. Ne bizim klanımızı ne de siyahileri yok etmek onun çıkarına değil – üç aşağı yukarı eşit güç merkezi işleri en azından bir nebze dengede tutuyor. Biri düşerse, her şey mahvolur. Eminim o da bunu anlıyordur – ama nedense onun işini yapmak yine bana kalıyor.";
			link.l1 = "Buradayken onu görmeye uğrayabilirim—tabii o da karşılık olarak o meşhur talimlerinden birini başlatmaya kalkmazsa, ha-ha.";
			link.l1.go = "Grinspy_12";
			link.l2 = "Fırsat bulursam uğrayıp onunla konuşmaya çalışırım. Kim bilir, belki de dinler.";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "Eğer birisi onu siyahları kontrol altında tutmaya ikna edebilecekse, o sensin, "+pchar.name+". Ama yüzlerinize bakılırsa, siyaset konuşmaya gelmediniz. Hadi bakalım, ne istiyorsunuz?";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "Ailem, Donald.";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "Ne istediğini tam olarak anlamıyorum, Mary.";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "Lütfen, bana onlardan bahset. Onları tanıyordun! Daha önce de sormuştum sana, ama bana cevap vermemiştin...";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "Ve işte bu yüzden Charles'ı buraya sürüklemeye karar verdin, ha-ha-ha! Sen bambaşkasın kızım, yalan söylüyorsam yıldırım çarpsın! Babanla annen hakkında sana hiç konuşmadıysam, sadece onları hiç tanımadığım içindi, hepsi bu!";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "Ama sen bizim klanın en yaşlı üyesisin, tamam mı! Ben kendimi bildim bileli buradasın...";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "Adalet Adası'na neredeyse yirmi yıl önce geldim, sen zaten doğmuştun. Sen küçücük bir şeydin, masaların ve taburelerin altından koşup sürünüyordun, zavallı Eric Udette'ye hiç huzur vermiyordun... Tabii ki, ona bu kadar yerinde duramayan bir çocuk nereden çıktı diye sordum – o da bana birkaç yıl önce Adada doğduğunu söyledi. Baban ya da annen hakkında tek kelime etmedi. Etse bile – ya hiç dikkat etmedim, ya da tamamen unuttum...";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = " Yıllar geçti... Anlıyorum Donald, gerçekten anlıyorum.";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = " Eric artık aramızda değil, ne yazık ki - buraya benden çok önce gelmişti. Bu arada, senin son maceralarını anlatırken sık sık Orelie Bertine’den bahsederdi. O yaşlı kadın sana bayılırdı, bunu çok iyi hatırlıyorum... Şimdi düşününce, sanırım sen doğduğunda o zaten Adalet Adası’nda yaşıyordu. Belki sana yardım edebilir?";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = " Belki. Onu ziyaret etmek için bir sebep işte. Uzun zamandır görmedim kendisini. Ne kadar düşüncesizim, tamam mı!";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "Bence sana kızgın değil. Ama üstüne fazla gitme – duyduğuma göre iyi değilmiş. Daha kötü bir şey olmasını istemeyiz...";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "Sus, Donald, başımıza iş açacaksın! Orelie hepimizden uzun yaşayacak, tamam mı?";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "Hadi gidelim, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "Elveda, "+npchar.name+". Yakında görüşürüz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "Merhametli Tanrım, az kalsın kalbim yerinden fırlayacaktı. İnsanları böyle korkutamazsın, tamam mı?";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "Jillian! Seni burada göreceğimi hiç düşünmemiştim, tamam mı? Ne yapıyorsun burada? Peki ya Orelie nerede?";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "Ve sana da merhaba, Mary. Ve sana da, "+pchar.name+". Orelie hasta, bilmiyor muydun? Onunla Brother Julian’ın isteği üzerine ilgileniyorum. Bana iksirler gönderiyor, ben de ona veriyorum ama... pek işe yaradıkları söylenemez. Şu anda kıçtaki kamarada, uyuyor. Onu oraya götürdüm ki burada biraz toparlanabileyim.";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "Bugün öğrendik, tamam mı. Donald söyledi bize. Nasıl o?";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "Pek iyi değil. Halsizlikten şikayet ediyor, yataktan zar zor kalkıyor. Bazen de anlaşılmaz bir şeyler mırıldanıyor, saçma sapan şeyler... O kadar çok eski günlerden hikaye dinledim ki, artık sayısını unuttum.";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "Hmm, işte tam da bunun için geldik buraya. Umarım bizimle konuşmayı reddetmez...";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "Bu gerçekten gerekli mi, Mary? Böyleyken onu rahatsız etmemeliyiz bence.";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "Bu, ailemle ilgili. Orelie onları tanıyor olabilir. Bu benim için gerçekten önemli, Jillian, tamam mı.";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "Adada onu iyileştirecek bir ilaç yok mu, di mi?";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "Julian Kardeş onun tentürlerini yapıyor. Ama bunlar sadece kısa bir süre işe yarıyor. Üstelik o zaman bile içmeyi reddediyor, neredeyse zorla boğazından aşağı dökmek zorunda kalıyorum. Bazen boğulacak diye korkuyorum – her şeyi yutmasını bile ben sağlamak zorunda kalıyorum...";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "Zavallı Orelie! Adada ona yardım edebilecek hiç kimse yok mu gerçekten?";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = " Sen de benim kadar iyi biliyorsun ki burada doğru düzgün bir hekim yok. Zaten ne yapılabilirdi ki? Yaşlılık kimseyi esirgemez... ";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+", belki gemimizden birini getirebiliriz?";
			link.l1 = "Korkarım, "+npchar.name+", burada ihtiyacımız olan bir gemi cerrahı değil, usta bir hekim, tamam mı?";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "Şu anda sihre inanabilirim, işe yarayacaksa, tamam mı.";
			link.l1 = "Hmm... Büyü mü? Belki Chimiset'le konuşmalıyım...";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "Chimiset mi? O kara büyücü mü? "+pchar.name+", ciddi misin?";
			link.l1 = "Her zamankinden daha fazla. Şu anda onun siyah mı beyaz mı olduğu umurumda bile değil. Orelie'ye başka kimin yardım edebileceğini bilmiyorum, sanmıyorum ki sen de biliyorsun. O yüzden çekil kenara ve sakın yoluma çıkmaya kalkma.";
			link.l1.go = "Jillian_16";
			link.l2 = "Kesinlikle. İlaçlar ona fayda etmedi. Julian Kardeş’in duaları da öyle. Chimiset son umudumuz.";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "Kulaklarıma inanamıyorum! Ama o... imansız bir adam!";
			link.l1 = "Ve o, ölmekte olan bir kadın – adını unutmasına bir nefes kalmış. Tamam mı, o bir büyücü, ama onların neler yapabileceğini duydum. İnanılmaz şeyler. Ve eğer onun aklını geri getirebiliyorsa, hangi tanrıya taptığının ne önemi var?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = " Kulaklarıma inanamıyorum! Ama o... dinsiz bir adam!";
			link.l1 = " Ve o, ölmekte olan bir kadın - kendi adını unutmasına bir nefes kalmış. Tamam mı, o bir büyücü, ama onların neler yapabildiğini duydum. İnanılmaz şeyler. Ve eğer onun aklını geri getirebilecekse, hangi tanrıya taptığının ne önemi var?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = ""+pchar.name+", dinle, Orelie’yi ben de önemsiyorum… Tanrı şahidim olsun, acısını hafifletmek için elimden geleni yapıyorum! Ama gerçekten o kara heretiğin bu kamarada ayin yapmasına izin mi vereceksin? Ya gemiyi yakarsa ya da ayin sırasında birini kurban etmeye kalkarsa?";
			link.l1 = "Buna izin vermeyeceğiz, "+npchar.name+", Sana söz veriyorum.";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "Ve ikinize de söylüyorum, eğer birisi bundan haberdar olursa... Burada ne olacağını biliyor musunuz? Diğer kasaba halkı hiç hoşlanmaz, özellikle de Narwhal'lar!";
			link.l1 = "Bu konuda haklısın. Chimiset'i buraya getirmemeliyiz, Orelie'yi ona götürmeliyiz.";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "Onu görmedin – yaşlı kadın ayakta zor duruyor. Güverteyi aşmadan durursa mucize olur!";
			link.l1 = "Bazen tek yapabileceğimiz bir mucizeye umut etmek oluyor. Ve, Jillian...";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "Başka ne var?";
			link.l1 = "Bunu kendine saklayacağına güveniyorum. Sen akıllı bir kadınsın, her şeyi doğru değerlendirdin... Adada huzursuzluk kolayca kan dökülmesine dönüşebilir, bunu kimse istemez, değil mi?";
			link.l1.go = "Jillian_22";
			link.l2 = "Kimseye tek kelime yok. Anlaşıldı mı? Sana güvendik - pişman etme bizi. Biliyorsun, bu duyulursa Adalet Adası'nda daha önce hiç görülmemiş bir katliam yaşanır.";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "Tamam mı? Ama kimsenin onu 'Protector'a sürüklediğini görmediğinden emin ol... Yoksa bana tuhaf sorular sormak zorunda kalacaklar.";
			link.l1 = "Sana garip cevaplar vermek zorunda kalma zahmetini yaşatmayacağız. Bu gece halledeceğiz.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "Tamam mı? Ama kimsenin onu 'Koruyucu'ya sürüklediğini görmediğinden emin ol... Yoksa ben de bazı garip sorulara cevap vermek zorunda kalacağım.";
			link.l1 = "Buna izin vermeyiz. Gece yaparız.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "Gece yarısından sonra gel. Burada olacak. Ve Allah aşkına, dikkatli ol.";
			link.l1 = "Endişelenmene gerek yok, "+npchar.name+", söz veriyorum öyle olacağız.";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "Gece yarısından sonra gel. Burada olacak...";
				link.l1 = "Tamam mı?";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = "Orelie hazır. Onu alabilirsin.";
				link.l1 = "Tamam mı? O zaman gidelim.";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "Gençler, nereye... nereye gidiyoruz biz?! Bu bir Rivados gemisi! Eric nerede?!";
			link.l1 = "Eric, Eddie Black’le arkadaş oldu, bilmiyor muydun?";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "Ne diyorsun sen, çocuk! Eric zencilere asla tahammül edemez!";
			link.l1 = "Bak sen! Tamam mı, o zaman gidelim ve ona burada ne halt ettiğini soralım!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "Bak hele, kimler gelmiş bizi görmeye! "+GetFullName(pchar)+" Canlı kanlı karşımda! Beyaz kardeşimi görmek güzel, ha-ha! Peki, seni buraya ne getirdi?";
			link.l1 = "Ve sana da merhaba, "+npchar.name+" . Keşke sadece bir kupa rom içmek için uğrayabilseydim, ama korkarım seninle—ya da daha doğrusu, Chimiset’le—acil bir işim var.";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "Sana sonsuza dek minnettarız, dostum. Yardım etmek için elimizden gelen her şeyi yapacağız.";
			link.l1 = "Bunu duymak güzel. Çünkü artık başvuracak başka kimsem kalmadı.";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "Hangi hanımla ilgili yardıma ihtiyacın var, "+pchar.name+"?";
			link.l1 = "Senin ciddi mi yoksa sadece şaka mı yaptığını anlayamıyorum, "+npchar.name+", ama şaka yapacak havada değilim. Yardıma ihtiyacı olan tabii ki Orelie.";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "Eric! ERIC! Göster kendini, seni tembel herif! Bu da ne saçmalık?! O cılız kıçını hemen buraya getir!";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "Demek doğruymuş... Benimkiler bu harabenin kafadan çatlak olduğunu söylemişti. Şimdi anlıyorum ki yalan söylememişler. Ama hâlâ Rivados'tan ne istediğini tam olarak anlamış değilim...";
			link.l1 = "Bırak Chimiset'le konuşayım, o zaman her şeyi anlayacaksın...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;
		
		case "Chimset_1":
			dialog.text = "Konuş, sevgili dostum. Seni dikkatle dinlemeye hazırım.";
			link.l1 = "Kısa keseceğim, Chimiset. Orelie'nin Mary ve benim ihtiyacımız olan bilgiye sahip olduğunu biliyoruz. Ama onun durumu yüzünden, ki yanlış anlamadıysam bu sadece yaş meselesi, bu bilgiyi ondan alamıyoruz ve doğru olup olmadığından da emin olamayız. Hem Hintli hem Afrikalı şamanların neler yapabildiğini duydum – bu yüzden yardımını istemeye geldim, Chimiset.";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Chimset_2":
			dialog.text = "Seni anlıyorum, dostum. Şamanlar gizemli ve mistik güçlere sahipler, çoğu zaman yabancıların, hatta kendi akrabalarının bile anlayışının ötesinde, beyazları hiç saymıyorum bile. Kimileri buna büyü der, kimileri mucize. Gerçekten de pek çok şeye kadiriz – ama kimse bir nehrin tersine akmasını sağlayamaz... Kimse onu durduramaz da.";
			link.l1 = "Ne demek istiyorsun, Chimiset?";
			link.l1.go = "Chimset_3";
		break;
		
		case "Chimset_3":
			dialog.text = "Zamanın nehri diyorum, dostum. Ya da hayatın nehri—hangisini istersen. Bak, tamamen haklısın—bu zavallı ruhun hastalığının kökü yıllarında yatıyor, başka hiçbir şeyde değil.";
			link.l1 = "Bununla ilgili biraz bir şeyler duydum. Bildiğim kadarıyla, öyle çok nadir bir sorun değil.";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "Haklısın. Onun yaşındaki insanlar sık sık hayallerin, bazen de kâbusların vadilerine kapılıp giderler. Geri dönerler, ama sonra yine giderler—çoğu zaman kendi istekleriyle değil, onları içine çeken gizemli güçler yüzünden. Zaman geçtikçe, bu hastalık daha da güçlenir—ta ki insan kendini ya da arkadaşlarını hatırlayamaz hale gelene kadar.";
			link.l1 = "Yani, bunun için yapabileceğin hiçbir şey yok mu, di mi?";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "Hastalığı kovmak mı – hayır. O benim elimden gelmez. Ama başka bir şey yapabilirim...";
			link.l1 = "Ne tam olarak?";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "Bu kadın kendine gelir gelmez, önceden hazırlanacağım kısa bir ritüel yapacağım.";
			link.l1 = "Hastalığı tamamen durdurmasa da, en azından yavaşlatır mı?";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "Tam olarak değil. Akıl sağlığını mümkün olduğunca uzun süre koruyabilmek için tüm gücünü toplaması gerekecek.";
			link.l1 = "‘Mümkün olduğunca uzun’ tam olarak ne kadar uzun, söyler misin?";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "Bu ritüele değil, insana bağlı. Kimisi bir hafta dayanabiliyor, kimisi bir ay... Neredeyse bir yıl, belki daha da uzun süre aklını ve hafızasını koruyan bir adam duydum... Ve herkes iyileştiğini sandığında, hastalık geri döndü—o gece onu aldı.";
			link.l1 = "İhtiyacımız olanı öğrenmek için bir saat yeterli olacak. Ritüeli ne zaman yapabilirsin, Chimiset?";
			link.l1.go = "Chimset_9";
		break;
		
		case "Chimset_9":
			dialog.text = "Kadını hemen şimdi alacağım, onu ambarın altına götür—orada böyle şeyler için hazırlanmış bir sığınak var... Bundan sonrası, ne zaman kendine geleceğine bağlı... Ama bence sabaha kadar işimiz biter.";
			link.l1 = "O zaman yoluna çıkmayacağım. Ve senin... Tanrın, Chimiset, sana yardım etsin.";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "Zikomo! Beyaz kadını ambarlara götürmeme yardım et.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "Başardık, beyaz kardeş. Bunu başardık...";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "Oh, "+GetFullName(pchar)+"! Sizin ve Mary'nin tekrar Adalet Adası'na döndüğünüzü hiç bilmiyordum! Ne güzel bir sürpriz!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "Chimiset, teşekkür ederim! Sana nasıl teşekkür edeceğimi bile bilmiyorum...";
			link.l1.go = "Chimset_14";
			link.l2 = "Vay canına, bak hele, Chimiset başardı! Sana bir an bile şüphe duymadım...";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "Tüm Rivado ailesi sana sonsuza dek minnettar, dostum! 'Koruyucu'nun kapıları sana her zaman açık.";
			link.l1 = "Umarım seni daha fazla rahatsız etmek zorunda kalmam... Mary, Orelie, 'Pluto'ya dönmemiz gerekiyor.";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "Tüm Rivado ailesi sana sonsuza dek minnettar, dostum! 'Koruyucu'nun kapıları sana her zaman açık.";
			link.l1 = "Umarım sizi daha fazla rahatsız etmek zorunda kalmam... Mary, Orelie, 'Pluto'ya dönmemiz gerekiyor.";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "Kamaradan nasıl çıktığımı bile hatırlamıyorum... Ah, şu yaşlılık – hafızam tamamen mahvoldu. ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "Pekala, pekala, genç hanım, seni kamarama getiren nedir?";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = "Orelie, ben...";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = "Orelie, sen yokken burayı toplamasını ben istedim ondan. Senin kötü dizlerinle sırtını zorlamana hiç gerek yok...";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "Temizlik mi yapayım?! Sen...";
			link.l1 = "Jillian, emeğin için teşekkür ederim. (fısıldayarak) Başardık. Chimiset işi halletti.";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "Bu olamaz...";
			link.l1 = "Gördüğün gibi. Şimdi, lütfen, konuşalım.";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "Pekala, gençler, yaşlı bir kadına eşlik ettiğiniz için teşekkür ederim. Korkarım yakında hiç dışarı çıkamayacağım. Zavallı bacaklarım, bacaklarım...";
			link.l1 = "Eğer sakıncası yoksa, "+npchar.name+", seninle sadece biraz kalacağız. Mary ve benim seninle çok önemli bir işimiz var.";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "Eğer bir daha kendimi başka bir gemiye sürüklemek zorunda kalmazsam, elimden geldiğince yardımcı olurum. Dinliyorum.";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = "Orelie, bana ailemi anlatmanı istiyorum. Bir de doğduğum günü. Burada, Adalet Adası’nda oldu, değil mi? Donald öyle diyor ama o zamanlar burada bile yoktu ki, kesin olarak bilemez. Ama sen ondan çok daha uzun zamandır buradasın, tamam mı! Yirmi yıldan fazla oldu, değil mi?";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "Sakin ol, sakin ol kızım, lütfen bu kadar hızlı konuşma! Sana yetişemiyorum...";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "Tamam mı, anladım. Peki, bir kez daha üstünden geçelim...";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "Endişelenme Mary, o kadar da yaşlı değilim henüz, ha-ha... Dediğini duydum. Ama gerçekten de Adalet Adası'nda herkesten daha uzun yaşadığım için, yaşımı biraz saygı ve anlayışla karşılamanı umuyorum...";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "Tabii ki, Orelie! Başka türlü düşünebileceğini nasıl hayal edersin?";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "Ah, sadece şunu söylemek istedim; şu gençlere bakınca... yok, yok, biz büyüklerimize öyle davranmazdık. Ama sen de öyle değilsin tabii ki. Sadece demek istediğim, sorularına hepsini birden değil de, teker teker cevap verirsem bizim için daha kolay olur...";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "Anladım, Orelie. Senin için nasıl kolaysa, tamam mı? Yani, ben doğduğumda Adada mıydın? Yani, eğer burada doğduysam...";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "1633 yılında Adalet Adası'na geldim, ve bazen o gün hâlâ kabuslarımda karşıma çıkıyor. Fırtına, bizim 'Reprisal'—kocamla birlikte Florida'ya doğru yelken açtığımız flüt tipi gemi—dalgalar arasında savruluyordu, her an alabora olacak gibiydik, bildiğimiz tüm duaları okuyup, yenilerini uyduruyorduk... Ve sonra, bir gürültü ve...";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "Yani sen buraya, ben daha doğmadan beş yıl önce gelmişsin, tamam mı.";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "Aşağı yukarı. O zamanlar işler farklıydı. San Jeronimo hâlâ suyun üstündeydi, dıştaki gemi halkası şimdi olduğunun yarısı kadardı, belki daha da az... Bir de dayanamayarak batanları saymıyorum bile! Size bir şey diyeyim gençler - hava açıksa, suya bakarsanız, aşağıda ne kadar çok enkaz olduğunu görmek insanın ödünü koparıyor...";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "Ailem buraya hangi gemiyle gelmiş, onunla ilgileniyoruz. Benimle mi... yoksa bensiz mi?";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "Seninle, kızım, seninle.";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "Yani, sonunda ana karada mı doğmuşum?";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "Hayır, 'seninle' derken biraz farklı bir şey kastettim. Annenin karnındaydın ve bir hafta sonra doğdun.";
			link.l1 = "Bunu komik mi buluyorsun, Orelie?";
			link.l1.go = "Oreli_32";
			link.l2 = "Ve yıllar geçse de mizah anlayışını kaybetmemişsin, Orelie.";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "Şey, ben kendime başkalarından çok daha fazla gülerim. Üzgünüm Mary, seni üzmek istememiştim.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "Şey, kendime başkalarından çok daha fazla gülerim. Üzgünüm Mary, seni kırmak istememiştim.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "Tamam, Orelie. Lütfen – devam et. Ben doğduktan sonra aileme ne oldu?";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "Sonrasında mı? Ah, canım, ikisinin de o zamana kadar hayatta kalması başlı başına bir mucizeydi! O Haziran gecesi ne fırtına kopmuştu! Sabah olunca, kayık anneni iç halkaya getirdiğinde, neredeyse kimse gözlerine inanamamıştı—doğum yapmak üzere olan bir kadının böyle korkunç bir gemi kazasından sağ çıkmasına. Zavallı Teresa, sanki dün gibi hatırlıyorum...";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "Teresa mıydı? Adı oydu, değil mi?";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "Evet, kendini böyle tanıttı – ve neredeyse söylediği tek şey de buydu. Günün sonunda ateşe tutuldu ve doğuma kadar da öyle kaldı. Kimse hayatta kalacağından emin değildi, hele ki çocuğun sağ doğacağına hiç kimse inanmıyordu – yaşadıklarından sonra. Ama Teresa başardı. O doğdu – ve sonra hayata gözlerini yumdu. Allah rahmet eylesin...";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "Annem öldü, ben de babamla mı kaldım? Ama o zaman neden herkes beni Eric Udette'in büyüttüğünü söylüyordu? Ve...";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "Mary, canım, sana söyledim... Beni bu kadar çok soruyla bunaltma, tamam mı...";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "Üzgünüm Orelie, kendimi kaptırdım, tamam mı? Babam da bir gemi kazasından sağ kurtulmuştu, değil mi?";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "Baban... Biliyor musun, baban hakkında fazla bir şey söyleyemem—ama kimseye öyle bir baba dilemem. Sen doğduktan sadece birkaç gün sonra ortadan kayboldu, seni kendi başına bıraktı. Neyse ki Eric’in kalbi o kadar iyi ve yumuşaktı ki—sanki bir bardak romda ıslanmış bisküvi gibi...";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "En azından bana adını söyle!";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "Ah... Jeffrey miydi yoksa John mu, keşke hatırlayabilsem...";
			link.l1 = "Yani, aslında pek hatırlamıyorsun, değil mi, "+npchar.name+"?";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "Sözlerimden şüphe mi ediyorsun, genç adam?!";
			link.l1 = "Sessiz ol, "+npchar.name+"Tamam mı, sakin ol. Seni kırmak istemedim. Sadece o günleri gayet iyi hatırlıyor gibisin, hepsi bu.";
			link.l1.go = "Oreli_45";
			link.l2 = "Hiç şüphem yok, "+npchar.name+". Sadece tüm ayrıntıları doğru hatırlamaya çalışıyorum - hepsi bu. Ama bu karmaşa işleri biraz daha zorlaştırıyor.";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "Hafıza, kaprisli bir hanımefendi, "+pchar.name+", oldukça seçici. Özellikle bunca yıldan sonra. Teresa'yı unutmak zor – bütün hafta boyunca onun acı çekişini izledim! Ah, ona ne kadar acıdım anlatamam!";
			link.l1 = "Ve kocası, o da yanında değil miydi?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "Hafıza, kaprisli bir hanımefendi, "+pchar.name+", oldukça seçiciyim. Özellikle bunca yıldan sonra. Teresa'yı unutmak zor – bütün hafta boyunca onun acı çekişini izledim! Ah, ona ne kadar üzüldüm anlatamam!";
			link.l1 = "Ve kocası, o da yanında değil miydi?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "Çok nadiren. Haftanın çoğunda ortalarda yoktu – o zamanlar Adalet Adası’nda pek bulunmayan ilaçlar ve iksirler aramaya giderdi...";
			link.l1 = "Yani, karısına yardım etmeye çalıştıysa iyi bir koca olmalıydı, di mi?";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "İyi bir koca olabilirdi. Aksini hiç söylemedim, tamam mı? Beni kandırmaya çalışma, genç adam!";
			link.l1 = "Böyle bir şeyi aklımdan bile geçirmedim, yemin ederim, "+npchar.name+". Belli ki onu pek takdir etmiyorsun. Bir de adını bile hatırlamaman...";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "O adamı bir anlığına, neredeyse bir gölge gibi, 'Ceres Demirhanesi' kulübesinin karanlığında gördüm—şimdi orada Herr Jürgen yaşıyor. Adam sadece geceleri gelirdi, yüzünü zar zor hatırlıyorum. Adına gelince—kimse ona asla adıyla seslenmezdi, hep soyadıyla çağırırlardı. Casper şöyle, Casper böyle...";
			link.l1 = "Seni anlıyorum, "+npchar.name+" . Yani Mary doğdu, ve birkaç gün sonra o hiçbir iz bırakmadan ortadan kayboldu. Öldürüldü mü?";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "Zor bir soru bu, genç adam. Bak, burada bir şeyi gizli tutmak gerçekten zor—herkes sürekli birbirini gözetliyor. Ne zaman bir kavga çıksa—ister gemilerin içinde olsun—ertesi gün bütün Adalet Adası'nın haberi olur.";
			link.l1 = "Hiç şaşırmadım.";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "Öldürülenlerin cesetleri her zaman bulunmaz - tecrübeli düzenbazlar cesetleri batırır, ellerini ve ayaklarını zincirli güllelerle bağlar ya da top gülleleriyle, taşlarla ağırlaştırırlar. Dipteki yengeçler işi tamamlar. Ama ölenlerin kişisel eşyaları eninde sonunda tekrar su yüzüne çıkar.";
			link.l1 = "En baştan mı?!";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "Tabii ki hayır! Sadece gözüne çarpıyorlar demek istedim—bir yüzük, üzerine kazıma yapılmış bir tabanca, törensel bir kılıç... İnsanlar bunlar hakkında nadiren soru sorar. Kaybedileni geri getiremezsin ve kimse başına daha fazla dert almak istemez.";
			link.l1 = "Geoffrey ya da John Casper'ın kendilerine özgü eşyaları var mıydı?";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+" Ruhun şad olsun – adamın adını bile hatırlamıyorum, sen bana böyle şeyler soruyorsun! Bir şey olduysa bile, o şeyin Adada başkasına geçtiğini hiç duymadım. O zamanlar meyhanede çalışıyordum, dedikoduların çoğu benden kaçmazdı. Ama bu her şeyi bildiğim anlamına gelmiyor tabii.";
			link.l1 = "Birileri iz bırakmadan kayboldu dediklerinde, genellikle öldürüldüklerini kastederler. Ama Bay Casper'ın durumunda, sen bundan pek emin değilsin gibi...";
			link.l1.go = "Oreli_54";
		break;
		
		case "Oreli_54":
			dialog.text = "Ben sadece şunu söylüyorum, 'kayboldu' demek illa ki 'öldü' anlamına gelmez. Özellikle o zamanlarda, kaçakçılarla ve çalıntı mal satıcılarıyla dolu tartanlar Adalet Adası ile Küba arasında sürekli gidip gelirdi... Biliyor musun, yüzünü hatırlayamıyorum ama gözleri... Onlarda, hiçbir yerde kaybolmayacak bir adamın bakışı vardı. Ya da en azından, kendisi buna gerçekten inanıyordu.";
			link.l1 = "Tartanlar, tartanlar... Bunda imkânsız bir şey yok. Adını bilseydik, o yılların koloni arşivlerine bakabilirdik. Ama hangi gemide, hangi isimle görev yaptığını bilseydik, işimiz çok daha kolay olurdu.";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "Ve neden bana bakıyorsun, genç adam? Bunu hatırlayacağımı mı sanıyorsun?";
			link.l1 = "Umarız öyle olur, "+npchar.name+" - şimdiye kadar bize ne kadar çok şey anlattığını düşünürsek.";
			link.l1.go = "Oreli_56";
			link.l2 = "Hmm... Bundan ciddi şüphelerim var.";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "Belki de kaç topu vardı, kalibresi neydi diye sormak istiyorsun? Canım, burada yıllar boyunca kaç geminin battığından haberin var mı? Hepsini hatırladığımı mı sanıyorsun? Üstelik o gemiden sağ çıkan da bir avuç insandı – yüzeyde bir günü bile zor geçirdi, biliyor musun...";
			link.l1 = "Anladım... Yani, mantıklı, yirmi yıl geçti. En azından bize anlatılanları hatırladığın için teşekkür ederim.";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "Belki de kaç topu vardı, kalibreleri neydi diye sormak istiyorsun? Canım, burada yıllar boyunca kaç geminin battığı hakkında bir fikrin var mı? Ve hepsini hatırladığımı mı sanıyorsun? Üstelik o gemiden sağ çıkanlar bir avuçtu – su üstünde bir gün bile zor dayandı, o da...";
			link.l1 = "Anlıyorum... Yani, mantıklı, yirmi yıl geçti. En azından bize söylenenleri hatırladığın için teşekkür ederim.";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "Umarım şaka yapmıyorsun ve hafızası delik deşik olmuş yaşlı bir kadınla dalga geçmeye çalışmıyorsun.";
			link.l1 = "Hiç de değil, "+npchar.name+". Bize gerçekten çok yardımcı oldun. Geçmiş olsun. Neyse, biz artık gidelim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "Yani, Teresa... Onun adı buydu. Zavallı annem, tamam mı...";
			link.l1 = "Eh, en azından şimdi nereden bu kadar güçlü ve inatçı olduğunu biliyoruz. Batan bir gemide hamile bir kadın... Düşünmesi bile tüylerimi diken diken ediyor.";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "Ama o halde bu gemide ne işi vardı, "+pchar.name+"?! Böyle bir şeyi yapmayı düşünmek bile delilik, tamam mı?!";
			link.l1 = "Bu sorunun cevabını yalnızca baban verebilir – John, Jack, Jacob, Jasper, Jordan...";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "Her İngilizce ismi ‘J’ harfiyle başlayanları mı hatırlamaya çalışıyorsun? Orelie sadece Geoffrey ve John’dan bahsetti, tamam mı?";
			link.l1 = "Belki de o da gerisini hatırlamıyordu, tıpkı benim gibi? Hani, yaş falan işte...";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+",   sence...";
			link.l1 = "Şu anda hafızasına tamamen güvenmem doğru olmaz. Ama yine de, sadece sömürge kayıtlarını değil, 1638'den kalma Donanma arşivlerini de bulmamız gerekecek ve bu çok daha zor: o kayıtlar gizli tutulur, özellikle de subaylarla ilgili olanlar. Ayrıca, sıradan bir denizcinin karısını gizlice gemiye almasına izin verileceğinden de ciddi şekilde şüpheliyim.";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "Öte yandan, bir subay hakkında bilgi bulmak sıradan bir denizciye göre çok daha kolay.";
			link.l1 = "Eğer geminin adını biliyorsan. Ya da tam adını. Sadece 'Geoffrey ya da John ya da, en kötüsü, Jack...' değil yani... Tabii eğer şanslıysak ve gemi donanmaya aitse. Tüccarların mürettebat listeleri çok daha dağınık olur.";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "Peki o zaman ne yapmalıyız, "+pchar.name+"? Orelie ile tekrar mı konuşacağız? Ondan alabileceğimiz her şeyi zaten aldık, sence de öyle değil mi?";
			link.l1 = "Orelie ile değil. Donald ile.";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "Peki, o bize nasıl yardım edecekmiş? Kendi söyledi, 1638'de Adalet Adası'nın yakınında bile değilmiş, tamam mı.";
			link.l1 = "Ama burada başka Narwhal’lar da vardı, değil mi?";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "Ne demek istediğini tam olarak anlamıyorum.";
			link.l1 = "Göreceksin, sevgilim, göreceksin. Çekebileceğimiz bir ip daha var. Hadi gidelim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "Ah, yine sen! Ee, arayışların nasıl gidiyor, tamam mı?";
			link.l1 = "Merhaba, "+npchar.name+". Her şey daha iyi olabilirdi. Şu anda sanki gizemler ve bilmecelerle dolu bir mağarada dolaşıyoruz. Ama çıkışın yakın olduğunu hissediyoruz.";
			link.l1.go = "Grinspy_32";
			link.l2 = "Ve sana da merhaba, "+npchar.name+"Başlangıçta hayal ettiğimden çok daha iyi. Durum... aslında o kadar da umutsuz değilmiş.";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "Bunu duyduğuma sevindim. Gerçekten. Ama yine ikinizin de benden bir şey istediği belli, di mi? Ne öğrenebildiniz bakalım?";
			link.l1 = "Mary burada, Adada, Haziran 1638'de doğdu. Annesi Teresa, doğumdan hemen sonra hayatını kaybetti. Babası ise—adı Casper olan bir adam—Mary doğduktan sadece birkaç gün sonra ortadan kayboldu. Onun hakkında bildiğimiz tek şey, adının 'J' harfiyle başladığı. Bazıları, onun yerel sığlıklarda yengeçlere yem olmadığını, aksine Adadan kaçakçıların tartanlarından biriyle ayrıldığını söylüyor...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_33":
			dialog.text = "Bunu duyduğuma sevindim. Gerçekten. Ama ikinizin de benden yine bir şey istediği belli, tamam mı? Peki, ne öğrendiniz?";
			link.l1 = "Mary burada, Adada, Haziran 1638'de doğdu. Annesi Teresa, doğumdan hemen sonra hayatını kaybetti. Babası—adı Casper olan bir adam—Mary doğduktan sadece birkaç gün sonra ortadan kayboldu. Onun hakkında bildiğimiz tek şey, adının 'J' harfiyle başladığı. Kimileri, onun yerel sığlıklarda yengeçlere yem olmadığını, kaçakçıların tartanlarından biriyle Adadan ayrıldığını söylüyor...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "Kızını geride mi bırakmış? Bu gerçekten tuhaf bir şey.";
			link.l1 = "Kesinlikle öyle. Ama bunu açıklayabilecek tek kişi şu Bay J.'den başkası değil.";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "Ve hâlâ hayatta olduğunu mu düşünüyorsun? Onu bu yüzden mi arıyorsun?";
			link.l1 = "Sadece bunun için değil. Kim olduğunu, nasıl yaşadığını bilmek istiyoruz. Bu Mary için çok önemli.";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "Hmm, anladım. Ve üzgünüm, gerçekten sana hiçbir konuda yardımcı olamıyorum...";
			link.l1 = "Aslında, yapabilirsin. Söylesene, Narwhallar Adada kaybolan gemilerle ilgili bir kayıt tutuyorlar, değil mi?";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "Ne demek istediğini tam olarak anlamadım, "+pchar.name+".";
			link.l1 = "Greenspen, Greenspen... Unutma, o koltukta hâlâ oturuyorsan, bu benim sayemde. O yüzden bana bir iyilik yap – sabrımı sınama.";
			link.l1.go = "Grinspy_38";
			link.l2 = "Eminim beni anlıyorsun, Donald. Ve dostluğumuz hatırına, sorudan kaçmaya çalışmayacaksın.";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "Hmm...";
			link.l1 = "Bazen gemiler dış halkaya vurur. Kimisi hemen batar, kimisi bir süre yüzeyde kalır—onlar aranır ve değerli ne varsa alınır. Rivadoslar hakkında bir şey diyemem ama Narwhal’ların buldukları her ıvır zıvır için kavga ettiğini sanmam—muhtemelen her şey önce ortak bir havuza atılır, sonra ganimetin hesabı tutulur ve ancak ondan sonra paylaştırılır.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Grinspy_39":
			dialog.text = "Hmm...";
			link.l1 = "Dış halkaya bazen gemiler vurur. Bazıları hemen batar, bazıları bir süre yüzeyde kalır—onlar aranır, değerli ne varsa alınır. Rivadoslar hakkında bir şey diyemem ama Narwhalların buldukları her ıvır zıvır için kavga ettiklerini sanmam—muhtemelen, her şey önce ortak bir havuza atılır, sonra tam bir envanter çıkarılır ve ancak ondan sonra ganimet paylaşılır.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "You’re no fool, +pchar.name+. Unlike many around here. Yes, that’s more or less how it works. Personally, I find all that paperwork tiresome, but it’s been that way since the time of Alan Milroe and those who led the Narwhal clan before him. We keep such records - and more than that: we even log ships that were reached first by the Rivados or pirates. In those cases, of course, we don’t know who or what was on board...";
			link.l1 = "Mary'nin ailesinin gemi kazasından sonra Ceres Demirhanesi'ne getirildiğine bakılırsa, gemilerini bulanlar Narwhal'larmış. Yani bununla ilgili bir kayıt olmalı.";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "Olabilir. Kesin bir şey söyleyemem. Ve söyleyemeyeceğim de.";
			link.l1 = "Şimdi ne demek istediğini anlamıyorum, "+npchar.name+".";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "Enkaz günlükleri. Dodson ayrıldıktan sonra Leighton Dexter Amiral olunca, o belgeleri bizden aldı.";
			link.l1 = "Öylece aldı mı onları? Ve sen karşı çıkmadın mı?";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "Öncelikle, yeterince nazikti. Sonra, onları yakında geri getireceğine söz verdi. Ve üçüncüsü... o kağıtlar umurumda bile değil, tamam mı?";
			link.l1 = "Tam olarak işe yaramaz kayıtlar değil, ama.";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "Dediğim gibi, bu sadece bir gelenek, esas olarak klanımızın gemilerden çıkan ganimet yüzünden birbirinin boğazına sarılmasını önlemek için. Bir gemi karaya vurur, alabildiğimiz her şeyi sökeriz, bir liste yaparız, bir kısmını paylaşırız, kalanı ambarlarımıza saklarız – işte hepsi bu. Çekmeceyi neden gereksiz yere dolduralım ki? Şimdi onlarda biraz daha fazla yer var – sanırım bunun için Amiral’e teşekkür bile etmeliyim.";
			link.l1 = "Tamam mı, anlaşıldı. O zaman rotamızı 'San Augustin'e çeviriyoruz. Ama belki tekrar seni görmeye uğrarız, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;
		
		case "WildRose_Dexter_1":
            dialog.text = "Ah, "+pchar.name+"Buyur, buyur. İş için mi geldin, dostum, yoksa sadece selam vermeye mi uğradın?";
            link.l1 = "Bu sefer iş için buradayım. Şöyle diyelim, bu iş bana özel.";
            link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
        break;

        case "WildRose_Dexter_2":
            dialog.text = "Ve senin için de önemli olduğu belli, nasıl da heyecanlandığın yüzünden okunuyor.";
            link.l1 = "Gerçekten mi? Bana sorarsan, daha çok yorgun gibiyim. Son birkaç gündür senin topraklarında epey dolaşmak zorunda kaldım. Eklem yerlerim isyan etmeye başladı—ve ben de, aptal gibi, sadece senin gibi yaşlı adamların böyle şeylerle uğraştığını sanıyordum.";
            link.l1.go = "WildRose_Dexter_3_1";
            link.l2 = "Sadece biraz nefes nefeseyim, hepsi bu. Bak, ben bütün gün sandalyede oturmuyorum. Senin gibi değilim yani – baksana, bacakların seni tamamen terk etmiş gibi, ha-ha-ha!";
            link.l2.go = "WildRose_Dexter_3_2";
        break;

        case "WildRose_Dexter_3_1":
            dialog.text = "Ve hiç düşündün mü neden bu sandalyeye mıhlanmış gibiyim, ha? Biliyor musun, insanın hayata bakışı değişiyor, sağlığını satın alamayacağını anladığında, bu Adada ne kadar zengin olursan ol.";
            link.l1 = "Komik olan şu ki – tam da bunun için buraya geldim, konuşmak için.";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "Ve hiç düşündün mü neden bu sandalyeye mıhlanmış gibiyim, ha? Biliyor musun, insanın hayata bakışı değişiyor; sağlığını parayla alamayacağını anladığında, bu Adada ne kadar servetin olursa olsun.";
            link.l1 = "Komik, tam da bunun için buraya geldim, konuşmak için.";
            link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "Sağlığım hakkında mı?";
            link.l1 = "Hayır, Adanın zenginlikleri hakkında. Ya da daha doğrusu, onların envanteri hakkında. Ve tamamen doğru olmak gerekirse, o envanterleri içeren defterler hakkında.";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "Şey... biraz daha basit anlatır mısın, "+pchar.name+"?";
            link.l1 = "Çok da uzun zaman önce değil, Narwhal'lardan Adalet Adası'nda mahsur kalan gemilerin günlüklerini almıştın...";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "Yani, şu aptal Greenspen gerçekten seni onların peşinden mi gönderdi? Ne cesaret.";
            link.l1 = "Hiç de değil, "+npchar.name+", Donald'ın bununla hiçbir ilgisi yok. Bu soruyla ona gittim, o da beni sana gönderdi. Ama tepkini itiraf etmeliyim ki eğlenceli buldum. Narwhal kayıtlarına neden ihtiyaç duyduğunu paylaşmak ister misin?";
            link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "Neden olmasın? Muhtemelen tahmin edersin, gemilerin kendisi umurumda bile değil. Ambarlarına tıktıkları değerli eşyalar mı? Aynı şekilde. Yeterince var burada, insanlar çok açgözlü olmazsa tabii. En azından, ben böyle düşünüyorum. Asıl umursadığım şey silahlar: tüfekler, kılıçlar... toplar, hatta. Evet, o akıllılar bazen onları da kurtarıyor. O kafasız kara pislikler başaramazdı, ama Narwhal’lar...";
            link.l1 = "Ve sen de Greenspen halkının yeni bir çatışmaya ne kadar hazır olduğunu görmek istedin, di mi?";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
            dialog.text = "Ve bana ve adamlarıma gözümüzü dört açmamızı söyleyen bir mesaj gönder. Oldukça açık bir sinyal bu, ama Donald’ın o tatbikatlarla yaptığı küçük sirki düşününce, paralarının peşinde olduğumu sanmasına hiç şaşırmam.";
            link.l1 = "Evet, işlerin tam da umduğun gibi gitmediğini görebiliyorum. Peki ya Rivados? Kara Eddie bir sorun çıkarıyor mu?";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "Rivados, Eddie... Alçak zenciler – Shark'ın onlardan bu kadar nefret etmesine şaşmamalı.";
            link.l1 = "Yani gerçekten de sorun çıkarıyor.";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "İşte mesele bu, hayır, yalan söylüyorsam lanet olsun! O kara herifler sessizleşti, gemilerine kapanıp kaldılar...";
            link.l1 = "Peki, seni asıl rahatsız eden ne, o zaman? "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "Bunu sana nasıl anlatacağım ki, "+pchar.name+"... Bak, bu açık denizdeki rüzgar gibi. Bazen hafif eser, bazen sert, bazen de tam bir fırtınaya dönüşür. Ama bir şekilde o rüzgar gemiyi ileri götürür ve iyi bir kaptan onu nasıl kullanacağını bilir.";
            link.l1 = "Hafif bir esinti, her zaman öfkeli bir fırtınadan iyidir.";
            link.l1.go = "WildRose_Dexter_12";
        break;

        case "WildRose_Dexter_12":
            dialog.text = "Aynen öyle. Ama bazen hiç rüzgar olmuyor, tamam mı? Tam bir durgunluk – ve hiçbir kaptan buna bir şey yapamaz. Sadece kıç güvertede oturur, suya bakar ve sırada ne halt olacak diye düşünürsün. Eddie ve onun arkadaşı Chimiset’le de aynı şey – bir şeyler çeviriyorlar, iliklerime kadar hissediyorum, hiç hayra alamet değil, yıldırım çarpsın ki doğru söylüyorum!";
            link.l1 = "Belki de kıçını kaldırıp Edward’la yüz yüze konuşmalısın. Hatta daha iyisi, üçünüz bir araya gelin, Donald’ı da çağırın, dürüstçe konuşun. Adalet Adası’nı yeniden kana bulamaktan çok daha iyi bir fikir bu. Ama tamam... Benim buraya neden geldiğime dönelim.";
            link.l1.go = "WildRose_Dexter_13";
        break;

        case "WildRose_Dexter_13":
            dialog.text = "Yani narvaların hazineleriyle ilgileniyorsun, di mi? Orada ne bulmayı umuyorsun?";
            link.l1 = "Burada kaybolan gemilerin listeleriyle ilgileniyorum. Özellikle de 1638 yılı için. Şöyle ki, Mary'nin ailesi hakkında bilgi bulmaya çalışıyoruz. Annesiyle ilgili az çok bir şeyler biliyoruz, ama babası için aynı şeyi söyleyemeyiz. Onunla ilgili detaylar oldukça belirsiz—adını bile bilmiyoruz ve elimizdeki tek ipucu, 1638 Haziran'ında dış halkada batan geminin adı...";
            link.l1.go = "WildRose_Dexter_14";
        break;

        case "WildRose_Dexter_14":
            dialog.text = "Asil biri. Bir zamanlar kendi babamın kim olduğunu düşünüp dururdum. Ama korkarım sana bu konuda yardımcı olamam.";
            link.l1 = "Ve bu neden, sormamda bir sakınca yoksa?";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "Senden hiçbir sır yok, "+npchar.name+". Ben değilim, Donald. O sadece 1651 yılından itibaren olan evrakları verdi. Daha eski kayıtları, en azından önceki on yılı sordum, ama bana Alan Milroe’dan devraldığı her şeyin bu kadar olduğunu söyledi. Bana aynen böyle dedi.";
            link.l1 = "Bence yalan söylemesi için hiçbir sebebi yoktu.";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "Ben de bilmiyorum, dostum. Düşünsene, bana yeni kayıtları tek bir soru bile sormadan verdi. Hatta bana öyle geldi ki, o eski evraklardan kurtulduğu için biraz da memnundu... Kim bilir, belki Milroew onlarca yıl öncesinin kağıtlarından kurtuldu sadece... Yaktı ya da belki...";
            link.l1 = "Hayır, bu olamaz.";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "Hayır, bu olamaz. Alan asla böyle bir şey yapmaz.";
            link.l1 = "Neden bu kadar eminsin, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "Onun daha çok bıçak ve balta insanı olduğunu sanırdım, bu kadar evrak işine bulaşacağını hiç düşünmezdim. Okuma yazması olduğuna bile şaşırdım.";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
            dialog.text = "Adalet Adası’yla ilgili her kaydı büyük bir özenle saklardı. Onları adanın hikayesinin bir parçası olarak görürdü. Ve tarih— sadece buranın değil— Alan’ın asıl tutkusu buydu, tamam mı? Eline geçen her tarihi belgeyi, her kitabı didik didik incelerdi... Bazen, dövüşçüden çok daha iyi bir bilgin olacağını düşünürdüm— bir keresinde kendisine de söylemiştim bunu.";
            link.l1 = "...";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_17_2":
            dialog.text = "Adanın her kaydına büyük bir özenle yaklaşırdı. Onları adanın tarihinin bir parçası olarak görürdü. Ve tarih—sadece buranın değil—Alan’ın gerçek tutkusu buydu, tamam mı? Eline geçen her tarihi belgeyi ve kitabı incelerdi... Bazen onun dövüşçüden çok daha iyi bir bilgin olacağını düşünürdüm—hatta bir keresinde ona da söylemiştim.";
            link.l1 = "Belki de gerçekten kılıç ve tabanca yerine gözlük, kağıt ve tüy kalem seçmeliydi—kim bilir, hâlâ bu çürük gemilerin güvertelerinde volta atıyor olabilirdi. Ama Milroe arşivleri bu kadar çok seviyorsa, o kayıtları nereye koydu? Diyelim ki bir kağıdın üstüne yanlışlıkla mürekkep döktü—ama onlarca, belki de yüzlerce kayıt vardı, değil mi?";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_18":
            dialog.text = "Tek bildiğim, o belgeleri kendi canından daha çok koruduğuydu. Belki birisi çaldı, ya da belki de onları birine kendi eliyle verdi...";
            link.l1 = "Çalındı mı? Kim, yıllar önce baştan kıça kadar soyulmuş gemiler hakkında bilgiye ihtiyaç duyar ki? Birine verdim—bu çok daha olası, ama kime ve ne karşılığında?";
            link.l1.go = "WildRose_Dexter_19_Add";
        break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "Başka bir tarih meraklısına, ha-ha-ha! Charles'a katılıyorum – o eski karalamaları başka kim isterdi ki, hiçbir fikrim yok.";
            link.l1 = "Birinin onlara ihtiyacı vardı, yine de. Bunu biraz düşünmem gerekecek. Tamam mı, "+npchar.name+", seni daha fazla tutmayacağız. Yine görüşeceğiz.";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+", seni tekrar görmek güzel. Mary ile işler nasıl gidiyor?";
			link.l1 = "Seni gördüğümüze sevindik, "+npchar.name+". Ama bizim için işlerin nasıl gideceği – bu sana bağlı, tamam mı?";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "İlginç bir şekilde başladın sohbete, kabul etmeliyim. Ve biraz da tedirgin edici, yüzlerinizdeki ifadeye bakılırsa.";
			link.l1 = "Panik yapmana gerek yok, "+npchar.name+", bu senin suçun değil. Sadece bu gıcırdayan batıkların arasında durmadan koşturduğumuz için biraz nefes nefese kaldık. Bugün hava da bayağı ağır, sence de öyle değil mi?";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "Adada seni arayıp durduk, bize yardım edebilirsin diye. Off, bu sıcak da ne böyle...";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "Öhöm, evet, şu anda hafif bir esinti hiç fena olmazdı. Ama anladığım kadarıyla seni yoran sadece hava değil. Peki, senin için ne yapabilirim?";
			link.l1 = "Bak, Mary ve ben yirmi yıl önce ne olduğunu aydınlatmak için bir araştırma başlattık.";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "Öhöm, evet, şu anda hafif bir esinti gerçekten iyi olurdu. Ama anladığım kadarıyla seni yoran sadece hava değil. Peki, senin için ne yapabilirim?";
			link.l1 = "Bak, Mary ve ben, yirmi yıl önce ne olduğunu aydınlatmak için bir araştırma başlattık.";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "Kulağa ilginç geliyor. Peki, tam olarak neyle ilgili?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "Anne babam, Antonio. Charles'la birlikte kim olduklarını ve başlarına ne geldiğini bulmaya çalışıyoruz. Annem doğumda ölmüş, bunu zaten öğrendik. Ama babamla ilgili işler o kadar basit değil...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "Hangi yılda doğdun, hatırlatsana...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "1638 yılında. Haziran ayında.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "O zamanlar sadece on iki yaşındaydım, Mary. O günleri pek net hatırlamıyorum. Şimdi bazı anılar aklımdan geçiyor tabii, ama dürüst olmak gerekirse, hepsini bir araya getirmek biraz zor. Üzgünüm, ama sana yardımcı olabileceğimden şüpheliyim...";
			link.l1 = "Senden tam olarak bunu istemiyoruz, Antonio. Ama Mary'nin doğduğu günle ilgili herhangi bir şey hatırlarsan, çok minnettar oluruz.";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "O zaman sana nasıl yardımcı olabilirim, "+pchar.name+"?";
			link.l1 = "Tarihe ilgi duyduğunu söylemiştin. Sadece dünya tarihine değil, özellikle Adalet Adası'nınkine de.";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "Doğru. Bulabildiğim her kitabı okudum, elime geçen her el yazmasını inceledim...";
			link.l1 = "Bahsettiğimiz şey el yazmaları. Senden başka, Adada tarih konusunda senin kadar tutkulu olan sadece bir kişi daha vardı...";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "Alan Milroe. Tamam mı, bunu Rivadoları yok etmeye ve sonra da korsanları ortadan kaldırmaya kafa yormadan önce konuşmuştuk. Akıllı biriydi, gerçekten dikkat çekici yetenekleri vardı.";
			link.l1 = "Hiç şüphe yok – o çocuk bambaşkaydı. Bize yardımcı olabilecek bir şeyi vardı. Ve bu, Adalet Adası’nda kimseye bir fayda sağlamaz, sadece size ikinize. Adanın yakınlarında batan gemilere ait günlükler, kurtarılan yüklerin ve değerli eşyaların açıklamaları, belki de yolcuların isimleri bile var...";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "Aynen öyle.";
			link.l1 = "Yani, onları gördün mü?";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "Onları sadece görmedim – içerdikleri bilgileri kendi notlarıma da geçirdim. Sohbetlerimizden birinde, bu günlüklerin varlığından bahsetti ve ben de onlardan çalışmak için istedim – Adalet Adası'nın Kronikleri gibi bir şey hazırlamaya çalışıyorum, o kayıtlar bana çok yardımcı oldu.\nAlan bu fikrime bayıldı – buranın tarihini yazmak. Gerçi bana tüm kayıtları vermedi, 1650'lerden olanları kendine sakladı, ama o zamanlar geri kalanı bana yetiyordu.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = " Bu kayıtlar... 1638 yılını da kapsıyor, değil mi? Lütfen, öyle de ki!";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "Bu günlüklerden bir yığın var bende – taa 1620'ye kadar gidiyor. Alan'a göre, bu kayıtları tutmaya o zaman başlamışlar. Ve evet, 1638 de orada, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "Onlara bir bakmamıza izin verir misin?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			if (PChar.location == "PlutoStoreSmall") StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
			else StartInstantDialog("LSC_Betancur", "WildRose_Betancur_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "Görünüşe bakılırsa başka seçeneğim yok, ha-ha-ha! Dur bir. Hepsi burada, bu dolabın alt çekmecesinde.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = " Lütfen, rahatınıza bakın, dilediğinizce araştırın...";
			link.l1 = "Aynen öyle yapacağız.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "Al işte, "+pchar.name+", bak! Joshua ve Teresa Casper! İnanamıyorum – başardık, gerçekten başardık, tamam mı! Ve geminin adı 'Wrangler'! Şimdi babam hakkında her şeyi öğrenebiliriz – kimdi, buraya nasıl geldi...";
			link.l1 = "Korkarım, "+npchar.name+", acele ediyorsun... İşler göründüğü kadar basit olmayabilir. Majestelerinin gemisi... Kraliyet Donanması arşivlerinden bilgi almamıza kim yardım edebilir, bunu düşünmemiz gerekecek...";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "Hadi düşünelim! Düşünelim, bulacağız, "+pchar.name+"! En zoru zaten geride kaldı, tamam mı!";
			link.l1 = "Belki de Bay Young ve Bay Friddick ile konuşmak mantıklı olur, tamam mı? Ama Adada bu isimleri taşıyan kimseyi hatırlamıyorum.";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Çünkü burada değiller, "+pchar.name+" . O ikisi, Caspers ailesiyle birlikte kurtarıldıktan hemen sonraki gece öldü.";
			link.l1 = "İlginç. Hamile kadın bir hafta daha yaşadı, oysa Kraliyet Donanması'ndan iki denizci aniden öldü...";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = " Başından beri iyi değillerdi, hatırladığım kadarıyla. Şimdi tekrar aklıma geliyor, "+pchar.name+" – Ceres Demirhanesi'nin oradaydım, onları gemiye getirdiklerinde... Tamam mı, sanırım Orelie Bertine'le birlikte Esmeralda'daydım. Bir de o siyah putperestlerin şamanı Chimiset vardı, nedense dükkâna gelmişti. Başta iki denizcinin zaten ölmüş olduğunu sandım, ama sadece bir gün sonra öldüler...";
			link.l1 = "Pekala, yapacak bir şey yok. Ama zaten epey şey öğrendik. Yardımın için teşekkür ederim, Antonio.";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = " Teşekküre gerek yok, "+pchar.name+". Hepsi Alan sayesinde oldu – o zırhlıların çoğu bu kayıtların gerçek değerini asla anlayamazdı. Ama işte böyle belgelerle tarih yeniden ortaya çıkıyor!";
			link.l1 = "Umarım bir gün Mary ve ben senin Günlüklerini okuruz, dostum. Al, bu da günlüğün—sakın kaybetme. Evet, artık gitme vakti. Belki bir gün tekrar karşılaşırız, dostum.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Çünkü burada değiller, "+pchar.name+" . O ikisi, Caspers ailesiyle birlikte kurtarıldıktan hemen sonraki gece öldüler.";
			link.l1 = "İlginç. Hamile kadın bir hafta daha hayatta kaldı, ama Kraliyet Donanması’ndan iki denizci aniden öldü...";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "Seni tekrar görmek güzel, dostum. Seni buraya getiren ne?";
			link.l1 = " A request, +npchar.name+... Or rather, a question.";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "Sorunu sor. Ya da isteğini söyle. Sana yardım etmek için elimden geleni yapacağım.";
			link.l1 = "Tamam mı? Ne zamandır Adalet Adası'nda yaşıyorsun?";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "On yıllar boyunca, dostum. Ben buraya çocukken geldim, ama akıllıydım – bir köle gemisinde. Benim hikayem burada duyduğun birçok hikayeden pek farklı değil. Bir fırtına, bir gemi enkazı... Hapsedildiğim İngiliz kalyonu, dış halkaya bile ulaşamadı; dalgaların üzerine attığı kayalardan birine çarpınca ortadan ikiye ayrıldı.";
			link.l1 = "Nasıl hayatta kaldın? Kayalıklar dış halkadan epey uzakta, fırtınalı dalgaların arasından buraya gelmek de, dürüst olalım, hiç kolay bir iş değil...";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = "O gece tanrılar benim yanımdaydı. Kelepçelerimden kurtulmayı başardım, sonra bir teknenin parçasına tutundum. Yanımda bir kabile üyesi vardı, Asana – birlikte dalgalarla savaştık, ta ki yorgunluktan bayılana kadar.";
			link.l1 = "Gemilerden birine mi vuruldun, di mi?";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "Evet, ambarın içinde bir deliğe süründük... Orada tekrar bayıldım, o kadar zayıftım ki. Kendime geldiğimde Asana çığlık atıyordu – yıkandığımız aynı gemiye tırmanmış dev bir yengeç onu paramparça ediyordu. Ve ben sadece orada durup izledim, sıranın bana geleceğini bilerek – korkudan ve çaresizlikten donup kalmıştım, kımıldayamadım bile.";
			link.l1 = "Arkadaşına yardım etmeyi deneyebilirdin. Ama o zaman şu an konuşuyor olmazdık, değil mi? Peki, nasıl kurtuldun?";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "Seninle başlamadığına şükret, "+npchar.name+". Peki nasıl kaçtın – tekrar suya atlayıp yüzerek mi uzaklaştın?";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "Asana'nın çığlıklarını, son kasırgadan sonra gemilerin ambarlarını yağmalamaya çıkan birkaç Rivado duydu. Canavarı çevreleyip öldürdüler. Asana için kimsenin yapabileceği bir şey yoktu, ama ben çok daha şanslıydım. İşte böyle geldim buraya. Ama şimdi sıra sende, dostum – bütün bunları neden bilmek istedin?";
			link.l1 = "Aslında, "+npchar.name+", sana nasıl buraya geldiğini değil, ne zaman olduğunu soracaktım.";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "Asana'nın çığlıklarını, son kasırgadan sonra gemi yükü avına çıkan birkaç Rivados duydu. Canavarı çevreleyip öldürdüler. Asana için yapılacak başka bir şey kalmamıştı ama ben çok daha şanslıydım. İşte bu yüzden şimdi buradayım. Ama şimdi sıra sende, dostum – bütün bunları neden öğrenmek istedin?";
			link.l1 = "Aslında, "+npchar.name+", buraya nasıl geldiğini değil, ne zaman olduğunu soracaktım.";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "Hmm, senin takvimine göre yıl 1623'tü, yaz sonu – bundan daha kesin bir şey söyleyemem...";
			link.l1 = "Gerek yok. Yani, 1638 yılında, Adalet Adası’nda zaten on beş yıldır bulunuyordun.";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "Öyle görünüyor, dostum.";
			link.l1 = "O yılın Haziran ayında, kasırga 'Wrangler' adlı brigantin Adalet Adası'nın dış halkasına sürükledi — Majesteleri Kral Charles I’in filosuna ait bir gemiydi bu. Mürettebattan sadece dört kişi hayatta kaldı — aralarında Mary’nin anne ve babası, Joshua ve Teresa Casper da vardı.";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "Tamam mı, bunu hatırlıyorum, dostum. Hafifçe, sanki bir sisin içinden bakar gibi, ama yine de hatırlıyorum...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "Gerçekten hatırlıyor musun? O zaman anlat, hadi!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "Fazla bir şey söyleyemem. Dört kişi: bir subay, karısı ve iki denizci. Kadın hamileydi, kurtaranlar sabaha çıkamaz diye düşünmüş, ama o aslan gibi güçlü çıktı, iki denizciyse bir günden az bir sürede bu dünyadan göçtü... Gördüm onları: zayıflardı, ama hâlâ içlerinde biraz hayat kalmıştı...";
			link.l1 = "Onların öldürüldüğünü mü ima ediyorsun?";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "Eğer öyleyse, o zaman buna şahit olan kimse yoktu ve bedenlerinde de hiçbir yara izi yoktu, dostum...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "Sen 'subay' dedin, tamam mı... Babam gerçekten subay mıydı?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "Bir subay üniforması giymişti – neye benzediğini hatırlamaya çalıştığımda aklımda kalan tek şey bu, sanırım.";
			link.l1 = "Eğer subaysa, başka bir şey giymiş olamazdı – gardırobunun çok çeşitli olduğundan şüpheliyim... Belki başka bir ayrıntı hatırlıyorsundur, "+npchar.name+"? Belirgin bir özelliği var mı... Mesela, yüzünde bir yara izi ya da başka bir sakatlık...";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "Çok bir şey hatırlamıyorum, dostum. Yüzü hafızamdan neredeyse silinmiş – yirmi yıl oldu... Ama bakışını – onu çok iyi hatırlıyorum. Bu adamla sadece bir kez konuştum, ama o gri gözlerindeki bakışı – tıpkı Mary'ninkiler gibi – asla unutamam. O gözlerde bir umutsuzluk vardı, köşeye sıkışmış bir antilop gibi bir korku, ama aynı zamanda – bir aslana yakışır bir öfke ve kararlılık...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "Onunla konuştun, tamam mı? Ne hakkında?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "Sen doğmadan birkaç saat önce oldu. Buraya, 'Koruyucu'ya geldi ve beni görmek istediğini söyledi. Rivados'un lideri Mogedi, onun bu cesaretine şaşırmıştı – ama ben birdenbire bu adamdan etkilenmiştim. Karşımda durduğunda dizlerinin üstüne çöktü ve karısını kurtarmam için bana yalvardı... Burada geçirdikleri kısa sürede birileri ona benden bahsetmeyi başarmıştı. Mogedi karşı çıkmasına rağmen kabul ettim...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = " O zaman sana hayatımı borçluyum, değil mi?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "Yalan söylemenin anlamı yok – annenize ulaşmayı başardık, ama çok geçti: Narwhal’lar beni ‘Ceres Smithy’ye almaya yanaşmadılar. Babanız onları... ikna etmeyi başardı, ama zavallı Teresa’yı sadece son nefesini verirken görebildim. Seni dünyaya getirdi ve eğer biraz daha önce yetişebilseydim, belki onu kurtarabilirdim, ama...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "Annem öldü.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "Ne yazık ki. Sana baktı ve son nefesini verdi, ama ondan önce, sanki bütün gücünü toplayarak, Rupert adında birini çağırdı. Adını var gücüyle haykırdı, sanki yardım istiyormuş gibi – ve sonra öldü.";
			link.l1 = "Rupert mi? Joshua değil mi?";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "Sana bunları anlatırken, dostum, sanki o anı yeniden yaşıyormuşum gibi hissettim. Bunu asla unutmayacağım – ne ölürken attığı çığlığı, ne de acıdan buruşmuş yüzünü. Ve evet, dudaklarından dökülen son kelime 'Rupert'tı.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "Annem güzel miydi? Bana nasıl göründüğünü anlatabilir misin, Chimiset?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = " Gerek yok Mary. Sadece aynaya bak – ona tıpatıp benziyorsun. Sadece o delip geçen bakışlarını babandan almışsın.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "Peki ya o, ona ne oldu? Doğduktan sadece birkaç gün sonra ortadan kaybolduğunu öğrendik, tamam mı! Ama öldürülmemiş, değil mi?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "Teresa'nın ölmekte olduğunu duyar duymaz, Joshua tam anlamıyla öfkeye kapıldı – yemin ederim, savanadaki aslanlar bile avlarına babanın o narvallara saldırdığı kadar öfkeyle saldırmazdı, beni flüte almayanlara... Onu zapt etmek için altı adam gerekti – hem de iki klan savaşçısını zırhlarıyla birlikte suya fırlattıktan sonra.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "Ve ona ne yaptılar - söyle bana, hadi!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "Onu 'Tartarus'un hücrelerinden birine attılar. Kimse onu yargılamaya cesaret edemedi—herkes önce hikayenin unutulmasını bekliyordu... Hemen herkes ona acıdı, ama çok azı böyle biriyle yan yana yaşamak isterdi. Joshua birkaç gün sonra ortadan kayboldu—tam o sıralarda, birkaç kaçakçı teknesi Adadan ayrılmıştı. Kimse onu teknelerde görmedi, işte bu yüzden ölümüne dair söylentiler başladı.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "O hâlâ yaşıyor diyorsun, di mi?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "Sana başkalarının da mutlaka söyleyeceği şeyi söyleyeyim – kimse onun cesedini bulamadı. Belki de teknelerden birinin dibine saklandı, ya da belki o hücrede boğazını kestiler ve yengeçlere yem ettiler...";
			link.l1 = "Onun ortadan kaybolmasının tam da o tüccarların yola çıktığı zamana denk gelmesi, ilk seçeneği daha mantıklı kılıyor – böyle tesadüfler olmaz. Belki de birine planlarından bahsetti, ağzından kaçırdı? Eğer kaçtıysa, kaçtı; yeni doğmuş kızını burada bırakıp gitti, ki bu da bir bakıma mantıklı – bir bebek, o çürük kayıkla Küba'ya yolculuğa dayanamazdı... Ama kesinlikle onu almak için geri dönmeyi düşünmüştür.";
			link.l1.go = "WildRose_Chimiset_51";
		break;
		
		case "WildRose_Chimiset_51":
			dialog.text = "Bilmem, dostum. O zamanlar Joshua Casper biriyle konuştuysa, bu ancak gardiyanları olabilirdi – ama onların hepsi çoktan bu günahkâr dünyadan göçüp gitti. Ha, bir de evet, bir gün Padre Domingo onu görmeye gelmişti – beyazların rahibiydi, Brother Julian’dan önce...";
			link.l1 = "İtiraf mı edecekti yoksa? Kaçarken öleceğinden mi korktu, ne?";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "Bilmediğim bir şeye ışık tutamam, dostum. Domingo da sana bir şey anlatamaz – çünkü kendisi yaklaşık on beş yıldır ölü, tamam mı? Belki birisi kafasına vurdu, belki de içkiyi fazla kaçırıp öldü – içkiyi pek severdi o...";
			link.l1 = "Ama belki Domingo bir günlük tutmuştur... ya da o konuşmayı Joshua'yla yaptığını kardeşi Julian'a anlatmıştır, di mi?";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "Onunla konuşmamız lazım, "+pchar.name+", tamam mı? Ve ne kadar erken olursa, o kadar iyi. Bu işi halletmeden gemiye dönmeyi düşünmek bile istemiyorum.";
			link.l1 = "Eğer hâlâ çözmemiz gereken bir şey kaldıysa... Julian’ın bundan haberi bile olmayabilir – ama biz işin aslını mutlaka öğreneceğiz. Teşekkür ederim, Chimiset.";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "Her zaman hizmetindeyim, dostum. Ama ikinize de bir tavsiye vereyim.";
			link.l1 = " Peki, o da ne?";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "Ava çıktığında, çalılıkların içine fazla dalma — bir daha yolunu bulamayabilirsin.";
			link.l1 = "Bunu unutmayacağız, şaman. Ve şimdi – elveda.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "Tanrı'nın evinin koruması altına hoş geldiniz, evlatlarım. İtiraf etmeye mi geldiniz, yoksa sadece dua mı etmek istiyorsunuz?";
			link.l1 = "Selamlar, Rahip Julian. Korkarım günahlarımızı saymak çok uzun sürerdi, ki ne yazık ki o kadar vaktimiz yok. Ama emin olun, iyi Katolikler olarak her limanda kiliseye gideriz.";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "Selamlar, Kardeş Julian. Biz dindar Katolikler olarak, günümüze Rabbimize dua ederek başlar ve aynı şekilde bitiririz.";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = " Evlilik dışı aynı çatı altında yaşayan iyi Katolikler... Bu neredeyse küfür sayılır, evladım. Ve bu, sana hatırlatırım, büyük bir günahtır!";
			link.l1 = "Kutsal Kitap, sevginin tüm günahları örttüğünü söylemiyor mu, di mi?";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = " İyi Katolikler olarak evlenmeden aynı çatı altında yaşamak... Bu neredeyse küfür sayılır, evladım. Ve bu, hatırlatayım, büyük bir günahtır!";
			link.l1 = "Ve Kutsal Kitap, sevginin bütün günahları örttüğünü söylemiyor mu, tamam mı?";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "Aşk, O'nun buyruklarına göre yaşamak demektir – bunları sana hatırlatmam gerekiyor mu, oğlum?";
			link.l1 = "Başka bir zaman. Biz burada başka bir iş için geldik.";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "Kayıp ruhların doğru yola dönmesi için asla geç değildir... Ama sizi dinliyorum, çocuklarım.";
			link.l1 = "Gerçekten de biraz kaybolduk, Julian Kardeş. Geçmişin çalılıklarında yolumuzu şaşırdık. Ve umuyoruz ki, bizi tekrar aydınlığa çıkarabilirsin.";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "Çok zekice, oğlum. Şunu unutma ki, insanı aydınlığa götüren insan değil, Rab'dir – ve O'nun peşinden giderken, yollarının gizemli olduğunu daima hatırla.";
			link.l1 = "Kısa keseceğim, Kardeş Julian. Mary'nin ailesi hakkında öğrenebileceğimiz her şeyi bulmaya çalışıyoruz. Annesi Teresa'ya gelince, durum az çok belli—kocasıyla birlikte Adalet Adası'na gelmiş ve bir hafta sonra doğum sırasında ölmüş. Ama babası... Mary doğduktan birkaç gün sonra ortadan kaybolmuş, 'Tartarus'tan kaçmış. Söylentiye göre, burada konuştuğu son kişi senin selefin Padre Domingo'ymuş.";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "O zaman en az on beş yıl geç kaldınız, çocuklarım.";
			link.l1 = "Evet, biliyoruz ki padre epey zaman önce öldü. O zamanlar, Julian Kardeş, sen hâlâ Adaya uygun rütbeyle gelmek için çok gençtin, öyle değil mi?";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "Onun ölümünden birkaç yıl sonra kendimi burada buldum. Burada, bu gemide her şeyi yoluna koymak çok çaba gerektirdi ama Tanrı'nın yardımıyla başardım, oğlum.";
			link.l1 = "Burada işleri hallederken, Domingo Baba'nın kayıtlarına rastladın mı, oldu mu?";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "Özel bir şey mi kastediyorsun, oğlum?";
			link.l1 = "Günlükler ya da bir çeşit seyir defteri arıyoruz... Bir mucizeye pek umut yok, ama belki padre o konuşmanın içeriğini notlarından birine kaydetmiştir. Mary'nin babasının adadan kaçakçıların teknelerinden biriyle ayrıldığına inanıyoruz—belki de padreye nereye gideceğini ve kızını almaya ne zaman döneceğini ima etmiştir?";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "Hiçbir zaman günlük ya da buna benzer bir şey bulmadım, orası kesin, ama her türlü kayıt vardı... Kilise işleri söz konusu olduğunda oldukça titizdi— her Tanrı hizmetkârına böyle bir titizlik nasip olmaz. Ama evraklarında sadece kuru kuruya rakamlar ve isimler var— başka hiçbir şey yok.";
			link.l1 = "Öğrenebildiğimiz kadarıyla, Joshua Casper – adı buydu – karısının ölümünden sonra öfkeye kapılıp, rivados büyücüsü Chimiseta'nın Mary'nin annesini görmesine izin vermeyen Narwhal klanından iki kişiyi öldürmüş...";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "Gerçekten Kilise'nin çocukları gibi davrandılar! Engizisyonun zindanları bu Şeytan'ın hizmetkârını bekliyor!";
			link.l1 = "Tanrı, bence O, adına kaç kişinin işkence gördüğünü bilse dehşete kapılırdı. Casper daha şanslıydı – onu sadece ‘Tartarus’a bir hücreye attılar, ama yargılanmaya hiç çıkamadı.";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "Evet, evet, bunda hiç şüphe yok. Casper'ı 'Tartarus'taki hücrelerden birine attılar, ama hakkında bir hüküm verilmedi – karısını kaybetmiş bir adamın yaptıklarını herkes kınamadı.";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "Sonra ne oldu – o kafir kaçtı mı?";
			link.l1 = "Bir haftadan kısa bir süre sonra Joshua ortadan kayboldu. Ondan önceki gece ise Padre Domingo onu ziyarete geldi. Şimdi asıl soru şu—neden? Casper kesinlikle Protestan’dı, bir Katolik rahibe günah çıkarması pek olası değil, sence de öyle değil mi?";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "Sonra ne oldu – o kafir kaçtı mı?";
			link.l1 = "Bir haftadan kısa bir süre sonra Joshua ortadan kayboldu. Ondan önceki gece, Padre Domingo onu görmeye geldi. Yani soru şu – neden? Casper kesinlikle Protestan’dı, bir Katolik rahibe günah çıkarması pek olası değil – sence neden olabilir?";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "Gerçek imana dönmek için asla geç değildir, oğlum. Ama mantığın sağlam. Eğer itirafa ihtiyacı yoksa, belki de karısının cenaze törenini papazla konuşuyordu—tabii eğer karısı Katolikse. Ya da belki kızının vaftizini, ya da daha doğrusu, vaftizi reddetmeyi konuşuyordu, çünkü Protestanlar bebekleri vaftiz etmez, kişinin vaftiz olmaya kendi iradesiyle ve bilinçli olarak karar vermesi gerektiğine inanırlar.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "Ama vaftiz edildim, Julian Kardeş. Eric Udette bana bundan bahsetmişti.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "Bunlar sadece benim varsayımlarım, evladım. Gerçeği ben de bilmiyorum. Rabbimiz gözlerimizi yalnızca gerçekten önemli ve gerekli olana açar.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "Ve işte tam olarak benim için de böyle, tamam mı? Belki Padre Domingo'nun kayıtlarının sayfalarında senin fark etmediğin bir şeyler kalmıştır, Julian Kardeş? Sonuçta, sadece göz gezdiriyordun, değil mi?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "I had no business there, my child. I can see you've been working on this for a long time, and with great care – the Lord is guiding you down this thorny path. If you are meant to find what you seek, then it is His will, and it is not for me to stand in its way. I can give you Domingo's records from the year you were born; perhaps you'll find something useful in them.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "Bu çok cömertçe olurdu, Julian Kardeş. 1638 yılından kalma kayıtlar hâlâ sende mi?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "Pekâlâ, pekâlâ... (tozu üfler). Görünüşe bakılırsa bu o. 1638 Milattan Sonra yılının defteri.";
			link.l1 = "Bırak ben halledeyim, Julian Kardeş...";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "Bak, "+pchar.name+": 3 Ağustos. Fabian’la vaftiz edildiğimiz gün. Ben 22 Haziran’da doğdum. Ama babam hakkında tek kelime yok, tamam mı.";
			link.l1 = "Kardeş Julian'ın dediği gibi – kuru rakamlar ve isimlerden başka bir şey yok. İlginç olan şu ki, Padre Domingo görevlerinde öyle hevesliymiş ki, Protestanlara bile son ayinleri yapmış – van Ekkus, Young ve Friddicks'in Katolik olduklarından şüpheliyim.";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "Cennetin Krallığı'na adım atacakları anda, gerçek inanca dönebilirlerdi, evladım.";
			link.l1 = "Elbette, Julian Abi—başka ne yapacaklardı ki? Özellikle Soren ve Rojas gibi öldülerse—sanırım Chimiset’in yolunu kesen Narvaller tam da onlardı.";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "Padre Domingo'nun ikinci adları tam olarak yazması daha iyi olurdu, tamam mı? Annemin adından ve benimkinden sonraki şu 'V.' ve 'J.' ne anlama geliyor ki?";
			link.l1 = "Ve bu Fabian kim, seninle aynı gün vaftiz edilen kişi?";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "Cecille Halard’ın oğlu. Ah, şimdi hatırladım! Beni o büyüttü, ama hiç de sıcak biri değildi. Muhtemelen ben hayatta kaldım, Fabian ise kalamadı diye. Fabian doğduktan birkaç ay sonra öldü, tamam mı?";
			link.l1 = "Belki de onunla konuşmalıyız, çünkü bu küçük kitaptan neredeyse hiçbir işe yarar şey öğrenemedik—tabii, doğum ve vaftiz tarihlerinin senin için bir anlamı varsa, o başka.";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "Orelie'den çok daha genç sayılmaz, "+pchar.name+" . Tek umabileceğimiz, en azından aklını başında tutmuş olması. Ama ona ne sormayı düşünüyorsun?";
			link.l1 = "Şey, hemşiren olduğuna göre, Padre Domingo’nun Joshua ile konuşması hakkında bazı ayrıntıları biliyor olabilir. Başka kime anlatacaktı ki, ona anlatmadıysa? Belki Orelie ya da Eric’e de söylemiştir. Ama bence ilkinden alabileceğimiz her şeyi aldık, ikincisi ise artık kimseye hiçbir şey anlatamaz.";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "Bu iyi kadın, Tanrı'nın bu evinin sadık bir cemaati. Hiçbir ayini kaçırmaz ve düzenli olarak günah çıkarır. Gerçekten size yardımcı olabileceğine inanıyorum, çocuklarım.";
			link.l1 = "Teşekkür ederim, baba. Elveda.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+" ve Mary Casper. Ne hoş bir sürpriz!";
			link.l1 = "Aynı şekilde, "+npchar.name+". Aslında, seni görmeye geldik. Seninle konuşmak istediğimiz bir şey var.";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "Gerçekten mi? Şey, şimdi tamamen seni dinliyorum.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "Bu annemle babamla ilgili, Cecille. Annem hakkında öğrenebileceğimiz her şeyi zaten öğrendik... Ben doğduktan hemen sonra ölmüş. Ama babam... o, birkaç gün sonra hiçbir iz bırakmadan kaybolmuş. Biz de genelde onun ölmediğini düşünürüz, tamam mı?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = " Gerçekten de, onun gibi bir adamı öteki dünyaya göndermek bayağı bir çaba isterdi...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "Onu gördün mü?! Onunla konuştun mu?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "Kızım, onu iki Narwhal'ı elleriyle yere seren biri olarak gördüm, neredeyse...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = "Sorreno ve Rojas?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "O zamanlar elim çok doluydu, o alçakların isimlerini hatırlamaya vaktim yoktu – şimdi ise hiç hatırlayamıyorum.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "Tamam mı, önemli değil. Lütfen devam et, Cecille.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "Ve devam edecek ne kaldı ki? O ikisini denize attı, taş gibi battılar, sonra da onu bağlayıp 'Tartarus'a sürüklediler. Doğrusunu yaptılar – kim bilir, o katil daha kimi boğmaya kalkardı...";
			link.l1 = "Katil mi? Bu biraz ağır olmadı mı, Bayan Halard? Burada bir adamdan, karısını yeni kaybetmiş bir subaydan bahsediyoruz...";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "Onun hakkında pek iyi düşünmediğini görüyorum – her subay hakkında böyle konuşulmaz, biliyorsun.";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "Subay, vay canına. Üniforması gerçekten dikkat çekiciydi, hâlâ aklımda. Neredeyse yepyeniydi. Ama ben hayatımda çok subay gördüm, genç adam. Ve hepsi de o... beyefendiden çok daha düzgün davranıyordu.";
			link.l1 = "Başka bir şey yaptı mı? O ikisini öldürmekten başka?";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "Subay, hmm, hmm. Üniforması gerçekten ilginçti, hâlâ gözümün önünde. Neredeyse yepyeniydi, terziden yeni çıkmış gibiydi. Ama ben hayatımda çok subay gördüm, delikanlı. Ve hepsi bu... beyefendiden çok daha düzgün davranırdı.";
			link.l1 = "Başka bir şey yaptı mı? O ikisini öldürmekten başka?";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "Hücresinde bir rahip görmek istedi – Padre De la Cruz...";
			link.l1 = "Bak hele şuna! Tam da seninle konuşmak istediğimiz şey buydu. O konuşmanın detaylarını biliyor musun?";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "Elbette, genç adam! O alçak Protestan, rahibin kızını vaftiz etmemesini istedi—halbuki annesi İrlandalıydı, yani Katolikti.";
			link.l1 = "Bir İngiliz kadınının bir Protestan hakkında böyle konuştuğunu neredeyse ilk kez duyuyorum... Hımm, böldüğüm için affedin, Bayan. "+npchar.lastname+".";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "Ben de eskiden Protestan’dım, saklamanın anlamı yok. Ama Julian Kardeş beni doğru yola yönlendirmeyi başardı.";
			link.l1 = "Demek öyle... Gerçekten de Tanrı'ya adanmış bir hizmetkâr. Ama konudan uzaklaştık. Yani, Casper kızının Protestan inancıyla yetişmesini istemiş.";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "Tam olarak bunu bizim papazımız De la Cruz'a söyledi. Bir de kıza Julia adını vermelerini emretmiş...";
			link.l1 = "Demek 'J.' harfi bunun içinmiş. Mary Julia Casper... Ama o zaman neden ona Mary demişler?";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "Çünkü annesi öyle istedi, işte bu yüzden. Kız onun karnından alındığında, bir isim fısıldamış – Mary. Orada değildim, ama Orelie Bertine doğumda yanındaydı. İstersen ona sorabilirsin...";
			link.l1 = "Yani annenin isteklerine boyun eğdin, öyle mi?";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = " Peki başka nasıl olabilirdi ki, işe yaramaz baba sanki havaya karışıp kaybolmuşken?";
			link.l1 = "Padre De la Cruz’un yetenekleri düşünüldüğünde, babanın fikri önemli olur muydu bilmiyorum, Tartarus’ta kalsaydı bile. Domingo sana söylemedi mi—Casper’ın kaçıp belki de kızı almak için geri dönmeyi planladığından haberi yoktu?";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "Belki de haklısın. Ama Peder Domingo’nun Bay Casper’la konuşmasına dönersek — rahip, Joshua’nın onunla kaçmaktan ya da kızını almaya ne zaman döneceğinden bahsedip bahsetmediğini söyledi mi?";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = " Böyle bir şeyden hiç bahsetmedi. Bir düşün, "+npchar.name+", eğer hapisten kaçmayı planlasaydın, bunu her önüne gelene anlatır mıydın? O adam kesinlikle anlatmazdı, sana bunu söyleyebilirim.";
			link.l1 = "Yani, bu ipucu da bizi bir yere çıkarmadı. Neyse, vaktinizi ayırdığınız için teşekkürler, Bayan. "+npchar.lastname+". Görüşürüz.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = " Böyle bir şeyden hiç bahsetmedi. Bir de düşün, "+npchar.name+", eğer hapishaneden kaçmayı planlasaydın, bunu her önüne gelene anlatır mıydın? O adam kesinlikle anlatmazdı, sana bunu söyleyebilirim.";
			link.l1 = "Yani, bu ipucu da bir çıkmaza çıktı. Neyse, vaktinizi ayırdığınız için teşekkür ederim, Bayan. "+npchar.lastname+". Görüşürüz.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "Oldukça ilginç şeyler öğrendik, "+pchar.name+". Ama neredeyse hiç ilerleyemedik, tamam mı.";
			link.l1 = "Ve hatta biraz karıştık bile. Merak ediyorum, annen ölmeden önce adını andığı bu Rupert kim acaba?";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "Belki bir erkek kardeş, ya da... yakın bir arkadaş, di mi?";
			link.l1 = "Arkadaş, diyorsun ha... Acaba Joshua ondan haberdar mıydı...";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "Ne demeye çalışıyorsun, "+pchar.name+"?";
			link.l1 = "Tüm bunları iyice düşünmemiz gerekiyor, tamam mı? Neyse ki, arayışımızda bize yardımcı olabilecek birini bulmaya çalışırken bolca vaktimiz olacak. Şimdiye kadar çok şey yaptık. Ama işimiz henüz bitmedi. Kraliyet Donanması'nın ofisine kendimiz giremeyiz, hem de ta Londra'da, okyanusun öbür ucunda... Sence bu konuda bize kim yardım edebilir?";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "Serge Benoit ne olacak, Charles?";
			link.l1 = "Abbot mı? Evet, çevresi geniş, doğru, ama Kraliyet Donanması arşivlerine girebileceğinden şüpheliyim.";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = "Eğer kendisi yapamıyorsa, belki bizi yapabilecek biriyle tanıştırır, tamam mı.";
			link.l1 = "Sanırım öyle. Yani, Saint-Pierre'e gidiyoruz.";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "Şimdi yapabileceğimiz tek şey beklemek, tamam mı.";
			link.l1 = "Eminim her şeyi öğrenecek, "+npchar.name+". Zaman su gibi akıp geçecek, farkına bile varmayacaksın. Şimdilik ise yapacak işlerimiz var.";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "Bir şeyi mi ima ediyorsun, canım?";
			link.l1 = "Yapacak çok işimiz var, ama neden gemiye dönüp kapıyı kilitleyip biraz baş başa vakit geçirmiyoruz, ha? Ne dersin?";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "Ve senin bunu önereceğini biliyordum, tamam mı! Benim fikrim şu: hiç vakit kaybetmeyelim!";
			link.l1 = "Hadi ama, canım.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "Oh, "+pchar.name+", senin hiçbir fikrin yok, gerçekten hiçbir fikrin yok, ruhumdan nasıl bir yük kalktı şu an, tamam mı!";
			link.l1 = "Seni hayal edebiliyorum, canım – adeta ışık saçıyorsun, ha-ha! Gördüğün gibi, her şeye değdi.";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "Babam ünlü bir subaymış, düşünebiliyor musun! Ama ne yazık ki hiç tanışamadık. Ve anakaraya ulaşıp ulaşmadığını bile öğrenemedik, tamam mı...";
			link.l1 = "Eğer öyle olsaydı, kesinlikle tekrar göreve dönerdi ve birileri, bir yerlerde, onun hakkında bir şeyler duyardı, tamam mı? Öyle bir adam asla öylece oturamaz – yoksa, sen bunu nereden almış olurdun?";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "Sence gerçekten öldü mü? Küba'da İspanyolların eline mi düştü, yoksa Adalet Adası'nda mı öldürüldü?";
			link.l1 = "Ben olaylara gerçekçi bakmaya çalışıyorum, "+npchar.name+". O zamanlar, Adalet Adası'na hâlâ biraz gidip gelinirdi. Kaçakçılar tartanlarıyla oraya düzenli olarak giderdi. Eğer gitmeyi başarsaydı, zamanla seni bulmak için mutlaka geri dönerdi, buna hiç şüphem yok.";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "Beni oradan çıkarmak için. Ama o zaman tanışamazdık, tamam mı.";
			link.l1 = "Hayat böyle, canım. Ne zaman ne bulacağını, ne zaman ne kaybedeceğini asla bilemezsin. Şu anda burada benimle olduğun için pişman olmazsın umarım, tamam mı?";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "Hayatımda bundan daha saçma bir şey duymadım, tamam mı! "+pchar.name+", sen harikasın, en iyisisin! Bana bu kadar yardımcı olmak için bu kadar çaba gösterdiğin için çok teşekkür ederim. Bu benim için gerçekten çok önemli, tamam mı! Ama hadi belgeleri bir inceleyelim—belki orada arkadaşımızın bize söylemediği bir şey buluruz...";
			link.l1 = "İyi fikir. Hadi hemen başlayalım.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "Şey, "+pchar.name+", ilginç bir şey fark ettin mi?";
			link.l1 = "Tamam mı, "+npchar.name+". Bir şey var...";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "Hayalet görmüş gibisin, di mi?";
			link.l1 = "Rupert Northwood'dan bahsediyor.";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "Rupert Northwood mı?! Gerçekten o mu?";
			link.l1 = "Sessiz ol, "+npchar.name+" - böyle bağırma. Hmm... Sanırım öyle, evet – Chimiset'in bahsettiği kişi bu. Başka türlü olamaz – böyle tesadüfler olmaz.";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "Peki, bütün bunlar hakkında sen ne düşünüyorsun, "+pchar.name+"?";
			link.l1 = "Bu hikaye gittikçe daha da karmaşıklaşıyor. Yani... 'Cornwall' Plymouth'tan yola çıkmış, 'Cornwall' aynı zamanda Antigua'ya da varmış, ama Adalet Adası'nın kayalıklarında batan gemi 'Wrangler'mış – dümenin başında yine aynı Joshua Casper varmış, ki bir şekilde Amirallik'ten gizli bir kadına evlenmiş, o kadın da can çekişirken Rupert adında birini çağırıyormuş.";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "Hiçbirini anlamıyorum. Kimin bu konuda bir şeyler açıklayabileceğini bile bilmiyorum. Babam hakkında ne kadar çok şey öğrenmeye çalışırsak, o kadar çok bu sırlar ve gizemler bataklığına saplanıyoruz, tamam mı.";
			link.l1 = "Eğer bu konuda bir açıklama getirebilecek biri varsa, o ya Joshua Casper ya da Rupert Northwood'dur.";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "Northwood mu? Ama o öldü, tamam mı? 'Cornwall' St. John’s’a vardığında tutulan raporun sahte olduğunu gerçekten düşünmüyorsun, değil mi?";
			link.l1 = "Ah, senin o saf halin yok mu, "+npchar.name+"... Bu hikayenin baştan sona yalanlarla dolu olduğunu düşünmeye başladım. Bir düşün: Joshua Casper örnek bir subaydı – bir sürü ödülü vardı ve tek bir uyarı bile almamıştı. Ama bu, Adalet Adası'nda onun hakkında öğrendiklerimizle hiç uyuşmuyor; orada iki adamı gözünü kırpmadan mezara gönderdi, sence de öyle değil mi?";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "Annem, yani karısı, için hayatı pahasına savaştı, "+pchar.name+"!";
			link.l1 = "Elbette, ama o zaman o kadın nereden çıktı? Ve daha da önemlisi, neden evliliği Amirallikten gizlemiş? Görevine ve kurallara sonuna kadar bağlı, tam bir kariyer adamı, yoksa sicili bu kadar temiz olmazdı, ama birden böyle bir şey yapıyor.";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "Ya peki, bütün bunların arkasında güzel, romantik bir hikaye varsa? Bazen olur öyle şeyler, nadiren de olsa, tamam mı?";
			link.l1 = "Beni yanlış anlama Mary, ama bu hiç aşk hikayesi gibi gelmiyor. Daha çok bir gösteri gibi, ve hâlâ bütün bunların neden yapıldığını anlayabilmiş değilim. Providence'a giderken neden geminin adını değiştirdiniz ki? Bu bir savaş gemisi—böyle numaralar seni mahkemeye çıkarabilir.";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "Kabul, güzel soru.";
			link.l1 = "Ve bu Rupert Northwood’da kesinlikle bir tuhaflık var. O savaşta tayfanın neredeyse yarısı öldü, ama garip bir şekilde, subaylardan sadece o hayatta kaldı. Ve neden Teresa ölüm döşeğinde kocasının adı yerine Rupert’in adını söyledi, Joshua’yı değil?";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "Yani, gerçekten emin misin birinci zabitin İspanyollarla savaşırken ölmediğine, ha? Ve ben aslında Joshua Casper’ın kızı değilim, Rupert Northwood’un kızıyım – demek istediğin bu mu?";
			link.l1 = "Daha önce de söylediğim gibi – gerçeği sadece bir kişi biliyor. Ya bir şekilde Teresa'ya karım diyen Joshua Casper, ya da en az onun kadar anlaşılmaz bir nedenle kaptanının adını alan Rupert Northwood.";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "Ne şeytani bir karmaşa, tamam mı! Şimdi ne yapacağız, "+pchar.name+"Şimdi gerçeği öğrenmeyi daha da çok istiyorum, ama zaten herkesten alabileceğimiz her şeyi aldık.";
			link.l1 = "Eğer cevaplar bir yerdeyse, Adalet Adası'ndadır – okyanusun bu tarafında, anne babanı tanıyan, hatta kısacık bile olsa, başka kimse kalmadı. Bence Orelie Bertine ile bir kez daha konuşmalıyız – belki de gözden kaçırdığımız bir şeyi hatırlar.";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "Ama ondan ne öğrenmek istiyorsun ki? Zaten bildiği her şeyi bize anlattı gibi görünüyor.";
			link.l1 = "Bize sorduğumuzu anlattı, ama önemli bir şeyi kolayca atlamış olabilir. Belki babanın yüzünde bir yara izi vardı ya da elinde bir parmağı eksikti... O kadar numarayı düşünen—geminin adını değiştiren, belki de kendi adını bile—birinin öylece bir adada ya da bir Kastilya zindanında sessizce ölüp gideceğine pek inanmıyorum.";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "Belki de haklısın...";
			link.l1 = "Eğer aramaya devam etmeye karar verirsek – Amiralti’nin tozlu raflarında değil de, burada, Takımadalar’da – sadece bir isme, hem de sahte bir isme, ihtiyacımızdan fazlası gerekecek.";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "Biliyor musun, bütün bunlar tüylerimi diken diken ediyor, tamam mı? Belki de her şey bu kadar... heyecan verici olduğu içindir, ya da belki de babamın Bishop’un plantasyonundaki o heriften çok da farklı olmamış olabileceği düşüncesindendir.";
			link.l1 = "Her halükarda, bu işin aslını öğrenmek için elimizden geleni yapacağımıza söz veriyorum. O yüzden vakit kaybetmeyelim. Hadi gidelim!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "Hadi gidelim, "+pchar.name+", daha fazla zaman kaybetmeyelim, tamam mı.";
			link.l1 = "Umarım Orelie kamarasında olur da, tüm Adalet Adası'nı aramak zorunda kalmayız...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "Yine şansımız yaver gitmedi, tamam mı? Bu sefer nereye gitmiş olabilir?";
			link.l1 = "Umarım hastalık yine aklını ele geçirmemiştir...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "Ah, yine geldin. Ee, merhaba... Ne oldu, yine Orelie'ye mi ihtiyacın var?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "Zekânı inkâr edemem, Jillian. Onun nerede olduğunu biliyor olamazsın, değil mi?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "Kilisede, itirafta bulunmak üzereydi. Acele edersen, onu orada bulabilirsin.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "Eh, madem itiraf ediyorsa, o zaman aklı da hafızası da yerinde, tamam mı?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = "Söylemesi zor... Son üç gündür kendinde değil, bir türlü rahatlayamıyor. Biliyor musun, nedense senin geminin direklerini dış halkada görünce fena halde huzursuz oldu.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "Acaba bunu neden söyledin?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "Sanırım senin tarafından tekrar sorgulanma düşüncesi onu huzursuz ediyor. Ama başkalarının dertlerini ne zamandan beri umursuyorsun ki?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "Bana böyle konuşmaya cüret etme, Jillian. Bu seferlik affediyorum seni, ama bir daha böyle bir şey söylemeye kalkarsan...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "Böyle huysuz bir kadın - bir şey hoşuna gitmezse hemen geriliyor, değil mi?";
			link.l1 = "Onu boş yere kızdırmamak en iyisi, "+npchar.name+". Biliyorsun, o kılıcı sadece gösteriş olsun diye taşımıyor.";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "Ve sen buna izin mi verecektin, "+pchar.name+"?";
			link.l1 = "Sen Mary'yi savaşta hiç görmedin, "+npchar.name+". Yoksa, hiç hayalin olmazdı - onu hiçbir şey ve hiç kimse durduramaz. Görüşürüz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "Bana muhtemelen bir şey sormak istiyorsun, di mi? "+pchar.name+", tamam mı...";
			link.l1 = "Açıkçası, aranıza ne girdiği umurumda değil, ama bunun belli bir kişiyle ilgili olduğunu tahmin ediyorum. Gerçekten konuşmak istiyor musun bunun hakkında?";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "Seninle Jillian arasında bir sorun mu çıktı? Yoksa, birisi yüzünden mi diyeyim?";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "Hmm, pek sayılmaz, hayır.";
			link.l1 = "Ne dersen de. Şimdi gidip Orelie'yi bulalım.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "O küçük sülük, Alan’ın beni onun yerine seçmesini asla affetmeyecek. Gerçi affedebilirdi, sonuçta artık o da yok... Açıkçası, "+pchar.name+", Bunu konuşmak istemiyorum, tamam mı.";
			link.l1 = "Dediğin gibi, canım. O zaman hadi Orelie'yi aramaya gidelim.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+", Mary! Adalet Adası'na döndün, ne büyük sevinç!";
			link.l1 = "Seni sağlıklı görmek güzel, "+npchar.name+". Aslında, Adalet Adası'na sadece seninle tekrar konuşmak için geldik. Ama merak etme, uzun sürmeyecek.";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "Ah, gençler, yaşlı bir kadına hiç acımanız yok gerçekten. Ama geleceğinizi hissetmiştim. Yine anne babanla ilgili bu, değil mi Mary?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "Lütfen, Orelie. Biliyorum, bunca zamandan sonra hatırlamak senin için zor, ama bir kez daha dene benim için, tamam mı.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "Sana hatırladığım her şeyi zaten anlattım. Daha neyi benden çekip almak istediğini hiç bilmiyorum.";
			link.l1 = "Sana birkaç sorumuz var, "+npchar.name+". Lütfen, bir şeyler hatırlamaya çalış—herhangi bir ayrıntı ya da aklına ne gelirse. Sana baskı yapmayacağız...";
			link.l1.go = "WildRose_Oreli_65";
		break;

		case "WildRose_Oreli_65":
			dialog.text = "Ve şu anda yaptığın şey tam olarak bu değil mi, di mi?";
			link.l1 = "Bizim için zaten çok şey yaptın, "+npchar.name+"... Tek umudumuz, hafızanın labirentlerinde bize çok yardımcı olacak başka bir şeyin de bulunması, tamam mı?";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "Uzun bir yol geldik, "+npchar.name+". Bize ne kadar emek ve zaman harcadığımızı hayal bile edemezsin. Ama yolumuzu kaybettik, ve bizi tekrar gerçeğin yoluna çıkaracak tek kişi sensin, bir de senin hafızan.";
			link.l2.go = "WildRose_Oreli_66_2";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "Anılar... Geriye ne kaldı ki, gerçekten. Bazı sabahlar kendi adımı bile hatırlayamıyorum, sen ise benden yirmi yıl önce olan şeylerle ilgili ayrıntılar istiyorsun. Ama tamam mı, sor bakalım.";
			link.l1 = "Mary'nin babası Bay Casper'la ilgileniyoruz. Görünüşüyle ilgili aklınızda kalan belirgin bir şey var mı? Belki yüzünde bir yara izi vardı ya da ağır aksak yürüyordu...";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "Anılar... Geriye ne kaldı ki, gerçekten. Bazı sabahlar tuvaleti nasıl bulacağımı bile hatırlayamıyorum, sen ise benden yirmi yıl önce bu enkazlarda ne olduğunu anlatmamı istiyorsun. Ama tamam, peki, sor bakalım.";
			link.l1 = "Bay Casper’ı, Mary’nin babasını soruyoruz. Görünüşüyle ilgili aklınızda kalan belirgin bir şey var mı? Belki yüzünde bir yara izi vardı, ya da topallayarak yürüyordu...";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "Ah... Sanırım daha önce söylemiştim, onu sadece zifiri karanlıkta, 'Ceres Smitty'nin ambarında gördüm, zavallı Teresa'ya bir yatak hazırlamışlardı orada. Kesinlikle topallamıyordu—aksine, oldukça çevik bir adamdı.";
			link.l1 = "Ve yaşı? Genç miydi yoksa yaşını almış biri mi?";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "Onu yaşlı bir adam olarak görmem, tamam mı... Ama ona pek dikkat etmedim – daha çok Teresa için endişeleniyordum. Oldukça perişan görünüyordu, sanki bir hayalet gibiydi. Ama unutma, bütün hafta boyunca neredeyse hiç uyumadı, karısı doğurmak üzereydi... Adanın her yerinde koşturup duruyordu, hiç durmadı.";
			link.l1 = "Demek ki karısını çok seviyormuş. Sen de onunla çok vakit geçirdin, değil mi? Hiç kocasından bahsetti mi?";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "Teresa sürekli onu sordu. Çok uyudu, bazen sayıklıyordu, ama ne zaman kendine gelse, yaptığı ilk şey onun nerede olduğunu sormaktı. Ve zavallı kız onu öyle, öyle çok bekledi ki. Ama en önemli anda – asla gelmedi.";
			link.l1 = "Anladım. Belli ki, onların aşkı karşılıklıymış... Neyse, sağ ol Orelie. Bize çok yardımcı oldun.";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "Ve bu kadar mı? Konuşmamız en az bir iki saat sürer sanmıştım.";
			link.l1 = "Sana fazla rahatsızlık vermeyeceğimize söz vermiştik. Kendine iyi bak, "+npchar.name+". Her şey gönlünce olsun.";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "Bekleyin, gençler! Sizin için başka bir şeyim var... Daha doğrusu, senin için, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			NPCsLookEachOther("LSC_Oreli", "Mary");
		break;
		
		case "WildRose_Oreli_72_a": //
			dialog.text = "Al bakalım, kızım, al... Geminin yelkenlerini görür görmez bu şapkayı yanıma aldım, unutmamak için. Ama iskeleye kadar inmek... Buna bir türlü cesaret edemedim.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "Ne oldu, Orelie? Bir şapka mı?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "Annenin şapkası, Teresa'nın. Gemiden kurtulanlar 'Ceres Demirhanesi'ne getirildiğinde yanındaydı. Teresa öldüğünde, o şapkayı yatağının yanındaki yerden aldım—tamam mı, sonra da tamamen unuttum... Bugün, seninle konuşurken hatırladım ancak.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_75":
			dialog.text = "Orelie... Bunca yıl boyunca saklamışsın! Ve... ve onu atmamışsın, satmamışsın... Teşekkür ederim, çok teşekkür ederim! Bu benim için ne kadar önemli, hiç bilmiyorsun, tamam mı!";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "Üzgünüm Mary — bunu sana çoktan vermeliydim... Ama hafızam artık eski bir süzgeç gibi — işte bu yüzden...";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "Bundan daha iyi bir an olamaz, Orelie! Hemen şimdi deneyeceğim, tamam mı!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "Peki, sevgilim, beni nasıl buldun?..";
			link.l1 = "Çok güzelsin. Ve şapka... daha modası geçmedi, o yüzden o da harika görünüyor.";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "Gerçekten mi? Beğenmene çok sevindim!";
			link.l1 = "Başka türlüsü mümkün mü, di mi?";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "Bir kez daha teşekkür ederim, Orelie – bu günü biraz daha aydınlattın! Her şey gönlünce olsun, iyi dinlen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "Demek gerçekten Rupert'mış. Rupert Northwood, tamam mı.";
			link.l1 = "Tabii ki, evet, canım. Karısını... ya da sevgilisini, bilmiyorum, kurtarmak için elinden geleni yapmış. Açıkçası, bunun pek bir önemi yok. Önemli olan, artık kimi aradığımızı biliyoruz.";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "Ama gerçek Joshua Casper'a, 'Cornwall'un kaptanına ne oldu?";
			link.l1 = "Güzel soru, ama şu an için en önemli soru bu değil. Eğer Rupert Teresa’yı bu kadar çok seviyorsa, neden senin için geri dönmedi – işte bu çok daha ilginç. Ona soracağımız ilk şey de bu olacak. Tabii hâlâ hayattaysa ve onu bulabilirsek. Bir şey kesin – filoya asla geri dönmedi. Böyle bir riski göze alması için hiçbir sebebi yoktu.";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "Babamın Joshua Casper adını almasına ne sebep olmuş olabilir? 'Cornwall' gemisinde, sonra 'Wrangler' olan o gemide ne yaşandı? Babam gerçekten bir suçlu olabilir mi, "+pchar.name+"?";
			link.l1 = "Ne yazık ki, bu ihtimali de göz ardı edemeyiz, "+npchar.name+". Her şeye hazırlıklı olmalıyız, tamam mı?";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "Bunu düşünmek bile istemiyorum...";
			link.l1 = "Şimdilik başka bir şeyi düşünmemiz lazım – onu nerede arayacağımızı. Korsanlara ya da kaçakçılara katılmış olabilir. Belki de bir kasabaya yerleşip sessiz sakin yaşıyordur. Her şey mümkün.";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "Peki, ne yapmamızı öneriyorsun? Onu nasıl bulacağız? Her koloniyi dolaşıp adını mı soralım, belki birisi Rupert Northwood'u duymuştur diye mi umut edelim?";
			link.l1 = "Ya da Joshua Casper. Eski kaptanının kimliğiyle yaşamaya devam edebilirdi—muhtemelen ölmüştü zaten. Ama bunun da bazı riskleri vardı, çünkü birileri kayıp brigantin peşine düşebilirdi. Özellikle de gemide Providence garnizonuna gönderilmek üzere bir sandık dolusu gümüş olduğu için.";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "Haklısın, tamam mı?";
			link.l1 = "Ve yine de, Azorlar yakınlarında kaybolduğu söylenen Rupert Northwood kimsenin ilgisini çekecek biri değil, değil mi? Ama yine de burada düşünmeye değer bir şeyler var.";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "Buna daha ne kadar zaman harcayacağız, "+pchar.name+"?! Her yerde, herhangi bir kolonide olabilir, tamam mı!";
			link.l1 = "Eğer hayatta kaldıysa tabii. Ama ben katılmıyorum. Akıcı İspanyolca konuştuğunu sanmıyorum, bu yüzden Küba ve Hispaniola ihtimal dışı. Biraz Fransızca biliyorsa, belki Tortuga'ya ya da Küçük Antiller'den birine gitmiş olabilir. Ya da Batı Anakarası'nda, başka İngilizlerin yanında kalmış olabilir. Onu bulmak için aylarca uğraşabiliriz ve yine de elimiz boş dönebiliriz.";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "Ama pes etmek istemiyorum, "+pchar.name+". Sadece şimdi değil, zaten bu kadar çok şey öğrenmişken, tamam mı!";
			link.l1 = "Pes etmemizi söylemiyorum, "+npchar.name+". Ama onu kendimiz aramak zorunda değiliz - doğru bağlantıları olan birine başvurabiliriz. Daha önce işe yaramıştı. Neden tekrar denemeyelim ki?";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "Yine başrahipten yardım mı isteyelim diyorsun? Bu konuda artık bize destek olmayacağını açıkça söylemişti, tamam mı.";
			link.l1 = "Bu yaşlı adama karşı biraz fazla küstahça olurdu, haklısın.";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "Ama o zaman kime gideceğiz? Böyle bir şey için parası ve bağlantıları olan kim var, tamam mı?";
			link.l1 = "Pekala, aramayı kesinlikle kendimiz finanse etmemiz gerekecek. Bağlantılar konusunda... Sanırım Fadey Moskovit bize yardımcı olabilir. Kolonilerde dolaştırabileceğimiz yetenekli insanları mutlaka tanıyordur. Ya da belki de bizi birilerine yönlendirir.";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "Yani, Basse-Terre'e mi gidiyoruz?";
			link.l1 = "Evet, hadi arkadaşımıza bir uğrayalım. Bana sorarsan, bu onun için pek de zor bir iş gibi görünmüyor.";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "Yarın demir alalım, ne dersin? Bugün ve bu geceyi seninle baş başa, sadece ikimiz, 'Ceres Smitty'de geçirmek istiyorum.";
			link.l1 = "Böyle bir teklife kimse hayır demez, canım. Küçük bir dinlenmeyi kesinlikle hak ettik.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "Ne, Adadan hemen mi gidiyorsun? Cenazede bile kalmayacak mısın?";
			link.l1 = "Cenaze mi?..";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "Ah, demek duymadın. Anladım... Orelie Bertine dün gece vefat etti.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "Ne?! Olamaz – daha dün onunla konuştuk, gayet iyiydi. Yoksa birisi...";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "Hayır, Mary. Orelie uykusunda öldü. Bugün onu görmeye gittim, eklemleri için Kardeş Julian'ın hazırladığı merhemlerden götürdüm – işte o zaman buldum onu. Yatağında yatıyordu, yüzünde garip bir gülümseme vardı. Ama çoktan solgun ve soğuktu.\nGeçen hafta, yaşlı kadın kendinde değildi, hatta kara büyücünün kovduğu hastalığın geri döndüğünü düşündüm. Ama zihni yeterince açıktı ve sayıklamıyor gibiydi.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "En azından acı çekmedi, tamam mı.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "Yani, cenazede kalacak mısın? Yarın olacak, en uzak resifte – orası yeterince derin, hem yengeçler de oraya kadar gitmez.";
			link.l1 = "Kalacağız, Jillian. Orelie Mary için o kadar çok şey yaptı ki, başka türlü davranamayız. Eğer kimsenin itirazı yoksa, töreni gemimizde yapacağız. Onu denize, tüm hak ettiği onurlarla defnedeceğiz.";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "Kimse itiraz etmeyecek. Daha pratik ve sonuçta, enkazın üzerinden tırmanmaktan daha güvenli.";
			link.l1 = "Cenaze işleriyle ilgilen o zaman – Mary sana yardım edecek. Benimse biriyle konuşmam gerek...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "Ve işte yine geldin, sevgili dostum! Bu sefer senin için ne yapabilirim?";
			link.l1 = "Merhaba, "+npchar.name+". Dün gece olanları duydun mu, di mi?";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "Orelie’nin ölümünden mi bahsediyorsun? Belli ki öyle. Tabii ki duydum. O ‘Pluto’da yaşıyordu, orası neredeyse tamamen Rivados’un bölgesi. Diğer gemilerdeki herkes de başka bir şey konuşamıyor zaten.";
			link.l1 = "Daha dün gördük onu, sağlığı yerindeydi—tabii, bütün hafta boyunca bir şey için endişeliydi. Gemimizi görünce ise iyice telaşlandı.";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "Bir insan, hayatının nehrinin kurumaya başladığını hissedebilir. Kimisi bunu çevresindekilere gösterir, kimisi içine saklar, ama herkes bir şekilde bunu anlar—özellikle de kalbinin sesini dinlemeyi bilenler.";
			link.l1 = "Bana sağlıklı gibi gelmişti, neredeyse genç bir ceylan gibi, "+npchar.name+". Ve burada bir şeyler hiç mantıklı gelmiyor...";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "Yine de, belli ki hâlâ son nefesini vermemişti, "+npchar.name+".";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "Arkadaşım, zihin ve beden tamamen farklı düzene ait şeylerdir. Zihin bedeni yönetir, bazen de beden zihni ele geçirmeye çalışır. Birbirlerine çok bağlıdırlar, ama aslında tam anlamıyla bir ve aynı değiller. Bir insan dışarıdan tamamen sağlıklı görünebilir, ama ruhu çoktan ölüm yolunda yürümeye başlamış olabilir.";
			link.l1 = "Sen akıllısın, dostum, hem de çok akıllı. Gerçeğin yakın olduğunu hissedersen, bir aslanın zebranın peşine düştüğü gibi onun peşinden gidersin – ve yakalayana kadar da durmazsın. Bunu seni ilk gördüğüm anda anladım.";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "Arkadaşım, zihin ve beden tamamen farklı düzene ait şeylerdir. Zihin bedeni yönetir, bazen de beden zihni ele geçirmeye çalışır. Birbirlerine çok bağlıdırlar, ama aslında tam anlamıyla bir ve aynı değiller. Bir insan dışarıdan tamamen sağlıklı görünebilir, ama ruhu çoktan ölüm yolunda yürümeye başlamış olabilir.";
			link.l1 = "Biliyor musun, Orelie’nin sanki bizi bekliyormuş gibi davrandığı aklıma geldi, sanki geleceğimizi biliyordu. Yaşlı kadın bir gün önce ya da sonra da ölebilirdi, ama tam da Mary’nin babasıyla ilgili önemli bir şeyi anlattıktan hemen sonra oldu bu."link.l1.go ="WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "Sen akıllısın, dostum, hem de çok akıllı. Gerçeğin yakın olduğunu hissedersen, bir aslanın zebranın peşine düşmesi gibi peşinden gidersin – ve yakalayana kadar da durmazsın. Bunu seni ilk gördüğüm anda anladım.";
			link.l1 = "Ben yapmadım... Bir saniye. 'Protector'un ambarında yaptığın o ritüel... Orelie'nin hastalığını yavaşlatmadı, değil mi? Peki, aslında ne yaptın?";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "Bir nehri taşlarla doldurabilirsin, ama bu onun akışını durdurmaz. Orelie’den senin için önemli bir şey gerektiğini biliyordum – ve ona hemen ulaşamayacağını da. Ama yolculuğunun ne kadar süreceğini kestiremiyordum. Bu yüzden bir baraj kurdum, tüm yaşam gücünü çağırarak hastalığı amacını yerine getirene kadar geri tuttum. Ve o an geldiğinde, engel çöktü...";
			link.l1 = " Yani, Orelie... ölüm anında, aslında kendinde değildi, bizim sandığımız gibi habersiz değil miydi? ";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "Tüm gücünü zihnini berrak, hafızasını canlı tutmak için harcadı ve artık buna gerek kalmadığında, hastalık büyük bir dalga gibi üstüne çöktü, onu ölümün vadisine sürükledi. Ölümü huzurlu muydu, yoksa geçmişin hayaletleri ve korkunç kabuslarla Tanrına mı gitti—bunu söyleyemem, çünkü bilmiyorum.";
			link.l1 = "Bunun nereye varacağını en başından biliyordun, tamam mı? Neden cezasının ne olacağını bana söylemedin, ha?! Söylesene!";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "Ne yaptığını gayet iyi biliyordun, "+npchar.name+" .  Neden bana bunun nereye varabileceğini söylemedin?";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "Sana yardım etmeye karar verdim, dostum, ihtiyacın olanı öğrenmen ve onun da kaderini yaşaması için. Eğer seni bekleyenleri söyleseydim, belki de vazgeçerdin—ve Orelie sırlarını mezara götürürdü. Bundan ne fayda çıkardı? Hiçbir şey için ölmüş olurdu. Aslan tarafından yere serilip yenmeyen, akbabaların insafına bırakılan bir antilop gibi.";
			link.l1 = "Amaca, faydaya... Kaderlerin ustasısın sen, "+npchar.name+". İnsan suretinde bir Tanrı.";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "Sana yardım etmeye karar verdim, dostum, ihtiyacın olanı öğrenmen ve onun kaderini yaşamasına izin vermen için. Eğer seni bekleyenleri söyleseydim, belki de vazgeçerdin—ve Orelie sırlarını mezara götürürdü. Bundan ne fayda çıkardı? Hiçbir anlamı olmazdı ölmesinin. Bir aslan tarafından yere serilip de yenmeyen, akbabaların insafına bırakılan bir antilop gibi.";
			link.l1 = "Amaca, faydaya bak... Kaderlerin ustasıymışsın, "+npchar.name+". İnsan suretinde bir Tanrı.";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "Sesinde bir hoşnutsuzluk duyuyorum, dostum. Ama hayır, kendimi asla bir tanrı olarak görmüyorum—ve inan bana, o bile her şeye kadir değil. Ne senin inandığın, ne de bizim taptıklarımız. Tanrılar bir insana doğuştan verilen gücün ötesinde bir güç veremez. Biz şamanlar ise o gücü sadece bir yöne ya da diğerine yönlendirebiliriz—hepsi bu.";
			link.l1 = "Ve sen onları öyle bir yola soktun ki, onun ölümüne sebep oldun...";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "Ben sadece Orelie'ye bir yol gösterdim, o da bu yolu izleyerek Mary'ye yardım etti — Mary doğduğu günden beri ona çok yakın olan birine. Sonuçta, yol arkadaşınız bu dünyaya onun gözleri önünde geldi. Lütfen bana aklını kaçırmışım gibi bakmayın. Herhalde beni, elini sallayarak zamanı geriye çevirebilen iyi niyetli bir büyücü olarak gördüğünüzü söylemezsiniz, değil mi?";
			link.l1 = "Sana ne söyleyeceğimi bilmiyorum, "+npchar.name+". Belki de gerçekten her şey boşuna değildi. Ama böyle olmamalıydı. Bana söylemeliydin, ben de seçimi yapmalıydım. Yine de, olan oldu. O zaman, elveda dostum.";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "Ah, son buluşmamızı böyle hayal etmemiştim, dostum...";
			link.l1 = "Sence onun sonuncusu olduğunu düşündüren ne?";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "Bazı nehirler diğerlerine karışır, onlara dahil olur, bazıları kurur, ve bazıları—bizimki gibi—büyük bir şelalede son bulur...";
			link.l1 = "Daha fazla bilmece mi, Chimiset? Bugünlük bu kadar yeter, sanırım. Eminim yine karşılaşacağız.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "Seni burada bulacağımı biliyordum, tamam mı? Chimiset'ten ne istedin, "+pchar.name+"? Sana ne söyledi?";
			link.l1 = "Tam olarak duymak istediğim şey değildi—ya da beklediğim. Ama içimde bir şüphe vardı zaten.";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "Bana söyleyeceksin, di mi?";
			link.l1 = "Hayır, "+npchar.name+". Bu sefer değil. Koruyucu’nun kamarasında söylenen her şey orada kalır, benimle Chimiset arasında, tamam mı?";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "Uzun zamandır sesinde böyle bir kararlılık duymamıştım, "+pchar.name+". Ama tamam mı, endişelenecek başka şeylerimiz var. Cenaze yarın, gün batımında, saat yedide olacak.";
			link.l1 = "Hadi, her şeyi hazırlamana yardım edeyim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "Görünüşe bakılırsa gelmek isteyen herkes burada, tamam mı.";
			link.l1 = "Daha çok insan olur sanmıştım. En azından birkaç huzurlu kişi olur diye düşünmüştüm.";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "Şey, Kurana ya da Rivados'u kimse davet etmedi. Abbott, o kendini beğenmiş, iğrenç hindi, Katolik bir kadını gömmekten daha önemli işleri olduğunu söyledi, Lauderdale ve Musket de benzer bir şeyler geveledi. Cassel, o kaba adam, ise doğrudan gelmeyeceğini söyledi. Ama diğer herkes burada.";
			link.l1 = "Bazı şeyleri asla anlayamayacağım, belli. Neyse, onların hesabını Tanrı'ya bırakalım. Ve işte Julian Kardeş geliyor... Şimdi her şey başlıyor.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;
		
		case "WildRose_funeral_1":
			dialog.text = "Yüreğimiz kederle dolu olsa da, Tanrı'ya Orelie'ye bahşettiği tüm nimetler için şükredelim ve şöyle diyelim: Sana şükürler olsun, Tanrım, Babamız\n"+"Tüm o yıllar ve günler boyunca Orelie bizimle kaldı ya\n"+"Kutsal vaftiz armağanı için, bu sayede Orelie Senin kızın oldu\n"+"Ona bahşettiğin hediyeler ve bilgi için\n"+"Ailesinin ve başkalarının iyiliği için yaptığı hizmetlerden dolayı\n"+"Bizim hatalarımıza karşı gösterdiği sabır için\n"+"Tanrı'ya dua edelim ki, aramızdan ayrılan kız kardeşimiz Orelie'yi yüceliğine kabul etsin, ve şöyle seslenelim: Sana yalvarıyoruz, Rabbim\n"+"Orelie’nin iyilikleri bol bol meyve versin\n"+"Başlattığı şey devam etsin\n"+"Yaptığı günahları ona bağışla\n"+"Onun anısı kalplerimizde yaşamaya devam etsin\n"+"Tanrı'ya dua edelim ki acı çekenlerin inancını ve umudunu güçlendirsin, ve O'na seslenelim: Rabbim, inancımızı artır\n"+"Oğlun aracılığıyla, insan olan\n"+"Oğlun İsa Mesih aracılığıyla, bizi her şeyden çok seven O'nun sayesinde\n"+"Oğlun aracılığıyla, günahlarımız için ölümü kabul eden ve kurtuluşumuz için yeniden dirilen\n"+"Oğlunuz aracılığıyla, bizim için cennetin yolunu açan\n"+"Bize kurtarıcımızın öğrettiği gibi, göksel yurda bizden önce giden tüm sadıklarla birlikte dua edelim.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;
		
		case "WildRose_funeral_2":
			dialog.text = "Yüce Tanrım, Dirilmiş Oğlun’a olan inançla sunduğumuz dualarımızı işit ve umudumuzu güçlendir ki, Senin aramızdan ayrılan kulunla birlikte biz de dirilişe kavuşalım. Rabbimiz İsa Mesih aracılığıyla, Senin Oğlun, Seninle ve Kutsal Ruh’un birliğinde yaşayan ve hükmeden Tanrı, sonsuzlara dek. Amin.";
			link.l1 = "God, Almighty Father, the mystery of the cross is our strength, and the Resurrection of Your Son is the foundation of our hope; free Your departed handmaid from the bonds of death and join her to the company of the saved. Through Christ our Lord. Amen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+", hadi hemen kamaraya gidelim, tamam mı. Az kalsın ağlayacağım... Kimsenin beni böyle görmesini istemiyorum.";
			link.l1 = "Tabii ki, "+npchar.name+". Hadi gidelim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "Birini gerçekten takdir etmeye ancak o gittikten sonra başlarsın – bunu hiç duydun mu, "+pchar.name+"?";
			link.l1 = "Evet, bir kereden fazla. .";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "Eric bunu sık sık söylerdi. Sanırım ailesini kastediyordu. Ona ailesi hakkında hiç sormadım—her zaman bunun için zamanımız olur diye düşünürdüm. Sonra öldü, tamam mı. Şimdi Orelie de gitti—ve ancak şimdi ona ne kadar az zaman ve ilgi gösterdiğimi fark ediyorum. Hak ettiğinden çok daha az.";
			link.l1 = "Hiçbir şey için kendini suçlama. Sevdiklerimizi ne zaman yanına alacağını asla bilemeyiz. Onlarla geçirdiğimiz zaman ise asla yetmez. Hiçbir zaman.";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "Belki öyledir, tamam mı? Eric de hep derdi ki – Orelie de ona katılırdı – bir yer her şeyden önce oradaki insanlardır. Ne evler, ne ağaçlar, ne de yollar – asıl insanlar. Haritada bir yeri düşündüğünde, aklına ilk gelen orada yaşayan insanlar olur. Ya da bir zamanlar yaşamış olanlar.";
			link.l1 = "Hiç gerçekten düşünmemiştim. Ama belki Eric haklıydı—sonuçta, eve adım attığında bir daha asla babanı ya da kardeşini göremeyeceksen, bir evin ne değeri kalır ki?";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = " Ben tam tersini savunurum. Mesela Paris’i düşündüğümde, aklıma sokakların görüntüsü, kokuları geliyor... Sadece birkaç kişi hafızamda kalmış, geri kalanlar neredeyse silinip gitmiş, oysa üzerinden sadece birkaç yıl geçti. ";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "Bence Eric ve Orelie Adadan konuştular, tamam mı? Bir de burada eskiden yaşayan insanlardan—çok, çok uzun zaman önce. Ben o zamanlar çocuktum ve hiçbir şey anlamıyordum, ama şimdi—her şeyi açıkça görüyorum. Sonuçta, Antonio, Cecille... ve Chimiset gibi birkaç Rivado benden daha uzun süredir buradalar—ama ben onlardan hiçbiriyle yakın olmadım. Geri kalanlara gelince: Eric, Orelie, Alan ve daha niceleri—hepsi öldü.";
			link.l1 = "Anladım. Dünya... biraz daha küçüldü, değil mi?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "Eric ve Orelie Adadan bahsetmişti, tamam mı? Bir de burada eskiden yaşayan insanlardan—çok, çok uzun zaman önce. Ben o zamanlar çocuktum ve hiçbir şey anlamıyordum, ama şimdi her şeyi çok net görüyorum. Sonuçta, Antonio, Cecille... ve Chimiset gibi bazı Rivadolar, benden daha uzun süredir buradalar—ama onlardan hiçbiriyle yakın değildim. Diğerlerine gelince: Eric, Orelie, Alan ve daha niceleri—hepsi gitti.";
			link.l1 = "Anladım. Dünya... biraz daha küçüldü, tamam mı?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Mary_215":
			dialog.text = "Artık daha çok boşalmış gibi. Bu dünya—dış halkasının içinde kalan kısmı. Şimdi bomboş, tamam mı? Ve yakında—tamamen yok olup gidebilir.";
			link.l1 = "Mary, ne diyorsun, tamam mı?.";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "Hiç hissetmedin mi, "+pchar.name+"? Az önce, Orelie'nin mezarının başında dururken.";
			link.l1 = "Ne tam olarak?";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "Nasıl açıklayacağımı bilmiyorum. Fırtınadan önce havanın nasıl koktuğunu bilirsin ya? Hatırlıyor musun—buraya ilk geldiğinde, her yerde bir gerginlik vardı... Herkes birbirinin boğazına sarılmaya hazırdı, çoğu barut ve kan kokusu aldığını söylüyordu. Chad’i öldürdükten sonra her şey değişti—nefes almak sanki daha kolaydı... Ama şimdi—o his yine geri geldi.";
			link.l1 = "Sanırım, ben de öyle bir şey hissettim. Ama belki de sadece ruh halimden kaynaklanıyordur? Sonuçta bir cenazede değil miyiz...";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "Çok yorulmuşsun, "+npchar.name+"   Biraz dinlen – her şey daha kolay gelecek. Ve gerçekten, bir cenazede kim kendini farklı hissedebilir ki, tamam mı?";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "Eric’i ve Adalet Adası’ndan başkalarını denize uğurladığımızda böyle değildi, inan bana. Bir tür... birlik vardı. Ama bugün—bazıları birbirine kurt gibi bakıyordu, oysa hepimiz aynı duayı ediyorduk.";
			link.l1 = "Leighton ve Donald'ı mı diyorsun?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "Eric’i ve Adalet Adası’ndan başkalarını denize uğurladığımızda böyle değildi, inan bana. Bir çeşit... birlik vardı. Ama bugün—bazıları birbirine kurt gibi bakıyordu, hepsi aynı duayı okurken bile.";
			link.l1 = "Leighton ve Donald'ı mı diyorsun?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "Demek sen de fark ettin, tamam mı.";
			link.l1 = "Greenspen matkaplara karışmaya kalkınca Dexter hemen geriliyor – ve kim onu suçlayabilir ki?";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "Bu iyi bitmeyecek, tamam mı.";
			link.l1 = "Eğer öyleyse, bugün sadece Orelie Bertine’in cenazesi değil, bu... Terkedilmiş Gemiler Şehri’nin de cenazesiydi.";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "Terkedilmiş Gemilerin Şehirleri?";
			link.l1 = "Beni affet Mary, ama bu yere Adalet Adası demeye elim varmıyor.";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "Artık dünyayı gördüm ve ne kadar büyük olduğunu anladım, burası... bir hapishane gibi geliyor, tamam mı? Burada büyüdüğüme inanmak zor.";
			link.l1 = "Ve bunca harap geminin arasında, senin gibi vahşi ve güzel bir gülün açabileceğine inanmakta zorlanıyorum.";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "Bu yere veda etmek istiyorum, "+pchar.name+"... Sanırım bir daha asla buraya dönmeyeceğiz, tamam mı. Ben istemiyorum. Burada neler olabileceğini kendi gözlerimle görmek istemiyorum.";
			link.l1 = "Eddie ve Donald'la konuşacağım. Belki onları biraz sakinleştirebilirim.";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "Anlamıyorsun... Bu sadece kaçınılmaz olanı geciktirir, bu yüzden çabana değmez. Bir gün geri döneceğiz – ve burada\nBöylesi en iyisi, "+pchar.name+", tamam mı... Artık burada beni tutan hiçbir şey yok.";
			link.l1 = "Dediğin gibi, sevgilim. Yapmamız gerekenleri bitireceğiz – sonra da buradan sonsuza dek gideceğiz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "Rupert Casper? Joshua Northwood?";
			link.l1 = "Bunu yol boyunca hep düşündüm, "+npchar.name+". Ve ben de şu sonuca vardım: Baban daha önce kullandığı bir isim ve soyadının arkasına saklanmazdı, tamam mı? Ama aynı zamanda, gerçek adını ya da soyadını bırakmaya da cesaret edememiş olabilir: ya yanlış bir anda sahte bir isme cevap veremezse, ne olurdu?";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "İstese kendine her ismi koyabilirdi, tamam mı?";
			link.l1 = "Tabii ki yapabilirdi. Belki de gerçekten öyle yaptı. Küba’da hayatta kaldıysa, ki oraya bir kaçakçı tartanıyla gelmiş. Eğer oraya ulaşabildiyse ve Adalet Adası’nın yengeçlerine yem olmadıysa… Şimdi yapabileceğimiz tek şey beklemek – en azından geçen seferki kadar uzun sürmeyecek. Sanırım bir ayı rahatça atlatırız.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "Babam hayatta, "+pchar.name+". Hep biliyordum, tamam mı!";
			link.l1 = "Tıpkı benim gibi, canım. Şimdi gidip şu Jerome'u görelim – ne kadar erken, o kadar iyi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "Sonunda başardık, tamam mı. Peki şimdi ne olacak, "+pchar.name+"?";
			link.l1 = "Jerome'u bulmamız lazım. Ya meyhanede bir odada pinekliyordur ya da bir ev kiralamıştır – eminim buna yetecek kadar parası vardır.";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "Fadey ona ne kadar para verdi düşününce... Bence kesinlikle ikinci seçeneği seçmiştir.";
			link.l1 = "Anlaştık. 'Cam Göz'ün sahibine onu sorabiliriz ya da kasaba halkına sorup soruşturabiliriz. Hadi gidelim, zaman değerli.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "Vay vay vay... Âşıklarımız burada. Tamam mı çocuklar, işi bitirelim ve ona haber verelim.";
			link.l1 = "Jerome Souvernier? Burada ne oluyor böyle?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "Ah, siz alçaklar, kh-kh. Neyse, tamam mı...";
				link.l1 = "Dilini tutmanı tavsiye ederim, canını düşünüyorsan... ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "O da var. Şimdi dökül bakalım: seni şeytana uydurup bize saldırmaya iten neydi – hem de Souvernier’yle birlikte, ha...";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "Senin Souvernier açgözlü, korkak bir herif. Casper ona güzel bir dayak çekip biraz para vaat edince, hemen uslu bir çocuk gibi o mektubu karaladı, hıh...";
			link.l1 = "Demek gerçekten bulmuş.";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "Seni buldum, seni buldum. Yani yakında öleceksin. Küçük sevgiline de aynı şey olacak. Casper ikinizi de lime lime edecek, heh-heh. Ben zaten ölmüş sayılırım, ama senin de sonunu getirmene yardım edeceğim. Keşke o ellerine düştüğünde merhamet dilenişini duyabilseydim...";
			link.l1 = "Tamam mı, bu dünyada fazla kalmayacağım, doğru. O yüzden çabuk konuş, son nefesimi vermeden önce.";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "Eğer onunla tanışmak istiyorsan, Chetumal Körfezi'ne git, orada yaşıyor. Onu aramana gerek yok, o seni kendi bulacak.";
			link.l1 = " Harika. Ölmek için acele etmene gerek yok, tamam mı? Bizim işimiz burada bitti.";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "Umarım öyle olur. Şimdi defol git.";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "Aman Tanrım, "+pchar.name+"... İnanamıyorum, gerçekten inanamıyorum, tamam mı! Bunu babam mı yaptı?!";
			link.l1 = "Öyle görünüyor, tamam mı? "+npchar.name+". Onu neyin harekete geçirdiğini ya da kim olduğunu hiç bilmiyorum, tamam mı... Ama başka bir Rupert Casper olduğuna da pek inanmıyorum. Böyle tesadüfler olmaz.";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "Şimdi ne yapmamız gerekiyor? Ona gözlerinin içine bakınca ne söylemem lazım, tamam mı?";
			link.l1 = "Önce ona ulaşmamız gerekiyor. Büyük ihtimalle, onu aramamız... böyle gergin bir tepkiye yol açtığına göre, kendini kanun kaçağı yapmıştır. Ama ne olursa olsun, o hâlâ senin baban. Ve onu bulmak için bir servet kadar emek, zaman ve para harcadık.";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "Ama ya bizimle konuşmazsa? Neden bizi öldürmemizi emretti?";
			link.l1 = "En azından, peşinde kimin olduğunu tam olarak bilmiyor olabilir. Fadey sadece adını vermiş, seninle ilgili ayrıntıları atlamış olabilir. Yoksa, şu anda kılıçlarımızı kana bulamamız gerekirdi diye düşünmüyorum.";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "Peki şimdi ne olacak? Chetumal Körfezi'ne mi gidiyoruz? Ama burada bize tuzak kurduysa... orada bizi ne bekliyor, kim bilir?";
			link.l1 = "Burada ne olduğunu öğrenmeden önce zaman avantajımız var. Bunu kullanalım. Koy’a yelken açacağız ve bizi desteklemesi için subaylardan birinin başında olduğu bir birliği karadan göndereceğiz.";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "Mantıklı geliyor, tamam mı? Ama bunu kim yönetecek?";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "Tichingitu. Kara savaşlarının gazisi. Ondan daha iyisi yoktur, kimse bu işi ondan iyi yapamaz.";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "Claude. Tabii ki pek hoşuna gitmeyecek, ama zamanla alışır.";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "Hercule. Bu işlerin nasıl yürüdüğünü çok iyi bilir.";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "Tommy. Bir şeyler ters gitse bile, o adam bir yolunu bulur, bana güven.";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "Longway. Düşmanını ormanda izlediği ilk seferi değil, tamam mı?";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "Alonso. Kılıcı hızlı çeker, aptal da değildir.";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "Tichingitu dikkatle dinliyor, kaptan "+pchar.name+".";
			link.l1 = "Arkadaşım, önünde önemli bir görev var. Bir grup katil Chetumal Körfezi'nde saklanıyor. Onları bulup ortadan kaldırmalısın. Gemimizle denizden yaklaşacağız.";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "Adamlarımızdan bir grupla ormanda ilerleyip o alçakların arkasına geçeceksin. Bana sormak istediğin bir şey var mı?";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "Hintlinin sorusu yok. Yarın öğlen grubumuz yerinde olacak ve orada pusuya yatıp bekleyecek.";
			link.l1 = "Pekala, Tichingitu. Sana bol şans.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = " Çağırdın mı, Kaptan? ";
			link.l1 = "Senin için bir işim var, Claude.";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "Savaşçılardan bir grup toplamamız ve onları ormandan geçirip Chetumal Körfezi’ne götürmemiz gerekiyor. Orada, Rupert Casper adında biri tarafından yönetilen bir çete bizi bekliyor. Bize kötü bir sürpriz hazırlamışlar. Ama asıl sürprizi biz yapacağız – daha doğrusu, sen yapacaksın. Benim işaretimle saldır. Sorusu olan var mı? ";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "Ormanda yürümekten nefret ediyorum. Ama derler ya, emir emirdir. Orada görüşürüz – sanırım yarın öğleye doğru. ";
			link.l1 = "İyi şanslar, Claude.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = " Dinliyorum, Kaptan. ";
			link.l1 = "Hercule, senin için bir iş var.";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "Birinin kalın kafasına birkaç kurşun sıkmak mı lazım? O iş bende, her zaman hazırım, biliyorsun bunu, tamam mı?";
			link.l1 = "Doğru tahmin ettin. Gemimizden bir grup savaşçıyı alıp ormandan geçerek Chetumal Körfezi’ne götürmen gerekiyor. Orada, bence bizi bekliyor olacak çeteye pusu kuracaksınız.";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "Zor bir şey düşündün sandım, Kaptan. Ama bu benim için bir meyhaneye gitmek gibi oldu. Yarın öğlene kadar orada olacağımızdan emin olabilirsin.";
			link.l1 = "Orada görüşürüz. Bol şans, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = " Ha, Kaptan, neden bu kadar ciddisin? Cenazeye mi gidiyorsun, ne? ";
			link.l1 = "Her zamanki gibi komiksin, değil mi Tommy? Sana da bir şaka: Bu ay maaş yok. Gelecek ay da yok. Neden bu kadar gerginsin?";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "Şaka bile yapamıyorum...";
			link.l1 = "Her şeyin bir zamanı var, Tommy. Öğrenecek çok şeyin var daha. Şimdi iyi dinle: ekibini topla ve ormandan geçip Chetumal Körfezi’ne git. Vardığında benim işaretimi bekle.";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "Ormanda yürüyerek mi gideceğiz? En erken yarın öğlene kadar oraya varamayız.";
			link.l1 = "Yani, yarın öğlen orada buluşacağız. Emir gelmeden harekete geçmeyin ve yerinizi terk etmeyin. Anlaşıldı mı? Anladığınıza göre. Şimdi, hadi işinize bakın.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "Uzun uzun dinliyorum, Kaptan.";
			link.l1 = "Selam, senin için bir işim var.";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "Adamlarımızdan oluşan bir ekibi ormandan geçirip Chetumal Körfezi’ne götüreceksin. Orada düşmanla karşılaşabilirsin, o yüzden herkesin hazır olduğundan emin ol.";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "Longway her şeyi anladı, endişelenmeye gerek yok, Kaptan. Yarın öğleye doğru varmış olacağız.";
			link.l1 = "Devam et, ama dikkatli ol.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "Beni mi çağırdın, Kaptan?";
			link.l1 = "Tamam mı? Dikkatle dinle, Alonso.";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "Bir grup savaşçıya liderlik edip ormandan geçerek Chetumal Körfezi’ne ulaşacaksın. Büyük ihtimalle orada bir grup alçak seni bekliyor olacak. Yerini alıp, ben işaret verdiğimde arkalarından saldırman gerekecek.";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "Çok kolay, Kaptan. Ama yarın öğleden önce körfeze yanaşma – ben ve tayfam oraya o kadar erken varamayız.";
			link.l1 = "Hazır ol, Alonso. Ve Tanrı yardımcımız olsun.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "Charles, bunu gördün mü?";
			link.l1 = "Bize çoktan pusu kurmuşlar gibi görünüyor. Eminim hemen şu köşede bekliyorlardır.";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "Hâlâ ayaktayız. Bize ateş etmeye bile çalışmıyorlar, tamam mı. ";
			link.l1 = "Belki hâlâ önce bizimle konuşmak ister. Onu kışkırtmayalım – oraya kendimiz gidelim, tayfamız arkamızda olacak. Hadi, buna bir son verelim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "Olduğun yerde kal! Bir adım daha atma! Çocuklar, o süslü adam kılını kıpırdatsa bile – delik deşik edin onu. Kıza dokunmayın.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "Baba?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			sld = CharacterFromID("Mary");
			if (CheckCharacterItem(sld, "hat11")) // У Мэри есть своя шляпа
			{
				dialog.text = " Veeell... Uzun ve zorlu hayatımda çok şey gördüm. Artık hiçbir şeyin beni şaşırtamayacağını düşündüğüm anda, hayat beni yine yanıltıyor. Demek gerçekten hayatta kaldın... Hem de Theresa’nın şapkasını bile saklamışsın. Onu bir daha göreceğimi hiç düşünmemiştim. ";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = " Veee... Uzun ve zorlu hayatımda çok şey gördüm. Artık hiçbir şey beni şaşırtamaz sanırken, hayat bana hep tersini gösteriyor. Demek gerçekten hayatta kaldın, Julia... ";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "Orelie bunu bana, o... vefat etmeden önce verdi.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_3":
			dialog.text = "Ne dokunaklı... Az kalsın ağlayacaktım. Ben de sandım ki Teresa'yı onunla birlikte gömdüler. Ona verdiğimden beri bir saniye bile yanından ayırmamıştı. Senin annen, sadece bir hizmetçi kız olmasına rağmen, içinde öyle bir macera ruhu vardı ki neredeyse kulaklarından taşıyordu. Fleur-de-Lys ele geçirilirken onu bulduğumda, hemen anladım ki Teresa buna bayılacak. O şapkayla komik görünüyordu ama hiç aldırmazdı: sadece uyurken çıkarırdı. Ama sen, Julia, sana gerçekten çok yakışıyor.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "Julia? Hayır, yanılıyorsun, benim adım Mary...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "Hmm, öyle mi. Demek o alçaklar sözümü dinlemeyip kendi bildiklerini okudular. Eh, o Katolik köpeklerden başka ne beklenirdi ki.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "Sen... Sen... Gerçekten benim babam mısın?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "Şey, öyle olmasaydı, sen ve arkadaşın şimdi çoktan kurşunlanmış halde yerde yatıyor olurdunuz. Uzun zamandır ne Tanrı'ya ne de Şeytan'a inanıyorum, ama belki de gerçekten vardırlar. İlki kesin—çünkü sana Teresa'nın güzelliğini vermiş. Ve bu da şu an hayatını kurtardı. Nasıl derler... Tanrı'nın işi belli olmaz, tamam mı? Ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "Baba... Ben... Ben anlamıyorum, tamam mı...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = " Tabii ki bilmiyorsun. Nasıl bilebilirdin ki...";
			link.l1 = "Kızınızı gördüğünüze pek sevinmiş gibi durmuyorsunuz Bay Casper. Özellikle de az önce onun sizin kızınız olduğunu kabul ettikten sonra.";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "Zekâdan yana eksiğin yok, süslü... Adın neydi tekrar?";
			link.l1 = ""+GetFullName(pchar)+"   Seni ararken, bütün bu zaman boyunca nasıl yaşadığını merak edip durduk. Hatta hayatta kalıp kalmadığını bile düşündük. Ama bakıyorum ki burada gayet iyi yerleşmişsin, Bay... Northwood.";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "Vay canına, bunu bile bulmuşsun. Eh, saygılarımı sunarım, Bay Kurbağa Yiyen, başka ne diyebilirim ki – sonuçta her şeyi sıkı sıkıya kapattığımdan emindim.";
			link.l1 = "Daha fazlası var. 'Cornwall'u ve onun yükünü biliyoruz, ayrıca bir süreliğine adını ödünç aldığın Joshua Casper'ı da, ve soyadını—görünüşe göre onu da temelli saklamışsın.";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "Bravo (alkışlar). Etkilendim. Her şeyi kendi başına mı çözdün, yoksa benim değerli çocuğum da sana yardım etti mi?";
			link.l1 = "Mary olmasaydı bunu başaramazdım. Anne babası hakkında her şeyi öğrenmeye kararlıydı. Theresa'ya ne olduğunu anlamak zor olmadı, ama seni bulmamız epey zaman aldı...";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "Hepsi o kadar dokunaklı ki, neredeyse gözlerim dolacak. Peki kızım, şimdi mutlu musun? Yetti mi? Babana bir sarılmak ister misin?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "Anlamıyorum, baba... Neden bana bunu yapıyorsun? Ne için?! (bağırır) Beni orada bırakan sendin—o batık gemilerin üstünde! Sonra da asla geri dönmeyi bile düşünmedin, tamam mı! Neden? Sen kimsin, ha, ve arkanda duran o insanlar kim?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "Söyle bana, "+pchar.lastname+", hep böyle mi huysuzluk yapar? Annesinden almış. Teresa harika bir kızdı, tanıdığım en iyisiydi. Ama öfkelendi mi, ortalığı ayağa kaldırırdı... Ne diyeyim... İrlandalı.";
			link.l1 = "Ona hakaret etmeye kalkışma sakın! Mary senin talihsizliklerinden sorumlu değil ve kesinlikle böyle muamele görmeyi hak etmiyor.";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "Beni susturmaya mı çalışıyorsun, ufaklık?!";
			link.l1 = "Aksine. Hikayeni anlatmanı istiyorum. Mary'nin bunu bilmesi çok önemli. Ama ona hakaret etmene izin vermem. O yüzden kendine hakim ol.";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "Bana kalbimi dökmek için can attığımı mı sanıyorsun? Hayatım böyle oldu, ve siz papazların dediği gibi—Tanrı şahidimdir—hiçbir şeyden pişman değilim. Sadece o zamanlar Teresa’yı kaybettiğime üzülüyorum—onun yüzünden. Senden nefret ediyor muyum, kızım? Belki bir zamanlar ediyordum, ama şimdi umurumda bile değilsin.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "You’re blaming me for Mama’s death?! How does that make any sense? What did I do - get born? Is that my crime? Fine, Father. +pchar.name+ is right - just tell us everything. After that, we’ll leave. You’ll never see my face again... if that’s what you want... (begins sobbing)";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "Ahhh, tıpkı Theresa gibi. Sanki yirmi yıl öncesine dönmüşüm, ha! Eh, neyse, senin istediğin gibi olsun. O anıları tekrar yaşamak hiç hoşuma gitmeyecek... Ama bu küçük hikayenin sonunda kafana bir kurşun sıkmak istersem, canım - kendini suçla.";
			link.l1 = "O zaman sen de kurşunu yersin, Rupert. Ve bunun senin planında olmadığını düşünüyorum – kendini seven birine benziyorsun.";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_20": //
			dialog.text = "Hayatımın neye değdiğini biliyorum, çocuk. Onu değerli bulmakla aynı şey değil bu. Ama sen bundan ne anlarsın ki? Peki, tamam, konuya gelelim. Tüm hikayeyi mi istiyorsun? Al bakalım. Ben Eastbourne yakınlarında bir çiftlikte doğdum – Kanal kıyısında küçük bir kasaba – 1611 yılında. Bir yıl aşağı bir yıl yukarı, kim bilir – annem tarihlere hiç kafa yormazdı, şaşırmam, içkiyi ne kadar yuvarladığını düşününce.";
			link.l1 = "Zor bir çocukluk mu geçirdin? Anladım.";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "Eğer sen istedin, o zaman dinle ve çeneni kapa, akıllılık yapma. Hiçbir zaman bir babam olmadı, nedenini de bilmiyordum—ama senin gibi değilim, küçük kız, ben bunu hiç umursamadım. Ondan aldığım soyadı bana gayet uygundu. On üç yaşındayken, bir gece Dunkirk korsanları kıyıya çıktı. Tamam mı, şimdi kimse bunu hatırlamak istemiyor ama o zaman sadece Hollandalılar değil, biz de—eski İngiltere'nin doğu kıyısında yaşayanlar da—onlardan çok çektik.";
			link.l1 = "Bunu duydum. O adamlar kimseyi sağ bırakmamış. Sen nasıl kurtuldun?";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "Onların geride bıraktığı dehşetleri biliyorum. Hiç kimseyi esirgemediler – ne yaşlıyı, ne genci. Senin hayatta kalman bu yüzden daha da inanılmaz, tamam mı?";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "O gece, o papaz domuzları birkaç çiftliği ateşe verdi, bizimkini de. Ben kaçmayı başardım ama annem, o kadar çok elma şarabı içmişti ki, şişman kıçını yataktan kaldıramadı, oracıkta yandı gitti. Tabii ki kendi suçu – ama yine de, sonuçta annemdi.";
			link.l1 = "Ve o zaman mı bütün papazlardan nefret etmeye başladın?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "O gece, o papaz domuzları birkaç çiftliği yaktı, bizimkini de. Ben kaçmayı başardım ama annem, o kadar çok elma şarabı içmişti ki, şişman kıçını yataktan kaldıramadı, oracıkta yandı gitti. Kendi suçu tabii – ama yine de annemdi.";
			link.l1 = "Ve o zaman mı tüm papazlardan nefret etmeye başladın?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "İşte o zaman açlıktan nefret etmeyi öğrendim, akıllı çocuk. Senin böyle bir şeyi gerçekten yaşadığını hiç sanmıyorum, ama ben yaşadım—kendi derimde hissettim. Kuzeye, başkente gittim ve donanmaya yazıldım—orada yemek yerine kırbaç daha çok dağıtılırdı, ama birkaç düzine darbe aklımı başıma getirmeye yetti. Sonrasında alıştım—ve denizde yaşamayı sevdim. Özellikle de, orada asla sıkıcı bir an olmadığı için...";
			link.l1 = "Buna inanabilirim. Kraliyet Donanması'nın ünü zaten her şeyi anlatıyor.";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "1633 yılında teğmenlik sınavını geçtim ve Cornwall adlı brigantine atandım.";
			link.l1 = "Joshua Casper'ın komutası altında.";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "Ah, evet... Joshua Casper... Bütün lanet filoda ondan daha büyük bir alçak bulamazsın. Yıllar geçti, ama o domuz hâlâ rüyalarımda peşimi bırakmıyor.";
			link.l1 = "Ne yaptı peki? Fazla istekli olduğun için seni fazladan nöbete mi koydu? Yoksa gizlice papist miydi?";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "O zalim herif mürettebatı öyle bir çalıştırırdı ki, insanlar yorgunluktan denize düşerdi. Onun adını ve 'Cornwall'un komutanı olduğunu bildiğine göre, belgelerini de görmüşsündür—kedi diliyle parlatılmış gibi pırıl pırıl.   Bizim kahraman Joshua'nın madalyalarla dolu koca bir kutusu vardı. Senin gibi saf delikanlılar onun emrinde hizmet etmek isterdi—ne dersen de, ama o Fransızları öyle bir biçerdi ki, yağmurdan sonraki ıslak çimenleri biçen keskin orak gibi, tamam mı—ama bir kere 'Cornwall'a adım attılar mı, hatalarını hemen anlarlardı.   Biz artık buna katlanmaktan öylesine yorulmuştuk ki, "+pchar.lastname+". Bazıları nakil için dilekçeler bile yazdı – ama bunlar Amirallik’in raflarında ya da fırınlarında kayboldu. Yine de hayat bize bir şans verdi – bizi 'Cornwall'dan almadılar, ama başkasını oraya getirdiler. John Lawson – Cromwell’in gözdesi, mutlaka duymuşsundur.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "O zamanlar da yalakalık yapmayı iyi bilirdi — belki o ve Casper iyi anlaşırdı, ama buna izin vermedim. Küçük Johnny’e tuzak kurdum, Joshua ise tüm hikayeyi bilmeden öfkesine kapılıp bastonuyla onu dövdü.";
			link.l1 = "Bir subay için tam bir küçük düşürülme. Ve Lawson babasına her şeyi anlattı mı?";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "Tabii ki yaptı – bu benim planımdı. Ama bak, sistem kendini yiyemez. Her şey örtbas edildi – Lawson'a erken terfi teklif edildi, Joshua ve 'Cornwall' ise gölgede bırakıldı – Londra'dan İngiltere'nin güneyindeki Plymouth'a tayin edildik. Sizi, kurbağa yiyicileri, korkutmaya devam edebilirdik ama 'Cornwall' bir ikmal gemisine dönüştürüldü, askeri malzeme taşıyarak İrlanda'nın küçük kasabası Dundalk'a gidip geliyordu.";
			link.l1 = "Ve Teresa'yla orada mı tanıştın?";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "İlk kez oraya demir attık. Theresa O’Fatt - yerel meyhanede çalışıyordu, barmaid’di. Birbirimiz için yaratıldığımızı anlamamız üç gün sürdü. Sanırım sen de ne demek istediğimi anlıyorsun, "+pchar.lastname+", değil mi?";
			link.l1 = "Sanırım öyle.";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "Sana şimdi bakınca, 'aşk' kelimesinin anlamını bildiğin aklıma gelmezdi.";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "Hayatımda ondan daha harika birini hiç tanımadım – ne öncesinde, ne de geçen yirmi yıl boyunca. İlk kez gerçekten mutlu hissettim, o da öyle – ya da en azından öyle söyledi.";
			link.l1 = "Ve ona seninle gitmesini mi teklif ettin?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "Hayatımda ondan daha harika birini hiç tanımadım – ne öncesinde, ne de geçen yirmi yıl boyunca. İlk kez gerçekten mutlu hissettim, o da öyleydi – ya da en azından öyle söyledi.";
			link.l1 = "Ve ona seninle gitmesini mi teklif ettin?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "Tabii ki hayır – bu imkansızdı, çünkü 'Cornwall' hâlâ bir savaş gemisiydi ve kaptanı da alçağın tekiydi. Sonsuz gibi gelen bir haftadan sonra, brigimiz Plymouth'a geri yelken açtı. İki ay sonra Dundalk'a döndük – ve Teresa beni şok eden haberi verdi: hamileydi.";
			link.l1 = "Evet, bir kızla yattığında genelde böyle olur, tamam mı?";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "Akıllılık yapma, velet. Teresa omzumda hıçkıra hıçkıra ağlıyordu, ben de ne yapacağımı düşünüyordum. Onun yanında kalmak istedim, gerçekten istedim – ama o zaman bile, o çocuktan iyi bir şey çıkmayacak gibi hissediyordum.\nTeresa’yı, hâlâ vakit varken o çocuktan kurtulmaya ikna etmeye çalıştım – ama bunun yerine, daha da şiddetli bir histeri nöbetiyle karşılaştım. O anda ne yapacağımızı bilemedik – bu yüzden iki ay daha beklemeye karar verdik, ‘Cornwall’ bir dahaki sefere Dundalk’a dönene kadar, çünkü o sırada Amirallik hâlâ Casper’a olan öfkesini merhamete çevirmemişti.\nDönüşümüzde onu hemen bulamadım — Theresa’nın hamileliği artık iyice belli olmuştu ve çalıştığı meyhanenin sahibi bana, o piç babasının onu dövüp eve kapattığını söyledi. Söylemeye gerek yok, o herifle öyle bir ilgilendim ki neredeyse bağırsaklarını kusacaktı. Tabii ki, onun o evde yaşamaya devam etmesi artık söz konusu bile olamazdı.";
			link.l1 = "Ve onu 'Cornwall'a mı getirdin?";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "Hızlıca bir karar vermem gerekiyordu. Casper’ın gemide bir kadına asla tahammül etmeyeceğini biliyordum, bu yüzden yola çıktıktan sonraki gece bir kayık çalıp sancak tarafımızda kalacak Dublin’e gitmeyi planladım.";
			link.l1 = "Peki sonra ne oldu? Seni yakaladılar mı?";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "Aynen öyle. Casper zaten kendine bolca viski koymuştu, bu yüzden hiçbir yalvarışa kulak asmadan kızı denize atmalarını emretti. Ne kadar yalvardıysam da, sadece nefessiz kalana kadar güldü—kahretsin, sana anlatırken bile hâlâ o kahkahayı kafamda duyuyorum...";
			link.l1 = "Ve işte o zaman isyan çıkarmaya karar verdin, di mi?";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "Başka çarem yoktu. Yakındaki bir nöbetçinin kemerinden bir tabanca kaptım ve o alçağın alnında bir delik açtım. Gemide hemen bir katliam başladı — kimse kaptanı sevmezdi ama mahkeme korkusu daha baskındı. Mürettebatın neredeyse üçte birinin canına mal oldu — sonunda kendimize geldiğimizde, 'Cornwall'un güvertesi baştan sona kana bulanmış ve ölü arkadaşlarımızın cesetleriyle doluydu.";
			link.l1 = " Ondan sonra, sanırım İngiltere'ye dönmek söz konusu bile olamazdı. Hepiniz orada darağacına gönderilirdiniz.";
			link.l1.go = "WildRose_Rupert_40";
		break;
		
		case "WildRose_Rupert_40":
			dialog.text = "Okyanusu ‘Cornwell’ ile aşabileceğimden emindim. Burada yüzlerimiz kimseye tanıdık değildi, bu da bize yeni bir hayat kurma şansı veriyordu. Diğer subayları ikna etmek pek zor olmadı — bunda otoritemden çok, tayfanın haberi olmadığı birkaç sandığın içindekiler etkili oldu. Mürettebat kararını verdi — Joshua Casper hayatta kalacaktı. Biz, dağlardan gelen subaylar, kendimize biraz zaman kazandırmaya, sandıklardan birini feda etmeye ve Antigua’ya uğrayıp orada onun adını almaya karar verdik. Sonrasında ise rotamızı Providence’a çevirecektik.\n Tam da öyle oldu: kimse değiş tokuştan şüphelenmedi, ama Providence’a sadece birkaç gün kala, bir alçak ikinci sandıktan bahsetti — ve bu da mürettebat arasında bir bölünmeye yol açtı.";
			link.l1 = "Yani şimdi sana karşı isyan mı ettiler?";
			link.l1.go = "WildRose_Rupert_45";
		break;

		case "WildRose_Rupert_45":
			dialog.text = "Hayır, ama görkemli kralımıza hizmet etmeye istekli adamların sayısı hızla azaldı. Korsan olmaya hevesli olanlar da pek fazla değildi. Biz de bir orta yol bulduk - bir Fransız limanına demir atıp gemiyi sattık, satıştan ve sandıktan gelen parayı paylaştık, sonra da herkes kendi yoluna gitti.";
			link.l1 = "Ve o kadar nefret ettiğin Katoliklerin arasında yaşamak zorunda kalacağını umursamadın mı?";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "O noktada, nereye vardığımız umurumda değildi. Teresa - güçlü görünmeye çalıştı, ama üç ay boyunca sürekli sallandıktan sonra, o da hamile bir kadının olacağı gibiydi. Ve üç ay önce olduğu gibi, etrafım Katoliklerle çevrili olsa da umurumda değildi, yeter ki onun yanında olayım.";
			link.l1 = "Ama Karayip Denizi'nin kuzeybatısında Fransız yerleşimleri yok, hiç olmadı da.";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = " 'Cornwall' gemisinde işler iyice kızıştığında, rüzgarın da yardımıyla yolun yarısını çoktan almıştık ve artık rotamızı St. Christopher'a çevirmemiz mümkün değildi...";
			link.l1 = "Ve varış noktası olarak Tortuga'yı mı seçtin?";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "O zamanlar, burası sadece basit bir köydü. Yetkililerin olası takibini geciktirmek için, kıçtaki isim levhasını değiştirdik—böylece 'Cornwall', 'Wrangler' oldu.";
			link.l1 = "Ama nedense, Kaplumbağa Adası'na hiç varamadın. Rotadan öyle bir sapmış olamazsın ki, Tortuga yerine Küba'nın batısına düşmüşsün, değil mi?";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "Sana söyleyeyim, ben deneyimli bir dümenciyim—çoğundan iyiyim. Hiçbir hata yoktu, dümdüz kuzeye gidiyorduk. Ama Windward Geçidi’ne girer girmez korkunç bir fırtına bastırdı. Hâlâ düşünüyorum, nasıl oldu da Küba kıyılarına çarpıp parçalanmadık da, o kıyı boyunca sürüklendik...";
			link.l1 = "Gerçek bir mucize, bundan daha azı değil.";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "Ağlayan Teresa'yı sıkıca kucaklarken, bütün kalbimle Rabbime dua ettim, bize kurtuluş göndermesi için yalvardım. Ve gerçekten de bize yardım etti.";
			link.l1 = "Adalet Adası'na vurulmuşsun.";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "Adalet – ah evet! 'Wrangler' kayalığa çarptığında ikiye ayrıldı, ama bir şekilde su üstünde kalmayı başardı – tam da o diğer enkazların yığıldığı yere sürüklenebilecek kadar. Fırtına neredeyse iki gün daha sürdü, sonunda dindiğinde – o zavallı küçük adadan gelen insanlar bizi kurtardı.";
			link.l1 = "Sen, Teresa ve iki denizci daha. Sonrasında neler olduğunu az çok biliyoruz. Bize asıl hapishaneden nasıl çıktığını ve adadan nasıl ayrıldığını anlat.";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "Keşke o zaman beni vursalardı... Başımda neyin beklediğini bilseydim, kendimi o parmaklıklara zincirler, bir santim bile kıpırdamazdım.";
			link.l1 = "Tartanda gerçekten brigde olduğundan daha mı rahatsızdı, tamam mı? "+npchar.name+"?";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "Sakın bana bir tartanede fırtınaya yakalandığını söyleme, tamam mı?";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "Tartana mı? Ha-ha-ha... Evet, planım buydu. Şansım yaver gitti sandım. Hapishane başgardiyanı, meğerse eski bir İngiliz Donanması subayıymış ve bana acıdı. Kübalı kaçakçıların tartanalarını anlattı bana, bir de beni idam etmeye karar verdiklerini söyledi. Sanırım ona onurlu bir adam diyebilirsin—bana kaçmamı teklif eden de oydu, böylece kaderimi şansa bırakabilirdim.";
			link.l1 = "Anlamıyorum... Eğer tartanlarla değilse, o zaman adadan nasıl ayrıldın?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_64_2":
			dialog.text = "Tartana mı? Ha-ha-ha... Evet, planım buydu. Şansım yaver gitti sandım. Hapishane başgardiyanı, meğer İngiliz Donanması'ndan eski bir subaymış, halime acıdı. Kübalı kaçakçıların tartanalarını ve beni idam etmeye hazırlandıklarını bana o söyledi. Belki ona onurlu bir adam diyebilirsin—kendi elleriyle kaçmamı teklif etti, böylece kaderimi şansa bırakabilirdim.";
			link.l1 = "Anlamıyorum... Eğer tartanlarla değilse, o zaman adadan nasıl ayrıldın?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "Eğer bir susup dinlersen, anlarsın. Tartanelere doğru yüzüyordum, uzun süre yüzdüm—ta ki yağmur duvarının ötesinde bir ışık görene kadar. Bu kesinlikle inanılmaz bir şeydi, kahretsin. Yarı batık kadırgalardan birinin güvertesinde güneş gibi parlıyordu ve ben de doğruca ona yöneldim. Henüz hayatımın en büyük hatasını yaptığımı bilmiyordum. Suyla gemiye çıkan merdivenden tırmandım—ve kendimi ışıkla burun buruna buldum. Altın bir heykelin üzerinde parlıyordu ve...";
			link.l1 = "Kukulkan'ın putu. Evet, o zamanlar 'San Jeronimo' henüz batmamıştı...";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "Demek sen de onu gördün, "+pchar.lastname+"?";
			link.l1 = "Sadece görmedim. Onun yardımıyla uzayda yolculuk ettim, hem de bir kereden fazla, tamam mı.";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "Yalan söylüyorsun! Birkaç kez mi, diyorsun?! O zaman nasıl olur da burada, böylesine canlı durabiliyorsun?!";
			link.l1 = "Taşındıktan sonra, bir Hint iksiri içtim, işte o sayede hayatta kaldım ve gücümü geri kazandım.";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "Ah, demek öyle. Gücümü geri kazanmak için ne kadar uğraştığımı biliyor musun? Biliyor musun, ha?!";
			link.l1 = "Sanırım tahmin edebilirim. İdole dokundun ve seni Dominika'ya gönderdi – o Kızılderili köyüne, orada seni heykele kurban ettiler, sonra da ana karada buldun kendini, değil mi?";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "Aynen öyle. O heykelin yanında yatarken hissettiğim acıyı hayatımda hiç yaşamadım, tamam mı? Ne ile kıyaslayacağımı bile bilmiyorum. Belki üstüne taş bir ev çökerse—yine de o kadar acı çekmezsin. Kendime gelir gelmez, bir grup yerlinin tekrar üstüme geldiğini gördüm. Dillerini konuşabilseydim—yemin ederim, oracıkta beni öldürmeleri için yalvarırdım.";
			link.l1 = "Bunlar yakındaki köyden Miskito yerlileri miydi?";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "Onlardı. Beni kulübelerden birine sürüklediler, orada diğerlerine benzemeyen tuhaf bir yerliden biri ağzıma bir şey döktü. Acı biraz hafifledi ama tamamen geçmedi. Akşama doğru beni ateşin yanına çıkardılar, o boyalı pislik bir tür ayin yapmaya başladı. Zavallı herif.";
			link.l1 = "Yılan Göz... Derini kurtardığı için ona minnettar olmalıydın.";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "Kurtarılmak mı?.. Üç yıl, "+pchar.lastname+"Üç yıl boyunca neredeyse hiç kıpırdamadan yattım, altıma yaptım, üstüme kustum – çünkü bana zorla içirdikleri o berbat kokulu iksirleri ve şurupları bir türlü midem kaldırmıyordu! Sonra da neredeyse bir yıl boyunca yeniden yürümeyi öğrenmekle geçti.";
			link.l1 = "Yürek burkan bir hikaye. Ama dürüst olmak gerekirse, sana neredeyse acıyacağım, tamam mı?";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "Acını al da git, Papa'nın o şişko Katolik kıçına sok. Kimsenin acımasına ihtiyacım yok. Devam edeyim mi, yoksa biraz ağlamak ister misin, küçük tavus kuşu?";
			link.l1 = "Bu yolculuk kesinlikle görgülerini geliştirmemiş. Ama tamam mı, Mary'nin hatırı için katlanacağım. Gerçi asıl meseleyi zaten öğrendik sanırım—yine de, sonuna kadar seni dinleyelim bakalım.";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "Bir şekilde tekrar ayağa kalkmayı başarıp o lanetli köyden ayrıldım ve kıyıya, Amatique Körfezi’ne doğru yol aldım. Orada, gemileri yakında demirlemiş olan bazı kaçakçılarla tanıştım ve onlara katıldım, kendime Rupert Casper dedim — adımı değiştirmek istemedim ama hayatımı mahvedenlerden birinin soyadını da bıraktım. Buraya neden geldiğimi asla unutmamak için.";
			link.l1 = " Herkes suçlu, sen hariç, Northwood... ama nedenini anlıyorum — yıllarca aşağılanma ve zorluk, şimdi de bu ormanda sıkışıp kaldın. Kim aklını yitirmezdi ki? ";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "Çok şey yaşadın, Northwood – bunda hiç şüphe yok. Ve şimdi bak neredesin... Ormanın içinde, medeniyetin sınırında. Burada aklını yitirmezsin...";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "Bu ormanların efendisiyim, "+pchar.lastname+" . On beş yılı aşkın sürede, kaçakçı bir gemide sefil bir denizciden onların liderine dönüştüm. Sadece küçük bir teknenin kaptanı değil, Amatique Körfezi'nden Ölüm Körfezi'ne kadar tüm kıyının efendisi oldum.";
			link.l1 = "Eh, bu bayağı bir cevap oldu, kabul ediyorum.";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "Bu ormanların efendisiyim, "+pchar.lastname+" . On beş yılı aşkın sürede, bir kaçakçı gemisinde mutsuz bir denizciden onların liderine dönüştüm. Sadece küçük bir teknenin kaptanı değil, Amatique Körfezi’nden Ölüm Körfezi’ne kadar tüm kıyının efendisi oldum.";
			link.l1 = "Doğrusu, bu bayağı sağlam bir cevap oldu, kabul ediyorum.";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "WildRose_Rupert_81":
			dialog.text = "Bazıları buranın Orman Şeytanı'nın bölgesi olduğunu söyler... Ne utanmazca bir yalan – buralar bana ait. Ve Svensson da bunu biliyor, ha-ha-ha. Adamlarını buraya defalarca gönderdi, kim olduğumu öğrenmeye çalıştı – ama hiçbiri ona geri dönmedi. Canlı olarak, heh-heh. Kaçakçılığa hangi isimle başladığımı ya da bu ormanda nerede yaşadığımı bilenleri bir elin parmaklarıyla sayabilirsin.";
			link.l1 = "Demek artık başka bir isimle dolaşıyorsun. O zaman Rupert Casper’ı arayan birini duyunca paniğe kapılmana şaşmamalı.";
			link.l1.go = "WildRose_Rupert_82";
		break;
		
		case "WildRose_Rupert_82":
			dialog.text = "Panik mi yapıyorum? Ciddi misin, çocuk? Burada panikleyen tek kişi sensin – benim bölgemde, benim insanlarımla çevrili, tamamen benim insafıma kalmışsın! Sana ne istersem yapabilirim. Ona da – sırf bütün o eziyeti yaşamama sebep olduğu için!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "Sen delisin, hem de düpedüz delisin, tamam mı? Sana çare olacak bir ilaç ya da doktor tanımıyorum, Rupert Northwood! Cehennemden geçmişsin, ama... nasıl olur da her şeyin suçunu bana yüklersin?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "Sana zaten söyledim – sen olmasaydın, bunların hiçbiri olmazdı. Kabul et işte, tamam mı?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "Bırak onu, "+npchar.name+". Yeterince duyduk. Bazı yolları sonuna kadar takip etmek gerçekten de doğru değil, tamam mı? Bütün bu işlere bulaşmaya karar verdiğimizde içimde kötü bir his vardı. Ama onu dinlemedim. Yazık.";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "Evet, o zaman ikiniz de burada, çaresiz ve hiçbir şey yapamaz halde olmazdınız. Şimdi sen de hisset bakalım, kızım, benim neler yaşadığımı!";
			link.l1 = "Ve sana kim dedi ki hiçbir şey yapamayız? Ta-a-a-akım, silah başına!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "Ne oldu, acemi? Birini mi kaybettin? Ha-ha-ha... Ha-ha-ha. HA-HA-HA-HA-HA-HA!!! Şu halini bir görmelisin, aptal! Hey Mason, misafirlerimize hediyemi getir bakalım.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "Piç herif! Benim adamlarım nerede?";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "Benim pusuya düşürebileceklerini sanan o avuç dolusu aptal mı diyorsun? Han sahibi dostum kasabaya geldiğini zamanında haber verdi, ben de onlara hak ettikleri karşılamayı yaptım... Birkaçı kaçmayı başardı. Ama merak etme – birini canlı yakaladım. Yani bugün seni neyin beklediğini kendi gözlerinle görebilirsin.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "Alçak! Bunun hesabını vereceksin! (ağlar) Yemin ederim, tamam mı!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "Alonso! Seni gördüğüme çok sevindim!";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "Ve ben de seni gördüğüme çok sevindim, Kaptan! Birisi o alçağa senin peşinde olduğunu haber vermiş — ve biz daha yolun yarısında misket yağmuruyla karşılandık. Bir avuç adamla geri çekilmeyi başardım ve hemen limana koştuk, seni uyarmak için. Neyse ki, nöbetçi beni kasabada alelacele satın aldığım barkta görünce hemen durumu anladı. Adamları çabucak topladı — ve buraya yardıma geldik.";
			link.l1 = "Teşekkür ederim, dostum. Bizi kesin bir ölümden kurtardın.";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "Bu bir şey değil. Şimdi ne yapıyoruz, Kaptan?";
			link.l1 = "Mürettebatı topla ve gemiye git. Mary ve ben biraz yalnız kalmak istiyoruz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "Aman Tanrım, "+pchar.name+"... Hâlâ inanamıyorum, gerçekten inanamıyorum. Babam... O bir canavar... Bana bunu neden yaptı ki? Gerçekten aklını mı yitirmiş?";
			link.l1 = "O korkunç acılara katlanmak zorunda kaldı. 'Cornwall'daki isyan, Atlantik'i aşarak kaçış, fırtına ve annenin ölümü. Comanche iksiri olmadan o putların kapılarından nasıl geçtiğini hayal bile edemiyorum – ama işte aklını mahveden de buydu.";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = "Ya peki ya o hep böyle miydi? Ya da belki de o da tam bir serseriydi, sadece biraz daha yumuşaktı ama annemi gerçekten seviyordu? Ya bütün bunlar onun içindekileri ortaya çıkardıysa? Ve eğer öyleyse... ya onun bir parçası bende de varsa? Olabilir, "+pchar.name+", tamam mı?";
			link.l1 = "Ondan kesinlikle bir şeyler kapmışsın, "+npchar.name+". Bugünkü kavgada fark ettim – sen de onun gibi kararlılıkla savaşıyorsun, gözlerinde aynı ateş, aynı öfke var. Ama onun deliliği sende yok. Sen bambaşkasın. Hayat dolu, açık, duygularını gizlemeyen birisin. İşte tam da bu yüzden sana aşık oldum. Ve galiba Northwood haklıymış: annenin ruhu tamamen sende, baştan sona.";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "Gerçekten öyle mi düşünüyorsun, sevgilim?";
			link.l1 = "Elbette, sevgilim. Onun kim olduğunu bilmeden öylece karşılaşsaydım, seninle akraba olduğunuzu asla tahmin edemezdim.";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "Biliyor musun, Adalet Adası’nda pek eğlence yok. Küçüklüğümden beri eskrimi çok severim—önce çocuklarla tahta sopalarla dövüşürdüm, sonra büyüyünce gerçek kılıçlarla, yetişkin adamlarla, tamam mı. Hep onlarla eşit olmak istedim... ama nedense, kazansam bile kendimi hep daha zayıf hissettim.   Sonra eve gidip daha çok çalışırdım. Saatlerce antrenman yapardım, ellerim titreyene kadar, tamam mı. Bahsettiğin o ateş bu mu? Sözünü ettiğin öfke bu mu?";
			link.l1 = "Bir bakıma – evet. Bence o ateş sende sandığından çok daha fazla güç var ediyor. İster hoşuna gitsin ister gitmesin, bu babandan sana kalan bir armağan. O sana hiçbir şey vermek istememiş olsa bile.";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "Sence geçmişi kurcalayarak doğru olanı mı yaptık, di mi?";
			link.l1 = "Artık her şeyi bildiğimize göre... bu o kadar da iyi bir fikir gibi gelmiyor. Ama gerçeği öğrenmek istiyorsan, hoşuna gitmeyecek bir şeyle karşılaşmaya da hazır olmalısın, tamam mı?";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "Haklısın, "+pchar.name+", tamam mı... Biraz daha burada kalalım. Şu an gemiye dönmek istemiyorum. Sadece... burada, sessizlikte oturmak istiyorum.";
			link.l1 = "Elbette, aşkım. Ben de tam aynı şeyi önerecektim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
		
		// Тичингиту
		case "WildRose_Tichingitu_Final_1":  
			dialog.text = npchar.name+", tam zamanında geldin, Kaptan "+pchar.name+".";
			link.l1 = "Sana güvenebileceğimi biliyordum, dostum. Teşekkür ederim — bunu senden daha iyi kimse yapamazdı.";
			link.l1.go = "WildRose_Tichingitu_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tichingitu_Final_2":
			dialog.text = "Orman "+npchar.name+"'ın evi. "+npchar.name+" ormanda savaşmaktan mutluyum. Orman güç verir "+npchar.name+".";
			link.l1 = "İşte tam da bu yüzden seni ekibin başına geçirdim. Ve işe yaradı — gördüğün gibi, bizi kucak açarak karşıladılar.";
			link.l1.go = "WildRose_Tichingitu_Final_3";
		break;

		case "WildRose_Tichingitu_Final_3":
			dialog.text = "Hangi Kaptan "+pchar.name+" bundan sonra ne yapmayı planlıyorsun?";
			link.l1 = "Mary ve ben biraz yalnız kalmalıyız. Yaralıları toplayıp gemiye götürün. Ölüleri de getirin — onları denize gömeceğiz. Ve, "+npchar.name+"... Alonso'ya söyle, Mary'nin babası burada, uygun Protestan usulüyle gömülmeli. Bunu sadece o ve sen bilmelisiniz. Başka hiç kimse — Mary bile değil. Zaten yeterince acı çekti, daha fazlasına gerek yok.";
			link.l1.go = "WildRose_Tichingitu_Final_4";
		break;

		case "WildRose_Tichingitu_Final_4":
			dialog.text = npchar.name+" Anladım, Kaptan "+pchar.name+". Tichingitu her şeyi yapacak.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Дюран
		case "WildRose_Duran_Final_1":   
			dialog.text = "Sıkı herifler... Ama onları alt ettik, ha-ha! Bırakalım burada çürüsünler de, bir daha bizimle uğraşmadan önce iki kere düşünsünler.";
			link.l1 = "Teşekkürler, "+npchar.name+", harika bir iş çıkardın. Seni arkamızı kollaman için göndermeseydim Mary'ye... ya da bana... ne olabileceğini düşünmek bile istemiyorum...";
			link.l1.go = "WildRose_Duran_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Duran_Final_2":
			dialog.text = "Ha, Kaptan, sen mutlaka bir yolunu bulurdun — seni tanıyorum. Liderlerinin elindeki o koca palayı gördün mü? Gözümü alamadım ondan. Eğer beğenmediysen, bana hediye edersen hiç alınmam, tamam mı?";
			link.l1 = "Hm... Göreceğiz, dostum, göreceğiz. Şimdilik, hayatta kalanları topla ve gemiye git. Düşenleri de gemiye getir — onları denize bırakacağız. Ve... o lider — Mary’nin babasıydı. Alonso’yu al ve burada bir yere, Protestan geleneğine uygun şekilde düzgünce göm. Mezarın yerini kimse bilmeyecek. Özellikle de Mary. Onun böyle bir acıya ihtiyacı yok.";
			link.l1.go = "WildRose_Duran_Final_3";
		break;

		case "WildRose_Duran_Final_3":
			dialog.text = "Yaparım, Kaptan. Bekle... Bir dakika... boşver. Gidiyorum.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Тонзаг
		case "WildRose_Tonzag_Final_1": 
			dialog.text = "Burada hava gerçekten lanet olası derecede sıcak, Kaptan. O herifler hak ettiklerini buldu. Biz ortaya çıkınca o ufaklığın suratının nasıl buruştuğunu gördün mü, di mi?";
			link.l1 = "Bunu kesinlikle beklemiyordu. Tıpkı Mary’yle benim onun bu kadar alçak olacağını beklemediğimiz gibi. Yine de, arkamızı kollamayı seçerken içgüdülerim beni yanıltmadı.";
			link.l1.go = "WildRose_Tonzag_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tonzag_Final_2":
			dialog.text = "Sen Karayipler’e yabancı değilsin, Kaptan. Buradaki pisliklere alışmışsındır artık, belayı da uzaktan koklamayı öğrenmişsindir. Şimdi ne yapıyoruz? Gemiye mi dönüyoruz?";
			link.l1 = "Yaralıları toplayın, ölüleri kaldırın ve herkesi gemiye alın. Kaybettiklerimizi denize teslim edeceğiz, gerçek denizciler gibi. Mary ve ben bir süre burada kalacağız — biraz yalnız kalmamız gerekiyor. Bir şey daha: Mary’nin babasını Protestan usulüyle gömün. Gerekirse Alonso’yu da yanınıza alın. Ama mezarın yerini kimse bilmesin. Özellikle Mary. Onun geçmişin hayaletleriyle yaşamasını istemiyorum.";
			link.l1.go = "WildRose_Tonzag_Final_3";
		break;

		case "WildRose_Tonzag_Final_3":
			dialog.text = "Haklısın. Sırf gözyaşı dökmek için buraya dönmesinin anlamı yok. Merak etme — bunu gerektiği gibi yapacağız ve yaşayan tek bir ruh bile bundan haberdar olmayacak.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Айронс
		case "WildRose_Irons_Final_1":
			dialog.text = "Kaptan, efendim, rapor veriyorum: pusu başarılı, alçaklar temizlendi, kaptan güvende.";
			link.l1 = "Şu an alay etmek için hiç uygun bir zaman değil, eğer komik olmaya çalışıyorsan — kötü fikir. Mürettebatın önünde güverteyi ovmak istemezsin, değil mi? Ah, onlar buna bayılırdı... Sana tavsiyem, bugün sabrımı sınama. Bugün değil.";
			link.l1.go = "WildRose_Irons_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Irons_Final_2":
			dialog.text = "Şey... yani, ben *gerçekten* bir subayım, ve...";
			link.l1 = "Şimdilik. Bugün subay — yarın tayfa, öbür gün ise dilenci.";
			link.l1.go = "WildRose_Irons_Final_3";
		break;

		case "WildRose_Irons_Final_3":
			dialog.text = "Anlaşıldı: "+GetFullName(pchar)+"   Kaptan Ciddiyet burada. Şaka yok artık. Emirleriniz nedir, efendim?";
			link.l1 = "Yaralıları toplayıp gemiye alın. Alonso’ya bir tayfa alıp adamlarımızın cesetlerini toplamasını söyleyin — onları denize bırakacağız. Ayrıca, Mary’nin babasını Protestan geleneklerine göre gömmesini isteyin. Mezarı sadece o ve ona yardım edenler bilmeli. Mary’nin bundan haberi olmasın. Onun geçmişin acısıyla üzülmesini istemiyorum.";
			link.l1.go = "WildRose_Irons_Final_4";
		break;

		case "WildRose_Irons_Final_4":
			dialog.text = "Tamam mı, tamam mı... Hallederim. Ve merak etme — ağzımı tutmayı bilirim.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Лонгвэй
		case "WildRose_Longway_Final_1":
			dialog.text = "Kaptan, efendim, başardık. Tek bir köpek bile kaçamadı.";
			link.l1 = "Aferin, "+npchar.name+", teşekkür ederim. Sana güvenebileceğimi biliyordum. Hayatta kalan herkesi topla ve gemiye dön. Mary ve ben biraz daha karada kalacağız.";
			link.l1.go = "WildRose_Longway_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Longway_Final_2":
			dialog.text = "Ölülerin bedenleriyle ne yapmalıyız?";
			link.l1 = "Onları denize teslim edeceğiz. Alonso'ya hazırlıkları yapmasını söyle. Bir de, Mary'nin babasını Protestan geleneklerine göre, burada, ormanın içinde, meraklı gözlerden uzak bir yere gömmesini iste. Mezarın yeri kimse tarafından bilinmemeli — özellikle de Mary tarafından. Onu tanıyorsan, buraya geri dönmek isteyecektir ve bu ona hiç iyi gelmez.";
			link.l1.go = "WildRose_Longway_Final_3";
		break;

		case "WildRose_Longway_Final_3":
			dialog.text = "Anlaşıldı. Başka bir şey var mı, efendim?";
			link.l1 = "Hepsi bu kadar, dostum. Git dinlen ve yaralarına iyi bak.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Алонсо
		case "WildRose_Alonso_Final_1":
			dialog.text = "Gerçekten kan gölüne döndü... İyi misin, Kaptan, tamam mı?";
			link.l1 = "İyiyim... sadece Mary'yle birlikte az önce babasını öldürmek zorunda kaldığımız gerçeği hariç...";
			link.l1.go = "WildRose_Alonso_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_Final_2":
			dialog.text = "Görünüşe bakılırsa, tam bir herifti...";
			link.l1 = "Doğru söyledin, "+npchar.name+". Yine de, düzgün bir cenaze törenini hak ediyor — Protestan usulüne göre. Bunu bizzat senin yapmanı istiyorum. Mezarın yeri kimse tarafından bilinmemeli. Özellikle Mary tarafından.";
			link.l1.go = "WildRose_Alonso_Final_3";
		break;

		case "WildRose_Alonso_Final_3":
			dialog.text = "Ona kötü anıları hatırlatmak istemiyor musun?";
			link.l1 = "Ve gereksiz acı. Herkesi gemiye gönderin, dinlensinler. Düşenleri de gemiye alın — Mary ve ben dönünce denize gömeriz. Şimdi, yalnız kalmamız gerek.";
			link.l1.go = "WildRose_Alonso_Final_4";
		break;

		case "WildRose_Alonso_Final_4":
			dialog.text = "Sana bulaşmamalarını çocuklara söyleyeceğim.";
			link.l1 = "Teşekkürler, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
	}
}
