//Jason общий диалог дворян
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

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
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("Mh. Navigi sotto la bandiera di "+NationNameGenitive(sti(pchar.nation))+", compagno. Che diavolo stai facendo qui, nella nostra città? Sparisci!","Non voglio essere sospettato come un amico di "+NationNameAblative(sti(pchar.nation))+"! Sparisci o chiamerò le guardie!","È la tua ultima possibilità di scappare. Altrimenti avrai solo te stesso da biasimare.","Ti ho avvertito. Ora pagherai per la tua insolenza, bastardo!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Un tale patriota, eh!","Bene, bene, calmati. Me ne sto andando.","Non fare tanto rumore. Me ne sto andando.","Cosa?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat("Guarda un po'! E come fanno le nostre guardie a permettere a un bastardo come te di girare liberamente per la città? Impossibile...","Vattene, non voglio nemmeno parlare con te! Boia...","È la tua ultima possibilità di scappare. Altrimenti avrai solo te stesso da incolpare.","Ti ho avvertito. Ora pagherai per la tua impudenza, bastardo!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ehi ehi! Mostrami più rispetto, signore!","Guardati, santo...","Calmati...","Cosa?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)//дворянин-пассажир
				{
					dialog.text = "Saluti, "+GetAddress_Form(NPChar)+". Vedo che sei il capitano di una solida nave. Vorrei chiederti di fare qualcosa. Puoi accettare o rifiutare.";
					link.l1 = "Sto ascoltando, "+GetAddress_FormToNPC(NPChar)+". Cosa intendi?";
					link.l1.go = "passenger";
					link.l2 = "Mi scusi, "+GetAddress_FormToNPC(NPChar)+", ma sono di fretta.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsUniversalShipType(pchar), IsMerchantShipType(pchar)))//дворянин-пассажир
				{
					dialog.text = "Saluti, "+GetAddress_Form(NPChar)+". Vedo che sei il capitano di una nave solida. Voglio chiederti di fare qualcosa. Puoi accettare o rifiutare.";
					link.l1 = "Sto ascoltando, "+GetAddress_FormToNPC(NPChar)+". Cosa intendi?";
					link.l1.go = "passenger";
					link.l2 = "Mi scusi, "+GetAddress_FormToNPC(NPChar)+", ma sono di fretta.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = "Aha, è bello vedere un gentiluomo nella nostra piccola città! Sono sicuro che vieni direttamente dall'Europa. Ascolta, voglio chiederti di aiutarmi - da gentiluomo a gentiluomo. Spero che mi capirai correttamente.";
					link.l1 = "Buon giorno a lei, signore. Sto ascoltando.";
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = "Buongiorno, "+GetAddress_Form(NPChar)+"! È un piacere incontrare un gentiluomo per le strade della nostra città! Mi permetteresti di rubarti qualche minuto?";
					link.l1 = "Certo, signore. Sto ascoltando.";
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = "Buongiorno a te, capitano! Sono lieto di vederti perché sembri un uomo in grado di risolvere problemi.";
					link.l1 = "Dipende dal problema. Sono specializzato nel risolverli con violenza, è quello che stai cercando, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple("Ciao, "+GetAddress_Form(NPChar)+". Vuoi qualcosa da me?","Cosa desidera, signore?");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Non prenderò molto del tuo tempo, voglio solo chiedere...";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Mi serve informazioni sulla tua colonia.","Mi serve informazione.");
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("L'intera città è in subbuglio - è arrivato don Fernando de Alamida, l'ispettore reale. Sai, ho visto molto qui, ma questo... Non è la sofferenza che cambia le persone, ma come la affrontano. Dicono che sia diventato un uomo diverso dopo la morte di suo padre. Ora non troverai un servitore più incorruttibile e... spietato della Corona in tutto l'Arcipelago.","Guarda solo la 'Santa Misericordia'! Dicono che lo stesso re l'abbia ordinata costruita secondo disegni speciali. E nota - non un solo graffio. Come se la stessa Vergine Maria la proteggesse. Anche se ho sentito voci... forse non è affatto la Vergine.","Sai quante volte hanno cercato di uccidere don Fernando? Dodici attacchi in acque aperte - e solo nell'ultimo anno! Beh, con un equipaggio così leale e addestrato, e sotto la protezione del Signore - sopravviverà anche al tredicesimo!"),LinkRandPhrase("Hai sentito? Don Fernando de Alamida è arrivato nella nostra città, e dicono che si trovi da qualche parte per le strade in questo momento. Mi piacerebbe vederlo con i miei stessi occhi...","Un uomo complicato, questo don Fernando. Alcuni dicono che sia un salvatore, che sta purificando la Madrepatria dalla sporcizia. Altri sussurrano che qualcosa in lui si è spezzata dopo la morte del padre e presto piangeremo tutti. Ma ti dirò questo: non aver paura di lui. Temi coloro che lo hanno reso quello che è.","Un uomo così affascinante, questo don Fernando! Ma sai cosa è strano? È come se non notasse nessuno. Tutto dovere e servizio. Ho sentito dire che c'era una ragazza... ma dopo aver incontrato un certo prete, ha completamente rifiutato i piaceri mondani. Come se avesse fatto un voto."),RandPhraseSimple(RandPhraseSimple("Maledetto ispettore! Mentre lui è qui - la città è come morta. Nessun commercio, nessun divertimento. Anche respirare, sembra, deve essere più silenzioso. E sai cosa è più spaventoso? È lo stesso in ogni porto. Come un orologio. Sua Maestà Reale non avrebbe potuto inventare appositamente questa tortura per tutti noi!","Don Fernando ha visitato di nuovo l'orfanotrofio. Dona generosamente, prega per ore. Un uomo così degno dovrebbe essere preso come esempio da quei maledetti imbroglioni!"),RandPhraseSimple("Ah! 'Santo' Fernando ha chiuso tutte le case di tolleranza di nuovo. Beh, non importa, presto salperà e riapriranno subito.","È arrivato l'isp... l'ispettore, questo è sicuro! Don Fernando de Almeyda, o come diavolo si chiama, Alamida! Così importante che persino il governatore cammina in punta di piedi attorno a lui. Dicono che ti guardi negli occhi e veda tutti i tuoi peccati in un attimo. Spaventoso!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("Cosa? Di nuovo? Non ho tempo per te. Cerca qualcun altro con cui parlare. Ci sono molti plebei in giro per le strade. E devo andare, ci sarà un banchetto stasera nella residenza del governatore e devo preparare il mio abito...","No, ora è davvero fastidioso! Non lo capisci? O sei un testardo?","Signore, sto cominciando a sospettare che tu non sia solo un idiota, ma un rozzo e un villano. Ti avverto, lasciami in pace o te ne pentirai per avermi disturbato.","Abbastanza. Ti insegnerò, maleducato!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Capisco. Addio.","Sì-sì, ho solo dimenticato quello che volevo chiedere...","Hai capito male...","Cosa?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase("Continua.","Cosa vuoi?","Domande? Bene, marinaio, sto ascoltando.");
			link.l1 = LinkRandPhrase("Non mi diresti l'ultimo pettegolezzo della tua città?","È successo qualcosa di interessante qui di recente?","Qualche notizia dai Caraibi, signore?");
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				dialog.text = ""+GetSexPhrase("Signore","Signora")+", ho bisogno di arrivare alla colonia"+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+", non appena possibile è su "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", per "+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+". La tua nave sembra solida e veloce rispetto alla maggior parte di queste piccole tinozze che navigano qui. Posso pagarti "+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+". Cosa diresti?"; // belamour gen
			}
			else
			{
				dialog.text = "Ciao, "+GetSexPhrase("signore","signora")+"! Ho bisogno di arrivare a "+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"! Questo è su "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", a proposito. Sì, sì, lo so - quei bastardi stanno solo aspettando che ci presentiamo lì. Ma ho un incontro molto urgente e importante lì! Non sono una persona avara - anche se non mi piace pagare, pago sempre. Lascia tutto quello che stai facendo, e appena arriviamo, ti darò "+FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money))+".";
			}
			link.l1 = "Hm. Sto andando anche io in questa direzione, quindi sono pronto a portarti a bordo con queste condizioni.";
			link.l1.go = "passenger_1";
			link.l2 = "Mi dispiace, "+GetAddress_FormToNPC(NPChar)+", ma sto navigando in una direzione diversa. Non posso aiutarti.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Peccato. Beh, aspetterò un'altra nave. Addio.";
			link.l1 = "Ci vediamo.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Benissimo! Sono stanco di aspettare. Riceverai il tuo pagamento quando arriveremo.";
			link.l1 = "Vai alla mia nave, "+GetAddress_FormToNPC(NPChar)+". Stiamo partendo presto.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "nobleman");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", at " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Eccoci qui, eccellente! Viaggiare sulla tua nave è stato molto soddisfacente. Hai un equipaggio disciplinato e ponti puliti! Grazie. Prendi i tuoi soldi, signore.";
			link.l1 = "Buona fortuna, "+GetAddress_FormToNPC(NPChar)+"! Addio.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Noblepassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = "Ho un affare piuttosto delicato..."+sTemp+"Ho bisogno di soldi subito o sono nei guai grossi. Non chiederei mai normalmente a un altro gentiluomo dei soldi ma la situazione è davvero brutta.";
			link.l1 = "Di quanto hai bisogno?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = hrand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text = "La somma è piuttosto piccola, è "+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+". Allora, puoi aiutarmi?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = "Sì, certo. Prendilo.";
				link.l1.go = "donation_2";
			}
			link.l2 = "Sarei felice di aiutare, ma le mie tasche sono vuote anche - non un solo peso di riserva.";
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = "La mia gratitudine, "+GetAddress_Form(NPChar)+"! Mi hai salvato! Ho amici nella residenza del governatore e parlerò loro della tua generosità. Mille grazie ancora!";
			link.l1 = "Prego, signore. Sono certo che fareste lo stesso per me.";
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text = "Mi serve il tuo aiuto. Sei ricco e un gentiluomo, quindi spero che capirai. Non molto tempo fa avevo un grande bisogno di denaro, quindi ho dovuto andare dal banchiere e impegnare "+pchar.GenQuest.Noblelombard.Item+"\nHa offerto buone condizioni. Dieci percento per ogni mese, tre mesi in totale. Ma il tempo è scaduto e non possiedo soldi per riscattare l'oggetto a causa di sfortunate circostanze\nOra dice di aver trovato un compratore per "+pchar.GenQuest.Noblelombard.Item+" e sta per venderlo se non rimborsa immediatamente il mio debito e gli interessi. Ma ora non ho molti soldi, e l'articolo che ho impegnato è molto costoso...";
			link.l1 = "E come posso aiutarti con questo, "+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text = "Ti chiedo di parlare con il nostro banchiere. Offrigli del denaro, garanti per me... o fai qualcos'altro. Sfortunatamente, non ho nessuno a cui chiedere, tutti i miei buoni amici sono improvvisamente andati 'in bancarotta'. In tre mesi "+pchar.GenQuest.Noblelombard.Text+", e vi ripagherò tutti i vostri costi, doppiamente! Avete la mia parola da gentiluomo!";
			link.l1 = "Bene, cercherò di aiutarti in questo caso.";
			link.l1.go = "lombard_2";
			link.l2 = "Sfortunatamente, anche io sono 'in bancarotta' al momento. Quindi non posso aiutarti, mi dispiace tanto!";
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = "Grazie per la vostra comprensione. Vi aspetterò nella taverna. Venite appena possibile.";
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard = "true"
			pchar.GenQuest.Noblelombard.Name = GetFullName(npchar);
			pchar.GenQuest.Noblelombard.id = npchar.id;
			pchar.GenQuest.Noblelombard.City = npchar.city;
			pchar.GenQuest.Noblelombard.Money = 20000+hrand(60)*500;
			pchar.GenQuest.Noblelombard.Percent = makeint(sti(pchar.GenQuest.Noblelombard.Money)*0.3);
			pchar.GenQuest.Noblelombard.Summ = sti(pchar.GenQuest.Noblelombard.Money)+sti(pchar.GenQuest.Noblelombard.Percent);
			pchar.GenQuest.Noblelombard.Chance = hrand(9);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			FreeSitLocator(pchar.GenQuest.Noblelombard.City + "_tavern", "sit1");
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", pchar.GenQuest.Noblelombard.City+"_tavern", "sit", "sit1", "Nobleman_lombardTavern", 10);
			SetFunctionTimerCondition("Noblelombard_Over", 0, 0, 1, false); //таймер до конца суток
			ReOpenQuestHeader("Noblelombard");
			AddQuestRecord("Noblelombard", "1");
			AddQuestUserData("Noblelombard", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Noblelombard.City));
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = "Cosa puoi dire, "+GetAddress_Form(NPChar)+"? Sei stato in banca? Hai buone notizie o cattive?";
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = "L'ho fatto. Ho ripagato tutto il tuo debito. Puoi andare là e riprendere il tuo reliquiario.";
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "L'ho fatto. Ho ripagato tutti gli interessi degli ultimi tre mesi e anche per i prossimi tre. Puoi aspettare tranquillamente i tuoi soldi. Solo non dimenticare di ripagare il tuo debito principale tra tre mesi.";
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "L'ho fatto. Ho rimborsato tutti gli interessi degli ultimi tre mesi. Il banchiere ha accettato di aspettare altri tre mesi finché non avrai l'intera somma.";
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = "Cosa puoi dire, "+GetAddress_Form(NPChar)+"? Sei stato in banca? Hai buone notizie o cattive?";
				link.l1 = "L'ho fatto. Questo avaro ha chiesto una somma incredibile. Ha rifiutato qualsiasi richiesta di concessioni e non ho la somma necessaria. Quindi non ho potuto aiutarti. Mi dispiace.";
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = "Cosa puoi dire, "+GetAddress_Form(NPChar)+"? Sei stato in banca? Hai buone notizie o cattive?";
				link.l1 = "Sono su di esso. Aspetta.";
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "Meh, "+GetAddress_Form(NPChar)+"... Ora sei anche tu testimone dell'irrefrenabile avidità di questi maledetti usurai assetati di sangue. Per Dio signore, fanno impallidire gli ebrei! Ricorda questo quando provi a prendere in prestito denaro da loro come ho fatto io. Grazie per averci provato almeno...";
			link.l1 = "Mai piaciuti. Beh, a chi piacciono gli usurai? Mi dispiace, "+GetAddress_FormToNPC(NPChar)+". Addio.";
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Noblelombard", "4");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			sld = characterFromId(pchar.GenQuest.Noblelombard.City+"_usurer");
			DeleteAttribute(sld, "quest.noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_5":
			dialog.text = "Incredibile! Mi hai appena salvato, "+GetAddress_Form(NPChar)+"! Non lo dimenticherò mai. Ti assicuro che tutte le tue spese saranno rimborsate il doppio. Vieni a vedere il nostro banchiere tra tre mesi. Aprirò un deposito a tuo nome.";
			link.l1 = "Bene, farò come dici. Ci vediamo!";
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = "Grazie ancora, capitano. Buona fortuna!";
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeOfficersLoyality("good_all", 1);
			AddQuestRecord("Noblelombard", "5");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			SetFunctionTimerCondition("Noblelombard_Regard", 0, 0, 90, false); //таймер
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+hrand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+hrand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = "Posseggo un "+LinkRandPhrase("fabbrica","mia","piantagione")+" e ho sempre bisogno di nuovi schiavi. Il clima li distrugge davvero. Adesso ho bisogno "+sti(npchar.quest.slaves.qty)+" teste. Sono disposto a ordinare un lotto di queste. Pagherò oro per ogni testa, "+sti(npchar.quest.slaves.price)+" dobloni\nNon c'è fretta, non ti metterò alcun limite di tempo se riesci a ottenere quello che mi serve. Beh, entro certi limiti ovviamente, non prolungarlo per più di mezzo anno. Allora, cosa ne dici? Affare?";
			link.l1 = "Affare fatto! La schiavitù è un affare sporco, ma vale la pena correre il rischio.";
			link.l1.go = "slaves_1";
			link.l2 = "Mi scusi, ma non sono un mercante di schiavi. Non è il mio genere di lavoro.";
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = "Molto bene allora. Ti aspetterò quando porterai il carico. Puoi trovarmi in chiesa dalle 11:00 alle 13:00 ogni giorno. Sono occupato o al lavoro per il resto della giornata.";
			link.l1 = "Bene. Me ne ricorderò. Ci vediamo, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = "Hai portato "+sti(npchar.quest.slaves.qty)+" schiavi come ti ho chiesto, capitano?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = "Sì. L'intero carico è nella mia stiva. Sono pronto a consegnartelo.";
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = "No, ci sto lavorando.";
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = "Capitano, se sei qui per quegli schiavi... ne ho già comprati abbastanza e non ne ho bisogno al momento. Hai impiegato troppo tempo, mi dispiace.";
				link.l1 = "Che peccato! Ma hai ragione, non sono stato abbastanza veloce. Addio!";
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = "Eccellente. Invierò subito una lancia per loro.";
			link.l1 = "E cosa ne sarà del mio pagamento?";
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = "Non preoccuparti, me ne ricordo. Ecco, prendi la somma, "+sti(npchar.quest.slaves.price)+" ducati a testa. Un bel affare per entrambi sì?";
			link.l1 = "Grazie. È stato un piacere fare affari con te.";
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = "Dovrei dire di sì... Perdonami ora, devo andare. Ci vediamo!";
			link.l1 = "Buona fortuna, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ascolta, come cittadino di questa città ti chiedo di rinfoderare la tua spada.","Ascolta, come cittadino di questa città ti chiedo di riporre la tua spada.");
			link.l1 = LinkRandPhrase("Bene.","Come desideri.","Bene.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "I've lost all my money in gambling yesterday and I don't have enough sum to wipe away the debt. Can you help me?" break;
		case 1: sText = "I had a nice time yesterday with a... certain lady of the evening, and now she is trying to blackmail me. I need to pay her first and then I will deal with her... Can you help me with some money?" break;
		case 2: sText = "I ran through a local fool with my rapier recently and now the commandant demands a bribe to hush up the event. I am short of money now. Can you help me?" break;
		case 3: sText = "I was unlucky enough to lose a bet and I don't have a trifling sum to repay the debt of honor. Can you help me?" break;
		case 4: sText = "Some bastard knows about my... indiscreet activities concerning a married woman. I don't have enough money to shut his mouth. Just a few gold coins are needed... " break;
		case 5: sText = "Some bastard has stolen important papers from my house and demanding a significant sum for their return. I've almost got it, just a few more coins needed. Can you help me?" break;
	}
	return sText;
}

void LombardText()
{
	switch (hrand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = "my mother's diamond pendant made by a jeweler from Madrid";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my inheritance","my ship will return from Africa loaded with slaves");
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = "an emerald necklace of my sister crafted by a jeweler in Paris";
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will inherit a county in Europe","my ship will return from India loaded with spices and silk");
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = "family ring with an emblem of our kin";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my expedition will return from the Spanish Main with gold ingots","I will get my inheritance");
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = "a ruby bracelet of my wife, a gift from her mother";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my investment with the interest from a European bank","I will get the profits from my plantation");
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = "a necklace of gold and diamonds, piece work, a pride of my wife";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get profits from my current business","my ship will be back from Africa with the cargo hold stuffed with black ivory");
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = "an ivory cane of semiprecious stones, a gift from my grandfather";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my ship will be back from India with the cargo hold filled with silks and spices","I will receive my interest from a European bank");
		break;
	}
}
