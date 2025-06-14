// Леонард Маскетт - пьяница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Non voglio parlare con te. Attacchi civili innocenti senza motivo e li provochi a menar le mani. Sparisci dai miei occhi!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> пей до дна
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "Compare, sei arrivato proprio al momento giusto... Voglio parlarti... d’affari. Affari seri, bada bene.";
				link.l1 = "Davvero? Pare che tu non sia ubriaco. È successo qualcosa? È raro vederti sobrio.";
				link.l1.go = "facio";
				break;
			}
			// <-- пей до дна
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "A-a... hic! Salve, compare...";
				link.l1 = TimeGreeting()+" Pare che tu ne abbia già avuto abbastanza, compare.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Hic! Che vuoi, forestiero?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti qualche domanda sull'isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. A presto!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Sì! Basta così? N-ooh! Son proprio un matto sbronzo, hi-hic! Sì, Leonard Musket è ubriaco fradicio, e così dev’essere!";
			link.l1 = "Ti piace bere, eh? Sì, il mio nome è "+GetFullName(pchar)+" . Lieto d'incontrarti.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Se lo dici tu. Qui tutti noi... hic, ci incontriamo prima o poi.";
			link.l1 = "Bene, sembra che tu non abbia voglia di ciarlare. Ci si rivede!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hai qualche storia interessante da raccontare?","È successo qualcosa di nuovo sull'isola?","Mi racconti gli ultimi pettegolezzi?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Vorrei farti qualche domanda sull'isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// --> пей до дна
		case "facio":
			dialog.text = "Sì, compare, sono quasi lucido. E questo perché ho una faccenda per te, una bella importante. E mi pare che tu sia proprio quello che può occuparsene...";
			link.l1 = "Cosa? Che hai in mente? Parla, e non farmi perdere tempo per nulla!";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "Amico, vuoi guadagnare qualche soldo? Pesos d’argento, dobloni d’oro? Posso svelarti come fare. Ma dovrai spartire con me – lavoreremo insieme, eh.";
			link.l1 = "Lo vorrei sempre, ma dipende tutto dalla tua proposta: non muovo un dito, neanche per mille dobloni, se non mi va a genio.";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "L’affare non è proprio legale, certo, ma rende... e avremo modo di dare una lezione a un tipo che si è fatto troppo schizzinoso. Non finirà in miseria, ha più dobloni di quanti ne possa contare. Tutti qui dividono con lui, ora tocca a lui ricambiare. Dimmi, reggi il rum? Quanti bicchieri riesci a buttare giù prima di strisciare sotto il tavolo?";
			link.l1 = "Dipende. Non sono certo d’aver la tendenza a bere fino alla follia... Ma insomma, mi racconti finalmente di che si tratta?";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "Sto arrivando al punto, solo che tu ancora non lo cogli. Va bene. Sarò chiaro. Sull’Isola c’è un porco grasso e ripugnante – Giuseppe Fazio. Una vera carogna. Scuoia vivi Narvali, Rivados e pure la gente del posto. Lo tengo d’occhio da un pezzo e finalmente ho qualcosa tra le mani.\nNella sua cabina a Carolina ci sono due scrigni: il primo zeppo di carte, il secondo di oro e argento. Entrambi serrati, ognuno con una chiave diversa. Quel lercio tiene sempre le chiavi addosso.";
			link.l1 = "Allora, pare proprio che tu voglia derubare Fazio? Io non ci sto a questa faccenda. E ti conviene ringraziarmi che non andrò a spifferarlo in giro. Se vuoi ficcare il naso nel baule del ciccione, trovati qualcun altro come compare.";
			link.l1.go = "facio_exit";
			link.l2 = "Ah! Interessante! Continua...";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "Che peccato, davvero una sventura... C'è oro in abbondanza, abbastanza per noi due. Va bene, ci si rivede in giro...";
			link.l1 = "Addio.";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "Due porte conducono alla sua cabina. Una di esse resta sempre sprangata. Ma la stessa chiave che apre lo scrigno col bottino apre pure quella porta. Non so che diavolo ci sia dietro, ma questi sono i fatti. Basta una chiave sola per entrare nella cabina e mettere le mani sull’oro. Logico chiedersi adesso — come si mette le grinfie su quella chiave? Ebbene, ho escogitato un piano\nUn piano sopraffino, se fila tutto liscio Fazio non capirà neanche cosa sia successo né a chi dare la colpa. Penseranno che sia stato quel ladro fantasma. Il guaio è che mi serve un socio con la testa più dura del piombo per portarla a termine. Mi segui?";
			link.l1 = "Ascolto. Continua pure.";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "A Fazio piace star seduto da Sancho a tracannare, ma la sua stazza è tale che il rum non riesce a fargli effetto. Così s’è inventato un gioco: chi lo sfida a bere più di lui. Se gli proponi la sfida, accetterà senza pensarci due volte.\nEd è qui che viene il bello. Scommetti con lui, andate in taverna, vi riempite di rum finché uno dei due non sbatte la testa sul tavolo. Se cedi prima tu, tutto il piano va a farsi benedire, io da solo non ce la faccio.\nPer questo ti ho chiesto se reggi. Se riesci a far grugnire e strillare Fazio come un maiale, considera la cosa fatta. Io resto nei paraggi. Quando lui crollerà, prenderò le sue chiavi.\nPoi trasciniamo il grassone su a letto e sgattaioliamo nella sua cabina mentre dorme. Riporterò la chiave appena svuotiamo il suo forziere, non si accorgerà nemmeno di essere stato alleggerito.\nIo mi occupo di prendere e restituire la chiave, tu devi solo ubriacare Fazio e intrufolarti nei suoi alloggi. Io farò la guardia, così se arriva qualcuno avrai tempo di scappare dalla porta sul retro.\nDivideremo il bottino a metà, così è giusto. Allora, ci stai?";
			link.l1 = "Bella trovata! E sia, proviamoci!";
			link.l1.go = "facio_6";
			link.l2 = "No, amico. Passo. Temo di non riuscire a tracannare abbastanza da restare in piedi e battere Fazio. Cerca un altro compare, più robusto di me.";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "Sono lieto d’averci visto giusto su di te. Ora vai da Fazio e organizza un incontro in taverna, stasera dopo le nove. Spero che riuscirai a far bere fino allo stremo quel maiale. Buona fortuna e ci si vede stasera!";
			link.l1 = "Ci proverò... Addio!";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = hrand(100); // итог бухалова
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "Compare, conto su di te. Stordisci quell’uomo grasso con una bevuta...";
			link.l1 = "Certo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "È fatta, quel porco grasso ronfa di sopra. Ho preso la chiave. Te la cavi bene, sembri ancora abbastanza lucido!";
			link.l1 = "Ah davvero? È passato un bel po’ dall’ultima volta che mi sono ubriacato così. La testa mi gira un poco... Andiamo?";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "Fatto, quel maiale grasso ronfa di sopra. Ho preso la chiave. Te la cavi bene, sei proprio riuscito ad affogare quel porco nel suo stesso rum...";
			link.l1 = "Ci sono stato, ma non mi sono ubriacato così da un bel pezzo. La testa mi gira come una bussola impazzita... Allora, andiamo?";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "Eh, compare, non sei riuscito a tracannare più del ciccione... Peccato. Beh, almeno ci abbiamo provato...";
			link.l1 = "M-maledizione, quello è come... un barile s-senza fondo. Argh, devo r-riprendere fiato... Basta così, v-vattene! Hic!..";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "Sì. Andiamo! Seguimi sulla 'Carolina'! E non perderti in giro, non abbiamo molto tempo!";
			link.l1 = "Andiamo!";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = "Ecco. Prendi la chiave. Il forziere che cerchi è sulla sinistra entrando. Prendi tutto quello che riesci, svelto. Non scordarti di richiuderlo. Se vedo qualcuno busserò tre volte alla porta. In quel caso scappa dalla galleria sul retro.";
			link.l1 = "D'accordo. Stai all'erta!";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// считаем деньги и дублоны взятые из сундука
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "not a single peso";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "not a single doubloon";
			else sDubl = ""+iDubl+" doubloons";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "What a miserable loot... And were we risking for it? Eh... Fine, let's share what we have got.";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "I thought that there will be much more... Risk wasn't worth it. Eh... Fine, let's share what we have got.";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "Hm. Not bad. But I thought that we will get more. Fine, let's share it.";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "Excellent! We have done well, partner! This is a whole lot of coins! Let's share!";
						else
						{
							sTotalTemp = "Wow! I haven't ever thought that the fat man's stash is so huge. Well done, partner! Let's share!";
						}
					}
				}
			}
			dialog.text = "Finalmente! Che sei riuscito a tirar fuori dal forziere di quel mascalzone? Mostramelo, che sto fremendo dalla voglia!";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "Non c'era proprio nulla. Solo qualche cianfrusaglia, amuleti e simili robacce.";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "Ho preso dal forziere "+sPeso+" e "+sDubl+"";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "Impossibile! Pare che tutto sia stato vano... Forse quel bastardo ha nascosto il suo bottino in un altro baule. Eh! Va bene, dammi la chiave e la restituirò al suo legittimo padrone, almeno finché non se ne accorgerà. Addio, compare...";
			link.l1 = "...";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "Dividiamo...";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveItems(pchar, "gold_dublon", iDubl);
			Log_Info("You have given "+iDubl+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Va bene, dammi la chiave e la restituirò al suo legittimo proprietario, almeno finché non sentirà la sua mancanza. Addio, compare...";
			link.l1 = "Buona fortuna, compare...";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("Fazio was complaining that someone has cleaned out his chest. It seems that the mysterious thief did that.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Have you heard? Fazio was robbed! He was robbed while being drunk after having a game with you.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("You have a strong head! To drink so much rum and stay on your own feet! That 's something...", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;//открыть локацию
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Davvero?... hic! Ti sto ascoltando...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei finito in questo dannato posto?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Bevi sempre? E dove diavolo trovi i dobloni per l’osteria?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Cosa puoi raccontarmi della gente del posto?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Vorresti lasciare questo posto e tornare sulla terraferma?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Sì! Giuro, non ricordo. Sì, sì, proprio no! È passato tanto tempo. Navigavo chissà dove, in qualche modo, e alla fine sono finito qui. Hic!";
			link.l1 = "Hm... Va bene, va bene.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Sì, sono un ubriacone... Bevo, maledizione, perché non ho più niente da fare... Vedi, compare, sono finito. La bottiglia di rum è tutto ciò che desidero. Quindi continuerò a bere. E i soldi... eh-eh, il rum non costa poi molto. Tanto, nemmeno devo comprarlo\nC’è un posto pieno di rum, ma bisogna nuotare per arrivarci, ecco perché compro il rum solo quando sono troppo sbronzo per nuotare... hic! Jizjezezejizeze, no, non ti dirò dove nuotare, eh-eh, nemmeno provarci...";
			link.l1 = "Meraviglioso.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Cosa posso dirti, hic... di loro? Gente brava per far due chiacchiere e tracannare insieme. Giuseppe Fazio è un pezzo grosso, un notabile da queste parti, coi forzieri pieni d’oro... eppure rispetta il vecchio Leo, gli offre da bere alla taverna. A volte, però, chiede anche qualche favore in cambio, ma niente di che, hic!\nEhi, sai quanti dobloni possiede Fazio, ahah! Basterebbero a passare il resto dei tuoi giorni nella miglior casa di tutti i Caraibi, senza lavorare e scolandoti il miglior rum del mondo. E invece resta qui, sull’Isola Giustizia. Pare che non abbia mai oro a bastanza, a quanto sembra...";
			link.l1 = "Capito...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "Andarsene? Hic! Perché mai? No, non voglio andare né sulla terraferma né su quell’isoletta disgraziata. C’è forse rum gratis? No! Non c’è rum gratis, hic! E questo vuol dire che non ho nulla da fare laggiù... Amico, qui sto proprio bene. E ti dirò di più – chiedi in giro se qualcuno vuole lasciare questo posto. Nessuno vuole, a parte due o tre, hic!";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che stai facendo lì, eh? Ladro!","Guarda un po’! Appena mi sono perso nei miei pensieri, tu hai deciso di frugare nel mio baule!","Hai deciso di frugare nei miei forzieri? Non te la caverai così facilmente!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Ti sei messo a frugare nei miei scrigni? Non la passerai liscia, mascalzone!";
			link.l1 = "Ragazza sciocca!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a riporre l’arma. Mi mette a disagio.","Sai, qui non si tollera andare in giro con la lama sguainata. Riponila.","Ascolta, lascia stare il ruolo del cavaliere medievale che corre brandendo la spada. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("Va bene.","D'accordo.","Come dite voi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la lama.");
				link.l1 = LinkRandPhrase("Va bene.","D'accordo.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Stai attento, compare, a correre con l’arma in pugno. Potrei innervosirmi...","Non mi piace quando gli uomini mi passano davanti con l’arma sguainata. Mi mette i brividi...");
				link.l1 = RandPhraseSimple("Capito.","La porto via.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
