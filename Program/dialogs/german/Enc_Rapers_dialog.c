void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "Exit_Fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar); 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			
			if(pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}			
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");			
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}	
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();	
			AddDialogExitQuest("OpenTheDoors");			
		break;
		
		case "First time":
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
//			Diag.TempNode = "OnceAgain";
			if(pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = LinkRandPhrase("Geh deinen eigenen Weg, "+GetSexPhrase("Kamerad","lass")+". Sie wird uns am Ende danken, weißt du.","Verschwinde! Lass die Herren eine gute Zeit haben.","Das geht dich nichts an, "+GetSexPhrase("Fremder","lass")+". Wir werden einfach nur Spaß haben, und das ist alles!");
				link.l1 = LinkRandPhrase("Ich werde das nicht zulassen!","Lass sofort deine bösen Pläne fallen!","Ich werde keine Gewalt dulden!");
				link.l1.go = "Node_Fight";
				link.l2 = RandPhraseSimple("Ich habe es verstanden, gehe jetzt. Entschuldigung für die Störung.","Ich wage es nicht, Sie weiter zu stören. Entschuldigung für die Störung.");
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if(pchar.GenQuest.EncGirl == "Begin_2")
			{
				if(sti(pchar.rank) < 10)
				{
					dialog.text = LinkRandPhrase("Geh deinen eigenen Weg, "+GetSexPhrase("Kamerad","lass")+". Am Ende wird sie uns danken, weißt du.","Verschwinde! Lass die Herren eine gute Zeit haben.","Das geht dich nichts an, "+GetSexPhrase("Fremder","lass es")+". Wir werden nur etwas Spaß haben, und das ist alles!!");
					link.l1 = LinkRandPhrase("Ich werde das nicht zulassen!","Verzichte sofort auf deine bösen Pläne!","Ich werde keine Gewalt dulden!");
					link.l1.go = "Node_Fight";
					link.l2 = RandPhraseSimple("Ich habe verstanden, ich gehe schon. Entschuldigung für die Störung.","Ich wage es nicht, Sie weiter zu stören. Entschuldigung für die Belästigung.");
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hallo, "+GetSexPhrase("Fremder","junge Dame")+", warum suchst du Ärger? Dieses Mädchen ist eine 'bekannte' Person in unserer Siedlung. Wir haben ihr bereits bezahlt, aber sie hat dich bemerkt und beschlossen, mit unserem Geld zu fliehen.","Hallo, "+GetSexPhrase("Kamerad","lass")+", geh deinen eigenen Weg und misch dich nicht in unsere Angelegenheiten ein. Wir haben dieses Mädchen in einem Würfelspiel gewonnen, aber sie war ein kleines bisschen zu schnell und ist weggelaufen, wir haben sie eine Stunde lang in diesem Dschungel verfolgt.");
					link.l1 = "Es ist mir egal, ich werde nicht zulassen, dass du ihr schadest!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Oh, ich sehe! Und ich habe ihr fast geglaubt! So eine Dirne...","Ach, nun, das ist eine andere Sache. Nun, viel Spaß, Kumpels!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}	
			}
			if(pchar.GenQuest.EncGirl == "Begin_3")
			{
				if(sti(pchar.rank) < 20)
				{	
					dialog.text = "Geh deinen eigenen Weg, "+GetSexPhrase("guter Mann","junge Dame")+". Wir werden es ohne dich herausfinden.";
					link.l1 = "Ich werde keine Gewalt dulden!";
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = RandPhraseSimple("Hallo, "+GetSexPhrase("Fremder","junge Dame")+", warum suchst du Ärger? Dieses Mädchen ist eine 'bekannte' Person in unserer Siedlung. Wir haben ihr bereits bezahlt, aber sie hat dich bemerkt und beschlossen, mit unserem Geld zu fliehen.","Hallo, "+GetSexPhrase("Kamerad","Lass")+", geh deinen eigenen Weg und misch dich nicht in unsere Angelegenheiten ein. Wir haben dieses Mädel in einem Würfelspiel gewonnen, aber sie war ein bisschen zu schnell, um wegzulaufen, wir haben sie schon seit einer Stunde verfolgt.");
					link.l1 = "Es ist mir egal - Ich werde nicht zulassen, dass du ihr schaden zufügst!";
					link.l1.go = "Node_3";
					link.l2 = RandPhraseSimple("Ach, ich verstehe! Und ich habe ihr fast geglaubt! So eine Dirne...","Ach, nun, das ist dann eine andere Angelegenheit. Na dann, viel Spaß, Kumpels!");	
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}			
		break;
		
		case "Node_Fight":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Nun, du hast sicherlich die richtige Zeit für einen Spaziergang gewählt...","Also, du hast dich also entschieden, ein Held zu sein?")+" Umgang mit h"+GetSexPhrase("ich bin","er")+", Jungs!","Du "+GetSexPhrase("Schleim","Dreck")+"! Du wagst es, uns im Weg zu stehen?! Schnitt h"+GetSexPhrase("im","er")+"!");
			link.l1 = "Ich habe schon bedrohlichere Leute gesehen!";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100*(rand(4)+5) + 200 * sti(pchar.rank);
			dialog.text = "Du solltest wissen, dass sie uns ziemlich viel gekostet hat! Und wenn du so edel bist, kannst du sie für "+sti(pchar.GenQuest.EncGirl.price)+" Pesos."+GetSexPhrase(" Du wirst eine gute Zeit mit ihr haben, he-he...","")+"";
			if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = RandPhraseSimple("Hier ist dein Geld. Ich nehme sie mit mir.","Hör auf, mit den Zähnen zu knirschen. Ich nehme das Mädchen mit mir. Hier ist dein Geld.");
				link.l1.go = "Node_4";
			}	
			link.l2 = LinkRandPhrase("Also, Geld ist es, was du willst? Wie wäre es mit kaltem Stahl?","Soll das lustig sein, schau dir das Mädchen an, du Narr! Sie hat Angst!","Wen versuchst du hier zu täuschen, du Degenerierter!");
			link.l2.go = "Node_Fight";
		break;
		
		case "Node_4": // бандюки уходят, девица остаётся - ГГ ее выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price))); 
			ChangeCharacterComplexReputation(pchar,"nobility", 7);
			//pchar.quest.LandEnc_RapersBadExit.over = "yes";
			sGlobalTemp = "Saved_CangGirl";
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_5":
			dialog.text = "Warum glauben Sie ihr überhaupt? Welche Gewalt? Sie ist von zu Hause weggelaufen, und wir wurden von unserem Chef geschickt, um sie zu finden.";
			link.l1 = RandPhraseSimple("Nun, das ist eine andere Geschichte. Geh, verfolge deinen Ausreißer.","Oh, ich verstehe. Nun, verfolge sie weiter... und ich habe einige Geschäfte zu erledigen.");
			link.l1.go = "Exit_NoFight";
			link.l2 = RandPhraseSimple("Erzähl diese Märchen deinen Enkeln, wenn du lange genug lebst, um sie zu haben!","Wen versuchst du hier zu verarschen, du Bastard?!");
			link.l2.go = "Node_6";
			link.l3 = "Ich bringe sie selbst nach Hause, um etwas Schlimmes zu vermeiden. Wer sind ihre Eltern?";
			link.l3.go = "Node_7";
		break;
		
		case "Node_6":
			dialog.text = "Willst du sterben? Das ist deine Wahl...";
			link.l1 = "Schau mal, wer da spricht.";
			link.l1.go = "Exit_Fight";
		break;
		
		case "Node_7":
			sGlobalTemp = "Saved_CangGirl";
			if(pchar.GenQuest.EncGirl.city == "Panama") i = hrand(2);
			else	i = hrand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = "is a store owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a store owner";
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = "serves in the port office";
					pchar.GenQuest.EncGirl.FatherGen = "who serves in the port office";
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = "serves as the prison's commandant";
					pchar.GenQuest.EncGirl.FatherGen = "of a prison's commandant";
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = "is a shipyard owner";
					pchar.GenQuest.EncGirl.FatherGen = "of a shipyard owner";
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;				
			}
			dialog.text = "Ihr Vater "+pchar.GenQuest.EncGirl.FatherNom+", in der Siedlung von "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+". Aber bitte, lasst uns nicht im Stich, denn er ist nicht jemand, mit dem man sich anlegen sollte, er wird uns alle lebendig häuten...";
			link.l1 = "Mach dir keine Sorgen. Ich werde sie ihm überbringen.";
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;
		
		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");			
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if(i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "","OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;
		
		case "Node_8":
			dialog.text = "Und so treffen wir uns wieder. Wo ist dein Begleiter? Oh, nun, eigentlich brauche ich sie nicht, wenn du hier bist.";
			link.l1 = "Meine Herren, ich denke wirklich, dass ihr bereits genug Geld bekommen habt, um das Mädel in Ruhe zu lassen.";
			link.l1.go = "Node_9";
		break;
		
		case "Node_9":
			if(hrand(1) == 0)
			{	
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;	
			}	
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);	
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;	
			}	
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch(hrand(4))
			{
				case 0:
					sTemp = "a leg";
				break;
				case 1:
					sTemp = "an arm";
				break;
				case 2:
					sTemp = "an ear";
				break;
				case 3:
					sTemp = "a nose";
				break;
				case 4:
					sTemp = "an eye";
				break;
			}
			dialog.text = "Was ist dein Geld im Vergleich zu den Schätzen von "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_GEN)+"? "+"Er war so gierig, dass er seine eigene Tochter nicht heiraten wollte, weil er zusätzliche Ausgaben vermeiden wollte...\nAber er hat unseren Anteil in seinen Truhen!"+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.PirateName2,NAME_NOM)+" hat beim Entern verloren "+sTemp+"! Also was haben wir stattdessen? "+"Jämmerliche Handvoll Silber? "+GetName(pchar.GenQuest.EncGirl.PirateIdx,pchar.GenQuest.EncGirl.PirateName1,NAME_NOM)+" hat immer die ganze Beute zu seinem Versteck gebracht. Aber jetzt geben wir nicht auf! Zeige uns, wo seine Truhen sind!";
			link.l1 = "Nun, ich habe sicherlich nicht darum gebeten, die Schätze Ihres Kapitäns zu bewachen, aber ich kann Ihnen den Ort nicht zeigen... Weil ich nicht weiß, wo dieser Ort ist.";
			link.l1.go = "Node_10";
		break;
		
		case "Node_10":
			dialog.text = "Du lügst!!! Ich kann den Duft von Gold riechen, der aus dieser Höhle kommt! Zeige mir den Ort, wenn du nicht sterben willst!";
			link.l1 = "Ich sehe, dass meine Worte dich nicht überzeugt haben. Vielleicht wird mein Schwert aussagekräftiger sein?";
			link.l1.go = "Node_11";
		break;
		
		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = "Du "+GetSexPhrase("Kurz","Dreck")+"! Geh mir aus dem Weg!";
			link.l1 = "Verdammt!";
			link.l1.go = "exit_fight";
		break;
		
		case "EncGirl_Berglar":
			dialog.text = "Hallo, gut "+GetSexPhrase("Mann","Dame")+". Wir haben Beschwerden über dich.";
			link.l1 = "Beschwerden von wem? Von dieser Hure?";
			link.l1.go = "EncGirl_Berglar1";
		break;
		
		case "EncGirl_Berglar1":
			dialog.text = "Halte deine Zunge im Zaum, verstanden? Ich werde nicht zulassen, dass du meine Schwester beleidigst! Erst hast du sie im Dschungel belästigt, dann hast du sie hierher gebracht "+GetSexPhrase("für mehr Unanständigkeit","und hat mich ausgeraubt")+".";
			link.l1 = "He, Kamerad, muss ich mir das wirklich alles anhören?";
			link.l1.go = "EncGirl_Berglar2";
		break;
		
		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money)/5) + 5000;
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if(sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = "Nein. Eine bescheidene Summe von nur "+sti(pchar.GenQuest.EncGirl.BerglarSum)+" Pesos werden Sie aus all den Ärger retten.";
				if(sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = "Nun, edle Taten sind sicherlich ein bisschen teuer heutzutage. Na gut, nimm es...";
					link.l1.go = "EncGirl_Berglar3";
				}	
				link.l2 = "Ich glaube, es wäre billiger, ein Loch in deinen Bauch zu machen, damit du mir nicht den Weg zum Ausgang versperrst.";
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = "Nein. Aber du wirst auch deine Taschen umstülpen, sonst steche ich dich!";
				link.l1 = "Also gut, nimm es, du Schurke! Aber damit kommst du nicht davon...";
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = "Ich denke, es wäre einfacher, ein Loch in deinen Bauch zu machen, damit du nicht auf meinem Weg zum Ausgang stehst.";
				link.l2.go = "EncGirl_Berglar4";				
			}			
		break;
		
		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = "Sehr gut. Gut, dass wir ihn los sind.";
			link.l1 = "Viel Glück.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");			
		break;
		
		case "EncGirl_Berglar3_1":
			dialog.text = "Natürlich werde ich nicht, natürlich... Nun, Auf Wiedersehen, "+GetSexPhrase("Kumpel","lass")+"."+GetSexPhrase(" Und denk daran, du bist nicht so gutaussehend, dass jedes Mädchen dich hätte sofort bei deinem Anblick verfallen können. Das wäre meine Lektion für dich.","")+"";
			link.l1 = ""+GetSexPhrase("Das ist sicher!..","Verschwinde endlich!")+"";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");			
		break;
		
		case "EncGirl_Berglar4":
			dialog.text = "Du siehst aus wie "+GetSexPhrase("so ein edler Mann","so eine gut erzogene Dame")+", warum die schlechte Sprache?";
			link.l1 = "Es passt am besten zu mir...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;
		
		case "Node_2":
			dialog.text = "Nun, du hast danach gefragt! Sollen wir sie kitzeln?"+GetSexPhrase("ich bin","er")+" mit Stahl, Jungs?";
			Link.l1 = "Bete, bevor du stirbst!";
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = "Also, möchtest du dich uns anschließen oder was? "+GetSexPhrase("Verschwinde, es gibt nicht genug für uns alle","Verschwinde, solange du noch kannst, eine Maid ist genug für uns")+"!";
			Link.l1 = "Nun, dann werde ich Sie nicht stören.";
			Link.l1.go = "Exit_NoFight";
			Link.l2 = "Ich werde keine Gewalt zulassen!";
			Link.l2.go = "Node_2";
		break;				
	}
}
