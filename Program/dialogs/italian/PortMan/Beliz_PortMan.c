// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "Cosa vuoi? Ah-ah, sei il partecipante alla regata! Ho ragione?";
				link.l1 = "Esatto, signore. Devo registrarmi qui secondo le regole.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già provato a farmi una domanda "+GetAddress_Form(NPChar)+"...","Hai parlato della stessa questione per la terza volta oggi...","Guarda, se non hai nulla da dirmi riguardo le questioni del porto, allora non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Mai mente.","Infatti, già la terza volta...","Mi dispiace, ma per ora non sono interessato alle questioni del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Грани справедливости
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "Si dice che qualcuno abbia tentato di toglierti la vita, e stai cercando di rintracciare il colpevole?";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "L'uomo che ha tentato la tua vita è caduto, Sig. "+npchar.lastname+". Non ti minaccia più niente.";
				link.l1.go = "GS_Portman_6";
			}
			//<-- Грани справедливости
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Mm... Hai infranto le regole della regata e devo squalificarti. Mi dispiace. Non parteciperai al prossimo viaggio. Ho già preparato un dispaccio per Port-Royal.";
			link.l1 = "Oops... che peccato! Ma non posso fare nulla qui, sei stato troppo vigile. Addio!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1 переход
			dialog.text = "Registriamoci: capitano "+GetFullName(pchar)+", la nave è "+pchar.Ship.Name+"... il tempo della regata in ore è "+sti(pchar.questTemp.Regata.FirstTransitionTime)+". Fatto, il tuo risultato è registrato, puoi continuare il tuo cammino.";
			link.l1 = "Ditemi il mio grado.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Sei qui ma non vedo la tua nave. Dove si trova?";
			link.l1 = "Mi dispiace, signore. Trasferirò immediatamente la mia nave al porto.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Sei in testa. Congratulazioni! Continua così!";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Sei l'ultimo. Dovresti sbrigarti.";
				link.l1 = "Sono in viaggio!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Sei il secondo. Il leader è "+sName+" sulla nave "+sShip+". Immagino che tu possa ancora superarlo.";
					link.l1 = "Grazie! Ci proverò!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "Il tuo rango è "+n+". Il tuo avversario più vicino è "+sName+" sulla nave "+sShip+".";
					link.l1 = "Grazie!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//отметка Белиза
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//первая засада у Сантьяго
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Гаваны
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
		break;
		//регата
		
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "È vero, ci hanno tentato di uccidermi. Per quanto riguarda la ricerca... non è proprio così. Non ho bisogno che un fuggitivo venga catturato, ho bisogno della sua testa. Solo allora la pace tornerà a me.";
			Link.l1 = "Hai qualche idea di chi ti ha attaccato e perché?";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_2":
			dialog.text = "Io... Io non so chi sia! Non so da dove venga o perché mi abbia attaccato. Ma una cosa è chiara — voleva la mia morte. E ora... ora desidero la sua morte con altrettanta furia! Mi capisci?\nQuindi risparmiami le tue domande inutili. La tua curiosità non significa nulla per me — solo l'azione può aiutare ora. Duecento dobloni per la sua testa, questo è il mio prezzo. Inizia la caccia, o smetti di sprecare il mio tempo.";
			Link.l1 = "Capisco che la paura e la rabbia offuscano la tua mente, e perdonerò anche il tuo tono. Ma controllati. Non vedo una fila di volontari pronti a risolvere i tuoi problemi, quindi tempera il tuo fuoco. Duecento dobloni sono accettabili, ma prima di accettare l'incarico, ho bisogno di sapere tutto.";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "Le tue parole sono solo chiacchiere inutili, e non ci sono indizi. Cercare qualcuno sconosciuto nella giungla è come cercare un ago in un pagliaio. Non sprecherò il mio tempo in una caccia senza senso. Buona fortuna. Ne avrai sicuramente bisogno.";
			Link.l2.go = "GS_Portman_End";
		break;
		
		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;
		
		case "GS_Portman_3":
			dialog.text = "Argh... Perdonami, "+GetAddress_Form(NPChar)+", i miei nervi sono a pezzi... Cosa vuoi sapere esattamente?";
			Link.l1 = "Hai notato qualche caratteristica che potrebbe aiutare a identificarlo? Era solo, o sostenuto da qualcuno più potente? Più mi dici, prima potrai dormire tranquillo.";
			Link.l1.go = "GS_Portman_4";
		break;
		
		case "GS_Portman_4":
			dialog.text = "Che nemico?! Non ho nemici! Mai avuti! Non ho fatto nulla per meritare la morte in mezzo alla strada in pieno giorno\nQuel malfattore... è solo un pazzo amareggiato, del tipo che si trova ovunque in queste città coloniali\nPer quanto riguarda dove cercare... credo si stia nascondendo nella giungla. È facile scomparire in quelle maledette foreste, ma sono sicuro che si dirigerà verso le grotte o le cale — più facile nascondersi lì\nPer quanto riguarda l'aspetto, il suo viso era coperto da un fazzoletto, un cappello in testa, e portava più armi delle guardie di Sua Maestà. Non c'era tempo per notare altro.";
			Link.l1 = "Beh, non è molto, ma è sufficiente per iniziare la ricerca. Parto subito. Tieni stretto quel oro, tornerò presto.";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddQuestRecord("GS", "2");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
			
			PChar.quest.GS_Peshera.win_condition.l1 = "location";
			PChar.quest.GS_Peshera.win_condition.l1.location = "Beliz_Cave";
			PChar.quest.GS_Peshera.function = "GS_Peshera";
			locations[FindLocation("Beliz_Cave")].DisableEncounters = true;
			
			PChar.quest.GS_Peshera_pusto.win_condition.l1 = "location";
			PChar.quest.GS_Peshera_pusto.win_condition.l1.location = "Beliz_Cave_2";
			PChar.quest.GS_Peshera_pusto.function = "GS_Peshera_pusto";
		break;
		
		case "GS_Portman_6":
			dialog.text = "Magnifico, "+GetFullName(pchar)+"! Assolutamente magnifico! Hai dimostrato la tua bravura ineguagliabile. Ecco la tua ricompensa: duecento dobloni. Per favore, prendilo!";
			Link.l1 = "Grazie a te! Ma dimmi, hai qualche motivo per sospettare che l'assassino sia stato assunto da uno dei tuoi ex clienti?";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_7":
			dialog.text = "Ex clienti?.. Che assurdità!... Sono un uomo onesto, e i miei affari sono sempre stati limpidi! Ma dato che mi hai aiutato, ti dirò qualcosa. Non molto tempo fa, dei pirati sono venuti da me\nMi hanno offerto denaro per informazioni sui vascelli mercantili. Ho rifiutato, e hanno lanciato minacce e maledizioni prima di andarsene in malo modo. Credo che l'assassino sia stato un loro lavoro. Non prendono molto bene i 'no'.";
			Link.l1 = "In tal caso, prenditi cura di te stesso. Chissà quanti altri spadaccini assoldati questi 'pirati' potrebbero mandare? Con questo, devo prendere il mio congedo — il dovere chiama.";
			Link.l1.go = "GS_Portman_8";
		break;
		
		case "GS_Portman_8":
			dialog.text = "Aspetta, Capitano. Voglio ringraziarti ancora una volta. Oltre all'oro, hai guadagnato il mio favore. Finché sarò il Capo del Porto qui, puoi lasciare qualsiasi tua nave ormeggiata qui per qualsiasi periodo di tempo con uno sconto del cinquanta percento. Che ne dici?";
			Link.l1 = "Un'offerta molto generosa! Grazie ancora una volta!";
			Link.l1.go = "GS_Portman_9";
		break;
		
		case "GS_Portman_9":
			dialog.text = "E vi ringrazio ancora una volta per i vostri sforzi. Sono certo che finché resterete concentrati su ciò che conta, i vostri affari continueranno a prosperare come hanno fatto oggi. Addio, Capitano.";
			Link.l1 = "Arrivederci.";
			Link.l1.go = "GS_Portman_10";
		break;
		
		case "GS_Portman_10":
			DialogExit();
			AddQuestRecord("GS", "4");
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_NaemnikMertv");
			pchar.questTemp.GS_BelizSkidka = true;
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
