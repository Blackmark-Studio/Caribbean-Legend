// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "Kaptan! Denize açıldın, duydum! Ne oldu? Bir şeyler öğrendin mi? Lütfen, anlat, hadi söyle!";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "Hayır, güzelim, bu baskın Valinin emriyle yapıldı. Çok üzgünüm ama Angelo kalenin zindanlarında öldü – artık bunda hiç şüphe yok. Güçlü ol! ";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "Haklıydın. Kardeşin kaçırılmış. Komutan, mahkumları sanki hayvanmış gibi Tüketim lakaplı bir köle tacirine satıyormuş. Ama ben onun gemisini yakaladım, şimdi o denizin dibinde yatıyor ve kardeşin Angelo yakında karaya çıkacak. Ne yazık ki, tüm yolcuları aynı anda karaya çıkaracak kadar sandalım yok. ";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "You were right. Your brother was kidnapped. The Commandant had been selling prisoners like cattle to a slaver nicknamed Consumption. But I caught up with his ship; although I failed to kill that bastard, your brother Angelo will come ashore soon. Unfortunately, I do not have enough longboats to bring all the passengers ashore at once. ";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "Angelo'nun akıbeti hakkında bir şey öğrenebildiniz mi, kaptan?";
				link.l1 = "Henüz değil. Ama yakında haberlerim olacak gibi. Sadece beklemen gerekiyor. ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "Señor, kardeşimi bulacağına söz vermiştin... Neden burada içki içerek vakit kaybediyorsun?";
			link.l1 = "Ohh... Evet, doğru... hık... Sakin ol, kızım... İsa her şeyi kontrol ediyor... 'şlap'... İsa her şeyi kontrol ediyor. Ben zaten gitmişim... hık...";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "İyi günler, señor. Burada ne işiniz var?";
			link.l1 = "Señor komutan için bir mesaj getirdim, ama onu bizzat kendisine teslim etmeliyim.";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "O zaman kalede onu aramaya git.";
			link.l1 = "Bu mesaj çok önemli ve askerlerin gözleri ya da kulakları için değil. Belki de çok erken geldim ama burada onu bekleyebilirim. Bana güven, bu gerçekten çok önemli!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
			{
				notification("Skill Check Failed (40)", SKILL_SNEAK);
				dialog.text = "Señor Komutan genellikle rutinde değişiklik gerektiren tüm önemli konularda beni uyarır... Aslında, bu özel durum hakkında da beni uyarmıştı.";
				link.l1 = "Ve ne dedi?";
				link.l1.go = "Servant_3";
			}
			else
			{
				notification("Skill Check Passed", SKILL_SNEAK);
				dialog.text = "Pekala, sana inanıyorum. Ve sözlerini doğrulamak için señor komutan geldiğinde sana daha da çok inanacağım. Ama o zamana kadar, gözümü sürekli üzerinde tutacağım.";
				link.l1 = "Beni istediğin kadar izleyebilirsin...";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "Böyle durumlarda garnizon muhafızlarını çağırmamı söyledi. Ama muhtemelen kendi başımıza hallederiz. Çocuklar! Onu gebertelim!";
			link.l1 = "Siktir!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "Daha ne istiyorsun? Mesajı bana vermeye karar verdin mi?";
			link.l1 = "Hayır, komutanı bekleyeceğim...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "Sen bir hırsızsın! Yoksa bir casus musun? Arkadaşlar, aşağıya, çabuk!";
			link.l1 = "Ah, şeytan!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "Affedersiniz, sizinle konuşabilir miyim?";
			link.l1 = "Açıkçası, acelem var. Ne istiyorsun?";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "Senin, hapishanemizdeki Juan adında bir adam ve bir hastalık hakkında soruşturduğunu duydum...";
			link.l1 = "Evet, yaptım... kendini açıklayabilir misin?";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "Sakin ol, sakin ol! Sakinleş ve kılıcına dokunma! Burada aynı taraftayız! Neden bizim sorunlarımızla ilgilendiğini bilmiyorum ama buna bir son verilmeli! Artık daha fazla susamam!";
			link.l1 = "Susmak mı? Neyden bahsediyorsun? Verem hakkında ne biliyorsun?";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "Her şeyi olmasa da çoğunu biliyorum ve kendimi açıklayacağım – ama burada değil. Akşam, ışıklar söndüğünde buluşalım. Ben bir sağlık görevlisiyim, bu yüzden kaleden çıkmama izin var. Şehir kapılarının dışında buluşacağız ve sana her şeyi anlatacağım. Ne olur – daha fazla soru sorma, onların dikkatini çekmeden önce, ya da belki çoktan çekmişsindir... Şimdi gitmeliyim. Unutma, gece, şehir kapılarının dışında.";
			link.l1 = "Pekala, orada olacağım. Hey! Bekle...";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "Tanrıya şükür, geldiniz... Umarım sizi kimse takip etmedi?";
			link.l1 = "Neden? Sen çok şüphecisin, belki komutan señor'dan bile fazla, o yüzden en iyisi konuya geçelim... Juan hakkında ne biliyorsun?";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "Benim adım Sergio Saldo. Kalemizde sağlık görevlisi olarak çalışıyorum ve...";
			link.l1 = "";
			link.l1.go = "Sergio_6_1";
		break;
		
		case "Sergio_6_1":
			dialog.text = "";
			link.l1 = "Bekle! Bunu duydun mu?";
			link.l1.go = "Sergio_7";
			Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73)
		break;
		
		case "Sergio_7":
			dialog.text = "Ne?! Nerede?";
			link.l1 = "Lanet olsun, burada yalnız değiliz... Kimi getirdin yanına, pislik?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "Bizi fark ettiler! Sen doktoru al, ben de diğerini alırım!";
			link.l1 = "...";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "Kılıcını indir, bitti artık! Gördün işte, beni de öldürmeye çalıştılar!";
			link.l1 = "Pekâlâ, bu iş biraz fazla karmaşık görünüyor, yani onlarla işbirliği yapmıyorsun. Nerede kalmıştık? Sen bir hapishane doktorusun, değil mi?";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "Evet. Hapishanenin doktoruyum. Gençken tıp okudum, burada eğitimli insan pek yok. O yüzden hapishanede neler olup bittiğini herkesten iyi bilirim!";
			link.l1 = "Ne oluyor peki? Mahkumlara ne oldu? Birdenbire ortadan kaybolmaları hakkında bir şey biliyor musun?";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "Komutanımız onları satıyor... onları sanki hayvan gibi, Juan adında bir köle tacirine satıyor. Kimsenin aramayacağı kişileri seçiyor - yoksulları, rastgele gemilerden denizcileri. Sonra da aniden 'veremden öldüler' deniyor - gerisini sen anlarsın...";
			link.l1 = "Demek ki Juan da insanmış, sonunda! Onun hakkında ne biliyorsun?";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "Biraz. Eskiden Fas'ta Berberi korsanlarla beraber pis işlerini yapardı, arada bir uğradığında o zamanlardan hikayeler anlatmayı sever. Lakabını da orada aldı - Verem. Nereden geldiğini düşünmek bile istemem\nHer ay buraya gelir ve tüm esirleri gemisine alır.";
			link.l1 = "'Tüketim!' Ve bana alaycı diyorlardı! Demek bu yüzdenmiş... Şu senin komutan tam bir ahmakmış!";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "Anladığım kadarıyla, kayıp mahkumlar arasında birini arıyorsun, yoksa bu hikayeden nasıl haberin olabilirdi, değil mi? Eğer öyleyse, acele etmelisin: bu ayın son gecesi bu gece. Üç kişinin daha ölümünü bildiren evrakları çoktan imzaladım, ve Juan onları teslim aldığında yarın öğleden önce demir alacak!";
			link.l1 = "Ne imzaladın? Seni tam olarak anlayamıyorum...";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "Bunu yapmak zorundaydım - zaten birkaç aydır yaptığım gibi! İşte bu yüzden buraya gelip buna son vermek istedim. Doktor Pinero'nun nasıl öldüğünü biliyor musun? Hani benden önce mahkumlarla ilgilenen doktor?";
			link.l1 = "Sanırım bana veremden öldüğü söylendi, değil mi? Yani, buna mecbur bırakılmışsınız. Bu mantıklı – ama neden kimse bu konuda yetkililere başvurmadı?";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "Buna kim inanır ki? Hiçbir kanıtım yok, üstelik mahkumları koruması gereken askerler de bolca para alıyor, yani insanları Karayiplilere yemek diye satsalar bile umurlarında olmaz\nKimsenin mahkumlarla ilgilendiği yok, bu da komutanın elindeki en büyük koz. Ama en azından bir süreliğine bunu durdurabilirsin, Juan'ı ortadan kaldırarak!";
			link.l1 = "Anladığım kadarıyla, karadaki o adamlar onun adamlarıydı, değil mi? Ona nasıl ulaşabilirim?";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "Muhtemelen sorularınla birinin dikkatini çektin... Sana daha dikkatli olmanı söylemiştim! Ama şimdi bu önemli değil. Juan'ın gemisi hakkında hiçbir şey bilmiyorum, ama mahkumlar her zaman adanın kuzeyindeki Galera Noktası'na gönderilir. Sanırım köle tacirinin gemisi de yakınlarda olmalı ve ona yetişebilirsin. Haberci adamları bugün, yarın öğle vakti yelken açacağını söylediler.";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "Teşekkür ederim, Sergio, sen gerçek bir subay ve onurlu bir adamsın. Şimdi hemen demir alacağım ve şu pis gemiyi bulacağım. Sen de onlar seni aramaya başlamadan önce kaleye dönmelisin.";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "Peki, bilmem gereken her şey bu. Eğer o 'Consumption'ı tüm Yeni Dünya'da aramak istemiyorsam hemen demir almam gerek. Bu arada, sen de bunu inceleyebilirsin.";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "İyi şanslar, kaptan! Benim için endişelenme - en önemlisi bunu, en azından bir süreliğine, durdurmak. Sana bol şans diliyorum!";
			link.l1 = "Toplarım hastalığa ve kötülüğe en iyi çaredir. Yemin ederim, tüm esirler şafak sökmeden karada olacak – ve Juan’ın gemisi denizin dibini boylayacak!";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("You have given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ne oldu? Burada albayın adı ve bir 'J' monogramı var mı? İnanılmaz! Bunu nereden buldun?";
			link.l1 = "Bunu bilmesen daha iyi, ama sana güveniyorum, en iyi şekilde kullanırsın.";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "Yemin ederim, kutsal olan her şey üzerine! Albay ay sonundan önce darağacına gidecek! Bununla bizzat ilgileneceğim!";
			link.l1 = "Korkarım ki bu iş disiplin cezasıyla sonuçlanacak, ki gördüğüm kadarıyla bu onun hayatındaki ilk ceza olmayacak. Belki de o köpeği vurmak daha iyi olur? Oldukça etkili bir çözüm... Şimdi gitmem gerek - 'Consumption'ı bekletmek istemem.";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "Ah, ne şanslı bir karşılaşma! Señor "+GetFullName(pchar)+"! Seni gördüğüme çok sevindim!";
			link.l1 = "Señor Sergio! Sizi burada göreceğimi hiç beklemiyordum! Nasılsınız? Eski komutan nasıl?";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "Ben iyiyim, ve señor komutan Los-Teques madenlerine gitti - Juan Consumption ile yaptığı pis düzenbazlıkları ortaya çıktı.";
			link.l1 = "Mayınlar mı?! Allah aşkına! Onun davasında adaletin yerini bulacağı hiç aklıma gelmezdi...";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "Ah, keşke öyle olsaydı, kaptan... Sadece başka yere gönderildi ve rütbesi düşürüldü. Şimdi garnizonda görev yapıyor, hem de subay rütbesi bile alınmadı. Neyse ki, en azından San Jose bu pislikten kurtuldu.";
			link.l1 = "Pekâlâ, şimdilik fena gitmiyor. Yine de daha fazlasını beklemiştim.";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "Ben de... Ama o pisliği unutalım - hakkında konuşmaya bile değmez. Señor, geminizin limana yanaşmak üzere olduğunu duyar duymaz, aceleyle iskeleye koştum. Size bir teklifim var.";
			link.l1 = "Gerçekten mi? Dinliyorum.";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			dialog.text = "Kaptan, güvenilebilecek birine benziyorsunuz. Bir diğer önemli şey de, sizin "+GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"")+" ve kendi geminiz var. Size bir ticaret anlaşması yapmamızı öneririm.";
			link.l1 = "Kulağa umut verici geliyor! Ne tür bir anlaşma?";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "Bunu başka bir yerde konuşsak iyi olur – deniz fenerinde, bekçinin kulübesinde. O eski bir dostumdur ve ona güvenirim. Bugün ya da yarın San Jose'deki deniz fenerine gel. Orada seni bekliyor olacağım. Teklifimi oldukça ilginç bulacağına eminim!";
			link.l1 = "Pekala, señor Sergio. Orada görüşürüz!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "Tekrar hoş geldiniz, señor. Size bu meseleyi açıklamama izin verin. ";
			link.l1 = "Tamamen dinliyorum. ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "As you may already know, I am not only a soldier, but also a doctor. Why? Because I am a well-educated man. My education kept me from wasting my time here on women and drink. Instead, I have organised several expeditions and managed to find a deposit of resin not far from here\nThis is a resource of strategic importance; this island is the only place where you can find the special resin used to build solid and lasting vessels\nA governor and a commandant ordered me to sell all the resin to the Spanish navy\nThe problem is, they pay me only half its market price and I can't sell it anywhere else. Therefore, I offer you the chance to buy it from me. It is a very important commodity and very hard to come by.";
			link.l1 = "Anlaşmamızın şartları nedir? ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "Hesaplarıma göre, şüphe çekmeden ayda 60 varil toplayabilirim. Anlaşma yapalım – her ayın beşinde, bu deniz fenerine gelip arkadaşımla bir içki içerim. Reçineyi almak istersen sen de katıl bize. Varili on altın doblon.\nTüm partiyi peşin ödersin ve hepsini bir seferde alırsın. Zorlama yok, karar senin. Ne dersin, anlaştık mı?";
			link.l1 = "Bana göre bu lanet olası iyi bir anlaşma! Tabii ki, anlaştık!";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "Harika. O zaman her ayın beşinde eski dostum, bekçiyle birlikte bir şişe Kanarya şarabı içeriz ve seni bekleriz.";
			link.l1 = "Pekâlâ. O şekilde yapalım.";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "Anlaştığımıza sevindim. Görüşürüz, kaptan!";
			link.l1 = "Reçine işinizde bol şanslar, señor!";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecordInfo("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "Merhaba, señor kaptan! Sanırım bir parti reçine almaya geldiniz.";
			link.l1 = "Doğru, señor Sergio. Her şey hazır mı?";
			link.l1.go = "oil_trade_1";
			link.l2 = "Señor Sergio, şu an ticaret yapacak havamda değilim. Belki sonra.";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			{
				dialog.text = "Evet. Yanında 2550 dublon var mı?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Tabii. Buyurun.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Şanssızlık! Parayı gemimde bıraktım. Hemen buraya getiririm!";
					link.l1.go = "oil_trade_exit";
				}
			}
			else
			{
				dialog.text = "Evet. Yanında altı yüz doblon var mı?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Tabii. Buyurun.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Şanssızlık! Parayı gemimde unuttum. Hemen getiririm!";
					link.l1.go = "oil_trade_exit";
				}
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // увеличить объём поставок смолами
			{
				link.l4 = "Señor Sergio, daha fazla reçine almak istiyorum. Mesela, beş kat daha büyük partiler sağlayabilir misiniz?";
				link.l4.go = "UpgradeOil";
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок смолами, если в первый раз не принесли
			{
				link.l4 = "İşte, söz verdiğim gibi, Señor Sergio, istediğiniz gibi üç bin doblon. Sizin öngörünüz ve benim yatırımımla, bu girişimin ikimize de hatırı sayılır bir kâr getireceğinden eminim.";
				link.l4.go = "UpgradeOil_Agreed";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "Sizinle iş yapmak bir zevk, kaptan. Adamlarım varilleri geminize yüklemenize yardımcı olacak.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "Anlaşmamız hâlâ geçerli. Eğer bir parti daha istersen, bir ay sonra tekrar gel.";
			link.l1 = "Pekala, Sergio. Görüşürüz.";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) AddCharacterGoods(pchar, GOOD_OIL, 300);
			else AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // счётчик покупок
		break;
		
		case "UpgradeOil":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Señor"+GetSexPhrase("","ita")+", daha fazla reçine satın alma isteğiniz işimize olan güveninizi gösteriyor. Ancak, bir sorun var\nDaha büyük miktarlarda alışveriş yapmak, ada yetkililerinin dikkatini çekme riskini artırıyor ve bu tür sevkiyatları kontrol etmek için insan gücü ve güvenlik önlemleri gerekiyor ki, itiraf etmeliyim, bunlar ucuz değil. Eğer fiyata bir defaya mahsus olmak üzere üç bin dublon eklemeye razıysanız, yükü koruyacak ve bilgi sızıntılarını önleyecek güvenilir adamlar tutarım. O zaman rotamız daha güvenli olur ve size her ay üç yüz varil reçine tedarik edebilirim. Yatırımınızı telafi etmek için, toptan alıcı olarak size tüm gelecek sevkiyatlarda yüzde on beş indirim sunacağım.";
				link.l1 = "Señor Sergio, üç bin dublon karşılığında sevkiyatları güvenceye almak mı? Saklamayacağım, bu fiyat bana inanılmaz geliyor – sanki sadece bir katran yükünü korumak değil de, Escorial'de bir komplo teklif ediyorsunuz!";
				link.l1.go = "UpgradeOil_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Señor"+GetSexPhrase("","ita")+", ilginiz için teşekkür ederim, ancak bu kadar büyük anlaşmalar deneyim ve dikkat gerektirir. Açık konuşmak gerekirse, ticaret konusundaki seviyeniz henüz bu hacmi kaldıracak kadar yüksek değil. Size biraz daha tecrübe kazanıp, daha büyük sevkiyatlara hazır olduğunuzda bana dönmenizi tavsiye ederim. O zaman belki bu konuyu etraflıca konuşabiliriz.";
				link.l1 = "Pekala. Bu soruya sonra döneriz.";
				link.l1.go = "oil_trade_exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeOil_1":
			dialog.text = "Señor"+GetSexPhrase("","ita")+", endişenizi anlıyorum. Ama biliyorsunuz, güvenlik hiçbir zaman ucuz değildir, hele ki bu kadar nadir mallar söz konusuysa. Üstelik sadece gizliliği garanti etmiyorum, aynı zamanda zamanla yatırımınızı telafi edecek bir indirim de sunuyorum. Bu makul bir uzlaşma değil mi?";
			link.l1 = "Kabul ediyorum: bizim işimizde güvenilirlik ve gizlilik pahalıya mal olur, indirim de anlaşmamızı bir nebze cazip kılıyor. Ama yine de, üç bin dublon çok yüksek bir meblağ. Belki biraz daha indirebilirsiniz?";
			link.l1.go = "UpgradeOil_2";
		break;
		
		case "UpgradeOil_2":
			dialog.text = "Üzgünüm, ama böyle konularda yarım önlemler kabul edilemez. Ya tam koruma sağlarız, ya da her şeyi riske atarız. Tutar değişmiyor, ancak bu şekilde güvenilirlik ve gizlilik garantisi verebilirim. Önce beni, sonra da sizi tüm kraliyet filosunun peşine düşmesini istemezsiniz, değil mi?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Pekâlâ, Señor Saldo, beni ikna ettiniz. Güvenlik ve güvenilirlik değerini hak ediyor. Üç bin dublon. Buyurun.";
				link.l1.go = "UpgradeOil_Agreed";
			}
			link.l2 = "Señor Saldo, beni bu önlemlerin gerekliliğine ikna ettiniz. Ancak, üç bin doblon oldukça yüklü bir meblağ ve şu anda o kadar param yok. Gerekli miktarı toparlayana kadar beklemem gerekecek.";
			link.l2.go = "UpgradeOil_4";
			link.l3 = "Böylesine bir parayla, tüm bir filoyu ve kıtadaki bütün askerleri bile satın almak mümkün, bırakın bir varil zift için birkaç koruma tutmayı! Kusura bakmayın, ama böyle bir teklifi kabul edemem. Her şeyi olduğu gibi bırakalım, ne fazlası ne de gereksiz masraf olsun.";
			link.l3.go = "UpgradeOil_3";
		break;
		
		case "UpgradeOil_Agreed":
			dialog.text = "Pekala, señor, görüyorum ki güvenimiz karşılıklı. İçiniz rahat olsun: her şey gerektiği gibi ayarlanacak. Şimdi ayrıntılara gelelim: her zamanki gibi, 300 varil reçine her ayın 5'inde burada Trinidad fenerinde sizi bekliyor olacak. Tüm partiyi 2550 dublona satın alabilirsiniz.";
			link.l1 = "Harika, Señor Sergio. Beni hayal kırıklığına uğratma.";
			link.l1.go = "UpgradeOil_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "4_1");
			pchar.questTemp.UpgradeOil = true;
			pchar.questTemp.SergioOilBlock = true;
			DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;
		
		case "UpgradeOil_Agreed_1":
			dialog.text = "Hiç şüpheniz olmasın, señor"+GetSexPhrase("","ita")+"Her şey en üst düzeyde organize edilecek ve ortak çabamız meyvesini verecek.";
			link.l1 = "Görüşürüz.";
			link.l1.go = "oil_trade_exit";
		break;
		
		case "UpgradeOil_3":
			DialogExit();
			pchar.questTemp.SergioOilBlock = true;
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "UpgradeOil_4":
			dialog.text = "Tüm parayı getirdiğinde geri gel. Seninle yeni bir anlaşma yapmaktan memnuniyet duyarım.";
			link.l1 = "Peki.";
			link.l1.go = "oil_trade_exit";
			pchar.questTemp.SergioOilBlock = true;
			pchar.questTemp.SergioOilPotom = true;
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "Sen de kimsin be!?";
			link.l1 = "Benim adım "+GetFullName(pchar)+", sana gelince, Consumption, şeytan seni bekliyor – ve ruhunu çok yakında alacak!";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "Bu gemi patlamak üzere – barut odasında fitil çoktan yanıyor – neden ikimiz de ölelim? Kılıçlarımızı bırakalım. Çıkmak için yeterince vaktin olacak, ben de denize atlarım – Galera Burnu buradan tükürük mesafesinde. Altın istiyorsan, al! Beş yüz doblon, peşin para – sen beni unutursun, ben de seni! Anlaştık mı?";
				link.l1 = "Altın mı? Tüm bunlara para için başlamadım Juan, pislikleri öldürmek için başladım, ve sen hepsinin en büyük ödülüsün.";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "Beş yüz dublon mu? Benimle dalga mı geçiyorsun, Consumption. Burada en az iki katını sakladığına eminim... Şimdi bana bin dublon ver, sonra nereye gidersen git umurumda olmaz, yoksa...";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "Gemi patlamak üzere, yani bana iyi bir arkadaşlık yapacaksın. Ne dersin?";
				link.l1 = "Çok konuşuyorsun, Consumption, sadede gel!";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "Anlaşabilirdik... Eh, neyse!";
			link.l1 = "Bu zavallı insanları hücrelerinden çıkardın, ne karşı koyabildiler ne de kaçabildiler. Sen bir korkaksın, Consumption, ve şimdi de korkak olarak öleceksin.";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "Senin işten anladığın belli dostum... Al bakalım - elimdeki her şey bu. Ama bir ömür için pek bir şey sayılmaz, değil mi?";
			link.l1 = "Hayatın bir kurşun bile etmez, demek ki bu hayatımın en kârlı pazarlığı oldu. Şimdi kaybol.";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("You received 1000 doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "Herkesi kurtarmaya ve beni öldürmeye vaktin olmayacak, değil mi? Fitil yanıyor, zaman tükeniyor...";
			link.l1 = "Kahretsin! Bu insanları buradan çıkarmam lazım... Defolun pislikler – er ya da geç hak ettiğinizi bulacaksınız!";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "Yine de deneyeceğim...";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Angelo";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "Ah... Nutkum tutuldu... Ne kabus ama!";
			link.l1 = "Ne yazık ki hiçbir şey yapamadım. Üzgünüm, kızım. Elveda.";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			AddQuestUserData("Consumption", "sSex", GetSexPhrase("",""));
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "İnanılır gibi değil! Sen... gerçekten onu kurtardın mı? Sana nasıl teşekkür edeceğimi bilmiyorum.";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "Bunu hayal edebiliyorum, güzelim. Ama anlaşmanın bana düşen kısmı bitti artık - geriye sadece ufak bir şey kaldı.";
				link.l1.go = "Waitress_3";
			}
			link.l2 = " Görev çağırdı – ve ben de harekete geçtim. Hepsi bu. ";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "Ben... ah Tanrım! Haklısın. Onun için, söz verdiğim gibi... Yukarıdaki odaya çık - fazla vaktimiz yok.";
			link.l1 = "Hadi o zaman, acele edelim!";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "İşte geldim, cesur caballerom! Ve bak, yanında ne getirdim.";
			link.l1 = "Vay canına, etkilendim, hadi şu vişne şarabını açalım! Sonra başka bir şey açarız... Bugün şanslı günündesin nihayetinde... Ha-ha!";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "Sen gerçek bir şövalyesin! Caballero! Bak - bunu bir hakaret olarak alma, ama bunu senin almanı istiyorum. Bu parayı Angelo'yu fidyeyle kurtarmak için biriktirmiştim, ama artık önemi kalmadı! Lütfen, reddetme - al bunu!";
				link.l1 = "Pekala, gözlerinizi unutmayacağım señorita - mutluluk gözyaşlarıyla parladıklarında çok daha güzeller, acıyla değil. Hediyenizi kabul ediyorum. Hoşça kalın, size ve Angelo'ya bol şans.";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "Sen gerçek bir şövalyesin! Caballero! Herkese anlatacağım! Seni hep hatırlayacağım!";
				link.l1 = "Pekala, ben de gözlerinizi hatırlayacağım señorita - mutluluk gözyaşlarıyla parladıklarında acıdan çok daha güzeller. Hep mutlu olun. Elveda!";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
