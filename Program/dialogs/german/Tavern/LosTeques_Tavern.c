#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Es wurde Alarm im Dorf geschlagen. Alle suchen dich! Wenn ich du wäre, würde ich hier nicht zu lange warten.","Die ganze Wache durchkämmt die Stadt, um dich zu finden. Ich bin kein Idiot und ich bin nicht im Begriff, mit dir zu reden!","Lauf, Kumpel, bevor die Soldaten dich in Hackfleisch verwandeln..."),LinkRandPhrase("Was brauchst du, Schurke?! Die Stadtwache ist bereits auf deiner Spur. Du wirst nicht weit kommen, Pirat!","Dreckiger Mörder, raus aus meinem Haus! Wachen!!","Ich habe keine Angst vor dir, Hund! Der Galgen ruft, du wirst nicht weit kommen..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, ich mache mir keine Sorgen um den Alarm...","Sie haben keine Chance, mich zu fangen."),RandPhraseSimple("Halt den Mund, "+GetWorkTypeOfMan(npchar,"")+", oder ich schneide deine verdammte Zunge ab.","Heh, "+GetWorkTypeOfMan(npchar,"")+", willst du auch einen Piraten jagen? Hör zu, Kumpel, bleib ruhig und du könntest vielleicht leben..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! Willkommen, "+GetAddress_Form(NPChar)+" zur Los-Teques-Mine-Taverne. Essen, Getränke und Mädchen, alles zu erschwinglichen Preisen! Mein Name ist "+GetFullName(npchar)+" und ich stehe immer zu Ihren Diensten.";
				Link.l1 = "Lass mal sehen... Ich bin "+GetFullName(pchar)+". Freut mich, Sie kennenzulernen, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Aha, es ist mein alter Bekannter, Kapitän "+GetFullName(pchar)+"! Froh dich zu sehen, alter Mann! Rum, Mädchen?";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "Gieß mir etwas Rum ein, "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "Ich würde gerne ein Auge zuwerfen. Haben Sie ein freies Zimmer?";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("Haben Sie aktuelle Nachrichten?","Was gibt's Neues in diesen Gegenden?","Wie läuft das Leben an Land?");
				link.l3.go = "rumours_tavern";
				link.l4 = "Nein, ich brauche nichts, "+npchar.name+". Ich bin nur vorbeigekommen, um dir hallo zu sagen.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Oh, ich bin so glücklich! Neue Gesichter sind eine Seltenheit in unserer Stadt. Wie wär's, wenn ich dir etwas Rum einschenke und wir uns unterhalten...";
			link.l1 = "Das ist mein erstes Mal hier und ich würde gerne ein bisschen mehr über diese Siedlung erfahren.";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "Gieß mir etwas Rum ein, "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "Ich würde gerne ein Auge zuwerfen. Haben Sie ein freies Zimmer?";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "Nichts Interessantes zu erzählen. Jeden Tag das gleiche Geschäft: Langeweile, Sonne und Staub. Nur Soldaten, Neger und Indianer leben hier. Du könntest auch ein paar Abenteurer und Banditen finden, die nach Gold hungern\nManchmal besuchen uns Gentlemen, Kapitäne wie du, um Sklaven für Barren zu verkaufen und Edelmetalle zu kaufen. Unser Händler ist ein ziemlich interessanter Mann, er verkauft nicht nur goldene und silberne Nuggets, sondern auch Halbedelsteine\nEr behauptet, dass Menschen mit besonderem Wissen diese Kieselsteine sehr nützlich finden könnten. Also schau in unserem Laden vorbei. Die Mine selbst befindet sich weiter unten im Berg. Du kannst sie besuchen, wenn du willst, aber ich empfehle, die Wache nicht zu verärgern\nSprich nicht mit Sträflingen und Gott bewahre dich vor Diebstahl. Jedenfalls ist der beste Ort in dieser Siedlung meine Taverne, der beste Ort, um sich von dieser brennenden Hölle zu erholen!";
			link.l1 = "Danke für die Information!";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "Kapitän, ich denke, es wäre besser, wenn Sie aufhören. Gott bewahre, dass Sie unter dem Einfluss von Alkohol Ärger machen. Wir sind hier wirklich streng. Selbst Ihre Autorität wird Ihnen nicht helfen.";
				link.l1 = "Hm... Ich vermute, du hast recht - ich habe schon genug gehabt. Danke für die Sorge!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "Seien Sie willkommen, Kapitän. Nur fünf Achtstücke für einen Krug meines besten schwarzen jamaikanischen Rums!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Also gut, auf deine Gesundheit und den Wohlstand deiner Einrichtung, Kumpel!","Also gut, zu denen auf See!","Also gut, zum Wohl deiner Stadt!"),LinkRandPhrase("Also gut, zu den Winden der Produktion, zu einer Böe des Glücks, dass wir alle unbeschwerter und wohlhabender leben!","Also gut, auf den Wind, der uns in allen Angelegenheiten immer im Rücken weht!","Also gut, auf Glück, Freude, Vergnügen und Mägde!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.LosTequesSex"))
			{
				dialog.text = "Herr, Sie haben für ein Zimmer und ein Mädchen bezahlt. Gehen Sie nach oben, sie wartet schon eine Weile auf Sie.";
				link.l1 = "In Ordnung.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Wir tun es. Wie lange hattest du vor zu bleiben?";
			if(!isDay())
			{
				link.l1 = "Bis zum Morgen.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Bis zur Nachtzeit.";
				link.l1.go = "room_night";
				link.l2 = "Bis zum nächsten Morgen.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "Das werden zehn Achtstücke sein. Möchten Sie ein Mädchen für das Zimmer dazu? Nur tausend Pesos für die Dirne.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Nein, ich brauche kein Mädchen. Hier, nimm das für das Zimmer.";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Ja, ich nehme das Zimmer und das Mädchen. Hier ist das Geld.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Ach, ich kann mir das Zimmer nicht leisten.";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "Das werden zehn Achtstücke sein. Möchten Sie ein Mädchen für das Zimmer dazu? Nur tausend Pesos für die Dirne.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Nein, ich brauche kein Mädchen. Hier, nimm das für das Zimmer.";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Gut. Lass uns das Zimmer und das Mädchen nehmen. Hier ist das Geld.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "Ach, ich kann mir das Zimmer nicht leisten.";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "Das werden zehn Achtstücke sein. Möchten Sie dazu ein Mädchen für das Zimmer? Nur tausend Pesos für die Dirne.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Nein, ich brauche kein Mädchen. Hier, nimm das für das Zimmer.";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "Gut. Lassen Sie uns das Zimmer und das Mädchen nehmen. Hier ist das Geld.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "Ach, ich kann das Zimmer nicht bezahlen.";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "Gehen Sie oben, Senor. Das Mädchen wird auf Sie warten. Schönen Aufenthalt!";
			link.l1 = "Danke, Kumpel...";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.LosTequesSex = "true";
			LocatorReloadEnterDisable("LosTeques_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("LosTeques_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\LosTeques_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LosTeques_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "Wie, weißer Meister. Schau nicht auf "+npchar.name+", so, "+npchar.name+" weiß, wie man alles noch besser macht als eine weiße Squaw aus dem Bordell. Ah, Senor, du bist so attraktiv... Verspreche, diese Squaw wird dich lange lieben.";
			link.l1 = "Das klingt gut, zeig mir deine besten indischen Amulette. Ich werde keinen Regentanz brauchen, um dich nass zu machen...";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Raub bei hellichtem Tag!!! Was geht hier vor?! Warte, halt ein, Kumpel...","He, was machst du da?! Versuchst du, mich zu berauben? Jetzt hast du dich verlaufen...","Warte, was zum Teufel tust du da? Es stellt sich heraus, dass du ein Dieb bist! Betrachte dies als das Ende der Linie, Arschloch...");
			link.l1 = LinkRandPhrase("Teufel!","Verdammt!","Ach, Scheiße");
			link.l1.go = "PL_Q3_fight";
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
	}
}
