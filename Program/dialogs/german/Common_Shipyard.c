// boal 08/04/06 общий диалог верфи
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;
	
	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int Material, WorkPrice;
	int amount;
	int	iCannonDiff;
	
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
 	// генератор парусов по кейсу <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "ship_tunning_not_now_1":  
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Der Alarm wurde in der Stadt ausgelöst und jeder sucht nach dir. Wenn ich du wäre, würde ich hier nicht bleiben.","Alle Stadtwachen durchkämmen die Stadt auf der Suche nach dir. Ich bin kein Narr und werde nicht mit dir reden!","Lauf, "+GetSexPhrase("Kumpel","lass")+", bevor die Soldaten dich in ein Sieb verwandeln..."),LinkRandPhrase("Was brauchst du, "+GetSexPhrase("Schurke","Stinker")+"?! Die Stadtwachen haben schon deine Spur, du wirst nicht weit kommen, du dreckiger Pirat!","Mörder, verlasse sofort mein Haus! Wachen!","Ich habe keine Angst vor dir, "+GetSexPhrase("Schurke","Ratte")+"! Bald wirst du in unserem Fort aufgehängt, du kommst nicht weit..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, ein Alarm ist für mich kein Problem...","Sie werden mich nie bekommen."),RandPhraseSimple("Halt dein Mund, "+GetWorkTypeOfMan(npchar,"")+", oder ich reiße dir die Zunge heraus!","Heh, "+GetWorkTypeOfMan(npchar,"")+", und dort auch - Piraten zu fangen! Das sage ich dir, Kumpel: sei ruhig und du wirst nicht sterben!"));
				link.l1.go = "fight";
				break;
			}
			
//Jason ---------------------------------------Бремя гасконца------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
				{
					dialog.text = "Brauchen Sie etwas, Monsieur?";
					Link.l1 = "Ich kam, um mir Ihre Schiffe anzusehen... Aber im Moment bin ich etwas beschäftigt - ich habe noch eine unerledigte Angelegenheit. Ich komme später vorbei, wenn ich damit fertig bin.";
					Link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
				{
					dialog.text = "Brauchen Sie etwas, Monsieur?";
					Link.l1 = "Hör zu, ich möchte ein Schiff von dir kaufen.";
					Link.l1.go = "Sharlie";
					break;
				}
				dialog.text = "Brauchen Sie sonst noch etwas, Monsieur?";
				Link.l1 = "Nein, ich denke nicht.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				NPChar.quest.meeting = "1";
				break;
			}
	//<-- Бремя гасконца
			// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
			{
				if (pchar.questTemp.FMQM == "remove_oil")
				{
					dialog.text = "Das ist es, Kapitän. Job erledigt. Jetzt der angenehme Teil - das Klirren der Münzen. Gib mir eine Sekunde...";
					link.l1 = "...";
					link.l1.go = "FMQM_oil_1";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil1")
				{
					dialog.text = "Offizier, warten Sie! Bitte! Das muss ein Missverständnis sein. Monsieur, der Kapitän hat nichts damit zu tun, er hat hier nur angelegt, um sein Schiff reparieren zu lassen. Er war gerade im Begriff zu gehen. Und welche Fässer? Wovon sprechen Sie?";
					link.l1 = "";
					link.l1.go = "FMQM_oil_2";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil2")
				{
					dialog.text = "Offizier, ich wiederhole: Der Kapitän ist hier, um für Schiffreparaturen zu bezahlen. Diese Fässer sind mein Eigentum und sie dienen ausschließlich Produktionszwecken. Ich bin ein Meisterschiffsbauer und dieses Harz ist für die Schiffe, die ich baue.";
					link.l1 = "";
					link.l1.go = "FMQM_oil_3";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil3")
				{
					dialog.text = "Oh, Monsieur Kapitän! Sie haben keine Ahnung, wie schlimm es für mich war. Zwei Tage in Verliesen, begleitet von Ratten, Mäusen und elenden Gestalten! Ich musste jede Verbindung nutzen, die ich hatte, um mich dort herauszuholen. Ah, die frische Luft!";
					link.l1 = "Sie haben mein Mitgefühl, Meister. Was ist mit unserem Harz? Und meine Münzen?";
					link.l1.go = "FMQM_oil_4";
					DelLandQuestMark(npchar);
					break;
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
			{
				dialog.text = "Oh, du bist es schon wieder! Ich erkenne dich, junger Mann! Du warst es, der neulich nach... einer Erhöhung der Schiffsgeschwindigkeit durch Seidentuchsegel gefragt hat, richtig?";
				link.l1 = "Deine Erinnerung ehrt dich, Meister."; 
				link.l1.go = "mtraxx_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0") // первая встреча
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Ha! Ein echter alter Seebär kam zu meiner bescheidenen Werkstatt! Sind Sie neu in den hiesigen Gewässern, Kapitän?","Willkommen, Herr! Wenn Sie kein Fremder zur See sind und ein Schiff besitzen - dann sind Sie genau richtig hier!","Hallo, Herr! Sie haben Glück - dies ist die beste Schiffswerkstatt in der gesamten britischen Neuen Welt."),LinkRandPhrase("Herr, ich nehme an, Sie sind ein fabelhafter Kapitän, nicht wahr? Wenn Sie es sind, haben Sie recht gehabt, meine bescheidene Werft zu besuchen!","Erste Mal hier, Herr Kapitän? Komm rein und triff diesen alten Schiffsbauer.","Lassen Sie uns das Vergnügen haben, einander kennenzulernen, Monsieur! Ein Schiff muss gestreichelt werden, genau wie eine Frau - und wir, die Franzosen, sind Experten darin! Vertrauen Sie mir, Sie werden es nicht bereuen, hierher gekommen zu sein!"),LinkRandPhrase("Ich habe Sie hier noch nie gesehen, Senor. Schön, Sie kennenzulernen!","Ich begrüße einen tapferen Eroberer der Meere! Du bist ein Seemann, nicht wahr? Und ich bin der örtliche Schiffsbauer, wir sollten uns kennenlernen.","Hallo, Caballero! Ich freue mich, Sie in meiner Werkstatt begrüßen zu dürfen!"),LinkRandPhrase("Guten Tag, Mynheer. Ich habe Sie noch nicht getroffen, oder? Haben Sie Geschäfte mit mir?","Hallo, Mynheer Kapitän. Seien Sie nicht überrascht, ich habe schon einige Kapitäne getroffen, also habe ich auf den ersten Blick erkannt, dass Sie auch ein Kapitän sind.","Kommen Sie rein, Mynheer. Ich bin der örtliche Schiffsbauer. Freut mich, Sie kennenzulernen."));
				Link.l1 = LinkRandPhrase("Ich freue mich auch, Sie kennenzulernen. Mein Name ist "+GetFullName(pchar)+", und ich bin neu in diesen Gegenden. Also, ich habe beschlossen, vorbeizuschauen.","Einfach vorbeigehen konnte ich nicht - du weißt, dieser Geruch von frisch gehobelten Planken... Ich bin "+GetFullName(pchar)+", Kapitän des Schiffes '"+pchar.ship.name+"'.'","Erlauben Sie mir, mich vorzustellen - "+GetFullName(pchar)+", Kapitän des Schiffes '"+pchar.ship.name+"', freut mich, Sie kennenzulernen. Also, Sie bauen und reparieren hier Schiffe, nicht wahr?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_shipyard")
				{
					dialog.text = "Grüße, Kapitän MacArthur.";
					link.l1 = "Sie können mich einfach Helen nennen, Herr "+npchar.lastname+". "+TimeGreeting()+".";
					Link.l1.go = "Helen_meeting";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Oh! Der Schrecken der lokalen Gewässer, Kapitän "+GetFullName(pchar)+"! Was kann ich für Sie tun?","Lassen wir uns gleich zur Sache kommen, "+GetAddress_Form(NPChar)+", Ich habe keine Zeit zum Plaudern. Brauchst du eine Reparatur oder willst du nur deine Wanne ersetzen?","Oh, ist das nicht "+GetFullName(pchar)+"! Was ist los, "+GetAddress_Form(NPChar)+"? Ist etwas Schlimmes mit deiner Wanne passiert?"),LinkRandPhrase("Was brauchen Sie dort, Kapitän? Nicht eine einzige Minute Ruhe - immer all diese Schurken, was für ein verfluchter Tag...","Hallo, "+GetAddress_Form(NPChar)+". Ich muss sagen, dass Ihr Besuch all meine Kunden verjagt hat. Ich hoffe, Ihre Bestellung deckt meinen Schaden?","Bei einem Geschäft mit mir, "+GetAddress_Form(NPChar)+"? Nun, mach weiter, und mach schnell."),LinkRandPhrase("Was führt Sie zu mir, Herr "+GetFullName(pchar)+"? Ich kann verstehen, dass Ihr Schiff Schwierigkeiten haben könnte, wenn man Ihren Lebensstil bedenkt...","Ich freue mich, einen Adligen zu begrüßen... oh, entschuldigen Sie, "+GetAddress_Form(NPChar)+", Ich hielt dich für jemand anderen. Was wolltest du?","Ich mag deine Art nicht wirklich, Kapitän, aber ich werde dich trotzdem nicht vertreiben. Was wolltest du?")),LinkRandPhrase(LinkRandPhrase("Ich freue mich sehr, Sie zu sehen, Herr "+GetFullName(pchar)+"! Also, wie läuft sie? Brauchst du eine Reparatur oder muss sie abgewrackt werden?","Willkommen, "+GetAddress_Form(NPChar)+"! Kapitän "+GetFullName(pchar)+" ist immer ein willkommener Gast in meiner Werkstatt!","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Sie haben mich wieder besucht! Ich hoffe, Ihre Schönheit geht es gut, nicht wahr?"),LinkRandPhrase(""+GetAddress_Form(NPChar)+", Ich bin so froh, dich wieder zu sehen! Wie geht es deinem wunderschönen Schiff? Brauchst du Hilfe?","Ach, "+GetAddress_Form(NPChar)+", Grüße! Wie geht es Ihnen? Vielleicht knarren die Masten oder du brauchst eine Bilgenreinigung? Meine Jungs werden ihr Bestes für dich tun!","Guten Tag, Kapitän "+GetFullName(pchar)+". Ich freue mich, dass Sie wieder vorbeigeschaut haben, und ich bin immer bereit, Ihnen zu helfen."),LinkRandPhrase("Ich freue mich, dass Sie hier sind, Kapitän! Sie sind ein sehr netter Kunde, "+GetAddress_Form(NPChar)+", und ich wünsche, dass du so bleibst.","Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Ich bin wirklich froh, dich hier zu haben! Was kann ich für dich tun?","Kapitän, Sie haben uns wieder besucht "+XI_ConvertString("Colony"+npchar.City+"Konto")+"! Glaub mir, wir helfen dir gerne.")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Holt Eure Instrumente, Meister, und haltet den Mund, verstanden? Ich bin nicht in Stimmung.","Hör auf zu schwätzen, Kumpel! Ich brauche deine Hilfe, und nicht dein Geschwätz."),RandPhraseSimple("Ich zahle - und du arbeitest. Still. Ist das klar?","Hallo, Kamerad, treib sie alle weg - ich bin's, dein bevorzugter Kunde!")),RandPhraseSimple(RandPhraseSimple("Es freut mich auch, Sie zu sehen, Meister. Leider habe ich nicht viel Zeit, also lassen Sie uns zur Sache kommen.","Und ich bin auch froh, dich zu sehen, Kumpel. Willst du deinem bevorzugten Kunden helfen?"),RandPhraseSimple("Guten Nachmittag, Kamerad. Lassen wir uns gleich zur Sache kommen. Versprochen, nächstes Mal setzen wir uns sicher mit einer Flasche hin.","Es freut mich, Sie zu sehen, Meister. Es ist immer ein Vergnügen, Sie zu sehen, aber gerade jetzt brauche ich Ihre Hilfe.")));
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = "Ich brauche Kanonen für mein Schiff.";
					link.l11.go = "Cannons";					
				}	
				
				if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
				{
					link.l22 = "Können Sie mir etwas Besonderes anbieten, etwas, das in keiner anderen Werft zu finden ist?";
					link.l22.go = "ship_tunning";
				}
				
				link.l15 = "Hast du nicht einen Job, der die Hilfe eines Fremden erfordert?";
			    link.l15.go = "Tasks";
				// Jason Исла Мона 
				if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "tools" && !CheckAttribute(npchar, "quest.IslaMonaTools"))
				{
					link.l20 = "Ich möchte ein Set europäischer Qualitätsbau-, Schmiede- und Messwerkzeuge kaufen. Können Sie mir helfen?";
					link.l20.go = "IslaMona";
				}
				if (CheckAttribute(npchar, "quest.IslaMonaMoney"))
				{
					link.l20 = "Ich habe Dublonen für einen Satz Bauwerkzeuge mitgebracht.";
					link.l20.go = "IslaMona_7";
				}
				//Jason --> генератор Призонер
				if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
				{
					ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
					if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
					{
						for(i = 1; i < COMPANION_MAX; i++)
						{
							int iTemp = GetCompanionIndex(PChar, i);
							if(iTemp > 0)
							{
								sld = GetCharacter(iTemp);
								if(GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
								{
									pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
									pchar.GenQuest.Findship.Shipyarder.OK = 1;
									pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
									pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder"))*1.5);
								}
							}
						}
					}
					if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
					{
						link.l16 = "Ich habe dir geliefert "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+", wie Sie gefragt haben.";
						link.l16.go = "Findship_check";
					}// <-- генератор Призонер
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
				{
					link.l17 = "Ich habe es geschafft, den Dieb ausfindig zu machen und zu bekommen "+pchar.GenQuest.Device.Shipyarder.Type+".";
					link.l17.go = "Device_complete";
				}
				// <-- генератор Неудачливый вор
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Ich möchte das Aussehen meiner Segel ändern.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Ich wollte nur reden.";
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Ich möchte mit Ihnen über finanzielle Angelegenheiten sprechen.";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Ich bin hier auf Anfrage eines Mannes. Sein Name ist Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" hat mich zu dir geschickt. Ich soll etwas abholen...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Ich habe die Zeichnung des Schiffes von "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				} // patch-6
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "Hallo, ich bin auf Einladung Ihres Sohnes gekommen."; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "Es geht um Ihre Tochter...";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "Ich muss gehen.";
				Link.l9.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Meeting":
				dialog.Text = "Ich freue mich sehr, einen neuen Kunden zu treffen. Meine Werft steht zu Ihrer Diensten.";
				Link.l1 = "Ausgezeichnet, "+GetFullName(NPChar)+". Lass uns mal sehen, was du mir anbieten kannst.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "Ich brauche Kanonen für mein Schiff.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Hast du nicht eine Aufgabe, bei der du die Hilfe eines Fremden benötigst?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Ich möchte das Aussehen meiner Segel ändern.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Ich wollte nur reden.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Ich möchte mit Ihnen über finanzielle Angelegenheiten sprechen.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Ich bin hier auf Anfrage eines Mannes. Sein Name ist Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" hat mich zu dir geschickt. Ich soll etwas abholen...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Ich habe die Zeichnung des Schiffes aus der Stadt geliefert "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Hallo, ich bin auf Einladung Ihres Sohnes gekommen."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "Es geht um Ihre Tochter...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Was können Sie mir über den Besitzer dieser Dokumente erzählen?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Ich muss gehen, danke.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;
		
		case "Helen_Meeting":
				dialog.Text = "Natürlich, Kapitän MacArthur, wie Sie wünschen. Was benötigen Sie heute?";
				Link.l1 = "Ausgezeichnet, "+GetFullName(NPChar)+". Lass uns mal sehen, was du mir anbieten kannst.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "Ich brauche Kanonen für mein Schiff.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Hast du nicht eine Arbeit, die die Hilfe eines Fremden erfordert?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Ich möchte das Aussehen meiner Segel ändern.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Ich wollte nur reden.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Ich möchte mit Ihnen über finanzielle Angelegenheiten sprechen.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Ich bin hier auf Antrag eines Mannes. Sein Name ist Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" hat mich zu dir geschickt. Ich soll etwas abholen...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Ich habe die Zeichnung des Schiffes aus der Stadt geliefert "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Hallo, ich bin auf Einladung Ihres Sohnes gekommen."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "Es geht um Ihre Tochter...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Was können Sie mir über den Besitzer dieser Dokumente erzählen?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Ich muss gehen, Danke.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;

		case "ship_tunning":
			dialog.text = "Unsere Werft ist bekannt für die Verbesserung von Schiffen. Sind Sie interessiert, Kapitän?";
			Link.l1 = LinkRandPhrase("Ausgezeichnet! Vielleicht kannst du dir mein Schiff ansehen und mir sagen, wie es verbessert werden kann?","Das ist sehr interessant, Meister! Und was können Sie für mein Schiff tun?","Hmm... Weißt du, ich habe mich an mein Schiff gewöhnt, aber wenn du mir etwas wirklich Interessantes anbietest, kann ich darüber nachdenken. Was sagst du?");
			Link.l1.go = "ship_tunning_start";
		break;
				
		case "ship_tunning_start" :		
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{				
				if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 6)
				{
					dialog.Text = "Äh... Ich beschäftige mich nicht mit Booten. Ein altes Waschbecken bleibt ein altes Waschbecken, egal wie viel Mühe man hineinsteckt.";
					Link.l1 = "Ich sehe...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// belamour legendary edition -->
				if(!TuningAvailable())
				{
					dialog.Text = "So lala... mal sehen, was wir hier haben... Ja - "+XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName)+". Ihr Schiff hat bereits die maximale Anzahl an verbesserten Eigenschaften, ich fürchte, dass weitere Arbeiten daran keinen Sinn machen und nur Schaden anrichten können.";
					Link.l1 = "Ich sehe...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// <-- legendary edition							
				if(GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
				{
					dialog.Text = "Bevor ein Schiff verbessert werden kann, muss es vollständig repariert sein. Dies kann auch hier in meiner Werft gemacht werden.";
					Link.l1 = "Verstanden...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				
				s2 = "Alright, let's see what we've got here... Aha " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
				// belamour legendary edition -->
				if(NPChar.city == "PortRoyal")
				{
					s2 = s2 + " Our shipyard is famous for improving the ship's performance we can increase either the maximum speed or the angle to the wind.";
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					s2 = s2 + " At our shipyard we can increase the maximum number of cannons or the ship's carrying capacity.";
				}
				if(NPChar.city == "Villemstad")
				{
					s2 = s2 + " My guys can reinforce the hull of your ship or increase the maximum number of sailors in your crew.";
				}
				if(NPChar.city == "Charles")
				{
					s2 = s2 + " At this shipyard you can improve the maneurability or decrease the minimum number of sailors in the crew.";
				}	
				
				dialog.Text = s2;
				
				if(NPChar.city == "PortRoyal")
				{
					// belamour legendary edition -->
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
					if(ok)
					{
						Link.l1 = "Erhöhe die Geschwindigkeit.";
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = "Erhöhe den Winkel zum Wind.";
						Link.l2.go = "ship_tunning_WindAgainst";
						Link.l3 = "Halt ein! Ich habe meine Meinung geändert.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
						{
							Link.l1 = "Erhöhe die Geschwindigkeit.";
							Link.l1.go = "ship_tunning_SpeedRate";
							Link.l2 = "Halt! Ich habe meine Meinung geändert.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
						{
							Link.l1 = "Erhöhe den Winkel zum Wind.";
							Link.l1.go = "ship_tunning_WindAgainst";
							Link.l2 = "Halt! Ich habe meine Meinung geändert.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("Oh! Mein Schiff ist bereits auf diese Weise verbessert. Nun, danke für deine Zeit!","Danke, Meister, aber ich habe bereits eine Verbesserung, und es ist genau das, was Sie mir gesagt haben. Viel Glück mit den anderen Schiffen und ihren Kapitänen!","Heh! Ich nehme an, dass mein Schiff schon einmal von einem früheren Besitzer umgerüstet wurde - es muss in dieser Werft gewesen sein. Nun, ich denke, ich muss ihm für seine Weitsicht danken, und euch und euren Leuten für ihre hervorragende Arbeit!");
						Link.l1.go = "ship_tunning_not_now_1";					
					}
						// <-- legendary edition
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
					if(ok)
					{	
						if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{	
							Link.l1 = "Erhöhe die maximale Anzahl an Kanonen.";
							Link.l1.go = "ship_c_quantity";
						}	
							Link.l2 = "Erhöhe das Leergewicht.";
							Link.l2.go = "ship_tunning_Capacity";
						Link.l3 = "Halt! Ich habe meine Meinung geändert.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
						{
							if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
							{	
								Link.l1 = "Erhöhe die maximale Anzahl an Kanonen.";
								Link.l1.go = "ship_c_quantity";
								Link.l2 = "Halt ein! Ich habe meine Meinung geändert.";
								Link.l2.go = "ship_tunning_not_now_1";	
								break;
							}	
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
						{
							Link.l1 = "Erhöhe das Tragfähigkeit.";
							Link.l1.go = "ship_tunning_Capacity";
							Link.l2 = "Halt! Ich habe meine Meinung geändert.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("Oh! Mein Schiff ist bereits auf diese Weise verbessert. Nun, danke für Ihre Zeit!","Danke, Meister, aber ich habe bereits eine Verbesserung, und es ist genau das, was Sie mir erwähnt haben. Viel Glück mit anderen Schiffen und deren Kapitänen!","Heh! Ich nehme an, dass mein Schiff bereits von einem früheren Besitzer umgerüstet wurde - es muss in dieser sehr Werft gewesen sein. Nun, ich muss ihm wohl für seine Weitsicht danken, und euch und euren Leuten für ihre ausgezeichnete Arbeit!");
						Link.l1.go = "ship_tunning_not_now_1";	
					// <-- legendary edition
					}						
				}
				if(NPChar.city == "Villemstad")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
					if(ok)
					{
						Link.l1 = "Erhöhe die Haltbarkeit des Rumpfes.";
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = "Erhöhe den Platz für die Besatzung.";
						Link.l2.go = "ship_tunning_MaxCrew";
						Link.l3 = "Halt! Ich habe meine Meinung geändert.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
						{
							Link.l1 = "Erhöhe die Haltbarkeit des Rumpfes.";
							Link.l1.go = "ship_tunning_HP";
							Link.l2 = "Halt! Ich habe meine Meinung geändert.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
						{
							Link.l1 = "Erhöhen Sie den Platz für die Mannschaft.";
							Link.l1.go = "ship_tunning_MaxCrew";
							Link.l2 = "Halt an! Ich habe meine Meinung geändert.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;	
						}
						Link.l1 = LinkRandPhrase("Oh! Mein Schiff ist bereits auf diese Weise verbessert. Nun, danke für deine Zeit!","Danke, Meister, aber ich habe bereits eine Verbesserung, und es ist genau das, was Sie mir erwähnt haben. Viel Glück mit den anderen Schiffen und ihren Kapitänen!","Heh! Ich nehme an, dass mein Schiff bereits von einem früheren Besitzer überholt wurde - es muss in dieser genauen Werft gewesen sein. Nun, ich schätze, ich muss ihm für seine Weitsicht danken, und dir und deinen Leuten für ihre hervorragende Arbeit!");
						Link.l1.go = "ship_tunning_not_now_1";	
						// <-- legendary edition
					}
				}
				if(NPChar.city == "Charles")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
					if(ok)
					{		
						Link.l1 = "Erhöhe die Manövrierfähigkeit.";
						Link.l1.go = "ship_tunning_TurnRate";
						if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l2 = "Verringern Sie die minimale Crewgröße.";
							Link.l2.go = "ship_tunning_MinCrew";
						}	
						Link.l3 = "Halt! Ich habe meine Meinung geändert.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
						{
							Link.l1 = "Manövrierfähigkeit erhöhen.";
							Link.l1.go = "ship_tunning_TurnRate";
							Link.l2 = "Halt ein! Ich habe meine Meinung geändert.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"))
						{
							if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
							{
								Link.l1 = "Reduziere die minimale Crewgröße.";
								Link.l1.go = "ship_tunning_MinCrew";
								Link.l2 = "Haltet ein! Ich habe es mir anders überlegt.";
								Link.l2.go = "ship_tunning_not_now_1";
								break;
							}	
						}
						// <-- legendary edition				
					}
					Link.l1 = LinkRandPhrase("Oh! Mein Schiff ist bereits auf diese Weise verbessert. Nun, danke für Ihre Zeit!","Danke, Meister, aber ich habe bereits eine Verbesserung, und es ist genau das, was Sie mir erwähnt haben. Viel Glück mit anderen Schiffen und ihren Kapitänen!","Heh! Ich nehme an, dass mein Schiff bereits von einem früheren Besitzer überholt wurde - es muss in dieser Werft gewesen sein. Nun, ich denke, ich muss ihm für seine Voraussicht danken, und Ihnen und Ihren Leuten für ihre ausgezeichnete Arbeit!");
					Link.l1.go = "ship_tunning_not_now_1";	
				}								
			}
			else
			{
				dialog.Text = "Wo ist das Schiff? Ziehst du mir das Bein oder was?";
			    Link.l1 = "Oh, mein Fehler, tatsächlich... Es tut mir leid.";
			    Link.l1.go = "ship_tunning_not_now_1";
			}			
		break;
		
		////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Well, let's see what we can do. At the moment the deadweight of your vessel is " + sti(RealShips[sti(pchar.Ship.Type)].Capacity);			
			s2 = s2 + ". For lighter bulkheads I will require: ironwood - " + Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";			
            dialog.Text = s2;
			Link.l1 = "Einverstanden. Ich akzeptiere Ihre Bedingungen. Ich werde Ihnen bringen, was Sie brauchen.";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "Nein. Das passt mir nicht.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_Capacity_start":
		    amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = "Ausgezeichnet. Ich werde auf das Material warten.";
			    link.l1 = LinkRandPhrase("Ich versichere Ihnen, dass Sie nicht lange warten müssen. Solche Probleme kann ich lösen, ist das klar?","Betrachte es so, als hättest du sie bereits und halte das Dock für mich frei. Ich werde schnell wie der Wind sein.","Natürlich. Ich muss nur ein paar Leute besuchen, die das haben, was du angefragt hast, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the tonnage of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'"+
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Ich sehe die Kaution nicht...";
				link.l1 = "Ich schaue später vorbei.";
				link.l1.go = "Exit";								
			}
		break;
				
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Die Zeit vergeht und das Schiff wartet. Haben Sie alles mitgebracht, was ich angefordert habe?";
			    Link.l1 = "Ja, ich habe es geschafft, etwas zu finden.";
			    Link.l1.go = "ship_tunning_Capacity_again_2";
			    Link.l2 = "Nein, ich bin noch dabei.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
			    dialog.Text = "Fehl"+GetSexPhrase("ter","s")+", haben Sie seit unserer Abmachung Ihr Schiff gewechselt? Das hätten Sie nicht tun sollen.";
			    Link.l1 = "Ach, es sind alle Umstände! Schade, dass die Anzahlung verloren ging...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Ausgezeichnet, jetzt habe ich alles, was ich brauche. Dann fange ich an zu arbeiten.";
			    link.l1 = "Ich warte.";
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Ich benötige immer noch: Eisenholz - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Gut.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
			}
			else
			{
				shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
			}			
	        shTo.Tuning.Capacity = true;

	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "...Das scheint alles zu sein... Ihr könnt nun euren Laderaum voll beladen, ich garantiere für die Qualität meiner Arbeit.";
			Link.l1 = "Danke! Ich werde es testen.";
			Link.l1.go = "Exit";
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar,  1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar,  2 );
			s2 = "Let's see what we can do, then. At the moment the speed of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);	
			s2 = s2 + " knots. In order to replace the sails I will require: sail silk - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
            dialog.Text = s2;
			Link.l1 = "Einverstanden. Ich akzeptiere Ihre Bedingungen. Ich werde Ihnen bringen, was Sie brauchen.";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "Nein. Das passt mir nicht.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
			
		case "ship_tunning_SpeedRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType   	= Pchar.Ship.Type;
			    NPChar.Tuning.ShipName   	= RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = "Ausgezeichnet. Ich werde auf das Material warten.";
				link.l1 = LinkRandPhrase("Ich versichere Ihnen, dass Sie nicht lange warten müssen. Ich kann solche Probleme lösen, in Ordnung?","Betrachten Sie es so, als hätten Sie sie bereits und halten Sie das Dock für mich frei. Ich werde so schnell sein wie der Wind.","Natürlich. Ich muss nur ein paar Leute besuchen, die das haben, was du angefordert hast, ha-ha!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the speed at " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". As the deposit was paid for " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Ich sehe die Einzahlung nicht...";
				link.l1 = "Ich schau später vorbei.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Die Zeit vergeht und das Schiff wartet. Haben Sie alles mitgebracht, was ich angefordert habe?";
			    Link.l1 = "Ja, ich habe es geschafft, etwas zu finden.";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
			    Link.l2 = "Nein, ich bin noch dabei.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Fehl"+GetSexPhrase("ter","s")+", hast du dein Schiff gewechselt, seitdem wir unsere Vereinbarung getroffen haben? Das hättest du nicht tun sollen.";
			    Link.l1 = "Ach, es sind all die Umstände! Schade, dass die Einlage verloren ging...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Ausgezeichnet, jetzt habe ich alles, was ich brauche. Dann fange ich an zu arbeiten.";
			    link.l1 = "Ich warte.";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Ich benötige immer noch: Schiffsseide - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Gut.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
			}
			else
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
			}		
	        shTo.Tuning.SpeedRate = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Alles ist bereit, Kapitän. Fang den Wind in vollen Segeln. Schau es dir an, wenn du möchtest!";
			Link.l1 = "Danke! Ich werde es testen.";
			Link.l1.go = "Exit";			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			s2 = "Let's see what we can do, then. At the moment the maneurability of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);			
			s2 = s2 + " In order to add new sails to shake it up I shall require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";										
            dialog.Text = s2;
			Link.l1 = "Einverstanden. Ich akzeptiere Ihre Bedingungen. Ich werde Ihnen bringen, was Sie brauchen.";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "Nein. Das passt mir nicht.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_TurnRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = "Ausgezeichnet. Ich werde auf das Material warten.";
				link.l1 = LinkRandPhrase("Ich versichere Ihnen, dass Sie nicht lange warten müssen. Solche Probleme kann ich lösen, in Ordnung?","Betrachte es so, als hättest du sie bereits und halte das Dock für mich bereit. Ich werde so flink wie der Wind sein.","Natürlich. Ich muss nur ein paar Leute besuchen, die das Zeug haben, das du angefordert hast, ha-ha!");			    
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase agility by " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of  " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Ich sehe die Einzahlung nicht...";
				link.l1 = "Ich werde später vorbeischauen.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Die Zeit vergeht und das Schiff wartet. Hast du alles mitgebracht, was ich angefordert habe?";
			    Link.l1 = "Ja, es ist mir gelungen, etwas zu liefern.";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
			    Link.l2 = "Nein, ich bin immer noch dabei.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Fehl"+GetSexPhrase("ter","s")+", haben Sie Ihr Schiff gewechselt, seitdem wir unsere Vereinbarung getroffen haben? Das hätten Sie nicht tun sollen.";
			    Link.l1 = "Ach, das sind alle Umstände! Schade, dass die Einlage verloren ging...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Ausgezeichnet, jetzt habe ich alles, was ich brauche. Dann fange ich an zu arbeiten.";
			    link.l1 = "Ich warte.";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Ich benötige immer noch: Seile - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Gut.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	

	        shTo.Tuning.TurnRate = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
			dialog.Text = "... Alles sollte jetzt bereit sein... Überprüfen Sie jetzt das Steuerrad, Kapitän!";
			Link.l1 = "Danke! Ich werde es testen.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the maximum number of sailors in your crew, including overloading, is " + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " men.";			
			s2 = s2 + " I will require: ironwood - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Einverstanden. Ich akzeptiere Ihre Bedingungen. Ich werde Ihnen alles bringen, was Sie brauchen.";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "Nein. Das passt mir nicht.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MaxCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = "Ausgezeichnet. Ich werde auf das Material warten.";
				link.l1 = LinkRandPhrase("Ich versichere Ihnen, dass Sie nicht lange warten müssen. Solche Probleme kann ich lösen, in Ordnung?","Betrachten Sie es als erledigt und halten Sie das Dock für mich frei. Ich werde so schnell sein wie der Wind.","Natürlich. Ich muss nur ein paar Leute besuchen, die das Zeug haben, das du angefragt hast, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For their efforts to increase the crew of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Ich sehe die Anzahlung nicht...";
				link.l1 = "Ich schaue später vorbei.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Die Zeit vergeht und das Schiff wartet. Hast du alles mitgebracht, was ich angefordert habe?";
			    Link.l1 = "Ja, ich habe es geschafft, etwas zu finden.";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
			    Link.l2 = "Nein, ich bin noch dabei.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Fehl"+GetSexPhrase("ter","s")+", haben Sie Ihr Schiff gewechselt, seit wir unsere Vereinbarung getroffen haben? Das hätten Sie nicht tun sollen.";
			    Link.l1 = "Ach, das sind alle die Umstände! Schade, dass die Einzahlung verloren ging...";				
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Ausgezeichnet, jetzt habe ich alles, was ich brauche. Dann fange ich an zu arbeiten.";
			    link.l1 = "Ich warte.";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Ich benötige noch: Eisenholz - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Gut.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    
	        shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
	        shTo.Tuning.MaxCrew = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Es ist getan, Kapitän. Sie können nun mehr Seeleute anheuern, es sollte genug Platz für alle geben.";
			Link.l1 = "Danke! Ich werde es testen.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;

		
		////////////////////////////////////////// MinCrew ////////////////////////////////////////////////////
		case "ship_tunning_MinCrew":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the minimum number of required sailors in your crew is " + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " men.";			
			s2 = s2 + " To improve the controllability of the ship and to reduce the required number of sailors in the crew I will require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Einverstanden. Ich akzeptiere Ihre Bedingungen. Ich werde Ihnen bringen, was Sie brauchen.";
			Link.l1.go = "ship_tunning_MinCrew_start";
			Link.l2 = "Nein. Das passt mir nicht.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MinCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
                dialog.text = "Ausgezeichnet. Ich werde auf das Material warten.";
				link.l1 = LinkRandPhrase("Ich versichere Ihnen, dass Sie nicht lange warten müssen. Ich kann solche Probleme lösen, in Ordnung?","Betrachte es als ob du sie bereits hättest und halte den Dock für mich frei. Ich werde so schnell wie der Wind sein.","Natürlich. Ich muss nur ein paar Leute besuchen, die das haben, was du angefragt hast, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to reduce the minimum required number of crew on " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Ich sehe die Kaution nicht...";
				link.l1 = "Ich werde später vorbeischauen.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MinCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "Die Zeit vergeht, und das Schiff wartet. Hast du alles mitgebracht, was ich angefordert habe?";
			    Link.l1 = "Ja, ich habe es geschafft, etwas zu finden.";
			    Link.l1.go = "ship_tunning_MinCrew_again_2";
			    Link.l2 = "Nein, ich bin noch dran.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Fehlt"+GetSexPhrase("ter","s")+", hast du dein Schiff gewechselt, seitdem wir unsere Abmachung getroffen haben? Das hättest du nicht tun sollen.";
			    Link.l1 = "Ach, es sind alle Umstände! Schade, dass die Anzahlung verloren ging...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MinCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Ausgezeichnet, jetzt habe ich alles, was ich brauche. Dann fange ich an zu arbeiten.";
			    link.l1 = "Ich warte.";
			    link.l1.go = "ship_tunning_MinCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "Ich benötige immer noch: Seile - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Gut.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MinCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
	        shTo.Tuning.MinCrew = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4")  && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Bereit, Kapitän! Jetzt können weniger Seeleute das Schiff mit dem gleichen Gesamtergebnis steuern.";
			Link.l1 = "Danke! Ich werde es testen.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what we can do, then. At the moment the ship's hull is " + sti(RealShips[sti(Pchar.Ship.Type)].HP);			
			s2 = s2 + ". To reinforce the hull, I will require: resin - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Einverstanden. Ich akzeptiere deine Bedingungen. Ich werde dir bringen, was du brauchst.";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "Nein. Das passt mir nicht.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_HP_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = "Ausgezeichnet. Ich werde auf das Material warten.";
				link.l1 = LinkRandPhrase("Ich versichere Ihnen, dass Sie nicht lange warten müssen. Ich kann solche Probleme lösen, in Ordnung?","Betrachte es als ob du sie bereits hast und halte das Dock für mich frei. Ich werde so schnell wie der Wind sein.","Natürlich. Ich muss nur ein paar Leute besuchen, die das Zeug haben, nach dem du gefragt hast, ha-ha!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his efforts to increase the strength of the hull " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Ich sehe die Einzahlung nicht...";
				link.l1 = "Ich schaue später vorbei.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Die Zeit vergeht, und das Schiff wartet. Hast du alles mitgebracht, was ich verlangt habe?";
			    Link.l1 = "Ja, ich habe es geschafft, etwas zu finden.";
			    Link.l1.go = "ship_tunning_HP_again_2";
			    Link.l2 = "Nein, ich bin noch dabei.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Fehl"+GetSexPhrase("ter","s")+", haben Sie Ihr Schiff gewechselt, seitdem wir unsere Vereinbarung getroffen haben? Das hätten Sie nicht tun sollen.";
			    Link.l1 = "Ach, es sind all die Umstände! Schade, dass die Einlage verloren ging...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_OIL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Ausgezeichnet, jetzt habe ich alles, was ich brauche. Dann fange ich an zu arbeiten.";
			    link.l1 = "Ich warte.";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Ich benötige immer noch: Harz - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Gut.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
			}
			else
			{
				shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
			}	
	        shTo.Tuning.HP = true;
			shTo.BaseHP = sti(shTo.HP);

			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
			TuningAvailable();
            NextDiag.TempNode = "First time";
			
			dialog.Text = "... Das sollte es tun... Ich garantiere, dass es für deine Feinde ab jetzt viel schwieriger sein wird, den Rumpf deines Schiffes in Stücke zu reißen!";
			Link.l1 = "Heh, ich nehme Ihr Wort dafür! Danke, Meister.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			fTmp = 180.0 - (stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed) * 90.0);
			s2 = "Let's see what we can do, then. At the moment the point of sail by the wind is " + makeint(fTmp) + " degrees.";
			// belamour legendary edition если спускать курс по ветру, то это даунгрейд
			s2 = s2 + " To accelerate the ship upwind, I will require: ship silk - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "Einverstanden. Ich akzeptiere Ihre Bedingungen. Ich werde Ihnen bringen, was Sie brauchen.";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "Nein. Das passt mir nicht.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;

		case "ship_tunning_WindAgainst_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial    	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = "Ausgezeichnet. Ich werde auf das Material warten.";
				link.l1 = LinkRandPhrase("Ich versichere Ihnen, dass Sie nicht lange warten müssen. Ich kann solche Probleme lösen, in Ordnung?","Betrachte es so, als hättest du sie bereits und halte das Dock für mich frei. Ich werde so schnell sein wie der Wind.","Natürlich. Ich muss nur ein paar Leute besuchen, die das Zeug haben, das du angefragt hast, ha-ha!");
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work on changing the wind angle of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Ich sehe die Anzahlung nicht...";
				link.l1 = "Ich schaue später vorbei.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = "Die Zeit vergeht und das Schiff wartet. Haben Sie alles gebracht, was ich angefordert habe?";
			    Link.l1 = "Ja, ich habe es geschafft, etwas zu liefern.";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
			    Link.l2 = "Nein, ich bin immer noch dabei.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Fehl"+GetSexPhrase("ter","s")+", hast du seit unserer Vereinbarung dein Schiff gewechselt? Das hättest du nicht tun sollen.";
			    Link.l1 = "Ach, das sind alle Umstände! Schade, dass die Anzahlung verloren ging...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Ausgezeichnet, jetzt habe ich alles, was ich brauche. Dann fange ich an zu arbeiten.";
			    link.l1 = "Ich warte.";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = "Ich benötige immer noch: Schiff Seide - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Gut.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим			
			// belamour legendary edtion чем больше WindAgainstSpeed, тем круче к ветру
	        shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.20 * stf(shTo.WindAgainstSpeed);	
			if (stf(shTo.WindAgainstSpeed) > 1.985) shTo.WindAgainstSpeed = 1.985;
	        shTo.Tuning.WindAgainst = true;

			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Bereit, Kapitän!.. Ihr Schiff wird nun viel schneller gegen den Wind segeln.";
			Link.l1 = "Danke! Ich werde es testen.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
						
		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what can be done there. Right now, the number of cannons on your ship is " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + ", and the maximum possible number is - " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + ".";			
			s2 = s2 + " I can tell you right away that it's not going to be cheap. I will require: resin - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
			dialog.Text = s2;		
			Link.l1 = "Einverstanden. Ich akzeptiere deine Bedingungen. Ich werde dir bringen, was auch immer du brauchst.";
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = "Nein. Das passt mir nicht.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_c_quantity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та еще морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Cannon 		= true;				
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 				
				NPChar.Tuning.ShipType      = Pchar.Ship.Type;
				NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "Ausgezeichnet. Ich werde auf das Material warten.";
				link.l1 = LinkRandPhrase("Ich versichere Ihnen, dass Sie nicht lange warten müssen. Ich kann solche Probleme lösen, in Ordnung?","Betrachte es als erledigt und halte das Dock für mich frei. Ich werde so schnell wie der Wind sein.","Natürlich. Ich muss nur ein paar Leute besuchen, die das haben, was du angefragt hast, ha-ha!");
				link.l1.go = "Exit";			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the number of cannons on the " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +						
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "Ich sehe die Einzahlung nicht...";
				link.l1 = "Ich schaue später vorbei.";
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Die Zeit vergeht und das Schiff wartet. Haben Sie alles mitgebracht, was ich angefordert habe?";
				Link.l1 = "Ja, ich habe es geschafft, etwas zu finden.";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "Nein, ich bin noch dabei.";
				Link.l2.go = "Exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.Text = "Fehl"+GetSexPhrase("ter","s")+", haben Sie seit unserer Absprache Ihr Schiff gewechselt? Das hätten Sie nicht tun sollen.";
			    Link.l1 = "Ach, das sind all die Umstände! Schade, dass die Anzahlung verloren gegangen ist...";
				Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_OIL);
			if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.text = "Ausgezeichnet, jetzt habe ich alles, was ich brauche. Dann fange ich an zu arbeiten.";
				link.l1 = "Ich warte.";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Ich benötige immer noch: Harz - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "Gut.";
				link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			makearef(refShip, pchar.Ship);
			
			iCannonDiff = sti(refShip.CannonDiff);
			iCannonDiff -= 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;										
					
				if(i < (sti(shTo.cannonr) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
					}	
				}					
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i < (sti(shTo.cannonl) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
					}	
				}										
			}	
			
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else										    shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;			

			shTo.Tuning.Cannon = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			NextDiag.TempNode = "First time";
			dialog.Text = "... Das ist es, Kapitän. Sie können zusätzliche Kanonen verwenden - das heißt, wenn Sie welche haben, he-he.";
			Link.l1 = "Danke!";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		
		case "Tasks":
			//--> Jason генератор Поиск корабля
			if (drand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
			{
				if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60) 
				{
					SelectFindship_ShipType(); //выбор типа корабля
					pchar.GenQuest.Findship.Shipyarder.ShipBaseName =  GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
					pchar.GenQuest.Findship.Shipyarder.City = npchar.city; //город квестодателя
					dialog.text = "Ich habe ein Problem, das gelöst werden muss. Ich habe eine Bestellung für ein Schiff - "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+". Allerdings gibt es in meinem Hof derzeit kein solches Schiff und auch innerhalb von zwei Monaten habe ich keine Möglichkeit, eines zu bekommen.\nWenn du mir ein solches Schiff geben kannst - Ich werde dir sehr dankbar sein und dir das Eineinhalbfache seines Verkaufspreises zahlen.";
					link.l1 = "Ein interessantes Angebot. Ich stimme zu!";
					link.l1.go = "Findship";
					link.l2 = "Das interessiert mich nicht.";
					link.l2.go = "Findship_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Findship");
					break;
				}
				
			}//<-- генератор Поиск корабля
			//Jason --> генератор Неудачливый вор
			if (drand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
			{
				if (!CheckAttribute(npchar, "Device")) 
				{
					switch (crand(4))
					{
						case 0:  
							pchar.GenQuest.Device.Shipyarder.Type = "inside gage";
							pchar.GenQuest.Device.Shipyarder.Describe = "two hammered strips, connected with a joint unriveted on both ends";
						break; 
						case 1:  
							pchar.GenQuest.Device.Shipyarder.Type = "Swedish broad axe";
							pchar.GenQuest.Device.Shipyarder.Describe = "an axe on a long straight handle with a thin semicircular blade";
						break; 
						case 2:  
							pchar.GenQuest.Device.Shipyarder.Type = "groover";
							pchar.GenQuest.Device.Shipyarder.Describe = "a small axe, looking like a farmer's mattock";
						break; 
						case 3:  
							pchar.GenQuest.Device.Shipyarder.Type = "stockpile level";
							pchar.GenQuest.Device.Shipyarder.Describe = "two wooden bars of equal length, linked by the same third one, which has in the middle a rotating liquid-filled plate with an air bubble";
						break;
						case 4:  
							pchar.GenQuest.Device.Shipyarder.Type = "barsik";
							pchar.GenQuest.Device.Shipyarder.Describe = "an ordinary flail, but the chain is rod-shaped and only moves in one direction";
						break; 
					}
					dialog.text = "Du bist gerade rechtzeitig. Vielleicht könntest du mir helfen. Jemand hat mir gestern ein sehr wertvolles Instrument gestohlen - "+pchar.GenQuest.Device.Shipyarder.Type+". Ich habe nicht die Möglichkeit, einen anderen zu machen und kann mir weder die Zeit noch die Kosten leisten, ihn aus Europa zu bestellen. Und ohne ihn kann ich nicht normalerweise Schiffe bauen, weißt du?\nUnd der ärgerlichste Teil - dieses Ding wird von niemandem außer Schiffbauern gebraucht, und ich bin der einzige Schiffbauer in der Kolonie. Dieser Dieb wird es an niemanden verkaufen und einfach wegwerfen. Vielleicht versuchst du, den Dieb aufzuspüren, fragst in der Stadt herum, aber ich habe einfach keine Zeit, vom Werft weg zu sein - Ich muss dringend spezielle Bestellungen abschließen.";
					link.l1 = "In Ordnung, ich werde es versuchen. Sag mir, wie sah dieses... Gerät von dir aus?";
					link.l1.go = "Device";
					link.l2 = "Das interessiert mich nicht.";
					link.l2.go = "Device_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Device");
					break;
				}//<-- генератор Неудачливый вор
			}
			dialog.text = "Ich habe nichts von dieser Art.";
			link.l1 = "Wie du sagst.";
			link.l1.go = "exit";
		break;
		
		case "Findship_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		
		case "Device_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		//--> Jason генератор Поиск корабля
		case "Findship":
			pchar.GenQuest.Findship.Shipyarder = "begin";
			pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
			ReOpenQuestHeader("Findship");
			AddQuestRecord("Findship", "1");
			AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Findship.Shipyarder.City+"Gen"));
			AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
			AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
			SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
			DialogExit();
		break;
		
		case "Findship_check":
			dialog.text = "Ausgezeichnet! Ich bin sehr froh, dass Sie es so schnell geschafft haben. Wo ist dieses Schiff?";
			link.l1 = "At the moment the vessel is at the roadstead; her name is '"+pchar.GenQuest.Findship.Shipyarder.ShipName+"'.";
				link.l1.go = "Findship_complete";
				break;
		
		case "Findship_complete":
			pchar.quest.Findship_Over.over = "yes";//снять прерывание
			sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			dialog.text = "Hier ist dein Geld - "+FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money))+". Danke für die Arbeit. Vergiss nicht, mich wieder zu besuchen. Auf Wiedersehen!";
			link.l1 = "Auf Wiedersehen, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
			AddQuestRecord("Findship", "3");
			AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
			CloseQuestHeader("Findship");
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		//<-- генератор Поиск корабля
		
		//Jason --> генератор Неудачливый вор
		case "Device":
			pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
			pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
			pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
			pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
			pchar.GenQuest.Device.Shipyarder.Money = 12000+rand(8000);
			//генерируем тип корабля для бонуса сейчас, чтобы не сливали
			if (sti(pchar.rank) < 2) iType = SHIP_SCHOONER; 
			if (sti(pchar.rank) >= 2 && sti(pchar.rank) < 5) iType = SHIP_BRIGANTINE; 
			if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 7) iType = SHIP_BRIG; 
			if (sti(pchar.rank) >= 7) iType = SHIP_CORVETTE + rand(makeint(SHIP_GALEON_H - SHIP_CORVETTE)); 
			pchar.GenQuest.Device.Shipyarder.Bonus = iType;
			dialog.text = "Natürlich werde ich versuchen, es in einfachen Worten zu erklären. Es sieht so aus "+pchar.GenQuest.Device.Shipyarder.Describe+". Es ist einzigartig, also wirst du es sehr leicht erkennen. Wenn du mir dieses Instrument bringst, werde ich dich fürstlich bezahlen.";
			link.l1 = "Verstanden. Ich fange sofort mit meiner Suche an!";
			link.l1.go = "exit";
			pchar.GenQuest.Device.Shipyarder = "begin";
			pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Device.Shipyarder.City = npchar.city;
			pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
			ReOpenQuestHeader("Device");
			AddQuestRecord("Device", "1");
			AddQuestUserData("Device", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Device.Shipyarder.City+"Voc"));
			AddQuestUserData("Device", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
			SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;
		
		case "Device_complete":
			pchar.quest.Device_Over.over = "yes";//снять прерывание
			dialog.text = "Du hast es geschafft! Du hast keine Ahnung, wie dankbar ich bin! Ich hatte schon jede Hoffnung aufgegeben, mein Instrument wiederzusehen.";
			link.l1 = "Hier, bitte.";
			link.l1.go = "Device_complete_1";
		break;
		
		case "Device_complete_1":
			RemoveItems(PChar, "Tool", 1);
			dialog.text = "Für deine Bemühungen werde ich dich bezahlen "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money))+". Ich hoffe, das wäre eine verdiente Belohnung.";
			link.l1 = "Danke!";
			link.l1.go = "Device_complete_2";
		break;
		
		case "Device_complete_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddQuestRecord("Device", "10");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
			CloseQuestHeader("Device");
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
			{
				dialog.text = "Im Übrigen möchte ich Ihnen ein Angebot machen, als zusätzlichen Dank.";
				link.l1 = "Das ist interessant. Nun, mach weiter - Ich mag angenehme Überraschungen.";
				link.l1.go = "Device_complete_3";
			}
			else
			{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
		break;
		
		case "Device_complete_3":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			dialog.text = "Ich habe gerade ein neues Schiff gestartet - "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType,"Name")+"Konto"))+". Es gibt bereits mehrere Kunden für dieses Schiff, aber ich gebe Ihnen Vorrang. Wenn Ihnen dieses Schiff gefällt und Sie sich nicht vor dem Preis fürchten - können Sie es kaufen.";
			link.l1 = "Heh! Sicher, lass uns mal nachsehen!";
			link.l1.go = "Device_complete_4";
			link.l2 = "Danke, aber mein aktuelles Schiff passt mir ganz gut und ich habe nicht vor, es zu ersetzen.";
			link.l2.go = "Device_complete_5";
		break;
		
		case "Device_complete_4":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
			DialogExit();
			LaunchShipyard(npchar);
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // лесник , митрокоста		   
		break;
		
		case "Device_complete_5":
			dialog.text = "Nun, wie du wünschst. Danke noch einmal - und viel Glück!";
			link.l1 = "Viel Glück auch dir!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// <-- генератор Неудачливый вор
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Lass mich mal nachdenken... Nein, so jemanden gab es nicht. Ich denke, du solltest dich wegen dieser Angelegenheit an den Hafenmeister wenden.";
				link.l1 = "Natürlich...";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "Let me take a look, Captain! A-ha! Those are the ship documents of a good friend of mine, my favorite customer! I am sure he will be extremely happy because of your find and will reward you deservedly.";
				sTemp = sTemp + "I guess I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " pesos on his behalf";
				dialog.text = sTemp;
				link.l1 = "Nein, das glaube ich nicht...";
				link.l1.go = "exit";
				link.l2 = "Danke, "+GetFullName(NPChar)+"! Bitte übermitteln Sie meinem Freund meine Hochachtung.";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "Ich höre Ihnen sorgfältig zu.";
			link.l1 = "Ich habe Ihren Flüchtling gebracht.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Oh, Kapitän, vielen Dank! Wie geht es ihr? Ist sie verletzt? Warum ist sie weggelaufen? Warum?\nVersteht sie nicht? Der Bräutigam ist ein reicher und wichtiger Mann! Die Jugend ist naiv und töricht... sogar grausam. Denk daran!";
			link.l1 = "Nun, du bist ihr Vater und die endgültige Entscheidung liegt bei dir, aber ich würde mit der Hochzeit nicht überstürzen...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Was wissen Sie schon? Haben Sie eigene Kinder? Nein? Wenn Sie eines haben, kommen Sie zu mir und wir werden reden.\nIch habe eine Belohnung für jeden versprochen, der sie zur Familie zurückbringt.";
			link.l1 = "Danke. Du solltest ein Auge auf sie werfen. Ich habe das Gefühl, dass sie damit nicht aufhören wird.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Oh, also bist du dieser Kapitän, der meiner verlorenen Sohn eine junge Braut gebracht hat?";
				link.l1 = "Ja, das war ich.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Oh, da "+GetSexPhrase("das ist er, unser Wohltäter","sie ist es, unsere Wohltäterin")+". Erwartest du eine Belohnung, nehme ich an?";
				link.l1 = "Nun, mir geht es gut ohne Belohnung, ein gutes Wort von dir würde mir schon reichen.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Ich bin Ihnen sehr dankbar, dass Sie mein Kind in einer schwierigen Situation nicht im Stich gelassen und ihm geholfen haben, einen Ausweg aus einer heiklen Situation zu finden. Lassen Sie mich Ihnen danken und bitte, nehmen Sie diese bescheidene Summe und ein Geschenk von mir persönlich an.";
			link.l1 = "Danke. Es war mir ein Vergnügen, diesem jungen Paar zu helfen.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Dank? Was für ein Dank?! Es ist ein halbes Jahr her, seit dieser Tölpel ohne Arbeit herumhängt - und schau ihn dir an, er hat genug Zeit für Liebschaften! Als ich in seinem Alter war, hatte ich bereits mein eigenes Geschäft! Pff! Ein Gouverneur hat eine heiratsfähige Tochter - und dieser Dummkopf hat eine Hure ohne Sippe oder Verwandtschaft in mein Haus gebracht und es gewagt, meinen Segen zu erbitten!";
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
			dialog.text = "Welche Gefühle? Von welchen Gefühlen sprichst du? Gefühle... wie kann man in deinem Alter so leichtsinnig sein?! Schande über dich, die Jugend in ihren Launen zu verwöhnen und als Kuppler zu handeln! Du hast nicht nur ein Mädchen aus ihrem Zuhause genommen, sondern auch das Leben meines Grünschnabels ruiniert. Es wird kein Dank für dich geben. Lebewohl.";
			link.l1 = "Also gut, und dir das Gleiche...";
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
		
		case "shipyard":
			if(CheckAttribute(npchar, "TrialDelQuestMark"))
			{
				DeleteAttribute(npchar, "TrialDelQuestMark");
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("PortRoyal");
			}
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Machst du Witze? Wo ist dein Schiff? Ich sehe es nicht im Hafen!","Ich schwöre beim Teufel, du wirst mich nicht täuschen! Dein Schiff ist nicht im Hafen!"),pcharrepphrase("Ich sehe Ihr Schiff nicht im Hafen, Kapitän "+GetFullName(pchar)+". Ich hoffe doch, sie ist nicht der 'Fliegende Holländer'?","Kapitän, es ist viel einfacher, die Ladung vom Pier zu laden. Bringen Sie Ihr Schiff zum Hafen und kommen Sie zurück."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Welch ein Ärger! Also gut, alter Schlawiner, bis bald!","Ich wollte dich nicht täuschen, "+GetFullName(npchar)+", ein Schiff auf der anderen Seite der Insel."),pcharrepphrase("Nein. Mein Schiff heißt 'Schwarze Perle'! Was ist mit deinem Gesicht passiert? Es ist blass... Haha! Witz!","Danke für den Rat, ich werde ihn sicher befolgen."));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Machst du Witze? Wo ist dein Schiff? Ich sehe es nicht im Hafen!","Ich schwöre beim Teufel, du wirst mich nicht täuschen! Dein Schiff ist nicht im Hafen!"),pcharrepphrase("Ich sehe Ihr Schiff nicht im Hafen, Kapitän "+GetFullName(pchar)+". Ich hoffe doch, sie ist nicht der 'Fliegende Holländer'?","Kapitän, es ist viel einfacher, die Ladung vom Pier zu laden. Bringen Sie Ihr Schiff in den Hafen und kommen Sie zurück."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Was für ein Ärger! Also gut, alter Schlitzohr, bis bald!","Ich wollte Sie nicht täuschen, "+GetFullName(npchar)+", ein Schiff auf der anderen Seite der Insel."),pcharrepphrase("Nein. Mein Schiff heißt 'Schwarze Perle'! Was ist mit deinem Gesicht passiert? Es ist blass... Haha! Witz!","Danke für den Rat, ich werde ihn sicher befolgen."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "Das Ändern der Farbe der Segel kostet "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+", das Ändern des Wappens kostet "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSGERALD_PRICE_RATE))+", die Segel auswechseln - hängt von deinem Schiff ab.";
							  
			    link.l1 = "Wähle eine neue Farbe.";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "Stellen Sie ein neues Wappen dar.";
			    link.l2.go = "SailsGeraldChoose";
				link.l3 = "Installiere einzigartige Segel."; 
				link.l3.go = "SailsTypeChoose";
			    Link.l9 = "Ich habe meine Meinung geändert.";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Machst du Witze? Wo ist dein Schiff? Ich sehe es nicht im Hafen!","Ich schwöre beim Teufel, du wirst mich nicht täuschen! Dein Schiff ist nicht im Hafen!"),pcharrepphrase("Ich sehe Ihr Schiff nicht im Hafen, Kapitän "+GetFullName(pchar)+". Ich hoffe doch, sie ist nicht der 'Fliegende Holländer'?","Kapitän, es ist viel einfacher, die Ladung vom Pier zu laden. Bringen Sie Ihr Schiff in den Hafen und kommen Sie zurück."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Was für Ärger! Na gut, alter Schlaukopf, bis bald!","Ich wollte dich nicht täuschen, "+GetFullName(npchar)+", ein Schiff auf der anderen Seite der Insel."),pcharrepphrase("Nein. Mein Schiff heißt 'Schwarze Perle'! Was ist mit deinem Gesicht passiert? Es ist blass... Haha! Witz!","Danke für den Rat, ich werde es sicher tun."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsTypeChoose":
			dialog.text = "Welche Segel möchtet Ihr installieren? Im Moment habt Ihr "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+".";
            Link.l6 = "Ich möchte installieren "+GetSailsType(6)+".";
			Link.l6.go = "SailsTypeChooseIDX_6";
			Link.l7 = "Ich möchte installieren "+GetSailsType(7)+".";
			Link.l7.go = "SailsTypeChooseIDX_7";
			Link.l8 = "Ich möchte installieren "+GetSailsType(8)+".";
			Link.l8.go = "SailsTypeChooseIDX_8";
			Link.l9 = "Ich möchte installieren "+GetSailsType(9)+".";
			Link.l9.go = "SailsTypeChooseIDX_9";
			Link.l10 = "Ich möchte installieren "+GetSailsType(10)+".";
			Link.l10.go = "SailsTypeChooseIDX_10";
			Link.l11 = "Ich möchte installieren "+GetSailsType(11)+".";
			Link.l11.go = "SailsTypeChooseIDX_11";
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
		    Link.l99 = "Ich habe meine Meinung geändert.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "Im Moment hast du "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+", Sie haben ausgewählt "+GetSailsType(sti(NPChar.SailsTypeChooseIDX))+". Die Kosten für den Ersatz betragen "+FindRussianMoneyString(sti(NPChar.SailsTypeMoney))+". Weiter?";

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
	            Link.l1 = "Ja.";
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = "Nein.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = "Ausgezeichnet! Alles wird gut sein.";
		    Link.l9 = "Danke.";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = "Welche Farbe sollen wir wählen? Der Preis beträgt "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = "Ich habe meine Meinung geändert.";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "Komm, wenn du das Geld hast.";
			    Link.l9 = "Gut.";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = "Einverstanden. Wir werden die Segel in "+GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name))+" Farbe.";
		    Link.l9 = "Danke.";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = "Leider kann Ihr Schiff kein Wappen tragen.";
				    Link.l9 = "Schade.";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "Komm zurück, wenn du das Geld hast.";
			    Link.l9 = "Gut.";
				Link.l9.go = "exit";	
			}
		break;

//--> -------------------------------------------Бремя гасконца---------------------------------------------------
		case "Sharlie":
			dialog.text = "Es tut mir leid, Sie zu enttäuschen, Monsieur, aber im Moment habe ich keine Schiffe zum Verkauf.";
			link.l1 = "Das ist wirklich seltsam, denn mir wurde gesagt, dass Sie einen brandneuen Kutter in Ihrer Werft haben.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = "Sie wissen, es geht wahrscheinlich um die Lugger, für die Michel de Monper eine Kaution von dreitausend Pesos hinterlegt hat? Also dieses Schiff ist bereits verkauft, denn laut Vertrag sollte der Gesamtbetrag spätestens eine Woche nach dem Abstieg des Schiffes ins Wasser bezahlt werden.\nAlle Fristen sind vorbei, und ich habe das Geld nicht erhalten, so wurde der Lugger verkauft. Es tut mir leid, Herr.";
				link.l1 = "Ja, das war wirklich Pech, in der Tat... Aber sind Sie sicher, dass Sie keine anderen Schiffe zum Verkauf haben?";
				link.l1.go = "Sharlie_6";
			}
			else
			{
			dialog.text = "Hmm. Ja, in der Tat. Aber...";
			link.l1 = "Und es gibt bereits eine Anzahlung darauf - fünftausend Peso. Michel de Monper, der das Geld hinterlegt hat, hat mir alle Rechte an diesem Schiff übertragen.";
			link.l1.go = "Sharlie_2";
			}
		break;
		
		case "Sharlie_2":
			int iDay = 3-sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
			sTemp = "You only have "+FindRussianDaysString(iDay)+"";
			if (iDay == 0) sTemp = "Today is the last day";
			dialog.text = "Nun, wenn das so ist, dann um unser Gespräch fortzusetzen, Herr. Wie Sie richtig bemerkt haben, habe ich die Anzahlung von fünftausend Pesos für das Schiff. Aber der volle Wert des Schiffes denke ich ist fünfzehntausend Pesos, zusammen mit Munition. Also zahlen Sie mir zehntausend und das Schiff gehört Ihnen.\nLaut Vertrag müssen Sie das Geld spätestens eine Woche nach dem Abstieg des Schiffes ins Wasser bezahlen. "+sTemp+", und dann bin ich frei, dieses Schiff an einen anderen Kunden zu verkaufen. Und, merken Sie sich, es gibt bereits einen, also sollten Sie sich besser beeilen.";
			if (sti(Pchar.money) >= 10000)
			{
				link.l1 = "Es gibt keinen Grund zur Eile. Ich habe die benötigte Summe gerade bei mir. Hier, bitte sehr.";
				link.l1.go = "Sharlie_4";
			}
			link.l2 = "Gut, gut. Sie werden Ihr Geld haben, Monsieur. Ich werde Sie nicht lange warten lassen.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = "Kann ich Ihnen helfen, Monsieur?";
				Link.l1 = "Ich bin nur vorbeigekommen, um einen Blick auf die verfügbaren Schiffe zu werfen... Aber im Moment bin ich ein bisschen beschäftigt - ich habe eine unerledigte Angelegenheit zu klären. Ich komme zurück, sobald ich damit fertig bin.";
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{	
				if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
				{
					dialog.text = "Herr, ich hatte Sie gewarnt, dass Sie nur drei Tage zur Verfügung hatten. Sie sind abgelaufen, und Sie haben mir immer noch kein Geld gebracht, also ist unser Geschäft abgelaufen, und ich habe das Schiff an einen anderen Kunden verkauft. Nichts für ungut.";
					link.l1 = "Ja, das war wirklich Pech, in der Tat ... Aber sind Sie sicher, dass Sie keine anderen Schiffe zum Verkauf haben?";
					link.l1.go = "Sharlie_6";
				}
				else
				{
					dialog.text = "Haben Sie mir zehntausend gebracht, Monsieur?";
					if (sti(Pchar.money) >= 10000)
					{
						link.l1 = "Sicher habe ich. Hier, bitte.";
						link.l1.go = "Sharlie_4";
					}
					link.l2 = "Nein, ich arbeite noch daran.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Sharlie_3";
				}
			}
		break;
		
		case "Sharlie_4":
			AddMoneyToCharacter(pchar, -10000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Dann erlauben Sie mir, Ihnen zu diesem erfolgreichen Kauf zu gratulieren. Das Schiff gehört Ihnen. Ich hoffe, es wird Ihnen gut dienen.";
			link.l1 = "Danke!";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "lugger";
			pchar.questTemp.Sharlie = "crew";
			//стартовый люггер
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 800, 40, 610, 16000, 15.2, 58.8, 1.42);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			//UpgradeShipParameter(pchar, "Cannons");
			pchar.ship.HP = 732; */
			//UpgradeShipFull(pchar);
			UpgradeShipParameter(pchar, "Capacity");
			RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull  = "q"; // belamour особый скин
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddCharacterGoods(pchar, GOOD_POWDER, 220);
			pchar.Ship.name = "Adeline";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_6":
			if (sti(Pchar.money) >= 15000)
				{
					dialog.text = "Hmm... Nun, ich habe tatsächlich einen, aber ich bin mir nicht sicher, ob er zu dir passen würde.";
					link.l1 = "Nun, ich kann es mir nicht leisten, jetzt zu wählerisch zu sein. Zeig mir, was du hast!";
					link.l1.go = "Sharlie_7";
				}
				else
				{
					dialog.text = "Hör zu, Monsieur, mach erst einen Haufen Geld und frag dann nach Schiffen, ja? Niemand hier wird dir etwas umsonst geben. Habe ich mich klar ausgedrückt?";
					link.l1 = "Vollkommen klar, obwohl es nicht nötig war, unhöflich zu sein. Gut, ich komme wieder, wenn ich das Geld habe.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_shipwait";
				}
		break;
		
		case "Sharlie_7":
			dialog.text = "Dann schau mal. Ich habe kürzlich zu einem vernünftigen Preis eine Schaluppe erworben. Dies war ein ehemaliges Piratenschiff, deren frühere Besitzer bereits sicher für zahlreiche Verbrechen gehängt wurden. Das Schiff ist ehrlich gesagt nicht so gut wie ein Logger und hat auch schwere Schäden, kann aber noch aufs Meer hinausfahren.\nIch habe jetzt keine Zeit, es zu reparieren - all meine Männer sind mit dem Bau einer Brigantine beschäftigt, die bestellt wurde, also kannst du es von mir im gleichen Zustand kaufen, in dem es sich befindet. Unter Berücksichtigung dessen werde ich es billiger als gewöhnlich verkaufen, während ich auch den Inhalt des Laderaums - fünfzehntausend Pesos - einbeziehe.";
			link.l1 = "Abgemacht. Sie ist seetüchtig, und das ist alles, was zählt. Guadeloupe ist ein Katzensprung entfernt - ich werde sie dort reparieren lassen, wenn du keine solche Möglichkeit hast.";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			AddMoneyToCharacter(pchar, -15000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Dann erlauben Sie mir, Ihnen zu diesem erfolgreichen Kauf zu gratulieren. Das Schiff gehört Ihnen. Ich hoffe, es wird Ihnen gut dienen.";
			link.l1 = "Danke!";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "sloop";
			pchar.questTemp.Sharlie = "crew";
			//стартовый шлюп
			pchar.Ship.Type = GenerateShipHand(SHIP_SLOOP, 6, 700, 50, 790, 20000, 13.1, 50.1, 1.25);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			AddCharacterGoods(pchar, GOOD_BALLS, 51);
			AddCharacterGoods(pchar, GOOD_GRAPES, 39);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
			AddCharacterGoods(pchar, GOOD_BOMBS, 36);
			AddCharacterGoods(pchar, GOOD_POWDER, 231);
			pchar.Ship.name = "Black Hound";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_shipwait":
			dialog.text = "Also, Monsieur, sind Sie mit dem Geld zurückgekommen?";
			if (sti(Pchar.money) >= 15000)
			{
				link.l1 = "Ja, ich denke, ich habe genug, um mir ein heruntergekommenes Schiff leisten zu können.";
				link.l1.go = "Sharlie_7";
			}
			else
			{
				link.l1 = "Ich habe noch nicht genug. Bin nur mal vorbeigekommen, um mich umzusehen...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_shipwait";
			}
		break;
//<-- -----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		case "FMQM_oil_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
			pchar.questTemp.FMQM = "remove_oil1";
		break;
		
		case "FMQM_oil_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil2";
		break;
		
		case "FMQM_oil_3":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil3";
		break;
		
		case "FMQM_oil_4":
			dialog.text = "Ach, mein Freund, wir haben beide hier gelitten. Sie haben das Harz beschlagnahmt und ich habe einen riesigen Geldbetrag für meine Kaution verschwendet. Und wie zum Teufel haben sie von unserer Operation erfahren? Muss einer meiner Arbeiter sein... Ich werde mich darum kümmern, der Herr habe Erbarmen mit dem Schuldigen!";
			link.l1 = "Das bedeutet, all meine Bemühungen waren umsonst...";
			link.l1.go = "FMQM_oil_5";
		break;
		
		case "FMQM_oil_5":
			dialog.text = "Es tut mir sehr leid, Kapitän. Wir können hier nichts tun, das Schicksal ist manchmal eine Schlampe.";
			link.l1 = "Ich verstehe. Gut, dann werde ich jetzt gehen. Auf Wiedersehen!";
			link.l1.go = "FMQM_oil_6";
		break;
		
		case "FMQM_oil_6":
			DialogExit();
			AddQuestRecord("FMQ_Martinique", "12");
			pchar.questTemp.FMQM = "officer";
			pchar.quest.FMQM_advice.win_condition.l1 = "location";
			pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
			DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_x":
            dialog.text = "Ich möchte zu diesem Gespräch zurückkehren. Ich bin bereit, einen anständigen Rabatt... einen sehr großen Rabatt für jede Arbeit an Ihrem Schiff zu geben... wenn Sie mir etwas zusätzliche Seide liefern...";
			link.l1 = "Meister, kommen wir gleich zur Sache. Ich verspreche, ich bin kein Spion und auch nicht einer von Colonel D'Oyleys Männern. Darüber hinaus arbeite ich mit Marcus Tyrex zusammen, ein Name, den Sie kennen sollten. Also, legen wir die Karten auf den Tisch. Ich weiß, Sie benötigen eine stetige Versorgung mit Seidentuch für Segel, und Marcus Tyrex ist bereit, es Ihnen zu bringen. Auch stetig. Allerdings nur im Fall, dass wir uns über den Preis einig sind. Sollen wir dann gleich dazu kommen, Meister?";
			link.l1.go = "mtraxx_x_1";
		break;
		
		case "mtraxx_x_1":
            dialog.text = "In Ordnung. Es scheint, als hätte ich keine Wahl - entweder du arbeitest für D'Oyley und wirst mich ins Gefängnis schicken, oder ich werde bankrott gehen, wenn ich nicht dringend eine große Lieferung Seide finde. Ich bin bereit, 25 Dublonen pro Stück zu zahlen, aber nur für große Lieferungen, nicht weniger als 100 Rollen.";
			link.l1 = "Dann haben wir einen Deal. Ich bin sicher, Tyrex kann Ihnen jeden Monat Lieferungen von 100 Rollen liefern.";
			link.l1.go = "mtraxx_x_2";
		break;
		
		case "mtraxx_x_2":
            dialog.text = "Das wäre ausgezeichnet! Ich könnte die erste Lieferung sofort kaufen.";
			link.l1 = "Kann es gerade jetzt nicht tun, aber es wird nicht lange dauern. Ein Schiff mit der Ladung, die Sie brauchen, befindet sich gerade in Capsterville, ich mache mich sofort auf den Weg dorthin und werde es zu Ihnen schicken. Wo sollen wir die Entladung vornehmen?";
			link.l1.go = "mtraxx_x_3";
		break;
		
		case "mtraxx_x_3":
            dialog.text = "Lassen Sie uns es so arrangieren. Zwischen dem 10. und 15. jeden Monats, nachts, werden meine Leute auf Ihre Besucher in der Bucht warten... nein, warte, besser am Kap Negril. Es wird sicher eine lange Fahrt sein, aber es gibt viel weniger Patrouillen... Das Passwort wird sein: 'Ein Händler aus Lyon'.";
			link.l1 = "Abgemacht, Meister. Ich mache mich sofort auf den Weg nach Capsterville.";
			link.l1.go = "mtraxx_x_4";
		break;
		
		case "mtraxx_x_4":
            dialog.text = "Ich hoffe, dass dein Schiff schnell ankommt, ich bin dringend auf neue Seide angewiesen.";
			link.l1 = "Mach dir keine Sorgen, alles wird gut. Viel Glück!";
			link.l1.go = "mtraxx_x_5";
		break;
		
		case "mtraxx_x_5":
			DialogExit();
            AddQuestRecord("Roger_2", "21");
			pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
			sld = characterFromId("Jeffry");
			sld.DeckDialogNode = "Jeffry_9";
		break;
		// Jason Исла Мона
		case "IslaMona":
			if (CheckAttribute(pchar, "questTemp.IslaMona.Shipyarder") && pchar.questTemp.IslaMona.Shipyarder == npchar.id)
			{
				if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
				{
					dialog.text = "Nein, "+pchar.name+". Ich habe nichts gegen dich, aber löse erst deine Probleme mit meinem Land. Den Verkauf eines so wertvollen Inventars an einen Feind der Krone könnte missverstanden werden.";
					link.l1 = "Ja, und wenn ihr geschmuggelte Waren unklarer Herkunft in Schiffe schmuggelt, seid ihr besten Freunde? Wartet, bis ich dieses Missverständnis kläre.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Sagen wir mal. Warum? Baust du etwas?";
					link.l1 = "Nein, ich mache eine ganz besondere Charter. Für einen Plantagenmanager.";
					link.l1.go = "IslaMona_1";
				}
			}
			else
			{
				npchar.quest.IslaMonaTools = "true";
				dialog.text = "Ich kann dir nicht helfen.";
				link.l1 = "Es ist eine Schande!";
				link.l1.go = "exit";
			}
		break;
		
		case "IslaMona_1":
            dialog.text = "Ich verstehe. Ich hoffe, dieser Manager hat genug für dich bereitgestellt, denn ich würde viel für ein solches Set verlangen. Du hast großes Glück, dass du kürzlich eine Einfuhr aus der Metropole hattest.";
			link.l1 = "Wie viel?";
			link.l1.go = "IslaMona_2";
		break;
		
		case "IslaMona_2":
			pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
            dialog.text = "Eintausend Gold-Dublonen.";
			link.l1 = "Du überhitzt, sehe ich. Mir geht's gut. Ich nehme es.";
			link.l1.go = "IslaMona_7";
			link.l2 = "Es ist zu viel. Ich bezweifle, dass es einen anderen Käufer für das gesamte Set wie mich geben wird. Einiges wird ausverkauft sein, einiges wird von den örtlichen Landstreichern gestohlen werden. Wie wäre es mit einem Rabatt?";
			link.l2.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				notification("Skill Check Failed (60)", SKILL_COMMERCE);
				dialog.text = "Ich garantiere, es wird auftauchen. Keine Preisänderung. Wie wär's? Ich warte nicht lange.";
				link.l1 = "Gut, in Ordnung, in Ordnung. Ich nehme es.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 900;
				dialog.text = "In Ordnung, wir nehmen hundert. Neunhundert. Ich gehe nicht tiefer. Frag mich nicht danach.";
				link.l1 = "Und ich werde nicht. Ich stimme zu.";
				link.l1.go = "IslaMona_7";
				link.l2 = "Warum gibst du mir nicht etwas mehr? Als Großhändler. Und dann werde ich bei dir Reparaturen und Farben bestellen, und das saftigste Galionsfigur.";
				link.l2.go = "IslaMona_4";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
		break;
		
		case "IslaMona_4":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 85)
			{
				notification("Skill Check Failed (85)", SKILL_COMMERCE);
				dialog.text = "Es ist mir egal, ob du eine lebendige Dirne bestellst. Neunhundert.";
				link.l1 = "Gut, gut, gut. Ich nehme es.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 800;
				dialog.text = "Bist du sicher? Du wirst es nicht vergessen? Gut, lass uns noch hundert abziehen. Aber das ist es!";
				link.l1 = "Ich werde es nicht vergessen. Abgemacht!";
				link.l1.go = "IslaMona_7";
				link.l2 = "Nun, wie soll ich das ausdrücken...";
				link.l2.go = "IslaMona_5";
				AddCharacterExpToSkill(pchar, "Fortune", 200);
			}
		break;
		
		case "IslaMona_5":
            dialog.text = "Undenkbar! "+pchar.name+", sie haben vergessen, das Schrotstück aus deinem Schädel zu entfernen? Gierig wie ein Skorpion! Wir haben alle von deinen jüngsten Eskapaden gehört! Du hast dein Goldhaufen schon verdient, also hindere andere nicht daran, ihren zu verdienen. Noch ein Wort und ich verkaufe nicht für weniger als tausend.";
			link.l1 = "In Ordnung, in Ordnung! Beruhige dich. Ich stimme zu.";
			link.l1.go = "IslaMona_7";
			link.l2 = "Aber, "+npchar.name+", Ich habe kleine Kinder! Ich muss auch an sie denken! Du bekommst nicht genug bezahlt für ehrlichen Frachtverkehr, das weißt du!";
			link.l2.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 100)
			{
				notification("Skill Check Failed (100)", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
				dialog.text = "Kinder von Bordellmädchen zählen nicht, "+pchar.name+". Ich habe genug von dir. Tausend Dublonen auf das Fass, oder wir sagen auf Wiedersehen.";
				link.l1 = "Was meinst du, sie sind es nicht? Ah ja. Ich stimme zu, du bist ein Schurke.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 800);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 700;
				dialog.text = "Ich wusste nicht, dass du Kinder hast. Und dass die Dinge so schlecht stehen. Gut, beschwere dich nicht. Siebenhundert. Es ist fast ein Verlust.";
				link.l1 = "Ich werde es nicht vergessen. Es ist ein Deal!";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Fortune", 400);
				Achievment_SetStat(106, 1);
			}
		break;
		
		case "IslaMona_7":
            dialog.text = "Also, du schuldest mir "+sti(pchar.questTemp.IslaMona.Shipyarder.Money)+" Dublonen.";
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.IslaMona.Shipyarder.Money))
			{
				link.l1 = "Hier, ich gebe dir das Letzte davon, ich habe nichts mehr übrig.";
				link.l1.go = "IslaMona_8";
			}
			else
			{
				if (GetCharacterItem(pchar, "gold_dublon") < 1)
				{
					link.l1 = "Warte, ich gehe zum Kredithai, um Schulden zu machen.";
					link.l1.go = "IslaMona_money_exit";
				}
				else
				{
					link.l1 = "Alles, was ich bei mir habe "+FindRussianDublonString(GetCharacterItem(pchar,"Gold-Dublone"))+". Nimm das, und ich gehe zu den Kredithaien.";
					link.l1.go = "IslaMona_money";
				}
			}
		break;
		
		case "IslaMona_money":
			pchar.questTemp.IslaMona.Shipyarder.Money = sti(pchar.questTemp.IslaMona.Shipyarder.Money)-GetCharacterItem(pchar, "gold_dublon");
			Log_Info("You gave "+FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon"))+"");
			RemoveItems(pchar, "gold_dublon", GetCharacterItem(pchar, "gold_dublon"));
			PlaySound("interface\important_item.wav");
            dialog.text = "Tut mir nicht leid, du hast eine Kajütenablage voller Gold. Du wirst mir schulden "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+".";
			link.l1 = "";
			link.l1.go = "IslaMona_money_exit";
		break;
		
		case "IslaMona_money_exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.quest.IslaMonaMoney = "true";
			pchar.questTemp.IslaMona = "dublon";
		break;
		
		case "IslaMona_8":
			Log_Info("You gave "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+"");
			RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.IslaMona.Shipyarder.Money));
			PlaySound("interface\important_item.wav");
            dialog.text = "Das ist großartig. Der volle Betrag ist vorhanden. Die Werkzeuge werden zu Ihrem Schiff geliefert. Das sind einige schwere Kisten.";
			link.l1 = "Danke, "+npchar.name+"!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			GiveItem2Character(pchar, "islamona_toolbox");
			DeleteAttribute(pchar, "questTemp.IslaMona.Shipyarder");
			DeleteAttribute(npchar, "quest.IslaMonaMoney");
			AddQuestRecord("IslaMona", "2");
			pchar.questTemp.IslaMona = "get_tools";
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;
	
	switch (_type)
	{
	    case 1 : sSail = ""+XI_ConvertString("sails_1")+""; break;
	    case 2 : sSail = ""+XI_ConvertString("sails_2")+""; break;
	    case 3 : sSail = ""+XI_ConvertString("sails_3")+""; break;
		case 4 : sSail = ""+XI_ConvertString("sails_4")+""; break;
		case 5 : sSail = ""+XI_ConvertString("sails_5")+""; break;
		case 6 : sSail = ""+XI_ConvertString("sails_6")+""; break;
		case 7 : sSail = ""+XI_ConvertString("sails_7")+""; break;
		case 8 : sSail = ""+XI_ConvertString("sails_8")+""; break;
		case 9 : sSail = ""+XI_ConvertString("sails_9")+""; break;
		case 10 : sSail = ""+XI_ConvertString("sails_10")+""; break;
		case 11 : sSail = ""+XI_ConvertString("sails_11")+""; break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) == 1) iRank = 0;
	if (sti(pchar.rank) > 1 && sti(pchar.rank) <= 2) iRank = 1;
	if (sti(pchar.rank) > 2 && sti(pchar.rank) <= 4) iRank = 2;
	if (sti(pchar.rank) > 4 && sti(pchar.rank) <= 7) iRank = 3;
	if (sti(pchar.rank) > 7 && sti(pchar.rank) <= 10) iRank = 4;
	if (sti(pchar.rank) > 10 && sti(pchar.rank) <= 18) iRank = 5;
	
	int iClassFlag = FLAG_SHIP_CLASS_5;
	int iTypesFlag = FLAG_SHIP_TYPE_MERCHANT;
	switch (iRank)
	{
		case 0:  
			iClassFlag = FLAG_SHIP_CLASS_5;
		break; 		
		case 1:  
			iClassFlag = FLAG_SHIP_CLASS_4;
		break;
		case 2:  
			iClassFlag = FLAG_SHIP_CLASS_4;
		break;
		case 3: 
			iClassFlag = FLAG_SHIP_CLASS_3;
		break;
		case 4:  
			iClassFlag = FLAG_SHIP_CLASS_3;
			iTypesFlag = or(FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_TYPE_WAR);
		break;
		case 5: 
			iClassFlag = FLAG_SHIP_CLASS_2;
			iTypesFlag = or(FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_TYPE_WAR);
		break;
	}
	
	pchar.GenQuest.Findship.Shipyarder.ShipType = GetRandomShipType(iClassFlag, iTypesFlag, FLAG_SHIP_NATION_ANY);
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial);
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда 
	 1 - товар	 
	 2 - цена в дублонах(сундуки)
  Функция возвращает кол-во материала необходимого для данного типа апгрейда	  
*/

int GetMaterialQtyUpgrade( ref _chr, ref _nchar, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	float fQuestShip 	= 1.0;
	float LEcoeff       = 1.0; // legendary edition
		
	int   	shipClass     		= sti(RealShips[sti(_chr.Ship.Type)].Class);	
	int   	shipMinCrew   		= sti(RealShips[sti(_chr.Ship.Type)].MinCrew);	
	int 	shipPrice			= sti(RealShips[sti(_chr.Ship.Type)].Price);	
		
    if(shipClass == 4) LEcoeff = 0.38;
    if(shipClass > 4) LEcoeff = 0.25;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 	fQuestShip = 1.3;	

	if(MaterialNum == 1) 
	{
	int Material 	= makeint((40 * (7 - shipClass) + 25 * MOD_SKILL_ENEMY_RATE + drand(shipMinCrew)) * fQuestShip * LEcoeff);
	if(Material < 1) 		Material 	= 1;
		return Material;
	}
	if(MaterialNum == 2)
	{
		int WorkPrice 	= 1;
		switch (shipClass)
		{
			case 1: 
				WorkPrice = 10;
			break;
			case 2: 
				WorkPrice = 7;
			break;
			case 3: 
				WorkPrice = 5;
			break;
			case 4: 
				WorkPrice = 3;
			break;
			case 5: 
				WorkPrice = 1;
			break;
		}
		return WorkPrice;
	}
	
	return 0;
}
// belamour legendary edition тюнинг - проверка на сделанное
bool TuningAvailable()
{
	int num = 0;
    ref shTo = &RealShips[sti(Pchar.Ship.Type)];

	if(CheckAttribute(shTo, "Tuning.SpeedRate"))    num++;
	if(CheckAttribute(shTo, "Tuning.WindAgainst"))  num++;
	if(CheckAttribute(shTo, "Tuning.Cannon"))       num++;
	if(CheckAttribute(shTo, "Tuning.Capacity"))     num++;
	if(CheckAttribute(shTo, "Tuning.HP"))           num++;
	if(CheckAttribute(shTo, "Tuning.MaxCrew"))      num++;
	if(CheckAttribute(shTo, "Tuning.TurnRate"))     num++;
	if(CheckAttribute(shTo, "Tuning.MinCrew"))      num++;
	
	if(sti(shTo.Class) > 4 && num == 7 && !CheckAttribute(shTo, "Tuning.MinCrew"))
	{
		if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
	}
	
	if(num < 8) return true;
	else
    {
        if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
    }
}