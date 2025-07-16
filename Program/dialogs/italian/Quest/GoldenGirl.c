// диалоги персонажей по квесту Дороже золота
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
			dialog.text = "Cosa vuoi, giusto?";
			link.l1 = "Dovrei andare...";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "Capitano Charles de Maure! Finalmente! Sua Eccellenza Jacques Dille de Parkuet esige di vederti! È urgente!";
			link.l1 = "Perché non mi sorprende? Va bene, per favore riferisci a Sua Eccellenza che arriverò presto.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "I miei occhi devono ingannarmi se è davvero Charles de Maure in persona! Non mi capita spesso di fare certi ricevimenti, e sono lieta che tu abbia trovato un po' di tempo per il mio umile rifugio. Che fortuna! Questo merita un brindisi!";
			link.l1 = "I miei omaggi, madama. Perdonate se il mio comportamento dovesse risultare deludente – è passato davvero tanto tempo dall’ultima volta che ho preso parte a simili... occasioni. L’etichetta di bordo si riduce a subordine, fazzoletti puliti e una tazza regolare di caffè rinvigorente ogni mattina.";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "Che fascino, Capitano, hai ancora addosso quel tocco di Parigi. Lo intravedo timido dietro questa maschera temprata dal sale e dal vento. Non preoccuparti, sono così felice di conoscerti finalmente che posso perdonarti molte cose. Per ora. Vedremo come andrà tra noi in futuro. Vino? Rosso o bianco?";
			link.l1 = "Un momento perfetto per una battuta sul rum, ma ahimè, non sono dell’umore, mi dispiace. Berrò volentieri qualsiasi cosa che le tue belle mani mi verseranno.";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "Bel colpo. Ma insisto. Il gusto per il vino dice molto su un uomo e stanotte voglio scoprire tutto di te. Quindi te lo chiedo di nuovo: rosso o bianco, giusto?";
			link.l1 = "Come vuoi tu. Vedo che stai bevendo rosso. Anche io allora – mi piacerebbe scoprire qualcosa su di te, giusto?";
			link.l1.go = "Julianna_3";
			link.l2 = "In quel caso, prendo il bianco ma scegli tu. Così va bene per entrambi, giusto?";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "Splendido, quindi ora tocca a me? Questo è Pinot Nero di Borgogna, i vignaioli lo chiamano 'una ragazza birichina'. Non è un vitigno facile da domare e il suo retrogusto può anche ingannare, sai. Soddisfatto?";
			link.l1 = "Pinot Noir, eh? Va bene per me. Inaffidabile e misterioso, all’inizio sembra amaro ma dagli un po’ d’aria e ti stupirà. Un ballo leggero di sfumature e sapori, una scelta da vero intenditore. Le prime impressioni ingannano, giusto? Bevo ai tuoi occhi, madama!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "Splendido, quindi ora tocca a me? Ho un meraviglioso Sauvignon Blanc, direttamente dalla valle della Loira. Abbastanza vivace, senti quasi le bollicine sulla lingua. E la ciliegina sulla torta – una nota di polvere da sparo. Suppongo che tu abbia qualcosa in comune con lui, giusto?";
			link.l1 = "Mi aspettavo di meglio, magari un Riesling. Beh, beviamoci questa rozza bevanda che sa d’estate e di polvere da sparo. Hai mai sentito dire che qualcuno lo confonde col pipì di gatto? Brinderò al tuo sorriso, luminoso come questi zaffiri!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "Straordinario, Charles! Posso chiamarti così? Non mi sbagliavo su di te, in un altro giorno saresti stato la stella della mia notte. Ma ahimè, Mio Capitano, oggi hai una concorrenza agguerrita. Sembra proprio che laggiù stia per scoppiare uno scandalo, lo vedi?";
			link.l1 = "Sento delle voci furibonde. Chi sarebbe questo signore sgradevole e cosa ha fatto per far arrabbiare il nostro caro governatore?";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "Questo 'sgradevole' signore è Angerran de Chievous, un bastardo non riconosciuto del conte de Levi Vantadur. Tu stai ascoltando la loro disputa. De Chievous cerca da anni di guadagnarsi le mie grazie e mi ha seguito fin qui, convinto di poter prendere il posto del padre ai miei occhi. Anche se non è figlio legittimo, è ricco e potente. La testardaggine è una delle sue doti, per certuni sostituisce la saggezza. Poco prima che arrivassi tu, lui e Jacques hanno iniziato a discutere del solito argomento. Sua Eccellenza mi protegge sempre in modo commovente, dovresti vedere! Su, stiamo a guardare come finisce stavolta.";
			link.l1 = "Sento puzza di guai nell’aria... C’è sempre qualche fregatura, anche in una notte così splendida...";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "Come scusa, Charles?";
			link.l1 = "Dimentica. Presentami la tua amica invadente, poi vediamo...";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "Monsieur, permettimi di presentarti il mio caro ospite – il Capitano Charles de Maure in persona ci onora della sua presenza! Figure così celebri non si vedono spesso da queste parti.";
			link.l1 = "...";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "Charles, questa faccenda non mi piace per niente! Jacques fa orecchie da mercante mentre Angerran sicuramente sta tramando qualcosa. Questi scontri avevano un senso e ora ho bisogno del tuo aiuto!";
			link.l1 = "Temo di non capire... Che cosa potrei mai fare qui? Ha già rifiutato di sfidarmi a duello...";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "Capitano, ti prego, non deludermi. Poco fa eri un maestro delle conversazioni e ora il tuo mondo si divide solo tra ciò che puoi infilzare con una spada e ciò che non puoi. Pensa fuori dagli schemi! Roviniamo lo spettacolo di Angerran. Vuole sfidare il povero Jacques da solo, ma che noia! Organizziamo un torneo! Qui ci sono diversi gentiluomini pronti a puntare sul serio e la tua fortuna è già leggenda! Forse stanotte le carte ti sorrideranno?";
			link.l1 = "Non vedo proprio come questo impedirà a de Chievous di affrontare il nostro caro governatore, ma ci sto, signora. Qualsiasi cosa pur di cancellare quel sorrisetto dalla sua faccia.";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "Splendido, ora vai al tavolo e mangia qualcosa, sarà una lunga notte. Quando sarai pronto, raggiungimi in sala, ci servirà più spazio per questa faccenda. Nel frattempo, metterò su uno spettacolo, convincendo gli altri a scommettere forte e a offrirmi qualche passatempo. Potrei pure urlare contro questi galli per far notare che c’è una dama che sta morendo di noia. Mi raccomando, non intrometterti, nessuno deve sospettare che stanotte giochiamo nella stessa squadra. A dopo, Mio Capitano!";
			link.l1 = "Come vuoi tu, signora, come vuoi tu...";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "Ebbene, congratulati con me, ci sono riuscita! Un pizzico d’orgoglio, un po’ di pregiudizio e voilà! Fai una faccia annoiata, ci stanno osservando. Lascia che credano tu sia qui solo per bere, non per me\nSta per cominciare un torneo, la posta è alta, niente seconde possibilità o rivincite. In qualche modo so che sei abituato a questo. Te la caverai. Ricorda, Angerran sta sicuramente tramando qualcosa, tenterà un colpo contro il nostro amico Jacques, ma non ha previsto il tuo arrivo. Sii il mio asso nella manica, perché vedere quella sua faccia tronfia non porta mai nulla di buono. Abbiamo otto giocatori, ma mi sono assicurata che tu non lo affrontassi prima della finale\nOh! Il tuo primo avversario! Colonnello e Comandante della nostra fortezza. Mare contro terra: una sfida degna per ospiti con esperienza militare! Applausi!";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Hai fatto un lavoro magnifico, Charles, davvero splendido. Angerran e Jacques stanno per affrontarsi proprio ora. Peccato che non abbiano ascoltato il consiglio di rimandare il torneo di una settimana. Avrei potuto radunare una compagnia davvero stellare, con pettegolezzi che sarebbero arrivati fino a Parigi! Beh, forse la prossima volta. Pare che il tuo prossimo rivale sia all’altezza della tua fortuna, un vero lupo di mare, il Capitano Moreno! Capitani, prego!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Ahimè, la fortuna t’ha voltato le spalle, Capitano. Mi dispiace, ma il gioco finisce qui per te. Angerran sta già giocando contro Jacques, quindi devo andarmene. Addio.";
				link.l1 = "È stato un piacere... signora.";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Ti faccio i miei complimenti per la vittoria meritata, Capitano! Resta ancora da vedere chi sarà il tuo avversario nella nostra finale... Facciamo due passi in disparte. Abbassa la voce e guarda quel tavolo. Vedi? Eccolo che si muove! Sto iniziando a capire cosa trama Angerran! Ha già spogliato il povero Jacques dei suoi soldi, ma non lo lascia alzarsi dal tavolo. Quando sono passata, il poveraccio aveva già scommesso dei documenti per una nave intera con tanto di carico. Purtroppo, questa notte la fortuna non è dalla sua parte. O magari qualcuno le ha detto di non esserlo.";
				link.l1 = "Pensi che de Chievous stia barando, giusto?";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "Ahimè, la fortuna ti ha abbandonato, Capitano. Mi rincresce, ma per te la partita è finita. Angerran sta già sfidando Jacques, quindi dovrei andare. Addio.";
				link.l1 = "È stato un piacere... signora.";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "Potrebbe farlo, se volesse, ma non ho prove. Il nostro caro governatore è bravo con le carte, ma lo è anche il suo avversario. Angerran non ha nemmeno battuto ciglio quando ha scommesso la sua fregata, pensa un po'. Se questo duello si tenesse a Parigi o a Lione, diventerebbe leggenda, Charles! Tuttavia, forse stasera è solo fortunato. Avviciniamoci e vediamo con i nostri occhi.";
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "Charles, stringimi o cadrò... Oppure no – questi idioti nemmeno si accorgerebbero se svenissi. L'hai visto? Jacques, maledetta la tua stupidità! Come un bambino, santo cielo! Un bambino imbecille!";
			link.l1 = "Marchesa, credo di non seguirvi.  Cosa sta succedendo laggiù a quel tavolo? Su cosa stanno scommettendo?";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "Su di me, Charles. Il nostro caro, sciocco Jacques ha puntato tutto su di me. Angerran ha trovato il suo unico punto debole e ci ha colpito proprio al momento giusto.";
			link.l1 = "Maledizione! Ma tocca a me nel torneo, potrei vincere di nuovo la sua maledetta nave al gioco d'azzardo! Perché?";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "Perché Angerran ci ha riflettuto a lungo e ha pianificato tutto nei minimi dettagli. Ascoltami, non abbiamo molto tempo. Devi fare lo stesso con lui. Spoglialo di tutto, prendi il suo denaro, tutte le sue navi, provocalo! Fagli perdere la testa per la reputazione, l’onore, la passione, qualsiasi cosa! Hai visto come si fa stanotte. Mettilo all’angolo e costringilo a rischiare grosso.\nTi supplico, Charles! Sono pronta a tutto, ma non andrò da lui. Non così! Persino il conte Vantadur non si opporrà a una vittoria onesta alle carte, non muoverà nemmeno un dito per aiutarmi. Capisci, le carte sono maledettamente sacre per la nobiltà, che vadano in malora! Sei la mia ultima e unica speranza, Charles!";
			link.l1 = "Non seppelliamo ancora il nostro governatore, signora. Magari riesce a riprendersi la nave? La fortuna è una dama... volubile.";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "Ancora non hai capito, vero? La fortuna non conta nulla a quel tavolo! Angerran de Chievous comanda tutto. Ha escogitato un modo per prendersi me e tenere suo padre fuori da questa storia. Non so da quanto tempo ci stia lavorando, ma ormai ha quasi vinto. Sta controllando il gioco e abbiamo solo un’occasione per mandare tutto all’aria. Prendi, tieni! Io farò finta, ti guadagnerò un minuto o due. Usali bene.";
			link.l1 = "Marchesa... Qualcuno, vi prego, aiutate! La signora non si sente bene! Presto!";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			Log_Info("You have received amulet 'Turtle'");
			Log_Info("You have received amulet 'Joker'");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "No, no, sto bene... Qui c'è un po' di afa... Mi scusate, signori. Esco un attimo a prendere una boccata d'aria fresca. Potete continuare senza di me.";
			link.l1 = "...";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "Non adesso e non a Saint-Pierre, ma conosco qualcuno. Te lo prometto, Angerran, sarà un dipinto degno di questo nome...";
			link.l1 = "...";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "Angerran, sei impossibile! Impara a perdere! È solo un gioco, non puoi prevedere tutto. Finisci il tuo vino e vestiti – le regole sono chiare – chi perde abbandona la nostra festicciola, giusto?";
			link.l1 = "Marchesa, aspetta...";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "State esagerando, signori! Basta così, immediatamente! Siamo tutti esausti dopo la notte passata e temo di dover chiedere ai miei ospiti di accomiatarsi. Potrete continuare la vostra disputa domani, come si conviene a uomini d’onore, a meno che non cambiate idea. Ma qui nessuno mette mano alle armi, è chiaro?";
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "Charles, temo che dovrò chiederti di lasciarmi sola anche tu. Sali di sopra e trova una stanza per te. Mi occuperò io di tutto. Ti sono grata per ciò che hai fatto per me, più di quanto possa dire, ma ho bisogno di un po' di tempo per me stessa e tu devi essere stremato.";
			link.l1 = "Non è poi così male, madama, ma non dirò di no a un letto. Questa festa improvvisata mi ha colpito più forte di una squadra navale nemica schierata! Capisco che tutto ciò non sia stato facile nemmeno per voi, marchesa. Riposate anche voi, e non preoccupatevi, non mi dovete nulla. Tutto ciò di cui ho bisogno ora è un po' di sonno.";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "Mi assicurerò che ti sveglino entro mezzogiorno. È già l’alba, quindi non posso più augurarti la buonanotte. Riposa bene.";
			link.l1 = "Anche tu, marchesa.";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "Eccoti, Charles. A dir la verità, non ho chiuso occhio, ma tu sembri bello riposato. Hai dormito bene? La colazione sta arrivando.";
			link.l1 = "La vostra ospitalità è leggendaria, madama, ma purtroppo non ho tempo per goderne. Sua Eccellenza, i secondi di de Chievous, le navi che ho vinto – tutto mi attende.";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "Hai conquistato non solo le navi. C’è un’altra cosa di cui volevo parlarti, Charles...";
			link.l1 = "Non sono né Jacques né Angerran, marchesa. Non scommetto sulle donne per guadagnarmi il loro favore. Non mi devi nulla.";
			link.l1.go = "Julianna_41";
			link.l2 = "Siete sotto la mia protezione, marchesa. Né Jacques, né Angerran vi daranno mai più fastidio, ve lo prometto.";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "O sei incredibilmente onorevole o innamorato, Charles. E non di me. Ma comunque, ti sarò eternamente grata con tutto il mio cuore. Se posso esserti utile in qualche modo – basta che me lo dica.";
			link.l1 = "Julianne, il tempo stringe e mi attende il compito più arduo. De Chievous è una canaglia, e persino un duello onorevole può finire male come quello cui abbiamo assistito ieri notte. Parliamone più tardi, quando tutto sarà finalmente finito. Ti ringrazio per avermi offerto un rifugio tranquillo dove dormire, e non vedo l’ora di rivederti.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "Ti sono grata con tutto il mio cuore, Charles... Fidati, essere il tuo bottino è una sorta di vittoria anche per me. Che ne dici se continuiamo questa conversazione in un ambiente più... privato?";
			link.l1 = "Julianne, il tempo stringe e sto per affrontare il compito più difficile che mi sia mai capitato. De Chievous è una canaglia e persino un duello onorevole può finire in modo sporco, proprio come quello che abbiamo visto ieri notte. Parliamone più tardi, quando tutto questo sarà finalmente finito. Ti ringrazio per avermi permesso di riposare in silenzio e non vedo l'ora di rivederti.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "Non ti trattengo oltre, Mio Capitano. Ma ricorda, Angerran è pericoloso. Non so giudicare le sue doti in battaglia, ma ha partecipato a diverse guerre e ha combattuto a Rocroi. Ho pure sentito che ha vinto più di un duello, soprattutto con le pistole. Soprattutto, però, è un uomo falso, come hai già notato. Ti prego di fare attenzione e... vieni da me, dopo!";
			link.l1 = "La premura ti si addice proprio, marchesa. Fidati, de Chievous non è il primo bastardo che cerchi di ostacolarmi. Me la caverò. Ora devo davvero andare da Sua Eccellenza a discutere della questione del duello.";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "Che il vento ti sia favorevole, Mio Capitano! E di’ a Jacques di tenersi ben lontano dalla porta di casa mia.";
			link.l1 = "Hai la mia parola. Ci vediamo, marchesa!";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "Capitano, ce l'hai fatta, che sollievo! Com’è andata? Stai sanguinando?!";
			link.l1 = "Non è tutto il mio sangue... almeno non tutto. Marchesa, dov’è de Chievous?";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "Stavo per chiederti la stessa cosa – non l’hai steso tu? Che è successo? Perché fuori vedo mezza guarnigione cittadina, giusto?";
			link.l1 = "Ho detto al governatore che potevi essere in pericolo. De Chievous è rimasto ferito ed è scappato, lasciando i suoi scagnozzi contro di noi. È stata una carneficina. Anche se, storie simili non sono per le tue belle orecchie. È finita. Sei libera da lui e dal nostro ‘dolce’ Jacques.";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "È davvero brutto, Charles. Nemici come Angerran de Chievous vanno eliminati per sempre quando ne hai l’occasione. Conosco quell’uomo da anni – non è certo uno che dimentica i torti. Prima o poi troverà il modo di vendicarsi. Ma non mi piace vederti tutto abbandonato così, la tua ferita è stata curata?";
			link.l1 = "Solo un graffio, ne ho passate di peggiori. Fa un po’ male, tutto qui. Grazie per la premura, signora, ma dovrei andare...";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "Capitano, hai rischiato le tue navi e il tuo oro per me, hai combattuto per me rischiando la vita e la reputazione. Il minimo che possa fare è curare le tue ferite e offrirti un rifugio sicuro. No! Non voglio sentire altro. Prendi la mia mano e seguimi di sopra. La tua stanza ti aspetta.";
			link.l1 = "Accetto la tua offerta, signora, grazie. Ma preferirei non gravare su di te. Salirò di sopra da solo.";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "Marchesa, sei il mio angelo custode. Temo di doverti qualcosa io, adesso.";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "Charles, sei proprio l’emblema della cavalleria! Giuro su Dio, se continui così, perderò la testa! Giusto? Va bene, mio cavaliere, mando Denise da te: si prenderà cura delle tue ferite come farebbe un medico vero.";
			link.l1 = "Grazie, marchesa. Se il mio cuore non fosse già impegnato, sarei lieto di stare al gioco. Ma ahimè! Buona notte!";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "In tal caso, esigo che tu mi assecondi subito. Prendimi la mano e fai come dico io. Denise! Porta della stoppa, vino caldo e qualcosa da mangiare di sopra! Andiamo, Mio Capitano. E ricorda – questa volta niente discussioni!";
			link.l1 = "Come dici tu, marchesa, sono tutto tuo.";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_KissJulianna");
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Buongiorno, Charles. Come vanno quei tuoi 'graffi', giusto?";
				link.l1 = "Grazie ai tuoi sforzi mi sento rinata. Ti prego, accetta la mia sincera gratitudine, Julianna.";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "Buongiorno, mio eroe. Come stanno quei tuoi ‘graffietti’?";
				link.l1 = "Grazie per la sua premura, signora, sto benissimo. Pagherei un tesoro per avere la vostra Denise come medico di bordo. È davvero un miracolo!";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "Temo che non sarà facile sistemare la cosa. Ma non mi sarei mai permessa di svegliarti senza un motivo serio. Fidati, ho vegliato sul tuo sonno senza paura, ma quest'uomo qui sotto è davvero ostinato. Dice di far parte del tuo equipaggio e che è urgente.";
			link.l1 = "La mia ciurma? Hai fatto bene a svegliarmi, marchesa! Mi metto subito in viaggio.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "In altre circostanze lo farei, Mio Capitano, ma dovremo rimandare. Un certo messer di scarsissima educazione ti aspetta giù: sostiene di essere uno della tua ciurma e dice che è urgente.";
			link.l1 = "Ci torneremo, Madame, quando sarò di ritorno. Spero che non si tratti di quegli spagnoli che ci assediano di nuovo.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "Charles, sei tornato! Che notizie ti ha portato il tuo uomo? Non mi hai nemmeno salutata, giusto?";
			link.l1 = "Mi scusi, marchesa. De Chievous ha giocato sporco ancora una volta. Ha rubato la mia nave e ha salpato questa notte. Una delle mie ufficiali di fiducia era a bordo e non posso lasciarla nelle mani di quel bastardo.";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "Lei? Tieni una donna come ufficiale a bordo della tua nave? Va contro tutto ciò che so sulla vita di mare. Cosa ti fa credere che sia ancora viva?";
			link.l1 = "Spero. Julianna, la speranza è tutto ciò che mi resta per ora. Devo sapere di più su Angerran de Chievous. Devo assolutamente scoprire dove sia andato! Devo riportarla indietro!";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "Adesso capisco! Sei davvero innamorato, mio cavaliere! Darei volentieri metà della mia vita per una fedeltà e un affetto così, senza pensarci due volte!";
			link.l1 = "Non ho fatto nessun voto, ma questa donna significa davvero molto per me, marchesa.";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "Questa gelosia mi commuove davvero. Ascolta, Charles, sono pronta a diventare gelosa anch’io per te! Ma quale cortigiana saprebbe resistere alla voce del vero amore? E poi, mi hai salvata, cavaliere mio—ovvio che ti darò una mano. Chiedimi pure, giusto?";
			link.l1 = "Grazie. Conosci de Chievous da un bel po'. Dove credi che possa essersi nascosto dopo tutto quel trambusto, per sfuggire all'ira di suo padre?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "E se riuscissi a sedurti con un bel brunch? Non hai pensato a questa ragazza per due giorni, magari può aspettare ancora un giorno, giusto?";
			link.l1 = "Marchesa, capisco come posso apparire ai vostri occhi, ma ciò che è fatto è fatto. Anche se non ho mai giurato fedeltà, il mio cuore ormai le appartiene. Vi supplico di comprendermi e di aiutarmi.";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "Dai, Charles! Difenderti parlando d’amore davanti a una cortigiana? Non ridevo così da secoli! Sei davvero incredibile! Rilassati, quello che è successo in questa casa resta qui. Non dimentico ciò che ti devo. Chiedi pure.";
			link.l1 = "Grazie. Conosci de Chievous da parecchio tempo. Dove credi che possa essersi rifugiato dopo tutto quel trambusto, per sfuggire all’ira di suo padre?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "A dire il vero, anche se invitare Angerran de Chievous non è la cosa più piacevole da fare, resta comunque molto utile dal punto di vista politico. È ben accolto ovunque, persino tra le nazioni alleate con la Francia. Ma so che solo un uomo qui vicino gli offrirà sempre una mano e un rifugio. François de Lyon, il governatore della nostra colonia in Guadalupa. È un vecchio collaboratore del conte de Levi Vantadur e ha sempre avuto un debole per quel bastardo.";
			link.l1 = "Guadalupa, dunque! È la migliore pista che potessi sperare! Se salpiamo questa sera, li raggiungeremo con solo un giorno di ritardo.";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "Aspetta, Charles, c’è ancora una cosa. Ho ricevuto una lettera per te, proprio di recente. Pensavo fosse legata al duello, ma ora non ne sono più tanto sicura. Eccola qui.";
			link.l1 = "Niente sigillo, ma la carta è di pregio. Non mi piace per niente...";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Dai, Charles! Non tenermi sulle spine, viene da lui, giusto?";
			link.l1 = "Sì, è proprio da lui. Lei è viva! L'ha catturata mentre rubava la mia nave. Ora propone di incontrarci e discutere tutto questo in modo civile. Proprio come hai detto tu, Guadeloupe, Basse-Terre.";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "Monseniore de Lyons sceglierà sicuramente il figlio di Leve Vantadur al posto tuo. De Chievous potrebbe tenderti un'altra trappola! Difendendomi, Charles, ti sei fatto un nemico potente. Vorrei poterti aiutare, ma temo che tutto ciò che posso fare sia chiederti di stare in guardia.";
			link.l1 = "Julianne, non sarei mai sopravvissuta nel Nuovo Mondo se avessi sempre scelto la via più diretta. Gli affari loschi non sono il mio forte, ma so come muovermi tra le ombre.";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "Novità, capitano?";
			link.l1 = "Ahimè, nulla...";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "Bentornato, Charles! Son felice di vederti vivo e vegeto. Quali novità?";
			link.l1 = "Tutto ciò che sapevamo sulle capacità di de Chievous si è rivelato essere una grave sottovalutazione. Quel bastardo tiene prigioniero il mio... ufficiale, e ho solo due settimane per raccogliere il riscatto. Temo che senza il tuo aiuto non potrò farcela.";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, il tuo amore è come un'anemone dei venti, ma ti sono molto debitrice e farò tutto il possibile per aiutarti. In che modo posso esserti utile?";
			}
			else
			{
				dialog.text = "Charles, te l'ho già detto che non dimenticherò mai quello che hai fatto per me. Farò il possibile per ricambiare. Sono pronta, anche se non capisco bene in che modo potrei esserti utile in questo.";
			}
			link.l1 = "Per favore, siediti, Julianna. Vedi, il riscatto di Angerran... sei tu. E non intendo come protetta ufficiale, ma proprio come una prigioniera legata nella stiva del suo bastimento.";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "Sono senza parole... Ma il tuo volto mi dice che non stai scherzando. Ha perso la testa?";
			link.l1 = "Piuttosto, lui è convinto che io l’abbia fatto. È così disperato da oltrepassare ogni limite, giusto?";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "E cosa, me lo stai davvero chiedendo? Di non urlare mentre mi rapiscono? Capitano, non credi che sia un po' troppo da pretendere? Ti sono molto grata, ma salvare l'amore di qualcun altro offrendo la mia vita a uno sciagurato senza onore... Qui il cavaliere sei tu, mentre io sono una donna estremamente realista e concreta.";
			link.l1 = "Temo, signora, che sia proprio questo ciò che vi chiedo. Preparate le vostre cose, ce ne andiamo. Mi duole molto, ma il tempo stringe.";
			link.l1.go = "Julianna_76";
			link.l2 = "Marchesa, non rapisco dame che si affidano a me. E questa potrebbe essere la nostra occasione.";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "Sei proprio pieno di sorprese, Charles. Hai sentito? Ecco, tutta la pazienza che avevo per te è appena svanita in mille pezzi. Che sia amore o no, non permetterò che tu mi rapisca. Guardie! Aiuto!!! Qualcuno!!!!";
			link.l1 = "E io che pensavo fossimo amici, giusto?";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "Questo è un oltraggio! Che cosa hai trasformato il mio salotto?! Che diavoleria è mai questa? Charles, rinsavisci! Sei un gentiluomo, non un maledetto pirata!!";
			link.l1 = "Ti ho già chiesto scusa. Ti ho pregato di non complicare ancora di più la situazione – ma non mi hai dato retta. Credimi, non godo affatto in quello che sto facendo, ma non ho alternative. Farò tutto ciò che serve per quella donna.";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "Che razza di dama sceglierebbe mai un cavaliere come te? Ci vado io da sola, tieni giù le mani! Non stai rubando una vacca, quindi dimostra un po' di decoro!";
			link.l1 = "Va bene. Seguimi, signorina. Stai dietro la mia schiena e tieni la testa bassa – magari non gli verrà voglia di sparare.";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.greeting = "Marquesa_again";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "Per un attimo ho pensato di non conoscerti affatto, Charles. Quello sguardo... Ma che cosa stai per fare allora? Quale occasione hai menzionato?";
			link.l1 = "Perché quel bastardo mi usa per arrivare a te? Perché ha messo in scena quella partita a carte invece di prendersi ciò che voleva? Di cosa ha paura, giusto?";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "Niente. Ahimè, le ragioni dietro tutto questo sono banali e primitive. Il conte Henri ha ancora un debole per me. Angerran rischierebbe troppo se mi facesse qualcosa contro la mia volontà. Mi dispiace, Charles, ma è un vicolo cieco. Negherà tutto e la farà franca. Nessuno crederà alle tue parole, tu che sei il rapitore, mentre suo padre ti annienterà.";
			link.l1 = "Maledizione! Avrei voluto evitarlo... Prepara tutto, marchesa, dobbiamo andare. E sì, ti chiedo di stare zitta.";
			link.l1.go = "Julianna_76";
			link.l2 = "Ma quel bastardo avrà pure altri punti deboli oltre a suo padre, giusto? Non è affatto perfetto, anzi, è proprio l’opposto!";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "Non so se questo ci tornerà utile... a noi. Angerran aveva degli affari con il barone dei pirati locali. Jacques Baraban?";
			link.l1 = "È Barbazon, madama. Una bella coppia, davvero! Ma Jacques il Buono non mi sopporta e non posso attaccare Le Francois senza una certezza assoluta.";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "Sei di nuovo troppo diretto, mio cavaliere. Ti ricordi del capitano Moreno? Il tuo secondo avversario al gioco? Scommetto che è qui per via di Angerran. Deve sapere qualcosa che ci può tornare utile.";
				link.l1 = "Capitano Moreno, eh! Sì, certo. È ancora in città? Dove posso trovarlo?";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "Sei di nuovo troppo diretto, mio cavaliere. Qualcuno sa sempre qualcosa, e non tutti riescono a tenere la bocca chiusa in certe situazioni. I miei... allievi ascoltano molte cose, in questa casa. Dammi un giorno e scoprirò di più, oppure ti troverò qualcuno che lo farà.";
				link.l1 = "Marchesa, pensavo che la preoccupazione ti donasse, ma la rabbia ti sta ancora meglio. Grazie, stai accendendo una speranza dentro di me!";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "Sì, è ancora qui e ti risparmierò la fatica di cercarlo in giro. Vieni qui domani sera – il capitano Moreno ti aspetterà proprio qui, in questa stanza. Vorrei poterti aiutare di più, ma non posso, Charles.";
			link.l1 = "È già più che sufficiente, marchesa. Con lui al mio fianco, tutto sarà molto più semplice. Grazie. Ci vediamo domani sera.";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "Vorrei sentirlo da te in un’altra circostanza, Charles. Vieni a trovarmi domani sera. Spero di poterti dare ciò che cerchi.";
			link.l1 = "Grazie ancora, Julianna! Allora, domani sera.";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "Eccoti qui, amico mio! Il capitano Moreno ti sta già aspettando.";
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "Charles, credo di aver trovato qualcosa. Ti ricordi del capitano Moreno? Quello che ha giocato contro di te quella notte maledetta?";
				link.l1 = "Sì che lo è, che mascalzone. E lui, allora?";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "Lo sapevo fin dall'inizio, Bartolomeo de la Cueva. Ecco perché sei riuscito a imbucarti alla mia festa. È stato come aggiungere un po' di peperoncino al banchetto, giusto? So che tu e i tuoi compari state curiosando su quest’isola già da un paio di settimane. E so che tutto questo deve avere a che fare con il barone pirata di Le Francois e Angerran de Chievous. Racconta tutto al mio amico e manterremo segreto il tuo nome leggendario. Altrimenti, chiamerò le guardie che già aspettano fuori dalla porta. Le ho fatte venire appena sei arrivato.";
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "Non solo loro! Angerran mi ha regalato una collana, bellissima! Perle grandi e pure, e al centro questa qui, scurissima come una notte nei mari del sud. Però l’ha fatta fare dai gioiellieri locali, giusto?";
			link.l1 = "...";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "Scommetto che non l'ha fatto solo per farmi contenta con un dono di lusso. Anche se, quel regalo era proprio l’ultima carta che gli restava per guadagnarsi il mio favore senza superare i limiti della decenza. Angerran non ha né titoli né terre, e persino la sua fregata resta sua solo finché deciderà suo padre. Si muove tra potere e influenze, ma non ha un soldo suo. Forse si è stufato di aspettare le elemosine paterne e ha deciso di sistemarsi le finanze da solo?";
			link.l1 = "Aspetta, signora! Il gioco delle carte! Se abbiamo ragione, e de Chievous ha pianificato tutto in anticipo, doveva procurarsi un bel gruzzolo per puntare abbastanza da mettere alle strette il nostro governatore. Chiedere una simile somma ai genitori avrebbe attirato attenzioni indesiderate. Rubare tesori già rubati ai corsari era il modo più silenzioso e sicuro per mettere insieme il denaro necessario. Nessuno l’avrebbe scoperto!";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "A noi, Charles! Angerran non deve passarla liscia stavolta. Il suo potere su di me è arrivato troppo oltre e vorrei aiutarti a sistemare la faccenda.";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "Un pirata da quattro soldi e una cortigiana quasi innamorata. Charles, ti sei messo insieme una bella squadra dei sogni, giusto?";
			link.l1 = "Comunque, grazie a entrambi. Davvero! Ora devo rifletterci un attimo e mettere insieme un piano.";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "Questa casa può offrire tutto ciò che desiderano i suoi ospiti. Mi occuperò io dei preparativi. Raggiungici quando sei pronto, Charles.";
			link.l1 = "Molto bene, signora.";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "Niente, ma qualcuno in città lo sta cercando. Stanno facendo domande su di te e sugli altri ospiti di quella notte. Non so ancora cosa stia succedendo, ma sono certa che ti sei cacciato in qualcosa di più grosso di quanto immagini.";
			link.l1 = "Qualcosa di più grande? Che intendi dire, Julianne?";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "Angerran... cioè Monseniour de Chievous mi ha regalato una collana di perle davvero splendida. Una delle perle era nera come la notte. Pensavo fosse solo un falso con una bella storia dietro. Non l’ho mai indossata, non volevo illuderlo, ma è davvero di una bellezza ipnotica.";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "Cosa farai, Charles? Hai qualche idea di cosa stia succedendo, giusto?";
			link.l1 = "Non ancora, ma lo farò. De Chievous è invischiato fino al collo in qualche faccenda grossa, e questa è la mia occasione. Nel suo paese nessuno osa sfiorarlo, ma le autorità britanniche potrebbero farlo. Preferirei non rapirti, Julianne.";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "Che carino da parte tua, Charles, ma non è affatto divertente.";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "Charles, hai scoperto qualcosa? Sembri agitato... Che succede?";
			link.l1 = "Maledizione! Vorrei che le cose fossero diverse... Prepara la tua roba, dobbiamo andarcene, Marchesa. Ti prego, non combinare guai.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "Charles, entra pure. Il Baronet è già arrivato e abbiamo scambiato due chiacchiere piacevoli. Gli stavo proprio raccontando del tuo interesse per gli ultimi avvenimenti.";
			link.l1 = "Julianne, non sono così certa che fosse una mossa saggia...";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "Baronetto, pare che i tuoi uomini abbiano appena lasciato cadere qualcosa dietro la porta! Potresti dir loro di comportarsi meglio, giusto?";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "Orrendo! E adesso che facciamo, giusto?!";
			link.l1 = "Maledizione! Vorrei che le cose fossero diverse... Prepara la tua roba, dobbiamo andare, Marchesa. Ti prego, non combinare guai.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "Per tutti i santi! Che diavolo avete fatto al mio salotto, signori?! Sembra l’incubo di un’epoca oscura! Chi sono queste persone? E dove sono finiti i soldati?";
			link.l1 = "Tutto bene, Julianne? Perfetto. Scommetto che le guardie si stanno già godendo la loro mazzetta in qualche taverna. Barone, congratulazioni: sei riuscito a far incazzare di brutto quel bastardo di Goodman Jack. Un attentato così pasticciato e improvvisato non è proprio il suo stile, giusto?";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "Perdonate se interrompo la vostra animata discussione, ma a meno che qualcuno di voi non sia ferito, spostiamoci in una cabina. Uno spettacolo simile non è certo rassicurante per una signora... Solo il soffitto è senza sangue!";
			link.l1 = "Allora vai di sopra, marchesa. Dovresti davvero sdraiarti un po', lontano da tutto questo sangue. Il baronetto Cortney ed io discuteremo la faccenda. Possiamo continuare?";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "Charles, sei pronto a svelarci il tuo piano?";
			link.l1 = "Quasi. Dimmi, de Chievous è uno di quei tipi pedanti? Tiene i suoi registri e libri tutti in ordine, giusto?";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "Angerran è la personificazione dell’indugio quando si parla di soldi! Firma più fogli lui di quanti ne abbia mai visti in mano a un banchiere. Credo sia sempre stato così, da quando era bambino e non sapeva chi fosse suo padre, vivendo nella miseria per le strade.";
			link.l1 = "Splendido! Ora ci servono il suo registro di bordo e i suoi libri! Saranno una prova valida per gli inglesi. Dobbiamo scoprire come metterci le mani! Ah, se solo lo avessi saputo quando avevo la sua nave... sospir.";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "Aspetta, Charles, credi davvero che dopo tutto quello che è successo io mi lascerò vendere a de Chievous come una capra da cortile?";
			link.l1 = "Non ti preoccupare, Julianne, ci vorranno solo pochi giorni. Prometto che ti tratteranno come una porcellana preziosa della Cina. Correggimi se sbaglio, ma de Chievous non si farà mai vedere allo scambio, giusto?";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "Ne sono certa. Angerran starà all'ombra di Francois de Lyons e non oserà mai affrontarti in mare aperto. Ma, a proposito di questa mia cattura...";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, scusami se interrompo, ma non pensi di dover chiedere anche il mio parere su tutto questo? Settimane chiusa in quelle casse scricchiolanti... Ti rendi conto di cosa mi stai chiedendo?! È chiaro che ci tieni a quella... ragazza, ma io non sono uno dei tuoi marinai! Scusami, ma tutto questo non mi sembra affatto una storia d’amore seria.";
				link.l1 = "Temo, marchesa, di dover insistere. Non posso permettermi di perderla.";
				link.l1.go = "Julianna_127";
				link.l2 = "Tutti sbagliamo, Julianna. Dovresti saperlo meglio di chiunque altro. Ti sto chiedendo di aiutarmi.";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "Charles, mi dispiace interrompere, ma non ti sei dimenticato di chiedermi cosa ne penso, in tutto questo? Settimane dentro quelle bare cigolanti... Hai davvero idea di cosa mi stai chiedendo?! I tuoi sentimenti sono degni dei poemi cavallereschi, ma io sono solo una semplice cortigiana. Ti ammiro e voglio aiutarti, però ogni cosa ha un limite!";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "Capisco, Charles. Vorrei credere nell’amore perfetto e vero, ma suppongo che in questo mondo non esista davvero.";
				link.l1 = "Grazie, marchesa. Stavolta rimetterò tutto a posto. Ho imparato molto da questa storia, e prego che il prezzo da pagare per i miei errori non sia troppo terribile.";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "Hai preso la tua decisione, ti ho sostenuto fin dall’inizio, ma ora basta. Sacrificare tutto per un amore che avevi già lasciato sul mio cuscino... È tutto molto commovente, Charles, ma non sono più così giovane e ingenua.";
				link.l1 = "Temo, marchesa, che dovrò insistere. Non posso permettermi di perderla.";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "Ebbene, Capitano, fai come vuoi. Non ti resisterò, ma sappi che lo faccio contro la mia volontà.";
			link.l1 = "Pensa di me ciò che vuoi, Julianna, me lo sono meritato. Ma la riporterò indietro a qualunque costo\nJulianna, ascolta, so bene cosa ti sto chiedendo. Lasciare tutto alle spalle e permettere che altri ti coinvolgano in un rischio incerto. Ma in questo momento tu sei la mia unica speranza! Ho bisogno del tuo aiuto e ti sarò debitore fino alla fine dei miei giorni!";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "Molto bene, Capitano. Alla fine, Angerran deve essere eliminato una volta per tutte. Ti darò una mano, ma dimmi: come pensi di tirarmi fuori dalla sua nave?";
			link.l1 = "...";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "Aspetta. Puoi prendere la perla della mia collana, gli inglesi cercano la perla nera, giusto? Questa li farà ascoltare quello che hai da dire. E ora che si fa?";
			link.l1 = "Poi porterò l’investigatore a bordo e salperemo per Guadalupa. Faremo una perquisizione ufficiale sulla fregata di de Chievous, quando sarà tornato con te a bordo. La faccenda della Mercury è stata un affare grave che ha coinvolto un nostro alleato, quindi De Lyon dovrà permetterlo!";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Dirà a tutti che sono stati i suoi uomini a salvarmi dalla prigionia. E sappi, Capitano, non ho ancora deciso cosa racconterò io a loro.";
				link.l1 = "Non dire nulla andrebbe benone, marchesa. Fidati, ti tirerò fuori di qui e farò pagare tutto ad Angerran.";
			}
			else
			{
				dialog.text = "Dirò loro che sono stata rapita da sconosciuti, proprio dalla mia casa, e portata sulla nave di Angerran. Sembrerà che lui abbia pagato dei mercenari per rapirmi, giusto?";
				link.l1 = "Un altro chiodo nella bara di Angerran, marchesa.";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Dammi tempo fino al mattino, a meno che tu non voglia portarmi in spalla come un sacco. Mandami anche un paio di uomini ad aiutarmi – una donna di rango non può viaggiare senza qualche comodità. Charles, mi hai salvata e ricambierò il favore, inoltre prendi questa perla nera preziosissima, è il mio dono per te. Se tutto va bene, saremo pari.";
				link.l1 = "Come dite, marchesa. Che il vento vi sia favorevole, ad entrambi! Ci rivediamo qui, quando tutto sarà finito.";
			}
			else
			{
				dialog.text = "Sarò pronta all'alba. Non ho intenzione di dormire come un sacco di patate in una stiva, quindi assicurati di prepararmi una stanza decente – o come diavolo la chiamate voi, qui. Charles, tieni, prendi questo. È una perla nera preziosa. So bene che vale più di questo posto intero, ma certe cose non si misurano in oro. Spero che ti sia utile. Che Dio ti assista!";
				link.l1 = "Che il vento vi sia favorevole, tutti e due! Ci rivediamo qui quando sarà tutto finito.";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Congratulazioni, Capitano. Il tuo piano ha funzionato. Che scandalo colossale hai messo in piedi! Gli inglesi si sono presi Angerran e la sua nave con tutto il carico, tranne me.";
				link.l1 = "Sir William non è nemmeno venuto a salutarmi. Aveva promesso che si sarebbe scusato.";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "Charles, ce l’abbiamo fatta! Ti lasceranno andare da un momento all’altro! Però dobbiamo lasciare quest’isola il prima possibile. Il governatore è furibondo dopo l’arresto di Angerran.";
				link.l1 = "Sono felice di vederti, Julianne. Come stai? Com’è andato lo scambio? Sta bene?";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Immagino fosse troppo occupato per pensarci. Proprio come il nostro governatore adesso. Faresti meglio ad andartene dalla città prima che si ricordi di te. Era davvero affezionato al figlio di Henri, ma la stampa inglese l’ha messo alle strette per bene. Io non aspetterei che decida di sfogare tutta la sua frustrazione su di te.";
			link.l1 = "Va bene. Inoltre, mi sta aspettando in Martinica. Com’è andato lo scambio? Sta bene?";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "Perdonami, ma non voglio parlarne. Chiedilo a lei, piuttosto. Addio, Capitano. Tornerò per conto mio. Ho bisogno di riposare un po’ dalla vita di mare – François è un ospite davvero piacevole, quando non viene infastidito da quegli noiosi funzionari inglesi.";
			link.l1 = "Mi dispiace sinceramente per tutto questo, Madame. Grazie comunque per la collaborazione. Sono lieto di sentire che avete trovato un nuovo... amico.";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "Grazie anche a te, Charles, per aver mantenuto la parola. Trova Bartholomew a casa mia a St. Pierre. Addio. Ci rivedremo.";
			link.l1 = "Addio, Julianne. Che il vento ti sia favorevole.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Non l’ho vista, ma Bartholomew l’ha portata via viva e in salute. Quell’inglese ha arrestato de Chievous e s’è preso i suoi averi proprio sotto il naso del governatore locale – e quello non ha fiatato! Da non credere!";
			link.l1 = "Sai, è andato incredibilmente liscio, considerando tutto quello che c'era dietro a questo arresto. Anche se, prima o poi, qualcosa ci cadrà addosso. Ma chissenefrega! Devo andare subito a Martinica, devo vederla il prima possibile!";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "Di sicuro voi due avrete tanto da dirvi. Oh, Charles, vorrei anch'io un uomo con quello sguardo ardente accanto a me. Su, sbrighiamoci: mi mancano un bagno caldo e lenzuola pulite. Bartholomew ci aspetterà a casa mia a Saint-Pierre.";
			link.l1 = "Sì, il romanticismo dei viaggi per mare è sopravvalutato. Avrai la mia cabina, marchesa, è il minimo che possa fare. Andiamo.";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "Hai già fatto per me tutto ciò che potevi, Charles. Hai fatto sì che una donna cinica tornasse a credere ancora.";
			link.l1 = "Anch'io, Julianne. Anch'io.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, sono così felice che tu sia venuto! E quella tua signorina, come sta? Sta bene, giusto?";
				link.l1 = "Va tutto bene, grazie a te, Julianne. Volevo dirtelo ancora una volta. Sei una donna straordinaria e ti sarò sempre debitore per il tuo coraggio e la tua astuzia.";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "Charles, sono così felice che tu sia venuto! E quella tua signora, come sta? Va tutto bene, giusto?";
				link.l1 = "Tutto va bene, grazie a te, Julianne. Volevo dirtelo ancora una volta. Sei una donna straordinaria e ti sarò per sempre debitore per tutto il tuo coraggio e la tua ingegnosità.";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "Forse sono io a doverti qualcosa. In fondo mi hai salvata da due clienti davvero fastidiosi. Credo di essere ancora in debito con te. Chiedimi qualsiasi cosa, Charles.";
			link.l1 = "In tal caso avrei un piccolo favore da chiederti, mia signora. Puoi fare qualcosa per pareggiare i conti fra noi.";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "Son tutta orecchi, Mio Capitano. Dimmi pure.";
			link.l1 = "La gente sbaglia, ma questo non rende il mondo cattivo. Ricordalo e sii felice, Julianne. Meriti davvero la felicità.";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "Io... ci proverò, Charles. Grazie. Verrai a trovarmi ogni tanto... come amico? Sarai sempre il benvenuto a casa mia!";
			link.l1 = "Ti ringrazio, marchesa. Addio, e non dimenticare ciò che mi hai promesso.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "Eppure a quanto pare non abbastanza straordinaria... ma sono felice che per te sia finita bene. Non mi devi nulla, dopo quello che hai fatto non ti ringrazierò mai abbastanza! Passa a trovarmi quando sarai a terra. Sarai sempre il benvenuto a casa mia, come amico!";
			link.l1 = "Grazie, marchesa. Ti auguro ogni bene. Addio!";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "Charles, amico mio, sei proprio maleducato – passi a trovarmi così di rado! Mi sei mancato, lo sai? Ti va un po' di vino? Muoio dalla voglia di sentire storie emozionanti raccontate da te! E magari provare la tua famosa fortuna, giusto?";
			link.l1 = "Marchesa, volevo solo salutarti e assicurarmi che stai bene, giusto?";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак Дьель дю Парке
		case "governor":
			dialog.text = "Eccoti qui, amico mio! Che piacere rivederti, giusto?";
			link.l1 = "...";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "Ebbene, il modo in cui tratti la mia amica non mi lascia altra scelta, monsieur. Accetto la tua sfida. Dove e quando?";
			link.l1 = "Qui e ora. Chiama i servitori, digli di portare delle candele, questa penombra accogliente non va affatto bene. Qui dev’esserci luce come in pieno giorno!";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "Amico mio, ti prego, non prenderla troppo sul personale. Angerran è proprio uno scellerato, questo è vero, ma non dovresti stuzzicarlo tu. Lascia fare a me, giusto?";
			link.l1 = "Sicura, vostra Eccellenza? È ubriaco fradicio come il mio nostromo dopo una settimana a terra, ma di certo sa come maneggiare la spada. Me ne accorgo subito, giusto?";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "Dio ce ne scampi, Charles! Non mi batterò con lui a duello. Giocheremo d’azzardo, ché le carte sono le armi dei gentiluomini. Lo rovinerò al tavolo e te lo manderò a supplicare un prestito per tornare sano e salvo a Québec.";
			link.l1 = "È un piano solido, giusto? Ma se vuoi sapere la mia, preferirei vedere quel bastardo morto, non solo al verde. Vento in poppa, Vostra Eccellenza!";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			sld.greeting = "Marquesa_needhelp";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "Maledizione, Angerran, non può essere dieci là! Proprio impossibile, giusto?";
			link.l1 = "Era forse un’accusa? L’accordo era il tuo, monsieur.";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "Non lo era. È solo che... sono un po’ troppo agitata, e ti chiedo scusa. È stato un incidente e pretendo la rivincita! Questa nave, io... devo riprenderla! O al diavolo la sfida, dimmi soltanto: per quanto saresti disposto a vendermela? Sputa il prezzo e domani prima di mezzogiorno vedrai i dobloni!";
			link.l1 = "Ahimè, credo con tutto il cuore che il bottino del gioco d’azzardo non si possa ricomprare: si può solo riconquistare. Il flauto ora è mio e non ho alcuna intenzione di venderlo. Mi spiace che la tua passione ti abbia messo in questa posizione, a volte dovremmo essere più realisti sulle nostre capacità... Forse hai altri documenti di bordo?";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "Sei un infame, Angerran, e mi hai messo alle strette. Credo di poter offrire una posta che accetterai.";
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "Charles, sei la mia unica speranza, ti prego aiutami! Quel flauto e il suo... carico sono già stati venduti alla Compagnia Olandese. Devo consegnare tutti i documenti domani. Pensavo di restare qui tutta la notte, quindi li ho portati con me. Mi troverei in un disastro se l’accordo saltasse!";
			link.l1 = "Ma ‘dolce Jacques’, non pensi anche tu che la donna che hai favorito si trovi ora in una situazione ancora più disastrosa? Ho avuto anch’io la mia dose di scommesse e capisco cosa vuol dire rischiare una nave, anche se non è la tua. Ma scommettere su una donna?! Mi hai davvero stupito, giusto! E adesso tutto ciò che ti interessa è il destino del tuo affare?";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "Non giudicarmi, Charles. Darsi da fare con l’ex amante di un potente conte e magari anche innamorarsi un po’ non è nulla in confronto al dover un milione di pesos a Peter Stuyvesant. Come lo spiego al suo agente? Immagina che danno per la reputazione!";
			link.l1 = "Una volta avevo anch’io un debito simile, ma non avevo nulla eppure me la sono cavata, giusto? Ce la farai anche tu. Ci vediamo in giro, Jacques. Nessuna promessa e non ti chiederò neanche che tipo di carico valga un milione, tanto da nasconderlo in una flûte.";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "Eccoti, Charles. Stavo proprio per mandare qualcuno a cercarti. De Chievous insiste per un duello e rifiuta ogni tentativo di riconciliazione. Te la sei cavata bene con le carte, ma sei sicuro di voler continuare così?";
			link.l1 = "Ho il sospetto, Vostra Eccellenza, che desideravate proprio questo risultato fin dall’inizio. Dunque sì, accetto. Questa faccenda va risolta una volta per tutte. E quali saranno le condizioni del duello?";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "Sei troppo perso nei tuoi pensieri, amico mio. Alcune cose in questo mondo non girano tutte intorno a te. Fidati, sono davvero delusa da come sono andate le cose ieri notte. Ma davvero. Prima però, parliamo del destino delle tue... vincite.";
			link.l1 = "Va bene. Vuoi sapere come riavere il tuo flauto o come se la passa Madame Julianne, giusto?";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "Vedo che hai scambiato la tua ironia fuori luogo con del puro dispetto? Charles, ricordati che siamo dalla stessa parte, non dimenticarlo.";
			link.l1 = "Argomento discutibile, Vostra Eccellenza. Per dirla in modo gentile. Da dove cominciamo, dalla nave o dalla dama?";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "L'affare con Stuyvesant, ovviamente – il suo emissario mi aspetta da stamattina e sto finendo le scuse. Mi servono i documenti del flauto, Charles.";
			link.l1 = "D'accordo. È tua. Non credo che de Chievous abbia giocato pulito, quindi puoi riprenderti la tua proprietà per metà prezzo. 150.000.";
			link.l1.go = "governor_18";
			link.l2 = "Sarei felice di accontentarti. Quanto hai detto che costava la nave? 500.000? Per me va benissimo, giusto?";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Ora, saranno quattrocentosessantamila pesos tasse incluse. Affare fatto. Centotrentacinquemila.";
			link.l1 = "Ascolta... Sto iniziando a stancarmi di discutere. Quindi paga, prendi i tuoi documenti e finiamola qui, giusto?";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "Non hai pietà nemmeno dei vecchi amici, vero Charles? Ora, con tutte le tasse incluse...";
			link.l1 = "I debiti di gioco e l'amicizia non vanno mai d’accordo, Vostra Eccellenza. Pagherete voi le tasse come acquirente, oppure vendo la nave a Le Francois. Sappiate che non sto ancora approfittando della vostra posizione... per ora.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "D'accordo, sia così. Ora, il duello. Non voglio rogne col conte de Levi Vantadur, quindi tutto deve svolgersi nella più assoluta legalità, chiaro? Mi hai sentito, Charles? Secondo la legge! Manderò due ufficiali della mia guarnigione a scortarti – sono entrambi nobili e uomini rispettati. Saranno loro i tuoi padrini al posto dei tuoi soliti... compari. Voglio che tutto sia limpido come il mare finché l'affare non sarà concluso!";
			link.l1 = "Che gentile da parte tua. Ma se il nostro caro amico decidesse di giocare sporco? Preferisco affidare le spalle a chi chiamo amici, e a chi sa come muoversi in certe situazioni, piuttosto che a chi è nato nella famiglia giusta.";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "Charles, smettila di comportarti come se questo duello fosse solo tra me e te. Questa è una faccenda seria. De Chievous non è un uomo che puoi uccidere e farla franca. Qualsiasi esito verrà seguito da indagini, forse persino da un tribunale. Avremo bisogno di testimoni fidati. Vedi? Mi prendo cura di te! Ma la cosa più importante è che non puoi ucciderlo.\nCapisco, Angerran è deciso e probabilmente è anche un buon combattente, ma Charles, non puoi ucciderlo! Feriscilo, umilialo pure, ma fermati lì. Se lo uccidi, ci saranno conseguenze che nessuno di noi potrà evitare o sopportare. Anche se il conte de Levi Vantadur non ha mai riconosciuto ufficialmente il suo bastardo, non ha altri figli. La sua furia non avrà fine.";
			link.l1 = "Meraviglioso, quindi dovrei farmi ammazzare piuttosto che lasciare che il conte furioso ti butti fuori dalla poltrona di governatore?";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "Temo che, se non ascolterai, non sopravviveremo ad Angerran de Chievous ancora a lungo. Tienilo a mente e sta’ attento. Il duello è fissato per stanotte alle dieci, oltre le porte della città. I miei ufficiali ti aspetteranno lì. Ora, l’ultima questione: Madame Julianne Botot – come sta?";
			link.l1 = "Vuoi sapere se ho già approfittato del mio premio? No, Eccellenza, non ancora o forse mai – poco importa. Ciò che conta davvero è che tu sia bandito per sempre dalla casa della marchesa. Lei è stata limpida come l’acqua su questo punto. Non posso biasimarla. Julianne sceglierà da sola il suo prossimo protettore.";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "Sei proprio bravo a sorprendere, Charles. Comunque sia, ho una noiosa riunione con l’agente della Compagnia a cui devo partecipare. Dovresti andare anche tu, prepararti, e ricorda quello che ti ho detto, giusto?";
			link.l1 = "Ci proverò senz'altro, Eccellenza. Ma è una rissa, quindi non posso promettere nulla. Grazie per l'aiuto, giusto?";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "Sei vivo, Charles! Che sollievo, come te la sei cavata? È sangue quello?! De Chievous ce l'ha fatta?";
			link.l1 = "Purtroppo sì. È ferito, ma niente di grave. Ha dovuto darsela a gambe, ma ci ha anche mandato contro i suoi scagnozzi. Insomma, un po' di questo sangue non è mio.";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "Bastardo! E i miei uomini? Sono vivi per testimoniare ciò che è successo?";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "Stanno bene, Eccellenza. Un po' malconci, ma se la caveranno.";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "Non tutti, Eccellenza. Un gentiluomo non ce l'ha fatta – de Chievous s’è portato dietro i moschettieri. Non ho potuto far nulla.";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "È stato un vero inferno laggiù, Eccellenza. Quei due valorosi gentiluomini sono caduti entrambi in battaglia. Se non fosse stato per loro, per me sarebbe finita male. De Chievous ha messo in piedi un’imboscata del diavolo, per tutti i santi.";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "Splendido! Raccoglierò le loro testimonianze scritte davanti a testimoni fidati. De Chievous la pagherà cara!";
			link.l1 = "Non credo proprio che riusciremo a scalfire anche solo di un poco il suo nome. Preferirei trovarlo io stessa e finire il lavoro, nonostante tutti i tuoi avvertimenti. Un codardo simile non merita di vivere.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "Orribile. Ma almeno otterremo una testimonianza scritta da un testimone. De Chievous la pagherà cara!";
			link.l1 = "Non credo che riusciremo a scalfire minimamente il suo nome. Preferirei trovarlo e finire il lavoro io stessa, nonostante tutti i tuoi avvertimenti. Un codardo simile non merita di vivere.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "Maledetto lui! Erano bravi uomini, Charles! Te lo giuro, quel bastardo pagherà!";
			link.l1 = "Non credo che riusciremmo nemmeno a scalfire il suo nome. Preferirei trovarlo io stessa e finire il lavoro, nonostante tutti i tuoi avvertimenti. Un codardo simile non merita di vivere.";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "Dimenticalo, Charles. Quel bastardo si è già rovinato da solo, credimi. Scommetto che adesso sta scappando, nascosto come una serpe in qualche colonia sfortunata. Non credo proprio che possa ancora farti del male. Questa vigliaccata era solo il morso di un serpente in fuga. Anche tu sembri ferito, hai bisogno di un medico?";
			link.l1 = "Grazie per la premura, Eccellenza, ma sto bene.";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "Bene a sapersi. Ora puoi respirare tranquillo, questa storia è finita. Rilassati e torna ai tuoi affari. A proposito... Non abbiamo ancora finito il discorso sui tuoi ultimi bottini. Hai deciso cosa farai con... quello, giusto?";
			link.l1 = "Non ti seguo bene, Jacques. Che intendi con 'It'? Parli della marchesa? Maledizione! Madame Botot! De Chievous è in fuga, non rappresenta più una minaccia per me, ma è disperato e potrebbe fare qualsiasi cosa! Devo andare! Manda le guardie a casa della marchesa! Subito!";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			if (pchar.questTemp.Sharlie == "escape")
			{
				dialog.text = "Un Capitano famoso, dici? Quello che ha respinto l’assalto degli spagnoli e quasi bruciato questa piccola città? Capisco. Cosa vuoi da bere?";
			}
			else
			{
				dialog.text = "Un capitano famoso, dici? Non ho mai sentito parlare di te... Che veleno preferisci?";
			}
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "Pinot Noir, come la nostra splendida padrona di casa? Sei sicuro di riuscire a sentirne il gusto dopo tutta questa salsedine? Di solito, gente del tuo stampo preferisce bere roba capace di sciogliere uno stivale vecchio.";
			link.l1 = "Se questa era una proposta per varcare insieme quei cancelli, allora ci sto. Nemmeno tu mi piaci, e sono lieta che il sentimento sia reciproco. Bando alle chiacchiere, tanto non sei portato. Ti lascio scegliere tu condizioni e armi.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "Un mazzo di terra e piscio di gatto? Che delizia! Questa roba acida non la fanno nemmeno invecchiare nelle botti, tanto non diventerà mai vino, giusto? Dimmi, è il sale del mare che le dà questo sapore tremendo?";
			link.l1 = "Se era un invito a passare i cancelli insieme, allora ci sto. Nemmeno tu mi piaci, e sono felice che il sentimento sia reciproco. Basta chiacchiere, non è il tuo forte. Ti lascio scegliere condizioni e armi.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "Ah, che ragazzo coraggioso! Ora calma i bollenti spiriti e tieni le distanze. Qui non siamo in taverna e io non sono una delle tue compagne di sbronza. Sei ben al di sotto della mia classe, non dovremmo nemmeno parlarci, ma la signora lo ha richiesto. Ora, Jacques ed io abbiamo ancora una faccenda in sospeso...";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "Julianne, tutto bene? Acqua, idioti! Portate dell’acqua!";
			link.l1 = "...";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "Hai proprio ragione, qui fa un caldo soffocante. È stata una partita davvero divertente finora, ma facciamo una piccola pausa prima del gran finale. Addio, addio Jacques – ricorda le regole del nostro torneo, giusto?\nEd ecco qui Charles de Maure, giusto? Un capitano con un gusto pessimo per il vino, ti ricordo bene. Non preoccuparti, dopo che avrò finito qui, berrai solo acqua. Quindi prenditi il tuo tempo, goditi il momento, bevi qualcosa. Quando sei pronto, raggiungimi in questa stanzetta. Finiremo la notte in un ambiente più confortevole...";
			link.l1 = "Non vedo l'ora, 'monsieur'.";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "Eccoti finalmente. Pronto a separarti dai tuoi soldi, giusto?";
			link.l1 = "Preferirei aggiungere la tua alle mie. Per favore!";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "Ben detto, ahimè il nostro caro governatore ha insistito per cambiare le regole proprio prima della sua vergognosa sconfitta. Ora siamo costretti ad aggiungere qualcos’altro oltre ai soldi in gioco. La posta dev’essere riconosciuta uguale da entrambe le parti. La mia è questo flauto d’argento.";
			link.l1 = "Andiamo, è noioso così – di questi ne potrei avere cinque in poche settimane di razzie, con l’oro che porto via. Dammi qualcosa di più grosso, giusto?";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Sì, ho visto la tua nave, devo ammettere che è davvero uno spettacolo da ammirare. Allora alziamo la posta – due navi contro una. La mia fregata e il flauto carichi d’argento contro la tua nave?";
				link.l1 = "Un degno duello! Madame Botot si sbagliava: QUESTO duello passerà alla leggenda. Affare fatto!";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "Guarda un po', il nostro capitano è proprio un furfantello! Però, la corsa è sacra. Che ne dici allora di una nave da guerra? Una fregata, quarantotto cannoni. Più veloce di molte corvette—nata nei cantieri reali, poi migliorata dalle mani migliori del mondo. I suoi cannoni hanno una gittata e una precisione eccellenti. Che ne pensi, giusto?";
					link.l1 = "Molto meglio, ci sto! Andiamo!";
				}
				else
				{
					dialog.text = "Ho sentito che hai gettato l’ancora qui, Capitano. Sii grato che abbia accettato la tua vecchia carretta come posta. Allora, vieni o ti tiri indietro?";
					link.l1 = "Va bene, hai ragione. Andiamo, giusto?";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "Gioco finito, Capitano, hai ottenuto ciò che volevi. Gongola pure, se ti va. Ti suggerisco di discutere i termini del riscatto della mia fregata domani a mezzogiorno.";
					link.l1 = "Tutto qui? Credimi, proprio come te, penso che quello che si perde al gioco non si possa ricomprare, solo riconquistare. Oppure potrei venderla come legna ai pescatori del posto e raccontare loro della tua generosa donazione.";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "Dunque la Fortuna ha detto la sua. Che storia curiosa! Complimenti, Capitano de Maure. Ti propongo di discutere domani a mezzogiorno le condizioni per riscattare la mia fregata.";
						link.l1 = "Così presto? Stiamo deludendo gli altri ospiti, monsieur. Se ben ricordo, ti resta ancora una nave. Sono sinceramente convinta, come te, che ciò che si perde in una scommessa non si possa riscattare, ma solo riconquistare.";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "Così la Fortuna ha detto la sua. Davvero curioso, questo. Complimenti, Capitano de Maure. Ti sei meritato un buon bicchiere, prova il Sangiovese. Immagino che Jacques ti pagherà bene per questa carretta, sembra ci sia affezionato più di quanto lo sia ad altre cose, e di molto. Dovrebbe bastare per un vino decente.";
						link.l1 = "Ti arrendi già? Così deludi gli altri ospiti, monsieur. Se ricordo bene, ti resta ancora una nave. Io punto la tua fregata contro il mio flauto con monete d’argento, visto che hai trovato la mia nave troppo modesta.";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "Sfortuna, Capitano. Tuttavia, apprezzo il tuo coraggio, e oggi sono di buon umore. Prenderò il tuo oro, ma la nave te la lascio. Sparisci dalla mia vista e, per carità, evita il gioco d’azzardo in futuro. Prima o poi ti porterà alla rovina.";
				link.l1 = "Molto nobile da parte tua, non me l’aspettavo. Addio, monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "Vi è una notevole differenza tra vantarsi e deridere il proprio avversario sconfitto, monsieur de Maure.";
			link.l1 = "Ti consideri già sconfitto? Ma era iniziato tutto così bene... ah! Signora Botot, credo che il tuo salone abbia appena guadagnato un'altra succosa storia sulle differenze tra il dire e il fare!";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "Cos’altro vuoi? Non ho altre navi nascoste nella cintura, né abbastanza monete per mantenerne anche solo una. Scommettere sui dobloni non è certo roba seria, dopo tutto quello che abbiamo visto stanotte, giusto?";
			link.l1 = "Sei forse meno ingegnoso del nostro caro Jacques Dille do Parkuet? Ti sto regalando la più splendida occasione per dimostrare che non tutto l’amore si compra. Neppure la Fortuna vende i suoi favori. La nave d’argento e la tua fregata contro ciò che per te vale più dell’oro.";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "Capitano, non c’è proprio nulla da ridere. Sbrighiamoci – l’alba è alle porte. Discuteremo il riscatto della mia fregata domani.";
			link.l1 = "Bene, eccoti qua – tre navi! Compresa una vera nave da guerra contro la più... beh, costosa signorina del Nuovo Mondo. Puoi davvero rifiutare una posta simile, giusto?";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "Sarebbe una follia. Eppure, è proprio una follia, monsieur de Maure. Ti prego. Ma ricorda, sei stato tu a proporlo.";
			link.l1 = "Questa sarà la leggenda che si racconteranno di nascosto per un anno intero! Ehi tu, porta altro vino e candele! La festa deve continuare, giusto?";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "Solo poco tempo fa pensavi che questo flauto non valesse nulla come posta contro le nostre navi. Cosa ti ha fatto cambiare idea?";
			link.l1 = "Mi sono annoiata. Dai, rendiamo il duello più interessante: la tua fregata e la mia nave contro...";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "Quel flauto che tanto disprezzavi? Hai la febbre per caso? Non mi sembri in gran forma.";
			link.l1 = "Sto benissimo, grazie. Non hai ascoltato, eh? Due contro uno non è proprio uno spettacolo, giusto? Allora pareggiamo i conti! Non tutte le ricchezze si misurano in oro, non sei d'accordo? O forse preferisci non sfidare il vento, se mai le cose non vanno secondo i tuoi piani e allora cambi rotta? Che peccato, allora. Mi sa che mi sbagliavo su di te. Madame Botot, credo che il tuo salone abbia appena guadagnato un'altra storia su chi parla e chi agisce...";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "Non cercare di farmi perdere la pazienza, monsieur de Maure, sei troppo ingenuo per riuscirci.";
			link.l1 = "In effetti. La mancanza di volontà non è un peccato... a meno che tu non sia un militare, naturalmente. O un nobile: l'onore della famiglia, come forse saprai, è un peso ben pesante talvolta. Dubito comunque che tu abbia mai dovuto affrontare simili dilemmi.";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "Vuoi sfidarmi a duello o continuare questo gioco, giusto?";
			link.l1 = "Andrebbero bene entrambe. Io intanto mi godo la cantina della Marchesa mentre tu ti rimetti in sesto.";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "Così sia. Questa notte merita un vero finale. Due grandi navi contro una vecchia carretta carica d’argento e la miglior donna della Nuova Francia! Respira a fondo, monsieur de Maure, questa sfida diventerà leggenda nei salotti dell’alta società.";
			link.l1 = "La tua sconfitta diventerà leggenda, davvero, monsieur de Chievous. Portaci ancora vino e candele! Facciamolo, giusto?";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "Hai perso la testa per la fortuna, monsieur de Maure. Qui rischi grosso, la benevolenza della sorte dura poco.";
			link.l1 = "Un piccolo favore apre la strada al vero amore. Ma lo stesso si può dire della lealtà comprata: porta solo al disprezzo o alla noia.";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "I tuoi tentativi di provocarmi mi divertono. Per questioni come favori, amore e tutto il resto che si può comprare o meno, chiedi alla signora Juliana. Ma sbrigati – domani lascia la città.";
			link.l1 = "Almeno la tua conoscenza dell’argomento è tutta da una parte. Non conquisterai il favore di Lady Fortuna né vincendo né pagando qui, quindi non potrai conoscere il suo amore. Ci vuole coraggio, monsieur, e una volontà ferrea per rischiare. Senza contare che anche le dame più... terrene apprezzano queste qualità. Metto in gioco due delle mie navi contro una delle tue, accetti la sfida?";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "Vuoi continuare con tutta questa foga? Va bene, come vuoi. Ma almeno aggiungiamo un po’ di pepe, monsieur de Maure. Dicevi qualcosa su amore e scommesse? Propongo di alzare la posta: il tuo barilotto e il flauto d’argento contro la mia fregata e la donna più straordinaria della Nuova Francia. Che ne dici adesso?";
			link.l1 = "Devo dire che sai proprio come giocartela con stile, monsieur! Ancora vino e candele! Andiamo, giusto?";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Incredibile, monsieur de Maure, è davvero incredibile!";
				link.l1 = "Già, davvero, l’Europa non aveva mai visto disfatta simile dai tempi della battaglia di Rocroi, monsieur de Chievous. L’artista che vive in me trema dal desiderio di immortalare un momento così storico. Peccato che non disegni più come un tempo, da giovane. Però magari madama Julianne ha già qualche artista di talento attorno, giusto?";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "Sfortuna, Capitano. Tuttavia, apprezzo il tuo coraggio, e oggi sono di buon umore. Prenderò il tuo oro, ma la tua nave puoi tenertela. Sparisci dalla mia vista, e cerca di star lontano dal gioco d’azzardo in futuro. Un giorno ti porterà dritto alla rovina.";
				link.l1 = "Molto nobile da parte tua, non me lo aspettavo. Addio, monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "No, non capisci. È talmente incredibile che non può essere vero!";
			link.l1 = "Tutti noi abbiamo visto le carte, monsieur de Chievous – la Fortuna non mente mai.";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "La fortuna no, ma tu sì, monsieur de Maure! Mi pare proprio che dietro la tua sfacciataggine ci fosse un piano bello e buono, non solo passione. Sei un bugiardo e un imbroglione — e sono pronta a dichiararlo davanti a tutti gli invitati.";
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "Monsieur de Chievous, ho capito bene? Sei pronto a sostenere le tue accuse non solo a parole? Pare che le tue offese stiano oltrepassando il limite e io, al contrario tuo, tengo all’onore della mia famiglia.";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "Secondogenito, un imbroglione e truffatore non oserà parlarmi d'onore di famiglia! Taci, Julianne, parlerò con te dopo! Charles de Maure, esigo soddisfazione immediata! Spada o pistola?";
			link.l1 = "Entrambe le cose. A dire il vero, sono felice che tu abbia cambiato idea. Ricordi che ti avevo proposto una passeggiata oltre le porte? Cosa avevi detto sulla mia umile condizione? Forse la partita a carte ti ha davvero dato un po' di coraggio, dopotutto?";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			sld.greeting = "Marquesa_vecherkonchen";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "Troppo onore, ma concordo con la marchesa. Ti finirò come si addice a un gentiluomo, de Maure, anche se non lo meriti. Ti sfido a duello domani a mezzogiorno, tramite Sua Eccellenza il governatore. Vieni di persona o manda i tuoi padrini a discutere i termini. A presto. Signora, i miei omaggi.";
			link.l1 = "...";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "Eccoti qua, il favorito della fortuna. Hai sistemato le tue faccende, giusto? Non ti sei scordato di confessarti? Dicono che l'inferno sia piuttosto scomodo senza.";
			link.l1 = "Parlare è facile, monsieur. Non sai nemmeno giocare a carte come si deve, adesso mettiamo alla prova la tua abilità con la spada... Balliamo!";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "Bella mossa... maledetto. Ma sono ancora viva, giusto?";
			link.l1 = "La tua ferita non sembra affatto buona, ma dovresti comunque farti vedere da un medico. Così non puoi andare avanti, finirai per crepare se insisti. Direi che abbiamo finito qui. Ho vinto io, e non ho barato. Ti restituirò la nave e tu lascerai St. Pierre. Non ci rivedremo mai più.";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "Che galanteria smisurata! Senti, monsieur de Maure, magari sei un talento naturale con la spada, ma alle carte hai sicuramente barato. Ho truccato il mazzo per ben tre volte. Tre volte, maledizione! Nessun miracolo potrebbe mai salvarti, eppure hai vinto lo stesso! Vorrei tanto sapere come ci sei riuscito... Bah, presto lo racconterai al Diavolo in persona. Ragazzi, addosso!";
			link.l1 = "Maledetto bastardo! Ti ho mostrato misericordia e così mi ripaghi?! Messeri, alle armi!";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "Lo ammetto, Monseniour de Maure, sono un po' sorpresa di vederti qui. Allora non mi sbagliavo su di te: quella ragazza selvaggia conta davvero qualcosa per te, eh?";
			link.l1 = "Mi chiedo come il tuo caro amico de Lyons la pensi sul rapire ufficiali dai rispettati capitani della nostra Marina. Magari dovremmo invitarlo qui e raccontargli tutta la faccenda, giusto?";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "Non ti servirà a niente, fidati. E poi, ho trattato la tua ragazza meglio di un generale prigioniero. Per ora. Ma tutto può cambiare, dipende solo da te, Charles.";
			link.l1 = "Non ricordo che ci sia stato un brindisi d’amore tra noi. Non farmi la parte di Charles, Monseniour de Chievous. Parla chiaro e dimmi che cosa vuoi da me?";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "Da te? Nulla, per carità! Tu ed io abbiamo solo risolto una brutta lite dopo una partita scandalosa a carte, ci siamo bevuti qualcosa e da questa stanza siamo usciti come vecchi amici, giusto?";
			link.l1 = "Angerran, sembri stare bene nonostante la ferita fresca, e ogni minuto passato a chiacchierare inutilmente mi fa venir voglia di sistemare la faccenda. Persino l’idea di macchiare questi bei tappeti di François de Lyons mi tenta sempre di più, giusto?";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "Ma il buon vecchio Francois adora questi tappeti, Charles. Tutti amano qualcosa. Se sei qui, allora devi amare la tua piccola ragazza d'armi. Sono disposto a restituirtela in cambio della mia proprietà. Hai rovinato il gioco e, sebbene di solito non perdoni simili mancanze, per te posso fare un'eccezione. Tu mi dai il premio che tanto desidero e io ti rendo il favore. Poi ci separeremo come si conviene. Ecco cos'è l'amore.";
			link.l1 = "Pensi che io tenga la marchesa come un dannato gioiello nella borsa? Sciocchezze! Come diavolo potrei mai consegnartela?!";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Non me ne importa proprio nulla, Charles. Hai due settimane per sistemare la faccenda. E sì, voglio che questo premio venga consegnato in gran segreto. Diciamo che un capitano che si è aggiudicato una cortigiana ridicolmente costosa, ma che non è riuscito comunque a conquistarne il favore, potrebbe fare qualche sciocchezza, no? Dimmi, sei già così disperato, Charles?";
			link.l1 = "Voglio vedere prima la mia ufficiale, per assicurarmi che sia ancora in vita.";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "Fuori discussione. Dovrai fidarti della mia parola. Lei resta in un luogo sicuro e vi rimarrà finché non avrò la mia ricompensa. Ma se insisti tanto a volerla vedere prima, sarò lieto di accontentarti inviandoti una sua parte. Che preferisci? Un orecchio, un naso, un paio di dita?";
			link.l1 = "Osi toccarla, feccia, e ti strangolo con le mie mani nude, lo giuro su Dio! Non mettermi alla prova, maledetto!";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "Calmati. Tutto quello che sta per succedere dipende solo da te. Non amo la violenza, la uso solo quando è necessario. Non costringermi a farlo. Consegnami il mio bottino a Capo Scott, a Dominica, entro due settimane e avrai ciò che ti spetta. Come ci riuscirai non mi interessa. Se vuoi rubare, ruba pure, sei un pirata dopotutto, anche se ben vestito.";
			link.l1 = "Sei fuori di testa, c’è una bella differenza tra un pirata e un dannato mercante di schiavi...";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "Respira a fondo, ora sfileremo con gran stile davanti al vecchio François. Siamo amici adesso, ricordi? Sorridi Charles, dai! Ora ognuno per la sua strada. Capo Scott, Dominica, tra due settimane. Non fare tardi.";
			link.l1 = "Ci vediamo lì, giusto?";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			PlaySound("VOICE\English\LE\Cortny\Cortny_01.wav");
			dialog.text = "Buona sera, madame Botot, capitano de Maure. Vi prego di mantenere la calma.";
			link.l1 = "Marchesa, dietro di me, subito! Monsignore, che diavolo significa tutto ciò?!";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "Ho una dozzina di uomini dietro la porta e poteri d’emergenza concessi dal tuo Stato. Le guardie non ti daranno alcun aiuto. Quindi, ti prego, riponi la spada, signore. Voglio solo parlare. Per ora.";
			link.l1 = "Monsignore, chi siete e come siete arrivato qui?! Dovreste spiegarmi, giusto?";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "Permettetemi di presentarmi: sir William Cortney, baronetto Cortney. Ora calmiamoci tutti e parliamo.";
			link.l1 = "Bene, Monseniour Cortney, siamo tutt’orecchi.";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "Perdonami se origlio, ma le circostanze attuali non mi lasciano altra scelta. Anche se qui a St. Pierre rimango nell’ombra, sto conducendo un’indagine di massima importanza per conto della Corona d’Inghilterra. Riguarda una nave corriera scomparsa in mare. Hai mai sentito parlare di una brigantina chiamata Regina?";
			link.l1 = "Non ho fatto nulla del genere e non capisco le vostre allusioni oscure, Monsignore. Sono un capitano onesto...";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "Non me ne frega un accidente delle tue losche faccende, signore. Ho fatto qualche indagine su di te e, a dire il vero, sei stato il mio primo sospetto quando ho saputo che eri passato per la Martinica subito dopo la sparizione della Regina. Però, non sei uno sprovveduto e i tuoi uomini qui non si sono messi a giocare con le perle. Quindi, per ora, sei fuori dai miei sospetti.";
			link.l1 = "Perle? Di quali perle vai cianciando, giusto?";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "Perle selezionate a mano, grandi come noci, direttamente dalle operazioni della Spagna nelle Indie Occidentali. E sono pure nere, capisci quanto sono rare? Ne avevi mai sentito parlare, giusto?";
			link.l1 = "Immagino di sì, ma ho sempre pensato che fosse una delle solite fandonie dei marinai. Proprio come le storie dell’Olandese Volante. Julianne, che succede?";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "Devo chiederle di presentarlo qui, signora. Si tratta di una questione della massima importanza. Nel frattempo, voi, signore, dovete raccontarmi tutto su capitano Moreno. Sospetto sia stato lui a darvi quella dritta. Sono molto curioso di sapere quale parte giochi in questa faccenda.";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "Moreno non è il suo vero nome, Monsignore Cortney. Il suo nome è Hernando Vasquez, conosciuto anche come il Don Sanguinario, un pirata spagnolo che un tempo era quartiermastro dell’Albatross, la nave del famigerato Bartolomeo il Portoghese.";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "Abbiamo scambiato solo poche parole. Non ho molto da raccontare. Sembrava proprio un vecchio lupo di mare.";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "Oh, oh. E posso sapere come lo sai, giusto?";
			link.l1 = "Conoscevo il suo capitano, sai? In realtà fui io a catturarlo e consegnarlo agli Olandesi. È una lunga storia... Peccato che allora non sia riuscita a prendere Vasquez in persona...";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "Anche tu sei un vecchio lupo di mare, signore. Non credo che ti sia sfuggito altro, eh?";
			link.l1 = "Solo un leggero accento, il modo in cui si muoveva e si comportava. Scommetto che è uno spagnolo, Monsignore Cortney.";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "Questo cambia davvero le carte in tavola, signore. Ed è una brutta faccenda. Signora, avete trovato la collana? Permettete che la esamini\nSì, in effetti, questa è una delle perle nere spagnole. Guardate un po’, questa fandonia da marinaio era proprio vera. Ora non resta che scoprire come quel de Chievous sia riuscito a mettere le mani su una di queste. A proposito, non è forse un bastardo del Duca de Levy Vantadur?";
			link.l1 = "È proprio lui, giusto? Per quanto ne sappiamo, aveva a che fare con il barone pirata locale a Le Francois. Forse quella perla l'ha comprata da lui?";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "Forse sarà così. Ma questa pista spagnola non mi convince affatto. In ogni caso, grazie per la collaborazione. Temo di dover tornare domani alla stessa ora. Vorrei anche la presenza del capitano de Maure. Forse avrò altre domande per voi. Ora dovrei andare a Le Francois.";
			link.l1 = "Monseniour Cortney, aspetta. Forse potrei unirmi a te? Jacques Barbazon non si è guadagnato il suo soprannome per essere dolce e affettuoso, e poi questa faccenda mi riguarda anch’io.";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "Capitano, mi commuove la vostra premura ma la risposta è no. Si tratta di affari di Stato. Quel furfante conosce il suo posto e non oserebbe mai mettere le mani sull'emissario della Corona, altrimenti il suo misero villaggio sparirebbe! Mi scuso ancora per l'intrusione, madama. Buona serata.";
			link.l1 = "Ci vediamo domani sera, Baronetto.";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Non arrabbiarti con lei, Capitano. So essere molto convincente. La tua storia è notevole, davvero. Credo che potresti essermi utile.";
			link.l1 = "Sembri soddisfatta, com’è andata a Le Francois?";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "Come immaginavo, quel tuo barone era docile come un agnellino. Mi ha detto tutto quello che volevo sapere. Te l’ho detto, so essere davvero molto persuasiva, giusto?";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "Oggi sono venuta qui da sola, non ci sono uomini miei dietro quella porta. Che diavolo?!";
			link.l1 = "Ho un brutto presentimento. Julianne, mettiti dietro di me, subito! Barone, gli emissari della Corona sanno combattere bene quanto sanno parlare?";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Sai davvero come maneggiare una spada, Capitano! Eh, a dirla tutta, non è stata una passeggiata. Ma chi diavolo erano quei tipi?!";
			link.l1 = "Dovremmo chiedere ai loro amici – sento altri passi. Vorrei tanto che fossero le guardie...";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "Incredibile! Pensi che quel bastardo abbia avuto il coraggio di fare tutto questo?! La pagherà, lo giuro!";
			link.l1 = "Respira. Barbazon si svicolerà da ogni accusa come un furetto. Ti racconterà che è stato solo un ordinario saccheggio di ladruncoli in una casa benestante. Inoltre, è un maledetto pirata, che gliene importa delle autorità! Tuttavia, ora sono certa che sei riuscito a scoprire qualcosa di davvero utile. Ti chiedo di condividere questa conoscenza con me.";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "Non posso proprio dire di no, giusto? Se no magari la prossima volta va a segno, eh? Va bene, facciamo finta che non ho sentito quella minaccia nel tono. Diciamo che ti sto restituendo un favore. Jacques il Gentile non ha venduto perle al tuo nobile bastardo. Le stava comprando, tutto qui.";
			link.l1 = "Quindi è stato de Chievous a intercettare la Regina? È proprio una canaglia, ma mi riesce difficile credere che si abbasserebbe a fare il semplice pirata.";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "Non si può certo chiamare la Regina una preda qualunque per un pirata, Capitano. Si suppone che avesse almeno una mezza dozzina di perle nere. E anche solo una perla nera vale più dell’oro. Devo assolutamente incontrare quel sir de Chievous, a qualsiasi costo.";
			link.l1 = "Posso darti una mano qui, Monsignore. Ma prima mettiamo una cosa in chiaro. Non mi sono mai interessata davvero alla collana della signora Botot, quindi i tuoi affari qui non riguardano le perle. Cos'altro trasportava la Regina a bordo?";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "Molto bene, suppongo che dovrò spiegarti di più, viste le... circostanze. Vedi, il carico non conta poi così tanto rispetto alla nave stessa. Il brigantino corriere Regina era stato assegnato al porto di San Jose, Trinidad. Il suo capitano raccoglieva informazioni e svolgeva qualche... lavoretto per noi.\nL’ultimo incarico che gli avevamo affidato era di trasportare il bottino che i nostri avevano strappato agli spagnoli dalle loro operazioni sulle perle. Ci sono voluti tre anni di sforzi per arrivare a quella pista. Le perle nere hanno il loro valore, certo, ma perdere la Regina è una vera sciagura. Non è stato un incidente: chi sapeva delle perle doveva sapere anche del resto.";
			link.l1 = "Splendido, quindi si tratta davvero di faccende di spionaggio! Hai paura che tutta la rete di spie che hai messo su sia in pericolo? Ora capisco davvero quanti guai hai, giusto?";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = "Hai mai sentito parlare di John Thurloe? È il capo dei servizi segreti della Corona. Un giorno sarò a Londra, a riferire di persona a lui sul destino della Regina. Devo capire dove c’è la falla e... occuparmi di chi la provoca. E poi c’è anche quel misterioso capitano Moreno, il tuo. Se gli spagnoli hanno rintracciato la nostra rete di spie nelle colonie, anni e anni di duro lavoro andranno in fumo!";
			link.l1 = "Sai, tutto questo inizia ad avere un senso se guardi la cosa da lontano. Sto iniziando a pensare che qualcuno con un accento spagnolo abbia parlato a de Chievous della Regina e delle perle nere, giusto?";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "La pensiamo allo stesso modo. Non c'è modo migliore di sfruttare una rete di spie scoperta. Un incidente diplomatico con un uomo di tale rango coinvolto... Una faccenda così può davvero rovinare i rapporti tra Inghilterra e Francia, basta fornire le dritte giuste e poi attendere che scoppi uno scandalo internazionale. Forse anche quella soffiata sulle perle nere ci è stata passata apposta.";
			link.l1 = "Quei dannati castigliani, giusto? Allora, che facciamo con de Chievous?";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "A dir la verità, non ne ho la minima idea. Se si tratta di una provocazione spagnola, allora sarebbe saggio semplicemente ignorarla. Ma devo scoprire come abbia saputo della Regina e quanto ciò possa compromettere la nostra rete nelle colonie spagnole. Ti devo anche la vita, e intendo sdebitarmi.";
			link.l1 = "Onestà per onestà, Baronet. Accetterei volentieri qualsiasi aiuto tu possa offrire. Ormai sono così disperata che sto persino pensando di rapire la marchesa.";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "Capisci che così de Chievous cancella le sue tracce? Sarebbe un gioco da ragazzi scaricare tutta quella faccenda su di te, inclusa la sparizione della Regina. Quindi, ti propongo questo: il marchese Botot mi ha detto che de Chievous non sarà presente allo scambio e resterà al sicuro a Basse-Terre. O ha capito in che guaio si è cacciato, oppure inizia a sospettare qualcosa. Starà attento come un topo in cambusa. Ecco perché verrò a Dominica insieme a te.";
			link.l1 = "Ma la prigioniera è la mia priorità, non posso rischiare la sua vita! È un ostaggio in attesa di uno scambio!";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "Non preoccuparti – costringerò Jacques Dille de Parkuet a firmare un mandato d’arresto per la nave di de Chievous. Dubito che i suoi uomini si rendano davvero conto in che guaio si sono cacciati, altrimenti sarebbero stati più cauti con quelle perle. Noi andremo da loro con una lancia e gli presenteremo il mandato di persona.";
			link.l1 = "Sì, ricordo il tuo dono di persuasione, Monsignore, ma è un rischio. E bello grosso.";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "Hai ragione, ma dovrai accettarlo se vuoi il mio aiuto. Quando avremo finito a Dominica, andrò a Basse-Terre e pretenderò che il governatore de Lyon ti consegni il tuo avversario. I miei poteri me lo permettono. Non possiamo lasciare che de Chievous sgattaioli via.";
			link.l1 = "Sei davvero pronto per questo, Monseniore? Potrebbe scatenare una guerra, giusto?";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "Scommetto che non lo permetteranno mai. È fuori discussione, ormai la verità la sappiamo entrambi. La politica è una lurida sgualdrina, Capitano. Ti prometto che presenterò de Chievous alle segrete inglesi, solo per te. Suona come una soluzione che persino suo padre considererebbe un prezzo ragionevole.";
			link.l1 = "Non posso dire che il tuo piano mi piaccia, ma non vedo alternative.";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "Ti assicuro che ce la faremo. Ora devo andare dal governatore e impartire ordini ai miei uomini. Se vedi la marchesa, dille che può tenere la perla come segno di gratitudine per il suo aiuto nelle indagini.";
			link.l1 = "Grazie, Baronetto. Ci vediamo sulla mia nave, salperemo presto.";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "William Cortney, Barone Cortney, al vostro servizio. In nome dell’Impero Britannico e con il pieno appoggio della fedele alleata Francia, la vostra nave è ufficialmente sotto sequestro. Ecco i documenti, fate attenzione a leggerli e ordinare ai vostri uomini di tenere le mani lontane dalle armi. Siete trattenuti, ma non ancora arrestati. Se non fate sciocchezze, sarete rilasciati al primo porto utile.";
			link.l1 = "Baronetto, devo recuperare il mio... il mio ufficiale!";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Non ti preoccupare, Capitano, la accompagnerò io alla tua nave. Ti chiedo solo di tornare ora alla scialuppa. Prenderò il comando di questa nave e salperò per Basse-Terre. Sentiti libero di andar via se non hai intenzione di prenderti gioco del tuo acerrimo nemico di persona. Ti chiedo solo di lasciarmi alcuni dei tuoi uomini per aiutarci ad arrivare a Guadalupa.";
			link.l1 = "Molto bene, Monseniore. Preferirei di no. Mandagli i miei peggiori saluti. Addio e ancora grazie, giusto?";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Charles, sono felice di vederti. Speravo che saresti tornato, ma non ci credevo davvero.";
			link.l1 = "Anche a te, Barone. Sei venuto a far visita alla Marchesa? E dov'è finita, per inciso?";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = "Ancora non capisci, vero? È fuggita. Inoltre, Angerran de Chievous ti manda le sue più sentite scuse. Sono riuscita a convincerlo che tu non facevi mai parte di questo gioco, solo un'altra vittima come lui. Il buon uomo non si è preso la briga di scrivere, ma è davvero addolorato per come sono andate le cose.";
			link.l1 = "Profondamente dispiaciuto, eh?! Ma di che stai parlando, Monsignore?";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "Tu ed io ci siamo persi la cosa più importante. Come ha fatto a sapere delle perle? Chi ha invitato quel capitano spagnolo proprio in questa casa? Chi avrebbe potuto spingere quella canaglia a inseguire un simile bottino?";
			link.l1 = "Sei seria? Non può essere...";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "Certamente può farlo. La Marchesa ha recitato la sua parte alla perfezione, quasi riusciva a portare tutto a termine. Tuttavia, grazie a una nostra indagine, mi sono avvicinata a de Chievous non come a un ladro o a un pirata, ma come a una vittima dell’inganno, che in effetti è. Ha capito in fretta in che guaio lo aveva cacciato lei, ma non aveva prove e ha deciso di agire da solo. Sai già cosa è successo dopo.";
			link.l1 = "Vuoi dire che tutto quello era stato organizzato dalla Marchesa? De Chievous ci è cascato come un bambino sprovveduto!";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "Esattamente. La passione è una cosa assai pericolosa, Charles! Ricordi quella notte in cui hai giocato d’azzardo proprio in questa casa? Angerran voleva strappare le prove necessarie alla marchesa ottenendo il suo patrocinio. Sì, ha barato, ma era disperato dopo anni di passione senza speranza, finiti col più devastante dei tradimenti! Ma tu sei intervenuto, ti sei proclamato suo campione e hai avuto successo. De Chievous pensava che tu e lei foste della stessa pasta. Ha rubato una nave che aveva perso contro di te solo per impedirti di mettere le mani sui suoi registri di bordo. Ha usato il tuo ufficiale per tentare di mettervi l’uno contro l’altra – voi, che per lui eravate nemici mortali.";
			link.l1 = "Non ho davvero parole!";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "Ora sai com’è, Charles! La Marchesa è furba, bellissima da togliere il fiato e altrettanto pericolosa. Non so per quanto tempo abbia manipolato i migliori della Nuova Francia. Anni, direi. In ogni caso, ormai non ti riguarda più. È stato un piacere rivederti, ma io ho ancora stanze da mettere a soqquadro, questa casa è un labirinto. Probabilmente non troveremo nulla, ma almeno dobbiamo provarci.\nUn’ultima cosa prima che ognuno vada per la sua strada. Tieni, prendi questo. Un ricordo da portare con te. Magari lo regalerai alla tua dama quando sarà il momento. Sei molto fortunato, lo sai? Soprattutto rispetto a de Chievous, poveraccio!";
			link.l1 = "Hai ragione, lo sono. Addio e che il vento ti sia favorevole nelle tue ricerche, Barone!";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Che bella giornata, eh Capitano? Ho sentito parlare delle tue imprese, ma mai avrei pensato che fossi un pirata qualunque. Che sfacciataggine – presentarti a St. Jones dopo quello che hai fatto!";
			link.l1 = "Sarò pure una piratessa, questo è certo, signore, ma ti sembro forse una sprovveduta? Per quale diavolo di motivo dovrei presentarmi qui dopo aver depredato il Mercury e portato via le perle spagnole?";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "Lo ammetto, è proprio per questo che stai ancora qui a chiacchierare invece di penzolare da una forca. Vedi, c’è un piccolo dettaglio che abbiamo tenuto nascosto in tutta questa faccenda. E non parlo della perla che abbiamo trovato addosso a te. Parlo del nome della brigantina.";
			link.l1 = "Cosa intendi?";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Una brigantina da corriere, la Regina era registrata al porto di San Jose negli ultimi due anni. Il suo capitano raccoglieva informazioni per noi e svolgeva anche... commissioni di ogni sorta. Ufficialmente la stiamo cercando con il pretesto della posta diplomatica smarrita che trasportava. Non è certo una copertura geniale, lo ammetto. Tuttavia, non potresti mai scoprire il vero nome della nave senza rovistare per bene nella cabina del suo capitano.";
			link.l1 = "Ero cieca, ma ora vedo. Ti prego, ascoltami, signore, lasciami spiegare!";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "Be', datti più da fare, capitano. La tua vita è appesa a un filo, giusto?";
			link.l1 = "Non c'entro nulla con questa storia di spie! Neppure gli spagnoli. La tua rete è al sicuro, non preoccuparti. Però, c'è stata una falla e qualcuno se n'è approfittato. E poi, sono finita a litigare proprio con quel qualcuno. Ho trovato delle prove del suo coinvolgimento nell'affare Mercury e volevo usarle per metterlo all'angolo.";
			link.l1.go = "Cortny_48_1";
		break;
		
		case "Cortny_48_1":
			dialog.text = "";
			link.l1 = "Dio mi sia testimone, ho preso questa faccenda per un semplice atto di pirateria, mai avrei pensato che i servizi segreti della Corona ci fossero coinvolti! Tutto ciò che ho è questa perla, ma so benissimo quando e dove puoi trovarne altre.";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "Hai mai sentito parlare di John Thurloe? È il capo delle spie della Corona. Un giorno sarò a Londra, a riferirgli di persona sul destino del Mercury. Dunque, dimmi il nome di quel tuo miserabile avversario.";
			link.l1 = "Angerran de Chievous, bastardo del Conte de Levy Vantadur. Immagino che per lui la Mercury fosse soltanto un vascello per trasportare bottino di filibustieri. Forse sapeva delle perle, ma non aveva la minima idea del legame con l’intelligence britannica.";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "Non deludi mai, Capitano, te lo concedo! Che compagnia e che avversari ti scegli! Molto bene. Oltre alla perla, che altre prove hai?";
			link.l1 = "De Chievous ha una fregata. Era mia, per una sola notte... eppure sono riuscita a scoprire qualcosa. È un uomo terribilmente pignolo, saprai tutto riguardo al suo attacco al Mercury dal suo diario di bordo. Sono piuttosto certa che abbia ancora una parte del bottino. Forse anche altre perle nere, se ce n’erano più di una.";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "Più di una, puoi scommetterci. Non rischieremmo mai la Regina per una manciata di perle comuni. Spero tu capisca che devo assolutamente parlare con Monseniour de Chievous. Delle perle non me ne importa un accidente, ma devo scoprire qualcosa in più sulla fuga di notizie. I miei superiori mi manderanno a fondo se non porto loro un quadro completo.";
			link.l1 = "Sarei lieta di organizzarti un incontro, ma dobbiamo sbrigarci! Proprio in questo momento la fregata di de Chievous sta navigando verso Guadalupa, dove il suo padrone si nasconde sotto la protezione del governatore locale. Sono certa che sa bene cosa ha fatto e scapperà dal Nuovo Mondo il prima possibile.";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "Queste sono accuse gravissime contro persone di grande rilievo, Capitano. Ti rendi conto di che... tempesta di guai potrebbe scatenarsi dopo? Un attacco di briganti a una nave che batte bandiera di un alleato? Questo può davvero complicare i rapporti tra due grandi nazioni. Mi riesce difficile immaginare quanto ti abbia fatto arrabbiare per spingerti a rischiare così tanto.";
			link.l1 = "Mi ha portato via qualcosa, milord. Qualcosa che vale più della mia stessa vita. Devo sistemare questa faccenda. Se porterà alla guerra, allora servirò il mio paese sotto la sua bandiera. Comunque sia, de Chievous avrà ciò che si merita, e la colpa sarà solo sua!";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "Ti hanno mai detto che sei un uomo da cui stare in guardia, Capitano? Saresti capace di scatenare una guerra su mezzo mondo pur di raggiungere il tuo scopo? Molto bene, facciamo come vuoi tu. Verrò a Basse-Terre con te. Non posso lasciarmi sfuggire una pista simile. Manderò uno scrivano a registrare le tue prove mentre io preparo la mia nave.";
			link.l1 = "Grazie, signore. Ma non abbiamo tempo da perdere qui, ti avverto!";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "Capitano de Maure, ci arriveremo in tempo, non ho dubbi su di te. Tuttavia, se questa avventura dovesse andare male... capisci cosa intendo? Non posso prometterti nemmeno una tomba degna, sai.";
			link.l1 = "Sì, mio signore. Ti comprendo perfettamente.";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "I dadi sono tratti, Capitano. Ho richiesto un incontro con Angerran de Chievous. La sua fregata verrà perquisita non appena metterà piede in porto. François de Lyon ha delle riserve, ma i sigilli sui miei documenti lo trattengono, per ora. Ti prego di restare in città finché la faccenda non sarà risolta.";
			link.l1 = "Certo, mio signore, ho capito.";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "Allora spero che capirai anche questo. Consegnate la spada a quei gentiluomini laggiù e seguiteli, così sarò certa che manterrai la tua parola.";
			link.l1 = "Incredibile... milord Cortney, fai sul serio?!";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "Serissima. Sei ancora uno dei miei principali sospetti e lasciarti andare in queste circostanze sarebbe un'enorme sciocchezza da parte mia. Ti chiederò scusa come riterrò opportuno, se e quando le tue parole si riveleranno vere.";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "Saluti, monsieur de Maure. Andiamo, giusto?";
			link.l1 = "Con piacere, quali sono le regole? A dire il vero, ero troppo presa dal cibo e forse mi sono persa i dettagli, giusto?";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "Le regole sono semplici. Diecimila pesos per una carta, giochiamo finché uno di noi non si arrende. Niente ricevute né cambiali accettate.";
			link.l1 = "Per me va bene. Facciamolo, colonnello.";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Maledizione! Mai più! Va bene, monsieur de Maure, buona fortuna per il prossimo giro.";
				link.l1 = "È stato un piacere, Colonnello. Addio.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Hai combattuto bene, ma la Signora Fortuna aveva altri piani. Addio, monsieur de Maure. Grazie per la partita.";
					link.l1 = "Sì, credo di aver puntato troppo in alto stavolta. Addio, Colonnello.";
				}
				else
				{
					dialog.text = "Hai deciso di rinunciare al gioco e così hai ammesso la sconfitta! Hai combattuto valorosamente, ma la sorte ha scelto diversamente. Addio, monsieur de Maure, grazie per la partita.";
					link.l1 = "Già, credo di essermi sopravvalutata in questa faccenda. Addio, Colonnello.";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Capitano Charles de Maure, che diavolo di sorpresa!";
					link.l1 = "Capitano. Moreno, un accidente! Che ci fai qui?!";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "Capitano Charles de Maure, è un piacere.";
						link.l1 = "Ci siamo già incontrati prima, monsieur... Moreno?";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "Capitano Charles de Maure, è un piacere.";
						link.l1 = "Ci siamo già incontrati prima, signor... Moreno?";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Capitano Charles de Maure, è un piacere.";
				link.l1 = "Ci siamo già incontrati prima, monsieur... Moreno?";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "È una lunga storia. La solita, capitano. Vedo nei tuoi occhi che hai delle domande. Basta che resti zitto e fai finta di prendere in giro un semplice marinaio.";
			link.l1 = "Eh, questo abito elegante ti sta proprio bene, amico mio semplice. Direi che sai proprio come portarlo, giusto?";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "Solo in rare occasioni, per fortuna. Oggi è il giorno. Giochiamo d'azzardo, Capitano. La gente ci osserva, non è educato farli aspettare.";
			link.l1 = "D'accordo, ne parliamo dopo. Affare fatto... capitano Moreno, se vuoi.";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "Ti conosco un po', ma poco importa. Dai, distribuisci le carte, Capitano de Maure, la gente vuole vedere uno spettacolo.";
			link.l1 = "Curioso. Soprattutto il tuo accento spagnolo, insieme alle lodi della signora Botot. Molto bene. Mare contro mare, vediamo chi la spunta!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "Ti ho riconosciuto, giusto? Tu e il mio ex capitano avete trafitto i miei ragazzi a Le Francois. Quel bastardo ha avuto ciò che si meritava, ma solo grazie al tuo aiuto, se ben ricordo. Però non aspettarti la mia riconoscenza: tu hai ucciso Franz Garke e per questo non ti perdonerò mai.";
			link.l1 = "Il nostromo dei portoghesi? Il Maledetto Don, giusto? Questa notte diventa sempre più interessante. Facciamolo!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "Hai deciso di tirarti indietro dal gioco e così ammetti la sconfitta! Immagino che Lady Fortuna abbia detto la sua. Addio, Capitano.";
				link.l1 = "Anche a te, monsieur Moreno. Grazie per la partita.";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Immagino che Lady Fortuna abbia detto la sua. Addio, Capitano, forse ci rincontreremo.";
					link.l1 = "Anche per me, monsieur Moreno. Grazie per la partita.";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "Mi sa che la Signora Fortuna ci ha messo lo zampino. Addio, Capitano, magari ci rivedremo in altre circostanze, eh eh.";
						link.l1 = "Non vedo l’ora, monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "Ecco fatto. Il destino ha parlato, Capitano. Addio.";
						link.l1 = "Addio, monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Ecco fatto. La sorte ha deciso, Capitano. Addio.";
				link.l1 = "Addio, monsieur Moreno.";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "Che piacere vederti, Monseniour capitano de Maure! A dire il vero, mi aspettavo di tutto, anche una scorta armata al completo, ma non te, giusto?";
			link.l1 = "Monseniour Moreno, hai dei problemi con gli ufficiali locali? Comunque, è bello vederti anche io, ahah!";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "Devo dire, non si può proprio rifiutare l’invito di una delle nostre belle ostesse. Almeno, non *quel* tipo di invito. Su Charles, smettila con questa commedia. La Marchesa ha fatto in modo che io sappia che lei conosce la mia vera identità.";
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "Signora, siete davvero incantevole! Questo nuovo amico vostro ha già tentato di consegnarmi una volta. A dire il vero, non è andata proprio bene, anzi, mi ha salvato la pelle talmente tante volte che ho perso il conto. Insomma, ora gli devo un favore, quindi niente minacce: state serena.";
			link.l1 = "Ti ringrazio, Bartholomew. Angerran de Chievous mi ha messa alle strette in una situazione davvero scomoda e devo assolutamente farlo cadere. La vita di... qualcuno a me molto caro dipende da questo. Fidati, stavolta nulla mi fermerà.";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "Basta così, Capitano, siamo amici, giusto? Ti ricordi quella corsa attraverso metà dell’Arcipelago? Una cosa del genere per me conta davvero molto. Farò tutto il possibile per darti una mano. Hai mai sentito parlare della Mercury?";
			link.l1 = "Allora, cos'è quello? Una nave?";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "Una brigantina inglese, per essere precisi. Il suo compito era trasportare il bottino dei corsari del colonnello D'Oyley, che avevano saccheggiato le operazioni di perle spagnole sulla Costa dell'Ovest. Quelle dove, di tanto in tanto, si pesca una perla nera leggendaria, ne hai mai sentito parlare? Se la mia fonte è affidabile, sulla Mercury erano state nascoste parecchie di quelle perle. Un mese fa ho teso un'imboscata tra Martinica e Guadalupa, aspettando quei bei galantuomini. Ma fu tutto inutile! Siamo rimasti in mare una settimana finché non abbiamo dovuto ammettere la sconfitta.";
			link.l1 = "Giusto, quindi la tua fonte non era affidabile dopotutto e non hai ottenuto alcun premio per te. Ma che c’entra de Chievous con tutta questa storia, giusto?";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "Anch’io pensavo lo stesso, finché non ho scoperto che la Mercury non è mai arrivata ad Antigua. Immagina la mia sorpresa quando l’hanno vista vicino a Curaçao, e non c’era modo che mi sfuggisse passando da Martinica. Gli inglesi sono furibondi! Perdere un bottino del genere, figurati! Comunque, mi sono incuriosita e ho iniziato a indagare, su chi fosse quel furfante che ha rovinato la festa a tutti. Un simile tesoro non si piazza da un giorno all’altro, così sono andata a Le François a cercare quel bastardo e a riscuotere ciò che mi spettava, giusto?";
			link.l1 = "La tua storia mi suona familiare. Hai mai sentito parlare di 'Karma'? Certo che sai proprio come attirarti dei guai addosso. Ma non vedo ancora come tutto ciò possa tornare utile a me, giusto?";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "Non avere fretta, Capitano, sto per raccontarti la parte migliore della mia storia. Quel tuo amico ben vestito ma poco pulito – i suoi uomini hanno lasciato una bella scia di perle preziose nelle botteghe locali. Un vero branco di spagnoli che smanacciava perle come se piovesse.";
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "Hai sentito, capitano?";
			link.l1 = "Pensi che de Chievous abbia comprato perle rubate da Jacques il Gentile e la sua banda? Temo che questo... non sia abbastanza.";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "Proprio così, capitano. Non stava comprando, stava vendendo! Ho parlato con Barbazon di questa storia e lui mi ha confermato che aveva comprato un bel carico di perle perfette da un suo compare. Poi le ha mandate in Europa. Abbiamo anche quella perla nera nella collana e il fatto che la nave di de Chievous sia stata riparata. Gli operai mi hanno raccontato che la sua fregata aveva buchi fatti da palle da dodici libbre. Chi, in nome del cielo, avrebbe mai l’ardire d’attaccare una fregata con simili giocattoli?";
			link.l1 = "Sembra proprio il nostro brigantino! E poi, ricordo che de Chievous si vantava sempre della velocità della sua fregata. Ma perché tutta questa follia? Siamo in pace con l’Inghilterra, perché rischiare così tanto, e per cosa? Le perle nere sono rare, giusto, ma non impossibili da trovare.";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "E lì ha proprio sbagliato! Gli inglesi hanno già avviato un’indagine ufficiale sulla sparizione della Mercury, anche se la chiamano una corvetta scomparsa con dei documenti importanti a bordo. Chiunque porti indizi riceverà una bella ricompensa, chiunque sia coinvolto verrà punito severamente. La parte migliore è che hanno mandato un ufficiale nobile ad Antigua che ora scava senza sosta nel caso. Non ricordo il suo nome, pomposo quanto la sua faccia da pavone, ma per fortuna non sta dando la caccia a me!";
			link.l1 = "Questa sì che è una novità! Pare che ci tengano davvero a quelle perle nere. Mi chiedo quante ne avessero sulla Mercury e come tutte queste informazioni possano tornarmi utili, giusto?";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "Come, anche a te ha fatto girare le scatole, marchesa? Maledetto farabutto dagli occhi vispi! Sono con te anche su questo, Capitano de Maure! Nessuno osa rubare il bottino a Bartolomeo il Portoghese!";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "Mi serve proprio da bere dopo tutto questo parlare. Marchesa, ora che siamo amiche, giusto?";
			link.l1 = "Non credo che abbiano del rum in questa casa, Bartholomew.";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "Sì, certo, basta mettere la sua fregata sotto il naso di quell’investigatore inglese! Se questo è il nostro piano, allora non riconosco più il nostro vecchio e caro capitano de Maure, giusto?";
			link.l1 = "Ti farà ridere, ma questo è proprio il piano. Avrò bisogno dell'aiuto di entrambi. Signora – lei sarà la prigioniera del pirata che ho assoldato – Bartholomew, tu sarai quello.";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "E anche di questa mia canagliata! Bartolomeo il Portoghese non ha mai rapito una donna!";
			link.l1 = "E lui non lo farà, ma sembrerà così agli uomini di de Chievous. Inoltre, non serve che tu dica il tuo nome. Prendi la nostra dama a bordo e incontra la fregata di Angerran vicino a Capo Scott Head. Scambia Julianna per il mio ufficiale e torna a Martinica. Poi aspetta la marchesa e me.";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "Tutto questo è stato davvero affascinante e tu sei un vero cavaliere, Charles. Ma come diavolo dovremmo riportarla indietro dopo lo scambio, giusto?";
			link.l1 = "Ci penso io. Non abbiamo molto tempo, quindi dividiamoci. Tu e la marchesa andate a Dominica, mentre io mi precipito a St. Jones. Troverò il colonnello D'Oyley o quel investigatore inglese e gli dirò chi è responsabile della sparizione della Mercury.";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "Hai riflettuto almeno un po’ sulla tempesta di guai che inevitabilmente scoppierà dopo un simile incidente, Capitano? In questo momento, Antigua è un vero nido di vespe e tu mi chiedi di scagliarci una pietra contro. Ricordo guerre scoppiate per molto meno!";
			link.l1 = "Un problema alla volta... La riporterò indietro a qualsiasi costo! Che sia quel de Levy Vantadur a sistemare tutto il casino da solo, se davvero è così potente come dicono! E poi, de Chievous dovrà sudare per spiegare come Madame Botot sia finita sulla sua nave.";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Pronta? Affidiamoci al destino! Marchesa, sei pronta a farti rapire?";
			}
			else
			{
				dialog.text = "Pronta? Conta pure su una preghiera! Marchesa, quanto ci metterai a prepararti, giusto?";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+", monsieur de Maure. Il mio nome è "+GetFullName(npchar)+", e questo è "+GetFullName(characterFromId("GG_SecundantGG_2"))+". Sua Eccellenza ci ha chiesto di assistere al vostro duello con monsieur de Chievous.";
			link.l1 = "Buonasera, signori. Spero che tutto fili liscio e che nessuno ci lasci la pelle stanotte. Ma siate pronti a ogni evenienza. Questo 'gentiluomo' può rivelarsi una bella delusione.";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "La tua inquietudine è infondata. Secondo i termini stabiliti per questo duello, in nessun caso i secondi possono intervenire. Ma grazie comunque per averci avvertiti. Il tuo avversario è arrivato. Che il vento ti sia favorevole, Capitano. Sua Eccellenza mi ha chiesto di dirti che pregherà per la tua... prudenza.";
			link.l1 = "Sono sicura che mi sarà davvero utile. Comunque, cominciamo.";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "Capo, abbiamo un problema. La nostra nave è... beh, finita, giusto?";
			link.l1 = "Aspetta, cosa?! Come, chi? Una squadra intera doveva sorvegliarla, quindi diavolo stai dicendo?!";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "No, Capo, non la nave. La nostra è splendente. Parlo della fregata che hai vinto ieri, quindi ora è pure nostra, giusto? Ci abbiamo mandato solo una dozzina di uomini come equipaggio di preda. Ha detto che basterebbe.";
			link.l1 = "Per l’amor del cielo, fermati e raccontami esattamente cosa è successo dall’inizio, giusto?";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nessuna idea, Capitano. La fregata è salpata tra le nebbie del mattino. La vedetta si è accorta della sua mancanza qualche ora dopo, quando la foschia era ormai svanita.";
			link.l1 = "Non può essere! Lei non mi farebbe mai una cosa simile! Anche se... maledizione, abbiamo litigato poco tempo fa. Forse potrebbe...";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Si teme che sia persino peggio, Capitano. Stamane i pescatori hanno trovato due dei nostri ragazzi della squadra di preda. Entrambi morti, con la gola tagliata.";
			link.l1 = "Maledetto incubo! De Chievous! Ha rubato la sua nave mentre io ero occupata con la marchesa! Spero che sia ancora viva... Se le succede qualcosa, anche solo un capello, io...";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "Dai l'ordine ai ragazzi di prepararsi, Capo? Possiamo salpare tra due ore, tutti sono stati sulle spine per tutta la mattina, soprattutto il tuo secondo, abbiamo dovuto tenerlo a bada per non fargli inseguire quelli, giusto?";
			link.l1 = "È troppo presto per questo. Devo... rifletterci bene, e parlarne con qualcuno. Sì! Preparate la nave! Voglio che tutti siano pronti, salperemo appena torno.";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "Capitano de Maure, che succede? Qualcuno ha assalito la signora?";
			link.l1 = "Non avresti dovuto venire qui. Ebbene, che Dio mi sia testimone, non era questo che volevo.";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "Monsignore, stavamo quasi perdendo la speranza di vedervi qui. Vedo la marchesa Botot sulla vostra scialuppa. Non voglio nemmeno chiedere come ci sia finita. La vostra compagna vi aspetta, è sana e salva: prendetela e filatevela da qui al più presto.";
			link.l1 = "Se le hai messo anche solo un dito addosso, ti faccio a pezzi la tua vecchia carretta!";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "Che premura inaspettata. Non temere, è stata trattata come una regina prigioniera. Le tue minacce non mi impressionano. Ah, a proposito, il Cavaliere de Chievous ti manda i suoi saluti.";
			link.l1 = "Al diavolo lui e i suoi saluti. Dov’è il mio... ufficiale? Iniziamo lo scambio.";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "Monsignore, stavamo quasi perdendo la speranza di vedervi qui. La vostra compagna vi sta aspettando. Sta bene... ma chi diavolo è questa? Dov'è la marchesa?";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "La spada, signore. E niente scherzi, i miei ragazzi sono un po' nervosi ultimamente. Non vuoi beccarti una pallottola, giusto?";
			link.l1 = "Serio? Va bene, prendilo pure, ma trattalo con cura: vale più delle tue baracche. Esigo un incontro con il baronetto Cortney, vostra Eccellenza!";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "Non preoccuparti, sono sicura che troverà un momento per venirti a trovare, giusto?";
			link.l1 = "Quando cerchi di aiutare qualcuno...";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "Neanch’io gradisco questa faccenda, Monseniore. Ahimè, questo insolente inglese ha tale autorità che neppure Monseniore de Lyon può fare molto. Mi scuso, Capitano, consegni pure la sua spada.";
			link.l1 = "Spero proprio che monsieur de Chievous non finirà nella mia stessa cella. Andiamo, signori, sono sfinita. Finalmente un po' di sonno.";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "Non vorrei sembrare scortese, monsieur, ma non ho tempo di parlare adesso, vedi cosa sta succedendo. Non voglio perdermi nulla!";
			link.l1 = "Come desideri, signore.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "Questa serata passerà alla storia, lo sento! Se ne parlerà da qui fino a Versailles! La mia Marianne sarà entusiasta e vorrà sapere ogni dettaglio. Per favore, monsieur, si sposti, mi sta oscurando la vista.";
			link.l1 = "Me ne vado già, monsieur, goditi lo spettacolo e saluta l’indimenticabile Marianne... chiunque sia, giusto?";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "Ahah! Dunque, ecco monsieur de Maure! Scusami... capitano Charles de Maure! Vieni, accomodati, qui abbiamo una magnifica selezione di vini dal caro Vecchio Mondo. Con cosa vuoi iniziare la serata: una novità – Cabernet Sauvignon dalle rive della nostra amata Gironda, oppure l'intramontabile classico – Sangiovese italiano?";
			link.l1 = "Grazie, signore, berrò con te, ma più tardi.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "Oh, capitano de Maure! Vuoi ancora un po’ di vino... hic? Guarda che ci hanno appena servito – Syrah del 1643, appena arrivato dalle colline del Rodano del nord. Questa è, maledizione, una vera perla! E quell’annata è stata eccellente in tutto, credimi... solo la sconfitta degli spagnoli a Capo Gat valeva la pena! A proposito... perché tutti si agitano così, lo sai? Qualcuno si sente male? Beh – che importa, alla salute...";
			link.l1 = "Beh, almeno qualcuno rende omaggio alle delizie. Au revoir, Monsieur.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "Oh, capitano Charles de Maure, ho sentito parlare di te, come tutti in questa città! Lascia che mi presenti - "+GetFullName(npchar)+", incontrarti è un vero onore, credimi! Hai davvero buoni rapporti con il nostro governatore? Puoi presentarci? Vorrei mostrargli tutto il mio rispetto e...";
			link.l1 = "Forse più tardi. Passa una buona serata, monsieur.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "Monsieur de Maure, hai visto questo?! Il nostro stimato governatore e monsieur de Chievous in persona – credevo si sarebbero sbranati a vicenda sul posto! Magnifico! La marchesa Botot oggi si è superata – tutto così maledettamente emozionante! Non vedo l’ora di scoprire come andrà avanti. Tra l’altro, magari questo è il momento giusto? Avevi promesso di presentarmeli... ";
			link.l1 = "Non ricordo di aver promesso nulla. Mi dispiace, ma devo andare.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "Monsieur de Maure, sei finalmente arrivato al salotto della brillante madame Botot! Si vocifera già da un po’ che desiderasse vederti. Hai già dato un’occhiata ai suoi ‘allievi’? Eh, stelle come la marchesa non sono roba per comuni mortali come noi. Ma credimi: queste dame sono veri capolavori. Forse meno sbalorditive, ma sempre – come Michelangelo e, che so, Tiziano.";
			link.l1 = "Un paragone interessante, monsieur. Bene, ti lascio goderti la notte....";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "No, qui è sempre divertente, ma adesso l’aria profuma proprio di uno scandalo di lusso, lo senti anche tu? Lady Jacqueline mi aspetta di sopra, ma non riesco proprio a staccarmi dai tavoli da gioco! Sua Signoria e monsieur de Chievous sono avversari degni e incredibilmente determinati. Sembra che oggi le scommesse non voleranno solo alle stelle, ma spaccheranno il firmamento fino all’inferno, giusto?";
			link.l1 = "I diavoli sono sotto di noi, monsieur. Dev’esserci angeli dietro il firmamento del cielo.";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "Beh, almeno un incontro piacevole! Ci siamo già visti, capitano de Maure, ma dubito che te lo ricordi."+GetFullName(npchar)+" - Ero il capitano della sesta compagnia di fanteria della guarnigione, ho combattuto al tuo fianco contro gli spagnoli sulle nostre strade. È vero, mi sono beccato una palla nel ginocchio e ho passato quasi tutta la battaglia a osservare questo stesso bordello che andava a fuoco, mentre me ne stavo sdraiato in un fosso. E ora eccomi qui – di nuovo civile, e di nuovo lo ammiro, ma stavolta da dentro.";
			link.l1 = "Piacere di conoscerti, monsieur. Quel giorno faceva davvero un caldo infernale, ma devo ammettere che da allora questo posto è diventato molto più bello!";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "E allora, che ne pensi dell’atmosfera qui, capitano? Pare che questi sciocchi vecchiacci abbiano deciso di scatenare un vero inferno! Mi domando, la sedia del governatore si può mettere in palio come una posta a carte? Ricorda le mie parole – finirà tutto a colpi d’acciaio. Peccato, con il mio ginocchio certe baldorie non fanno più per me. Però, mi pare d’aver visto Jacqueline – il suo gentiluomo è proprio preso da tutta questa faccenda... Beh, credo che andrò a tentare la sorte, giusto che qui è ancora tutto tranquillo.";
			link.l1 = "Buona decisione, ti auguro ogni successo, monsieur. E ora devo tornare dai... babbei.";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
