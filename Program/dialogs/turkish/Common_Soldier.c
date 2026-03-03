// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int DeceptionChance  = 0;
	int DeceptionPenalty  = 0;
	if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeceptionPenalty = sti(pchar.StealtDeceptionPenalty);
	
	DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/110);
	if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	if (false) 
	{
		DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/310);
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
	{
		DeceptionChance = 100;
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(DeceptionChance > 90) DeceptionChance = 90;
	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
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
			if (false)
			{
				// заглушка на пирата
				if (false)
				{
    				dialog.text = RandPhraseSimple("Kasabada korsanlar mı var?! İnanamıyorum... Yakala "+GetSexPhrase("onu","onu")+"!!","Bu bir korsan! Yakalayın "+GetSexPhrase("onu","onu")+"!!!");
					link.l1 = RandPhraseSimple("Ben bir korsanım, peki ne olmuş?","Heh, deneyebilirsin...");
					link.l1.go = "fight"; 
					break;
				}
				else
				{
					if (DeceptionChance > (10+rand(150)+rand(150)))
					{
						dialog.text = RandPhraseSimple("Sen kimsin ve burada ne yapıyorsun?","Olduğun yerde kal! Sen kimsin ve hangi hakla kasabaya girmeye çalışıyorsun?");
						link.l2 = "Demir attım, hemen yanında "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+"   bayrağı altında  "+NationNameGenitive(sti(npchar.nation))+". Neyi anlamıyorsun? (Aldatma olasılığı "+DeceptionChance+"%%)";
						link.l1.go = "NotPegYou";
					}
					else
					{
						dialog.text = RandPhraseSimple("Bir casus! Silahını bırak ve beni takip et!","Bir düşman ajanı! Yakalayın "+GetSexPhrase("onu","onu")+"!");
						link.l1 = RandPhraseSimple("Kapa çeneni, süt çocuğu!","Siktir git!");
						link.l1.go = "fight"; 
					}
				}
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (false)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("Sen kimsin ve burada ne yapıyorsun?","Olduğun yerde kal! Sen kimsin ve hangi hakla kasabaya girmeye çalışıyorsun?");
						link.l1 = "Şu kağıda bak, asker. Engizitör Baba Vincenzo'dan izinle buradayım.";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("Sen kimsin ve burada ne yapıyorsun?","Orada dur! Sen kimsin ve hangi hakla kasabaya girmeye çalışıyorsun?");
						link.l1 = "Şu kağıda bak, asker. Engizitör Baba Vincento'nun izniyle buradayım.";
						link.l1.go = "vincento"; 
						break;
					}
					if (PChar.location == "Maracaibo_Plantation")
					{
						dialog.text = LinkRandPhrase("Kendine hakim ol ve kölelere bulaşma.","Hadi, yürü devam et!","Ah, demek sensin. Devam et, senin hakkında zaten bilgilendirildik.");
						link.l1 = "...";
						link.l1.go = "exit";
						break;
					}
					dialog.text = RandPhraseSimple("Sen kimsin ve burada ne yapıyorsun?","Olduğun yerde kal! Sen kimsin ve hangi hakla kasabaya girmeye çalışıyorsun?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Subay, benim var "+GetRusNameNationLicence(HOLLAND)+", yani burada yasal bir gerekçeyle bulunuyorum. Bakın, lütfen göz atın...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "Şu bayrağı görmüyor musun "+NationNameGenitive(sti(pchar.nation))+"gemimin direğinde mi?! (Aldatılma olasılığı "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l2 = "Demir attım, hemen yanında "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+"   bayrağı altında "+NationNameGenitive(sti(pchar.nation))+". Ne anlamıyorsun? (Aldatılma olasılığı "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (false)
						{
    						dialog.text = RandPhraseSimple("Kasabada korsanlar mı var?! İnanamıyorum... Onu yakalayın!","Bu bir korsan! Yakalayın onu!");
							link.l1 = RandPhraseSimple("Evet, korsanım - şimdi ne olacak?","Heh, yakalayabiliyorsan yakala...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Şu bayrağı görmüyor musun "+NationNameGenitive(sti(pchar.nation))+" gemimde mi?! (Aldatma olasılığı "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l1 = "Demir attım yakınlarda "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" bayrak altında "+NationNameGenitive(sti(pchar.nation))+". Ne anlamıyorsun? (Aldatılma olasılığı "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Ah kaptan, seninle denizde harika zamanlar geçirdik! Senin komutanlığında birlikte ne gemiler batırdık! Ve şimdi burada...";
									link.l1 = "Ve burada, dostum, denizde göremeyeceğin zarif hanımlara gözlerini doyasıya bakabilirsin.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Kaptan, bunu hak etmek için ne yaptık biz?! Biz karada yaşayan fareler değiliz, öyle mi?";
									link.l1 = "Sessiz ol, denizci! Görevin çok önemli ve onurlu, o yüzden mızmızlanmayı bırak.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Denizde neler oluyor, kaptan? Bir daha görebilecek miyiz?";
									link.l1 = "Elbette, denizci! Görevinden kurtulduğunda, iskeleye gidip denizin tadını dilediğin kadar çıkarabilirsin.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Bir şikayetim var, kaptan: hepimiz denizi özledik. Bu kara görevi hepimize fazlasıyla yetti artık!";
									link.l1 = "Bu sızlanmalardan bıktım! Burada da yeterince rom var! Kaptanın seni görevlendirdiği yerde hizmet et, yoksa başkalarına ibret olsun diye biri asılacak.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Sana gizlice söyleyeyim kaptan, yeni vali rüşvetçi ve zimmetine para geçiriyor. Ama bu gerçekten beni ilgilendirmez...";
									link.l1 = "Aynen öyle, korsan. Senin işin nöbetinde durup düzeni sağlamak. Valiyi seren direğine asmak ise benim işim. İyi iş çıkardın!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Bizi unutmadığınız için teşekkürler, kaptan! Sizinle ateşe de suya da gideriz!";
									link.l1 = "Sizin gibileri bilirim, düzenbazlar! Gerçekten umurunuzda olan tek şey altın. Bu akşam meyhanede bir eğlence var, içkiler benden. Sakın gelmeyi unutmayın.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Heh, kaptan! Bir düşün, bir korsan gerçekten düzenin koruyucusu olabilir mi?! Ne zamandır gerçek bir işte olmadık!";
									link.l1 = "Rahatlamaya zaman yok, korsan! Düşman armadaları adalarımızın yakınındaki sularda dolaşıyor ve her an kanlı bir çatışmaya hazır olmalıyız.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Kaptan, tacın buraya bir filo daha gönderdiğini duydum?";
									link.l1 = "Elbette, korsan. Yaşadığımız sürece bize huzur yok. Hatta Cehennem’de bile şeytanlarla savaşacağız!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Vay canına! Dün geceki içki gerçekten çok sertti, kaptan! Keşke orada olsaydınız.";
									link.l1 = "O kadar da önemli değil, telafi ederim. Ve sizi kıskandığım da yok, arkadaşlar.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Sana güvenerek söylüyorum kaptan, çünkü bize her zaman iyi davrandın. Dün gerçekten çok hoş bir kızla güzel vakit geçirdik...";
									link.l1 = "Heh, korsan, tam da ihtiyacın olan şey bir ilmek!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Kaptan! Lütfen, beni bu lanetli görevden kurtarın! Artık düzenin koruyucusu rolünü oynayamıyorum.";
									link.l1 = "Bir gemide gece nöbeti de kolay değildir. Dostum, görev görevdir, nerede ve ne olursa olsun.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("Önemli bir şey var!","Sizinle bir işim var.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("Uyarı! Silahlı, akli dengesi yerinde olmayan bir deli burada!","Silaha, silaha! Burada bir deli herif var!");
								link.l1 = RandPhraseSimple("Ha? Ne?","Ee, neden bunu yapıyorsun?");
								link.l1.go = "pirate_fight";
							}
							else
							{
							    /* dialog.text = LinkRandPhrase(RandPhraseSimple("Benimle bir işiniz mi var, Kaptan?","Ben sadece iş için buradayım, bir şeye ihtiyacın olursa çekinmeden sor."),RandPhraseSimple("Kaptan, çok meşgulüm, konuşacak başka birini bul.","Bir sorun mu var, Kaptan? Sorunuz yoksa, gidebilir miyim?"),"Yol ver, Kaptan, acelem var.");
							link.l1 = LinkRandPhrase("Üzgünüm dostum, ben "+GetSexPhrase("Yanılmışım","обозналась")+" ","Pekala, işine bak.","Hayır, hiçbir şey.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("Sana birkaç sorum var.","Sizinle bir işim var."),RandPhraseSimple("Acelen olduğunu görüyorum. Sadece bir soru, sonra serbestsin.","Ben "+GetSexPhrase("хотел","хотела")+" bir şey sor."),"İşin bekleyebilir. Sana bir şey sormam lazım "+GetSexPhrase("хотел","хотела")+".");
							    link.l2.go = "quests";//(перессылка в файл города) */
								
								//Экку Korsar - что-то они больно вежливые для пиратов были...
								dialog.text = RandPhraseSimple("Ne istiyorsun? Yürümeye devam et.","Yolu kapatma, çekil.");
					            link.l1 = RandPhraseSimple("Biliyor musun? Bağırma!","Ateşini biraz azalt. Hemen soğutamam!");
					            link.l1.go = "exit";
						    	/* link.l2 = LinkRandPhrase(RandPhraseSimple("Sana birkaç sorum var.","Sizinle bir işim var."),RandPhraseSimple("Acelen olduğunu görüyorum. Sadece bir soru, sonra serbestsin.","Ben "+GetSexPhrase("хотел","хотела")+" bir şey sor."),"İşin bekleyebilir. Sana bir şey soracağım "+GetSexPhrase("хотел","хотела")+".");
							link.l2.go = "quests";//(перессылка в файл города) */
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("Sadece bak  "+GetSexPhrase("şu alçağa bak! Yüzünü göstermeye cüret etti","şu alçağa bak! Yüzünü göstermeye cesaret etti")+" içinde "+XI_ConvertString("Colony"+npchar.city)+". Ele geçir "+GetSexPhrase("onu","onu")+"!!!","Ha, seni tanıyorum, "+GetSexPhrase("serseri","serseri")+"! Ele geçirin "+GetSexPhrase("onu","onun")+"!!!");
							link.l1 = RandPhraseSimple("Ah!..","Peki, bunu sen istedin...");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "Ah, kimler gelmiş! Leydi "+pchar.GenQuest.EncGirl.name+" kendisi bizi şereflendirdi! Nasıl cesaret ettin, merak ediyorum? Seni arıyorduk! Lütfen zindana buyur - hücren hazır ve seni bekliyor. ";
							link.l1 = "Ne saçmalıyorsun sen!? Mürettebatım ve ben "+GetSexPhrase("cavalier","yoldaş")+" ormanda dolaşıp çiçek topluyorduk. Beni rahat bırakın! Bu zorba adamların hiç mi görgüsü yok?! Güzel bir kız görünce hemen başının etini yemeye başlıyorlar! "+GetSexPhrase("Canım, lütfen şu ahmaklara defolup gitmelerini ve namuslu bir kadını rahat bırakmalarını söyle!","Sevgilim, lütfen o ahmaklara söyle...")+"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "Ah, işte buradasın, güzelim! Baban bütün garnizonu seni bulup eve getirmek için seferber etti.";
							link.l1 = "Defolun! Nereye gittiğimi biliyorum ve sizin yardımınıza ihtiyacım yok! Kaptan, onlara ellerini üzerimden çekmelerini söyleyin.";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях

					// --> belamour ночной приключенец
					if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
					{
						dialog.text = "Bir askerin hayatı bellidir - nöbet tutmak, devriye gezmek ... Ne istiyorsun, "+GetAddress_Form(NPChar)+"?";
						link.l1 = "Dinle, yakın zamanda burada o sarhoşla kavga eden sen miydin? Görünüşe bakılırsa, evet, sendin...";
						link.l1.go = "NightAdventure_CitizenHomieSolder";
						break;
					}
					// <-- ночной приключенец
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Sayın Ekselansları, Genel Vali! Size nasıl hizmet edebilirim?";
							link.l1 = "Bir şeye ihtiyacım yok, teşekkürler.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Bu benim için büyük bir onur, Sayın Genel Vali! Size nasıl yardımcı olabilirim?";
								link.l1 = "Hizmetini özenle yerine getir - senden başka bir şey istemiyorum.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Sizi görmek ne güzel, Ekselansları! Bizim mütevazı bir asker olarak kolonilerimizin genel valisi için ne yapabilirim?";
								link.l1 = "Şahsen, senden hiçbir şey istemiyorum. Hizmet etmeye devam et.";
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
							link.l1 = "Sakin ol, asker, raporuna ihtiyacım yok. Subayına rapor ver.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Sizi görmek ne güzel, Amiral Yardımcısı! Size bir konuda yardımcı olabilir miyim?";
								link.l1 = "Hayır, sadece ne kadar dikkatli olduğunu kontrol ediyordum. Beni tanıdığın için memnun oldum.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Amiral Yardımcısı, bu benim için büyük bir onur! Size nasıl yardımcı olabilirim?";
								link.l1 = "Servis Et "+NationNameGenitive(sti(npchar.nation))+", asker! Yapabileceğin en iyi şey bu.";
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
							dialog.text = "Selamlar, kaptan! Bana vereceğiniz bir talimat varsa, affınıza sığınırım: her ne kadar hizmetinizde olsam da "+NationNameGenitive(sti(npchar.nation))+",   ben sadece komutan ve valiye karşı sorumluyum."; 
							link.l1 = "Subaylarım ve tayfam benim emrimde. Görevini yap, asker.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Kaptan, geminizde hizmet edebilir miyim? Aynı hizmet karşılığında "+NationNameGenitive(sti(npchar.nation))+", ama ben denizi tercih ederim."; 
								link.l1 = "Sana verilen görevde bulunman gerekiyor, bu yüzden hizmetini onurla yerine getir. Bir saniyeliğine gözlerini kapatırsan, onu denize götürürler.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Şanslısınız:    bir geminin kaptanısınız ve şu anda hizmetindesiniz "+NationNameGenitive(sti(npchar.nation))+"... Ve ben bütün gün burada mahsur kaldım."; 
								link.l1 = "Karayipler'e yeni gelmişim de bir hafta sonra kaptan olmuşum sanıyor musun? Bunların hepsi yılların emeği...";
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
							link.l1 = "Hayır, hiç yok, bu arada ben de bir kaptanım. Görüyorum ki artık dinlemiyorsun? Hoşça kal.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Burası askeri bir tesis, o yüzden burada fazla gürültü yapma.";
							link.l1 = "Pekala, bunu aklımda tutacağım.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Böyle güzel bir hava var, ben ise burada dikiliyorum. Kasabada en azından kızlar var, peki burada ne var? Sadece fareler dolaşıyor.";
							link.l1 = ""+GetSexPhrase("Üzgünüm, ama yardımcı olamam - sonuçta bu senin görevin.","Hey! Benim neyim var? Kadın değil miyim?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Eğer sohbet etmekten hoşlanıyorsan, başka birini bul. Burada düzeni sağlamak zorundayım ve boş muhabbet için vaktim yok.";
							link.l1 = "Ah, hayır, sadece hala hayatta mısın diye bakıyordum. Bir heykel gibi öylece duruyordun.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Muhtemelen garnizon görevinin çocuk oyuncağı olduğunu düşünüyorsun? Hiç de öyle değil! Bu iş hem zor hem de çok önemli. Bir keresinde... ";
							link.l1 = "Bu hikayeyi bana başka bir zaman anlatırsın. Şimdi biraz acelem var.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Dikkatli ol, burası bir kale! Fare gibi sessiz ol!";
							link.l1 = "Dediğiniz gibi, asker.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Hey! Yanında su var mı, tesadüfen? Susuzluktan ölüyorum.";
							link.l1 = "Hayır dostum, sabırlı ol...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Garnizon hayatı ne kadar sıkıcı, etrafta sadece senin gibi kırolar var! Şimdi, kasaba garnizonu kesin daha iyi zamanlar geçiriyordur...";
							link.l1 = "Ve buna 'görev başında olmak' mı diyorsun? Bu gidişle, kesin bir casusu gözden kaçıracaksın!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Güçlü birine benziyorsun, değil mi? Kale garnizonunda göreve katılmak ister misin? Geniş koğuşlarımız, günde iki öğün yemeğimiz ve bedava içkimiz var.","Ah, genç hanımefendi, böyle tenha bir yerde böylesine zarif bir genç bayanla karşılaşmak ne kadar hoş, bilemezsiniz!")+"";
							link.l1 = ""+GetSexPhrase("Bu kesinlikle cazip, ama yine de reddetmeliyim. O kışla talimleri bana göre değil.","İltifatınız için teşekkür ederim, asker.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Bu lanet sıcak... Avrupa'ya geri dönebilmek için hayatımın yarısını seve seve verirdim.";
							link.l1 = "Evet, sağlığınızın yerel iklime uygun olmadığını görebiliyorum.";
							link.l1.go = "exit";
						break;

					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Bir dakika. Sana bir şey sormak istiyordum "+GetSexPhrase("хотел","хотела")+"...";
					link.l3.go = "quests";//(перессылка в файл города) */				
				}
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier") && npchar.location.group == "soldiers" && npchar.city == "Bridgetown")
			{
				dialog.text = "Bridgetown'a hoş geldiniz, "+GetAddress_Form(NPChar)+"...";
				link.l1 = "Yüzümün sadece Fransız kolonilerinde değil, başka yerlerde de tanındığını sanıyordum... Benim adım "+GetFullName(pchar)+".";
				link.l1.go = "WildRose_Soldier_1";
				DeleteAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier");
				DelLandQuestMark(npchar);
			}
			//<-- Дикая Роза
		break;
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Bana kalırsa bu bir hile. Komutanla konuşalım, "+GetSexPhrase("dostum","tatlım")+", ve her şeyi çöz...","Hmm... Bir şey bana, göründüğün kişi olmadığını söylüyor... Silahını teslim et "+GetAddress_Form(npchar)+", ve daha fazla araştırma için beni takip et!");
			link.l1 = RandPhraseSimple("Siktir git!","Bir haftada iki pazar günü olursa...");
			link.l1.go = "fight";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Anladım... Her şey yolunda görünüyor, gidebilirsiniz, "+GetAddress_Form(pchar)+".","Sanırım nöbet tutarken biraz yorulmuşum... Her şey yolunda görünüyor, "+GetAddress_Form(pchar)+", üzgünüm.");
			link.l1 = " Sorun değil! ";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("Anladım... Her şey yolunda görünüyor, gidebilirsiniz. "+GetAddress_Form(pchar)+".","Bakalım şimdi... Evet, her şey yolunda görünüyor, "+GetAddress_Form(pchar)+", üzgünüm.");
			link.l1 = "Sana ders olsun!";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Bir düşünsene! Ne küstahlık! Tüccar kılığına girip buraya gelmek! Resimlerin her kışlada asılı, alçak herif! Bu sefer paçayı kurtaramayacaksın! Yakala onu!";
				link.l1 = RandPhraseSimple("Arrgh!..","Pekala, bunu sen istedin...");
				link.l1.go = "fight";	
				break;
			}
			if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = "Buraya ticaret yapmak için mi geldiniz? Nasıl geldiğinizi sorabilir miyim? Geminiz nerede? Biliyor musunuz, bu iş bana çok şüpheli görünüyor ve meseleyi açıklığa kavuşturana kadar sizi alıkoymak zorundayım. Silahınızı teslim edin ve beni takip edin!";
				link.l1 = RandPhraseSimple("Siktir git!","Bir haftada iki pazar günü olursa...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Lisansınızın süresi dolduğu için iptal edilmiştir ve artık geçerli değildir. Silahınızı teslim edin ve daha fazla inceleme için benimle gelin!";
				link.l1 = RandPhraseSimple("Siktir git!","Bir haftada iki pazar günü olursa...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Her şey yolunda görünüyor. Yine de, ruhsatınızın bugün sona erdiğini belirtmeliyim. Bu sefer geçmenize izin vereceğim, ama yine de yeni bir ruhsat almanız gerekecek.";
				link.l1 = "Teşekkür ederim, en kısa zamanda yenisini alacağım.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Her şey yolunda görünüyor. Yine de, lisansınızın yakında sona ereceğini belirtmeliyim. Sadece şu kadar süre geçerli: "+FindRussianDaysString(iTemp)+" . Bunu aklında tut, "+GetAddress_Form(npchar)+".";
				link.l1 = "Teşekkür ederim, en kısa zamanda yenisini alırım.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Pekâlâ, her şey yolunda görünüyor. Ruhsatınızın süresi daha  "+FindRussianDaysString(iTemp)+". Geçebilirsiniz.","Her şey açık, "+GetAddress_Form(npchar)+". Şehre girip çıkmakta özgürsünüz, ruhsatınızın süresi daha  "+FindRussianDaysString(iTemp)+" . Rahatsız ettiğim için üzgünüm.","Her şey yolunda görünüyor, "+GetAddress_Form(npchar)+", artık seni burada tutmuyorum.");
				link.l1 = RandPhraseSimple("Mükemmel. Saygılarımla.","Teşekkür ederim, memur.");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("Hey, dostum, deniz fenerinde hiçbir şeyi kırma.","Bu deniz feneri kasabanın çok önemli bir parçası. Dikkatli ol!");
			link.l1 = RandPhraseSimple("Pekala, endişelenme.","Pekâlâ, endişelenme.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("Toplara fazla yaklaşma - burası askeri bir tesis!","Yabancılar topların yanına yaklaşamaz!","Topların yakınında dolaşırken seni yakalarsam, işin biter!");
			link.l1 = RandPhraseSimple("Anladım.","Pekala, anladım.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = "Sen de kimsin kaptan? Yoksa bu yerleşimdeki en azılı hırsızın suç ortağı falan mı çıktın?";
			link.l1 = "Kime suç ortağı dedin sen az önce?! Güneş mi geçti kafana ne?! Hey, kızdan elini çek!";
			link.l1.go = "GirlEnc_11";
			link.l2 = "Aslında, ben "+GetSexPhrase("onu tanıdım","onu tanıdım")+" son zamanlarda...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+GetSexPhrase("Bayım","Hanımefendi")+", onu tutuklayıp zindana götürmemiz emredildi. Bizi durdurabileceğini sanıyorsan, yanılıyorsun.";
			link.l1 = "Bakalım, o zaman...";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = "Gerçekten mi? O halde, ceplerini kontrol etmeni tavsiye ederim. O hanımefendi bu işte profesyoneldir, biliyorsun";
			link.l1 = "Teşekkür ederim, öyle yapacağım. Nasıl bu kadar rezil olabildim ki...";
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = ""+GetSexPhrase("Efendim","Hanımefendi")+", o kadını bulup babasına götürmemiz için emir aldık.";
			link.l1 = "Pekâlâ, emir emirdir - devam et o zaman.";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "Artık çok geç, çünkü ben zaten onun babasıyla konuşuyorum.";
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "Kaptan, emirlerimiz var, ve eğer bizi durdurabileceğinizi sanıyorsanız, yanılıyorsunuz.";
				link.l1 = "Bak bakalım, o zaman...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Heh, "+GetSexPhrase("şanslı bir adamsın","şanslı bir kızsın")+" .  Babası, onu geri getiren herkese cömert bir ödül vaat etti.";
				link.l1 = "Umutsuzluğa kapılma - önünde hâlâ pek çok ödül var.";
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// <-- генератор "A damsel in the jungle"
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomieSolder":
			dialog.text = "Evet, benimle. Bırak parmaklıklar ardında oturup davranışlarını düşünsün. Eğer onun adına beni tehdit etmeye geldiysen, inan bana: Kale komutanına bile ulaşabilirim.";
			link.l1 = "Evet, tehdit etmeye gelmedim, sadece ondan olan iddialarınızdan vazgeçmenizi istemeye geldim. Bakın, o eski bir tanıdığım, sadece sarhoş oldu, ama bilirsiniz, sarhoş için deniz diz boyu...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;
		
		case "NightAdventure_CitizenHomieSolder_1":
			dialog.text = "Yani, ben görev başındayken bana bir gözümü morarttı, şimdi de serbest mi bırakılmalı? Neden böyle olsun ki?";
			link.l1 = "Onun davranışları için özür olarak beş yüz peso ne dersiniz?";
			link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;
		
		case "NightAdventure_CitizenHomieSolder_2":
			dialog.text = "Öyle mi düşünüyorsun? Onurumla alay etti, ve sen bunun beş yüz peso için affedilebileceğini mi sanıyorsun? Onurumun satın alınabileceğini mi düşünüyorsun?";
			link.l1 = "...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;
			
		case "NightAdventure_CitizenHomieSolder_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
			{
				DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
				pchar.quest.NightAdventure_SeaExit.over = "yes";
				pchar.quest.NightAdventure_JungleExit.over = "yes";
				SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
				dialog.text = "Hayır, Kaptan, her şey adil. Bunu hak etti. Ve sizden bir daha beni görevlerimden alıkoymamanızı rica ediyorum.";
				link.l1 = "Haklısın.";
				link.l1.go = "exit";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
			{
				dialog.text = "Bin. Ve bir peso bile eksik olmasın.";
				link.l1 = "Hayır, belki de tek bir yara için bu kadar çok ödemeye hazır değilim.";
				link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
				if (sti(pchar.money) >= 1000)
				{
					link.l2 = "Oh... Peki, bekle biraz. Hemen bir kalem ve biraz parşömen getiriyorum. Arkadaşıma karşı tüm hak iddialarından vazgeçtiğini yaz.";
					link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
				}
			}
		break;
		
		case "NightAdventure_CitizenHomieSolder_3NM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "O halde sizi daha fazla görevlerimden alıkoymamanızı rica ediyorum.";
			link.l1 = "Yapmam.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieSolder_3GM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.GenQuest.NightAdventureToPrisoner = true;
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Buyurun.";
			link.l1 = "İşinde bol şanslar.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		//--> Дикая Роза
		case "WildRose_Soldier_1":
			if (GetHour() >= 6 && GetHour() <= 21)
			{
				dialog.text = "Ah, sensin kaptan... Güneş beni mahvetti... Lanet sıcak!";
			}
			else
			{
				dialog.text = "Buna karşı çıkamam. Yine de, gece olunca herkes aynı görünüyor, biliyor musun.";
			}
			link.l1 = "Ne oldu, asker? Normalde sizin tayfa benimle laf dalaşına girmez.";
			link.l1.go = "WildRose_Soldier_2";
		break;
		
		case "WildRose_Soldier_2":
			dialog.text = "Öhöm, evet, "+GetAddress_Form(NPChar)+". Ama Lord Willoughby'den bir emrim var: adaya yeni gelen herkesi uyarmam gerekiyor, birkaç gün önce bir grup köle Bishop'un plantasyonundan kaçtı. Kahrolası gözetmenler zincirlerini kırarken derin uykudaydılar herhalde. Ve bugün ben de tatlı Angelique'imin kollarında olmalıydım...";
			link.l1 = "Dur tahmin edeyim: plantasyon sahibinin malını bulmak için garnizon askerlerini mi gönderdiler?";
			link.l1.go = "WildRose_Soldier_3";
		break;
		
		case "WildRose_Soldier_3":
			dialog.text = "Elbette... Bishop, paralı askerlerinden birkaç grubu da ormana yolladı, ama bu bile ona yetmedi. Köleleri geri getiren herkese güzel bir ödül vadetti. Canlı olarak. Genelde onun için çalışanlar siyahiler olur, ama kısa süre önce bir grup donanma kaçağını getirdiler – taş ocağında pek işe yaramazlar, ama plantasyondan kaçacak kadar akıllılarmış...";
			link.l1 = "Yani onlar beyaz mıydı?";
			link.l1.go = "WildRose_Soldier_4";
		break;
		
		case "WildRose_Soldier_4":
			dialog.text = "Ne kadar beyaz olurlarsa olsunlar, şaşırdım doğrusu! Zenciler olsa hemen kaçardı, ama bunlar öldürdükleri paralı askerlerden birkaç tüfek ve pala kapıp hemen kullanmaya başladılar. Bizden birini, Bishop’un adamlarından da birkaçını yere serdiler – kalanları da deliye döndürdü bu.\nNeredeyse kendi adamlarımızı yanlışlıkla vuracaklardı, kaçaklar sanıp. Birkaç sivil de ormanda iz bırakmadan kayboldu.";
			link.l1 = "Şehir kapıları kilitli mi?";
			link.l1.go = "WildRose_Soldier_5";
		break;
		
		case "WildRose_Soldier_5":
			dialog.text = "Hayır, tabii ki hayır – şehir kuşatma altında değil. İstediğiniz yere gidebilirsiniz. Ama kaçakları kovalamaya kalkışıp çapraz ateşte kalırsanız, sonra gelip sızlanmayın. Ve hayatta kalırsanız, Lortun konağına gidip şikayet etmeye de kalkmayın – sonuçta, kendisi sadece Bridgetown halkına değil, misafirlerine de yeterince iyi niyet gösterdi.";
			link.l1 = "Ne... nazik bir davranış. Tanrı Francis Willoughby'i korusun!";
			link.l1.go = "WildRose_Soldier_6";
			link.l2 = "Ah, keşke tüm valiler Sir Willoughby kadar yeni gelenlere önem verseydi!..";
			link.l2.go = "WildRose_Soldier_7";
		break;
		
		case "WildRose_Soldier_6":
			dialog.text = "Çok komik. Gidebilirsin, kaptan.";
			link.l1 = "O halde hoşça kal, asker.";
			link.l1.go = "WildRose_Soldier_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "WildRose_Soldier_7":
			dialog.text = "Evet, işimiz çok daha az olurdu. Sizi daha fazla tutmayacağım, kaptan.";
			link.l1 = "İyi şanslar, asker.";
			link.l1.go = "WildRose_Soldier_8";
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
		break;
		
		case "WildRose_Soldier_8":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves");
		break;
		//<-- Дикая Роза
		
		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
			dialog.text = "Kaptan, sizden silahlarınızı indirmenizi rica ediyorum: şehrimizde silah çekmek yasaktır.";
			link.l1 = LinkRandPhrase("Pekâlâ, onu kaldıracağım...","Zaten yapıldı.","Dediğiniz gibi...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Siktir git!","Bunu kullanırım sanırım!","Zamanı geldiğinde onu kaldırırım.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Hey, bu silah sallamalar da neyin nesi?! Hemen yerine koy şunu!","Silahını derhal indirmeni emrediyorum!","Hey, "+GetAddress_Form(NPChar)+", insanları korkutmaktan vazgeç! Silahını indir.");
			link.l1 = LinkRandPhrase("Pekâlâ, kaldırıyorum...","Zaten yapıldı.","Dediğiniz gibi...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Siktir git!","Bunu kullanırım sanırım!","Zamanı gelince onu kaldırırım.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}
