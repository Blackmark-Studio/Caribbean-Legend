// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Sana nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bu üçüncü kez beni rahatsız ediyorsun artık...","Sanırım daha fazla sorunuz var?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит /за Англию/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Bir içki istiyorum. En iyi romundan koy bana.";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "Dinle, Callow Gaston nerede?";
                link.l1.go = "Tonzag_Letter";
            }
			//Голландский гамбит /против всех/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "Bir işiniz var mı acaba? Ya da belki önerebileceğiniz bir şey vardır?";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "İşi bitirdim. Fernando Rodriguez öldü.";
                link.l1.go = "Task_check";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Dinle, bu kasabaya bir simyacı ya da hekim geldi mi? İtalyan, otuz yaşlarında, adı Gino Gvineili. Onunla ilgili bir şey duydun mu?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Голландский гамбит /за Англию/
		case "TavernDone":
			dialog.text = "İşte içkiniz. Yeni misafirimize en iyi romumuz! Özel bir gün mü, yoksa sadece boğazınızı ıslatmaya mı uğradınız";
			link.l1 = "Aye, you could say it's a special occasion. I'm taking some slaves to Blueweld. I've recently modified my new brig's hold specifically for this purpose. I just stopped by a plantation and spoke with the overseer; he ordered a fine batch of 'black ivory' from me. So wait for me back at your tavern soon. I'll deliver the merchandise to Blueweld and then I'll be doing some more business here on Barbados, yo ho!";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "Gerçekten mi? Eh, iyi bir anlaşma için içmekte utanılacak bir şey yok! Barbados'ta iş yapacağını mı söylüyorsun? Harika! Şerefe kaptan!";
			link.l1 = "Çok teşekkür ederim, dostum. Peki... Oturacak bir yer bakayım bari.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "Gaston left town two days after your 'trader' act. You put on quite a show here, ha! Your deception was exposed quickly; this town is small and gossip travels fast. That made Gaston take his leave. No one has seen him here since. He did leave a letter for you, though.\nHe asked me to give it to you personally if you showed up here before he returned. Actually, you're not the first man looking for Gaston. There was a narrow-eyed big man and an old one, looked Spanish or Portuguese, I can't say for sure. But I can't forget his face—there was something very wrong about him...";
			link.l1 = "O mektubu ver... Teşekkürler!";
			link.l1.go = "Tonzag_Letter_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//закрыть дом Флитвуда
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//закрыть подземелье
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
			AddMapQuestMarkShore("Shore24", true);
		break;
		
		//Голландский гамбит /против всех/
		case "Tonzag_check"://начинаем проверять нашего ГГ по всем статьям
			if(sti(pchar.reputation.nobility) > 48)//высокая репа
			{
				// belamour legendary edition покажем критерии
				Notification_Reputation(false, 48, "high");
				PlaySound("Voice\English\hambit\Ercule Tongzag-03.wav");
				dialog.text = "Bir alçağın hizmetlerine ihtiyacım yok. Sana verebileceğim bir işim de yok.";
				link.l1 = "Hey, hey. Ağzını topla biraz, dostum!";
				link.l1.go = "exit";
				break;
			}
			bool bOk = GetSummonSkillFromName(pchar, SKILL_F_LIGHT) > 34 || GetSummonSkillFromName(pchar, SKILL_FENCING) > 34 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) > 34 || GetSummonSkillFromName(pchar, SKILL_PISTOL) > 34;
			if(!bOk)//слабое фехтование
			{
				// belamour legendary edition покажем критерии -->
				Notification_Skill(false, 35, SKILL_F_LIGHT);
				Notification_Skill(false, 35, SKILL_FENCING);
				Notification_Skill(false, 35, SKILL_F_HEAVY);
				Notification_Skill(false, 35, SKILL_PISTOL);
				// <--
				dialog.text = "Kaptan, fazla yumuşaksın. Bana senden biraz daha namlı bir dövüşçü lazım. O kemerinde sallanan çeliği kullanmayı öğrendiğinde tekrar gel. Biraz daha isabetli atış da fena olmazdı.";
				link.l1 = "Anladım. O zaman sana sonra uğrarım.";
				link.l1.go = "exit";
				break;
			}
			PlaySound("Voice\English\hambit\Ercule Tongzag-02.wav");
			dialog.text = "Hm... Aslında tam zamanında geldin. Hemen halledilmesi gereken bir işim var. Eğer kendini iyi gösterirsen, seni bazı etkili insanlarla tanıştırırım. Şimdi iyi dinle, yapman gerekenler şunlar.";
			link.l1 = "Tamamen dinliyorum.";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "Sevilla'dan yeni gelen bir hidalgo, Avrupa'daki bir düellonun istenmeyen sonuçlarından kaçmaya çalışıyor. Fakat intikamın sınırı yoktur; İspanyol soylu bir aile bu hidalgo'nun ölümünü istiyor. Onların isteğini yerine getir, ne gerekiyorsa yap.\nAdamın yüzüğüyle birlikte parmağını kanıt olarak getir. Ayrıca cesedinde bulduğun diğer eşyaları da getir. Bu işi almaya hazır mısın?";
			link.l1 = "Ödeme iyiyse, ben varım.";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "Bir suikastçi olarak çalışmak mı? Asla!";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//признак, что против всех уже бралась
		break;
		
		case "Tonzag_exit":
			dialog.text = "O zaman defol git ve konuştuklarımızı unut.";
			link.l1 = "Gidiyorum.";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//откат к двум другим вариантам
			pchar.questTemp.HWIC.Fail3 = "true";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
		break;
		
		case "Tonzag_task_1":
			dialog.text = "Ödülün 30.000 sekizlik olacak, iyi para. Üstelik, cesedinde bulduğun her madeni parayı da alabilirsin. Şimdi, detayları konuşalım. Adı Don Fernando Rodriguez, 35 yaşında, uzun boylu, esmer, askeri bir subay gibi giyinir. İyi bir denizci ve tecrübeli bir kılıç ustasıdır\nNerede olduğunu söyleyemem, bildiğim tek şey Karayipler'de bir yerde olduğu\nOnu bulana kadar her İspanyol şehrini ara. İki ayın var. Son bir şey: Üzerinde ne taşıdığını biliyorum, o yüzden herhangi bir eşyayı benden saklamayı aklından bile geçirme. Sorun var mı?";
			link.l1 = "Hiçbir sorum yok. Yoluma devam ediyorum!";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //таймер
			//SetFunctionExitFromLocationCondition("CreateMapMarksTonzag", pchar.location, false);
			AddQuestRecord("Holl_Gambit", "3-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила . чтобы вышел из архива																				  
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Lucas"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Self.SpainCity, true);
			AddLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity+"_tavernkeeper"), "questmarkmain");
		break;
		
		case "Task_check":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Yüzüklü parmak yanında mı? Göster bakalım.";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "Evet, tabii ki. Buyurun.";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "Hayır. Fernando gemisiyle birlikte suya gömüldü, parmak da Fernando'yla birlikte battı.";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "Yüzüklü parmak, sözleşmede zorunlu bir şarttı. Müşterinin öldüğüne dair kanıt olarak sunulacaktı. Kim bilir, Rodriguez batık gemiden kıyıya ulaşabildi mi? Kontrol ettin mi? Hayır. Aslında görevi yerine getiremedin, bu yüzden anlaşmamız sona erdi. Her şey gönlünce olsun.";
			link.l1 = "Ama ondan kurtuldum. Artık yok! Kahretsin seni... Karayipler'de yapılacak daha çok şey var. Hoşça kal.";
			link.l1.go = "exit";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "Harika! Parmağı kendime saklayacağım. Şimdi, bakalım ceplerinde ne varmış. Getirdiklerine bir göz atalım.";
			link.l1 = "Devam et, bir göz at...";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "Aha, tam da ihtiyacım olan buydu. Aferin! Gerçekten iyi iş çıkardın. Senden çok memnunum.";
				link.l1 = "Teşekkür ederim! İyi yapılmış bir iş için övgü almak her zaman güzeldir.";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "Hm... Seni uyarmıştım, Rodriguez'in asla vazgeçemeyeceği şeyleri biliyorum. Ve burada ihtiyacım olanı göremiyorum. O eşyaları cebe mi attın? Yoksa kaybettin mi? Artık fark etmez. Seninle daha fazla uğraşmak istemiyorum. Defol buradan.";
				link.l1 = "Ah, kahretsin sana...";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
				{
					AddMapQuestMarkCity("Villemstad", false);
					AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
				}
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
				{
					AddMapQuestMarkCity("SentJons", false);
					AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
				}
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Söz verdiğim gibi ödülünüz burada, otuz bin. Ayrıca size ekstra bir işim var; sorumluluğu ve riski yüksek ama ücreti de ona göre artacak: 40.000 peso.";
			link.l1 = "Hevesle dinliyorum. Sıradaki müşteri kim?";
			link.l1.go = "Fleetwood_house";	
		break;
		
		//2 задание
		case "Fleetwood_house":
			PlaySound("Voice\English\hambit\Ercule Tongzag-05.wav");
			dialog.text = "Bu sefer, bir adamı değil, bir eşyayı avlayacaksın. Antigua’daki Richard Fleetwood’un evine gizlice girip günlüğünü çalmalısın. Kendisi bir İngiliz kaptanıdır. Ev iyi korunuyor ve Richard’ın kendisi de nadiren evine uğrar\nPlan basit. St. John’s valisi on gün içinde özel bir davet verecek ve Fleetwood da orada olacak. Gece saat bir ile üç arasında evine girmelisin. İçeride sadece bir asker olacak\nOndan kurtul. Richard’ın dairesinde günlüğü ara. Bu anahtarı al.";
			link.l1 = "Hm... İlginç. Ne yapmam gerektiğini anladım. Hazırım, başlayabilirim!";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "Dikkatli ol. Sana belirttiğim tarihten önce eve gizlice girme. Yoksa, en iyi ihtimalle seni kapı dışarı ederler, en kötü ihtimalle ise kendini parmaklıklar ardında bulursun. Tarih ve saati bana tekrar söyle.";
			link.l1 = "Tam on gün sonra, gece bir ile üç arası.";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "Peki. Gidebilirsin. Bol şans!";
			link.l1 = "Teşekkür ederim, Gaston.";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//комнату закроем
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//положим в комод СЖ
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//и песочные часы
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//4 солдат в доме
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//таймер
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//доступно открывание двери
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//если надумает раньше заявиться
			AddMapQuestMarkCity("sentjons", true);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Hayır, duymadım. Şifacılarımız ve hekimlerimiz var, ama o isimde biri yok.","Böylesine garip bir ismi ilk kez duyuyorum. Hayır, bahsettiğiniz adam buraya hiç uğramadı.","Bizde hiç simyacı yok. Hekimlerimiz var, ama böyle tuhaf bir isimle kimse yok.");
			link.l1 = "Anladım. Ne yazık. Aramaya devam edeceğim!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

string FindSpainCity()//Jason выбрать радномный испанский город - пусть побегает
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
