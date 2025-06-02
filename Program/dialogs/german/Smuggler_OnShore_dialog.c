void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;	
	int Shit, i;
	ref refStore;
	ref sld;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "First time":
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				int iTmp = false;
				int iChIdx;

				// поиск мин.  те старшего класса
				for (i=0; i<COMPANION_MAX; i++)
				{
					iChIdx = GetCompanionIndex(GetMainCharacter(), i);
					if (iChIdx>=0)
					{
						sld = GetCharacter(iChIdx);
            			if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
					}
				}
				
				if (iTmp)
				{
					dialog.text = NPCStringReactionRepeat("Wurde dir nicht gesagt, dass du nicht mit einem so auffälligen Schiff hierher kommen sollst! Warum bringst du nicht ein Paar Linienschiffe mit? Verzieh dich und komm mit einem kleineren Schiff.","Verschwinde! Sonst geben wir dich selbst an die Patrouille weiter.","Geh zu deinem Boot und verschwinde.","So müde von dir...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("In Ordnung, in Ordnung, ich werde mein Schiff wechseln.","Beruhige dich, ich bin auf dem Weg.","Verdammt, ich dachte, es würde funktionieren...","Ja, ich bin wirklich stur!",npchar,Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("He, was machst du hier, "+GetSexPhrase("Kumpel","Mädchen")+"?",RandSwear()+"Was machst du hier?!");
				Link.l1 = "Entspann dich, Kumpel, lass uns handeln!";
				Pchar.quest.Contraband.Counter = 0; // не торговали
				if(Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))				
				{
					Link.l2 = "Ich bin hier auf Befehl des Gouverneurs von "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"! Legt eure Waffen nieder und folgt mir, ihr seid verhaftet!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("Ach, endlich! Wir haben auf dich gewartet. Los, es ist Zeit abzusegeln.","Lass es uns schnell machen. Überall sind Patrouillen. Wir müssen hier weg!");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "Ich bin hier auf Befehl des Gouverneurs von "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"! Legt eure Waffen nieder und folgt mir, ihr seid verhaftet!";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "Und wer bist du? Wir haben nur von einem Passagier gesprochen!";
						Link.l1 = "Ups..";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("Wer bist du? Wir haben auf einen Passagier gewartet, nicht auf einen Kapitän.","Verschwinde! Komm nicht zurück, bis du dein Schiff losgeworden bist.");
						Link.l1 = "Mist!";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
						    dialog.Text = "Scheiße, Patrouille! Wir kennen dich nicht und du uns nicht.";
							Link.l1 = "Gut...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("Danke für deine Hilfe. Das werden wir nicht vergessen. Lass uns jetzt segeln.","Gut gemacht! Guter Kampf. Lasst uns weitergehen.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "Ich bin auf dem Weg.";
					Link.l2.go = "Exit";
					//а это патруль... 
					if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0*(1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else 
					{
						//поместим Грея в локацию.
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
                        refStore.dialog.CurrentNode = "Travel_talkStart";
						//поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // признак выхода с палубы
						
						SetLaunchFrameFormParam(".. " + sti(Pchar.GenQuest.contraTravel.destination.days) + " days passed." + NewStr() + "Smuggler's ship deck.",
						                        "Reload_To_Location", 0.1, 5.0);
                        bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // подмена палубы
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
//================ METRO ====================
				}
				else
				{
                    // если таможня уже бежит
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
					    dialog.Text = RandSwear()+"Patrouille! Wir kennen dich nicht und du kennst uns nicht.";
						Link.l1 = "Gut!";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "Verschwinde! Wir reißen dir die Eingeweide heraus, wenn du unseren Handel verdirbst.";
						Link.l1 = RandPhraseSimple("Du wagst es, mich zu bedrohen, du Köter!?","Du wirst an deinen Worten ersticken!");
						Link.l1.go = "Exit_fight";
						Link.l2 = "Mach dir keine Sorgen, ich weiß, was Geschäft bedeutet. Tschüss.";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "Trägst du es auf deinem Rückgrat? Wo ist dein Schiff?";
			Link.l1 = RandPhraseSimple("Zuerst möchte ich sehen, ob da ein Haken dran ist.","Habe das Schiff nicht riskieren wollen. Ich sehe alles lieber mit meinen eigenen Augen.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "Der Handel ist vorbei!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "Wir sind ehrliche Männer und wir werden dich nicht betrügen. Bring dein Schiff hierher, lass nur keine Patrouillen dir folgen.";
			Link.l1 = "Gut. Warte hier auf mich.";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "Vorbei? Du machst wohl Witze!";
    			Link.l1 = "Ich meine es ernst.";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "Gut dann. Wir hatten heute sowieso gute Geschäfte.";
    			Link.l1 = "Richtig!";
    			Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = "Du Bastard! Du kannst uns nicht so einfach täuschen! Du wirst es mit deinem eigenen Kopf bezahlen!";
					Link.l1 = "Bezweifle es!";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "Du wirst damit nicht davonkommen!";
					Link.l1 = "Geh woanders bellen, ihr Hunde!";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "Das wirst du bereuen!";
				Link.l1 = "Du redest zu viel.";
				Link.l1.go = "Exit_cancel";			
			}	
		break;

		case "GenQuestKillContraband_1":
			//счетчик подстав по "метро"...
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //репу контры вниз
			}
			dialog.Text = "Du wirst dafür bezahlen!";
			Link.l1 = "Dann seid ihr alle tot. Ich habe einen klaren Befehl - euch alle zu eliminieren, wenn ihr Widerstand leistet.";
			Link.l1.go = "Exit_fight";
		break;
		
		case "Exit_Cancel":
            DeleteAttribute(Pchar, "quest.Contraband");
            CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;
		
		case "Exit_fight":
            DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");			

			AddSimpleRumourCity("Heard the latest news? The local smugglers were rounded up by a patrol not long ago. And you know what? Captain who had a deal with them escaped!" +
				"He had dashing lads in his crew and the whole patrol was killed. And our local smugglers just vanished. There was nothing found on the shore. No goods, no stash and smugglers. See, how they do their business here!", Pchar.quest.contraband.City, 3, 5, "");	

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Finish_exit":
            // таможня на суше
            if(GetSummonSkillFromName(pchar, "Sneak") < Rand(120))
			{
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i=1; i<=3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
				}
			}
			AddCharacterExpToSkill(Pchar, "Sneak", 100);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
            OfficersReaction("bad");
            ChangeCharacterComplexReputation(pchar,"nobility", -1);
            
            CloseQuestHeader("Gen_Contraband");
            
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
	
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		break;

		case "Exchange":
			// сама торговля -->
            if(FindContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = "Und was machst du hier? Du hast nichts zu verkaufen! Jede Ware in deiner Fracht kann in der Stadt verkauft werden!";
				Link.l1 = "Kein Glück dieses Mal.";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
                {
                    if(hrand(11) == 3)
                    {
        				dialog.Text = "Ich sehe.. Wissen Sie, wir nehmen Ihre Waren kostenlos. Ich bezweifle, dass Sie sich sowieso beschweren können.";
        				Link.l1 = "Versuch es, Abschaum!";
        				Link.l1.go = "Exit_fight";
                        break;
        			}
        			// море и солдаты на суше НЕЗАВИСИМЫ!!!
        			if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
        			{
                        SetCoastalGuardPursuit();
        			}
        			// при убегании от патруля на карту - корабли трем
        			SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// если в порту сидим, спим, то 2 день
        			
                    Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
        			Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
    			}
    			// установим окружение <--
				dialog.text = "Gut, lass uns sehen, was du hast.";										  
				Link.l1 = "Zeig uns, was du hast.";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "Ich habe meine Meinung geändert.";
    				Link.l99.go = "Cancellation";
				}				
            }
		break;
		
		case "Exchange1":
			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;		 
			DialogExit();
			// belamour legendary edition опасный груз
			pchar.GenQuest.Smugglerzpq = npchar.id;
			
			LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId),  sti(pchar.FindContrabandGoods.StoreIdx));	
		break;				
		// belamour legendary edition опасный груз -->
		case "SmugglerZPQ":
			dialog.text = "Guter Handel, Kapitän! Wenn es noch andere interessante Produkte gibt - kontaktieren Sie uns!";										  
			Link.l1 = "Ich stimme zu, ich bin auch zufrieden mit unserem Handel. Ach, wenn ich nur alle Waren zu einem solch guten Preis kaufen könnte...";
			Link.l1.go = "SmugglerZPQ_1"; 
		break;

		case "SmugglerZPQ_1":
			dialog.text = "Warum sollten wir gewöhnliche Waren zu solchen Preisen kaufen, wenn sie legal in einem Geschäft erworben werden können? Aber lass dich nicht entmutigen: Tatsächlich kann jedes Produkt verkauft werden, sogar gewöhnliches Schießpulver! Du könntest zu einem astronomischen Preis verkaufen, man muss nur den Ort kennen.";										  
			Link.l1 = "Los geht's. Wer wird Schießpulver zu einem astronomischen Preis kaufen?";
			Link.l1.go = "SmugglerZPQ_2"; 
		break;
		
		case "SmugglerZPQ_2":
			dialog.text = "Nun, das ist es, was ich dir gesagt habe, hehe ... Obwohl ... Du weißt, es gibt wirklich eine solche Möglichkeit, Schießpulver für ein Vermögen zu verkaufen, aber dieses Geschäft scheint uns immer noch nicht, dafür musst du einen ziemlich guten Ruf haben, und wir, wie du verstehst, sind keine Adligen.";										  
			Link.l1 = "Nun, vielleicht kann ich es mir ansehen. Ich kann gut und freundlich sein, wenn es nötig ist. Können Sie mir von dem Deal erzählen?";
			Link.l1.go = "SmugglerZPQ_3"; 
		break;
		
		case "SmugglerZPQ_3":
			dialog.text = "Alles kostet Geld in dieser Welt, Kapitän, sogar Informationen. Ich würde sogar sagen, besonders Informationen. Ich schlage vor: Ich gebe Ihnen diesen Tipp für einen symbolischen Betrag von ... sagen wir fünftausend Pesos. Wird das Ihnen passen?";										  
			Link.l1 = "Fünftausend Pesos für zweifelhafte Informationen bezahlen, wo man Schießpulver zu einem hohen Preis verkaufen kann? Nein, ich denke, ich kann irgendwie ohne diesen Tipp leben.";
			Link.l1.go = "SmugglerZPQ_NM"; 
			if(sti(pchar.money) > 4999)
			{
				Link.l2 = "Ich denke, ich kann bei diesem Deal mehr als nur fünftausend machen. Gut dann, ich stimme zu.";
				Link.l2.go = "SmugglerZPQ_4";
			}
		break;	
		
		case "SmugglerZPQ_NM":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "Es liegt an dir, Kapitän. Auf jeden Fall hatten wir einen guten Handel. Viel Glück... und laufe nicht in eine Patrouille hinein!";										  
			Link.l1 = "Auch du. Auf Wiedersehen.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_4":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Ausgezeichnet, Kapitän! Sie sind ein erstaunlicher Kunde, das wissen Sie. Also hören Sie. Mir wurde ins Ohr geflüstert, dass es in einigen der spanischen Städte in Maine ein Problem mit Schießpulver gibt. Ob es nun tropische Schauer sind oder etwas anderes - im Allgemeinen gibt es in dem Fort, das die Kolonie bewacht, nur sehr wenige Reserven. Und der Kommandant dieses Forts sucht jemanden, der ihm in dieser schwierigen Situation helfen könnte.\nEs gibt nur zwei Probleme: Erstens, das ist eine heikle Angelegenheit, und der Kommandant wird nicht mit irgendwelchen Gaunern darüber sprechen, und zweitens, wir sprechen von einer sehr großen Partie - nicht jedes Schiff wird so viel Schießpulver passen, so dass Sie möglicherweise eine Flotte benötigen. Auch nicht jeder Kapitän wird zustimmen, sein Schiff in eine schwimmende Bombe zu verwandeln, die leicht eine ganze Insel zerstören kann, wenn sie von einer verirrten Kanonenkugel getroffen wird.";
			if(CheckAttribute(pchar,"questTemp.zpq"))
			{
				Link.l1 = "Entschuldigung, aber ich weiß bereits von diesem Handel. Jedenfalls ist der Handel mehr wert als Geld, daher verdienst du fünftausend.";
				Link.l1.go = "SmugglerZPQ_5"; 
			}
			else
			{
				Link.l1 = "Wertvolle Informationen, danke. Wenn ich auf Maine bin, werde ich die örtlichen Kommandanten der Forts nach ihren Missgeschicken fragen. Und irgendwie hoffe ich, dass ich mit diesen Problemen umgehen oder sie missbrauchen werde, he-he.";
				Link.l1.go = "SmugglerZPQ_6"; 
			}
		break;
		
		case "SmugglerZPQ_5":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "So läuft das. Auf jeden Fall hatten wir einen guten Handel. Viel Glück... und lauf nicht in eine Patrouille!";										  
			Link.l1 = "Auch du. Auf Wiedersehen.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_6":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			AddQuestRecord("zpq", "0");
			dialog.text = "So passiert es. Auf jeden Fall hatten wir einen guten Handel. Viel Glück... und lauf nicht in eine Patrouille!";										  
			Link.l1 = "Du auch. Auf Wiedersehen.";
			Link.l1.go = "exit"; 
		break;
		// <-- legendary edition опасный груз
	}
}
