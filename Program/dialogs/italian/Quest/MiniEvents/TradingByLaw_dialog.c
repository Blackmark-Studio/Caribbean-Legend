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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Cosa vuoi, furfante?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;

		case "Kristian":
			dialog.text = "Benvenuto nella mia umile dimora! Sono Christian. Christian Deluce al tuo servizio. Cosa ti porta alla mia porta, forestiero?";
			link.l1 = "Il nome è Capitano "+GetFullName(pchar)+". Cerco d’acquistare una buona quantità di acquavite. Spero che il mio intento sia chiaro?";
			link.l1.go = "Kristian_2";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_2":
			dialog.text = "Cosa??? Chi mai spargerebbe simili menzogne? Un terribile equivoco, te lo giuro! Non traffico affatto con spiriti di sorta!";
			link.l1 = "Ebbene, ebbene... Pare proprio che abbia trovato chi cercavo.";
			link.l1.go = "Kristian_3";
		break;

		case "Kristian_3":
			dialog.text = "Oh cielo, no-no-no! Che accuse mi portate! Contrabbandare liquori? Io? Io... io soltanto, ehm, voglio dire... Va bene, possiedo certe bevande, ma tutto perfettamente legale! Mi limito a procurare rinfreschi per cittadini privati, eh... per festini e modeste riunioni sociali!";
			link.l1 = "Perché tremi così, buon uomo? Non vengo come tuo carceriere, ma come tuo benefattore. La tua sorte potrebbe volgere al meglio, e la mia borsa farsi più pesante di qualche doblone, se ti va la sorte.";
			link.l1.go = "Kristian_4";
		break;

		case "Kristian_4":
			dialog.text = "Io? N-nervoso? Assurdità! Che motivo avrei per agitarmi? Son uomo d'onore specchiato – la mia dimora sorge proprio all’ombra della residenza del governatore! Non infrango una sola legge, lo giuro su tutto il mio onore!";
			link.l1 = "Dunque non traffichi in spiriti? Che gran peccato, davvero. Ero venuto con una proposta per un guadagno sostanzioso. Una fortuna in dobloni che un modesto mercante clandestino a malapena riesce a sognare. Ma visto che non sei il mio uomo, non ti disturberò oltre e me ne andrò. A meno che...?";
			link.l1.go = "Kristian_5";
		break;
		
		case "Kristian_5":
			dialog.text = "Ah... aspetta un momento... "+GetAddress_Form(NPChar)+"... perdonami, la mia mente vaga come gabbiani nella tempesta, ho proprio dimenticato il tuo illustre nome.";
			link.l1 = "Capitano "+GetFullName(pchar)+".";
			link.l1.go = "Kristian_6";
		break;

		case "Kristian_6":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" "+pchar.lastname+"A dir la verità, io... cioè... forse conosco dove si trovi la persona che cercate. Potrei riferire a costui... la vostra generosa proposta.";
			link.l1 = "Staffetta? Ma dài, non scherzare. Pensi davvero che faccende così delicate debbano passare per mani inutili?";
			link.l1.go = "Kristian_7";
		break;

		case "Kristian_7":
			dialog.text = "Hai ragione. Ma... che Dio mi assista... il dado è tratto... sì, sono davvero al tuo servizio.";
			link.l1 = "Ora ci intendiamo, Cristiano. La taverna scarseggia di buon rum, e credo che entrambi possiamo trarre un bel profitto da questa situazione.";
			link.l1.go = "Kristian_8";
		break;

		case "Kristian_8":
			dialog.text = "Capitano, conosco fin troppo bene i travagli dell’oste. La gente fa la fila alla mia porta, e ormai mi mette paura continuare la mia umile attività – troppe occhiate indiscrete, adesso. Speravo che magari voi... insomma, una persona del vostro rango potesse...";
			link.l1 = "Perché non vai tu stesso dall’oste a offrire la tua mercanzia?";
			link.l1.go = "Kristian_9";
		break;

		case "Kristian_9":
			dialog.text = "Lui... preferirebbe abbracciare un lebbroso piuttosto che fare affari con me. Quel buffone altezzoso non prova altro che disprezzo per i modesti mercanti del mio rango.";
			link.l1 = "In verità, la sua fama lo precede. Potrebbe disprezzare i tuoi doni se glieli offri tu stesso. Ma se li porto io... beh, questa è tutta un'altra faccenda.";
			link.l1.go = "Kristian_10";
		break;

		case "Kristian_10":
			dialog.text = "Ti proponi come intermediario? Mi va più che bene, ragazzo... Abbiamo messo le mani su un carico di dimensioni spettacolari – mai visto tanto tutto insieme! Mi avrebbe riempito le cantine per almeno mezzo anno. Ma per grazia dell’Onnipotente, ce la siamo cavata per un soffio, sfuggendo alla scoperta.\nAncora non capisco come diavolo siamo passati tra le maglie del governatore. Rischiare la sorte una seconda volta così sarebbe pura follia, roba da suicidarsi.";
			link.l1 = "Forse allora è tempo che tu esca un po' dall'ombra. Non del tutto, bada bene, ma quanto basta per trattare i tuoi affari con meno rischi.";
			link.l1.go = "Kristian_11";
		break;

		case "Kristian_11":
			dialog.text = "F-far un passo alla luce? Ma... perché, ci vogliono amici potenti! E una borsa ben fornita! Per quale scopo, di grazia? Non vorrà mica restare qui per sempre, lei che comanda la propria nave, a rifornire bettole come un semplice bottegaio?";
			link.l1 = "Per quanto riguarda le conoscenze, la mia influenza arriva dove la tua non può. Quanto ai soldi... l’investimento sarà modesto. E sulla tua ultima preoccupazione – non temere. Opererai come mio uomo in queste faccende. Sarò il tuo scudo, tu la mia risorsa costante. Il nostro patto sarà duraturo e vantaggioso per entrambi. Tu ottieni un cliente affidabile, io merce di cui mi posso fidare. Che ne dici, ti solletica quest’avventura?";
			link.l1.go = "Kristian_12";
		break;

		case "Kristian_12":
			dialog.text = "Ero certo che fosse una trappola ben congegnata. Eppure, a dir la verità, la tua proposta suona... davvero allettante. Stabilità, affidabilità... Mai avrei pensato che la sorte mi avrebbe sorriso così."+GetSexPhrase("Monsieur","Mademoiselle")+", hai il mio pieno consenso! Quale quantità desideri acquistare?";
			link.l1 = "Mettiamo prima la tua mercanzia su basi solide, poi parleremo dei dettagli. Quante botti di rum e vino adornano attualmente il tuo magazzino?";
			link.l1.go = "Kristian_13";
		break;

		case "Kristian_13":
			dialog.text = "In questo preciso momento? Ah... Forse dovremmo ispezionare la mia cantina, dove potrei darti un resoconto preciso delle mie scorte.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_GoToPogreb");	// спускаемся в погреб
		break;
		
		// погреб
		case "Kristian_15":
			dialog.text = "Vediamo un po'... Quali tesori si celano quaggiù? Ah sì\nIl mio attuale magazzino conta esattamente cento bottiglie di ottimo rum e cento bottiglie di eccellente vino.";
			link.l1 = "Direi che è un inizio promettente. Una volta risolti i tuoi problemi d’importazione, riusciresti a garantire queste consegne ogni mese senza mancare mai?";
			link.l1.go = "Kristian_16";
		break;

		case "Kristian_16":
			dialog.text = "Certamente, Capitano! Per mille tempeste, potrei gestire il triplo, anzi no... quattro volte questa quantità! Non avrete mai ritardi – terrò sempre ampie scorte, così che ogni sventura possa essere sconfitta in fretta senza toccare i vostri rifornimenti.";
			link.l1 = "Dimmi il tuo prezzo per questo carico.";
			link.l1.go = "Kristian_17";
		break;

		case "Kristian_17":
			dialog.text = "Considererei un pagamento equo: dieci dobloni per dieci bottiglie di vino e tre dobloni per ogni dieci bottiglie di rum. In totale, centotrenta dobloni per l’intero carico.";
			link.l1 = "Benissimo. Andrò a parlamentare con l’oste e ritornerò senza indugio.";
			link.l1.go = "Kristian_18";
		break;
		
		case "Kristian_18":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_18_1";
			pchar.questTemp.TPZ_Tavern_2 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			AddQuestRecord("TPZ", "4");
		break;
		
		case "Kristian_18_1":
			dialog.text = "Capitano, quali novità? Com’è andata la vostra chiacchierata con l’oste?";
			link.l1 = "Non ci ho ancora parlato. Sarà la mia prossima tappa.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_18_1";
		break;

		case "Kristian_21":
			dialog.text = "Com'è andata, Capitano? Siete riuscito a trovare un accordo con l'oste?";
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				link.l1 = "Mi sono comportato in modo eccellente, Christian. Comprerà questo carico e tutti quelli futuri per duecentoquaranta dobloni. Per il primo giro, ti pagherò i centotrenta che hai chiesto, e il resto lo terrò come ricompensa. Ma i guadagni futuri saranno tutti tuoi, parola di pirata.";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				link.l1 = "Ho fatto un buon lavoro, Cristiano. Comprerà questa e le prossime partite per duecento dobloni. Per la prima, ti pagherò i centotrenta che hai chiesto, e terrò la differenza come giusta ricompensa. Tutti i futuri profitti saranno solo tuoi.";
			}
			link.l1.go = "Kristian_22";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_22":
			dialog.text = "Questa sì che è una notizia stupefacente, Capitano! Mai avrei osato sperare in un accordo simile – vi ringrazio! Ma... forse avete agito con troppa fretta? Il governatore... io... cioè...";
			link.l1 = "Il governatore ne è ben consapevole. D’ora in poi, pagherai una tassa mensile di cento dobloni e presenterai regolari registri di commercio.";
			link.l1.go = "Kristian_23";
		break;

		case "Kristian_23":
			dialog.text = "Incredibile! Come diavolo ci sei riuscito, Capitano? Il governatore è un uomo duro, e un vero flagello per i contrabbandieri...";
			link.l1 = "È proprio questo il punto, Christian: lui si oppone al contrabbando, non agli affari onesti. Mi ha ascoltato e ha fissato condizioni chiare per il commercio di liquori sull’isola. D’ora in poi agirai sotto il mio nome. Se combini qualche marachella, ne rispondo anch’io. Quindi non tradirmi, o ti darò la caccia anche nell’aldilà.";
			link.l1.go = "Kristian_24";
		break;

		case "Kristian_24":
			dialog.text = "Lo giuro, Capitano, non ve ne pentirete!";
			link.l1 = "Ora dobbiamo sistemare le cose con l’oste, poi definiremo i dettagli del nostro accordo.";
			link.l1.go = "Kristian_25";
		break;
		
		case "Kristian_25":
			dialog.text = "Certamente, Capitano. Siete pronto a prendere la merce proprio adesso? Saranno centotrenta dobloni.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Sì, ecco i tuoi dobloni.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Al momento, non ho il denaro necessario. Rimani qui — tornerò con il pagamento.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_25_1":
			dialog.text = "Capitano! Siete tornato per ritirare la merce? Il prezzo resta centotrenta dobloni.";
			if (PCharDublonsTotal() >= 130)
			{
				link.l1 = "Proprio così! Ecco la tua ricompensa.";
				link.l1.go = "Kristian_26";
			}
			else
			{
				link.l1 = "Sfortunatamente, non ho ancora il denaro. Tornerò più tardi, parola di marinaio.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Kristian_25_1";
			}
		break;

		case "Kristian_26":
			dialog.text = "Molto obbligato! Prendili! Cento bottiglie di vino e cento bottiglie di rum, come promesso.";
			link.l1 = "La mia ciurma si occuperà del carico. Nel frattempo, devo scambiare due parole con l’oste.";
			link.l1.go = "Kristian_27";
			RemoveDublonsFromPCharTotal(130);
		break;
		
		case "Kristian_27":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.TPZ_Tavern_4 = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;
		
		case "Kristian_31":
			dialog.text = ""+pchar.name+"! Torni così in fretta! Dimmi, il nostro accordo è andato a buon fine?";
			link.l1 = "Tutto è andato a gonfie vele, Cristiano. L’oste ora vorrà la stessa partita di merce due volte al mese. Tieni ben fornita la sua taverna di spirito, e presto potrai scordarti cosa vuol dire aver bisogno di qualcosa.";
			link.l1.go = "Kristian_32";
			DelLandQuestMark(npchar);
		break;

		case "Kristian_32":
			dialog.text = "Capitano... voi... sembra che la Provvidenza stessa vi abbia condotto alla mia soglia! Un vero miracolo si è compiuto davanti a me – a stento oso credere alla mia fortuna! Quale azione mi ha valso tanta benevolenza? Le parole non bastano a esprimere la mia gratitudine!";
			link.l1 = "Io, tuttavia, posso illuminarti, cristiano. Ogni mese dovrai mettere da parte una scelta porzione delle tue merci migliori esclusivamente per me, senza offrirla ad altri. Io le acquisterò al prezzo che stabilisci – dieci dobloni per ogni dieci bottiglie di vino e tre dobloni per ogni dieci di rum.";
			link.l1.go = "Kristian_33";
		break;

		case "Kristian_33":
			dialog.text = "Sarebbe per me un vero piacere, "+pchar.name+", per mettere da parte la mercanzia solo per te, capitano! Te lo giuro sul mio onore, non ti deluderò mai! Quanta te ne serve? Cinquanta bottiglie? Magari cento? Dimmi tu la cifra che vuoi!";
			link.l1 = "Quantità simili superano di gran lunga le mie necessità attuali. Venti bottiglie per tipo saranno più che sufficienti. Se il mio fabbisogno aumenterà, sarete prontamente avvisati.";
			link.l1.go = "Kristian_34";
		break;

		case "Kristian_34":
			dialog.text = "Certamente, certamente! Allora è deciso – venti bottiglie di vino e venti di rum per ventisei dobloni. Il quindicesimo giorno di ogni mese, la vostra mercanzia vi attenderà pronta da ritirare. Sarò lieto di accogliere la vostra stimata presenza ogniqualvolta vorrete onorarmi, anche solo per scambiare quattro chiacchiere!";
			link.l1 = "Splendido! Un’ultima faccenda necessita d’enfasi, Cristiano. Ho scommesso il mio buon nome sulla tua rettitudine. Non tradirmi, o assaggerai le conseguenze.";
			link.l1.go = "Kristian_35";
		break;

		case "Kristian_35":
			dialog.text = "Io... quale proposta avanzate, capitano... davvero voi... no, no, mai deluderò! Tutto si svolgerà con la massima rettitudine, lo giuro sulla mia anima!";
			link.l1 = "Allora, finché i nostri destini non s’incroceranno di nuovo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TPZ_SpawnShip");
		break;
		
		case "Pirate_1":
			dialog.text = "Tu ficcanaso "+GetSexPhrase("bastardo","sgualdrina")+"! Non t’hanno mai insegnato che ficcare il naso negli affari altrui porta solo sventura?";
			link.l1 = "Sei stato tu a salire sulla mia nave senza invito, e ora osi accusarmi d’immischiarmi? Hai perso del tutto il senno, sciagurato?";
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			dialog.text = "Fulmini e saette sulla mia trinchetto! Dunque sei tu, "+GetSexPhrase("cucciolo miserabile","sgualdrina da quattro soldi")+", non hai la minima idea degli intrighi in cui ti sei cacciato? Credevi forse che le scorte della taverna sparissero per caso?";
			link.l1 = "Sei tu che ti prendi il merito per aver ridotto quella distilleria in cenere?";
			link.l1.go = "Pirate_3";
		break;

		case "Pirate_3":
			dialog.text = "Ah-ah, finalmente la verità trapassa quel tuo cranio di legno, che la mitraglia mi squarci le budella! Sì, l’ho fatto io! Quel fornitore aveva le mani troppo ben piantate nel commercio. Ma come vedi, non mi sfugge mai di abbattere i rivali. E tu seguirai la loro sorte, che la cartucciera mi riduca le vele a brandelli!";
			link.l1 = "Che divertente. Ebbene, vediamo di che pasta sei fatto, che i mostri di Nettuno si abbuffino del tuo cadavere! Ah-ah!";
			link.l1.go = "Pirate_4";
		break;
		
		case "Pirate_4":
			DialogExit();
			
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Kristian_41":
			dialog.text = "Saluti, "+pchar.name+"! Quali venti propizi ti hanno portato fin sulla mia soglia?";
			if(CheckAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom")) // торговля вином и ромом
			{
				if (GetDataDay() == 15)
				{
					link.l1 = "Buondì, Christian. Hai preparato la mia mercanzia?";
					link.l1.go = "Kristian_42";
				}
			}
			link.l2 = "Buon giorno, Christian. Volevo solo assicurarmi che i tuoi affari vadano a gonfie vele. Non ti darò altro fastidio per ora.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Kristian_41";
		break;

		case "Kristian_42":
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				dialog.text = "Certamente, Capitano! Potreste anche solo dubitare della mia solerzia?";
				if (PCharDublonsTotal() >= 130)
				{
					link.l1 = "Neanche per un attimo, Christian. Ecco il tuo compenso, come pattuito. Ora mi prendo il mio rum.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Neanche per sogno. Ahimè, la mia borsa è tristemente vuota in questo momento. Tornerò quando avrò le tasche più gonfie.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			else
			{
				dialog.text = "Certamente, Capitano! Potreste forse dubitare, sia pur per un battito d’ali, della mia solerzia?";
				if (PCharDublonsTotal() >= 26)
				{
					link.l1 = "Neanche per un attimo, Cristiano. Ecco i tuoi dobloni, come pattuito. Ora prendo possesso del mio rum.";
					link.l1.go = "Kristian_43";
				}
				else
				{
					link.l2 = "Nemmeno per sogno. Ahimè, al momento mi trovo senza il giusto compenso. Tornerò quando la mia borsa peserà quanto si conviene.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Kristian_41";
				}
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoBlock")) // увеличить объём поставок вина и рома
			{
				link.l4 = "Christian, desidero aumentare la mia fornitura abituale. Cento bottiglie al mese sia di rum che di vino, per essere precisi.";
				link.l4.go = "UpgradeVino";
			}
			if(sti(pchar.questTemp.TPZ_KritstianVinoAndRom) >= 1 && CheckAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom") && sti(pchar.Money) >= 50000) // увеличить объём поставок вина и рома, если в первый раз не принесли
			{
				link.l4 = "Christian, desidero riconsiderare l’idea di allargare il nostro accordo.";
				link.l4.go = "UpgradeVino_Agreed";
			}
		break;
		
		case "Kristian_43":
			dialog.text = "Splendido. Come sempre, nuova merce fresca ti aspetterà il quindici. Attendo con ansia la tua prossima visita.";
			link.l1 = "Puoi contarci sul mio ritorno. Finché le nostre rotte non si incroceranno ancora.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			
			if (CheckAttribute(pchar, "questTemp.TPZ_UpgradeVino"))
			{
				RemoveDublonsFromPCharTotal(130);
				AddItems(pchar, "potionrum", 100);
				AddItems(pchar, "potionwine", 100);
			}
			else
			{
				RemoveDublonsFromPCharTotal(26);
				AddItems(pchar, "potionrum", 20);
				AddItems(pchar, "potionwine", 20);
			}
			
			DeleteAttribute(pchar, "questTemp.TPZ_TradeVinoAndRom");
			SetFunctionTimerCondition("TPZ_KristianReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			pchar.questTemp.TPZ_KritstianVinoAndRom = sti(pchar.questTemp.TPZ_KritstianVinoAndRom) + 1; // счётчик покупок
		break;

		case "UpgradeVino":
			dialog.text = "Capitano, una simile espansione sarebbe certo ben accolta per gli affari, ma non senza spese di riguardo! Maggiori quantità richiedono più braccia, depositi più ampi, il noleggio di navi più capienti... Senza un investimento adeguato, non potrei mai garantire la consegna puntuale di ordini tanto ingenti.";
			link.l1 = "E quale somma servirebbe per simili accordi? Quale investimento garantirebbe che quest’impresa ampliata fili liscia come l’olio?";
			link.l1.go = "UpgradeVino_2";
		break;

		case "UpgradeVino_2":
			dialog.text = "Cinquanta mila pesos basterebbero. Qualsiasi altra spesa la coprirò di tasca mia.";
			link.l1 = "Cinquanta mila? Per la mia barba... non è certo una somma da poco. Non potresti cavartela con un gruzzolo più misero?";
			link.l1.go = "UpgradeVino_3";
		break;

		case "UpgradeVino_3":
			dialog.text = "Con profondo rammarico, Capitano, devo insistere che questa somma rappresenta il minimo indispensabile. Se dovessimo lesinare, la nostra impresa potrebbe... diciamo, sbandare rovinosamente dalla rotta. Disgrazie simili non gioverebbero né ai vostri interessi né ai miei, oso dire.";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Ecco il tuo pagamento completo. Fa' in modo di mostrarti degno di tale fiducia, cristiano.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Riflettendoci meglio, Christian, forse questa espansione è un tantino affrettata. Riparliamone quando i venti ci saranno più propizi.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_4":
			dialog.text = "Come desiderate, Capitano. Se doveste cambiare idea, resto al vostro servizio.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Kristian_41";
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			pchar.questTemp.TPZ_KritstianVinoPotom = true;
		break;
		
		case "UpgradeVino_Agreed":
			dialog.text = "Capitano, notizie eccelse! Avete portato i cinquantamila in argento per procedere senza indugio?";
			if (sti(pchar.Money) >= 50000)
			{
				link.l1 = "Ecco il tuo pagamento completo. Fa' in modo di dimostrarti degno di tale fiducia, cristiano.";
				link.l1.go = "UpgradeVino_5";
			}
			link.l2 = "Al momento, le mie casse sono vuote. Tornerò quando le mie finanze mi permetteranno un tale investimento.";
			link.l2.go = "UpgradeVino_4";
		break;

		case "UpgradeVino_5":
			dialog.text = "Sull’onore mio, "+pchar.name+", non ti pentirai mai di questa decisione! Mi metterò subito all’opera. Già dal prossimo carico, potrai ricevere cento bottiglie del miglior rum e altrettante di vino squisito, tutto al prezzo di centotrenta dobloni per spedizione completa.";
			link.l1 = "Molto soddisfacente. Ma rammenta – agisci sempre con la massima discrezione. Il tuo comportamento ricade direttamente sulla mia reputazione in queste acque.";
			link.l1.go = "UpgradeVino_6";
			AddMoneyToCharacter(pchar, -50000);
		break;
		
		case "UpgradeVino_6":
			DialogExit();
			
			NextDiag.CurrentNode = "Kristian_41";
			pchar.questTemp.TPZ_UpgradeVino = true;
			pchar.questTemp.TPZ_KritstianVinoBlock = true;
			DeleteAttribute(pchar, "questTemp.TPZ_KritstianVinoPotom");
			AddQuestRecordInfo("Useful_Acquaintances", "4_1");
		break;
		
		
	}
}