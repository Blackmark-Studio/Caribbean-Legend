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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Der Alarm wurde in der Stadt ausgelöst und jetzt sucht jeder nach dir. Wenn ich du wäre, würde ich dort nicht bleiben.","Alle Stadtwachen durchkämmen die Stadt auf der Suche nach dir. Ich bin doch kein Narr, mit dir zu reden!","Lauf, "+GetSexPhrase("Kamerad","lass")+", bevor die Soldaten dich mit Löchern durchlöchern..."),LinkRandPhrase("Was brauchst du, "+GetSexPhrase("Schurke","Stinker")+"?! Die Stadtwachen haben bereits deine Spur aufgenommen, du wirst nicht weit kommen, du dreckiger Pirat!","Mörder, verlasse sofort mein Haus! Wachen!","Ich habe keine Angst vor dir, "+GetSexPhrase("Schurke","Ratte")+"! Bald hängen sie dich in unserer Festung, du kommst nicht weit..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, ein Alarm ist für mich nie ein Problem...","Sie werden mich nie kriegen."),RandPhraseSimple("Halt den Mund, "+GetWorkTypeOfMan(npchar,"")+", und vielleicht reiße ich deine dreckige Zunge nicht heraus!","Heh, "+GetWorkTypeOfMan(npchar,"")+", und alle dort - fangt die Piraten! Das sage ich dir, Kumpel: sei still und du wirst leben..."));
				link.l1.go = "fight";
				break;
			}
			//Jason, фрахт
			if (CheckAttribute(pchar, "questTemp.WPU"))
			{
				if (pchar.questTemp.WPU.Fraht == "fail" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					dialog.text = "Oh, ich weiß, wer du bist. Du hast dich verpflichtet, Ladung zu liefern, aber du hast sie stattdessen gestohlen! Wachen, Wachen!";
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
				dialog.text = "Was kann ich für Sie tun, Monsieur?";
				Link.l1 = "Ich habe Geschäft mit Ihnen...";
				Link.l1.go = "quests";
				Link.l2 = "Es tut mir leid, aber ich muss gehen.";
				Link.l2.go = "exit";
				NPChar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			if(NPChar.quest.meeting == "0")
			{
				
				dialog.text = "Grüße, "+GetAddress_Form(NPChar)+". Ich glaube, wir haben uns noch nie getroffen. Ich bin "+GetFullName(npchar)+" - der Hafenmeister.";
				Link.l1 = "Hallo, "+GetFullName(NPChar)+". Ich bin "+GetFullName(PChar)+", Kapitän der '"+PChar.ship.name+"'.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice")
				{
					dialog.text = "Kapitän MacArthur, wie ich Sie immer daran erinnere - es ist nicht nötig, jedes Mal bei mir einzuchecken. Machen Sie sich keine Sorgen.";
					link.l1 = "Hör auf damit, Herr "+npchar.lastname+" Ich bin genau wie alle anderen.";
					Link.l1.go = "node_2";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Grüße, "+GetAddress_Form(NPChar)+". Haben Sie Geschäfte mit mir?","Hallo, "+GetFullName(Pchar)+". Ich habe gesehen, wie Ihr Schiff in unseren Hafen eingelaufen ist und ich war sicher, dass Ihr zu mir kommen würdet.","Oh, Kapitän "+GetFullName(Pchar)+". Was hat dich zu mir geführt?");
				Link.l1 = "Hallo, "+GetFullName(NPChar)+". Ich wollte mit dir reden.";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "Also, was ist mit dem Geld? Hast du mindestens tausend Pesos für mich?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "Ja, ich habe"+GetSexPhrase("","")+". Das sind genau tausend Pesos. Jetzt die Informationen!";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("Nein, noch nicht...","Noch nicht...","Noch nicht, aber ich bringe es bald...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "Bitte, lassen Sie mich das Herz des Problems erklären. Ich und mein alter Freund, Kapitän  "+PChar.GenQuest.ChurchQuest_1.CapFullName+", haben uns nur um ein paar Stunden verpasst und ich habe dringende Geschäfte mit ihm. Jetzt muss ich ihn einholen, aber ich habe keine Ahnung"+GetSexPhrase("","")+" von seinem Aufenthaltsort.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "Hafenmeister, Herr, ich brauche Informationen über das Schiff namens '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"' gehört Kapitän "+PChar.GenQuest.ChurchQuest_1.CapFullName+".";
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
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Die Ladung für Ihre Kolonie befindet sich im Laderaum meines Schiffes.";
					Link.l1.go = "Fraht_completeLevelUp";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht != "lost" && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Die Ladung für deine Kolonie befindet sich im Laderaum meines Schiffes.";
					Link.l1.go = "Fraht_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht == "lost" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					if (pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
					{
						dialog.text = "Ach, also bist du endlich gekommen. Ehrlich gesagt, habe ich nicht erwartet, dass du zurückkommst. Wir haben bereits die Behörden gebeten, dich als gesuchte Person zu kennzeichnen. Also, was hast du zu sagen?";
						Link.l1 = "Ich habe es wegen unvorhergesehener Umstände nicht geschafft, die Ladung rechtzeitig zu liefern. Aber ich möchte diesen Konflikt auf friedliche Weise beilegen. Ich habe Ihre Ladung gebracht und ich hoffe, dass wir uns einigen können.";
						Link.l1.go = "Fraht_complete_bad";
					}
					else
					{
						dialog.text = "Oh, ich weiß wer du bist. Du hast dich verpflichtet, die Ladung zu liefern, aber du hast sie stattdessen gestohlen! Wachen, Wachen!";
						Link.l1 = "Aaargh!";
						Link.l1.go = "exit";
						LAi_group_Attack(NPChar, Pchar);
					}
				}
// <-- фрахт
//-------------------------------------------//Jason, почта---------------------------------------------------	
		
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer != "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Ich habe Post für eure Kolonie geliefert.";
					Link.l1.go = "Postcureer_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer == "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Oh, also bist du endlich gekommen. Ehrlich gesagt, wir dachten schon, du wärst tot... Nun, ich vermute, es ist eine gute Sache, dass du nur ein Dummkopf und kein toter Mann bist.";
					Link.l1 = "Ich habe es aufgrund unvorhergesehener Umstände nicht geschafft, die Post rechtzeitig zu liefern. Aber hier ist sie.";
					Link.l1.go = "Postcureer_complete_bad";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.fail") && pchar.questTemp.WPU.Postcureer.StartCity == npchar.city)
				{
					dialog.text = "Was ist passiert? Du siehst aus wie der leibhaftige Tod.";
					Link.l1 = ""+GetAddress_FormToNPC(NPChar)+", du hattest recht, als du mich vor der Gefahr gewarnt hast. Zwei Männer in Schwarz haben mich direkt am Ausgang des Hafenamts angegriffen und... nun, sie haben das Paket von mir weggenommen.";
					Link.l1.go = "Postcureer_complete_fail";
					break;
				}
// <-- почта
//-------------------------------------------//Jason, эскорт---------------------------------------------------	
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Ich wurde hier vom Hafenmeister geschickt "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Mir wurde aufgetragen, ein Schiff zu eskortieren, das eine Ladung Waffen und Munition transportiert. Hier sind meine Papiere.";
					Link.l1.go = "Escort_LUGo_0";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0") && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Ich habe das Schiff mit den Waffen eskortiert, genau wie wir es vereinbart haben.";
					Link.l1.go = "Escort_LUGo_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "current" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Ich habe das vermisste Schiff gefunden und zu eurem Hafen gebracht. Der Schiffskapitän sollte bereits bei Ihnen gemeldet haben.";
					Link.l1.go = "Escort_LU1WM_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Ich habe das vermisste Schiff gefunden und es zu eurem Hafen gebracht. Der Kapitän des Schiffes sollte bereits bei euch gemeldet haben.";
					Link.l1.go = "Escort_LU1VSP_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "sink" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Ich habe das vermisste Schiff an den Ufern der Insel gefunden "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Ihr Kapitän war in einen ungleichen Kampf gegen die überwältigenden Piratenkräfte verwickelt. Ich half, so gut ich konnte, ach, vergebens: verdammte Schurken versenkten das Schiff. Alles, was ich zu diesem Zeitpunkt tun konnte, war, sie zu rächen.";
					Link.l1.go = "Escort_LU1VSP_completeSink";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Ich habe das vermisste Schiff an den Küsten der Insel gefunden "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Nun, nicht das Schiff, eigentlich, sondern eher etwa ein halbes Hundert Mann ihrer Besatzung und der Kapitän. Sie sind jetzt sicher - die Besatzung ist auf mein Schiff gestiegen, und der Kapitän ist jetzt in eurer Stadt - ich nehme an, er hat euch bereits einen Besuch abgestattet.";
					Link.l1.go = "Escort_LU1S_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Ich habe Ihre Aufgabe erfüllt. Die Piratenstaffel, die den Handelskonvoi angegriffen hat, wurde zerstört.";
					Link.l1.go = "Escort_LU2_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus != "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Ich bin der Kapitän des Begleitschiffes. Ich kam, um zu berichten, dass ich die Handelsschiffe in den Hafen gebracht habe.";
					Link.l1.go = "Escort_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus == "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Ich bin der Kapitän des Eskortschiffs. Ich wurde gesandt, um zwei Handelsschiffe und Fracht zum Hafen zu bringen, aber leider sanken beide eskortierten Schiffe während eines Kampfes mit einem feindlichen Konvoi. Trotzdem konnte ich die Fracht noch liefern.";
					Link.l1.go = "Escort_fail";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id && !CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp"))
				{
					dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
					Link.l1 = "Ich bin der Kapitän des Eskortschiffs. Ich kam, um zu berichten, dass ich die Handelsschiffe zum Hafen gebracht habe.";
					Link.l1.go = "Escort_complete";
					break;
				}
// <-- эскорт
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice" && NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Wie angenehm, das von Ihnen zu hören. Viele wären an Ihrer Stelle eingebildet geworden. Also, wie können ich und meine Aufzeichnungen Ihnen behilflich sein?";
			}
			else dialog.text = "Ausgezeichnet. Ich stehe zu Ihren Diensten, "+GetFullName(PChar)+".";
			if (npchar.city != "Panama") // Captain Beltrop, 24.12.2020, запрет брать задания и ставить корабли в ПУ Панамы
			{
				Link.l2 = "Haben Sie irgendwelche Jobs, die ich übernehmen kann? Oder vielleicht einen Vertrag?";
				Link.l2.go = "Work_check"; //квесты
				Link.l3 = "Kann ich eines meiner Schiffe für einige Zeit hier anlegen?";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "Ich möchte mein Schiff abholen.";
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Ich bin gekommen, um finanzielle Geschäfte zu besprechen.";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Ich bin hier auf Anfrage eines bestimmten Mannes. Sein Name ist Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" hat mich zu dir geschickt. Ich soll etwas abholen...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "Ich möchte mehr über die Kapitäne erfahren, die sich bei Ihrer Hafenbehörde registriert haben.";
			link.l6.go = "CapitainList";
			link.l61 = "Könnten Sie Einblicke in die einzigartigen, maßgeschneiderten Schiffe und ihre legendären Kapitäne geben?";
			link.l61.go = "UniqueShips";
			
			link.l8 = "Ich bin mit einer anderen Angelegenheit beschäftigt.";
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
					link.l9 = "Hallo, ich bin auf Einladung deines Sohnes gekommen."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Es geht um Ihre Tochter...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "Ich bin zufällig auf dieses Paket mit Schiffsunterlagen gestoßen.";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "Ich bin zufällig über dieses Paket mit Schiffsdokumenten gestolpert, jemand muss sie verloren haben.";
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
			Link.l15 = "Danke. Auf Wiedersehen.";
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "Ihr Problem kann leicht gelöst werden. Gehen Sie zum Navigationsservicebeamten und er kann Ihnen alle Informationen zur Route des Schiffes Ihres Freundes geben.";
			link.l1 = "Leider ist es nicht so einfach. Mein Freund hat sein Schiff in eurem Hafen umbenannt... aus religiösen Gründen.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "Ich verstehe. Das macht die Dinge ein bisschen komplizierter. Ich muss in den Aufzeichnungen im Schiffsregister herumwühlen, und das wird einige Zeit in Anspruch nehmen. Und Zeit ist Geld, wie Sie wahrscheinlich wissen.";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "Ich verstehe das perfekt, Herr "+GetFullName(NPChar)+", und ich bin ausreichend vorbereitet, um Ihre Zeit zu bewerten ... sagen wir mal, im Wert von tausend Pesos.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "Das ist schade, da ich im Moment kein Geld bei mir habe... Ich komme später wieder...";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "Perfekt! Lasst uns jetzt sehen... nur eine Minute... hier... genau. Die Umbenennung des Schiffes wurde registriert, und das Schiff, das von nun an als '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"' befehligt von Kapitän "+PChar.GenQuest.ChurchQuest_1.CapFullName+" ist heute in Richtung  gesegelt "+XI_ConvertString("Colony"+sColony+"Gen")+".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "Oh! Sie verstehen wirklich, dass ich ein sehr beschäftigter Mann bin, und ich freue mich, dass Sie das zu schätzen wissen! Mal sehen... nur eine Minute... hier... richtig. Die Umbenennung des Schiffes wurde registriert, und das Schiff, das von nun an als '"+PChar.GenQuest.ChurchQuest_1.CapShipName+"' befehligt von Kapitän "+PChar.GenQuest.ChurchQuest_1.CapFullName+" hat heute in Richtung  abgelegt "+XI_ConvertString("Colony"+sColony+"Gen")+".";			
				link.l1 = "Danke, Herr, Sie haben mir einen großen Gefallen getan.";
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
			dialog.text = "Was genau möchten Sie wissen?";
			link.l1 = "Können Sie mir sagen, ob das Schiff dieses Kapitäns Ihren Hafen besucht hat?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "Hmm... Und darf ich wissen, warum Sie fragen?";
			link.l1 = "Ich habe Geschäfte mit ihm. Aber wenn er nicht in deinem Hafen angerufen hat oder du nicht weißt...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "Er hat. Aber preise alle Heiligen, erst heute Morgen hat er uns seine Anwesenheit genommen und ist zu "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapGoToColony+"Konto")+". Und ich fühle aufrichtiges Mitleid für jeden, der mit ihm zu tun hat.";
			link.l1 = "In diesem Fall wünscht mir Glück - und danke für deine Hilfe.";
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
			dialog.text = "Was möchten Sie wissen, "+GetSexPhrase("Herr","Fräulein")+" "+GetFullName(PChar)+"?";
			link.l1 = "Könnten Sie mir sagen, ob dieser Kapitän in Ihrem Hafen vor Anker gegangen ist oder nicht?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "Hmm, das hat er sicherlich. Und ich muss sagen, dass ich ungeduldig auf diesen gesegneten Moment warte, wenn er diesen lange ertragenen Hafen endlich verlässt.";
			link.l1 = "Du meinst, sein Schiff ist noch hier?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "Ja, gnädig "+GetSexPhrase("Herr","Dame")+". Der gesamte Hafen, beginnend mit den niedrigsten Ladern und endend mit dem Leiter des Lotsendienstes, betet für seine schnelle Abreise. Sein Schiff hat gerade das Trockendock verlassen, wo es prompt repariert wurde, aber zu diesem Zeitpunkt hatte ihr galanter Kapitän bereits mit jedem Zimmermann Streit und lehnte drei Lieferungen ausgewählter Planken für den Schiffsrumpf ab. Aber morgen wird uns unser gnädigster und allsehender Herr von dieser... von dieser Plage, von diesem Dorn im Fleische des Menschen befreien!";
			link.l1 = "Jetzt beruhigen Sie sich, Herr "+NPChar.Name+", und bedenken Sie, dass es jemandem noch schwerer fallen wird. Sie haben diese Prüfung bereits bestanden, während ich diesen Kapitän von Ihnen noch treffen muss. Und jetzt, wenn Sie mich entschuldigen...";
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
			dialog.text = "Lassen Sie mich einen Blick darauf werfen! Ja, tatsächlich, in meinen Dokumenten ist dieses Set als ungültig gekennzeichnet. Es ist sehr nett von Ihnen, dass Sie einen Moment gefunden haben, um zu mir zu kommen und mir diese Papiere zu übergeben. Ab vom Wind, Kapitän!";
			link.l1 = "Danke!";
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
			dialog.text = s1+"Sag mal, würdest du eine Summe von "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" pesos ein passender Lohn?";
			link.l1 = "Natürlich nicht!";
			link.l1.go = "exit";
			link.l2 = "Nun, eine bescheidene Summe, aber auch keine große Sache. Ja, ich akzeptiere Ihr Angebot, "+npchar.name+".";
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
			dialog.text = "Wirst du mein Angebot annehmen?";
			link.l1 = "Natürlich nicht!";
			link.l1.go = "exit";
			link.l2 = "Vielleicht. Obwohl ich sicher bin, dass diese Papiere viel mehr wert sind.";
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
			dialog.text = "Ich bin ganz Ohr.";
			link.l1 = "Ich habe Ihren Flüchtling gebracht.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, Kapitän, vielen Dank! Wie geht es ihr? Ist sie verletzt? Warum ist sie weggelaufen? Warum?\nVersteht sie nicht? Der Bräutigam ist ein reicher und wichtiger Mann! Die Jugend ist naiv und töricht... sogar grausam. Denken Sie daran!";
			link.l1 = "Nun, du bist ihr Vater und die endgültige Entscheidung liegt bei dir, aber ich würde mit der Hochzeit nicht überstürzen...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Was wissen Sie schon? Haben Sie eigene Kinder? Nein? Wenn Sie eines haben, kommen Sie zu mir und dann reden wir.\nIch habe eine Belohnung versprochen für jeden, der sie zu ihrer Familie zurückbringt.";
			link.l1 = "Danke. Du solltest ein Auge auf sie haben. Ich habe das Gefühl, dass sie damit nicht aufhören wird.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, du bist das "+GetSexPhrase("Kapitän, der gebracht hat","junge Dame, die gebracht hat")+" mein verlorener Sohn mit einer jungen Braut?";
				link.l1 = "Ja, ich habe ihre Flucht unterstützt.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, komm, Wohltäter. Wahrscheinlich auf eine Belohnung wartend?";
				link.l1 = "Nun, ich komme auch ohne Belohnung aus, Ihre Dankbarkeit würde mir vollkommen ausreichen.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Ich bin Ihnen sehr dankbar, dass Sie mein Kind in der Not nicht im Stich gelassen und ihm geholfen haben, einen Ausweg aus dieser heiklen Situation zu finden. Lassen Sie mich Ihnen danken und bitte nehmen Sie diese bescheidene Summe und ein persönliches Geschenk von mir an.";
			link.l1 = "Danke. Es war mir eine Freude, diesem jungen Paar zu helfen.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Danke? Was für ein Dank?! Es ist ein halbes Jahr her, seit dieser Trottel ohne Arbeit herumhängt - und schau ihn an, er hat genug Zeit für Liebschaften! Als ich in seinem Alter war, hatte ich bereits mein eigenes Geschäft! Pff! Ein Gouverneur hat eine heiratsfähige Tochter - und dieser Dummkopf hat eine Dirne ohne Sippe oder Verwandtschaft in mein Haus gebracht und gewagt, um meinen Segen zu bitten!";
			link.l1 = "Hmm... Anscheinend glaubst du nicht an aufrichtige Gefühle?";
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
			dialog.text = "Welche Gefühle? Von welchen Gefühlen sprichst du? Gefühle... wie kannst du in deinem Alter so leichtsinnig sein?! Schande über dich, dass du die jungen Leute in ihren Launen verwöhnst und als Kuppler handelst! Du hast nicht nur ein Mädchen aus ihrem Zuhause genommen, sondern auch das Leben meines Grünschnabels ruiniert. Es wird kein Dank an dich gehen. Lebewohl.";
			link.l1 = "Gut, und das Gleiche gilt für dich...";
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
				dialog.text = LinkRandPhrase("Ja, verdammt noch mal! Ich habe eine Aufgabe für dich!","Ha! Du bist gerade rechtzeitig! Ich habe ein Problem, das gelöst werden muss.","Aber natürlich! Natürlich habe ich Arbeit für dich! Weißt du, ich bin in letzter Zeit einfach überhäuft mit Problemen...");
				link.l1 = "Dann komm bitte zur Sache, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 Генер "Сгоревшее судно"
			if(hrand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "Gott! Kapitän "+GetFullName(PChar)+", du kommst gerade rechtzeitig! Ein solches Unglück ist passiert, eine solche Katastrophe... Das Schiff brannte im Hafen, während es in der Obhut der Hafenbehörde war! Wegen der Nachlässigkeit der Sicherheitskräfte hat das Schiff gebrannt... bis zur Wasserlinie gebrannt...\n"+"Herr, was habe ich getan, um eine solche Strafe zu verdienen? Ich war so viele Jahre ein treuer Diener...";
				link.l1 = "Also, was ist das große Problem? Ein Schiff ist abgebrannt? Und wofür gibt es Versicherungsverträge? Oder hast du dich entschieden, es nicht zu versichern, um dein Geld zu sparen, und jetzt frisst du dir das Herz aus?";
				link.l1.go = "BurntShip4";
				link.l2 = "Die Werft wird Ihnen dabei besser helfen können als ich. In ein paar Monaten werden sie das alte Schiff restaurieren oder sogar ein neues bauen. Entschuldigung, ich bin kein Schiffsbauer...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "Der Gouverneur sorgt sich um das Wohl seiner Bürger, deshalb hat er immer einige Jobs zu bieten. Es könnten Händler in der Taverne sein, die Hilfe suchen, und der Laden braucht Frachtkapitäne.";
			Link.l1 = "Ich habe noch eine Frage.";
			Link.l1.go = "node_2";
			Link.l2 = "Danke. Auf Wiedersehen.";
			Link.l2.go = "exit";
		break;

///Jason-----------------------новые генераторы накопительного типа для портмана----------------------------
		int iTime, idaysQty, iGoods, iGoodsQty, amount;
		case "Work_check"://фейс-контроль - общая проверка профпригодности ГГ и выбор задания
			//--> проверка миниквестов начальника порта. 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "Du solltest den Kapitän ausfindig machen "+npchar.quest.PortmansJornal.capName+" und bring ihm sein Schiffstagebuch zurück. Hast du Erfolg gehabt?";
				link.l1 = "Nein, noch nicht...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "Du hast dich dazu verpflichtet, ein gestohlenes zu suchen "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"'. Es wird keine weiteren Aufgaben für dich geben, bis du mit dieser fertig bist.";
				link.l1 = "Ich werde meine Suche fortsetzen, warte nur.";
				link.l1.go = "exit";
				link.l2 = "Ich möchte den Auftrag aufgeben.";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "Du hast mir versprochen, das Gestohlene zu suchen "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName))+" '"+npchar.quest.PortmansSeekShip.shipName+"'. Hast du es getan?";
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
					link.l1 = "Ja, ich habe es gefunden, es ist jetzt im Hafen. Du kannst es nehmen.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "Ich werde meine Suche fortsetzen, warte nur.";
					link.l1.go = "exit";
				}
				link.l2 = "Ich möchte den Auftrag aufgeben.";
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
						dialog.text = RandPhraseSimple("Es gibt keine Arbeit für diejenigen, die unter der Flagge von segeln "+NationNameGenitive(sti(pchar.nation))+"! Verlassen Sie sofort mein Büro!","Ich werde nicht zusammenarbeiten mit "+NationNameAblative(sti(pchar.nation))+". Verschwinde!");
						link.l1 = RandPhraseSimple("Nun, wie du willst...","Nun, wie du möchtest...");
						link.l1.go = "exit";
						break;
					}
					if (isBadReputation(pchar,40)) // проверка репутации ГГ с вызывающим доверие belamour legendary edition
					{
						dialog.text = "Dein Ruf erweckt kein Vertrauen in mir. Ich werde nicht mit dir zusammenarbeiten. Lebewohl.";
						link.l1 = "Was! Das sind alles Lügen.";
						link.l1.go = "exit";
						break;
					}
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
					{
						dialog.text = "Ich möchte Sie nicht beleidigen, Kapitän, aber... Ich fürchte, Sie könnten meine Aufgabe nicht erfüllen - Ihnen fehlt einfach die Erfahrung. Ich kann keinen Vertrag mit Ihnen abschließen.";
						link.l1 = "Ich verstehe. Nun, wie du sagst.";
						link.l1.go = "exit";
						break;
					}
					dialog.Text = "Hmm... Nun, das hängt von der Arbeit ab, an der du interessiert bist.";
					link.l1 = "Ich könnte Ihnen anbieten, mein Schiff für den Warentransport zu chartern.";
					Link.l1.go = "Fraht_begin";		//фрахты
					link.l2 = "Ich möchte zusätzliches Geld verdienen, indem ich Kaufleute begleite oder Post ausliefere.";
					Link.l2.go = "Check_other";		//доставка почты, эскорт
					Link.l3 = "Nun, vielleicht könntest du etwas anbieten?";
					Link.l3.go = "node_4"; 			//судовой журнан, угнанное судно, сгоревшее судно
				}
				else
				{
					dialog.Text = "Es bleibt nichts für heute. Komm an einem anderen Tag.";
					link.l1 = "Gut.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ich sehe dein Schiff nicht im Hafen. Halt dich fern und komm dann wieder zu mir - wir werden versuchen, etwas für dich zu finden.";
				link.l1 = "In Ordnung, das werde ich tun.";
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
						dialog.text = "Leider kann ich Ihnen nichts Derartiges anbieten. Schauen Sie in ein paar Tagen noch einmal vorbei.";
						link.l1 = "In Ordnung, ich werde genau das tun.";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Postcureer.count) > 3 && hrand(1) == 1) { //если 2 уровень
							dialog.text = "So... Du hast bereits mehrere Jobs als Kurier übernommen und warst dabei, nach meinem besten Wissen, ziemlich erfolgreich. Du kannst wahrscheinlich die Aufgabe, die ich dir gleich zuweisen werde, bewältigen.";
							link.l1 = "Ich bin ganz Ohr, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "Postcureer_LevelUp";
						} else { // первый уровень
							dialog.text = "Ich sehe, Sie haben ein schnelles Schiff. Ich kann Ihnen einen Botenjob anbieten - Zustellung von Post und Handelspapieren.";
							link.l1 = "Das ist interessant. Ich stimme zu. Wo muss ich hin?";
							link.l1.go = "Postcureer";
							link.l2 = "Danke, aber das ist einfach nicht meine Art von Arbeit.";
							link.l2.go = "exit";
						}
					}
				break;

				case "escort":
					if (pchar.questTemp.WPU.Escort == "begin" || pchar.questTemp.WPU.Escort == "late" || pchar.questTemp.WPU.Escort == "win" || CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp")) { // если заняты
						dialog.text = "Leider kann ich Ihnen nichts dergleichen anbieten. Schauen Sie in ein paar Tagen noch einmal vorbei.";
						link.l1 = "In Ordnung, das werde ich tun.";
						link.l1.go = "exit";
					} else { // если не заняты
						if (sti(pchar.questTemp.WPU.Escort.count) > 3 && hrand(1) == 1) { // 2 уровень
							dialog.text = "Sie haben bereits mehrmals erfolgreich Handelsschiffe eskortiert. Ich vermute, ich habe einen Auftrag, der Ihnen passen würde.";
							link.l1 = "Ich bin ganz Ohr.";
							link.l1.go = "Escort_LevelUp";
						} else { // 1 уровень
							if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_H && 2500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) < 0 && !CheckAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID")) { // если на ТГ
								dialog.text = "Ich habe einen Auftrag nur für dich. Es gibt zwei Handelsschiffe im Hafen, die schon längst hätten auslaufen sollen. Die Sache ist die, ihr Eskortschiff wurde beschädigt und wartet noch immer auf die notwendigen Reparaturen, so dass es vorerst nicht auslaufen kann. \nEs stellt sich heraus, dass dein Schiff ideal für den Job ist - außerdem muss ich noch zusätzliche Ladung in deinen Laderaum einlagern. Natürlich wird die Bezahlung doppelt sein - für die Fracht und die Eskorte.";
								link.l1 = "Was für ein interessantes Angebot! Ich nehme es an!";
								link.l1.go = "escort_bonus";
								link.l2 = "Danke, aber das ist einfach nicht meine Art von Arbeit.";
								link.l2.go = "exit";
							} else { // просто эскорт
								dialog.text = "Ich habe einen Job nur für dich. Zwei Handelsschiffe liegen gerade in unserem Hafen - sie brauchen Geleitschutz. Ich biete dir an, diese Schiffe zu ihrem Ziel zu begleiten. Wirst du das tun?";
								link.l1 = "Ein interessantes Angebot! Ich nehme es!";
								link.l1.go = "escort";
								link.l2 = "Danke, aber das ist einfach nicht meine Art von Arbeit.";
								link.l2.go = "exit";
							}
						}
					}
				break;
			}
			break;
		}
		//ничего не подошло
		dialog.text = "Leider kann ich Ihnen nichts dergleichen anbieten. Schauen Sie in ein paar Tagen wieder vorbei.";
		link.l1 = "In Ordnung, das werde ich tun.";
		link.l1.go = "exit";
		break;

///--> ------фрахт со свободным выбором пункта назначения, оплаты и вида груза из предложенного списка---------

		case "Fraht_begin":
			if (hrand(4) < 4)
			{
				if (pchar.questTemp.WPU.Fraht == "begin" || pchar.questTemp.WPU.Fraht == "late" || pchar.questTemp.WPU.Fraht == "lost" || CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))//проверка на занятость
				{
					dialog.Text = "Aber ich habe gehört, dass dein Schiff bereits gechartert wurde. Ich kann dir keine weiteren Frachten geben. Erfülle die Verpflichtungen, die du bereits eingegangen bist.";
					link.l1 = "Ja, du hast wahrscheinlich recht.";
					Link.l1.go = "exit";
					break;
				}
				if (1500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) > 0)//мало места - не даем
				{
					dialog.text = "Sie haben zu wenig Platz in Ihrem Laderaum. Ich brauche ein geräumigeres Schiff für eine Fracht. Ich schlage vor, Sie schauen im Laden nach - der örtliche Händler chartert häufig Schiffe, um kleine Mengen von Ladungen zu liefern.";
					link.l1 = "Ich verstehe. Nun, wie Sie sagen.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.WPU.Fraht.count > 3 && rand(1) == 0)
				{
					dialog.text = "Ich habe im Moment nichts Passendes. Aber du hast bereits mehrere erfolgreiche Lieferungen gemacht. Ich habe eine bestimmte Aufgabe, die ich speziell dir zuweisen möchte.";
					link.l1 = "Ich höre zu. Welche Art von Arbeit?";
					link.l1.go = "Fraht_LevelUp";
					break;
				}
				dialog.Text = "Nun, ich kann Ihnen mehrere Charter-Möglichkeiten anbieten.";
				link.l1 = "Lass uns sehen, dann...";
				Link.l1.go = "Fraht_choise";
			}
			else
			{
				dialog.Text = "Es gibt keine Frachten mehr für heute. Komm an einem anderen Tag.";
				link.l1 = "Ach, na gut.";
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
				dialog.text = "Die folgenden Varianten sind verfügbar:\n"+"Fracht "+GetGoodsNameAlt(iFrahtGoods1)+" in Höhe von "+FindRussianQtyString(iFrahtGoodsQty1)+" in die Stadt von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". Zahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\nFracht "+GetGoodsNameAlt(iFrahtGoods2)+" in der Menge von "+FindRussianQtyString(iFrahtGoodsQty2)+" in die Stadt von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", im "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\nFracht "+GetGoodsNameAlt(iFrahtGoods3)+" in der Menge von "+FindRussianQtyString(iFrahtGoodsQty3)+" in die Stadt von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty3)+". Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3))+"\nWas ist deine Wahl?";
				Link.l1 = "Ich wähle die zweite Variante - eine Charta für die Stadt "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" beladen mit "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Ich wähle die dritte Variante - eine Charta zur Stadt "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" beladen mit "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
				Link.l3 = "Ich werde die dritte Variante wählen - eine Charta zur Stadt "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3)+" beladen mit "+GetGoodsNameAlt(iFrahtGoods3)+".";
				Link.l3.go = "Fraht_Choise_3";
			}
			else //два варианта
			{
				dialog.text = "Die folgenden Varianten sind verfügbar:\n"+"Fracht "+GetGoodsNameAlt(iFrahtGoods1)+" in Höhe von "+FindRussianQtyString(iFrahtGoodsQty1)+" zur Stadt von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1)+". Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1))+"\nLadung "+GetGoodsNameAlt(iFrahtGoods2)+" in Höhe von "+FindRussianQtyString(iFrahtGoodsQty2)+" in die Stadt von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+", in "+FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2)+". Zahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2))+"\nWas ist deine Wahl?";
				Link.l1 = "Ich werde die erste Variante wählen - Charter in die Stadt "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1)+" beladen mit "+GetGoodsNameAlt(iFrahtGoods1)+".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Ich wähle die zweite Variante - eine Charta für die Stadt "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2)+" beladen mit "+GetGoodsNameAlt(iFrahtGoods2)+".";
				Link.l2.go = "Fraht_Choise_2";
			}
			Link.l4 = "Leider gibt es nichts Passendes für mich.";
			Link.l4.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;
	
		case "Fraht_Choise_1":
			dialog.text = "Nun, großartig! Ich werde die notwendigen Dokumente bearbeiten, und Sie können Ihr Schiff für die Beladung vorbereiten.";
			link.l1 = "Ich werde mein Bestes geben!";
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
			dialog.text = "Nun, großartig! Ich werde die notwendigen Dokumente bearbeiten, und Sie können Ihr Schiff für die Beladung vorbereiten.";
			link.l1 = "Ich werde mein Bestes geben!";
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
			dialog.text = "Nun, großartig! Ich werde die notwendigen Dokumente bearbeiten und Sie können Ihr Schiff für das Laden vorbereiten.";
			link.l1 = "Ich werde mein Bestes geben!";
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
			if (pchar.questTemp.WPU.Fraht.Chance > 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
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
				dialog.text = "Lass uns mal sehen. Du solltest eine Ladung liefern von "+GetGoodsNameAlt(iFrahtGoods)+" in Höhe von "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Aber wie ich sehe, hast du nicht die gesamte Lieferung geliefert - du bist "+FindRussianQtyString(sti(amount))+" kurz.";
				link.l1 = "Tausend Haie! Es müssen diese verfluchten Ratten sein! Aber mach dir keine Sorgen, "+GetAddress_FormToNPC(NPChar)+", Ich werde die fehlende Menge kaufen und die gesamte Charge abgeben.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Lass mal sehen. Du solltest eine Ladung liefern von "+GetGoodsNameAlt(iFrahtGoods)+" in Höhe von "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Korrekt?";
			link.l1 = "Absolut richtig, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "Fraht_complete_1";
		}
		else
		{
			dialog.text = "Ich sehe dein Schiff nicht im Hafen. Leg ab und komm dann wieder zu mir - dann werden wir reden.";
			link.l1 = "In Ordnung, ich werde genau das tun.";
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
				dialog.text = "Hm... Aber du warst "+FindRussianDaysString(iTime)+" zu spät. Daher muss ich deine Bezahlung für die Fracht kürzen. Laut Vertrag beträgt deine Strafe fünf Prozent des Gesamtbetrags für jeden Tag der Verspätung. Jetzt bitte, nimm dein "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+", und versuche, dich in Zukunft an den Vertrag zu halten.";
				link.l1 = "Nun, es ist zumindest etwas.";
				link.l1.go = "Fraht_complete_2";
				break;
			}
			dialog.text = "Danke für deine Arbeit. Bitte, nimm deine Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Danke!";
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
			dialog.text = "Haben Sie die Fracht geliefert? Hübsch. Tatsächlich mussten wir sie selbst kaufen, um sie dem Empfänger zu übergeben! Und das war ziemlich teuer, das sag' ich Ihnen. Also, wenn Sie Ihr Wohlwollen wiederherstellen wollen, müssen Sie unsere Ausgaben ausgleichen und auch die Strafe zahlen. Was die Fracht betrifft, können Sie sie behalten - wir brauchen sie nicht mehr.";
			link.l1 = "Ja, sicher. Wie viel?";
			link.l1.go = "Fraht_complete_bad_1";
		break;
	
		case "Fraht_complete_bad_1":
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)*3;
			dialog.text = "Dreimal die Kosten der Waren. Das beläuft sich auf "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+".";
			if (sti(Pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
			{
				link.l1 = "Das ist ziemlich viel. Aber Geschäft ist Geschäft. Gut, hier ist dein Geld.";
				link.l1.go = "Fraht_complete_pay";
			}
			link.l2 = "Bist du verrückt? Eine solch unverschämte Summe zu verlangen ist der Gipfel der Gier! Du wirst nichts von mir bekommen!";
			link.l2.go = "Fraht_complete_fail";
		break;
	
		case "Fraht_complete_pay":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			dialog.text = "Eine weise Entscheidung. Jetzt sehe ich, dass du tatsächlich eine ernste Person bist. Ich denke, wir können in der Zukunft immer noch zusammenarbeiten.";
			link.l1 = "Danke, und jetzt muss ich gehen.";
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
			dialog.text = "Oh, ich verstehe... Nun, in diesem Fall solltest du dein Gesicht nie wieder bei irgendeiner Hafenbehörde zeigen "+NationNameGenitive(sti(pchar.questTemp.WPU.Fraht.Nation))+"! Verschwinde!";
			link.l1 = "Ich habe sicher nicht viel verpasst...";
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
			dialog.text = "Beeil dich, der Empfänger weiß bereits, dass dein Schiff angekommen ist und er sorgt sich um seine Fracht.";
			link.l1 = "In diesem Fall werde ich keine Zeit mehr verschwenden!";
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
			dialog.text = "Dieses Paket muss bei der Hafenbehörde in der Stadt abgeliefert werden "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)+", für "+FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DaysQty)+", und so schnell wie möglich. Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))".";
			link.l1 = "Ich stimme zu!";
			link.l1.go = "Postcureer_1";
			link.l2 = "Hmm... Aber ich gehe nicht in diese Richtung. Tut mir leid, aber ich muss ablehnen.";
			link.l2.go = "exit";
		break;
	
		case "Postcureer_1":
			dialog.text = "Ausgezeichnet! Ich zähle auf dich. Hier ist das Paket.";
			link.l1 = "Ich werde sofort in See stechen!";
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
				dialog.text = "Hm... Aber du warst "+FindRussianDaysString(iTime)+" spät. Daher muss ich Ihre Bezahlung für die Arbeit kürzen. Laut Vertrag beträgt Ihre Strafe fünf Prozent des Gesamtbetrags für jeden Tag der Verspätung. Jetzt bitte, nehmen Sie Ihr "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+", und versuche in Zukunft, dich an den Vertrag zu halten.";
				link.l1 = "Nun, es ist zumindest etwas.";
				link.l1.go = "Postcureer_complete_1";
				break;
			}
			dialog.text = "Danke für deine Arbeit. Bitte, nimm deine Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
			link.l1 = "Danke!";
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
			dialog.text = "Und was sollen wir jetzt damit anfangen? Die Leute haben Gott weiß wie lange darauf gewartet, und du hast es erst heute gebracht. Gut, gib es mir - vielleicht kann man es noch gebrauchen. Und ich hoffe, du verstehst, dass jetzt überhaupt keine Bezahlung fällig ist.";
			link.l1 = "Natürlich, das tue ich. Nimm dein Bündel. Lebewohl.";
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
			dialog.text = "Also, du musst Schiffe eskortieren '"+pchar.questTemp.WPU.Escort.ShipName1+"' und '"+pchar.questTemp.WPU.Escort.ShipName2+"' zur Stadt von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", für "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))". Beide Schiffe müssen sicher und unversehrt ihr Ziel erreichen. Du wirst die Schiffe dem Beamten der örtlichen Hafenbehörde übergeben. Er wird auch derjenige sein, der dich für die Arbeit bezahlt.";
			link.l1 = "Alles scheint klar zu sein. Soll ich fortfahren?";
			link.l1.go = "escort_1";
			link.l2 = "Hmm... Aber ich gehe nicht in diese Richtung. Tut mir leid, aber ich muss ablehnen.";
			link.l2.go = "exit";
		break;
	
		case "escort_1":
			dialog.text = "Mach weiter. Zu diesem Zeitpunkt stehen diese Schiffe unter deinem Befehl.";
			link.l1 = "Ich setze die Segel, dann!";
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
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
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
				FantomMakeSmallSailor(sld, ShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
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
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
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
				dialog.text = "Hmm... Ich sehe nur ein Schiff in Ihrer Eskorte. Ist das korrekt?";
				link.l1 = "Ja, "+GetAddress_FormToNPC(NPChar)+". Ein weiteres wurde in einer Schlacht mit einem feindlichen Geschwader versenkt.";
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
					dialog.text = "In Ordnung, dann. Sie sollten Schiffe eskortieren und die Ladung liefern "+GetGoodsNameAlt(iGoods)+" in der Menge von "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+". Aber ich sehe, dass du nicht die gesamte Lieferung abgegeben hast - du bist "+FindRussianQtyString(sti(amount))+" kurz.";
					link.l1 = "Tausend Haie! Das müssen diese verfluchten Ratten sein! Aber mach dir keine Sorgen, "+GetAddress_FormToNPC(NPChar)+", Ich werde die fehlende Menge kaufen und die gesamte Charge abgeben.";
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
				dialog.text = "Hm... Aber du warst "+FindRussianDaysString(iTime)+" zu spät. Daher muss ich Ihre Bezahlung für die Arbeit kürzen. Gemäß dem Vertrag beträgt Ihre Strafe fünf Prozent des Gesamtbetrags für jeden Tag der Verspätung. Nun nehmen Sie bitte Ihr "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", und versuchen Sie in Zukunft, sich an den Vertrag zu halten.";
				link.l1 = "Nun, es ist zumindest etwas.";
				link.l1.go = "Escort_complete_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				dialog.text = "Also gut, dann. Du warst dazu bestimmt, Schiffe zu eskortieren und die Fracht zu liefern "+GetGoodsNameAlt(iGoods)+" in der Menge von "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty))+". Danke für deine Arbeit. Bitte, nimm deine Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			else
			{
				dialog.text = "Danke für Ihre Arbeit. Bitte, nehmen Sie Ihre Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
			}
			link.l1 = "Danke!";
			link.l1.go = "Escort_complete_1";
		}
		else
		{
			dialog.text = "Ich sehe dein Schiff nicht im Hafen. Leg ab und komm dann wieder zu mir - dann werden wir reden.";
			link.l1 = "In Ordnung, ich werde genau das tun.";
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
			dialog.text = "Also, du musst die Schiffe eskortieren '"+pchar.questTemp.WPU.Escort.ShipName1+"' und '"+pchar.questTemp.WPU.Escort.ShipName2+"' zur Stadt von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)+", für "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+". Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+"\nAlso auf Ihrem Schiff, lege ich die Last von "+GetGoodsNameAlt(iGoods)+" in Höhe von "+FindRussianQtyString(iGoodsQty)+". Bezahlung für die Lieferung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+".";
			link.l1 = "Alles scheint klar zu sein. Soll ich fortfahren?";
			link.l1.go = "escort_bonus_1";
			link.l2 = "Hmm... Aber ich gehe nicht in diese Richtung. Tut mir leid, aber ich muss ablehnen.";
			link.l2.go = "exit";
		break;
	
		case "escort_bonus_1":
			dialog.text = "Ausgezeichnet! Übernehmen Sie das Kommando über das Geschwader.";
			link.l1 = "Ich setze die Segel, dann!";
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
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
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
			dialog.text = "Unglaublich! Und wozu brauchten wir dich? Wie konntest du das nur zulassen?! Ich hoffe, du verstehst, dass eine Belohnung nun ausgeschlossen ist.";
			link.l1 = "Natürlich, ich tue... Nun, beste Grüße.";
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
					dialog.text = "Unglaublich! Und wofür brauchten wir dich? Wie konntest du das zulassen?! Ich hoffe, du verstehst, dass eine Belohnung für die Eskorte nun ausgeschlossen ist... Nicht nur das, sondern dir fehlt auch Fracht - "+FindRussianQtyString(sti(amount))+"\nIm Allgemeinen bezahle ich Ihnen nur für den Frachttransport von Waren, die in akzeptablem Zustand geliefert wurden, abzüglich des Wertes der fehlenden Artikel. Holen Sie sich Ihre "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" und du kannst gehen, wohin du willst.";
					link.l1 = "Nun, es ist zumindest etwas.";
					link.l1.go = "EscortBonus_complete_fail_1";
					break;
				}
				if (amount > 100)
				{
					dialog.text = "Unglaublich! Und wofür haben wir dich gebraucht? Wie konntest du das zulassen?! Ich hoffe, du verstehst, dass eine Belohnung für die Eskorte jetzt ausgeschlossen ist... Nicht nur das, du hast auch einen riesigen Mangel an Ladung.\nIch habe keine Zeit, darauf zu warten, dass du die fehlenden Waren beschaffst. Also musst du die Kosten vollständig ausgleichen - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+". Was die Ladung betrifft, kannst du sie behalten.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Also gut, reg dich nicht zu sehr auf. Hier ist dein Geld.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Habt ihr alle den Verstand verloren? Das ist buchstäbliche Erpressung! Ich werde euch nichts geben!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Unglaublich! Und wofür haben wir dich gebraucht? Wie konntest du das zulassen?! Ich hoffe, du verstehst, dass jegliche Belohnung für die Eskorte nun außer Frage steht. \nIm Allgemeinen werde ich nur für die Fracht für Waren bezahlen, die du mitgenommen hast. Hol dir deine "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+" und du kannst gehen, wohin du willst.";
				link.l1 = "Nun, es ist zumindest etwas.";
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
					dialog.text = "Unglaublich! Und wofür haben wir dich gebraucht? Wie konntest du das zulassen?! Ich hoffe, du verstehst, dass eine Belohnung für die Eskorte nun ausgeschlossen ist... Du hast ein Schiff verloren, du bist angekommen "+FindRussianDaysString(iTime)+" spät, und dazu fehlt auch noch Fracht - "+FindRussianQtyString(sti(amount))+"\nIch habe keine Zeit zu warten, bis du die fehlenden Waren beschafft hast. Also musst du die Kosten vollständig kompensieren "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+". Was die Ladung betrifft, kannst du sie behalten.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "In Ordnung, reg dich nicht zu sehr auf. Hier ist dein Geld.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Habt ihr alle den Verstand verloren? Dies ist buchstäbliche Erpressung! Ich gebe euch nichts!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Unglaublich! Und wofür haben wir dich gebraucht? Wie konntest du das zulassen?! Ich hoffe, du verstehst, dass eine Belohnung für die Eskorte jetzt ausgeschlossen ist... Außerdem bist du angekommen "+FindRussianDaysString(iTime)+" zu spät.\nDaher musste ich die Zahlung für die Fracht reduzieren. Nach dem Vertrag beträgt die Strafe 10 Prozent des ursprünglichen Betrags für jeden Tag der Verspätung. Nun, nimm dein "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+", und du kannst gehen.";
				link.l1 = "Nun, es ist zumindest etwas.";
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
			dialog.text = "Oh, ich verstehe... Nun, in diesem Fall solltest du dein Gesicht nie wieder bei irgendeiner Hafenbehörde zeigen "+NationNameGenitive(sti(pchar.questTemp.WPU.Escort.Nation))+"! Verschwinde!";
			link.l1 = "Ich habe sicherlich nicht viel verpasst...";
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
			dialog.text = "Das ist sehr, sehr schlecht! Wofür haben wir dich eingestellt, kannst du mir das sagen? Um die Schiffe zu bewachen? Oder nur um herumzuhängen?";
			link.l1 = "Ich verstehe. Der Feind war einfach zu stark, und... aber was bringt es zu streiten - was passiert ist, ist passiert. Aber die Ladung - die Ladung ist noch intakt! Also lasst uns das klären.";
			link.l1.go = "Escort_fail_complete";
		break;
	
		case "Escort_fail_complete":
			iFrahtGoods = makeint(pchar.questTemp.WPU.Escort.Goods);
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (amount > 0)
			{
				dialog.text = "Lass uns sehen, dann. Du solltest eine Ladung liefern von "+GetGoodsNameAlt(iFrahtGoods)+" in der Menge von "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+". Aber ich sehe, dass du nicht die gesamte Lieferung geliefert hast - du bist "+FindRussianQtyString(sti(amount))+" kurz.";
				link.l1 = "Tausend Haie! Es müssen diese verfluchten Ratten sein! Aber mach dir keine Sorgen, "+GetAddress_FormToNPC(NPChar)+", ich werde die fehlende Menge kaufen und die gesamte Partie abliefern.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Lass uns sehen. Du solltest eine Ladung liefern von "+GetGoodsNameAlt(iFrahtGoods)+" in Höhe von "+FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty)+". Korrekt?";
			link.l1 = "Absolut richtig, "+GetAddress_FormToNPC(NPChar)+".";
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
				dialog.text = "Hmm... Nicht nur, dass du die dir anvertrauten Schiffe verloren hast, sondern du warst auch noch zu spät dran "+FindRussianDaysString(iTime)+". Also musste ich die Bezahlung für die Fracht kürzen. Da du nicht in der Lage warst, die Schiffe zu retten, habe ich die Bezahlung für die Fracht halbiert, und das ist das Meiste, was ich dir anbieten kann.\nZusätzlich beträgt die Strafe laut Vertrag 10 Prozent des ursprünglichen Betrags für jeden Verzögerungstag. Nun, nimm dein "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+", und weg bist du.";
				link.l1 = "Nun, es ist zumindest etwas.";
				link.l1.go = "Escort_fail_complete_2";
				break;
			}
			dialog.text = "Nun, obwohl ich äußerst verärgert bin, dass du die dir anvertrauten Schiffe nicht beschützen konntest, hast du zumindest die Ware geliefert. Da du die Schiffe nicht retten konntest, habe ich die Bezahlung für die Fracht halbiert, und das ist das meiste, was ich dir anbieten kann. Nun, nimm deine Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+" und du kannst gehen, wohin du willst.";
			link.l1 = "Nun, es ist zumindest etwas.";
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
					dialog.text = "Sie müssen eine dringende offizielle Depesche an den Gouverneur der Stadt "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" nicht später als "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Sei sehr vorsichtig - unsere Feinde könnten auch nach dieser Depesche suchen. Bezahlung für die Lieferung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Ich stimme zu!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Nein, ich glaube, ich verzichte.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_Mayor";//ИД губера
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == "Villemstad_Mayor") pchar.questTemp.WPU.Postcureer.TargetPortmanID = "hol_guber"; // фикс Матиаса Бека #717
					pchar.questTemp.WPU.Current.Add = "a dispatch for the governor";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp1";//описание
				break;
			
				case 1:
					dialog.text = "Sie müssen diese Papiere an den Ladenbesitzer liefern von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" nicht später als "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Dies ist die neueste Zusammenfassung der Preise in Geschäften im ganzen Archipel - ein wertvolles Handelsdokument. Vorsicht sollte geboten sein - Konkurrenten könnten eine Jagd arrangieren. Bezahlung für die Lieferung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Ich stimme zu!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Nein, ich glaube, ich verzichte.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_trader";//ИД торговца
//					pchar.questTemp.WPU.Current.Add = "сводку цен для хозяина магазина";
					pchar.questTemp.WPU.Current.Add = "a price list for the store owner";     // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp2";//описание
				break;
			
				case 2:
					dialog.text = "Sie müssen diesen Bündel von Dokumenten zum Wucherer in der Stadt liefern "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" nicht später als "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Es handelt sich um sehr wichtige Informationen über Wechselkurse und Aktienkurse. Seien Sie sehr vorsichtig - einige zwielichtige Figuren sind bereits daran interessiert, dieses Paket zu bekommen. Bezahlung für die Lieferung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Ich stimme zu!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Nein, ich glaube, ich werde passen.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_usurer";//ИД ростовщика
					pchar.questTemp.WPU.Current.Add = "a packet of information for the moneylender";   // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp3";//описание
				break;
			
				case 3:
					dialog.text = "Du solltest dieses Bündel dem Dockmeister in der Stadt übergeben "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" nicht später als "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Es enthält Baupläne für die neue "+RandPhraseSimple(LinkRandPhrase("Brigg","Korvette","Fregatte"),LinkRandPhrase("Flöte","Pinasse","Galeone"))+", mit einzigartigen technologischen Entwürfen. Ich hoffe, Sie verstehen, dass es andere... interessierte Parteien gibt, also müssen Sie diskret handeln. Zahlung für die Lieferung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Ich stimme zu!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Nein, ich denke, ich werde passen.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_shipyarder";//ИД верфиста
					pchar.questTemp.WPU.Current.Add = "the draft of a new ship for the owner of the shipyard";
					pchar.questTemp.WPU.Current.Item = "ShipyardsMap";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_ShipyardsMap_PortmanLevelUp4";//описание
				break;
			}
		break;
	
		case "Postcureer_LevelUp_Go":
			dialog.text = "Dann nimm die Dokumente und stich in See. Viel Glück... und möge der Allmächtige über dich wachen.";
			link.l1 = "Danke!";
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
			dialog.text = "Schade, wirklich ... Tatsächlich werden Angebote dieser Art normalerweise nicht aufgeworfen. Aber es ist trotzdem Ihre Entscheidung.";
			link.l1 = "Ja, das ist mein Ruf, "+GetAddress_FormToNPC(NPChar)+".";
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
					TraderHunterOnMap(false);
				break;
		
				case 1://создание скоростного перехватчика на глобалке
					EnemyNationHunterOnMap(true);
				break;
		
				case 2://запуск ДУ на глобалке и в порту прибытия
					TraderHunterOnMap(false);
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
			dialog.text = "Verdammt! Also haben sie dich doch verfolgt. Schade, dass du kein Soldat bist, Kapitän - in diesem Fall hätten die Dinge anders ausgehen können... Wie sahen sie aus?";
			link.l1 = "Zwei kräftige, stämmige Männer in Schwarz, mit Halbmasken auf ihren Gesichtern, bewaffnet mit Hellebarden und doppelläufigen Gewehren...";
			link.l1.go = "Postcureer_complete_fail_1";
		break;

		case "Postcureer_complete_fail_1":
			dialog.text = "Ich werde sofort den Gouverneur benachrichtigen, um nach ihnen zu suchen. Gut, wir sehen uns, "+GetAddress_Form(NPChar)+". Wiederum ist es schade, dass du kein Soldat bist...";
			link.l1 = "Ich bin wirklich leid, "+GetAddress_FormToNPC(NPChar)+", für das, was passiert ist. Nun, auf Wiedersehen.";
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
				dialog.text = "Die Nachfrage nach einer bestimmten Ware hat in unserer Kolonie kürzlich dramatisch zugenommen. Die lokalen Läden haben es nicht mehr auf Lager. Daher möchte ich, dass du mir mit "+GetGoodsNameAlt(iGoods)+" in der Menge von "+FindRussianQtyString(iGoodsQty)+", und ich bin bereit, das Doppelte zu zahlen - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" pro Artikel. Das wird sich auf "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, und versuche, die Frist von einem Monat einzuhalten - ich kann nicht länger auf die Waren warten.";
				link.l1 = "In Ordnung, ich werde diese Mission annehmen.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Es tut mir leid, Sie zu enttäuschen, aber ich kann es im Moment nicht tun.";
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
				dialog.text = "Die Nachfrage nach einer bestimmten Ware hat in unserer Kolonie kürzlich dramatisch zugenommen. Die örtlichen Geschäfte haben sie nicht mehr auf Lager. Daher möchte ich, dass Sie mir liefern "+GetGoodsNameAlt(iGoods)+" in Höhe von "+FindRussianQtyString(iGoodsQty)+", und ich bin bereit, das Doppelte zu zahlen - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" pro Artikel. Das wird sich auf "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, und versuche, die Frist von einem Monat einzuhalten - ich kann nicht länger auf die Waren warten.";
				link.l1 = "In Ordnung, ich werde diese Mission annehmen.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Es tut mir leid, Sie zu enttäuschen, aber ich kann es in diesem Moment nicht tun.";
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
				dialog.text = "Das Arsenal unserer Kolonie mangelt es drastisch an "+GetGoodsNameAlt(iGoods)+". Die örtlichen Geschäfte haben es nicht mehr vorrätig. Daher möchte ich, dass du mir mit "+GetGoodsNameAlt(iGoods)+" in der Menge von "+FindRussianQtyString(iGoodsQty)+", und ich bin bereit, das Dreifache zu zahlen - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" pro Artikel. Das wird sich auf "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, und versuche, die Frist von einem Monat einzuhalten - ich kann nicht länger auf die Waren warten.";
				link.l1 = "In Ordnung, ich nehme diese Mission an.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Es tut mir leid, Sie zu enttäuschen, aber ich kann es im Moment nicht tun.";
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
				dialog.text = "Nach dem jüngsten Fieberausbruch in unserer Kolonie fehlen uns medizinische Vorräte - und in den Läden ist nichts mehr übrig. Der Gouverneur fürchtet um die Sicherheit der Stadtbewohner. Daher möchte ich Sie bitten, mir zu liefern "+GetGoodsNameAlt(iGoods)+" in Höhe von "+FindRussianQtyString(iGoodsQty)+", und ich bin bereit, das Dreifache zu zahlen - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" pro Packung. Das wird sich belaufen auf "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, und versuche, die Frist von einem Monat einzuhalten - ich kann nicht länger auf die Waren warten.";
				link.l1 = "In Ordnung, ich werde diese Mission annehmen.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Es tut mir leid, Sie zu enttäuschen, aber ich kann es in diesem Moment nicht tun.";
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
				dialog.text = "Nach einer schlechten Ernte ist unsere Kolonie ständig auf importierte Lebensmittel angewiesen. Derzeit sind unsere Vorräte fast aufgebraucht und die Regale der Geschäfte sind schon vor einiger Zeit geleert worden. Ich möchte Sie bitten, mir zu liefern "+GetGoodsNameAlt(iGoods)+" in der Menge von "+FindRussianQtyString(iGoodsQty)+", und ich bin bereit, das Doppelte zu zahlen - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice))+" pro Packung. Das wird sich belaufen auf "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+". Oh, und versuche, die Frist von einem Monat einzuhalten - ich kann nicht länger auf die Ware warten.";
				link.l1 = "In Ordnung, ich werde diese Mission annehmen.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Es tut mir leid, Sie zu enttäuschen, aber ich kann es in diesem Moment nicht tun.";
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
		dialog.text = "Ausgezeichnet! Ich bin sehr froh, dass du zugestimmt hast. Ich hoffe, dich bald wieder zu sehen.";
		link.l1 = "Natürlich, "+GetAddress_FormToNPC(NPChar)+".";
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
			dialog.text = "Machst du Witze? Du hast nicht die Menge an Waren, die ich bestellt habe!";
			link.l1 = "Es tut mir leid, mein Fehler...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Gut, du solltest eine Ladung liefern von "+GetGoodsNameAlt(iGoods)+" in Höhe von "+FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty)+". Ausgezeichnet, vielen Dank. Hier ist Ihre Bezahlung - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Freut mich, Geschäfte mit Ihnen zu machen, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "Fraht_completeLevelUp_1";
		}
	}
	else
	{
		dialog.text = "Ich sehe dein Schiff nicht im Hafen. Halte dich fern und komm dann wieder zu mir - dann werden wir reden.";
		link.l1 = "In Ordnung, das werde ich tun.";
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
				dialog.text = "Diese Katastrophe ereignete sich vor zehn Tagen... ein Karawanenkonvoi von Handelsschiffen, der auf dem Weg zu unserer Kolonie war, wurde von Piraten angegriffen. Ein heftiger Sturm zwang die Piraten zum Rückzug, aber die Handelsschiffe wurden verstreut und verloren den Kontakt zueinander. Schließlich erreichten alle Schiffe verschiedene Häfen, außer einem. \n"+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' verschwand und ihr Schicksal bleibt unbekannt. Vermutlich kann sie in der Nähe der unbewohnten Insel gefunden werden "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+". Ich bitte Sie, dorthin zu gehen, herauszufinden, was mit dem verlorenen Schiff passiert ist und, wenn sie überlebt hat, sie zu unserem Hafen zu bringen. Wir werden Ihre Entschädigung entscheiden, nachdem die Arbeit erledigt ist, aber ich versichere Ihnen, es wird sich lohnen.";
				link.l1 = "Natürlich, ich stimme zu!";
				link.l1.go = "Escort_LevelUp_1";
				link.l2 = "Es tut mir leid, aber diese Arbeit passt nicht zu mir. Ich fürchte, ich werde passen.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 1://защитить конвой вблизи текущего острова от пиратов
				pchar.questTemp.WPU.Current.TargetIslandID = Islands[GetCharacterCurrentIsland(PChar)].id;//текущий остров
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				dialog.text = "Eine Handelskarawane sollte in unserer Kolonie eintreffen, aber kurz vor dem Einlaufen in den Hafen wurde sie von Piraten angegriffen. Die Schlacht findet gerade jetzt statt. Sie liegt außerhalb der Reichweite der Fortkanonen und ich habe im Moment keine Eskortschiffe zur Verfügung, also kann ich den armen Händlern keine Hilfe anbieten. Du bist ein mutiger Kapitän, deshalb bitte ich dich einzugreifen und den Händlern zu helfen, den Angriff abzuwehren! Wirst du das tun?";
				link.l1 = "Natürlich! Es ist eine Frage der Ehre!";
				link.l1.go = "Escort_LevelUp_2";
				link.l2 = "Es tut mir leid, aber diese Arbeit ist nichts für mich. Ich fürchte, ich werde passen.";
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
				dialog.text = "Ein Schiff mit Waffen und Munition, das unsere Kolonie bestellt hat, ist kürzlich in der Kolonie angekommen "+XI_ConvertString(pchar.questTemp.WPU.Escort.City)+". Ihr Eskortschiff hat das Riff getroffen, wurde schwer beschädigt und wird so schnell nicht den Hafen verlassen können. Wir können es nicht riskieren, ein Handelsschiff mit einer solchen Ladung alleine zu schicken.\nWürden Sie zustimmen, sie zu unserer Kolonie zu eskortieren? Die Bezahlung für die Arbeit ist festgelegt auf "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
				link.l1 = "Natürlich, ich stimme zu!";
				link.l1.go = "Escort_LevelUp_0";
				link.l2 = "Es tut mir leid, aber diese Arbeit ist nichts für mich. Ich fürchte, ich werde passen.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
		}
	break;
	
	case "Escort_LevelUp_exit":
		dialog.text = "Schade, wirklich. Ich habe tatsächlich auf dich gezählt...";
		link.l1 = "Es tut mir auch leid. Nun, bis wir uns wiedersehen, "+GetAddress_FormToNPC(NPChar)+".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	break;
	
	case "Escort_LevelUp_0":
		dialog.text = "Ausgezeichnet! Ich wusste, dass ich auf dich zählen kann. Bitte versuche so schnell wie möglich zu sein. Ich denke "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+" wird ausreichen, um zu "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gen")+". Hier, nehmen Sie diese Beglaubigungen, die Ihre Identität bestätigen. Rückenwind, Kapitän!";
		link.l1 = "Keine Sorge, ich werde dich nicht enttäuschen.";
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
		dialog.text = "Endlich! Dieses Schiff war lange genug ein Dorn im Auge. Übernehmen Sie dann das Kommando. Der Name des Schiffes ist "+pchar.questTemp.WPU.Escort.ShipName+", und ihr Kapitän wird sofort über deine Ankunft informiert.";
		link.l1 = "Sag ihm, er soll sein Schiff segelfertig machen - Ich werde bei der ersten Gelegenheit aufbrechen.";
		link.l1.go = "Escort_LUGo_01";
	}
	else
	{
		dialog.text = "Ich sehe dein Schiff nicht im Hafen. Lege für jetzt ab und komm später wieder zu mir - dann werden wir reden.";
		link.l1 = "Ich werde genau das tun.";
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
		dialog.text = "Ausgezeichnet! Wieder einmal hast du bewiesen, dass man sich auf dich verlassen kann. Vielen Dank für die gut gemachte Arbeit. Bitte, nimm deine Bezahlung entgegen - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+". Und vergiss nicht, mich ab und zu zu besuchen - für einen Kapitän wie dich gibt es immer ein oder zwei Aufträge.";
		link.l1 = "Schön, das zu hören, "+GetAddress_FormToNPC(NPChar)+"! Natürlich wird unsere Zusammenarbeit fortgesetzt. Herzliche Grüße!";
		link.l1.go = "Escort_LUGo_complete_1";
	}
	else
	{
		dialog.text = "Ich sehe dein Schiff nicht im Hafen. Leg dich für jetzt hin und komm später wieder zu mir - dann werden wir reden.";
		link.l1 = "In Ordnung, ich werde genau das tun.";
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
		dialog.text = "Dann wünsche ich Ihnen eine sichere Reise. Und bitte, zögern Sie nicht mit Ihrer Suche! Die Besatzung dieses Schiffes könnte sofortige Hilfe benötigen.";
		link.l1 = "Hab's verstanden. Ich werde heute in See stechen!";
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
		dialog.text = "Ja, ich wurde bereits benachrichtigt. Hervorragende Arbeit, "+GetAddress_Form(NPChar)+"! Du hast einmal mehr bewiesen, dass ich mich auf dich verlassen kann. Nimm deine Belohnung - 30.000 Pesos.\nDenk daran, mich von Zeit zu Zeit zu besuchen - Leute wie du sind unbezahlbar und ich werde immer einen passenden Job für dich finden.";
		link.l1 = "Schön, das zu hören, "+GetAddress_FormToNPC(NPChar)+"! Natürlich werden wir weiterhin zusammenarbeiten. Alles Gute!";
		link.l1.go = "Escort_LU1WM_complete_1";
	}
	else
	{
		dialog.text = "Ich sehe dein Schiff nicht im Hafen. Bleib vorerst fern und komm später wieder zu mir - dann werden wir reden.";
		link.l1 = "In Ordnung, ich werde genau das tun.";
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
		dialog.text = "Ja, er hat mir bereits von der Schlacht mit den Piraten erzählt und wie heldenhaft du sein Schiff verteidigt hast. Hervorragende Arbeit, "+GetAddress_Form(NPChar)+"! Du hast einmal mehr bewiesen, dass ich mich auf dich verlassen kann. Hol dir deine Belohnung - 50.000 Pesos.\nVergiss nicht, mich ab und zu zu besuchen - Leute wie du sind unbezahlbar und ich werde immer eine passende Arbeit für dich finden.";
		link.l1 = "Schön, das zu hören, "+GetAddress_FormToNPC(NPChar)+"! Natürlich wird unsere Zusammenarbeit fortgesetzt. Beste Grüße!";
		link.l1.go = "Escort_LU1VSP_complete_1";
	}
	else
	{
		dialog.text = "Ich sehe Ihr Schiff nicht im Hafen. Halt dich für jetzt fern und komm später wieder zu mir - dann werden wir reden.";
		link.l1 = "In Ordnung, ich werde genau das tun.";
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
		dialog.text = "Welch tragisches Ende... Gott möge ihre Seelen ruhen lassen.";
		link.l1 = "Ich habe alles getan, was ich konnte, "+GetAddress_FormToNPC(NPChar)+". Der Sturm verschlimmerte die Situation noch weiter.";
		link.l1.go = "Escort_LU1VSP_completeSink_1";
	break;
	
	case "Escort_LU1VSP_completeSink_1":
		dialog.text = "Ich glaube doch, "+GetAddress_Form(NPChar)+", dass Sie alles unternommen haben, um das Schiff und die unglücklichen Matrosen zu retten. Aber leider... Nun, bitte nehmen Sie Ihre Belohnung - 10000 Pesos - und danke für Ihren Dienst.";
		link.l1 = "Nichts, wofür du mir danken müsstest, "+GetAddress_FormToNPC(NPChar)+". Es tut mir wirklich leid. Nun, auf Wiedersehen.";
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
		dialog.text = "Ja, er hat mir schon von dir erzählt, wie du gegen die rotäugigen Heiden gekämpft und dann ein Piratenschiff bekämpft hast - wie ein wahrer Held. Hervorragende Arbeit, "+GetAddress_Form(NPChar)+"! Sie haben sich einmal mehr als die Person bewiesen, auf die ich mich verlassen kann.\nHolen Sie sich Ihre Belohnung - 40.000 Pesos. Denken Sie daran, mich ab und zu zu besuchen - Leute wie Sie sind unbezahlbar und ich werde immer eine passende Arbeit für Sie finden.";
		link.l1 = "Schön, das zu hören, "+GetAddress_FormToNPC(NPChar)+"! Natürlich wird unsere Zusammenarbeit fortgesetzt. Beste Grüße!";
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
		dialog.text = "Ich wusste, dass ich auf dich zählen kann. Viel Glück dir, Kapitän! Die ganze Kolonie wünscht dir den Sieg!";
		link.l1 = "Ich werde versuchen, Ihren Erwartungen gerecht zu werden. Ich werde jetzt in See stechen und möge Gott uns helfen!";
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
				dialog.text = "Ja, die ganze Stadt hat deinen Kampf beobachtet. Die armen Händler, ich bedauere sie wirklich. Nun, zumindest hast du es geschafft, ein Schiff zu retten, daher hast du deine Belohnung von 10000 Pesos wohl verdient. Bitte, nimm es an - und danke für deine Hilfe.";
				link.l1 = "Nichts, wofür du mir danken müsstest... Es ist bedauerlich, dass ich diesen Kampf nicht entschieden gewonnen habe, aber ich habe alles getan, was ich konnte. Leb wohl, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 2:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 25000;
				dialog.text = "Ja, die ganze Stadt hat den Kampf beobachtet, den du geführt hast - und das hast du sehr geschickt gemacht, muss ich sagen. Dieser arme Händler, ich fühle mich so leid für ihn... Aber wenn nicht für dich, hätte keiner von ihnen lebend entkommen, also ist deine Belohnung von 25000 Pesos sehr wohl verdient. Bitte nimm es an - und danke für deine Hilfe.";
				link.l1 = "Nun, danke für die schmeichelhafte Beurteilung meiner Taten, aber ich glaube nicht, dass das meine beste Schlacht war - ich habe immer noch ein Schiff verloren. Nun, Schicksal ist Schicksal, und da kann man nichts machen. Auf Wiedersehen, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 3:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 50000;
				dialog.text = "Ja, die ganze Stadt hat den Kampf beobachtet, den du geführt hast - du warst absolut großartig! Du hast das gesamte Geschwader dieser dreckigen Piraten einfach zerstört! Jetzt haben sie ihre Lektion gelernt - schade, dass es ihnen nicht mehr helfen wird. Deine Belohnung beträgt 50000 Pesos - bitte nimm sie an.";
				link.l1 = "Danke für die schmeichelhafte Beurteilung meiner Taten! Es ist immer ein Vergnügen zu helfen. Und jetzt, "+GetAddress_FormToNPC(NPChar)+", bitte erlauben Sie mir, mich zu verabschieden.";
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
			dialog.text = "Hmm, das ist schlecht. In diesem Fall kommt eine weitere Arbeit für mich nicht in Frage.";
			link.l1 = "Verstanden. Hier ist, was ich sagen wollte...";
			link.l1.go = "node_2";
		break;
		
		//сгоревшее судно
		case "BurntShip2":
			dialog.text = "Schade, Kapitän... Es ist schade, dass Sie nicht bereit sind, mir zu helfen.";
			link.l1 = "Das ist keine Frage meines Willens, mein guter Mann. Du musst verstehen. Lebewohl.";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		case "BurntShip4":
			dialog.text = "Was ist los mit Ihnen, Kapitän?! Schämen Sie sich nicht?! Wie konnten Sie nur?! Ich kenne meinen Kram, ich bin seit vielen Jahren im Dienst. Es gibt Versicherungsverträge, und die Versicherungsgesellschaft ist bereit zu zahlen, und ich versichere Ihnen, dass die Versicherungssumme ganz anständig ist.";
			link.l1 = "Was ist Ihr Problem, Herr? Ein Pulverkammer ist explodiert, es gab Verluste, und jetzt müssen Sie wegen Ihrer Nachlässigkeit vor Gericht stehen?";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "Nein! Natürlich nicht! Gott bewahre meine Seele, sonst würde ich meinen Kopf verlieren. Der Laderaum war absolut leer, danke Gott, der Heiligen Jungfrau Maria!\n"+"Und das Problem ist, dass das Schiff gehört... oder besser gesagt, gehörte Herrn. "+sCapitainId+", bekannt in allen Karibik. Und sie wurde in Europa auf Sonderbestellung gebaut, mit außergewöhnlichen Eigenschaften. "+"Und dieser Schiffseigner war viel zu stolz und prahlte links und rechts, eine Art Dummkopf, Gott verzeihe mir... Was soll ich ihm jetzt sagen? Ich sollte mich besser umbringen, ich schwöre...";
			link.l1 = "Oh, jetzt sehe ich tatsächlich, was das Problem ist. Und was war so besonders an dem Schiff? Welche ungewöhnlichen Merkmale hatte sie, auf die ihr Besitzer so stolz war?";
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
			link.l1 = "Und was sagen die Leute am Hafen? Ist es wirklich unmöglich, hier ein weiteres zu bauen?";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "Niemand kann. Ich bin sogar zur nahegelegenen Insel gegangen, um die Leute zu fragen. Sie sagten, dass es auf der Isla Tesoro einen bemerkenswerten Meister gibt, der fast alles im Schiffbau erreichen kann. Aber die verdammte Isla Tesoro ist so verdammt weit weg. Alles, was mir bleibt, ist auf die Hilfe freier Kapitäne wie Sie zu hoffen. Vielleicht finden Sie zufällig ein solches Schiff für mich. Und ich kümmere mich um den Rest\n"+"Ich werde Ihnen großzügig danken, und die Versicherungsgesellschaft wird dasselbe tun. Die Angelegenheit ist ungewöhnlich, wissen Sie. Wer würde schon so einen mächtigen Mann verärgern wollen?";
			link.l1 = "Ja, das wird nicht einfach sein. Und wie viel Zeit habe ich?";
			link.l1.go = "BurntShip8";
			link.l2 = "Nein, Kumpel, ich kann mich nicht in solche Angelegenheiten einmischen. Ganz zu schweigen davon, dass es keine Garantien gibt, dass ein Schiff mit solchen Parametern überhaupt existiert. Es tut mir leid...";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "Dank Gott, es ist noch Zeit. Der Besitzer ist nach Europa gesegelt und wird nicht früher als in einem halben Jahr zurück sein.";
			link.l1 = "Nun, ich denke, ich werde es schaffen. Ich bringe dir ein ähnliches Schiff. Aber behalte das im Hinterkopf - wenn du dich entscheidest, zu knauserig zu sein, werde ich es direkt vor deinen Augen verbrennen!";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "Was wollen Sie andeuten, Kapitän? Sicherlich, ich verstehe, dass Sie Zeit brauchen - es geht nicht darum, eine beliebige Wanne in der nächstgelegenen Pfütze zu finden... Bringen Sie uns einfach das Schiff und wir werden unser Bestes tun, darauf können Sie sich verlassen...";
			link.l1 = "Ich hoffe es... Nun, warte auf mich und auf die guten Nachrichten. Lebewohl.";
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
			dialog.text = "Worüber wolltest du sprechen?";
			link.l1 = "Und wo ist der frühere Hafenmeister, Herr "+NPChar.Quest.BurntShip.LastPortmanName+"? Ich habe Geschäfte mit ihm.";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "Er ist nicht mehr hier. Stell dir vor - er hat ein Schiff, das einer bekannten Person gehörte, niedergebrannt und das Versicherungsgeld eingesteckt. Während die Behörden das alles klärten, trat er zurück und verschwand nach Europa. Ein ziemlicher Betrüger, nicht wahr?";
			link.l1 = "Ja, ich habe diese Geschichte gehört. Es tut mir leid, aber ich muss gehen.";
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
			dialog.text = "Worüber wollten Sie sprechen?";
			link.l1 = "Ich habe Ihnen ein ungewöhnliches Schiff gebracht, genau wie Sie es verlangt haben. Ich erwarte jetzt meine Belohnung.";
			link.l1.go = "BurntShip14";
			link.l2 = "Weißt du, "+GetFullName(NPChar)+", Ich habe immer noch kein einziges Schiff gefunden, das dem entspricht, was Sie brauchen. Ich denke, ich werde diesen Job aufgeben. Entschuldigung, wenn ich dich enttäuscht habe...";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "Schade, Kapitän... Es ist schade, dass Sie nicht bereit sind, mir zu helfen.";
			link.l1 = "Das ist nicht eine Frage meines Willens, mein guter Mann. Bitte verstehen Sie. Lebewohl.";
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
			dialog.text = "Oh, wirklich! Und wie heißt unser neues Schiff?";
			
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
			
			link.l99 = "Entschuldigung, ich komme später wieder.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Oh, Kapitän, ich bin so froh, dass Sie mich nicht im Stich gelassen haben! Was für ein "+GetSexPhrase("feiner junger Mann","feine junge Dame")+"Sie sind es, Sie haben buchstäblich mein Leben gerettet... Bitte, könnten Sie in ein paar Tagen vorbeikommen, um Ihr Geld abzuholen? Sie wissen, ich muss die Formalitäten mit der Versicherung klären... In der Zwischenzeit könnten Sie kleinere Reparaturen am Schiff vornehmen - Sie wissen, erneuern Sie die Segel, flicken Sie die Löcher, Kalfatern würde auch nicht schaden...";
			link.l99 = "Ich habe versprochen, dem Schiff etwas Schlimmes anzutun, wenn du versuchst, mich zu täuschen. Hast du das vergessen?";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "Nein, nein, natürlich nicht! Ich werde mein Wort halten, mach dir keine Sorgen. Siehst du, da ich wusste, dass es mehr Ausgaben für, sozusagen, die Tarnung des neuen Schiffes geben wird, habe ich das Versicherungsgeld, das ich für das alte Schiff bekommen habe, verzinst verliehen. Ich hoffe, du verstehst...";
			link.l1 = "Ich werde es viel besser verstehen, wenn das Geld in meiner Truhe liegt. Bis wir uns wiedersehen.";
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
			dialog.text = "Worüber wolltest du sprechen?";
			link.l1 = "Ich bin gekommen, um meine Belohnung abzuholen. Ich habe noch das Gefäß, das du brauchst.";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "Würdest du mich bitte an seinen Namen erinnern? Mein Gedächtnis ist nicht mehr das, was es einmal war - du weißt schon, all der Ärger...";
			
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
			
			link.l99 = "Entschuldigen Sie, ich komme später wieder.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 3;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "Ja, perfekt. Ich bin bereit, dir deine Belohnung zu übergeben, "+FindRussianMoneyString(cn)+". So hat die Versicherungsgesellschaft den Wert des verbrannten Schiffes bewertet. Die Versicherungssumme wird in Kreditkisten ausgezahlt - kein Bargeld, tut mir leid.";
			link.l1 = "Oh nein, diese Summe passt mir nicht. Ich bin sicher, dass dieses Schiff viel teurer ist.";
			link.l1.go = "BurntShip21";
			link.l2 = "Das ist richtig. Ich bin froh, dass ich Ihnen helfen konnte. Auf Wiedersehen.";
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
			dialog.text = "Was sagst du da, Kapitän?! Vertraue mir, ich weiß, wovon ich rede. Mit dem Geld könntest du zwei solche Schiffe kaufen!";
			link.l1 = "Ich denke, ich werde es behalten. Weißt du, es hat mir einfach gefallen... Auf Wiedersehen.";
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
				dialog.text = "Einer der Kapitäne hat sein Logbuch in meinem Büro vergessen. Was für ein Schussel! Ich brauche dich, um ihn einzuholen und es ihm zurückzugeben.";
				link.l1 = "Oh, das wird einfach sein... Ich nehme das!";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "Nein, das werde ich nicht in die Hand nehmen. Es ist tatsächlich sein eigenes Problem.";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "Ein Schiff wurde dort vom Liegeplatz gestohlen. Ich möchte, dass du das gestohlene Schiff suchst und es zurückbringst.";
				link.l1 = "Hmm, nun, ich bin bereit, die Untersuchung aufzunehmen.";
				link.l1.go = "SeekShip_1";
				link.l2 = "Es tut mir leid, aber ich beteilige mich nicht an der Suche nach gestohlenen Schiffen.";
				link.l2.go = "node_2";
			}
		break;
//-------------------------------- квест доставки судового журнала до рассеяного кэпа ---------------------
		case "PortmanQuest_1":
			dialog.text = "Ausgezeichnet, hier ist sein Logbuch... Du hast mir wirklich eine Last von der Seele genommen! Der Verlust eines Schiffslogs ist eine sehr üble Sache. Ich habe die Kapitäne immer bedauert...";
			link.l1 = "Nun, das ist wirklich etwas, worüber man sich Sorgen machen sollte! Jetzt erzähl mir mehr von diesem zerstreuten Kapitän.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "Ja, natürlich! Sein Name ist "+npchar.quest.PortmansJornal.capName+", er ist ein Kapitän von "+GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName+"Gen"))+" namens '"+npchar.quest.PortmansJornal.shipName+"'. Er hat vor nicht allzu langer Zeit die Segel gesetzt und ist nach "+XI_ConvertString("Colony"+npchar.quest.PortmansJornal.city+"Akk")+".";
			link.l1 = "Ich verstehe. Gut, ich werde ihn finden. Nun, was ist mit der Bezahlung?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName+" er selbst wird dich bezahlen, es liegt in seinem besten Interesse. Du konzentrierst dich einfach darauf, ihn so schnell wie möglich zu erreichen und alles wird gut sein.";
			link.l1 = "Ich verstehe. Nun, ich gehe dann...";
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
			dialog.text = "Ausgezeichnet! Wissen Sie, das gestohlene Schiff gehört einer einflussreichen Person, daher ist dies für mich sehr wichtig. Ich werde Sie für diese Arbeit großzügig belohnen...";
			link.l1 = "Ich verstehe. Erzähl mir mehr über das Schiff und die Umstände, unter denen es gestohlen wurde.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)+" mit dem Namen '"+npchar.quest.PortmansSeekShip.shipName+"' wurde in der Nacht gestohlen "+FindRussianDaysString(rand(5)+10)+" vor. Der Wachmann wurde ermordet.";
			link.l1 = "Hmm... Sie müssen mittlerweile weit weg sein. Die Spur ist nicht mehr frisch und das ist das Problem.";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "Wahr ist, aber ich sah trotzdem keinen Grund, sofort Alarm zu schlagen. Das Militärschiff hätte sie einholen können, aber es hätte das Schiff einfach in Stücke gesprengt - und das ist nicht gerade das, was ich brauche.";
			link.l1 = "Ich verstehe. Nun, ich werde meine Suche beginnen. Hoffentlich habe ich Glück.";
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
			dialog.text = "Schade - aber wir konnten kaum auf Erfolg hoffen.";
			link.l1 = "Ja, es ist zu lange her, seit das Schiff gestohlen wurde.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "Nun, danke für deine Hilfe trotzdem, auch wenn deine Bemühungen nicht so fruchtbar waren wie wir erhofft hatten.";
			link.l1 = "Ich habe alles getan, was ich konnte...";
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
				dialog.text = "Ausgezeichnet! Obwohl ich vermute, dass dies nicht genau das Schiff ist, das gestohlen wurde... Ach, wen kümmert's! Ich nehme es.";
				link.l1 = "Ja, tatsächlich...";
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
				dialog.text = "Ausgezeichnet! Du hast mir sehr geholfen. Ich kann mir nicht vorstellen, wie schwierig es war.";
				link.l1 = "Ja, in der Tat...";
				ChangeCharacterComplexReputation(pchar,"nobility", 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "Ich bin bereit, dir deine Belohnung zu zahlen. Sie besteht aus "+FindRussianMoneyString(makeint(sti(npchar.quest.chest)*15000))+" in Kisten. Leider kann ich Ihnen nicht mehr als das zahlen.";
			link.l1 = "Nun, das reicht. Danke und herzliche Grüße.";
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
				dialog.text = "Es gibt mehrere registrierte Kapitäne. Interessieren Sie sich für jemanden Bestimmten?";
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
				dialog.text = "Ich habe keine Kapitäne auf meiner Liste, die für Sie von Interesse sein könnten.";
				link.l1 = "Ich verstehe. Nun, danke für die Information.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Nun, lass uns mal sehen... A-ha! Da! ","Aha... A-ha! Da! ","In Ordnung, dann. ")+"Kapitän "+GetFullName(sld)+" "+arCapLocal.date+" verließ unser Hafen und segelte nach "+XI_ConvertString("Colony"+arCapLocal+"Konto")+".";
			link.l1 = "Danke. Ich möchte die Liste noch einmal überprüfen...";
			link.l1.go = "CapitainList";
			link.l2 = "Gut, das ist alles. Ich interessiere mich für keinen anderen Kapitän.";
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
			dialog.text = LinkRandPhrase("Nun, lass uns sehen... A-ha! Da! ","Ach-ha... A-ha! Da! ","In Ordnung, dann. ")+"Kapitän "+GetFullName(sld)+" "+arCapLocal.date+" verließ unseren Hafen und segelte zu "+XI_ConvertString("Colony"+arCapLocal+"Konto")+".";
			link.l1 = "Danke. Ich möchte die Liste noch einmal durchsehen...";
			link.l1.go = "CapitainList";
			link.l2 = "Gut, das ist alles. Ich bin an keinem anderen Kapitän interessiert.";
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
			dialog.text = LinkRandPhrase("Nun, lass uns sehen... A-ha! Da! ","Ah-ha... A-ha! Da! ","In Ordnung, dann. ")+"Kapitän "+GetFullName(sld)+" "+arCapLocal.date+" verließ unser Hafen und segelte zu "+XI_ConvertString("Colony"+arCapLocal+"Akz")+".";
			link.l1 = "Danke. Ich möchte die Liste noch einmal durchgehen...";
			link.l1.go = "CapitainList";
			link.l2 = "Gut, das ist alles. Ich interessiere mich für keinen anderen Kapitän.";
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
			dialog.text = LinkRandPhrase("Nun, lass uns sehen... A-ha! Da! ","Aha... Aha! Da! ","In Ordnung, dann. ")+"Kapitän "+GetFullName(sld)+" "+arCapLocal.date+" verließ unser Hafen und segelte nach "+XI_ConvertString("Colony"+arCapLocal+"Konto")+".";
			link.l1 = "Danke. Ich möchte die Liste noch einmal überprüfen...";
			link.l1.go = "CapitainList";
			link.l2 = "Gut, das ist alles. Ich bin an keinem anderen Kapitän interessiert.";
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
			dialog.text = LinkRandPhrase("Nun, lass uns mal sehen... A-ha! Da! ","Aha... A-ha! Da! ","In Ordnung, dann. ")+"Kapitän "+GetFullName(sld)+" "+arCapLocal.date+" verließ unser Hafen und segelte zu "+XI_ConvertString("Colony"+arCapLocal+"Konto")+".";
			link.l1 = "Danke. Ich würde gerne die Liste noch einmal durchgehen...";
			link.l1.go = "CapitainList";
			link.l2 = "Gut, das ist alles. Ich interessiere mich für keinen anderen Kapitän.";
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
			dialog.text = "Ich höre zu - welches Schiff, für welche Laufzeit?";
    		Link.l1 = "Lucas Rodenburg hat mich geschickt. Er sagte, dass ich mein Schiff hier kostenlos anlegen kann.";
    		Link.l1.go = "ShipStock_HWICHoll";
			DelLandQuestMark(npchar);
			break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoPortoffice" && !CheckAttribute(npchar, "quest.HWICEng"))
			{
			dialog.text = "Ich höre zu - welches Schiff, für welche Laufzeit?";
    		Link.l1 = "Richard Fleetwood hat mich geschickt. Er sagte, dass ich mein Flaggschiff hier für 10000 Pesos anlegen kann.";
    		Link.l1.go = "ShipStock_HWICEng";
			break;
			}
            if (sti(NPChar.Portman) >= 3 || CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip"))
			{
                dialog.text = "Nun, das ist korrekt. Aber leider kann ich Ihr Schiff im Moment nicht akzeptieren. Kein Dockplatz verfügbar.";
    			Link.l1 = "Das ist schade.";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "Und welches besondere Schiff wirst du hier lassen?";
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
	    			Link.l17 = "Macht nichts, danke.";
	    			Link.l17.go = "exit";
    			}
    			else
    			{
					dialog.text = "Hmm... Ich sehe keines deiner Schiffe.";
	    			Link.l1 = "Ich wollte nur über die Möglichkeit des Anlegens wissen.";
	    			Link.l1.go = "exit";
				}
			}
		break;

/*  //////////   hasert уже не надо но пусть висит ////////////////////////////////////
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Lass uns mal das Schiff anschauen.";
			Link.l1 = "Gut.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Nein, ich habe meine Meinung geändert.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Lassen wir uns das Schiff mal ansehen.";
			Link.l1 = "Gut.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Nein, ich habe meine Meinung geändert.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Lassen Sie uns mal das Schiff anschauen.";
			Link.l1 = "Gut.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Nein, ich habe meine Meinung geändert.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Lass uns mal das Schiff anschauen.";
			Link.l1 = "Gut.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Nein, ich habe meine Meinung geändert.";
			Link.l2.go = "exit";
		break;
*/		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (MOD_SKILL_ENEMY_RATE >= 6) NPChar.MoneyForShip = 5*GetPortManPriceExt(NPChar, chref); // для высокой сложности - 5x цена
			else NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName)+" '"+chref.Ship.Name+"', Klasse "+RealShips[sti(chref.Ship.Type)].Class+", Liegeplatz kostet "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+" pro Monat, Zahlung für einen Monat im Voraus.";
			Link.l1 = "Ja, das passt mir.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
			    Link.l1.go = "ShipStock_3";
			}
			else
			{
                Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = "Nein, ich habe meine Meinung geändert.";
			Link.l2.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "Und es wird mir auch passen, sobald du die erforderliche Menge gesammelt hast.";
			Link.l1 = "Ups... Ich komme später wieder.";
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

			dialog.text = "In Ordnung. Sie können Ihr Schiff jederzeit zurücknehmen, wenn Sie es benötigen.";
			Link.l1 = "Danke.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = "Welches bestimmte Schiff wirst du nehmen?";
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
	
	    			Link.l99 = "Nein, ich habe meine Meinung geändert.";
	    			Link.l99.go = "exit";
				}
				else
				{
	                dialog.text = "Haben Sie Platz für ein weiteres Schiff?";
	    			Link.l1 = "Ach, richtig. Danke.";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. Ich sehe Ihr Flaggschiff nicht im Hafen. Und Sie können Ihre Schiffe nur hier zurücknehmen.";
    			Link.l1 = "In Ordnung, ich komme später für sie.";
    			Link.l1.go = "exit";
			}
		break;

        case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
			if (CheckAttribute(chref, "quest.Mutiny.date")) {
				dialog.text = "Lass uns sehen... Dieses Schiff hat den Hafen verlassen um "+chref.quest.Mutiny.date+".";
				link.l1 = "Was meinst du mit 'links'? Sie muss hier sein, in den Docks!";
				link.l1.go = "ShipStockManMutiny";
				break;
			}
			// <--
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
			    dialog.Text = "Möchtest du dein Schiff abholen? Für die Anlegestelle schuldest du noch "+FindRussianMoneyString(sti(NPChar.MoneyForShip))+".";
			}
			else
			{
				dialog.Text = "Aufheben?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "Ja.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "Nein, ich habe meine Meinung geändert.";
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
			dialog.Text = "Welchem Ihrer Offiziere soll ich es geben?";
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
				dialog.text = "Ja, ja, ich weiß. Aber ich kann nur ein Schiff für das freie Anlegen nehmen. Also bitte, klären Sie die Dinge mit Ihrer Staffel und kommen Sie dann wieder.";
				link.l1 = "Gut, ich bringe nur das Flaggschiff.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Ja, ja, ich weiß. Auf Befehl von Mynheer Rodenburg nehmen wir Ihr Schiff zur Aufbewahrung auf und stellen für die gesamte Zeit, die Ihr Schiff hier bleibt, einen Wachoffizier zur Verfügung. Bitte unterschreiben Sie hier... und hier...";
				link.l1 = "In Ordnung... Ich verstehe, alle Formalitäten sind jetzt geregelt?";
				link.l1.go = "ShipStock_HWICHoll_1";	
			}
		break;
		
		case "ShipStock_HWICHoll_1":
			dialog.text = "Ja. Es besteht keine Notwendigkeit mehr, sich um Ihr Schiff zu kümmern - wir werden uns darum kümmern. Sie können zu Mynheer Rodenburg zurückkehren.";
			link.l1 = "Danke. Auf Wiedersehen.";
			link.l1.go = "exit";	
			npchar.quest.HWICHoll = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "ShipStock_HWICEng":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Ja, ja, ich weiß. Aber ich kann nur ein Schiff für das kostenlose Anlegen nehmen. Also bitte, klären Sie die Dinge mit Ihrer Staffel und kommen Sie dann wieder.";
				link.l1 = "In Ordnung, ich bringe nur das Flaggschiff.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Ja, natürlich. Hast du das Geld dabei?";
				if(makeint(Pchar.money) >= 10000)
				{
					link.l1 = "Sicher. Hier bitte.";
					link.l1.go = "ShipStock_HWICEng_1";	
				}
				else
				{
					link.l1 = "Nein. Ich bin gleich wieder da.";
					link.l1.go = "exit";	
				}
			}
		break;
		
		case "ShipStock_HWICEng_1":
			dialog.text = "In Ordnung. Wir werden uns um Ihr Schiff kümmern und für die gesamte Zeit, die Ihr Schiff hier bleibt, einen Wachoffizier bereitstellen.";
			link.l1 = "Danke!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			npchar.quest.HWICEng = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Fleetwood"), "questmarkmain");
		break;
		//<-- Голландский гамбит
		case "Escort_companion":
			dialog.text = "Brauchen Sie etwas, Käpt'n?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Escort_companion";
		break;
		
		// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
		case "ShipStockManMutiny":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			dialog.text = "Ihr Offizier "+GetFullName(chref)+" informiert"+NPCharSexPhrase(chref,"","")+" erzähl mir das "+NPCharSexPhrase(chref,"er","sie")+" musste auf Ihren Befehl hin zur See fahren. Ich habe nicht widersprochen "+NPCharSexPhrase(chref,"ihn","sie")+".";
			link.l1 = "Verdammt! Es gab keinen solchen Befehl! Hätte mein Schiff nicht dem Bastard anvertrauen sollen! Eh, was auch immer, ich kann sowieso nichts über meinen Verlust tun.";
			link.l1.go = "ShipStockManMutiny1";
			// вот тут можно микроквестик сделать
			//link.l2 = "Was für eine Überraschung... Hat "+NPCharSexPhrase(chref,"er","sie")+"Könnten Sie mir vielleicht sagen, wohin sie gegangen sind?";
			//link.l2.go = "ShipStockManMutiny2";
		break;
		
		case "ShipStockManMutiny1":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.lifeday = 0;

			dialog.text = "Es tut mir leid, "+GetAddress_Form(NPChar)+". Sie sollten vorsichtiger mit Ihren Untergebenen sein.";
			link.l1 = "Ich weiß, ich bin ein Idiot. Auf Wiedersehen, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
		break;
		// <--
		
		// уникальные корабли и легендарные капитаны -->
		case "UniqueShips":
			dialog.text = "Eindeutige Schiffe und die ihnen anvertrauten Personen können im Archipel nicht unbemerkt bleiben. Diese Information ist jedoch von erheblichem Wert und wird nicht leichtfertig gegeben.";
			if (sti(pchar.Money) >= 25000)
			{
				link.l1 = "Ich verstehe. Würde die Summe von 25000 Pesos ausreichen, um meine ernsthaften Absichten zu demonstrieren?";
				link.l1.go = "UniqueShips_2";
			}
			else
			{
				link.l1 = "In Ordnung, dann ein anderes Mal.";
				link.l1.go = "node_2";
			}
		break;
		
		case "UniqueShips_2":
			dialog.text = "Tatsächlich wäre das akzeptabel. An welchem speziellen Schiff sind Sie interessiert?";
			if (GetDLCenabled(DLC_APPID_4) && !CheckAttribute(pchar, "questTemp.SantaMisericordia_InfoPU") && CharacterIsAlive("SantaMisericordia_cap"))
			{
				link.l1 = "Galeone 'Heilige Barmherzigkeit'.";
				link.l1.go = "UniqueShips_SantaMisericordia";
			}
			if (GetDLCenabled(DLC_APPID_5) && !CheckAttribute(pchar, "questTemp.LadyBeth_InfoPU") && CharacterIsAlive("LadyBeth_cap"))
			{
				link.l2 = "Patrouillenschnau 'Lady Beth'.";
				link.l2.go = "UniqueShips_LadyBeth";
			}
			if (GetDLCenabled(DLC_APPID_6) && !CheckAttribute(pchar, "questTemp.Memento_InfoPU") && CharacterIsAlive("Memento_cap"))
			{
				link.l3 = "Brigg 'Memento'.";
				link.l3.go = "UniqueShips_Memento";
			}
			link.l99 = "Ich glaube, ich weiß genug.";
			link.l99.go = "node_2";
		break;
		
		case "UniqueShips_SantaMisericordia":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "1");
			pchar.questTemp.SantaMisericordia_InfoPU = true;
			dialog.text = "Heilige Barmherzigkeit wurde vom Escorial aus Europa gesandt, um die spanischen Kolonien zu überwachen. Ihr Kapitän, Don Alamida, ist ein bekannter Diener der spanischen Krone, ein rücksichtsloser Kämpfer gegen Korruption und Verbrechen und ein Eiferer des katholischen Glaubens. Heilige Barmherzigkeit kreuzt zwischen den Kolonien, beginnt und beendet ihre Reise in Havanna und konzentriert sich ausschließlich auf ihre Mission.\nIn jedem Hafen verbringt Alamida mehrere Tage, manchmal länger. Man sagt, dass er in diesen Zeiten sogar auf der Straße getroffen werden kann, aber die Einheimischen sind nicht besonders daran interessiert - in den Spaniern weckt der Señor nur Angst und Ehrfurcht.\nHeilige Barmherzigkeit hat eine erfahrene und loyale Crew, die von Alamida persönlich ausgewählt wurde. Jeder Seemann ist bereit, sein Vaterland und seinen Kapitän mit seinem Leben zu verteidigen. Man sagt, Don Fernando habe angeordnet, dass Heilige Barmherzigkeit nie erobert werden dürfe, und es gibt Gerüchte, dass die Besatzung bei unüberwindbaren Boarding-Quoten das Schiff lieber in die Tiefe schicken würde, als zu sehen, wie es geentert wird.";
			link.l1 = "Vielen Dank.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_LadyBeth":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "2");
			pchar.questTemp.LadyBeth_InfoPU = true;
			dialog.text = "'Lady Beth' ist eine wahre Schönheit. Ein Wunder britischer Marinekunst unter dem Kommando von Albert Blackwood, einem ehemaligen Offizier der Royal Navy. Nicht jeder schafft es, so spektakulär zu desertieren! Er verließ den Dienst, zerstörte eine glänzende Karriere und stahl ein Kriegsschiff - alles wegen der Schatzsuche!\nUnd es war nicht umsonst. Er hat schon so viel gefunden, dass er die Hälfte von Barbados kaufen könnte, aber ihm reicht das nicht. Wenn ihr ihm auf See begegnet - versucht gar nicht erst, ihn abzufangen\nZu gutes Schiff, und der Kapitän ist erfahren und vorsichtig. In letzter Zeit ist Blackwood oft auf den Kaimaninseln - gräbt dort Tag und Nacht, treibt die Leute bis zum Umfallen. Wenn ihr nachsehen wollt - nehmt mindestens 60 Mann und gute Schusswaffen... Vielleicht reicht selbst das nicht\nIch hoffe, ihr könnt schießen, denn mit ihm ist eine Kompanie ehemaliger Marineinfanteristen unter Colonel Fox desertiert. Profis, keine gewöhnlichen Halunken. Und greift ihn niemals in französischen Häfen an - dort hat er Schutz und Gönner, die an seinen Funden mitverdienen.";
			link.l1 = "Vielen Dank.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_Memento":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "3");
			pchar.questTemp.Memento_InfoPU = true;
			dialog.text = "Die 'Memento' – eine wahre Piratenlegende. Eine schwarze Brigg unter dem Kommando von Kapitän Mortimer Grim.\n"+
			"Grim jagt ausschließlich Sklavenhändler. Man sagt, er befreit Sklaven und rettet zum Tode Verurteilte, indem er sie mit hartem Gold freikauft. Eine edle Sache – wenn man den Rest nicht kennt.\n"+
			"Wenn ihr keine menschliche Fracht transportiert, wird Grim euch nicht anrühren. Er ist sonderbar, aber er hat Prinzipien. Doch wenn ihr Sklaven im Laderaum habt... betet, dass ihr keine schwarzen Segel am Horizont seht.\n"+
			"Die 'Memento' kreuzt zwischen Piratensiedlungen, legt jedoch fast nie an. Die Mannschaft lebt monatelang an Bord, als fürchte sie, festen Boden zu betreten. Man munkelt, das Schiff habe einst eine schreckliche Seuche überstanden – deshalb ist die Crew so schwer zu töten.\n"+
			"Wenn ihr angreifen wollt – nehmt viele Kanonen mit. Die 'Memento' zu entern ist nahezu unmöglich – die Mannschaft kämpft wie von Dämonen besessen, als hätte sie keine Angst vor dem Tod. Der einzige Weg, sie zu besiegen, ist, das Schiff in Stücke zu schießen und ihnen so das Versteck zu nehmen. Splitter schrecken sie nicht, aber gezielte Kartätschentreffer – das ist etwas anderes.\n"+
			"Viel Glück. Und denkt an den Tod.";
			link.l1 = "Vielen Dank.";
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
