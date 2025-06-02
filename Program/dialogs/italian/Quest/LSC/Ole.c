// Оле Кристиансен - Белый Мальчик
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
			dialog.text = "Cosa vuoi, forestiero?";
			link.l1 = "Niente.";
			NextDiag.TempNode = "First time";
		break;
		
		// в магазине - первая встреча
		case "store":
			dialog.text = "Ops... Salve, zio. Hai una perla bianca? Dammi la perla bianca...";
			link.l1 = "Hm. Buon dì. Sei tu... il Ragazzo Bianco?";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "Perla! Perla bianca per il ragazzo bianco! Ce l’hai una perla bianca, zio?";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Hmm, non ho perline, ma posso darti questa perla. È bianca, proprio come una perlina. Ti va bene lo stesso?";
				link.l1.go = "store_2";
			}
			link.l2 = "No, non ho perline, né bianche né rosse. Non sono né una donnicciola né un selvaggio da andare in giro con perline. Dimmi...";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "Perla! Perla bianca! Niente perla - niente chiacchiere. Brutto zio... Dammi una perla!";
			link.l1 = "Maledetto! Che tipo fuori di testa! L’Occhio di Serpente e Chimiset avevano ragione – ha la testa vuota... Ma che perla va cercando, lui?";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "Dai una perla, zio. Bravo zio... Perla bianca!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Ecco, prendi la tua perla. È questo che volevi?";
				link.l1.go = "store_2";
			}
			link.l2 = "Ah, maledizione...";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Sì, sì! È proprio lei! Lo zio mi ha dato una perla! Grazie, brav’uomo! Ora Ole ha una perla in più. Presto rivedrò la mamma...";
			link.l1 = "Sono felice per te. Allora, possiamo parlare adesso?";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "Certo, brav'uomo. Sei davvero un brav'uomo, zio? Noi saremo amici. Ole sarà lieto di fare due chiacchiere. Come ti chiami?";
			link.l1 = "Il mio nome è "+pchar.name+"Ehilà, un uomo mi ha parlato di te, ma ormai non c’è più. Diceva che gli hai dato una mano, e che potresti aiutare anche me.";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "Lo zio ha dato una perla a Ole – è proprio un bravo zio. Ole ama aiutare la brava gente. Di brave persone ce n’è poche – zii malvagi ovunque. Ti aiuterò, certo. Mi piace dare una mano.";
			link.l1 = "Bene! Ormai siamo amici, mio vecchio. Dimmi, ricordi forse un uomo dalla pelle rossiccia e un cappello magnifico, adorno di piume? Mi ha detto che un tempo tu gli salvasti la pellaccia.";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "Ricordo quel zio. È un brav’uomo. L’ho salvato io. L’ho portato alla statua. E da poco ho salvato un altro brav’uomo dalla stiva con le provviste. L’ho strappato via dagli zii del cattivo ammiraglio. Quelli l’avrebbero fatto fuori. Volevo portare anche lui alla statua, ma m’ha rifiutato. Senza mezzi termini.";
			link.l1 = "Dalla stiva, dici? Eh, credo di sapere di chi parli... E conosco quel vecchio furfante. Dimmi, Ole, chi è quest’uomo che hai salvato?";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "Si chiama zio Nathan. È malato, maledettamente malato. A malapena riusciva a camminare quando Ole l’ha trovato.";
			link.l1 = "Certo... È strano che sia riuscito a farlo davvero.";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "No, non è strano. L’ho trovato e gli ho dato un po’ di rum infuocato. Sono entrato a nuoto nella stiva perché su quella nave c’è da mangiare. I cattivi chiudono sempre la porta, ma io la apro ogni volta. Eh eh eh... Sciocchi bastardi. Attirano i granchi, lo so bene. Mascalzoni...\nSono arrivato lì e ho trovato Nathan. Stava male. Avevo il rum infuocato – gliel’ho fatto bere, così s’è rimesso. Poi gli ho dato anche la tintura, ne porto sempre una con me, per quando i granchi maledetti mordono il vecchio Ole. Il buon zio Chimiset mi ha detto di fare così...";
			link.l1 = "Gli hai dato l’antidoto e del rum? Eh, non sei lo sprovveduto che tutti credono. Bravo, Ole.";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "Gli zii malvagi pensano che Ole sia uno sciocco e lo prendono in giro: Ole il tonto... Ma Ole non è uno sciocco, deve solo raccogliere tutte le perle bianche, altrimenti sua madre lo scaccerà. Mi darai un’altra perla più tardi?";
			link.l1 = "Hm... Certo, Ole, siamo amici. Dimmi, come pensavi di mandare Hawk... zio Nathan alla statua. Zio Chimiset mi ha detto che fu affondata insieme alla nave...";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "La statua sta sul fondo. Ole lo sa. Ma non è profondo e il buon zio Henrik può mandarci lo zio Nathan. Zio Henrik sa camminare sott’acqua. Ma ci sono un sacco di granchi spaventosi. Ole li teme. Mordono che fa un male cane.";
			link.l1 = "Zio Henrik? Chi sarebbe costui?";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "Zio Henrik vive tra i malvagi zii Narvali. Tutti lo conoscono. Sa camminare sott’acqua e insegna agli zii Narvali come immergersi laggiù. Zio Henrik è buono, ha regalato una perla bianca a Ole.";
			link.l1 = "E come ti lasciano entrare i Narvali? O il loro territorio è forse aperto per te?";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "Ih ih... I brutti zii non lasciano Ole entrare, ma Ole può infilarsi in ogni stanza delle loro navi di notte. Sono grossi e rumorosi, ma Ole è silenzioso e attento. E ho incontrato zio Henrik mentre nuotavo intorno alla nave da cui zio Henrik si tuffa. Zio Henrik ha dato a Ole una perla bianca e ora siamo amici.";
			link.l1 = "Interessante... Anch'io vorrei diventare amico dello zio Henrik.";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "Vuoi tuffarti e raggiungere la statua? Sta laggiù, nel relitto della vecchia nave. Ci sono un sacco di granchi grossi e minacciosi. Non ti fanno paura? Possono mordere, sai.";
			link.l1 = "No, non li temo. Ne ho già fatto fuori uno, quindi farebbero meglio ad aver paura loro di me.";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "Oh, "+pchar.name+" Sei davvero coraggioso! Allora dovresti andare dallo zio Henrik, lui ti insegnerà a camminare sul fondo e potrai far fuori ogni granchio laggiù. Troverai anche un’altra grossa perla per Ole. giusto?";
			link.l1 = "Certo, lo farò. Ma prima devo trovare zio Henrik.";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "E perché lo cerchi? Sta sulla nave chiamata 'San Gabriel', nella bottega. Ma i maledetti Narvali potrebbero non accoglierti a braccia aperte.";
			link.l1 = "Mi occuperò io stesso dei maledetti zii. E un’ultima domanda: dov’è ora zio Nathan? Lo sto cercando ed è proprio lui la ragione della mia venuta qui.";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "Nascondo lo zio Nathan nel mio rifugio sulla 'Fernanda'. È lontana e nessuno ci vive. Tutti pensano che affonderà presto, ma Ole sa il contrario. Ho salvato lo zio Nathan e l'ho portato lì.  È ancora molto malato e si scola rhum infuocato tutto il tempo. Cammina a malapena e non riesce a sollevare nulla che pesi più di cinque libbre. Mi dispiace per lo zio Nathan, gli porto il rhum dai forzieri e il cibo dalla stiva dei cattivi dell'ammiraglio. Gli cucino pure i topi che catturo. Topi gustosissimi!";
			link.l1 = "Ratti saporiti, eh? Capisco. Dunque, Nathan sta su una nave che si chiama... come hai detto? La 'Fernanda'? Non la conosco, quella...";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "Zio "+pchar.name+", ti ho appena detto che non è lontano da qui. Devi nuotare per arrivare da lei. Ha una porta a poppa, ma zio Nathan non la apre mai. Ole gli ha detto di non farlo. Però, se sei amico di zio Nathan, ti dirò come aprirla. Bussa così: toc-toc... toc-toc. Allora ti aprirà.";
			link.l1 = "Me ne ricorderò. Grazie, vecchio lupo! Mi hai davvero tolto dai guai! Non so proprio come sdebitarmi.";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "Portami un'altra perla bianca. Se mai riuscirai a trovarla, s'intende.";
			link.l1 = "Ah, sì! Perline bianche! Bene. A presto, Ole!";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ноду и вякалку Натану
			pchar.questTemp.LSC.DiffIndoor = "true"; //атрибут прохода к Натану
			pchar.questTemp.LSC = "mechanic"; // флаг на разговор с Механиком
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "Ah, zio "+pchar.name+"! Felice di vederti! Come te la passi?";
			link.l1 = "Grazie, Ole, sto bene. Anche per me è un piacere vederti.";
			link.l1.go = "exit";
			link.l2 = "Ascolta, Ole, hai detto che i pirati dell’ammiraglio chiudono la porta della stiva e tu la riapri sempre... Tutti i forzieri lì sono serrati e hai detto che prendi il rum per zio Nathan da quelli. Come diavolo ci riesci?";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "Ole possiede un mazzo di chiavi pregiate. Aprono ogni porta o scrigno. Beh, non tutte... Alcune restano chiuse, ma la maggior parte si lascia domare. Ole le ha scovate nella cabina dello zio Jurgen, quel maledetto. Lui lavora ogni giorno col suo martello vicino al forno; fabbrica serrature e chiavi. E poi forgia anche quei moschetti grossi e minacciosi per i maledetti Narvali.";
			link.l1 = "Capisco. Ole, puoi vendermi quelle chiavi? Posso pagartele...";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "Va bene, zio "+pchar.name+", Ti venderò le chiavi. Mi terrò solo quella per me. Apre la stanza dell’ammiraglio. C’è un bel po’ di cibo e rum per lo zio Nathan. Tanto nei forzieri non è rimasto né una perlina né una goccia di rum.";
			link.l1 = "Quanto vuoi per loro?";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "Prima di tutto, raccontami, zio "+pchar.name+", hai una grossa nave?";
			link.l1 = "Sì, l'ho vista. Ma non è qui, sta al cerchio esterno. Però presto lascerò quest'isola e tornerò su questa dannata zattera con la mia gran nave, per lo zio Nathan.";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "Per zio Nathan? Oh, che meraviglia! Ascolta, allora promettimi che mi porterai via di qui sulla tua grande nave, lasciandomi navigare con te finché ne avrò bisogno. Posso rendermi utile. So prendere e cucinare i topi... Inoltre, dammi cinque perle bianche. E ti darò le chiavi.";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Certo! Ecco le tue perle. Prendile.";
				link.l1.go = "lock_4";
			}
			link.l2 = "Per acchiappare e cucinare topi? Eh! Una dote curiosa. D’accordo, vecchio mio, affare fatto. Ti porterò cinque perline e la mia parola.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "Ah, zio "+pchar.name+"! Felice di vederti! Come butta il vento?";
			link.l1 = "Grazie, Ole, sto bene. Son lieto di rivederti anch’io.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Ti ho portato cinque perle bianche per le tue chiavi.";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "Perle! Perle bianche! Zio "+pchar.name+"  ha dato perline a Ole! Presto ti vedrò, mamma!... Zio "+pchar.name+", mi prometti che mi porterai via da qui quando tornerai?";
			link.l1 = "Lo farò, Ole. Non ho ancora mangiato topi. Ti porterò con me.";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "Grazie, grazie, buon zio "+pchar.name+"Prendi pure le tue chiavi. Usarle è un gioco da ragazzi: infilale una за другой, и пробуй. Prima o poi una aprirà la serratura che ti serve. Se non funziona, vuol dire che quella serratura è davvero furba — ti servirà una chiave particolare, senza dubbio.";
			link.l1 = "Capisco. Suppongo che me ne occuperò io.";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "Aspetta, zio "+pchar.name+"! Ho trovato un'altra chiave. È bella e astuta. Il maledetto zio Jurgen non fabbrica chiavi come questa. Non so cosa apra, ma forse tu lo scoprirai. Guarda, è proprio una chiave graziosa, scommetto che non hai mai visto nulla di simile.";
			link.l1 = "Mostrami... Sì, la chiave è davvero intrigante. Ma a cosa serve, se non sai quale serratura apre?";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "Zio "+pchar.name+", , sei davvero strano. A che serve tutto ciò? Se c’è la chiave, da qualche parte dev’esserci la serratura. Se c’è la serratura, da qualche parte dev’esserci la moneta. Ho trovato la chiave sull’isola. Significa che anche la serratura è qui. Su questo non v’è dubbio. È una chiave astuta, e solo cose di gran valore vengono protette da simili chiavi. Ole lo sa.";
			link.l1 = "A dir la verità, sei proprio buffo, Ole. Va bene, lo prendo. Vuoi delle perline in cambio?";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "Sì, Ole vuole cinque perline. Le darai, zio? "+pchar.name+"?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Ecco, prendi queste perle.";
				link.l1.go = "key";
			}
			link.l2 = "Non li ho adesso, ma ti porterò delle perline, te lo prometto.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Perle! Perle bianche per il ragazzo bianco! Per la sua mamma! Tieni, zio "+pchar.name+", prendi la chiave. E troverai la serratura, Ole lo sa. Sei coraggioso, non temi nemmeno quei granchi spaventosi.";
			link.l1 = "Oh, non farmi ridere, vecchio lupo! Grazie per la chiave. Ci si rivede in giro!";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "Ah, zio "+pchar.name+"! Felice di vederti! Come te la passi?";
			link.l1 = "Grazie, Ole, sto bene. Anche per me è un piacere vederti.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Ti ho portato cinque perle bianche per la tua chiave.";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "Ah, zio "+pchar.name+"! Lieto di vederti! Come te la passi?";
			link.l1 = "Grazie, Ole, sto bene. Anche io son lieto di rivederti.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "Oh, zio "+pchar.name+", sei tornato! Sei tornato sulla grande nave! Mi porterai via da qui? Zio "+pchar.name+", mi hai dato la tua parola, ricordi?";
			link.l1 = "Certo che sì, vecchio lupo di mare. Benvenuto a bordo! Immagino che i topi siano nei guai, ah-ah!";
			link.l1.go = "return_1";
			link.l2 = "Davvero? E quando mai ti avrei promesso una cosa simile? Non ricordo d’aver fatto tali promesse...";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "Grazie, zio! Ole sarà utile, vedrai! Oh, forse rivedrò la mamma? Vado subito!";
			link.l1 = "Non correre così, Ole. Puoi mettere insieme la tua roba con calma. Non ho nessuna fretta di salpare.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "Mi avevi promesso, sì! Avevi giurato di portar via Ole da questo dannato posto! Maledetto zio! Hai imbrogliato Ole! Zio infame!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // Мэри
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // иначе завершение
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		break;
		
		// Блудный сын
		case "givemepearl":
			dialog.text = "Zio, zio... Mi serve ancora una perla bianca. Per favore, regala una perla bianca a Ole!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Sapevo che l’avresti chiesto. Tieni, prendi la tua perla. Contento adesso?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Oh, e che scocciatura... Non ho più perline, Ole, non ne ho proprio!";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "Grazie! Bravo, bravo zio "+pchar.name+"! Ole ha ancora una perla e non ne sono rimaste molte! E io andrò dalla mamma...";
			link.l1 = "Oh, e perché sei così strambo...";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = sti(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "Grazie per la perla, buon zio "+pchar.name+"!";
			link.l1 = "Sei il benvenuto...";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "Nessuna perla? Ma com’è possibile, zio "+pchar.name+"?! Solo qualche perlina ancora… Devo raccoglierle. Se è così, scenderò a terra. Andrò in cerca di perline…";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "E dove pensi di andare? Che farai da solo? No, non voglio portare il peso del tuo destino sulla coscienza. Aspetta, fammi controllare le tasche... Ecco! Prendi questa perla e resta con me. Va bene così?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "È tuo diritto, Ole. Se ti sei stancato di navigare con me, non ti tratterrò. Avevamo un patto. Però hai dato la caccia a quei bastardi proprio bene...";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "Addio, zio "+pchar.name+". Ole ha bisogno di perline bianche, altrimenti non tornerà mai da sua madre...";
			link.l1 = "Oh, mi dispiace davvero per te, ma che ci posso fare? Vai, vecchio mio. Buona fortuna.";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // Оле уходит - квест не довели до конца
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "Zio "+pchar.name+"! Mi serve ancora una perla bianca. L’ultima, ti prego. Dalla a Ole!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Sapevo che me l’avresti chiesto. Tieni, prendi la tua perla. Contento adesso?";
				link.l1.go = "mother_1";
			}
			link.l2 = "Oh, che scocciatura... Non ho più perline, Ole, non ne ho proprio!";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Grazie, grazie, buon zio "+pchar.name+" Ora Ole ha tutte le perline. Sì, tutte quante! Ora Ole può portarle alla mamma e lei non manderà Ole via...";
			link.l1 = "Ascolta, chi è quella madre di cui parli sempre? E spiegami finalmente perché ti servono quelle perle... quei grani bianchi? E cosa vuol dire che li possiedi tutti?";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "Bravo zio "+pchar.name+" ha aiutato Ole a raccogliere perline per sua mamma... Ole era piccolo quando strappò la collana di perle bianche di mamma. Tutte caddero in mare. Mamma si arrabbiò tanto con Ole, e lui non può tornare a casa finché non avrà raccolto tutte le perle perdute\nMi ricordo quante erano. Cinque volte dieci perle. Ora Ole le ha tutte. Zio "+pchar.name+"Ti prego, portami a casa! Voglio far felice la mamma, restituire le perline. Portami a casa!";
			link.l1 = "Per mille tempeste, che storia incredibile... Sei arrivato sull’Isola quand’eri ancora un moccioso. Ti hanno cacciato da casa perché hai rotto la collana di perle di tua madre? Roba da far accapponare la pelle...";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "Portami da mia madre, buon zio "+pchar.name+". Voglio vederla. Sarà lieta di ricevere queste perline.";
			link.l1 = "Mi piacerebbe, ma sai dov’è casa tua? Dove vive tua madre?";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "Vive sull'isola, nella casa dal tetto rosso.";
			link.l1 = "Davvero! Hai idea di quante isole ci siano qui e quante case col tetto rosso? Come si chiama quest’isola? Dammi qualche dettaglio...";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "Non so come si chiama. So che era un’isola, la mamma diceva al papà che stavamo sull’isola! E abitavamo in una casa col tetto rosso. Bella casa, grande. Portami dalla mamma, zio "+pchar.name+"  Ti prego...";
			link.l1 = "Oh, va bene. Cercheremo una casa simile su ogni isola e chiederemo di tua madre. Come si chiama?";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "Il suo nome? Sei proprio strambo, compare "+pchar.name+". Il nome di mia madre è madre. Il nome di tua madre è diverso?";
			link.l1 = "Oh, Dio, dammi la forza... Va bene, Ole. Cercheremo la tua dimora. Ora vai alla nave.";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "Grazie, zio "+pchar.name+" Sei davvero, davvero gentile e buono! Presto Ole rivedrà la mamma!";
			link.l1 = "Oh...";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ставим Агнес Кристиансен и открываем ее дом в Мариго
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "Mamma... Mamma, mama! Son tornato!";
			link.l1 = "Figliolo...";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "Mamma, ti ho portato perle bianche! Le ho raccolte tutte! Avrai di nuovo una collana. Sei ancora in collera con me?";
			link.l1 = "Dio...(piangendo) Ole! Figlio mio, perché? Perché te ne sei andato? Delle perle non mi importa nulla!";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "Mamma, tieni... prendi questi. Li ho raccolti da tanto tempo. Dei bravi zii mi hanno aiutato, soprattutto zio "+sld.name+". Mi ha portato sulla sua grande nave, mi ha aiutato a raccogliere perline e mi ha riportato a casa...";
			link.l1 = "Ole... Sei proprio cresciuto, ma resti ancora un ragazzino... Vieni qui, lasciati abbracciare, figliolo! Ti chiedo perdono, scusami per quella maledetta collana! Non ti lascerò mai più solo, mai! Vivremo insieme e avrò cura di te... Farò penitenza, te lo giuro!...";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "Mamma, mi sei mancata... Voglio restare con te. Sei ancora in collera con me? Perché piangi?";
			link.l1 = "(piangendo) No, no... Ti prego, perdonami, figliolo!...";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "Zio "+pchar.name+"! Quanto sono felice che tu sia arrivato! Grazie per avermi riportato da mia madre. È così bello stare qui con lei... Non è meraviglioso essere a casa, vero, zio? "+pchar.name+"?";
			link.l1 = "Sì. Vecchio mio. Proprio così. Mi fa piacere che tu sia felice.";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a riporre quell’arma. Mi mette a disagio.","Sai, qui non si tollera andare in giro con la lama sguainata. Riponila.","Ascolta, non fare il cavaliere errante che va in giro sguainando la spada. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("Va bene.","Bene.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("D’accordo.","Bene.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Attento, compare, a girare con l'acciaio scoperto. Mi fai venire il prurito alle mani...","Non mi piace quando gli uomini camminano davanti a me con l’arma sguainata. Mi mette i brividi...");
				link.l1 = RandPhraseSimple("Capito.","Lo porto via.");
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
