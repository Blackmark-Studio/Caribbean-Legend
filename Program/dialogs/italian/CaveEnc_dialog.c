// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Vuoi qualcosa?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("Whoa-ho, guarda chi è qui! Beh, oggi è il tuo giorno fortunato, compagno. Noi siamo bravi ragazzi, vedi, cuciniamo un po' di cibo e roba... Non ti sto invitando a cena con noi, ma dovresti sparire mentre ne hai ancora la possibilità.","Vattene adesso e non darci fastidio. Torna domani - e non dimenticare di portare con te la tua borsa, ah-ah-ah!","Non farmi arrabbiare, marinaio! Ti ricordi ancora dove si trova l'ingresso della grotta? Dovresti andarci ora, molto, molto velocemente...","Ebbene, ora hai oltrepassato il limite, amico! Immagino che dovrò distogliermi dai miei affari e occuparmi di te, stronzo!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Così gentile da parte tua, amico...","Vedo che sei proprio un buffone...","Bene, continua a friggere le tue frittelle, allora...","Ora stiamo parlando, ah-ah!",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Caspita, santo cielo! Non c'è bisogno di andare a caccia della preda - è già qui... Ehi, ragazzi - facciamo tremare questo sciocco, vero?","Nessuno ti ha invitato qui, amico... Ma è così bello che tu sia qui, comunque. Vediamo ora, proprio quanto è pesante la tua borsa!","Nessuno ti ha trascinato qui con la forza, he-he... Ma se sei già qui, suppongo che ti solleticheremo un po' per vedere cosa cade dalle tue tasche...");
				link.l1 = LinkRandPhrase("Ora ti accorcerò un po' la lingua...","Spero che le tue abilità con la spada siano all'altezza della tua arguzia, ciarlatano!","Ebbene, sembra che sia il momento di fare un paio di buchi in più nel tuo corpo deperibile...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("Oh, santo cielo! Non c'è bisogno di andare a caccia della preda - è già qui... Ehi, ragazzi - facciamo tremare questo dandy, lo facciamo?","Nessuno ti ha invitato qui, compagno... Ma è così bello che tu sia qui, comunque. Vediamo ora, quanto pesa la tua borsa!","Nessuno ti ha trascinato qui con la forza, he-he... Ma dato che sei già qui, suppongo che ti solletichiamo un po' per vedere cosa cade dalle tue tasche...");
			link.l1 = LinkRandPhrase("Ora accorcerò un po' la tua lingua...","Spero che le tue abilità con la spada siano all'altezza del tuo ingegno, chiacchierone!","Beh, sembra che sia il momento di fare un paio di fori in più nel tuo corpo deperibile...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("Sparisci, compagno. Non c'è nulla da fare per te qui!","Ehi, lo sto chiedendo in modo amichevole: vattene. Non si sa mai cosa può succedere...","Ultimo avvertimento: se non te ne vai subito, te ne pentirai di essere venuto qui.","Ecco fatto, amico, hai chiesto guai.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Non dirmi cosa fare, capito?","E cosa c'è di così speciale laggiù? Solo una grotta, niente di più...","Oh, dai ora...","Ha! Beh, vediamo chi è il migliore, verme!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("Viso pallido vada via. Lui è felice che "+npchar.name+"  gentile. Gli dei hanno pietà di te oggi.","Esci dalla mia grotta, prima che io e i miei fratelli ci arrabbiamo!","Vattene, cane dal viso pallido!","La tua fortuna e la tua vita sono finite, cane bianco!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Beh, grazie, amico, molto gentile da parte tua...","Questa grotta non è tua, e vado dove voglio.","Abbassa un po', creatura delle paludi.","Ora farò ingoiare queste parole, bestia...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Maledetto viso pallido è arrivato al nostro falò! Evviva! Sei finito!","Stupido viso pallido è venuto nella tana del giaguaro. Friggerò il tuo fegato!","Impudente viso pallido osa venire nella mia grotta? Allora non ne uscirà mai vivo!");
				link.l1 = LinkRandPhrase("Ora strapperò la tua lingua...","Ora il mondo avrà diversi cannibali in meno...","Ebbene, sembra che sia il momento di fare un paio di fori in più nel tuo corpo deperibile, tu scimmia dalla faccia rossa.");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("Un viso pallido disgustoso è venuto nella nostra grotta! Whe-hee! Ti taglierò la lingua e la friggerò!","Stupido viso pallido è arrivato nella tana del giaguaro. Fratelli, tagliate questo maledetto cane bianco!","Insolente viso pallido osa venire nella mia caverna? Allora non ne uscirà mai vivo!");
			link.l1 = LinkRandPhrase("Ti taglierò quella maledetta testa...","Ora il mondo avrà diversi cannibali in meno...","Ebbene, preparati a incontrare i tuoi antenati, pelle-rossa. All'inferno con te!");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
