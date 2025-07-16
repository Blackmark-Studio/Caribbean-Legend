// Соломон Шнеур - старый еврей
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
//--------------------------------------за Голландию------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyFather")
				{
					dialog.text = "Cosa vuoi da questo vecchio ebreo, giovanotto?";
					link.l1 = "Solomon, devi spremerti le meningi e ricordare quell’isola sperduta dove hai fatto naufragio. Lì, hai nascosto un bel tesoretto. Ho parlato con tua figlia. Il mio capo, Lucas Rodenburg, mi ha dato mano libera per agire a vantaggio della tua famiglia. A mio avviso, la cosa più urgente per te adesso è recuperare il patrimonio di casa tua, e senza il mio aiuto, di quell’oro non sentirai neppure l’odore.";
					link.l1.go = "SolomonBonanza";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Oh, giovanotto mio, sei proprio tu? Non hai forse una buona novella per me? Siete di nuovo voi cristiani a venire a tormentare questo povero vecchio ebreo con le vostre domande?";
					if (CheckCharacterItem(pchar, "SkullAztec"))
					{
						link.l1 = "Ho trovato l’isola, anche se non è stato affatto facile. Ho recuperato anche il tuo forziere con il denaro e questo teschio. Immagino che sia il cranio di quel tuo nonno-capostipite di cui blateravi tanto.";
						link.l1.go = "SolomonBonanza_2";
					}
					link.l2 = "Ho trovato l'isola, anche se non è stato affatto facile. Ho trovato pure il tuo baule con il denaro. Ma dentro non c'erano teschi.";
					link.l2.go = "SolomonBonanza_3";
					link.l3 = "No, non ho domande al momento.";
					link.l3.go = "exit";
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "GiveLucasMoney" && GetQuestPastDayParam("questTemp.HWIC.Holl.LucasMoney") > 7)
				{
					dialog.text = "Oh, giovanotto mio, sei tu? Hai forse qualche buona novella da darmi? O sei venuto di nuovo a tormentare questo povero vecchio ebreo con le tue domande?";
					link.l1 = "Ho trovato l’isola, anche se non è stato affatto facile. Ho pure recuperato il tuo forziere col denaro. Ecco qui.";
					link.l1.go = "SolomonBonanza_5";
					break;
				}
				dialog.text = "Salve, giovanotto. Che cosa vuoi da questo povero vecchio giudeo?";
				link.l1 = "Buon pomeriggio. No, niente di che, sono venuto solo a salutare.";
				link.l1.go = "exit";
				break;
			}
//----------------------------------------за Англию-----------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "toAbigile")
				{
					dialog.text = "Buon pomeriggio, giovanotto. Vedo che sei qui per un motivo... Che cosa cerchi? Ci guadagno qualcosa anch’io, o mi sto perdendo qualcosa?";
					link.l1 = "Buon pomeriggio, Salomone. Vorrei parlare con Abigail.";
					link.l1.go = "Solomon_treasure";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Salve, giovanotto. Che cerchi da questo povero vecchio ebreo?";
				link.l1 = "Buon pomeriggio, Solomon. Niente di che, sono passato solo a salutarti.";
				link.l1.go = "exit";
				break;
			}
//-----------------------------------------против всех-------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Buon pomeriggio, giovanotto. Vedo che sei qui per un motivo... Che ti serve? Ci guadagno qualcosa da questa faccenda, o mi sta sfuggendo qualcosa?";
					link.l1 = "Devo parlare con Abigail. Ho una lettera per lei.";
					link.l1.go = "Abigile_kidnap";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDayOver")
				{
					dialog.text = "Buongiorno, giovanotto. Che vuoi? Un'altra lettera per mia figlia?";
					link.l1 = "No.   Dov'è Abigail?";
					link.l1.go = "Abigile_GoOver";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistory")
				{
					dialog.text = "Ehi... Stai forse parlando dei miei dobloni, giovanotto?";
					link.l1 = "Sì, signor mio. Riguardo al denaro che avete nascosto su quell’isola. È vero che né voi né Abigail ricordate dove si trova?";
					link.l1.go = "Solomon_history";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryAfter")
				{
					dialog.text = "D'accordo. Mi ricordo della fluyt e del suo capitano. L'avevo già visto una volta ad Amsterdam. La nave si chiamava 'Leiden' e il capitano si chiamava Toff Keller.";
					link.l1 = "È un inizio! Adesso ho una pista.";
					link.l1.go = "Solomon_history_3";
					pchar.questTemp.HWIC.Self = "SolomonHistoryEnd";
					break;
				}
				dialog.text = "Oy vey, che vuoi da questo povero vecchio ebreo stavolta?";
				link.l1 = "Buon pomeriggio. No, niente, sono passato solo per salutare.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Oi vey, che vuoi ancora da questo povero vecchio ebreo?";
			link.l1 = "Buon pomeriggio. No, niente di particolare, sono venuto solo a salutare.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-----------------------------------------------За Голландию-----------------------------------
		case "SolomonBonanza":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "E cosa vuoi da me? Ti sembro forse uno che sa qualcosa? Come potevo immaginare che proprio in un giorno così maledetto ci sarebbe stata una striscia di terra con merci e oro pronta da prendere? Immagina: tutti quei gentili in strada vorrebbero infinocchiare uno come me e portarmi via il denaro!\nC'è un'isola. Nemmeno un'anima viva, solo Abi e io. Nessuno, nessuno. Proprio nessuno. In mezzo c'era una grotta. Lì ho nascosto il mio baule per salvarlo da quel pirata goy Amalek! Un baule pieno d'oro, neanche uno straccio di cianfrusaglia. L'ho trascinato qui dalla Vecchia Europa! Tutto quello che ho sudato per guadagnare è lì. E anche il cranio di mio nonno... Fidati, quel coso ci ha salvati, sì-sì.\nOh-ho-ho, è un talismano antico carico di magia del Talmud! Che Dio ci scampi da Amalek! Oy vey, che fatica ricominciare in questi tempi dei gentili! Potessi capirlo, ragazzo! Oh, se solo potessi capire!";
			link.l1 = "Che diavolo stai farneticando, pazzo? Chi se ne frega. Me la vedo io da solo. Addio!";
			link.l1.go = "SolomonBonanza_1";
		break;
		
		case "SolomonBonanza_1":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbySeekIsland";
			pchar.quest.Joakim_meeteng.win_condition.l1 = "location";
			pchar.quest.Joakim_meeteng.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Joakim_meeteng.function = "Create_Joakim";
		break;
		
		case "SolomonBonanza_2"://отдаем всё
			dialog.text = "Ohibò, c’è davvero un Dio e tu sei un vero uomo d’onore! Hai riportato non solo il mio oro, ma anche riscattato il nome degli Shneur! Che vergogna hai evitato! Il signor Rodenburg può esser fiero di avere capitani come te al suo servizio. Consegnerei il teschio al signor Rodenburg, che mi ha promesso una buona somma per esso. Permettimi di ringraziarti di persona: sei un ottimo shabbos goy – prendi quest’amuleto come piccolo segno della gratitudine di questo ebreo.";
			link.l1 = "Ehm, grazie, suppongo.";
			link.l1.go = "SolomonBonanza_4";
			RemoveItems(PChar, "SkullAztec", 1);
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			AddDialogExitQuestFunction("DeleteJoakimFromRoom");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Joakim"));
			pchar.questTemp.Caleuche.SolomonSkul = true;
		break;
		
		case "SolomonBonanza_3":
			dialog.text = "Ohibò, che il cielo ti benedica, sei davvero un uomo d'onore! Hai riportato non solo il mio oro, ma anche restituito dignità al nome Shneur! Che vergogna hai evitato! Quanto al teschio... bah, lasciamo perdere, era uno sciagurato fuori di testa! Mynheer Rodenburg può davvero vantarsi d’avere capitani come te al suo servizio. Permettimi di ringraziarti personalmente, sei un ottimo compare cristiano – prendi questo amuleto, che ti ricordi di me.";
			link.l1 = "Ehm, grazie, suppongo.";
			link.l1.go = "SolomonBonanza_4";
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "obereg_10");
			pchar.questTemp.HWIC.Holl.ScullnotReturn = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			DelLandQuestMark(npchar);
		break;
		
		case "SolomonBonanza_4":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyLeavesMarried";//теперь можно говорить с Аби
			AddQuestRecord("Holl_Gambit", "1-32");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "SolomonBonanza_5":
			dialog.text = "Cosa? Che stai blaterando, giovanotto? È forse vero? Fammi vedere... ";
			link.l1 = "Ecco i tuoi soldi. Sono per te e per Abigail. Ma ahimè, non ho ancora trovato il cranio di tuo nonno.";
			link.l1.go = "SolomonBonanza_6";
		break;
		
		case "SolomonBonanza_6":
			AddMoneyToCharacter(pchar, -200000);
			GiveItem2Character(pchar, "amulet_7"); 
			dialog.text = "Oh denaro, denaro, denaro, meraviglioso denaro... Hmm, ma questo non sembra il mio denaro... Né profuma come il mio amatissimo bottino. Ma dopotutto – il denaro è sempre denaro, giovanotto, non è vero? Non mi lamenterò. 'Non si guarda in bocca il cavallo donato,' come diciamo noi! Mille grazie per avermi restituito i risparmi. Gradirei ringraziarti anch’io, accetta questo amuleto. Ora va’ a raccontare la lieta novella ad Abi. Io intanto mi metto a contare.";
			link.l1 = "Tanti auguri, Salomone.";
			link.l1.go = "SolomonBonanza_4";
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";//признак для Лукаса
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

//-------------------------------------------за Англию------------------------------------------------
		
		case "Solomon_treasure":
			dialog.text = "Oy vey, fa' attenzione! Mynheer Rodenburg sta quasi per diventare mio genero gentile. Tutti i soldati della guarnigione saranno qui in un baleno se grido aiuto!";
			link.l1 = "Chi diavolo sei tu?";
			link.l1.go = "Solomon_treasure_1";
		break;
		
		case "Solomon_treasure_1":
			dialog.text = "Ascoltami, capitano. Sono suo padre, Salomone. Fa' la cosa giusta, riportami le mie monete perdute e il teschio di giada del suo bisnonno. Questo vecchio ebreo forse non è astuto quanto te, ma sa bene che vuoi qualcosa da sua figlia.  Forse qualcuno ti ha mandato, qualche capitano che mi conosce, non temere: racconterò tutto ad Abi. Lei ora non è in casa, sta pregando per le anime di peccatori gentili come te.";
			link.l1 = "Non ci ho capito un’acca... Dannazione, sei proprio un bel tipo tu. Addio, vecchio avaro.";
			link.l1.go = "Solomon_treasure_2";
		break;
		
		case "Solomon_treasure_2":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-17");
			pchar.questTemp.HWIC.Eng = "AbigileInChurch";
			sld = characterFromId("Abigile");
			sld.greeting = "abigile_3";
			ChangeCharacterAddressGroup(sld, "Villemstad_church", "goto", "goto1");//Аби в церковь
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
//----------------------------------------------против всех---------------------------------------------	
		
		case "Abigile_kidnap":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Villemstad");
			dialog.text = "Una lettera? Ma guarda un po’! Senti qui, forestiero, il signor Rodenburg è quasi mio genero. Quindi fila via da qui col tuo sederone, che lui mi sta proprio simpatico!";
			link.l1 = "Ascolta, non me ne frega un accidente di chi sia tuo genero. Ho l'obbligo di consegnare questa lettera ad Abigail. Sai dove posso trovarla? E tu chi diavolo sei?";
			link.l1.go = "Abigile_kidnap_1";
		break;
		
		case "Abigile_kidnap_1":
			dialog.text = "Chi sono io? Sono suo padre, Salomone... E tu non mi piaci, goy.";
			link.l1 = "Mi preoccuperei di più se dicessi che ti sto simpatico. Allora, vuoi continuare a trattarmi dall’alto in basso o chiamerai finalmente Abigail? Te lo ripeto, sono un messaggero! Ho una lettera per vostra figlia!";
			link.l1.go = "Abigile_kidnap_2";
		break;
		
		case "Abigile_kidnap_2":
			dialog.text = "Dammi questa lettera. La consegnerò io a mia figlia.";
			link.l1 = "Ti raderò la testa e ti storcerò il naso prima di consegnarti questa lettera. Ho ricevuto ordini di dare questo messaggio solo a lei, di persona. Non mi hanno detto una parola su suo padre, e a dirla tutta non me ne frega un accidente. Dove posso trovare Abigail?";
			link.l1.go = "Abigile_kidnap_3";
		break;
		
		case "Abigile_kidnap_3":
			dialog.text = "Appena alzerò la voce, giovanotto, ogni soldato della città sarà qui in un batter d’occhio. Non fare tanto il testardo, vedi bene che ho io il coltello dalla parte del manico.";
			link.l1 = "Gesù, Maria e Giuseppe! Davvero? E poi che? Ti aspetti che mi trascinino in catene solo per aver recapitato una lettera? Non dire sciocchezze!";
			link.l1.go = "Abigile_kidnap_4";
		break;
		
		case "Abigile_kidnap_4":
			DialogExit();
			sld = characterFromId("Abigile");
			ChangeCharacterAddressGroup(sld, "Villemstad_houseSP2", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_GoOver":
			dialog.text = "Sei impazzito? Hai sconvolto la mia povera figliola con la tua lettera... S’è messa in testa di rincorrere quel mascalzone di capitano inglese! È salpata col primo bastimento che ha trovato! Oy vey, la mia povera figlia! Che farà mai questo vecchio ebreo adesso? La mia vita è finita! Che vergogna! Lasciami piangere la mia miseria, o resta qui a goderti lo spettacolo, mi è indifferente! Ohhh, la mia povera Abigail! Hai fatto scendere la testa canuta di suo padre nello Sheol dal dolore!";
			link.l1 = "Ebbene, guarda un po’! Pare che non abbia potuto aspettare nemmeno un battito di ciglia. Addio, Solomon!";
			link.l1.go = "Abigile_GoOver_1";
		break;
		
		case "Abigile_GoOver_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-69");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
		break;
		
		case "Solomon_history":
			PlaySound("Voice\English\hambit\Solomon Shneur-03.wav");
			dialog.text = "Che vuoi che ci sia? È solo un’isola, deserta, ci viviamo solo io e Abigail. Lì ho nascosto il mio forziere, così quel cane pirata, Amalek, non potesse metterci le sue luride mani. Tutto ciò che ho guadagnato onestamente, sudando sette camicie, sta dentro quel forziere...";
			link.l1 = "Dimmi, Salomone, potresti forse ricordare il nome dello fluyt di cui parlava tua figlia? E come si chiamava il suo capitano?";
			link.l1.go = "Solomon_history_1";
		break;
		
		case "Solomon_history_1":
			dialog.text = "Hmm... Eh, non saprei proprio. La testa di questo povero vecchio ebreo è più confusa di una pentola di gefilte fish! E perché lo chiedi, giovanotto?";
			link.l1 = "Voglio solo aiutare tua figlia, Solomon. Non posso promettere nulla, ma vorrei provarci. Il mio vecchio padrone l'ha trattata male, e dopo tutto ciò credo di avere il dovere di darle una mano a sistemarsi, in qualche modo.";
			link.l1.go = "Solomon_history_2";
		break;
		
		case "Solomon_history_2":
			dialog.text = "Ohibò, se le cose stanno così...";
			link.l1 = "";
			link.l1.go = "Solomon_history_3";
			pchar.questTemp.HWIC.Self = "SolomonHistoryNext";
		break;
		
		case "Solomon_history_3":
			DialogExit();
			sld = characterFromId("Abigile");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Solomon_thanks":
			dialog.text = "Giovanotto! Aspetta!";
			link.l1 = "Sì?";
			link.l1.go = "Solomon_thanks_1";
		break;
		
		case "Solomon_thanks_1":
			dialog.text = "Giovane uomo! Vorrei ringraziarti per tutto ciò che hai fatto per me e mia figlia. Ci hai salvati. Mi dispiace per averti accolto freddamente la prima volta e per aver dubitato delle tue vere intenzioni d'aiuto. Perdonami, vecchio ebreo che sono. Sei davvero un uomo benedetto tra i gentili. Dimmi, non hai trovato altro oltre ai miei soldi nella grotta?";
			link.l1 = "No, Salomone. Non c’era altro che denaro. Ho dovuto affrontare i tagliagole di van Berg – è stato lui ad affondare la tua nave mesi fa. Forse avevano già rubato qualcosa... Cos’altro doveva esserci là?";
			link.l1.go = "Solomon_thanks_2";
		break;
		
		case "Solomon_thanks_2":
			dialog.text = "Oh niente d’importante... Solo un’antica reliquia di famiglia... Beh, lasciamo stare! Dimenticalo pure, era un poveraccio comunque! E... Solo un’ultima cosa, giovanotto... ";
			link.l1 = "Avanti.";
			link.l1.go = "Solomon_thanks_3";
		break;
		
		case "Solomon_thanks_3":
			dialog.text = "Tu... ebbene, ho scoperto qualcosa su di te. Il nostro governatore ti tiene in grande considerazione, e sei un capitano di tutto rispetto. Ti svelerò un segreto... mia figlia ti ha preso davvero a cuore. Me l'ha detto lei stessa. Forse... ci penserai su? Abigail è una ragazza davvero perbene, te lo garantisco, migliore di qualunque sgualdrina forestiera che tu abbia incontrato nei tuoi viaggi.";
			link.l1 = "Oy vey... Non è così semplice, Salomone. Tua figlia è davvero una gemma rara. Custodiscila come il più prezioso dei tesori.";
			link.l1.go = "Solomon_thanks_4";
		break;
		
		case "Solomon_thanks_4":
			dialog.text = "Riflettici su, giovanotto. Ripensaci e torna pure! Saremo lieti di rivederti!";
			link.l1 = "Certo... addio, Salomone.";
			link.l1.go = "Solomon_thanks_5";
		break;
		
		case "Solomon_thanks_5":
			DialogExit();
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload1", false);
			AddQuestRecord("Holl_Gambit", "3-65");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "Solomon_poor":
			dialog.text = "Oyyy... Talvolta è impossibile ricominciare da capo, giovanotto. Vivere nella miseria... che c’è di peggio per un vecchio rimbambito come me?";
			link.l1 = "Mi dispiace, Salomone. Tieni duro e cerca conforto in Cristo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Solomon_poor";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tu sei un "+GetSexPhrase("Ladro, signore! Guardie, prendetelo","ladra, ragazza! Guardie, prendetela")+"!!!","Ma guarda un po'! Appena mi son perso nei miei pensieri, tu già frughi nel mio baule! Al ladro!!!","Guardie! Rapina! Acchiappate il ladro!!!");
			link.l1 = "Maledizione!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
