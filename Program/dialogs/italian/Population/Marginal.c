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
			dialog.text = "Cosa vuoi?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Ho una domanda per te.","Mi serve informazione.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = "Ehi, capitano! Sì, tu. Vieni qui, ho un affare per te...";
					link.l1 = "E qual è l'accordo?";
					link.l1.go = "passenger";
					link.l2 = "Sono di fretta, amico. Forse la prossima volta.";
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Ehi, capitano, sono occupato in realtà. Di cosa hai bisogno?","Cosa vuoi, capitano?","Capitano, non sono dell'umore per parlare. Cosa vuoi?");
				link.l1 = "Saluto, "+GetAddress_FormToNPC(NPChar)+". Aspetta un minuto, voglio che mi dici qualcosa.";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Ho una domanda per te.","Mi serve informazione.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Non è niente, sono sulla via per la taverna...";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = "Hm. Sei il capitano di una nave ma non sembri un mercante. Sembra che tu abbia qualche moneta in tasca... Che ne dici di ottenere qualche informazione interessante in cambio di un pugno di dobloni?";
				link.l1 = "Prima, dimostra che le tue informazioni valgono un solo pezzo da otto.";
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = "Lo è, cap, lo è. Costa molto più di quanto chiedo. Mi dai l'oro e ti dirò quando e su quale nave una certa persona molto importante salperà. Sarai in grado di riscattare questa per un prezzo molto buono... Ti dirò anche il nome dell'acquirente. Affare?";
				link.l1 = "Ma neanche per sogno! Non sono un rapitore. Levati dai piedi!";
				link.l1.go = "exit_quest";
				link.l2 = "E come posso sapere che stai dicendo la verità?";
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+hrand(5)*10;
				dialog.text = "Sarebbe molto imprudente imbrogliarti, cane di mare. Vivo in questa città e non ho bisogno di problemi. Solo per "+sti(pchar.GenQuest.Marginpassenger.Dublon)+" darò informazioni complete per i dobloni. Guadagnerai molto di più.";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Hai ragione. Prendi l'oro e inizia a parlare.";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Non ho abbastanza monete con me ora.";
				link.l2.go = "passenger_3";
				link.l3 = "Stai scherzando? Pagare oro vero per promesse vuote? Vattene...";
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = "Non ce l'hai? Va bene, cap. Posso aspettare ancora qualche giorno e anche queste informazioni possono. Cercami quando avrai il tuo oro. Non sarà difficile trovarmi... oggi, ah-ah-ah!";
				link.l1 = "Non mostrare i tuoi denti in quel modo. Va bene, ti porterò l'oro... se non cambio idea. ";
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = "Hai portato il mio oro?";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Sì. Prendilo. Non provare nemmeno a mentire adesso...";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Non ancora. Forse più tardi...";
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveItems(pchar, "gold_dublon", sti(pchar.GenQuest.Marginpassenger.Dublon));
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
				dialog.text = "Tieni la tua polvere asciutta, ne avrai bisogno presto, cap. Ora ascolta, in "+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+"una nave salperà dalla nostra colonia, la nave è "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" chiamato '"+pchar.GenQuest.Marginpassenger.ShipName+"' e si dirigerà verso "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+". Ci sarà un passeggero -  "+pchar.GenQuest.Marginpassenger.Text+", chiamato "+pchar.GenQuest.Marginpassenger.q1Name+"\nIl capitano "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")+"Gen"))+" è un vigliacco giallo come tutti i mercanti, ah-ah-ah! Forse, eviterai anche ogni combattimento. Basta mettergli paura con il diavolo e dovrebbe consegnare lui stesso l'obiettivo, eh-eh\nCome capisci, "+pchar.GenQuest.Marginpassenger.Text1+", probabilmente otterrai le tue monete, sì, ma le autorità locali ti cacceranno a morte dopo. Sarebbe meglio portare la tua preda a "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+". Troverai lì un uomo di nome "+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+" e non avrai nemmeno bisogno di dire il tuo nome. È tua la decisione dove riscattare il tuo uomo, ma non mordere più di quanto puoi masticare... Ma "+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+" sicuramente puoi chiedere dei dobloni. Capito?";
				link.l1 = "Sì. Sto per tornare sulla mia nave e scriverlo nel registro.";
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = "Esatto! Buona scelta. Bene, cap, buona fortuna in questo compito facile. Ah sì, quasi me ne dimenticavo: "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" salperà non dal porto ma da una delle baie vicine. Quindi stai attento. Buona fortuna e grazie per l'oro!";
				link.l1 = "Prego. Non spendere tutto in una sola notte.";
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
			dialog.text = NPCharSexPhrase(NPChar,"Ascolta compagno, calmati e infila la tua arma.","Ascolta compagno, calmati e infila la tua arma.");
			link.l1 = LinkRandPhrase("Bene.","Bene.","Come desideri.");
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase("Non girarci intorno, cap. Dì quello che vuoi!","Oh, bene. Cosa vuoi?","Domande? Bene, marinaio, sto ascoltando.");
			link.l1 = LinkRandPhrase("Potresti dirmi l'ultimo pettegolezzo?","È successo qualcosa di interessante qui di recente?","Cosa sta succedendo nei Caraibi?");
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
