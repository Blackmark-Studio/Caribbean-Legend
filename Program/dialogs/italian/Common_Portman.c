#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
string sProf;		//  без оффа hasert	
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    int i, cn, iTemp;
    ref chref, compref; // без оффа hasert
	ref rRealShip;
    string attrL, sTitle, sCapitainId, s1;
	string sColony;
    
	String sLastSpeakDate = LastSpeakDate();
	
	// Warship 25.07.09 Генер "Сгоревшее судно". Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
    
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
    string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}
	
	attrL = Dialog.CurrentNode;
	// hasert блок для сторожа ==>
	if(HasSubStr(attrL, "ShipStockManBack11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}
	
	if(HasSubStr(attrL, "ShipStockManBack22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack2_"))
	{
		i = findsubstr(attrL, "_" , 0);
		AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));

		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));//сторож

		////DownCrewExp(chref,GetNpcQuestPastDayParam(chref, "ShipInStockMan.Date"));

        int iChar = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); //выбранный пассажир
		compref = GetCharacter(iChar);

		DeleteAttribute(compref,"ship");//зачем-то стираем корабль офицера, хотя его там и не должно быть
		compref.ship = "";

		aref    arTo, arFrom;

		makearef(arTo, compref.ship);
		makearef(arFrom, chref.Ship);
		CopyAttributes(arTo, arFrom);

		// снимем пассажира -->
		CheckForReleaseOfficer(iChar);//увольнение офицера с должностей, если он не просто пассажир
		RemovePassenger(pchar, compref);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);
		DelBakSkill(compref);
		DeleteAttribute(chref, "ShipInStockMan");
		chref.id = "ShipInStockMan";//сбрасываем индекс к стандартному, чтобы этот номер массива в следующий раз можно было занять
		DeleteAttribute(chref,"ship");//затираем данные корабля у сторожа
		chref.ship = "";
		LAi_SetCurHP(chref, 0.0);//ещё и убивать непися, чтоб точно очистился из массива?

		NPChar.Portman	= sti(NPChar.Portman) - 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		Dialog.CurrentNode = "exit";//закрываем диалог, ещё одно подтверждение уже не справшиваем
	}
	
	if(HasSubStr(attrL, "ShipStockMan11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}

	if(HasSubStr(attrL, "ShipStockMan22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}
    //  <=== hasert
    
	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
	 	NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
 	    Dialog.CurrentNode = "BurntShip19";
	}
    
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'allarme è stato dato in città e ora tutti ti stanno cercando. Se fossi in te, non ci resterei.","Tutte le guardie della città stanno setacciando la città alla tua ricerca. Non sono uno sciocco per parlare con te!","Corsa, "+GetSexPhrase("compagno","ragazza")+", prima che i soldati ti crivellino di colpi..."),LinkRandPhrase("Di che cosa hai bisogno, "+GetSexPhrase("birbante","puzzolente")+"?! Le guardie della città hanno già colpito il tuo odore, non andrai lontano, sporco pirata!","Assassino, lascia subito la mia casa! Guardie!","Non ho paura di te, "+GetSexPhrase("birbante","ratto")+"! Presto ti impiccheranno nel nostro forte, non andrai lontano..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Eh, un allarme non è mai un problema per me...","Non mi prenderanno mai."),RandPhraseSimple("Chiudi la bocca, "+GetWorkTypeOfMan(npchar,"")+", e forse non strapperò la tua sporca lingua!","Eh, "+GetWorkTypeOfMan(npchar,"")+", e tutti là - catturate i pirati! Ecco cosa ti dico, amico: stai zitto e vivrai..."));
				link.l1.go = "fight";
				break;
			}
			//Jason, фрахт
			if (CheckAttribute(pchar, "questTemp.WPU"))
			{
				if (pchar.questTemp.WPU.Fraht == "fail" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					dialog.text = "Oh, so chi sei tu. Hai firmato per consegnare la merce, ma l'hai rubata invece! Guardie, guardie!";
					Link.l1 = "Aaargh!";
					Link.l1.go = "exit";
					LAi_group_Attack(NPChar, Pchar);
					break;
				}
			}
			//фрахт
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				dialog.text = "Cosa posso fare per te, signore?";
				Link.l1 = "Ho affari con te...";
				Link.l1.go = "quests";
				Link.l2 = "Mi dispiace ma devo andare.";
				Link.l2.go = "exit";
				NPChar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			if(NPChar.quest.meeting == "0")
			{
				
				dialog.text = "Saluti, "+GetAddress_Form(NPChar)+". Non credo ci siamo mai incontrati prima. Io sono "+GetFullName(npchar)+" - il capitano del porto.";
				Link.l1 = "Ciao, "+GetFullName(NPChar)+". Io sono "+GetFullName(PChar)+", capitano del '"+PChar.ship.name+"'.'";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice")
				{
					dialog.text = "Capitano MacArthur, come ti ricordo sempre - non c'è bisogno di fare il check-in con me ogni volta. Non preoccuparti.";
					link.l1 = "Fermati, Signore "+npchar.lastname+"Sono proprio come tutti gli altri.";
					Link.l1.go = "node_2";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Saluti, "+GetAddress_Form(NPChar)+". Hai degli affari con me?","Ciao, "+GetFullName(Pchar)+". Ho visto la tua nave entrare nel nostro porto ed ero sicuro che saresti venuto a vedermi.","Oh, capitano "+GetFullName(Pchar)+". Cosa ti porta da me?");
				Link.l1 = "Ciao, "+GetFullName(NPChar)+". Volevo parlare con te.";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "Eccellente. Sono al vostro servizio, "+GetFullName(PChar)+".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "Allora, che ne è del denaro? Hai almeno mille pesos per me?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "Sì, ho"+GetSexPhrase("","")+". Ecco esattamente mille pesos. Ora, le informazioni!";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("No, non ancora...","Non ancora...","Non ancora, ma lo porterò presto...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "Per favore, permettetemi di spiegare il cuore del problema. Io e il mio vecchio amico, capitano  "+PChar.GenQuest.ChurchQuest_1.CapFullName+", ci siamo appena persi di un paio d'ore, e ho degli affari urgenti con lui. Ora dovrò raggiungerlo, ma non ho conoscenze"+GetSexPhrase("","")+" della sua ubicazione.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "Signore del porto, ho bisogno di alcune informazioni sulla nave chiamata '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"' posseduto dal capitano "+PChar.GenQuest.ChurchQuest_1.CapFullName+".";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // Он здесь, в этой колонии!		
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}				
				break;
			}		
//-------------------------------------------//Jason, фрахт---------------------------------------------------
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && CheckAttribute(PChar, "questTemp.WPU.Fraht.LevelUp") && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Eccellente. Sono al tuo servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Il carico per la tua colonia è nella stiva della mia nave.";
					Link.l1.go = "Fraht_completeLevelUp";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht != "lost" && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Eccellente. Sono al vostro servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Il carico per la tua colonia si trova nella stiva della mia nave.";
					Link.l1.go = "Fraht_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht == "lost" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					if (pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
					{
						dialog.text = "Oh, quindi sei finalmente arrivato. Francamente, non mi aspettavo che tu tornassi. Abbiamo già presentato una richiesta alle autorità per segnalarti come persona ricercata. Allora, cosa hai da dire?";
						Link.l1 = "Non sono riuscito a consegnare il carico in tempo a causa di circostanze impreviste. Ma voglio risolvere questo conflitto in modo pacifico. Ho portato il tuo carico e spero che saremo in grado di arrivare a un accordo.";
						Link.l1.go = "Fraht_complete_bad";
					}
					else
					{
						dialog.text = "Oh, so chi sei tu. Ti sei impegnato a consegnare il carico, ma l'hai rubato invece! Guardie, guardie!";
						Link.l1 = "Aaargh!";
						Link.l1.go = "exit";
						LAi_group_Attack(NPChar, Pchar);
					}
				}
// <-- фрахт
//-------------------------------------------//Jason, почта---------------------------------------------------	
		
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer != "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Eccellente. Sono al vostro servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Ho consegnato la posta per la tua colonia.";
					Link.l1.go = "Postcureer_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer == "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Oh, quindi sei finalmente arrivato. Francamente, pensavamo già che fossi morto... Beh, suppongo sia una buona cosa che tu sia solo un idiota e non un uomo morto.";
					Link.l1 = "Non sono riuscito a consegnare la posta in tempo a causa di circostanze impreviste. Ma eccola qui.";
					Link.l1.go = "Postcureer_complete_bad";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.fail") && pchar.questTemp.WPU.Postcureer.StartCity == npchar.city)
				{
					dialog.text = "Cosa è successo? Sembri la morte riscaldata.";
					Link.l1 = ""+GetAddress_FormToNPC(NPChar)+", avevi ragione quando mi hai avvertito del pericolo. Due uomini in nero mi hanno attaccato proprio all'uscita dell'ufficio dell'autorità portuale e... beh, mi hanno portato via il pacco.";
					Link.l1.go = "Postcureer_complete_fail";
					break;
				}
// <-- почта
//-------------------------------------------//Jason, эскорт---------------------------------------------------	
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Eccellente. Sono al vostro servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Sono stato mandato qui dal maestro del porto "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Mi è stato chiesto di scortare una nave che trasporta un carico di armi e munizioni. Ecco i miei documenti.";
					Link.l1.go = "Escort_LUGo_0";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0") && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Eccellente. Sono al vostro servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Ho scortato la nave con le armi, proprio come abbiamo concordato.";
					Link.l1.go = "Escort_LUGo_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "current" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Eccellente. Sono al vostro servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Ho trovato la nave scomparsa e l'ho portata al vostro porto. Il capitano della nave dovrebbe aver già fatto rapporto a voi.";
					Link.l1.go = "Escort_LU1WM_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Eccellente. Sono al vostro servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Ho trovato la nave dispersa e l'ho portata al vostro porto. Il capitano della nave dovrebbe avervi già fatto rapporto.";
					Link.l1.go = "Escort_LU1VSP_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "sink" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Eccellente. Sono al vostro servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Ho trovato la nave mancante sulle rive dell'isola di "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Il suo capitano era impegnato in una lotta ineguale contro le schiaccianti forze dei pirati. Ho aiutato in ogni modo possibile, ahimè, invano: i maledetti furfanti hanno affondato la nave. Tutto quello che potevo fare a quel punto era vendicarla.";
					Link.l1.go = "Escort_LU1VSP_completeSink";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Eccellente. Sono al vostro servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Ho trovato la nave mancante sulle coste dell'isola di "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Beh, non la nave, in realtà, ma piuttosto circa una cinquantina di uomini del suo equipaggio e il capitano. Sono al sicuro ora - l'equipaggio è salito a bordo della mia nave e il capitano è nella tua città ora - immagino che ti abbia già fatto visita.";
					Link.l1.go = "Escort_LU1S_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Eccellente. Sono al tuo servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Ho completato la vostra missione. La squadra di pirati che ha attaccato il convoglio commerciale è stata distrutta.";
					Link.l1.go = "Escort_LU2_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus != "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Eccellente. Sono al vostro servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Sono il capitano della nave di scorta. Sono venuto a segnalare che ho portato le navi mercantili al porto.";
					Link.l1.go = "Escort_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus == "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Eccellente. Sono al vostro servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Sono il capitano della nave scorta. Sono stato inviato per portare due navi mercantili e il carico al porto, ma, sfortunatamente, entrambe le navi scortate sono affondate durante una battaglia con un convoglio nemico. Sono comunque riuscito a consegnare il carico.";
					Link.l1.go = "Escort_fail";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id && !CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp"))
				{
					dialog.text = "Eccellente. Sono al tuo servizio, "+GetFullName(PChar)+".";
					Link.l1 = "Sono il capitano della nave scorta. Sono venuto a segnalare che ho portato le navi mercantili al porto.";
					Link.l1.go = "Escort_complete";
					break;
				}
// <-- эскорт
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice" && NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Che piacere sentirti dire così. Molti si sarebbero montati la testa al tuo posto. Allora, come posso io e i miei registri assisterti?";
			}
			else dialog.text = "Eccellente. Sono al tuo servizio, "+GetFullName(PChar)+".";
			if (npchar.city != "Panama") // Captain Beltrop, 24.12.2020, запрет брать задания и ставить корабли в ПУ Панамы
			{
				Link.l2 = "Hai qualche lavoro che posso fare? O forse un contratto?";
				Link.l2.go = "Work_check"; //квесты
				Link.l3 = "Posso ormeggiare una delle mie navi qui per un po' di tempo?";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "Voglio ritirare la mia nave.";
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Sono venuto a discutere di affari finanziari.";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Sono qui su richiesta di un certo uomo. Il suo nome è governatore "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" mi ha mandato da te. Sono qui per ritirare qualcosa...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "Vorrei saperne di più sui capitani che si sono registrati presso la vostra autorità portuale.";
			link.l6.go = "CapitainList";
			link.l61 = "Potresti condividere qualche informazione sui leggendari capitani e le loro navi uniche e personalizzate?";
			link.l61.go = "UniqueShips";
			
			link.l8 = "Sono qui per un'altra questione.";
			// Warship 26.07.09 Генер "Сгоревшее судно"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Ciao, sono venuto su invito di vostro figlio."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Questo riguarda tua figlia...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "Mi sono imbattuto in questo pacco di documenti di nave.";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "Mi sono imbattuto in questo pacco di documenti navali, qualcuno deve averli persi.";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";						
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}		
			}												
			Link.l15 = "Grazie. Arrivederci.";
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "Il tuo problema può essere facilmente risolto. Vai a vedere l'ufficiale del servizio di navigazione e lui può fornirti tutte le informazioni riguardanti la rotta della nave del tuo amico.";
			link.l1 = "Sfortunatamente, non è così semplice. Il mio amico ha rinominato la sua nave nel vostro porto... per motivi religiosi.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "Capisco. Questo complica un po' le cose. Devo frugare nei registri delle navi, e ciò richiederà del tempo. E il tempo è denaro, come probabilmente sai.";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "Capisco perfettamente, signore "+GetFullName(NPChar)+", e sono adeguatamente preparato per valutare il tuo tempo ... per l'ammontare di, diciamo, mille pesos.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "Peccato, perché al momento non ho soldi con me... Tornerò più tardi...";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "Perfetto! Vediamo ora... solo un minuto... qui... giusto. La rinominazione della nave è stata registrata, e la nave, che d'ora in poi sarà conosciuta come '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"' comandato dal capitano "+PChar.GenQuest.ChurchQuest_1.CapFullName+" ha salpato oggi verso "+XI_ConvertString("Colony"+sColony+"Gen")+".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "Oh! Davvero capisci che sono un uomo molto occupato, e sono contento che lo apprezzi! Vediamo ora... solo un minuto... qui... esatto. La rinominazione della nave è stata registrata, e la nave, che d'ora in poi sarà conosciuta come '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"' comandato dal capitano "+PChar.GenQuest.ChurchQuest_1.CapFullName+" ha salpato oggi verso "+XI_ConvertString("Colony"+sColony+"Gen")+".";			
				link.l1 = "Grazie, signore, mi ha reso un grande favore.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);	
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "Cosa esattamente vuoi sapere?";
			link.l1 = "Potete dirmi se la nave di quel capitano ha visitato il vostro porto?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "Mmm... E posso sapere perché chiedi?";
			link.l1 = "Ho affari con lui. Ma se non ha fatto scalo nel vostro porto o non lo conoscete...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "L'ha fatto. Ma grazie a tutti i Santi, proprio questa mattina ci ha liberato dalla sua presenza e si è diretto verso "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapGoToColony+"Acc")+". E mi dispiace sinceramente per chiunque debba avere a che fare con lui.";
			link.l1 = "In tal caso augurami buona fortuna - e grazie per il tuo aiuto.";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Voc")); // belamour gen
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // Спрашиваем портмана в колонии, куда отправился кэп.
			if(rand(2) == 1) 
			{
				Log_TestInfo("The next colony is the last");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // Флаг - следующая колония будет последней
			}
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "Cosa vuoi sapere, "+GetSexPhrase("signore","signorina")+" "+GetFullName(PChar)+"?";
			link.l1 = "Potreste dirmi se questo capitano ha fatto scalo nel vostro porto o no?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "Mmm, certo che l'ha fatto. E devo dire che sto aspettando con impazienza quel benedetto momento in cui finalmente lascerà questo porto tanto sofferto.";
			link.l1 = "Vuoi dire che la sua nave è ancora qui?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "Sì, grazioso "+GetSexPhrase("signore","signora")+". L'intero porto, a partire dai più umili scaricatori fino al capo del servizio piloti, prega per la sua partenza rapida. La sua nave ha appena lasciato il cantiere navale dove è stata prontamente riparata, ma in quel momento il suo galante capitano aveva già litigato con ogni falegname e rifiutato tre lotti di assi selezionate per lo scafo della nave. Ma domani il nostro Signore più grazioso e onnisciente ci libererà di quella... di quella peste, di quel spine nel fianco di un uomo!";
			link.l1 = "Ora, calmati, signore "+NPChar.Name+", e ricorda che qualcuno avrà ancora più difficoltà. Hai già superato questa prova, mentre io devo ancora incontrare quel tuo capitano. E ora, se mi scusi...";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;
						
		case "ShipLetters_out1":
			dialog.text = "Lasciami dare un'occhiata! Sì, infatti, nei miei documenti questo set è etichettato come nullo. È molto gentile da parte tua aver trovato un momento per venire a trovarmi e consegnarmi questi documenti. Buon vento, capitano!";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook"); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "10");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
				
		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "Let me take a look! Yes, this vessel and its captain are both registered in my documents. ";
			s1 = s1 + "Your conscientiousness, captain, reflects credit upon yourself! Of course, your efforts must not go unrewarded.  ";
			dialog.text = s1+"Dimmi, considereresti una somma di "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" sono pesos una ricompensa adatta?";
			link.l1 = "Certo che no!";
			link.l1.go = "exit";
			link.l2 = "Ebbene, una somma modesta, ma d'altronde non era un grande affare, neanche. Sì, accetto la tua offerta, "+npchar.name+".";
			link.l2.go = "ShipLetters_Portman1_2";
		break;
		
		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "5");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "ShipLetters_Portman2":
			dialog.text = "Accetterai la mia offerta?";
			link.l1 = "Certo che no!";
			link.l1.go = "exit";
			link.l2 = "Forse. Anche se sono sicuro che questi documenti valgono molto di più.";
			link.l2.go = "ShipLetters_Portman2_1";
		break;
		
		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "6");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 		
		break;

		case "EncGirl_1":
			dialog.text = "Sono tutto orecchie.";
			link.l1 = "Ho portato il vostro fuggitivo.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, capitano, grazie mille! Come sta? È ferita? Perché è scappata? Perché?\nNon capisce? Lo sposo è un uomo ricco e importante! La gioventù è ingenua e stupida... perfino crudele. Ricorda questo!";
			link.l1 = "Ebbene, tu sei suo padre e la decisione finale è tua, ma non mi precipiterei con il matrimonio...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Cosa ne sai tu? Hai figli tuoi? No? Quando ne avrai uno, vieni a trovarmi e allora parleremo.\nHo promesso una ricompensa a chiunque l'avesse riportata alla sua famiglia.";
			link.l1 = "Grazie. Dovresti tenerla d'occhio. Ho il sospetto che non si fermerà a questo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, sei tu quello "+GetSexPhrase("capitano che ha portato","la giovane signora che ha portato")+" mio figlio prodigo con una giovane sposa?";
				link.l1 = "Sì, ho aiutato la loro fuga.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, vieni, benefattore. Probabilmente aspetti una ricompensa?";
				link.l1 = "Beh, sto bene senza una ricompensa, la tua gratitudine sarebbe più che sufficiente.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Sono molto grato a te che non hai abbandonato mio figlio in gravi difficoltà e lo hai aiutato a trovare una via d'uscita da quella delicata situazione. Permettimi di ringraziarti e per favore accetta questa modesta somma e un dono personale da me.";
			link.l1 = "Grazie. È stato un piacere aiutare questa giovane coppia.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Grazie? Che grazie?! Sono sei mesi che quel testa di legno gira senza lavoro - e guardalo, ha tutto il tempo per gli amori! Quando avevo la sua età, gestivo già la mia azienda! Pff! Un governatore ha una figlia da maritare - e quel idiota ha portato una sgualdrina senza parenti né amici a casa mia e ha osato chiedere la mia benedizione!";
			link.l1 = "Mmh... A quanto pare, non credi nei sentimenti sinceri?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Quali sentimenti? Di che tipo di sentimenti stai parlando? Sentimenti... come si può essere così sconsiderati alla tua età?! Vergogna su di te per indulgere i giovani nei loro capricci e agire come un ruffiano! Non solo hai portato via una ragazza dalla sua casa, ma hai anche rovinato la vita del mio giovane inesperto. Non ci saranno ringraziamenti per te. Addio.";
			link.l1 = "Bene, e lo stesso a te...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		case "node_4":
			//--> дача миниквестов начальника порта. 
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("Sì, dannazione! Ho un lavoro per te!","Ah! Sei arrivato proprio in tempo! Ho un problema da risolvere.","Certo! Certo che ho lavoro per te! Sai, sono proprio sommerso di problemi ultimamente...");
				link.l1 = "Allora per favore, vai al dunque, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 Генер "Сгоревшее судно"
			if(hrand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "Dio! Capitano "+GetFullName(PChar)+", sei arrivato proprio in tempo! È successa una tale disgrazia, un tale disastro... La nave è bruciata in rada mentre era sotto la custodia dell'autorità portuale! A causa della negligenza della sicurezza, la nave è bruciata... bruciata fino alla linea di galleggiamento...\n"+"Signore, cosa ho fatto per meritare una tale punizione? Sono stato un servo fedele per così tanti anni...";
				link.l1 = "Allora, qual è il grosso problema? Una nave è bruciata? E a cosa servono i contratti di assicurazione? O hai deciso di non assicurarla per risparmiare i tuoi soldi e ora te ne stai mangiando il cuore?";
				link.l1.go = "BurntShip4";
				link.l2 = "Lo scalo navale potrà aiutarti meglio di me. In un paio di mesi potranno restaurare il vecchio, o addirittura costruirne uno nuovo. Mi dispiace, non sono un costruttore di navi...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "Il governatore si preoccupa per il benessere dei suoi cittadini, quindi ha sempre alcuni lavori da offrire. Potrebbero esserci mercanti nella taverna interessati a ottenere aiuto, e il negozio ha bisogno di capitani di trasporto, anche.";
			Link.l1 = "Ho un'altra domanda.";
			Link.l1.go = "node_2";
			Link.l2 = "Grazie. Arrivederci.";
			Link.l2.go = "exit";
		break;

///Jason-----------------------новые генераторы накопительного типа для портмана----------------------------
		int iTime, idaysQty, iGoods, iGoodsQty, amount;
		case "Work_check"://фейс-контроль - общая проверка профпригодности ГГ и выбор задания
			//--> проверка миниквестов начальника порта. 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "Dovevi localizzare il capitano "+npchar.quest.PortmansJornal.capName+" e restituisci il suo registro di bordo. Sei riuscito?";
				link.l1 = "No, non ancora...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "Ti sei impegnato a cercare un oggetto rubato "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"'. Non ci saranno altre missioni per te fino a quando non avrai terminato quella.";
				link.l1 = "Continuerò la mia ricerca, solo aspetta.";
				link.l1.go = "exit";
				link.l2 = "Voglio rinunciare all'incarico.";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "Mi hai promesso di cercare il rubato "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"'. L'hai fatto?";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName && 
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}				
				if (bOk)
				{
					link.l1 = "Sì, l'ho trovato, ora è nel porto. Puoi prenderlo.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "Continuerò la mia ricerca, aspetta solo.";
					link.l1.go = "exit";
				}
				link.l2 = "Voglio rinunciare all'incarico.";
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта. 
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2)//проверка повтора
				{
					if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
					{
						dialog.text = RandPhraseSimple("Non c'è lavoro per coloro che navigano sotto la bandiera di "+NationNameGenitive(sti(pchar.nation))+"! Uscite dal mio ufficio immediatamente!","Non collaborerò con "+NationNameAblative(sti(pchar.nation))+". Vattene!");
						link.l1 = RandPhraseSimple("Bene, come desideri...","Bene, come preferisci...");
						link.l1.go = "exit";
						break;
					}
					if (isBadReputation(pchar,40)) // проверка репутации ГГ с вызывающим доверие belamour legendary edition
					{
						dialog.text = "La tua reputazione non mi ispira fiducia. Non ho intenzione di collaborare con te. Addio.";
						link.l1 = "Cosa! Sono tutte bugie.";
						link.l1.go = "exit";
						break;
					}
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
					{
						dialog.text = "Non voglio insultarti, capitano, ma... temo che tu non sia in grado di eseguire la mia missione - ti manca semplicemente l'esperienza. Non posso firmare un contratto con te.";
						link.l1 = "Capisco. Beh, come dici tu.";
						link.l1.go = "exit";
						break;
					}
					dialog.Text = "Mmm... Beh, dipende dal lavoro che ti interessa.";
					link.l1 = "Potrei offrirti di noleggiare la mia nave per il trasporto di merci.";
					Link.l1.go = "Fraht_begin";		//фрахты
					link.l2 = "Voglio guadagnare soldi extra scortando mercanti o consegnando posta.";
					Link.l2.go = "Check_other";		//доставка почты, эскорт
					Link.l3 = "Ebbene, forse potresti offrire qualcosa?";
					Link.l3.go = "node_4"; 			//судовой журнан, угнанное судно, сгоревшее судно
				}
				else
				{
					dialog.Text = "Non c'è più nulla per oggi. Torna un altro giorno.";
					link.l1 = "Bene.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Non vedo la tua nave nel porto. Allontanati e poi torna a trovarmi - cercheremo di trovare qualcosa per te.";
				link.l1 = "Bene, farò proprio così.";
				link.l1.go = "exit";
			}
		break;
	
		case "Check_other"://выбор между почтовым курьером, эскортом и ничем
		SaveCurrentNpcQuestDateParam(npchar, "work_date"); // mitrokosta безусловно сохраняем
		int nTask = 0;
		string tasks[10]; // mitrokosta сделал выбор задания расширяемым на тот случай если задания добавятся
		if (sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER) {
			tasks[nTask] = "cureer";
			nTask++;
		}
		if (GetCompanionQuantity(pchar) < 3 && sti(RealShips[sti(pchar.Ship.Type)].Class) >= 4 && or(sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_WAR, sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER)) {
			tasks[nTask] = "escort";
			nTask++;
		}
		if (nTask > 0 && hrand(5) > 1) {
			string sTask = tasks[hrand(nTask - 1)];
			switch (sTask) {
				case "cureer":
					if (pchar.questTemp.WPU.Postcureer == "begin" || pchar.questTemp.WPU.Postcureer == "late" || pchar.questTemp.WPU.Postcureer == "lost" || pchar.questTemp.WPU.Postcureer == "fail" || CheckAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp")) { // если заняты
						dialog.text = "Sfortunatamente, non posso offrirti nulla del genere. Passa di nuovo tra un paio di giorni.";
						link.l1 = "Va bene, farò proprio così.";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Postcureer.count) > 3 && hrand(1) == 1) { //если 2 уровень
							dialog.text = "Allora... Hai già svolto diversi incarichi come corriere e, a quanto ne so, sei stato abbastanza bravo. Probabilmente puoi gestire il compito che sto per affidarti.";
							link.l1 = "Sono tutto orecchie, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "Postcureer_LevelUp";
						} else { // первый уровень
							dialog.text = "Vedo che hai una nave veloce. Posso offrirti un lavoro da corriere - consegnare posta e documenti commerciali.";
							link.l1 = "Questo è interessante. Sono d'accordo. Dove devo andare?";
							link.l1.go = "Postcureer";
							link.l2 = "Grazie, ma questo semplicemente non è il tipo di lavoro per me.";
							link.l2.go = "exit";
						}
					}
				break;

				case "escort":
					if (pchar.questTemp.WPU.Escort == "begin" || pchar.questTemp.WPU.Escort == "late" || pchar.questTemp.WPU.Escort == "win" || CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp")) { // если заняты
						dialog.text = "Sfortunatamente, non posso offrirti nulla del genere. Passa di nuovo tra un paio di giorni.";
						link.l1 = "Bene, farò proprio così.";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Escort.count) > 3 && hrand(1) == 1) { // 2 уровень
							dialog.text = "Hai già scortato con successo diverse navi mercantili. Immagino di avere un incarico che potrebbe farti al caso tuo.";
							link.l1 = "Sono tutto orecchie.";
							link.l1.go = "Escort_LevelUp";
						} else { // 1 уровень
							if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_H && 2500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) < 0 && !CheckAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID")) { // если на ТГ
								dialog.text = "Ho un lavoro proprio per te. Ci sono due navi mercantili nel porto che avrebbero già dovuto salpare. Il fatto è che la loro nave di scorta è stata danneggiata e sta ancora aspettando le riparazioni necessarie, quindi non sarà in grado di partire presto.\nSi scopre che la tua nave è ideale per il lavoro - in più devo ancora depositare un carico aggiuntivo nella tua stiva. Naturalmente, il pagamento sarà doppio - sia per il trasporto che per la scorta.";
								link.l1 = "Che offerta interessante! La accetto!";
								link.l1.go = "escort_bonus";
								link.l2 = "Grazie, ma questo non è il tipo di lavoro che fa per me.";
								link.l2.go = "exit";
							} else { // просто эскорт
								dialog.text = "Ho un lavoro solo per te. Due navi mercantili sono attualmente ancorate nel nostro porto - hanno bisogno di scorta. Ti offro di scortare queste navi alla loro destinazione. Lo farai?";
								link.l1 = "Un'offerta interessante! La accetto!";
								link.l1.go = "escort";
								link.l2 = "Grazie, ma questo semplicemente non è il mio tipo di lavoro.";
								link.l2.go = "exit";
							}
						}
					}
				break;
			}
			break;
		}
		//ничего не подошло
		dialog.text = "Sfortunatamente, non posso offrirti nulla di quel genere. Passa di nuovo tra un paio di giorni.";
		link.l1 = "Bene, farò proprio così.";
		link.l1.go = "exit";
		break;

///--> ------фрахт со свободным выбором пункта назначения, оплаты и вида груза из предложенного списка---------

		case "Fraht_begin":
			if (hrand(4) < 4)
			{
				if (pchar.questTemp.WPU.Fraht == "begin" || pchar.questTemp.WPU.Fraht == "late" || pchar.questTemp.WPU.Fraht == "lost" || CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))//проверка на занятость
				{
					dialog.Text = "Ma ho sentito dire che la tua nave era già affittata. Non posso darti altri carichi. Adempie agli impegni che hai già preso.";
					link.l1 = "Sì, probabilmente hai ragione.";
					Link.l1.go = "exit";
					break;
				}
				if (1500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) > 0)//мало места - не даем
				{
					dialog.text = "Hai troppo poco spazio nella tua stiva. Ho bisogno di una nave più capiente per un carico. Ti suggerisco di controllare nel negozio - il mercante locale affitta spesso navi per consegnare piccole partite di merci.";
					link.l1 = "Capisco. Beh, come dici tu.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.WPU.Fraht.count > 3 && rand(1) == 0)
				{
					dialog.text = "Non ho nulla di adatto al momento. Ma hai già effettuato diverse consegne di successo. Ho un certo lavoro che vorrei assegnarti specificamente a te.";
					link.l1 = "Sto ascoltando. Che tipo di lavoro?";
					link.l1.go = "Fraht_LevelUp";
					break;
				}
				dialog.Text = "Ebbene, posso offrirti diverse opportunità di noleggio.";
				link.l1 = "Vediamo, allora...";
				Link.l1.go = "Fraht_choise";
			}
			else
			{
				dialog.Text = "Non ci sono più merci per oggi. Vieni un altro giorno.";
				link.l1 = "Vabbè.";
				Link.l1.go = "exit";
			}
		break;
	
		int iFrahtGoods1, iFrahtGoods2, iFrahtGoods3, iFrahtGoods;
		int iFrahtGoodsQty1, iFrahtGoodsQty2, iFrahtGoodsQty3;
		case "Fraht_choise":
			//выбираем города
			pchar.questTemp.WPU.Fraht.City1 = findCurrentCity1(npchar);
			pchar.questTemp.WPU.Fraht.City2 = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Fraht.City3 = findCurrentCity3(npchar);
			//выбираем товары
			iFrahtGoods1 = hrand(GOOD_PAPRIKA);
			iFrahtGoods2 = hrand(GOOD_PAPRIKA-3);
			iFrahtGoods3 = hrand(GOOD_PAPRIKA-7);
			pchar.questTemp.WPU.Fraht.Goods1 = iFrahtGoods1;
			pchar.questTemp.WPU.Fraht.Goods2 = iFrahtGoods2;
			pchar.questTemp.WPU.Fraht.Goods3 = iFrahtGoods3;
			//определим количество
			iFrahtGoodsQty1 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods1))/(1+frand(0.5));
			iFrahtGoodsQty2 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods2))/(1+frand(0.5));
			iFrahtGoodsQty3 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods3))/(1+frand(0.5));
			if (sti(iFrahtGoodsQty1) > 10000) iFrahtGoodsQty1 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty2) > 10000) iFrahtGoodsQty2 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty3) > 10000) iFrahtGoodsQty3 = 10000 + rand(500);
			pchar.questTemp.WPU.Fraht.GoodsQty1 = iFrahtGoodsQty1;
			pchar.questTemp.WPU.Fraht.GoodsQty2 = iFrahtGoodsQty2;
			pchar.questTemp.WPU.Fraht.GoodsQty3 = iFrahtGoodsQty3;
			pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Fraht.Chance = rand(4);//форс-мажор
			//определим сроки с учётом рандома
			int daysQty1 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City1));
			int daysQty2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City2));
			int daysQty3 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City3));
			pchar.questTemp.WPU.Fraht.DaysQty1 = makeint(sti(daysQty1)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty2 = makeint(sti(daysQty2)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty3 = makeint(sti(daysQty3)*(frand(1.3)+0.7));
			//установим цену исходя из объёма груза, дальности и сроков
			pchar.questTemp.WPU.Fraht.Money1 = (makeint((sti(iFrahtGoodsQty1) * sti(Goods[iFrahtGoods1].Weight) / sti(Goods[iFrahtGoods1].Units))))*(sti(daysQty1)*2)*sti(daysQty1)/sti(pchar.questTemp.WPU.Fraht.DaysQty1);
			pchar.questTemp.WPU.Fraht.Money2 = (makeint((sti(iFrahtGoodsQty2) * sti(Goods[iFrahtGoods2].Weight) / sti(Goods[iFrahtGoods2].Units))))*(sti(daysQty2)*2)*sti(daysQty2)/sti(pchar.questTemp.WPU.Fraht.DaysQty2);
			pchar.questTemp.WPU.Fraht.Money3 = (makeint((sti(iFrahtGoodsQty3) * sti(Goods[iFrahtGoods3].Weight) / sti(Goods[iFrahtGoods3].Units))))*(sti(daysQty3)*2)*sti(daysQty3)/sti(pchar.questTemp.WPU.Fraht.DaysQty3);
			if (hrand(5) < 4)//три варианта
			{
				dialog.text = "Ecco le varianti disponibili:\n"+"carico "+GetGoodsNameAlt(iFrahtGoods1)+" in quantità di "+FindRussianQtyString(iFrahtGoodsQty1)+" alla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\nmerce "+GetGoodsNameAlt(iFrahtGoods2)+" in quantità di "+FindRussianQtyString(iFrahtGoodsQty2)+" alla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\nmerce "+GetGoodsNameAlt(iFrahtGoods3)+" in quantità di "+FindRussianQtyString(iFrahtGoodsQty3)+" alla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty3)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3))+"\nQual è la tua scelta?";
				Link.l1 = "Sceglierò la seconda opzione - una carta per la città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" carico di "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Sceglierò la terza variante - un affitto per la città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" carico di "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
				Link.l3 = "Sceglierò la terza variante - carta per la città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+" carico di "+GetGoodsNameAlt(iFrahtGoods3)+".";
				Link.l3.go = "Fraht_Choise_3";
			}
			else //два варианта
			{
				dialog.text = "Ecco le varianti disponibili:\n"+"carico "+GetGoodsNameAlt(iFrahtGoods1)+" nell'importo di "+FindRussianQtyString(iFrahtGoodsQty1)+" alla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\nmerce "+GetGoodsNameAlt(iFrahtGoods2)+" nella quantità di "+FindRussianQtyString(iFrahtGoodsQty2)+" alla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\nQual è la tua scelta?";
				Link.l1 = "Sceglierò la prima variante - una carta per la città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" carico di "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Sceglierò la seconda variante - una carta per la città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" carico di "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
			}
			Link.l4 = "Sfortunatamente, non c'è nulla di adatto per me.";
			Link.l4.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;
	
		case "Fraht_Choise_1":
			dialog.text = "Bene, ottimo! Elaborerò i documenti necessari e tu puoi preparare la tua nave per il carico.";
			link.l1 = "Farò del mio meglio!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods1), sti(pchar.questTemp.WPU.Fraht.GoodsQty1));
			iFrahtGoods1 = pchar.questTemp.WPU.Fraht.Goods1;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods1));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty1)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty1)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty1), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City1+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods1].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods1].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty1);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods1);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty1);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money1);
		break;
	
		case "Fraht_Choise_2":
			dialog.text = "Bene, fantastico! Elaborerò i documenti necessari e tu potrai preparare la tua nave per il carico.";
			link.l1 = "Farò del mio meglio!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods2), sti(pchar.questTemp.WPU.Fraht.GoodsQty2));
			iFrahtGoods2 = pchar.questTemp.WPU.Fraht.Goods2;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods2));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty2)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty2)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty2), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City2+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods2].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods2].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty2);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods2);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty2);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money2);
		break;
	
		case "Fraht_Choise_3":
			dialog.text = "Bene, ottimo! Provvederò ai documenti necessari, e tu puoi preparare la tua nave per il carico.";
			link.l1 = "Farei del mio meglio!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods3), sti(pchar.questTemp.WPU.Fraht.GoodsQty3));
			iFrahtGoods3 = pchar.questTemp.WPU.Fraht.Goods3;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods3));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty3)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty3)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty3), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City3+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods3].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods3].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty3);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods3);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty3);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money3);
		break;
	
		case "Fraht_Forcemajor":
			pchar.questTemp.WPU.Fraht = "begin";
			sld = characterFromId(pchar.questTemp.WPU.Fraht.TargetPortmanID);
			pchar.questTemp.WPU.Fraht.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Fraht.TargetCity = FindTownOnIsland(pchar.questTemp.WPU.Current.TargetIslandID);
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Fraht.Chance > 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Fraht.Chance == 2) FrahtHunterOnSea();//создание ДУ в акватории
			DialogExit();
		break;
	
		case "Fraht_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			iFrahtGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
			amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
			if (amount > 0)
			{
				dialog.text = "Vediamo allora. Dovevi consegnare un carico di "+GetGoodsNameAlt(iFrahtGoods)+" in quantità di "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Ma come posso vedere, non hai consegnato l'intera spedizione - tu sei "+FindRussianQtyString(sti(amount))+" breve.";
				link.l1 = "Mille squali! Devono essere quei maledetti ratti! Ma non preoccuparti, "+GetAddress_FormToNPC(NPChar)+", acquisterò la quantità mancante e consegnerò l'intero lotto.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Vediamo, allora. Dovevi consegnare un carico di "+GetGoodsNameAlt(iFrahtGoods)+" nella quantità di "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Corretto?";
			link.l1 = "Assolutamente corretto, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Fraht_complete_1";
		}
		else
		{
			dialog.text = "Non vedo la tua nave nel porto. Allontanati e poi vieni a cercarmi di nuovo - allora parleremo.";
			link.l1 = "Bene, farò proprio così.";
			link.l1.go = "exit";
		}
		break;
	
		case "Fraht_complete_1":
			if (pchar.questTemp.WPU.Fraht == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Fraht.Late"))+1;
				pchar.questTemp.WPU.Fraht.DayLate = iTime;
				pchar.questTemp.WPU.Fraht.PercentLate = iTime/0.2;
				pchar.questTemp.WPU.Fraht.Money = makeint(sti(pchar.questTemp.WPU.Fraht.Money) - sti(pchar.questTemp.WPU.Fraht.Money)*sti(pchar.questTemp.WPU.Fraht.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Mh... Ma tu eri "+FindRussianDaysString(iTime)+" in ritardo. Pertanto devo tagliare il tuo pagamento per il trasporto. Secondo il contratto, la tua multa è del cinque percento dell'importo totale per ogni giorno di ritardo. Ora per favore, prendi il tuo "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+", e cerca di attenerti al contratto in futuro.";
				link.l1 = "Bene, è comunque qualcosa.";
				link.l1.go = "Fraht_complete_2";
				break;
			}
			dialog.text = "Grazie per il tuo lavoro. Per favore, prendi il tuo pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Grazie!";
			link.l1.go = "Fraht_complete_2";
		break;
	
		case "Fraht_complete_2":
			if (pchar.questTemp.WPU.Fraht == "begin")
			{
				pchar.quest.FrahtTime_Over.over = "yes";
				AddQuestRecord("Fraht", "2");
			}
			else
			{
				pchar.quest.FrahtTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Fraht", "4");
				AddQuestUserData("Fraht", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Fraht.DayLate));
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
			}
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
			CloseQuestHeader("Fraht");
			DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "Fraht_complete_bad":
			dialog.text = "Hai consegnato il carico? Bene. In realtà, abbiamo dovuto acquistarlo da soli per consegnarlo al destinatario! E sai, è costato parecchio. Quindi, se vuoi ristabilire la tua buona volontà, dovrai compensare le nostre spese e pagare anche la multa. Quanto al carico, puoi tenerlo - non ne abbiamo più bisogno.";
			link.l1 = "Sì, certo. Quanto?";
			link.l1.go = "Fraht_complete_bad_1";
		break;
	
		case "Fraht_complete_bad_1":
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)*3;
			dialog.text = "Tre volte il costo delle merci. Questo ammonta a "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+".";
			if (sti(Pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
			{
				link.l1 = "È un bel po'. Ma gli affari sono affari. Bene, ecco i tuoi soldi.";
				link.l1.go = "Fraht_complete_pay";
			}
			link.l2 = "Sei pazzo? Chiedere una somma così esorbitante è il colmo dell'avidità! Non otterrai nulla da me!";
			link.l2.go = "Fraht_complete_fail";
		break;
	
		case "Fraht_complete_pay":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			dialog.text = "Una decisione saggia. Ora vedo che sei davvero una persona seria. Immagino che potremmo ancora lavorare insieme in futuro.";
			link.l1 = "Grazie, e ora devo andare.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 12);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 30);
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "8");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "6");
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Fraht");
				pchar.questTemp.WPU.Fraht = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 70);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
		break;
	
		case "Fraht_complete_fail":
			dialog.text = "Oh, capisco... Beh, in tal caso non dovresti mai mostrare di nuovo il tuo viso in qualsiasi autorità portuale di "+NationNameGenitive(sti(pchar.questTemp.WPU.Fraht.Nation))+"! Vattene!";
			link.l1 = "Certo che non mi sono perso molto...";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "9");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "7");
				CloseQuestHeader("Fraht");
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
		break;
	
		case "Fraht_complete_3":
			dialog.text = "Sbrigati, il destinatario sa già che la tua nave è arrivata e si preoccupa per il suo carico.";
			link.l1 = "In tal caso non sprecherò più tempo!";
			link.l1.go = "exit";
		break;
	//фрахт <--
	
/// -------------------------------работа курьером по доставке почты-------------------------------------

		case "Postcureer":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.7)); 
			if (sti(pchar.questTemp.WPU.Postcureer.DaysQty) == 1) pchar.questTemp.WPU.Postcureer.DaysQty = 2;
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*1000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));
			dialog.text = "Questo pacco deve essere consegnato all'autorità portuale nella città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)+", per "+FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DaysQty)+", e il più presto possibile. Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))".";
			link.l1 = "Sono d'accordo!";
			link.l1.go = "Postcureer_1";
			link.l2 = "Mmm... Ma non sto andando in quella direzione. Mi dispiace, ma devo rifiutare.";
			link.l2.go = "exit";
		break;
	
		case "Postcureer_1":
			dialog.text = "Eccellente! Sto contando su di te. Ecco il pacco.";
			link.l1 = "Salperò immediatamente!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "PostLetters");
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)+1;//считаем сделанные доставки
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			if (pchar.questTemp.WPU.Postcureer.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Postcureer.Chance == 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "1");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_complete":
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.DayLate = iTime;
				pchar.questTemp.WPU.Postcureer.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money) - sti(pchar.questTemp.WPU.Postcureer.Money)*sti(pchar.questTemp.WPU.Postcureer.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Mh... Ma tu eri "+FindRussianDaysString(iTime)+" in ritardo. Pertanto devo ridurre il tuo pagamento per il lavoro. Secondo il contratto, la tua penalità è del cinque percento dell'importo totale per ogni giorno di ritardo. Ora per favore, prendi il tuo "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+", e cerca di attenerti al contratto in futuro.";
				link.l1 = "Bene, è qualcosa almeno.";
				link.l1.go = "Postcureer_complete_1";
				break;
			}
			dialog.text = "Grazie per il tuo lavoro. Per favore, prendi il tuo pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
			link.l1 = "Grazie!";
			link.l1.go = "Postcureer_complete_1";
		break;
	
		case "Postcureer_complete_1":
			if (pchar.questTemp.WPU.Postcureer == "begin")
			{
				pchar.quest.PostcureerTime_Over.over = "yes";
				AddQuestRecord("Postcureer", "2");
			}
			else
			{
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "4");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DayLate));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			}
			RemoveItems(PChar, "PostLetters", 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Achievment_Set("ach_CL_118");
			DialogExit();
		break;
	
		case "Postcureer_complete_bad":
			dialog.text = "E cosa dovremmo farne ora? La gente l'aspettava da chissà quanto tempo, e tu l'hai portato solo oggi. Va bene, dammelo - forse ci sarà ancora qualche utilità. E spero che capisci che ora non è dovuto nessun pagamento.";
			link.l1 = "Certo, lo faccio. Prendi il tuo fagotto. Addio.";
			link.l1.go = "exit";
			RemoveItems(PChar, "PostLetters", 1);
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			Group_DeleteGroup("Fraht_Attack");
			pchar.questTemp.WPU.Postcureer = "fail";
		break;
	
/// ---------------------------работа в качестве эскорта для торговых кораблей----------------------------

		case "escort":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods1 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.Goods2 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1)); 
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));
			dialog.text = "Allora, dovrai scortare le navi '"+pchar.questTemp.WPU.Escort.ShipName1+"' e '"+pchar.questTemp.WPU.Escort.ShipName2+"' alla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", per "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))". Entrambe le navi devono raggiungere la loro destinazione sani e salvi. Consegnerai le navi all'ufficiale dell'autorità portuale locale. Sarà anche lui a pagarti per il lavoro.";
			link.l1 = "Tutto sembra chiaro. Posso procedere?";
			link.l1.go = "escort_1";
			link.l2 = "Mah... Ma non sto andando in quella direzione. Mi dispiace, ma devo rifiutare.";
			link.l2.go = "exit";
		break;
	
		case "escort_1":
			dialog.text = "Vai avanti. A questo punto, quelle navi sono al tuo comando.";
			link.l1 = "Allora sto prendendo il largo!";
			link.l1.go = "escort_add_ships";
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "1");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)); // belamour gen
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "escort_add_ships":
			int iGoods1, iGoods2, iSpace1, iSpace2, ShipType, Rank;
			int iNation = pchar.questTemp.WPU.Escort.ShipNation;
			int iLifeday = sti(pchar.questTemp.WPU.Escort.DaysQty)+10;
			string sTemp;
	        for (i=1; i<=2; i++)
	        {
				ShipType = GetRandomShipType(GetClassFlag(sti(RealShips[sti(pchar.Ship.Type)].Class)), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
				Rank = 5 * (6 - sti(RealShips[sti(pchar.Ship.Type)].Class)) + rand(5);
				if (i == 1) sTemp = pchar.questTemp.WPU.Escort.ShipName1;
				if (i == 2) sTemp = pchar.questTemp.WPU.Escort.ShipName2;
				if (i == 2) ShipType = SHIP_FLEUT;//один всегда флейт
	            sld = GetCharacter(NPC_GenerateCharacter("EscortCaptain_"+i, "trader_"+(rand(15)+1), "man", "man", Rank, iNation, iLifeday, true, "citizen"));
				FantomMakeSmallSailor(sld, ShipType, sTemp, -1, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				SetCharacterGoods(sld, GOOD_FOOD, 400+rand(200));
				SetCharacterGoods(sld, GOOD_MEDICAMENT, 60+rand(30));
	            iGoods1 = sti(pchar.questTemp.WPU.Escort.Goods1);
				iSpace1 = GetCharacterFreeSpace(sld, iGoods1);
				iSpace1 = makeint(iSpace1/2 + rand(iSpace1/2));
				iGoods2 = sti(pchar.questTemp.WPU.Escort.Goods2);
				iSpace2 = GetCharacterFreeSpace(sld, iGoods2);
				iSpace2 = makeint(iSpace2/2 + rand(iSpace2/2));
				if (i == 1) SetCharacterGoods(sld, iGoods1, iSpace1);
				if (i == 2) SetCharacterGoods(sld, iGoods2, iSpace2);
				sld.CompanionEnemyEnable = false; //всегда друзья
	            SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.loyality = MAX_LOYALITY;
				SetCharacterRemovable(sld, false);
				sld.Dialog.Filename = "Common_portman.c";
				sld.dialog.currentnode = "Escort_companion";
				pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l1.character = "EscortCaptain_1";
				pchar.quest.Escort_fail.win_condition.l2 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l2.character = "EscortCaptain_2";
				pchar.quest.Escort_fail.function = "Escort_failed";
	        }
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			DialogExit();
		break;
	
		case "Escort_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//проверяем, все ли корабли
			if (GetCharacterIndex("EscortCaptain_1") == -1 || GetCharacterIndex("EscortCaptain_2") == -1)
			{
				dialog.text = "Mmm... Vedo solo una nave nella tua scorta. È corretto?";
				link.l1 = "Sì, "+GetAddress_FormToNPC(NPChar)+". Un altro è stato affondato in una battaglia con una squadra nemica.";
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
				{
					link.l1.go = "EscortBonus_complete_fail";
				}
				else
				{
					link.l1.go = "Escort_complete_fail";
				}
				break;
			}
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				//pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney);
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.TotalMoney);
				amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
				if (amount > 0)
				{
					dialog.text = "Bene, allora. Dovevi scortare le navi e consegnare il carico di "+GetGoodsNameAlt(iGoods)+" in quantità di "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+". Ma vedo che non hai consegnato l'intero carico - tu sei "+FindRussianQtyString(sti(amount))+" breve.";
					link.l1 = "Mille squali! Devono essere quei maledetti ratti! Ma non preoccuparti, "+GetAddress_FormToNPC(NPChar)+", Acquisterò la quantità mancante e consegnerò l'intero lotto.";
					link.l1.go = "Fraht_complete_3";
					break;
				}
			}
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Mm... Ma tu eri "+FindRussianDaysString(iTime)+" in ritardo. Pertanto devo tagliare il tuo pagamento per il lavoro. Secondo il contratto, la tua multa è del cinque percento dell'importo totale per ogni giorno di ritardo. Ora per favore, prendi il tuo "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", e cerca di attenerti al contratto in futuro.";
				link.l1 = "Ebbene, è sempre qualcosa.";
				link.l1.go = "Escort_complete_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				dialog.text = "Bene, allora. Dovevi scortare le navi e consegnare il carico di "+GetGoodsNameAlt(iGoods)+" nell'importo di "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+". Grazie per il tuo lavoro. Per favore, prendi il tuo pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			else
			{
				dialog.text = "Grazie per il tuo lavoro. Per favore, prendi il tuo pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			link.l1 = "Grazie!";
			link.l1.go = "Escort_complete_1";
		}
		else
		{
			dialog.text = "Non vedo la tua nave in porto. Allontanati e poi torna a vedermi - allora parleremo.";
			link.l1 = "Bene, farò proprio così.";
			link.l1.go = "exit";
		}
		break;
	
		case "Escort_complete_1":
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				AddQuestRecord("Escort", "2");
			}
			else
			{
				pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//опоздавший рейс не засчитываем
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
				{
					pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				}
				AddQuestRecord("Escort", "4");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_1"));//удалим компаньонов
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_2"));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 100);//защита
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "escort_bonus":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods = 	hrand(GOOD_PAPRIKA);//для ГГ
			pchar.questTemp.WPU.Escort.Goods1 = hrand(GOOD_PAPRIKA-3);
			pchar.questTemp.WPU.Escort.Goods2 = hrand(GOOD_PAPRIKA-5);
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			iGoodsQty = makeint(GetCharacterFreeSpace(pchar, iGoods))-(50+rand(100));//количество груза
			pchar.questTemp.WPU.Escort.GoodsQty = iGoodsQty;
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1));//дни
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));//оплата за сопровождение
			pchar.questTemp.WPU.Escort.BonusMoney = (makeint((sti(iGoodsQty) * sti(Goods[iGoods].Weight) / sti(Goods[iGoods].Units))))*(sti(idaysQty)*2)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty);//оплата за фрахт
			pchar.questTemp.WPU.Escort.TotalMoney = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney); // общая сумма
			dialog.text = "Allora, dovrai scortare le navi '"+pchar.questTemp.WPU.Escort.ShipName1+"' e '"+pchar.questTemp.WPU.Escort.ShipName2+"' alla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", per "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". Pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+"\nAnche sulla tua nave, colloco il carico di "+GetGoodsNameAlt(iGoods)+" nella quantità di "+FindRussianQtyString(iGoodsQty)+". Pagamento per la consegna - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+".";
			link.l1 = "Tutto sembra chiaro. Posso procedere?";
			link.l1.go = "escort_bonus_1";
			link.l2 = "Hmm... Ma non sto andando in quella direzione. Mi dispiace, ma devo rifiutare.";
			link.l2.go = "exit";
		break;
	
		case "escort_bonus_1":
			dialog.text = "Eccellente! Prendi il comando della squadra.";
			link.l1 = "Allora, salpo!";
			link.l1.go = "escort_add_ships";
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.Bonus = "true";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap();//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 3) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "6");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
			AddQuestUserData("Escort", "sGoods", GetGoodsNameAlt(iGoods));
			AddQuestUserData("Escort", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)));
			AddQuestUserData("Escort", "sMoney1", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Escort.GoodsQty);//средняя стоимость товара
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "Escort_complete_fail":
			dialog.text = "Incredibile! E a cosa servivi? Come hai potuto permettere che ciò accadesse?! Spero tu capisca che ora è fuori discussione una ricompensa.";
			link.l1 = "Certo, lo faccio... Beh, cordiali saluti.";
			link.l1.go = "exit";
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			pchar.quest.EscortTime_Over.over = "yes";//снять прерывание // patch-2
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));
			AddQuestRecord("Escort", "11");
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "EscortBonus_complete_fail":
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));//удалим компаньона
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			pchar.questTemp.WPU.Escort.GoodsQty = GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				pchar.questTemp.WPU.Escort.MinusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)*sti(amount));
				if (sti(pchar.questTemp.WPU.Escort.MinusMoney) < 0) amount = 101;
				if (amount > 0 && amount <= 100)
				{
					pchar.questTemp.WPU.Escort.BonusMoney = sti(pchar.questTemp.WPU.Escort.MinusMoney);
					dialog.text = "Incredibile! E a cosa servivi? Come hai potuto permettere che succedesse?! Spero tu capisca che qualsiasi ricompensa per la scorta è ora fuori discussione... Non solo, ma sei anche a corto di carico - "+FindRussianQtyString(sti(amount))+"\nIn generale, ti pagherò solo per il trasporto di merci che sono state consegnate in condizioni accettabili, meno il valore degli articoli mancanti. Prendi il tuo "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" e puoi andare dove ti pare.";
					link.l1 = "Beh, è qualcosa almeno.";
					link.l1.go = "EscortBonus_complete_fail_1";
					break;
				}
				if (amount > 100)
				{
					dialog.text = "Incredibile! E perché avevamo bisogno di te? Come hai potuto permettere che ciò accadesse?! Spero tu capisca che qualsiasi ricompensa per l'escorta è ora fuori discussione... Non solo, ma hai anche una grossa mancanza di merce.\nNon ho tempo di aspettare che tu acquisisca le merci mancanti. Quindi devi compensare il costo in pieno - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+". Per quanto riguarda il carico, puoi tenerlo.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Bene, non ti agitare troppo. Ecco i tuoi soldi.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Siete tutti impazziti? Questa è pura estorsione! Non vi darò nulla!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Incredibile! E perché avevamo bisogno di te? Come hai potuto permettere che ciò accadesse?! Spero che tu capisca che ora qualsiasi ricompensa per l'escorta è fuori discussione.\nIn generale, pagherò solo per il trasporto delle merci che hai preso. Prendi il tuo "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" e puoi andare dove ti pare.";
				link.l1 = "Bene, è qualcosa almeno.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
			if (pchar.questTemp.WPU.Escort == "late")
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.BonusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Escort.BonusMoney)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				if (amount > 0)
				{
					dialog.text = "Incredibile! E a cosa servivi? Come hai potuto permettere che succedesse?! Spero tu capisca che ora è fuori discussione qualsiasi ricompensa per la scorta... Hai perso una nave, sei arrivato "+FindRussianDaysString(iTime)+" in ritardo, e per di più, sei a corto di carico anche - "+FindRussianQtyString(sti(amount))+"\nNon ho tempo di aspettare che tu acquisisca le merci mancanti. Quindi devi compensare il costo per intero "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+". Per quanto riguarda il carico, puoi tenerlo.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Bene, non ti agitare troppo. Ecco i tuoi soldi.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Siete tutti impazziti? Questo è estorsione pura! Non vi darò nulla!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Incredibile! E a cosa servivi tu? Come hai potuto permettere che ciò accadesse?! Spero tu capisca che ora qualsiasi ricompensa per la scorta è fuori discussione... Inoltre, sei arrivato "+FindRussianDaysString(iTime)+" in ritardo.\nQuindi ho dovuto ridurre il pagamento per il trasporto. Secondo l'accordo, la multa è del 10 percento dell'importo originale per ogni giorno di ritardo. Ora, prendi il tuo "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+", e puoi andare.";
				link.l1 = "Beh, è almeno qualcosa.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
		break;
	
		case "EscortBonus_complete_fail_1"://потеряли корабль, время и груз в норме или частично
			AddQuestRecord("Escort", "12");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.BonusMoney));
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_2"://потеряли корабль и груз, время норма или нет, мир
			AddQuestRecord("Escort", "13");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_3"://потеряли корабль и груз, время норма или нет, война
			dialog.text = "Oh, capisco... Beh, in questo caso non dovresti mai mostrare di nuovo il tuo volto in qualsiasi autorità portuale di "+NationNameGenitive(sti(pchar.questTemp.WPU.Escort.Nation))+"! Vattene!";
			link.l1 = "Certo che non mi sono perso molto...";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "14");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Escort.Nation)) + "hunter", 30);
			pchar.questTemp.WPU.Fraht.Nation = pchar.questTemp.WPU.Escort.Nation;
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "Escort_fail"://потеряли 2 корабля
			dialog.text = "Questo è molto, molto male! Per cosa ti abbiamo assunto, puoi dirmelo? Per proteggere le navi? O solo per perdere tempo?";
			link.l1 = "Capisco. Il nemico era semplicemente troppo forte, e... ma a che serve discutere - ciò che è successo, è già successo. Ma la merce - la merce è ancora intatta! Quindi sistemiamola.";
			link.l1.go = "Escort_fail_complete";
		break;
	
		case "Escort_fail_complete":
			iFrahtGoods = makeint(pchar.questTemp.WPU.Escort.Goods);
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (amount > 0)
			{
				dialog.text = "Vediamo, allora. Dovevi consegnare un carico di "+GetGoodsNameAlt(iFrahtGoods)+" nella quantità di "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+". Ma vedo che non hai consegnato l'intero carico - tu sei "+FindRussianQtyString(sti(amount))+" breve.";
				link.l1 = "Mille squali! Devono essere quei maledetti ratti! Ma non preoccuparti, "+GetAddress_FormToNPC(NPChar)+", Acquisterò la quantità mancante e consegnerò l'intero lotto.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Vediamo allora. Dovevi consegnare un carico di "+GetGoodsNameAlt(iFrahtGoods)+" nella quantità di "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+". Corretto?";
			link.l1 = "Assolutamente corretto, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Escort_fail_complete_1";
		break;
	
		case "Escort_fail_complete_1":
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney)/2);
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Mmm... Non solo hai perso le navi che ti erano state affidate, ma sei anche in ritardo di "+FindRussianDaysString(iTime)+". Quindi ho dovuto tagliare il pagamento per il trasporto. Dal momento che non sei stato in grado di salvare le navi, ho dimezzato il pagamento per il trasporto, e questo è il massimo che posso offrirti.\nInoltre, secondo il contratto, la multa è del 10 percento dell'importo originale per ogni giorno di ritardo. Ora, prendi il tuo "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", e via vai.";
				link.l1 = "Bene, è qualcosa almeno.";
				link.l1.go = "Escort_fail_complete_2";
				break;
			}
			dialog.text = "Ebbene, anche se sono estremamente sconvolto dal fatto che non sei riuscito a proteggere le navi che ti erano state affidate, almeno hai consegnato la merce. Poiché non sei stato in grado di salvare le navi, ho ridotto del cinquanta per cento il pagamento per il trasporto, ed è il massimo che posso offrirti. Ora, prendi il tuo pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+" e puoi andare dove ti pare.";
			link.l1 = "Bene, è qualcosa almeno.";
			link.l1.go = "Escort_fail_complete_2";
		break;
	
		case "Escort_fail_complete_2":
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";
				AddQuestRecord("Escort", "17");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			else
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				AddQuestRecord("Escort", "18");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//фейловый рейс не засчитываем
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
//-------------------------------------задания 2 уровня для курьера---------------------------------------------
		case "Postcureer_LevelUp":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);//целевой город
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.6));//дни
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*3000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));//оплата
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			pchar.questTemp.WPU.Postcureer.StartNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}

			switch (rand(3))
			{
				case 0:
					dialog.text = "Dovrai consegnare un dispaccio ufficiale urgente al governatore della città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" non più tardi di "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Fai molta attenzione - i nostri nemici potrebbero essere alla ricerca di quella spedizione. Il pagamento per la consegna - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Sono d'accordo!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "No, credo che passerò.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_Mayor";//ИД губера
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == "Villemstad_Mayor") pchar.questTemp.WPU.Postcureer.TargetPortmanID = "hol_guber"; // фикс Матиаса Бека #717
					pchar.questTemp.WPU.Current.Add = "a dispatch for the governor";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp1";//описание
				break;
			
				case 1:
					dialog.text = "Dovrai consegnare questi documenti al proprietario del negozio di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" non più tardi di "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Questo è l'ultimo riepilogo dei prezzi nei negozi di tutto l'arcipelago - un documento commerciale di valore. Bisogna fare attenzione - i concorrenti potrebbero organizzare una caccia. Pagamento per la consegna - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Sono d'accordo!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "No, credo che passerò.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_trader";//ИД торговца
//					pchar.questTemp.WPU.Current.Add = "сводку цен для хозяина магазина";
					pchar.questTemp.WPU.Current.Add = "a price list for the store owner";     // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp2";//описание
				break;
			
				case 2:
					dialog.text = "Dovrai consegnare questo pacco di documenti all'usuraio nella città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" non più tardi di "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". È un'informazione molto importante sui tassi di cambio e sui prezzi delle azioni. Fai molta attenzione - alcuni personaggi loschi sono già interessati a ricevere questo pacchetto. Pagamento per la consegna - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Sono d'accordo!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "No, credo che passerò.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_usurer";//ИД ростовщика
					pchar.questTemp.WPU.Current.Add = "a packet of information for the moneylender";   // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp3";//описание
				break;
			
				case 3:
					dialog.text = "Dovresti consegnare questo pacco al capo del molo nella città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" non più tardi di "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Contiene i progetti per il nuovo "+RandPhraseSimple(LinkRandPhrase("brigantino","corvetta","фрегат"),LinkRandPhrase("flauto","pinnace","galeone"))+", utilizzando disegni tecnologici unici. Spero che tu capisca che ci sono altre... parti interessate, quindi dovrai agire con discrezione. Il pagamento per la consegna - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Sono d'accordo!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "No, credo che passerò.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_shipyarder";//ИД верфиста
					pchar.questTemp.WPU.Current.Add = "the draft of a new ship for the owner of the shipyard";
					pchar.questTemp.WPU.Current.Item = "ShipyardsMap";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_ShipyardsMap_PortmanLevelUp4";//описание
				break;
			}
		break;
	
		case "Postcureer_LevelUp_Go":
			dialog.text = "Allora prendi i documenti e salpa. Buona fortuna... e che l'Onnipotente ti stia guardando.";
			link.l1 = "Grazie!";
			link.l1.go = "Forsmajor_choose";
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.LevelUp = "true";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) + 1;
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			ChangeItemDescribe(pchar.questTemp.WPU.Current.Item, pchar.questTemp.WPU.Current.Itemdescr);
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "6");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sText", pchar.questTemp.WPU.Current.Add);
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_LevelDown":
			dialog.text = "Peccato, davvero... Di solito, offerte di questo tipo non si rifiutano. Ma la scelta è tua, in ogni caso.";
			link.l1 = "Sì, è il mio richiamo, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 1;//за отказ от спецзадания счетчик скрутим
		break;
	
		case "Forsmajor_choose":
			switch (sti(pchar.questTemp.WPU.Postcureer.Chance))
			{
				case 0://охотники в городе прибытия + ДУ
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.City + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerGopHuntersOnLand";
					TraderHunterOnMap();
				break;
		
				case 1://создание скоростного перехватчика на глобалке
					EnemyNationHunterOnMap(true);
				break;
		
				case 2://запуск ДУ на глобалке и в порту прибытия
					TraderHunterOnMap();
					FrahtHunterOnSea();
				break;
		
				case 3://наёмники в стартовом городе
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerProfHuntersOnLand";
				break;
		
				case 4://агент
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerAgent";
				break;
			}
			DialogExit();
		break;

		case "Postcureer_complete_fail":
			dialog.text = "Maledizione! Quindi ti hanno rintracciato, dopotutto. Peccato che tu non sia un soldato, capitano - in quel caso le cose potrebbero essere andate diversamente... Come sembravano?";
			link.l1 = "Due robusti uomini in nero con semimaschere sui loro volti, armati di picche e fucili a doppia canna...";
			link.l1.go = "Postcureer_complete_fail_1";
		break;

		case "Postcureer_complete_fail_1":
			dialog.text = "Informerò immediatamente il governatore per iniziare a cercarli. Bene, ci vediamo, "+GetAddress_Form(NPChar)+". Di nuovo, è un peccato che tu non sia un soldato...";
			link.l1 = "Mi dispiace davvero, "+GetAddress_FormToNPC(NPChar)+", per quello che è successo. Beh, arrivederci.";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.fail");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
	
//----------------------------------------задания 2 уровня фрахт------------------------------------------

	case "Fraht_LevelUp":
		rColony = GetColonyByIndex(FindColony(npchar.city));
		pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Fraht.Nation = npchar.nation;//нация получателя
		switch (rand(4))//для тестов
		{
			case 0:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_CHOCOLATE + hrand(makeint(GOOD_TOBACCO - GOOD_CHOCOLATE));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 3000 + sti(pchar.rank)*30*(hrand(9)+1);
				iGoodsQty = 1000+sti(pchar.rank)*10*(hrand(9)+1); // min 1100 max 5000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "Una richiesta per una certa merce è recentemente aumentata drasticamente nella nostra colonia. I negozi locali non l'hanno più in stock. Pertanto, vorrei che tu mi fornissi "+GetGoodsNameAlt(iGoods)+" in quantità di "+FindRussianQtyString(iGoodsQty)+", e sono disposto a pagare il doppio - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" per articolo. Questo ammonta a "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, e cerca di rispettare la scadenza di un mese - non potrò aspettare la merce più a lungo.";
				link.l1 = "Bene, accetterò questa missione.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Mi dispiace deluderti, ma non posso farlo in questo momento.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 1:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_EBONY + hrand(makeint(GOOD_CINNAMON - GOOD_EBONY));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 1500 + sti(pchar.rank)*20*(hrand(9)+1);
				iGoodsQty = 600+sti(pchar.rank)*5*(hrand(6)+1); // min 630 max 2000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "La domanda per una certa merce è recentemente aumentata drasticamente nella nostra colonia. I negozi locali non ce l'hanno più in magazzino. Pertanto, vorrei che tu mi fornissi "+GetGoodsNameAlt(iGoods)+" in quantità di "+FindRussianQtyString(iGoodsQty)+", e sono disposto a pagare il doppio - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" per articolo. Questo ammonta a "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, e cerca di rispettare la scadenza di un mese - non potrò aspettare la merce più a lungo.";
				link.l1 = "Bene, accetterò questa missione.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Mi dispiace deluderti, ma non posso farlo in questo momento.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 2:
				//pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS + hrand(makeint(GOOD_POWDER - GOOD_BOMBS));
				pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				iGoodsQty = 5000+sti(pchar.rank)*10*(hrand(9)+1); // min 5100 max 9000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/20);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "L'arsenale della nostra colonia è drasticamente carente "+GetGoodsNameAlt(iGoods)+". I negozi locali non lo hanno più in magazzino. Quindi, vorrei che tu mi fornissi "+GetGoodsNameAlt(iGoods)+" in quantità di "+FindRussianQtyString(iGoodsQty)+", e sono disposto a pagare il triplo - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" per articolo. Questo ammonta a "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, e cerca di rispettare la scadenza di un mese - non potrò aspettare la merce più a lungo.";
				link.l1 = "Bene, accetterò questa missione.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Mi dispiace deluderti, ma non posso farlo in questo momento.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 3:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_MEDICAMENT;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 7000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/30);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "Dopo la recente epidemia di febbre nella nostra colonia, ci mancano le forniture mediche - e non c'è più nulla nei negozi. Il governatore teme per la sicurezza dei cittadini. Quindi, vorrei che tu mi fornissi "+GetGoodsNameAlt(iGoods)+" in quantità di "+FindRussianQtyString(iGoodsQty)+", e sono disposto a pagare il triplo - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" al pacchetto. Questo ammonta a "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, e cerca di rispettare la scadenza di un mese - non potrò aspettare oltre per la merce.";
				link.l1 = "Bene, accetterò questa missione.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Mi dispiace deluderti ma non posso farlo in questo momento.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 4:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_FOOD;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2)/10);//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "Dopo un cattivo raccolto, la nostra colonia ha costantemente bisogno di cibo importato. Al momento le nostre scorte sono quasi vuote, e tutto è stato spazzato via dagli scaffali dei negozi già da un po' di tempo. Vorrei chiederti di consegnarmi "+GetGoodsNameAlt(iGoods)+" in quantità di "+FindRussianQtyString(iGoodsQty)+", e sono disposto a pagare il doppio - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" per pacchetto. Questo ammonta a "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, e cerca di rispettare la scadenza di un mese - non sarò in grado di aspettare la merce più a lungo.";
				link.l1 = "Bene, accetterò questa missione.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Mi dispiace deluderti, ma non posso farlo in questo momento.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		}
	break;
		
	case "Fraht_LevelDown":
		DialogExit();
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//скрутим счетчик
	break;
		
	case "Fraht_LevelUp_Go":
		dialog.text = "Eccellente! Sono molto contento che tu abbia accettato. Spero di rivederti presto.";
		link.l1 = "Certo, "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Fraht = "begin";
		pchar.questTemp.WPU.Fraht.LevelUp = "true";
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count) + 1;
		pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.StartCity +"_portman";//ИД портмана
		iGoods = pchar.questTemp.WPU.Fraht.Goods;
		ReOpenQuestHeader("Fraht");
		AddQuestRecord("Fraht", "8");
		AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
		AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
		AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iGoods));
		AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty)));
		AddQuestUserData("Fraht", "sText", pchar.questTemp.WPU.Current1.Add);
		SetFunctionTimerCondition("FrahtTimeLevelUp_Over", 0, 0, 30, false);
	break;
	
	case "Fraht_completeLevelUp":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		iGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
		amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
		if (amount > 0)
		{
			dialog.text = "Stai scherzando? Non hai la quantità di merci che ho ordinato!";
			link.l1 = "Mi dispiace, è colpa mia...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Bene, dovevi consegnare un carico di "+GetGoodsNameAlt(iGoods)+" in quantità di "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Eccellente, grazie mille. Ecco il tuo pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Un piacere fare affari con te, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "Fraht_completeLevelUp_1";
		}
	}
	else
	{
		dialog.text = "Non vedo la tua nave nel porto. Allontanati e poi vieni a vedermi di nuovo - allora parleremo.";
		link.l1 = "Bene, farò proprio così.";
		link.l1.go = "exit";
	}
	break;
	
	case "Fraht_completeLevelUp_1":
		pchar.quest.FrahtTimeLevelUp_Over.over = "yes";//снять таймер
		AddQuestRecord("Fraht", "2");
		CloseQuestHeader("Fraht");
		RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current1"); // лесник  Current1 вместо Current
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.LevelUp");
		pchar.questTemp.WPU.Fraht = "complete";
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
		DialogExit();
	break;
	
//----------------------------------------задания 2 уровня эскорт ------------------------------------------

	case "Escort_LevelUp":
		pchar.questTemp.WPU.Escort.LevelUp = "true";//установим атрибут
		pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Escort.Nation = npchar.nation;//нация квестодателя
		pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
		i = 0;
		while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
		{
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
			i++;
			if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
		}
		switch (hrand(2))
		{
			case 0://приключения на необитаемых островах
				pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();//выбор необитайки
				while (!isLocationFreeForQuests(pchar.questTemp.WPU.Current.TargetIslandID)) pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();//выбор корабля
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));//имя корабля
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				pchar.questTemp.WPU.Escort.ShipBaseName = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.WPU.Escort.ShipType), "Name") + "Gen"));
				dialog.text = "Questa calamità è accaduta dieci giorni fa... un convoglio di navi mercantili dirette verso la nostra colonia è stato attaccato dai pirati. Una forte tempesta ha costretto i pirati a ritirarsi, ma le navi mercantili si sono disperse e hanno perso di vista l'una l'altra. Alla fine tutte le navi sono arrivate in porti diversi, eccetto una. \n"+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' è scomparsa e il suo destino rimane sconosciuto. Presumibilmente può essere trovata vicino all'isola disabitata di "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Ti chiedo di andare là, scoprire cosa è successo alla nave perduta e, se è sopravvissuta, portarla al nostro porto. Decideremo la tua ricompensa dopo che il lavoro è fatto ma ti assicuro che ne varrà la pena.";
				link.l1 = "Certo, sono d'accordo!";
				link.l1.go = "Escort_LevelUp_1";
				link.l2 = "Mi dispiace, ma questo lavoro non è adatto a me. Temo che dovrò passare.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 1://защитить конвой вблизи текущего острова от пиратов
				pchar.questTemp.WPU.Current.TargetIslandID = Islands[GetCharacterCurrentIsland(PChar)].id;//текущий остров
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				dialog.text = "Una carovana commerciale doveva arrivare alla nostra colonia, ma proprio prima di entrare in porto è stata attaccata dai pirati. La battaglia sta avvenendo proprio mentre parliamo. È fuori dalla portata dei cannoni del forte e al momento non ho nessuna nave di scorta disponibile, quindi non posso fornire alcun aiuto ai poveri mercanti. Sei un capitano galante, quindi ti chiedo di intervenire e aiutare i mercanti a respingere l'attacco! Lo farai?";
				link.l1 = "Certo! È questione d'onore!";
				link.l1.go = "Escort_LevelUp_2";
				link.l2 = "Mi dispiace ma questo lavoro non fa per me. Temo che dovrò rinunciare.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 2://встретить и довести
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();
				pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//город, откуда забрать
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
				sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
				pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
				pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(npchar);//ИД целевого ареала
				pchar.questTemp.WPU.Escort.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));//расстояние в днях
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.DaysQty)*2000+20000;
				pchar.questTemp.WPU.Escort.Chance = rand(1);
				dialog.text = "Una nave con armi e munizioni che la nostra colonia ha ordinato è recentemente arrivata alla colonia "+XI_ConvertString(pchar.questTemp.WPU.Escort.City)+". La sua nave scorta ha colpito la barriera corallina, è stata gravemente danneggiata e non sarà in grado di lasciare il porto a breve. Non possiamo rischiare di mandare una nave mercantile con un carico del genere da sola.\nAccetteresti di scortarla nella nostra colonia? Il pagamento per il lavoro è fissato a "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
				link.l1 = "Certo, sono d'accordo!";
				link.l1.go = "Escort_LevelUp_0";
				link.l2 = "Mi dispiace ma questo lavoro non è adatto per me. Temo che dovrò passare.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
		}
	break;
	
	case "Escort_LevelUp_exit":
		dialog.text = "Un peccato, davvero. Contavo proprio su di te...";
		link.l1 = "Mi dispiace anche a me. Bene, fino al nostro prossimo incontro, "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	break;
	
	case "Escort_LevelUp_0":
		dialog.text = "Eccellente! Sapevo di poter contare su di te. Per favore, cerca di essere il più veloce possibile. Penso "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+" sarà sufficiente per arrivare a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gen")+". Ecco, prendi queste credenziali che confermeranno la tua identità. Vento in poppa, capitano!";
		link.l1 = "Non preoccuparti, non ti deluderò.";
		link.l1.go = "Escort_LevelUp_0_go";
	break;
	
	case "Escort_LevelUp_0_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "19");
		AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty));
		SetFunctionTimerCondition("EscortArsenalShip_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+1, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.LevelUp_0 = "true";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LUGo_0":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.EscortArsenalShip_Over.over = "yes";
		dialog.text = "Finalmente! Quella nave è stata un occhio di rospo abbastanza a lungo. Prendi il comando, allora. Il nome della nave è "+pchar.questTemp.WPU.Escort.ShipName+", e il suo capitano sarà immediatamente informato del tuo arrivo.";
		link.l1 = "Digli di preparare la sua nave a salpare - partirò alla prima occasione.";
		link.l1.go = "Escort_LUGo_01";
	}
	else
	{
		dialog.text = "Non vedo la tua nave nel porto. Tieniti lontano per ora e vieni a cercarmi più tardi - allora parleremo.";
		link.l1 = "Farò proprio così.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_01"://добавляем компаньона
		int iShipType = sti(pchar.questTemp.WPU.Escort.ShipType);
		sTemp = pchar.questTemp.WPU.Escort.ShipName;
		sld = GetCharacter(NPC_GenerateCharacter("ArsenalShipCaptain", "citiz_41", "man", "man", 15, sti(pchar.nation), -1, true, "quest"));
		FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 65, 22, 24, 35, 33);
		SetFantomParamFromRank(sld, 15, true); 
		SetCaptanModelByEncType(sld, "war");
		SetCharacterGoods(sld, GOOD_FOOD, 500);
		SetCharacterGoods(sld, GOOD_BALLS, 5000);
		SetCharacterGoods(sld, GOOD_GRAPES, 3000);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 3000);
		SetCharacterGoods(sld, GOOD_BOMBS, 5000);
		SetCharacterGoods(sld, GOOD_POWDER, 10000);
		SetCharacterGoods(sld, GOOD_WEAPON, 3000);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		SetCharacterRemovable(sld, false);
		sld.loyality = MAX_LOYALITY;
		sld.Dialog.Filename = "Common_portman.c";
		sld.dialog.currentnode = "Escort_companion";
		DialogExit();
		AddQuestRecord("Escort", "20");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
		pchar.quest.Escort_fail.win_condition.l1.character = "ArsenalShipCaptain";
		pchar.quest.Escort_fail.function = "EscortArsenalShip_failed";
		SetFunctionTimerCondition("EscortArsenalShipGo_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+6, false);
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0");
		pchar.questTemp.WPU.Escort.LevelUpGo_0 = "true";
		if (sti(pchar.questTemp.WPU.Escort.Chance) == 0) EnemyNationHunterOnMap(true);//скоростной перехватчик
		else FrahtHunterOnSea();
	break;
	
	case "Escort_LUGo_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.Escort_fail.over = "yes";
		pchar.quest.EscortArsenalShipGo_Over.over = "yes";
		dialog.text = "Eccellente! Ancora una volta, hai dimostrato di essere affidabile. Grazie per l'ottimo lavoro. Per favore, accetta il tuo pagamento - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+". E non dimenticare di venire a trovarmi di tanto in tanto - c'è sempre un lavoro o due per un capitano come te.";
		link.l1 = "È bello sentirlo, "+GetAddress_FormToNPC(NPChar)+"! Certamente, la nostra collaborazione continuerà. I miei migliori saluti!";
		link.l1.go = "Escort_LUGo_complete_1";
	}
	else
	{
		dialog.text = "Non vedo la tua nave in porto. Stai lontano per ora e vieni a trovarmi più tardi - allora parleremo.";
		link.l1 = "Bene, farò proprio così.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_complete_1":
		RemoveCharacterCompanion(Pchar, characterFromID("ArsenalShipCaptain"));
		sld = characterFromId("ArsenalShipCaptain");
		sld.lifeday = 0;//на всякий случай
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
		AddQuestRecord("Escort", "24");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		CloseQuestHeader("Escort");
		DialogExit();
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 100, 100, 0, 100, 0, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_1":
		dialog.text = "Allora ti auguro un viaggio sicuro. E per favore, non ritardare con la tua ricerca! L'equipaggio di quella nave potrebbe aver bisogno di aiuto immediato.";
		link.l1 = "Capito. Sto per mettermi in mare oggi!";
		link.l1.go = "Escort_LevelUp_1_select";
	break;
	
	case "Escort_LevelUp_1_select"://выберем приключение
		switch (rand(2))
		{
			case 0://весь побитый и остался без мачты
				pchar.quest.DisasterShip_WM.win_condition.l1 = "location";
				pchar.quest.DisasterShip_WM.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_WM.function = "CreateDisasterShip_WithoutMasts";
				pchar.questTemp.WPU.Escort.LevelUp_1WM = "true";
			break;
			case 1://ведет бой с пиратусами в шторме
				pchar.quest.DisasterShip_VSP.win_condition.l1 = "location";
				pchar.quest.DisasterShip_VSP.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_VSP.function = "CreateDisasterShip_VSPirate";
				for (i=0; i<MAX_ISLANDS; i++)//устроим шторм
				{				
					if (Islands[i].id == pchar.questTemp.WPU.Current.TargetIslandID)
					{
					Islands[i].alwaysStorm = true; 
					Islands[i].storm = true;
					Islands[i].tornado = true; 
					}
				}
				pchar.questTemp.WPU.Escort.LevelUp_1VSP = "true";
			break;
			case 2://потонул
				pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
				pchar.quest.DisasterShip_S.win_condition.l1 = "location";
				pchar.quest.DisasterShip_S.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
				pchar.quest.DisasterShip_S.function = "CreateDisasterShip_Crew";
				pchar.questTemp.WPU.Escort.LevelUp_1S = "true";
			break;
		}
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "25");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		SetFunctionTimerCondition("DesIsland_Over", 0, 0, 15, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LU1WM_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Sì, sono già stato informato. Ottimo lavoro, "+GetAddress_Form(NPChar)+"! Hai dimostrato ancora una volta che sei quello su cui posso contare. Prendi la tua ricompensa - 30.000 pesos.\nRicorda di venire a trovarmi di tanto in tanto - persone come te sono inestimabili e troverò sempre un lavoro adatto a te.";
		link.l1 = "Contento di sentirlo, "+GetAddress_FormToNPC(NPChar)+"! Certamente, continueremo a cooperare. Tutto il meglio!";
		link.l1.go = "Escort_LU1WM_complete_1";
	}
	else
	{
		dialog.text = "Non vedo la tua nave in porto. Stai alla larga per ora e vieni a cercarmi più tardi - allora parleremo.";
		link.l1 = "Bene, farò proprio così.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1WM_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 30000);
		ChangeCharacterComplexReputation(pchar,"nobility", 5);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 5);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 30000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Repair", 300);//починка
		AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Sì, mi ha già raccontato della battaglia con i pirati e di come hai difeso eroicamente la sua nave. Ottimo lavoro, "+GetAddress_Form(NPChar)+"! Hai dimostrato ancora una volta di essere qualcuno di cui posso fidarmi. Prendi la tua ricompensa - 50.000 pesos.\nRicordati di venire a trovarmi di tanto in tanto - persone come te sono inestimabili e troverò sempre un lavoro adatto a te.";
		link.l1 = "Un piacere sentire questo, "+GetAddress_FormToNPC(NPChar)+"! Certamente, la nostra collaborazione continuerà. I miei migliori saluti!";
		link.l1.go = "Escort_LU1VSP_complete_1";
	}
	else
	{
		dialog.text = "Non vedo la tua nave nel porto. Stai alla larga per ora e vieni a trovarmi di nuovo più tardi, allora parleremo.";
		link.l1 = "Bene, farò proprio così.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1VSP_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 50000);
		ChangeCharacterComplexReputation(pchar,"nobility", 10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 6);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 50000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_completeSink":
		dialog.text = "Che fine tragica... Dio abbia pietà delle loro anime.";
		link.l1 = "Ho fatto tutto quello che potevo, "+GetAddress_FormToNPC(NPChar)+". La tempesta ha peggiorato ulteriormente la situazione.";
		link.l1.go = "Escort_LU1VSP_completeSink_1";
	break;
	
	case "Escort_LU1VSP_completeSink_1":
		dialog.text = "Credo proprio, "+GetAddress_Form(NPChar)+", che hai fatto tutto il possibile per salvare la nave e quei marinai sfortunati. Ma ahimè... Beh, per favore prendi la tua ricompensa - 10000 pesos - e grazie per il tuo servizio.";
		link.l1 = "Non c'è nulla per cui ringraziarmi, "+GetAddress_FormToNPC(NPChar)+". Mi dispiace davvero. Bene, arrivederci.";
		link.l1.go = "Escort_LU1VSP_completeSink_2";
	break;
	
	case "Escort_LU1VSP_completeSink_2":
		DialogExit();
		AddMoneyToCharacter(pchar, 10000);
		ChangeCharacterComplexReputation(pchar,"nobility", 1);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 10000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(50, 50, 50, 50, 0, 0, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1S_complete":
		dialog.text = "Sì, mi ha già parlato di te che combatti i pagani dalla pelle rossa e poi una nave pirata - come un vero eroe. Ottimo lavoro, "+GetAddress_Form(NPChar)+"! Hai dimostrato ancora una volta di essere quello su cui posso contare.\nPrendi la tua ricompensa - 40.000 pesos. Ricordati di venire a trovarmi di tanto in tanto - persone come te sono inestimabili e troverò sempre un lavoro adatto per te.";
		link.l1 = "Contento di sentire questo, "+GetAddress_FormToNPC(NPChar)+"! Certo, la nostra collaborazione continuerà. I miei migliori saluti!";
		link.l1.go = "Escort_LU1S_complete_1";
	break;
	
	case "Escort_LU1S_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 40000);
		ChangeCharacterComplexReputation(pchar,"nobility", 8);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 3);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 40000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_2":
		dialog.text = "Sapevo di poter contare su di te. Buona fortuna a te, capitano! L'intera colonia ti augura la vittoria!";
		link.l1 = "Cercherò di essere all'altezza delle vostre aspettative. Sto per salpare, e che Dio ci aiuti!";
		link.l1.go = "Escort_LevelUp_2_go";
	break;
	
	case "Escort_LevelUp_2_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "41");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		SetFunctionTimerCondition("CaravanNearIsland_Over", 0, 0, 2, false);
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
		pchar.quest.CaravanNearIsland_Start.win_condition.l1 = "location";
		pchar.quest.CaravanNearIsland_Start.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
		pchar.quest.CaravanNearIsland_Start.function = "CreateCaravanNearIsland";
		pchar.questTemp.WPU.Escort.LevelUp_2 = "true";
		pchar.questTemp.WPU.Escort = "begin";
		DialogExit();
	break;
	
	case "Escort_LU2_complete":
		switch (sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty))
		{
			case 1:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 10000;
				dialog.text = "Sì, l'intera città stava guardando la tua battaglia. Poveri mercanti, mi dispiace davvero per loro. Beh, almeno sei riuscito a salvare una nave, quindi la tua ricompensa di 10000 pesos è ben meritata. Per favore, accettala - e grazie per il tuo aiuto.";
				link.l1 = "Non c'è bisogno di ringraziarmi... È sfortunato che non abbia vinto quella battaglia in modo decisivo, ma ho fatto tutto quello che potevo. Addio, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 2:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 25000;
				dialog.text = "Sì, tutta la città ha assistito alla battaglia che hai combattuto - e devo dire che l'hai fatto molto abilmente. Quel povero mercante, mi dispiace tanto per lui... Ma se non fosse stato per te, nessuno di loro sarebbe scappato vivo, quindi la tua ricompensa di 25000 pesos è più che meritata. Ti prego di accettarla - e grazie per il tuo aiuto.";
				link.l1 = "Ebbene, grazie per l'apprezzamento lusinghiero delle mie azioni, ma non penso che quella fosse la mia migliore battaglia - ho comunque perso una nave. Ebbene, il destino è destino, e non c'è niente da fare al riguardo. Addio, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 3:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 50000;
				dialog.text = "Sì, l'intera cittadina ha assistito alla battaglia che hai condotto - sei stato assolutamente magnifico! Hai appena distrutto l'intero squadrone di quei luridi pirati! Ora hanno imparato la loro lezione - peccato che non gli servirà più. La tua ricompensa ammonta a 50000 pesos - per favore, accettala.";
				link.l1 = "Grazie per l'apprezzamento dei miei atti! È sempre un piacere aiutare. E ora, "+GetAddress_FormToNPC(NPChar)+", per favore, permettetemi di prendere il mio congedo.";
				link.l1.go = "Escort_LU2_complete_1";
			break;
		}
	break;
	
	case "Escort_LU2_complete_1":
		iTemp = sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty);
		DialogExit();
		Group_DeleteGroup("CaravanShip");
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", iTemp*2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), iTemp);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		CloseQuestHeader("Escort");
		AddCharacterExpToSkill(pchar, "Sailing", iTemp*35);//навигация
		AddCharacterExpToSkill(pchar, "Accuracy", iTemp*50);//меткость
		AddCharacterExpToSkill(pchar, "Cannons", iTemp*50);//орудия
		AddCharacterExpToSkill(pchar, "Grappling", iTemp*35);//абордаж
		AddCharacterExpToSkill(pchar, "Leadership", iTemp*40);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", iTemp*35);//везение
		AddCharacterExpToSkill(pchar, "FencingL", iTemp*35);//лёгкое оружие
		AddCharacterExpToSkill(pchar, "FencingS", iTemp*35);//среднее оружие
		AddCharacterExpToSkill(pchar, "FencingH", iTemp*35);//тяжелое оружие
		AddCharacterExpToSkill(pchar, "Pistol", iTemp*35); //пистоли
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
		case "PortmanQuest_NF":
			dialog.text = "Mmm, è un brutto affare. In tal caso, è fuori discussione che tu continui a lavorare per me.";
			link.l1 = "Capito. Ecco quello che volevo dire...";
			link.l1.go = "node_2";
		break;
		
		//сгоревшее судно
		case "BurntShip2":
			dialog.text = "Un peccato, capitano... È un peccato che non sei disposto ad aiutarmi.";
			link.l1 = "Non è una questione di volontà, buon uomo. Devi capire. Addio.";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		case "BurntShip4":
			dialog.text = "Cosa succede a te, capitano?! Non ti vergogni?! Come hai potuto?! So le mie cose, sono in servizio da molti anni. Ci sono contratti di assicurazione, e la compagnia di assicurazione è disposta a pagare, e ti assicuro che la somma assicurata è piuttosto decente.";
			link.l1 = "Qual è il tuo problema, signore? Un deposito di polvere da sparo è esploso, ci sono state vittime, e ora devi rispondere del tuo negligenza?";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "No! Certamente no! Dio salvi la mia anima, altrimenti perderei la mia testa. La stiva era assolutamente vuota, grazie a Dio, la Beata Vergine Maria!\n"+"E il problema è che la nave appartiene a... o meglio, apparteneva al Signor. "+sCapitainId+", ben nota a tutti i Caraibi. E fu costruita in Europa su ordinazione speciale, con caratteristiche straordinarie. "+"E questo armatore era troppo orgoglioso e si vantava a destra e a manca, una sorta di testa di legno, Dio mi perdoni... Cosa gli dirò adesso? Sarebbe meglio che mi uccidessi, lo giuro...";
			link.l1 = "Oh, ora vedo qual è il problema, davvero. E cosa c'era di così speciale nella nave? Quali caratteristiche insolite aveva che il suo proprietario ne era così orgoglioso?";
			link.l1.go = "BurntShip6";
			
			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;
		
		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s wind speed was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " knots. That was the privateer's pride... And now he'd just tell his boys to hang me in the yard. What devil has brought him to our harbor together with that pirate tub...";
				break;
				
				case "turnrate":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s maneuverability was more than " + NPChar.Quest.BurntShip.ShipNeededValue + " units. That was the soldier's pride... And now he'd just have me flogged to death. What devil advised him to leave his tub there...";
				break;
				
				case "capacity":
					attrL = "His " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "' had a deadweight of over " + NPChar.Quest.BurntShip.ShipNeededValue + " units. Greed is bad, I'll tell ya. And now he'd just have me quartered in court. What devil advised him to leave his tub there...";
				break;
			}
			
			dialog.text = attrL;
			link.l1 = "E cosa dicono le persone al molo? È davvero impossibile costruirne un altro qui?";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "Nessuno può. Sono persino andato sull'isola vicina per chiedere alla gente. Hanno detto che c'è un maestro notevole su Isla Tesoro che è in grado di realizzare quasi tutto nella costruzione navale. Ma Isla Tesoro è così maledettamente lontana. Tutto ciò che mi rimane è contare sull'aiuto di capitani liberi come te. Forse riuscirai a trovare una nave del genere per me. E io me ne occuperò del resto\n"+"Ti ringrazierò generosamente, e lo farà anche la compagnia di assicurazione. Il caso è insolito, sai. Chi mai vorrebbe sconvolgere un uomo così potente?";
			link.l1 = "Sì, non sarà facile. E quanto tempo ho?";
			link.l1.go = "BurntShip8";
			link.l2 = "No, amico, non posso essere coinvolto in un affare del genere. Per non parlare del fatto che non ci sono garanzie che una nave con tali parametri esista affatto. Mi dispiace...";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "Grazie a Dio, c'è ancora tempo. Il proprietario è salpato per l'Europa e non tornerà prima di mezzo anno.";
			link.l1 = "Bene, credo che potrò farcela. Ti porterò una nave simile. Ma ricorda - se decidi di essere troppo avaro, la brucerò proprio davanti ai tuoi occhi!";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "Cosa stai insinuando, capitano? Certamente, capisco che hai bisogno di tempo - non si tratta di trovare una vasca a caso nella pozzanghera più vicina... Portaci solo il vascello e faremo del nostro meglio, puoi contarci su quello...";
			link.l1 = "Spero di sì... Beh, aspettami e spera nelle buone notizie. Addio.";
			link.l1.go = "BurntShip9_exit";
		break;
		
		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 6, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "speed. The wind speed of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be at least " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "turnrate":
					attrL = "manoeuvrability. Manoeuvrability of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " must be no less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "capacity":
					attrL = "hold. Hold of the " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " has to be no less than " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}
			
			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Dat"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);
			
			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // Запомнм имя
			
			DialogExit();
		break;
		
		// Вариант, когда не уложились в сроки
		case "BurntShip10":
			dialog.text = "Di cosa volevi parlare?";
			link.l1 = "E dove si trova l'ex capo del porto, signor "+NPChar.Quest.BurntShip.LastPortmanName+"? Ho affari con lui.";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "Non è più tra noi. Immagina - ha dato fuoco a una nave di una persona ben conosciuta e ha intascato i soldi dell'assicurazione. Mentre le autorità stavano risolvendo tutto questo, ha rassegnato le dimissioni e si è dileguato in Europa. Un vero truffatore, non è vero?";
			link.l1 = "Sì, ho sentito quella storia. Mi dispiace, ma devo andare.";
			link.l1.go = "BurntShip11_exit";
		break;
		
		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		// Не просрочено - проверяем корабль
		case "BurntShip12":
			dialog.text = "Di cosa volevi parlare?";
			link.l1 = "Ho portato una nave insolita per te, proprio come hai chiesto. Ora mi aspetto la mia ricompensa.";
			link.l1.go = "BurntShip14";
			link.l2 = "Sai, "+GetFullName(NPChar)+", Non ho ancora trovato una sola nave simile a quella di cui hai bisogno. Credo che abbandonerò questo lavoro. Mi dispiace se ti ho deluso...";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "Un peccato, capitano... È un peccato che non sei disposto ad aiutarmi.";
			link.l1 = "Non è una questione di volontà, mio buon uomo. Per favore, capisci. Addio.";
			link.l1.go = "BurntShip13_exit";
		break;
		
		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip14":
			dialog.text = "Oh, davvero! E qual è il nome della nostra nuova nave?";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}
			
			link.l99 = "Scusami, tornerò più tardi.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Oh, capitano, sono così felice che non mi hai deluso! Che "+GetSexPhrase("bravo giovane uomo","bella giovane signora")+"sei tu, hai letteralmente salvato la mia vita... Per favore, potresti venire a ritirare i tuoi soldi tra un paio di giorni? Sai, devo sistemare le formalità con l'assicurazione... Nel frattempo, potresti fare delle piccole riparazioni alla nave - sai, rinnovare le vele, rattoppare i buchi, non farebbe male nemmeno un carenaggio...";
			link.l99 = "Promisi che avrei fatto qualcosa di brutto alla nave se avessi provato a ingannarmi. Hai dimenticato?";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "No, no, certo che no! Rimarrò fedele alla mia parola, non preoccuparti. Vedi, sapendo che ci saranno più spese per, per così dire, travestire la nuova nave, ho prestato i soldi dell'assicurazione che ho ottenuto per la vecchia nave con interessi. Spero tu capisca...";
			link.l1 = "Lo capirò molto meglio quando il denaro arriverà al mio petto. Fino a quando ci incontriamo di nuovo.";
			link.l1.go = "BurntShip16_exit";
		break;
		
		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");
			
			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // Запомним дату
			
			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время
			
			DialogExit();
		break;
		
		case "BurntShip17":
			dialog.text = "Di cosa volevi parlare?";
			link.l1 = "Sono venuto a ritirare la mia ricompensa. Ho ancora il vascello di cui hai bisogno.";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "Potresti per favore ricordarmi il suo nome? La mia memoria non è più come una volta - sai, tutte quelle seccature...";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}
			
			link.l99 = "Scusami, tornerò più tardi.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 3;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "Sì, perfetto. Sono pronto a consegnarti la tua ricompensa, "+FindRussianMoneyString(cn)+". Questo è come la compagnia assicurativa ha valutato il valore della nave bruciata. L'indennizzo viene pagato in casse di credito - niente contanti, mi dispiace.";
			link.l1 = "Oh no, questa somma non mi va bene. Sono sicuro che questa nave valga molto di più.";
			link.l1.go = "BurntShip21";
			link.l2 = "Proprio così. Sono contento di poterti aiutare. Ci vediamo.";
			link.l2.go = "BurntShip20_exit";
			NPChar.Quest.BurntShip.Money = cn;
		break;
		
		case "BurntShip20_exit":
			TakeNItems(pchar, "chest", makeint(sti(NPChar.Quest.BurntShip.Money)/12000));
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip21":
			dialog.text = "Cosa stai dicendo, capitano?! Fidati di me, so di cosa sto parlando. Quei soldi ti comprerebbero due navi come quella!";
			link.l1 = "Penso che lo terrò. Sai, mi è proprio piaciuto... Addio.";
			link.l1.go = "BurntShip21_exit";
		break;
		
		case "BurntShip21_exit":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		//--> миниквесты портмана
		case "PortmanQuest":
			if (hRand(5) == 2)
			{	//квест догнать и передать судовой журнал
				dialog.text = "Uno dei capitani ha dimenticato il suo registro nel mio ufficio. Che testa di vento! Ho bisogno che tu lo raggiunga e glielo restituisca.";
				link.l1 = "Oh, sarà facile... Lo prenderò!";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "No, non me ne occuperò. È un suo problema, in realtà.";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "Una nave è stata rubata dal suo ormeggio. Voglio che tu cerchi la nave rubata e la riporti indietro.";
				link.l1 = "Mah, bene, sono pronto a intraprendere l'indagine.";
				link.l1.go = "SeekShip_1";
				link.l2 = "Mi dispiace ma non mi occupo della ricerca di navi rubate.";
				link.l2.go = "node_2";
			}
		break;
//-------------------------------- квест доставки судового журнала до рассеяного кэпа ---------------------
		case "PortmanQuest_1":
			dialog.text = "Eccellente, ecco il suo registro di bordo... Hai davvero tolto un peso dalla mia mente! La perdita di un registro di bordo di una nave è una cosa molto brutta. Ho sempre provato pena per quei capitani...";
			link.l1 = "Bene, questo è davvero qualcosa di cui preoccuparsi! Ora, raccontami di più su quel capitano distratto.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "Sì, certo! Il suo nome è "+npchar.quest.PortmansJornal.capName+", è un capitano di "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName+"Gen"))+" chiamato '"+npchar.quest.PortmansJornal.shipName+"'. Ha salpato non molto tempo fa e si è diretto a "+XI_ConvertString("Colony"+npchar.quest.PortmansJornal.city+"Acc")+".";
			link.l1 = "Capisco. Va bene, lo troverò. Ora, riguardo al pagamento?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName+" lui stesso ti pagherà, è nel suo interesse. Ti basta concentrarti a raggiungerlo il più presto possibile e tutto andrà bene.";
			link.l1 = "Capisco. Bene, allora andrò...";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", which is on " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}			
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = "Eccellente! Sai, la nave rubata appartiene a una persona influente, quindi questo è molto importante per me. Ti pagherò generosamente per questo lavoro...";
			link.l1 = "Capisco. Dimmi di più sulla nave e le circostanze in cui è stata rubata.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)+" con il nome di '"+npchar.quest.PortmansSeekShip.shipName+"' è stato rubato di notte "+FindRussianDaysString(rand(5)+10)+" fa. Il guardiano è stato ucciso.";
			link.l1 = "Hmm... Devono essere andati lontano ormai. La pista non è più fresca ed è questo il problema.";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "È vero, ma non vedevo ancora il motivo di suonare l'allarme subito. La nave militare avrebbe potuto raggiungerli, ma avrebbe solo fatto a pezzi la nave - e non è esattamente quello di cui ho bisogno.";
			link.l1 = "Capisco. Bene, inizierò la mia ricerca. Spero di avere fortuna.";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;

		case "SeekShip_break":
			dialog.text = "Un peccato - ma difficilmente potevamo contare sul successo.";
			link.l1 = "Sì, è passato troppo tempo da quando la nave è stata rubata.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "Bene, grazie per il tuo aiuto in ogni caso, anche se i tuoi sforzi non sono stati fruttuosi come speravamo.";
			link.l1 = "Ho fatto tutto quello che potevo...";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор еще жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0; 
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterComplexReputation(pchar,"nobility", -7);
		break;	

		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "Eccellente! Anche se sospetto che questa non sia esattamente la nave che è stata rubata... Oh, chi se ne importa! La prendo.";
				link.l1 = "Sì, infatti...";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterComplexReputation(pchar,"nobility", 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
                AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "Eccellente! Mi hai aiutato molto. Non riesco a immaginare quanto sia stato difficile.";
				link.l1 = "Sì, infatti...";
				ChangeCharacterComplexReputation(pchar,"nobility", 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "Sono pronto a pagarti la tua ricompensa. Consiste in "+FindRussianMoneyString(makeint(sti(npchar.quest.chest)*15000))+" nei bauli. Purtroppo, non posso pagarti di più di così.";
			link.l1 = "Bene, è sufficiente. Grazie e cordiali saluti.";
			link.l1.go = "exit";
			TakeNItems(pchar, "chest", sti(npchar.quest.chest));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = "Ci sono diversi capitani registrati. Sei interessato a qualcuno in particolare?";
				makearef(arCapBase, npchar.quest.capitainsList); 
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
    				arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", captain of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Gen")) + " '" + sld.Ship.name + "'.";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "Non ho nessun capitano nella mia lista che potrebbe interessarti.";
				link.l1 = "Capisco. Beh, grazie per l'informazione.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Bene, vediamo... A-ha! Eccolo! ","Ah-ha... A-ha! Ecco! ","Bene, allora. ")+"Capitano "+GetFullName(sld)+" "+arCapLocal.date+" anno ha lasciato il nostro porto e ha navigato verso "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Grazie. Mi piacerebbe rivedere l'elenco ancora...";
			link.l1.go = "CapitainList";
			link.l2 = "Bene, è tutto. Non sono interessato a nessun altro capitano.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Bene, vediamo... Ah-ah! Ecco! ","Ah-ha... A-ha! Eccolo lì! ","Bene, allora. ")+"Capitano "+GetFullName(sld)+" "+arCapLocal.date+" anno ha lasciato il nostro porto e ha navigato verso "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Grazie. Vorrei rivedere la lista di nuovo...";
			link.l1.go = "CapitainList";
			link.l2 = "Bene, è tutto. Non mi interessa nessun altro capitano.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Bene, vediamo... A-ha! Eccolo lì! ","Ah-ha... A-ha! Ecco! ","Bene, allora. ")+"Capitano "+GetFullName(sld)+" "+arCapLocal.date+" anno ha lasciato il nostro porto e ha navigato verso "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Grazie. Mi piacerebbe rivedere l'elenco di nuovo...";
			link.l1.go = "CapitainList";
			link.l2 = "Bene, è tutto. Non mi interessa nessun altro capitano.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Bene, vediamo... A-ha! Eccolo! ","Ah-ha... A-ha! Ecco! ","Bene, allora. ")+"Capitano "+GetFullName(sld)+" "+arCapLocal.date+" anno ha lasciato il nostro porto e ha navigato verso "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Grazie. Vorrei rivedere l'elenco ancora una volta...";
			link.l1.go = "CapitainList";
			link.l2 = "Bene, è tutto. Non sono interessato a nessun altro capitano.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Bene, vediamo... Ah-ah! Ecco! ","Ah-ha... A-ha! Eccolo!","Bene, allora. ")+"Capitano "+GetFullName(sld)+" "+arCapLocal.date+" anno ha lasciato il nostro porto e ha navigato verso "+XI_ConvertString("Colony"+arCapLocal+"Acc")+".";
			link.l1 = "Grazie. Vorrei rivedere la lista ancora...";
			link.l1.go = "CapitainList";
			link.l2 = "Bene, è tutto. Non mi interessa nessun altro capitano.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " that is in " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobTakeShip" && !CheckAttribute(npchar, "quest.HWICHoll"))
			{
			dialog.text = "Sto ascoltando - quale nave, per quale termine?";
    		Link.l1 = "Lucas Rodenburg mi ha mandato. Ha detto che posso ormeggiare la mia nave qui gratuitamente.";
    		Link.l1.go = "ShipStock_HWICHoll";
			DelLandQuestMark(npchar);
			break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoPortoffice" && !CheckAttribute(npchar, "quest.HWICEng"))
			{
			dialog.text = "Sto ascoltando - quale nave, per quanto tempo?";
    		Link.l1 = "Richard Fleetwood mi ha mandato. Ha detto che posso ormeggiare la mia nave ammiraglia qui per 10000 pesos.";
    		Link.l1.go = "ShipStock_HWICEng";
			break;
			}
            if (sti(NPChar.Portman) >= 3 || CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip"))
			{
                dialog.text = "Ebbene, è corretto. Ma purtroppo, non posso accettare la tua nave al momento. Non c'è spazio al molo disponibile.";
    			Link.l1 = "Che peccato.";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "E quale nave in particolare hai intenzione di lasciare qui?";
	    			for(i=1; i<COMPANION_MAX; i++)
					{
						cn = GetCompanionIndex(PChar, i);
						if(cn > 0)
						{ // hasert со сторожем.
							chref = GetCharacter(cn);
							if (!GetRemovable(chref)) continue;							
							attrL = "l"+i+COMPANION_MAX;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockMan22_" + i;

						}
					}
	    			Link.l17 = "Non importa, grazie.";
	    			Link.l17.go = "exit";
    			}
    			else
    			{
					dialog.text = "Mmm... Non vedo nessuna delle tue navi.";
	    			Link.l1 = "Volevo solo sapere della possibilità di attraccare.";
	    			Link.l1.go = "exit";
				}
			}
		break;

/*  //////////   hasert уже не надо но пусть висит ////////////////////////////////////
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Diamo un'occhiata a quella nave.";
			Link.l1 = "Bene.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, ho cambiato idea.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Diamo un'occhiata a quella nave.";
			Link.l1 = "Bene.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, ho cambiato idea.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Diamo un'occhiata a quella nave.";
			Link.l1 = "Bene.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, ho cambiato idea.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Diamo un'occhiata a quella nave.";
			Link.l1 = "Bene.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "No, ho cambiato idea.";
			Link.l2.go = "exit";
		break;
*/		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (MOD_SKILL_ENEMY_RATE >= 6) NPChar.MoneyForShip = 5*GetPortManPriceExt(NPChar, chref); // для высокой сложности - 5x цена
			else NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName)+" '"+chref.Ship.Name+"', classe "+RealShips[sti(chref.Ship.Type)].Class+", il costo dell'ormeggio è "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+" al mese, pagamento per un mese in anticipo.";
			Link.l1 = "Sì, mi va bene.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
			    Link.l1.go = "ShipStock_3";
			}
			else
			{
                Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = "No, ho cambiato idea.";
			Link.l2.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "E mi andrà bene anche a me, non appena raccoglierai l'importo richiesto.";
			Link.l1 = "Oops... Tornerò più tardi.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3": // hasert новый кейс выбора для оффов
			//AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			if (sti(NPChar.StoreWithOff))
			{
				AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.ShipInStockMan = NPChar.id;
			// Warship 22.03.09 fix Не перенеслось с КВЛ 1.2.3
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчёта
			chref.Ship.Crew.Quantity  = 0;
			RemoveCharacterCompanion(pchar, chref);
			}
			else
			{
				AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			chref = GetCharacter(NPC_GenerateCharacter("ShipInStockMan_", "citiz_"+(rand(9)+31), "man", "man", 1, NPChar.nation, -1, false, "quest"));
			chref.id = "ShipInStockMan_" + chref.index; //меняем ID на оригинальный
			chref.loyality = MAX_LOYALITY; 
			chref.name = "";
			chref.lastname = "";
			 chref.Ship.Crew.Quantity  = 0;
			DeleteAttribute(chref,"ship");
			chref.ship = "";
			
			chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчёта
			//  chref.Ship.Crew.Quantity  = 0;
			compref = GetCharacter(sti(NPChar.ShipToStoreIdx));//компаньон, у которого надо забрать корабль
			compref.Ship.Crew.Quantity  = 0;
            RemoveCharacterCompanion(pchar, compref);
			makearef(arTo, chref.ship);
			makearef(arFrom, compref.Ship);
			CopyAttributes(arTo, arFrom);

			compref.ship.type = SHIP_NOTUSED;
			RemoveCharacterCompanion(pchar, compref);
			AddPassenger(pchar, compref, false);
			DelBakSkill(compref);
			}

			chref.location = "";
			chref.location.group = "";
			chref.location.locator = "";
			NPChar.Portman	= sti(NPChar.Portman) + 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) + 1;

			dialog.text = "Bene. Puoi riprendere la tua nave quando ne hai bisogno.";
			Link.l1 = "Grazie.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = "Quale nave in particolare hai intenzione di prendere?";
	                cn = 1;
	                for(i=1; i<MAX_CHARACTERS; i++)
					{
						makeref(chref, Characters[i]);
						if (CheckAttribute(chref, "ShipInStockMan"))
						{    
							if (chref.ShipInStockMan == NPChar.id)
							{
								attrL = "l"+cn;
								if(HasSubStr(chref.id, "ShipInStockMan_"))											  
								{ 
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
								Link.(attrL).go = "ShipStockManBack22_" + i; 
								}
								else
								{  
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' and my officer " + GetFullName(chref) + ".";
								Link.(attrL).go = "ShipStockManBack11_" + i;
								}
								cn++;
							}
						}
					}
	
	    			Link.l99 = "No, ho cambiato idea.";
	    			Link.l99.go = "exit";
				}
				else
				{
	                dialog.text = "Hai spazio per un'altra nave?";
	    			Link.l1 = "Oh, giusto. Grazie.";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Mmm. Non vedo la tua nave ammiraglia nel porto. E puoi solo riprendere le tue navi qui.";
    			Link.l1 = "Bene, verrò a prenderli più tardi.";
    			Link.l1.go = "exit";
			}
		break;

        case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
			if (CheckAttribute(chref, "quest.Mutiny.date")) {
				dialog.text = "Vediamo... Questa nave ha lasciato il porto alle "+chref.quest.Mutiny.date+".";
				link.l1 = "Cosa intendi dire con 'partita'? Lei deve essere qui, nei moli!";
				link.l1.go = "ShipStockManMutiny";
				break;
			}
			// <--
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
			    dialog.Text = "Vuoi riprendere la tua nave? Per l'ormeggio, devi ancora "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+".";
			}
			else
			{
				dialog.Text = "Ritirando?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "Sì.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "No, ho cambiato idea.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockManBack2": // hasert новый кейс для сторожа.
			if (sti(NPChar.StoreWithOff))
			{   
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			}
			else
			{   
			dialog.Text = "A quale dei tuoi ufficiali dovrei darlo?";
			int _curCharIdx;
			int q = 0;
			int nListSize = GetPassengersQuantity(pchar);
			for(i=0; i<nListSize; i++)
				{
				_curCharIdx = GetPassenger(pchar,i);
				sld = GetCharacter(_curCharIdx);
					if (_curCharIdx!=-1)
					{
						ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;

						if (!CheckAttribute(sld, "CompanionDisable"))
					    {
							if (!ok && GetRemovable(&characters[_curCharIdx]))
							{
								attrL = "l"+i;
								sProf = "";
								if (IsOfficer(sld)) sProf += " (vanguard)";
								if (sti(pchar.Fellows.Passengers.navigator) == sti(sld.index)) sProf += " (navigator)";
								if (sti(pchar.Fellows.Passengers.boatswain) == sti(sld.index)) sProf += " (boatswain)";
								if (sti(pchar.Fellows.Passengers.cannoner) == sti(sld.index)) sProf += " (cannoneer)";
								if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index)) sProf += " (surgeon)";
								if (sti(pchar.Fellows.Passengers.carpenter) == sti(sld.index)) sProf += " (carpenter)";
							    if (sti(pchar.Fellows.Passengers.treasurer) == sti(sld.index)) sProf += " (purser)";
								Link.(attrL)	= GetFullName(&characters[_curCharIdx]) + sProf;
								Link.(attrL).go = "ShipStockManBack2_" + i;
								q++;
							}
						}
					}
				}
			attrL = "l"+nListSize;
			if (q == 0)
				{
				Link.(attrL) = RandSwear() + "I forgot to bring an officer with me for this ship.";
				Link.(attrL).go = "exit";
				}
			else
				{
				Link.(attrL) = "No, I've changed my mind..";
				Link.(attrL).go = "exit";
				}
			}
		break;
		
		//--> Jason Голландский гамбит
		case "ShipStock_HWICHoll":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Sì, sì, lo so. Ma posso prendere solo una nave per l'ormeggio gratuito. Quindi, per favore, risolvi le cose con la tua squadra e poi torna di nuovo.";
				link.l1 = "Bene, porterò solo la nave ammiraglia.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Sì, sì, lo so. Per ordine del mio signore Rodenburg, accettiamo la tua nave per la conservazione e forniremo un ufficiale di guardia per tutto il tempo che la tua nave rimane qui. Per favore, firma qui... e qui...";
				link.l1 = "Bene... Capisco che tutte le formalità sono ora risolte?";
				link.l1.go = "ShipStock_HWICHoll_1";	
			}
		break;
		
		case "ShipStock_HWICHoll_1":
			dialog.text = "Sì. Non c'è bisogno che tu ti preoccupi della tua nave - ci prenderemo cura di lei. Puoi tornare dal mio signore Rodenburg.";
			link.l1 = "Grazie. Arrivederci.";
			link.l1.go = "exit";	
			npchar.quest.HWICHoll = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "ShipStock_HWICEng":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Sì, sì, lo so. Ma posso prendere solo una nave per l'ormeggio gratuito. Quindi, per favore, risolvi le cose con la tua squadra e poi torna di nuovo.";
				link.l1 = "Bene, porterò solo l'ammiraglia.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Sì, certo. Hai i soldi con te?";
				if(makeint(Pchar.money) >= 10000)
				{
					link.l1 = "Certo. Ecco a te.";
					link.l1.go = "ShipStock_HWICEng_1";	
				}
				else
				{
					link.l1 = "No. Torno tra un attimo.";
					link.l1.go = "exit";	
				}
			}
		break;
		
		case "ShipStock_HWICEng_1":
			dialog.text = "Bene. Ci prenderemo cura della tua nave e forniremo un ufficiale di guardia per tutto il tempo che la tua nave rimane qui.";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			npchar.quest.HWICEng = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Fleetwood"), "questmarkmain");
		break;
		//<-- Голландский гамбит
		case "Escort_companion":
			dialog.text = "Volevi qualcosa, cap?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Escort_companion";
		break;
		
		// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
		case "ShipStockManMutiny":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			dialog.text = "Il tuo ufficiale "+GetFullName(chref)+" informato"+NPCharSexPhrase(chref,"","")+" mi quello "+NPCharSexPhrase(chref,"lui","lei")+" ho dovuto prendere il mare per tuo ordine. Non ho obiettato "+NPCharSexPhrase(chref,"lui","lei")+".";
			link.l1 = "Cazzo! Non c'era un ordine del genere! Non avrei dovuto affidare la mia nave a quel bastardo! Eh, vabbè, non posso fare nulla per la mia perdita comunque.";
			link.l1.go = "ShipStockManMutiny1";
			// вот тут можно микроквестик сделать
			//link.l2 = "Che sorpresa... Hai "+NPCharSexPhrase(chref,"lui","lei")+"ti dirò, dove sono andati, per caso?";
			//link.l2.go = "ShipStockManMutiny2";
		break;
		
		case "ShipStockManMutiny1":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.lifeday = 0;

			dialog.text = "Mi dispiace, "+GetAddress_Form(NPChar)+". Dovresti stare più attento con i tuoi subordinati.";
			link.l1 = "Lo so, sono un idiota. Addio, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
		break;
		// <--
		
		// уникальные корабли и легендарные капитаны -->
		case "UniqueShips":
			dialog.text = "Navi uniche e gli individui a cui sono affidate non possono passare inosservate all'interno dell'arcipelago. Tuttavia, queste informazioni hanno un valore considerevole e non vengono fornite a cuor leggero.";
			if (sti(pchar.Money) >= 25000)
			{
				link.l1 = "Capisco. Basterebbe la somma di 25000 pesos per dimostrare le mie sincere intenzioni?";
				link.l1.go = "UniqueShips_2";
			}
			else
			{
				link.l1 = "Va bene, allora un'altra volta.";
				link.l1.go = "node_2";
			}
		break;
		
		case "UniqueShips_2":
			dialog.text = "Certo, sarebbe accettabile. In quale nave specifica sei interessato?";
			if (GetDLCenabled(DLC_APPID_4) && !CheckAttribute(pchar, "questTemp.SantaMisericordia_InfoPU") && CharacterIsAlive("SantaMisericordia_cap"))
			{
				link.l1 = "Galeone 'Santa Misericordia'.";
				link.l1.go = "UniqueShips_SantaMisericordia";
			}
			if (GetDLCenabled(DLC_APPID_5) && !CheckAttribute(pchar, "questTemp.LadyBeth_InfoPU") && CharacterIsAlive("LadyBeth_cap"))
			{
				link.l2 = "Patrullare la neve 'Signora Beth'.";
				link.l2.go = "UniqueShips_LadyBeth";
			}
			link.l99 = "Credo di saperne abbastanza.";
			link.l99.go = "node_2";
		break;
		
		case "UniqueShips_SantaMisericordia":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "1");
			pchar.questTemp.SantaMisericordia_InfoPU = true;
			dialog.text = "La Santa Misericordia è stata inviata dall'Escorial dall'Europa per supervisionare le colonie spagnole. Il suo capitano, Don Alamida, è un rinomato servitore della corona spagnola, un combattente spietato contro la corruzione e il crimine, e un zelota della fede cattolica. La Santa Misericordia naviga tra le colonie, iniziando e terminando il suo viaggio a L'Avana, concentrando solo sulla sua missione.\nIn ogni porto, Alamida trascorre diversi giorni, a volte più lunghi. Dicono che in questi momenti si può anche incontrarlo per strada, ma i locali non sono particolarmente desiderosi di tali incontri - negli spagnoli, il signore incute solo paura e timore.\nLa Santa Misericordia ha un equipaggio esperto e leale, scelto personalmente da Alamida. Ogni marinaio è pronto a difendere la loro Patria e il capitano con la propria vita. Dicono che Don Fernando ha ordinato che la Santa Misericordia non deve mai essere catturata, e ci sono voci che se l'equipaggio dovesse affrontare ostacoli insormontabili all'imbarco, preferirebbero mandare la nave negli abissi piuttosto che vederla presa d'assalto.";
			link.l1 = "Grazie mille.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_LadyBeth":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "2");
			pchar.questTemp.LadyBeth_InfoPU = true;
			dialog.text = "La signora Beth è una vera bellezza. Un miracolo del genio marittimo inglese, comandato da Albert Blackwood, ex ufficiale della marina reale. Infatti, non tutti riescono a disertare in modo così spettacolare! Ha lasciato il servizio, ha ucciso una brillante carriera e ha rubato una nave da guerra - tutto per la caccia al tesoro!\nE non invano. Ha già trovato abbastanza per comprare metà di Barbados, ma vuole ancora di più. Se lo incontri in mare - non cercare nemmeno di intercettarlo. Troppo buona una nave, e il capitano è esperto e cauto. Ultimamente, Blackwood ha frequentato Cayman - scavando giorno e notte, lavorando la gente fino alla morte. Se decidi di controllare - non prendere meno di sessanta uomini e buone armi da fuoco... In realtà, anche quello potrebbe non essere abbastanza\nSpero che tu sappia sparare, poiché una compagnia di ex fanteria marina del colonnello Fox è disertata con lui. Professionisti, niente a che vedere con i comuni tagliagole. E non attaccarlo mai nei porti francesi - ha protezione e patroni lì, ricevendo una quota dei suoi ritrovamenti.";
			link.l1 = "Grazie mille.";
			link.l1.go = "node_2";
		break;
		
		// уникальные корабли и легендарные капитаны <--
	}
}

float BurntShipQuest_GetMaxNeededValue(int iShipType, string _param)
{
	float NeededValue = makefloat(GetBaseShipParamFromType(iShipType, _param));
	switch (_param)
	{
		case "speedrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "turnrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "capacity":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/8.0)); 
		break;
	}
	return NeededValue;
}

// Warship 25.07.09 Генер "A burnt vessel". Начальные иниты для портмана - тип разыскиваемого судна, выдающаяся характеристика и т.д.
void BurntShipQuest_FillStartParams(ref _npchar)
{
	int rank = sti(PChar.rank);
	int shipType, temp;
	float neededValue;
	String shipAttribute;
	
	// TODO Пересмотреть зависимость от ранга
	if(rank <= 5)
	{
		shipType = SHIP_LUGGER + rand(1);
		
		switch(shipType)
		{
			case SHIP_LUGGER:
				shipAttribute = "speedrate";
			break;
			
			case SHIP_SLOOP:
				temp = rand(2);
				
				if(temp == 2)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
		}
	}
	
	if(rank > 5 && rank <= 15)
	{
		shipType = SHIP_SCHOONER + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER:
				if(rand(1) == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_BARKENTINE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_SHNYAVA:
				shipAttribute = "capacity";
			break;
		}
	}
	
	if(rank > 15 && rank <= 25)
	{
		shipType = SHIP_FLEUT + rand(3);
		
		switch(shipType)
		{
			case SHIP_FLEUT:
				shipAttribute = "turnrate";
			break;
			
			case SHIP_CARAVEL:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_PINNACE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_BRIGANTINE:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
		}
	}
	
	if(rank > 25 && rank <= 35)
	{
		shipType = SHIP_SCHOONER_W + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER_W:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_GALEON_L:
				shipAttribute = "capacity";
			break;
			
			case SHIP_CORVETTE:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
		}
	}
	
	if(rank > 35)
	{
		shipType = SHIP_GALEON_H + rand(1);
		
		switch(shipType)
		{
			case SHIP_GALEON_H:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_FRIGATE:
				shipAttribute = "turnrate";
			break;
		}
	}
	
	neededValue = BurntShipQuest_GetMaxNeededValue(shipType, shipAttribute);
	
	Log_TestInfo("shipType == " + shipType);
	Log_TestInfo("ShipAttribute == " + shipAttribute);
	Log_TestInfo("ShipNeededValue == " + neededValue);
	
	_npchar.Quest.BurntShip.ShipType = shipType;
	_npchar.Quest.BurntShip.ShipAttribute = shipAttribute;
	
	if(shipAttribute != "capacity") // Чтобы трюм с десятичными не писался
	{
		_npchar.Quest.BurntShip.ShipNeededValue = FloatToString(neededValue, 2);
	}
	else
	{
		_npchar.Quest.BurntShip.ShipNeededValue = MakeInt(neededValue);
	}
}

void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true, "citizen"));
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	SetCaptanModelByEncType(sld, "trade");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушел кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo("The absent-minded cap " + sld.id + " went to: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
    makearef(arCapBase, npchar.quest.capitainsList);
    int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId; 
	for (int i=0; i<Qty; i++)
    {
    	arCapLocal = GetAttributeN(arCapBase, i);
        sCapitainId = GetAttributeName(arCapLocal);
    	if (GetCharacterIndex(sCapitainId) > 0) //если еще жив
    	{
			bResult++;			
    	}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
    }
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true, "soldier"));
	SetSeekCapShip(sld);
	sld.Ship.Mode = "pirate";
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	npchar.quest.chest = 12-sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Thieving cap " + sld.id + " sailed out of: " + sld.city + " and went to: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry3"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry6"; 
		break;
	}
	return itemID;
}

// --> Jason, новые мини-квесты
string findCurrentCity1(ref NPChar)//выбираем целевой город 1
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}

string findCurrentCity2(ref NPChar)//выбираем целевой город 2
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-3)];
	return colonies[nation].id;
}

string findCurrentCity3(ref NPChar)//выбираем целевой город 3
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-7)];
	return colonies[nation].id;
}

int Escort_ShipType()
{
	int iShipType;
	switch (rand(2))
	{
		case 0: iShipType = SHIP_FLEUT; 	break;
		case 1: iShipType = SHIP_GALEON_L; 	break;
		case 2: iShipType = SHIP_PINNACE;	break;
	}
	return iShipType;
}
//<-- новые мини-квесты

void DelBakSkill(ref _compref) // hasert
{
	DelBakSkillAttr(pchar);
	ClearCharacterExpRate(pchar);
	RefreshCharacterSkillExpRate(pchar);
	SetEnergyToCharacter(pchar);

	DelBakSkillAttr(_compref);
	ClearCharacterExpRate(_compref);
	RefreshCharacterSkillExpRate(_compref);
	SetEnergyToCharacter(_compref);
}

void SetSeekCapShip(ref _chr)
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) < 27) iRank = 3;
	if (sti(pchar.rank) >= 27) iRank = 4;
	
	int iShip = SHIP_WAR_TARTANE;
	switch (iRank)
	{
		case 0:
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 1:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break; 
		case 2:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 3:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 4:  
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	_chr.Ship.Type = GenerateShipExt(iShip, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, "pirate");
    Fantom_SetBalls(_chr, "pirate");
	Fantom_SetUpgrade(_chr, "pirate");
	Fantom_SetGoods(_chr, "pirate");
}
