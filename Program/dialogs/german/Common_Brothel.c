void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
		
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - hrand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;
	
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Was für Mädchen, Liebling?! Die halbe Garnison ist hinter dir her, und du kommst direkt ins Bordell!","Verschwinde, kannst du? Die halbe Garnison ist hinter dir her!")+"","Jeder Stadtwächter sucht nach dir. Ich bin kein Narr, um dir in diesem Moment Dienste anzubieten ...","Du hast hier nichts zu tun!"),LinkRandPhrase(""+GetSexPhrase("Trau dich nur, meine Mädchen zu berühren und ich werde dich bei lebendigem Leib häuten!","Verschwinde, du Schurke!")+"","Dreckig"+GetSexPhrase("","")+" Mörder, verlasse mein Etablissement, jetzt! Wachen!!!","Ich habe keine Angst vor dir, "+GetSexPhrase("Schurke","Ratte")+"! Bald wirst du in unserer Festung gehängt, du wirst nicht weit kommen..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, ein Alarm ist für mich nie ein Problem...","Sie werden mich niemals fangen."),RandPhraseSimple("Halt einfach den Mund, dumme Alte.","Halt den Mund, wenn du keine Probleme willst..."));
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "Oh, "+GetSexPhrase("junger Mann","süßes Kind")+", wir haben heute geschlossen.";
				link.l1 = "Geschlossen?";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Мерзкий Божок
			if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog")) {
				dialog.text = "Oh, mein Gott! Wie bist du hier reingekommen? Lieber Kapitän, bitte geh - ich flehe dich an! Unser Etablissement ist derzeit geschlossen!";
				link.l1 = "Schön dich zu sehen, Lieber "+npchar.name+". Ich stand auf der Gästeliste. Allerdings muss man in solchen Einrichtungen auch als Gast bezahlen, also... Bitte mach mir das nicht zu schwer, aber ich möchte für ein Zimmer bezahlen.";
				link.l1.go = "chicken_god";
				
				DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
				break;
			}
			//<-- Мерзкий Божок
			//--> туториал Мартиника
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Hör zu, Aurora, ich brauche eine Frau für die Nacht. Und ich will sie mit nach Hause nehmen. Kannst du das arrangieren?";
                link.l1.go = "Gigolo";
				break;
			}
			//<-- туториал Мартиника
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.Block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "Sie sind ein so stattlicher Mann. Darüber hinaus mögen meine Mädchen Sie sehr. Ich möchte Sie um einen kleinen Gefallen für mein Etablissement bitten.";
				link.l5 = "Ich fühle mich geschmeichelt, das ist sicher. Wobei brauchst du meine Hilfe?";
				link.l5.go = "Badboy";
				link.l8 = "Es tut mir leid, aber ich bin gerade beschäftigt.";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "Oh, du bist zurückgekehrt! Hast du das arrangiert "+pchar.GenQuest.Badboy.Brothel.Name+", meine Mädchen in Ruhe zu lassen?";
					link.l5 = "Ja. Er wird sein Gesicht hier nicht mehr zeigen.";
					link.l5.go = "Badboy_complete";
				break;
				}
			}
			// <-- Заносчивый аристократ
			
			//--> Jason Португалец
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0)
				{
					DelMapQuestMarkCity("marigo");
					DelLandQuestMark(npchar);
					dialog.text = "Kapitän, darf ich Sie um einen Gefallen bitten?";
					link.l5 = "Für Sie, Madame, alles was Sie mögen! Ich stehe zu Ihren Diensten!";
					link.l5.go = "Portugal";
					link.l8 = "Es tut mir leid, aber ich bin gerade beschäftigt.";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Haben Sie mit Hugo gesprochen, Mynheer Kapitän?";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "Darüber hinaus, Madame, hier ist Ihr Geld. Alles lief auf die günstigste Weise...";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "Ja, ich habe ihm Ihre Anfrage übermittelt.";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Oh mein Gott, schau dir das an! Charlie Prince, ein berühmter Korsar! In Fleisch und Blut!";
				link.l1 = RandSwear()+"Hallo, Janette. Ich bin hier auf der Mission für Marcus Tyrex.";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Bist du bereit für eine unvergessliche Erholungsbehandlung, mein tapferer Korsar?";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "Ich bin's! Charlie Prince verschwendet nicht so viele Worte wie er Geld verschwendet, ha-ha!";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "Fast... Ich glaube, ich habe eine Geldbörse in Ihrer Einrichtung verloren... Ich komme mit Geld zurück!";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Willkommen in meinem Haus der Liebe. Mein Name ist "+npchar.name+", und ich bin der Besitzer. "+GetSexPhrase("Was kann ich für Sie tun, "+GetAddress_Form(NPChar)+"?","Ehrlich gesagt, bin ich ein wenig überrascht, dich hier zu sehen, "+GetAddress_Form(NPChar)+", aber ich versichere Ihnen, dass wir Dienste nicht nur für Männer erbringen.")+"",TimeGreeting()+". Ich begrüße dich, "+GetSexPhrase("Fremder","junge Dame")+", zu meiner bescheidenen Einrichtung. Lassen Sie mich mich vorstellen, ich bin "+NPChar.Name+" - Halter dieser Zuflucht für Männer, hungrig nach einer Frau Berührung. "+GetSexPhrase("Was kann ich für Sie tun?","Obwohl wir auch ein oder zwei Dinge für Damen haben...")+"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+"?",TimeGreeting()+". Was kann ich für Sie tun, "+GetAddress_Form(NPChar)+"?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идёт квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name+", Ich möchte etwas qualitätsvolle Zeit mit einem deiner Mädchen verbringen.";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идёт старт Шарля
			{
				if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - а смысл, если нет как корабля, так и команды?
				{
					link.l3 = "Es ist eine Weile her, seit ich meine Männer das letzte Mal verwöhnt habe. Kann ich eine Großbestellung von Mädchen für meine Leute machen?";
					link.l3.go = "ForCrew";
				}
			}
			link.l4 = "Ich habe eine Frage.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
				link.l4.go = "quests";//(перессылка в файл города)
			}	
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "Hör zu, "+npchar.name+", ich suche nach dem Ring des Gouverneurs. Er hat sich in Ihrer Einrichtung ausgeruht und hat ihn wahrscheinlich hier verloren.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра

			// belamour ночной приключенец -->
			if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
			{
				link.l8 = "Schau mal, ich möchte das beste Mädchen, das du hast.";
				link.l8.go = "NA_Girl";
			}
			// <-- приключенец
			link.l9 = "Macht nichts, ich gehe schon.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("Was willst du, Schöner?","Ich höre Ihnen zu, Kapitän.");
				link.l1 = "Hör zu, "+npchar.name+", ich habe diese Papiere in einem privaten Raum Ihrer Institution gefunden ...";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Lass mich sehen! Hmm... irgendein Kapitän hat seine Dokumente verloren, richtig? Ich denke, du solltest den Hafenmeister danach fragen.";
				link.l1 = "Vielleicht, vielleicht...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Lass mich mal sehen! Oh! Dem Namen nach zu urteilen, gehören sie meinem geschätzten Kunden und einem würdigen Bürger unserer Stadt. Ich kann ihm diese Dokumente selbst übergeben.";
				link.l1 = "Wahrscheinlich nicht...";
				link.l1.go = "exit";
				link.l2 = "Ausgezeichnet! Immer froh, einer guten Person und einer würdigen Einrichtung zu helfen.";
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+GetSexPhrase("Wir sind immer glücklich, einem Kunden zu dienen. Nun sag mir, Hübscher - hast du schon jemanden ausgewählt oder ist es dir egal?","Nun, meine Mädchen können sicherlich... Ihnen helfen. Haben Sie schon jemanden ausgesucht oder ist es Ihnen egal?")+"";
					Link.l1 = ""+GetSexPhrase("Heh, ich brauche jetzt sofort eine Hure. Mir ist egal welche, deine Mädchen sehen alle gut aus für mich...","Jeder wird in Ordnung sein, wenn sie ihre Pflichten kennt, natürlich...")+"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "Ja, es gibt einen, "+GetSexPhrase("wer hat meine Laune genommen...","sie wäre die Netteste...")+"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "Ich habe heute keine freien Mädchen für dich, wir haben bereits zu viele Kunden. Komm morgen, und du wirst es nicht bereuen!";
					Link.l1 = "Schade, ich hatte gerade erst angefangen, es zu genießen.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. Du hast bereits für das Mädchen bezahlt. Lenk mich bitte nicht ab.";
				Link.l1 = "In Ordnung, ich komme.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "Ich habe im Moment keine freien Mädchen, Sie müssen in ein paar Tagen wieder nachsehen.";
				Link.l1 = "Gut, wie du sagst.";
				Link.l1.go = "exit";	
			}
			else
			{
				// belamour legendary edition Орден Святого Людовика -->
				if(IsEquipTalisman9() && npchar.nation == FRANCE)
				{
					dialog.text = ""+GetSexPhrase("Nun, Hengst, das ist ausgezeichnet!","Ich habe sie alle geschickt, da kannst du sicher sein.")+"Ich kann ein hübsches Mädchen namens anbieten "+GetFullName(sld)+", sie ist jetzt frei.\nOh, was versteckst du dort so bescheiden?! Ist das die höchste Auszeichnung in Frankreich? Gerüchte besagen, dass die Träger dieses Abzeichens nicht nur auf dem Schlachtfeld legendär sind... Nun, du weißt, was ich meine, mein Filibuster... Außerdem würde jeder es als Ehre betrachten, deine 'Ordnung' zu berühren, also ruhst du heute auf Kosten meiner Einrichtung. Ablehnungen werden nicht akzeptiert, Schönling.";
					Link.l1 = "Natürlich stimme ich zu, welche Fragen könnten da sein?!";
					Link.l1.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
					break;
				}
				// <-- legendary edition
				dialog.text = ""+GetSexPhrase("Nun, ausgezeichnet, mein Hengst!","Sie sind alle sehr geschickt in dem, was sie tun, zweifellos.")+" Ich kann Ihnen ein sehr nettes Mädchen anbieten, ihr Name ist "+GetFullName(sld)+", und sie ist im Moment frei. Dieses Vergnügen wird dich kosten "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". Einverstanden?";
				Link.l1 = "Nein. Ich nehme an nicht. Es ist zu teuer...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "Natürlich, wie könnte ich ablehnen?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "Oh Mist, ich habe nicht so viel Geld dabei...";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "Gut, "+GetSexPhrase("schön","schön")+". "+sld.name+" wird in einem privaten Zimmer im zweiten Stock auf dich warten.";
				Link.l1 = ""+GetSexPhrase("Gut, ich komme dann","Gut, dann komme ich")+"...";
				Link.l1.go = "exit";
				// belamour legendary edition деньги только без ордена или адмиральского мундира
				if(IsEquipTalisman9())
				{
					if(npchar.nation != FRANCE) AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				else
				{
					AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// генератор найденных бумаг
				
				// belamour legendary edition не давать квесты губернатору и адмиралу
				bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor");
				bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4;
				
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10 && !MCGovernon && !MCAdmiral ) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
										
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("The papers are in location " + sld.startLocation + ", in locator " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				// генератор - "Повод для спешки"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !MCGovernon && !MCAdmiral) // Addon-2016 Jason
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}				
			}
			else
			{
				dialog.text = "Oh, Sie sehen, das Problem ist, dass "+sld.name+" ist kein billiges Mädchen, ihr Preis ist "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". Und ich sehe, dass du dir sie momentan einfach nicht leisten kannst. Komm zurück, wenn du reich bist"+GetSexPhrase(", Lieber","")+"..., Freund.";
				Link.l1 = "So ist mein Glück...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "Ich bin immer glücklich, wenn Mädchen und Kunden warme Gefühle füreinander entwickeln... Sag mir ihren Namen.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Hmm... du musst dich irren. Ich habe kein solches Mädchen in meiner Einrichtung. Vielleicht hast du ihren Namen falsch verstanden.";
				Link.l1 = "Hmm... aber ich habe gerade erst mit ihr gesprochen.";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "Vielleicht. Es wäre besser, noch einmal ihren Namen zu fragen, nur um sicher zu sein. Ich werde später mit dir darüber sprechen.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld)+", sprichst du von ihr?";
				Link.l1 = "Ja, über sie.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "Nein, sie ist es nicht.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "Dann solltest du mir vielleicht noch einmal ihren Namen sagen, und vielleicht werde ich dann erkennen, über wen du redest.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Vielleicht. Es wäre besser, ihren Namen noch einmal zu fragen, nur um sicher zu sein. Ich werde später mit dir darüber sprechen.";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Hmm... Willst du deinen Leuten helfen, 'Dampf abzulassen'? Siehst du, meine Einrichtung ist eine seriöse, und ich habe die besten Mädchen hier. Aber ich kenne einige Hafenhuren, und sie werden sich freuen, all deine Matrosen zu erfreuen. Das wird dich kosten "+FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost)+".";			
			link.l1 = "Gut, ich stimme zu.";
			link.l1.go = "ForCrew_1";
			link.l2 = "Sie kommen wohl auch ohne aus...";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*crewWhoreCost && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*crewWhoreCost));
	            AddCrewMorale(Pchar, 10);
				ChangeCharacterComplexReputation(pchar,"authority", 1);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "Es geht mich nichts an, aber ich denke, dass du zuerst genug Geld verdienen solltest, um eine Crew anzuheuern, und dir erst dann Sorgen um ihren Geist machen solltest.";
			    link.l1 = "Du hast wahrscheinlich recht...";
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = "Lieber, was machst du da?! Und du sahst aus wie ein anständiger Kapitän... Du wirst diesmal nicht 'wegfliegen', Hübscher. Die Wachen werden dir die Flügel abschneiden...";
			link.l1 = "Halt den Mund, alte Hexe.";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "Ich habe keinen Ring gefunden.";
			link.l1 = "Und eure Mädchen?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "Sie haben es auch nicht. Wenn ein Kunde etwas vergisst oder verliert, bringen meine Mädchen es zu mir. Aber niemand hat mir den Ring des Gouverneurs gebracht.";
			link.l1 = "Ich verstehe... Aber könnte es sein, dass sie beschlossen haben, es für sich zu behalten?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "Unwahrscheinlich. Mädchen dürfen Geschenke von den Kunden behalten, aber das ist alles.";
			link.l1 = "Ich verstehe. Nun, danke, "+npchar.name+".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "Oh, hier bist du...";
			link.l1 = "Hier bin ich, meine Dame!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				dialog.text = ""+sld.name+"! Mein Held, ich sehe, dass du deine Zeit unten nicht verschwendet hast!";
				link.l1 = "Ich hoffe, Ihr werdet mir diese Schwäche verzeihen, meine Königin?";
				link.l1.go = "RomNaTroih_2";
			}
			AddDialogExitQuestFunction("SexWithHostess_fack");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.RomNaTroih");
            if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 10);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 5);
		break;
		
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Du solltest besser das Etablissement verlassen!","Alle Wachen in der Stadt suchen nach dir! Es wäre besser für dich zu gehen...","Du hast ein Chaos angerichtet und jetzt tauchst du hier auf?! Nein, nicht diesmal..."),LinkRandPhrase("Verschwinde!","Dreckiger Mörder, verschwinde hier! Wachen!","Ich habe keine Angst vor dir,"+GetSexPhrase("Schurke","Ratte")+"! Bald wirst du in unserer Festung gehängt werden, du wirst nicht weit kommen..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, ein Alarm ist für mich nie ein Problem...","Sie werden mich nie fangen."),RandPhraseSimple("Heh, was für eine dumme Dirne du bist...","Halt den Mund, Hure, oder ich werde ihn mit etwas anderem verschließen..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("Hallo, "+GetAddress_Form(NPChar)+""+GetSexPhrase("",", hee-hee..")+". Sie müssen zur Dame gehen und den Auftrag ausfüllen.","Du schon wieder? Bitte sprich mit der Wirtin. Sie ist in ihrem Büro.","Schau, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", Ich hoffe doch, dass du in anderen Dingen genauso hartnäckig bist wie beim Reden... Wieder","Noch einmal")+" Ich bitte Sie, den Besitzer des Etablissements zu sehen.","Oh, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", bist du ein sturer Kerl!",", Hee-hee... Du bist ein sturer Bursche, nicht wahr?")+" Sie müssen zur Dame gehen und die Bestellung ausfüllen.","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("In Ordnung, "+GetSexPhrase("Schönheit, ","")+"Ich habe es"+GetSexPhrase("","")+".","Ja, klar...",""+GetSexPhrase("Habe keinen Zweifel, mein Hübscher, ich bin so stur und stark wie ein Stier!","Ja, ja...")+"",""+GetSexPhrase("Oh verdammt, ich muss etwas übersehen haben... Es tut mir leid, Liebling.","Gut, in Ordnung.")+"",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "Und wo ist sie?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+GetSexPhrase("Oh, Schönheit, ich wette, ich könnte in diesen Augen von dir ertrinken...","Du siehst wunderschön aus, Liebling!")+"",""+GetSexPhrase("Sie wissen, ich habe noch nie so eine schöne Frau getroffen!","Du weißt, ich habe noch nie so eine nette Dame getroffen!")+"",""+GetSexPhrase("Liebling, du siehst wunderschön aus.","Verdammt, ich war so müde von all diesen Hinterwäldlern... Und du bist so charmant!")+"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("Hör zu, "+GetSexPhrase("Schönheit","Schatz")+", hast du hier vielleicht einen Ehering gefunden? Ein Mann scheint ihn verloren zu haben...","Liebling, hast du einen Ehering oder so etwas gesehen?","Hör zu, "+GetSexPhrase("mein Kätzchen","Schatz")+", hast du hier irgendwo einen Ehering gesehen?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "Hallo, Liebling. Marcus Tyrex hat mich geschickt, schau dir diese Bernsteinhalskette an...";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "Sie ist in ihrem Büro. Sie können von hier aus durch die Tür gegenüber dem Ausgang zur Straße dorthin gelangen, oder von der Straße auf der anderen Seite des Hauses. Ihr Name ist "+characters[GetCharacterIndex(npchar.city+"_Hostess")].name+".";
			Link.l1 = "Ich verstehe, "+GetSexPhrase("Schatz","Schatz")+", danke.";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("Oh mein Gott, es ist so schön, solche Dinge zu hören! Hey, ich habe gerade Zeit, also wenn du mich auswählst, wirst du es nicht bereuen...","Glaubst du wirklich? Weißt du, das ist so süß... Hör zu, ich habe gerade Zeit, also kannst du mich aussuchen."+GetSexPhrase(" Ich verspreche dir das Meer der Liebe und einen Ozean der Zärtlichkeit...","")+"",""+GetSexPhrase("Glaubst du das wirklich? Oh, ich fühle mich wirklich geschmeichelt. Weißt du, ich höre selten solche Komplimente...","Oh, Mädchen... wenn du nur wüsstest, wie satt ich diese Landeier habe...")+" Hey, hör mal, ich bin im Moment frei, also kannst du mich auswählen, um dich glücklich zu machen. Ich werde dich nicht enttäuschen, das verspreche ich...");
				if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
				{
					link.l1 = "Meine Liebe, genau das hatte ich vor! Wie glücklich, dass deine Gastgeberin bereits ein privates Treffen mit mir oben arrangiert hat. Möchtest du dich uns anschließen?";
					Link.l1.go = "RomNaTroih_1";
					pchar.questTemp.RomNaTroih_Pogovoril = true;
					break;
				}
				link.l1 = "Nun, dann wähle ich dich!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+GetSexPhrase("Nein, das war nur ein Kompliment für eine nette Dame","Das war nur ein Kompliment")+".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+GetSexPhrase("Weißt du, was ich sage, Süße? Ich brauche dieses billige Gerede nicht. Mach Geschäfte oder geh!","Das ist alles, was ich brauchte! Komplimente von Frauen!")+"",""+GetSexPhrase("Bist du einer von denen, die glauben, dass Frauen mit ihren Ohren lieben? Nun, Lieber, das ist einfach nicht wahr. Wenn du mich willst, dann zahle der Madame und erlöse mich von deinen leeren Worten.","Lass, verschwende dich nicht mit hohlen Worten. Wenn du es ernst meinst - dann zahle...")+"",""+GetSexPhrase("Oh, ein weiterer Liebhaber der Sinnlichkeit... Du zahlst einfach und ich gehöre dir. Es ist alles so einfach, ohne all diesen sanften Unsinn!","Was ist los mit dir, Liebling? Wenn du dich Vergnügungen hingeben willst, dann zahl einfach und hör auf mit dem ganzen Unsinn!")+"");
				link.l1 = "Oh, was für ein Griff!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city+"_Hostess")].name+" erledigt alle Formalitäten in ihrem Kabinett. Geh sie sehen"+GetSexPhrase(", mein Held,","")+" und sag meinen Namen - "+npchar.name+". Ich werde auf dich warten...";
			Link.l1 = "Ich sehe, Liebling, ich komme bald wieder...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("Du hast bereits bezahlt.","Ich habe dir gesagt 'geh nach oben'.","Oben, junger Mann.","Manche Leute denken so langsam...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ja, ich weiß.","Ich erinnere mich.","Ach, wiederhole dich nicht, ich erinnere mich.","Hmm, was meinst du?.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Ich verstehe Sie einfach nicht ganz."+GetSexPhrase("Erst machst du Komplimente, und dann nimmst du deine Worte zurück. Was für ein seltsamer Typ...","")+"","Wieder Komplimente?.","Die Wirtin ist in ihrem Büro. Kapiert?","Wir sollten unsere Kunden nicht beleidigen, aber du forderst es wirklich heraus"+GetSexPhrase("","")+"...","Block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Es ist einfach so passiert, wie es passiert ist...","In Ordnung, ich werde das tun.","Ja, ich habe es.","Entschuldigung, meine Liebe.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Danke für das Kompliment. Wenn du mich mitnehmen willst, geh einfach zur Madame. Geschäft wie üblich.";
				Link.l1 = "Ich sehe.";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Liebes, wir haben schon alles besprochen. ","")+"Lass mich nicht zu lange warten...",""+GetSexPhrase("Hmm... Hör zu, Liebchen, ich","Ich")+" Ich finde deine Worte ja ganz nett und so, aber könnten wir zur Sache kommen...","Vielleicht werden Sie dies mit der Dame besprechen, nicht wahr?","Hm... Ich weiß nicht mal, was ich sagen soll...","Block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Ich würde das niemals tun, warte auf mich!","Sicherlich!","Natürlich, wie Sie sagen!","Ich laufe schon, um Ihre Madame zu sehen...",npchar,Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Ich habe auf dich gewartet, aber du bist nicht gekommen, um mich abzuholen... Ich kann nicht sagen, dass mir das gefallen hat...";
					Link.l1 = "Sie sehen, es ist einfach so passiert, wie es passiert ist...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "Oh, das bist wieder du, mein "+GetSexPhrase("herrlicher Korsar","hübsches Mädchen")+"! Wenn Sie mich wiedersehen wollen, kommen Sie zur Dame, Sie werden nicht enttäuscht sein..."+GetSexPhrase("Übrigens, ich habe dich erkannt, Liebster, aber uns wird gesagt, dass wir mit allen Kunden gleich sprechen müssen, es sollte keinen Liebling geben, tut mir leid...","")+"";
				Link.l1 = "Mach dir keine Sorgen, Liebling. Warte nur ein kleines bisschen auf mich, "+GetSexPhrase("Süße","Süße")+", und bald werden wir uns wieder privat treffen.";
				Link.l1.go = "exit";
				Link.l2 = "Es ist sehr schön, dass du dich an mich erinnerst, aber ich kann diese Nacht nicht mit dir verbringen, tut mir leid.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Also,"+GetSexPhrase(" lieber Freund,","")+" du solltest dich besser mit Geschäften beschäftigen. Es wird nützlicher sein als nichts zu tun.",""+GetSexPhrase("Hmm, warum bist du ","Warum bist du")+"Immer wieder das Gleiche sagen?","He, ist das nicht genug?!","Hm, was für eine Überraschung, nichts Neues"+GetSexPhrase(", schon wieder all diese dummen Versuche zu schmeicheln! Wenn du mit mir schlafen willst, geh und sieh die Madam, du Federkopf!","...")+"","Block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ja, ich habe gehört"+GetSexPhrase("","")+" du...","Hmm, so stellt sich das heraus ...","Hmm, vielleicht ist das genug, oder vielleicht auch nicht ...","Halte deine Zunge im Zaum"+GetSexPhrase(", Ziege","")+"...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ohh, du bist es schon wieder! "+GetSexPhrase("Und schon wieder all diese dummen Komplimente. In dieser Welt ändert sich nie etwas... Wenn ","Nur zur Erinnerung: wenn ")+"du willst"+GetSexPhrase("Viel Spaß","hab eine gute Zeit")+" mit mir, bezahle den Besitzer der Einrichtung. Deine Worte könnten mir nicht gleichgültiger sein.";
				Link.l1 = "Das ist keine große Überraschung...";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "Ich kann nicht sagen, dass es mich glücklich gemacht hat... Schade.";
			Link.l1 = "Es tut mir Leid...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "Ach, du bist endlich angekommen! Wunderbar! Wir können frei sprechen, niemand hört zu...";
				Link.l1 = "Also, war es der Spanier, der dir den blauen Bernstein gegeben hat?";
				Link.l1.go = "mtraxx_2";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SantoDomingo");
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("Ich bin sehr froh, dich zu sehen. "+GetSexPhrase("Also, was werden wir als nächstes tun?","Wie wäre es, wenn wir uns amüsieren?")+"","Hab keine Scheu"+GetSexPhrase(", mach es dir für mindestens zwei Stunden gemütlich.",". Ich werde dich unterhalten können, daran besteht kein Zweifel.")+"");
					Link.l1 = RandPhraseSimple("Ich glaube nicht, dass es langweilig wird...",""+GetSexPhrase("Lass uns eine gute Zeit haben, Baby!","Lass uns keine Zeit verschwenden!")+"");
				break;
				case "1":
					dialog.text = "Oh, das bist wieder du, mein "+GetSexPhrase("herrlicher Korsar! Ich habe dir etwas versprochen und bin bereit, mein Wort zu halten","hübsche Maid! Du wirst die nächsten zwei Stunden nie vergessen")+"...";
					Link.l1 = "Das klingt verlockend...";	
				break;
				case "2":
					dialog.text = "Ohh, da bist du ja endlich. Lass uns keine Zeit verschwenden!";
					Link.l1 = ""+GetSexPhrase("Lass uns nicht, feige...","Zeig mir jetzt, was du kannst...")+"";
				break;
			}
			if (pchar.sex == "woman")
			{
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex";
				AddDialogExitQuest("PlaySex_1");
				// кач от борделя
				if (CheckNPCQuestDate(pchar, "BrothelSex"))
				{
					if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
					else 												AddCharacterHealth(pchar, 5);
					SetNPCQuestDate(pchar, "BrothelSex");
				}
				// изменение статусов
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "FencingS", -15);
				AddCharacterExpToSkill(pchar, "Pistol", -15);
			}
			else
			{
				pchar.horsekiss = npchar.id;
				Link.l1.go = "Horse_Kiss";
			}
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
		break;
		
		case "Horse_Kiss":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("Horse_Kiss", "");
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "Kapitän, warum seid Ihr so still?";
				link.l1 = LinkRandPhrase("Nun, das bin ich.","Wir werden uns das nächste Mal unterhalten.",RandPhraseSimple("Ich bezahle dich nicht zum Reden.","Aber du, "+GetSexPhrase("Schönheit","Liebchen")+", waren nicht die ganze Zeit so still."));
				link.l1.go = "exit";
				link.l2 = ""+GetSexPhrase("Du warst einfach großartig, ich habe fast meinen Verstand verloren! Es ist eine sehr seltene Gelegenheit, wenn eine Frau sowohl so schön als auch heiß ist","Ohh, du weißt wirklich, wie man eine Frau erfreut... Ich bin so aufgeregt.")+".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("Hat es dir gefallen?","Also, was können Sie sagen? War alles in Ordnung?","Also,"+GetSexPhrase("Seeräuber, ist, alles"," alles")+" gut?");
						Link.l1 = RandPhraseSimple(""+GetSexPhrase("Natürlich ist alles in Ordnung","Du kennst sicherlich deine Pflichten")+".",""+GetSexPhrase("Alles ist gut, Liebling","Weißt du, ich war ziemlich zufrieden")+".");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("Also, habe ich mein Versprechen gehalten?","Also,"+GetSexPhrase(" hat es dir gefallen",", hat es dir gefallen")+"?","Ich hoffe, "+GetSexPhrase("du warst zufrieden, denn ich bin seeeehr zufrieden","du warst zufrieden, weil ich mein Bestes gab")+"...");
						Link.l1 = RandPhraseSimple("Ja, es hat mir sehr gefallen.",""+GetSexPhrase("Wir hatten eine großartige Zeit, du warst wunderschön!","Alles war einfach grandios!")+"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("Nun, das war's, du musst gehen.","Deine Zeit ist vorbei,"+GetSexPhrase("Kapitän,","")+".");
						Link.l1 = RandPhraseSimple("Ja, wir sehen uns...","Auf Wiedersehen und danke...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "Also, wie hat es dir hier gefallen?";
				link.l1 = "Sag mir Schönheit, hast du irgendwo einen Handkoffer gesehen?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("Schau doch mal wieder vorbei...","Tschüss. Wir warten jederzeit auf dich...","Wir freuen uns, dich hier wieder zu sehen...");
				Link.l1 = "In Ordnung...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "War es diese braune Kiste mit einem Griff?";
			link.l1 = "Ja, so etwas...";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "Weil der Besitzer dieser Truhe nicht aufgetaucht ist, hat die Dame sie in ihr Boudoir mitgenommen.";
			link.l1 = "Danke, Liebling. Auf Wiedersehen.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "Dann komm jederzeit vorbei, ich werde immer froh sein, dich zu sehen. Du bist so "+GetSexPhrase("sanft, nicht wie die anderen","sanft, nicht wie diese Hinterwäldler")+" kein Hallo, kein Auf Wiedersehen, und oft versuchen sie sogar zu verletzen...";
			link.l1 = "Was meinst du damit?";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "Vor dir war hier ein Hauptfeldwebel. Normalerweise schaut er nicht bei uns vorbei, aber dieses Mal hat ihn irgendein Teufel hierher gebracht. Darüber hinaus hat er mich ausgesucht... Er stöhnte, während er einige Minuten über mir war, und nannte mich dann ungeschickt und eilte zu einer Bucht. Er zog so schnell ab, dass er fast seine Hosen dort unten ließ, ha-ha-ha...";
			link.l1 = "Kennst du nicht, "+GetSexPhrase("Schönheit","Schatz")+", wer Männer wirklich sind? Er hatte seiner Frau gesagt, dass er zur 'Inspektion' ins Bordell gehen würde, dann erzählte er seiner Geliebten, dass er es eilig habe zu seiner Frau, aber das Einzige, was er immer wollte, ist diese Bucht zu patrouillieren. "+GetSexPhrase("Ha-ha-ah!..","Ha-ha-ha!")+"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "")
			{ 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true;
				LAi_LocationDisableOfficersGen(TargetLocation, true);
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// <-- генератор "A reason to hurry"
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase("Nein, Liebling, tut mir leid, aber nein. Ich würde dir gerne helfen, aber ich kann nicht.","Nein, "+GetSexPhrase("schön","junge Dame")+", Ich habe keinen Ring gesehen...","Es tut mir leid, aber nein. Ich habe keinen Ring gesehen.");
				link.l1 = "Schade... Nun, danke trotzdem.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "Meinen Sie den Ring des Gouverneurs?";
					link.l1 = "Genau, Schätzchen!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("Nein, Liebling, tut mir leid, aber nein. Ich würde dir gerne helfen - aber ich kann nicht.","Nein, "+GetSexPhrase("schön","junge Dame")+", Ich habe keinen Ring gesehen...","Entschuldigung, aber nein. Ich habe keinen Ring gesehen.");
					link.l1 = "Schade... Nun, danke trotzdem.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "Es tut mir leid, aber der Ring wurde mir als Geschenk gegeben, also bin ich nicht verpflichtet, ihn zurückzugeben.";
			link.l1 = "Ein Geschenk?! Und wer hat es dir gegeben?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "Der Gouverneur selbst, natürlich!";
			link.l1 = "Aber er war... sagen wir mal, angeschickert. Er kann sich an nichts erinnern.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "Und was habe ich damit zu tun? Wenn er betrunken war, ist das sein Problem, nicht meins!";
			link.l1 = "Musst du wirklich mit ihm streiten? Es ist ein Ehering, und das weißt du... Gib ihn einfach zurück, so eine Kleinigkeit ist keine Ärger wert.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "Nun, ich gebe den Ring zurück, aber du wirst mir fünftausend Pesos zahlen.";
				link.l1 = "Gut, nimm dein Geld und gib mir den Ring.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "Oh, na gut. Lass ihn es haben!";
				link.l1 = "Das ist sicher, Liebling!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "Hier, bitteschön...";
			link.l1 = "Gut, dann. Danke für die Hilfe, Liebling.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
		
		//Jason --> Заносчивый аристократ
		case "Badboy":
			pchar.GenQuest.Badboy.Brothel.City = npchar.city; //город квестодателя
			//log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
			pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
			pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Sehen Sie, wir haben einen unangenehmen Kunden - "+pchar.GenQuest.Badboy.Brothel.Name+". Und er nervt uns jedes Mal, wenn er kommt! Zuerst betrinkt er sich in der Taverne, dann kommt er hierher, nimmt ein Mädchen und macht einen gewalttätigen Aufruhr\nUnd das Schlimmste daran ist, dass er von edler Abstammung ist! Er ist ein entfernter Verwandter unseres Gouverneurs, also sind wir gezwungen, all seine Eskapaden zu ertragen. Vielleicht könnten Sie diesen jungen, unverschämten Mann... nun... ein bisschen beruhigen... damit er aufhört, meine Einrichtung zu besuchen?";
			link.l1 = "Gouverneursverwandter, sagst du? Hmmm... Ich möchte mich wirklich nicht mit den Behörden anlegen. Es tut mir wirklich leid.";
			link.l1.go = "exit";
			link.l2 = "Ich denke, ich kann das arrangieren. Sag mir, wo kann ich diesen Taugenichts finden?";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Normalerweise ist er um diese Zeit bereits in der Taverne. Er betrinkt sich dort und kommt dann zu Besuch.";
			link.l1 = "Ich verstehe. Nun, ich werde ihn dort wahrscheinlich treffen.";
			link.l1.go = "exit";
			//создаем дебошира
			int iRank, iType, b;
			string sBlade, sPistol;
			if (sti(pchar.rank) < 6) iType = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16) iType = 1;
			if (sti(pchar.rank) >= 16) iType = 2;
			switch (iType)
			{
				case 0:
					iRank = 6;
					sBlade = "blade_12";
					sPistol = "pistol1";
					b = 25;
				break;
				case 1:
					iRank = sti(pchar.rank)+10;
					sBlade = "blade_09";
					sPistol = "pistol1";
					b = 65;
				break;
				case 2:
					iRank = sti(pchar.rank)+5;
					sBlade = "blade_14";
					sPistol = "pistol1";
					b = 40;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_"+(7+rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank*5));
			sld.name = pchar.GenQuest.Badboy.Brothel.Name;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Badboy";
			sld.greeting = "noble_male"; // patch-6
			LAi_SetLoginTime(sld, 15, 22);
			LAi_SetSitType(sld);
			FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
			pchar.GenQuest.Badboy.Brothel.Type = iType; //запомним тип
			pchar.GenQuest.Badboy.Brothel = "true";
		break;
		
		case "Badboy_complete":
			dialog.text = "Oh, du bist ein richtiger Mann, nicht wahr? Ich wusste immer, dass ich mich auf dich verlassen kann..";
			link.l1 = "Ich helfe immer gerne so einer netten Dame und ihren... Schützlingen.";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "Du bist nicht nur mutig, sondern auch sehr galant. Ich möchte dir auf besondere Weise danken - auf eine Art, wie nur eine Frau einem Mann danken kann. Das wirst du nie vergessen, das verspreche ich. Komm nach oben, tapferer Seemann...";
			link.l1 = "..., Freund.";
			link.l1.go = "Badboy_complete_2";
		break;
		
		case "Badboy_complete_2":
			pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); 
			DialogExit();
			if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
			{
				DeleteAttribute(pchar, "GenQuest.Badboy");
			}
			else
			{
				pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
				pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City +"_town";
				pchar.quest.Badboy_Brothel.function = "Badboy_friends";
				DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
			}
			SaveCurrentQuestDateParam("questTemp.Badboy");
			if (!CheckAttribute(pchar, "questTemp.RomNaTroih"))
			{
				pchar.questTemp.RomNaTroih = true;
			}
		break;
		// <-- Заносчивый аристократ
		
		//Португалец
		case "Portugal":
			dialog.text = "Es gibt einen Mann und er schuldet mir etwas Geld... Ich weiß nicht, wie ich es sagen soll...";
			link.l1 = "Keine Worte! Ich werde ihn finden und ihn bis zum letzten Peso schütteln, nur für einen Blick in deine unergründlichen Augen! Sag mir einfach seinen Namen!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Nein, nein, Sie haben mich nicht richtig verstanden, Kapitän! Dieser Mann... tut ihm nichts Böses. Erinnere ihn nur an seine Schulden. Sein Name ist Hugo Avendell und ich vermute, Sie werden ihn dort finden, wo sehr billiger Schnaps verkauft wird. Um Gottes willen, wende keine Gewalt an ihm an!\nSag einfach... erinnere ihn daran, dass er versprochen hat zu zahlen. Ich will keinen Kontakt zur Wache, aber ich habe Offiziersfreunde, also sag ihm, dass ich warte, und mit allem gebührenden Respekt zu ihm, werde ich gezwungen sein, nicht später als morgen Maßnahmen zu ergreifen. Erinnere ihn einfach an sein Versprechen.";
			link.l1 = "Ihr Wort ist mein Gesetz, Madame. Ich werde Ihre Anfrage gerne erfüllen.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			//создаем Хьюго
			sld = GetCharacter(NPC_GenerateCharacter("Avendel", "Hugh", "man", "man", 10, HOLLAND, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_04", "pistol1", "bullet", 50);
			sld.name = "Hugo";
			sld.lastname = "Avendell";
			sld.dialog.FileName = "Quest\Portugal_dialog.c";
			sld.dialog.currentnode = "Avendel_tavern";
			sld.greeting = "avendel_1";
			sld.rank = 12;
			LAi_SetHP(sld, 80, 80);
			SetSelfSkill(sld, 10, 12, 10, 10, 70);
			SetShipSkill(sld, 50, 75, 15, 15, 25, 55, 10, 15, 30);
			SetSPECIAL(sld, 3, 8, 3, 10, 10, 3, 6);
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "AdvancedCommerce");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "Gunman");
			GiveItem2Character(sld, "blade_12");
			sld.equip.blade = "blade_12";
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");
			TakeNItems(sld, "bullet", 10);
			AddItems(sld, "gunpowder", 10);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			LAi_SetImmortal(sld, true);
			LAi_SetSitType(sld);
			FreeSitLocator("Marigo_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
			AddLandQuestMark(sld, "questmarkmain");
			SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
			pchar.questTemp.Portugal = "begin";
		break;
		
		case "Portugal_exit":
			dialog.text = "Danke, Kapitän. Ich hoffe doch, dass er die gebotene Vorsicht walten lassen wird.";
			link.l1 = "Ich bin mir dessen sicher, Madame. Erlauben Sie mir nun, mich zu verabschieden.";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "Ach nein! Sag mir nicht, dass du ihm etwas Schreckliches angetan hast... Er hatte kein Geld, und ich wusste es! Wir sind einfach in der gleichen kleinen Stadt aufgewachsen, ich würde mich nie an die Wachen wenden! Ich wollte ihn nur ein bisschen erschrecken... ihn aufschütteln, bevor er in der Flasche ertrinken würde!";
			link.l1 = "Hmm ... Trotzdem, hier ist dein Geld. Und mach dir keine Sorgen um Hugo, ihm geht es gut ... Zumindest wird es ihm gut gehen, wenn er nüchtern wird.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Ach, Kapitän, Sie verstehen nicht! Er war einer von ... na ja, Sie wissen schon, sie werden Kopfgeldjäger genannt - Söldner, sie jagen Piraten und Räuber und eliminieren sie. Aber, er war nicht der Glücklichste, um es gelinde zu sagen\nNicht so lange her hat er endlich über die Stränge geschlagen und seine Crew und sein Schiff verloren, seitdem treibt er am Boden seines Bechers, Tag für Tag. Ich erlaube ihm aus alter Erinnerung hin und wieder hierher zu kommen. Er ist so... so jämmerlich jetzt. Er war der schönste Mann in unserer Stadt an der Küste des Ärmelkanals, und schauen Sie ihn sich jetzt an\nIch weiß, dass er Ihnen etwas versprochen hat, und Sie haben aus eigener Tasche bezahlt! Ich gebe Ihnen dieses Geld, tun Sie ihm nur nichts Schlimmes an, ich flehe Sie an, Kapitän!";
			link.l1 = "Also gut, Madame, ich habe verstanden. Behalten Sie das Geld, es gehört Ihnen. Und was deinen Freund betrifft, verspreche ich, ihm nicht weh zu tun. Und nun erlauben Sie mir, mich zu verabschieden, ich habe noch Geschäfte zu erledigen. Außerdem war ich froh, einer so schönen Dame helfen zu können.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_tavern_7";
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Portugal = "AvendelTavern";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Still, halt deine Stimme niedrig... Geh und frag Madame Lolita, ob sie sich mit mir verabreden will. Dann komm nach oben, wo wir frei sprechen können. Und kein Wort bis dahin... Hey, Seemann, geh und bezahl Madame, bevor du mich berührst! (kichert)";
			link.l1 = "Auf meinem Weg, Liebling...";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   chrDisableReloadToLocation = false;
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = "Nein, nicht ich. Ich erzähle dir die ganze Geschichte, unterbrich mich einfach nicht.";
			link.l1 = "Ich bin ganz Ohr!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Also gut. Vor etwa einer Woche kam ein Militärschiff in Santo Domingo an. Es war beschädigt, entweder durch einen Sturm oder einen Kampf, also begannen die Reparaturen sofort, und die Besatzung zog in die Festung. Ihr Kapitän, jedoch, verbrachte all seine freie Zeit genau hier. Zwei Tage lang trank und entspannte er in Begleitung eines unserer Mädchen. Sie war es, die den Edelstein bekam, und nicht nur einen. Sie prahlte damit ohne Ende - Lolita lässt uns die Geschenke der Kunden behalten \nDas dumme Mädchen wusste nicht einmal den wahren Wert des Geschenks, wohingegen ich es sofort einschätzte. Als sie mir erzählte, wie der betrunkene Kapitän von einem Berg voller Bernsteine prahlte, schickte ich prompt einen Brief an Tyrex...";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Bis zur nächsten Ankunft des Kapitäns habe ich alles so eingerichtet, dass sein Lieblingsmädchen mit einem anderen Kunden beschäftigt war, und habe den 'Job' für mich selbst bekommen. Ich habe versucht, die Koordinaten aus ihm herauszuholen, leider vergeblich. Er prahlte nur damit, wie er so reich wie Crassus werden und in die Alte Welt zurückkehren würde\nKein einziges Wort über den Standort. Das Einzige, was ich herausfand, war, dass sein Schiff repariert wurde und es nach Havanna segeln sollte, wo er versuchen würde, eine Mission in die richtige Richtung zu organisieren. Er ist schließlich nicht der Eigentümer des Schiffes.";
			link.l1 = "Also, er ist jetzt in Havanna?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Segelte vor zwei Tagen bei Tagesanbruch ab. Du bist der Seemann hier, du machst die Zählung.";
			link.l1 = "Name des Kapitäns, Typ und Name seines Schiffes, irgendetwas?";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "Was, hältst du mich für einen Narren? Sein Name ist Esberdo Cabanas, Kapitän der Cantavro. Ich denke, die Matrosen nannten es eine Schoner.";
			link.l1 = "Und das ist alles, was du weißt?";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = "Was willst du noch mehr? Ich bin sicher, du könntest ihn vor Havanna einholen. Verschwende aber keine Zeit, ich glaube nicht, dass er sich lange ausruhen wird, bevor er Kuba verlässt und zu seiner Beute aufbricht, und dann ist es eine verlorene Sache. Bei näherer Überlegung könntest du ein oder zwei Stunden bleiben, du hast schließlich dafür bezahlt.";
			link.l1 = "Guter Punkt, Liebling. Zwei Stunden werden nicht viel Unterschied machen...";
			// belamour legendary edition -->
			link.l1.go = "mtraxx_7S";
			link.l2 = "Ein andermal, Liebling. Gönn dir eine Mittagspause. Geh in die Kirche, oder mach was anderes.";
			link.l2.go = "mtraxx_7NS";
			sTotalTemp = npchar.id;
			AddMapQuestMarkCity("Havana", false);
			AddLandQuestMark(characterFromId("Havana_PortMan"), "questmarkmain");
		break;
		
		case "mtraxx_7S":
            DialogExit();
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "mtraxx_7NS":
            DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			AddQuestRecord("Roger_1", "3");
			pchar.questTemp.Mtraxx = "jewelry_3";
			SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // таймер
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
			pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
			DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
			DeleteAttribute(pchar, "questTemp.ZA.Block");
		break;
		// <-- legendary edition
		case "mtraxx_R":
            dialog.text = "A-ach... Was für eine Schande. Und ich dachte, du bist hier im Urlaub. Meine Mädchen vermissen tapfere Korsaren so sehr. Nun denn, sprich, was ist die Aufgabe?..";
			link.l1 = "Marcus hat mich beauftragt, in deinem Etablissement eine verdammt gute Party für zwei Tage zu veranstalten, all den Wein zu trinken und jedes Mädchen zu vernaschen. Wann fangen wir an?";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = "Ach, Charlie Prince, dein Humor ist so scharf wie dein Säbel! Du hast mich fast verärgert... Mädchen! Wir haben einen Gast, einen besonderen Gast! Bringt Wein und Mahlzeiten!";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "Ruft jedes hübsche Mädchen hierher! Wir werden uns ausruhen und Spaß haben! Yo-ho-ho!..";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "Haltet ein Minute, Janette. Ich muss das Gold von meinem Schiff holen für dich und deine Damen. Bis gleich!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = "Ich wünschte, alle unsere Kunden wären so süß, gutaussehend und großzügig wie Sie... Wir werden Ihnen eine perfekte Entspannung bieten. Mädchen!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
		// belamour ночной приключенец
		case "NA_Girl":
            dialog.text = "Oh, also haben wir hier einen Kenner, hee hee ... Nun, nun, ich habe so ein Mädchen. Aber sie kommt nicht billig: "+makeint(pchar.GenQuest.NightAdventure_money)+" Pesos."; 
			link.l1 = "Abgemacht.";
			link.l1.go = "NA_Girl_1";
		break;
		
		case "NA_Girl_1":
			AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
            dialog.text = "Das ist großartig, Liebling. Die Priesterin der Liebe wird oben auf dich warten. Glaub mir, du wirst es nicht bereuen."; 
			link.l1 = "Ich tue es bereits nicht.";
			link.l1.go = "NA_Girl_2";
		break;
		
		case "NA_Girl_2":
			DialogExit();
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhore"; 
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_NobleWhore_7";
		break;
		// <-- приключенец
		
		case "chicken_god":
			dialog.text = "Für Sie und m'lord Agueybana? Selbstverständlich tun Sie das. Das wird zehntausend sein, Kapitän.";
			if (sti(pchar.money) >= 10000) {
				link.l1 = "Warte, nicht so!.. Verdammt! Wie auch immer, hier ist das Gehalt.";
				link.l1.go = "chicken_god_pay";
			} else {
				link.l2 = "Kann ich ein Darlehen bekommen?";
				link.l2.go = "chicken_god_notpay";
			}
		break;
		
		case "chicken_god_pay":
			dialog.text = "Genießen Sie Ihren Aufenthalt, Kapitän. Bitte kommen Sie wieder, wenn wir geöffnet haben. Unsere Einrichtung bietet alle Arten von Freizeitaktivitäten für edle Männer und Frauen.";
			link.l1 = "...";
			link.l1.go = "chicken_god_pay_1";
		break;
		
		case "chicken_god_pay_1":
			dialog.text = "";
			link.l1 = "Madame "+npchar.name+", könntest du mir zumindest erklären, was hier vor sich geht? Ist dem Gouverneur überhaupt bewusst, dass du seit einem Monat einen Eingeborenen zur Leitung hast? Keine Siedlung kann einen Tag überleben, an dem das Bordell geschlossen ist, das kann ich dir sagen!";
			link.l1.go = "chicken_god_pay_2";
		break;
		
		case "chicken_god_pay_2":
			dialog.text = "Das Zimmer gehört Ihnen, Kapitän. Jetzt, wenn Sie mich entschuldigen würden.";
			link.l1 = "Charmant. Auf Wiedersehen, Madame.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;
		
		case "chicken_god_notpay":
			dialog.text = "Warum, Herr, warum? Raus hier! Geh weg, geh weg, ich kann es nicht mehr ertragen! Schurke!";
			link.l1 = "Das lief gut.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;
		
		//-->> Sinistra Ром на троих
		case "RomNaTroih_1":
			dialog.text = "Mhm... Ich mache das normalerweise nicht... aber ich bin bereit, es für dich zu riskieren. Es ist dein Glückstag, Kapitän!";
			link.l1 = "Lass uns gehen!";
			link.l1.go = "exit";
			pchar.RomNaTroih_Shluha = npchar.id;
		break;
		
		case "RomNaTroih_2":
			dialog.text = "Ich bin wütend auf dich, Kapitän... Aber ich werde dir Gnade zeigen, wenn du hart genug dafür arbeitest.";
			link.l1 = "Oh, das werde ich. Sollen wir Wein öffnen?";
			link.l1.go = "exit";
			Achievment_Set("ach_CL_105");
		break;
		//<<-- Sinistra Ром на троих
		
		//--> прибыла инспекция на Святом Милосердии
		case "SantaMisericordia_1":
			dialog.text = "Bis dieser verdammte de Alamida geht. Verfluchter Heiliger...";
			link.l1 = "Aber vielleicht...";
			link.l1.go = "SantaMisericordia_2";
		break;
		
		case "SantaMisericordia_2":
			dialog.text = "Keine Vielleicht. Was ist, wenn er jetzt hier reinkommt? Alle raus.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
		break;
		//<-- прибыла инспекция на Святом Милосердии
		
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse" && rCharacter.horse == "HorseStay")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
