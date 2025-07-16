// Диего де Монтойя
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "C'è qualcosa che desideri?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "patrol":
			dialog.text = TimeGreeting()+", "+GetFullName(npchar)+", Capo della ronda di San Jose. Abbiamo ricevuto notizia di movimenti sospetti nei dintorni di questa città. Saresti così gentile da spiegarci chi sei e cosa stai tramando?";
			link.l1 = "Capitano "+GetFullName(pchar)+", signor ufficiale. Sono qui per ordine e sotto istruzioni dirette dell’Inquisitore Padre Vincento. Ecco un documento che attesta la mia autorizzazione.";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "D’accordo... Tutto sembra in ordine. È compilato per bene, con tanto di firma dell’inquisitore. Perdona i miei sospetti. Che diavolo ci fai al faro?";
			link.l1 = "Non sono autorizzato a rispondere a domande simili. Se davvero ti preme conoscere lo scopo del mio incarico per l’inquisitore, ti consiglio di rivolgerti direttamente a lui a Santiago per chiarimenti. Sei un ufficiale, avrai certo dimestichezza con segreti militari e affini. L’unica cosa che posso rivelarti è che sto indagando sulle circostanze di un naufragio spagnolo.";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "Chiedo ancora venia, Monsieur. Non oso più trattenerla... ah, un attimo! Ho appena intravisto il bagliore di una lama, o è solo la mia fantasia? Che pugnale curioso avete! Me lo mostrate, per favore?";
			link.l1 = "Assicurati di restituirlo, non scordartelo. Per me è davvero importante.";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "Dio mio! Riconosco questo pugnale, l’ho visto illustrato in uno dei libri della biblioteca! È il pugnale di Cortés in persona! Qui c’è persino il suo marchio... Signore, la prego, non mi dica di no. Mi lasci avere questo pugnale! Colleziono armi antiche e personalizzate e questa è davvero una meraviglia. La pagherò a peso d’oro.";
			link.l1 = "Señor, questo pugnale non è in vendita. L’ho ricevuto in dono e non ho nessuna intenzione di sbarazzarmene con chiunque. Restituiscilo, per cortesia.";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "Neppure cinquecento dobloni d’oro ти fanno felice? È una fortuna, con quella somma ci compri una nave intera!";
			link.l1 = "No. Ho già una nave e quel pugnale è unico. Non lo vendo.";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "Eh, che peccato... Va bene, prendi il tuo tesoro. Non oso più disturbarti. Buona fortuna!";
			link.l1 = "Tutto il meglio, capitano.";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("Voice\English\Sharlie\Diego De Montoya.wav");
			dialog.text = "Basta! Voglio parlargli di persona...";
			link.l1 = "Dunque, vedo proprio davanti a me il famoso Diego de Montoya... Ma perdona la mia sfacciataggine, señor. Ci siamo già incontrati, vero? Ah sì, esatto. A Trinidad, al faro del porto. Ma lì, se non erro, usavi un nome diverso...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "La vostra memoria vi è fedele, signore. Ma non siete l’unico a saper tessere intrighi e scatenare guerre nell’ombra. So bene del vostro ardente desiderio di vedermi. Ebbene, pare che il vostro desiderio sia stato esaudito.";
			link.l1 = "Non era proprio questo il tipo d’incontro che speravo, señor.";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "Ebbene, le cose stanno così. Ma ti concederò una possibilità di uscirne vivo, se mi consegni il tuo pugnale.";
			link.l1 = "La tua passione per le rarità ti ha davvero portato così in basso, caballero, da dovermi tendere una trappola tanto raffinata?   Oh, non credo proprio. È forse il Guardiano della Verità che ti tiene al guinzaglio, o sono lontano dalla verità?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "Non ho la minima idea di che diavolo tu stia blaterando. Il pugnale deve tornare dove gli spetta, e questo è tutto quel che ti serve sapere. Non l’hai voluto cedere per l’oro, quindi adesso lo cederai per la tua pellaccia.";
			link.l1 = "Davvero credi, señor, che io mi beva le tue storielle? Ormai hai già deciso che da questa baia non metto piede fuori, vero?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "E se ti dessi la mia parola?";
			link.l1 = "La parola per 'mangiarane'? Mh...";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Monsieur, ti offro un’ultima possibilità. O mi consegni la daga che mi interessa, oppure tra poco la prenderò dal tuo cadavere. Resistere è inutile, abbiamo un vantaggio schiacciante in uomini.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "Mi hai davvero sorpreso, señor, su questo non c’è dubbio. Davvero credi che sia uno sciocco testardo disposto a ficcare la testa nelle fauci di uno squalo senza prima afferrare il mio arpione? Ragazzi, uccideteli!";
			else link.l1 = "Il vero potere non sta nei numeri, ma nell’abilità, signore!";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
