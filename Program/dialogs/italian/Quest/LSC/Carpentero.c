// Санчо Карпентеро - бармен
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
				dialog.text = "Non voglio parlare con te. Attacchi povera gente senza motivo e li provochi a menar le mani. Fuori dalla mia taverna, canaglia!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = ""+pchar.name+"! Che gioia vederti! Lo sapevo, lo sapevo che le dicerie erano solo menzogne! Diamine, ora dobbiamo proprio bere su questa cosa!";
				link.l1 = "Ebbene, beviamo, compare! Son dannatamente lieto di vederti anch’io!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// пей до дна
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+"Mi dispiace per la tua sconfitta. Pochi riescono a battere il grassone nel bere. Come va la testa?";
				link.l1 = "Eh, compare, hai del rum bello forte qui. Ti devo per i boccali... quant'è che ti devo?";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "Hai sconfitto Fazio, "+pchar.name+"! Son stupito, pochi sono riusciti a berlo sotto al tavolo. Tieni, prendi i tuoi duecento dobloni.";
				link.l1 = "Grazie per le parole gentili, compare!";
				link.l1.go = "drunk_win";
				break;
			}
			// крабовый салат
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
			{
				dialog.text = ""+pchar.name+" ? Dicono che ti sei tuffato negli abissi con una corazza forgiata da un meccanico Narvalo. È vero o sono solo chiacchiere, come al solito?";
				link.l1 = "È vero, compare. Ci sono andato davvero laggiù.";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Salute al nuovo arrivato nella mia taverna! Benvenuto! Qui il grog non manca mai, le mie botti di vino son piene, anche se non posso dire lo stesso del cibo, ah-ah... Scherzo. Mi chiamo Sancho Carpentero e questo posto è roba mia.";
				link.l1 = TimeGreeting()+", Sancho. Il mio nome è "+GetFullName(pchar)+" Piacere di fare la tua conoscenza.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, mio compare "+pchar.name+"! Lieto di vederti nella mia taverna! Vuoi bere qualcosa?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "Ascolta, Sancho, sai dove posso procurarmi un buon moschetto? Non una di quelle carabattole da recluta, ma qualcosa di preciso, magari per la caccia?";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "Ascolta, Sancho, ho da farti qualche domanda. Sto cercando un uomo di nome Adolf Barbier. Si dice che frequenti spesso questo posto...";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "Ascolta, Sancho, dicono che Chad Kapper ti abbia comprato dell’arsenico...";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "Sancho, vuoi che ti mostri qualcosa di curioso? È questa la maschera da pipistrello che volevi tanto acchiappare?";
					link.l7.go = "rat";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && GetCharacterItem(pchar, "gold_dublon") >= 1)
				{
					if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.ratmoney))
					{
						if(!CheckAttribute(npchar, "quest.ratmoneyagain")) ChangeCharacterComplexReputation(pchar, "fame", 5);
						link.l7 = "Sancho, sono venuto per la mia corazza. Ecco il denaro.";
						link.l7.go = "rat_3";
					}
					else
					{
						npchar.quest.ratmoneyagain = true;
						link.l7 = "Sancho, son venuto per la mia corazza. Ecco il denaro.";
						link.l7.go = "rat_take_money_not_all";
					}
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "Versami un po' di rum, Sancho.";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "Voglio restare qui stanotte.";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "Annoiato... Sancho, voglio passare il tempo qui con una bottiglia di vino fino a sera...";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("Hai qualche storia interessante da raccontare?","Che cosa è successo ultimamente sull'isola?","Qualche pettegolezzo?");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "Sancho, voglio venderti delle chele di granchio.";
					link.l10.go = "crab_trade";
				}
				link.l4 = "Sancho, voglio chiederti qualcosa sull’Isola Giustizia.";
				link.l4.go = "int_quests"; //информационный блок
				link.l5 = "No, compare. Volevo solo vedere come te la cavi in questo posto.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Anch’io, amico mio. Spero di vederti almeno un giorno sì e uno no, o magari ogni sera, ahah! Mi rallegra sinceramente avere ospiti nella mia taverna.";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "Versami un po’ di rum, Sancho.";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "Voglio restare qui stanotte.";
				link.l2.go = "room";
			}
			link.l3 = "Sancho, vorrei chiederti qualcosa sull'isola.";
			link.l3.go = "int_quests"; //информационный блок
			link.l4 = "Ci vediamo, Sancho!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "No, amico, non posso aiutarti. Vedi, sono un intenditore di boccali di birra e bottiglie di vino - ma non di moschetti, ah-ah! Vai alla bottega, ho sentito che Axel ogni tanto vende armi interessanti. Magari là trovi quello che cerchi.";
			link.l1 = "Grazie per il consiglio.";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "Adolf? Sì, viene a trovarmi di tanto in tanto, anche se non l’ho visto negli ultimi giorni. È sparito da quando ha scambiato due parole con quel grassone di Giuseppe.";
			link.l1 = "Giuseppe? Intendi forse Giuseppe Fazio?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Ah, compare, sull’Isola Giustizia c’è un solo Giuseppe – Giuseppe Fazio. Eh già, proprio lui. Se ne stavano seduti da ore a tracannare rum, a chiacchierare animatamente.";
			link.l1 = " Stavano litigando? ";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "No. Sembravano vecchi compari. Ascolta, vai da Fazio alla 'Caroline' e chiedigli di Adolf.";
			link.l1 = "D’accordo, lo farò.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "È tutto qui? Dicevi d’avere qualche domanda in più...";
			link.l1 = "Sì. Dimmi, chi sono la Rossa Mary e Marcello il Ciclope?";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "Mary la Rossa è una delle Narvali. Giovane e bella ragazza, ma totalmente selvatica, sì. Sa maneggiare la lama e la pistola come il più scafato dei masnadieri. Era la dama di Alan Milrow, un tempo capo dei Narvali, prima che l’ammiraglio lo mandasse dritto all’inferno.\nLa morte di Alan l’ha spezzata, passa le sue giornate a piangere e maledire lo Squalo nella sua cabina sulla 'Ceres Smithy'... Ma si rimetterà, la vita va avanti, per quanto crudele sia.\nDi Marcello non so molto, l’ho visto solo un paio di volte. Tipo sospetto. Si dice fosse un cacciatore reale, ha perso un occhio in una rissa e s’è dato alla vita di abbordatore.\nDetesta i pirati, pare abbia un conto in sospeso con loro. Non c’è da stupirsi, dopo anni passati ad assaltare navi mercantili.";
			link.l1 = "Capisco. Grazie di cuore, Sancho, mi hai dato proprio una gran mano!";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "Benvenuto, compare, torna pure a trovarmi e ci faremo una birra insieme...";
			link.l1 = "Certo!";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; //флаг на Джузеппе
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Kapper? No. Non ha messo piede in taverna ultimamente. Marcello Ciclope ha comprato una fiaschetta d’arsenico appena un quarto d’ora fa – pure lui tormentato dai topi. Lo capisco benissimo... Maledetti ratti.";
			link.l1 = "Marcello Il Ciclope?!";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Ebbene sì. Ti pare strano?";
			link.l1 = "No, certo che no! Lo sto cercando da qualche giorno e pare che sia stato qui di recente. Potresti dirmi dove sia andato?";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Era con Adolf Barbier, quello che abita alla 'Santa Florentina'. Forse stavano andando proprio lì.";
			link.l1 = "Grazie!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Se cerchi dell’arsenico, te ne posso vendere una fiaschetta per venti dobloni.";
			link.l1 = "Va bene. Ne parleremo dopo, Sancho. A presto!";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // ноду Акуле
			// важный момент! От дальнейшего поведения геймера зависит результат
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
			// закрываем вход к Фацио
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// пей до дна
		case "drunk_fail":
			dialog.text = "Andiamo, compare! Non mi devi nulla. Hai già perso cento dobloni. È stato un errore trafficare con Fazio...";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "No-no, Sancho! Grazie e prendi pure queste cinquecento pesos. Dovrebbero bastare per pagare da bere, se la memoria non m'inganna. Non voglio restare tuo debitore.";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "Eh, grazie, Sancho. Hai ragione.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You have received 200 doubloons");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// крабовый салат
		case "crab":
			dialog.text = "Hm... allora ho una proposta per te. Hai mai visto quei granchi giganti laggiù?";
			link.l1 = "Ho visto granchi? Ce n’erano a frotte! E di quale proposta parli, di grazia?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Se ammazzi qualche granchio, portami pure le loro chele. Ti pagherò bene in dobloni – cinque monete per ciascuna. Axel Yost non ti darà mai così tanto, fidati. Non ti sto chiedendo di andare a caccia di granchi apposta – ma se ti capita di incontrarne qualcuno, tienilo a mente...";
			link.l1 = "Perché le chele? E le altre parti del granchio? Che ci fai con quelle?";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = "Perché le chele? Perché lì si trova quasi tutta la carne. Le zampe dei granchi non hanno granché, e il corpo è coperto da un duro carapace. Qui la carne di granchio è una vera leccornia: ha un sapore sopraffino ed è molto nutriente.\nIn più, possiedo una ricetta unica per cucinarla, quindi ti pagherò cinque dobloni per ogni chela che mi porti.";
			link.l1 = "Va bene. Terrò a mente, non temere.";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "Splendido! Quanti ne possiedi?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			link.l1.go = "crab_trade_1";
			link.l2 = "Ho cambiato idea.";
			link.l2.go = "exit";
		break;
		
		case "crab_trade_1":
			dialog.text = "Affare fatto. Prendi pure i tuoi dobloni - "+FindRussianQtyString(iTotalTemp*5)+"Grazie, compare, se ne trovi ancora, portameli.";
			link.l1 = "Certo, amico.";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+iTotalTemp*5+" doubloons");
		break;
		
		// крыс
		case "rat":
			dialog.text = "Cosa?! Fammi vedere! Mostramelo subito!";
			link.l1 = "Certo.";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Eccolo... È proprio lui! Identico a quello del disegno che mi fece quel marinaio! Amico, dev’esserci un motivo se l’hai portato qui da me, che vuoi in cambio? Quanto chiedi?";
			link.l1 = "Certo che te l’ho portata per un motivo. Ma quanto alla ricompensa, che mi dai in cambio? Se la memoria non m’inganna, mi avevi promesso una ricompensa regale per questa cosuccia...";
			link.l1.go = "rat_2";
			link.l2 = "Mi spiace, compare, non è in vendita. Mi serve a me. Volevo solo esser certo che questo sia il talismano di cui parlavi.";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "Eh, che peccato... Sì, ragazzo, proprio quel talismano. Bel colpo, maledetto fortunato! Ora quei topastri non ti daranno più noia. E io dovrò ancora sterminarli con l’arsenico...";
			link.l1 = "Perdonami se ti ho preso in giro, Sancho. Non l'avevo mai visto prima, quindi avevo bisogno di un parere. Scusami davvero.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = "Per questo,"+pchar.name+", ti offro la possibilità di acquistare il pezzo più pregiato e raro che posseggo. Sarebbe uno scambio degno per questo amuleto, soprattutto per un guerriero d’animo come te. Lascia che te lo mostri.\nGuarda qua: una corazza di Milano unica, magnifica, forgiata con arte! Ti protegge in battaglia senza intralciare i movimenti, leggera e comoda da indossare. Una corazza di questa fattura è merce rara sia nei Caraibi che nel Vecchio Continente.\nMi capitò tra le mani anni fa, nella cabina di un capitano spagnolo, e l’ho conservata proprio per un momento simile. Te la cedo per duemila monete d’oro... e il Dio-Ratto!";
			link.l1 = "Hmm... Questa È davvero una corazza eccellente! Direi che lo scambio mi va a genio. Mi occuperò io dei topi, ma trovare un’altra corazza simile sarebbe quasi impossibile. Non ne ho mai vista una così prima d’ora. Davvero, è un pezzo d’armatura unico.";
			link.l1.go = "rat_yes";
			link.l2 = "Quanto? Sancho, i tuoi topi ti hanno già morsicato stamattina? Come sarebbe a dire, duemila? Hai idea di cosa mi sia costato procurarti quest’idolo? Abbassa subito il prezzo!";
			link.l2.go = "rat_torg";
			link.l3 = "Quanto?! Sei peggio di uno squalo, lo sai, Sancho? 'Offri una possibilità d'acquisto!' Ha! Per quei soldi potrei farmi forgiare un'armatura sulla terraferma che mi parerebbe i proiettili e mi guarirebbe pure! E tu che faresti con tutto quell’oro? Ti faresti scolpire una statua da Jurgen e la metteresti in bella mostra sul ‘San Agustin’ a grandezza d’uomo?";
			link.l3.go = "rat_no";
		break;
		
		case "rat_yes":
			dialog.text = "Sono lieto che tu sia dei nostri, amico mio. Grazie per non aver scordato il mio cruccio! Allora, aspetto i miei dobloni. L’armatura ti starà aspettando.";
			link.l1 = "Li porto qui tra poco!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 2000;
		break;
		
		case "rat_torg":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				notification("Skill Check Failed (60)", SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", in altre circostanze ne chiederei cinquemila. Persino l’ammiraglio ci ha messo gli occhi sopra, e non è l’unico, credimi. Prenditi il tempo che vuoi per decidere. L’armatura ti aspetterà quanto serve. La venderò solo a te.";
				link.l1 = "Ci penserò, Sancho. Ci rifletterò a lungo e con attenzione.";
				link.l1.go = "rat_yes_1";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", in altre circostanze, ne chiederei cinquemila. Persino l’ammiraglio si è interessato alla faccenda, e non è l’unico, credimi. Va bene, ti tolgo cinquecento, visto che non ti sei scordato di me e dei miei guai. Pare che ci siano state delle belle avventure per strada.";
				link.l1 = "Così va meglio. Ma continuo a non capire perché dovrei pagare di più in questo scambio di tesori altrettanto rari. Forse dovresti essere tu a allungare qualche moneta a me, eh Sancho?";
				link.l1.go = "rat_yes_1500";
				AddCharacterExpToSkill(pchar, "Commerce", 100);
			}
		break;
		
		case "rat_yes_1500":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
			{
				notification("Skill Check Failed (90)", SKILL_COMMERCE);
				dialog.text = "No, "+pchar.name+", non se ne parla proprio. Ai topi posso pensare con il veleno, ma questa corazza potrebbe salvarti la pelle un giorno. E ti farà sembrare un duca italiano, indossandola. Millecinquecento, questa è la mia ultima offerta. Prenditi pure il tempo che vuoi per pensarci e fammi sapere. L’armatura ti aspetterà finché vorrai, la venderò solo a te.";
				link.l1 = "Sancho, se non fossi l’unico oste in questa lugubre necropoli… Ci penserò sulla tua proposta.";
				link.l1.go = "rat_yes_1500exit";
				AddCharacterExpToSkill(pchar, "Commerce", 600);
			}
			else
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "Per un capitano di ventura e un filibustiere, hai la parlantina giusta per gli accordi! Ti ricordi di Jost? Quello riuscì a prendersi tutto il mio arsenico a prezzo stracciato, mentre i topi già mi rosicchiavano i piedi. Va bene, "+pchar.name+", hai vinto. Ti tolgo altre cinquecento monete! Ma questa è la mia ultima offerta!";
				link.l1 = "This still feels like a rip-off, but at least now I won't feel like a typical damsel in distress in the jungle. Wait for the money; I'll bring it soon.";
				link.l1.go = "rat_yes_1000exit";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
		break;
		
		case "rat_no":
			dialog.text = "Calmati, "+pchar.name+"Da chiunque altro avrei preteso cinquemila! Perfino l’ammiraglio s’è fatto avanti, e non è il solo, puoi fidarti. L’armatura t’aspetterà finché vorrai. Pure questo è compreso nel prezzo dell’idolo.";
			link.l1 = "Che onore! Continua a lucidare quei bicchieri, ed io mi levo di torno. Duemila!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1500exit":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1500;
		break;
		
		case "rat_yes_1000exit":
			Achievment_SetStat(106, 1);
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1000;
		break;
		case "rat_3":
			dialog.text = "Fatto! Son lieto che tu abbia accettato, compare. Ti ringrazio di non aver scordato il mio guaio! Prendi la corazza, che ti serva bene in battaglia.";
			link.l1 = "Tieni, prendi anche il tuo talismano – pare che tempi oscuri stiano calando sui topi della tua taverna!";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.ratmoney));
			Log_Info("You have given away the talisman 'God of rats'");
			Log_Info("You have received a Milanese armor");
			Log_Info("You gave "+FindRussianDublonString(sti(npchar.quest.ratmoney))+"");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.ratmoney");
			if(CheckAttribute(npchar, "quest.ratmoneyagain"))
				DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;
		
		case "rat_take_money_not_all":
			npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - GetCharacterItem(pchar, "gold_dublon");
			Log_Info("You gave "+FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon"))+"");
			RemoveItems(pchar, "gold_dublon", GetCharacterItem(pchar, "gold_dublon"));
			PlaySound("interface\important_item.wav");
			dialog.text = "Mi lasci ancora senza fiato "+FindRussianDublonString(sti(npchar.quest.ratmoney))+", "+pchar.name+".";
			link.l1 = "Non me lo rammentare!";
			link.l1.go = "exit";
		break;
		
		//--> информационный блок
		case "int_quests":
			dialog.text = "Ascolto.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Che razza di posto è questo? Puoi raccontarmi qualcosa in più?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Come posso lasciare l’Isola Giustizia?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Cosa dovrei sapere dell’Isola Giustizia?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "E come te la cavi qui? E la tua taverna, va tutto a gonfie vele?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Non ho domande, lascia stare...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Questo posto? Beh, la chiamano Isola Giustizia, l’Isola delle Navi Perdute, o la Città delle Navi Abbandonate – ma noi la chiamiamo semplicemente l’Isola. È fatta di relitti incagliati su una secca tra le scogliere. La parte centrale dell’Isola è abitata, il cerchio esterno resta deserto. Da dieci anni nessuno qui ha più contatti col mondo di fuori.";
			link.l1 = "Capito...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Costruisci una scialuppa o una zattera, ma finirà male per te. C’è una tempesta d’anomalia che avvolge l’Isola, non supererai l’anello esterno senza rischiare la pelle. Inoltre, la corrente qui intorno è feroce.\nTi serve una ciurma se vuoi anche solo una briciola di speranza di sopravvivere. Ma pochi tra gli isolani hanno voglia d’andarsene. E ancora meno sono pronti a rischiare il collo. Qui la gente s’è abituata a questa vita. Chiedi in giro, se non ci credi.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Prima di tutto, rammenta che sull’Isola Giustizia ci sono zone proibite. Due clan – i Narvali e i Rivados – vivono qui da tempi remoti, si scannano tra loro e difendono con le unghie e coi denti ciò che credono loro. Se ci metti piede senza invito, sei carne morta.\nPer entrare nei loro domini serve la parola d’ordine del momento. Non temere d’inciampare per sbaglio, le sentinelle ti daranno più d’un avvertimento prima di farti assaggiare il piombo.";
			link.l1 = "Lo terrò a mente...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "You know, my friend, it's fine. I used to work with food and drinks: I worked as a cook a long time ago in Europe, as an intendant in a garrison, a tavern keeper, and a cook on a ship; so the first thing I did here was establishing a tavern\nI like my job and my life is oddly satisfying. Folks are friendly here, mostly. At least they don't kill each other frequently. Clans don't interfere with my activities. All in all, this the best place I've had my life. I'm free here and no one tells me what to do\nThe only thing driving me mad are rats. They torture me, eating my provisions and ruining my tableware. I have trouble getting rid of them.";
			link.l1 = "Topi? Eh già, sono la piaga di tutti qui...";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Ahimè, sono la persona più sfortunata dell'Isola quando si parla di topi. Sulle altre navi non fanno così paura, e Axel Yost è riuscito a liberarsene una volta per tutte, chissà come. Ma io... qui ho eserciti di topi che mi marciano addosso. Eh, mi hanno detto che esiste uno strano amuleto chiamato il Dio dei Topi.\nPare sia una maschera con muso di pipistrello. Si dice che quest'amuleto faccia scappare i topi a gambe levate. Scommetto che qualcuno l'ha rifilato ad Axel, quello compra e rivende ogni ciarpame trovato sull'anello esterno.\nSe qualcuno mi portasse quell’amuleto... gli darei una ricompensa da re!";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//<-- информационный блок
		
		//--> выпивка
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = ""+pchar.name+", Credo che dovresti smettere. Dio non voglia che ti metti nei guai o finisca in pasto ai granchi... Non è saggio bere troppo da queste parti, molti ci hanno lasciato la pelle per questo.";
				link.l1 = "Hm... Suppongo tu abbia ragione, Sancho - ne ho già avuto abbastanza. Grazie per la tua premura!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
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
				
				dialog.text = "Benvenuto, compare. Solo venticinque pesos per una pinta del mio miglior rum!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Ebbene, alla tua salute e alla prosperità della tua taverna, compare!","Ebbene, a chi naviga tra le onde!","Ebbene, agli abitanti della vostra Isola Giustizia!"),LinkRandPhrase("Ebbene, all’Isola Giustizia, e che possa durare in eterno!","Ebbene, che il vento ci sia sempre propizio in ogni nostra impresa!","Ebbene, alla fortuna, alla gioia e... alle donne!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Non credo sia saggio bere adesso, fidati di me...";
				link.l1 = "Va bene.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				dialog.text = "Ehi, sei proprio un tipo strano... Non hai nessuno con cui passare il tempo qui, sull’Isola Giustizia? Amico, Mary mi farebbe la pelle se ti lasciassi qui a ubriacarti da solo. Vieni la sera con compagnia e goditi la baldoria fino all’alba, se ti va.";
				link.l1 = "D'accordo...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Nessun problema, compare. Per solo trecento pesos ti procuro una bottiglia pregiata di "+LinkRandPhrase("Spagnolo","Italian","Francese")+" vino - e divertiti finché ti pare.";
				link.l1 = "Grazie!";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//<-- выпивка
		
		//--> сон в таверне
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Non credo sia il momento di dormire adesso. Fidati di me...";
				link.l1 = "Bene.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				if(!isDay())
				{
					dialog.text = "Non ho mai incontrato un uomo così bizzarro. C'è una bella fanciulla che l'aspetta nella 'Forgia di Cerere', e lui invece vuole passare la notte all'osteria. Non ti far venire in mente che ti lasci dormire qui, neh. Mary mi farebbe la pelle.";
					link.l1 = "D'accordo...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Puoi riposarti di sopra fino a sera. Ma non ti permetterò di passare la notte qui – Mary mi ammazzerebbe per questo. Mi dispiace...";
					link.l1 = "D'accordo. Resterò qui fino a sera...";
					link.l1.go = "hall_night_wait";
					link.l2 = "Va bene... Me la caverò senza chiudere occhio.";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "Puoi dormire nel letto al piano di sopra per soli venti pesos. Quando vuoi che ti svegli?";
			if(!isDay())
			{
				link.l1 = "Al mattino.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "Prima che cali la notte.";
				link.l1.go = "hall_night_wait";
				link.l2 = "La mattina seguente.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "Ho cambiato idea. Non ho più voglia di dormire.";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
