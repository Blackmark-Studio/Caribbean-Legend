// boal 25/04/04 общий диалог мэры
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool bOk, bOk1, bOk2;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Du hast es gewagt, dein Gesicht in meinem Zuhause zu zeigen?! Sehr mutig von dir, oder dumm...","Wie haben meine idiotischen Wachen es zugelassen, dass ein Feind in meinen Palast eindringt? Jemandem wird dafür der Kopf rollen.","Anscheinend sind meine Wachen keinen Kupferpfennig wert, wenn irgendein Schurke in meiner Residenz herumläuft und in meinen Sachen wühlt..."),LinkRandPhrase("Was brauchst du, "+GetSexPhrase("Schurke","Teufel")+"?! Meine Soldaten sind bereits auf deiner Spur"+GetSexPhrase(", dreckiger Pirat","")+"!",+"Mörder, verlass sofort meine Residenz! Wachen!","Ich habe keine Angst vor dir, "+GetSexPhrase("Schurke","Ratte")+"! Bald wirst du in unserem Fort gehängt werden!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Deine Soldaten sind nutzlos.","Versuch mich zu fangen."),RandPhraseSimple("Halt den Mund, "+GetWorkTypeOfMan(npchar,"")+", oder ich schließe es für dich!","Sei still, Kumpel, und du bleibst am Leben."));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "Was brauchst du?";
					link.l1 = "Ich wollte mit dir über wichtige Arbeit sprechen.";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = "Was brauchst du?";
					link.l1 = "Ich wollte mit dir über wichtige Arbeit sprechen.";
					link.l1.go = "quests";
					break;
				}
					dialog.text = "Es gibt nichts zu besprechen, Bursche. Ich bin beschäftigt.";
					link.l1 = "Meine Entschuldigung.";
					link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = "Oh, schau mal wer da ist! Es ist"+GetSexPhrase("","")+" "+GetFullName(pchar)+". Weißt du, ich habe erst kürzlich Piratenjäger ausgesandt, um dich hierher zu bringen. Hätte ich gewusst, dass du einfach durch meine Tür tanzen würdest, hätte ich mein Geld gespart.";
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = "Ich war gerade dabei, unsere Rechnungen zu begleichen.";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "Es ist Zeit für mich, eine schnelle Abreise zu machen.";
				link.l2.go = "arest_1";
				break;
            }
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = "Ein Einbruch! Wachen! Alarm! Mord!";
				link.l1 = "Scheiße!";
				link.l1.go = "fight"; 
				break;
			}
			//--> Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = "Was wünschen Sie, Monsieur?";
				link.l1 = "Hallo, Eure Gnaden. Ich bin Charles de Maure, gerade erst aus Paris angekommen. Ich suche Michel de Monper.";
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // patch-6
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = "Oh, Sie sind es, Herr... Ich muss mich für meine Unhöflichkeit entschuldigen. Meine Entschuldigung, wir sind weit entfernt von den Annehmlichkeiten von Paris hier in den Kolonien.";
					link.l1 = "Natürlich, Eure Gnaden.";
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = "Hast du etwas gewollt, Charles?";
					link.l1 = "Ich habe eine Frage...";
					link.l1.go = "quests";
					link.l2 = "Nein, nichts.";
					link.l2.go = "exit";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
				{
					link.l3 = "Herr, ich habe eine Banditenleiche im Dschungel gefunden. Er wurde von den Indianern getötet. Es gab Ohrringe an seinem Körper, sieht so aus, als wären sie aus Europa hierher gebracht worden. Vielleicht gehörten sie einem der Adligen in Ihrer Stadt?";
					link.l3.go = "Sharlie_junglejew";
				}
				npchar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_TravlyaKrys") && npchar.city == "FortFrance")
			{
    			dialog.text = "Willkommen in der Karibik, Kapitän de Maure. Diesmal wirklich.";
				link.l1 = "Danke, Eure Exzellenz.";
                link.l1.go = "TK_TravlyaKrys";
				DelLandQuestMark(npchar);
				break;
			}
			// Jason НСО
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && IsUniformEquip())
			{
    			dialog.text = "Es ist gut, Sie zu sehen, Gouverneur! Wie geht es Ihnen? Alles ist unter Kontrolle auf Sint Maarten.";
				link.l1 = "Ich habe keine Zeit zu bleiben. Mach weiter so.";
				link.l1.go = "exit";
				link.l2 = "Ich wollte über die Arbeit sprechen.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Wie wäre es mit einem Glücksspiel?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && IsUniformEquip())
			{
    			dialog.text = "Mein Gott, froh Sie zu sehen, Generalgouverneur! Alles ist großartig hier in unserer bescheidenen kleinen Kolonie! Bitte nehmen Sie Platz, ich werde den Dienern befehlen, den Tisch zu decken...";
				link.l1 = "Es besteht keine Notwendigkeit. Ich bin nicht lange geblieben. Mach weiter so.";
				link.l1.go = "exit"; 
				link.l2 = "Ich wollte über die Arbeit sprechen.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Wie wäre es mit einem Glücksspiel?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") &&  IsUniformEquip())
			{
    			dialog.text = "Wen haben wir denn hier! Monsieur Gouverneur-General der französischen Kolonien! Was wünschen Sie, Eure Gnaden? Setzen Sie sich, ich befehle meinen Dienern, Wein und frisches Obst zu bringen.";
				link.l1 = "Mach dir keine Sorgen, ich bin nur hier, weil ich die Insel besuchte, und ich konnte einfach nicht vorbeigehen, ohne hallo zu sagen.";
				link.l1.go = "exit"; 
				link.l2 = "Ich wollte über die Arbeit sprechen.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Wie wäre es mit einem Glücksspiel?";
				link.l8.go = "Play_Game";
				break;
			}		
			//--> Jason, Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = "Oh, da bist du ja, Kapitän! Ich muss sagen, du hast dir Zeit gelassen.";
				link.l1 = "Ich bin so schnell wie möglich angekommen, Eure Exzellenz. Mir wurde gesagt, Sie haben dringende Geschäfte?";
				link.l1.go = "Portugal"; 
				break;
			}			
			//<-- Португалец
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = "Meine Männer haben mir erzählt, dass Sie sehr hartnäckig um eine Audienz gebeten haben. Mein Name ist "+GetFullName(npchar)+". Ich bin der Gouverneur der Stadt "+GetCityName(NPChar.city)+", Betreff von "+NationKingsName(npchar)+". Und nun, bitte, was wünschen Sie "+GetAddress_Form(NPChar)+"?";
				link.l1 = "Mein Name ist "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_townhall")
				{
					dialog.text = TimeGreeting()+", Fräulein MacArthur.";
					link.l1 = TimeGreeting()+", Eure Exzellenz.";
					link.l1.go = "Helen_node_1"
				}
			}
			else
			{
               	//ОСАДЫ homo
				if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "Ist das alles?";
                        link.l1 = "Ja, Herr. Ich halte Sie nicht länger auf.";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "Es tut mir leid, dich zu verärgern, aber ich habe im Moment keine Zeit, mit dir zu sprechen. Wie du wissen solltest, wurde unsere Kolonie von "+NationNamePeople(sti(aData.nation))+". Ich kümmere mich immer noch um unsere Verteidigungen.";
                        link.l1 = "Ich möchte meine Hilfe bei der Verteidigung der Festung anbieten.";
                        link.l1.go = "siege_task";
                        link.l2 = "Dann werde ich Sie nicht weiter aufhalten.";
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterComplexReputation(pchar,"nobility", 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                        //--> слухи
                        SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and to defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "Oh, du bist es, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", ich bin froh, dich zu sehen. Gute Nachrichten für unsere Kolonie - wir haben es geschafft, die "+NationNameSK(sti(aData.nation))+" Eindringlinge. Du hast auch einen Teil daran, also hier ist deine Belohnung - "+(sti(aData.iSquadronPower)*1500)+" Stücke von Acht. Hier, nimm.";
                        link.l1 = "Danke, "+GetAddress_FormToNPC(NPChar)+", freut mich, Geschäfte mit Ihnen zu machen!";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
						{// Addon-2016 Jason
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "Ich habe eine Aufgabe für dich, aber sie ist etwas ungewöhnlich.";
								link.l1 = "Das sind die Aufgaben, die ich am besten kann.";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple("Oh, bist du es schon wieder? Was willst du diesmal von mir?","Du lenkst mich von den Angelegenheiten meiner Stadt ab. Was willst du, "+GetAddress_Form(NPChar)+"?");
						if (npchar.city != "Panama") // Addon-2016 Jason
						{
							link.l1 = "Ich möchte mit dir über die Arbeit für "+NationNameGenitive(sti(NPChar.nation))+".";
							link.l1.go = "work";
						}
						// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen")+" Ich habe einige Piraten gefunden. Alle "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" sind momentan an Bord. Ich möchte sie den Behörden übergeben.";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "Ich wollte mit dir über ein wichtiges Thema sprechen.";
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(перессылка в файл города)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = "Es gibt einen Kapitän, der die Patrouille befehligt "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Konto"))+" genannt "+pchar.GenQuest.CaptainComission.Name+", wie kann ich ihn sehen?";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "Ehemaliger Kapitän im Kommando der Patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Akk"))+" "+pchar.GenQuest.CaptainComission.Name+" hat zugestimmt, sein Versteck den Behörden zu enthüllen.";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "Ehemaliger Kapitän im Kommando der Patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Akz"))+" "+pchar.GenQuest.CaptainComission.Name+" hat mir sein Versteck gezeigt.";
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25  && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Ich habe den Kapitän getroffen "+pchar.GenQuest.ShipWreck.Name+" und seine Matrosen, die von Piraten an Land gesetzt wurden "+pchar.GenQuest.ShipWreck.BadName+". "+"Leider hatte ich bereits zu viele Männer auf meinem Schiff und konnte sie nicht an Bord nehmen. Aber ich habe ihnen Proviant und Waffen gelassen. Wenn kein Rettungsschiff sie innerhalb "+(30 - iDay)+" Tage, dann weiß ich nicht, ob ich sie lebend finden werde oder nicht.";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Gen"))+" Ich habe Matrosen vom verunglückten Schiff getroffen '"+pchar.GenQuest.ShipWreck.ShipTypeName+"' mit ihrem Kapitän. "+"Leider hatte ich bereits zu viele Männer an Bord meines Schiffes und konnte sie nicht aufnehmen. Aber ich ließ sie mit Proviant und Waffen zurück. Wenn ein Rettungsschiff sie nicht innerhalb "+(30 - iDay)+" Tage, dann weiß ich nicht, ob es sie lebend finden wird oder nicht.";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "Ich möchte einen Gefangenen abliefern.";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "Ich muss einige finanzielle Angelegenheiten mit Ihnen klären.";
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "Ich habe es geschafft, Ihren Ring zu finden. Hier, bitte.";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "Ich habe deinen Ehering. Eine der...Arbeitsmädchen im Bordell hatte ihn.";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
						
						//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Ich bringe eine Nachricht aus der Stadt "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<-- генер почтового курьера 2 уровня
						
						// Warship, 16.05.11. Квест "Правосудие на продажу" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", ich habe eine Bande von Schmugglern ausfindig gemacht, deren Anführer kürzlich von den Wachen gefangen genommen wurde. Jetzt planen sie seine Flucht. Ihr Schiff '"+PChar.GenQuest.JusticeOnSale.ShipName+" liegt vor Anker bei "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+".";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", die Bande der Schmuggler ist nicht mehr!";
							link.l15.go = "JusticeOnSale_7";
						}
						// <--Правосудие на продажу
						//Jason --> Регата
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = "Ich bin hier für die Regatta. Hier ist meine Einladung.";
							link.l16.go = "Regata";
						}
        				//link.l7 = "Ich möchte wissen, wo der Generalgouverneur von "+NationNameGenitive(sti(NPChar.nation))+"ist.";
        				link.l8 = "Vielleicht möchten Sie eine Pause einlegen und ein Glücksspiel spielen?";
        			    link.l8.go = "Play_Game";
        				link.l10 = "Entschuldigen Sie bitte, aber die Pflicht ruft.";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		
		// Warship Генер "Пираты на необитайке"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = "Sehr gut. Wir müssen diese gemeinsame Plage mit unseren vereinten Anstrengungen bekämpfen. Ich werde sofort ein Schiff entsenden, um sie abzuholen. Seien Sie versichert, dass sie in weniger als einer Woche am Galgen hängen werden. Oh, und natürlich steht eine Belohnung an - "+FindRussianMoneyString(qty)+".";
			link.l1 = "Danke Euer Gnaden. Immer eine Freude. ";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "Nein. Bei näherer Betrachtung, das wird nicht tun.";
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);
			
			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
			
			if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				
				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = "Ich bin ganz Ohr, Kapitän.";
			link.l1 = "Ich wollte Ihnen von einer kriminellen Verschwörung zwischen einem Offizier Ihrer Garnison und Piraten erzählen... (erklärt die Angelegenheit).";
			if(sti(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";			
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";	
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_GMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Danke, "+GetSexPhrase("Herr","Fräulein")+"! Ich werde sofort den Befehl geben, diesen Verräter zu verhaften.\nDu musst viel Geld ausgegeben haben, ach, unsere Schatzkammer ist leer...";
				link.l1 = "Ich habe es nicht für das Geld gemacht, Euer Exzellenz.";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Ich danke Ihnen! Ich werde diesen Schurken festnehmen lassen.\nDenk nur! Ich war kurz davor, ihm zum zehnten Dienstjahr einen Säbel mit goldenem Griff zu verleihen! Sie haben mich vor einer ernsthaften Blamage gerettet!";
				link.l2 = "Gerechtigkeit ist ihre eigene Belohnung.";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Fehl"+GetSexPhrase("ter","s")+" de Maure, Sie können einfach keinen Verdächtigen ohne Zeugen töten! Jetzt können wir nicht einmal Beweise für seine Verbrechen bekommen! Es ist alles, was ich tun kann, um Sie vor einer Verhaftung wegen Totschlags zu bewahren.";
				link.l3 = "Ahoi, es war in Selbstverteidigung, Eure Exzellenz.";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "Kapitän, begreifst du, was zum Teufel du getan hast?!! Ich habe mehr als einen Monat damit verbracht, diese Falle aufzustellen! Und jetzt, nur zu deinem eigenen Vergnügen, hast du das Treffen unserer Patrouille durcheinander gebracht mit "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" und jetzt kommst du hierher, um damit zu prahlen?!! Vielleicht kannst du mir jetzt erklären, wie ich all die Ausgaben und Kosten dieser Operation rechtfertigen soll?!";
				link.l1 = "Eure Gnaden, ich habe gerade Euer Problem gelöst, wenn Ihr es genau betrachtet, hättet Ihr mir die ganze Zeit bezahlen sollen!";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Lass mich diese Karte sehen\nBist du gerade ernst? Dieser zerlumpte Fetzen Papier ist ein Beweis?";
				link.l2 = "Seien Sie jetzt vernünftig, Euer Gnaden.";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Nun, nun, jetzt wissen wir, was mit meiner Patrouille passiert ist. Zumindest haben Sie uns durch Ihr Kommen die Notwendigkeit erspart, den Mörder zu suchen.";
				link.l3 = "Eure Gnaden! Ihr weigert Euch einfach, den Punkt zu sehen...";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "You may be an idiot but you are at least a useful idiot. Here - take this map; found it on a pirate who we hanged last week. God willing, perhaps you will find his treasure, although I find it quite unlikely...";
			link.l1 = "Danke, das ist sehr großzügig von dir!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		
		case "ReasonToFast_GMayor_21":
			dialog.text = "Dein Eifer ist lobenswert. Bitte nimm dieses Schwert als Belohnung an - es ist das Mindeste, was ich tun kann. Oh, und die Karte kannst du für dich behalten. Ich bin sicher, dass es viele solcher Fälschungen in der Karibik gibt.";
			link.l1 = "Danke, das ist sehr großzügig von Ihnen!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "Vielleicht, vielleicht... Nun, sagen wir einfach, dass dieser Handel durch göttliche Gerechtigkeit und durch den Willen unseres Herrn entschieden wurde.";
			link.l1 = "Danke, das ist sehr großzügig von dir!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "Halt deine Zunge, Junge! Du bist entweder verrückt oder im Bunde mit unseren Feinden! Wachen, ergreift diesen Idioten!";
			link.l1 = "Leg Hand an mich und du wirst sie verlieren!";
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		
		// --------------------------Операция 'Галеон'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = "Gerade jetzt ist das unmöglich. Er ist in Haft und wartet auf seinen Prozess.";
			link.l1 = "Ist er das? Und was wird ihm vorgeworfen?";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "Leider ist es keine Vermutung, sondern eine bewiesene Tatsache. Wir haben Informationen, dass er unter dem Vorwand der Patrouille Schiffe überfallen hat. Er konfiszierte Waren von Kaufleuten und verkaufte sie dann an Schmuggler und Piraten. Es ist eine Schande... zu denken, dass er einmal als einer der besten Kapitäne galt, die die Krone hatte...";
			link.l1 = "Und wer hat Ihnen die Beweise geliefert?";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "Einer seiner Opfer verfasste einen Bericht, in dem er den Vorfall im Detail beschrieb, einschließlich des Datums, des Namens des überfallenen Schiffes und der Mengen der beschlagnahmten Waren. "+"Vertraue mir, die Zahlen sind ziemlich beeindruckend. An jenem Tag Patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))+" Kapitän "+pchar.GenQuest.CaptainComission.Name+" war tatsächlich im Dienst. Der Kapitän beschrieb diesen Vorfall in seinem Bericht als Begegnung mit einem Piratenschiff, erwähnte aber überhaupt keine Fracht.";
			link.l1 = "Aber gab es überhaupt eine Fracht?";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "Es besteht kein Zweifel daran. Die geschädigte Partei ist ein sehr bekannter Mann und er würde sich nicht mit Verleumdung und übler Nachrede erniedrigen. Im Moment suchen unsere Patrouillen nach dem Versteck des Kapitäns. "+"Sobald es gefunden ist, kann der Kapitän vor Gericht erscheinen\nWenn Sie uns in dieser Angelegenheit Hilfe leisten, werden wir Ihnen sehr dankbar sein.";
			link.l1 = "Wahrscheinlich nicht. Ich kenne die Gegend nicht gut genug, um nach einem Versteck zu suchen. Entschuldigung, ich muss gehen.";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "Vielleicht... Wie viel Zeit habe ich?";
			link.l2.go = "CapComission_Mayor6";	
		break;
		
		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor6":
			dialog.text = "Ich glaube, dass die Patrouillen in zwei Tagen den Cache ohne deine Hilfe finden können, also solltest du dich beeilen."; 
			link.l1 = "Jawohl, ich kümmere mich darum. Aber ich muss Kapitän einen Besuch abstatten "+pchar.GenQuest.CaptainComission.Name+". Kann das arrangiert werden?";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "Das wird kein Problem sein. Ich werde den Kommandanten des Forts über Ihren Besuch informieren.";
			link.l1 = "Danke. Jetzt entschuldigen Sie mich bitte.";
			link.l1.go = "CapComission_Mayor8";
		break;
		
		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor9":
			dialog.text = "Ausgezeichnet! Wo ist der Schatz?";
			link.l1 = "Ich habe noch keine Ahnung. Er hat mir den genauen Ort nicht gezeigt.";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "Hmm, welch ein Zufall! Weißt du, er hat mir auch nicht den genauen Ort genannt...";
			link.l1 = "Ich arbeite daran.";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "Nicht mehr\nWachen! Bringt den Gefangenen zurück in die Kammern\nDu bist frei zu gehen, "+GetFullName(pchar)+".";
			link.l1 = "Aber Gouverneur...";
			link.l1.go = "CapComission_Mayor12";
		break;
		
		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";									
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);			
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = "Ausgezeichnet! Und wo suchen wir nach seinem Schatz?";
			link.l1 = "In dem "+RandPhraseSimple(RandPhraseSimple("nördlich","westlich"),RandPhraseSimple("östlichen","südlich"))+" Ende von "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+"Am Fuße der Klippe befindet sich eine große Nische, deren Eingang mit Steinen übersät ist. Das ist das Versteck.";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "Ausgezeichnete Arbeit! Und wo ist "+pchar.GenQuest.CaptainComission.Name+" selbst? Mir wurde gesagt, dass du ihn aus den Verliesen der Festung geholt hast.";
			link.l1 = "Leider ist er in einem Gefecht mit den Schmugglern ums Leben gekommen.";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "Das ist schlecht... Das ist sehr schlecht, "+GetSexPhrase("Herr","Fräulein")+" "+GetFullName(pchar)+". Ich wollte ihn öffentlich hinrichten, 'um die anderen zu ermutigen.'"+"So oder so, er hätte den Galgen nicht vermeiden können\nAlso, da du technisch gesehen das Gesetz gebrochen hast, indem du einen Gefangenen illegal freigelassen hast, ihn aber trotzdem nicht gerettet hast, kann ich das nicht in den Bericht aufnehmen. Daher bekommst du keine Belohnung... Aber ich möchte dir persönlich danken. Akzeptiere mein Geschenk - eine sehr nützliche Sache für einen kämpfenden Kapitän. ";
			link.l1 = "Danke. Immer froh zu dienen.";	
			link.l1.go = "CapComission_Mayor16";
		break;
		
		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------Операция 'Галеон'-----------------------------
		
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple("Wie machst du das? Selbst mit Rückenwind braucht man mindestens fünfzehn Tage, um dorthin zu gelangen!","Kapitän "+GetFullName(pchar)+", deine Verantwortungslosigkeit erstaunt mich! Warum hast du mir das nicht früher gesagt?");
				link.l1 = "Nun, ich weiß nicht einmal, was ich sagen soll...";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "Das ist großartige Neuigkeiten! Wir hatten bereits die Hoffnung aufgegeben zu sehen "+pchar.GenQuest.ShipWreck.Name+"  wieder lebendig. Ich werde sofort eine Rettungspartei entsenden. Oh, und bitte akzeptieren Sie diese Belohnung für Ihre Effizienz und Beteiligung an ihrer Rettung.";
				link.l1 = "Danke, Eure Gnaden. Ich bin froh, dass ich helfen konnte. Ich bin sicher, dass die Expedition rechtzeitig dort ankommt.";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen таймер на 30 дней тоже нужно снять
		break;
		
		case "ShipWreck2":
			dialog.text = "Wow....Was soll man dazu sagen? Geh und studiere das Seerecht, Junge! Wie auch immer, ich werde mein Bestes tun, um diese Leute zu retten.";
			link.l1 = "Eure Gnaden, aber ich habe ihnen genug Vorräte gelassen. Ihr habt Zeit, das versichere ich Euch ...";
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		
		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = "Ich bin mir bewusst, dass Sie, wie soll ich sagen... "+GetSexPhrase("bist ein Stammgast in Bordellen","besuche ab und zu gerne Bordelle")+". Und daher beschlossen, Sie um Hilfe zu bitten\n"+"Weißt du, es ist mir peinlich, es zuzugeben, aber ich war vor kurzem dort...";
			link.l1 = "Und was ist falsch daran? Sex ist eine völlig natürliche Sache, weißt du...";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "Oh, nein, ich predige nicht, nein. Die Sache ist, dass ich bei einer Gelegenheit zu viel getrunken habe und meinen Ehering verloren habe...";
			link.l1 = "Das ist ein Problem. Es tut mir leid.";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "HI brauche niemanden, der mir leid tut. Ich brauche meinen Ring zurück. Wenn du es schaffst, ihn vor Mitternacht zurückzuholen, werde ich sehr großzügig sein. Wenn Sie scheitern, wird meine Frau mich umbringen.";
			link.l1 = "Ich sehe... Und wo genau könnten Sie es verloren haben? Erinnern Sie sich an etwas Besonderes?";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "Leider nein. Gar nichts.";
			link.l1 = "Ich verstehe. Nun, dann lass uns danach suchen.";
			link.l1.go = "TakeRing_5";
			link.l2 = "Weißt du, "+GetAddress_FormToNPC(NPChar)+", Ich glaube, ich werde diese auslassen. Bitte entschuldigen Sie mich...";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "Ausgezeichnet! Aber denke daran - du musst es vor Mitternacht finden.";
			link.l1 = "Ich erinnere mich. Ich komme bald zurück.";
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo("The ring is at " + sld.startLocation + ", in locator " + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = "Oh? Nun, das war wirklich unerwartet... Nun, viel Glück dann, Kapitän.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = "Das ist mein Ring! Du hast mein Leben gerettet!";
			link.l1 = "Es ist nichts, Herr.";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "Hier ist dein Geld für einen gut gemachten Job! Ich bin dir sehr dankbar!";
			link.l1 = "Froh zu helfen, Herr, bitte seien Sie das nächste Mal vorsichtiger.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = "Herr, hab Erbarmen! Ich sollte wirklich aufhören, so viel zu trinken...";
			link.l1 = "Das ist sicher! Hier ist dein Ring.";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "Ja, ja, vielen Dank. Ich bin in deiner Schuld! Hier ist dein Geld für einen gut gemachten Job!";
			link.l1 = "Danke "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 3);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Wir haben doch schon alles besprochen, oder?";
                    link.l1 = "Richtig. Ich halte dich nicht länger auf.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Es tut mir leid, dich zu verärgern, aber ich habe im Moment keine Zeit, mit dir zu reden. Wie du wissen solltest, wurde unsere Kolonie angegriffen von "+NationNamePeople(sti(aData.nation))+". Ich muss unsere Verteidigung überprüfen.";
                    link.l1 = "Nun, ich wollte nur meine Hilfe bei der Verteidigung des Forts anbieten.";
                    link.l1.go = "siege_task";
                    link.l2 = "Dann werde ich Sie nicht weiter verzögern.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Ach, du bist es, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", ich freue mich, dich zu sehen. Gute Nachrichten - wir haben es geschafft, den "+NationNameSK(sti(aData.nation))+" Eindringlinge. Du hast auch deinen Teil dazu beigetragen, und hier ist deine Belohnung - "+(sti(aData.iSquadronPower)*1500)+" Stücke von Acht. Hier, nehmt das.";
                    link.l1 = "Danke, "+GetAddress_FormToNPC(NPChar)+", ein Vergnügen, Geschäfte mit Ihnen zu machen!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Also, was war der Grund für dich, hierher zu kommen und mich von wichtigen Staatsangelegenheiten abzulenken?";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Ich wollte arbeiten für "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" Ich habe einige Piraten getroffen. Alle "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" sind momentan an Bord. Ich möchte sie den Behörden übergeben.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Ich wollte mit dir über eine wichtige Angelegenheit sprechen.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Es gibt einen Kapitän, der die Patrouille befehligt "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Konto"))+" genannt "+pchar.GenQuest.CaptainComission.Name+", wie kann ich ihn treffen?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Ehemaliger Kapitän im Kommando der Patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Konto"))+" "+pchar.GenQuest.CaptainComission.Name+" hat zugestimmt, sein Versteck den Behörden zu offenbaren.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Ehemaliger Kapitän im Kommando der Patrouille  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Akz"))+" "+pchar.GenQuest.CaptainComission.Name+" hat mir sein Versteck gezeigt.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Das"))+" Ich traf einen Kapitän "+pchar.GenQuest.ShipWreck.Name+" und seine Matrosen, die von Piraten an Land gesetzt wurden "+pchar.GenQuest.ShipWreck.BadName+". "+"Leider hatte ich bereits zu viele Männer auf meinem Schiff und konnte sie daher nicht an Bord nehmen. Aber ich habe ihnen Essen und Waffen hinterlassen. Wenn das Rettungsschiff sie nicht innerhalb "+(30 - iDay)+" Tage, dann weiß ich nicht, ob sie noch am Leben sein werden oder nicht.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Ich habe Seeleute von einem Wrack des Schiffes ' getroffen"+pchar.GenQuest.ShipWreck.ShipTypeName+"' mit ihrem Kapitän. "+"Leider hatte ich bereits zu viele Männer auf meinem Schiff und konnte sie daher nicht an Bord nehmen. Aber ich ließ ihnen Essen und Waffen zurück. Wenn das Rettungsschiff sie nicht innerhalb "+(30 - iDay)+" Tage, dann weiß ich nicht, ob sie noch lebendig sind oder nicht.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Ich habe eine Nachricht aus der Stadt "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Milord, ich habe eine Bande von Schmugglern ausfindig gemacht, deren Anführer kürzlich von den Wachen gefangen genommen wurde. Jetzt planen sie seine Flucht. Ihr Schiff '"+PChar.GenQuest.JusticeOnSale.ShipName+"liegt vor Anker bei "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Ich muss den gefangenen Kapitän den Behörden übergeben.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Ich bin hier für die Regatta. Hier ist meine Einladung.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Vielleicht möchtest du eine Pause machen?";
        			link.l5.go = "Play_Game";
        			link.l10 = "Es war nur ein Höflichkeitsbesuch, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Helen_node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Wir haben doch bereits alles besprochen, oder nicht?";
                    link.l1 = "Richtig. Ich halte dich nicht länger auf.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Es tut mir leid, Sie zu verärgern, aber ich habe im Moment keine Zeit, mit Ihnen zu reden. Wie Sie wissen sollten, wurde unsere Kolonie angegriffen von "+NationNamePeople(sti(aData.nation))+". Ich muss unsere Verteidigung überprüfen.";
                    link.l1 = "Nun, ich wollte nur meine Hilfe bei der Verteidigung der Festung anbieten.";
                    link.l1.go = "siege_task";
                    link.l2 = "Dann werde ich Sie nicht weiter aufhalten.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Oh, du bist es, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", Ich freue mich, dich zu sehen. Gute Nachrichten - wir haben es geschafft, die "+NationNameSK(sti(aData.nation))+" Eindringlinge. Du hast auch deinen Teil dazu beigetragen, und hier ist deine Belohnung - "+(sti(aData.iSquadronPower)*1500)+" Stücke von Acht. Hier gehst du.";
                    link.l1 = "Danke, "+GetAddress_FormToNPC(NPChar)+", ein Vergnügen, Geschäfte mit Ihnen zu machen!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Was bringt dich zu mir? Ich dachte, du regelst alle deine Angelegenheiten mit deinem... Patron. Aber sprich, ich höre dir immer gerne zu.";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Ich wollte arbeiten für "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" Ich traf einige Piraten. Alle "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" sind momentan an Bord. Ich möchte sie den Behörden übergeben.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Ich wollte mit dir über eine wichtige Angelegenheit sprechen.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Es gibt einen Kapitän, der das Patrouillenkommando führt "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Konto"))+" genannt "+pchar.GenQuest.CaptainComission.Name+", wie kann ich ihn treffen?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Ehemaliger Kapitän im Befehl der Patrouille "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Konto"))+" "+pchar.GenQuest.CaptainComission.Name+" hat zugestimmt, seinen Versteck den Behörden zu offenbaren.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Ehemaliger Kapitän im Kommando der Patrouille  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Akk"))+" "+pchar.GenQuest.CaptainComission.Name+" hat mir sein Versteck enthüllt.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Ich habe einen Kapitän getroffen "+pchar.GenQuest.ShipWreck.Name+" und seine Matrosen, die von Piraten an Land gesetzt wurden "+pchar.GenQuest.ShipWreck.BadName+". "+"Leider hatte ich bereits zu viele Männer auf meinem Schiff und konnte sie daher nicht an Bord nehmen. Aber ich ließ ihnen Essen und Waffen. Wenn das Rettungsschiff sie nicht innerhalb "+(30 - iDay)+" Tage, dann weiß ich nicht, ob sie noch am Leben sein werden oder nicht.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Ich habe Matrosen von einem Schiffswrack des Schiffes ' getroffen"+pchar.GenQuest.ShipWreck.ShipTypeName+"' mit ihrem Kapitän. "+"Leider hatte ich bereits zu viele Männer an Bord meines Schiffs und konnte sie daher nicht aufnehmen. Aber ich ließ ihnen Essen und Waffen zurück. Wenn das Rettungsschiff sie nicht innerhalb "+(30 - iDay)+" Tage, dann weiß ich nicht, ob sie noch am Leben sind oder nicht.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Ich habe eine Nachricht aus der Stadt "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Milord, ich habe eine Bande von Schmugglern ausfindig gemacht, deren Anführer kürzlich von den Wachen erwischt wurde. Jetzt planen sie seine Flucht. Ihr Schiff '"+PChar.GenQuest.JusticeOnSale.ShipName+" liegt vor Anker bei "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Ich muss den gefangenen Kapitän den Behörden übergeben.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Ich bin hier für die Regatta. Hier ist meine Einladung.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Vielleicht möchtest du eine Pause einlegen?";
        			link.l5.go = "Play_Game";
        			link.l10 = "Es war nur ein Höflichkeitsbesuch, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Nicht jetzt! Wir haben eine Inspektion, Don de Alamida ist in der Stadt. Oh, jedes Jahr das Gleiche, was habe ich getan, um das zu verdienen...";
				link.l1 = "Wie Sie sagen. Ich werde Sie nicht ablenken.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			dialog.text = "Hmm, und welche Art von Spielen bevorzugst du?";
			link.l1 = "Möchtest du um ernsthaftes Geld eine Partie Karten spielen?";
			link.l1.go = "Card_Game";
   			link.l2 = "Wie wäre es mit einigen Würfeln im Poker-Joker?";
			link.l2.go = "Dice_Game";
			link.l10 = "Bitte entschuldigen Sie mich, aber die Pflicht ruft.";
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Entschuldigen Sie, Monsignor, aber ich habe gerade keine Zeit dafür. Vielleicht beim nächsten Mal."; // Jason НСО
                else dialog.text = "Ich spiele nicht mit Piraten!";
    			link.l1 = "Wie du wünschst.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "Warum nicht! Entspannung ist gut für das Herz, aber nicht für die Börse...";
	    			link.l1 = "Ausgezeichnet.";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "Welches sind die Regeln unseres Spiels?";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "Nein, für heute habe ich genug. Ich habe Dinge zu erledigen.";
	    			link.l1 = "Wie du wünschst.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Nun, dann lasst uns beginnen!";
			link.l1.go = "Cards_begin";
			link.l3 = "Nein, das ist nichts für mich...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "Lassen wir uns zuerst auf die Wette einigen.";
			link.l1 = "Lass uns um 1000 Acht-Stücke spielen.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Lass uns um 5000 Achtstücke spielen.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Ich denke, ich muss gehen.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Du bist ein berüchtigter Betrüger. Ich werde nicht mit dir spielen.";
                link.l1 = "Das ist alles Lüge!";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Machst du Witze, "+GetAddress_Form(NPChar)+"? Du hast kein Geld!";
                link.l1 = "Es passiert.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "Das ist es! Ich habe genug von Karten - bevor sie mich einen Verschwender nennen und mich zwingen, meinen Posten zu verlassen.";
                link.l1 = "Schade.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Gut, lass uns um 1000 Achtstücke spielen.";
			link.l1 = "Lass uns anfangen!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Du bist ein berüchtigter Betrüger. Ich werde nicht mit dir spielen.";
                link.l1 = "Das ist alles Lüge! Na ja, was auch immer.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "Sie sagen, du bist ein sehr guter Spieler. Ich werde nicht um hohe Einsätze mit dir spielen.";
                link.l1 = "Sollen wir vielleicht den Einsatz senken?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "Es tut mir leid, aber ich muss gehen.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Machst du Witze, "+GetAddress_Form(npchar)+"? Du hast nicht 15000 Achtstücke!";
                link.l1 = "Ich werde sie erhöhen!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Nein, diese Wetten werden die Stadtkasse leeren.";
                link.l1 = "Wie du wünschst.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Gut, spielen wir um 5000 Achtstücke.";
			link.l1 = "Lass uns anfangen!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Verzeihen Sie, Monsignore, aber ich habe jetzt keine Zeit dafür. Vielleicht nächstes Mal."; // Jason НСО
                else dialog.text = "Ich werde nicht mit Piraten spielen!";
    			link.l1 = "Wie du wünschst.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Warum nicht! Entspannung tut dem Herzen gut... aber nicht dem Geldbeutel...";
	    			link.l1 = "Ausgezeichnet.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "Wie lauten die Regeln unseres Spiels?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Nein, für heute habe ich genug. Ich habe Dinge zu erledigen.";
	    			link.l1 = "Wie du wünschst.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Nun, dann lass uns beginnen!";
			link.l1.go = "Dice_begin";
			link.l3 = "Nein, das ist nichts für mich...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			dialog.text = "Lassen wir uns zuerst auf die Wette einigen.";
			link.l1 = "Lass uns um 500 Achtstückmünzen pro Würfel spielen.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Lassen Sie uns für 2000 Achtstücke pro Würfel spielen.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Ich schätze, ich muss gehen.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Du bist ein berüchtigter Betrüger. Ich werde nicht mit dir spielen.";
                link.l1 = "Es ist alles Lügen! Na ja, was auch immer.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Machst du Witze, "+GetAddress_Form(NPChar)+"? Du hast kein Geld!";
                link.l1 = "Es passiert.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "Das ist es! Ich habe genug vom Glücksspiel - bevor sie mich noch einen Verschwender nennen und mich zwingen, meinen Posten zu verlassen...";
                link.l1 = "Schade.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Gut, wir spielen um 500 Achtstücke.";
			link.l1 = "Lass uns anfangen!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Du bist ein berüchtigter Betrüger. Ich werde nicht mit dir wetten.";
                link.l1 = "Das ist alles gelogen! Na ja, was auch immer.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Man sagt, du bist ein sehr guter Spieler. Ich werde nicht um hohe Einsätze mit dir spielen.";
                link.l1 = "Sollen wir vielleicht den Einsatz senken?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Es tut mir leid, aber ich muss gehen.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Machst du Witze, "+GetAddress_Form(NPChar)+"? Du hast keine 15000 Dublonen!";
                link.l1 = "Ich werde sie hochziehen!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Nein, diese Wetten werden die Stadtkasse sicherlich leeren.";
                link.l1 = "Wie du wünschst.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Gut, wir spielen um 2000 Achtstücke pro Würfel.";
			link.l1 = "Lass uns anfangen!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.text = "In diesem Fall würde ich Sie bitten, mein Studium zu verlassen und mich nicht weiter von meiner Arbeit abzulenken";
			link.l1 = "Ja, ja, natürlich. Entschuldigung für die Störung.";
			link.l1.go = "exit";
		break;

		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = "Das ist ein Fehler. Benachrichtige die Entwickler darüber.";
        	link.l1 = "Danke, das ist ein großartiges Spiel!";
        	link.l1.go = "exit";
			
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Nicht jetzt! Wir haben eine Inspektion, Don de Alamida ist in der Stadt. Oh, jedes Jahr das gleiche, was habe ich getan, um das zu verdienen...";
				link.l1 = "Wie du willst. Ich werde dich nicht ablenken.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple("Soweit ich das beurteilen kann, haben Sie bereits eine Mission von dem Gouverneur von "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen")+". Beende den Job, den du bereits hast, und wir werden reden.","Hmm, warst du das nicht in "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Voc")+" wo Sie Befehle vom örtlichen Gouverneur angenommen haben? Ja, das ist korrekt. Beenden Sie zuerst diese Mission.");
					link.l1 = RandPhraseSimple("Ich sehe...","Verstanden..."+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".");
					link.l1.go = "exit";					
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase("Eine Mission, um Banditen zu lokalisieren "+GetFullName(arName)+" wurde dir bereits ausgestellt. Erfülle es jetzt!","Sie haben bereits eine Mission, einen Banditen namens zu lokalisieren "+GetFullName(arName)+". Ich warte auf die Ergebnisse!","Während du deine Zeit in meiner Residenz verschwendest, "+GetFullName(arName)+" beraubt unsere Kolonisten! Mach dich an die Arbeit!");
							link.l1 = RandPhraseSimple("In Ordnung, "+GetAddress_FormToNPC(NPChar)+".","Ich bin damit beschäftigt, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Die dir gegebene Zeit, diesen Banditen zu finden und auszuschalten, ist vorbei. Und welche Art von Berichten denkst du, erhalte ich? Und ich werde dir sagen - "+GetFullName(arName)+" lebt noch und tritt! Jetzt erklären Sie sich, "+GetAddress_Form(NPChar)+".","Die dir gegebene Zeit, diesen Schurken namens "+GetFullName(arName)+", ist ausgegangen. Trotzdem höre ich, dass überhaupt kein Fortschritt gemacht wurde. Was ist los?");
							link.l1 = "Ich konnte Ihre Arbeit nicht zur festgelegten Zeit erledigen, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du es geschafft, den besagten Banditen zu beseitigen? "+GetFullName(arName)+" ist endlich tot?","Sag mir nur eine Sache - ist "+GetFullName(arName)+" tot oder lebendig?");
							link.l1 = "Leider, immer noch am Leben, "+GetAddress_FormToNPC(NPChar)+". Ich habe es geschafft, ihn ausfindig zu machen, aber ich war unterlegen und musste mich zurückziehen. Dieser Bandit ist ein wirklich harter Bastard. Es tut mir leid.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du es geschafft, den besagten Banditen zu beseitigen? "+GetFullName(arName)+" ist endlich tot?","Sag mir nur eins - ist "+GetFullName(arName)+" tot oder lebendig?");
							link.l1 = "Er ist tot, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 180);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контркурьер ---------->>
				if (QuestName == "TakePostcureer")
				{
					switch (pchar.GenQuest.TakePostcureer)
					{
						case "":
							dialog.text = LinkRandPhrase("Eine Mission zur Ergreifung eines Kurierschiffes wurde dir bereits erteilt. Jetzt erfülle sie!","Du hast bereits eine Mission, ein Kurierschiff zu kapern! Ich warte auf die Ergebnisse!","Während du deine Zeit in meiner Residenz verschwendest, rutschen die Dokumente, die ich benötige, direkt in die Hände unseres Feindes! Mach dich an die Arbeit!");
							link.l1 = RandPhraseSimple("In Ordnung, "+GetAddress_FormToNPC(NPChar)+".","Ich bin damit beschäftigt, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Die Ihnen gegebene Zeit, um dieses Kurierschiff zu lokalisieren und zu fangen, ist vorbei. Und welche Art von Berichten erhalte ich, glauben Sie? Und ich werde Ihnen sagen - die Dokumente, die ich erwartete, fielen direkt in die Hände unseres Feindes! Nun deignen Sie sich zu erklären, "+GetAddress_Form(NPChar)+".","Alle dir gegebenen Fristen, um die Dokumente vom Kurierschiff zu beschaffen, sind abgelaufen. Trotzdem wurde überhaupt kein Fortschritt gemacht. Was ist das?");
							link.l1 = "Ich konnte die Arbeit nicht rechtzeitig erledigen, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du es geschafft, die Dokumente zu beschlagnahmen?","Sag mir nur eines - hast du es geschafft, die Korrespondenz zu sichern?");
							link.l1 = "Leider nein, "+GetAddress_FormToNPC(NPChar)+". Ich habe das Schiff gefunden, aber die Dokumente haben mich entkommen lassen.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du es geschafft, die Dokumente zu beschaffen?","Sag mir nur eines - hast du es geschafft, die Korrespondenz zu sichern?");
							link.l1 = "Ja, "+GetAddress_FormToNPC(NPChar)+". Ich habe sie. Hier bitte.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							RemoveItems(pchar, "ContraPostLetters", 1);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контрфрахт - арсенал ---------->>
				if (QuestName == "TakeArsenalship")
				{
					switch (pchar.GenQuest.TakeArsenalship)
					{
						case "":
							dialog.text = LinkRandPhrase("Eine Mission zur Zerstörung eines Militärtransports wurde Ihnen bereits erteilt. Jetzt erfüllen Sie es!","Du hast bereits eine Mission, einen Militärtransport zu zerstören! Ich warte auf die Ergebnisse!","Während du deine Zeit in meiner Residenz verschwendest, werden Schießpulver und Munition direkt zu den Kanonen des Feindes geliefert! Mach dich an die Arbeit!");
							link.l1 = RandPhraseSimple("In Ordnung, "+GetAddress_FormToNPC(NPChar)+".","Ich bin damit beschäftigt, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Die Dir gegebene Zeit, diesen Militärtransport zu lokalisieren und zu zerstören, ist vorbei. Und welche Art von Berichten erhalte ich, wie denkst Du? Und ich werde Dir sagen - der feindliche Konvoi hat sein Ziel erfolgreich erreicht! Jetzt würdige, Dich zu erklären, "+GetAddress_Form(NPChar)+".","Alle dir gegebenen Fristen, um den feindlichen Militärtransport zu zerstören, sind abgelaufen. Dennoch wurde überhaupt kein Fortschritt gemacht. Was ist los?");
							link.l1 = "Ich konnte Ihre Aufgabe in der vorgegebenen Zeit nicht ausführen, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du es geschafft, den feindlichen Transport zu zerstören?","Sag mir nur eins - liegt dieses feindliche Inventar auf dem Meeresboden?");
							link.l1 = "Leider nein, "+GetAddress_FormToNPC(NPChar)+". Ich habe den Konvoi gefunden, es aber nicht geschafft, das erforderliche Schiff zu versenken.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du es geschafft, diesen feindlichen Transport zu zerstören?","Sag mir nur eins - liegt das Arsenal des Feindes auf dem Meeresboden?");
							link.l1 = "Ja, "+GetAddress_FormToNPC(NPChar)+". Unser Feind wird dieses Schießpulver und Munition nicht erhalten.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 220);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- ОЗГ - пират ---------->>
				if (QuestName == "TakePirateship")
				{
					switch (pchar.GenQuest.TakePirateship)
					{
						case "":
							dialog.text = LinkRandPhrase("Eine Mission zur Eliminierung eines Piraten wurde bereits an dich vergeben. Nun erfülle sie!","Du hast bereits eine Mission, ein Piratenschiff zu zerstören! Ich warte auf die Ergebnisse!","Während du deine Zeit in meiner Residenz vergeudest, plündert dieser schmutzige Pirat schon wieder ein unschuldiges Opfer! Mach dich an die Arbeit!");
							link.l1 = RandPhraseSimple("In Ordnung, "+GetAddress_FormToNPC(NPChar)+".","Ich bin damit beschäftigt, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Die dir gegebene Zeit, den Piraten zu finden und zu eliminieren, ist vorbei. Und welche Art von Berichten erhalte ich, denkst du? Und ich sage dir - dieser verdammte Pirat überfällt immer noch unsere Schiffe! Nun erbarme dich, dich zu erklären, "+GetAddress_Form(NPChar)+".","Alle dir gegebenen Fristen, das Piratenschiff zu zerstören, sind abgelaufen. Trotzdem wurde überhaupt kein Fortschritt gemacht. Was ist los?");
							link.l1 = "Ich konnte Ihre Aufgabe nicht rechtzeitig erledigen, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du es geschafft, das Piratenschiff zu zerstören?","Sag mir nur eine Sache - liegt dieser schmutzige Pirat endlich auf dem Meeresboden?");
							link.l1 = "Leider nein, "+GetAddress_FormToNPC(NPChar)+". Ich habe es geschafft, diesen Schurken ausfindig zu machen, aber es ist mir nicht gelungen, sein Schiff zu versenken.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du es geschafft, das Piratenschiff zu zerstören?","Sag mir nur eine Sache - ruht dieser schmutzige Pirat endlich auf dem Meeresgrund?");
							link.l1 = "Ja, "+GetAddress_FormToNPC(NPChar)+". Dieser Schurke wird unseren Handelsschiffverkehr nicht mehr stören.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
					//-------- ОЗГ - пассажир ---------->>
				if (QuestName == "TakePassenger")
				{
					switch (pchar.GenQuest.TakePassenger)
					{
						case "":
							dialog.text = LinkRandPhrase("Eine Mission zur Suche nach einem Verbrecher wurde dir bereits erteilt. Erfülle sie jetzt!","Du hast bereits eine Mission, um einen Kriminellen zu suchen! Ich warte auf die Ergebnisse!","Während du deine Zeit in meiner Residenz verschwendest, segelt dieser schmutzige Schurke weiterhin herum! Führe sofort die dir anvertraute Mission aus!");
							link.l1 = RandPhraseSimple("In Ordnung, "+GetAddress_FormToNPC(NPChar)+".","Ich bin damit beschäftigt, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Die dir gegebene Zeit, diesen Schurken zu finden, ist vorbei. Und welche Art von Berichten erhalte ich, wie denkst du? Und ich sage dir - er ist erfolgreich an seinem Ziel angekommen und dann in Luft aufgelöst! Nun deign dich zu erklären, "+GetAddress_Form(NPChar)+".","Alle dir gegebenen Fristen, um den Verbrecher zu finden, sind abgelaufen. Dennoch wurde überhaupt kein Fortschritt gemacht. Was ist los?");
							link.l1 = "Ich konnte Ihre Aufgabe nicht in der vorgegebenen Zeit ausführen, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du den Schurken gefangen?","Sag mir nur eins - ist dieser schmutzige Schurke in deinem Frachtraum, geknebelt und gefesselt?");
							link.l1 = "Leider nein, "+GetAddress_FormToNPC(NPChar)+". Ich habe es nicht geschafft, den Schurken zu fangen. Er ging mit dem Schiff unter, auf dem er war.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du den Schurken gefangen?","Sag mir nur eine Sache - ist dieser schmutzige Schurke in deinem Laderaum, geknebelt und gefesselt?");
							link.l1 = "Ja, "+GetAddress_FormToNPC(NPChar)+". Bitte schickt Eure Soldaten zum Pier, und ich werde ihn Euch übergeben.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							sld.lifeday = 0;
						break;
					}
				}
				//-------- таможенный патруль ---------->>
				if (QuestName == "CustomPatrol")
				{
					switch (pchar.GenQuest.CustomPatrol)
					{
						case "":
							dialog.text = LinkRandPhrase("Eine Mission, die Schmuggler ausfindig zu machen, wurde Ihnen bereits erteilt. Erfüllt sie nun!","Du hast bereits eine Mission, die Schmuggler zu suchen! Ich warte auf die Ergebnisse!","Während du deine Zeit in meiner Residenz vergeudest, bereiten sich diese Schmuggler darauf vor, einen weiteren Deal abzuschließen! Setze sofort die dir anvertraute Mission fort!");
							link.l1 = RandPhraseSimple("In Ordnung, "+GetAddress_FormToNPC(NPChar)+".","Ich bin damit beschäftigt, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Die dir gegebene Zeit, die Schmuggler zu finden, ist vorbei. Und welche Art von Berichten erhalte ich, was glaubst du? Und ich sage dir - sie haben fröhlich alle ihre Waren verkauft! Nun würdigen Sie, sich zu erklären, "+GetAddress_Form(NPChar)+".","Alle dir gegebenen Hinweise, um die Schmuggler zu finden, sind erschöpft. Trotzdem wurde überhaupt kein Fortschritt gemacht. Was ist los?");
							link.l1 = "Ich konnte Ihre Aufgabe nicht rechtzeitig ausführen, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du mit den Schmugglern abgerechnet?","Sag mir nur eines - hast du den Deal dieser Schmuggler vereitelt?");
							link.l1 = "Leider nein, "+GetAddress_FormToNPC(NPChar)+". Ich habe es nicht geschafft, die Pläne dieser Schurken zu vereiteln.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du mit den Schmugglern fertig?","Sag mir nur eines - hast du den Deal dieser Schmuggler zunichte gemacht?");
							link.l1 = "Ja, "+GetAddress_FormToNPC(NPChar)+". Ich habe sie eingeholt und die Schiffe beider Parteien, Käufer und Verkäufer gleichermaßen, eliminiert.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 300);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- Дезертир ---------->>
				if (QuestName == "FindFugitive")
				{
					switch (pchar.GenQuest.FindFugitive)
					{
						case "":
							dialog.text = LinkRandPhrase("Eine Mission, den Deserteur zu suchen, wurde dir bereits erteilt. Erfülle sie jetzt!","Du hast bereits eine Mission, den Deserteur zu suchen! Ich warte auf die Ergebnisse!","Während du deine Zeit in meiner Residenz vergeudest, könnte dieser Deserteur gerade unsere Staatsgeheimnisse verraten! Führe sofort die Mission aus, die dir anvertraut wurde!");
							link.l1 = RandPhraseSimple("In Ordnung, "+GetAddress_FormToNPC(NPChar)+".","Ich bin damit beschäftigt, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Die dir gegebene Zeit, den Deserteur zu finden, ist vorbei. Und was für Berichte bekomme ich, glaubst du? Und ich sage dir - kein Ergebnis, überhaupt keins! Nun würdige dich zu erklären, "+GetAddress_Form(NPChar)+".","Alle Ihnen gegebenen Fristen, um den Deserteur zu finden, sind abgelaufen. Trotzdem wurden überhaupt keine Fortschritte gemacht. Was ist los?");
							link.l1 = "Ich konnte Ihre Arbeit nicht rechtzeitig erledigen, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Also, was sagst du? Hast du den Deserteur gefangen?","Sag mir nur eins - ist dieser Deserteur in deinem Laderaum, geknebelt und gefesselt?");
							link.l1 = "Leider nein, "+GetAddress_FormToNPC(NPChar)+". Ich habe es versäumt, diesen Schurken zu fangen. Ich habe seine Spur in der Siedlung von "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.City)+", aber genau am Tag vor meiner Ankunft ist er auf einem Piratenschiff nach Süden gefahren. Ich vermute, er ist jetzt bei diesen Glücksrittern.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Ach ja... Hier ist unser "+pchar.GenQuest.FindFugitive.Name+"... Gute Arbeit, Kapitän! Hatten Sie eine harte Zeit bei der Suche?","Oh, welche Gäste wir haben! Hallo, "+pchar.GenQuest.FindFugitive.Name+"! Tolle Arbeit, Kapitän! Haben Sie viel Mühe in Ihre Suche gesteckt?");
							link.l1 = "Wie soll ich sagen, "+GetAddress_FormToNPC(NPChar)+". Was auch immer es war - deine Mission ist erfüllt worden.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 300);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar, "authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							LAi_SetActorType(sld);
							sld.lifeday = 0;
							pchar.quest.FindFugitive_Over.over = "yes"; //снимаем таймер
							chrDisableReloadToLocation = false;//открыть локацию
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple("Die dir gegebene Zeit, den Brief zu liefern, ist vorbei. Und ich nehme an, dass du gescheitert bist.","Die Zeit ist abgelaufen. Trotzdem wurde überhaupt kein Fortschritt erzielt. Was ist los?");
								link.l1 = "Ich konnte Ihre Aufgabe nicht erfüllen, "+GetAddress_FormToNPC(NPChar)+".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("Eine Mission, mir einen Brief zu liefern, wurde dir bereits erteilt. Erfülle sie jetzt!","Du hast bereits eine Mission, einen Brief direkt an mich zu liefern! Ich warte auf die Ergebnisse, ich brauche diesen Brief so schnell wie möglich!","Während du deine Zeit in meiner Residenz verschwendest, befindet sich die Information, die ich dringend benötige, noch immer in den Händen der Person, die sie mir senden soll! Mach dich sofort auf den Weg und erfülle die dir anvertraute Mission!");
								link.l1 = RandPhraseSimple("In Ordnung, "+GetAddress_FormToNPC(NPChar)+".","Ich werde mich sofort darum kümmern, "+GetAddress_FormToNPC(NPChar)+".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Haben Sie den Brief geliefert, den ich erwarte?","Sag mir jetzt - hast du es?!");
							link.l1 = "Ja, das tue ich. Wie vereinbart - persönlich an Sie geliefert.";
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							else
							{
								link.l1.go = "All_Execute";		
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				break;
			}
			sTemp = npchar.city;
			//занят ПГГ
			i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
			if (i != -1)
			{
				dialog.text = "Ach, heute habe ich keine Arbeit für dich. Die letzte wurde erledigt von "+GetFullName(&Characters[i])+". Kommt morgen, vielleicht taucht etwas auf.";
				link.l1 = "Oh, verdammt! Kein Glück...";
				link.l1.go = "exit";
				break;
			}
//navy <--
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
    		{	
				SaveCurrentNpcQuestDateParam(npchar, "work_date");
				if(CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)
				{
					dialog.text = "Sie sind gerade rechtzeitig, Kapitän. Ich muss mich mit einem dringenden Problem befassen, das mit dem Schmuggel von Waren in unsere Kolonie verbunden ist. Ich nehme an, Ihr Schiff ist seetüchtig und kampfbereit.";
					link.l1 = "Mein Schiff ist immer seetüchtig und bereit für die Schlacht. Erzählen Sie mir mehr über die bevorstehende Mission, Euer Gnaden.";
					link.l1.go = "CustomPatrol";
					break;
				}
				if (rand(5) > 4 && !bBettaTestMode && pchar.location == "Panama_townhall") // patch-5
				{
					dialog.text = LinkRandPhrase("Für jetzt habe ich keine Arbeit für dich. Komm morgen, vermute ich...","Ach, ich habe heute keine Arbeit für dich. Bitte, komm in ein oder zwei Tagen wieder vorbei.","Heute gibt es nichts, was ich Ihnen vorschlagen könnte. Ich würde mich freuen, Sie an einem anderen Tag zu sehen.");
					link.l1 = "Ich verstehe, "+GetAddress_FormToNPC(NPChar)+".";
					link.l1.go = "exit";
				}
				else
				{
					sTemp = GetSpyColony(npchar);
					// не даём задание пробраться во вражеский город, если у нации ГГ нет врагов
					if (sTemp == "none")
						i = 1 + hrand(6);
					else
						i = hrand(7);
					switch (i)
					{
						//========== пробраться во вражеский город ============//Jason: оставляем, как годный
						case 0:
							pchar.GenQuest.Intelligence.Terms = hrand(10) + (42 - MOD_SKILL_ENEMY_RATE); //сроки выполнения задания
							pchar.GenQuest.Intelligence.Money = ((hrand(4) + 6) * 2000) + (sti(pchar.rank) * 1000 + 10000); //вознаграждение
							pchar.GenQuest.Intelligence.City = sTemp; //враждебная колония
                            sTemp = ", which is on " + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat");                         
							dialog.text = "Ich habe eine Mission für dich, die einige ernsthafte Risiken beinhaltet. Ich brauche dich, um dich einzuschleichen in "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Akz")+sTemp+", treffe dort eine bestimmte Person und bringe mir dann, was er dir geben würde.";
							link.l1 = "Hmm, ich glaube nicht, dass in "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" Ich werde ein willkommener Gast sein...";
							link.l1.go = "Intelligence";
						break;
						//========== квест уничтожения банды ============ //Jason: оставляем, как классику
						case 1:
							pchar.GenQuest.DestroyGang.Terms = hrand(2) + 2; //сроки выполнения задания
							pchar.GenQuest.DestroyGang.Money = ((hrand(6)+4)*500)+(sti(pchar.rank)*300+2000); //вознаграждение
							makearef(arName, pchar.GenQuest.DestroyGang);
							arName.nation = PIRATE;
							arName.sex = "man";
							SetRandomNameToCharacter(arName); //имя бандита в структуру квеста	
							dialog.text = "Gerade jetzt habe ich eine Mission für dich. Im Dschungel in der Nähe "+XI_ConvertString("Colony"+npchar.city+"Gen")+" eine Bande von Räubern ist aufgetaucht, und ich weiß, dass ein Anführer davon heißt "+GetFullName(arName)+". Lokalisieren und eliminieren Sie diese Bande von Schlägern.";
							link.l1 = "Bin ich irgendwie in den Bedingungen eingeschränkt?";
							link.l1.go = "DestroyGang";
						break;
						
						//========== контркурьер - отобрать почту ============
						case 2:
							dialog.text = "Ja, ich habe eine Mission für dich. Um sie zu erfüllen, musst du Schnelligkeit und auch einige Fähigkeiten im Seekampf beweisen. Bist du bereit, deinen Wert zu zeigen?";
							link.l1 = "Eure Gnaden, könnten Sie mehr Details über die Mission verraten?";
							link.l1.go = "TakePostcureer";
						break;
						
						//========== контрфрахт - потопить корабль с боеприпасами ============
						case 3:
							dialog.text = "Ja, ich habe eine Mission für dich. Um sie zu erfüllen, musst du außergewöhnliche Tapferkeit beweisen und auch einige Fähigkeiten im Seekampf haben. Bist du bereit, deinen Wert zu zeigen?";
							link.l1 = "Eure Gnaden, könnten Sie mehr Einzelheiten über die bevorstehende Mission preisgeben?";
							link.l1.go = "TakeArsenalship";
						break;
						//========== ОЗГ - охотник на пирата ============
						case 4:
							dialog.text = "Ja, ich habe eine wichtige Mission für dich. Um sie zu erfüllen, müsstest du all deine Fähigkeiten einsetzen. Das betrifft Piraten...";
							link.l1 = "Piraten? Könnt ihr mir genauer sagen, was von mir erwartet wird?";
							link.l1.go = "TakePirateship";
						break;
						//========== ОЗГ - охотник на пассажира ============
						case 5:
							dialog.text = "Sie kommen gerade rechtzeitig, mein Herr. Ich habe eine dringende Mission, die Ihnen gerade recht kommt. Sie beinhaltet das Aufspüren und Festnehmen einer bestimmten Person...";
							link.l1 = "Eine Menschenjagd? Könnt Ihr mir genauer erklären, was von mir erwartet wird?";
							link.l1.go = "TakePassenger";
						break;
						//========== Патруль - таможенник ============
						case 6:
							dialog.text = "Du kommst gerade rechtzeitig, Kapitän. Ich muss mich mit einem dringenden Problem befassen, das mit dem Schmuggel von Waren in unsere Kolonie verbunden ist. Ich nehme an, dein Schiff ist seetüchtig und bereit für den Kampf?";
							link.l1 = "Mein Schiff ist immer seetüchtig und bereit für den Kampf. Bitte, erzählen Sie mir mehr über die bevorstehende Mission, Eure Gnaden.";
							link.l1.go = "CustomPatrol";
						break;
							//========== Найти дезертира ============
						case 7:
							dialog.text = "Ich habe eine Mission für dich, die den Besuch mehrerer Siedlungen in der Karibik beinhaltet. Bist du bereit für eine lange Reise?";
							link.l1 = "Ja, meine Männer und ich sind bereit, sofort abzureisen? Was genau muss ich tun?";
							link.l1.go = "FindFugitive";
						break;
					}
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Heute kann ich Ihnen keine Jobs anbieten.","Heute gibt es keine Jobs mehr für dich.","Keine Jobs mehr für heute, tut mir leid. Komm morgen wieder und wir werden sehen...");
				link.l1 = RandPhraseSimple("Schade...","Ach, was für ein Jammer, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
			}
		//---------------------------- генератор квестов мэра -------------------------------
		break;

		case "sell_prisoner":
            dialog.text = "Wen möchten Sie auslösen?";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "Niemand.";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "So, this is captain " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
			if(HasShipTrait(pchar, "trait14")) qty = makeint(qty * 1.35);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " I am ready to pay the ransom for my compatriot in the amount of  " + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " I can give " + FindRussianMoneyString(qty) + "  for this gallowsbird. And then we'll execute the scoundrel at once.";

                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " " + FindRussianMoneyString(qty) + "for that man, not a peso more.";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "Abgemacht. Er gehört ganz dir, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "Nein. Das wird nicht tun.";
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = "Das ist gut.";
			link.l1 = "Alles Gute.";
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterComplexReputation(pchar,"nobility", -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // всё, все свободны
			
			// --> Левассер
			if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
			{
                dialog.Text = "Arrgh! Was ist dieser Skandal, de Maure? Seit wann greifen die Franzosen ihre eigenen Landsleute an?!";
                Link.l1 = "Im Auftrag des Generalgouverneurs Francois Longvillier de Poincy werden Sie, Monsieur Levasseur, vom Amt des Gouverneurs von Tortuga entfernt und zum Tode verurteilt! Und ich bin derjenige, der dieses Urteil vollstrecken wird!";
                Link.l1.go = "levasser";
				break;
			}
			// <-- Левассер
            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "Du hast schon alles genommen. Was brauchst du noch?";
                Link.l1 = "Ja, richtig, falsche Stadt.";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернём диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = "Noch nie dagewesene Frechheit! Die Verstärkungen aus der Festung werden bald eintreffen und du wirst dafür bezahlen!";
                Link.l2 = "Ich werde nicht hier bleiben, bis sie ankommen. Zahle mir einfach, und wir werden diese Stadt verlassen.";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = "Du hast dieses Mal gewonnen, aber wisse, dass ein Geschwader unserer Piratenjäger dich jagen und jeden Peso aus deinem dreckigen Piratenfleisch reißen wird!";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "Silence! This town belongs to me from now on; as for your piratehunters - I'll send them straight to Davy Jones' Locker. Hey lads, grab this pig and put it behind bars.";
	    				}
	    				else
	    				{
	    					Link.l1 = "Diese Stadt gehört jetzt mir. Jungs, begleitet den Ex-Gouverneur zu seinen neuen 'Quartieren', heh heh.";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "Verstärkung aus dem Fort? Zahle mir nur ein hübsches Lösegeld, und wir werden deine Stadt verlassen.";
				}
				else
				{
	            	Link.l2 = "Eine Staffel von Piratenjägern? Hmm ... Zahlen Sie mir einfach und wir werden Ihre Stadt verlassen.";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "Noch nie dagewesene Unverschämtheit! Wie wagst du es, die Kolonie anzugreifen, die gehört zu "+NationNameGenitive(sti(NPChar.nation))+"?! Du wirst teuer bezahlen für das Blut, das du vergossen hast und für den Schaden, den du unserem Staat zugefügt hast.";
	                Link.l1 = "Ab diesem Punkt gehört diese Kolonie mir. Wer sich entscheidet, meine Autorität anzufechten, geht direkt zur Hölle.";
	                Link.l1.go = "City_patent";
	                Link.l2 = "Tritt zurück. Ich handle im Namen von "+NationNameGenitive(sti(PChar.nation))+". Von diesem Punkt an gehört diese Kolonie zu "+NationKingsCrown(PChar)+"!";
	                Link.l2.go = "City_nation";
	                Link.l3 = "Schönes Städtchen, das ihr hier habt. Es wäre wirklich eine Tragödie, wenn es bis auf die Grundmauern abgebrannt und sein Gouverneur am Stadtplatz aufgehängt würde. Wir sollten die Höhe des Lösegeldes besprechen, das ihr bereit seid zu zahlen, um diese Tragödie zu verhindern. ";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
		
		// --> Левассер
		case "levasser":
            dialog.Text = "Poincy?! Verdammt sei dieser papistische Bastard! Ich werde mich um ihn kümmern... und du bist erledigt, Schurke! Du wirst hier nicht lebend rauskommen - Ich werde dich persönlich beenden!";
			Link.l1 = "Verschone mich mit deiner Predigt, Ketzer. Wenn ich deine Hugenottenseele in die Hölle schicke, grüße Luzifer und Jean Calvin von mir. En garde!";
			Link.l1.go = "levasser_1";
        break;
		
		case "levasser_1":
			chrDisableReloadToLocation = true;//закрыть локацию
            DialogExit();
			LAi_SetImmortal(npchar, false);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
			AddDialogExitQuest("MainHeroFightModeOn");	
        break;
		// <-- Левассер
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 400);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info("All ships have been repaired.");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -20); // пираты мы, но у нас патент
            dialog.Text = "Du hast diesmal gewonnen, aber sei dir bewusst, dass unsere Staffel bald eintreffen wird und von dir nichts übrig lassen wird!";
			Link.l1 = "Shut your mouth. This town belongs to me from now on; as for your squadron - I'll send it straight to Hell. Boys, escort the ex-governor to his new 'quarters', heh heh.";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "Was brauchen Sie noch von mir?";
            Link.l1 = "Nur überprüfen, ob ich etwas übersehen habe...";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернём диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = "Ich habe keine andere Wahl, als Ihren Bedingungen zuzustimmen. Nehmen Sie Ihr verdammtes Geld und verlassen Sie sofort unsere Kolonie.";
            Link.l1 = "Es war mir ein Vergnügen, Geschäfte mit Ihnen zu machen.";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 300);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 300);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
        break;

        case "Summ_patent":
            dialog.Text = "Gut, nenne deine Bedingungen...";
            Link.l1 = "Ja, wehe den Besiegten! Fang an, dein Geld zu zählen.";
            Link.l1.go = "Summ";
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = "Gut, wir ergeben uns deiner Gnade.";
			Link.l1 = "Ich würde Ihnen raten, die Stadt so bald wie möglich zu verlassen - die bevorstehenden Veränderungen könnten sehr schlecht für Ihre Gesundheit sein. Lebewohl.";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 600);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 400);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не даёт, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернём диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = "Was brauchst du noch von mir, Schurke?";
            Link.l3 = "Wie gefällt Euer Exzellenz sein neues Zimmer? Geräumig genug? Nun, jetzt muss ich gehen!";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "Siedeln? Und wie stellen Sie sich das vor?";
            link.l1 = "Ich denke, eine Summe von "+iTotalTemp*6000+" Pesos können mich noch retten, oder nicht?";
			link.l1.go = "arestFree_2";
			link.l2 = "Nein. Und es ist Zeit für mich zu gehen. Beste Grüße.";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= hrand(7) && iTotalTemp < 21)
            {
    			dialog.text = "Ich denke, wir könnten unseren Vorfall auf diese Weise regeln. Du hast es noch nicht so weit gebracht, die Situation unumkehrbar zu machen.";
    		    link.l1 = "Ausgezeichnet. Ich bin sehr froh. Bitte, nimm meine Spende an.";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -iTotalTemp*6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
    		    AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
    			dialog.text = "Bietest du mir ein Bestechungsgeld an? Oh nein! Deine bösen Taten können nur auf eine Weise gesühnt werden... Wachen! Nehmt "+GetSexPhrase("ihn","ihr")+" in Ketten!";
    		    link.l1 = "Halt an!";
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = "Natürlich, es ist Zeit. Wir werden dich verabschieden. Wachen! Ergreift "+GetSexPhrase("ihn","sie")+"!";
		    link.l1 = "Keine Chance!";
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "Du hattest genug Zeit zum Nachdenken! Wachen!";
			link.l1 = "Du wirst mich nicht so leicht bekommen!";
		    link.l1.go = "fight";
		break;    
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			dialog.text = "Natürlich. Um diese Mission zu erfüllen, gebe ich dir "+FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms))+", und deine Belohnung im Falle eines Erfolges wird sein "+FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money))+".";
			link.l1 = "Jawohl, ich nehme diese Aufgabe an.";
		    link.l1.go = "DestroyGang_agree";
			link.l2 = "Hmm... Nein, ich denke, ich werde passen.";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = "Halt ein, ich habe gerade den Bericht von gestern vergessen. Die Sache ist, dass diese Bande unsere Insel bereits verlassen hat. Also muss ich die Mission abbrechen.";
				link.l1 = "Ich verstehe. Schade.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "Nun, großartig! Ich werde in meiner Residenz auf dich und deine Berichte warten.";
				link.l1 = "Ich werde Sie nicht lange warten lassen, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контркурьер
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePostcureer":
			//установка параметров
			pchar.GenQuest.questName = "TakePostcureer"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index)); //вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Heute kann ich Ihnen keine Jobs anbieten.","Heute gibt es keine Jobs mehr für dich.","Keine Arbeit mehr für heute, tut mir leid. Komm morgen wieder und wir werden sehen...");
				link.l1 = RandPhraseSimple("Schade...","Ach, was für ein Jammer, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePostcureer.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakePostcureer.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
			pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island)+5;
			pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms)-1;
			pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
			pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
			pchar.GenQuest.TakePostcureer.Money = ((hrand(5)+hrand(6)+4)*2000)+(sti(pchar.rank)*500);
			dialog.text = "Natürlich. Sie müssen ein Kurierschiff finden "+NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation))+" im Namen von '"+pchar.GenQuest.TakePostcureer.ShipName+"', enter sie und bringen Sie mir die Papiere, die Sie in der Kapitänskabine finden sollten. Dieses Schiff wird in der Nähe vorbeifahren "+XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen")+" ungefähr in "+FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms)+".";
			link.l1 = "In Ordnung, ich akzeptiere diese Mission. Und welche Art von Papieren soll ich suchen?";
		    link.l1.go = "TakePostcureer_agree";
			link.l2 = "Hmm... Nein, ich glaube, ich passe.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Post. Es gibt sehr wichtige Papiere für mich. Aber es besteht keine Notwendigkeit für dich, unter den Dokumenten zu suchen, bringe einfach das ganze Paket zu mir. Ich werde dich bezahlen "+FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money))+"\nAlso, ich werde auf dich und das Ergebnis deiner Arbeit in meiner Residenz warten.";
			link.l1 = "Ich werde Sie nicht lange warten lassen, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakePostcureer.win_condition.l1 = "location";
			pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
			pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
			pchar.quest.TakePostcureer.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakePostcureer.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контрфрахт - уничтожить корабль с арсеналом
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakeArsenalship":
			//установка параметров
			pchar.GenQuest.questName = "TakeArsenalship"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Heute kann ich Ihnen keine Jobs anbieten.","Heute gibt es keine Jobs mehr für dich.","Keine Jobs mehr für heute, tut mir leid. Komm morgen wieder, dann sehen wir weiter...");
				link.l1 = RandPhraseSimple("Schade...","Ach, was für ein Jammer, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakeArsenalship.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakeArsenalship.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
			pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island)+5;
			pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms)-1;
			pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectArsenalShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
			pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
			pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка
			pchar.GenQuest.TakeArsenalship.Money = ((hrand(5)+hrand(6)+4)*1800)+(sti(pchar.rank)*500);
			dialog.text = "Natürlich. Sie müssen einen militärischen Transport finden von "+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+", with gunpowder and ammunition on board; the name of the vessel is '"+pchar.GenQuest.TakeArsenalship.ShipName+"', find and destroy it. We'll weaken our enemy by doing that\nThe transport will sail with an escort to the colony "+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+", and will be approximately in "+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+", so you should hurry.";
			link.l1 = "Gut, ich akzeptiere. Soll ich das Arsenalschiff versenken oder sollte ich versuchen, es zu erobern?";
		    link.l1.go = "TakeArsenalship_agree";
			link.l2 = "Hmm... Nein, ich glaube, ich passe.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Ich kümmere mich nicht darum, das liegt bei dir. Das Wichtigste ist, dass diese Ladung ihr Ziel nicht erreicht. Wenn du erfolgreich bist, werde ich dich bezahlen "+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+"... Ich halte Sie nicht länger auf, Kapitän.";
			link.l1 = "Ich werde Sie nicht lange warten lassen, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			pchar.quest.TakeArsenalship.win_condition.l1 = "location";
			pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
			pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
			pchar.quest.TakeArsenalship.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakeArsenalship.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - уничтожить корабль пиратов
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePirateship":
			//установка параметров
			pchar.GenQuest.questName = "TakePirateship"; //тип квеста
			pchar.GenQuest.TakePirateship.City = FindQuestCity(npchar, "all", -1, true, true); // belamour legendary edition 
			pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
			pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island)+5;
			pchar.GenQuest.TakePirateship.ShipType = SelectPirateShipType();
			pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
			pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
			pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
			pchar.GenQuest.TakePirateship.Money = ((hrand(5)+hrand(6)+4)*2400)+(sti(pchar.rank)*500);
			dialog.text = "Natürlich. Ich bin wirklich verärgert über die Aktivitäkeiten eines Piratenkapitäns, dessen Name ist "+pchar.GenQuest.TakePirateship.Name+". Dieser Schurke hat sich angewöhnt, unsere Kaufleute zu überfallen, was den Handel zwischen den Kolonien enorm schädigt. Jetzt ist der perfekte Zeitpunkt, um diesen Bastard loszuwerden, denn ich weiß zufällig, wo er sich gerade versteckt. Bist du bereit, diesen Hurensohn zu Gottes Gericht zu schicken?";
			link.l1 = "Ich wäre geehrt! Wo kann ich diesen Piraten finden?";
		    link.l1.go = "TakePirateship_agree";
			link.l2 = "Hmm... Nein, ich glaube, ich passe.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "In der nächsten "+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+" sein Schiff mit dem Namen '"+pchar.GenQuest.TakePirateship.ShipName+"' wird in der Nähe der Küsten kreuzen "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Findet ihn und tötet ihn. Schickt ihn mit dem Schiff, um die Fische zu füttern, entert das Schiff - es ist mir egal. Mir ist nur wichtig, dass dieser verdammte Pirat aufhört, unser Meer mit seiner Anwesenheit zu entweihen\nFür diese Aufgabe bin ich bereit, dich zu bezahlen "+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+". Vergeuden Sie keine Zeit, Kapitän: dieser Schurke wird nicht auf Sie warten bei "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Geh, und möge Gott dir helfen!";
			link.l1 = "Den Anker schon heben, "+GetAddress_FormToNPC(NPChar)+"! Du wirst nicht lange warten.";
			link.l1.go = "exit";
			pchar.quest.TakePirateship.win_condition.l1 = "location";
			pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
			pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "9");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - захватить пассажира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePassenger":
			//установка параметров
			pchar.GenQuest.questName = "TakePassenger"; //тип квеста
			pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));//вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Heute kann ich Ihnen keine Jobs anbieten.","Heute gibt es keine Jobs mehr für dich.","Keine Jobs mehr für heute, tut mir leid. Komm morgen wieder und wir werden sehen...");
				link.l1 = RandPhraseSimple("Schade...","Ach, was für ein Pech, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePassenger.City = FindQuestCity(npchar, "enemy", sti(pchar.GenQuest.TakePassenger.Nation), false, false); // belamour legendary edition
			pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
			pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
			pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA))+1;
			pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1)+sti(pchar.GenQuest.TakePassenger.Terms2);
			pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
			pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
			pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
			pchar.GenQuest.TakePassenger.Money = ((hrand(5)+hrand(6)+4)*2200)+(sti(pchar.rank)*500);
			string sText = SelectPassText();
			dialog.text = "Natürlich. Ich spreche von einem Schurken namens "+pchar.GenQuest.TakePassenger.Name+". "+sText+" Ich habe ihn schon seit geraumer Zeit gesucht, und jetzt habe ich endlich zuverlässige Informationen, wo er gefunden werden kann. Ich brauche dich, um diesen Mann zu mir zu bringen, auf jeden Fall lebend. Ich will ihn öffentlich auf unserem Marktplatz hängen. Bist du bereit, diese Mission zu übernehmen?";
			link.l1 = "Ich bin bereit, "+GetAddress_FormToNPC(NPChar)+". Wo kann ich diesen Schurken finden?";
		    link.l1.go = "TakePassenger_agree";
			link.l2 = "Hmm... Nein, ich glaube, ich passe.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Nur rein "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1)+", er, als Passagier auf einem Schiff namens '"+pchar.GenQuest.TakePassenger.ShipName+"', wird aussegeln aus "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen")+" und gehe zu "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc")+". Du hast "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms)+" um dieses Schiff auf dem angegebenen Pfadsegment zu finden, zu entern und diesen Bastard zu ergreifen. Wenn du dieser Anweisung folgst, werde ich dich bezahlen "+FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money))+". Viel Glück für dich, Kapitän!";
			link.l1 = "Ich werde keine Zeit mehr verschwenden, "+GetAddress_FormToNPC(NPChar)+"! Ich werde sofort die Segel setzen.";
			link.l1.go = "exit";
			SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc"));
			AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
			AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Таможенный патруль
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "CustomPatrol":
			//установка параметров
			pchar.GenQuest.questName = "CustomPatrol"; //тип квеста
			pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation);//нация
			pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
			pchar.GenQuest.CustomPatrol.LoginDay = rand(4)+1;
			pchar.GenQuest.CustomPatrol.Loginlocator = rand(3)+4;
			pchar.GenQuest.CustomPatrol.ShipType = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
			pchar.GenQuest.CustomPatrol.Money = ((hrand(5)+hrand(6)+4)*1400)+(sti(pchar.rank)*300);
			dialog.text = "Ich habe zuverlässige Informationen, dass irgendein Kapitän eine Transaktion mit Schmugglern über den Verkauf einiger Sklaven abgewickelt hat. Wie Sie wissen müssen, sind solche Transaktionen von Privatpersonen in unseren Kolonien als Schmuggelware gekennzeichnet\nEin Problem besteht darin, dass ich weder die genaue Zeit, noch das Datum, noch den Ort kenne, an dem die Schmuggler sich treffen werden. Es ist nur bekannt, dass eine kriminelle Transaktion in den nächsten fünf Tagen auf unserer Insel durchgeführt wird. Zu allem Überfluss sind alle meine Patrouillenschiffe entweder in Reparatur oder für andere Aufgaben eingeteilt und können diese Schurken nicht finden\nIch schlage vor, dass Sie sich dieser Aufgabe annehmen - die Schmuggler aufzuspüren und mit den radikalsten Methoden mit ihnen umzugehen, sie zu einem Beispiel zu machen. Sind Sie bereit, diese Mission zu erfüllen?";
			link.l1 = "Ich bin bereit, "+GetAddress_FormToNPC(NPChar)+". Sag mir, hast du noch zusätzliche Informationen? Wie der Name des Kapitäns, der Name oder die Art seines Schiffes?";
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = "Hmm... Nein, ich glaube, ich verzichte.";
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Meine Quelle hat mir gerade gesagt, dass ein Geschäft vorbereitet wird und abgeschlossen sein wird. Das ist alles. Also schau dir einfach alle verdächtigen Schiffe in unseren Gewässern genauer an. Wenn du erfolgreich bist, werde ich dir eine Summe von "+FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money))+"\nWeiterhin, unter den gegebenen Umständen, autorisiere ich Sie, die ganze Ladung Schmuggelware, die Sie finden können, aufzuheben. Unoffiziell natürlich, vorausgesetzt, Sie verkaufen sie nicht in unserer Stadt.";
			link.l1 = "Recht großzügig. Gut, ich werde mit der Patrouille der Gewässer Ihrer Kolonie beginnen, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 6, false);
			pchar.quest.CustomPatrol.win_condition.l1 = "location";
			pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
			pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
			pchar.quest.CustomPatrol.win_condition.l2.date.hour  = sti(GetTime()+rand(8));
			pchar.quest.CustomPatrol.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Найти дезертира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "FindFugitive":
			//установка параметров
			pchar.GenQuest.questName = "FindFugitive"; //тип квеста
			pchar.GenQuest.FindFugitive.Startcity = npchar.city;
			pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
			pchar.GenQuest.FindFugitive.Chance = rand(2);
			pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
			pchar.GenQuest.FindFugitive.Money = ((hrand(5)+hrand(6)+4)*2600)+(sti(pchar.rank)*600);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			dialog.text = "Ich werde Ihnen alles im Detail erzählen. Eine sehr hässliche Geschichte ist passiert - "+sText+". Nach Befragung seiner Kollegen und Freunde glauben wir nicht grundlos, dass der Deserteur Zuflucht bei den Piraten in einer ihrer Siedlungen gefunden hat\nIch schlage vor, du besuchst das Piratennest, findest den Flüchtigen, nimmst ihn fest und bringst ihn hierher. Desertion ist ein schweres Vergehen und darf nicht ungestraft bleiben. Bist du bereit, diese Mission zu übernehmen?";
			link.l1 = "Ich bin bereit, "+GetAddress_FormToNPC(NPChar)+". Können Sie mir den Namen des Deserteurs nennen?";
		    link.l1.go = "FindFugitive_agree";
			link.l2 = "Hmm... Nein, ich glaube, ich passe.";
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Ja, natürlich. Sein Name ist "+pchar.GenQuest.FindFugitive.Name+". Ich bezweifle stark, dass er seine Uniform trägt, also schau dir all das Gesindel genauer an. Ich gebe dir einen Monat für die Suche, denn ich fürchte, danach macht es keinen Sinn mehr, nach ihm zu suchen. Wenn du Erfolg hast, werde ich dir eine Summe zahlen "+FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money))+".";
			link.l1 = "Ich werde keine Zeit mehr verschwenden, "+GetAddress_FormToNPC(NPChar)+"! Ich werde sofort die Segel setzen.";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
			//создаем дезертира
			sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_"+(21+rand(9)), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			sld.name = pchar.GenQuest.FindFugitive.Name;
			sld.lastname = "";
			sld.dialog.FileName = "MayorQuests_dialog.c";
			sld.greeting = "marginal";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			dialog.text = "Ich verstehe. Vielleicht eine Belohnung von "+FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money))+" wird ein guter Anreiz für dich sein.";
			link.l1 = "Ja, es ist anständiges Geld... Ich werde diese Mission annehmen.";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "Hmm... Nein, ich glaube, ich werde ablehnen. Es ist zu gefährlich.";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = "Obwohl, ich kann nicht sagen, dass ich dir vollständig vertrauen kann... Ich glaube, ich werde dir diese Mission nicht geben.";
				link.l1 = "Ach ja... Es ist schade, aber es gibt nichts, was ich tun kann.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = "Großartig! Jetzt zur Sache. In "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" du musst einen Einheimischen finden "+GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)],"Gen")+", sein Name ist "+GetFullName(&characters[GetCharacterIndex(sTemp)])+". Du wirst ihm meinen Namen nennen und er wird dir ein Paket mit Dokumenten geben. Für die Übergabe dieses Pakets in meine Hände gebe ich dir "+FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms))+". Und denken Sie daran, dass alles heimlich erledigt werden muss. Wenn Ihre Tarnung auffliegt, wird der Agent nicht riskieren, Kontakt aufzunehmen. Ist das klar?";
				link.l1 = "Ja, ich habe es, "+GetAddress_FormToNPC(NPChar)+". Ich werde sofort anfangen.";
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
			dialog.text = RandPhraseSimple("Nicht schlecht. Aber Sie haben die Frist nicht eingehalten, und daher muss ich Ihre Belohnung etwas kürzen. Jetzt wird Ihre Gebühr sein "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Hier, bitte.","Das ist gut. Aber du hast die Frist versäumt und ich habe auf diese Briefe gewartet. Du hast meine Pläne durcheinander gebracht und daher bin ich gezwungen, deine Belohnung etwas zu kürzen. Dennoch bin ich froh, dir deine verdiente Belohnung zu überreichen - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Hier, bitte.");
			link.l1 = "Ich würde nicht sagen, dass es mir gefällt, aber letztendlich wurden tatsächlich Fristen verletzt. Also habe ich keine Beschwerden, "+GetAddress_FormToNPC(NPChar)+".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple("You know, governor " + GetFullName(npchar) + " are not very pleased with the quickness of a captain " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is not very pleased with captain " + GetMainCharacterNameDat() + ", "+ GetSexPhrase("who","who") +" complied with his orders, but did not in due time..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = "Du enttäuschst mich!";
			link.l1 = "Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+", aber ich kann diesen Job nicht annehmen.";
		    link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Nun, sehr schlecht - was soll ich sonst sagen. Ich habe auf dich gezählt - und es stellt sich heraus, dass ich nur meine Zeit verschwendet habe. Ich bin enttäuscht.","Nun, ich muss sagen, dass ich völlig enttäuscht von dir bin... Es gibt viele Leute bei mir zu Hause, die immer bereit sind, solche Besorgungen für mich zu erledigen - und ich habe meine Zeit mit dir verschwendet. Na ja...");
			link.l1 = "Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+", Ich habe alles getan, was ich konnte.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Just imagine - he failed to fulfill his assignment in time!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " put his shoulder to the wheel, but fail to fulfill his assignment in time. That's too bad...", 
				"I heard that governor " + GetFullName(npchar) + " is very displeased with you, captain " + GetFullName(pchar) + ", since you failed to meet the deadline while trying to fulfill his assignment."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Ich bin einfach schockiert! Du hast es geschafft, dein Ziel zu lokalisieren, aber hast dich nicht um Mittel gekümmert, um deine Überlegenheit zu sichern - das ist extreme Rücksichtslosigkeit. Ich bin enttäuscht!","Nun, ich muss sagen, dass ich von dir enttäuscht bin... Dein Ziel zu finden reicht nicht aus - du musst die Mittel haben, um es zu zerstören. Es gibt viele Halsabschneider in meiner Residenz, die immer bereit sind, solche Besorgungen für mich zu erledigen. Was habe ich mir nur dabei gedacht, als ich mich an dich gewandt habe?");
			link.l1 = "Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+", aber ich bin einfach nicht bereit, mein eigenes Leben leichtsinnig zu riskieren.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Imagine, "+ GetSexPhrase("he turned out to be a downright coward","she turned out to be a downright coward") +"!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " took the job, but failed to carry it out because of their own indecision. Hee-hee, what wilt captains!", 
				"I heard that Governor " + GetFullName(npchar) + " very displeased with you, Captain " + GetFullName(pchar) + ". They say you're nothing but a coward"+ GetSexPhrase("","") +"..."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Ausgezeichnete Neuigkeiten! Nun, es ist Zeit, alles zusammenzufassen. Ihre Gebühr wird sein "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Hier, bitte.","Ausgezeichnet! So ist es am besten für alle... Nun, ich freue mich, Ihnen Ihre wohlverdiente Belohnung zu überreichen - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Hier, bitte.");
			link.l1 = "Danke, "+GetAddress_FormToNPC(NPChar)+", "+RandPhraseSimple("Freude, Geschäfte mit Ihnen zu machen!","Ich bin angenehm überrascht von der Klarheit der Siedlungen.");
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + "  was praising for diligence"+ GetSexPhrase("a captain","a young lady") +" " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is praising captain " + GetMainCharacterNameGen() + ", "+ GetSexPhrase("he","she") +" is always a flawless performer when it comes to governor's assignments. An irreplaceable person for the governor, I say...", 
				"I heard that governor " + GetFullName(npchar) + " is very much pleased with you, captain " + GetFullName(pchar) + ". He defines you as a very careful and thorough officer. That's very nice to hear, captain..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Sehr gut. Du kannst mich wieder besuchen - vielleicht habe ich einen anderen Job für dich.","Nun, großartig! Ich nehme an, ich werde dir solche Aufgaben wieder anbieten.");
			link.l1 = RandPhraseSimple("Großartig.","Gut.");
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 180);
			OfficersReaction("good"); // dlc
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "In diesen schweren Zeiten wäre jede Hilfe sehr willkommen. Wir nehmen Ihre Hilfe an - helfen Sie uns, unsere Kolonie zu verteidigen, und Sie werden belohnt werden.";
			link.l1 = "Dann verschwenden wir keine Zeit.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> Бремя гасконца
		case "Sharlie":
			dialog.text = "Sie suchen nach Michel de Monper? Interessant... Und wofür brauchen Sie ihn?";
			link.l1 = "Ich bin sein Bruder. Mein Vater hat mir gesagt, dass Michel in Schwierigkeiten steckt und Hilfe braucht, also ich...";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
			DelLandQuestMark(sld);
			dialog.text = "Sind Sie das? Ich kann mich nicht erinnern, dass Monsieur de Monper Brüder hatte... Sie wissen, Monsieur, Sie sehen sehr verdächtig aus... also verhafte ich Sie zur weiteren Untersuchung. Leutnant! Verhaften Sie diesen Mann!";
			link.l1 = "Aber Euer Gnaden!";
			link.l1.go = "exit";
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}	
			AddDialogExitQuestFunction("Sharlie_enterSoldiers");
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Sharlie_2":
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload3_back");
			dialog.text = "Und dennoch möchte ich Wiedergutmachung leisten. Hier - bitte nehmen Sie dieses Schwert, diese Pistole und diese leichte Rüstung - es ist mein Geschenk an Sie. Ich glaube, Sie werden diese Dinge ziemlich nützlich finden.";
			link.l1 = "Danke, Monsieur. Angesichts der Tatsache, dass Ihre Wachen alles genommen haben, was ich besitze, wird dies sehr nützlich sein.";
			// belamour legendary edition -->
			link.l1.go = "Sharlie_5";		
			link.l2 = "Danke Ihnen, Monsieur. Gibt es eine andere Möglichkeit, wie Sie mir helfen können? Von Gentleman zu Gentleman? Sie können selbst sehen, in welch schrecklicher Lage ich mich befinde!";
			link.l2.go = "Sharlie_3";	
		break;
		
		case "Sharlie_3":
			dialog.text = "Nun, Charles... (kramt durch Schreibtisch) Hier, behalte dieses heilige Amulett für Glück. Ich kann nicht mehr helfen, sorry. Hier in den Kolonien wirst du dich nur auf dich selbst verlassen müssen.";
			link.l1 = "Nun, zumindest etwas. Danke für das Geschenk, Herr.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Commerce", 10);
			Log_Info("You'have received equipment");
			Log_Info("You have received the 'Holy Water' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Sharlie_5":
			// <-- legendary edition
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 10);
			Log_Info("You'have received equipment");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		//<-- Бремя гасконца
		
		//Sinistra --> Травля крысы		
		case "TK_TravlyaKrys":
			dialog.text = "Ein ziemlicher Schicksalsschlag, Charles... Es ist nicht oft, dass wir jemanden so schnell in unserer Welt aufsteigen sehen. Ich habe das Gefühl, dass du und ich uns gut verstehen werden.";
			link.l1 = "Ich wäre geehrt. Vielleicht haben Sie eine Aufgabe für mich?";
			link.l1.go = "TK_TravlyaKrys_2";
			DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
			PChar.quest.TK_Timer.over = "yes";
		break;
		
		case "TK_TravlyaKrys_2":
			dialog.text = "Absolut! Besonders nach Ihrer erfolgreichen Auseinandersetzung mit einem von Barbazons Piraten in der Nähe von Le Francois...";
			link.l1 = "Ich kann nicht sagen, dass ich gute Erinnerungen an diese Begegnung habe. Wer genau ist Barbazon?";
			link.l1.go = "TK_TravlyaKrys_3";
		break;
		
		case "TK_TravlyaKrys_3":
			dialog.text = "Jacques Barbazon, auch bekannt als Jacques der Gutmensch, führt das Banditennest in Le Françcois. Er ist einer der sogenannten Piratenbarone, der mit Piraterie und Schmuggel in den Kleinen Antillen Ärger bereitet. Er ist ein berüchtigter Verbrecher, und markiere meine Worte, er wird eines Tages am Galgen in St. Pierre sein Ende finden!";
			link.l1 = "Entschuldigung, aber sind Sie nicht die wahre Autorität in Martinique? Können Sie nicht einfach dieses Nest beseitigen? Ich war dort und glauben Sie mir, es ist nicht viel zu sehen.";
			link.l1.go = "TK_TravlyaKrys_4";
		break;
		
		case "TK_TravlyaKrys_4":
			dialog.text = "Ich würde davon abraten, mit deinem Wissen über die weniger ansehnlichen Orte meiner Insel zu prahlen, Charles. Das steht einem Edelmann nicht gut zu Gesicht. Was deine Frage betrifft\nNicht alles in unserer Welt kann mit roher Gewalt gelöst werden. Es gibt Politik und Geschäftsinteressen, die eine Rolle spielen. Aber lassen wir die unnötigen Details beiseite: Ich habe eine spezielle Aufgabe, die etwas rohe Gewalt erfordert.";
			link.l1 = "Bitte mach weiter.";
			link.l1.go = "TK_TravlyaKrys_5";
		break;
		
		case "TK_TravlyaKrys_5":
			dialog.text = "Barbazon lockt kleine Crews an, die nach leichtem Gold hungern. Manchmal wirft er einem von ihnen nur zum Spaß einen Knochen hin, um zu beobachten, wie sie alle darum kämpfen. Gelegentlich setzt er den Überlebenden zu Arbeit ein, aber öfter wirft er sie raus, und glaub mir, es gibt nichts Gefährlicheres als einen verzweifelten Piraten, der herumstreunt.";
			link.l1 = "Ich glaube, ich verstehe, aber ich bin mir nicht sicher, ob ich bereit dafür bin. Ich habe erst kürzlich das Kommando über mein Schiff übernommen und lerne noch die Seile, sozusagen...";
			link.l1.go = "TK_TravlyaKrys_6";
		break;
		
		case "TK_TravlyaKrys_6":
			dialog.text = "Aber was! Du hast schon einmal den Sieg gekostet - mehr als die meisten der Nichtstuer unter meinen Offizieren! Die Stadt wird dich mit fünftausend Pesos für das Versenken einer weiteren Ratte von Barbazon belohnen, steuerfrei. Achttausend, wenn du den Piraten lebend bringst - für eine ordnungsgemäße Hinrichtung, natürlich.";
			link.l1 = "Ich könnte das Geld sicherlich gebrauchen. Wo kann ich diesen Piraten finden?";
			link.l1.go = "TK_TravlyaKrys_7";
			link.l2 = "Es tut mir leid, aber ich glaube, ich bin noch nicht bereit für diese Art von Aufgabe.";
			link.l2.go = "TK_TravlyaKrys_Otkaz";
		break;
		
		case "TK_TravlyaKrys_Otkaz":
			dialog.text = "Das ist schade, Charles. In dem Fall werde ich dich nicht länger aufhalten.";
			link.l1 = "Auf Wiedersehen, Eure Exzellenz.";
			link.l1.go = "exit";
		break;
		
		case "TK_TravlyaKrys_7":
			dialog.text = "Ich bin froh, dass du an Bord bist, Charles. Unsere Geheimdienstberichte deuten darauf hin, dass die Hater, eine Schaluppe, sich derzeit auf die Abfahrt von Le Francois vorbereitet. Wir können uns keine Verzögerung leisten, also setz die Segel und greif an. Mach dir keine Sorgen, mein Freund, du wirst erfolgreich sein.";
			link.l1 = "Mit der Gnade Gottes, Eure Exzellenz.";
			link.l1.go = "TK_TravlyaKrys_8";			
		break;
		
		case "TK_TravlyaKrys_8":
			DialogExit();
			SetQuestHeader("TravlyaKrys");
			AddQuestRecord("TravlyaKrys", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			FantomMakeSmallSailor(sld, SHIP_LUGGER, "Hater", CANNON_TYPE_CANNON_LBS3, 20, 40, 20, 25, 35);
			SetCharacterGoods(sld, GOOD_GOLD, 1);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("HeiterAttack");
			Group_SetType("HeiterAttack", "pirate");
			Group_AddCharacter("HeiterAttack", "TK_Heiter");

			Group_SetGroupCommander("HeiterAttack", "TK_Heiter");
			Group_SetTaskAttack("HeiterAttack", PLAYER_GROUP);
			Group_SetAddress("HeiterAttack", "Martinique", "Quest_Ships", "Quest_Ship_6");
			Group_LockTask("HeiterAttack");
			
			PChar.quest.TK_Potopil.win_condition.l1 = "Character_sink";
			PChar.quest.TK_Potopil.win_condition.l1.character = "TK_Heiter";
			PChar.quest.TK_Potopil.win_condition = "TK_Potopil";
		break;
		//<-- Травля крысы
		
		//Jason --> Португалец
		case "Portugal":
			dialog.text = "Sicher kannst du das, Kapitän! Deshalb habe ich dich belästigt.";
			link.l1 = "Dann bin ich ganz Ohr.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Die örtlichen Fischer haben gestern Nacht ein seltsames Schiff in der Nähe der Insel gesehen. Sie sagen, es war ein riesiges Kriegsschiff, wie ein Linienschiff, ohne irgendwelche Flaggen oder Signallichter. Ich glaube nicht, dass dieses Schiff tatsächlich größer als eine Fregatte sein könnte, aber selbst das wäre schon zu viel!";
			link.l1 = "Die Angst verwandelt Maulwurfshügel in Berge, das ist sicher... aber was ist der Sinn?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Ich wende mich nur an dich, Kapitän. Meine Handelspartner sind von diesen Gerüchten erschreckt - sie glauben, es seien Piraten oder spanische Freibeuter, und das ist schlecht für den Handel. Am schlimmsten von allem - derzeit gibt es keine Kriegsschiffe in der Kolonie, nur ein paar Sloops zum Schutz und eine alte Schoner, geeignet für die Jagd auf Schmuggler\nIch kann das nicht unbeaufsichtigt lassen... Wie auch immer, jetzt, wo das Gerücht über das mysteriöse Schiff von der halben Stadt bekannt ist! Bitte, schließe dich mit deinem Schiff an, um uns zu helfen, es zu finden - Ich kenne dich als anständigen Kapitän, und selbst wenn es wirklich nur eine Fregatte ist, können deine Kanonen es überzeugen, anderswo nach Beute zu suchen!";
			link.l1 = "Herr... Eigentlich hatte ich andere Pläne...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Bitte, Kapitän! Nur für ein paar Tage, bis diese unruhigen Gerüchte sich beruhigen! Und Sie werden natürlich für Ihre Zeit bezahlt. Wären 10.000 Acht-Reales-Stücke für Sie in Ordnung?";
			link.l1 = "Hmm... aber, Euer Exzellenz, ich...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Und wir werden es verdoppeln, sollten Sie tatsächlich mit diesem Schiff in den Kampf ziehen, und verdreifachen, wenn Sie es versenken! Nun, was sagen Sie dazu?";
			link.l1 = "In Ordnung, ich hatte sowieso vor, hier ein paar Tage zu bleiben.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Ausgezeichnet, ich habe nie wirklich an Ihnen gezweifelt, Monsieur Kapitän! Denken Sie daran - nur zwei Tage in unseren Gewässern - und das Geld gehört Ihnen. Und wenn Sie gezwungen sind, in die Schlacht zu ziehen, werden Sie entsprechend dem Ausgang bezahlt.";
			link.l1 = "Ich habe verstanden, Eure Exzellenz. Wir haben einen Deal und ich kehre jetzt zu meinem Schiff zurück.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Ich werde auf Ihre Rückkehr warten, Kapitän!";
			link.l1 = "Erlauben Sie mir, mich zu verabschieden.";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			DialogExit();
			AddQuestRecord("Portugal", "10");
			NextDiag.CurrentNode = "Portugal_8";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false);//открыть выходы из города
			bDisableFastReload = true;//закрыть быстрый переход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
			pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;
		
		case "Portugal_8":
			dialog.text = "Kapitän, ich glaube, wir hatten eine Abmachung, dass Sie zwei Tage lang unsere Küstengewässer patrouillieren würden!";
			link.l1 = "Ja, natürlich. Ich erinnere mich daran.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = "Nun, du hast deinen Teil des Handels erfüllt. Hier ist deine Belohnung - 10.000 Pesos, wie wir vereinbart haben.";
			link.l1 = "Danke! Wie du sehen kannst, waren deine Bedenken unbegründet. Viel Glück dir!";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			DialogExit();
			AddMoneyToCharacter(pchar, 10000);
			NextDiag.CurrentNode = "First time";
			pchar.quest.MartiniqueGovernorOver.over = "yes"; //снять таймер
		break;
		//<-- Португалец
		
		// Warship, 16.05.11. Генер "Правосудие на продажу".
		case "JusticeOnSale_1":
			dialog.text = "Oh "+GetAddress_Form(NPChar)+", du hast mich überrascht! Sind diese Schurken wirklich so dreist geworden? Ich muss sofort den Kommandanten benachrichtigen und eine Küstenpatrouille dorthin senden!";
			link.l1 = "Ich war froh zu helfen. Kann ich jetzt gehen?";
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Natürlich, Kapitän. Hier - bitte, nehmen Sie diese bescheidene Belohnung persönlich von mir.";
			link.l1 = "Danke.";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_3":
			AddQuestRecord("JusticeOnSale", "5");
			CloseQuestHeader("JusticeOnSale");
			
			AddMoneyToCharacter(PChar, 1000 + sti(PChar.rank) * 30 * hrand(10));
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			
			DialogExit();
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Sie haben recht, Kapitän! Wir können es einfach nicht so lassen! Ich würde Sie bitten, zu gehen zu "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", finde ihr Schiff und nimm die ganze Bande fest! Wenn sie Widerstand leisten - benutze Gewalt und zögere nicht!";
			link.l1 = "Erlauben Sie mir, meinen Abschied zu nehmen.";
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Jetzt geh. Segle dorthin und sorge dafür, dass niemand der Gerechtigkeit entkommt. Ich denke, dass du zuerst an Land gehen musst, und dann kannst du dich um das Schiff kümmern.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_6";
		break;
		
		case "JusticeOnSale_6":
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShipPirate", "", "man", "man", sti(PChar.rank) + 5, PIRATE, -1, true, "quest"));
			sld.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.JusticeOnSale.ShipType), true, sld);
			sld.Ship.Name = PChar.GenQuest.JusticeOnSale.ShipName;
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetCannons(sld, "pirate");
			Fantom_SetBalls(sld, "pirate");
			Fantom_SetUpgrade(sld, "pirate");
			SetCaptanModelByEncType(sld, "pirate");
			SetRandGeraldSail(sld, PIRATE);
			
			Character_SetAbordageEnable(sld, false);
			
			Group_FindOrCreateGroup("JusticeOnSaleGroup");
			Group_AddCharacter("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetGroupCommander("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetAddress("JusticeOnSaleGroup", PChar.curislandid, "reload", Island_GetLocationReloadLocator(PChar.curislandid, PChar.GenQuest.JusticeOnSale.ShoreId));
			Group_SetTaskNone("JusticeOnSaleGroup");
			Group_LockTask("JusticeOnSaleGroup");
			
			sld.AlwaysFriend = true;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			
			SetCharacterShipLocation(sld, PChar.GenQuest.JusticeOnSale.ShoreId);

			DeleteAttribute(sld, "SinkTenPercent");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			DeleteAttribute(sld, "AboardToFinalDeck");
			
			sld.AlwaysSandbankManeuver = true;
			sld.AnalizeShips = true;
			sld.DontRansackCaptain = true;
			
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.function = "JusticeOnSale_ShoreEnterFromMayor";
			
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1 = "Character_sink";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1.character = "JusticeOnSale_ShipPirate";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.function = "JusticeOnSale_PirateShip_Sink";
			
			DialogExit();
		break;
		
		case "JusticeOnSale_7":
			dialog.text = "Vielen Dank für Ihre Hilfe. Diese Schurken haben ihre gerechte Strafe erhalten. Bitte erlauben Sie mir, Ihnen diese bescheidene Belohnung persönlich zu überreichen. Ich schätze Ordnung und Frieden in meiner Stadt sehr.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + hrand(1000));
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();
		break;
		//<-- Правосудие на продажу
		
			//--> Jason регата
		case "Regata":
			// belamour legendary edition -->
			if(sti(pchar.rank) < 20)
			{
				notification("Level 20 required", "None");
				dialog.text = "Ach, wunderbar, schön dich zu sehen, Kapitän! Ich habe von deinen Talenten gehört, aber komm, wenn du wirklich bereit bist.";
				link.l1 = "Ja, sicher. Wie du wünschst.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Oh, großartig, froh dich zu sehen, Kapitän! Du bist gerade rechtzeitig angekommen - die Regatta wird in ein paar Tagen beginnen. Hast du die Regeln der Regatta durchgelesen, die dir von einem Ordonnanz übergeben worden sein müssen?";
				link.l1 = "Ja, Herr, das habe ich getan.";
				link.l1.go = "Regata_1";
				RemoveItems(PChar, "letter_open", 1);//уберем письмо
				DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
			}
		break;
		
		case "Regata_1":
			dialog.text = "Und haben Sie 50000 Pesos vorbereitet - Ihre Eintrittsgebühr, die zum Preisgeld beitragen wird?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Ja, natürlich. Bitte akzeptieren Sie mein Honorar.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Ich bin momentan etwas knapp bei Kasse. Aber ich werde definitiv den benötigten Betrag aufbringen.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Sehr gut. Wenn du gewinnst - bekommst du dein Geld fünffach zurück. Jetzt musst du dich besser mit den Regeln der Regatta vertraut machen\nAlle Details kannst du von Sir Henry Stivenson erfahren, er sollte in einem Raum der Residenz sein. Geh zu ihm - er wird dir alles erklären.";
			link.l1 = "In Ordnung. Ich werde genau das tun.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Gut, aber bitte, zögern Sie nicht zu lange, Kapitän. Die Regatta beginnt sehr bald.";
			link.l1 = "Ich verstehe. Ich werde versuchen, Ihnen das Geld so schnell wie möglich zu bringen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "Aha! Und hier haben wir den Sieger der Regatta! Guten Tag Kapitän "+GetFullName(pchar)+"! Lassen Sie mich Ihnen zu diesem wohlverdienten Erfolg gratulieren! Die Gewinner der Regatta waren schon immer beliebt in den englischen Kolonien - und das aus gutem Grund.";
			link.l1 = "Danke, Herr!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Jetzt kommen wir zum angenehmsten Teil - der Siegerehrung. Der Hauptpreis beträgt 250.000 Pesos. Herzlichen Glückwunsch!";
			link.l1 = "Danke!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			// belamour legendary edition в регате только один приз -->
			GiveItem2Character(pchar, "blade_26");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "bussol");
			
			dialog.text = "Außerdem erhältst du eine Reihe wertvoller Preise: den legendären Toledo-Stahl-Degen 'Asoleda', eine Mailänder Rüstung und einen feinen Kompass. Alles deins.";
			// <-- legendary edition
			link.l1 = "Ich bin sehr froh, Herr. Wirklich, ich hätte eine solche Großzügigkeit nicht erwartet.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "Im Namen aller Untertanen der englischen Kolonien danke ich Ihnen für die Teilnahme an der Regatta und gratuliere Ihnen erneut zu Ihrem Sieg! Wenn Sie eine Wette abgeschlossen haben, suchen Sie Sir Henry Stevenson auf und holen Sie Ihren Gewinn ab, wenn Sie dies noch nicht getan haben. Viel Glück, Kapitän!";
			link.l1 = "Vielen Dank für Ihre freundlichen Worte, Herr! Lassen Sie mich Ihnen im Gegenzug dafür danken, dass Sie mir die Möglichkeit gegeben haben, an einem so großartigen Ereignis teilzunehmen. Nun gestatten Sie mir bitte, mich zu verabschieden.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_LOCATIONS);  
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> на всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[hrand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		// Rebbebion, чуть изменил функцию, чтобы условно испанцы не просили пробраться к испанцам, французы к французам и т.д
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City && colonies[n].nation != npchar.nation)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore-1)]].id;
}

int SelectCureerShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL + FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}

int SelectCustomPatrolShipType(int iFlagType)
{
	if(CheckAttribute(pchar, "questTemp.StatusCity"))
	{
		return SHIP_CAREERLUGGER;
	}
	
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

int SelectArsenalShipType(int iFlagType)
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

string SelectPassText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "That Judas, using his position, sold an important state secret to an enemy power."; break;
		case 1: sText = "That foul scoundrel killed his relative, a well-known and noble man, in order to inherit his fortune."; break;
		case 2: sText = "That foul scoundrel insulted my family and me personally."; break;
		case 3: sText = "This thieving rogue stole a decent sum of money from our city's treasury."; break;
		case 4: sText = "That villain is guilty of deaths of nearly a dozen of our citizens."; break;
		case 5: sText = "That rogue used his connection to take possession of a merchant vessel, and then he stole it and sold at the neighboring shipyard."; break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
		case 0: sCity = "LaVega"; break;
		case 1: sCity = "PuertoPrincipe"; break;
		case 2: sCity = "LeFransua"; break;
		case 3: sCity = "FortOrange"; break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "one of the junior officers in our garrison has deserted and left the colony on board of a merchant ship."; break;
		case 1: sText = "one of our officers deserted right on duty and escaped on board of a smuggler ship."; break;
		case 2: sText = "one of our naval officers serving on a patrol brig deserted for unknown reason, hijacked a long boat and disappeared on it."; break;
		case 3: sText = "one of our prison guards threw up his service for  unknown reason and left our colony aboard a private vessel."; break;
		case 4: sText = "one of the soldiers in our garrison abandoned his post while keeping guard, went to the cove and left this place aboard an unknown vessel."; break;
		case 5: sText = "one of our military officers, captain of a patrol lugger, abandoned his ship in the open sea and went south on a fishing long boat."; break;
	}
	return sText;
}
