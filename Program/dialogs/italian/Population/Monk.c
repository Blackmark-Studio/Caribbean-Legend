//Jason общий диалог уличных монахов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

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
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "Buon giorno a te, mio figlio. Ti chiedo di mostrare un po' di favore e di donare qualche moneta d'argento per il bene dei poveri, la tua anima e la Santa Madre Chiesa.";
					link.l1 = "Ebbene padre, suppongo che dobbiamo tutti aiutarci a vicenda come Cristo e la Sua Chiesa ci insegnano. Può dirmi dove andranno i soldi?";
					link.l1.go = "donation";
					link.l2 = "Perdonami, padre, ma sono povero come un topo di chiesa ora.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "Buongiorno a te, mio figlio. Vorrei chiederti un favore. Pagherò, naturalmente.";
					link.l1 = "Ti sto ascoltando, padre. Di cosa hai bisogno?";
					link.l1.go = "passenger";
					link.l2 = "Mi dispiace tanto, padre, ma devo andare.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "Saluti, mio figlio. Credo che tu sia un capitano. Quindi ho una proposta per te.";
					link.l1 = "Sto ascoltando, padre.";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("Saluti, mio figlio. Cosa ti preoccupa?","Saluti, mio figlio. Vai dal pastore se vuoi confessarti.","Saluti, mio figlio. 'Ricorda il tuo Creatore nei giorni della tua giovinezza.'"),LinkRandPhrase("Saluti, mio figlio. Cosa ti turba?","Buon giorno a te, mio figlio, che Dio ti benedica!","Buon giorno a te, mio figlio, possa il volto di Dio risplendere su di te!"));
				link.l1 = LinkRandPhrase("Lo stesso a te, padre. Come stai?","Buongiorno a lei, padre. Come sta la sua parrocchia?","Come sta, padre?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Ho una domanda per te, padre.","Ho bisogno di informazioni.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "Padre, ho delle persone sulla mia nave. Sono schiavi, sia cristiani che pagani non battezzati. Voglio che tu battizzi i pagani e amministri la comunione ai cristiani. Dopo li libererò tutti per la gloria di Dio e della nostra Chiesa.";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Padre, desidero che tu benedica la mia nave e offra una messa per il mio equipaggio. Quanto costerebbe?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Perdonami, padre, ma devo andare.","Mi scuso per il disturbo, padre.","Devo tornare alla mia nave, padre. Addio!");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("Di nuovo tu, mio figlio? Cosa desideri?","Hai ancora qualcosa da dirmi, mio figlio?","È bello rivederti, mio figlio.");
				link.l1 = LinkRandPhrase("Anche a te, padre. Come stai?","Buon giorno a lei, padre. Come va la sua parrocchia?","Come sta, padre?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Ho una domanda per te, padre.","Mi serve informazione.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "Padre, ho delle persone sulla mia nave. Sono schiavi, sia cristiani che pagani non battezzati. Voglio che tu battezzi i pagani e amministri la comunione ai cristiani. Dopo li libererò tutti per la gloria di Dio e della nostra Chiesa.";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Padre, voglio che benedica la mia nave e offra una messa per il mio equipaggio. Quanto costerebbe?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Perdona, padre, ma devo andare.","Scusami per il disturbo, padre.","Devo andare alla mia nave, padre. Addio!");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "Ho un affare urgente per te, mio figlio. Devo consegnare questi documenti al pastore di  "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+". Stai navigando in quella direzione? I documenti devono essere consegnati in due settimane...";
				link.l1 = "Abbastanza facile, padre. Dammi quei documenti e li consegnerò a "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+".";
				link.l1.go = "Monkletter";
				link.l2 = "Sarei felice di farlo, padre, ma sto navigando in un'altra direzione.";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "Mio figlio, saresti d'accordo ad aiutarmi in una questione urgente? La nostra chiesa sta rimanendo senza Bibbie e libri di preghiera che diamo a tutti coloro che ne hanno bisogno\nPotresti navigare fino alla colonia più vicina "+NationNameGenitive(sti(npchar.nation))+", per raccogliere alcune Bibbie e libri di preghiere dalla chiesa locale e portarli qui? E cerca di farlo in un mese, non ne abbiamo molti rimasti.";
				link.l1 = "Aiuterò volentieri la vostra chiesa. Posso ottenere questi libri da qualsiasi pastore?";
				link.l1.go = "Churchbooks";
				link.l2 = "Sarei felice di farlo, padre, ma non posso farlo ora.";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("Va tutto bene, mio figlio. Grazie per le tue gentili parole.","La nostra parrocchia sta bene, mio figlio. Grazie per la tua preoccupazione.");
			link.l1 = "Devo andare allora, padre.";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "Certo, mio figlio."+sTemp+"";
			link.l1 = "Quale donazione sarebbe considerata sufficiente?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "Tutto dipende dal tuo borsellino e desiderio personale, mio figlio. 'Dio ama chi dona con gioia.' Siamo profondamente grati per qualsiasi donazione.";
			link.l1 = "100 pesos";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 pesos";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000 pesos";
			link.l3.go = "donation_rate_3";
			link.l4 = "10000 pesos";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Grazie per le monete, mio figlio! Andranno a una buona causa!";
				link.l1 = "Sei il benvenuto, santo padre.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "'Non vi fate ingannare, Dio non può essere deriso. Perché quello che un uomo semina, quello raccoglierà. Colui che semina nella sua carne, dalla carne raccoglierà corruzione. Ma colui che semina nello spirito, dallo spirito raccoglierà vita eterna.'";
				link.l1 = "Ah-ah! Risparmia la predica, non faccio beneficienza. Sparisci!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ti ringrazio, mio figlio. Questa somma aiuterà davvero la nostra missione parrocchiale. Dio ti benedica!";
				link.l1 = "Buona fortuna, padre!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "La punizione di Dio ti aspetta, mascalzone! Prendere in giro un servo della santa chiesa di Cristo è una blasfemia!";
				link.l1 = "Ah-ah! Non faccio carità. Sparisci!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Non avrei mai immaginato che tu fossi così generoso, mio figlio! Ti nominerò nella mia prossima lettera al nostro vescovo e pregheremo per te ogni giorno! Ti benedico e accetto i tuoi soldi con gratitudine!";
				link.l1 = "I soldi non valgono nulla a meno che non vengano usati per lo scopo di Dio! Buona fortuna, padre!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "La retribuzione di Dio ti aspetta, mascalzone! Beffare un servitore della santa chiesa di Cristo è una bestemmia!";
				link.l1 = "Ah-ah! Non faccio beneficenza. Sparisci!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "Cosa... Ti ho capito bene? Donerai davvero diecimila pesos!? Ti benedico e accetto il tuo denaro con gratitudine. Ti menzionerò nella mia prossima lettera al nostro vescovo e pregheremo per te ogni giorno! Questo è un enorme aiuto per la Chiesa!";
				link.l1 = "'A chi molto è dato, molto è richiesto', giusto? Buona fortuna, santo padre.";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "La punizione di Dio ti aspetta, mascalzone! Beffare un servitore della santa Chiesa di Cristo è una blasfemia!";
				link.l1 = "Ah-ah! Non faccio beneficenza. Sparisci!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "Certo, mio figlio. È il nostro sacro dovere aiutare questi poveri miseri. Farò ciò che mi chiedi.";
			link.l1 = "Grazie, padre. Donerò dieci pezzi di otto per ogni prigioniero battezzato e amministrato.";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "Sebbene non sia necessario, accetto con gratitudine il tuo pedaggio. I tuoi soldi andranno a sostegno delle varie missioni della nostra parrocchia. Potresti accompagnarmi alla tua nave?";
			link.l1 = "Sì, padre. Seguimi.";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Two hours later"+ NewStr() +"Slaves were freed", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 7;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "I have only one ship in my squadron and it's "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = 5000*(7-iTemp);
				break;
				case 2:
					sTemp = "I have two ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(7-iTemp)));
				break;
				case 3:
					sTemp = "I have three ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(7-iTemp)));
				break;
				case 4:
					sTemp = "I have four ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(7-iTemp)));
				break;
				case 5:
					sTemp = "I have five ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(7-iTemp)));
				break;
			}
			dialog.text = "Tutto dipende dal numero totale di navi nella tua squadra e dalla loro dimensione.";
			link.l1 = ""+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "Ti costerà "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+", mio figlio.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "Posso pagarti questa somma, padre. Prendi i soldi.";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "Sfortunatamente, non ho così tanti soldi con me.";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "Molto bene, mio figlio. Permettimi di raccogliere i vasi sacri e andremo al porto.";
			link.l1 = "Seguimi, padre.";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Several hours later"+ NewStr() +"The priest has held mass aboard your ship and blessed it", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "Salve capitano, permettimi di presentarmi. Sono un prete e ho abbastanza esperienza come cappellano a bordo delle navi da guerra. Ho lasciato la mia ultima nave perché il capitano ed io avevamo alcune...discrepanze morali. Vuoi prendermi nel tuo equipaggio?";
			link.l1 = "Un prete a bordo? Dimmi padre, cosa fa un cappellano di nave?";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = "Perché, è abbastanza ovvio. Prego Dio per te e il tuo equipaggio, celebro messa ogni giorno, benedico i tuoi uomini e ascolto le confessioni prima della battaglia. La parola di Dio concede forza alle mani e agli spiriti del tuo equipaggio. Il tuo equipaggio avrà l'opportunità di ricevere comunione e confessione regolarmente. Credimi, un marinaio in stato di grazia resisterà in situazioni in cui uno empio vacillerà\nNon chiedo molto per me: un pagamento unico di cinquantamila pesos per la mia parrocchia di origine, un semplice letto in una cabina e un pasto come quelli che hanno i tuoi ufficiali. Questo sarebbe tutto.";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "Interessante... Hai ragione, un buon capitano deve preoccuparsi non solo dei corpi del suo equipaggio, ma anche delle loro anime. Benvenuto a bordo, padre!";
				link.l1.go = "capellan_2";
			}
			link.l2 = "No, padre. Mi dispiace ma non posso permettermi i tuoi servizi.";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Grazie per la tua fiducia, mio figlio. Hai speso i tuoi soldi saggiamente. Ma ti avverto, servo solo capitani degni, sia che siano commercianti o corsari, non importa. Ma non predicherò mai a bordo di una nave pirata!\nQuindi, se mai dovessi issare il Jolly Roger del diavolo, lascerò immediatamente la tua nave al primo porto.";
			link.l1 = "Considererò ciò, padre, e cercherò di non deluderti. Per favore, sali a bordo e presentati all'equipaggio!";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "loc1", "Monk_Capellan", -1);
			pchar.questTemp.ShipCapellan.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.ShipCapellan.Yes = "true";//капеллан в команде
			Achievment_Set("ach_69");
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			npchar.reputation = 60;
		break;
		
		case "capellan_4":
			dialog.text = "Hai bisogno di qualcosa, mio figlio?";
			link.l1 = "No, non è niente, padre.";
			link.l1.go = "exit";
			link.l2 = "Padre, vorrei che lasciassi la nave nel prossimo porto. Non mi spiegherò ulteriormente.";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "Molto bene, mio figlio. Tu sei il capo qui. Lascio la tua nave nel prossimo insediamento.";
			link.l1 = "Grazie per la tua comprensione, padre.";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "Ahimè, capitano! Ti ho avvertito, che ti avrei lasciato se avessi issato la bandiera dei pirati! Lascio la tua nave al prossimo porto. Prego per il tuo immediato pentimento e il ritorno al grembo della Santa Madre Chiesa.";
			link.l1 = "Be', dannazione...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				dialog.text = "Mio "+GetSexPhrase("figlio","figlia")+", devo arrivare a "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+" è acceso "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+", per "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+". Ti pagherò "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+" per questo. Cosa ne dici?";
			}
			else
			{
				dialog.text = "Mio "+GetSexPhrase("figlio","figlia")+", il Signore muove in modi misteriosi, e così cerco un capitano affidabile. Puoi aiutarmi a raggiungere "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+", che si trova su "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+"? Capisco che è come un viaggio nella ardente Gehenna, dato che i nostri nemici non dormono mai. E capisco che tu non sei Gesù Cristo, ma nemmeno io sono un apostolo, e quindi ho dei risparmi. Verrai "+FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money))+" ti basta?";
			}
			link.l1 = "Sono d'accordo, padre.";
			link.l1.go = "passenger_1";
			link.l2 = "Mi dispiace, padre, ma sto navigando in una direzione diversa. Non posso aiutarti.";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "È la volontà di Dio per tutti, mio figlio. Aspetterò un'altra nave. La pace sia con te!";
			link.l1 = "Addio, padre.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Dio ti benedica! Riceverai il tuo pagamento quando arriveremo alla nostra destinazione.";
			link.l1 = "Dirigetevi verso la mia nave, padre. Partiremo presto.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
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
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Grazie, mio "+GetSexPhrase("figlio","figlia")+". Hai mantenuto la tua promessa ed ora è il mio turno. Prendi i tuoi soldi come avevo promesso.";
			link.l1 = "Grazie. Buona fortuna, padre.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
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
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "Ecco. Prendi questo pacco, mio figlio. Ricorda che hai solo due settimane per consegnarlo. Il pastore lo sta aspettando. Vai, e che Dio sia con te!";
			link.l1 = "Non ti deluderò, padre. Addio.";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "Sì. Puoi ottenerli in qualsiasi colonia "+NationNameGenitive(sti(npchar.nation))+". Porta tutti i libri che troverai al nostro pastore in chiesa. Dio ti benedica!";
			link.l1 = "Grazie! Riceverai i tuoi libri presto.";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (hrand(9))
	{
		case 0: sText = "I am gathering money for building "+LinkRandPhrase("a chapel","an almshouse","a hospital")+". The local citizens give little in alms so I must ask prosperous men like you." break;
		case 1: sText = "I am gathering donations for our church. Sailors don't usually have much time to visit the house of God, but everyone must do his best in saving his own soul." break;
		case 2: sText = "I am gathering money to buy food and medicines for our poorhouse for the sick, widows, orphans, and infirm. Please donate sir, because there but for the grace of God go all of us." break;
		case 3: sText = "I am gathering money for new sacred vessels, the ones which we brought from Europe are battered with continual use. It's a duty for every Christian to take care of our Church." break;
		case 4: sText = "I am gathering money for our church's renovation, the roof is leaking terribly and the pews have to be repaired too. It's a duty for every Christian to take care of our Church." break;
		case 5: sText = "I am gathering money to pay the good artist who is able to paint the walls of our church and draw scenes from the Bible on them for those of our parish who cannot read. It's a duty for every Christian to take care about his Church." break;
		case 6: sText = "I am gathering money for a new high altar for our church. Our parish is poor and we would like a noble seat for the Blessed Sacrament. I do hope for your help." break;
		case 7: sText = "There are a lot of wounded sailors from pirate raids in our hospital. They need medicines and bandages. Pray help them, for you can really understand sufferings of the common sailors." break;
		case 8: sText = "I am trying to get money for clothes and food for our poorest citizens. The only hope they have is our holy church. Please help them." break;
		case 9: sText = "I am going to go deep in our island for missionary work to bring the light of Christ's Gospel to the lost souls of the pagan Indians. I am gathering funds for this expedition. Please help our good deed!" break;
	}
	return sText;
}
