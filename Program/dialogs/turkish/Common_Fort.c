// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <-- */
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Bir casus! Silahını bırak ve benimle gel!","Bir düşman ajanı! Yakalayın "+GetSexPhrase("onu","onu")+"!");
				link.l1 = RandPhraseSimple("Kapa çeneni, korkak!","Siktir git!");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("Sen kimsin ve burada ne yapıyorsun?","Kıpırdama! Sen kimsin? Kaleye neden girmeye çalışıyorsun?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Subay, ben de varım "+GetRusNameNationLicence(sti(npchar.nation))+", bu yüzden burada yasal bir gerekçeyle bulunuyorum. Bakın, lütfen göz atın...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Korsan kalede mi?! Yakalayın"+GetSexPhrase("onu","onu")+"!","Bu bir korsan, kalemizde gizlice dolaşıyor! Hapse götürün!!!");
							link.l1 = RandPhraseSimple("Evet, korsanım, peki şimdi ne olacak?","Heh, yakalayabilirsen yakala...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Şu bayrağı görmüyor musun "+NationNameGenitive(sti(pchar.nation))+" gemimin direğinde mi?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "Demir attım, hemen yanında "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+"   bayrağı altında"+NationNameGenitive(sti(pchar.nation))+"! Başka bir şeye ihtiyacınız var mı?";
						}
						// belamour legendary edition вызываюий доверие даёт возможность обмануть стражу
						if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
						{
							Notification_Perk(true, "Trustworthy");
							link.l1.go = "NotPegYou";
						}
						else
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								notification("Skill Check Failed", SKILL_SNEAK);
								link.l1.go = "PegYou";
							}
							else
							{
								link.l1.go = "NotPegYou";
							}
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Ah kaptan, seninle denizde harika zamanlar geçirdik! Senin komutanlığında ne gemiler batırdık birlikte! Ve şimdi...";
									link.l1 = "Ve burada, dostum, denizde göremeyeceğin zarif hanımları gözlerinle seyredebilirsin.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Kaptan, bunu hak etmek için ne yaptık biz?! Biz kara faresi değiliz, değil mi?";
									link.l1 = "Sessiz ol, denizci! Görevin çok önemli ve onurlu bir görev, o yüzden mızmızlanmayı bırak.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Denizde neler oluyor, kaptan? Bir daha görecek miyiz orayı?";
									link.l1 = "Elbette, denizci! Görevinden kurtulduğun anda iskeleye gidip denizin tadını dilediğin kadar çıkarabilirsin.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Bir şikayetim var, kaptan: Hepimiz denizi özledik. Bu kara görevi artık hepimize fazlasıyla yetti!";
									link.l1 = "Bu sızlanmalardan bıktım! Burada da bolca rom var! Kaptanın seni nereye koyduysa orada hizmet et, yoksa başkalarına ibret olsun diye biri asılacak.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Sana gizlice söyleyeyim kaptan, yeni vali rüşvetçi ve zimmetçi biri. Ama bu aslında benim işim değil...";
									link.l1 = "Aynen öyle, korsan. Senin işin nöbet tutup düzeni sağlamak. Valiyi seren direğine asmak ise benim işim. İyi iş çıkardın!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Bizi unutmadığınız için teşekkürler, kaptan! Sizinle ateşe de suya da gideriz!";
									link.l1 = "Sizin gibileri bilirim, düzenbazlar! Sizin tek derdiniz altın. Bu akşam meyhanede bir eğlence var, içkiler benden. Sakın gelmeyi unutmayın.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Heh, kaptan! Bir düşün, bir korsan gerçekten düzeni sağlayabilir mi?! Ne zamandır gerçek bir işe koyulmadık!";
									link.l1 = "Rahatlamaya vakit yok, korsan! Düşman armadaları adalarımızın yakınındaki sularda kol geziyor, her an bir kan gölüne hazır olmalıyız.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Kaptan, tacın bize doğru bir filo daha gönderdiğini duydum?";
									link.l1 = "Elbette, korsan. Yaşadığımız sürece bize huzur yok. Ve Cehennem’de bile şeytanlarla savaşacağız!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Kahretsin, dün geceki içki gerçekten çok sertti kaptan! Keşke orada olsaydınız.";
									link.l1 = "Önemli değil, telafi ederim. Ve sizi kıskandığım da yok, arkadaşlar.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Sana güvenerek söylüyorum kaptan, çünkü bize her zaman iyi davrandın, dün gerçekten çok hoş bir kızla güzel vakit geçirdik...";
									link.l1 = "Heh, korsan, tam da ihtiyacın olan şey bir ilmek!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Kaptan! Lütfen, beni bu lanetli görevden kurtarın! Artık düzenin koruyucusu rolünü oynayamam.";
									link.l1 = "Geceleri gemide nöbet tutmak da kolay değil. Dostum, görev görevdir, nerede ve ne olursa olsun.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("Önemli bir iş var!","Sizinle bir işim var.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
					}
					
					//Jason --> мини-квест Дефицитный товар
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason пиратская линейка
						string wineCity = "FortFrance";
						if(SandboxMode)
						{
							if(CheckAttribute(pchar,"HeroParam.ToCityId"))
							{
								wineCity = pchar.HeroParam.ToCityId;	
							}
						}
						if(GetCityNameByIsland(LoadedLocation.islandId) ==  wineCity && npchar.location.locator == "protector1")
						{
							dialog.text = "Hey, dostum! Bana küçük bir iyilik yapar mısın?";
							link.l1 = "Ne yapılması gerektiğine bağlı.";
							link.l1.go = "Wine_soldier";
							link.l2 = "Benim bununla uğraşacak vaktim yok.";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							DelLandQuestMark(npchar);
							break;
						}
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort")
							{
								dialog.text = "Hey, dostum! Bana küçük bir iyilik yapar mısın?";
								link.l1 = "Ne yapılması gerektiğine bağlı.";
								link.l1.go = "Wine_soldier";
								link.l2 = "Bunun için vaktim yok.";
								link.l2.go = "exit";
								pchar.questTemp.Wine = "true";
								DelLandQuestMark(npchar);
								break;
							}
						}
					}
					// <-- мини-квест Дефицитный товар
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Sayın Ekselansları, Genel Vali! Size nasıl hizmet edebilirim?";
							link.l1 = "Bir şeye ihtiyacım yok, teşekkür ederim.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Bu benim için büyük bir onur, Sayın Genel Vali! Size nasıl yardımcı olabilirim?";
								link.l1 = "Hizmetini özenle yerine getir - senden başka bir şey istemiyorum.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Sizi görmek ne güzel, Ekselansları! Bizim mütevazı bir asker olarak kolonilerimizin genel valisi için ne yapabilirim?";
								link.l1 = "Şahsen, senden hiçbir şey istemiyorum. Hizmetine devam et.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Вице-адмирал на службе нации узнается без мундира
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Amiral Yardımcısı, Ekselansları! Rapor vermeme izin verin: nöbetim sırasında...";
							link.l1 = "Sakin ol, asker, raporuna ihtiyacım yok. Amirine rapor ver.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Sizi görmek ne güzel, Amiral Yardımcısı! Size nasıl yardımcı olabilirim?";
								link.l1 = "Hayır, sadece ne kadar dikkatli olduğunu kontrol ediyordum. Beni tanıdığın için memnun oldum.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Amiral Yardımcısı, bu benim için bir onur! Size nasıl yardımcı olabilirim?";
								link.l1 = "Servis et "+NationNameGenitive(sti(npchar.nation))+", asker! Yapabileceğin en iyi şey bu.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Офицер с патентом
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Selamlar, kaptan! Bana vereceğiniz bir talimat varsa, affınıza sığınırım: her ne kadar hizmetinizde olsam da "+NationNameGenitive(sti(npchar.nation))+",   ben sadece komutana ve valiye hesap veririm."; 
							link.l1 = "Subaylarım ve tayfam emrimde. Görevini yap, asker.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Kaptan, geminizde hizmet edebilir miyim? Aynı hizmet karşılığında "+NationNameGenitive(sti(npchar.nation))+", ama ben denizi tercih ederim."; 
								link.l1 = "Sana verilen görevi onurla yerine getirmen gerekiyor. Bir an gözlerini kapat, onlar onu denize götürecekler.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Şanslısın: bir geminin kaptanısın ve hizmetindesin "+NationNameGenitive(sti(npchar.nation))+"... Ve ben bütün gün burada mahsur kaldım."; 
								link.l1 = "Karayipler'e yeni gelmişim de bir hafta sonra kaptan olmuşum sanıyor musun? Bu, yılların emeği...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Görmüyor musun? Görev başındayım. Rahatsız etme beni.";
							link.l1 = "Pekala, pekala...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Bana şüpheli bir hareketten mi bahsedeceksin?";
							link.l1 = "Hayır, hiç yok, bu arada ben de bir kaptanım. Bakıyorum artık dinlemiyorsun? Hoşça kal.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Burası askeri bir tesis, o yüzden burada fazla gürültü yapma.";
							link.l1 = "Pekala, bunu aklımda tutacağım.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Böyle güzel bir hava, ama ben burada dikilip duruyorum. Şehirde en azından birkaç kız var, peki burada ne var? Sadece fareler dolaşıyor.";
							link.l1 = ""+GetSexPhrase("Üzgünüm, ama yardımcı olamam – sonuçta bu senin görevin.","Hey! Benim neyim var? Kadın değil miyim ben?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Eğer sohbet etmeyi seviyorsan, başka birini bul. Burada düzeni sağlamak zorundayım ve boş lakırdıya ayıracak vaktim yok.";
							link.l1 = "Ah, hayır, sadece hâlâ hayatta mısın diye bakıyordum. Bir heykel gibi öylece duruyordun.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Muhtemelen garnizon görevinin çocuk oyuncağı olduğunu düşünüyorsun? Hiç de öyle değil! Bu iş hem zor hem de çok önemli. Bir keresinde... ";
							link.l1 = "Bu hikayeyi bana başka bir zaman anlatırsın. Şu anda biraz acelem var.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Dikkatli ol, burası bir kale! Fare gibi sessiz ol!";
							link.l1 = "Dediğiniz gibi, asker.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Hey! Sende su var mı, tesadüfen? Susuzluktan ölüyorum.";
							link.l1 = "Hayır dostum, sabırlı ol...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Garnizon hayatı ne kadar sıkıcı, etrafta senin gibi köylülerden başka kimse yok! Şehir garnizonu ise kesin daha iyi vakit geçiriyordur...";
							link.l1 = "Ve buna 'görev başında olmak' mı diyorsun? Bu gidişle, kesinlikle bir casusun gözünden kaçmasına izin vereceksin!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Güçlü birine benziyorsun, değil mi? Kale garnizonunda göreve katılmak ister misin? Geniş koğuşlarımız, günde iki öğün yemeğimiz ve bedava içkimiz var.","Ah, genç hanımefendi, böyle ıssız bir yerde böylesine zarif bir genç bayanla karşılaşmak ne büyük bir mutluluk, bilemezsiniz!")+"";
							link.l1 = ""+GetSexPhrase("Bu kesinlikle cazip, ama yine de reddetmek zorundayım. O kışla talimleri bana göre değil.","İltifatınız için teşekkür ederim, asker.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Bu lanet sıcak... Avrupa'ya geri dönmek için hayatımın yarısını seve seve verirdim.";
							link.l1 = "Evet, sağlığınızın buranın iklimine uygun olmadığını görebiliyorum.";
							link.l1.go = "exit";
						break;
					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Hmm... Anladım. İşte "+GetSexPhrase("хотел","хотела")+" sormak...";
					link.l3.go = "quests";//(перессылка в файл города) */
				}
			}
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_soldier":
			dialog.text = "Bakın, gerçekten biraz şarap istiyorum... Ama çürük meyveden yapılan ve varili iki pesoya satılan yerel pislikten değil – gerçek Avrupa şarabı istiyorum. Kasabadaki tüccarlardan bulabilirsiniz. Oldukça pahalı, ama bedelini tamamen ödeyeceğim, üstüne de üç yüz peso fazladan vereceğim. O halde, bana biraz getirir misiniz?";
			link.l1 = "Peki, neden kendin alamıyorsun? Fazla ödeme yapmana gerek yok, görevinden ayrılınca gidip alırsın. İşin içinde ne var?";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "Bir tuzak yok. Sadece iznimi alana kadar kaleden şehre çıkamam, ki bu da yakın zamanda olmayacak gibi. Üstelik, komutanımız kalede içki içmeyi kesinlikle yasakladı, Allah kahretsin! Yani, bir askere yardım edecek misin?";
			link.l1 = "Peki, neden olmasın? Sana o şarabı getiririm, zaten şu anda boş vaktim var.";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "Üzgünüm dostum, ama bunu yapamam. Sana yardım edecek başka birini bul.";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "Harika! Çok teşekkür ederim! Bugün nöbetteyim, o yüzden yarın gel. Beni kalenin tepesinde bulacaksın, orada şişeyi bana gizlice verebilirsin, kimse fark etmez...";
			link.l1 = "Pekala. Beni bekle, yarın seni görmeye geleceğim.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			if(StartHeroType == 2) pchar.questTemp.Wine.City = "Santiago";
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
		// <-- мини-квест Дефицитный товар
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Bana kalırsa bu bir hile. Komutanla konuşalım, "+GetSexPhrase("yoldaş","tatlım")+", ve her şeyi çöz...","Hmm... Bir şey bana, iddia ettiğin kişi olmadığını söylüyor... Silahını teslim et "+GetAddress_Form(npchar)+", ve daha fazla araştırma için beni takip et!");
			link.l1 = RandPhraseSimple("Siktir git!","Bir haftada iki Pazar olursa...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Anladım... Her şey yolunda görünüyor, gidebilirsiniz, "+GetAddress_Form(pchar)+".","Sanırım nöbet tutarken biraz yorulmuşum... Her şey yolunda görünüyor, "+GetAddress_Form(pchar)+", üzgünüm.");
			link.l1 = "Hiç sorun değil!";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Bir düşünsene! Ne cüret! Tüccar kılığına girip buraya gelmişsin! Suratın her kışlada asılı, alçak herif! Bu sefer paçayı kurtaramayacaksın! Yakala onu!";
				link.l1 = RandPhraseSimple("Arrgh!..","Eh, bunu sen istedin...");
				link.l1.go = "fight";	
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе
			{
				dialog.text = "Buraya ticaret yapmak için mi geldiniz? Nasıl geldiğinizi sorabilir miyim? Geminiz nerede? Biliyor musunuz, bu durum oldukça şüpheli görünüyor ve her şeyi açıklığa kavuşturana kadar sizi alıkoymak zorundayım. Silahınızı teslim edin ve beni takip edin!";
				link.l1 = RandPhraseSimple("Siktir git!","Bir haftada iki pazar günü olursa...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Lisansınızın süresi dolmuş ve bu yüzden geçersiz. Silahınızı teslim edin ve daha fazla inceleme için benimle gelin!";
				link.l1 = RandPhraseSimple("Siktir git!","Bir haftada iki pazar günü olursa...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Her şey yolunda görünüyor. Yine de, ruhsatınızın bugün sona erdiğini belirtmeliyim. Bu sefer geçmenize izin vereceğim, ama yine de yeni bir ruhsat almanız gerekecek.";
				link.l1 = "Teşekkür ederim, en kısa zamanda halledeceğim.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Her şey yolunda görünüyor. Yine de, lisansınızın yakında süresinin dolacağını belirtmeliyim. Sadece şu kadar süre geçerli: "+FindRussianDaysString(iTemp)+". Bunu aklında tut, "+GetAddress_Form(npchar)+".";
				link.l1 = "Teşekkür ederim, en kısa zamanda yenisini alacağım.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Pekâlâ, her şey yolunda görünüyor. Ruhsatınız geçerli, süresi "+FindRussianDaysString(iTemp)+". Geçebilirsiniz.","Her şey açık, "+GetAddress_Form(npchar)+". Kasabaya gelip gitmekte özgürsünüz, ruhsatınız şu süreyle geçerli  "+FindRussianDaysString(iTemp)+" . Rahatsız ettiğim için üzgünüm.","Her şey yolunda görünüyor, "+GetAddress_Form(npchar)+", artık seni burada tutmuyorum.");
				link.l1 = RandPhraseSimple("Mükemmel. Saygılarımla.","Teşekkür ederim, memur bey.");
				link.l1.go = "exit";
			}
		break;

		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
				dialog.text = "Captain, I ask you to put away your weapons; it is forbidden to draw them in our city.";
				link.l1 = LinkRandPhrase("Pekala, kaldırıyorum...","Zaten yaptım.","Dediğiniz gibi...");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("Siktir git!","Sanırım bunu kullanacağım!","Zamanı gelince onu kaldırırım.");
				link.l2.go = "fight";
				npchar.greeting = "soldier_common";
				NextDiag.TempNode = "First Time";
				break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Ne diye kılıcın çekik halde ortalıkta dolaşıyorsun? Hemen silahını indir!","Silahını derhal kınına koymanı emrediyorum!","Hey, "+GetSexPhrase("dostum","kız")+", insanları korkutmaktan vazgeç! Silahını kınına koy.");
			link.l1 = LinkRandPhrase("Pekala.","Pekala.","Dediğiniz gibi...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Siktir git!","Hayal kurmanın zararı yok...","Bir haftada iki pazar günü olursa.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
