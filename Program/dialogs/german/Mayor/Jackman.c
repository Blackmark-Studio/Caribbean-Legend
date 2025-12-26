// Якоб Джекман
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Bist du wahnsinnig? Wolltest du Metzger spielen? Alle Piraten sind wütend auf dich, Junge, du solltest besser diesen Ort verlassen...","Es scheint, dass du verrückt geworden bist, Junge. Wolltest du deine Hände ein bisschen strecken? Nichts für ungut, aber du hast hier nichts zu suchen. Verschwinde!");
				link.l1 = RandPhraseSimple("Hör zu, ich möchte die Situation klären...","Hilf mir, dieses Problem zu lösen...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", ich würde gerne" + GetSexPhrase(""," mit dir") + " über meine Sicherheit auf See sprechen. Die Jungs von der Bruderschaft der Küste zeigen zu viel Interesse an meiner bescheidenen Person. Könntest du sie ein wenig zügeln?";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("Hast du mir etwas zu sagen? Nein? Dann verschwinde von hier!",
						"Ich glaube, ich habe mich klar ausgedrückt, hör auf, mich zu nerven.",
						"Obwohl ich mich klar ausgedrückt habe, nervst du mich weiterhin!","Also gut, ich habe genug von dieser Unhöflichkeit.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ich gehe schon.",
						"Sicher, "+npchar.name+"...",
						"Entschuldigung, "+npchar.name+"...",
						"Autsch...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
			{
				link.l1 = "Wo kann ich Jimmy Higgins finden?";
				link.l1.go = "Saga_Jimmy";
			}	
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
			{
				link.l1 = "Wieder ich, Jackman. Sie sagen, dass du nach einigen vermissten Leuten suchst...";
				link.l1.go = "Saga_search";
			}	
			//<-- Сага

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Es geht um deinen Gefangenen.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Hallo, Jackman. Über deine Mission...";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "Es geht um deinen Gefangenen.";
					link.l1.go = "CapComission6";
				}
			}	
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Bist du wahnsinnig? Wolltest du den Schlachter spielen? Alle Piraten sind wütend auf dich, Junge, du solltest besser diesen Ort verlassen...");
				link.l1 = RandPhraseSimple("Hör zu, ich will die Situation klären...","Hilf mir, dieses Problem zu lösen...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", ich würde gerne" + GetSexPhrase(""," mit dir") + " über meine Sicherheit auf See sprechen. Die Jungs von der Bruderschaft der Küste zeigen zu viel Interesse an meiner bescheidenen Person. Könntest du sie ein wenig zügeln?";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("Hast du mir etwas zu sagen? Nein? Dann verschwinde von hier!",
						"Ich glaube, ich habe mich klar ausgedrückt, hör auf, mich zu nerven.",
						"Obwohl ich mich klar ausgedrückt habe, nervst du mich weiterhin!","Also gut, ich habe genug von dieser Unhöflichkeit.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ich gehe schon.",
						"Sicher, "+npchar.name+"...",
						"Entschuldigung, "+npchar.name+"...",
						"Autsch...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Es geht um deinen Gefangenen.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}				
		break;

//-----------------------------------------пиратская сага----------------------------------------------------
		case "Saga_Jimmy":
			dialog.text = "Wirklich! Jemand braucht diesen faulen Hintern! Er trinkt schon seit mehreren Tagen alleine Rum in seiner Hütte. Ich rate dir nicht, ihn zu besuchen. Er ist nicht gerade der feinste Mann, auch wenn er nüchtern ist...";
			link.l1 = "Es ist in Ordnung, ich bin auch kein Heiliger. Wo ist seine Hütte?";
			link.l1.go = "Saga_Jimmy_1";
		break;
		
		case "Saga_Jimmy_1":
			dialog.text = "Es ist direkt vor der Taverne. Er hat einen guten Ort für schnelle Läufe um ein Getränk zu holen, gewählt.";
			link.l1 = "Danke!";
			link.l1.go = "Saga_Jimmy_2";
		break;
		
		case "Saga_Jimmy_2":
			DialogExit();
			pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
			pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
			pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
			pchar.questTemp.Saga = "jimmy";
		break;
		
		case "Saga_search":
			dialog.text = "Und wer hat dir das erzählt? Dieser betrunkene Kopf Higgins? Hast du etwas über Gladys Chandler oder Henry, den Henker, herausgefunden?";
			link.l1 = "Nichts Besonderes, wirklich, aber ich möchte etwas Spezifisches über diesen Henker wissen.";
			link.l1.go = "Saga_search_1";
		break;
		
		case "Saga_search_1":
			dialog.text = "Es gibt nichts zu wissen. Ein paar erinnern sich jetzt an ihn, aber vor zwanzig Jahren war Henry sehr beliebt bei den Huren von Bridgetown bis Tortuga. Wetten Sie! Ein Bootsmann der 'Neptune', unter dem Kommando von Kapitän Butcher selbst! Er muss jetzt wirklich alt sein, wenn er noch lebt, natürlich.\nDie Chancen stehen schlecht, aber Sie wissen, nichts ist unmöglich. Ich werde zwanzigtausend Pesos für jede Information über ihn bezahlen, doppelt, wenn Sie ihn lebend hierher bringen.";
			link.l1 = "Wie viel wirst du für Gladys und ihre Tochter zahlen?";
			link.l1.go = "Saga_search_2";
		break;
		
		case "Saga_search_2":
			dialog.text = "Oh, sie ist nicht ihre Tochter. Wenn du dieses Mädchen lebend bringst, zahle ich dir einen Haufen Dublonen. Ich interessiere mich nicht für Gladys. Fragen?";
			link.l1 = "Ich wünschte, ich könnte den Grund für diesen Wirbel kennen, aber ich werde nicht fragen. Es sieht so aus, als könnte es meine Biographie verkürzen.";
			link.l1.go = "Saga_search_3";
		break;
		
		case "Saga_search_3":
			dialog.text = "Vielleicht... Diese Geheimnisse gehen dich nichts an. Wisse weniger, lebe länger. Versuch nicht, mich solche Fragen noch einmal zu stellen, denn ich habe angefangen zu vermuten, dass mit dir etwas nicht stimmt. Verschwinde, bevor ich meine Meinung ändere.";
			link.l1 = "Auf Wiedersehen, Baron!";
			link.l1.go = "Saga_search_4";
		break;
		
		case "Saga_search_4":
			DialogExit();
			AddQuestRecord("Saga", "6");
			if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
			{
				AddQuestUserData("Saga", "sText", "To Antigua now. The corvette must be boarded.");
				DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
			}
			pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
			pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
			pchar.questTemp.Saga = "donovan";
		break;
		
		// абордаж, в каюте
		case "Jackman_abordage":
			dialog.text = "Ha! Wir treffen uns wieder, Kapitän "+GetFullName(pchar)+". Ich gebe zu, du bist ein würdiger Gegner, trotz deiner Versuche, dich in Maroon-Town als Einfaltspinsel darzustellen. Ich habe etwas über dich herausgefunden, deine Intrigen mit der Holländischen Westindien-Kompanie wurden aufgedeckt... Ich verstehe jetzt, was für ein Typ du bist.";
			link.l1 = "Ich kenne deine Sorte auch, Jacob. Also lasst uns keine Illusionen schaffen.";
			link.l1.go = "Jackman_abordage_1";
		break;
		
		case "Jackman_abordage_1":
			dialog.text = "Und wie du mich mit 'Marlin' hereingelegt hast! Ich nehme an, dass mein armer Bruder tot ist...";
			link.l1 = "Ich nehme an, dass du dich für ihn rächen willst? Aber ich habe auch eine lange Rechnung für dich. Für den in die Enge getriebenen Nathaniel, seine Frau, seine Fregatte, den verleumdeten Shark, Blaze Sharp...";
			link.l1.go = "Jackman_abordage_2";
		break;
		
		case "Jackman_abordage_2":
			dialog.text = "Blaze? Ich habe ihn nicht getötet.";
			link.l1 = "Sogar wenn es stimmt, reicht der Rest meiner Liste. Ich habe genug von deinem Namen. Genug der Worte, Jackman! Unsere Klingen werden sprechen!";
			link.l1.go = "Jackman_abordage_3";
		break;
		
		case "Jackman_abordage_3":
			dialog.text = "So ein heftiger Narr.. Verdammt! Jetzt halte dich besser fest! Jacob Jackman wurde noch nie besiegt! Carpacho, du kommst gerade rechtzeitig! Komm her!";
			link.l1 = "...";
			link.l1.go = "Jackman_abordage_4";
		break;
		
		case "Jackman_abordage_4":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int iScl = 30 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
			LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			sld = characterFromId("Danielle");
			RemovePassenger(Pchar, sld);
		break;

		//*************************** Генератор "Captain's offer - Ransom" **********************
		case "CapComission1":
			dialog.text = "Ha-ha. Glaubst du, ich habe hier nur einen Gefangenen? Nenn ihn.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". Ist er hier?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Er war es. Ich habe ihn an diesen Plantagenbesitzer aus Barbados verkauft - Oberst Bishop, als er vor einer Woche hier war.";
				link.l1 = "Verdammt...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ach, endlich. Ich hatte darüber nachgedacht, ihn an diesen Plantagenbesitzer aus Barbados zu verkaufen, der wird in einer Woche oder zwei hier sein... Hast du ein Lösegeld?";
				link.l1 = "Schau, es gibt ein kleines Problem... Eigentlich habe ich nicht so viel Geld. Aber ich bin bereit zu arbeiten.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Es ist gut, dass du ihn nicht verkauft hast. Hier sind deine Münzen - 150.000 Pesos. Wo kann ich ihn bekommen?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Du warst zu langsam... Und warum kümmert er dich? Ich habe nur mit seinen Verwandten verhandelt.";
			link.l1 = "Sie haben mich gebeten, hierher zu kommen.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Nun, du bist spät dran. Ich kann nichts tun.";
			link.l1 = "Hör zu, für wie viel hast du ihn verkauft, wenn es kein Geheimnis ist?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, ist es nicht. Aber ich werde es dir nicht sagen... Du wirst lachen, wenn ich es tue. Ha-ha-ha-ha! Lebewohl.";
			link.l1 = "Bis dann...";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Nun, nun.. Ich habe einige Geschäfte... Weiß nicht einmal, wie ich anfangen soll. Ich muss einen Piraten versenken, der die Linie überschritten hat.";
				link.l1 = "Kann er nicht einfach im Dschungel getötet werden?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Nun, "+pchar.name+", weißt du, so funktioniert das nicht. Komm zurück mit dem Geld und du bekommst deinen Schwächling, ha-ha.";
				link.l1 = "Gut. Bis dann.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Das ist nicht, wie Geschäfte laufen, weißt du... Ich brauche seinen Tod nicht, ich muss einigen Leuten beibringen, sich von meinem Anteil der Beute fernzuhalten. Aber wenn er zu den Haien geht, werde ich nicht verärgert sein.";
			link.l1 = "Warum schickst du nicht deine eigenen Leute hinter ihm her?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Hm... Nun, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" hat einige Piraten davon überzeugt, dass ihr Anteil an der Beute nicht weit von unserer Versteck aufbewahrt wird "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Ihre beiden Schiffe '"+pchar.GenQuest.CaptainComission.ShipName1+"' und '"+pchar.GenQuest.CaptainComission.ShipName2+"' hat vor kurzem den Anker gelichtet und ist nach "+sLoc+". Jetzt siehst du, warum ich meinen Männern diese Arbeit nicht anvertrauen kann?";
			link.l1 = "Ich tue. Wie viel Zeit habe ich?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 bis 15 Tage, nicht mehr, vermute ich. Ich will nicht, dass sie zur Beute gelangen, oder es wäre unsinnig, sie mit wertvoller Fracht zu versenken. In diesem Fall wäre es besser, wenn sie es hierher brächten...";
			link.l1 = "Gut, ich bin dabei. Ich werde versuchen, sie zu fangen.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Mach dir keine Sorgen. Meine Männer werden ihn zu deinem Schiff bringen. Und warum kümmert er dich?";
			link.l1 = "Ich nicht. Seine Verwandten haben mich gebeten, ihn zu liefern.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ach, das ist gut. Ich war fast bedauern, so einen niedrigen Preis für deinen Mann zu geben. Ha-ha-ha-ha. Lebewohl.";
			link.l1 = "Bis dann.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen		
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Also, , "+GetFullName(pchar)+", hast du meinen Kumpel versenkt? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nein. Ich habe es nicht geschafft, sie zu fangen. Und ich habe sie bei der Rückkehr nicht getroffen.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Ich habe. Ich habe sie geschickt, um die Haie zu füttern.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Verdammt! Ob du sie getroffen hast oder nicht, spielt jetzt keine Rolle mehr! Und was wird dein nächster Vorschlag sein?";
			link.l1 = "Vielleicht hast du einen einfacheren Job für mich?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Hör zu, Jackman, senke den Preis für den Gefangenen...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nein.";
			link.l1 = "Dann leb wohl...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Den Preis senken? Ich habe gerade meinen Vorrat wegen deiner Inkompetenz verloren! Und jetzt kann ich den Preis erhöhen! Du kannst ihn für 200.000 Pesos haben, wenn du willst, oder du kannst zum Teufel hier raus.";
			link.l1 = "Es ist zu teuer... Lebewohl...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Verdammt, nimm deine Münzen.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Gut, du kannst diesen Schwächling nehmen...";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Gut gemacht! Nimm deinen Schwächling und viel Glück.";
			link.l1 = "Danke. Leb wohl.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "Hast du das Geld mitgebracht, Charles? Ich habe nicht gescherzt, als ich davon sprach, den Mann an die Plantage zu verkaufen.";			
			link.l1 = "Hör zu, "+NPChar.name+", es gibt ein Problem... Ich habe nicht so viel Geld. Aber ich bin bereit zu arbeiten.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Es ist gut, dass du ihn nicht verkauft hast. Hier sind deine Münzen - 150.000 Pesos. Wo kann ich ihn bekommen?"link.l2.go ="HauptmannsKommission2_3";
			}			
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Raub!!! Das ist inakzeptabel! Mach dich bereit, "+GetSexPhrase("Junge","Mädchen")+"...","He, was zur Hölle machst du da?! Dachtest du könntest mich ausrauben? Du bist erledigt...","Warte, was zum Teufel? Hände weg! Du bist also ein Dieb! Ende der Fahnenstange, Mistkerl...");
			link.l1 = LinkRandPhrase("Scheiße!","Donnerwetter!!","Verdammt noch mal!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("Verschwinde von hier!","Verlass mein Zuhause!");
			link.l1 = "Ups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Belästige mich nicht mit deinem billigen Geschwätz. Das nächste Mal wirst du das Ergebnis nicht mögen...";
        			link.l1 = "Ich habe es.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "Es ist vorbei, kein Gerede.""Ich will nicht mehr mit dir reden, also wäre es besser, wenn du mich nicht belästigen würdest.";
			link.l1 = RandPhraseSimple("Wie du wünschst...","Gut dann...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ich hoffe, du wirst mehr Respekt zeigen und aufhören, unhöflich zu sein? Sonst müsste ich dich töten. Das wäre sehr unangenehm.";
        			link.l1 = "Du kannst sicher sein, Jackman, ich werde es tun.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Fortorange_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Das Problem gelöst? Verstehst du, was du getan hast? Wie auch immer, bring mir eine Million Pesos und ich werde die Jungs überzeugen, deine 'Heldentaten' zu vergessen. Wenn dir die Idee nicht gefällt, kannst du zur Hölle fahren.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Gut, ich bin bereit zu zahlen.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Verstanden. Ich gehe jetzt.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Gut! Betrachten Sie sich wieder als sauber. Aber ich hoffe, dass Sie solche widerlichen Dinge nicht noch einmal tun werden.";
			link.l1 = "Ich werde nicht. Viel zu teuer für mich. Lebewohl...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("Wir haben das heute schon besprochen.",
				                                      "War ich nicht deutlich genug?",
				                                      "Deine Hartnäckigkeit geht mir langsam auf die Nerven.",
				                                      "Jetzt reicht's. Verschwinde!",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Dann vielleicht ein andermal...",
				                                   "Natürlich, "+npchar.name+"...",
				                                   "Entschuldige, "+npchar.name+"...",
				                                   "Aua...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "Ha! Unsere Bruderschaft macht dir zu schaffen, was, " + GetSexPhrase("Kumpel", "Mädel") + "? Ich kann sie für eine Weile in Schach halten. Aber das wird dich ordentlich was kosten. " + FindRussianDublonString(iBarbazonTotalTemp) + " auf den Tisch, und wir sind im Geschäft.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "Natürlich, hier ist dein Geld.";
					else link.l0 = "Scheint, als hätte ich keine Wahl. Hier ist dein Geld.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "Ich komme ein andermal wieder...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "Bist du verrückt geworden" + GetSexPhrase("", ", Mädchen") + "? Unsere Jungs machen einen Bogen um dich, als hättest du die Pest. Also verschwinde und nerv mich nicht.";
				else
					dialog.text = "Wovon redest du, " + GetSexPhrase("Kumpel", "Mädel") + "? Du bist eine richtige Nervensäge – selbst die Köter merken das. Keiner will was mit dir zu tun haben.";
				link.l1 = "Verstanden...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
	}
}
