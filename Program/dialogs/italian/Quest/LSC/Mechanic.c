// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buon dì, messere. Non vi ho mai scorto prima d’ora. Siete forse uno dei nuovi? E’ la prima volta che posate piede su questa zattera di legni perduti?";
				link.l1 = TimeGreeting()+". Il mio nome è "+GetFullName(pchar)+". Sono appena arrivato qui e sto solo guardandomi intorno per conoscere la gente...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "Ascolta, "+pchar.name+", se continui a distrarmi non finirò mai queste riparazioni.";
					link.l1 = "Sì, sì, me ne ricordo. Perdona il disturbo, amico mio!";
					link.l1.go = "exit";
					break;
				}
				// возвращение блудного скафандра
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "Ah! Guarda un po’! L’annegato è tornato dall’aldilà! Allora, dimmi, come diavolo hai fatto? Hanno già celebrato il tuo funerale e ti hanno seppellito in effigie, per caso non ne fossi al corrente...";
					link.l1 = "Peccato, non ho intenzione di crepare ancora. Il trucco è semplice – ho solo sfiorato l’idolo di Kukulcan sul fondo. Mi ha teletrasportato a Dominica, dritto al villaggio dei Caribi...";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"!";
				// квестовые ветки
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "Henrik, ho un affare per te. Un affare molto importante. Ole Christiansen mi ha parlato di te. Lo chiamano anche il Ragazzo Bianco.";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "Henrik, ti ho portato la giusta quantità di 'argento'. Proprio come volevi: uno dei tuoi più dieci pezzi in più. Su, prendili.";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "Sono di nuovo io, Henrik. Come va la tua corazza? Sei riuscito a rattopparla?";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= sti(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "Ho abbastanza metallo, quello che mi hai chiesto. Prendilo.";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "Buon dì, Henrik. Allora, la tuta è pronta per una bella immersione?";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "È finita, ho sistemato i miei guai e sono pronto a tuffarmi. Quando si comincia?";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "Ciao, Henrik. Allora, il vestito è pronto per una bella immersione?";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "Voglio restituirti il tuo completo.";
					link.l5.go = "immersion_next_2";
				}
				// квестовые ветки				
				link.l1 = LinkRandPhrase("Hai qualche storia degna di nota da raccontare?","È successo qualcosa di nuovo sull’Isola Giustizia?","Mi racconti gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l3 = "Volevo solo sapere come te la passi.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "E io sono Henrik Vedecker. Però, la maggior parte della gente qui mi chiama il Meccanico, e a dire il vero, non c’è nome più giusto.";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "Sei tu Henrik Vedecker? Felice d'incontrarti! Ti stavo cercando.";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "Devi essere davvero un uomo dai mille mestieri, vero?";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "Oh, sì, i Narvali apprezzano davvero le mie capacità. I miei attrezzi gli permettono di recuperare un bel po’ di tesori dalle navi perdute dell’anello esterno, così possono comprare provviste dall’ammiraglio Dodson.\nA dire il vero, la scienza e l’esplorazione sono la mia vera passione. Perciò scusami se non potrò dedicarti molto tempo – i miei esperimenti mi assorbono quasi tutto.";
			link.l1 = "Capisco. Non vorrò importunarla senza motivo, messer Vedecker, glielo assicuro. Sono davvero lieto di far la vostra conoscenza!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "Ah sì? E per quale motivo?";
			link.l1 = "Ole Christiansen mi ha parlato di te. Lo chiamano anche il Ragazzo Bianco.";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "Ah, quel tipo buffo! Sì, sì, lo conosco. E cosa ti ha raccontato?";
			link.l1 = "Mi scuso se la mia prossima domanda ti sembrerà sciocca ma... te la faccio comunque. Ole mi ha detto che potresti insegnarmi come immergermi sul fondo, sott'acqua. Ti prego, non ridere di me se era solo una sua fantasia.";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "È vero. Anch'io sono stato sul fondo parecchie volte. Però, ormai non m’immergo più: lo scoglio pullula di granchi giganti e, come puoi vedere, non sono più in grado di affrontarli; sono uno scienziato, non ho fiato né braccia per lottare contro quelle bestiacce. \nInoltre c’erano anche altri due uomini, due Narvali, che si tuffavano spesso, ma alla fine hanno smesso – saccheggiare le stive delle navi dell’anello esterno si è rivelato meno rischioso che scendere laggiù dove banchettano i granchi giganti.\nAdesso usano la mia attrezzatura di rado: da mesi nessuno osa più immergersi, da quando la tuta si è incrinata...";
			link.l1 = "Hai davvero una tuta con cui puoi scendere fino al fondo? Non ho sentito male?";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "Le tue orecchie non ti ingannano, giovanotto. Questa tuta l’ho ideata e costruita con le mie stesse mani. È fatta di robusta tela impermeabile inzuppata, con parti metalliche e un elmo d’acciaio che io e Jurgen abbiamo forgiato nella sua fucina.\nHo rinforzato la tuta con una piastra sul petto, ginocchiere, protezioni e stivali per tener lontani i granchi e aggiungere un po’ di peso.\nSerbatoi speciali pieni d’aria compressa ti permettono di respirare e restare un po’ sott’acqua. È un pezzo unico, e ne vado fiero come un pavone.";
			link.l1 = "Questo è magnifico. Ma hai detto che l'abito è rovinato?";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "Purtroppo è così. Diverse parti della corazza erano unite da piastre di metallo per offrire flessibilità e maggior protezione, ma l’acqua di mare le ha rovinate per davvero. Le piastre si sono arrugginite dopo anni di servizio e ora non proteggono più dall’acqua.\nMeno male che mi sono accorto del danno, così ho evitato che qualcuno ci lasciasse le penne. Anche la tuta asciutta aveva preso un po’ di sale e acqua, e ormai il loro lavoro maledetto era fatto.";
			link.l1 = "Beh... Ma puoi riparare la tuta! Puoi cambiare i vecchi pezzi arrugginiti con quelli nuovi... O sbaglio?";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "Per quale scopo? Per sostituirle di nuovo tra un anno? Hai idea di quanto sia faticoso questo lavoro? Assemblare la tuta con giunture flessibili e renderla stagna? È almeno una settimana di fatica senza tregua.";
			link.l1 = "E questa sarebbe la ragione per cui sei disposto a gettare via la tua invenzione?";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "No, certo che no. Ho un’idea. Devo fare le giunture con un metallo che l’acqua e il sale non possano corrodere. E so bene quale metallo mi può aiutare...";
			link.l1 = "Allora, qual è il guaio?";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = "Il problema è che questo metallo è assai raro. Ne ho solo un pezzo, che certo non basta. Me ne servirebbero almeno altri dieci, o magari quindici.";
			link.l1 = "E che sarebbe mai questo... metallo di cui vai cianciando?";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "Oh, questo è un metallo davvero unico, sottovalutato da troppi. Ha una durevolezza e una plasticità fuori dal comune, ed è del tutto immune agli agenti esterni – né l’acqua né il sale riescono a scalfirlo.\nForse l’avrai già visto in giro. È bianco, sembra argento, ed è per questo che gli spagnoli lo chiamarono ‘plata’. Ah! È cento volte meglio dell’argento! Meglio persino dell’oro! Un giorno lo capiranno, ma l’ora giusta non è ancora arrivata.";
			link.l1 = "Ascolta, perché non usate altri tipi di metallo allora? Perché non forgiate quelle piastre d’oro? Non ho mai sentito che l’oro arrugginisca o vada in malora.";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "Hai una mente flessibile e vivace, giovanotto. Fa piacere saperlo. Sfortunatamente, la tua proposta non regge. L’idea dell’oro è stata la prima che mi è passata per la testa. Ma l’oro è troppo molle per legare insieme le varie parti della corazza. Ahimè, solo il platino può farcela. Lavorerò solo con quello, anche se ci vorranno anni per raccoglierne abbastanza. Ma ho già visto pezzi di quel metallo sull’Isola — spesso lo confondono con l’argento, per via dell’aspetto.";
			link.l1 = "Hm. E se ti aiuto a trovare abbastanza di questo... 'argento', mi presterai la muta così che possa tuffarmi sott'acqua?";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "Non c'è bisogno di chiedere! Certo che lo farò. Ti ho già detto che non ci sarei mai andato per via dei granchi e nessun altro vuole farlo nemmeno.";
			link.l1 = "Allora mostrami questo pezzo di metallo, così capisco cosa devo cercare.";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "Allora vuoi davvero cercarlo? Ottimo. Tieni, prendi questo pezzo come esempio. Cerca qualcosa di simile tra i filoni d’argento e le pepite. Non sarà affatto facile trovarlo, ma ce la farai. L’argento ha piccole macchie scure, invece il nostro metallo è limpido e molto più duro. Il modo più semplice per riconoscerlo è graffiare una moneta d’argento su di esso: se la moneta si rovina, allora hai trovato quello che cerchi.";
			link.l1 = "Bene. Vado subito a cercarlo. Hai qualche dritta su dove dovrei cominciare a cercare?";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a platinum ingot");
			dialog.text = "Ahimè, no. Se sapessi dove trovarlo, ci sarei già andato io stesso. Ma posso darti un consiglio: cerca sulle navi dei Rivados. Non ci metto mai piede, quindi è assai probabile che ce l’abbiano loro.";
			link.l1 = "Ci penserò, Henrik. Spero che la sorte mi assista.";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "Raccogli altri dieci pezzi. È il minimo per rattoppare la muta. Buona fortuna!";
			link.l1 = "Grazie. Addio, Meccanico!";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "Ebbene, ebbene, fammi vedere... Eccellente! Ben fatto, giovanotto! È stata un’impresa ardua?";
			link.l1 = "Non proprio...";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "Ebbene, ora posso iniziare le riparazioni. Non perderò tempo e comincerò domani. Sei proprio impaziente di tuffarti, vero?";
			link.l1 = "Proprio così. Ho una gran voglia d’esplorare il fondo del mare.";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "Molto bene, perché avrò una richiesta per te quando organizzeremo la tua discesa. Ma ne parleremo più avanti. Vieni a trovarmi tra cinque giorni, spero di aver finito le riparazioni.";
			link.l1 = "Bene. Ti auguro buona fortuna!";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "La sorte serve, certo, ma per riparare l’armatura ci vorrà soprattutto maestria. E poi dovrò passare una giornata intera vicino alla fornace con Jurgen, per forgiare le piastre dal metallo che mi hai portato.";
			link.l1 = "Allora non ti disturbo oltre. Ci vediamo tra cinque giorni. Addio!";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (sti(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "Sì. Io e Jurgen abbiamo fatto un lavoro dannato e la quantità di pezzi che hai portato è bastata. La tuta è sistemata e pronta. Devo solo fare qualche prova, ma sono certo che vada bene. Torna domani alle dieci del mattino: riempirò i serbatoi d'aria e potrai fare ciò che ti pare.";
				link.l1 = "Eccellente! Non vedo l’ora. A domani, Henrik!";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Devo deluderti, "+pchar.name+".   Come temevo, il metallo non basta.   Mi serve "+FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty))+" altri pezzi per finire la riparazione. Devo chiederti aiuto ancora una volta.";
				link.l1 = "Ebbene, questa non me l’aspettavo proprio. Va bene, cercherò di scovare per te quelle pepite che ti mancano.";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "Ti aspetterò. Puoi star certo che questa somma basterà di sicuro. Porta quello che serve e finirò il lavoro in un sol giorno.";
			link.l1 = "Spero di sì... A presto!";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", sti(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "Splendido! Ora la tuta sarà rimessa a nuovo. Devo solo fare qualche prova, ma sono certo che tutto filerà liscio. Torna domani alle 10 del mattino – riempirò i serbatoi d’aria e potrai andare dove ti pare.";
			link.l1 = "Eccellente! Non vedo l’ora. A domani, Henrik!";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "the day after tomorrow";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "tomorrow";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "But I have to find Nathaniel Hawk first before I dive."; //не было разговора с Натаном
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "Sì, la tuta è pronta e gonfia d’aria. Puoi tuffarti.";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
			{
				link.l1 = "Bene. Ma non posso immergermi ora, devo risolvere una questione riguardo al mio... amico, Nathan Hawk. Non riesco a trovarlo. La tuta può aspettare un po'?";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "Splendido! Quand’è che cominciamo? Ora?";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "Certo. Può aspettare. Non starai forse cercando il tuo compare per un anno intero?";
			link.l1 = "Certo, non lo farò. Magari lo troverò già oggi stesso. Verrò a trovarti appena avrò sbrigato i miei affari con lui.";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "Sì, per favore. Vieni quando sei pronto a tuffarti.";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "Anche subito, se vuoi. Ma lascia che ti dia un paio d’istruzioni prima. Inizierai la discesa dalla piattaforma della ‘Fenice’, ci arrivi dalla poppa del San Gabriel. C’è un argano che ti porta giù e ti riporta su. È l’unica via per tornare su, quindi ficcati in testa dov’è l’argano sott’acqua e non perderti. Le bombole della tuta tengono aria per venti minuti di immersione, bada al tempo o creperai soffocato. Non allontanarti troppo dall’argano, o non ce la farai a rientrare in tempo, e che Dio ti protegga se esci dal nostro banco – ti schiacceranno piatto come una sogliola. Attento ai granchi, se ti avvicini troppo ti assalgono. Non rischiare per nulla, non potrai far fuori un branco intero e laggiù scappare non è proprio un’opzione.";
			link.l1 = "Mi occuperò dei granchi. Il resto è cosa mia. Non tuffarti troppo in fondo, non allontanarti dal verricello e non perdere il conto del tempo. Quando posso tuffarmi?";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "Quando vuoi, ma solo dalle sette del mattino fino alle nove di sera. Nell’oscurità non ci vedrai un accidente.";
			link.l1 = "Ricevuto.";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "Proprio così. Prendi la muta dalla stanza sulla piattaforma. Toglila dopo l’immersione e portamela. Io la riempirò d’aria di nuovo. Ma non provare a tuffarti più di una volta al giorno, anche solo venti minuti sott’acqua a respirare aria compressa ti rovineranno la salute.";
			link.l1 = "Ebbene, allora non mi tufferò più di una volta al giorno.";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "Sono lieto che tu comprenda. Ora vai, e che la buona sorte ti accompagni!";
			link.l1 = "Grazie!";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
			NextDiag.CurrentNode = "after_first_immersion"; // нода после первого погружения
			AddQuestRecord("LSC", "11");
			QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "Allora, perché sei ancora qui? Il completo ti aspetta.";
				link.l1 = "Sì, sì. Mi sto avviando.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Allora, com'è andata la prima immersione?";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "Eccellente, e sono ben soddisfatto dei risultati. Ho trovato un idolo di pietra nel galeone affondato. Ho sentito dire che i Rivados gli avevano fatto offerte sacrificali, tempo fa. Dimmi, Henrik, conosci qualcuno che possa raccontarmi di più a riguardo?";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "D'accordo. L'ho fatto! È stato davvero interessante, anche se un po' emozionante.";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "Vuoi sapere della nostra storia? Vai da Antonio Betancourt. Lui è nato qui. Vive sulla flûte Pluto. Se nemmeno lui ne sa qualcosa, allora nessuno può saperlo.";
			link.l1 = "Eccellente! Gli farò senz'altro visita.";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "Lascia qui la tuta. Torna domani o quando vuoi, la gonfierò d’aria io.";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Certo. Ecco il tuo abito. Grazie!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Certo. Lo porto subito!";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "Ebbene, mi hai portato il mio equipaggiamento?";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Certo. Ecco qui il tuo vestito. Grazie!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Lo farò subito!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// даем старт мини-квестам с крабикусами
			sld = characterFromId("Carpentero");
			if(!CheckAttribute(sld, "quest.crab")) sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// блок погружений, за искл. первого
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
			{
				dialog.text = "Sì, certo. La tuta è stata provata e riempita d’aria. Hai con te la cauzione? 500 000 pesos?";
				if (sti(pchar.money) >= 500000)
				{
					link.l1 = "Sì, certo. Tieni, prendi.";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "Ohi! Me ne sono proprio dimenticato. Lo porto subito...";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Sì, certo. La muta è stata provata e riempita d’aria. Controlla la piattaforma ‘Fenice’ come al solito.";
				link.l1 = "Allora mi tufferò. Grazie!";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); //открываем вход в Феникс
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;
		
		case "immersion_next_2":
			dialog.text = "Va bene. Torna domani o più tardi. Devo preparare l’abito.";
			link.l1 = "Grazie, Meccanico!";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // возврат залога
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "Avrai indietro i tuoi dobloni quando restituirai il completo. Affare fatto.";
			link.l1 = "Grazie, Meccanico! Ora mi tuffo.";
			link.l1.go = "immersion_next_1";
		break;
		// блок погружений
		
	//--------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = "Aspetta un attimo, per favore! Quale statua? A-ah, ora capisco. Intendi quell'idolo nella nave affondata 'San-Geronimo', vero? Allora le storie dei Rivados sono vere?";
			link.l1 = "Esatto! E non ci sono leggende. Conosco altri due idoli nell'arcipelago che trasportano chi li tocca, da uno all'altro, in cerchio.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Capisco, capisco. Dovrò fidarmi di te, anche se le tue parole sono pura follia antiscientifica. Teletrasporti, statue... ah! E chi mai potrebbe concepire tali cose, come diavolo funzionano?";
			link.l1 = "Fidati di me e non cercare senso qui. Non ti sto raccontando frottole.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "D'accordo. Ma spero che non ti sia perso la giubba durante quella tua sparizione, eh?";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Certo che no. In un certo senso mi ha salvato dai Caribi. Eccolo qui.";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "Certo che no. Mi ha salvato dai Caraibi, per così dire. Ma ora non ce l'ho con me.";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "Allora portamelo, maledizione! Non fiaterò finché non me lo restituisci, chiaro?";
			link.l1 = "Calmati, Meccanico. Te lo restituirò, parola di pirata!";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "Ah, davvero hai portato il mio abito! Grazie, cominciavo a preoccuparmi.";
				link.l1 = "Non c’era motivo di preoccuparsi. Ti ho dato la mia parola che te l’avrei restituito.";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "Non ti azzardare a venire qui finché non hai la mia giubba.";
				link.l1 = "Va bene, va bene.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "Molto bene. Ho già cominciato a rimuginare su come rifarne uno nuovo, ma sarebbe un lavoro d’almeno un anno intero... Mi rallegra vedere che hai avuto buon senso e mi hai riportato la mia roba tutta intera. Ti farò pure un regalo, guarda.";
			link.l1 = "Parli sul serio?";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "Certo che lo sono! Mi hai aiutato a riparare la tuta e non l’hai gettata via alla prima occasione. Te ne sei preso cura, e alla fine me l’hai riportata. Comunque, ecco una bella cassetta degli attrezzi. Impara ad usarla. Con questa potrai creare un sacco di cose utili.";
			link.l1 = "E cos'altro potevo aspettarmi dal Meccanico! Ovviamente, la cassetta degli attrezzi! Grazie mille, Henrik, sono commosso... Non meritavo un dono simile.";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("You have received a toolbox");
			PlaySound("interface\important_item.wav");
			dialog.text = "So meglio io ciò che meritavi e ciò che no. Prendi! Ti tornerà utile. Ma ti ridarò la divisa solo se giurerai cinquecentomila pesos, visto il tuo vizio di sparire con quegli idoli.";
			link.l1 = "Perdindirindina! Capisco bene... misure di precauzione...";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "Certo. E se un giorno te la filassi con il bottino? Allora quei soldi saranno la mia consolazione.";
			link.l1 = "Va bene, Henrick. Accetto. A dire il vero, pensavo che non me l’avresti più ridato.";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "Nemmeno per sogno. Prometti mezzo milione e sarà tutto tuo.";
			link.l1 = "Affare fatto! Posso allora tuffarmi come al solito? Da domani, s’intende?";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "Esattamente.";
			link.l1 = "Grazie! A presto, Henrik!";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // залог за скафандр
			NextDiag.CurrentNode = "First time";
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che fai laggiù, eh? Ladro!","Guardate un po’! Appena mi sono perso nei miei pensieri, tu hai pensato bene di ficcare il naso nel mio baule!","Hai deciso di mettere il naso nei miei forzieri? Non la passerai liscia!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei forzieri? Non la passerai liscia!";
			link.l1 = "Ragazza sciocca!...";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette i nervi a fior di pelle.","Sai, qui non si tollera andare in giro con la lama sguainata. Mettila via.","Ascolta, lascia stare il cavaliere medievale che corre brandendo la spada. Mettila via, non fa proprio per te...");
			link.l1 = LinkRandPhrase("Bene.","Certo.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di rinfoderare la lama.","Ascolta, sono cittadino di questa città e ti chiederei di rinfoderare la lama");
				link.l1 = LinkRandPhrase("Va bene.","Certo.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Fa' attenzione, compare, a correre armato. Potrei agitarmi...","Non mi piace quando la gente mi passa davanti con l’arma sguainata. Mi mette i brividi...");
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
