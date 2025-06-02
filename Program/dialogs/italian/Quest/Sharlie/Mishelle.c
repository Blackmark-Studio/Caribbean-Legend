// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
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
		case "First time":
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "Benvenuto, Charles il Viaggiatore! Ho sentito tutto sulle tue prodezze contro quei cani di pirati sulla costa orientale della Martinica. Ora sono certo che non mi sbagliavo su di te, fratello.";
				link.l1 = "Figli di puttana mi hanno teso una trappola. Ma ci hanno sottovalutati. Il mio navigatore, l’equipaggio ed io ne siamo usciti vincitori. Devo però ammettere, caro fratello, che all’inizio... la faccenda sembrava proprio nera.";
				link.l1.go = "trial";//промежуточная стадия
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				bool bFMQM = CheckAttribute(pchar,"questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
				bool bFMQN = CheckAttribute(pchar,"questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
				bool bFMQT = CheckAttribute(pchar,"questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
				bool bFMQP = CheckAttribute(pchar,"questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
				bool bFMQG = CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
				bool bFMQL = CheckAttribute(pchar,"questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
				if(bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
				{
					if (sti(pchar.rank) < 12)
					{
						dialog.text = "Salute, fratello! Apprezzo il tuo sincero ardore nel volermi tirar fuori di qui, ma per il prossimo passo non sei ancora pronto. Il mio piano richiede un capitano navigato. Continua a solcare i mari dei Caraibi, guadagna premi e fatti le ossa! Quando sarai all’altezza, riprenderemo il discorso.";
						link.l1 = "Ebbene, come vuoi tu, fratello. Qui dentro ci stai tu, non io.";
						link.l1.go = "exit";
					} 
					else 
					{
						dialog.text = "Felice di vederti, fratello. Non dimenticare gli impegni presi con gli altri. Appena hai le mani libere, ti aspetto – ho in mente il prossimo colpo per noi!";
						link.l1 = "Capito, fratello. Mi prendo il tempo per i miei impegni, ma tornerò presto!";
						link.l1.go = "exit";
					}
					break;
				}
				if (sti(pchar.rank) < 12)
				{
					Log_info("Level 12 is required");
					dialog.text = "Carlo il Navigatore! Ho sentito delle tue imprese! Sei quasi pronto per la prossima tappa del mio piano. Torna da me appena avrai fatto un po' più di strada.";
					if (sti(pchar.rank) < 7)
					{
						dialog.text = "Saluti, fratello! Apprezzo il tuo ardore sincero nel volermi tirar fuori di qui, ma ancora non sei pronto per il passo successivo. Il mio piano richiede un capitano d’esperienza. Continua a esplorare i Caraibi, fatti onore e impara! Quando sarai pronto, andremo avanti.";
					} 
					else 
					{
						if (sti(pchar.rank) < 10)
						{
							dialog.text = "Bene rivederti, fratello! Ho sentito che ti stai dando da fare! Ma non sei ancora pronto per la prossima mossa del mio piano. Continua a fare quello che fai e torna da me quando sarai pronto.";
						}
					}
					link.l1 = "E va bene, come vuoi tu, fratello. Sei tu a marcire qui dentro, non io.";
					link.l1.go = "exit";
					if(sti(pchar.rank) > 8)
					{
						link.l2 = "Non direi proprio, fratello. Forse tu ti sei già rassegnato a questa cella, ma io non ho alcuna voglia di marcire qui a lungo – nostro padre non aspetterà in eterno. Sputa il rospo.";
						link.l2.go = "gambitA";
					}
					break;
				}
				else
				{
					dialog.text = "Buon pomeriggio, Charles. Vederti mi riempie il cuore di gioia: stai proprio cambiando in meglio.";
					link.l1 = "Ah sì?   E come mai sei così sicuro, eh?";
					link.l1.go = "gambit";//переход на Гамбит
					break;
				}
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//признак, что Гамбит пройден или провален
			{
				dialog.text = "Capisco. Vedo che hai notizie per me, Charles! Allora, cosa mi racconti? Spero non sia nulla di funesto?";
				link.l1 = "Ho seguito il consiglio che mi desti l’ultima volta...";
				link.l1.go = "saga";//переход на Сагу
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//признак, что Гамбит провален по всем трем вариантам
			{
				dialog.text = "Finalmente sei arrivato... Quali notizie porti, caro fratello?";
				link.l1 = "Ho seguito il consiglio che mi desti l’ultima volta...";
				link.l1.go = "gambit_fale";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//Сага готова к старту
			{
				dialog.text = "Felice di vederti, Charles! Hai incontrato il Chevalier de Poincy? Com’è andato il vostro colloquio?";
				link.l1 = "Sì, caro fratello. Ci siamo già incontrati. Ho due notizie per te, una buona e una cattiva. Comincio da quella buona: ho saldato il tuo debito con de Poincy. Quella cattiva è che non ti lascerà libero finché non avrò mantenuto la tua promessa di sistemare certe faccende con qualche eretico...";
				link.l1.go = "saga_5";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью
			{
				dialog.text = "Come te la sei cavata a La Vega, fratello?";
				link.l1 = "Niente di cui vantarsi, davvero. Tyrex è un tipo pittoresco, ma il suo modo di fare affari non fa proprio per me.";
				link.l1.go = "saga_17e";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
			{
				dialog.text = "Come te la sei cavata a La Vega, fratello? Ho sentito certe voci e, per dirla tutta, non mi sento affatto tranquillo... Charlie Prince.";
				link.l1 = "Penso di aver capito di quali dicerie si trattasse. Ma ormai è acqua passata. Non collaboro più con Tyrex, quel lavoro si è fatto troppo sudicio persino per me.";
				link.l1.go = "saga_17f";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
			{
				dialog.text = "Ebbene, saluti... Corsaro Principe Charlie. Dimmi, Charles, come hai fatto a cadere così in basso? Non ci posso credere. Mio fratello, che faceva una smorfia schifata quando una volta ho accennato al saccheggio di un galeone mercantile spagnolo, ora è uno dei pirati più ricercati e temuti di queste acque! Persino io, immerso nella merda fino al collo, divento paonazzo ogni volta che sento parlare delle tue imprese famigerate. Ho maledetto il giorno in cui ti ho mandato a La Vega. Che vergogna! Un nobile francese che si mette con i filibustieri, e in così poco tempo diventa il peggiore fra tutti! E ora, fratello? Cerchi forse un impiego come barone dei pirati?";
				link.l1 = "No. Ho chiuso per sempre con la pirateria.";
				link.l1.go = "saga_17g";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			
			dialog.text = "Cos'altro, Charles? Credo che abbiamo discusso tutto. Il tempo è denaro, caro fratello – muoviti, su!";
			link.l1 = "Sì, sì, sto andando...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "Mishelle_prisoner":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Maltie_officer"));
			QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
			SetCurrentTime(13, 30);
			dialog.text = "Charles!.. Che piacere vederti, fratello! Capisco bene che ti sarà difficile crederci, ma sono dannatamente felice che tu sia qui...";
			link.l1 = "Ah! Guardalo lì! È tutto contento! Mentre tu te ne stavi sul tuo piedistallo a parlare d’‘Ordine’, Charles era la vergogna della famiglia, un pittorello da strapazzo, mantenuto dalle cortigiane e ‘cavaliere’ solo nei salotti, eh? Ma adesso che i tuoi stessi compari ti hanno sbattuto in cella, sei ‘felice come una Pasqua’ di rivedere quel buono a nulla di tuo fratello!";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "Charles, tu...";
			link.l1 = "Non ho ancora finito! Perché non hai mandato nemmeno una notizia di te in Francia?! Ti hanno forse tolto il diritto alla corrispondenza?! Nostro padre si è ammalato di crepacuore per la tua assenza! E mi ha pregato di scoprire almeno qualcosa sul tuo destino!..";
			link.l1.go = "Mishelle_prisoner_1a";
		break;
		
		case "Mishelle_prisoner_1a":
			dialog.text = "Charles, con quali parole potrei raccontare a nostro padre ciò che mi è accaduto? Cosa dovrei scrivergli? No, fratello, per quanto sia difficile, è meglio che nostro padre non sappia ancora nulla. E scriverti sarebbe inutile – tu cambi sempre indirizzo a Parigi... Come hai fatto a trovarmi?..";
			link.l1 = "Su richiesta di nostro padre sono andato a Malta. Lì ho raccolto qualche notizia dal tuo amico, il cavaliere de La Brignais. Mi scrisse delle tue disgrazie, dicendo che probabilmente ti trovavi da qualche parte in Martinica. Poi sono tornato in Francia e ho fatto visita a nostro padre. E dopo tutto questo sono finito in questo maledetto buco, sotto un sole che ti arrostisce vivo e dove le zanzare ti divorano senza pietà...";
			link.l1.go = "Mishelle_prisoner_1b";
		break;
		
		case "Mishelle_prisoner_1b":
			dialog.text = "Hai raccontato tutto questo a nostro padre?";
			link.l1 = "No. E il cavaliere de La Brignais non ha mai risposto alle sue lettere, temendo brutte conseguenze... Nostro padre ancora ignora del tutto la tua sorte. Ho deciso di venire a cercarti e scoprire la verità. Ma sappi, sono arrivato in Martinica non per te, ma per il nostro povero padre!";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "Davvero? Charles, da quando ti importa della tua famiglia? Diciamolo chiaro, fratello, tutta Parigi sa chi è tuo padre. Porterai pure il nome dei de Maure, ma non vuoi che il nome dei de Monper venga infangato.\nPerché, se succedesse, non potresti più vantarti in giro raccontando frottole sulle tue imprese eroiche, vero? Le porte delle migliori case di Parigi ti sarebbero sbattute in faccia e al Louvre non ti lascerebbero nemmeno avvicinarti di un miglio.\nDavvero credi che le tue cortigiane e amanti, i cui mariti rendi cornuti mentre combattono per la patria, sarebbero felici di spassarsela con il fratello di un criminale di stato come me?\nScommetto che sei arrivato qui dritto dal letto di qualche donna sposata, indovino? Charles, che ti prende? Ti ho punto sul vivo?";
			link.l1 = "Tu... Tu!..";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "Va bene, fratello. Ci siamo già scambiati abbastanza frecciatine. Ammetto di non essere perfetto. Ma nemmeno tu sei un santo. Charles, questo non è il momento di litigare. Abbiamo entrambi lo stesso scopo: salvare l’onore e la dignità della famiglia Monper... qualunque siano le nostre ragioni. Fratello, per una volta nella vita, mettiamo da parte le ostilità e scegliamo la pace. Intesa?";
			link.l1 = "Mettiamolo alla prova... Ma mi spieghi di cosa ti accusano, per l’amor del cielo?";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "Ufficialmente si parla di spese della Compagnia. In verità, la faccenda è assai più profonda.";
			link.l1 = "Ah, quindi ti sei intascato il denaro della tua compagnia? Eh bravo, proprio così...";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "Ti ho già detto che queste sono le accuse ufficiali. Non ho toccato nemmeno un louis d'or. Ti spiego com'è andata... vedi, non posso raccontarti tutto nei dettagli finché sto dietro le sbarre. Non ho il diritto morale di svelare i segreti della nostra Società.";
			link.l1 = "Per favore, cerca di spiegarti, caro fratello. Ho il diritto di sapere, non credi?";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = "Va bene. Avevo ricevuto del denaro per una faccenda maledettamente rischiosa e delicata, che avrebbe dovuto ribaltare il gioco politico nei Caraibi. Agivo su ordini diretti di Philippe de Poincy, il general-governatore delle colonie francesi. Ma l’operazione è andata a rotoli, nonostante tutti i miei sforzi.\nDe Poincy si è infuriato come un diavolo, vedendo tutti i suoi piani svanire in fumo. Ha firmato di suo pugno il mio ordine d’arresto e si è premurato che fossi ben chiuso in cella. Poi è venuto qui di persona e ha dichiarato che mi avrebbe accusato di peculato e tradimento contro l’Ordine, se io o i miei parenti non avessimo restituito il denaro speso per l’operazione.";
			link.l1 = "Ecco un bel pasticcio. Dov’è, dunque, questo denaro che, a quanto pare, la nostra famiglia deve sborsare per i tuoi pasticci, eh?";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "Se n’è andato tutto per preparare l’impresa. Mazzette, organizzare le spedizioni, comprare ogni sorta di mercanzia e attrezzi. Ho avuto spese non da poco. Te l’ho già detto: non mi sono intascato nemmeno uno scudo.";
			link.l1 = "E qual è la somma che viene richiesta?";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "Un milione.";
			link.l1 = "Merde!   Stai scherzando, vero?!";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "Sembro forse uno disposto a scherzare? No, caro fratello, questa è la cruda verità. Dovremo consegnare a de Poincy un milione di pesos.";
			link.l1 = "Ma dannazione! La nostra famiglia non ha mai visto tanta grana! Non riusciremmo a mettere insieme una simile somma nemmeno in vent’anni!";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "Se non fossi dietro le sbarre e incatenato ai doveri verso la Società, ce la farei in sei mesi, forse un anno, al massimo un anno e mezzo. Charles, questo è il Nuovo Mondo. Qui tutto va al rovescio. Un uomo sveglio e ambizioso può farsi una fortuna senza consumarsi l’intera vita, come succede in Europa.";
			link.l1 = "Un milione in sei mesi?! Sei impazzito? Se ne sei così sicuro, perché non lo vai a raccontare al tuo de Poincy? Lascia che ti liberi lui. Fatti valere...";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "Oh, non dire sciocchezze, Charles! Poincy non mi lascerà mai uscire da questa cella. Se fosse stato così facile, non ti avrei chiesto aiuto.";
			link.l1 = "Allora tocca a me trovare il denaro per la tua libertà?!";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "Non solo la mia libertà. O hai già dimenticato? Torniamo forse a parlare dei palazzi, dei balli e di quelle porche nobildonne? Sì, Charles, tocca proprio a te. Sempre che tu voglia continuare quella tua vita da damerino a Parigi, come niente fosse. Ti piacerebbe, vero, fratello?";
			link.l1 = "Ma dannazione, dove accidenti dovrei trovarli?! Conosci forse dei vecchi boschi da queste parti dove crescono luigi d’oro al posto delle foglie?";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "Tutto il Nuovo Mondo è come un bosco di alberi carichi d’oro, ma la gente è troppo pigra per alzare il голову e allungare la mano verso i rami. Non temere, Charles, te la caverai alla grande. Ti conosco da quando eravamo marmocchi, e mai avrei perso tempo a convincere nostro padre a spedirti quaggiù se ti avessi creduto uno stupido o un buono a nulla. \nPer quanto tu abbia i tuoi difetti, come già ti dissi, hai coraggio, ambizione, cervello; la lingua sciolta e la mano ferma sulla spada – dote, questa, che qui può far la differenza tra la vita e la morte...";
			link.l1 = "Grazie infinite. Mio caro fratello si è davvero degnato di lodarmi? E io che pensavo d’essere solo un triste pittore, un damerino di corte...";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "Smettila con le fandonie. Abbiamo un accordo, sì o no?";
			link.l1 = "Perdona, fratello. Mi è scappato. Non sono abituato a sentirti parlare così. È come se una sgualdrina di strada si mettesse a predicare sulla salvezza dell'anima.";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "Andiamo avanti, fratello. Come ti ho detto, hai tutto quel che serve per sfondare qui. E non sei solo: ti guiderò con consigli su cosa fare e come farlo per bene. Dammi retta e andrà tutto a gonfie vele. Fidati, nessuno potrà darti la mia esperienza. Sei pronto a smetterla coi discorsi inutili e arrivare al sodo?";
			link.l1 = "Sembra proprio che mi tocchi restare qui per un po'... Va bene. Ti ascolto, Michel.";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "Sì, fratello, ti toccherà restare qui per un bel pezzo. Meglio che tu lo capisca fin d’ora. Se qualche cortigiana ti aspetta a Parigi, ti consiglio di scordartela. Ma non crucciarti: le ragazze di queste parti hanno fascino da vendere. \nPerò, amano i veri uomini, forti, decisi, persino un po’ rozzi. Se vuoi portarti a letto una donzella della colonia, lascia perdere la poesia, i discorsi sui dipinti o le passeggiate al chiaro di luna. Non è roba che apprezzino.";
			link.l1 = "D'accordo, fratello. Ti ha colpito una folata di ciarle vane? Andiamo al sodo. Sono disposto ad ascoltare i tuoi consigli, ma risparmiami le tue insinuazioni velenose.";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "Splendido. Per avere un briciolo di fortuna, devi possedere una nave. I Caraibi sono un arcipelago, lo sai, vero? Qui la vita è intrecciata col mare. Un uomo con la sua nave ha un orizzonte infinito di possibilità e bottino.";
			link.l1 = "Ma io non sono mica un marinaio!";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "Allora, è tempo di diventarlo. Tanto altra via non hai. Non vorrai же fare lo scribacchino in porto o marcire nella guarnigione, vero? No? Allora, sarai capitano.";
			link.l1 = "Che svolta nella mia carriera! E dove mai troverò una nave per me?";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "C'è una splendida lugger che ti aspetta al nostro cantiere navale. Non è grande, ma è una barca assai comoda, perfetta per muovere i primi passi nell’arte marinaresca. Questa lugger l’hanno costruita apposta per me. Ho già lasciato un acconto di cinquemila pesos per la nave – con un aiutino dai miei amici. Va’ dal costruttore e digli che ti manda Michel de Monper. Capirà subito per cosa sei venuto.";
			link.l1 = "La nave costa solo cinquemila? Strano, davvero...";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "Fratello, mi stai ascoltando? Cinquemila sono solo per l’acconto. Il prezzo dello schooner si aggira sui ventimila pesos. Dovrai guadagnare il resto da solo. E poi ti serviranno denari pure per ingaggiare un equipaggio e un pilota.";
			link.l1 = "Magnifico!   E come dovrei procurarmelo?";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "Nessuna gran sorpresa, così vanno le cose. Guadagnatelo. Come altrimenti? Qui il denaro spunta dietro ogni cespuglio, basta saper dove cercare e non aver paura delle sventure. Fatti un giro per le taverne e i postacci di queste parti. Scambia due chiacchiere con la gente del posto. Un lavoretto salterà fuori di sicuro. Ma fa’ attenzione, i truffatori qui sono più dei galantuomini. E se proprio non ti senti uomo d'onore, puoi sempre tentare la fortuna svaligiando qualche casa.";
			link.l1 = "Ma siamo nobili, giusto?";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "I titoli qui non valgono un accidente. Lavora, combatti, ruba come tutti gli altri. Quando ti sarai comprato una nave, assolda un equipaggio. All’inizio non saprai nemmeno come condurre la barca, quindi ti servirà un nocchiere. Di tutto questo puoi parlare col padrone della taverna, saprà darti una mano. E cerca di non perderti per la strada, mi raccomando. Quando molli gli ormeggi, punta la prua dritto su Guadalupe...";
			link.l1 = "Cos'è quello? Una città?";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "È un’isola che si trova quasi a due giorni di navigazione da qui. Procurati al più presto una mappa dell’arcipelago e imparala a memoria come il ‘Padre Nostro’, così non passerai per un babbeo davanti a chiunque sappia distinguere una città da un’isola. Dovrai veleggiare parecchio in queste acque, quindi preparati per tempo.";
			link.l1 = "Hm. Bene. E dunque, che diavolo dovrei fare su questa... ehm... Guadalupa?";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "Trova un uomo laggiù di nome 'Fadey'. Ha una casa tutta sua non lontano dal molo. Digli che ti mando io e chiedigli di saldare il debito: mi deve una bella sommetta, persa a carte. I soldi che otterrai ti serviranno per rimetterti in sesto. Usali per avviare le tue faccende.";
			link.l1 = "Che vuoi dire con 'dare il via alle danze'?";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "Voglio dire di usare questi soldi per farne ancora di più, capisci? Tipo, facendo un po’ di commercio qua e là. Ma di questo parleremo più tardi. Ora pensa alla nave, salpa verso la Guadalupa, trova quel grasso moscovita e fatti ridare il debito.\nNon parlo sul serio, ovviamente: Fadey è uomo assai rispettato laggiù, amico persino del governatore locale. Non ha senso fare casino. Anzi, cerca di fartelo amico. Torna da me appena metti insieme la somma. Hai capito, fratello?";
			link.l1 = "Capito. Oh, perché... Che ho fatto per meritarmi questa dannata sventura...";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "Non crucciarti, Charles. Prendila come una disgrazia inevitabile, oppure... come una fortuna. Un giorno, ringrazierai il destino per averti fatto cambiare rotta così. Ecco la tua occasione, fratello, per dimostrare d’essere uomo vero. Magari diventerai persino una brava persona...";
			link.l1 = " (INIZIO TUTORIAL) Ancora questa menata?";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = "(SALTA IL TUTORIAL) Fratello, non ho tempo da perdere con queste sciocchezze. Voglio saltare subito la parte noiosa e prendere il largo senza indugio. Prima avrò una nave, prima ti tirerò fuori da questa fogna. O forse preferiresti marcire qui ancora un po'?";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "No, no. Non fraintendermi... Va bene Charles, non perdere tempo. Sai cosa devi fare. Ti aspetterò quando tornerai da Guadalupa come capitano della tua nave, coi soldi di Fadey. In bocca al lupo, fratello. Conto su di te.";
			link.l1 = "Cercherò di non deluderti. Va bene, Michel. Fino alla prossima volta!";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//флаг на старт мини-квестов для сбора денег
			//LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);// таверна закр
			if(!bHardcoreGame) LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true);// ЦЕРКОВЬ закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);// ростовщик закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);// тюрьма закр
			bDisableFastReload = false;//open быстрый переход
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			//Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
				QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
			}
			QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
			/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
			pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
			pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
			pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
			/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
			pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
			pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
			pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
			pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
			//устанавливаем прерывание на джунгли
			pchar.quest.Jungle_jew.win_condition.l1 = "location";
			pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";
			
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "Ehi! Questa 'seccatura' potrebbe un giorno salvarti la pelle... Ma insomma. C’è un modo semplice per raccattare quei soldi subito.\nVai alla chiesa del posto e cerca l’Abate Benoit. È vecchio amico di nostro padre. Spiegagli la situazione, gettati in ginocchio e supplica che ti presti abbastanza monete per comprarti una nave.";
			link.l1 = "(SALTA IL TUTORIAL) Molto meglio così! Ora filiamo dritti dall’abate.";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "(INIZIA IL TUTORIAL) Vuoi che cominci col farti ancora più debiti, eh? Mi prendi forse per uno stupido, fratello? Vedo benissimo che qui non puoi aiutarmi in nulla. Allora tutto ricade sulle mie spalle.";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "Accidenti! Pare proprio che non mi fossi sbagliato su di te, fratello. Non vedo l’ora di vederti tornare da Guadalupa da vero capitano, con i soldi di Fadey in tasca. Che il vento ti sia favorevole!";
			link.l1 = "Ci si vede. Divertiti in questa topaia.";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
			pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			Sharlie_removeLocks("");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Vuoi dirmi che ti sei spaventato? Su, rilassati, fratello. Va tutto bene, credimi. Alla mia prima battaglia in mare non mi sono certo sentito un eroe. Sciocchezze. Tra un mese o due, queste scaramucce ti sembreranno pane quotidiano... Sei già stato da Fadey?";
			link.l1 = "Ci ho provato... Ma con un successo simile... Perché mi sono pure scomodato?";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Hm. Perché mai?";
			link.l1 = "Perché è nei guai fino al collo. È stato derubato di recente e ora ha i suoi di problemi coi soldi. Mi ha offerto un pugnale dalla sua collezione al posto del denaro. Diceva che vale molto più di tutto il debito. Così, l’ho preso io...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Fadey? Nei guai? Senza un soldo? Ah-ah-ah! Mi hai fatto ridere, caro fratello! Quel dannato moscovita ti ha letto come un libro aperto, ha visto subito che eri un pivello e... oh, quel furfante! Fammi vedere il pugnale che il vecchio ti ha mollato in cambio del suo debito.";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "Ecco a te...";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "Non ce l'ho addosso. A vederlo sembra solo un pugnale qualsiasi. Fadey mi ha detto che è stregato da uno sciamano indiano e si chiama l'Artiglio del Capo.";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "Hm. Vediamo un po'... Che il Signore giudichi quell’orsacchiotto grassoccio. Robaccia del genere, Charles, la trovi in ogni mercatino del porto. Ti ha fregato ben bene, approfittando della tua inesperienza... Tieni, riprenditi ‘sto pezzo di ferro. Conservalo come ricordo. Puoi pure appenderlo sopra la branda nella tua cabina.";
			link.l1 = "Figlio di puttana! Bah, chi se ne frega... Tornerò a trovarlo a Guadalupa e darò una scrollata a quel rognoso bruciato di sole!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "Incantato da uno stregone? L’Artiglio del Capo? Eh... tutto chiaro. Dio giudicherà quell’orsacchiotto grassoccio. Robaccia simile, Charles, te la rifilano in qualunque bottega del porto. Ti ha fregato per bene, approfittando della tua ingenuità... Ha provato a raccontarmi fandonie e io l’ho rimesso al suo posto. Puoi sempre appendere quell’artiglio nella tua cabina sopra il letto, come ricordo... Sempre che tu non l’abbia già buttato tra gli stracci.";
			link.l1 = "Bastardo! Oh, chi se ne frega... Tornerò a trovarlo a Guadalupa e darò una scrollata a quel lurido bruciato!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "Calmati, fratellino caro, rilassati. Non c'è bisogno di agitarsi, a meno che tu non abbia voglia di marcire qualche mese nelle galere di Basse-Terre. Hai già dimenticato quel che ti dicevo? Quel sacco gonfio è un compare di Claude François de Lyon, il governatore di Guadalupa. Appena metto piede fuori di qui, vado a fargli visita... da uomo a uomo. Non scapperà da nessuna parte.";
			link.l1 = "Va bene. Allora pensaci tu... Pare che rimarrò senza il fondo iniziale promesso?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Così pare, Charles. Ma tieni su la testa. Chi ha una nave e cervello sulle spalle non può sbagliare nei Caraibi. E tu hai entrambi, vero?";
			link.l1 = "Cosa stai cercando di dire? Ho combinato un pasticcio con questo pugnale, e allora che dovrei...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "Calmati, caro fratello! Perché ti agiti così all’improvviso? Stai tranquillo, vivrai più a lungo. Non sto alludendo a nulla. Nemmeno mi sono passato per la mente queste idee!";
			link.l1 = "Perdonami, Michel. È solo che sono un po'... cerca di capirmi anche tu!";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "Capisco. E desidero davvero aiutarti! Ascolta bene: devi farti un po’ di esperienza e mettere da parte qualche moneta prima di impelagarti in faccende più serie. Buttarsi a capofоро senza preparazione è pura follia, roba da volersi trovare con la gola tagliata. Non vorrei che questa terra ti schiacciasse ancor prima, ragazzo.";
			link.l1 = "Molto edificante. Su quali avventure vai farneticando, Michel? Ho perso il filo dei tuoi sproloqui, chissà perché.";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Fratello, lascia che ti ricordi che io, o meglio dire noi, dobbiamo a de Poincy un milione di pesos. Pensi davvero che potrai guadagnarli onestamente? Certo, puoi commerciare quella somma, è possibile se la fortuna ti assiste, ma il commercio nei Caraibi non è certo una passeggiata.\nLe avventure ti troveranno anche se non le cerchi, la domanda è: sarai pronto quando arriverà il momento? Meglio colpire per primi. Si vis pacem, para bellum, Charles...";
			link.l1 = "Ancora con queste parole pompose? Parla francese, te ne supplico...";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "È latino, caro fratello. Ho detto: 'Se vuoi la pace, prepara la guerra'. Prendi questa frase come spirito di comando, un invito all’azione. Puoi scriverla nel tuo diario di bordo e rileggerla ogni mattina dopo le preghiere. Hai ancora molto da imparare e ancor più da capire...";
			link.l1 = "Va bene, basta così. Mi sono stufato dei tuoi trattati dotti. Andiamo dritti al sodo.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "Sono chiaro, sei tu che ancora non ci arrivi. Va bene. Prima di tutto, devi prendere confidenza con queste isole e abituarti alla nuova vita da capitano di nave. Dovrai darti da fare per garantirti il benessere e pagare la ciurma. I modi per riempire la borsa non mancano.\nTrasportare merci e passeggeri è la via più semplice. I mercanti nelle botteghe ti offriranno contratti di carico, e i passeggeri ti fermeranno direttamente per strada. Ti conviene anche passare dagli uffici portuali: se hai una goletta o qualsivoglia nave veloce, puoi guadagnare bene da corriere.\nI maestri di porto, una volta che avrai una nave più grossa, ti daranno contratti di trasporto molto redditizi. Parla con la gente, non vantarti troppo del tuo sangue blu, sii amabile e tutto andrà liscio. Fai visita ai governatori delle colonie: spesso hanno incarichi ben pagati.\nPotresti provare a commerciare, ma in tal caso ti serve un buon intendente. Occhio in mare, evita gli squadroni militari spagnoli e le navi da guerra. Se invece scorgi un mercantile spagnolo solitario o un convoglio indifeso, potresti tentare la sorte e prenderli d’assalto.";
			link.l1 = "Cosa?! Michel, sono forse diventato sordo? Mi stai davvero consigliando di buttarmi nella vita da pirata? Tu, vanto della Società, servo di Dio e della Trinità, proponi a me una simile esistenza?";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "Oh, Charles... Ti consiglio di lasciar perdere certe tue raffinatezze una volta per tutte, qui nessuno le apprezza. E quanto all’Ordine... non fare il fesso, fratello. Forse in Europa il Louvre e l’Escorial sono in qualche equilibrio, ma qui c’è solo guerra. Qualsiasi corsaro spagnolo non esiterà a depredare la tua nave e a farti penzolare con tutto l’equipaggio sull’albero maestro, come baccalà.\nDunque, nessuno ti biasimerà se assalti una nave mercantile di una nazione nemica, te lo assicuro. E con una lettera di corsa avrai pure la benedizione dei governanti...";
			link.l1 = "Comincio a comprendere i tuoi principi di vita. Così come intuisco i metodi con cui, a quanto pare, saresti capace di 'guadagnare' un milione in mezzo anno.";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "E dovrai ricorrere a questi metodi, Charles. In fin dei conti, sono sostenuti dalle autorità, sia alla luce del sole che nelle retrovie. Anche se ti limiti al commercio, prima o poi ti toccherà affrontare pirati o corsari spagnoli: per loro sei solo un bottino.\nTi conviene lasciar perdere i tuoi vecchi princìpi. Fidati di me, fratello, qui puoi fare di tutto senza perdere onore, anzi: potresti guadagnarti il favore dei potenti e l’amore della gente.";
			link.l1 = "Non smetti mai di stupirmi, Michel. Ora mi dici pure di diventare un pirata. Che cosa mi toccherà fare dopo?";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "Non farne una tragedia, Charles. È tutto molto semplice: caccia, o sarai cacciato. Questa è la filosofia di fondo. Io scelgo la prima via e vorrei che tu facessi lo stesso. Non ti sto dicendo di diventare un pirata, ma di compiere azioni militari contro una nazione nemica, e solo quando ci sia una buona ragione.";
			link.l1 = "Un sussidio, dici?";
			link.l1.go = "trial_15";
		break;
		
		// Rebbebion, небольшое изменение диалога
		case "trial_15":
			dialog.text = "Vedi, dunque capisci, fratello. Ma basta chiacchiere. È ora di metterti alla prova. Vieni da me solo quando ti sentirai pronto. Fatti qualche soldo serio, procurati una nave migliore, impara a conoscere l’arcipelago e affina le tue abilità.\nMa bada bene: se spenderai i prossimi mesi tra taverne e bordelli senza imparare nulla di buono... allora non tornare affatto. Siamo intesi, Charles?";
			link.l1 = "Non preoccuparti. Non sono venuto qui per farmi una vacanza... E dopo che succede?";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "Ti dirò poi cosa fare dopo. Ho già architettato un piano. Hai davanti a te un futuro luminoso, Charles, se saprai seguire i miei consigli e raccomandazioni senza sgarrare.";
			link.l1 = "Preferirei il mio umile passato piuttosto che un futuro tanto splendente e pomposo...";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "Fidati di me, fratello, un giorno riderai del tuo passato da buono a nulla e ringrazierai il destino che ti ci ha strappato. Sii ottimista e guarda avanti: adorerai questa nuova vita, vedrai.\nAh, un'altra cosa: fai una capatina dal nostro amico comune Fadey e chiedigli di trovarti un impiego. Quel vecchio orso ha i suoi agganci, sono sicuro che ti sistemerà da qualche parte. Non perdere tempo, o rischi di lasciarti scappare la fortuna. E, ti prego, non farmi fare brutta figura.";
			link.l1 = "Prediche morali ancora... Signore, ma quando finirà tutto questo? Va bene, Michel... Posso andarmene adesso?";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "Aspetta. Un paio di consigli tattici in più. Se mai dovessi metterti contro una nazione e diventare fuorilegge, vai subito alla chiesa locale e parla con l’Abate Benoit. Digli che ti mando io. Ha le mani in pasta sia coi papisti che coi calvinisti, e m’ha già tirato fuori dalle peste più d’una volta. Ma sappi che non è né semplice né a buon mercato, quindi meglio evitare di farsi troppi nemici.\nAspetta, un’ultima cosa! Siamo nobili, sì, ma sarebbe da stupidi guardare con disprezzo all’artigianato, specie qui. Puoi fabbricare oggetti assai utili, se solo hai gli attrezzi e i materiali necessari... Dimmi, fratello, come carichi le tue pistole?";
			link.l1 = " Mh. Come sempre, una pallottola e un pizzico di polvere da sparo.";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "Ah! Non mi aspettavo certo di sentir altro.";
			link.l1 = "Conosci forse un’altra via, caro fratello?";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "Certo. Ma ci sono pochi che lo fanno, per ignoranza e pura pigrizia. Se solo spendessi un paio d’ore del tuo tempo, potresti fabbricare cartucce di carta con polvere da sparo e palle. Usandole, dimezzi il tempo di ricarica della pistola. Colpito?";
			link.l1 = "Hm. Direi di sì. Curioso, davvero.";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "Prendi queste istruzioni per fabbricare cartucce di carta, studiale quando hai tempo libero, e non fare il pigro: sfrutta il sapere nuovo che hai imparato.\Aspetta un attimo, fratello. Non scordarti di fare visita al nostro caro governatore.";
			link.l1 = "C’è qualche motivo per festeggiare?";
			link.l1.go = "trial_22";
		break;
		
		// Rebbebion, намёк на "Травлю крысы"
		case "trial_22":
			dialog.text = "Conviene sempre mantenere buoni rapporti coi governatori, soprattutto quando tengono i tuoi parenti rinchiusi sulle loro isole.";
			link.l1 = "Parlami di lui.";
			link.l1.go = "trial_23";
		break;
		
		case "trial_23":
			dialog.text = "Non tutti riescono a tenere lo scranno della Martinica. Gli interessi dell’Ordine, della Corona, dei filibustieri... e un gentiluomo non dovrebbe mai scordare i propri. Se Parquet non fosse tanto molle e incline ai vizi, persino Poincy dovrebbe prenderlo sul serio.";
			link.l1 = "E a che diavolo potrei servirgli io?";
			link.l1.go = "trial_24";
		break;
		
		case "trial_24":
			dialog.text = "Gli ufficiali hanno sempre qualche lavoretto per i capitani liberi. Pagano con il contagocce, però, e solo se la faccenda riguarda il bene pubblico, non i cavoli loro. Comunque, non c’è modo migliore nei Caraibi per farsi un nome e tirare su la reputazione della patria che lavorare per i governatori. Cogli l’attimo, soprattutto ora che il Parquet s’è cacciato in un bel pasticcio. Che razza di pasticcio, dici?";
			link.l1 = "Che razza di guai?";
			link.l1.go = "trial_25";
		break;
		
		case "trial_25":
			dialog.text = "Perdonami, fratello. Ci sono gli interessi dell’Ordine in mezzo. Ti dirò solo che non siamo gli unici a cercare scorciatoie per far fortuna.";
			link.l1 = "Di nuovo con questi misteri... Va bene, passerò quando avrò tempo.";
			link.l1.go = "trial_26";
		break;
		
		case "trial_26":
			dialog.text = "Vai ora. Che la sorte ti assista, fratello!";
			link.l1 = "Grazie... A dopo, Michel.";
			link.l1.go = "trial_27";
		break;
		
		case "trial_27":
			TakeNItems(pchar, "bullet", 5);
			TakeNItems(pchar, "gunpowder", 5);
			DialogExit();
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "trial";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Trial = "begin"; // старт промежуточной линейки
			SetFunctionTimerCondition("Sharlie_TrialOver", 0, 0, 24, false); // таймер
			AddMapQuestMarkCity("Baster", false);
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddQuestRecord("Sharlie", "19");
			// открываем все острова
			for (i=0; i<MAX_ISLANDS; i++)
			{				
				if (!CheckAttribute(&Islands[i], "hidden")) Island_SetReloadEnableGlobal(Islands[i].id, true);
			}
			DeleteAttribute(pchar, "questTemp.Sharlie.Lock"); //снимаем блокировку
			LocatorReloadEnterDisable("FortFrance_store", "reload2", false); // откроем склад магазина
			sld = characterFromId("Benua");
			sld.quest.help = "true";
			npchar.greeting = "mishelle_3";
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 5000;
			// Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.quest.Sharlie_FMQ.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_FMQ.win_condition.l1.value = 4;
			pchar.quest.Sharlie_FMQ.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_FMQ.function = "FMQ_SetConditions";
			// Sinistra - миниквест "Делюк"
			PChar.quest.Del_Alonso.win_condition.l1 = "location";
			PChar.quest.Del_Alonso.win_condition.l1.location = "FortFrance_town";
			PChar.quest.Del_Alonso.win_condition = "Del_Alonso";
			// при достижении уровня даём флаг на квест "Голландский Гамбит"
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.value = 9;
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_9.function = "Sharlie_GambitStage_level_9";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.value = 12;
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_12.function = "Sharlie_GambitStage_level_12";
			//маркер на контрабандиста по квесту "Деньги на деревьях"
			AddLandQuestMark(characterFromId("FortFrance_Smuggler"), "questmarkmain");
			PChar.quest.MOT_UbratMarku.win_condition.l1 = "MapEnter";
			PChar.quest.MOT_UbratMarku.win_condition = "MOT_UbratMarku";
			// Sinistra - Старт квеста "Травля крысы"
			pchar.questTemp.TK_TravlyaKrys = true;
			AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
			SetTimerCondition("TK_Timer", 0, 0, 30, false);
			//маркер на торговца БасТера по квесту "Бесчестный конкурент"
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "gambitA":
			dialog.text = "Fa' come credi allora. Io credo in te, fratello. Quando ti guardo adesso, sento che stai davvero cambiando in meglio.";
			link.l1 = "Ma davvero? E come mai, di grazia?";
			link.l1.go = "gambit";
		break;
		
		case "gambit":
			dialog.text = "Lo vedo, caro fratello. Vedo il tuo passo e l’espressione sul tuo volto. Finalmente la maschera di quel ragazzino vanesio, che mi faceva perdere il senno, si è sciolta via da te. La tua nuova vita ti ha chiaramente giovato, ormai.";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Non capisco, fratello, se le tue parole siano lodi o insulti. Ma ti dirò la verità: poco m’importa di quel che pensi di me laggiù. Ho raccolto il milione che serve a saldare il tuo debito, quindi presto sarai un uomo libero. Dove posso trovare de Poincy?";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "Non riesco proprio a capire, fratello, se le tue parole siano lodi o insulti. Ma ti dico la verità: di quel che pensi di me da laggiù poco m’importa. Ho un mare — non una manciata — di faccende da sbrigare e non ho tempo né voglia di perdermi in dispute e ciarle qui con te. Hai qualcosa di importante da dire? Se no, io prendo il largo...";
				link.l1.go = "gambit_1";
			}
			DelLandQuestMark(npchar);
			DeleteQuestCondition("Sharlie_GambitStage_level_9");
			DeleteQuestCondition("Sharlie_GambitStage_level_12");
			// уберем маркеры, если ФМК не стали проходить
			DelMapQuestMarkCity("Baster");
			DelMapQuestMarkCity("Fortfrance");
			DelMapQuestMarkCity("Charles");
			DelMapQuestMarkCity("Tortuga");
			DelMapQuestMarkCity("Portpax");
			
			if(CharacterIsAlive("FMQG_pass_1"))
			{
				sld = CharacterFromID("FMQG_pass_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQM_carpenter"))
			{
				sld = CharacterFromID("FMQM_carpenter");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQN_seafox_1"))
			{
				sld = CharacterFromID("FMQN_seafox_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQT_girl"))
			{
				sld = CharacterFromID("FMQT_girl");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") 
			{
				DeleteAttribute(pchar, "questTemp.FMQP");
				sld = CharacterFromID("PortPax_waitress");
				DelLandQuestMark(sld);
			}
			if(CharacterIsAlive("FMQG_cureer"))
			{
				sld = CharacterFromID("FMQG_cureer");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("Guide_y"))
			{
				sld = CharacterFromID("Guide_y");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "Sei riuscito a mettere insieme un milione? Bravo, Charles, davvero impeccabile! Ma purtroppo Philippe de Poincy non si trova più nella sua residenza, è partito per affari della Compagnia in una spedizione segreta. Dovrai quindi pazientare un po' prima di poterlo incontrare.";
			link.l1 = "Al diavolo te e i tuoi intrighi segreti! Credevo di finirla con tutto questo e tornare a casa, e invece...";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "E adesso t’è spalancata la via per guadagnare molto di più, e non solo quello. Fratello, il fatto che tu abbia messo insieme la somma richiesta da quel vecchio volpone è una cosa mirabile, ma io non sarei così sicuro e tranquillo... De Poincy è un’anguilla ben viscida, e ha mostrato un interesse non da poco per la tua persona modesta, e...";
			link.l1 = "E adesso temi che nemmeno un milione gli basti?! O forse c’è altro che ti sei dimenticato di raccontare l’ultima volta?";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "Non temo nulla, ma devo avvertirti che Poincy non è un uomo qualunque. Finché lui è lontano, hai l’occasione di farti un nome, così che tu possa parlargli da pari a pari, non come servo davanti al signore. Perciò ti esorto caldamente a seguire il piano che sto per spiegarti ora.";
			link.l1 = "D'accordo. Piangere sul latte versato non servirà a nulla. Resisterò ancora un po' in questa lurida tana. De Poincy non navigherà i mari in eterno. Dimmi, qual è il tuo piano?";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "Oh! Una risposta lodevole. Mi fa piacere, Charles, che tu sia diventato un uomo. Tuttavia, non essere così severo con tuo fratello. Detto ciò, devo dirti una cosa. Ho atteso con ansia il nostro incontro e ho già escogitato un piano per il tuo prossimo incarico.";
			link.l1 = "Bene. Allora, aggiornami.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "Guarda. Certo, nei Caraibi il denaro conta molto, come ovunque, ma non tutto si compra a sonanti dobloni. Un uomo di successo non deve avere solo la borsa piena, ma anche una rete ampia e varia di conoscenze; e non canaglie da taverna, ma persone che davvero contano su questa scacchiera di mare.\nNon importa il loro sangue o la loro bandiera. Le conoscenze aprono porti che nemmeno il denaro può scardinare. Solo unendo 'monete e legami' si ottiene la vera ricchezza di questo mondo: il potere.\nPensaci, dovresti cercare proprio tali alleanze. Non le troverai trasportando merci, trafficando, assaltando barche da strapazzo o leccando gli stivali dei governatori.";
			link.l1 = "Cosa proponi, dunque?";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "Non ci sono poi così tante potenti organizzazioni nei Caraibi. Una di queste è la Compagnia Olandese delle Indie Occidentali. Puoi unirti a loro. La loro sede è a Willemstad, su Curaçao. La Compagnia spesso assume capitani indipendenti e offre contratti speciali a lungo termine ai più abili tra loro. \nSe la fortuna ti assiste, potresti farti una bella carriera là dentro. Ho sentito che ora stanno passando un brutto periodo – un corsaro inglese si è rivoltato contro la Compagnia e affonda regolarmente le loro navi. Non riescono a fargli nulla, è un ufficiale della marina: troppo tosto per loro. \nSi mormora che abbia contatti con i servizi segreti di Sua Maestà, e quelli non scherzano affatto. Forse, quindi, schierarti dalla parte di questo capitano ti farebbe guadagnare ancora di più… ma il guaio è che non so come si chiami; so soltanto che ha base ad Antigua. \nPotresti salpare fin là e fare qualche domanda. Ho pure sentito parlare di una strana organizzazione che si è intromessa in questa faida anglo-olandese, ma non saprei proprio da che parte stia. Tutto ciò che so è che le tracce portano a Barbados, a Bridgetown...";
			link.l1 = "Quindi mi suggerisci di arruolarmi sotto la bandiera olandese, oppure di mettermi a caccia di qualche capitano losco o, peggio ancora, di una di quelle 'organizzazioni' che puzzano di guai?";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = "La scelta è tua. In ogni caso, non avrai altra via per entrare in grazia a chi qui nei Caraibi tira i fili e comanda davvero. Spero che tu non creda che bastino due o tre favori al governatore per farti arruolare direttamente nella marina reale.";
			link.l1 = "Sai, caro fratello. Non è che sognassi proprio una carriera militare nella marina francese. Dio me ne scampi dal finire come te, rinchiuso in una cella per qualche faccenda andata storta... Va bene, ho capito. Penso che riuscirò a trovare il Quartier Generale della Compagnia Olandese senza troppi intralci, ma sul resto dei compari non ho la minima idea di dove mettere le mani.";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "Per quanto riguarda il corsaro inglese, puoi chiedere in giro a St. John's, Antigua. Qualcuno di certo saprà darti informazioni. Dì che cerchi lavoro con la flotta inglese. Quanto alla 'terza forza', parla con la gente di Bridgetown: laggiù qualcuno sarà senz'altro legato a questa compagnia.";
			link.l1 = "Almeno saranno pagati per la loro fatica? La Compagnia, questo corsaro... O tutto finirà per essere solo per quei dannati ‘contatti’?";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "Charles, mi sorprendi davvero. La Compagnia Olandese delle Indie Occidentali maneggia somme che farebbero ingelosire un re. Quel corsaro di cui ti parlavo ha saccheggiato così tante navi olandesi che ormai dev’esser saturo d’oro fino alle orecchie. E quelli dell’“organizzazione” non hanno solo un bel gruzzolo. Hanno una montagna di dobloni, per tutti i diavoli! \nLavorare per loro è sempre un affare grasso e succulento. Gente di quel calibro gioca solo partite grosse. E se sai come si fa, puoi sempre girare la ruota a tuo favore e guadagnare ancora di più.";
			link.l1 = "D'accordo. Ci rifletterò su e deciderò quale sia la mia mossa migliore. Hai altre istruzioni da darmi?";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "Sì. Dovresti imparare a usare strumenti di navigazione. Ahimè, troppi navigatori si orientano solo con bussola e stelle, ma non sanno calcolare le coordinate. E questo è vitale.\nAllora. Usa una boussole per stimare la latitudine. È uno strumento raro e non lo troverai nelle botteghe, ma puoi fabbricarlo da te usando due oggetti comuni: una bussola e un astrolabio. Tieni, prendi queste istruzioni.\nDeterminare la longitudine è una faccenda più complicata. Ti serve un cronometro tarato. Puoi crearne uno da un semplice cronometro di bordo, sistemato con una clessidra. Il guaio è che questo arnese resta preciso solo per un mese prima di diventare inaffidabile a causa degli errori.\nUn cronometro va sempre ricalibrato. Le clessidre le puoi acquistare all’ufficio della Compagnia Olandese delle Indie Occidentali. Lì ho preso anche i cronometri. Ecco, prendi queste istruzioni.";
			link.l1 = "Grazie. Mi metto subito a studiare.";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "Cerca di procurarti questi strumenti il prima possibile. Tutti i capitani degni di rispetto navigano usando latitudine e longitudine. Finché non saprai cosa indicano quei numeri, per la gente di mare resterai solo un pivello.\nEbbene, torna a vantarti appena avrai avuto successo nelle faccende di cui abbiamo parlato. Buon vento, Charles!";
			link.l1 = "Grazie, caro fratello. Son certo che mi tornerà utile!";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//флаг на Голландский Гамбит
			pchar.questTemp.HWIC.CanTake = "true"; //Голландский Гамбит доступен для взятия
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
			AddMapQuestMarkCity("Bridgetown", false);
			AddMapQuestMarkCity("Villemstad", false);
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			// Rebbebion, убираем марки
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "gambit_fale":
			dialog.text = "E di che ti vanti, tu?";
			link.l1 = "Niente per adesso. Ho trovato tutte e tre le compagnie e ho provato a collaborare con loro, ma come una pipa spenta è andato tutto in fumo già dal primo passo. Pare proprio che il destino abbia imbrogliato le carte contro di me...";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "Dunque, le voci erano vere... Caro fratello, il destino non t’ha voltato le spalle. È la tua testa vuota e la tua mano maldestra. Mi hai deluso. Torna in Francia, qui non hai più nulla da fare.";
			link.l1 = "Ma come...";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "Non t’impicciare più. Me la vedrò da solo. Ho gente ben più capace per rimediare ai miei guai. Avevo paura che confidarmi con te mi avrebbe inchiodato qui fino alla fine dei miei giorni. Comunque sia, sparisci. Torna pure dalle tue cortigiane.";
			link.l1 = "Va’ al diavolo, allora...";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "Non ho nulla da dirti. Sparisci.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "I've entered service with the Dutch West India Company and become a special tasks agent and close friend of the vice administrator of the Company, Lucas Rodenburg. I managed to carry out several serious missions, in particular, I liquidated the actual English privateer. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "holl_fail": sTemp = "I've entered service with the Dutch West India Company, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "eng_win": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship' and did away with Lucas Rodenburg himself, vice administrator of the Company. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "eng_win_half": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship'. Of course, Fleetwood departed to England and my service with him is over, but still..."; break;
				
				case "eng_fail": sTemp = "I've entered service with the English privateer from Antigua, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "self_win": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, and achieved quite a bit: I did away with that English privateer, Richard Fleetwood, put Lucas Rodenburg, the vice administrator of the Company, behind bars, become a close friend of governor Matthias Beck and the company's director Peter Stuyvesant. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "self_fail": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, however it all went down in dust at the moment of truth..."; break;
			}
			dialog.text = "E allora? Dai, caro fratello, non tirarla per le lunghe. Quali sono le novità? Mi sono giunte all’orecchio certe dicerie sul tuo ardore e la tua operosità, ma volevo sentir tutto dalla tua bocca.";
			link.l1 = sTemp;
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Eccellente! Ben fatto, Charles! Non ho mai dubitato di te, nemmeno per un attimo! Farai strada, caro fratello... Darti tanto da fare e stringere legami con gente tanto importante, beh, non me lo sarei aspettato. Complimenti!";
			}
			else
			{
				dialog.text = "Non crucciarti, Charles. Se non è andata come speravi, poco ci puoi fare. Troveremo altri modi per ottenere ciò che ci serve.";
			}
			link.l1 = "E allora, Michel, che si fa adesso? È il momento di far visita al Cavaliere de Poincy? Mi sento ben pronto per una chiacchierata con lui.";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "Hai già messo insieme la somma richiesta di un milione di pesos?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Sì, ho già in tasca la somma necessaria.";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "No, non ho ancora quella somma di denaro.";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "Eccellente! Allora presto smetterò di г marcire in questa dannata prigione... Vai subito a Capsterville, si trova su Saint Christopher, e chiedi udienza a de Poincy. Dovrebbe trovarsi nel palazzo del governatore, dove risiede. Dopodiché, valuta in base alla situazione e rammenta: Poincy è furbo, dannatamente furbo... Ho una brutta sensazione, tutta questa faccenda non andrà liscia come il rum. Vai, fratello, e fa’ attenzione!";
			link.l1 = "Terrò a mente le tue cautele, Michel. Non ti agitare, non sono nato ieri nemmeno io. Ora vado da quella vecchia volpe. A dopo!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "Inutile parlare con de Poincy allora. Non ti lascerà nemmeno entrare. Raccogli i soldi, fratello mio, ormai hai già un po’ di esperienza quindi non dovrebbe essere un gran problema. Appena li hai, salpa per Capsterville su Saint Christopher.\nIl Cavaliere dev’essere al palazzo del governatore. Chiedi udienza e ti faranno entrare. Poi vedi con i tuoi occhi e fa' attenzione: Poincy è furbo, ma davvero furbo… Ho come la sensazione che questa storia non finirà così facilmente.";
			link.l1 = "Terrò a mente le tue cautele, Michel. Non preoccuparti, non sono nato ieri nemmeno io. Appena metto insieme la somma, andrò dritto a quel vecchio volpone. Ci si vede!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			AddMapQuestMarkCity("Charles", false);
			AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//флаг на Пиратскую Сагу
		break;
		
		case "saga_5":
			dialog.text = "Santissimo cielo! Proprio di questo avevo paura. Poincy ti tiene d’occhio da un bel pezzo, Charles. Ecco perché si è tanto interessato a te! In queste acque ti sei già fatto una certa fama, e lui ha deciso di servirsi di te per sistemare faccende andate a ramengo...";
			link.l1 = "Ho come l'impressione, Michel, che tu lo sapessi benissimo e semplicemente non volessi avvisarmi prima. Tutto fila troppo liscio... Prima i soldi, ora il tuo lavoro... Non succede mai per caso.";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Charles, non cercare messaggi segreti dove non ce ne sono. Se solo avessi dato a Poincy i soldi il primo giorno che sei arrivato... Beh, voglio dire, se li avessi avuti. Il Cavaliere non ti avrebbe mai domandato altro. Ma ora che s'è accorto di te, che ha visto quanto ti sei ambientato qui e tutto ciò che sei riuscito a combinare, ha deciso di sfruttare i tuoi talenti.";
			link.l1 = "Già... perché i tuoi talenti ormai non gli bastano più, eh? Maledizione! Va bene. Vedo che qui ho sbattuto contro un vicolo cieco. Chi è questo eretico? Come posso trovarlo?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Non c’è nemmeno bisogno di cercarlo! Non mette mai piede fuori из Tortuga, se ne sta rintanato nella sua roccaforte circondato da orde di Ugonotti fedelissimi che gli fanno da guarnigione. Ogni soldato lo serve con devozione. Poincy si riferiva proprio a François Levasseur, il governatore di Tortuga. \nGli spagnoli ancora non sono riusciti a schiodarlo di lì, e de Poincy, con tutta la sua serietà, crede davvero che proprio io possa farcela da solo, senza nessun aiuto della marina, solo perché scatenare una guerra civile, con la guarnigione di Santo Domingo così vicina, sarebbe una catastrofe politica. \nQuel vecchio cane pensa troppo alla propria carriera immacolata e alla pensione che sogna per rischiare tutto in questo modo. Eppure, Levasseur ha passato il segno ed è diventato una minaccia per la Corona. \nDe Poincy, che l’ha messo lui stesso su quella poltrona, ormai vede quest’Ugonotto feroce come un nemico personale, e freme dalla voglia di sostituirlo col Cavaliere Maltese de Fontenay, il mio diretto superiore, sotto il cui comando sono arrivato qui da Malta.";
			link.l1 = "Glorioso! Prima fai un milione, poi ammazzi il governatore di Tortuga. Quale sarà il mio prossimo incarico? Organizzare un complotto all'Escorial? Maledizione! Non mi stupisce che tu abbia fatto fiasco con quella faccenda. Far fuori il governatore non è come sfilare la borsa ai mercanti spagnoli. Spero che almeno una mezza idea ce l’avevi, quando hai giurato di togliere le castagne dal fuoco?";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "A dirla tutta, non avevo alcun piano: tanto avrei lasciato il servizio comunque, e in caso di successo della mia follia, me ne sarei tornato nella nostra villa di famiglia. In quanto ai guai di de Poincy, francamente me ne infischio.\nDi sicuro, sarebbe diventato assai più accomodante non appena avesse visto l’oro degli indiani... Ma per ora tiene tutte le carte in mano contro di noi. Credo che rimarrò qui finché Levasseur resta governatore di Tortuga.";
			link.l1 = "E perché mai i maltesi guidati da de Fontenay, con gli occhi puntati sulla poltrona del governatore, non assalirebbero Tortuga di persona?";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Immagina un po'. L’ordine che dichiara guerra a Luigi? Non dire sciocchezze! Uno scandalo simile non si può permettere. Solo un uomo privato può conquistare Tortuga. Un pirata, o un avventuriero cattolico come te.\nPoi potrà cedere l’isola al nuovo governatore che de Poincy manderà. Un gesto che farà un figurone agli occhi dei grandi burattinai della politica.";
			link.l1 = "Quindi c’è senso a trattare coi filibustieri?";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Il guaio è che Levasseur comanda rispetto tra una folla di filibustieri della Fratellanza e oltre. Li lascia nascondersi sotto i cannoni di Tortuga e smerciare il bottino come pare a loro, purché gli diano una parte.\nPrima divideva con de Poincy, ma ora non passa più nulla. Le navi pirata difenderanno Tortuga e la sua guarnigione, rendendo l’assalto al forte ancora più dannato arduo.";
			link.l1 = "Pensi che questa faccenda sia ormai persa?";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "C'è sempre una via d'uscita, fratellino. Non sempre si vede a occhio nudo, però. Non tutti i filibustieri hanno simpatia per gli ugonotti di Tortuga. Conosco almeno due capitani di peso che pensano che Levasseur sia un traditore e una carogna. Parlo di Steven Dodson, detto lo Squalo, e del leggendario barone della Baia delle Zanzare, Jan Svenson. \nNon saprei dirti dove sia lo Squalo; si dice abbia dovuto lasciare la sua tana a Isla Tesoro per qualche guaio. Ma Svenson lo trovi sempre a Blueweld. Lì comanda davvero.";
			link.l1 = "Pensi che questo... Svenson mi darà una mano?";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Lo farà, se gli darai una mano. In questo momento le cose gli vanno tutt’altro che bene e avrebbe proprio bisogno di gente leale e in gamba. Prima dovrai dimostrargli quanto vali, solo allora potrai intavolare un discorso serio con lui. Quando arriverai laggiù, troverai il modo per farlo. Da qui, difficile darti consigli.\nImmagino che tu abbia deciso di partire, Charles, visto che continui a tempestarmi di domande?";
			link.l1 = "Vedi, Michel, ho appena mollato una montagna del mio argento a de Poincy. L'ho sudato col sangue e col dolore! Non sono certo che tu avresti rischiato nemmeno un solo luigi d’oro per me, se fossi stato al mio posto.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "Charles...";
			link.l1 = "Non interrompermi! Sarebbe una sciocchezza tornare a nostro padre a mani vuote. Il guaio non è ancora risolto: tu sei qui rinchiuso e rischi d’esser condannato per tradimento alla Compagnia. Poincy non esiterebbe a infangare il nome dei Monper, se non eseguo il suo 'ordine'. Lo si leggeva in faccia, quel dannato. Dunque, me ne andrò a Blueweld per trovare il modo d’avvicinare Svenson. Nel frattempo, pensa un po’ a cos’altro hai ‘dimenticato’ di raccontarmi. Per esempio, è la prima volta che sento parlare di qualche oro indiano che dovevi portare a de Poincy.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Ci sono cose che è meglio lasciare nell’ombra. Hai ragione, non ti ho confessato tutto ciò che so. Forse, un giorno ti svelerò di più, ma non prima che tu abbia sistemato gli affari con Levasseur: ora sarebbe sapere sprecato.  Non ho dubbi che questa tua premura commovente verso di me nasca solo dal desiderio di salvare l’onore della nostra casata. Salvando me, salvi in primis te stesso e poi la tua possibilità di frequentare i migliori salotti di Parigi. Sbaglio forse?";
			link.l1 = "Temo che non sia più così, fratello. Avevi ragione. Questi ultimi mesi trascorsi nei Caraibi hanno mutato ogni fibra del mio essere e tutto il mio modo di vedere il mondo. E son certo che sia per il meglio. Quelle sale parigine ormai non mi servono più, e un giorno potrò fare a meno anche del nome Monper. De Maure non vale certo di meno...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "...";
			link.l1 = "E adesso, l’unica cosa che m’ha davvero ferito è che la tua vergogna lascerà un’ombra sul nostro vecchio padre. Ignora la verità di quel che accade qui, e la situazione reale. E, come giustamente hai detto, il patrimonio va strappato alla rovina. Inoltre, il milione sborsato per la tua libertà ha prosciugato le mie casse, che ora tocca rimpinguare.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "Hai appreso alla perfezione tutte le lezioni della vita, Charles. Ne sono davvero lieto. E mi rallegra il cuore che tu abbia accettato l’incarico di de Poincy invece di tornare a casa in Francia. Spero che tutto vada a buon fine per te e che tu riesca a compiere ciò che io stesso non sono stato in grado di fare.";
			link.l1 = "Temo di non avere altra scelta. Dal mio primo giorno nei Caraibi, me la cavo sempre da solo. Ci vediamo, Michel. Penso che la prossima volta che ci incontreremo porterò l’ordine per la tua libertà.";
			link.l1.go = "saga_17a";

		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "saga_17a":
            dialog.text = "Aspetta un attimo! Prima di andare da Jan Svenson, passa a trovare Marcus Tyrex – lui è il Custode del Codice. Comanda La Vega su Hispaniola. Ha un’autorità senza limiti tra i filibustieri e perfino gli spagnoli tremano solo при его имени.";
			link.l1 = "Potrebbe darmi una mano con la nostra faccenda?";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "Ne dubito. Non saprei proprio da che parte stia, probabilmente pensa solo al proprio tornaconto. Comunque ti serviranno lo Squalo e Svenson, ma al momento – Tyrex è il bucaniere più potente di queste acque. Non per caso l’hanno scelto come Custode del Codice. Non dovresti sottovalutare un uomo così importante. Potresti trarne vantaggio conoscendo meglio questa marmaglia prima di incontrare Svenson. Magari riuscirai perfino a farti un nome tra loro...";
			link.l1 = "E ancora una volta, eccoci tornati ai discorsi da filibustiere. Pare proprio che non possa sfuggirci, eh? E sia. Andrò a fargli visita.";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "Essere un filibustiere e fare affari con quella marmaglia sono due mestieri diversi, fratello. Spero che tu sappia cogliere la differenza. Vai a La Vega e chiedi lavoro a Tyrex. Se non vi intendete... manda al diavolo quel furfante e torna da me.";
			link.l1 = "Va bene, Michel. A presto!..";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
			AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
			AddMapQuestMarkCity("LaVega", false);
		break;
		
		case "saga_17e":
            dialog.text = "Almeno ci hai provato. Hai avuto l’occasione di ‘stringere amicizia’ con un famigerato barone pirata. Poco male. Vai da Jan Svenson, si trova a Blueweld. Cerca di fartelo amico, altrimenti la nostra faccenda con Levasseur finirà in un bagno di sangue.";
			link.l1 = "D’accordo. Mi metto in cammino.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "Contento che ti sia fermato, fratello. Ti dissi una volta che esser pirata o far affari con пиратами — son due giochi ben diversi. E tu hai perso la rotta. Spero tu non commetta lo stesso errore con lo Squalo e Svenson. Porta a termine il lavoro, ma resta a distanza da loro. Sei pur sempre un nobile francese, dunque mantieni il tuo rango. Ora va’ da Jan Svenson, si trova a Blueweld. Cerca di fartelo alleato, altrimenti la nostra faccenda con Levasseur finirà in un bagno di sangue.";
			link.l1 = "Va bene. Mi metto subito in cammino.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "Mi fa assai piacere sentirlo, se davvero dici il vero. Ma posso io fidarmi della parola d’un filibustiere che dà fuoco alle città, anche se sono spagnole, e sgozza la povera gente, donne comprese?";
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
			{
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "good")
				{
			link.l1 = "Fermati... Ti chiedo davvero perdono per le mie follie al fianco di Tyrex. Ho visto l'inferno coi miei occhi, fratello... Basta, è finita! Ho chiuso con la pirateria e non metterò mai più piede a La Vega. Farò tutto il necessario per riscattare il mio nome.";
			link.l1.go = "saga_17gx";
				}
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
				{
					link.l1 = "Che tu ci creda o no, sei tu dietro le sbarre, non io.";
					link.l1.go = "saga_17gxa";
				}
			}
			else //заглушка
			{
				link.l1 = "Smettila... Mi pento davvero delle abominazioni commesse quando lavoravo con Tyrex. Ho visto l’inferno con questi occhi, fratello! ... No, il mio passato da pirata è finito! Non sono più a La Vega. Farò di tutto per riscattare il mio buon nome.";
				link.l1.go = "saga_17gx";
			}
		break;
		
		case "saga_17gxa":
            dialog.text = "Oh, fratello... Non far adirare il Signore... Spero che non si ripeta con Svenson e Shark. Fai quel che devi, ma resta distante e ricorda che razza di canaglie sono. Non si addice a un nobile francese diventare come loro. Sii superiore. Ora vai da Jan Swenson a Blueweld e cerca una via per arrivare al vecchio corsaro. Senza di lui, non sarà possibile sistemare la faccenda con Levasseur senza spargere troppo sangue.";
			link.l1 = "Va bene. Non indugerò oltre.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;

		case "saga_17gx":
            dialog.text = "Dovrai faticare non poco, fratello. Ricordi cosa ti dissi una volta? Che essere un pirata e fare affari con loro sono due mari diversi. Tu... Lascia stare, spero solo che non commetterai lo stesso errore con lo Squalo e Svenson. Sbriga la faccenda, ma resta a distanza da quei furfanti. Sei un nobile francese, dunque, mantieni il tuo rango sopra di loro. Ora va’ da Jan Svenson, lo troverai a Blueweld. Prova a fartelo alleato, altrimenti la nostra trattativa con Levasseur finirà in un bagno di sangue.";
			link.l1 = "D'accordo. Mi metto in cammino.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			npchar.greeting = "mishelle_3";
			if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
				SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
			}
			AddMapQuestMarkCity("SantaCatalina", false);
			AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;
		
		case "Base_fight":
			dialog.text = "Ora non è il momento per chiacchiere, fratello! Il nemico ha messo piede nel nostro rifugio!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) sTemp = "I see you've become a captain of the navy... I didn't see that coming to be honest. I truly congratulate you!";
			dialog.text = "Sei arrivato proprio al momento giusto, caro fratello! Che gioia rivederti! Quei maledetti castigliani hanno ormai messo le mani su tutta Saint-Pierre. Credevo che fossimo spacciati, per tutti i diavoli!"+sTemp+"";
			link.l1 = "Non siamo ancora fuori pericolo, la città è sgombra ma quei dannati se ne stanno rintanati al forte e c'è una flotta intera guidata da una nave da battaglia. Ma ti porto una notizia che scalda il cuore: Michel, sei libero!";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "Non ci posso credere alle mie orecchie! È davvero possibile? La libertà?!";
			link.l1 = "Levasseur è morto, Tortuga ora è guidata dal tuo ex comandante, e il vecchio volpone Poincy ha ritirato tutte le accuse contro di te. D’ora in poi, nulla minaccia il buon nome della nostra famiglia.";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "Ho dubitato fino all’ultimo istante... Mi hai davvero sorpreso, Charles, e hai trionfato là dove io ho miseramente fallito.";
			link.l1 = "La fortuna aiuta gli audaci, fratello... Come vedi, ormai so pure il latino. Dov’è la chiave della tua cella?";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "La chiave della mia cella dovrebbe stare sulla scrivania dell’ufficiale di servizio. Cercala lì. Magari è caduta a terra e s’è infilata da qualche parte...";
			link.l1 = "Vado a cercarli e torno subito!";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "Libertà, finalmente! Ah, quanto ho atteso quest’attimo!";
			link.l1 = "Non puoi nemmeno immaginare quanto ho atteso questo momento... Michel, abbiamo uomini pronti a menar le mani?";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "Che ti frulla in testa, Charles?";
			link.l1 = "La minaccia degli Spagnoli non è ancora svanita. Voglio scacciarli dal forte e poi unire le forze per assalire lo squadrone sia da terra che dal mare! Usando i cannoni del bastione potrò menar le mani col vascello da guerra!";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "Abbiamo uomini a volontà. Un buon numero di cavalieri è partito per difendere il palazzo del governatore. Troveremo sicuramente qualcuno in città... Radunerò tutta la gente che riuscirò a scovare. Ci vediamo oltre le porte della città!";
			link.l1 = "...";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "Eccola qui, fratello, la nostra armata. Tutta la gente che sono riuscito a radunare. Non siamo molti, ma combatteremo per la nostra Patria! Sputeremo fuori questi maledetti invasori dal forte! L'effetto sorpresa ci aiuterà – non si aspettano il nostro attacco. Avanti!";
			link.l1 = "Dolce e glorioso è morire per la patria! Avanti!";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "È fatta, fratello! La fortezza è nostra!";
			link.l1 = "Peccato che abbia preso una bella mazzata nello scontro con la squadra spagnola... ma è ancora più che buono per guidare una battaglia.";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "Farò la mia parte. Caricheremo i cannoni e daremo al nemico una bella lezione! Ma solo quando vedremo la tua squadra avvicinarsi, altrimenti il vascello da guerra ci farà a pezzi in un batter d’occhio.";
			link.l1 = "Raduna la ciurma, Michel! Me ne vado subito verso la riva!";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "Charles, ricorda: la parte più temibile dello squadrone è la nave da guerra! Prova a metterla fuori gioco per primo. Noi pure concentreremo il fuoco su di lei con ciò che resta della batteria del forte.";
			link.l1 = "Va bene, fratello. Forse dovrei farla mia prigioniera.";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "A giudicare dalle circostanze, non sono certo io quello che deve insegnarti qualcosa. Ora basta sprecare tempo, avanti!";
			link.l1 = "…";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
			// закрываем городские заведения
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "Gloria alla vittoria! Complimenti per il trionfo, fratello! Sei stato magnifico! Gli spagnoli sono stati annientati!";
			link.l1 = "Spero che questo gli insegni a pensarci due volte prima di assaltare le colonie francesi.";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "Dimmi ora, Charles: quanto vale la tua vita passata... rispetto a questa?";
			link.l1 = "Non me lo rammentare...";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "Ti ricordi cosa ti dissi al nostro primo incontro qui? 'Amerai questa vita', ecco cosa! Già, e ti devo davvero un grazie enorme, fratello, per il tuo aiuto. Senza di te, probabilmente non sarei mai riuscito a sfuggire a quella dannata prigione sotterranea.";
			link.l1 = "Non dirlo nemmeno, Michel. Sei pur sempre mio fratello e avevo il dovere di tirarti fuori dai guai.";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "Ma guarda un po’ te, fratello, son davvero colpito: quanta forza nello sguardo, quanta sicurezza nei gesti, che portamento fiero... che fine ha fatto quel pittore da strapazzo e buffone di corte? Davvero! Hai superato ogni mia più sfrenata aspettativa, in tutta onestà non avrei mai pensato che saresti diventato... questo.\nMi fai quasi... paura, sai? Perché ora nulla ti fermerà dal raggiungere ciò che vuoi. Sei bravo, fin troppo bravo...";
			link.l1 = "Per qualche strana ragione, fatico di nuovo a capirti. Sei di nuovo scontento di me?";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "No!  Ma che dici?...  Niente affatto!  Stavo solo cercando di contenere la mia esuberanza.";
			link.l1 = "D'accordo. E allora, che farai adesso, fratello? Continuerai a servire la Compagnia? O tornerai ai nostri possedimenti? Ah già, stavo per dimenticare: mi avevi promesso di raccontarmi una certa cosa.";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "Di che parli, precisamente?";
			link.l1 = "Del tuo servizio per de Poincy. Dell’oro indiano che dovevi portargli. Di tutto ciò che ha preceduto la tua prigionia. Mi hai lasciato all’oscuro di molte cose, Michel. Quindi...";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "Fratello, ricordo benissimo quello che ho detto. Ti racconterò tutto. Ma non qui, in mezzo a una città che va a fuoco!\nAdesso abbiamo entrambi il nostro bel da fare. Tu devi sistemare la tua squadra, rimetterla in sesto e preparare di nuovo le navi. Io col governatore ci occuperemo di tranquillizzare questa marmaglia.\nDomattina, con un bicchiere di buon vino francese, parleremo di tutto quanto. Fidati di me, fratello, ho un piano enorme. Davvero enorme. Ma non ora. Passa domani dall’Abate Benoit alle nove. Passerò la notte da lui, è un vecchio compare.";
			link.l1 = "D'accordo, Michel. Allora è deciso. Non vedo l'ora di chiacchierare con te domani.";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_6A":
			dialog.text = "Dialogo 28.";
			link.l1 = "D'accordo, Michel. Allora è deciso. Attenderò con ansia la nostra chiacchierata di domani.";
			link.l1.go = "Victory_7";
		break;
		
		case "Victory_7":
			dialog.text = "Nessun bisogno di saluti, Charles!";
			link.l1 = "...";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// раздача экспы
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("All those residing in the French colony owe you, Captain. Defending Saint-Pierre from the vile attack of the Spanish is quite a feat!", FRANCE, 30, 15);
			AddSimpleRumour("It's an honor for me to speak with the brave Captain that has beaten a bunch of Spanish invaders hollow!", FRANCE, 30, 15);
			AddSimpleRumour("The French colonists may sleep in peace, while brave naval officers such as you are at the King's service!", FRANCE, 30, 15);
			AddSimpleRumourCity("We are all forever indebted to you, Captain! You have saved our colony from devastation!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are a brave and astute naval officer. All those residing in Saint-Pierre are praying for you, know that!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are the pride and joy of our nation and the hero of Saint-Pierre. We will never forget that!", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("Voice\English\sharlie\mishelle-04.wav");
			dialog.text = "Così ci rincontriamo, "+pchar.name+"  Nonostante i miei avvertimenti, hai continuato a cercarmi e le tue ricerche ti hanno portato molto, molto lontano... ";
			link.l1 = "Michel?... Non so perché, ma non mi stupisce affatto. Forse Miguel Dichoso è tornato a Tayasal per un altro mucchio di tesori? Eh-eh-eh. Sì, cercavo proprio un incontro con te, caro fratello. Morivo dalla voglia di guardarti negli occhi senza vergogna. E poi, quel tuo piccolo attentato alla mia vita nella cripta del cimitero... ciliegina sulla torta. Ma prima, dimmi, come devo chiamarti? Michel de Monper o Miguel Dichoso?";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "Questi nomi ormai non contano più, "+pchar.name+"È tutto ormai sepolto dal passato, che presto svanirà persino dalle pagine della storia. Ora è giunto il momento della verità, verso cui mi sono trascinato per un lungo quarto di secolo da quando ho messo piede su questa terra...";
			link.l1 = "Cosa?! Questo... questo è impossibile!!!";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "Sì, "+pchar.name+"Vedo dalla tua faccia che hai capito chi sono, ma proprio non ci credi. Sono colui che hai desiderato incontrare negli ultimi mesi. Colui con cui il rappresentante del tuo Dio, l’Inquisitore di Santiago, ti ha benedetto per affrontare la battaglia.";
			link.l1 = "Kukulcan?!";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "Sono d’accordo, "+pchar.name+", che è difficile da credere. La vita è più complicata e sorprendente di qualsiasi fiaba...";
			link.l1 = "Ero pronto a tutto, ma... mio fratello!";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "Fratello? Solo per via del sangue paterno. Le nostre madri non sono le stesse, "+pchar.name+"Sappi che mia madre era figlia di Kanek, si chiamava Shochikezhal. Fu rapita dai corsari francesi al comando del celebre Nicolas Gotier, dopo che scioccamente lasciò Tayasal. Avevano deciso di farne una schiava. Tra loro c’era un uomo di nome Serge Benoit. Vergognandosi dell’atto del suo capitano, lo abbandonò, prese i voti e ora lo conosci come Abate Benoit. Henri de Monper, nostro padre, era allora un ufficiale di marina. Comprò Shochikezhal e la portò in Francia, dove mi diede alla luce. Più o meno nello stesso periodo, anche tu venisti al mondo, "+pchar.name+". Tua madre morì dandoti alla luce, e nostro padre dichiarò che la sua legittima consorte aveva dato alla luce due gemelli.\nShochikezhal, mia madre, divenne balia per entrambi. Sei stato allattato col latte di una donna india della stirpe Itza, "+pchar.name+"! In seguito tua nonna materna decise di prendersi cura della tua educazione e ti fu dato il cognome di tua madre – de Maure.";
			link.l1 = "Come hai scoperto tutto questo?!";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "Non penseresti, fratello, che io sappia più del volgo? Nostro padre poi mi ha raccontato non poche cose e sono a conoscenza di molto... È proprio come si dice, vado a naso.";
			link.l1 = "Ora tutto è chiaro... E che ne è stato di tua madre? Perché non l'ho mai vista?";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "Morì salvandomi la vita. Poco più di un anno dopo la mia nascita, stavo per crepare a causa d’una malattia. Mia madre, figlia d’un sacerdote Itza, celebrò per me di nascosto un rito maya di guarigione magica. Guarii, sì, ma il rito scatenò certi... effetti collaterali devastanti: tuoni, fulmini e un uragano tropicale. Shochikezhal fu denunciata, accusata di stregoneria e arsa viva dai cani dell’Inquisizione...";
			link.l1 = "E sei migliorato...";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "Oltre a guarirmi, questo rituale mi ha donato anche altre abilità, oltre ad aprire un varco verso il mondo degli dèi. Il resto lo conosci già. Come ben sai, porterò la luce della conoscenza e l’esperienza della razza bianca nel passato e la trasmetterò al popolo Maya. La storia verrà riscritta, e voi, bianchi, non sarete più i padroni di questo mondo. Io stesso lo garantirò.";
			link.l1 = "Quindi tutta la tua vita, gli anni all’accademia navale più rinomata, il servizio nell’esercito e nell’Ordine di Malta, non erano altro che una lunga raccolta d’esperienza bellica?";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "Proprio così. Quando mi sono reso conto di sapere abbastanza, ho fatto in modo che mi ordinassero di andare ai Caraibi. Ho convinto il Chevalier de Poincy a creare una base in Martinica. Poi, dovevo raggiungere Tayasal. Non è stata proprio una passeggiata, dato che questo corpo mortale resta fragile, e i portali nei Caraibi funzionavano a malapena.";
			link.l1 = "E così sei diventato Miguel Dichoso...";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = "Caro fratello, questo soprannome l’ho guadagnato sui campi di battaglia d’Europa. È lì che ho incontrato anche Ramon de Mendoza y Riba. Pensi davvero che la vita sia fatta di coincidenze? Tutt’altro, ogni caso segue una legge nascosta. Ho dovuto fare molto per poter tornare a Tayasal. Ho vissuto due vite: Michel de Monper e Miguel Dichoso. Dovevo far credere a tutti che fossero uomini diversi.\nCome te, sono stato costretto a fare il corsaro al servizio di de Poincy, per guadagnarmi la sua fiducia, il suo favore e i suoi dobloni. Ho dovuto far fuori Blaze Sharp, uno dei capi della fratellanza, per compiacere Ramon de Mendoza e ottenere soldati per la spedizione.\nHo stuzzicato sia de Poincy che de Mendoza con storie sui tesori di Tayasal. Dalle casse di de Poincy ho ricevuto settecentocinquantamila pezzi d’argento e ho venduto la fregata militare spagnola al bucaniere Dodson. E poi, la spedizione ha avuto luogo. Sono tornato a Tayasal solo per andare incontro al fallimento...";
			link.l1 = "Capisco... Mentre tu, un ragazzino di appena cinque anni, rincorrevi le farfalle nei possedimenti di nostro padre, il grande sacerdote Kanek, spaventato dall'invasione di Don Alonso de Maldonado a Tayasal, nascose con cura la maschera di Kukulcan, così fondamentale per viaggiare nel passato... perdona la mia lingua, intendevo dire LA TUA maschera.";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "Sì, Kanek aveva finito per ingannare sé stesso. Combinò il più arduo dei rituali, uno che neppure gli antichi avevano mai osato tentare. Nascose la maschera su un’isola appena emersa e riuscì persino a perdere la chiave di Ksocheatem – il cosiddetto Guardiano della Verità.\nDovevo giocare d’astuzia. Il rituale impediva a qualunque vascello con oggetti protetti dai tesori di Taysal di lasciare i Caraibi, scaraventando le navi verso le coste di Ksocheatem. Avevo intenzione di sfruttare proprio questo. Presi abbastanza oro per placare Mendoza. E presi anche un oggetto speciale, protetto dal rito.\nUna nave che trasportasse quell’oggetto sarebbe stata condannata a finire dritta a Ksocheatem, proprio dove si trova la mia maschera. Così salpai e feci in modo che Mendoza sapesse della mia presenza.";
			link.l1 = "  Dunque, sei partito da Tayasal tutto solo?";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "Intendi senza i soldati di Mendoza? Certo. Tutti gli spagnoli furono massacrati qui, a Tayasal. Gli Itza portarono i tesori sulla riva da soli e io raccontai a Mendoza che i soldati erano caduti in un’imboscata dei Miskito. Mi credette, visto che a lui importava soltanto l’oro, non la sorte degli uomini.\nAvevo pianificato di far caricare la nave coi tesori proprio sotto i cannoni del 'Gryffondor', ma è andata anche meglio: il barone decise di spedire tutto in Spagna sotto la mia sorveglianza. Non poteva esserci esito più favorevole, dovevo solo aspettare che la nave superasse il confine invisibile dei Caraibi.\nMa il capitano aveva ordini diversi. Venni a sapere che una squadra speciale doveva ammutinarsi appena avessimo raggiunto l’Atlantico, uccidere l’equipaggio e tutti gli ufficiali. Poi, il capitano doveva riportare l’oro indiano a Mendoza.\nChe bell’esempio della razza bianca, eh, fratello? Ho dovuto rischiare, non sapevo quando sarebbe scoppiato l’ammutinamento. Ma tutto filò come previsto: la tempesta ci colpì appena la 'Santa Quiteria' doppiò il lato orientale di Trinidad e Tobago. La fregata fu spinta di nuovo nei Caraibi, verso Ksocheatem.\nE lì subii il più grande smacco della mia vita: un’onda mi strappò dalla nave e mi ritrovai alla baia di Le Marin, in Martinica, dopo qualche giorno. Dei pescatori mi raccolsero e mi portarono a Le Francois. Ma gli uomini di de Poincy mi presero mentre riprendevo i sensi a casa di Cesar Craig. Il 'Gryffondor' non trovò la 'Santa Quiteria' dove avevo indicato. Il cavaliere de Poincy andò su tutte le furie quando seppe che l’oro indiano era svanito insieme al denaro sottratto al tesoro dell’Ordine e ai suoi risparmi.\nMi fece arrestare. Non poteva uccidermi, però, e non voleva nemmeno: voleva l’oro. Oro! È tutto ciò che la tua gente brama e per cui vive! Fareste qualsiasi cosa per averlo... Mi trovai in un mare di guai: senza maschera, senza un soldo, a marcire in cella.\nFu allora che ti convocai. Sì, fratellino caro, dovevi liberarmi, così avrei potuto compiere il mio destino. E hai fatto un lavoro straordinario. Pare che il latte degli Itza che hai bevuto ti abbia giovato davvero.";
			link.l1 = "Quello che mi chiedo è: su cosa contavi quando sei scappato da Saint-Pierre, eh? Qual era il tuo piano?";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("Voice\English\sharlie\mishelle-05.wav");
			dialog.text = "Sei sempre stato il mio piano, fratello. Kukulcan sa leggere nei cuori degli uomini. La lettera che ti ho lasciato dall’abate doveva spingerti all’azione. E avevo ragione su di te. Ti osservavo fin dal primo incontro con l’Inquisitore di Santiago. Hai fatto tutto per me. Hai forgiato il Guardiano della Verità. Hai fatto sparire i rivali. Hai trovato Ksocheatem. \nIo c’ero, sempre all’ombra dei tuoi passi. Anche se non pensavo saresti arrivato fino a Tayasal. Hai superato tutte le mie aspettative. E ora, con il tuo aiuto, compirò ciò per cui sono nato. Il motivo per cui ho preso carne mortale.";
			link.l1 = "C'è solo una piccola postilla nel tuo ragionamento, caro fratello. Non hai la tua maschera e senza di essa non sei nessuno. Ce l'ho io. E non mi arde certo la voglia di restituirtela. Piuttosto la farei a pezzi che lasciarla finire nelle tue grinfie.";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "Non puoi cambiare ciò che è scritto dal destino. Non ti permetterò di danneggiare il mio artefatto. Lo sento... È con te. E tu sei qui, nel mio tempio, dove la mia potenza è assoluta! Di qui non uscirai mai. È giunta l’ora della tua ultima prova, caro fratello: vediamo quanto vali contro Kukulcan in battaglia!";
			link.l1 = "Suppongo che il tuo corpo mortale possa ancora sanguinare!";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "Ah! Mi fai pena, Charles. È davvero triste, sai? Ma ti meriti una possibilità di affrontare un Dio. Anche se è una follia. Te lo spiegherò dopo, se sopravvivi alla prima recita.";
			link.l1 = "Suppongo che il tuo corpo mortale possa ancora sanguinare!";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "Sembra che i tuoi poteri ti stiano abbandonando, grande Kukulcan... Puoi essere forte quanto vuoi, ma il tuo corpo resta pur sempre mortale!";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = "Penso che questo basti per il divertimento. Sei davvero un maestro di spada e un gran combattente, oserei persino dire il più valoroso guerriero del tuo tempo, ma questa battaglia l’hai persa, "+pchar.name+"...";
				link.l1 = "Stiamo solo...";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "Basta così, caro fratello. Non puoi resistere al potere di Kukulcan quando stringe il suo artefatto! Ti ho lasciato vivere fin troppo, solo per vedere cosa saresti stato capace di combinare davvero.";
			link.l1 = "Merda... Quel colpo finale... Ma di quale artefatto parli? La maschera? Ce l’ho io!";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = "Povero, povero Capitano "+GetFullName(pchar)+"... Sei arrivato fin qui, hai superato ogni pericolo, abbattuto i più forti nemici, solo per essere sconfitto alla fine!.. La maschera di giada che hai trovato dentro la cassa di metallo vicino ai relitti della 'Santa Quiteria' su Ksocheatem è un falso! È solo un’antica maschera del tesoro di Taysal. NON È LA MASCHERA DI KUKULCAN!.\nL’avevo portata qui di persona dopo la mia spedizione fallita, ed è protetta dall’antico rituale. Fu proprio questa maschera a scatenare la tempesta che fece naufragare la Santa Quiteria su Ksocheatem. Aveva anche un secondo scopo: doveva ingannare chiunque fosse arrivato lì in cerca del mio VERO artefatto.";
			link.l1 = "Ma... allora dov’era la vera maschera?! Ho cercato in lungo e in largo per tutto Ksocheatem!..";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "Non l’hai fatto, "+pchar.name+". Il mio artefatto giaceva dall'altra parte dell'isola rispetto alla 'Santa Quiteria', nascosto in un santuario ben sorvegliato. La strada per arrivarci passa per caverne sotterranee. Non è facile da trovare e resta invisibile agli occhi inesperti dei comuni mortali. Eccolo là! Dagli un'ultima occhiata, una buona occhiata...";
			link.l1 = "Non è possibile!";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "Ne hai scampate tante e vinto mille battaglie, fratello. Ma questa l’hai persa, "+pchar.name+"...";
			link.l1 = "E adesso che si fa?";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "Viaggerò direttamente nel decimo secolo, sette secoli indietro. Questo basterà perché la civiltà Maya raggiunga un potere militare e scientifico inespugnabile rispetto alla razza bianca.";
			link.l1 = "E che ne sarà del nostro mondo? Sparirà forse?";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "No. Cambierà. Forse ci sarà un posto anche per te, ma non ricorderai nulla di ciò che è accaduto in questo mondo. Alcuni nati qui non nasceranno mai laggiù, ed è vero anche il contrario. I morti torneranno tra i vivi e i vivi cadranno, in un modo o nell’altro, tutti rinasceranno. Suum cuique, a ciascuno il suo, "+pchar.name+".\nNon temere, fratellino. Non ti accorgerai nemmeno di ciò che è accaduto e accetterai questa nuova realtà come fosse naturale. Solo io, Kukulcan, conserverò i ricordi... Ma basta così! Kanek ha già predisposto tutto per il rituale.\nMi seguirai, "+GetFullName(pchar)+", e assisterai agli ultimi istanti di questa realtà che tanto bramavi proteggere.";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "Le porte del tempo si sono spalancate! Esultate, figli miei, ché siete vicini alla gloria! Forgeremo un nuovo mondo, un mondo dove non ci sarà posto per gli invasori pallidi!\nAddio, "+pchar.name+", e preparati ad accettare il tuo nuovo destino, qualunque esso sia. Suum cuique!";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "Questa battaglia non è ancora finita, mortale. Sei piuttosto esausto e i miei rinforzi stanno arrivando! Restituirai il mio artefatto. Altrimenti lo strapperò dal tuo cadavere, per me non cambia un accidente...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "Urakan! Ti ordino di far fuori quest’uomo all’istante!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "Urakan! Non mi hai sentito? Ripeto: ordino a te e ai tuoi guerrieri di catturare e far fuori quest’uomo!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "Urakan! Ma che diavolo? Kanek! Ripeti il mio ordine a tuo figlio, maledetto!!!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "Tu tradisci la tua gente, Urakan! Hai tremato dinnanzi a tali mutamenti grandiosi! Guerrieri, vi ordino di catturare e mettere a morte non solo quest’uomo che si spaccia per mio fratello, ma anche Urakan il traditore!";
			link.l1 = "Guerrieri, in nome di Cavil e Hurakan vi ordino di restare fermi dove siete, se tenete alla vostra pellaccia! Nessuno di voi sopravviverebbe a схватке с Cavil! Che siano gli dèi stessi a decidere chi tra loro è il più possente su questa terra!";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "Questa giornata migliora di minuto in minuto. Non ti aspettavi proprio una piega simile, eh, fratello? Che siano gli dèi stessi a scegliere chi tra loro è il più possente. E ognuno avrà ciò che gli spetta, Michel. Suum cuique! A ciascuno il suo...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
