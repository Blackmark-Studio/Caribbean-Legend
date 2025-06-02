// Натаниэль Хоук - пиратский барон Марун-Тауна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Cercavi qualcosa?";
			link.l1 = "No, non è nulla.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "diffindoor":
			PlaySound("Voice\English\saga\Nataniel Hawk-02.wav");
			dialog.text = "Ah... chi sei tu, maledizione?.. Khe... (tosse roca e feroce) Maledetta debolezza...";
			link.l1 = "Saluti, Nathaniel. Sei tu Nathaniel Hawk, vero?";
			link.l1.go = "diffindoor_1";
		break;
		
		case "diffindoor_1":
			dialog.text = "Sì, sono io, se posso ancora chiamarmi così. Un tempo ero Nathaniel Hawk, ma ora non sono che un sacco di merda dal volto triste. Al diavolo quella statua! Mi ha succhiato via tutta la vita.";
			link.l1 = "Conosco bene questa sensazione...";
			link.l1.go = "diffindoor_2";
		break;
		
		case "diffindoor_2":
			dialog.text = "Come potresti, figliolo, se nemmeno capisci di cosa parlo? Eh... Sai che vuol dire sentirsi mezzo morto, un vecchio decrepito, quando un attimo fa eri sano e forte?\nNe ho viste di ogni sorta, pensavo che quel tempio indiano che visitai da giovane mi avesse già tolto la capacità di stupirmi... ma questa! Perché non l’ho previsto! Quella maledetta statua pareva identica al vecchio idolo che apriva la porta del tempio!";
			link.l1 = "D'accordo, Nathan, parliamo. Permettimi di presentarmi, io sono "+GetFullName(pchar)+" Primo, ti capisco benissimo perché sono arrivato qui proprio come te – passando per il portale di Kukulcan.";
			link.l1.go = "diffindoor_3";
		break;
		
		case "diffindoor_3":
			dialog.text = "Davvero?! Allora perché tu sembri in ottima forma? O forse quel… Kukulcan ha fatto danni solo a me?";
			link.l1 = "Occhio di Serpente, lo sciamano Miskito che ti ha aiutato a scappare, mi ha dato una pozione così potente che mi sono ripreso appena sveglio a San Agostino. Mi ha rimesso in piedi come nuovo, parola mia. Sono certo che Occhio di Serpente potrà aiutare anche te. Basta solo portarti da lui.";
			link.l1.go = "diffindoor_4";
		break;
		
		case "diffindoor_4":
			dialog.text = "Ah, quell’indiano! Una pozione? E perché non ne ha data una anche a me?";
			link.l1 = "Ha detto che non c’era tempo. Ti stavano alle calcagna e l’unica cosa che poteva fare era indicarti la via di fuga – il portale.";
			link.l1.go = "diffindoor_5";
		break;
		
		case "diffindoor_5":
			PlaySound("Voice\English\saga\Nataniel Hawk-01.wav");
			dialog.text = "Fuga? Oh... Non vedi in che stato mi trovo? Non riesco nemmeno a reggere una sciabola. Come potresti chiamare questo una fuga? Grazie al Cielo, ci sono ancora brave anime in questo mondo. Ole, che il buon Dio lo protegga... Conosci Ole?";
			link.l1 = "Sì. In realtà, è stato lui a parlarmi di te, mi ha raccontato di come ti dava da mangiare topi e di come tracanni vino, fiasco dopo fiasco...";
			link.l1.go = "diffindoor_6";
		break;
		
		case "diffindoor_6":
			dialog.text = "Schiatterò prima d’una candela accesa se non tracanno del rum. È l’unica cosa che mi tiene in vita. Rum...";
			link.l1 = "Ti senti ancora così male? Proprio come dopo quella maledetta teletrasportazione?";
			link.l1.go = "diffindoor_7";
		break;
		
		case "diffindoor_7":
			dialog.text = "Ebbene, non mi sento proprio lo stesso... Ma nemmeno meglio, a dirla tutta. Dimmi, compare, perché mai t’è saltato in testa cercar il vecchio Nathan? Per tutti i diavoli, che ci fai su questa caracca fradicia? Solo per scambiare due chiacchiere con me?";
			link.l1 = "In realtà sì. Non ci crederai, ma tutta questa storia con la teletrasportazione era solo per trovarti. Lavoro per la Fratellanza della Costa e rappresento Jan Svenson.";
			link.l1.go = "diffindoor_8";
		break;
		
		case "diffindoor_8":
			dialog.text = "Maledizione... il Diavolo della Foresta? Argh... Sei venuto a darmi il colpo di grazia? Davvero, no? Parli troppo per essere un sicario. Ti prego – non farmi soffrire. Se ti hanno mandato a cavare qualcosa da me – ti dirò tutto da solo, non ho nulla da nascondere.";
			link.l1 = "Cosa vuoi dire? Ah-ah, capisco. Tu, proprio come Danielle, pensi che sia stato Svenson a preparare quell'agguato contro di te nella selva. Posso assicurarti che Jan non c'entra nulla. Anzi, sta dalla tua parte e si preoccupa parecchio per la tua sparizione.";
			link.l1.go = "diffindoor_9";
		break;
		
		case "diffindoor_9":
			dialog.text = "Davvero? Diavolo, son proprio contento di sentirlo. E già mi chiedevo... ma chi diavolo è stato? La mia squadra è stata spazzata via in pochi minuti. Ci aspettavano. Avevano persino cannoni di bordo! Hanno falciato metà dei miei uomini con la mitraglia e poi ci hanno finiti coi moschetti...";
			link.l1 = "A dir la verità, non so i dettagli, ma sono certo che dietro a tutto questo c’è Jackman. Troppe coincidenze, prima Blaze, poi tu... Jackman vuole impadronirsi del potere e fa fuori chiunque gli intralci la rotta. Adesso comanda lui a Maroon Town al posto tuo.";
			link.l1.go = "diffindoor_10";
		break;
		
		case "diffindoor_10":
			dialog.text = "Jackman? Maledetto bastardo! Eh... la Fratellanza s’è sfasciata negli ultimi anni, un tempo era tutt’altra cosa. Zachariah s’è dato alla follia religiosa, Tyrex se ne infischia di tutto e Barbazon pensa solo agli dobloni. Venti anni fa era tutto diverso...";
			link.l1 = "Come ti hanno preso? Raccontami tutto, dai.";
			link.l1.go = "diffindoor_11";
		break;
		
		case "diffindoor_11":
			dialog.text = "Non c'è nulla d'interessante da raccontare! Come ho già detto, quei furfanti avevano tutto pianificato. Agivano con ordine, coordinati, seguendo chiaramente gli ordini di qualcuno. Avrebbero potuto farmi la pelle cento volte, ma non l'hanno fatto. Mi volevano vivo. Mi hanno portato in una miniera abbandonata e rinchiuso in una delle baracche. 'Finché non arriva il capo', dicevano. Pensavo che il capo fosse Svenson, ma sembra che sia Jackman a comandare. Non so cosa volesse da me, ma sono sicuro che dopo una chiacchierata con lui, non sarei rimasto in vita a lungo.";
			link.l1 = "Non ne dubito affatto. Svenson è convinto che Jackman abbia fatto fuori Blaze Sharp... Ma tu come sei riuscito a svignartela?";
			link.l1.go = "diffindoor_12";
		break;
		
		case "diffindoor_12":
			dialog.text = "Quel diavolo d’Indiano Occhio di Serpente riuscì in qualche modo a introdursi nella miniera. Da quel che ho capito, i Miskito non vanno d’accordo coi banditi. Eppure, Occhio di Serpente organizzò la mia fuga per qualche ragione. Scavò un cunicolo fino a me, entrò, mi tagliò le corde e fuggimmo nella giungla.\nVoleva portarmi al suo villaggio, dai Miskito. Ma pare che Jackman mi volesse a tutti i costi: avevano messo su una gran battuta di caccia. Ci tallonavano senza tregua. Occhio di Serpente faceva di tutto per depistarli, ma riuscivano sempre a ritrovare le nostre tracce. Avevano segugi dannatamente bravi, su questo non ci piove.\nEravamo quasi arrivati al villaggio di Occhio di Serpente quando finalmente ci acciuffarono. A quel punto non mettevo qualcosa sotto i denti da due giorni e ormai ero allo stremo, con una gamba pure malconcia. Era mezzanotte e ricordo ancora quanto brillava la stella sopra la statua... Occhio di Serpente mi disse che l’unica mia speranza era raggiungere l’idolo e toccarlo.\nPensavo fosse completamente fuori di testa, ma si sa che chi annega si aggrappa a tutto. Zoppicai fino alla statua, la sfiorai... e da lì cominciarono a succedere cose da non credere!";
			link.l1 = "Non serve che tu vada avanti, so già come sono andate le cose dopo.";
			link.l1.go = "diffindoor_13";
		break;
		
		case "diffindoor_13":
			dialog.text = "Mi ritrovai nella stiva fradicia di qualche nave sfasciata. Ero mezzo morto. Non potevo camminare, solo strisciare. Ogni minuto peggioravo. Ole arrivò proprio all’ultimo. Mi versò giù una mistura caraibica che sapeva di schifo, qualcosa tra un antidoto e un elisir curativo. Poi mi diede del rum.\nSubito mi sentii meglio. Poi trovò un vecchio tronco e mi trascinò fin qui. Vivo qui da un po’, ma non saprei dire quanto – ho perso la nozione del tempo.";
			link.l1 = "Andrà tutto bene, Nathan. Io e Svenson abbiamo grandi piani e il tuo ruolo è di grande importanza. Devi tornare al tuo posto a Maroon Town e ci occuperemo di quella feccia di Jackman.";
			link.l1.go = "diffindoor_14";
		break;
		
		case "diffindoor_14":
			dialog.text = "Maroon Town? E come diavolo pensi che possa funzionare? Guardami, sono un relitto inzuppato di rum! Buono a nulla... No, i miei anni di comando su Maroon Town sono spariti per sempre. Sono intrappolato su questo maledetto cimitero di navi. Quanto pensi che resisterò? Un mese, due, un anno?\nE poi finirò disteso su queste assi marce, e Ole getterà quel che resta di Nathaniel Hawk in mare. La cosa peggiore è che non rivedrò mai più la mia Dannie. Eh, è finita, compare.";
			link.l1 = "Non essere così menagramo. Ti tirerò fuori di qui.";
			link.l1.go = "diffindoor_15";
		break;
		
		case "diffindoor_15":
			dialog.text = "Come pensi di tirarmi fuori di qui? E come ce ne andiamo da questo posto? Non ci sono navi. Vuoi forse costruire una zattera?";
			link.l1 = "No. Me ne andrò da qui esattamente come sono arrivato. So dov’è la statua... più o meno. La troverò e poi tornerò per te e Shark Dodson. Dopo ti porteremo da Occhio di Serpente. Lui ti rimetterà in sesto.";
			link.l1.go = "diffindoor_16";
		break;
		
		case "diffindoor_16":
			dialog.text = "Che hai detto? Shark Dodson? Anche Steve si trova qui? Che posto bizzarro...";
			link.l1 = "Sì, è qui. È il 'governatore' di quest'isola, per così dire. Gli ho chiesto di te, ma non ne sa un accidente.";
			link.l1.go = "diffindoor_17";
		break;
		
		case "diffindoor_17":
			dialog.text = "E non dovrebbe. Non voglio che mi veda in queste condizioni. Hai detto che lo sciamano mi guarirà... Faccio fatica a crederci. Hai nominato anche Dannie... L’hai vista?";
			link.l1 = "Sì.   È stata lei a trovarmi a Blueweld. Aveva origliato la mia chiacchierata con Svenson e ha capito che Jan non aveva intenzione di ucciderti, che anzi sta tramando contro Jackman. Si è imbarcata sulla mia nave come ufficiale per aiutarmi a rintracciarti.";
			link.l1.go = "diffindoor_18";
		break;
		
		case "diffindoor_18":
			dialog.text = "Ah, mia cara Dannie! Non è cambiata... sempre impulsiva come da giovane... Non puoi nemmeno immaginare quanto desideri vederla e stringerla tra le braccia proprio adesso! Ho riflettuto tanto mentre giacevo qui. Vedi, compare, quando ti trovi vicino alla morte tutto appare con occhi diversi. Ho passato così poco tempo con mia moglie!\nScorribande sul mare, affari ufficiali della Fratellanza, governare Maroon Town. E lei mi ha sempre sostenuto in tutto: restava sola per settimane, litigava con altri filibustieri mentre ero via, comandava la nostra nave... La mia Dannie è la miglior donna del mondo! E io... avrei dovuto dirle più spesso che la amo!\nRicordo il giorno in cui decidemmo di restare insieme! Anzi, fu proprio quel giorno che incontrai e affrontai per la prima volta cose soprannaturali. Tutto accadde per colpa di quell’idolo maledetto che sembrava proprio le statue. Non ti dispiace ascoltare una storia, vero? È piuttosto interessante.";
			link.l1 = "Ma che! Dimmi tutto!";
			link.l1.go = "story";
			link.l2 = "Nathan, non abbiamo tempo per le chiacchiere. Raccontamelo dopo, quando staremo seduti al villaggio Miskito con una bottiglia di vino.";
			link.l2.go = "diffindoor_19";
		break;
		
		case "story":
			dialog.text = "Era venticinque anni fa... Ero giovane, impetuoso e irrequieto. I Caraibi erano il mio terreno di gioco. Già allora conoscevo Dannie. Mi piaceva, davvero, e il sentimento era reciproco. Ma spesso litigavamo, ci punzecchiavamo e ci prendevamo in giro. Sciocchezze da ragazzi... Credo che fossimo un gran divertimento per i rispettabili marinai dell’epoca!\nComunque, in qualche modo io e Dannie ci ritrovammo invischiati nella stessa faccenda. Avevamo trovato una mappa di Khael Roa, e ci dissero che lì si trovava l’oro degli indiani. Avevamo anche scovato uno strano idolo d’oro, una piccola copia della sommità delle statue.\nL’idolo era maledetto, risucchiava la forza vitale da chi lo portava con sé. Ma ci serviva quella dannata reliquia per arrivare al tesoro nascosto nel tempio. L’unico problema era che non avevamo la minima idea di come usarlo davvero. Io e Dannie salpammo verso l’isola. C’era un tempio antico, coperto di erba e alberi. Quando entrammo, ci ritrovammo in un enorme labirinto.\nSiamo riusciti a trovare la strada giusta e arrivammo al centro del labirinto. Pensavamo fosse un vicolo cieco, ma quando la disperazione cominciava a prendere il sopravvento, vedemmo una strana piattaforma con una piccola fessura e un disegno. Ho infilato l’idolo in quella fessura e...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "idol";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_1";
		break;
		
		case "story_1":
			dialog.text = "La piattaforma di pietra sprofondò di qualche pollice e una delle pareti si rivelò essere un passaggio segreto. L'idolo rimase incastrato nella piattaforma, non riuscii a tirarlo fuori. Alla fine arrivammo in una sala gigantesca. Che spettacolo meraviglioso!\nLa struttura più sontuosa che abbia mai visto. Incisioni sulle pareti, statue colossali... Abbiamo perlustrato tutta la sala, ma non c'era traccia di tesori.";
			link.l1 = "Eh, capita spesso a gente come noi. Tanto sbattimento e alla fine restiamo con un pugno di mosche...";
			link.l1.go = "story_2";
		break;
		
		case "story_2":
			dialog.text = "Non fu certo per nulla. Dopotutto, siamo entrati in una sala del trono con una statua enorme di un uccello in fondo. C’era una luce mistica vicino alla statua, proprio come quella che brilla sull’idolo a mezzanotte. Ci siamo avvicinati e abbiamo visto una sfera fluttuante splendida. Ti giuro, ti dico solo la pura verità!\nEra reale, eppure sembrava fatta d’aria. Mentre io rimuginavo, Dannie – ah, quella pazza scavezzacollo – toccò la sfera. Quella cominciò a brillare ancora di più, e alla fine si trasformò in un piccolo oggetto tra le sue mani...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "temple";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_3";
		break;
		
		case "story_3":
			dialog.text = "Pareva che avessimo commesso un sacrilegio. Il tempio prese vita: tutto intorno a noi cominciò a muoversi, le pareti tremavano e ogni cosa crollava. Era come se avessimo risvegliato tutti i demoni indiani, e ora riversavano su di noi tutta la loro furia...";
			link.l1 = "Per tutti i diavoli!";
			link.l1.go = "story_4";
		break;
		
		case "story_4":
			dialog.text = "È difficile crederci, lo so. Ma...";
			link.l1 = "Sei mesi fa ti avrei dato del bugiardo senza pensarci. Ma ormai vivo da abbastanza tempo nei Caraibi per capire che non ho motivo di dubitare di te. Continua. Come hai fatto a cavartela?";
			link.l1.go = "story_5";
		break;
		
		case "story_5":
			dialog.text = "Siamo corsi fuori dal tempio e, per nostra fortuna, riuscimmo a salire sulla nave in tempo. Ordinai di salpare l’ancora: volevamo levarci da quel maledetto posto il prima possibile.";
			link.l1 = "Eh! Quindi alla fine hai trovato solo qualche strano ciondolo invece di veri tesori? Che bel baratto, ahah... E hai capito almeno a cosa serve? O era solo una robaccia inutile?";
			link.l1.go = "story_6";
		break;
		
		case "story_6":
			dialog.text = "Aspetta un attimo. La storia non è ancora finita. Dannie aveva l’artefatto e appena decidemmo di andare in cabina a studiarlo, il cielo si fece scuro e apparve una nave. Santo cielo! Era...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "blackpearl";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_7";
		break;
		
		// вот тут делаем развилку, в зависимости прошёл ли игрок Калеуче
		case "story_7":
			dialog.text = "... Van der Decken in persona!!";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Van der Decken? Mh...";
				link.l1.go = "story_8_1";
			}
			else
			{
				link.l1 = "E chi sarebbe costui?";
				link.l1.go = "story_8";
			}
		break;
		
		case "story_8":
			dialog.text = "Non hai mai sentito parlare dell’Olandese Volante?";
			link.l1 = "Chi non ha mai sentito parlare dell'Olandese Volante! Io ho già incontrato un olandese e spedito il suo capitano dritto all’inferno marino. Era solo un pirata qualunque che aveva addobbato la sua nave con cianfrusaglie da ballo in maschera: alghe e vele sbrindellate.";
			link.l1.go = "story_9";
		break;
		
		case "story_8_1":
			dialog.text = "Sì, ma quello era Van der Decken in persona, il capitano dell’Olandese Volante!";
			link.l1 = "Interessante. Continua pure. Come hai fatto a cavartela?";
			link.l1.go = "story_11";
		break;
		
		case "story_9":
			dialog.text = "Eheh, amico... Hai affondato qualche buffone, ma io parlo del vero Olandese Volante. Un vascello da guerra enorme. Dio ti scampi dall’incontrarlo mai in mare aperto. Il suo capitano Van der Decken e l’equipaggio furono maledetti a navigare senza pace per l’eternità.\nRicordo le sue vele nere sbrindellate, la ciurma di morti in piedi sul ponte con le lame sguainate e il capitano stesso – uno scheletro raccapricciante con un tricorno nero... Gesù...";
			link.l1 = "Mi stai dicendo la verità?";
			link.l1.go = "story_10";
		break;
		
		case "story_10":
			dialog.text = "Posso giurare sulla Bibbia che non sto mentendo... Un incontro con l’Olandese Volante significa solo morte certa. È potente, maledettamente potente: una sola bordata dei suoi cannoni affonda perfino una fregata pesante con tutto l’equipaggio... ma la cosa peggiore è: come diamine combatti contro i morti che camminano?";
			link.l1 = "Ma sei sopravvissuto a quest’incubo!";
			link.l1.go = "story_11";
		break;
		
		case "story_11":
			dialog.text = "Tutto questo lo devo alla mia adorata Dannie e all’artefatto indiano che strappammo dal tempio. Avevo dato l’ordine di prepararsi alla battaglia, ma sapevo che era la nostra ora. Il ‘Vascello Fantasma’ puntava dritto verso di noi, e io già vedevo la sua ciurma maledetta e Van der Decken in persona sul ponte. La nave cominciò ad allineare i suoi cannoni contro di noi, ma...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "artefact";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_12";
		break;
		
		case "story_12":
			dialog.text = "Dannie sollevò l’artefatto e lo lanciò. Non avevo la minima idea del perché avesse fatto una simile follia. Borbottò qualcosa riguardo al suo sesto senso femminile... L’artefatto tornò a essere una sfera luminosa ed esplose, massacrando la nave fantasma e fiaccando lo spirito della sua ciurma. Ordinai di aprire il fuoco contro l’Olandese.\nLa prima bordata li fece vacillare. Attaccammo di nuovo, sventrando il loro scafo marcio una seconda volta, appena prima che si riprendessero dall’effetto dell’artefatto e iniziassero a rispondere al fuoco...";
			link.l1 = "Quindi, alla fine hai dovuto menar le mani comunque?";
			link.l1.go = "story_13";
		break;
		
		case "story_13":
			dialog.text = "Proprio così. E ti giuro che è stata la battaglia più dura della mia vita. Quella maledetta bagnarola stava per affondare, eppure sono riusciti a sfasciarmi mezza carena prima che li spedissimo all’inferno facendo saltare la loro dannata santabarbara.";
			link.l1 = "Allora, l’hai mandato a fondo? Hai affondato l’Olandese Volante?";
			link.l1.go = "story_14";
		break;
		
		case "story_14":
			dialog.text = "Sì, maledizione! L’ho fatto davvero!..";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "ending";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_15";
		break;
		
		case "story_15":
			dialog.text = "Quella maledetta nave è affondata. Il sole ha ricominciato a splendere e il cielo si è fatto limpido. Ed è stato allora che finalmente ci siamo sentiti felici... ah, non puoi nemmeno immaginare quanto. Avevamo fregato la morte in persona. Momenti simili stringono i cuori, fratello. E così abbiamo fatto quel che avremmo dovuto fare molto prima di quell’incontro: ci siamo abbracciati, baciati, confessato il nostro amore e giurato di restare insieme per l’eternità.";
			link.l1 = "E siete ancora insieme...";
			link.l1.go = "story_16";
		break;
		
		case "story_16":
			dialog.text = "Sì, lo siamo. Io e Dannie ci siamo sposati e non l’ho mai rimpianto. Non troverai moglie o compagna d’arme migliore.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Dunque, ora finalmente so chi sia davvero quel capitano misterioso che è riuscito ad affondare il 'Vascello Fantasma'... Sei un vero eroe!";
				link.l1.go = "story_17_1";
			}
			else
			{
				link.l1 = "Allora, siete davvero degli eroi voi due? Siete riusciti ad affondare la famigerata nave fantasma. Aspetta! Hai detto che l’Olandese Volante sta ancora navigando... Ma com’è possibile, se giace ormai sul fondo del mare?";
				link.l1.go = "story_17";
			}
		break;
		
		case "story_17":
			dialog.text = "Ehi, compare, non sai proprio nulla... Puoi mandare a fondo Van der Decken, ma non puoi ammazzarlo. La maledizione che pesa su lui e sul suo equipaggio è troppo potente, ben più forte della morte stessa...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_17_1":
			dialog.text = "Eroe potrei anche esser chiamato, ma Van der Decken non si può ammazzare. La maledizione che grava su lui, sulla sua ciurma e sul suo vascello, è più potente della morte stessa...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_18":
			dialog.text = "Ogni volta che affondi la nave, il suo equipaggio rattoppa lo scafo, la rimette in acqua e riprende il suo viaggio senza fine.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Lo so, Nathaniel, lo so. Ma ormai, l’Olandese Volante non darà più fastidio a nessuno.";
				link.l1.go = "story_22";
			}
			else
			{
				link.l1 = "Ah, sai, sembra una favola. Rimettere insieme una nave sfasciata e affondata...";
				link.l1.go = "story_19";
			}
		break;
		
		case "story_19":
			dialog.text = "La gente ha visto la nave molte volte dopo che l’abbiamo affondata… Sta a te decidere se credere a queste storie.";
			link.l1 = "E dove si trova quell’isola col tempio, quella da cui hai preso l’artefatto?";
			link.l1.go = "story_20";
		break;
		
		case "story_20":
			dialog.text = "Non è segnato sulle carte ed è nascosto da qualche parte a oriente, nel mar dei Caraibi. Ho lasciato una mappa dell’isola a Maroon Town, ma come ben sai, adesso non posso certo veleggiare fin laggiù. E a dirla tutta, non ne ho neppure voglia. L’unica cosa che ricordo è il suo nome: Khael Roa...";
			link.l1 = "Che storia affascinante. Mi piacerebbe proprio scovare quell’isola!";
			link.l1.go = "story_21";
		break;
		
		case "story_21":
			dialog.text = "Oh, non te lo consiglio... Io di certo non ci torno, su questo puoi scommetterci.";
			link.l1 = "Mi piacerebbe visitarlo comunque... Va bene, grazie per la tua storia interessante! Ora so di più su tua moglie. Siete entrambi leggende viventi!";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
			pchar.questTemp.NatanStory = "true";
		break;
		
		case "story_22":
			dialog.text = "Che stai suggerendo, compare? Non ti ho appena detto che non può essere fatto fuori?";
			link.l1 = "Nathaniel, sono salpato verso Khael Roa. Ho visitato il tempio dei Chavins, dove tu, Danielle e un vecchio ci siete stati venticinque anni fa. L’artefatto che allora prendeste dal tempio si chiamava ‘globo del sole nascente’. Fu proprio quell’artefatto ad attirare su di voi l’attenzione dell’Olandese Volante. Pare che il suo capitano avesse un debole per i manufatti dei Chavins.";
			link.l1.go = "story_23";
		break;
		
		case "story_23":
			dialog.text = "Sei stato a Khael Roa? Ma non può essere! Mi stai davvero dicendo la verità?";
			link.l1 = "Lo giuro. Quando mi hai parlato del labirinto e della statua dell'enorme uccello, ho subito capito di che luogo si trattava. Lo sciamano caribico Tuttuathapak mi ha raccontato delle tue imprese. È stato lui a indicarmi quell’isola. Si trova a est di Saint-Christophe. È piccolissima, con la forma d’un anello. Tutt’intorno scogli, e al centro una caletta. C’è solo un sentiero invaso dalla giungla che porta a un tempio costruito come una piramide.";
			link.l1.go = "story_24";
		break;
		
		case "story_24":
			dialog.text = "Sì! Questa è Khael Roa. Ma perché diavolo ci sei andato?";
			link.l1 = "Per spezzare la maledizione del Caleuche... o meglio, della 'Nave Fantasma'. In verità, il suo nome era 'Cuore Volante', e il capitano si chiamava Balthazar de Cordes. Cinquant’anni fa fu maledetto da Yum Cimil, il dio indiano della Morte. Ho recuperato il teschio di giada di Yum Cimil, che Balthazar aveva rubato dal tempio tempo addietro, e l’ho rimesso sul piedistallo davanti a quella statua di condor...";
			link.l1.go = "story_25";
		break;
		
		case "story_25":
			dialog.text = "";
			link.l1 = "...restituendo il teschio ho spezzato la maledizione del Caleuche. E siccome avevo con me altri due amuleti Chavins, lei mi ha assalito vicino all’isola, proprio come successe a te allora. Ma senza la maledizione, Balthazar non era più immortale, proprio come predisse Tuttuathapak. Così... la 'Olandese Volante' non naviga più. Me ne sono occupato io di persona.";
			link.l1.go = "story_26";
		break;
		
		case "story_26":
			dialog.text = "Per mille fulmini! Sono sbalordito! Tu... Non stai prendendo in giro il vecchio Nathan, vero? No, lo vedo nei tuoi occhi che dici la verità! Sei un vero eroe!";
			link.l1 = "Eroe o meno, ho vissuto anch’io le mie avventure, proprio come te. Ma dai, sono certo che torneremo a rievocare il passato più d’una volta, visto che ormai ci lega una faccenda comune.";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;
		
		case "diffindoor_19":
			dialog.text = "Mi abbandonerai adesso, compare?";
			link.l1 = "Sì, Nathan. Ti prego, resisti finché non torno. Stammi bene. E soprattutto, resta vivo finché non sarò di nuovo qui e tutto si sistemerà. La Confraternita della Costa ha bisogno di te, Danielle ha bisogno di te.";
			link.l1.go = "diffindoor_20";
		break;
		
		case "diffindoor_20":
			dialog.text = "Dannie fa parte del tuo equipaggio adesso? Ti prego, veglia su di lei. Non è cambiata affatto dai tempi della giovinezza, è sempre la solita testa calda e non esiterà a buttarsi all’inferno. Dille che le voglio un bene dell’anima...";
			link.l1 = "Certo che lo farò. Torneremo insieme per te, te lo giuro, Nathan. Tieni duro e non abbatterti. Ole si prenderà cura di te. A presto!";
			link.l1.go = "diffindoor_21";
		break;
		
		case "diffindoor_21":
			DialogExit();
			LAi_SetGroundSitTypeNoGroup(npchar);
			NextDiag.CurrentNode = "diffindoor_wait";
			pchar.questTemp.LSC.NatanTalk = "true"; // атрибут - разговор с Натаном состоялся
			AddQuestRecord("BaronReturn", "10");
			npchar.greeting = "nathaniel_1";
		break;
		
		case "diffindoor_wait":
			dialog.text = "Ah, sei tu, "+pchar.name+"  Non hai ancora lasciato l’isola?";
			link.l1 = "Non temere, Nathan, tutto fila come previsto. Ora riposa.";
			link.l1.go = "exit";
			NextDiag.TempNode = "diffindoor_wait";
		break;
		
		case "danny":
			PlaySound("Voice\English\saga\Nataniel Hawk-03.wav");
			dialog.text = "Danielle!.. Dannie! Mia Dannie!..";
			link.l1 = "...";
			link.l1.go = "danny_1";
		break;
		
		case "danny_1": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = "danny_2";
		break;
		
		case "danny_2":
			dialog.text = "Grazie, amico mio. Grazie per tutto, e soprattutto per la mia Dannie...";
			link.l1 = "Sei il benvenuto, Nathan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "danny_2";
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = "Guarda un po' chi ci è capitato fra i piedi! È "+GetFullName(pchar)+"  in persona! Vieni, vieni pure, amico! Come va?";
			link.l1 = "Sto bene. E tu, Nathan? Vedo che la malinconia è sparita. Hai un bell’aspetto. Occhio di Serpente si è comportato da vero lupo di mare!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Sì, il tuo sciamano è davvero un mago. Mi sento persino meglio di prima di quella maledetta teletrasportazione! Mi pare d’esser ringiovanito di dieci anni!"+pchar.name+", Ti devo moltissimo. E sono davvero colpito: hai aiutato un perfetto sconosciuto, attraversato quel maledetto portale, strappandomi dalle grinfie della morte, riportandomi da mia moglie! \nE persino di più! Ci hai restituito la nostra nave e la nostra casa. Sei ormai il nostro più caro amico. Per sempre. Se mai avrai bisogno di qualcosa – sai a chi rivolgerti! Maroon Town ti offrirà sempre protezione, sostegno e rifugio quando ne avrai bisogno. \nTutto il villaggio combatterà al tuo fianco se sarai in pericolo. Nei tempi di pace qui troverai amicizia, il miglior rum, un letto morbido e un posto dove riposare le ossa stanche. Dannie ed io ce ne assicureremo, te lo prometto.";
			link.l1 = "Grazie, barone! Son davvero lieto di vederti in buona salute e... in compagnia di Dannie.";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			dialog.text = "Attendevo la vostra visita, "+pchar.name+", e ho preparato un dono – un’arma rara e potente. Forse un giorno ti troverai a dover abbattere una folla di canaglie con un solo colpo, e questo mortaio da mano ti tornerà utile. La ‘sclopetta’ spara granate speciali, così ti ho scritto anche le istruzioni per fabbricarle. Tieni, prendi.";
			link.l1 = "Che splendida arma! Grazie!";
			link.l1.go = "marun_town_3";
		break;
		
		case "marun_town_3":
			GiveItem2Character(pchar, "grape_mushket"); 
			GiveItem2Character(pchar, "recipe_grenade"); 
			Log_Info("You have received a hand mortar");
			Log_Info("You have received a grenade instruction");
			PlaySound("interface\important_item.wav");
			dialog.text = "Vieni a trovarci più spesso, "+pchar.name+"! Dannie ed io saremo sempre lieti di vederti quando vorrai.";
			link.l1 = "Sarà un piacere per me. Presto mi vedrai, stanne certo!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "marun_town_4":
			dialog.text = "Ah, mio buon amico "+GetFullName(pchar)+"Avanti, avanti, Capitano! Come va? Serve una mano?";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
			{
				link.l2 = "Nathan, sono venuto da te per una faccenda della massima importanza. Ti ricordi quando mi raccontasti, sull’Isola delle Navi Abbandonate, di te e Dannie che vi intrufolaste in un tempio indiano e mandaste a picco il ‘Vascello Fantasma’?";
				link.l2.go = "caleuche";
			}
			link.l1 = "Grazie, sto bene. Volevo solo vedervi tutti e due.";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "caleuche":
			dialog.text = "Ma certo che sì.";
			link.l1 = "Devo arrivare su quell'isola col tempio. Mi serve trovarla a tutti i costi. Hai detto che avevi una mappa. Puoi darmi le coordinate?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Oh, amico, questa è un’impresa assai rischiosa, sai... il tempio di Khael Roa è maledetto. Se solo sapessi chi infesta quei corridoi...";
			link.l1 = "Al momento è abitata da mostri assai più spaventosi di quelli che hai visto allora. Eppure ci andrò lo stesso.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Non mi perdonerei mai se dovessi lasciarci la pelle laggiù. "+pchar.name+", Ti scongiuro: lascia perdere questa impresa! Inoltre, è proprio lì che si vede più spesso l’Olandese Volante...";
			link.l1 = "L’ho già incontrata, e so come seminarla. Nathan, per favore, dammi le coordinate di Khael Roa e raccontami tutto ciò che sai su quel tempio, oltre al fatto che sia infestato da indiani non morti.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Ahimè... non posso dirti di no, ma... non immagini nemmeno cosa abbiamo passato io e Dannie laggiù! Khael Roa si trova a est di Antigua. Ho trovato la sua mappa appena tornato a Maroon Town, è a... (guarda) le coordinate: 19 gradi 32' Nord, 62 gradi 25' Ovest.";
			link.l1 = "Segnerò il posto sul mio diario... Grazie, Nathan!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "You can thank me later. Now the details. The island of Khael Roa is a ring of rocks with a cove inside. Seek for the passage between the crags - it's fairly deep there. In the cove, you should cast anchor and disembark at the beach. Look for an old path heading deeper into the island - there's only one there. It will lead you to an Indian pyramid - this is the temple you seek.\nThe island itself is quiet, but the temple is crawling with abominations of all sorts. The entrance is located at the top of the pyramid. There will be three passages inside; you should take the middle one. Then you walk down the corridor and you will find a platform with four entrances or exits. This is where the temple creatures attacked me for the first time, so you should be careful.\nThen there is a labyrinth. It's very complex, and I, for the life of me, can't remember the right route. There is a multitude of foul creatures in the labyrinth. You must kill them all, then walk up to a hall with two entrances, six columns and a platform with nine stone slabs. This is the vestibule of the sanctuary. Its stone wall is closed, and I have no idea how you're going to open it.\nThere is some kind of mechanism, but I swear to God that I have no clue how it functions! I used an idol as a key. I inserted it into the central slab, and the door opened. But you don't have such an idol, so you'll have to figure out how this mechanism functions.";
			link.l1 = "D'accordo, farò del mio meglio per capirci qualcosa. E il rifugio?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Il santuario è una sala immensa dal soffitto altissimo e grandi scalinate di pietra. Non puoi usarle – sono troppo vecchie e quasi tutte crollate. Ma i costruttori del tempio, a quanto pare, erano anche gran stregoni. Ci sono portali, come quelli di Kukulcan, che ti trasportano da un punto all’altro.\nLi riconoscerai subito – paiono vortici colorati. Ce ne saranno due al primo piano, ma uno è una trappola, quindi occhio! Solo quello giusto ti farà salire al secondo piano. Lì dovrai trovare un altro portale per salire ancora, e infine dritto nel cuore del tempio!\nLà, ai piedi della grande statua dell’uccello, fu posato quell’artefatto magico che io e Dannie avemmo con noi. E già ti narrai quel che accadde dopo.";
			link.l1 = "Terrò a mente ciò che mi hai appena detto. Grazie, Nathaniel. Mi hai dato un bel aiuto.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Abbi cura di te, "+pchar.name+" I corridoi e il labirinto del tempio traboccano di minacce. Basterà un passo falso per restarci rinchiuso in eterno.";
			link.l1 = "Praemonitus praemunitus, amico. Chi è avvisato è mezzo salvato. Ora devo andare. Ci si rivede!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Buona fortuna, "+pchar.name+"!";
			link.l1 = "Grazie, compare!";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NatanStory");
			DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
			AddQuestRecord("Caleuche", "35");
			NextDiag.CurrentNode = "marun_town_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
