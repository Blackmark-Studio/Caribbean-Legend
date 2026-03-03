//Jason общий диалог уличных контриков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Sana bir sorum var.","Bilgiye ihtiyacım var.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = "Hey, kaptan! Evet, sen. Buraya gel, sana bir teklifim var...";
					link.l1 = "Peki, mesele ne?";
					link.l1.go = "passenger";
					link.l2 = "Aceleyle gidiyorum, dostum. Belki bir dahaki sefere.";
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Hey, kaptan, aslında meşgulüm. Ne istiyorsun?","Ne istiyorsun, kaptan?","Kaptan, konuşacak havamda değilim. Ne istiyorsun?");
				link.l1 = "Selam, "+GetAddress_FormToNPC(NPChar)+". Bir dakika, senden bir şey duymak istiyorum.";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Sana bir sorum var.","Bilgiye ihtiyacım var.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Önemli değil, ben meyhaneye gidiyorum...";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = "Hm. Bir geminin kaptanısın ama bir tüccara benzemiyorsun. Cebinde birkaç sikke var gibi görünüyor... Bir avuç dublon karşılığında ilginç bilgiler almaya ne dersin?";
				link.l1 = "Önce, verdiğin bilginin bir kuruş etmeye değer olduğunu kanıtla.";
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = "Evet, kaptan, öyle. İstediğimden çok daha fazlasına değer. Altını ver, sana ne zaman ve hangi gemiyle çok önemli birinin yola çıkacağını söyleyeyim. Onu çok iyi bir fiyata fidyeyle kurtarabilirsin... Hatta alıcının adını da söyleyeceğim. Anlaştık mı?";
				link.l1 = "Olmaz! Ben kaçıran biri değilim. Defol git!";
				link.l1.go = "exit_quest";
				link.l2 = "Ve bana gerçeği söylediğini nereden bileceğim?";
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+hrand(5)*10;
				dialog.text = "Seni kandırmak akılsızlık olurdu, deniz kurdu. Bu kasabada yaşıyorum ve başıma iş almak istemem. Sadece "+sti(pchar.GenQuest.Marginpassenger.Dublon)+" doblon ver, sana her şeyi anlatayım. Çok daha fazlasını kazanırsın.";
				if (PCharDublonsTotal() >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Haklısın. Altını al ve konuşmaya başla.";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Şu anda yanımda yeterince param yok.";
				link.l2.go = "passenger_3";
				link.l3 = "Benimle dalga mı geçiyorsun? Boş vaatler için altın mı vereceğim? Defol...";
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = "Sen istemiyor musun? Peki, Kaptan. Birkaç gün daha bekleyebilirim, bu bilgi de öyle. Altının olduğunda beni bul. Beni bulmak zor olmayacak... bugün, ha-ha-ha!";
				link.l1 = "Bana öyle dişlerini gösterme. Peki, altınları getireceğim... fikrimi değiştirmezsem tabii. ";
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = "Altınımı getirdin mi?";
				if (PCharDublonsTotal() >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Evet. Al şunu. Şimdi yalan söylemeye bile kalkışma...";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Henüz değil. Belki sonra...";
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveDublonsFromPCharTotal(sti(pchar.GenQuest.Marginpassenger.Dublon));
				pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
				pchar.GenQuest.Marginpassenger.City = npchar.city;
				pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city); 
				pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
				pchar.GenQuest.Marginpassenger.Days = 10+hrand(5);
				pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
				pchar.GenQuest.Marginpassenger.Chance = 0.8+frand(0.4);
				SelectMarginpassengerParameter();
				log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
				dialog.text = "Barutunu kuru tut, yakında ihtiyacın olacak, Kaptan. Şimdi dinle, "+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+" kolonimizden bir gemi ayrılacak, gemi "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" adlı '"+pchar.GenQuest.Marginpassenger.ShipName+"' ve o da yöneliyor olacak "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+". Bir yolcu olacak -  "+pchar.GenQuest.Marginpassenger.Text+",   adında "+pchar.GenQuest.Marginpassenger.q1Name+"\nKaptan "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")+"Gen"))+"   bütün tüccarlar gibi ödlek bir korkak, ha-ha-ha! Belki de dövüşmekten tamamen kaçarsın. Şeytanın korkusunu içine sal, o zaman hedefi kendi elleriyle teslim eder, he-he\nAnladığın gibi, "+pchar.GenQuest.Marginpassenger.Text1+", muhtemelen paralarını alırsın, evet, ama yerel yetkililer peşine düşer. Avını buraya getirmen daha iyi olur "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+". Orada   adında bir adam bulacaksın "+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+" ve adını bile söylemene gerek kalmayacak. Adamını nerede fidye ile kurtaracağına sen karar verirsin, ama boyundan büyük işlere kalkışma... Ama "+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+" Doubloon isteyebilirsin, tabii. Anladın mı?";
				link.l1 = "Evet. Gemime geri döneceğim ve bunu günlüğe yazacağım.";
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = "Kesinlikle! Doğru seçim. Güzel, Kaptan, bu kolay işte sana bol şans. Ah evet, neredeyse unutuyordum: "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" limandan değil, yakındaki koylardan birinden ayrılacak. O yüzden gözünü açık tut. İyi şanslar ve altın için teşekkürler!";
				link.l1 = "Rica ederim. Hepsini bir gecede harcama.";
				link.l1.go = "exit_quest";
				npchar.lifeday = 0;
				ReOpenQuestHeader("Marginpassenger");
				AddQuestRecord("Marginpassenger", "1");
				AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
				AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity));
				AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
				AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
				AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
				AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
				AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Voc")));
				AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
				AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
				pchar.GenQuest.Marginpassenger = "begin";
				SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
			break;
			
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Dinle, sakin ol ve silahını kınına koy.","Dinle, sakin ol ve silahını kınına koy.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi olsun.");
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase("Lafı dolandırma Kaptan. Ne istiyorsan söyle!","Tamam, peki. Ne istiyorsun?","Soruların mı var? Peki denizci, seni dinliyorum.");
			link.l1 = LinkRandPhrase("Bana en son dedikoduları anlatır mısın?","Burada son zamanlarda ilginç bir şey oldu mu?","Karayipler'de neler oluyor?");
			link.l1.go = "rumours_marginal";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (hrand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "women_"+(rand(5)+11);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = "He wants to marry her and will pay a significant sum for the girl.";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "store keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the store keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_"+(rand(9)+11);
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = "He has been planning to ingratiate himself with this family and he will pay a lot for the prisoner ";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "trader's relative, shipmaster's";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipmaster";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	if (sti(pchar.rank) < 5) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 17) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 17 && sti(pchar.rank) < 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
