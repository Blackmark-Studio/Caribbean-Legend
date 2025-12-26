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
				
				float fMaxClass = ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5);
				if (IsEquipCharacterByArtefact(pchar, "talisman21")) fMaxClass = 2.0;
				
				if (GetCompanionQuantity(pchar) > 1) iTmp = true;
				if (GetCharacterShipClass(pchar) < fMaxClass) iTmp = true;

				// поиск мин.  те старшего класса
				/* for (i=0; i<COMPANION_MAX; i++)
				{
					iChIdx = GetCompanionIndex(GetMainCharacter(), i);
					if (iChIdx>=0)
					{
						sld = GetCharacter(iChIdx);
            			if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
					}
				} */
				
				if (iTmp)
				{
					dialog.text = NPCStringReactionRepeat("Não te disseram para não aparecer aqui com um navio tão chamativo? Por que não traz logo dois navios de guerra? Cai fora e volta com um navio menor.","Fora daqui! Ou nós mesmos vamos te entregar para a patrulha.","Vá para o seu barco e vá embora.","Tão cansado de você...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Certo, certo, eu vou trocar de embarcação.","Fique calmo, estou a caminho.","Droga, achei que isso fosse funcionar...","Sim, eu sou realmente teimoso!",npchar,Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("Ei, o que você está fazendo aqui, "+GetSexPhrase("amigo","garota")+"?",RandSwear()+"O que você quer aqui?!");
				Link.l1 = "Relaxa, amigo, vamos negociar!";
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
					Link.l2 = "Estou aqui sob as ordens do governador de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+" Larguem as armas e venham comigo, vocês estão presos!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("Ah, finalmente! Estávamos esperando por você. Vamos, é hora de zarpar.","Vamos fazer isso rápido. Tem patrulhas por toda parte. Precisamos sair daqui!");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "Estou aqui por ordem do governador de "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"! Larguem suas armas e me sigam, vocês estão presos!";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "E quem é você? Estávamos falando de apenas um passageiro!";
						Link.l1 = "Opa..";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("Quem é você? Estávamos esperando um passageiro, não um capitão.","Cai fora! Só volte depois de se livrar do seu navio.");
						Link.l1 = "Merda!";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
						    dialog.Text = "Merda, patrulha! Nós não conhecemos você e você não conhece a gente.";
							Link.l1 = "Tudo bem...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("Muito obrigado pela sua ajuda. Não vamos esquecer isso. Vamos zarpar agora.","Muito bem! Lutou com coragem. Vamos em frente.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "Estou a caminho.";
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
					    dialog.Text = RandSwear()+"Patrulha! Nós não conhecemos você e você não conhece a gente.";
						Link.l1 = "Tá bom!";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "Cai fora! Vamos arrancar suas tripas se você atrapalhar nosso negócio.";
						Link.l1 = RandPhraseSimple("Você ousa me ameaçar, vira-lata!?","Você vai engasgar com suas próprias palavras!");
						Link.l1.go = "Exit_fight";
						Link.l2 = "Não se preocupe, eu entendo como os negócios funcionam. Tchau.";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "Você está carregando isso nas costas? Onde está seu navio?";
			Link.l1 = RandPhraseSimple("Primeiro, quero ver se não tem nenhuma pegadinha nisso.","Não quis arriscar o navio. Prefiro ver tudo com meus próprios olhos.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "O acordo acabou!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "Somos homens honestos e não vamos te enganar. Traga seu navio aqui, só não deixe as patrulhas te seguirem.";
			Link.l1 = "Tudo bem. Espere por mim aqui.";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "Acabou? Você só pode estar brincando!";
    			Link.l1 = "Estou falando sério.";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "Tudo bem então. De qualquer forma, tivemos bons negócios hoje.";
    			Link.l1 = "Certo!";
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
					dialog.Text = "Seu desgraçado! Você não vai nos enganar tão fácil assim! Vai pagar por isso com a própria cabeça!";
					Link.l1 = "Duvido!";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "Você não vai se safar dessa!";
					Link.l1 = "Vão latir em outro lugar, cães!";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "Você vai se arrepender disso!";
				Link.l1 = "Você fala demais.";
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
			dialog.Text = "Você vai pagar por isso!";
			Link.l1 = "Então vocês estão todos mortos. Recebi ordens claras — eliminar todos vocês se resistirem.";
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
				dialog.Text = "E o que você está fazendo aqui? Você não tem nada para vender! Tudo o que está no seu porão pode ser vendido na cidade!";
				Link.l1 = "Sem sorte desta vez.";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
                {
                    if(hrand(11) == 3)
                    {
        				dialog.Text = "Entendi... Sabe, vamos levar suas mercadorias de graça. Duvido que você consiga reclamar de qualquer jeito.";
        				Link.l1 = "Tenta a sorte, canalha!";
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
				dialog.text = "Certo, vamos ver o que você tem.";										  
				Link.l1 = "Mostre o que você tem.";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "Mudei de ideia.";
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
			dialog.text = "Bom negócio, capitão! Se tiver mais alguma mercadoria interessante, avise a gente!";										  
			Link.l1 = "Concordo, também estou satisfeito com a nossa negociação. Ah, se eu pudesse comprar todas as minhas mercadorias por um preço tão bom...";
			Link.l1.go = "SmugglerZPQ_1"; 
		break;

		case "SmugglerZPQ_1":
			dialog.text = "Por que deveríamos comprar mercadorias comuns por esses preços, se elas podem ser adquiridas legalmente em uma loja? Mas não desanime: na verdade, qualquer produto pode ser vendido, até mesmo pólvora comum! Você poderia vendê-la por um preço altíssimo — só precisa saber o lugar certo.";										  
			Link.l1 = "Qual é. Quem compraria pólvora por um preço tão absurdo?";
			Link.l1.go = "SmugglerZPQ_2"; 
		break;
		
		case "SmugglerZPQ_2":
			dialog.text = "Well, that's what I told you, hehe ... Although ... You know, there really is an opportunity to sell gunpowder for a fortune, but this deal still isn't for us; for that, you need to have a rather good reputation, and we, as you understand, are not nobles.";										  
			Link.l1 = "Bem, talvez eu possa dar uma olhada nisso. Sei ser bom e gentil quando é preciso. Pode me contar sobre o acordo?";
			Link.l1.go = "SmugglerZPQ_3"; 
		break;
		
		case "SmugglerZPQ_3":
			dialog.text = "Tudo custa dinheiro neste mundo, capitão, até mesmo informação. Eu diria até, principalmente informação. Proponho o seguinte: te dou essa dica por um valor simbólico de... digamos cinco mil pesos. Serve para você?";										  
			Link.l1 = "Pagar cinco mil pesos por uma informação duvidosa sobre onde posso vender pólvora por um bom preço? Não, acho que posso me virar sem essa dica.";
			Link.l1.go = "SmugglerZPQ_NM"; 
			if(sti(pchar.money) > 4999)
			{
				Link.l2 = "Acho que posso ganhar mais do que só cinco mil com esse negócio. Tudo bem, eu aceito.";
				Link.l2.go = "SmugglerZPQ_4";
			}
		break;	
		
		case "SmugglerZPQ_NM":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "Você decide, capitão. De qualquer forma, fizemos um bom negócio. Boa sorte... e cuidado para não topar com uma patrulha!";										  
			Link.l1 = "Você também. Adeus.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_4":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Excellent, captain! You are an exceptional customer, you know. So listen. I heard whispers that in some of the Spanish cities on the Main, there is a problem with gunpowder. Whether it's tropical downpours or something else – in short, the fort guarding the colony has very little in reserve. And the commandant of this fort is looking for someone who could help him in this difficult situation.\nThere are only two problems: first, this is a delicate matter, and the commandant will not discuss it with just any rogue; and secondly, we are talking about a very large shipment – not every ship can carry so much gunpowder, so you might need a fleet. Also, not every captain will agree to turn his vessel into a floating bomb that could easily destroy an entire island if struck by a stray cannonball.";
			if(CheckAttribute(pchar,"questTemp.zpq"))
			{
				Link.l1 = "Desculpe, mas eu já estou sabendo desse acordo. Ainda assim, ele vale mais do que dinheiro, então você merece cinco mil.";
				Link.l1.go = "SmugglerZPQ_5"; 
			}
			else
			{
				Link.l1 = "Informação valiosa, obrigado. Se eu estiver no Maine, vou perguntar aos comandantes locais dos fortes sobre seus infortúnios. E, de algum jeito, espero conseguir lidar com esses problemas ou tirar proveito deles, he-he.";
				Link.l1.go = "SmugglerZPQ_6"; 
			}
		break;
		
		case "SmugglerZPQ_5":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "É assim que é. De qualquer forma, fizemos um bom negócio. Boa sorte... e cuidado para não topar com uma patrulha!";										  
			Link.l1 = "Você também. Adeus.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_6":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			AddQuestRecord("zpq", "0");
			dialog.text = "É assim que é. De qualquer forma, fizemos um bom negócio. Boa sorte... e cuidado para não topar com uma patrulha!";										  
			Link.l1 = "Você também. Adeus.";
			Link.l1.go = "exit"; 
		break;
		// <-- legendary edition опасный груз
	}
}
