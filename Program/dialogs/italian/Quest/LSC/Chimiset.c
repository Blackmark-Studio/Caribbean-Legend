// колдун ривадос - Чимисет
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
			dialog.text = "Desideri qualcosa?";
			link.l1 = "No, lascia stare.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "Aspetta! Fermati... Ti supplico, ascoltami prima di commettere uno sbaglio.";
			link.l1 = "Ascolto... Spero tu abbia una buona ragione per fermarmi dal...";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если еще есть
		break;
		
		case "KillChad_1":
			dialog.text = "Dal farmi fuori, vero? Ti ho sentito parlare con Chad di sopra e non ti biasimo – chiunque avrebbe fatto lo stesso, probabilmente. Ma sbagli a pensare che Chad ti lascerà andare dopo avermi fatto fuori.";
			link.l1 = "Hm... Interessante, e perché mai non lo farà? L'unica cosa che so è che dovrò sudare sette camicie per uscirmene da questa dannata isola, a meno che non decida di ammazzarti qui e ora.";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "Non avrai alcun futuro se mi uccidi. Ascolta, i Narvali e Chad vogliono liberarsi di me, ma hanno troppa paura per farlo con le proprie mani – chi mi tocca sarà maledetto in eterno. Perciò spingono te a sporcarti le mani.\nChad sa bene che non sei dei Rivados, ti sta fregando. Quando avrai fatto fuori me – ti faranno la stessa cosa, e useranno il tuo cadavere per ingannare lo Squalo.";
			link.l1 = "Squalo? Steve Dodson? È davvero qui? E spiegami finalmente — chi diavolo sono questi Rivados?";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "Ehi, non sembri uno del posto, davvero... Ma non è il momento di raccontar storie. Dobbiamo salvarci la pelle. Ho un piano.";
			link.l1 = "Sai una cosa, stregone, di recente ho attraversato un portale stregato e ci sono quasi rimasto secco, quindi le tue maledizioni non mi fanno né caldo né freddo. Ne ho abbastanza – è ora di spedirti all'altro mondo.";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "D'accordo, mi fido di te. Qual è il piano?";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "Là c’è un forziere. Dentro troverai armi decenti e qualche pozione. È chiuso, ma la serratura è vecchia e malandata: cerca un piede di porco per forzarla.\nPrendi tutto dal forziere, armati e sali le scale. Da lì potrai difenderti meglio, li costringerai a venire uno alla volta, solo sta’ attento ai moschettieri.\nSpero che tu abbia la mano ferma con la lama, io sono troppo vecchio per menar fendenti. Se riuscirai a farli fuori tutti e a restar vivo... ti prometto la protezione dei Rivados, la mia stirpe...";
			link.l1 = "Bene. Prega i tuoi dèi per me – la battaglia sarà dura. Quei ragazzi lassù hanno l’aria di non scherzare affatto.";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "Non perdere tempo! Forza la serratura in fretta...";
			link.l1 = "Sì, sì, sto arrivando.";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "Ben fatto! Sei davvero un maestro di scherma. Ti sono debitore, forestiero. Dimmi, come ti chiami?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". E il tuo, qual è?";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Il mio nome è Chimiset, sono uno sciamano dei Rivados e consigliere del nostro capo - Eddie il Nero. Sarà lieto di sapere che mi hai liberato e salvato la vita. Sei amico di Chimiset, di Eddie il Nero e di tutta la gente dei Rivados. Da oggi sarai sempre ospite gradito sul nostro Protettore...";
			link.l1 = "Aspetta... Chimiset, se ancora non l’hai capito, sono arrivato qui solo da poche ore. Mi puoi spiegare dove mi trovo, chi sono i Rivados, e dove posso trovare Squalo Dodson?";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "Questo posto si chiama la Città delle Navi Abbandonate. Anche se, a dire il vero, sembra quasi uno scherno. Non è affatto una città, sai. È un’isola fatta di centinaia di relitti ammucchiati, con un centro appena adatto a ospitare anime perse. Qui vivono quelli che si sono salvati da naufragi misteriosi, trascinati da tempeste che non lasciano scampo, finendo su queste assi marce.\nI Rivados sono un clan, una banda che si conosce da tempo immemore. Ma non siamo soli: ci sono anche altri tre gruppi. I Narvali — nostri acerrimi nemici, i pirati di Shark Dodson e la gente comune. Shark, quello lì, si crede il padrone dell’isola, si fa chiamare ammiraglio.\nÈ arrivato qui da poco e ha preso il potere con la forza. Ha messo le mani sulla 'San Augustine', dove tenevamo le nostre provviste. Ora ci tocca comprare il cibo ai prezzi che decide Shark. Mi pare che tu abbia già messo piede in quel magazzino.\nChad Kapper era nostromo di Shark e comandava la prigione. Layton Dexter, invece, era il suo primo ufficiale — anche lui ha una certa influenza. Questi tre, con i loro masnadieri, tengono l’isola in pugno, schiacciando sia i Rivados che i Narvali.";
			link.l1 = "Perché Chad Kapper voleva che ti uccidessi?";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "Chad aveva stretto contatti coi Narvali, nostri acerrimi nemici. Intendeva far fuori lo Squalo con il loro aiuto e prendersi il suo posto. I Narvali serbano rancore all’ammiraglio per la morte di Alan Milrow, il loro vecchio capo. Credono che sia stato lo Squalo a farlo fuori, ma si sbagliano. Io so chi fu. È stato Chad. Io solo ho visto quel misfatto con i miei occhi.\nPerciò Chad non poteva lasciarmi andare, ma al contempo temeva di farmi del male. I pirati non tremano in battaglia, ma sono pieni di superstizioni. Così voleva usare te. Chad e i Narvali avrebbero fatto fuori lo Squalo e dato la colpa ai Rivados.";
			link.l1 = "Ah davvero? Raccontami il perché...";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+", amico mio, parliamone dopo. Dobbiamo sbrigarci, prima che arrivino i pirati di Squalo. Fruga il corpo di Chad e prendi le sue chiavi. Ma prima, controlla la sua scrivania, potrebbe averci lasciato qualche carta interessante.\nVai da Squalo Dodson, lo troverai sulla 'San Augustine', una grossa nave incagliata lontano dalle altre, c’è un ponte che la collega alla nave chiamata 'Plutone'. Digli che Chad stava tramando un tradimento, aggiungi che dietro tutto questo ci sono i Narvali, e che noi Rivados non c’entriamo nulla.\nSarò lieto di darti tutte le informazioni che vuoi su quest’isola, sul mio clan e sugli altri, quando arriverai alla nostra residenza nel Protettore. Ora filiamo via di qui!";
			link.l1 = "Va bene, Chimiset. Ti troverò più tardi sulla... 'Protettore'. Usciamo da qui!";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Un'altra cosa. Le nostre navi, compresa la 'Protector', sono vietate agli stranieri. Devi essere un Rivados, oppure conoscere la parola d'ordine per salire a bordo. Te la direi, ma la cambiano ogni settimana e io sto qui da troppo tempo per sapere qual è quella attuale. Dovresti andare prima alla 'San Augustine'. Mentre tu parli con Squalo, io avviserò la mia gente di chi sei: ti aspetteranno. Ma non andare ora alla 'Protector', prima parla con Squalo e lasciami radunare i miei, altrimenti i Rivados ti tratteranno da nemico.";
			link.l1 = "Capisco. Sto andando a 'San Augustine'. Ci si vede!";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("Ha, they say that you are a friend of clan Rivados. This is interesting. Congratulations...", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that you have saved the Rivados wizard Chimiset from 'Tartarus'. Now you are a welcome guest on their ships.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("So it was you who has set Chimiset free! Interesting. Now you are a friend of Rivados but an enemy of Narwhals. I am not sure whether to congratulate you or to sympathize...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Cosa ti serve da me, forestiero?";
			link.l1 = "Il tuo nome è Chimiset, giusto?";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Sì, sono io. Hai da dirmi qualcosa, oppure vuoi solo scambiare due chiacchiere?";
			link.l1 = "Ho degli affari da trattare. Vengo dall’Ammiraglio, Squalo Dodson. Ho portato un ordine per liberarti, ma a una condizione: dovrai rispondere a qualche mia domanda.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Dodson ha deciso di lasciarmi andare? Son lieto di udirlo. Fai pure le tue domande. Spero che non ci sia alcun inganno, altrimenti la mia trepidazione sarà stata vana.";
			link.l1 = "Nessun inganno, ho solo bisogno del tuo aiuto. Dimmi, Chimiset, c’è forse un idolo di pietra strano su quest’isola? A mezzanotte si tramuta in oro. Non pensare che sia matto...";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "Altre domande, forestiero?";
			link.l1 = "Sì. Conosci un tale chiamato il Ragazzo Bianco?";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "Ragazzo bianco? Certo che lo conosco. È il soprannome di Olle Christiansen, il nostro scemo di paese. Ormai è un uomo fatto e finito, anche se la testa gli è rimasta quella d’un ragazzino.";
			link.l1 = "Ah davvero? Dimmi, dove posso trovarlo?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "In qualsiasi angolo della nostra città. Spesso lo trovavi in bottega, nella taverna o a passeggiare per le strade. Ha i capelli bianchi, lo riconoscerai.";
			link.l1 = "Splendido! Un’ultima domanda: hai forse incontrato qui un certo Nathaniel Hawk? Dovrebbe essere arrivato un po’ di tempo fa, e potrebbe essere gravemente malato.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "Non posso aiutarti con questo, forestiero. Non conosco nessuno con quel nome. Ti assicuro che non si trova sulle navi dei Rivados, e nemmeno dovrebbe essere nella zona neutrale. Non posso dire lo stesso per i territori dei Narvali, però: i Rivados lì non ci mettono piede.";
			link.l1 = "Ebbene, grazie lo stesso... Mi hai dato una gran mano, Chimiset!";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "E tutto qui? Lo Squalo mi lascerà libero adesso?";
			link.l1 = "Sì. Non ho altro da chiederti. Chad Kapper ti lascerà libero. Bene, ora devo andare...";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "Fermati! Aspetta... Torna indietro.";
			link.l1 = "Hai qualcos'altro da raccontarmi?";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "Non proprio... (abbassando la voce) Vedo che non sei uno degli uomini di Kapper. Non fidarti di lui. È un porco infame. Poco tempo fa, ha ammazzato a sangue freddo il povero Alan Milrow con una spada larga, disarmato com’era. Era il capo dei Narvali. Non me l’aspettavo, Chad si è solo avvicinato alla sua cella e l’ha finito senza batter ciglio.\Ho anche sentito voci che gli stessi uomini dell’Ammiraglio progettano di farlo fuori. Dillo allo Squalo. E digli che avrò altro da raccontare quando ci vedremo faccia a faccia.";
			link.l1 = "Hm. Va bene, ne parlerò a Dodson. Ci vediamo!";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "Vai dallo Squalo e raccontagli tutto quello che ti ho detto. Eh, spero che aprano presto questa gabbia...";
			link.l1 = "Sì, sì. Sto andando.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "Eccoti, mio caro amico. Ancora grazie per avermi salvato e per aver riposto fiducia in me invece che in quel dannato Kapper. Voglio darti questi amuleti in segno di riconoscenza. Son certo che ti torneranno utili.";
			link.l1 = "Grazie! Non me l’aspettavo proprio...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "E ora sono pronto ad ascoltarti. Volevi chiedermi qualcosa, ho ragione?";
			link.l1 = "Hai ragione, Chimiset. Ho bisogno del tuo aiuto. Prima di tutto, devo sapere: c’è per caso un idolo di pietra strano su quest’isola? A mezzanotte si tramuta in oro. Non pensare che sia pazzo...";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "Ah, capisco bene, amico mio. Ho visto con questi occhi la statua degli dèi indiani. Si trasforma in oro solo sotto i raggi del sole mattutino, non della luna... molte volte abbiamo sacrificato quei maledetti Narvali e il dio li ha inghiottiti tutti. Ma ora non è più sull’Isola.";
			link.l1 = "Come sarebbe a dire che non c’è più?! Vuoi dirmi che è sparito tutto d’un tratto?!";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "Non proprio così. Questa statua stava nella 'San Geronimo'. Quella nave affondò con la statua diversi anni fa.";
			link.l1 = "Che sfortuna maledetta! Pare proprio che sia impossibile lasciare quest’isola ormai... E dove diavolo era finita quella nave?";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "Non lontano dai territori dei Narvali, vicino ai relitti della nave chiamata 'Fenice'. Nei giorni limpidi la puoi scorgere adagiata sul fondo del mare.";
			link.l1 = "Ah! Dunque giace tra le secche? Allora posso raggiungerla a nuoto...";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "You can't, my friend. First, it's too deep down there; second, there are many giant crabs. They will tear you apart before you get to the 'San Geronimo'.";
			link.l1 = "Hm. Va bene, ci rifletterò su. Almeno ora so che la statua esiste, ed è la cosa più importante.";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "Vedo che hai ancora domande. Chiedi pure, amico mio.";
			link.l1 = "Shark Dodson mi ha chiesto di trovare i complici di Chad nei suoi misfatti. Ho trovato una lettera nel baule di Chad. Parla di un certo tiratore e di una pistola. Pare che vogliano far fuori Shark da lontano. Ti viene in mente qualcosa?";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "Hmm. Vogliono fucilare l'ammiraglio? Devo rifletterci su... Vedi, l’ammiraglio quasi mai lascia la sua dimora, e quando lo fa, è circondato da mezza dozzina di canaglie. Ma c’ha un vizietto: la sera tardi gli piace passeggiare vicino alla poppa.\nCi sono due punti da cui un tiratore potrebbe colpire la residenza dell’Ammiraglio: la prua della ‘Santa Florentina’ e l’albero della ‘Furia’. Ma anche così, servirà un occhio di falco per abbatterlo da lì. E ci vorrà pure un fucile da vero demonio. Dovresti chiedere in giro sull’isola chi può mettere le mani su armi simili.";
			link.l1 = "Ehi, pare proprio che tu abbia ragione, nella lettera si parla di una pistola... Hai visto qualcuno con un'arma del genere?";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "No. Non ho mai visto un'arma così in vita mia. Chiedi in giro, magari qualcuno saprà dirti qualcosa.";
			link.l1 = "D'accordo... Comunque, le tue informazioni valgono oro, grazie! Allora, un'ultima domanda, anche se non m'aspetto che tu risponda... Hai mai sentito parlare del Ragazzo Bianco?";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "Ragazzo bianco? Sì, lo conosco. È il soprannome di Olle Christiansen, il nostro sciocco di casa. Ormai è cresciuto e non sembra più un ragazzo, ma la sua testa è rimasta quella d'un bambino.";
			link.l1 = "È davvero così? Dimmi, dove posso trovarlo?";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "In qualsiasi angolo della nostra città. Lo trovi spesso nella bottega, alla taverna o che vaga per le strade. Ha i capelli bianchi – lo riconoscerai di sicuro.";
			link.l1 = "Magnifico! Grazie, Chimiset, mi hai dato proprio una mano!";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "Sono sempre lieto di aiutare! Vieni pure da me se avrai altre domande.";
			link.l1 = "Certo! Ora devo andare. Ci vediamo!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "Ecco il mio caro amico, a cui devo la mia libertà e forse la vita stessa. Grazie per aver aiutato i miei fratelli a salvarmi da quel lurido Kapper. Ti dono questi amuleti in segno di riconoscenza. Son certo che ti torneranno utili.";
			link.l1 = "Grazie! Non me l’aspettavo proprio...";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "Hai qualcos'altro da chiedere, amico pallido?";
			link.l1 = "Dimmi, Chimiset, conosci il Ragazzo Bianco?";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Oh! Mio amico bianco "+pchar.name+"! Non sei affogato? Gli spiriti ti hanno salvato, lo so bene...";
				link.l1 = "Sto bene e sono vivo, Chimiset. Spiriti? Forse hai ragione, tutto questo è accaduto per colpa di Kukulcan...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Cosa ti porta qui, buon amico?";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "Raccontami com’è morto il capo dei Narvali. Solo tu hai assistito a quella scena.";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "Hai nominato quei granchi sul fondo vicino al 'San Geronimo'. Puoi descrivere quei mostri?";
				link.l2.go = "crab";
			}
			link.l9 = "Niente di speciale, Chimiset. Volevo solo vederti.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "Qui verrà scritta la storia della morte di Alan Milrow.";
			link.l1 = "Bene!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "Nessuno sa da dove siano venute queste bestie, né perché abbiano raggiunto dimensioni così gigantesche. Ne sappiamo poco, di questi mostri. Esistono, in molti li hanno visti. Gruppi di loro si aggirano tra i relitti delle navi nelle acque basse. Strisciano sul fondo del mare, danno la caccia ai pesci e si ingozzano di tutta l'immondizia che buttiamo.\nSono un vero pericolo. Le loro chele possono infliggere ferite tremende, e le fauci rilasciano un veleno micidiale, simile a quello dei pesci palla. Se avvelenato e lasciato senza cure, un uomo finisce dritto da San Pietro. Fortuna che la tossina può essere annientata con un antidoto preparato con erbe dell'isola.\nTra noi c'era un cacciatore di granchi. Portava la loro carne, un piatto da leccarsi i baffi. Ma la cosa più importante: spesso portava le chele di queste bestie e le fauci piene di veleno. Erano l'ingrediente principe di alcune delle mie pozioni. Peccato, è tanto che nessuno me ne porta più...";
			link.l1 = "E dove si trova adesso quel cacciatore?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Cogli il suggerimento. Devi essere pronto a diventare preda tu stesso quando dai la caccia a quelle bestie. Un giorno semplicemente non fece più ritorno. Ecco perché ti metto in guardia: sii cauto e tieni gli occhi ben aperti con quelle creature.";
			link.l1 = "Capisco...";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
