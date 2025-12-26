//navy 26.07.06
//генератор дуэлей...
//в диалоге НПС делаем линк с проверкой флага оскорбления... по нему переход на "outraged"
//если НПС сделал что-то ГГ (продажа фальшивки) или ГГ наехал на НПС, вешаем на него флаг.
//для некоторых, например ПГГ, можно делать переход сразу на вызов: "let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//флаг убираем
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Beni nasıl aşağılamaya cüret edersin, seni serseri?!","Bu sözlerin bedeli sana pahalıya patlayacak!"),RandPhraseSimple("Onuruma hakaret ettin, "+GetAddress_Form(NPChar)+"! Ve bunun bedelini ödeyeceksin.","Sen ne cüretle böyle konuşuyorsun? Hemen sözlerini geri al!"));

		//это такая засада.. чтобы читали текст :)
		MakeRandomLinkOrderTwo(link, 
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("Ha?! I don't even want to stain my sword with your blood!", "Ha?! I don't even want to stain my sword with your blood!"), 
				RandPhraseSimple("I am always at your service!", "I am not going to choose words while speaking with the rabble!")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I didn't mean it!", "I fired up..."), 
				RandPhraseSimple("That was a mistake. I am sorry.", "I took you for someone else, " + GetAddress_FormToNPC(NPChar) + ". Please forgive me.")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,RandPhraseSimple("Kulaklarını keseceğim!","Kalbini yerinden sökeceğim!"),RandPhraseSimple("Umarım mazeretlerini dinlerim, yoksa kendimi tutacağıma söz veremem!","Ne anlama geldiğinin farkında mısın... gerçekten mi?"));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I hope that your saber is as swift as your tongue!", "My blade will speak for me."), 
				RandPhraseSimple("I challenge you to a duel!", "That's a matter of honor!")), "let_s_duel",
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("I think I am not ready yet!", "Think, we shouldn't get excited! These are words only!"), 
				RandPhraseSimple("I remembered, I am waiting. All blessings...", "Ah! Seems, my ship is sailing already. Bye.")), "change_mind");
		break;

	case "let_s_duel":
		//проверка на начатые дуэли.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "Önce diğerleriyle işini hallet, sonra konuşuruz.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "Zaten bir anlaşmaya vardık.";
			}
			link.l1 = RandSwear()+"Ah, bunu nasıl unuttum...";
			link.l1.go = "exit";
			break
		}
		//может отказаться.
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("Düello mu?! Defol git, zamanımı harcamaya değmezsin.","Düello mu? O onuru hak etmiyorsun! Defol git!");
			link.l1 = RandPhraseSimple("Pekala...","Sanırım bekleyebilirim...");
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("Sence öyle mi? O kadar emin olma, alçak!!!","Gerçekten mi?! Bakalım kanının rengi neymiş!");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple("Düello mu diyorsun? Benim için sorun yok. Silahlarımız kılıçlar ve tabancalar olacak.","Bir kılıcı tutabiliyor musun?");
		link.l1 = RandPhraseSimple("Merhamet için dizlerinin üstüne çöküp yalvaracaksın.","Seni çıplak ellerimle boğacağım, alçak herif!");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text+" Ya da denize açılırız ve kim kimmiş görürüz!","Düello mu?!! Ha, seni böcek gibi ezeceğim! Nasıl ölmek istediğini seç!");
			link.l2 = RandPhraseSimple("Denizde, benden iyisi yoktur.","Gemim senin eski tekneni kolayca batırır!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "Fikrimi değiştirdim...";
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("Liman’da gemini göremiyorum...","En azından eski püskü bir tekne bulana kadar kaybol!");
		link.l1 = RandPhraseSimple("Benim hatam...","O zaman seni terk ediyorum.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "Pekala, seni koyun çıkışında bekleyeceğim...";
			link.l1 = "Seni fazla bekletmeyeceğim.";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	//на суше
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear()+RandPhraseSimple("Kılıcını çek, bakalım kanının rengi neymiş!","Pekâlâ, eğer ölümüne susadıysan...");
		link.l1 = RandPhraseSimple("Çok fazla şahit olmayan bir yere gitsek iyi olur. Şehir kapılarının ilerisinde tam uygun bir yer biliyorum. Orada buluşalım "+iHour+" saat.","Sakin ol. Böyle şeyler şahitler olmadan halledilir. İçeri gel "+iHour+"  saat şehre kadar.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("Pekâlâ, madem bu kadar çok ölmek istiyorsun...","Lanet olsun! Kendi gözlerinle Cehennem'i göreceksin, sana yardım edeceğim!");
		link.l2.go = "fight_right_now";
		link.l3 = "Fikrimi değiştirdim...";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear()+RandPhraseSimple("Bence şehir kapılarının dışına geçsek iyi olur. Orada seni bekleyeceğim "+pchar.questTemp.Duel.WaitTime+" saat. Gecikme!","Burası anlaşmazlıkları çözmek için en uygun yer değil. Şehirden ayrılsak iyi olur. In "+pchar.questTemp.Duel.WaitTime+" saat içinde orada olacağım.");
			link.l1 = RandPhraseSimple("Sen o onuru hak etmiyorsun! Kendini savun!","Vaktim yok! Kılıcını çek!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("Pekala, hadi biraz dolaşalım.","Muhtemelen haklısın. Kapıların ilerisinde buluşalım.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение "пойдём выйдем" рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("Bu onuru hak etmiyorsun! Kendini savun!","Vaktim yok! Tam burada, tam şimdi!");
		link.l1 = RandPhraseSimple("Pekâlâ, madem bu kadar ölmek istiyorsun...","Lanet olsun! Cehennemi kendi gözlerinle göreceksin, sana yardım edeceğim!");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("Pekala, hadi biraz dolaşalım.","Muhtemelen haklısın. Kapıların ilerisinde buluşalım.");
			link.l1 = RandPhraseSimple("Orada seni bekliyor olacağım.","Vakit kaybetme.");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	//что ж, пойдём выйдем
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			//где?
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			//приходит ко времени.
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			//на случай, если не дождется, часа вполне достаточно
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = "Yani, hazır mısın?";
		link.l1 = "Evet. Bakalım kim daha iyi adammış!";
		link.l1.go = "fight_right_now";
		link.l2 = "Hayır, özrümü sana getirmeye karar verdim. Hatalıydım, kendimi kaybettim.";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("Hey, bak, bunu düşündüm ve şimdi hatalı olduğumu anladım. Özür dilerim.","Kahretsin! Hepsi şu lanet romun suçu!!! Affedin beni, "+GetSexPhrase("kardeşim","kız kardeş")+"!");
			link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Hayır, artık beni ancak kanın tatmin edebilir!","Kılıcını çek ve ağlamayı bırak artık!"),RandPhraseSimple("Hayır! Hesaplaşma istiyorum!","Ailene yüz karasısın! Çek kılıcını!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar,RandPhraseSimple("Pekâlâ, kabul ediyorum. Biraz fazla heyecanlandık.","Arkadaşlar arasında kim skor tutar ki!"),RandPhraseSimple("Muhtemelen haklısın. Böyle önemsiz şeyler için kan dökmemeliyiz.","Cömertliğimin sınırı yok! Affedildin!"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//дуэли быть!
	case "fight_right_now":
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":	
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();	
		break;
		
	//передумал, э... не хорошо ;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("O zaman defol!","Öyleyse defol git, yoksa fikrimi değiştiririm."),RandPhraseSimple("O halde, sizi daha fazla oyalamayayım!","O zaman fikrimi değiştirmeden gitmen daha iyi olur."));
		link.l1 = "Zaten gidiyorum...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Defol!","Gözümün önünden kaybol, yoksa fikrimi değiştiririm."),RandPhraseSimple("Sana yardımcı olabilir miyim?","Bir şey ister misin?"));
		link.l1 = "Gidiyorum.";
		link.l1.go = "peace";
		break;

	//мир и все такое.
	case "peace":
		LAi_SetWarriorType(NPChar);
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
	}
}
