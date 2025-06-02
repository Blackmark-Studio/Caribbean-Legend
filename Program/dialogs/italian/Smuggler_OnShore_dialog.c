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
					dialog.text = NPCStringReactionRepeat("Non ti è stato detto di non venire qui su una nave così evidente! Perché non porti un paio di vascelli da guerra? Vattene e torna su una nave più piccola.","Vattene! O ti consegneremo noi stessi alla pattuglia.","Vai alla tua barca e scappa.","Così stanco di te...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Va bene, va bene sto per cambiare la mia nave.","Calmati, sono in cammino.","Maledizione, pensavo che avrebbe funzionato...","Sì, sono davvero testardo!",npchar,Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("Ehi, cosa stai facendo qui, "+GetSexPhrase("amico","ragazza")+"?",RandSwear()+"Qual è il tuo affare qui?!");
				Link.l1 = "Rilassati, compagno, facciamo affari!";
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
					Link.l2 = "Sono qui per ordine del governatore di "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"! Depone le tue armi e seguimi, sei arrestato!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("Ah, finalmente! Ti stavamo aspettando. Andiamo, è ora di salpare.","Facciamolo in fretta. Ci sono pattuglie dappertutto. Dobbiamo scappare da qui!");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "Sono qui per ordine del governatore di "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"! Abbassate le vostre armi e seguitemi, siete arrestati!";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "E chi sei tu? Stavamo parlando di un solo passeggero!";
						Link.l1 = "Ops..";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("Chi sei tu? Stavamo aspettando un passeggero, non un capitano.","Sparisci! Non tornare finché non ti liberi della tua nave.");
						Link.l1 = "Cavolo!";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
						    dialog.Text = "Cazzo, pattuglia! Non ci conosciamo e tu non ci conosci.";
							Link.l1 = "Bene...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("Grazie per il tuo aiuto. Non lo dimenticheremo. Naviguiamo ora.","Bene fatto! Buona lotta. Andiamo.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "Sono sulla mia strada.";
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
					    dialog.Text = RandSwear()+"Pattuglia! Non ci conosciamo e voi non ci conoscete.";
						Link.l1 = "Bene!";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "Vattene! Ti strappiamo le budella se rovini il nostro affare.";
						Link.l1 = RandPhraseSimple("Osi minacciarmi, canaglia!?","Ti soffocherai con le tue parole!");
						Link.l1.go = "Exit_fight";
						Link.l2 = "Non preoccuparti, so cosa sono gli affari. Ciao.";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "La porti sulla tua schiena? Dove si trova la tua nave?";
			Link.l1 = RandPhraseSimple("Prima, vorrei vedere se c'è qualche tranello in esso.","Non volevo rischiare la nave. Preferisco vedere tutto con i miei propri occhi.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "L'affare è finito!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "Siamo uomini onesti e non ti trufferemo. Porta la tua nave qui, basta non far seguire le pattuglie.";
			Link.l1 = "Bene. Aspettami qui.";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "Finito? Probabilmente mi stai prendendo in giro!";
    			Link.l1 = "Sono serio.";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "Bene allora. Abbiamo fatto buoni affari oggi comunque.";
    			Link.l1 = "Corretto!";
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
					dialog.Text = "Maledetto! Non puoi prenderci in giro così facilmente! Pagherai con la tua stessa testa!";
					Link.l1 = "Dubitaci!";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "Non te la caverai!";
					Link.l1 = "Andate ad abbaiare altrove, cani!";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "Te ne pentirai!";
				Link.l1 = "Parli troppo.";
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
			dialog.Text = "Risponderai per questo!";
			Link.l1 = "Allora siete tutti morti. Ho un ordine chiaro - eliminare tutti voi se vi opporrete.";
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
				dialog.Text = "E cosa ci fai qui? Non hai niente da vendere! Ogni bene nel tuo carico può essere venduto in città!";
				Link.l1 = "Nessuna fortuna questa volta.";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
                {
                    if(hrand(11) == 3)
                    {
        				dialog.Text = "Capisco.. Sai, prenderemo la tua merce gratis. Dubito che sarai in grado di lamentarti comunque.";
        				Link.l1 = "Provaci, feccia!";
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
				dialog.text = "Bene, vediamo cosa hai.";										  
				Link.l1 = "Mostraci cosa hai.";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "Ho cambiato idea.";
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
			dialog.text = "Buon affare, capitano! Se ci sono altri prodotti interessanti - contattaci!";										  
			Link.l1 = "Sono d'accordo, sono anche soddisfatto del nostro commercio. Ah, se solo potessi comprare tutte le merci a un prezzo così buono...";
			Link.l1.go = "SmugglerZPQ_1"; 
		break;

		case "SmugglerZPQ_1":
			dialog.text = "Perché dobbiamo comprare beni ordinari a questi prezzi, se possono essere acquistati legalmente in un negozio? Ma non scoraggiarti: in realtà, qualsiasi prodotto può essere venduto, persino la polvere da sparo comune! Potresti vendere a un prezzo altissimo, basta conoscere il posto.";										  
			Link.l1 = "Andiamo. Chi comprerà la polvere da sparo a un prezzo altissimo?";
			Link.l1.go = "SmugglerZPQ_2"; 
		break;
		
		case "SmugglerZPQ_2":
			dialog.text = "Ebbene, è quello che ti ho detto, hehe... Anche se... Sai, c'è davvero una possibilità di vendere la polvere da sparo per una fortuna, ma questo affare non ci sorride ancora, per questo devi avere una buona reputazione, e noi, come capisci, non siamo nobili.";										  
			Link.l1 = "Ebbene, forse posso controllarlo. Posso essere buono e gentile quando serve. Puoi dirmi qualcosa sull'affare?";
			Link.l1.go = "SmugglerZPQ_3"; 
		break;
		
		case "SmugglerZPQ_3":
			dialog.text = "Tutto costa soldi in questo mondo, capitano, anche le informazioni. Direi addirittura, soprattutto le informazioni. Propongo questo: ti darò questo consiglio per una somma simbolica di ... diciamo cinquemila pesos. Ti va bene?";										  
			Link.l1 = "Pagare cinquemila pesos per informazioni dubbie su dove poter vendere la polvere da sparo a un prezzo alto? No, penso di poter vivere in qualche modo senza questo consiglio.";
			Link.l1.go = "SmugglerZPQ_NM"; 
			if(sti(pchar.money) > 4999)
			{
				Link.l2 = "Credo di poter fare più di cinquemila su questo affare. Bene, allora accetto.";
				Link.l2.go = "SmugglerZPQ_4";
			}
		break;	
		
		case "SmugglerZPQ_NM":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "Sta a te, capitano. In ogni caso, abbiamo fatto un buon affare. Buona fortuna... e non incappare in una pattuglia!";										  
			Link.l1 = "Anche tu. Addio.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_4":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Eccellente, capitano! Sei un cliente straordinario, lo sai. Allora ascolta. Mi è stato sussurrato all'orecchio che in alcune delle città spagnole sul Maine c'è un problema con la polvere da sparo. Che siano piogge tropicali, o qualcos'altro - in generale, nel forte che protegge la colonia, ci sono pochissime riserve. E il comandante di questo forte sta cercando qualcuno che possa aiutarlo in questa difficile situazione.\nCi sono solo due problemi: primo, è una questione delicata, e il comandante non ne parlerà con qualsiasi canaglia, e in secondo luogo, stiamo parlando di un lotto molto grande - non ogni nave riuscirà ad adattarsi a così tanta polvere da sparo, quindi potrebbe essere necessaria una flotta. Inoltre non ogni capitano accetterà di trasformare il suo vascello in una bomba galleggiante che potrebbe facilmente distruggere un'intera isola se viene colpita da un colpo di cannone vagante.";
			if(CheckAttribute(pchar,"questTemp.zpq"))
			{
				Link.l1 = "Mi dispiace, ma so già di questo affare. Comunque, l'affare vale più del denaro, quindi meriti cinquemila.";
				Link.l1.go = "SmugglerZPQ_5"; 
			}
			else
			{
				Link.l1 = "Informazioni preziose, grazie. Se mi trovo nel Maine, chiederò ai comandanti locali dei forti dei loro malanni. E in qualche modo spero di affrontare questi problemi o di approfittarne, he-he.";
				Link.l1.go = "SmugglerZPQ_6"; 
			}
		break;
		
		case "SmugglerZPQ_5":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "Ecco come succede. In ogni caso, abbiamo fatto un buon affare. Buona fortuna... e non incappare in una pattuglia!";										  
			Link.l1 = "Anche tu. Addio.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_6":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			AddQuestRecord("zpq", "0");
			dialog.text = "Ecco come succede. In ogni caso, abbiamo fatto un buon affare. Buona fortuna... e non incappare in una pattuglia!";										  
			Link.l1 = "Anche a te. Addio.";
			Link.l1.go = "exit"; 
		break;
		// <-- legendary edition опасный груз
	}
}
