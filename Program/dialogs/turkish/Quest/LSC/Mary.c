// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hayır, bir şey yok.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
		case "Cabin":
			dialog.text = "Marcello, onu tanıyorum. Rivados ve korsanların dostu. Adolf asla onunla iş birliği yapmazdı. Hey... barut kokusunu alıyor musun? Ve duvarda kan var... Adolf'u öldürmüş ve şimdi de bizi kandırmaya çalışıyor! Kesinlikle Amiral için çalışıyor! Onu öldür!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Cabin_fight");
		break;
		
		// на улице
		case "Town":
			dialog.text = "Ah, affedersin... bana yardım edebilir misin?";
			link.l1 = "Hm. Güzel bir hanıma yardım etmeye her zaman hazırım. Sorun nedir?";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "Bak, Sessile Gallard'dan bir sandık dolusu metal parçası aldım. O Eva'da yaşıyor. Jurgen bana güzel bir şey döveceğine söz verdi, di mi... Sandığı aldım, evet, ama ona götüremiyorum. Kahretsin!\nSandığı Eva'dan alıp Esmeralda'daki Narwhals bloğuna götürebilir misin? Lütfen, çok minnettar olurum!";
			link.l1 = "Ve hepsi bu mu? Tabii hanımefendi, size yardım edeceğim. Hiç sorun değil.";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "Teşekkür ederim! Sandığı sana göstereceğim.";
			link.l1 = "Hanımefendi...";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "Ve işte buradayız... Şimdi söyle bakalım, pislik, anahtar nerede?!";
			link.l1 = "Vay canına! Ha, galiba yardıma gerek yokmuş... Mary.";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "Akıllı geçinen, ha? Az konuş, kahretsin seni! Anahtar nerede? Ver onu bana, yoksa pişman olursun!";
			link.l1 = "Ne kabasın! Böyle güzel bir kıza ne kadar da sivri dilliymişsin. Hangi anahtar?";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "Adolf Barbier'den aldığın anahtar. İnkar etmeye çalışma, kamarasından çıkarken seni gördüler. Adolf öldü ve onu sen öldürdün... Şimdi, anahtarı ver bana!";
			link.l1 = "Demek sonunda sendin... Büyük bir hata yaptın kızım, hem de çok büyük bir hata!";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "Ne dedin sen...? Kahretsin, sen sıradan bir haydut değilsin! O Amiral için çalışıyor! Yere serin onu, çocuklar!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "Chad, bu o! Kahretsin, yardım getirmiş! Çocuklar, hepsini öldürün!";
			link.l1 = "...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			// Акулу к бою
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// устанавливаем 4 толстых нарвалов
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				if(i == 4) 
				{
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl*2);
					sld.DontClearDead = true;
					sld.SaveItemsForDead = true;
				}
				else FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// Мэри и Чада к бою
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------покушение на Акулу - вариант M --------------------------------
		case "mary":
			dialog.text = "Tam zamanında geldin... Onlarla asla tek başıma baş edemezdim... Off! Açıkçası, bittim sandım!";
			link.l1 = "Bir Valkyrie gibi savaştın! Hiç bu kadar güzel bir kızın böyle azimle dövüştüğünü görmemiştim...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Ha-ha, ne centilmenmişsin, kılıcın hâlâ elindeyken iltifat ediyorsun. Yardımın için sağ ol. Hayatımı kurtardın, di mi! Tanıştırsana kendini, centilmen, seni daha önce hiç görmedim. Yeni mi geldin buraya?";
			link.l1 = "Benim adım "+GetFullName(pchar)+", ama güzel kızlar bana böyle diyebilir "+pchar.name+". . Burada yeni miyim? Hm... Sanırım öyleyim.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Belli oluyor. Böyle yakışıklı bir adamı burada görseydim mutlaka fark ederdim. Ben Mary, Mary Casper. Ama burada herkes bana Kızıl Mary der. Çünkü kızılım, di mi?";
			link.l1 = "Seninle tanıştığıma memnun oldum, Mary...";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Oh, iki kere sevindim... çünkü sen olmasaydın şimdi ölmüş olurdum! O alçak Chad blöf yapmıyormuş. Tam bir sıçan! Alt kapıları açık bırakmakla aptallık ettim. Sen de öyle girdin içeri, di mi?";
			link.l1 = "Evet. Adanın etrafında yüzüyordum, karaya çıkacak bir yer arıyordum.";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Anladım. O açık kapı yüzünden az kalsın ölüyordum. Kilitleri bana Jurgen'in kendisi yaptı, doğru anahtar olmadan açamazsın, maymuncuk da işe yaramaz. Ayrıca, biri içeri girmeye çalışırken öylece duracak değilim — tabancamın dört namlusu ister kapıda ister birinin bedeninde dört delik açar, ha-ha! Ama şu lanet Chad peşimi bırakmıyor. Eğer beni kendi tarafına çekmek için haydutlar gönderdiyse, bu işi gerçekten ciddiye alıyor demektir. Sen olmasaydın, evet demek zorunda kalacaktım. Burada kuşatma altında kalmam gerekecek, "+pchar.name+", all right! Thank God I prepared for that; I have plenty of supplies and Jurgen is my neighbour, I've no quarrel with him.";
			link.l1 = "Mary, neden sorunlarını tam olarak anlatmıyorsun? Yardımıma ihtiyacın olduğunu görüyorum ama dudaklarından çıkan hiçbir şeyi anlayamadım.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Evet, yardıma ihtiyacım var, di mi? Şimdi yalnızım. Donald'la kavga ettim, sonra Chad'in de bir hain olduğu ortaya çıktı... Ah, özür dilerim, yine gevezelik ediyorum. Tamam, başıma gelenleri anlatayım sana...";
			link.l1 = "Unutma ki ben buraya yeni geldim, o yüzden pek bir şey anlamıyorum henüz. Bu Chad seni 'ikna etmeye' ya da öldürmeye çalışan kim? Peki ya Donald kim?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Chad, Amiral Shark Dodson'ın tayfasından bir korsan, Tartarus'ta bir gardiyan...";
			link.l1 = "Bekle! Shark Dodson mı dedin? O burada mı?!";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Sen bunu daha bilmiyorsan, kesin bu gece geldin buraya. Köpekbalığı başka nerede olurdu ki? Benim başım onun buraya birkaç ay önce gelmesiyle derde girdi. Gerçi, kabul ediyorum, bütün bunlar Narvallerin ve Rivadoların suçu. Köpekbalığı tayfasıyla buraya geldiğinde bir üs kurmak istedi, ama bizimkilerle Rivadolar bu fikri hiç sevmedi. Geceleyin Köpekbalığı'nın brigini bastık ve ateşe verdik. Kötü fikirdi! Köpekbalığı'nın tayfası adam değil, şeytan resmen, di mi? Önce teknelerimizi yok ettiler, sonra karaya çıkıp bizi doğramaya başladılar. Narvaller geri çekildi, Rivadolar ise canlarını kurtarmak için kaçtı. Sonunda korsanlar adanın erzaklarının çoğunun olduğu San Augustine'i ele geçirdiler, sonra da Tartarus'u aldılar. Köpekbalığı liderimizi, Alan Milrow'u - ki o aynı zamanda benim... benim çok değerli dostumdu - ve Rivadoların büyücüsü Chimiset'i tutsak etti. Onları Tartarus'un kafeslerinde hayvan gibi çürümeye gönderdi. Buradan Tartarus'a yüzmek kolay, ben de birkaç kez Alan'ı ziyaret etmeyi başardım. Orada Chad Kapper'la tanıştım. Köpekbalığı onu gardiyan yaptı. Chad'den Alan'ı salmasını istedim, para da teklif ettim, ama Amirale karşı gelmekten korktu. Sonra Alan hapiste öldürüldü. Chad bana bunu Köpekbalığı'nın yaptığını söyledi, di mi? Ben de Alan'ın yerine lider seçilen Donald'a gittim, korsanlara hemen saldırmasını istedim, ama o reddetti, o deniz şeytanlarının bize fazla güçlü olduğunu söyledi. Ben de ona kendi işine bakmasını söyledim. Benimkilerden hayır yoktu, ben de Köpekbalığı'nın yerine geçmek isteyen o pislik Kapper'la anlaştım. Bir planımız vardı - Amiral'i kalesinden çıkarıp tenha bir yere çekip öldürecektik. Ayrıca iyi tüfeği olan bir keskin nişancı bulduk. Fury'nin direğinden Amiral'i vurabilirdi. Şimdi asıl ilginç kısım: evvelsi gece Tartarus'a geceleyin gittim, Chad'e planımızla ilgili önemli bir şey söyleyecektim. Gemiye yüzdüm ve Chad'in iki Narvalle konuştuğunu duydum. Meğer Alan'ı Köpekbalığı öldürmemiş. Chad öldürmüş. Amiral'in suçlu olduğuna dair dedikodu yaymış. Chad Alan'ı benim yüzümden öldürmüş - önce beni yatağında oyuncak yapmak için, sonra da beni kullanıp Köpekbalığı'ndan kurtulmak için. Chad intikam almadan durmayacağımı biliyordu. Düşünebiliyor musun? Ne aşağılık herif!";
			link.l1 = "Evet, onun gibilerini gördüm...";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Orospu çocuğu daha da beter! O... Onu tarif edecek kelimem yok! Yüzüp uzaklaştıktan sonra, ertesi sabah onu buldum ve ona hakkındaki düşüncelerimi açıkça söyledim. Evet, Amiral'e karşı kurduğu plana asla karışmayacağımı da söyledim.";
			link.l1 = "Ve bundan hoşlanmadı tabii ki... Bu aceleciydi, Mary. Daha dikkatli olmalıydın.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "Biliyorum, ama dilimi tutamadım. O alçak Alan'ı öldürdü ve beni kendi çıkarları için kullanmaya kalktı! Pislik! Tabii ki sinirlendi ve pişman olacağımı söyledi. Ben de ona, taşaklarını kesip yengeçlere yedireceğimi söyledim!\nFikrimi değiştirmezsem adamlarını üstüme salmakla tehdit etti. Güldüm. Bir Narwhal’ın bana el kaldırmaya cesaret edeceğini hiç düşünmemiştim.";
			link.l1 = "Yanılmışsın gibi görünüyor.";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Aye, "+pchar.name+", I underestimated Chad and overestimated myself. He found cutthroats who'd stoop to attacking a lone girl in her own cabin. What do I do now? I can't trust anyone, not even trust my own people; these two we've killed are Narwhals. I knew both of them, all  right. As long as Chad is alive, I'm in danger. He'll send more men, no doubt.\nI'm scared to walk out the door; the sniper we found to assassinate Shark may shoot me from Rivados territory and slip away. I won't go to Donald - he won't listen.\nAnd the Admiral? 'Please, sir, I know I helped plan your assassination, but could you see your way through to forgiving me and saving me from my former mates?'\nHe'd send me to rot in the cells of Tartarus, if he didn't put a bullet in my brain. Fuck, I'm trapped! I'm going to sit here with my guns loaded until the food runs out and then... I don't know!";
			link.l1 = "Eh, o zaman sana yardım etmekten başka çarem yok, di mi? Zaten senin durumun da burada benim planlarıma uyuyor...";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "Bana yardım mı etmek istiyorsun? Ama nasıl? Chad'i öldürecek misin?";
			link.l1 = "Bu da planın bir parçası, tabii.";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Dinle, "+pchar.name+", Düşünceni takdir ediyorum ama bu iş sana göre değil. Chad, Amiral'in en yakın dostlarından biri ve ona ulaşsan bile oradan sağ çıkamazsın. Köpekbalığı'nın korsanları seni öldürür. Gerçeği bilmiyorlar, di mi?";
			link.l1 = "Sakin ol. Zaten Köpekbalığı ile konuşmam lazım.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Demek sen de korsansın, öyle mi?! En iyisi konuşmaya başla. Yakışıklı yakışıklı evime daldın, hayatımı kurtardın, yardım edeceğine söz verdin ama senin hakkında hiçbir şey bilmiyorum!";
			link.l1 = "Pekala... Korsan değilim, ama şu anda bir korsan baronu olan Jan Svenson'la çalışıyorum. Buraya Nathaniel Hawk'ı bulmak için geldim. Onu duydun mu?";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "Hayır, o da kim?";
			link.l1 = "Bir başka ünlü korsan daha. Onunla tanışmamış olmana üzüldüm, mutlaka buralarda bir yerde olmalı. Ben de Köpekbalığı'nı arıyordum ama onu burada bulacağımı hiç beklemiyordum.";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "Ama buraya nasıl geldin? Bir gemi kazasından kurtulan biri için fazlasıyla iyi görünüyorsun.";
			link.l1 = "Ve neden gemi kazası geçirdiğimi düşündün ki?";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "Buraya gelmenin tek yolu bu. Buraya kadar yelken açabilen tek kişi Köpekbalığı.";
			link.l1 = "Aslında, gördüğün gibi, Köpekbalığı 'tek' kişi değil.";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "Yani, bir gemin var mı? Harika!";
			link.l1 = "Çok heyecanlanma, Mary. Buraya... bir barkla geldim. Bir barkla geldim ama dibe battı.";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "A-ah... Şey, dediğim gibi: bir gemi kazası. Artık sen de bizimle burada mahsur kaldın, di mi?";
			link.l1 = "Mary, sana planımı anlatayım. Chad'in Shark'ı öldürmeyi planladığını söylemiştin. Shark'ın hayatta kalması gerekiyor. Ben ve Jan onu korsanların başı yapacağız. Bu yüzden onu uyarmam şart, çünkü anlattıklarından Chad'in sen yardım etsen de etmesen de bunu deneyeceğine eminim.";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "Muhtemelen öyle. Bunu yapacak adamları var...";
			link.l1 = "Bu, öncelikli amacımın Shark'ın güvenini kazanmak ve onu kurtarmak olduğu anlamına geliyor. Sonra da resmen Chad'e ulaşacağım. Onun suçlu olduğuna dair bir kanıtın var mı?";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "Onun mektubu bende, buraya şu yerde yatan... aptallardan biri getirdi. İçinde Amiralin ilgisini çekebilecek tehditler ve ayrıntılar var. Bekle! Peki ya ben? Shark, Chad'le birlikte çalıştığımı öğrenecek!";
			link.l1 = "Mary, burada tabancalarınla sonsuza kadar oturup o güzel yüzünü herkesten saklamaya mı niyetlisin? Gerçekten vicdanımda güzel bir kızın ölümüyle yaşamak istediğimi mi sanıyorsun? Önce mektubu göster, bakalım ne yapabilirim...";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "Al bakalım. Ne düşünüyorsun?";
			link.l1 = "Dur hele... (okuyor). Evet, Chad bu dünyayı istila eden o özel piçlerden biriymiş, öyle görünüyor. Bu mektup, Shark'ın Chad'in boynuna ilmeği kendi elleriyle geçirmek istemesi için fazlasıyla yeterli olacak. Merak etme, hanımefendi, Shark'ın senden asla şüphelenmemesini sağlayacağım. Zaten Chad'le uğraşmaktan başka bir şeye vakti kalmayacak.";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "Bunu gerçekten yapar mısın? Bana söz ver, di mi! Bana yemin et, beni asla yarı yolda bırakmayacaksın!";
			link.l1 = "Mary, sana yemin ederim, sana asla ihanet etmeyeceğim. Seni kurtardım çünkü ölmeni istemedim.\nChad peşini bırakmayacak, bu kesin. Çok fazla şey biliyorsun. O ölmeden burada kal.";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "Ben burada kalacağım. Bir keskin nişancı tarafından vurulmak ya da arkadan bıçaklanmak istemem.";
			link.l1 = "Aferin kızım. Bütün kapıları kapat, alt kattakiler dahil. Anahtar sadece sende mi?";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "Hayır. Bir tane daha var. İster misin?";
			link.l1 = "Evet.   Bana güveniyor musun?";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "Eh, hayatımı yeni kurtaran şu yakışıklı beyefendi bana ihanet ederse, yaşamanın pek bir anlamı kalmaz zaten... Al bakalım.";
			link.l1 = "Korkma, güzelim! Seni asla yüzüstü bırakmam. Şu işi halleder halletmez yanında olacağım. Umarım fazla sürmez.";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "Sorun yok, burayı birkaç hafta idare edebilirim.";
			link.l1 = "Harika. O zaman vakit kaybetmeyeceğim. Cesetleri dışarı çıkaracağım, sonra da Köpekbalığı ile konuşacağım. San Augustine'de, değil mi?";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "Evet, o her zaman orada. Ve buradan nasıl girdiysen öyle çık - Ceres’in üst güvertesine adım atmana izin vermem.";
			link.l1 = "Ve nedenmiş o?";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "Çünkü ölürsen bana yardım edemezsin. Burası Narwhal bölgesi ve seni yabancı olarak öldürürler.";
			link.l1 = "Hm... Anladım. Peki Mary, görüşürüz. Güvenli olur olmaz döneceğim.";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "Beni istediğin zaman görebilirsin, bunda bir sakınca yok. (kıkırdar)";
			link.l1 = "Hoşça kal, güzelim!";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;
		
		case "mary_wait":
			dialog.text = "Merhaba, "+pchar.name+", benim için iyi bir haber var mı? İyi misin?";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "Shark Dodson'la olan anlaşmazlığın çözüldü. Artık seni avlamakla ilgilenmiyor. Şu anda tek derdi Chad'in ihaneti.";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "Henüz değil, Mary. Ama elimden gelen her şeyi yapacağım.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = "Oh, Tanrıya şükür! Teşekkür ederim, bunu unutmayacağım, di mi! En azından Amiral için endişelenmeme gerek kalmadı. Peki ya Chad? Köpekbalığı ne yaptı?";
			link.l1 = "We convinced the Rivados to go after him. Layton Dexter removed the guards from the Tartarus and gave the gaol key to Black Eddie. The blacks freed their wizard Chimiset, but they failed to kill Chad; they got two of his Narwhal friends, but Chad ran away and is hiding somewhere.";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "Lanet olsun! Bu şimdi daha da dikkatli olmam gerektiği anlamına geliyor!";
			link.l1 = "Sakin ol, Mary. Eminim onun için sen değil, Shark daha önemli. Muhtemelen Rivados'u ona karşı kimin kışkırttığını biliyor. Shark'ı öldürmek için her şeyi yapar, seni değil.";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "Ona güvenme. Chad öyle kolay kolay vazgeçmez. Ah, ondan korkarak yaşamaktan o kadar yoruldum ki...";
			link.l1 = "Hm. Seni kolay kolay korkacak biri sanmazdım.";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "Ha! Düzgün bir kavgadan korkmam, ama öyle oturup öldürülmeyi beklemek mi? Ondan gerçekten çok korkarım "+pchar.name+", di mi!...";
			link.l1 = "Bana güven Mary: Kapper'ın Amiral'le başı zaten dertte. Şimdilik... Senin fikrine ihtiyacım var.";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "Benim tavsiyem mi? Ne tavsiyesi?";
			link.l1 = "Eddie, Chad'in yazdığı iki mektup buldu. Oku onları, belki neyin peşinde olduğunu anlarsın. Sonuçta Chad'le birlikte planı yapan sendin...";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Ver onları buraya... (okuyor). Axel, Esmeralda'daki tüccarımız, di mi? Chad ondan viski almak mı istemiş? Garip. Chad sadece rom içer, viski için de 'köylülerin içkisi' der...";
			link.l1 = "   Peki ya ikinci mektup?   ";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "'Marcello'? Marcello Cyclops, eski bir kraliyet avcısı. Bu kabinden çıkmayı reddetmemin sebebi o.";
			link.l1 = "O, tuttuğun keskin nişancı mı?";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "Evet. Bir gözü eksik olmasına rağmen, Marcello kırk adım öteden sineği vurabilir, di mi? Görevi, Santa Florentina'nın baş bodoslamasından ya da Fury'nin platformundan uzun menzilli stutzen'la Shark'ı vurmakmış...";
			link.l1 = "Yani hâlâ Chad'in Shark'ı öldürme planının bir parçası. Ama... Eva? Cecille? İçkiler?";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "Eva tarafsız bir gemi ve Cecille de Cecille Halard, gemide yaşayan eğlenceli yaşlı bir kadın. Kısa süre önce Santa Florentina'dan buraya taşındı. Orelie Bertine onun arkadaşı. Onlar, ben doğmadan önce Adalet Adası'ndaydılar, di mi?";
			link.l1 = "Hm. Saçmalık. İki koca adam, bir fıçı viskiyi birlikte içmek için yaşlı bir kadından mı saklanıyor? Saçma... Chad’in içki içmesi için tuhaf bir zaman ve yer.";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "Sana söylemiştim, o viski içmez, sadece rom içer... bir şeyler tutmuyor.";
			link.l1 = "Pekala, Cyclops'tan başlayalım. Onu nerede bulacağımızı biliyor musun?";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "Hayır. Çok içine kapanık biridir. Her gün dış halkada kuş avlar, kimse nerede uyuduğunu bilmez. Sık sık Rivados'u ziyaret eder.";
			link.l1 = "Çok fazla ipucu yok... Neyse, o zaman gidip Axel’le konuşayım. Belki o bir anlam çıkarır bundan. Görüşürüz Mary! Kapıyı kilitle!";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+", lütfen Chad'i hemen bul. Son saldırıdan beri hiç uyumadım.";
			link.l1 = "Sıkı tutun, sevgilim. Elimden gelenin en iyisini yapacağım.";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! O buraya nasıl geldi? Yoksa gelmek mi istedi--?";
			link.l1 = "Evet, seni öldürmek için, Mary. Jurgen'in kamarasından geçti ve buraya inmek için bir ip kullandı.";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "Ah! Ne aptalım! O yolu tamamen unuttum! Chad ona bundan bahsetmişti, di mi, eminim!";
			link.l1 = "Büyük ihtimalle. Zar zor başardım.";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "Ve ben uyuyordum. Bir saniyede beni öldürebilirdi... Ama onun buraya geldiğini nereden bildin?";
			link.l1 = "Ah... Benim de yöntemlerim var, Mary.";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "Yine beni kurtardın, yakışıklı. Her seferinde tam zamanında çıkıp geliyorsun, di mi? Bunu nasıl başarıyorsun?";
			link.l1 = "Eh, bilmiyorum. Birçok yeteneğimden biri olsa gerek. Kuşatman sona erdi – Chad Kapper öldü, arkadaşlarının hepsi de öyle. Cyclops ise o çürük tayfanın sonuncusuydu.";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "Gerçekten, "+pchar.name+"? Benimle dalga geçmiyorsun, di mi?";
			link.l1 = "Hiç de bile. Eh, şu son birkaç günden sonra biraz dinlenmeye ihtiyacım var...";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "Artık sonunda rahatça nefes alabiliyorum! Teşekkür ederim... sana minnettarım! Sen benim kahramanımsın, di mi?";
			link.l1 = "Bu kulağa harika geliyor - senin kahramanın olmak yani. Sonunda güvende olmana çok sevindim.";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "Ee?";
			link.l1 = "Ne oldu, güzelim?";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "Neden öylece duruyorsun? Buraya gelsene, centilmen.";
			link.l1 = "Ve ne yapacağız?";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "Buraya gel ve bana sarıl, beni öp. Bunu istediğini biliyorum, di mi?";
			link.l1 = "Mary...";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_Fade("LSC_MaryRomantic_1", "");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;
		
		case "happy_10":
			dialog.text = "Beni bırakma...";
			link.l1 = "Buradayım, Mary, sevgilim...";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "Her şey bekleyebilir. Amiral’in bekleyebilir, korsanların bekleyebilir – bu gece sadece ikimize ait, di mi?";
			link.l1 = "Evet.";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "Ve sonraki tüm geceler...";
			link.l1 = "Evet, Mary.";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Geri döndün... onsuz. Demek ki, o seni benden alamadı.";
				link.l1 = "Mary, şüphelerin yersizdi. Benim için tek kişi sensin. Hep düşüncelerimde ve rüyalarımda seninleydim.";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", neden Narwhal'larla savaşıyorsun? Ben onların topraklarında yaşıyorum – hatta onlardan biriyim, unuttuysan diye söylüyorum. Lütfen, Fazio'ya git ve barış yap, sana yalvarıyorum.";
				link.l1 = "Tamam, Mary, istediğin gibi yapacağım, di mi?";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашёл статую - прощается
			{
				dialog.text = ""+pchar.name+", bir şey seni rahatsız ediyor. Ne oldu?";
				link.l1 = "Mary, seninle konuşmam lazım.";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+"! Bütün Narwhal tayfası senden bahsediyor!";
				link.l1 = "Gerçekten mi, sevgilim?";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! Bu pala inanılmaz! Teşekkür ederim! Ben de sana bir hediye vermek istiyorum. Tabii ki seninkisiyle kıyaslanmaz ama yine de almanı istiyorum, di mi?";
				link.l1 = "Mary, senden gelen her hediyeyi saklardım... teşekkür ederim, sevgilim.";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Yoğun bir günüm var, "+pchar.name+"? İyi şanslar!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, bugün gidip Jurgen'i görmemiz lazım, di mi?";
					link.l3.go = "narval";
				}
				link.l1 = "Teşekkürler, Mary! Bundan hiç şüphem yok.";
				link.l1.go = "exit";
				link.l2 = "Bugün değil, Mary. Biraz dinlenmek istiyorum burada. Senin için sorun olmaz, di mi?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Peki, "+pchar.name+", nasılsın? Her zamanki gibi adada koşturuyor musun?";
				link.l1 = "Evet, Mary. Yapılacak çok şey var...";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = ""+pchar.name+",   akşam oldu bile, neyin lafını ediyorsun? Burada kal, biraz içip rahatlayalım, di mi? Her şey sabaha kadar bekleyebilir!";
				link.l1 = "(gülerek) Tabii ki aşkım, fazla söze gerek yok...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, bugün meyhaneye gidelim!";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "Mary, canım, şu anda çok meşgulüm. Birazdan döneceğim.";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Akşam beni ziyaret etmeyi unutma. Ve sakın benden kaçmaya kalkma, di mi?";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, bugün gidip Jurgen'i görmemiz lazım.";
					link.l3.go = "narval";
				}
				link.l1 = "Tabii ki, Mary, nasıl yapmam? Elbette seni ziyaret edeceğim.";
				link.l1.go = "exit";
				link.l2 = "Mary, bu gece burada kalmak istiyorum. Senin için de uygunsa, di mi?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "Ne diyorsun? Zaten gece oldu! Hiçbir yere gitmiyorsun, burada, benimle kalacaksın, di mi?";
			link.l1 = "(gülerek) Sen ne istersen, o olur tatlım...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "Sakın...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// сходить в таверну
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("Harika bir fikir, "+pchar.name+", di mi! Kabul ediyorum!","Tamam, gidelim, "+pchar.name+"! Sancho'nun harika bir şarap koleksiyonu var, seçilecek çok şey var!","Ah, çok memnun olurum, di mi? Sancho’nun meyhanesinde her zaman eğlence vardır, bir de harika şarapları var!");
			link.l1 = "Hadi gidelim!";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "Tabii ki, "+pchar.name+", ne kadar kalacaksın?";
			link.l1 = "Öğlene kadar kalacağım...";
			link.l1.go = "rest_day";
			link.l2 = "Akşama kadar kalacağım...";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "Tabii ki, "+pchar.name+", ne kadar kalacaksın?";
			link.l1 = "Akşama kadar kalacağım...";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых
		
	//--> если скоро уходит через портал
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Geri geldin... onsuz. Demek ki seni benden koparamadı!";
				link.l1 = "Mary, şüphelerin yersizdi. Benim için tek kişi sensin. Hep aklımda ve rüyalarımda seninleydim.";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", neden Narwhal'larla savaşıyorsun? Ben onların bölgesinde yaşıyorum – hatta onlardan biriyim, unuttuysan diye söylüyorum. Lütfen, Fazio'ya git ve barış yap, yalvarıyorum sana.";
				link.l1 = "Tamam, Mary, istediğin gibi yapacağım, di mi?";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! Bu pala inanılmaz! Teşekkür ederim! Ben de sana bir hediye vermek istiyorum. Tabii ki seninkiyle kıyaslanamaz ama yine de almanı istiyorum, di mi?";
				link.l1 = "Mary, senden gelen her hediyeyi saklarım... teşekkür ederim, sevgilim.";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Şimdiden gidiyor musun, "+pchar.name+"? İyi şanslar ve beni unutma, olur mu...";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, bugün gidip Jurgen’i görelim, di mi?";
					link.l3.go = "narval";
				}
				link.l1 = "Teşekkürler, Mary!";
				link.l1.go = "exit";
				link.l2 = "Mary, burada biraz dinlenmek istiyorum. Senin için de uygun mu, di mi?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Kukulcan'ına gitmeyecek misin, "+pchar.name+"?";
				link.l1 = "Henüz değil, hâlâ hazırlanıyorum.";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "Artık akşam oldu, "+pchar.name+". Neden burada kalmıyorsun? Seninle olmak istiyorum.";
				link.l1 = "Peki, sevgilim, kalıyorum...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, bugün meyhaneye gidelim!";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Bol şans ve beni unutma... Akşam gelirsen beni gör, di mi!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, bugün Jurgen'i görmeliyiz.";
					link.l3.go = "narval";
				}
				link.l1 = "Pekala, sevgilim.";
				link.l1.go = "exit";
				link.l2 = "Mary, burada biraz dinlenmek istiyorum. Senin için de uygun mu, di mi?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "Ne diyorsun sen? Gece oldu! Hayır, hiçbir yere gitmiyorsun, burada kalacaksın, di mi!";
			link.l1 = "(gülerek) Di mi, kalacağım...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал
		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Kaptan "+pchar.name+"! Subay Mary Casper, emrinizde hizmete hazır!";
				link.l1 = "Aferin, subay! Hemen gemiye çıkmanı emrediyorum. Ama önce... kaptanını öp!";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "Harikaydı, aşkım... Günaydın!";
				link.l1 = "Günaydın, tatlım! Harikasın!";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// стал другом нарвалам
		case "donald":
			dialog.text = "Donald ile konuştun mu? Amiral'in Rivadoslarla ittifak yapıp Narwhallara karşı savaşmak istediği doğru mu? Onu bundan vazgeçirdiğin doğru mu? Korsanlarla Narwhallar arasında barış mı olacak?";
			link.l1 = "Evet, Mary. Öyle.";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", kelimeleri bulamıyorum... Bir de Donald'ın seni arkadaş olarak gördüğünü söylüyorlar. Belki de Narwhal'lardan biri olabilirsin, di mi!";
			link.l1 = "Fırsatın olunca Donald'ı gör – o da seninle barışmak istiyor. Senden hem söyledikleri hem de Chad'den seni koruyamadığı için affını diliyor.";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "Donald cehenneme gitsin! Gerçi... bunu duyduğuma sevindim tabii. Onu göreceğim. Ama sen! Ben... Seninle gurur duyuyorum, di mi?";
			link.l1 = "Aman Tanrım Mary, sen... ah, kalbimi hızla attırıyorsun!";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "Konuşalım! Bir derdin mi var?";
			link.l1 = "Hayır. Mary... ilk tanıştığımız geceyi hatırlıyor musun? O iki herifle işimizi bitirdikten sonra, buraya bir gemiyle geldiğimi söylemiştim sana.";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Hatırlıyorum, evet. Gemin batmıştı ve buraya kadar yüzmek zorunda kalmıştın... di mi?";
			link.l1 = "Yalan söyledim. O zaman sana gerçeği söyleseydim beni deli sanırdın. Hiçbir barque yoktu. Buraya gelmek için İspanyol Ana Karası'nda bir Hint tanrısı olan Kukulcan'ın sihirli putunu kullandım.";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... ne diyorsun sen? Kukulcan?";
			link.l1 = "Mary, canım, bana inanmalısın, çünkü bunda mantıklı hiçbir şey yok ve bunu senden başka kimseyle paylaşamam. Nathaniel Hawk, Hint putuna dokunarak kayboldu. Peşindeydiler ve o put onu buraya gönderdi...";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "...";
			link.l1 = "Nathaniel'i arıyordum. Bir Kızılderili şamanla konuştum ve Hawk'ın yaptığı gibi put'a dokundum. Bir anda kendimi San Augustine'in ambarında buldum, gövdesindeki bir delikten dışarı çıktım... ve kader beni sana getirdi.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Bu bir gün çocuklarımıza anlatacağımız komik bir hikaye mi olacak, yoksa aklını mı kaçırdın?";
			link.l1 = "Sana kızgın değilim, Mary! Bunun inanması zor olduğunu anlıyorum – ve sana delilik gibi gelmeli – ama lütfen... bana güven.";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Eric'in hikayeleri doğruymuş, öyle görünüyor...";
			link.l1 = "Eric kim? Hangi hikayeler?";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "Eric buranın yerlilerindendi, yaşlı bir denizciydi, şimdi çoktan öldü. Ben çocukken bana hep bir Hint putundan, Rivadoların bu adada insan kurban ettiği bir tapınaktan bahsederdi.   Ona dokunanlar... kaybolurmuş... bir daha da kimse onları görmezmiş. Bunların sadece çocukları korkutmak için uydurulmuş masallar olduğunu sanırdım.";
			link.l1 = "Doğru, Mary. Eric yalan söylemiyordu.";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "Neyse ki, o korkunç putun bulunduğu gemi battı. Onu hiç kendi gözlerimle görmedim.";
			link.l1 = "Bulduğumda, en dipte yatıyordu.";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "Oraya mı daldın?! O lanet olası mucit Vedecker sana dalış giysisini mi verdi? Aşağıda yengeçler cirit atıyor, di mi! Herifin teki! Seni böyle bir tehlikeye atmaya nasıl cüret eder--!";
			link.l1 = "Mary, benim için endişelenme. Yengeçlerle başa çıkabilirim. İnsanların söylediği kadar tehditkâr değiller. Bu adaya ilk geldiğim günden beri heykeli arıyordum ve sonunda buldum.";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "Şimdi ne olacak?";
			link.l1 = "Put, buradan çıkmanın tek yolu. Ben de bu adaya, deniz dibindekinin aynısı olan bir put sayesinde geldim ve yine onunla geri döneceğim... Mary! Ağlıyor musun? Ah Mary, lütfen yapma...";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark, ";
			else sTemp = "";
			dialog.text = "Neden ağlamayayım ki? Ağlamak istiyorsam ağlarım, di mi... (ağlar) Hep benim adamlarıma olur böyle şeyler! Yine yalnız kalacağım!";
			link.l1 = "Sence bana ne olacak? Gerçekten seni burada bırakıp gideceğimi mi sanıyorsun?! Senin için geri döneceğim, bir gemiyle. Hem seni hem de "+sTemp+"Nathaniel yine benimle. Benimle birlikte dünyaya açılmaya var mısın?";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(gözyaşları içinde) Tabii ki... tabii ki, kabul ediyorum... Geri döneceksin, değil mi? Peki buraya nasıl dönmeyi düşünüyorsun? Sadece Köpekbalığı buraya nasıl gidileceğini biliyor – ve sakın beni unutayım deme, yoksa seni bulduğumda pataklarım!";
			link.l1 = "Mary, yeter! Elbette senin için geri döneceğim! Seni tanıdığımdan beri kalbimi böyle hızlandıran başka kim var ki? Merak etme sevgilim, Shark bana adanın koordinatlarını ve yol tarifini verdi. Seni tekrar bulacağım.";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "İspanyol Sahili’ndeki putun seni buraya gönderdiğini söyledin, ama ya aşağıdaki seni başka bir yere, mesela Afrika’ya götürürse? O zaman ben ne yapacağım?!";
			link.l1 = "Kukulcan is an Indian god; it will take me somewhere in the Caribbean or the Spanish Main. I only need to find a settlement; then it will be easy for me to find my ship and crew.";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "(ağlar) Bana söz ver... hayır, bana yemin et ki geri döneceksin, di mi?!";
			link.l1 = "Mary, sevgilim, sana yemin ederim ki geri döneceğim. Ve seni bu lanet yerden alıp götüreceğim. Çok uzun süre özlemene gerek kalmayacak. Artık yeter, dökme şu gözyaşlarını.";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "Peki, "+pchar.name+"... ... Bana geri dön, seni bekliyor olacağım, di mi! Ne zaman gideceksin?";
			link.l1 = "Henüz bilmiyorum. Önce kendimi hazırlamam lazım, sonra dalıp heykele dokunacağım. Sana boğulduğumu söyleyecekler – sakın inanma. Her şey yoluna girecek.";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "Anladım. "+pchar.name+", sevgilim, sarıl bana... öp beni...";
			link.l1 = "Mary... sevgili Mary'm...";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// дарим Мэри палаш Нарвал
		case "narval":
			dialog.text = "Jurgen mi? Neden?";
			link.l1 = "Göreceksin. Bu hoş bir sürpriz olacak.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Vay, ne ilginç! Hoş mu? Di mi? Hadi gidelim, yoksa meraktan öleceğim!";
			link.l1 = "Buna bayılacaksın, eminim. Hadi gidelim!";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "Hadi gidelim, "+pchar.name+"!";
			link.l1 = "Tabii...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "Peki, "+pchar.name+", benim için ne sürprizin var?";
			link.l1 = "Mary! Jurgen and I decided to make you a present from us both. This is a unique blade, a broadsword carrying the Narwhal name. There are only two of such swords in the world: the first was owned by Alan Milrow; this one will be yours. It is made of special iron, forged by Jurgen's masterful touch, which will never go dull or rust.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "Sevgili kızım... Tüm Narwhal'lar ne kadar acı çektiğini biliyor. Bu geniş kılıcı, Narwhal klanının simgesini, taşımayı hak ediyorsun. Onu gururla taşı. Bu kılıç, düşmanlarına korku salacak ve savaşta seni iyi koruyacak.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "Jurgen? Bu... benim için mi?...";
			link.l1 = "Evet, Mary. "+sld.name+"  Bunu senin için yapmamı istedi ve denizin dibinden eşsiz bir demir getirdi. Hiçbir çelik bu malzemenin ağırlığına ve sağlamlığına yaklaşamaz. Bu kılıca ruhumu kattım, tıpkı bir zamanlar Alan'ınkine kattığım gibi.";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "I don't know what to say... Thank you, Jurgen, thank you! I'll carry it with pride, and be worthy of it, I swear, all right! I don't train with broadswords often; I will now!";
			link.l1 = "Hiç şüphem yok, kızım.";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"... bekle... şimdiye kadar tanıdığım en iyi adamsın! Gerçekten harikasın, di mi? Bunun benim için ne anlama geldiğini biliyor musun? Bu kılıç, hayatımda aldığım en güzel hediye! Benim için zaten o kadar çok şey yaptın, hayatımı iki kez kurtardın, ama hâlâ beni şaşırtmaya devam ediyorsun! Teşekkür ederim, aşkım!";
			link.l1 = "Bunu hak ediyorsun, Mary. Ve son nefesime kadar seni her gün şaşırtmaya devam edeceğim! Gülüşün içimi sevinçle dolduruyor ve hediyeyi beğenmene çok sevindim.";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "(kıkırdar) Teşekkür ederim! Ne harika bir kılıç, di mi? Onu kullanmak için güçlü bir el gerek... Onunla antrenman yapmaya başlamak için sabırsızlanıyorum!";
			link.l1 = "Bunu hemen kavrayacağına eminim. Koş kamarana ve hemen dene!";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "Bunu yapacağım. Tekrar teşekkür ederim, beyefendi! "+pchar.name+"... Bu gece gel, hazır olduğunda yanıma gel... (kıkırdar)";
			link.l1 = "Elbette, hanımefendi. Akşam görüşürüz.";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
			// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// Мэри дарит талисман
		case "talisman":
			dialog.text = "Bak, bir göz at. Dış halkadaki gemilerden birinde, bir kaptanın sandığında buldum bunu. Tecrübeli her denizci bu tılsımın bir rotacı için çok değerli olduğunu söyler. Gemiyi en kötü fırtınalardan koruyabiliyormuş. Birçok kişi almak için can atıyordu ama satmadım... Senin olmasını istedim, sevgilim. Bu tılsımı kullan, denizde güvende ol.";
			link.l1 = "Teşekkür ederim, Mary! Çok düşüncelisin, seni seviyorum!";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a talisman of 'Jonah'");
			dialog.text = "Gerçekten mi? Beğendin mi? Ah, harika! Çok sevindim, di mi?";
			link.l1 = "Bu çok nadir ve değerli bir tılsım. Tabii ki hoşuma gitti! Teşekkür ederim, canım!";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... geri geldin. Seni bekliyordum, her gün ufka bakıyordum, di mi! Bana döndün...";
			link.l1 = "Evet, Mary. Söz verdiğim gibi geldim. Gel, sarılayım sana, sevgilim!";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Ah, "+pchar.name+"... You can't imagine what it's been like! The Narwhals said you drowned. They were all so sure you were dead. I kept telling them that you were alive... Of course, nobody believed me; they thought I'd gone mad after all that's happened.";
			link.l1 = "Mary... Sevgilim! Ne oldu? Titriyorsun... üşüyor musun?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Hayır, üşümüyorum. Sadece... burada konuşmak istemiyorum. Sonra kamarama gel. Seninle yalnız konuşmak istiyorum, di mi? Şimdi Amiral ve Nathaniel’in yanına mı gidiyorsun?";
			link.l1 = "Evet. Köpekbalığı ile konuşmam ve tabii ki Danielle'i Nathaniel'e götürmem gerekiyor. Uzun sürmeyecek. Yakında görüşürüz, Mary.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Ben... Seni görmeyi dört gözle bekliyorum. Mümkün olan en kısa sürede gel, di mi?";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"! Sonunda. Konuşmamız lazım, di mi!";
			link.l1 = "Ne oldu Mary? Bir şey seni üzüyor. Ne yaşandı?";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "O oldu... "+pchar.name+", geminde o fahişe de kim?";
			link.l1 = "Orospu mu? Danielle'den mi bahsediyorsun? Ama zaten biliyorsun ki--";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "Hayır, Danielle değil. O yarı çıplak sarışın var ya, senin geminin güvertesinde salına salına dolaşan! Dürbünle gördüm onu, di mi!";
			link.l1 = "A-ah! O Helen McArthur. O da Danielle gibi bu tuhaf hikâyeye karıştı. Şu anda subayım olarak görev yapıyor – tabii ki geçici olarak.";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "Subay mı? O senin subayın mı?!";
			link.l1 = "Evet, öyle. Bunun nesi var? Mary... kahretsin, kıskanıyorsun!";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "Şaşıracak ne var ki?!... (gözyaşları içinde) Bunca zamandır seni bekledim. Senin yüzünden uyuyamadım, şimdi de buraya bir orospu ile dönüyorsun--";
			link.l1 = "Mary! Ağlama artık! Sana ne oldu? Bir adamı gözünü kırpmadan doğrayabilirsin ama gözlerin hep yaşlı... Mary, canım, Helen sadece bir subay, ortak hedeflerimize ulaşana kadar geçici olarak burada, hepsi bu.";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "I've been training hard with the broadsword you gave me, and I've mastered it perfectly!";
				notification("Heavy Weapons +", "Mary");
			}
			else sTemp = "I've been training hard with rapiers and I've mastered them perfectly.";
			dialog.text = "(ağlayarak) Subay... O zaman ben de senin subayın olmak istiyorum, di mi? Dövüşebilirim, bunu biliyorsun! "+sTemp+" Ve ben iyi nişan alırım! Denizcilikten hiç anlamam ama çabuk öğrenirim. Yetenekliyim, di mi!";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "(kabul ediyorum) Mary... Bu teklifi zaten ben sana yapacaktım. Senden daha ateşli ve yetenekli bir kız yok! Yanımda olmanı istiyorum!";
			link.l1.go = "adversary_hire";
			link.l2 = "(reddet) Mary! Biniş subayı olmak tehlikeli! Ne istediğini anlamıyorsun. Hayatını riske atamam.";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "Yapamaz mıyım? O sarışın orospu subay olabiliyor da ben olamıyor muyum? Yalan söylüyorsun, "+pchar.name+", sen aslında benimle olmak istemiyorsun! (ağlıyor) O zaman o kız benden daha mı iyi, ha?";
			link.l1 = "Mary, anlamıyorsun!";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "Ben de biliyorum! Sana bakarken gözlerinin nasıl parladığını gördüm! O sadece bir subay değil, di mi? Bunu anlıyorum. (ağlayarak) Tabii ki onunla boy ölçüşemem - gemi yönetmeyi biliyor...";
			link.l1 = "Mary, ne diyorsun?";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "Bitti... (ağlıyor) Git buradan! Git o fahişene dön! Ben de burada kalacağım...! Anahtarımı ver!";
			link.l1 = "Ama Mary...";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "Git buradan...";
			link.l1 = "...";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // обидел Мэри - больше от неё ничего не получишь
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// соглашаемся
		case "adversary_hire":
			// проход второй - смотрим, Элен может стать подругой или нет
			bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
			if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
			{
				dialog.text = "Gerçekten mi? Beni gerçekten subayın olarak mı istedin? "+pchar.name+", kahretsin, bunun beni ne kadar mutlu edeceğini hayal bile edemezsin! Senin subayın olmayı o kadar çok istiyorum ki... ama o sarışınla aynı gemide değil!";
				link.l1 = "Mary, ama neden?!";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "Gerçekten mi? Beni gerçekten subayın olarak mı istedin? "+pchar.name+" Lanet olsun, ne kadar mutlu olduğumu hayal bile edemezsin! Yemin ederim, seni asla hayal kırıklığına uğratmayacağım, göreceksin!";
				link.l1 = "İsa aşkına, Mary, sevgilim, sen gerçekten çok değerlisin. Az önce ağlıyordun, şimdi ise yüzün ışıl ışıl! Ve Mary, sen benim için sadece bir subay değilsin. Bundan çok daha fazlasısın ve beni asla hayal kırıklığına uğratabileceğini sanmıyorum.";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "Sen onu sadece subayın olarak görüyor olabilirsin, ama onun seni sadece kaptanı olarak gördüğünden şüpheliyim. Sana attığı bakışı gördüm, o bakışı iyi bilirim, di mi! Ama o bakışları sana atacak tek kişi benim.";
			link.l1 = "Mary, sevgilim, sana zaten söyledim, ona karşı hiçbir şey hissetmiyorum, hepsi bu! Aramızda hiçbir şey yok! Yemin ederim, lanet olsun! Bana Kıyı Kardeşliği'nin yarattığı karmaşayı çözmek için onun yardımı lazım. Eğer ona yardım etmezsem, Jan Svenson da bana Tortuga'yı ele geçirmemde yardım etmeyecek ve ona ihtiyacım var!";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+", sevgilim, sarıl bana... Üzgünüm. Sana inanıyorum. Ama onun yanında kalıp seninle flört etmesini izleyemem, di mi! Sonunda kılıcımı alır, onu ortadan ikiye bölerim!";
			link.l1 = "Bence yapardın... Oldukça ateşli bir mizacın var, di mi?";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "Ve eğer onu öldürseydim - beni terk ederdin... ve bunun için kendimi asla affetmezdim.";
			link.l1 = "Peki ne öneriyorsun, Mary? Onunla ne yapmamı istersin?";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "Onun geçici bir subay olduğunu söyledin. Onu karaya çıkardığında – tercihen ıssız bir adada – sana katılırım. (kıkırdar) Seninle dünyanın öbür ucuna kadar gelirim, di mi?  Şimdi söyle bakalım, "+pchar.name+" sevgilim... o gerçekten benden daha mı iyi?";
			link.l1 = "Saçmalık! Böyle konuşmayı bırak, Mary, senden daha iyi bir kadın yok!...";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "O zaman kanıtla. Seni kimseyle paylaşmam, "+pchar.name+"! Seni başkasıyla paylaşmaktansa bırakırım daha iyi, di mi?";
			link.l1 = "Peki, Mary. Bir anlaşma yapalım. Şu anda Helen'den kurtulamam - görevim için çok önemli. Ona sorunlarında yardımcı olacağım, onu Isla Tesoro'nun kraliçesi yapacağım, sonra da bırakacağım ve artık aramızda hiçbir engel kalmayacak. Umarım bu bir iki aydan fazla sürmez. O kadar bekler misin beni, di mi?";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "Yapacağım, di mi! Açık olayım... Eğer bana geri dönersen, bu beni onu seçtiğine işaret eder. Ve eğer dönmezsen... o zaman mesele kapanır. Burada kalır, kendi klanımı kurarım – Casper klanı!";
			link.l1 = "Yine mi gözyaşları? Mary, hadi ama. Yeter artık! 'Kendi kabilemi bulacağım'... Ah seni aptal kız, tabii ki döneceğim! Seni bu çürük eski gemilerin arasında bırakmaya cesaret edemem! Adalet Adası'nı gözyaşlarınla sular altında bırakırdın!";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = " O zaman, mümkün olan en kısa sürede geri dön... "+pchar.name+", öp beni, lütfen...";
			link.l1 = "Geri döneceğim. Söz veriyorum!"; // ага, а мы посмотрим, обманешь или нет
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// повторный разговор после расставания с Элен
		case "adversary_hire_return":
			dialog.text = ""+pchar.name+", benim için mi döndün?";
			link.l1 = "Elbette! Sana hiç yalan söyledim mi? Senden ayrı kalmaya dayanamam ve bir daha senden ayrılmaya hiç niyetim yok... aşkım.";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
			dialog.text = "Gerçekten mi? "+pchar.name+"! Nereye gidersen git, peşinden gelirim! Sana asla yalan söylemem, asla ihanet etmem, yemin ederim!";
			link.l1 = "Sana inanıyorum, sevgilim... Ben de yapmayacağım."; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+", sevgilim, sarıl bana... Birlikte olacağız, değil mi? Söz ver bana!";
			link.l1 = "Evet, birlikte olacağız, Mary. Sonsuza dek.";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "Tıpkı Danielle ve Nathaniel gibi mi?";
			link.l1 = "(gülerek) Evet, tıpkı onlar gibi.";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... Seni seviyorum! Sanırım bana evlenme teklif etsen kabul ederdim...";
			link.l1 = "Sevgili Mary... Tabii ki, bunu sonra konuşuruz. Bu gemi mezarlığındaki hayatın sona erdi. Hadi seni buradan çıkaralım. Gemime hoş geldin... ve geniş dünyaya, sevgilim!";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "Bu adada, Ceres'te, son bir geceyi birlikte geçirelim. Sadece ikimiz. Sabah olana kadar seni hiçbir yere bırakmam, di mi?";
			link.l1 = "Şu anda senin gemindeyiz, benimkinde değil... o yüzden senin emirlerini dinleyeceğim, Kaptan Casper.";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "LSC_mary_hire":
			dialog.text = "Emredersiniz, kaptan!";
			link.l1 = "...";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> консультации по морским сражениям
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! Bir fikrim var...";
			link.l1 = ""+npchar.name+"?   Burada güvende değilsin.  Gemide kalmanı emretmiştim--";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", kahretsin, hiçbir yer güvenli değil! Bu tenekede tüm adayı haritadan silmeye yetecek kadar barut var! Şunu bir dinle, di mi?";
			link.l1 = "Dinliyorum, ama lütfen çabuk ol.";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "Korsan korveti ve fırkateyn. Hâlâ bizi kendi adamları sanıyorlar... şu Knave herifi yüzünden, di mi? O zaman birkaç varil barut, bir fitil alıp fırkateyne gidelim.\nYanlarına yanaşınca fitili ateşleriz, varili onlara atarız ve olabildiğince hızlı uzaklaşırız. Kıçlarını talaşa çeviririz, sonra da korvete çıkarız.";
			link.l1 = "Riskli... ama... planın işe yarayabilir. Yeter ki onlara yaklaşana kadar kandırabilelim.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Bence denemeliyiz, "+pchar.name+"";
			link.l1 = "Pekala. Hadi deneyelim. Çocuklar! Üç varil barut getirin! Ha-ha, aklına bayılıyorum, "+npchar.name+"! Bunu kendi başıma asla düşünemezdim.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "Bana sonra teşekkür edersin... (göz kırpar)";
			link.l1 = "...";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Mary");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "Emriniz üzerine geldim, efendim! (kıkırdar) Ne oldu?";
			link.l1 = "Jackman'ın gemisi Sabo-Matila Koyu'nda: ağır bir fırkateyn, Centurion. Bu gemi bir zamanlar Hawkes ailesine aitti, bu yüzden kaptan kamarasında önemli eşyalar ve belgeler olmalı... Gemiyi ele geçirmeliyiz.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Damn me... How are you going to do that with our little bird? I looked through the spyglass; I've seen how many men and cannon Centurion's got, all right!";
			link.l1 = "Haklısın. Jackman'ın adamları bizimkilerin en az iki katı, hem de hepsi usta katil ve paralı asker. Önce sayılarını azaltmadan gemiye çıkmak delilik olurdu. Centurion'un topları da bu iş için fazla güçlü, uzun süren bir deniz savaşı da seçenek değil. Ne yapacağımı bilmiyorum...";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+",   henüz   bizi   düşman   olarak   görmediler,   değil   mi?   Tıpkı   o   aptallar   gibi   Turks'ta?   Barut   numaramızı   yine   kullanabiliriz...";
			link.l1 = "Mary, sana az önce fırkateyni ele geçirmemiz gerektiğini söyledim, batırmamız gerektiğini değil!";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Bunu biliyorum, "+pchar.name+"! Onu batırmayacağız. Birkaç boş rom fıçısı alıp barut, saçma ve kısa fitillerle dolduracağız. Sonra Centurion'un yanına yanaşıp bombayı güvertesine fırlatacağız.";
			link.l1 = "Ha! Gerçekten işe yarayacağını mı sanıyorsun?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "Neden olmasın? Onların bordası bizimkinden yüksek ama iki ya da üç adam - makara ve halat yardımıyla - dolu bir fıçıyı kolayca kaldırıp atabilir. Bağırırız: 'İşte Knave'den bedava rom!' Fıçı, tepki vermeye bile fırsat bulamadan patlar.";
			link.l1 = "Patlayan saçma güvertede herkesi paramparça eder... Kahretsin, kulağa çok cazip geliyor.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Beş varil kullan, "+pchar.name+". We have the element of surprise. They won't suspect a thing! But we've got to sail away after throwing the bomb so they don't board us though; once it blows, then we move back in and board them.";
			link.l1 = "Ve fıçıları atmadan önce kimliğimizi öğrenmemeliler... Kahretsin, onlara yaklaşmak hiç kolay olmayacak. Jackman, Ghoul gibi aptal değil.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "En iyi tılsımlarını alsan iyi edersin, "+pchar.name+". Kızıl Mary'ye güven. Denemeye değer, di mi?";
			link.l1 = "İyi söyledin, kaybedecek bir şeyimiz yok... Fitilleri hazırlasan nasıl olur?";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "Emredersin kaptan! Bana güvenebilirsin.";
			link.l1 = "Mary, harikasın!";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "Teşekkür ederim, "+pchar.name+"! Seni hayal kırıklığına uğratmayacağım!";
			link.l1 = "I know you won't; I hope we're the ones that don't let you down by fucking up this plan of yours... To arms!";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// <-- консультации по морским сражениям
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "İşte buradasın! Seni bulmak biraz uğraştırdı... Harikaydın, Kaptan! Hayatımda böyle nefes kesici bir atlayış görmedim! Tam bir kahramansın! Ama itiraf edeyim, az kalsın kalbime iniyordu. Bir gün bu numaralarınla beni öldüreceksin, sevgilim...\nPeki, bu kadın da kim oluyor? Sadece bir dakika gözümü senden ayırayım, hemen kendine bir yosma bulmuşsun.";
			link.l1 = "Mary! Bu 'serseri' Catherine Fox, Deniz Tilkilerinin komutanı Albay Fox'un kızı. Onu Antigua'ya götürmeliyiz.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Gerçekten mi? Ne hoş. Peki, bana ondan bahsedebilirsin... bu gece. Kamaramızda. Benimle. Yalnız. Şimdi, hadi gidelim, acele etmemiz lazım!";
			link.l1 = "(iç çeker) Sensiz ne yapardım, Mary? Catherine, hadi ama!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Aman Tanrım, uyanmışsın! Seni gidi alçak! Bir daha beni böyle korkutma sakın!";
			link.l1 = "Mary... canım, ne oldu? Başım... ah...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Kaptanın kamarasına girdiğimizde, sen yerde bir ceset gibi hareketsiz yatıyordun. Seni kaldırıp gemimize sürükledik – tam zamanında, çünkü güvertede yatan iskeletler tekrar ayağa kalkmaya başlamıştı.\n Tanrım, çok korkunçtu! Onlara karşı hiçbir şey yapamadık! Halatları kestik ve uzaklaşmaya çalıştık, ama toplarından gelen bir salvo gemimizi fena halde hasara uğrattı ve kontrolü kaybettik. Gerçekten şeytandılar, di mi! Sonra yelken açıp göz açıp kapayıncaya kadar ufukta kayboldular.\nGemimiz karaya oturdu, bu yüzden fırtına onu yok etmeden önce sandallarla bu sahile çıktık. Bugün birçok adam öldü, ama gemi sonunda hayatta kaldı... zar zor.";
			link.l1 = "Aferin Mary... Sensiz ne yapardım, di mi?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Ah, bakalım... belki boğuldum? O gemide kapana kısıldım? Ölüler tarafından paramparça edildim? Kahretsin... ve seni de kahretsin, "+pchar.name+", beni böyle korkuttuğun için!";
			link.l1 = "Sus, Mary, sus. Beni kurtardığın için teşekkür ederim, aşkım. Ne kadar zamandır baygındım?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "A day. I cleaned your wounds, gave you medicine, and poured some rum into you. You should get well soon; don't you dare die on me!";
			link.l1 = "Söz veriyorum yapmayacağım, sevgilim. Ama... kendimi daha iyi hissettiğim zamanlar oldu...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Daha iyi görünüyordun... O muydu, "+pchar.name+"? 'Uçan Hollandalı' mıydı? Hikâyelerini duymuştum ama asla böyle bir şey hayal etmemiştim...\nNeden peşimize düştüler? Ve neden bize ateş açmadan gemimize çıktılar?";
			link.l1 = "Kaptanları muska istiyordu, hani şu Tuttuathapak'la konuştuğum - Hintli şaman. Bu yüzden gemimize çıktılar, ama kaptanları muskayı alınca, artık bizi sağ bırakmalarına gerek kalmadı...\nNe korkunç bir şeydi! Ölülerin kullandığı bir gemi! İnanılmaz... Karayipler'de görebileceğim en kötü şeyi gördüğümü sanıyordum.";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Tabii ki, 'Uçan Hollandalı' eninde sonunda gelip seni bulacaktı, başka kimi bulacaktı ki? Tanrı aşkına, bu beni kiliseye geri dönecek kadar korkuttu!";
			link.l1 = "Ne hissettiğini biliyorum. O Kızılderili köyüne geri dönmem gerek, Tuttuathapak'a olanları anlatmalıyım. O gemi bize muska yüzünden saldırdı! Umarım o kızıl derili şeytan, şu yaşayan ölülerin o şeyi neden istediğine dair bir açıklama yapar.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Peki, ama dikkatli ol – hâlâ perişan haldesin.";
			link.l1 = "Sen benim için gereken tek ilaçsın. Ve... Mary, seni seviyorum...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Ben de seni seviyorum, canım... Tanrı'ya şükür hayattayız!";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", senin kollarında olmaktan daha mutlu eden hiçbir şey yok, di mi... Hadi gidelim!",""+pchar.name+", mümkün olsaydı her uyanık anımda senin yanında olurdum. Hadi gidelim!");
			link.l1 = RandPhraseSimple("Sen en iyisisin, aşkım...","Harikasın, sevgilim...");
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Mmm, harikaydın... her zaman öylesin!","Harikaydı!");
			link.l1 = RandPhraseSimple("Seni mutlu edebildiğim için çok memnunum, aşkım...","Seni seviyorum Mary...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов							
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", kollarında olmaktan daha çok istediğim bir şey yok, di mi... Ama şimdi zamanı değil - o alçak Thibaut kaçmadan önce onu yakalamamız lazım.";
				link.l1 = "Her zamanki gibi haklısın, kızım...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", senin kollarında olmaktan daha mutlu eden hiçbir şey yok, di mi... Hadi gidelim!",""+pchar.name+", mümkün olsa her an yanında olurdum. Hadi gidelim!");
			link.l1 = RandPhraseSimple("Sen en iyisisin, güzelim...","Sen harikasın, ateş saçlı güzelim...");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "LoveSex_Room_Go");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", çok uzun zaman oldu birlikte olmadık... Beni tamamen unuttun, di mi! Bu gece için bir oda tutalım ve dertlerimizi başka bir güne bırakalım.",""+pchar.name+", Beni tamamen unuttuğunu düşünmeye başlıyorum! Sevgilim, seninle biraz... baş başa kalmak istiyorum. Bu gece için bir oda tutalım, di mi?",""+pchar.name+", neredeydin sen? Seninle bir gece geçirmek, biraz şarap içip rahatlamak için can atıyorum. Bunca zamandır denizdesin, beni tamamen unuttun!");
			link.l1 = "Mary, canım, ne diyorsun, 'beni tamamen unuttun' diye? Saçmalama... Ama gerçekten de çok meşguldüm – ilgilenmem gereken dertler bitmek bilmiyor. Affet beni, sevgilim. Hadi yukarı çıkalım, bu gece tamamen seninim. Dünya bekleyebilir!";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("Bugün olmaz, canım. Yapacak çok işim var.","Mary, tatlım, seni unuttuğumu nasıl düşünebilirsin? Birlikte vakit geçireceğiz, sonra - ama şimdi yapacak işlerimiz var."),RandPhraseSimple("Mary, aklımdan hiç çıkmıyorsun, ama şu anda rahatlayamayız.","Mary "+npchar.lastname+", bugün bunun için vaktimiz yok."));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
		if(sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); 
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes"; 
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "(iç çeker) Peki, sanırım kamarada kendi başıma oyalanırım... Peki kaptan.";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			if(bImCasual) Log_Info("To refuse Mary become more famous");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "Charles...";
			link.l1 = "Mary, canım, ne diyorsun, 'beni tamamen unuttun' diye? Saçmalama... Ama gerçekten de çok meşguldüm – ilgilenmem gereken dertler bitmek bilmiyor. Affet beni, sevgilim. Hadi yukarı çıkalım, bu gece tamamen seninim. Dünya bekleyebilir!";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "Ah, işte buradasın! Artık beni sevmiyorsun, değil mi? Söylesene!";
			link.l1 = "Ne?! Mary, bu da ne saçmalık? Neden böyle düşünüyorsun?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "O zaman neden o fahişeleri, o genelev kadınlarını ziyaret ediyorsun? Yaptığını biliyorum, bana yalan söyleme! Sevişirken bende hoşuna gitmeyen bir şey mi var, ha? (ağlar) Söylesene...";
			link.l1 = "Mary, Mary... sakin ol lütfen, kızım. Evet, geneleve birkaç kez gittim ama sadece iş için. Eğlenmek gibi bir niyetim yoktu!";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "Ve yukarıdaki yatak odasında ne tür 'iş meselelerin' vardı? (ağlayarak) Yalan söylüyorsun, "+pchar.name+"!";
			link.l1 = "Mary, canım, lütfen yapma bunu... Gerçekten de genelevin sahibesiyle iş konuşuyordum.  Evet, birkaç kez yukarı çıktım – son seferinde valinin özel bir işi için: benden evlilik yüzüğünü bulmamı istedi. Ekselanslarına nasıl hayır diyebilirdim ki?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "...";
			link.l1 = "Ve yukarıdaki yatağın altına bakmam gerektiğini hanıma nasıl açıklayabilirdim ki? Açıklayamazdım. O yüzden geceyi yukarıda geçirebilmek için bir fahişe satın almak zorunda kaldım...\nİkinci seferde ise, bir tüccarın orada gemi belgelerini kaybettiği söylendi bana. Odayı arayabilmek için yine bir kızla anlaşmam gerekti – ve gerçekten de belgeleri buldum, üstelik bunun karşılığında oldukça iyi bir ödeme aldım...";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "...";
			link.l1 = "Üçüncü seferde ise yerel komutanın işine yardım ediyordum: genelevdeki kadınlara garnizondan bir subay hakkında sorular sormam gerekiyordu. O subay casusluk ve korsanlarla iş birliği yapmakla suçlanıyordu. Sonunda onu yakaladık ve ben de güzel bir ödül aldım...";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "...";
			link.l1 = "Görüyor musun şimdi? Sana söylüyorum, hepsi iş içindi. Mary, sevdiğim ve ihtiyaç duyduğum kişi sensin. Sana sadığım, yemin ederim! Gerçekten, sen varken gidip o pis liman fahişesiyle yatabileceğimi mi düşünüyorsun? Bunu nasıl aklına getirebildin ki!";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = "... Hayatımda duyduğum en büyük saçmalık bu, di mi? Ama... "+pchar.name+"... bana doğruyu mu söylüyorsun? Arkamdan başka bir kadınla yatmadın mı?";
			link.l1 = "Mary, canım, hayır, söz veriyorum yapmadım. Sevdiğim tek kadın sensin, bu doğru. Gel yanıma, canım. Sana sarılayım... Gözyaşlarını sil ve lütfen artık kıskanmayı bırak! Eğer istersen, bir daha genelevin önünden bile geçmem!";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "Evet, tam da istediğim bu!... "+pchar.name+", Kıskanıyorum çünkü seni seviyorum... ve seni kaybetmek istemiyorum, di mi? Eğer bir kaltak sana şöyle bir gülümserse, bir sonraki karnında olacak olan benim kılıcım olur!";
			link.l1 = "İsa aşkına, Mary, sakin ol... Kimseyi öldürmene gerek yok! Beni kaybetmeyeceksin, söz veriyorum. Her şey yolunda, sakin ol. Sen benim tek kadınımsın – hem de dünyanın en iyisi! Bana güven.";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", ne tuhaf bir soru? Seni seviyorum. Beni kurtardın. Gerçekten oraya tek başına gitmene izin vereceğimi mi sandın? Sakın aklından bile geçirme, di mi! Ben seninleyim! Ne zaman gidiyoruz?";
			link.l1 = "Haklısın, sevgilim. Bunu nasıl sorgulayabilirim ki? Gittiğimizde sana anlatırım. Önce kendimizi iyi hazırlamamız lazım.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Hazırım, "+pchar.name+". Seninle Cehennem’e ve ötesine giderim!";
			link.l1 = "Sana teşekkür ederim, sevgilim...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.MarySexBlock = "true"; // fix 22-03-20
			dialog.text = "Bu sefer neyle karşı karşıyayız, Kaptan? İspanyollar mı? Korsanlar mı? Yoksa daha beteri mi?";
			link.l1 = "Daha da kötü, Mary, hem de çok daha kötü. Vali, adı çıkmış bir hayat kadınına ziyarete gitmeyi düşünüyor ve ben de yanında ilgi çekici biri olarak eşlik edeceğim. Sıkıcı sohbetler, fahiş fiyatlı şaraplar ve sıkıcı soylular.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Tam tersi: soylu bir hanımefendinin düzenlediği bir davete davet edildim. Ekselansları bana eşlik etmemi isteyince şaşırdım açıkçası, ama dürüst olmak gerekirse, böyle bir değişiklik bana iyi gelecek, dört gözle bekliyorum.";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "O-ho! Gerçekten daha da beter! Bir hayat kadını! Güçlü şarap! Sosyallik! Evet, kulağa tam bir işkence gibi geliyor, "+pchar.name+", seni pi--";
			link.l1 = "Mary, sakin ol lütfen. Oraya gidiyorum diye... yani, orası bir genelev değil! Yani... aslında genelev, ama kahretsin, ben hem soylu bir adamım hem de sözümde dururum. Bunca şeyden sonra bana hâlâ güvenmiyor musun? Vali benden sadece küçük bir iyilik istedi ve ona yardımcı olmam gerekiyor, hepsi bu!";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Evet, böyle birkaç 'soylu' duydum, di mi? Senin yanında da gördüm onları. Fahişelik onların ekmeği. 'Yüksek' sosyete, 'asil' eğlenceymiş, hadi oradan! Evlilik bile bu... ıyy... 'hanımefendilere' gitmelerine engel olmuyor. Senden daha iyisini beklerdim, "+pchar.name+". Şey, siz 'soylular' benim yıkanmamış kıçımı yalayabilirsiniz.";
			link.l1 = "Mary, bekle! Kahretsin...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "İkimiz de bir tatili hak ettik. Heh, kırmızı ceketli bir kadını görmeye hazırlar mı sence? Köşelerdeki fısıldaşmaları bir düşün! Biri kesin bayılır - eğlenceli olurdu, di mi?";
			link.l1 = "Mary, canım, burası bir hanımefendiyi götüreceğin türden bir eğlence değil... en azından senin gibi bir hanımefendi için değil. Biraz karışık ama anlatayım--";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Benim gibi bir kadın mı? Açık konuş: O peruklu heriflere layık değilim. Fazla sıradanım, fazla aşağı tabakadanım, di mi? O şatafatlı partilere, saygıdeğer Charles de Maure'a layık değilim, öyle mi?";
			link.l1 = "No, not at all. You're amazing and I don't care about the kind of impressions we make on the people around us. The governor is trying to solve his problems with my help, as always. I will be like a valuable trophy for him; an interesting guest to impress the noble good-for-nothings.";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Hayır, "+pchar.name+", sorun yok, anladım. Soylular soylularla - ayaktakımı dışarıda kalsın. (eğilir) Umarım sosyalliğinizden keyif alırsınız, Lord Kıçıkıran. Sıradan toprağa döndüğünde konuşuruz, olur mu?";
			link.l1 = "Mary, bekle! Ah, kahretsin...";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Umarım sosyalliğinin tadını çıkarırsın, Lord Kıçıkıran. Mütevazı toprağa döndüğünde seninle konuşurum.";
			link.l1 = "Mary hadi ama!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Şuna bak, di mi! Yüksek sosyetede kaybolmuş kaptanımız gelmiş!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Bir günlüğüne geneleve kayboluyorsun, şimdi bütün kasaba senden bahsediyor. Charles, bana Narwhal'ı kıçına sokmamam için tek bir iyi sebep söyle.";
			link.l1 = "Mary, her şeyi açıklayacağım ama sonra. Şimdi bir düelloya hazırlanmalıyım – sağ kalırsam beni öldürmekte özgürsün. Bu arada, lütfen yeni gemimize göz kulak ol, di mi? Dün gece bir kart oyununda ödül olarak kazandım onu.";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Siktir et gemiyi, bu düello da neyin nesi? Buradakilere bakarsan ya kralın oğluyla ya da Papa'nın kendisiyle dövüşeceksin. Söylesene, burada ne bok dönüyor!";
			link.l1 = "Bu adam çok nüfuzlu bir soylunun, Kont de Levi Vantadur'un piç oğlu. Meydan okumayı başlatan oydu ve düelloyu onu incitmeden kazanmam gerekiyor – yoksa babasının gazabını üzerime çekerim.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Ben ise senin az önce kazandığın tenekenin üstünde kıçımın üstünde oturuyor olacağım. Aklını mı kaçırdın Charles?";
			link.l1 = "Korkarım böyle olması gerekiyor. Vali, sonrasında herhangi bir karışıklık olmasın diye bana birkaç soylu subay verdi, düelloda bana eşlik edecekler. Resmi bütünlüğü korumak için seni ya da mürettebattan kimseyi götüremem. Bu iş çok ciddi, üzgünüm.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "... Şimdi ne yapacağımı biliyor musun? O lanet gemiye çıkıp iyice sarhoş olacağım. Ne istersen yap, ama bir şeyi doğru söyledin: o soylu piç seni öldüremezse, ben öldüreceğim.";
			link.l1 = "Mary, her şey yoluna girecek, bana güven. Şimdi, bekle... Kahretsin! Yine başlıyoruz!";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "İşte orada! Bütün gün senden tek bir haber alamadık! Çarşıda dedikoduları duyduk, endişelendik. Gemilere ve kadınlara kumar oynadığını, hatta bir prensle ya da Papa'nın kendisiyle düello ettiğini söylüyorlar! Ne oluyor lan?";
			link.l1 = "Bu biraz karışık, Mary. Anlatmam zaman alacak. Ama bir fırkateyn kazanmayı başardım. Onunla ilgili işimi hallederken sen ona göz kulak olmalısın.";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Yani düello var, öyle mi?! Önceki sahibi kim? Neden onunla dövüşüyorsun?";
			link.l1 = "Durum biraz karışık ama kısaca şöyle: Gemisini ve... sevgilisini kazandım. Beni hile yapmakla suçladı ve düelloya davet etti. Bu adam çok nüfuzlu bir soylunun, Kont de Levi Vantadur'un piçi. Onu incitmeden bu düelloyu bir şekilde kazanmam gerekecek.";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Yani söylentiler doğru mu? Bir gemi için kumar oynamak anlarım da... bir kadın için mi, gerçekten?";
			link.l1 = "Damn it, Mary, it's not like that at all! He won her from the governor; I won her back from him to release her, that's it. There is nothing more to it, I swear!";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Belki bu siz soylular için normaldir, ama benim için değil, di mi! Ne istersen yap, ne istersen söyle... onun için ölmek istiyorsan öl! Bana gelince, ben senin kazandığın şu lanet gemiye gidip tavan arasını romla iyice dağıtmak isterim. Kahrolasıca, "+pchar.name+", bizim yaşadıklarımızın gerçek olduğuna ve... sonsuza dek süreceğine inanmıştım. Sanırım fazla umutlanmışım!";
			link.l1 = "Mary, o kadın umurumda bile değil! Sadece bekle, lütfen... Kahretsin! Yine başlıyoruz...";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, benim için geldin! Biliyordum, hiç şüphem yoktu, di mi? Seni gördüğüme öyle sevindim ki!";
			link.l1 = "Ben de, Mary! Bütün bu olanlar beni mahvetti... Tanrı'ya şükür iyisin!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Bu arada, beni bu kadar kolay serbest bırakmaları için tam olarak ne yaptın? Ne düzgün bir kavga, ne de bir silahlı çatışma oldu! Ha, bir de güvertede beni çıkarırlarken bir kadın gördüm. Ne oldu, Charles?";
			}
			else
			{
				dialog.text = "Onları beni böyle serbest bırakmaya nasıl ikna ettin, tam olarak ne yaptın? Ne kavga oldu, ne silah patladı, hiçbir şey! Beni çıkarırlarken güvertede birkaç İngiliz horozu gördüm. Ne oluyor Charles, bu işin aslı ne?";
			}
			link.l1 = "Tüm önemli olan, tekrar yanımda olman. Sana ihanet ettim Mary, çok üzgünüm! Umarım kalbinde bana affetmek için bir yer bulabilirsin. Aramızda olanların bu şekilde kalmasına dayanamıyorum.";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Ben de yaptım. Ben de üzgünüm, di mi? O kadınla olan işlerini bu kadar kişisel almamalıydım... O gece nöbeti düzgün tutsaydım, bizi asla bu kadar kolay alt edemezlerdi! Ne aptalmışım!";
			link.l1 = "Geçmiş, geçmişte kaldı. Seni seviyorum ve bir daha asla seni böyle bırakmayacağım. Söz veriyorum!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Üzgünüm, sana güvensizlik ettiğim için, Charles. Belki de... tam olarak ne yaptığını bilmemem daha iyi olur, di mi? Yine birlikteyiz ve önemli olan da bu.";
			link.l1 = "Senden hiçbir şey saklamıyorum. Sana her şeyi anlatacağım...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Ne hikaye ama... başkası olsa inanmaz, di mi? Biliyordum! O 'sosyal' gecenin altında bir iş olduğunu biliyordum! O asalet taslayan tavus kuşları... vicdansız herifler! En azından senin hakkında yanılmamışım – farklı olduğunu biliyordum, di mi!";
				link.l1 = "Eminim dışarıda pek çok insan beni çok daha kötü biri olarak görüyor. Masallardan çıkma gerçek bir canavar gibi.";
			}
			else
			{
				dialog.text = "Ne hikaye ama... Başka kimse inanmaz buna, di mi? Biliyordum! O 'sosyal' gecenin altında bir iş olduğunu biliyordum! Siyaset, casuslar, kom-plo-lar - ve yine, herkesi kurtardın, di mi? Benim kahramanım.";
				link.l1 = "Bundan pek emin değilim... Büyük ihtimalle birkaç hafta içinde Britanya'yla savaş başlayacak. Ama yapmam gerekeni yaptım, Mary. Sen benim için her şeysin.";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "I don't care what people think; if that's the case, you'll be my monster, Charles! And if people don't like it, let me talk to 'em. I'll always be by your side, all right!";
			}
			else
			{
				dialog.text = "Biliyorum Charles. Hep biliyordum... ama bunu senden duymak güzel. Ve ben de her zaman yanında olacağım, di mi!";
			}
			link.l1 = "Hiç şüphem yoktu, Mary. Hadi gidelim, tayfa endişeli. Yelken açıp buradan defolup gitme zamanı. Yine yanımdasın ve o ufuk bizi bekliyor...";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "Emredersiniz, Kaptan!";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, gerçekten sen misin? Umudumu neredeyse tamamen kaybetmiştim, di mi! Tanrım, seni öyle çok özledim ki! Lütfen, lütfen beni affet!";
			link.l1 = "Hayır, affet beni, bunu hiç beklemiyordum... Tanrıya şükür geldin, Mary! Çok mutluyum!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Affetmek demişken... dürüst olmak gerekirse, seni vurmalı mıyım yoksa sarılmalı mıyım diye düşünüyorum. Bana ne olup bittiğini hemen anlat, di mi?";
			link.l1 = "Seni seviyorum, Mary. Sana söylemek istediğim tek şey buydu.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Bu pek bir açıklama sayılmaz ama... Kahretsin Charles. Ben de seni seviyorum, di mi. Tanrım, sonunda, nihayet yanımdasın!";
			link.l1 = "Ve kalan zamanımızı önemsiz şeylerden bahsederek geçirmek istemiyorum. Benimle gel, bu gece seni asla bırakmaya cesaret edemem, gökyüzü bu zavallı kasabanın üstüne inse bile. Bir daha asla seni bırakmayacağım. Asla.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Belki de... tam olarak ne yaptığını bilmemem en iyisi, di mi? Yine beraberiz ve önemli olan da bu...";
			link.l1 = "Senden hiçbir şey saklamıyorum. Sana her şeyi anlatacağım...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Yani diyorsun ki... bu markiz seni bana geri getirmene yardım etti? Ve neredeyse İngiltere'yle Fransa arasında savaş çıkarıyordun? Yanlış anlama – bu gerçekten çok romantik, ama şimdi ne olacak?";
			link.l1 = "Hiçbir fikrim yok, Mary. Yine birlikteyiz, başka hiçbir şeyin önemi yok. Eğer yetkililer her şeyi halının altına süpüremezse... şey, taç adına görevimi yapmaya hazırım.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "Ve o senin markizin? Onu da geri mi getirdin? Portekizli ondan övgüyle bahsetti. Bana onun ilgisine Bastille kalesi gibi direndiğine dair söz verdi. Ona inanmak istiyorum, di mi, ama bunu senin ağzından duymak istiyorum.";
			link.l1 = "Madame Botot ile aramda hiçbir şey yok, Mary. Ona yardım ettim, o da bana yardım etti, hepsi bu. Bartholomew demişken, o nerede?";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Çoktan gitti, di mi? Beni buraya getirdikten hemen sonra yelken açtı. O lanet geneleve gitmeyeceğime yemin ettim, o da bana bir oda kiraladı, birkaç haftalığına peşin ödedi ve... gitti işte. Ah, neredeyse unutuyordum! Sana bir mektubum var!";
			link.l1 = "Bir mektup mu? Portekizli Bartholomew'dan mı? Bunun nereye varacağını hiç beğenmiyorum...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Devam et, oku bakalım. Ben gidip çocuklara bakayım. Muhtemelen endişelenmişlerdir. Herkes sağ salim geldi mi? Aşağıda bir iki kadeh içmemize aldırmazsın umarım. Ben dönene kadar başını başka bir belaya sokma, di mi?";
			link.l1 = "Peki, ama onlara dikkat et olur mu, Mary? Bu gece seninle vakit geçirmek isterim, sarhoşları gemiye taşımak zorunda kalmak yerine. Tanrım, seni tekrar kazandığıma hâlâ inanamıyorum!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Sen, ben, kumsal ve güzel bir şarap - Charles, bu çok romantik! Bunu daha sık yapmalıyız, di mi?";
			link.l1 = "Beğenmene sevindim. Bundan sonra böyle anlar için birbirimize daha çok zaman ayıracağız, di mi?";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Ne demek istiyorsun? Gemiye bir şey mi oldu? Neden diz çöküyorsun?";
			link.l1 = "Çünkü seni seviyorum, Mary. Bunu sen de biliyorsun, ben de biliyorum, bütün dünya biliyor. O yüzden şimdi, burada, denizin ve gökyüzünün önünde, sana soruyorum Mary Casper: Bana, halkımızın ve Tanrı'nın huzurunda, bize verilen günler boyunca yanımda durma onurunu verir misin? Ben, Charles de Maure, Chevalier de Monper, sana soruyorum... Benimle evlenir misin?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "Ben bunu hayal etmiştim, di mi, ama gerçekten... Ben... cevabımı biliyorsun Charles - ah, kahretsin!";
				link.l1 = "Ha-ha! Boşver, sadece şarap, hem bu gömleği hiç sevmedim zaten.";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, tabii ki evet! Evet, evet, bin kere evet!!! Sen... burası... beni bundan daha mutlu edecek hiçbir şey olamaz!!! Aman Tanrım, gülümsemekten yanaklarım çatlayacak gibi hissediyorum, di mi!";
				link.l1 = "Beni mutlu ediyorsun, Mary. Senin şerefine içiyorum, ateşli Karayip Güneşim!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Senin şerefine içiyorum, kaptanım ve gelecekteki kocam, di mi? Hayatıma giren en güzel şey sensin!";
			link.l1 = "Ama bu sadece başlangıç - bize! Ve birlikteki geleceğimize! Önümüzde daha çok şey var!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Sana içiyorum, kaptanım ve gelecekteki kocam, di mi? Hayatıma giren en güzel şey sensin!";
			link.l1 = "Ama bu sadece başlangıç - bize! Ve birlikteki geleceğimize! Önümüzde daha çok şey var!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Charles, Abbot Benoit ile konuş da devam edebilelim, di mi? Ama elbise giymem, umarım alınmazsın.";
			link.l1 = "Mary, I love you in any outfit and ... well, you know. You can wear anything you like; anyone who has a problem with that can speak to me! But, I do want to consult you about the guests and the ceremony.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "Biliyor musun, bizim mutluluğumuza gerçekten sevinecek çoğu insan bu adayı uzaktan bile göremeyecek, di mi, kiliseyi geçtim. O yüzden... burada, olması gerektiği gibi, tüm saygın kasabalılarla evlenelim, sonra da Isla Tesoro'ya gidip gerçek dostlarımızla adam gibi kutlayalım! Ne dersin?";
				link.l1 = "Harika fikir! Hadi yapalım. Abbot Benoit ile konuşacağım. Kimlerin geleceğine karar vermemiz, davetiyeleri göndermemiz gerekecek... yapılacak çok iş var!";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = "Biliyor musun, tayfadaki çocuklar dışında pek arkadaşım yok. O yüzden, sevdiğin birkaçını davet et, ben de mutlu olurum, di mi?";
				link.l1 = "Dediğin gibi, sevgilim. Rahip Benoit ile konuşup her şeyi ayarlayacağım. Muhteşem bir töreni hak ediyorsun.";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "Misafirleri dert etme, onlarla ben ilgilenirim, di mi? Arkadaşlarımıza yazar, her şeyi ayarlarım. Ama önce söyle bakalım: Düğünümüzde kimi görmek istersin?";
			link.l1 = "Benim hayalim sensin, ben ve en yakın dostlarımız. Martinik'teki tüm o resmi suratlardan sonra biraz samimiyet isteyeceğiz.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Bugünü unutulmaz yapalım. Herkesi çağır! Kimse dışarıda kalmasın!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "Biliyor musun, gün batımında açık denizde, kıç güvertede bir papazla yapılan bir gemi düğünü bana yeterdi, di mi? Ama eğer sen böyle istiyorsan, kutlayacağız! Charles ... Ağlayacağım şimdi. Sarıl bana, di mi ...";
			link.l1 = "Mary...";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "Peki, sakinim. Özür dilerim, bu benim için çok yeni. Ama Charles, ben de bu işin içinde olmak istiyorum. Ayrıca tayfalar için bir kutlama da ayarlamamız lazım, di mi, ama sanmıyorum ki bütün mürettebat kiliseye sığsın. Ben meyhaneyle konuşurum, ama içki ve para lazım olacak - denizcilerin nasıl eğlendiğini bilirsin.";
			link.l1 = "Pekala, öyle yapacağız. Ne hazırlamam gerekiyor?";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "Bence, "+sti(pchar.questTemp.LongHappy.MarryMoney)+" peso yeter, di mi? "+sti(pchar.questTemp.LongHappy.MarryRum)+" varil rom - içkisiz kalmaktan daha kötüsü yok! Her şeyi toplar toplamaz meyhaneye gel. Gerisini ben hallederim.";
			link.l1 = "Pekala, tatlım, orada görüşürüz.";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Anladım. Ama Sharptown'a da uğrayıp orada da hazırlık yapmamız gerekecek. Elli fıçı rom ve birkaç düzine şarap fıçısı yeterli olur, di mi? Ama ne olur ne olmaz, üç yüz bin peso lazım olacak.";
			link.l1 = "Bu bayağı bir para, ama buna değer. Toplarım, merak etme. Şimdi, önce rahibi ziyaret edeceğim, sonra da Sharptown'a gideceğim.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Harika, herkesi toplayacağız, di mi? Ama Sharptown'a uğrayıp her şeyi hazırlamamız gerekecek – bir kalyon dolusu içki lazım! Sanırım yüz varil rom ve elli varil şarap yeterli olur. Ama ne olur ne olmaz, beş yüz bin peso da ekleyeceğim. İçki biterse parti de biter, hiç iyi olmaz, di mi?";
			link.l1 = "Evet, arkadaşlarımız susuzluktan ölmemeli -  her şeyi hallederim, merak etme! Şimdi, önce rahibi ziyaret edeceğim, sonra da Sharptown'a gideceğim.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Her şey hazır, Charles. İçeceği indirtip sonra yerel meyhaneye gideceğim, baronla buluşup davetiyeleri teslim edeceğim. Burada bekle, di mi?";
			link.l1 = "Dümende sensin, sevgilim! Ben de bir yerlerde oyalanırım. İspanyol Ana'nın ormanına yapılan keşiflerin, bir düğüne hazırlanmaktan daha kolay olacağını asla hayal etmemiştim!";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Burada işimiz bitti Charles, di mi! Her şeyi ayarladım. Bana inan – harika olacak! Sadece, bir şey var... Yerel meyhane geçen hafta bir kutlama sırasında yanıp kül olmuş. Ama neredeyse yeniden inşa edildi, eskisinden daha büyük ve daha güzel! Hepimiz rahatça sığarız.";
			link.l1 = "Umarım burayı bir daha yakıp kül etmeyiz. Eski Ağaçkakan'ı gerçekten seviyordum! Neyse, hâlâ yapacak çok işimiz var. Artık yelken açma zamanı. Mary... sen harikasın, bunu biliyorsun, di mi?";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Yani... başlıyoruz mu? Misafirler geldi, kilise hazır. Biliyorum, çoğu çiftten daha yakınız ve bunlar sadece güzel bir salonda edilen büyük laflar, ama kahretsin - o eski Hint şehrinde bile bu kadar heyecanlanmamıştım, di mi!";
			link.l1 = "I'm sure it's absolutely normal, my love; I'm nervous too. I think Abbot Benoit is waiting, I'll go to him and find out when the service will begin.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Pekala, biraz kasabada dolaşacağım, kafamı toparlamam lazım, di mi! Charles... anlıyor musun, artık geri dönüş yok?";
			link.l1 = "Mary, canım, seni tanıdığım andan beri geri dönüşüm yoktu. Bu günü tüm kalbimle bekledim. Endişelenme, her şey güzel olacak.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "Evet.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Evet.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Evet.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Ben, Charles Henry de Maure, Chevalier de Monper, seni, Mary Casper, eşim olarak kabul ediyorum; bugünden itibaren, iyi günde ve kötü günde, zenginlikte ve yoksullukta, hastalıkta ve sağlıkta, ölüm bizi ayırana dek yanında olacağım. Tanrı'nın kutsal yasası uyarınca, Rabbimizin huzurunda bu yemini ediyorum.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Ben, Mary Casper, seni, Charles de Maure, kocam olarak kabul ediyorum; bugünden itibaren, iyi günde de kötü günde de, zenginlikte de yoksullukta da, hastalıkta da sağlıkta da, ölüm bizi ayırana dek yanında olacağıma söz veriyorum. Tanrı'nın kutsal yasasına göre, Rabbimizin huzurunda, bu yemini ediyorum.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amin.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Bu inanılmaz bir şey, di mi? Ben... ağlıyorum, özür dilerim Charles, ben... burnum da kıpkırmızı oldu, değil mi?";
			link.l1 = "Mary de Maure, karım, bugün de her zamanki gibi güzelsin!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "Teşekkür ederim, Charles, teşekkür ederim... Her şey öyle anlamlı ve harikaydı ki! Hayatımın en güzel günü bu, di mi!!! Bak, herkes ne kadar mutlu! Ama artık misafirlerimizle kaynaşıp tebriklerini kabul etme zamanı! İşin bitince geri gel – meyhanedeki çocuklara da bir bakalım.";
			else dialog.text = "Teşekkür ederim Charles, teşekkür ederim... Her şey o kadar anlamlı ve harikaydı ki! Hayatımın en güzel günü bu, di mi!!! Bak, herkes ne kadar mutlu! Ama şimdi misafirlerimizle kaynaşıp tebrikleri kabul etme zamanı! İşin bitince geri gel – Sharptown'da bizi bekliyorlar.";
			link.l1 = "Hemen yaparım, tatlım. Bir öpücük alayım, hemen gidiyorum!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Charles, aşkım, misafirlerimizle konuştun mu?";
			link.l1 = "Henüz değil, tatlım, yakında döneceğim.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Evet, üzerime bu kadar çok 'tebrik' yığılmışlığı hiç olmamıştı. Ve biliyor musun? Çoğu da gerçekten içtendi!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "Evet, evet! Benim için de aynı şey geçerli! Tabii ki, bazıları kıyafetime bayağı şaşırıyor, di mi? Hem de öyle heyecanlıyım ki, insanların söylediklerinin yarısı kulağımdan uçup gitti. Charles, meyhanedeki çocuklar bizi bekliyor – onlara gitmeliyiz. Kaptanlarını kutlamak için çok sevinecekler, di mi!";
				link.l1 = "Şimdi hemen gidiyoruz. Ama... Bu günü meyhanedeki bir odadan daha romantik bir yerde bitirmek isterim. Umarım, karıcığım, bu geceyi kamarada geçirmemize bir itirazın yoktur? Üstelik, artık gemide nöbetçi de yokken...";
			}
			else
			{
				dialog.text = "Evet, evet! Benim için de aynı şey geçerli! Tabii ki, bazıları kıyafetime bayağı şaşırıyor, di mi? Ve ben de öyle heyecanlıyım ki, insanların söylediklerinin yarısı kulağımdan kaçıp gidiyor. Ama Charles, bizi Sharptown'da bekliyorlar. Ne zaman yelken açıyoruz?";
				link.l1 = "Şu anda. Misafirlerimizin tüm erzaklarımızı tüketmesine izin veremeyiz! Umarım, karıcığım, bu geceyi kamarada birlikte geçirmekten rahatsız olmazsın?";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Sen yanımda olduktan sonra, sivrisinek kaynayan bir kulübede, ıssız bir adada geçirsek de umurumda olmaz.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Ben de aynı şekilde hissediyorum. Hadi gidelim, yoksa çocuklar bütün romu içip meyhaneyi yakacaklar.";
			else link.l1 = "Ben de seni seviyorum. O zaman... yelken açalım!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Ah sevgilim, öyle mutluyum ki! Bugün harika bir gün...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Charles, şu pis kafasını kopar!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "İyiyim, di mi! Nathaniel nasıl, hayatta mı?";
			link.l1 = "Çok fazla kan... Dannie, nefes alıyor mu? Nefes aldığını görüyorum!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Daha hızlı, sevgilim, vakit kaybetme!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Kazandık, di mi! Kusura bakma, geciktim. Yukarıda bir düzine alçakla kapıştık. Ellerim doluydu.";
			link.l1 = "Merak etme, burada her şeyi hallettim. Jacques'la olan bu hikayeyi sonunda bitirdiğim için mutluyum... Sonunda, hak ettiğini buldu.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "O zaman Sharptown'a dönelim, di mi? Nathaniel'e bakmamız lazım. O deli adam bizim için hayatını riske attı!";
			link.l1 = "Haklısın, sevgilim. Git, hemen arkandayım.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Bu arada, tatlım, Marcus'u bulduk! Kargo ambarındaymış, bağlı ve baygındı.";
			link.l1 = "Hayatta mı?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Bloody, but he'll heal. You can't break our baron, all right; barely awake and already craving a scrap!.";
			link.l1 = "Ah Marcus, eski dostum! Neyse, kıyıya gidelim.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Üzgünüm Charles, di mi, ben... yürüyüşe çıktım. Senin döndüğünü gördüm, herkesin hayatta olduğunu ve kazandığını duydum ama ben... bana ne oluyor, di mi?!";
				link.l1 = "Her şey yoluna girecek, sevgilim, her şey yoluna girecek. Ben de üzgünüm. Ama kazandık ve Jacques Barbazon yaptıklarının bedelini ödedi.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Gino için, Charles için çok üzgünüm, di mi! Duyduğumda inanamadım!";
					link.l1 = "Ben de inanamıyorum... Günün böyle biteceğini hiç hayal etmemiştim.";
				}
				else
				{
					dialog.text = "Yine kazandık, di mi? Kocam, Kıyı Kardeşliği'nin kendini beğenmiş baronlarına karşı tam bir fırtına! Dostlarımız sağ, düşmanlarımız ölü - olması gereken de bu, di mi?";
					link.l1 = "Başardık, sevgilim. Başardık.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Zar zor ayakta duruyorsun, di mi? Hadi, Dannie bize kenarda bir ev buldu, şu an gemiye dönmek istemiyorum. Oturup kaybettiğimiz dostlarımız için içelim – bunların hepsi ayık kafayla çekilecek gibi değil, di mi.";
			link.l1 = "Evet, Mary, hadi gidelim.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Gino için, Charles için kendimi çok kötü hissediyorum, di mi! Duyduğumda inanamadım!";
				link.l1 = "Ben de inanamıyorum... Günün böyle biteceğini hiç hayal etmemiştim.";
			}
			else
			{
				dialog.text = "Üzgünüm geciktim, sevgilim. Bir yürüyüşe çıktım, sonra seni gördüm ve olabildiğince hızlı koştum! Danielle beni durdurdu, Gino tehlikenin geçtiğini söyleyince. İyi olmana öyle sevindim ki!";
				link.l1 = "Ben de, sevgilim. Ve kazandık. Barbazon öldü, baronlar ise geriye kalan adamlarını topluyor. Savaş bitti.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, ayakta zor duruyorsun! Ve kimse Tichingitu'yu bulamıyor.";
			link.l1 = "Jan gave me a tip... Let's take a walk to Sabo-Matila Cove; a few people saw him heading in that direction.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Bak işte bizim soğukkanlı Kızılderilimiz burada, di mi? Hadi gel, Dannie bize burada, kenarda bir ev buldu - Charles, sen de bitmişsin zaten.";
			link.l1 = "İşte orada ... kaçır beni, güzelim. Ve sabah olduğunda her şey kötü bir rüya gibi gelsin.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "Don't get me wrong, husband; the church was luxurious, but here the atmosphere is so much more soulful, all right. Well... that's all, Charles. All our troubles are behind us. We can relax.";
			link.l1 = "Pek 'hepsi' sayılmaz, karım - hayatımız birlikte devam ediyor! Gelecekte ne olacağını söylemek zor. Hadi, gidelim, tayfalarımızla bir içki içelim, sonra da - hatırlıyorsun: kamarada, şarap ve ikimiz...";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "Kocam... bu kelime ne kadar da hoş geliyor, di mi? Artık sen benimsin, sonsuza dek.";
			link.l1 = "Ben zaten uzun zamandır seninim, şimdi ise sonsuza dek olacağım, aşkım...";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "Çok mutluyum, Charles! Ve artık ne yaparsak yapalım, birlikte yapıyoruz, di mi?";
			link.l1 = "Tabii ki, tatlım! Yan yana, sonsuza dek birlikte!";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Korkarım bu hastalık kızlarına ağır geliyor, Rodrigo. Onları örgüyle falan oyalamaya bak!";
			link.l1 = "Bu konuşma hiçbir yere varmıyor. Yarın kiliseye gideceğimize karar verdik - tabii ki dua etmek için.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Seninle gurur duyuyorum, aşkım!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Charles...";
			link.l1 = "Aklından ne geçiyor, Mary?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "(gülerek) Benimle Alan'ın, burada senin yaptığını Adalet Adası'nda yapmak istememiz ne tuhaf, di mi?";
			link.l1 = "Senin... Alan?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Gerçekten tam bir hayalperestti - yaşasaydı, ikiniz de çok iyi arkadaş olurdunuz.";
			link.l1 = "Bir konuda kesinlikle zevklerimiz aynı...";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Ne? Ha-ha-ha! Ah, sus artık Charles!\nHer halükarda, bu harika... Bu insanlara ne kadar çok mutluluk verdik!";
			link.l1 = "We gave them a chance; the rest, they've done on their own. So... what are you thinking?";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "Sonra gel, öğrenirsin...";
			link.l1 = "Tabii ki yapacağım!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Karanlık ve dar yerleri severim. Beni sakinleştiriyor. Sonunda düşüncelerimi toparlayabiliyorum\nSanki bütün dertlerim... bir anda yok oluyor! Bu hissi özlemişim...";
			link.l1 = "Bir doktora görünmelisin.";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Sanki tekrar Ceres'tesin.";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "... Too bad I'm not alone. In silence, in darkness, in solitude, aye; that would be perfect.";
			link.l1 = "Hayal kurmaya devam et, Mary Casper.";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "Bir keresinde yatağıma bir yengeç girdi - onu parçaladım ve yedim.";
			link.l1 = "Hayal kurmaya devam et, Mary Casper.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Maskeli pislik! Ah! Yardım et bana, sevgilim – şu parmaklıkları kırmamız lazım!";
			link.l1 = "Sessiz ol! Ne yapacağımı anlamaya çalışıyorum!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Sevgilim, bu maskeli herifler her yerdeler! Gövdeyi delip içeri sızdılar, yengeç gibi dolanıyorlar! Hepsini biçmemiz lazım, di mi?";
			link.l1 = "Mary, burada kal, komutayı devral! Gemiyi çatışmadan uzaklaştır - bir saldırıya daha dayanamayız!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Ve nereye gidiyorsun? Seni bırakmaya hiç niyetim yok!";
			link.l1 = "Hercule ve tayfamıza yardım etmem gerek! Bana güven, Mary!";
			link.l1.go = "tonzag_after_boarding_2";
		break;

		case "tonzag_after_boarding_2":
			dialog.text = "Tabii tabii, sevgilim!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Zafer! Gel buraya, sevgilim! Seni bir iki saatliğine istiyorum.";
			link.l1 = "Ah...";
			link.l1.go = "tonzag_after_victory_1";
			link.l2 = "Hadi gidelim!";
			link.l2.go = "tonzag_after_victory_1";
		break;

		case "tonzag_after_victory_1":
			dialog.text = "Hey, Hercule! Seni görmek ne güzel, ak sakal!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

		case "tonzag_after_victory_2":
			dialog.text = "";
			link.l1 = "Mary! Mary, bekle! Raporuna ihtiyacım var!";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "Ha? Eee, kazandık, di mi? O lanet gemi kaçtı. Bir herifin kafasını ikiye yardım!\nOf, şu düğmeler yok mu!";
			link.l1 = "Oh, Mary...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Aman Tanrım, bana bakma, sevgilim! Ben şimdi... of!";
			link.l1 = "Dayan, kızım. Ben buradayım!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! Seninle konuşmam lazım, di mi? Cidden!";
				Link.l1 = "Ne oldu, Mary? Bir sorun mu var?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Dinliyorum, sevgili kaptanım!","Evet, "+pchar.name+", Kulak kesildim!","Benim için bir işin var mı, "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mary, eski Maya şehri Tayasal’a gideceğim. Sana yalan söylemeyeceğim: bu yolculuk çok tehlikeli ve dahası, sana bahsettiğim o putu kullanmamı gerektiriyor. Benimle... gelir misin?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary, bana tam bir rapor ver.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Her limana yanaştığımızda belirli malları satın almanı istiyorum.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Mary, sana danışmam lazım.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Mary, sana bir görevim var...";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("Sevgilim, seni şu anda istiyorum. Buna hazır mısın, di mi?","Mary, bir süre... beraber kalsak nasıl olur? Sadece ikimiz.");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Mary, bir oda kiralayıp birlikte kalalım mı, di mi?","Aşkım, seninle baş başa kalmak istiyorum... ne dersin, bir oda kiralayıp her şeyi birkaç saatliğine unutalım mı?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "Bir şey değil, Mary.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, tam bir güzellik, di mi! Su hattının altındaki deliği kapattık ve yelkenleri kuruttuk. Ne bekliyordun ki? Bana öyle bakma, ben kambiyo memuru olacak değilim ki.";
			Link.l1 = "Üzgünüm Mary, gerçekten hiç düşünmemişim.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Charles, iyiyim! Paltomu ve bıçağımı çoktan aldım bile. Ama sorduğun için teşekkür ederim, çok naziksin, di mi!";
			link.l1 = "Ama ben bile... Neyse, boşver, canım, biz iyiyiz.";
			link.l1.go = "exit";
		break;

		case "stay_follow":
            dialog.Text = "Emirler?";
            Link.l1 = "Burada dur!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Beni takip et ve yetişmeye çalış!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Mary, ateşli silahlar için mühimmat değiştir.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Mermi türünü seçmek:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Hemen, aşkım!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Hemen, aşkım!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
