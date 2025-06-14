// диалог прочих НПС по квесту Саги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Desideri qualcosa?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "Cosa vuoi? Non vedi che sono in lutto! Sparisci prima che ti butti giù per le scale!";
			link.l1 = "Beh, comprati una casa più grande con le scale, allora. Poi ne riparleremo di buttar giù la gente dalle scale, eroe...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "Perché sei così agitato, Jimmy? Che io resti senza rum fino alla fine dei miei giorni, se non c'entra una bella donna! Solo una donna potrebbe far minacciare ai vecchi amici un vecchio lupo di mare come te...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "Odio i pedanti come te! Prendete sempre la fetta migliore della torta. Non mi hanno lasciato far fuori quell’impertinente, quindi sfogherò la mia rabbia su di te!";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_KillJimmy");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Jimmy_1_2":
			dialog.text = "Eh?! Ti conosco, io? Non mi ricordo di te, maledizione...";
			link.l1 = "Sono io, "+pchar.name+"! Ci siamo divertiti a Blueweld dopo che hai quasi sventrato quel tizio insolente col cappotto. Come si chiamava, già? Me lo sono scordato... Comunque, dei cannoni della sua corvetta non me ne importa un accidente se mai lo incrocio in mare!";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "Si chiamava Arthur! Arthur Donovan, capitano della corvetta 'Arbutus'! Maledetto farabutto! Quindi ammetti che per un pelo non l’ho mandato dritto all’inferno?";
			link.l1 = "Ma certo! Non aveva nessuna speranza, ma i tuoi compari ci hanno messo lo zampino. Perdonali, non volevano che finissi impiccato per l'omicidio d'un ufficiale di marina.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "Argh! Se solo avessi una nave! Quel bastardo si fa trovare facile vicino ad Antigua... ah! Ti sarò debitore se lo mandi a dormire coi pesci!";
			link.l1 = "Affare fatto, ah-ah! Ma dimmi, la Rumba vale davvero tutte queste pene?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "Per tutti i santi! Non ho mai incontrato nessuna migliore di lei. Ma lei si fa solo beffe di me. Tutti vogliono quella sirena. Alcuni marinai mi hanno confessato che il nostro Giacobbe cerca una ragazza che somiglia proprio alla mia Rumba. Anche lui la desidera! Come faccio ora a seguire i suoi ordini?";
			link.l1 = "Zitto, compare! Le pareti hanno orecchie... E secondo te perché Jackman va a caccia di Rumba?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "Lo è di sicuro! Sta cercando un certo Henry il Boia e una fanciulla di vent’anni, con i capelli biondi e gli occhi azzurri. Una certa Gladys Chandler di Belize dovrebbe essere la sua tutrice.";
			link.l1 = "Aspetta! Gladys ha un cognome diverso. Eppure è sua madre!";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "Jackman è furbo! Non lo cogli mai alla sprovvista! È da un po' che faccio la corte a Rumba e ho scoperto che Gladys s’è sposata con Sean McArthur esattamente vent’anni fa. Prima di allora, abitava a Belize. Il suo primo marito si chiamava Pete Chandler.\nPovero Pete, finì ammazzato in una rissa da bettola. Si mormora che sia stato lo stesso McArthur a mandarlo all’altro mondo, ché già sbavava dietro la rotondetta Gladys. Così lei rimase vedova, con una creatura tra le braccia. Ma il piccolo non sopravvisse a suo padre e poco dopo lo portò via la febbre.\nE guarda caso, solo un paio di mesi dopo, Gladys e Sean si presentarono a Blueweld con una ragazzina, spacciata per figlia di McArthur. Ora dimmi tu: come avrebbe potuto Gladys sfornare un’altra creatura in così poco tempo? Mi segui?";
			link.l1 = "L'hai detto a qualcun altro di questa faccenda?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "Non ancora. Tieni la bocca chiusa o... beh, mi conosci!";
			link.l1 = "Sì, lo so. Hai una lingua marcia che spiffera ogni segreto a chiunque. Rumba ha fatto bene a sbatterti fuori, lingua lunga...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "Certo! Bocca cucita, puoi contarci! Ma adesso devo andarmene. Addio, Jimmy.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "Cosa... cosa hai detto?!";
			link.l1 = "Non potrai raccontarlo a nessun altro...";
			link.l1.go = "Jimmy_fight";
			pchar.questTemp.Saga.Jimmysecret = "true";
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			pchar.questTemp.Saga = "jackman";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "4_1");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("Voice\English\saga\Artur Donovan.wav");
			dialog.text = "Argh, maledetto bastardo!";
			link.l1 = "Parli da solo, signore?! Dov’è Rumba?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "Quale Rumba? Non voglio canaglie con nomignoli sulla mia nave. Questa è una nave della marina inglese!";
			link.l1 = "Non fare il fesso con me, Donovan. Sai benissimo di кого sto parlando. Dov’è la ragazza? Dov’è Helen? Rispondimi, lurido bastardo...";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "Hélène? Non ci sono sgualdrine di terra sulla mia nave, figlio di puttana!";
			link.l1 = "Niente sgualdrine di terra? Difficile da credere, visto che una mi sta proprio davanti in questo momento... Immagino che non abbia senso continuare questa chiacchierata. Crepa, verme miserabile!";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "Capitano, abbiamo perquisito tutte le cabine e la stiva come ci avete ordinato. Abbiamo trovato una ragazza incatenata nella stiva...";
			link.l1 = "Che mascalzone! Proprio come immaginavo... Hai già liberato la ragazza?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Certo, Capitano. È stata portata sana e salva a bordo della vostra nave.";
			link.l1 = "Ben fatto! Portala nei miei alloggi, voglio parlarle appena avremo finito qui.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Ai vostri ordini, Capitano!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "Che ti serve?";
			link.l1 = "Salute, boia! Il capitano Butcher ti manda i suoi omaggi.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "Il mio nome è Charles de Maure. Cerco Enrique, il figlio della señora Gonzales, per conto di una sua vecchia amica. Credo che tu sia lui...";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "Che diavolo! Non conosco nessun Macellaio!";
			link.l1 = "Avanti, Henry. Dimmi perché i pirati di Jackman ti stanno dando la caccia e prometto che non ti farò del male.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = " Aiuto! Pirati! Assassinii! ";
			link.l1 = "Taci, imbecille! Mezzo villaggio verrà qui per via delle tue urla. Ah, è questo che vuoi?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = " Mh... Signore, dev’esserci un errore. Sono cresciuta in una famiglia straniera, non ricordo mia madre naturale. Porto il cognome di chi si prese cura di me. Non conosco il nome di mia madre, ma dubito fosse Gonzales. Potete chiedere di me in città, qualunque vecchio abitante vi confermerà le mie parole. Il mio patrigno era uomo noto, non aveva figli, così questa casa è passata a me e...";
			link.l1 = "Mi rincresce. Pare che mi sia sbagliato. Addio.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesA_3_1":
			dialog.text = "Non credo proprio.";
			link.l1 = "Come, scusa?";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "Sai, di recente la nostra colonia è stata assalita ferocemente da una banda di pirati. Immagino che tu ne abbia sentito parlare? Dopo quell’attacco, una marea di gente ha patito le pene dell’inferno. Io ne sono uscito illeso, ma la mia attività di famiglia sta ora affondando come una galea bucata. E il responsabile di tutta questa sciagura è il capo di quei canaglie, un furfante di nome Charlie Prince.";
			link.l1 = "Mi dispiace assai, ma che c'entra tutto ciò con la mia persona?";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "Ah-ah, guarda un po’ che agnellino innocente! Ti propongo di coprire le mie perdite, visto che sei tu il responsabile. Mi accontenterò di quindicimila pesos. E farò finta che tu non sia mai entrato nella mia casa.";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "Quanto siete tutti rancorosi... Ecco i tuoi soldi. E ricorda: se qualcuno scopre che sono stato in questa città, tornerò a cercarti.";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "Quindicimila? Mh... Non credo che la tua vita valga tanto. Direi che più conveniente sia farti fuori subito, così non vai a spifferar nulla in giro.";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "Guardie! Pirati! Assassinio!";
			link.l1 = "Taci, idiota!";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// <-- участвовал в событиях Картахены
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("Voice\English\citizen\Pirati v Gorode-08.wav");
			dialog.text = "Vedo che ti piace la mia sciabola. Te la posso vendere, se vuoi. Non ti chiederò molto, sto morendo dalla voglia di bere un po’ di rum e le mie tasche sono vuote.";
			link.l1 = "E perché diamine dovrei averne bisogno? Il Diavolo della Foresta mi ha detto di porgerti i suoi saluti.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Ebbene sì. Hai proprio una bella sciabola, davvero. Quanto chiedi?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "Avrebbe fatto meglio a darmi un paio di centinaia di pesos, dannazione!";
			link.l1 = "Allora conosci Svenson?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "Va’ al diavolo tu e quel tuo Svenson, che se ne vada pure all’inferno, sia quello della foresta o quello del mare, non me ne frega un accidente. Se non vuoi aiutare un poveraccio comprando il suo sciabola, allora te la ficco io per niente dritto nel culo.";
			link.l1 = "Ah sì? Vediamo come pensi di farlo, faccia di merda!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "Vedo che sei un uomo di mondo! Mille pesos ed è tutto tuo.";
			link.l1 = "Affare fatto!";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Ci sono soltanto due sciabole così a Cartagena: la mia e quella del vecchio Alvares del faro. Ma la sua non la venderà mai. Ipocrita che è, sento l’odore di vecchio bucaniere a leghe di distanza. Quella lama per lui è come un amuleto.\nPare che il poveraccio si struggia per cose che vorrebbe scordare. Forse è per questo che ogni mese va a messa, per quei peccati che non gli danno pace la notte.";
			link.l1 = "E vedo che anche tu hai qualche storia alle spalle. Devi essere tu quello di cui parlava Svenson. Mi ha detto di porgerti i suoi migliori saluti, se mai ti avessi incontrato a Cartagena.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "Svenson? Mai sentito nominare. Mi chiamo Enrique Gallardo. Ma se il tuo Svenson ha una bottiglia di rum per me, posso anche diventare Henry per lui. Chiamami come ti pare, basta che non mi chiami tardi a cena. Allora, si parte?";
			link.l1 = "Oggi no. Svenson è lontano, ma la taverna è proprio qui vicino. Le tue tasche non sono più vuote, quindi stai in campana, Enrique.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesB_3_1":
			dialog.text = "Non sono ancora del tutto colmi. Ne voglio di più. E toccherà a te pagare, maledetto.";
			link.l1 = "Sono confuso... Non tieni alla tua pellaccia? Vuoi rapinarmi in piena città? E questo dopo che tu stesso mi hai appena venduto l’arma?";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "No, mi pagherai di tasca tua. E sai perché?";
			link.l1 = "Curioso di sentire.";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "Ti ho riconosciuto. Ero nelle segrete per una rissa ubriaca in taverna quando la tua ciurma ha fatto irruzione nella prigione e ha fatto fuori tutte le guardie. Sono riuscito ad arrivare al cadavere di una guardia con le chiavi e mi sono fiondato in strada. La città era in fiamme, cadaveri, sangue e fumo di polvere da sparo ovunque... Proprio come durante un abbordaggio! E attraverso quel fumo ti ho visto uscire dalla residenza del governatore. Poetico, no? Yo-ho-ho, saluti, Principe Charlie!";
			link.l1 = "Smettila di strillare così! Con quello che sai, sei proprio tu che non dovresti provare a spillarmi quattrini. Hai idea di cosa potrei farti?";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "In mezzo alla città che hai già depredato una volta? Non puoi farci nulla, sei nelle mie mani. Dunque, per concludere... facciamo così: tu mi consegni subito... diciamo, diecimila pesos. Dovrebbe bastare per un mese. E poi te ne vai per la tua strada! Da quell’Henry che tanto ami, da Svenson, o dritto all’inferno, se ti garba... Ma se non accetti, basta che io urli una sola volta, e ti trascineranno in una stanzetta speciale che ho già fatto allestire, piena zeppa di ferri da tortura.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Maledizione, prendi i tuoi diecimila e sparisci dalla mia vista! E che il cielo mi scampi dal rivederti ancora.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Basta, ne ho le tasche piene di tutto questo. L’arma è mia, quindi non hai alcuna speranza, canaglia.";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "Ahah, sei in gamba! Sai che ti dico? Chiunque altro l’avrei già sventrato dalla pancia alla gola. Ma di gente come te ho proprio bisogno. Facciamo così: ti do diecimila pesos, ti restituisco il tuo ‘Impiccato’ e ci aggiungo tremila ogni mese – dovrebbero bastare per l’acquavite – e tu diventi un mio compagno di bordo.";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "Va bene, va bene, me ne vado già! Buona fortuna con la tua caccia, Principe Charlie!";
			link.l1 = "...";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "Guardie! Guardie!!! È il Principe Charlie!!!";
			link.l1 = "Maledetto farabutto!";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "Mi stai forse chiedendo d’imbarcarmi con la tua ciurma?";
			link.l1 = "Esatto. Ma questa è un’offerta che capita una sola volta. Allora, che ne dici? Accetti, o ti faccio fuori come un cane. Non penserai davvero di poter ricattare il buon vecchio Charlie Prince così facilmente, vero?";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				dialog.text = "Diavolo! Il principe Charlie in persona mi invita a salire a bordo della sua ciurma! Dannato sia, accetto! Ridammi la mia lama e diecimila pesos. Non avrei mai immaginato che la faccenda avrebbe preso questa piega!";
				link.l1 = "Ecco. E tieni la bocca chiusa: nessuno in questa città deve sapere chi sono, capito?";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				dialog.text = "No. Sarai anche un capitano di valore, ma a me pare che tu abbia il bastone troppo su per il culo. Sì, una volta hai insegnato paura agli spagnoli, con quel colpo azzardato a Cartagena — ma tutto solo grazie a Marcus Tyrex. Da solo non hai il fegato per un saccheggio come si deve. Quindi, sgancia la grana!";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = "No. Sei senz'altro un pirata di mala fama, ma come capitano non fai gran figura. Sei riuscito a saccheggiare la colonia solo grazie a Marcus Tyrex – da solo non avresti avuto il fegato nemmeno d’abbordare una goletta sgangherata. Quindi, sgancia i dobloni!";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Maledizione, prendi i tuoi diecimila e sparisci dalla mia vista! E che il diavolo mi porti, se ti rivedo ancora.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Basta così, ne ho fin sopra i capelli. La tua arma è mia, quindi non hai speranze, canaglia.";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "Capito, non sono mica uno sprovveduto.";
			link.l1 = "Bene.";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// <-- участвовал в событиях Картахены
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "Non sto aspettando visite, né oggi né mai. Che diavolo vuoi?";
			link.l1 = "Ciao, Impiccato. Il Diavolo della Foresta mi ha mandato. È una fortuna che ti abbia trovato prima dei tirapiedi di Jackman. I suoi uomini ti cercano in ogni angolo dei Caraibi. Ti è andata bene, Henry, perché solo Svenson sa dove sei nato. Mi ha chiesto di avvisarti.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "Adesso capisco... Pare che Svenson sia ancora vivo e non si sia scordato del suo vecchio compare. Da quando l’ho visto per la prima volta come un pivello sulla coperta di una goletta sventrata, quante onde insanguinate sono passate... La vita è volata via troppo in fretta, e il mio tempo qui si sta esaurendo.\nVolevo spirare di vecchiaia su questa landa desolata, lontano dagli uomini e vicino al mare. Ma se Jackman ha rimesso piede nei Caraibi, non mi lascerà in pace. Non fu colpa mia, ma sono in debito col suo padrone. Non che qualcuno mi crederebbe, ormai.\nNon temo la morte, ma il dolore. E Jackman, di dolore, se ne intende fin troppo. Solo il pensiero mi fa gelare il sangue nelle vene, e tutto si oscura.";
			link.l1 = "Il Macellaio è stato impiccato vent’anni fa, quindi non devi restituire debiti a nessuno. Se hai paura di Jackman, puoi pure passare il tuo debito a me. Tanto credo che prima o poi lo incontrerai comunque.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "Non è cosa semplice impiccare gente come il Macellaio. L’ex boia di St. John potrebbe raccontarti mille storie sui morti tornati dall’inferno. E Giacobbe ha avuto un buon maestro nel suo capitano, quindi non so davvero chi dei due tema di più.";
			link.l1 = "Perché mai Jackman dovrebbe aver bisogno di te?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "Dovevo consegnare dell’oro a una vedova come ricompensa per aver protetto la figlia del Macellaio. Perché mi guardi così? Sì, la piccola era nata poco prima che il 'Nettuno' affondasse. Lui non poté tornare in tempo per lei, così mi mandò a occuparmi della creatura e di chi la teneva.";
			link.l1 = "Il nome della custode era Gladys Chandler?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "Non fare lo scemo. Se Jackman mi cerca, è perché gli serve la figlia del Macellaio. Lo sai già che sta cercando una donna di Belize chiamata Gladys e la sua figlioccia. Sii sincero con me e forse potrei fidarmi di te.";
			link.l1 = "Cosa dovevi riferire a Gladys?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "Niente. Dovevo mostrarle l'anello del Macellaio, così avrebbe capito che ero il corriere mandato dal capitano. Dovevo anche consegnarle un forziere di dobloni per la creatura. Ho dovuto ammazzare un bastardo per strappargli quell’anello, e questo mi ha costretto a restare ad Antigua per un altro mese.\nQuando finalmente sono arrivato a Belize, Gladys era già sparita e la città era stata data alle fiamme e saccheggiata dagli spagnoli. Era riuscita a vendere la casa e a fuggire col suo nuovo uomo e la piccola Helen. Spero solo che si sia presa cura di lei e non abbia venduto la ragazza agli zingari o a qualche lupanare.";
			link.l1 = "La figlia del Macellaio si chiamava Elena, vero?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "Esatto. In onore della madre del Macellaio. Se non temi i morti che camminano e i pirati che ti fissano con occhi vuoti, allora posso darti l’anello e l’oro. Mai li ho toccati. Morivo di fame, ma non li ho sfiorati. Fanne ciò che vuoi. E in cambio ti chiedo solo...";
			link.l1 = "Cosa sta succedendo, Henry?!";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "Tu... tu... Io chie... do... oh!";
			link.l1 = "No!";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				TraderHunterOnMap(true);
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "A-ah, ecco il nostro amico ficcanaso! Hai finalmente trovato Gonzales? Ben fatto, ci hai condotto dritti a lui... ora non ci servi più. Ragazzi, fate fuori questo buffone!";
			link.l1 = "È l’ora di crepare, viscere di granchio!";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "U-ah! U-ah! Il grande Kukulcan esige una nuova vittima! O-eh! Lo spirito del possente guerriero d’altri tempi è giunto al nostro villaggio per essere sacrificato al grande Kukulcan! O-eh! Tutti in ginocchio davanti allo spirito del valoroso guerriero!";
			link.l1 = "(sottovoce) Ma che diavolo, dove sono finito?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "O-eh! Il grande guerriero vuol essere divorato dal possente Kukulcan! Il sole sorge, le ombre si accorciano! Presto il grande Kukulcan prenderà vita! Ti portiamo da lui, possente guerriero, e proseguirai il tuo viaggio nelle terre degli antenati!";
			link.l1 = "(sottovoce) Sciocchezze... Kukulcan di nuovo? Ehi, capo, sono venuto in pace! Son qui per...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "O-eh! Il grande guerriero dice che vuole essere sacrificato a Kukulcan subito. Oh, grande guerriero! Andiamo ora da Kukulcan e attendiamo la sua venuta! Guerrieri! Abbiamo il grande onore di portare lo spirito dell’antenato a Kukulcan!";
			link.l1 = "(sottovoce) Idiota... Va bene, devo andare con loro. Meno male che non mi hanno ancora aggredito, non saprei nemmeno difendermi con ‘sto coso addosso...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "Giungiamo a Kukulcan, grande spirito degli antenati. Presto il sole calerà, le ombre si allungheranno e Kukulcan verrà a trovarci. Attendi, valoroso guerriero...";
			link.l1 = "(piano) Ora capisco, capo guerra indiano...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "Kukulcan è vivo! Kukulcan è con noi! Un grande guerriero può essere sacrificato a Kukulcan! Guerrieri, inchinatevi davanti al grande spirito degli antenati!";
			link.l1 = "(sottovoce) Stai alla larga, Capo. Lo farò io stesso. Non è mica la prima volta...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "Come posso aiutarvi, signor mio?";
			link.l1 = "Ebbene, ebbene... dimmi, compare, che ci fai qui?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "Cosa ci faccio qui? Sono un pescatore e sto pescando, che diamine! E tu chi sei per interrogarmi con questo tono, eh?";
			link.l1 = "Non mentirmi, compare. Magari sei davvero un pescatore, ma non stavi certo pescando pesci da queste parti. Delle stoffe preziose di nave sono state gettate in mare, proprio qui. E la tua presenza qui mi puzza parecchio.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "Che sciocchezze sono queste? Di che seta blateri, eh?";
			link.l1 = "Quale seta? Quella cinese... Non fare il fesso! Ora senti bene: o mi consegni subito la seta che hai nella stiva, oppure la prenderò io di persona. Ma prima la mia ciurma ti sistemerà per bene, te e i tuoi uomini. Allora? Devo chiamare i miei ragazzi?";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "No! Monsù, non sapevo... Quelle balle galleggiavano lì, così ho pensato bene di...";
			link.l1 = "Porta la seta alla mia nave. Sbrigati!";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "Sì, sì, certo. Lo faremo subito, solo non portare via la mia barca!";
			link.l1 = "Muovi il culo! Non ho tutto il giorno...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "Ecco, abbiamo portato tutto quello che abbiamo trovato – tutti e nove i balletti. Questo è tutto, lo giuro...";
			link.l1 = "Va bene. Continua pure a pescare, ma non ti venga più in mente di mettere le mani sulla roba altrui!";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "Hai già ottenuto ciò che volevi. Non mi resta più nulla! Che diavolo vuoi ancora?";
			link.l1 = "Calmati, compare. Me ne vado.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "Se ti manda Barbazon, digli che non ho nessuna voglia di uscire di prigione per suo ordine. Preferisco aspettare il processo. Persino la canapa olandese al collo è meglio della sua benevolenza.";
			link.l1 = "Non scorreggiare ancora. Il tuo navigatore ha detto a Jacques che sei morto. Mi ha mandato a cercare la seta che hai gettato in mare. Quanta ce n’era sul tuo brigantino?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "È stata colpa mia, maledizione. Il corriere portava nove balle di seta per Barbazon. Ordinai di seguirlo. Fece troppo rumore, così gli abbiamo tagliato la gola. Aveva altre tre balle nascoste, che mi sono preso e ho nascosto nel mio nascondiglio. Ma a quanto pare abbiamo attirato attenzioni sgradite.\nCi hanno trovati in fretta e una pattuglia olandese aspettava il 'Cane Salato' in mare aperto. Non siamo riusciti a scappare. Puoi tenerti la seta se non dici nulla a Barbazon su di me. Il bottino si trova alla spiaggia Grand Case, tra le rocce vicino al fondo cieco. Dubito che mi servirà ancora.";
			link.l1 = "Va bene. Non dirò a Barbazon che sei ancora vivo. Se quello che dicono su di lui è vero, allora è meglio che tu finisca impiccato dagli olandesi. O magari ti va di lusso e ti condannano ai lavori forzati.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "Sto aspettando l’uomo che sa quando inizierà la caccia allo squalo bianco.";
			link.l1 = "La caccia è cominciata.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "Finalmente! Ora ascolta bene. Dovrai andare da Marcus Tyrex a La Vega e dirgli che la brigantina 'Separator' è stata assaltata vicino all’isola dei Turchi e ora si nasconde alla Baia del Sud. Il suo capitano è gravemente ferito e l’equipaggio aspetta soccorso. Hai raccolto un marinaio del 'Separator' che ti ha raccontato tutto. Ora è morto. Questo è tutto ciò che sai. Capito?";
			link.l1 = "E perché mai avresti bisogno di me per questo? Ho aspettato fin troppo solo per questa faccenda...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "Ti pagano per lavorare, non per ficcare il naso dove non ti chiedono. Però hai ragione. Devo avvisarti: Tyrex non ti lascerà andare finché non sarà sicuro che dici la verità. Ma una volta che avrà scoperto tutto, ti ricompenserà come si deve. Sempre che possa farlo...";
			link.l1 = "Mi prendi per fesso, signore... Perché non vuoi ricevere i suoi ringraziamenti di persona?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "Caramba! Non mi piace la tua curiosità! A furia di ciarlare finirai dritto in una fossa, un giorno.";
			link.l1 = "Sì, a volte sono proprio insopportabile. Soprattutto quando sento puzza di fregatura. No, furfante, ora si gioca secondo le mie regole. Chi è il tuo padrone, maledizione? Parla o ti faccio sputare tutto io!";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "Tu... bastardo! Barbazon la pagherà per questo e la tua vita finirà, mangia-merda!";
			link.l1 = "Ah! Me lo aspettavo. Preparati, furfante!";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "Charlie Prince? Che ci fai qui? A-ah, maledizione, sei stato tu! Tutto questo è colpa tua!";
				link.l1 = "Calmati, Bernie. Sono dalla tua parte. L’agguato è stato sistemato, tu e la tua nave siete al sicuro.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "Chi diavolo sei? Come sei arrivato fin qui? Sparisci subito, la mia nave è imbottita di polvere e quei cani sulla riva possono farla saltare in aria con un colpo solo.";
				link.l1 = "Non temete, signore. L'agguato sulla riva è stato spazzato via. La vostra nave è al sicuro, a patto che non vi venga in mente d'accendere una pipa sul ponte, s'intende. Come vi chiamate?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "Vincent. Bernard Vincent. E tu come ti chiami?";
			link.l1 = "Capitano "+GetFullName(pchar)+" Taglierò quelle corde e ti renderò libero...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "Oh... la mia gratitudine. Come posso mai sdebitarmi?";
			link.l1 = "Non è ancora finita, signore. C’è qualcuno della tua ciurma che respira ancora?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "Tre dozzine dei miei uomini sono rinchiusi nella stiva...";
			link.l1 = "Lascia andare queste persone e sparisci da qui subito. ";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "Ma...";
			link.l1 = "Non perdere tempo, Bernard. Mi ringrazierai più tardi a La Vega... Forse anche Tyrex mi sarà riconoscente.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "Allora, non sei qui per caso? Sapevi già tutto?";
			link.l1 = "Sì, lo sapevo. Sono riuscito a smascherare le macchinazioni di Jackman e i suoi piani per fare fuori Marcus. Ah, di’ a Tyrex di starsene buono, il suo ficcanasare può mettere in fuga Jackman.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "Glielo dirò senz'altro! Parti già adesso?";
			link.l1 = "Sì. E faresti bene a muoverti anche tu.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "Davvero? Ascolta, mi dispiace, fratello...";
			link.l1 = "Dimentica. Lascia che tagli queste corde e ti renda libero.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "Merda... non sento più le mani...";
			link.l1 = "Bernie, ci sono altri superstiti sulla nave?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "Trenta uomini sono rinchiusi nella stiva...";
			link.l1 = "Lasciali andare e sparisci al diavolo da qui. Subito!";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "Ma...";
			link.l1 = "Salpa subito per La Vega. Racconta a Marcus ogni maledetto dettaglio di questo pasticcio.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "Ti manda Marcus?";
			link.l1 = "Non l’ha fatto lui. Sono riuscito a smascherare l’intrigo di un farabutto: voleva far fuori Marcus con tutta questa faccenda. Digli che per ora se ne stia buono e non ficchi носа... Gli spiegherò tutto di persona più tardi. E, per carità, dìgli di smetterla di prendersela con me.";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "Cosa vuoi sulla mia nave, signore?";
			link.l1 = "Buongiorno, Paul. Il tuo nome è Paul Molligan, giusto?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "Sì, sono io. In che posso esservi utile?";
			link.l1 = "Il mio nome è "+GetFullName(pchar)+" e Jan Svenson mi ha mandato.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "Jan? Ah-ah, mi ricordo di te. Certo! Ultimamente sei sempre a casa sua. Dunque, che cosa vuole Jan da me?";
			link.l1 = "Te ne sei andato da Blueweld con una tale fretta. Jan voleva che caricassi sulla tua nave altri duecento casse di mogano da consegnare a lord Willoughby a Bridgetown. Prepara la tua nave, i miei uomini metteranno il mogano nella stiva.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "Mogano? Jan ha detto così? Mh. E perché non lo porti tu stesso a Barbados? Perché proprio io?";
			link.l1 = "Perché sei tu che navighi laggiù e non io. Ho ricevuto un incarico urgente da Svenson, quindi non posso perdere tempo a veleggiare fino a Bridgetown anch’io. Inoltre, Jan non si fida di меня per trattare con lord Willoughby e vuole che sia tu a farlo. Mi spiace. Ora carichiamo la roba, devo andare.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "Ascolta, non ho spazio libero nella stiva. Non potrò fare ciò che Jan mi chiede, anche se mi piacerebbe.";
			link.l1 = "Nessuna stanza? Strano... Jan mi aveva detto che c'era posto libero.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "È vero, ma Jan non sapeva che ho armato l’‘Oyster’ con cannoni più pesanti. Non posso caricare più merce di quella che ho già. Quindi porta tu stesso il legname a Barbados, eh compare? Di’ a Jan che non ci sono riuscito. Trattare con Willoughby è facile: lo incontri, gli consegni il carico e ti fai dare la ricevuta. Più semplice di così!";
			link.l1 = "Hm. Questo non era nei miei piani... Diamo un'occhiata alla tua stiva, d'accordo? Il mio nostromo è un vero mago nel sistemare le merci, saprà infilare il carico nella tua stiva e lasciarti pure un po' di spazio libero...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "Amico, non posso imbarcare altra merce. Vuoi che butti i miei cannoni e lasci l’‘Ostrica’ senza difesa?";
			link.l1 = "Ebbene, se ne sei così sicuro... Ma Jan non la prenderà bene, tienilo a mente!";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "Lo spiegherò a Svenson, non preoccuparti. In fondo è colpa sua, non s’è nemmeno degnato di chiedere stazza alla mia nave.";
			link.l1 = "Ehi, ora dovrò trascinare quei tronchi fino a Barbados, maledizione... Addio, compare.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "The scoundrel is still not suspecting a thing. I should get closer and shoot at him with grapeshot. A sudden strike will always win in any battle. ";
				log_Testinfo("Friends");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Enemies");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "Siamo intesi, vero?";
			link.l1 = "Sì, sì. Sto andando alla mia nave.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "Cosa vuoi da me? Le chiacchiere e il gioco d’azzardo non fanno per me. E il mio rum preferisco scolarmelo in solitudine. Inoltre, sono di pessimo umore dopo l’ultima mia traversata.";
			link.l1 = "E che diavolo t’è successo durante l’ultima traversata?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "Un brav’uomo s’è fidato di me e io l’ho gettato in mare perché l’equipaggio lo pretendeva.";
			link.l1 = "E quale sarebbe stata la sua colpa?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "Sono appena arrivato e non conosco quasi nessuno da queste parti. Ecco perché ho preso a servizio quel grassone di buon cuore come cerusico, senza sapere nulla del suo passato. I filibustieri ci tallonavano fin da quando abbiamo lasciato Barbados. Ma cosa gli poteva servire la mia bagnarola?\nSiamo riusciti a scampare per il rotto della cuffia, grazie a una burrasca improvvisa. Ci siamo fatti un goccetto per festeggiare. E quel balordo grassoccio non ha trovato di meglio che raccontare a tutti che i pirati probabilmente ci inseguivano per causa sua, perché era stato boia e sapeva ciò che non doveva sapere.\nOvviamente, i miei marinai sono andati su tutte le furie. Un boia a bordo, spacciato per chirurgo! E nessuno voleva attirarsi addosso i pirati... Così ho dovuto sbatterlo a terra, povero sciocco. Tutta colpa sua, non sapeva tenere la bocca chiusa. Eppure mi dispiace per quel villano: era un medico coi fiocchi. Mi bastava un suo tocco e mi passava la sbornia in un minuto.";
			link.l1 = "Maledizione! Il tuo dottore si chiamava Raymond Baker, giusto?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "Sì. Esatto. E come lo sai? Mi stavi forse pedinando?";
			link.l1 = "No, non ero io. Mi serve solo quell’uomo, è un gran dottore. Dove lo avete sbarcato?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "Latitudine 15 gradi 28' nord, longitudine 63 gradi 28' ovest. Sbrigati, signore! Dev’essere ancora vivo e, se lo salvi, mi toglierai dai guai!";
			link.l1 = "Sto già levando le ancore!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "Capitano, sbrigati! Deve essere ancora vivo!";
			link.l1 = "Sì, sì, sto arrivando...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Ehi! Fermo lì! Non muoverti. Questo territorio è sotto controllo!";
				link.l1 = "Non essere troppo severo, compare! Amici! Ci manda Jackman. Dobbiamo arrivare alla miniera. Ordini del padrone...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ehi! Fermo lì! Non muovere un muscolo. Questo territorio è sotto controllo!";
				link.l1 = "Hm. Ma voglio passare... Perché diavolo mi stai fermando?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, ancora tu? Vedo che non ti entra in testa... Ragazzi, fuoco!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "Forza, avanti, muoviti!";
			link.l1 = "D'accordo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "Perché la miniera alle mie spalle è proprietà privata e io sto qui proprio per fermare forestieri come te dal проходить oltre. Faresti meglio a voltarti e sparire, straniero. I nostri cannoni sono carichi a pallettoni: fai solo un altro passo e ti ridurremo a una pozza fradicia.";
			link.l1 = "Heh, capisco. La tua miniera è ben sorvegliata. Va bene, me ne vado.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "Tu, bastardo! Ah, vedremo chi finirà steso come una pozzanghera!";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "Ti ho dato una possibilità... Ragazzi, fuoco!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Ehi! Allontanati! Questo territorio è sotto la nostra protezione!";
				link.l1 = "Ehi, stai calmo, amico! Ci manda Jackman. Dobbiamo raggiungere la miniera. Ordine del padrone...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ehi! Vai via! Questo territorio è sorvegliato!";
				link.l1 = "Mm.   E che c’è laggiù?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "A-ah, di nuovo tu? Vedo che non capisci... Ragazzi, fuoco!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "Non sono affari tuoi. Sparisci o ti riempiamo di piombo, te lo giuro!";
			link.l1 = "Calmati. Me ne vado.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "Tu, bastardo! Vedremo chi sparerà a chi!";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "Ti ho dato una possibilità... Moschetti pronti! Fuoco!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "Davvero? Allora dovresti conoscere la parola d'ordine. Dilla subito, ma ti pentirai amaramente, se menti...";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attackx_1";
		break;
		
		case "mine_attackx_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "neptune")
			{
				dialog.text = "Esatto. Ma tu, compare, sei arrivato dalla parte sbagliata. Non ti hanno avvertito? Torna indietro e prendi la strada a sinistra dal pozzo secco. Poi aggira la collina e lì vedrai il portone principale.";
				link.l1 = "Non posso entrare qui?";
				link.l1.go = "mine_attackx_2";
			}
			else
			{
				dialog.text = "Ragazzi, abbiamo un ficcanaso! Moschetti pronti! Fuoco!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_attackx_2":
			dialog.text = "No. Solo dall’ingresso principale.";
			link.l1 = "D'accordo, compare... Ohi! Guarda là! Ma che diavolo è quello in cima alla palizzata?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "Davvero? Allora dovresti conoscere la parola d’ordine. Su, dilla forte che io possa sentirla. E se provi a fregarmi, sarà l’ultima burla della tua misера vita.";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "neptune")
			{
				dialog.text = "Giusto. Avanti, su. Il capo dell'accampamento sta nella casa a sinistra dell'ingresso della miniera. Vai a parlarci.";
				link.l1 = "D’accordo, compare...";
				link.l1.go = "mine_attack_2";
			}
			else
			{
				dialog.text = "Ragazzi, abbiamo un ficcanaso! Cannoni, fuoco a volontà!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_attack_2":
			DialogExit();
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "Cos’altro? Hai scordato qualcosa?";
			link.l1 = "Sì. Mi hanno chiesto di porgerti i più sentiti saluti.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "A me? Ah-ah! Da chi, di grazia?";
			link.l1 = "Jan Svenson, maledetto furfante!";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			LAi_SetPlayerType(pchar);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Mine_bandit_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			if (pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetActorType(sld);
				LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
				LAi_ActorAnimation(sld, "shot", "Saga_MineBanditDie", 1.0);
			}
			else
			{
				for (i=1; i<=6; i++)
				{
					sld = characterFromId("Mine_bandit_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "Saga_BanditsDestroyed");
				AddDialogExitQuest("MainHeroFightModeOn");	
			}
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.character = "Mine_bandit_1";
			pchar.quest.Saga_MineAttack_07.win_condition.l2 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l2.character = "Mine_bandit_2";
			pchar.quest.Saga_MineAttack_07.function = "Saga_SvensonMineexitAttack";
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("Faremo a pezzi quei bastardi!","Non vedo l’ora di dare una lezione a quei canaglie!","I tirapiedi di Jackman non hanno alcun diritto di scorrazzare nel Main Occidentale! Li scacceremo a calci da qui!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("Siamo pronti a menar le mani!","Gliela faremo vedere noi!","Non hanno la minima idea con chi si stanno mettendo nei guai!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\English\evilpirates01.wav");
			dialog.text = "Comandante, il cannone è pronto. L’abbiamo caricato con una bomba, proprio come avete ordinato.";
			link.l1 = "Immagino che nessuno ci stia aspettando qui... È ora di farci conoscere. Jan mi ha detto che il loro accampamento è dietro quella collina. Ce la farai ad arrivarci?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "Facile, comandante. Alziamo un po' la canna, così... fatto.\nPronti!.. Fuoco!!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "Uhm. Randolf, pensi che abbiamo urtato qualcosa? Vorrei sentire il tuo parere.";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Comandante, abbiamo colpito qualcosa o qualcuno, ma non saprei dire con certezza... questa maledetta collina ci copre la vista. Cambio angolo.\nPronti! Fuoco!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "Ah! Guarda, Comandante! C’è del fumo! Dannazione, abbiamo centrato il fienile di qualche furfante! All’arrembaggio!";
			link.l1 = "Sì, vedo il fumo... Una vittoria epica già, senza dubbio. Ricarica il cannone e puntalo verso il sentiero, pare che i nostri ospiti stiano arrivando. Li accoglieremo come si conviene!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Ai vostri ordini, comandante! Caricate una bomba! La ciurma ai pezzi, pronti! Miccia pronta! Al mio segnale, fuoco!";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\English\evilpirates05.wav");
			dialog.text = "Ah-ah, questa dev’essere una bella legnata!";
			link.l1 = "Non rilassarti ancora! Carica il cannone! Non credo che abbiano avuto abbastanza. Altri stanno arrivando!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "Ai vostri ordini, comandante! Caricate una bomba! Pronti! Fuoco al mio segnale!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\English\evilpirates06.wav");
			dialog.text = "Ah-ah-ah, quei bastardi ci mostrano la schiena! Carne da cani! La mitraglia li sta facendo a pezzi da questa distanza! Pare che non abbiano fegato per venirci addosso un'altra volta!";
			link.l1 = "Ora tocca a noi. Randolph, tu resta qui vicino al cannone. Spara un paio di colpi verso il sentiero, poi punta al fumo – dai fuoco al loro covo! Ma non osare colpirci, dannato!";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Ai vostri ordini, comandante! Pronti i cannoni! Caricate una bomba!";
			link.l1 = "Uomini! Alle armi! Seguitemi, all'attacco! All'arrembaggio!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("Non farmi del male, non sono dei loro! Ammazza quei furfanti!","Liberaci, compare! E fa fuori tutti quei cani!","Tagliali, compare, tagliali! Falli schiattare!");
				link.l1 = "Ah! Non ti crucciare, proprio questo stiamo facendo in questo istante.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("La nostra schiavitù è finita? Ci libererai?","Ehi, sono davvero arrivato vivo fino a questo giorno?","Maledetti ci hanno dissanguati fino all’ultima goccia....");
				link.l1 = "Penso che presto potrai goderti la tua libertà, compare...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Faresti meglio ad andartene, signore. Non proteggiamo furfanti qui e non ci servono grane con le autorità della colonia.";
				link.l1 = "Va bene, me ne vado...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// Первый диалог с Элен
				if(startHeroType == 4)
				{
					dialog.text = "Ah, Helen. Potevi vestirti un po' più decentemente prima di presentarti da Jan, invece di mostrargli chi sei davvero. Peccato che lui non mi creda.";
					link.l1 = "E in che cosa sarei così diverso? Lui mi ha cresciuto fin da bambino e mi conosce meglio di chiunque altro. Non ho segreti davanti a lui. Sopporto questo caldo infernale da quando ero piccolo, ho solo imparato ad arrangiarmi a modo mio, tutto qui.";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+", Signore. Volete vedere Jan?";
				link.l1 = "Buongiorno. È stato un piacere incontrarvi, signorina?..";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// заглушка элен
				if(startHeroType == 4)
				{
					dialog.text = "Jan è dentro. Avanti, qui non c’è nulla da vedere, e mi stai già dando ai nervi.";
					link.l1 = "Tanto non ne avevo proprio voglia.";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "Grr!";
					link.l1 = "E anche a voi, buona salute, madame Svensson.";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", Capitano "+GetFullName(pchar)+"Se sei qui per Jan, devo deluderti – non è qui. È andato a sbrigare affari di gran peso.";
					link.l1 = "Maledizione! E mi serve proprio adesso! Ditemi, Madame Svenson, vi ha detto quando torna?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "A-ah, ancora tu, Capitano "+GetFullName(pchar)+"... avanti, Jan è di sopra, come al solito.";
				link.l1 = "Vi ringrazio, madame Svenson...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Madama, madama Johanna Svenson.";
			link.l1 = "Capitano "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "Capitano? Beh, son lieto di darvi il benvenuto nella mia dimora. Ma se cercate Jan, temo di deludervi – non è qui. È partito a sbrigare certe faccende importanti.";
				link.l1 = "Maledizione! E proprio ora che mi serve! Ditemi, madame Svenson, vi ha detto quando farà ritorno?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Capitano? Benvenuto nella mia dimora. Mio marito si trova al secondo piano, nel suo studio. Sali pure.";
			link.l1 = "Ho capito, signora Svenson...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "No. Non mi ha nemmeno detto la data esatta del suo ritorno, perché lui stesso ignora quanto durerà la ricerca.";
			link.l1 = "Mi dispiace d’intromettermi, ma ho davvero bisogno di lui... Che razza di indagini sta conducendo?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "Te lo racconto io. La bella Helen, detta anche Rumba, figlia del defunto amico suo Sean McArthur, è svanita nel nulla. Jan tratta quella diavoletta come fosse figlia sua; gli ricorda la sua vecchia fiamma, che aveva lo stesso temperamento sfrontato. Almeno, così credo sia questa la causa della sua affezione.\nComunque sia, la ragazza è sparita una settimana fa assieme alla sua goletta, la 'Rainbow', e tutto il suo equipaggio. Sean McArthur le insegnò l’arte marinaresca e la 'Rainbow' fu lasciata a lei nel testamento. E ora gioca a fare il capitano...";
			link.l1 = "Cosa mai le sarà accaduto?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Chi lo sa... Una settimana non è poi così tanto, ma la vedova McArthur è convinta che qualcosa sia capitato a sua figlia, e ha saputo convincere anche Jan. Lui ha radunato i suoi uomini e si è messo a cercarla di persona, senza alcun risultato per ora. Io, per conto mio, credo che Helen stia benone e che Jan si stia solo rodendo il fegato per niente.\nHa dato troppo ascolto alle farneticazioni di quella vecchia balena e si è fatto prendere dal panico. La ragazza, molto probabilmente, si sta sollazzando con qualche altro galante, lontana da occhi indiscreti in qualche rifugio sicuro. Tornerà appena avrà placato l'appetito.";
			link.l1 = "Johanna, dove posso trovare Gladys? Ho bisogno di parlarle...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "La sua casa è vicino al molo, a sinistra. Ma difficilmente la troverai lì. Passa le sue giornate sulle mura del forte, a scrutare l’orizzonte in cerca della sua amata figlia.";
			link.l1 = "Capisco. Mille grazie per le tue dritte!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "Jan non è ancora arrivato, capitano, torna più tardi.";
			link.l1 = "Capisco...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "You're always in heat, I'd say. You should go to church; I've barely ever seen you there.";
			link.l1 = "La mia coscienza è limpida – non ho nulla da farmi perdonare. Sei ancora stizzita perché ha aiutato a rifornire la mia nave invece di comprarti un altro vestito, Joanna?";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "Io? Invidioso? Non ti do neanche quel piacere. È solo che a te tutto cade in grembo senza fatica, e non lo meriti.";
			link.l1 = "Ma appena ho messo le mani su quella nave, ho cominciato a guadagnare da solo. E da quando ti ha raccolto come un randagio, tu non hai fatto un giorno di fatica. Allora, chi è che davvero gli succhia il sangue?";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "Continua a parlare così, e un giorno la fortuna ti volterà le spalle. Jan e Gladys avrebbero dovuto insegnarti un po’ di buone maniere. Va bene, sputa il rospo – e poi sparisci dalla mia vista, Helen. Lui è dentro.";
			link.l1 = "Gallina stupida. Certo, lo farò.";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "Ehi! Che diavolo ci fai qui?";
			link.l1 = "Vorrei farti la stessa domanda: che ci fai tu, insieme ai tuoi compari, nella mia segreta?";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "Ah! La tua prigione? E quand’è che t’è diventata tua, canaglia da cortile?";
			link.l1 = "Il giorno in cui tuo padre commise l’errore di fottere tua madre.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "Cerchi grane, eh?";
			link.l1 = "Ascolta, compare, ti do un’ultima chance per filartene da qui. Questa è la mia galera, e non lascerò nessuno entrare a spasso come gli pare, capito? Mi basta fischiare una volta sola, e mezzo branco di filibustieri dell’Isla Tesoro sarà qui in un batter d’occhio.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "E allora, vediamo di tapparti quella bocca!";
			link.l1 = "Ah-ah! Sei proprio una nullità, feccia!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "Aspetta un attimo, falco!";
			link.l1 = "Non è proprio il momento migliore, tesoruccio.";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "Oh, ti sbagli, bellimbusto. Questa ragazza ti ha preso in simpatia, e il sentimento è ricambiato, lo vedo nei tuoi occhi.";
			link.l1 = "Non è proprio una gran referenza... Va bene, che vuoi? L'elemosina?";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "Voglio offrirti un aiuto in questa tua impresa difficile. Guarda qua! Un boccale magico e un unguento proibito. Il boccale ti darà fortuna nelle bevute, mentre l’unguento – negli affari di cuore. Cosa scegli? Solo duemila!";
			link.l1 = "Non mi serve nulla – ho già dato un bel mucchio d’argento a gente come te.";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "Unguento proibito, dici? Beh, non sono certo un santo, lo ammetto. Dammi qua.";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "Una boccale? Sembro forse un ubriacone? Bah, chi voglio ingannare... versane uno!";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "Bello, ma sciocco. Vola via allora, falco.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "Oh, non nasconderlo nelle tue tasche senza fondo! Vola via, falco, e non peccare!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("Talisman 'Throat of cast iron' acquired!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "Oh, non nasconderlo nelle tue tasche senza fondo! Vola via, falco, e non peccare!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Talisman 'Cupid's Balm' acquired!");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "Ah! Fuori di qui, mascalzone! Quante volte ti ho detto di non infilarti in casa mia! E chi sarebbe questo?";
			link.l1 = "Signora, ci conosciamo già.";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "Monsieur de Maure? Ma che piacere! Così fate i vostri affari con mio marito?! Lo sapevo! Avevo avvisato Jan: un giorno questa sgualdrina avrebbe mandato i suoi uomini alla rovina! E che cos’hai in mano?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "Wha-a-a-at?! How dare you, wretch?! You're not going anywhere; my husband will be here any moment now and he'll teach you how to talk to the elders!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "Cosa succede qui? Signorina MacArthur! Ho nutrito grande rispetto per vostro padre, e il signor Svensson ci è amico... Ma non ricordate come andò a finire l’ultima volta? \nChe delusione, parola d’ufficiale, che delusione! Potevate almeno invitarci!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "Grazie per la vostra ospitalità, signorina MacArthur. Permettetemi di dire che tutti noi siamo davvero lieti di rivedervi tra noi. Quel che è accaduto resta un gran mistero, ma non c’è da stupirsi che il porto già ne bisbigli. Tuttavia vi assicuro che nessuno si lascerà andare a pettegolezzi. Vi porgo le mie più sentite scuse per la recente condotta d’un nostro capitano. E desidero ringraziarvi di cuore, monsieur de Maure.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "Andrà tutto bene, signorina. Monsieur de Maure, sarò schietto – benché Donovan si comporti come un vero furfante e mascalzone, la flotta non lo biasimerà mai apertamente. Anzi, è più probabile che lo difendano pure. La vostra piccola spedizione è finita nei rapporti ufficiali e ha complicato di molto le relazioni fra le nostre nazioni. Tuttavia, considerando il peso di monsieur Svensson, e le notevoli concessioni ricevute da Capsterville, non avete nulla da temere.";
			link.l1 = "Splendido! Direi che ci beviamo su, amici!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "Perdonate la mia sfacciataggine, ma che mi dite di quell’incarico?";
			link.l1 = "Sei ancora qui?";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "Caro signore, dove mai potrei andare? Sono andato solo a svuotare la vescica, ho origliato la vostra sdolcinata conversazione e mi sono un po’ scaldato. Nel cuore, intendo!";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "Santo cielo! Ormai ti ho dato la mia parola, non ci si può tirare indietro. Va', prendi il comando.";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "Non ho faccende per voi, signore.";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "Aye aye, Capitano!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "Peccato! Comunque, grazie per il boccone, Capitano!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "In nomine Patris et Filii et Spiritus Sancti... avanti, figliolo mio.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Ciao, Madre Amelia. Anche tu vuoi farmi la predica?";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "Sparisci! Che razza d’incubo è mai questo? Che sta succedendo? Sto forse sognando?";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "No, mio piccolo falchetto. E perdona Jan – il poveretto s’è lasciato prendere. Ma sì, voglio proprio rimproverarti. Perché sei venuto in chiesa? A pentirti dei tuoi peccati? O cercavi la rossa?";
			link.l1 = "Non lo so nemmeno io...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "L'hai vista anche tu? Mi ha subito stregato.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "Sparisci di qui. Dovevamo già incontrarci, ma tu continui a tirarla per le lunghe. Perché sei venuto in chiesa? A confessare i tuoi peccati? O ti interessava la rossa?";
			link.l1 = "Non lo so nemmeno io...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "L'hai vista anche tu? Mi ha subito stregato.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "Buongiorno, mio falco. La cerimonia non è ancora iniziata, attendi in fila, per cortesia.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Salve, Vostra Eccellenza. Anche voi avete intenzione di sgridarmi?";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "Sparisci! Che razza d’incubo è mai questo? Che sta succedendo? Sto forse sognando?";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "No, my falcon. And forgive Jan, the poor man got worked up. No need to scold you; you did everything right - didn't go after the red-haired one to the church. Good boy!";
			link.l1 = "Essere lodato fa sempre piacere. Soprattutto quando è chiaro per quale motivo.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "L'hai vista anche tu? Mi ha stregato lo sguardo.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "Sparisci tu stesso. Dovevamo già incontrarci, ma stai tirando troppo la corda. Vieni qui, ti farò i complimenti – non sei corso dietro alla rossa in chiesa. Bravo ragazzo!";
			link.l1 = "Ricevere elogi fa sempre piacere. Soprattutto quando è chiaro il motivo.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "L’hai vista anche tu? M’ha rapito lo sguardo.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "Non ti annoierò coi dettagli, sciocchino, ma sappi questo: sei destinato a diventare un grande uomo. Porterai con te molto male, ma ancor più bene. Tuttavia, la felicità non ti è promessa. La felicità, mio falchetto, è per chi segue la propria via senza deviare. E una donna leale ti aiuterà a non smarrirti.\nNe avrai due, entrambe ti doneranno gioia, ma dovrai scegliere quella dai capelli chiari.";
			link.l1 = "Perché mai? Decido io stesso!";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "Certo, scegli pure, ma la bionda è la migliore. Così abbiamo deciso, punto e basta.";
			link.l1 = "Chi sarebbe questo noi?";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "La poveretta non conosce nemmeno il suo vero nome. Pronuncialo, e sarà tua. Così si dice.";
			link.l1 = "Non ci capisco più un accidente.";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "Senti bussare? Apri subito, e non fare lo gnorri.";
			link.l1 = "Infatti, qualcuno bussa... Avanti!";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "Monsieur, il signor Svensson desidera scambiare qualche parola con voi, se potete concedergli un poco del vostro tempo.";
			link.l1 = "Maledizione, non promette nulla di buono. Farò il possibile, ma non giuro nulla.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "Giorno fortunato, ragazzi! Vi avevo detto che prima o poi sarebbe arrivata qui, vero? Su, bellezza, consegna le armi e vieni con noi.";
			link.l1 = "Vi sbagliate, ragazzi. Lei è con me.";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "Non immischiarti, o ti faccio saltare le cervella come a un cane. C’è una bella ricompensa per la ragazza, e noi siamo canaglie affamate senza scrupoli.";
			link.l1 = "Continua a parlarmi così, e risolverò il tuo problema di fame una volta per tutte.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "Sei impazzito del tutto, Lucky? Siamo stati noi a trovarla per primi! Meglio che tu abbia una buona scusa per sbraitare contro di me, imbecille!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "You're the rat here! We had just torn a big fat Spaniard apart; we can sit on our asses for a year!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "Ma guarda un po’ chi si vede. Bene, tutti gli altri fuori dai piedi, e tu, madama, vieni con noi.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "Siamo in più di voi, e siamo più tosti, danese. Che altro ti serve come motivo, sorcio di sentina? Sono sei mesi che non vedi un bottino decente e campi delle briciole che ti getta Vuazie!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "Pare che qui non si arriverà a una soluzione pacifica.";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "Come dici? Fortunato? Ho sentito dire che lui e Vuazie hanno tramato per rifilarti soffi fasulli. Ecco perché il fato in mare ti volta sempre le spalle.";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "Son stanco di questa farsa. Isla Tesoro, ascoltatemi! Chi era con me a Cartagena?! Chi ha dato fuoco a Merida al mio fianco?! Queste carogne osano sfidare proprio Charlie il Principe! Mostriamogli chi siamo, compari!";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "Sei ancora qui, medusa? Va bene, ragazzi, avanti: legate il capitano e con la ragazza ce la vediamo dopo, intesi?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "Certo, versiamo un po’ di sangue almeno. Eh eh.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "Cosa?! Maledetto, lo sapevo che tramavi con quel furfante dagli occhiali! Spadateli tutti, ragazzi, e della ragazza ci occuperemo dopo!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "Di che vai cianciando, capitano? Sparisci finché la gente perbene tratta d’affari.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "Di che cianci, Capitano? Ho visto Charlie Prince, e tu non arrivi nemmeno alle sue ginocchia. Sparisci finché la gente perbene parla d’affari.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "Charles de Maure? Figlio di Henri de Monpe?";
			link.l1 = "Esatto, monsieur. E voi chi siete?";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "Colonel Francois de Tavanne. You may consider this a direct challenge, monsieur; the gauntlet for the duel has been laid. I don't even wish to dirty my hands with you, but I swear, my blade will taste your blood!";
			link.l1 = "Un duello? Allora dovrete sforzarvi di più, colonnello. Al momento, potreste solo passar per brigante, e con questa razza qui non si chiacchiera: si fa parlare la lama! Spiegatevi!";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "Hai sedotto mia moglie, monsieur! Mentre io versavo il mio sangue per re e patria, tu... tu te la spassavi con mia moglie!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "Silenzio, madama. Il vostro abbigliamento sfacciato getta vergogna sull’onore d’ogni donna, sebbene accanto a questo indegno seduttore d’una nobile dama pariate ben a posto!";
			link.l1 = "Non vedo ancora motivi sufficienti per sfidarvi a duello, colonnello. E permettetemi di osservare che anche voi qui vi comportate con altrettanta indegnità.";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "Non basta, forse? Ho chiesto in giro – al mio posto ci potrebbero stare una dozzina di mariti nobili, signore. Ma se proprio volete i dettagli, vergogna mia, confesso che una delle vostre passioni era Lulu de Tavann, la più bella e onesta fra le donne!";
			link.l1 = "Lulu, dici... E com'è lei?";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "Silenzio! Mia moglie, distrutta dalle angosce che tu le hai fatto patire, è morta da poco! Ho speso quasi un anno e una fortuna intera per rintracciarti, malnato! Ora basta chiacchiere! O accetti la sfida o ti faccio fuori come un cane. Richard! Tu mi farai da testimone!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "Silenzio, signore! Accetta la sfida o perdi ogni briciolo d’onore che ti resta!";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = "Un duello è un duello. Non ti nascondo che mi ci diverto. Capitano, riferisci al Colonnello che è ora di ordinarsi una bara adatta.";
			} else {
				link.l1 = "Vuoi menar le mani? Allora preparati! Capitano, fate sapere al Colonnello che è ora di ordinare una bara degna di lui.";
			}
			link.l1.go = "francois_duel";
			link.l2 = "Questa non è l’Europa, Colonnello. L’onore nei Caraibi si conquista con fatica, ma non si perde altrettanto facilmente. Rifiuto il tuo duello, semplicemente perché non ne ho voglia.";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "Tuo padre ha già un piede nella fossa, mascalzone! E ti giuro che verrà a sapere della tua vigliaccheria!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "Colonnello, vi riconosco il diritto al duello, ma non tollererò atti da volgari briganti! Monsieur de Maure, sono il capitano Richard Small. Siete disposto a soddisfare le richieste del colonnello de Tavann?";
			link.l1 = "Un momento, Capitano. Conoscevo bene Lulu... ed era solita cambiare spasimanti come il vento, e stava meglio in salute di me... Come è morta, Colonnello? Prima o dopo il vostro ritorno a casa?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "Per favore, François, lascia fare a me. Monsieur de Maure, siete stato chiamato a duello. La società degli ufficiali di Blueweld riconosce che la richiesta di soddisfazione del colonnello de Tavann è giustificata. Accettate la sfida o perdete l'onore.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "Charles, ti prego, qui siamo gentiluomini. Non è il caso. Il Colonnello ha viaggiato fin qui per incontrarti! È uno scandalo!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "S-sì, certo, signorina. Ma io...";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "Capitano de Maure, la giornata è tua! Non è stata una battaglia proprio onorevole, ma oggi hai difeso il tuo nome.";
			link.l1 = "Hai detto qualcosa, Capitano? Potrei forse infilare un altro duello nel mio fitto programma di oggi.";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "Le mie scuse, Capitano. Sono solo i nervi!";
			link.l1 = "Penso che la tua presenza qui non sia più richiesta.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "Una decisione giusta! Anche se espressa in modo poco onorevole... Signori! Diamo inizio alle danze!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "Capitano, magari non capisco tutte le belle parole che questi damerini si бросают, ma vedi, se uno viene chiamato codardo, di solito non lo lasci andare così. Dagli una sberla, Capitano, o l’equipaggio comincerà a farsi delle idee.";
			link.l1 = "Volete sangue? La vita è troppo noiosa, vi manca il brivido? Ebbene, avrete il vostro sangue, bestiacce!";
			link.l1.go = "francois_duel";
			link.l2 = "Uhu, che paura mi fate. Avete finito qui, signori? Ho ben altro da fare.";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "It won't look good if our captain backs down from a public challenge. Just give that nobleman a good whack; we know you're great with a sword!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "Codardo! Libertino! Ratto! Hai paura, mascalzone? Avete visto tutti questo?! Richard, lo farò fuori lo stesso!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "F-farabutto! Va bene, sono abituato alle ferite. Mi riprenderò, e...";
			link.l1 = "Mi pare una minaccia, colonnello. E io con le minacce non ci vado leggero.";
			link.l1.go = "francois_sit_kill";
			link.l2 = "Quando ti sarai rimesso, non scordare di vantarti con gli ufficiali su come ti sei beccato quella ferita.";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			notification("Helen approves", "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}
