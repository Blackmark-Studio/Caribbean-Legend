void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Kasabada alarm verilmiş. Herkes seni arıyor! Senin yerinde olsam burada fazla oyalanmazdım.","Tüm kasaba muhafızları seni bulmak için şehri didik didik arıyor. Ben aptal değilim ve seninle konuşmayacağım!","Kaç, dostum, yoksa askerler seni lime lime eder..."),LinkRandPhrase("Ne istiyorsun, alçak?! Şehir muhafızları şu anda peşinde. Uzaklaşamayacaksın, pis korsan!","Evimden defol, katil! Muhafızlar!!","Senden korkmuyorum, velet! Yakında seni asacaklar, kaçamayacaksın..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, alarm için pek endişelenmiyorum...","Beni yakalama şansları yok."),RandPhraseSimple("Kapa çeneni, "+GetWorkTypeOfMan(npchar,"")+", yoksa o lanet dilini koparırım!","Heh, "+GetWorkTypeOfMan(npchar,"")+", sen de bir korsanı avlamak istiyorsun! Dinle dostum, sakin olursan hayatta kalırsın..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! Sizi daha önce hiç görmedim, señor. Kaptan olduğunuzu varsaymaya cesaret edebilir miyim... Doğru mu tahmin ettim? Benim adım "+GetFullName(npchar)+", ve dükkanım hizmetinizde. Altın, gümüş ve meraklı birinin ilgisini çekecek çok daha fazlası.";
				Link.l1 = "Anladım. Ben "+GetFullName(pchar)+" . Tanıştığımıza memnun oldum, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", señor! Sizi mağazamda tekrar görmekten memnun oldum. Biraz altın külçesi almak ister misiniz? Yoksa bugün minerallere mi ilginiz var?";
				link.l1 = "   Mallarını göster bana, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "Hayır, hiçbir şeye ihtiyacım yok, "+npchar.name+". Sadece sana merhaba demek için uğradım.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ben de öyleyim, señor. Mallarıma bir göz atmak ister misiniz? Eminim ilginizi çekecek bir şeylerim vardır.";
			link.l1 = "Buraya ilk kez geliyorum ve bu yerleşim hakkında biraz daha bilgi almak istiyorum.";
			link.l1.go = "info";
			link.l2 = "O halde, satılık neleriniz var gösterin bana.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "Our small town was built thanks to the gold mine. They extract gold ore, silver, and golden nuggets. Sometimes even gems. We used to have only a garrison here until friendly Indians and some white settlers joined us\nIgnacio Ortega built a tavern and made our lives a bit cheerier. All kinds of adventurers visit this place with the foolish intention of robbing us. We don't have a court here, so their numbers dropped after we hanged several idiots right in the middle of town\nGold ore is sent to the ships under the protection of soldiers and friendly Indians; nuggets, however, you can buy right here in this store\nBesides, I sometimes have very interesting minerals to offer, so visit me when you have time, I always resupply my stock.";
			link.l1 = "İlginç hikaye için teşekkürler! Bunu aklımda tutacağım.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Gündüz vakti soygun mu olurmuş!!! Burada neler oluyor?! Bekle, dur bir, dostum...","Hey, ne yapıyorsun orada?! Beni mi soymaya çalışıyorsun? Şimdi yandın...","Dur, ne halt ediyorsun sen? Demek ki hırsızmışsın! Buraya kadarmış, alçak...");
			link.l1 = LinkRandPhrase("Şeytan!!","Vay canına!!","Ah, kahretsin!");
			link.l1.go = "fight_owner";
		break;
		
		case "fight_owner": // лесник . выход из диалога . если копался в сундуках. 
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
