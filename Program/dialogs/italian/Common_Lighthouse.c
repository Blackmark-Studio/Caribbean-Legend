#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Allarme in città. A quanto pare, è ora anche per me di impugnare le armi...","Non è che per caso le guardie della città ti stanno inseguendo?","Non troverai riparo qui, ma potresti trovare diversi pollici di freddo acciaio sotto le tue costole!"),LinkRandPhrase("Di cosa hai bisogno, "+GetSexPhrase("birbante","birbante")+"?! Le guardie ti stanno cercando, non andrai lontano, "+GetSexPhrase("sporco pirata","puzzolente")+"!",""+GetSexPhrase("Sporko","Sporco")+" assassino! Guardie!!!","Non ho paura di te, "+GetSexPhrase("verme","puzzola")+"! Presto sarai impiccato nel nostro forte, non andrai lontano..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Vedo che sei stanco di vivere...","Sembra così, non esiste popolo pacifico in "+XI_ConvertString("Colony"+npchar.city+"Gen")+", tutti vogliono essere un eroe!"),RandPhraseSimple("Vai all'inferno!","Eh, questi saranno gli ultimi secondi della tua vita..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			//belamour legendary edtion карибские нравы
			if(npchar.quest.meeting != "0" && CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Cosa ti porta da me questa volta?";
				link.l1 = "Credo che tu conosca un signore di nome Gerard LeCroix? Dovrebbe aver lasciato una ricompensa per me...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Buon pomeriggio, marinaio! Il mio nome è "+GetFullName(npchar)+", e io sono il custode di questo faro. Che vento ti ha portato qui?","Ciao! È passato un bel po' di tempo dall'ultima volta che ho visto dei nuovi volti al mio faro... Permettimi di presentarmi - "+GetFullName(npchar)+", e questo faro è la mia casa e il mio lavoro. Cosa posso fare per te?");
				link.l1 = "Ciao là, "+npchar.name+"! Il mio nome è "+GetFullName(pchar)+", sono un capitano di nave. Stavo facendo una passeggiata attorno a questa meravigliosa insenatura e ho deciso di fermarmi per vedere chi ci vive.";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Oh, mio vecchio amico, capitano "+GetFullName(pchar)+"! Entra, entra! Cosa ti ha portato qui questa volta?";
				link.l1 = "Ti saluto, vecchio lupo di mare! Non stai mica gemendo in solitudine qui al tuo faro?";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "Ora lo sai. Ero un marinaio, proprio come te, ma è passato molto tempo da quando ho messo piede per l'ultima volta sul ponte di una nave. Ora questo faro è sotto la mia cura, e vendo anche qualche roba...";
			link.l1 = "E cosa stai vendendo esattamente?";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = "Che cosa ti ha portato qui questa volta?";
			link.l1 = RandPhraseSimple("Potresti dirmi, se è successo qualcosa di interessante nella tua colonia di recente?","Non sono stato sulla terraferma per un bel po'... Cosa sta succedendo qui?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "Vediamo cosa hai in vendita.";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "Allora, "+npchar.name+", è già arrivato il mio amuleto?";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+", voglio ordinare un amuleto da te.";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "Ascolta, "+npchar.name+", so che ti occupi della consegna di amuleti su ordinazione. Quindi, sicuramente ne sai molto su di loro. Guarda, per favore, questa piccola cosa - cosa puoi dirmi su di essa?";
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "Amico, sono qui di nuovo per chiederti di quegli strani amuleti";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "C'era qualcosa che volevo chiederti...";
			link.l4.go = "quests";
			link.l9 = "Ho appena dato un'occhiata...";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "A volte vado sulla spiaggia e raccolgo conchiglie, c'è un bel posto non lontano da qui, quindi puoi sempre comprare perle da me. Ogni tempesta porta ambra, la vendo anch'io, anche se ti costerà molto. \nA volte le onde portano ogni tipo di cianfrusaglie interessanti da navi affondate e i miei vecchi compagni mi portano oggetti speciali. Sono interessato agli amuleti incantati, i saggi pagano buone monete per quelli. \nOffro anche armi in occasioni speciali, non chiedermi da dove le ottengo. Un mercante di città compra tutta la roba inutile da me, le cose buone le vendo io dopo averle riparate e pulite. \nSono interessato al rum. Non sto parlando della pisciata che servono nella taverna locale per due pesos a brocca. Sto parlando di vero rum giamaicano in bottiglia. Guarisce e resuscita le persone. Pagherò dieci volte di più per ogni bottiglia che mi porti. Pensa a questo.";
			link.l1 = "Ascolta, "+npchar.name+", hai detto di avere vecchi amici marinai, che ti portano amuleti incantati. È possibile ordinare un certo amuleto da te? Lo pagherò generosamente.";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+hrand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+hrand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (hrand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "Capitano, una quantità di merci è stata recentemente trascinata a riva - "+GetGoodsNameAlt(sti(npchar.quest.goods))+". Alcune parti sono state rovinate dall'acqua salata, ma "+FindRussianQtyString(sti(npchar.quest.goodsqty))+" Sono riuscito a salvare in ottimo stato. Vuoi comprare qualcosa? Te le cederò a buon mercato, solo per "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" per unità.";
				link.l1 = "Nah. Mostrami i tuoi ultimi ritrovi.";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "Mh... Un'offerta onesta, accetto. Immagino che potrei rivenderla per un certo profitto. Vediamo... Questo ammonta a "+FindRussianMoneyString(sti(npchar.quest.goodscost))+". È corretto?";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "Hai colto nel segno, capitano. Un affare d'oro! Abbiamo entrambi ricavato un bel guadagno...";
			link.l1 = "Bene, allora. Manderò i marinai a portare il carico sulla mia nave. Ora mostrami cosa hai raccolto per la vendita.";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
			{
				dialog.text = "Ebbene, non tutti, ma alcuni cimeli vengono portati più frequentemente di altri, quindi suppongo che potrei aiutarti. Ma ti avverto: tutti gli amuleti ordinati in questo modo ti costeranno 100 dobloni. Dovresti capire...";
				link.l1 = "Il prezzo non è un problema. Quali amuleti puoi fornire?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "Pff! Con quel tipo di soldi si potrebbe comprare una nave. È troppo costoso. Immagino che me la caverò da solo...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "No, capitano. Tali cose si possono trovare solo per caso, quindi è impossibile ordinarle in anticipo. E inoltre dovresti aspettarle un po' meno che per sempre...";
				link.l1 = "Ebbene, se è così, non c'è nulla da fare.";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "Come desideri. Vieni a trovarmi se cambi idea.";
			else dialog.text = "Vorresti vedere cosa ho in vendita oggi, capitano? Se non trovi nulla di degno, torna presto - potrei avere qualcos'altro in vendita.";
			// belamour legendary edition карибские нравы -->
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				link.l1 = "Tutto questo, ovviamente, è buono, ma ecco cosa volevo chiedere - suppongo tu conosca un gentiluomo di nome Gerard Lecroix? Dovrebbe aver lasciato una ricompensa per me...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			link.l1 = "Mostrami i tuoi oggetti.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "Dimmi solo, quali cose interessanti sono successe nella tua colonia di recente?";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "Il commercio è commercio, ma volevo chiedere qualcosa.";
			link.l3.go = "quests";
			link.l4 = "Buona giornata, "+npchar.name+"! È stato un piacere incontrarti! Passerò un'altra volta...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "Fai la tua scelta.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "Sfortunatamente, nulla da questa lista mi interessa finora.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "Una bambola voodoo? Ti piacciono le armi da fuoco? Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "Un provatore di polvere da sparo? Il tiro al bersaglio è la chiave del successo in qualsiasi schermaglia. Bello...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "Un coltello rituale? Ti piace squartare i tuoi nemici con potenti fendenti di una pesante spada larga? Allora è per te. Bene... ";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "Un'ascia da palo? Un colpo dall'alto con un'ascia enorme schiaccerà qualsiasi nemico! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "Una tsantsa? Ora quella cosa può spaventare persino il pirata più temerario. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "Un capo corallino? La mitraglia dei tuoi cannoni volerà dritta al bersaglio! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "Gobba? L'infaticabilità è il miglior amico del guerriero. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "Xiuhtecuhtli? Lascia che lo scafo della nave nemica si sbricioli in polvere! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Baldo? Metti Baldo a comando - e tutte le palle di cannone voleranno dritte al bersaglio! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "Cascavella? Il veleno di serpente è la cosa più pericolosa. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "Maschera di Ngombo? Abbassa la guardia dei tuoi nemici, ah-ah! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "Scudo Ngombo? Se non sei riuscito a schivare un proiettile, questo amuleto può salvare la tua vita. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "Eucologio? Una buona preghiera può anche deviare un proiettile. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "Un crocifisso? Questo sarà di grande aiuto a un cristiano nel combattimento ravvicinato. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "El Trozo? Questo farà sembrare una ferita mortale solo un graffio. Bene...";
			link.l1 = "Quando dovrei tornare per ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "Sogbo? E che i cannoni siano sempre pronti per la battaglia! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "Madonna? L'immagine della Santissima Vergine possiede potenti proprietà curative. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "Acqua santa? Anche un poveraccio spruzzato con acqua santa diventerà un eroe epico! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "Un'ancora? E che la tua nave rimanga a galla anche sotto una raffica di palle di cannone, ah-ah! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "Encolpion? Le tue vele non temeranno alcun vento, mentre possiedi questo amuleto. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "Stupore? Possa il Signore vegliare sulla tua ciurma sia sulla terra che in mare! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Cimaruta? I proiettili di moschetto voleranno sopra la tua testa, senza farti alcun danno! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "Teredo? Ogni costruttore di navi sogna quello. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "Xochipilli? Questo risparmierà del tempo a rattoppare le vele. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "Una scimmia? Direi un mulo! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "Fan della zingara? Metti le bende sugli occhi di un pattugliatore! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "Una tartaruga di giada? Questa è la tua carta vincente! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "Un pugno di scimmia? Come si suol dire - fagli rispettare! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "Un pescatore? È il sogno di ogni navigatore. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "Perline del mercante? Al denaro piace essere contato, vero? Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "Ehecatl? Qualsiasi vecchia tinozza a bassa velocità volerà più veloce del vento! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "Orecchino del marinaio? Daglielo al tuo timoniere! Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "Pellegrino? Il vento contrario diventa vento a favore. Bene...";
			link.l1 = "Quando dovrei tornare a ritirare il mio ordine?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "Tra due mesi, non prima. Penso che entro quel tempo me lo avranno portato. Quindi ti aspetterò con i soldi tra due mesi.";
			link.l1 = "Ottimo! Sarò lì! Grazie, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "Sì, ce l'ho. Hai preparato 100 dobloni, capitano?"; // Addon-2016 Jason
				// belamour legendary edition -->
				if(PCharDublonsTotal() >= 100) 
				{
					link.l1 = "Certo! Ecco a te, come concordato.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "Oh, ho dimenticato i soldi sulla nave! Li porterò presto.";
					link.l1.go = "exit";
				}
				// <-- legendary edition
			}
			else
			{
			dialog.text = "Non ancora. Vieni a trovarmi più tardi. E non ti preoccupare - il tuo amuleto arriverà sicuramente.";
			link.l1 = "Bene.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveItems(pchar, "gold_dublon", 100); // Addon-2016 Jason
			Log_Info("You have given 100 doubloons");
			dialog.text = "Tutto sembra a posto. Ecco il tuo amuleto. Buona fortuna con esso!";
			link.l1 = "Grazie, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("You have received "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "Mostra quello che hai lì.";
			link.l1 = "Ecco, sembra un antico amuleto indiano. Ma non ho idea di come usarlo o del suo potere nascosto.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "Bene-bene. Sei la terza persona che mi mostra una cosa del genere, compagno. Questo amuleto è stato portato qui dalla selvaggia selva del Main Meridionale. Ci sono indiani non lontani da Panama che indossano ciondoli come questo. I pellirossa dicono che si tratta di un'eredità dei loro 'grandi antenati.'\nNon ho idea di chi fossero i loro antenati o che tipo di eredità abbiano lasciato, ma posso darti un consiglio su dove informarti. Interessato?";
				link.l1 = "Certo!";
				link.l1.go = "caleuche_2";
				DelLandQuestMark(npchar);
				if (npchar.id == "BasTer_Lightman") DelMapQuestMarkShore("Mayak4");
				if (npchar.id == "Santiago_Lightman") DelMapQuestMarkShore("Mayak9");
			}
			else
			{
				dialog.text = "Hmm... I've held a lot of amulets in my hands, but this one, I see for the first time in the Caribbean. Sorry, mate, I cannot help you; I don't know this kind of stuff. But it is not a simple thing; that's a fact. Ask somebody else. I know for sure that there are other lighthouse keepers like me who know about amulets not any less.";
				link.l1 = "Scusatemi... Allora continuerò a chiedere.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "There is a Carib village on Dominica, and the local chief is named Moknitekuvri. They have a shaman named Tuttuathapak, a highly respected Indian. He's not one of the Caribs; he's from that place about which I've told you already. He can tell you more about this amulet than me. But be careful - Tuttuathapak hates white people. He really hates them. After all, they once enslaved him and took him away from his home...";
			link.l1 = "Presumo che sia arrivato ai Caraibi in quel modo?";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Sì. Questa è una storia piuttosto interessante. La nave, che trasportava schiavi indiani, fu intrappolata da una calma piatta vicino a Marie Galante e metà dell'equipaggio morì per una febbre improvvisa. Eppure, non un solo indiano si ammalò!\nIn seguito, un capitano impazzì e incendiò la sua nave. Di conseguenza, gli indiani imprigionati iniziarono una rivolta e massacraron l'equipaggio. Indovini chi era il loro leader?";
			link.l1 = "Faccio...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Ecco. Scommetto che è stato un incantesimo dello sciamano che ha reso il mare calmo come un morto, e ha infettato l'equipaggio con una malattia mortale. Questo indiano è molto astuto e molto pericoloso. Se vai da lui - comportati con rispetto e guarda la tua lingua - altrimenti ci saranno un sacco di problemi per te. Inoltre, non parlerà nemmeno con te senza un'offerta per lui.";
			link.l1 = "E che tipo di offerta potrebbe richiedere?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Non lo corromperai con qualche schifezza. Per quanto ne so, manda i suoi soldati Caribi nei insediamenti dei bianchi per comprare armi da fuoco. Portagli un moschetto come regalo e poi, penso, sarà contento e ti darà un po' della sua attenzione.";
			link.l1 = "Grazie! Farò come dici... Dimmi, compagno, come sai tutto questo?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Il mio amico era un marinaio sulla nave maledetta. Fortunatamente, è riuscito a sopravvivere in quell'inferno... Ho visto su di lui un amuleto come il tuo, sembra che anche il defunto capitano abbia preso le cose degli Indiani. Sono sicuro che il tuo amuleto proviene dalla sua collezione - quando il capitano è impazzito e ha dato fuoco alla sua nave, i suoi marinai lo hanno ucciso e poi hanno saccheggiato i bauli nella cabina.";
			link.l1 = "Capito. Allora devo solo andare con un regalo a Dominica. Grazie per il tuo aiuto e per la storia interessante!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Buona fortuna, amico mio, e stai attento con questo diavolo dalla pelle rossa...";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "Sì? Hai parlato con Tuttuathapak, ho ragione?";
			link.l1 = "Esatto. E ora voglio trovare altri due amuleti. Hai detto che ero il terzo che ti ha mostrato questo artefatto. E chi erano gli altri due?";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Uno è il mio amico, il marinaio di quella nave che ha portato Tuttuathapak alle isole dei Caraibi. Da quell'incidente, non ha più messo piede sul ponte di nessuna nave. Non lo vedo da un po', ma so dove vive. Cercalo in West Main, a Belize - è un cacciatore ora e vaga per le giungle. Il suo nome è Fergus Hooper.";
			link.l1 = "Bene. E la seconda?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Conosco il secondo solo un po'. Che si chiami Jack o Jackson, che sia un corsaro, un piccolo imprenditore o semplicemente un avventuriero. Possiede un xebec con un nome strano... hmm... il suo nome è... Dannazione, l'ho dimenticato! Ma il nome è di qualche tipo demoniaco. Gli ho chiesto cosa significasse, e lui ha detto che era una donna-uccello, nata dagli dei del mare. Bah! Senza Dio...";
			link.l1 = "Smanioso... Dunque non ricordi il suo nome?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "No, che il fulmine mi colpisca, non mi ricordo. Oh, e quando si è presentato, ha detto che veniva da Barbados.";
			link.l1 = "Ecco qualcosa! Va bene, cercherò di trovare questo amante delle donne piumate finché non sarà trovato da qualcun altro... Grazie, amico, mi hai aiutato molto!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "Di nulla, capo, passa ogni tanto.";
			link.l1 = "Certo!";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerType(NPChar); // belamour иначе обижается навсегда		   
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Sei "+GetSexPhrase(" un ladro, mia cara! Guardie, prendetelo"," ladra! Guardie, prendetela")+"!!!","Caspita! Mi sono distratto un attimo, e tu sei già con la testa nel baule! Fermate il ladro!","Guardie! Rapina! Fermate il ladro!");
			link.l1 = "Argh, merda!";
			link.l1.go = "fight";
		break;
		
		// belamour legendary edition карибские нравы
		case "Trial":
			dialog.text = "Ah, quindi tu sei quel capitano! Sì, ti stavo aspettando. Anche Gerard stava aspettando, ma doveva andare urgentemente in qualche tipo di spedizione, quindi mi ha chiesto di trasferirti il pagamento. Ha detto che devi venire. Ci sono quattrocento dobloni qui, se ti fa piacere.");
			link.l1 = "Grazie! È bello trattare con persone oneste.";
			link.l1.go = "Trial_1";
		break;
		
		case "Trial_1":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 400);
			Log_Info("You have received 400 doubloons");
			PlaySound("interface\important_item.wav");
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.IslamonaSpaOfficer = true;
			CloseQuestHeader("Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		// <-- legendary edition
	}
}
