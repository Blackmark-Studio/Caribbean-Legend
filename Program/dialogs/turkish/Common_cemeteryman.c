// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Kasaba alarmda. Görünüşe bakılırsa, benim de silaha sarılma vaktim geldi...","Bütün kasabanın muhafızları peşinde değil mi? Askerler, bana!","Burada barınacak yer bulamazsın. Ama kaburgalarının altına saplanacak birkaç santim soğuk çelik bulursun!"),LinkRandPhrase("Ne istiyorsun, alçak herif?! Şehir muhafızları zaten peşinde, fazla uzağa gidemezsin, "+GetSexPhrase("pislik korsan!","alçak")+"!","Dur! "+GetSexPhrase("Pis katil! Muhafız!!!","Senden korkmuyorum! Yakında kalemizde asılacaksın, saklanacak bir yerin yok...")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Yaşamaktan bıkmış gibisin...","Ve neden barış içinde yaşamak istemiyorsunuz, vatandaşlar..."+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Cehenneme git!","Bu dünyada senin için sadece birkaç saniye kaldı..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "A-a-ah! Ah, sensin... Sen kimsin? Mezarlığa ne getirdi seni?";
				link.l1 = "Benim adım "+GetFullName(pchar)+". Peki sen kimsin, burada ne yapıyorsun? Ve neden bu kadar korkmuş görünüyorsun?";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "Peki, nasıl geçti? Gördün mü? Şimdi bana inanıyor musun?";
				link.l1 = "Hayır, henüz mahzene inmedim. Biraz daha bekle, her şeyi kontrol edeceğim.";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "Peki? Göz attın mı? Gördün mü?";
				link.l1 = "Evet, yaptım! Haklıydın!";
				link.l1.go = "Lantern_10";
				link.l2 = "Beklediğin gibi değildi.";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Merhaba, denizci! Benim adım "+GetFullName(npchar)+", ve burada yaşayan tek ruh benim. Aslında, hepimiz yine de öleceğiz, ha-ha-ha! Neden geldin?","Merhaba! Uzun zamandır canlı bir insan görmemiştim... Kendimi tanıtmama izin verin - "+GetFullName(npchar)+", ve bu mezarlık benim son sığınağım. Görünüşe göre buraya gömüleceğim. Size nasıl yardımcı olabilirim?");
				link.l1 = "Merhaba, "+npchar.name+"! Benim adım "+GetFullName(pchar)+", ve ben bir kaptanım. Ormanda yürüyüp buraya geldim. Bu rahat evde kim yaşıyor, kim bu kadar cesurmuş diye bir bakayım dedim...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, eski dostum, Kaptan "+GetFullName(pchar)+" ! Buyurun, buyurun!";
				link.l1 = "Hoş geldin, dostum! Seni görmek ne güzel. Hiç geceleri dans eden iskeletler ve gözlerinde bakır paralar olan ölüler görüyor musun rüyalarında?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ve neden korkacakmışım, kaptan? Korkmamız gerekenler yaşayanlar, ölüler değil — onlar ısırmaz. Eh! Bir zamanlar bambaşka bir hayatım vardı, şimdi ise bu mezarlığın bekçisiyim. Mezarlarla ilgileniyorum. Bazen de tuhaf eşyalarla ticaret yaparım...";
			link.l1 = "Ne tür mallarla ticaret yapıyorsunuz, söyler misiniz lütfen?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "Bu sefer seni bana ne getirdi?";
			link.l1 = "Bugün satılık neyin var, göster bakalım.";
			link.l1.go = "trade";
			link.l2 = "Sana bir soru sormak istiyorum...";
			link.l2.go = "quests";
			link.l3 = "Önemli bir şey yok. Sadece seni selamlamaya geldim.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Boş vaktim çok, bu yüzden ormanda dolaşıp işe yarar bitkilerle ilginç taşlar toplamayı seviyorum. Sonra onları kasabada satıyorum. Pek para etmeseler de, hiç yoktan iyidir. Bir de arkadaşlarımdan türlü türlü şeyler alıyorum...";
			link.l1 = "Arkadaşlar mı? Yani, başkalarının getirdiklerini tekrar mı satıyorsun?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "O-ho-ho... Hayır, bana her şeyi bedavaya veriyorlar. Mezarlık bekçisiyle ölülerden başka kim arkadaş olur ki?";
			link.l1 = "Ne... Ölülerin cesetlerini mi soyuyorsun?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "I don't rob; I just take things off those who don't need them anymore. Many different people are buried here-some unknown and not from our lands. The commandant brings a dead body from the town and says: 'This is for you, "+npchar.name+", send him on his final journey.' Homeless, hanged pirates, bandits killed by guardians-all are buried here. And old "+npchar.name+" buries their bodies on a Christian custom.";
			link.l1 = "Anladım. Para paradır, neyin var göster bakalım.";
			link.l1.go = "trade";
			link.l2 = "Anladım. Gitmem gerek. Sizinle tanışmak bir zevkti.";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Ve sen, "+GetFullName(pchar)+", sen bir hırsızsın! Muhafızlar!!!","Ne oluyor be! Bir an gözümü çevirdim, hemen bana ait olana el uzatmaya kalkışmışsın! Yakalayın şu hırsızı!!!","Gardiyan! Soygun!!! Hırsızı yakalayın!!!");
			link.l1 = "Vay canına!!!";
			link.l1.go = "fight";
		break;
		//belamour квест на получение фонаря -->
		case "Lantern_01":
			dialog.text = "Vay, demek sadece bir yolcusun... Benim adım "+GetFullName(npchar)+", ben bu lanet olası yerin bakıcısıyım.";
			link.l1 = "Neden mezarlık hakkında böyle hissediyorsun? Tam tersine, Rabbimiz buradan, gömülmelerinin ardından doğru insanları yanına alır.";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "Fakat anlaşılan, günahkârlar gömüldükten sonra bile burada kalıyor! Son birkaç gecedir, mahzenden tuhaf sesler geliyor. O inlemeler öyle ürkütücü ki tüylerim diken diken oluyor... Sanki kayıp bir ruh huzur bulamıyor! Artık sadece gündüzleri uyuyorum - geceleri ne nöbet yerimi terk edebiliyorum ne de gözümü kırpabiliyorum...";
			link.l1 = "Sesler mi? İnlemeler mi? Ama orada ölülerden başka kimse yok.";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "Ben de tam olarak bunu söylüyorum, anlıyor musun? Hayalet seni fark etmeden buradan gitmen en iyisi... Yoksa benim gibi uykusuz kalırsın.";
			link.l1 = "Hm, evet, sanırım buradan ayrılmam daha iyi olur.";
			link.l1.go = "Lantern_04";
			link.l2 = "Belki sana yardımcı olabilirim? Bu gece o garip seslere bir bakayım.";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "Akıl sağlığını mı yitirdin?! Silahın olduğunu görüyorum, ama onunla ölülerle nasıl savaşmayı düşünüyorsun? Ya orada ölürsen ne olacak? Hayalet serbest kalacak ve belki de seni kendi hizmetkârı olarak diriltecek!";
			link.l1 = "Eh, bu sadece batıl inanç...";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "Hangi batıl inanç? Burası lanet olası Avrupa'nın dindar toprakları değil... Yerliler, o kızıl derililer, her şeyi ortaya çıkarabilirler - ve şimdi burada yaşamak zorundayız!";
			link.l1 = "Yine de deneyeceğim. Gece olunca mezara ineceğim.";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "Peki, ne istiyorsan yap. Ama şafak vakti dönmezsen, her şeyi kilitleyip barikat kurarım ve buradan tek başıma kaçarım! Güverteyi temizleyen bir denizci ya da iskelede sandık taşıyan bir hamal olsam da, buraya bir daha asla dönmem!";
			link.l1 = "Sakin ol... Her şey yoluna girecek.";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "Bekle... Şu feneri al. Yedek bir tane var bende. Orada ihtiyacın olacak. Zifiri karanlık!";
			link.l1 = "Teşekkürler, böyle bir yerde fener gerçekten işe yarar.";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			Log_Info("'Lantern' received");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "Değil mi? Orada ne vardı? Anlat!";
			link.l1 = "Bir kadının huzursuz ruhu vardı! Neyse ki, yerel rahibe kılıcımı kutsattım, böylece kötülüğü alt edebildim ve her şey yoluna girdi. O ruh artık seni rahatsız etmeyecek.";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "Ey Rabbim, günahkâr ruhlarımızı kurtar! Seni uyardım! Ama bana inanmadın!";
			link.l1 = "Evet, ve bunu gerçekten çok üzgünüm. Ama şimdi her şey yolunda – burayı kutsal suyla serptim, artık hiçbir ruh mezarından kalkmaya cesaret edemez. Artık rahatça uyuyabilirsin.";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "Çok teşekkür ederim! Bunun benim için ne kadar önemli olduğunu bilemezsiniz! Buyurun, lütfen bunu alın. Çok değerli değil ama sizi ödülsüz göndermek istemem.";
			link.l1 = "Teşekkür ederim, reddedemem. Sana bol şans!";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "Hayır mı? O zaman ne halt... Yani, Tanrı aşkına, orada ne oldu?";
			link.l1 = "Hiçbir hayalet yokmuş. Genç bir çift, buluşmak için bu mezar odasını seçmiş. Aileleri bu birlikteliğe karşı olduğu için yalnız kalabilecekleri bir yer arıyorlarmış.";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "Yalnız mı?.. Şu veletler yok mu! Bir daha buraya gelmeye kalksınlar, ya kırbacımla kovarım ya da ikisini de mahzene kilitlerim, orada kalsınlar!!!";
			link.l1 = "Artık buraya bir daha gelmeyecekler. Onlara, küçük kaçamaklarının buradaki muhafızları gerçekten korkuttuğunu söyledim. Zaten öyle olmasını istemişlerdi. Bu arada, kapının kilidi de zaten bozuk.";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = " Sorun değil, onu değiştiririm. Ama onları bir gün yakalarsam... ";
			link.l1 = "Bu kadar sinirlenme. Hepimiz o yaşlardan geçtik. Buraya gelmelerinin sebebi flört etmek için en iyi yer olması değildi.";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "Eh, peki... Neyse, Tanrı onlarla olsun. Bir yaşlıyı darda bırakmadığın için teşekkür ederim. Al, lütfen bunu kabul et. Çok bir şey değil ama seni ödülsüz göndermem doğru olmazdı.";
			link.l1 = "Teşekkür ederim, reddedemem. Sana da bol şans!";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря 
	}
}
