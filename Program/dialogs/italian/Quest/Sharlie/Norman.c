// Абрахам Норман
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
			dialog.text = "Serve qualcosa?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Cosa vuoi, compare? Fatti i fatti tuoi, segui la tua rotta. Lasciami in pace.","Ehi, ehi, compare. Vai a farti una passeggiata? Allora cammina pure e lascia stare monsieur Abraham. Pure lui va a sgranchirsi le gambe. Sta prendendo una boccata d’aria salmastra.","Ciao, amico. Vuoi fare due chiacchiere? C’è solo un piccolo problema: non ho nessuna voglia di parlare. Vai a seccare qualcun altro, dài. Rilassati in taverna, beviti un po’ di rum...");
				link.l1 = "Ascolta, Abramo, per caso ti sei imbattuto di recente su Isla Tesoro in un certo Miguel Dichoso? Da queste parti è una vecchia volpe abbastanza nota.";
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("Che ti serve, compare? Fatti gli affari tuoi, bada alla tua rotta. Lasciami in pace.","Ehi, ehi, compare. Vai a farti una passeggiata? Allora cammina pure e lascia in pace il signor Abraham. Anche lui si sta sgranchendo le gambe, vuole respirare un po' d'aria salmastra.","Ciao, compare. Vuoi scambiare due chiacchiere? Peccato che oggi non ho proprio voglia di parlare. Vai a scocciare qualcun altro. Buttati in taverna, fatti un sorso di rum..."),LinkRandPhrase("Ehi, marinaio. Che sei, duro d’orecchi o cosa? Credevo d’esser stato chiaro come il sole.","Compare, va’ a riposarti. Pare che tu abbia la cera nelle orecchie.","Ehi compare, che hai, sei scemo o cosa? Te l'ho già detto chiaro e tondo, no?"),"Amico, non farmi arrabbiare. Ho fatto fuori così tanti zucconi di terra in vita mia che uno in più o in meno nemmeno si заметит.","D'accordo, mi hai fatto girar le palle. Ora o tiri fuori quella tua spada arrugginita o scappi a gambe levate. Ti consiglio la seconda...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("D'accordo, amico. Non ti disturbo più.","Va bene, va bene. Ho capito...","Urca, sembri proprio il terrore dei sette mari! Va bene, io me la svigno.","Cosa?!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Cosa vuoi, compare? Fatti i fatti tuoi e segui la tua rotta. Lasciami in pace.","Ehi, ehi, amico. Vai a fare una passeggiata? Allora continua pure a camminare e lascia in pace il signor Abraham. Anche lui va a sgranchirsi le gambe, a prendere una boccata d’aria salmastra.","Ciao, compare. Vuoi fare due chiacchiere? Peccato che non ho nessuna voglia di parlare. Vai a scocciare qualcun altro. Vai a sdraiarti in taverna. Beviti un po’ di rum...");
				link.l1 = "Ascolta, Abramo, per caso ti sei imbattuto di recente su Isla Tesoro in un tale chiamato Miguel Dichoso? È una vecchia volpe piuttosto nota da queste parti.";
				link.l1.go = "tieyasal";
				break;
			}
			switch (hrand(5))
			{
				case 0:
					dialog.text = "Fermo! Sono il governatore di quest’isola. Eh? Non mi credi?!";
					link.l1 = "Ma certo che lo conosco! Chi non ha mai sentito parlare del governatore di Isla Tesoro...";
					link.l1.go = "norman_fes0_fight";
					link.l2 = "Ah, chiamati pure ammiraglio mentre ci sei, ci crederei di sicuro!";
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = "Attenti! Ammirate - l’Ammiraglio Barbarigo! Non riconoscete la mia celebre sciabola da cavalleria?";
					link.l1 = "Le chiedo perdono, Signor Ammiraglio! Da ora in poi sarò più vigile, parola mia.";
					link.l1.go = "norman_fes1_peace";
					link.l2 = "La tua sciabola da cavalleria è ben nota. Peccato sia finita nelle mani d’un babbeo.";
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = "Come vedi, sono qui in esilio. Attendo nuove istruzioni dal Generale Monk. Ti prego di non svelare la mia vera identità regale. Le spie di Cromwell hanno orecchie lunghe.";
					link.l1 = "Ma certo, Maestà. Nessuno verrà mai a sapere che Carlo II si nasconde nelle Indie Occidentali.";
					link.l1.go = "norman_fes2_fight";
					link.l2 = "E allora io sono Papa Innocenzo Decimo, perbacco.";
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = "Che ti è successo, Blaze? Ti cerco da due giorni. Hai completamente dimenticato tuo padre Nicolas!";
					link.l1 = "Non ho tempo per te padre! Ho il mare di cose da fare.";
					link.l1.go = "norman_fes3_peace";
					link.l2 = "Vi sbagliate, messere. Il mio nome è "+GetFullName(pchar)+".";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = "Sh-sh... Io sono Davy Jones. Dimmi, hai paura della morte?";
					link.l1 = "Ma certo che lo sono, signor Jones. Soprattutto dopo una sbornia.";
					link.l1.go = "norman_fes4_fight";
					link.l2 = "Una morte è una tragedia, mille morti sono solo una statistica.";
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = "Ho fretta di finire la mia nuova commedia. Devi aiutarmi a completare la frase 'Essere o non essere'?!";
					link.l1 = "Ecco il dilemma! Dobbiamo ingoiare l’offesa e andare avanti...";
					link.l1.go = "norman_fes5_fight";
					link.l2 = "Un bicchiere, di sicuro. Ma non mi stupirei affatto se beccassi qualche malanno in un bordello!";
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = "Ma che diavolo stai blaterando? 'Tesoro'?! Tanto vale chiamarla le Bermuda! Quest’isola si chiama Isola Norman, in mio onore, e non ti azzardare a scordartelo! Mi sa che dovrò darti una lezione di geografia...";
			link.l1 = "Eh! Che vuoi dire?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = "Hai ragione, marinaio. In verità sono proprio l’Ammiraglio Barbarigo, ma che resti tra noi. Preparati a metterti in marcia. Salpiamo a breve. Ti tornerà utile, vedrai.";
			link.l1 = "Ti sono immensamente grato!";
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info("You've received a three-barreled shotgun");
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info("You've received a match-lock musket");
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info("You've received a paper cartridge");
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = "Vedremo subito chi è lo sciocco. In guardia!";
			link.l1 = "Sei davvero serio?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = "Che t'avevo detto! Su, bevi alla mia salute.";
			link.l1 = "Alla salute, ammiraglio!";
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info("You've received a gold doubloon");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info("You've received a chest of doubloons");
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = "Ti avevo ordinato di non spargere in giro il mio nome! Ora dovrò sbarazzarmi di te come testimone scomodo...";
			link.l1 = "Oh, questo lo aspettavo da un pezzo!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = "Perdonatemi, Vostra Grazia! Non vi avevo riconosciuto in questi abiti. Vi prego, accettate questo umile dono da un vero cattolico.";
			link.l1 = "La follia si fa sentire...";
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info("You've received the Wonderworker Amulet");
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info("You've received the Talisman of the Accomplice");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info("You've received a wax candle");
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = "Tutti mi vengono addosso! Ho preso una spia sputata a mio figlio! Sono certo che quel dannato Thomas l’ha mandato per cavarmi il secondo occhio!";
			link.l1 = "Vattene, idiota!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = "Sei stanco e non hai proprio un bell'aspetto, figliolo. Va’ a farti curare.";
			link.l1 = "Grazie!";
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info("You've received a potion");
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info("You've received the Scorpion Amulet");
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info("You've received remedial essence")
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = "Non temere, compare. Vedi, tirare le cuoia non è poi così spaventoso...";
			link.l1 = "Sembra che tu non stia scherzando davvero!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = "A quanto pare non hai paura. Lo sapevo. Questo sì che è coraggio!";
			link.l1 = "Sei proprio un vecchio buffone...";
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info("You've received a fire-eater waistcoat");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info("You've received a parade cuirass");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info("You've received some tobacco");
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = "Sei un poeta da quattro soldi, marinaio. Forse la tua lama è più svelta della tua lingua?";
			link.l1 = "Caramba! Quella tua sciabola da cavalleria non è certo un giocattolo!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = "Maledizione! Le cose ti sono andate proprio lisce! Che ne dici, la tua fantasia ci aveva pensato?";
			link.l1 = "Ripeti, per cortesia.";
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info("You've received a bottle of rum");
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info("You've received a throat of cast iron");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info("You've received a glass flask");
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = "Ahah, ti riconosco! Ah-ah!";
			link.l1 = "Di nuovo...";
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = "Va bene, compare, ci siamo detti tutto. Ora levati dai piedi.";
			link.l1 = "Come dite voi...";
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = "Dichoso?   E che te ne fai di lui, eh?";
			link.l1 = "Ebbene, mi serve. Mi serve, punto e basta. Lo hai visto, per caso?";
			link.l1.go = "tieyasal_1";
			link.l2 = "Cosa vuoi dire, a che mi serve lui? Miguel è un mio vecchio compare, potresti chiamarlo amico. Dovrebbe...";
			link.l2.go = "tieyasal_2";
			link.l3 = "Voglio che mi rimorchi un’altra nave, proprio come fece una volta per Shark Dodson.";
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l4 = "Miguel Dichoso ha ammazzato un uomo. Ecco perché lo sto cercando.";
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ti serve solo lui... Ti serve sooooolo lui! Tutto ciò che ti occorre è Miguel Dichoso! No, non l’ho visto. Non l’ho visto da tempo. Non posso aiutarti in nulla, marinaio.";
			link.l1 = "Hm... Va bene, addio.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = "Un amico, dici... Pare che si sia coltivato una bella collezione di amici. Ma presto ne avrà uno di meno...";
			link.l1 = "Ehi, vecchio. Che ti rode?";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = "Sì, Dichoso è un vero maestro in questi mestieri, in qualsiasi modo tu lo guardi. Ma non so dove si sia cacciato. Era qui, poi è sparito di nuovo. Vai pure da Alexus, marinaio. Ti metterà insieme una vasca di nave che farà invidia ai santi.";
			link.l1 = "Hm... Grazie per il consiglio, compare.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = "E chi sarebbe, allora, quello che Dichoso ha fatto fuori, visto che ora lo state cercando, eh compagno? ";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_4_1":
			dialog.text = "Che vuoi dire? Quale Sharp ha fatto fuori, di preciso? Di Sharp ce n’è una marea, sai.";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			sTemp = GetStrSmallRegister(dialogEditStrings[8]);
			if (sTemp == "blaze sharp")
			{
				dialog.text = "Sh-sh-sh... (guardando in giro) Anche tu pensi che Blaze Sharp sia stato fatto fuori da Dichoso?";
				link.l1 = "Sì. Non ho solo sospetti, ma prove concrete. Annotazioni nel suo giornale di bordo...";
				link.l1.go = "tieyasal_6";
				break;
			}
			if (sTemp == "sharp")
			{
				dialog.text = "Avanti, piccolo marinaio...";
				link.l1 = "Cosa vuoi dire? Spiegati meglio.";
				link.l1.go = "tieyasal_4_1";
				break;
			}
			dialog.text = "Ah... Beh. L’ha fatto fuori, e punto e basta. Sai quanti assassini scorrazzano da queste parti? Uno через uno! No, marinaio. Non vedo Dichoso da un bel pezzo. Non posso aiutarti in nulla.";
			link.l1 = "Che peccato...";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = "Calmati, compare. Come ti chiami, eh? Mi è proprio sfuggito dalla memoria...";
			link.l1 = "Capitano "+GetFullName(pchar)+".";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Ascolta, "+pchar.name+". Dichoso ha ammazzato il povero Blaze. L'ho visto coi miei occhi, sì-sì. Ma non mi credono. Capisci, pensano ch’io sia matto. Uno dei loro, ma svitato. Eppure un tempo ero il miglior abbordatore nella ciurma dello stesso Nicolas Sharp! Bei tempi! Ma alla fine ho perso unghie, zoccolo e lente, e sono rimasto a terra.\nCosa? Ah, giusto! Tutti pensavano che fosse colpa di Shark, ma non era così. No-no-no. C’era il dente di squalo, il talismano di Dodson, ma fu Dichoso a piazzarlo lì.\nDeve averlo rubato a Shark quando navigavano insieme sulla fregata chiamata Fortuna. Quella notte non dormivo bene e sono uscito a passeggiare. Ho visto Dichoso sgattaiolare nella residenza di Sharp, ho sentito qualcuno urlare e poi gemere. Poco dopo Dichoso se n’è andato dalla casa e le sue mani erano insanguinate.\nNon mi hanno creduto, no-no. Perché quel giorno sull’isola non c’era Dichoso, ma Shark sì. E hanno trovato il suo dente. Ma io ho visto Dichoso, ne sono certo. Nessuno sapeva che lui fosse lì quel giorno. ‘Il Fortunato’ è un uomo furbo e spietato...";
			link.l1 = "Non sei il primo a chiamare Dichoso 'il Fortunato'. Perché lo chiamano così? È un soprannome?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Non conosci lo spagnolo, ragazzo? 'Dichoso' vuol dire 'fortunato' nella lingua dei papisti. Miguel il Fortunato, Miguel il Benedetto. Ecco cosa significa il suo nome.";
			link.l1 = "Miguel il Fortunato?... Mh. Questo mi ricorda qualcosa. Mh. Questa frase mi suona così familiare...";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Ebbene, anche se si chiama Dichoso, continuo a pensare che spagnolo non sia. No, no. Non è uno spagnolo. Anche se l’aspetto ce l’ha tutto.";
			link.l1 = "Allora chi potrebbe essere? Inglese, francese?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Non è di questo che parlo, marinaio... Oh, perdonami, Capitano. Sì, Dichoso ciancia in francese in modo davvero squisito, non peggio di te. E anche in inglese. Ma nelle sue vene scorre sangue indio. Ne ho visti molti così, nella mia vita. Non si nota subito, ma è un mezzosangue. Te lo garantisco.";
			link.l1 = "Sa parlare la lingua degli indiani?";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = "Oh, chi lo sa, diavolo! Forse sì. Anzi, aspetta. Sì, lo faceva! Continuava a sparare frasi strambe in qualche lingua strampalata, tirava fuori una faccia da veggente e gonfiava le gote mentre parlava. Tipo, se ne usciva con roba del genere: cogito ergo sum! Poi roteava gli occhi e spiava le facce dei marinai. Oppure gridava così: aut Caesar, aut nihil! Sparava fuori un sacco di altre fandonie. Non mi ricordo tutto quello che diceva.";
			link.l1 = "Questa non è lingua indiana. È latino. Latino... Latino?! Santo cielo!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "Ma che ti prende, amico? Perché strilli così? T’ha punto una serpe, forse? Dov’è finita?";
			link.l1 = "Come ho fatto a non capirlo fin dall’inizio! Era tutto lì davanti ai miei occhi! Il latino! Miguel... Miguel il Fortunato!!!";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = "Ehi, compare. La smetti di strillare, per mille balene? Ci stanno tutti fissando. Che ti rode, marinaio... pardon, capitano?";
			link.l1 = "So chi è davvero Miguel Dichoso. Non è spagnolo. È francese! Ah, che sciocco sono stato!";
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = "No, sciocco. Non è francese. È un bastardo mezzo sangue. Suo padre bianco s’è trastullato con una ragazzina indiana, una di quelle Arawak o Miskito dei Caraibi, o magari pure una Itza, e così è nato il santo Miguel Dichoso su questa terra. Tu non ci fai caso, ma io lo vedo. Sta scritto nei suoi occhi...";
			link.l1 = "Mettiamo da parte per un attimo la questione delle sue origini. Dov’è lui, Abraham?! È stato qui?!";
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = "Sh-sh... Sì, era qui. Ma se n'è andato. Non si trova più sull'Isla Tesoro.";
			link.l1 = "Che ci fa qui, lui? E con che nave è arrivato?";
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = "La sua nave è un galeone. Un gran galeone da guerra. Perché sia venuto qui... Beh, s'è messo a ficcare il naso e a fare domande. Ma io ho sentito le sue chiacchiere, oh sì! Cercava un certo Charles de Maure. Sì, proprio così. Charles de Maure. Aspetta, sei tu, Charles de Maure! Cercava proprio te, compare.";
			link.l1 = "Sai per cosa, eh?";
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = "Be’, di certo non era per andare in taverna a bere un goccio di rum con te. Ti voleva acciuffare, sì, sì! Metterti in catene! Sei nei guai fino al collo, capitano!";
			link.l1 = "Non ne dubito...";
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = "E tu? Perché lo cerchi? Ah, ho capito, ho capito: per ucciderlo! Uccidilo, dannato bastardo! Vendica Blaze Sharp! Blaze era un tipo eccezionale. Me lo ricordo, anche da ragazzino era proprio come Nicholas.";
			link.l1 = "Dove diavolo è finito Dichoso?";
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = "Era diretto a Blueweld. Disse che Charles de Maure va cercato sotto l’ala del Diavolo della Foresta. Ma ha lasciato qui la sua ciurma... Aspetta. Credo che già ti abbiano puntato!";
			link.l1 = "Chi mi ha notato?";
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = "Gli uomini di Dichoso. Ha ordinato di tenerti d’occhio qui. Oh, lo so, lo so! Stai all’erta, capitano: le scogliere dell’Isla Tesoro pullulano di navi e ti aspettano lì per tagliarti la testa. Quel capitano è furbo come una volpe. Non lasciarti infinocchiare.";
			link.l1 = "Ci proverò...";
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = "E ancora una cosa: tieni, prendi la mia spada da cavalleria. Su, prendila, prendila pure. Ti servirà. Questa è la spada del Capitano Barbarigo in persona. Una lama superba. La migliore di tutto l’arcipelago. Non fare il timido, prendila. Blaze Sharp sarà vendicato!";
			link.l1 = "Grazie, Abramo.";
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info("You've received Barbarigo's sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Vai ora. Vai, ti tengono d’occhio. Fa’ finta d’essere furbo. O uno sciocco. È lo stesso. Basta che stai in campana!";
			link.l1 = "Grazie, compare. Non immagini nemmeno quanto mi hai aiutato. Buona fortuna!";
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
