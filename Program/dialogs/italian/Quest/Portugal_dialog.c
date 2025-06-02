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
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "Errore. Avvisa i diavoli che han fatto il gioco.";
		link.l1 = "Certo.";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Oh, un altro coraggioso marinaio! Conosco la tua razza, maledetto il mio occhio che vi riconosce subito, ah! Vuoi sapere perché?";
			link.l1 = "Volevo parlarti d’una faccenda diversa: riguarda il debito che hai con la padrona di questo... ehm, locale. Mi ha chiesto di ricordartene; ti consiglio di saldarlo, altrimenti domani dovrà rivolgersi alle guardie per farti lo stesso discorsetto.";
			link.l1.go = "Avendel_tavern_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "L’oste è... oh, dannazione! Johanna, quella strega non può farmi questo! Sei sicuro? Ha davvero detto che mi butterebbe nelle segrete per quattro maledette monete?";
			link.l1 = "Assolutamente. È proprio ciò che ha detto. Suppongo che la mia missione sia conclusa, addio, signor Avendell.";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "Aspetta! Ti prego, aspetta! Hai proprio l’aria di un capitano navigato. Son certo che qualche doblone in tasca ce l’hai, io invece sono al verde! Solo il vecchio oste ancora mi riempie il boccale a credito per l’amicizia che ci lega da anni. Ora ascolta... ascolta la mia proposta, capitano! Mi saldi il debito e ti lascio una fetta del bottino.\nC’è un affare... un affare che rende più dell’oro dei galeoni, maledetto me e la mia ciurma! Te lo giuro su questa mia ancora insanguinata, dammi fiducia, capitano - qualunque sia il tuo nome!\nBasta riscattare un piccolo debito, diecimila pesos appena, e avrai la tua occasione per riempirti le tasche abbastanza da comprare tutte le case di piacere del Nuovo dannatissimo Mondo! Che ne dici? Tu dai a me, io do a te, come tra gente d’onore...";
			link.l1 = "Un pezzente che promette tesori. Risparmiami queste fandonie, non faccio elemosina a tipi come te. Trova i soldi oppure presto ti ritroverai a marcire nelle segrete del forte. Addio!";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Una fetta? E perché dovrei fidarmi delle ciance d’un ubriacone? Per via di promesse campate in aria?";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "Ascoltami, capitano! Hic, che il diavolo mi porti se sto mentendo! Ma ti giuro che dico la verità! Pensa un po', se mi becchi a mentire, puoi aprirmi le budella con quella bellezza che porti alla cintura! Maledizione, l’elsa di quella lama vale cinque volte più del mio misero debito! Allora, che ne dici? Non hai nulla da perdere!";
			link.l1 = "Ne ho abbastanza delle tue chiacchiere. Addio.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Va bene, Hugo... Rischierò di dar credito a quelle tue fandonie. Ma ricordati: dovrai convincermi e dimostrarmi che i miei dobloni non sono stati sperperati per niente quando tornerò, altrimenti sarai tu a finire sulla graticola.";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "Niente minacce, ho capito. Ti do la mia parola, capitano! Saremo ricchi! Torna quando questo dannato debito sarà saldato e noi p-parleremo! Sì, lo faremo! Non resterai a mani vuote!";
			link.l1 = "Bene, cancellerò il tuo debito, ma faresti meglio a pregare, Hugo Avendell, che la tua 'proposta' mi soddisfi davvero.";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;
		
		case "Avendel_repeat":
			dialog.text = "Capitano, torna il più in fretta possibile – questa faccenda potrebbe svanire come il vento.";
			link.l1 = "Sì, sì, presto ti restituirò il debito.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Sei tornato, capitano! Per mille tempeste e fulmini dell’inferno, che gioia rivederti! E il mio debito, allora?";
			link.l1 = "Me ne sono occupato io, ora tocca a te, Hugo. Raccontami la tua storia e cerca almeno di renderla vagamente credibile!";
			link.l1.go = "Avendel_tavern_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "Non temere, capitano! Lo sapevi che ero un cacciatore di taglie? O meglio... lo ero un tempo. Non sono stato abbastanza fortunato, suppongo. Forse persino il Diavolo in persona con tutte le sue malefatte non era uno sfigato come me. Ho perso tutto nell’ultimo incarico... L’equipaggio è scappato e ho dovuto vendere la nave per pagare i debiti...";
			link.l1 = "Sono già al corrente delle tue gesta eroiche. Andiamo al sodo, Hugo, non mettere alla prova la mia pazienza.";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "Sì, sì, capitano..."+GetFullName(pchar)+", ho ragione? So anch'io qualcosa su di te. Ma che il diavolo mi porti se conta qualcosa. Hai mai sentito il nome di Bartolomeo il Portoghese?";
			link.l1 = "Bart il Portoghese? Certo che ho sentito parlare di lui. Tutti ne hanno sentito. È un pirata, un macellaio, e un lurido mascalzone, per quel che so. Ma che parte ha nella tua storia?";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "Sta giocando un dannato ruolo principale in tutto questo! L'ho braccato per un anno e mezzo. La Compagnia Olandese ha messo una gran taglia sulla sua testa. Ma ho fallito, e ho perso tutto. E adesso la Compagnia ha triplicato la ricompensa, ma solo se lo porto vivo, maledetto lui!";
			link.l1 = "Per buona ragione, non è affatto una passeggiata catturarlo vivo. Comunque, perché me ne dovrei preoccupare, Hugo? Sembra proprio che tu stia cercando di fregarmi!";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "Non ci pensavo nemmeno, capitano! Sa, il dottor Peter Van Stal, quello del posto, un uomo assai garbato, m’ha dato una pozione per guarir le mie emicranie! Ebbene, il dottore non s’è fatto vedere in casa sua per quasi tre giorni e...";
			link.l1 = "Hugo, la mia pazienza è quasi finita! Ho promesso alla dama che non ti infilzerò con la spada, ma i miei pugni andranno benissimo! Ti giuro che nessuna pozione potrà guarire il tuo cranio domani!";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "Aspetti, capitano! La prego! Mi ascolti, ho visto alcuni tipi vicino alla casa del medico e li ho riconosciuti. Sono dell’‘Albatross’, una fregata dei dannati portoghesi! E uno di loro parlava proprio della salute del loro capitano! Guardi adesso, "+pchar.name+", Bartolomeo è qui, in questa città! Proprio sotto il nostro naso, sarà ferito o malato, ecco perché hanno bisogno di dannato cerusico!\nDubito che il portoghese abbia portato con sé tutta la sua ciurma, ma non posso lanciarmi in questo casino da solo! Di certo, maledizione, sai come menar la tua spada dannata! Prendi con te un paio di bravi tagliagole e troveremo quel topo di sentina! Poi lo acciufferemo e lo consegneremo alle autorità!\nE due mila buoni dobloni d’oro finiranno nelle nostre tasche!";
			link.l1 = "No, Hugo, ne ho abbastanza delle tue chiacchiere. Non voglio immischiarmi in questa faccenda, anche se potresti aver ragione. Addio.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Hmm, interessante. Sai dove si nasconde? Se va tutto liscio parleremo di spartizioni, ma se dici il vero allora dobbiamo sbrigarci, ora!";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "No, non so dove sia, capitano. Avevo troppa paura per inseguire quei mascalzoni. Se quello con un occhio solo mi avesse visto...ah! Ma insieme, coi tuoi uomini, riusciremo a setacciare tutta la città, raduna la tua ciurma e diamoci dentro! Maledizione, i dobloni olandesi ci aspettano! Una dannata occasione così capita una volta sola nella vita, che mi venga un accidente!";
			link.l1 = "Un entusiasmo lodevole... Spero che tu riesca a staccarti dal tavolo, gran cacciatore di taglie. Io parto subito alla ricerca, puoi seguirmi se vuoi, basta che non mi rompi troppo le scatole.";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "Sì, sì, capitano, lasciami solo finire il mio bicchiere e vengo con te... Dove gettiamo l’ancora per primi?";
			link.l1 = "Dove?!... Vado io, con te o senza di te.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "Casa sbagliata, compare. Sparisci subito!";
			link.l1 = "Hm. E penso proprio che sia la casa giusta...";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "Ebbene, t'avevo avvisato...";
			link.l1 = "...";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "Vento in poppa, bandiera al vento, figli di... preparate i cannoni!... ah-ha-ha... oh mia bellezza...";
			link.l1 = "Hmm, ha avuto una gran botta di fortuna a restare vivo...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "Oh Dio, chi sei tu? Ti prego, abbassa l’arma! Qui c’è un malato!";
			link.l1 = "Questo tuo 'malato' ha fatto fuori più anime di quante tu ne abbia mai viste, dottore. Togliti dai piedi!";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "È il mio paziente ed è persino incapace di reggersi in piedi! Non lo vedi? Ti prego, abbassa la lama! Te ne supplico!";
			link.l1 = "E che diavolo gli prende, maledizione!?";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "Suppongo sia tutto colpa della sua ferita, un colpo ricevuto da un'arma avvelenata dei Caribi... e gli uomini che l'hanno portato qui hanno detto che se lui muore, morirò anch'io! Ma sto facendo tutto ciò che posso, diteglielo voi!";
			link.l1 = "Non preoccuparti di quei mascalzoni, dottore. I miei ragazzi veglieranno sulla tua casa e io devo andare a far visita al governatore. Scommetto che si piscerà addosso dalla gioia. Non muoverti da qui finché non torno, dottore.";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "Non me ne andrò, non temere. Diamolo già nelle mani delle autorità e mettiamo fine a questo incubo.";
			link.l1 = "Ma certo, mi ci metto subito.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "Ce l’abbiamo fatta, capitano! L’abbiamo trovato e presto saremo ricchi, proprio come vi avevo detto! Qual è il prossimo passo?";
			link.l1 = "Spero anch’io, Hugo. Comunque, non è ancora finita. Suppongo che ora tocchi a me andare dal governatore a discutere della nostra ricompensa?";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "No-no, No capitano! Non andare da quel maledetto Thomas! Fidati di me, quel furfante ci porterà via il prigioniero e se ci va bene ci offrirà una tazza di caffè! Sua Eccellenza è un tipo losco, quindi se vuoi la ricompensa completa devi far rotta su Curaçao! Altrimenti i portoghesi ce li portano al forte e ci scacciano come pezzenti!";
			link.l1 = "Ebbene, se ne sei davvero certo...";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "Lo sono, capitano, dannazione se lo sono! Ma ricorda che gli uomini di Bartolomeo devono essere in giro per la città e non vogliamo nemmeno attirare l’attenzione della guarnigione, questo è poco ma sicuro! Dobbiamo decidere come portare il portoghese sulla tua nave e farlo senza farci notare, per tutti i diavoli!";
			link.l1 = "D'accordo... Non voglio incrociare le lame col suo vascello sulla rotta per Willemstad. Hai qualche idea?";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "Sì, ne ho uno. Prima dobbiamo procurargli un abito più nobile, poi lo trasciniamo dentro dall’ingresso sul retro come un ufficiale ubriaco! Nessuno sospetterà che sia un maledetto pirata, fidati di me!";
			link.l1 = "Hmm, non sono sicuro di questa faccenda, ma per ora non abbiamo un piano migliore. Proverò a procurarmi della stoffa pregiata per il nostro passeggero. Tu resta qui e sorveglia Bart e il dottore.";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
			AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
			QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;
		
		case "Avendel_house_guard":
			dialog.text = "Non temere, capitano. Il portoghese è sotto la mia sorveglianza fidata, eh eh...";
			link.l1 = "Mi piacerebbe crederlo...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "Non vedo i soldati, "+GetAddress_Form(NPChar)+". Dove sono? Hai detto che l'avrebbero arrestato appena avresti raccontato loro la situazione. Allora perché quei soldati non sono ancora qui?";
			link.l1 = "Non ci saranno soldati, mynheer Van Stal. Farò il lavoro da solo e devo portare il vostro paziente a Curaçao il prima possibile.";
			link.l1.go = "Portugal_doctor_5";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "Capitano, ascolta, non riesco a curare la sua ferita; tutto ciò che posso fare è abbassargli un po’ la febbre. È quasi sempre privo di sensi e vaneggia, non c’è dubbio che morirà anche senza che nessuno ci metta mano, e il dondolio del mare lo finirà in pochi giorni. Ti lascerò qualche mistura che potrà aiutare...";
			link.l1 = "No, dottore, vieni a bordo con noi. Primo, io con la medicina sono una frana, secondo, dubito che tu voglia restare qui a spiegare ai portoghesi dove sia finito il loro capitano.";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "...Sì, suppongo tu abbia ragione. Ma sappi che questo filibustiere è davvero tosto, ho visto gente con solo qualche graffio fatto dalle armi degli indiani e sono tutti crepati in meno di tre giorni. E secondo i suoi 'compagni', sta così già da una settimana! Eppure ti dico che resisterà solo poco tempo ancora su una nave in mare aperto. Tre giorni, non di più!\nQuesto è tutto il tempo che ci resta.";
			link.l1 = "Nemmeno un dannato uccello arriverebbe a Curacao in tre giorni. Ma credo di sapere cosa posso fare! Ho... un compare, vive a St. John's, ad Antigua. Sa guarire la gente anche dalle ferite mortali. È l’unico che può darci una mano adesso. Il nostro obiettivo è semplice: arrivarci prima che il portoghese tiri le cuoia. Prepara la tua roba, dottore, salpiamo subito e il tuo paziente sarà il prossimo a bordo!";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			QuestPointerDelLoc("marigo_town", "reload", "houseF1");
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "Che peccato, capitano. Abbiamo perso, e quell’infame oro non lo vedremo mai. Addio.";
			link.l1 = "Addio, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "Dottore, prepara il tuo paziente per lo sbarco. La scialuppa è pronta. Sbrigati!";
			link.l1.go = "Portugal_doctor_10";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "Sto arrivando, "+GetAddress_Form(NPChar)+".";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придёт через 7 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "Questa casa puzza di maledette misture! Sarebbe una vera sorpresa se il portoghese crepasse qui; solo a respirare quest’olezzo, si guarisce ogni malanno!\nE la ciurma di quell’uomo ci troverà facile, guidata da questo fetore!";
			link.l1 = "Hugo, risparmiami le tue facezie. Ho lasciato alcuni uomini in strada a sorvegliare la casa, ma una guardia in più non guasterà per il nostro ospite. Tienilo d’occhio e cerca di morderti la lingua con le bestemmie, o Gino ti farà trangugiare uno dei suoi intrugli, sono certo che saprà curarti per bene.";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "Non temete, capitano! Sorveglierò il nostro bottino con occhi da falco, quello lì non scapperà manco se stesse in piena salute! E vi supplico, niente più intrugli, per carità!";
			link.l1 = "Vedi, sai essere gentile quando vuoi. Stai all’erta, devo andarmene.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "Te ne vai già, capitano? Ah, bene! Era ora! Ho visto alcuni figli di... loschi figuri per strada. Non sembrano portoghesi, ma cercavano qualcosa. Dobbiamo stare all’erta, capitano!";
			link.l1 = "Bene, grazie per l'avvertimento, Hugo. Andiamo alla nave.";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "Capitano, abbiamo atteso questo incontro per troppo tempo! E chi è quello con te? Bartolomeo il Portoghese in persona, ah, pare che il Temerario Pierre avesse ragione – è proprio lui! Fatti da parte, capitano, lo porteremo via con noi e nessuno si farà male.";
			link.l1 = "Mi scusi, signore, ma chi diavolo siete voi? Toglietevi dai piedi o domani nessuno di voi vedrà la luce!";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "Oh, guardate che canaglia minacciosa, ragazzi! Ah-ah-ah! Ascolta bene, cucciolo, non metterti mai fra Leo Cord e il suo bottino! Sono mesi che rincorriamo quel portoghese e adesso, finalmente, l’abbiamo tra le mani. Quindi posa quel tuo stuzzicadenti e sparisci finché hai ancora fiato nei polmoni! Non siamo così avidi: anche un morto ci va a genio, ah-ah!";
			link.l1 = "Basta. Allora danziamo, gentiluomini!";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Sapevo che qui c’era puzza di bruciato! Bravo, capitano! Ma ora si deve filare via, quel dannato Leo Cord ha una ciurma di furfanti e una nave niente male! Dobbiamo sgomberare da quest’isola!";
				link.l1 = "Ben detto, Hugo, e son ben lieto che nessuna palla sia volata verso la tana dove te ne stavi nascosto.";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "Che peccato, capitano. Abbiamo perso e quell’infame oro non lo vedremo mai. Addio.";
				link.l1 = "Addio, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "Io... io stavo coprendo le spalle, capitano! Te la cavavi benissimo anche senza di me, ma se qualcuno ci avesse assalito dall’altro lato della strada? Non avresti avuto il tempo di correre alla nave.";
			link.l1 = "Forse è per questo che non hai avuto fortuna nel tuo mestiere? Bando alle ciance, dobbiamo raggiungere la nave! Il tempo stringe!";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "Capitano, il portoghese sta davvero male, dobbiamo fermarci!";
			link.l1 = "Ecco perché siamo qui, mynheer van Stal, il nostro viaggio è quasi giunto al termine. Prenderò una stanza in taverna e il nostro prigioniero vi rimarrà per qualche giorno.";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "Mynheer capitano, mi prenderò cura del portoghese, ha bisogno di riposo completo.";
			link.l1 = "Ho capito, dottore, va bene. Maledizione, per quanto dovrò ancora occuparmi di questo bucaniere? Non gli fa bene, non è ciò di cui ha bisogno! Pare che mi abbiano assoldato come balia e... ah, perdonatemi, dottore, ma è davvero troppo... ci vediamo più tardi.";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "Monsieur, siete voi il capitano "+GetFullName(pchar)+", la cui nave è appena attraccata nel nostro porto quest’oggi?";
			link.l1 = "Hai ragione, in che modo posso esserti d’aiuto?";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "Sua Eccellenza Jacques Dille du Parquet, il governatore della nostra colonia, vi attende. La questione è d'urgenza!";
			link.l1 = "Va bene, monsieur, oggi farò visita a Sua Eccellenza.";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "Siamo arrivati a Martinica, capitano! Il nostro bottino ormai non è lontano...";
			link.l1 = "Solo se il portoghese sopravviverà fino a Willemstad. Hugo, devo andare alla nave, quindi dovrai vegliare tu sul dottore e il suo paziente.";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "Andare alla nave? Perché mai? Mi presterai qualche tuo uomo per darmi una mano? E se dovesse accadere qualcosa mentre sei via?";
			link.l1 = "Mi dispiace, ma no. Dubito che qualcosa possa minacciarti qui. La guarnigione è all’erta e ci sono più soldati per le strade del solito, quindi se dovesse succedere qualcosa, chiamali pure. Hanno avvistato una grossa nave non lontano da quest’isola, forse una nave di filibustieri. E sua Eccellenza il governatore m’ha ordinato di rafforzare la difesa dell’isola pattugliando con la mia nave.";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "Una nave? Da pirati? Potrebbe essere l’Albatro! O forse qualche compare del nostro vecchio amico Leo Cord!";
			link.l1 = "O forse è solo una nave pirata qualunque. Tuttavia, Hugo, se questa nave è venuta per le nostre teste, farei meglio ad affrontarla con la pattuglia locale al mio fianco e per l’oro del governatore. Meglio che stare a guardarci le spalle per tutto il resto del viaggio. Se invece è un falso allarme, mi risparmierà giusto qualche giorno a scaldare la panca nella taverna.";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "Pensa bene, capitano, è saggio lasciare il dannato... il portoghese senza guardia mentre la sua fregata potrebbe scorrazzare nei paraggi? Stai rischiando la nostra ricompensa accettando la paga del governatore!";
			link.l1 = "Basta ciarlare, Hugo Avendell! Qui comando io, e l’ultima parola spetta a me! Fa’ come ti dico. Vai alla taverna e sorveglia il dottore e il portoghese finché non torno.";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "Sei tornato, capitano, finalmente! Temo di avere cattive notizie per te: il portoghese è sparito, e anche il dottore!";
			link.l1 = "Come?! E cosa diavolo facevi allora, testa di legno?!";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "Scommetto che quella nave era l’‘Albatross’. Ho visto quei portoghesi, sono entrati in taverna e io… sono scappato. Mi dispiace, ma incontrare il Cane Guercio era troppo, perfino per tutti quei soldi!";
			link.l1 = "Merda! Dimmi almeno che diavolo è successo in taverna?";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "Ti ho già detto che non ho visto nulla. Sono scappato in cucina appena ho visto Franz Garcke e i suoi uomini... Era un bel rischio! È successo ieri sera e non sapevo come avvertirti...";
			link.l1 = "Sì, sei davvero un uomo coraggioso e pieno di risorse... Bene, ti daremo un'altra possibilità, andremo a cercarli. Ho tenuto da parte questo furfante fin troppo a lungo e ormai lo considero roba mia. Abbiamo ancora un po' di tempo per braccarli, quindi cominciamo dalla taverna, magari qualcuno ne sa più delle tue calcagna in fuga. Su, va’ a prepararti!";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "Hai sentito, capitano? Parlava del Cane Guercio, te ne ho parlato poco fa. E quel castigliano che fischia è Hernando Vasquez, maledetto Don – il macellaio di Vera Cruz, non l’ho visto io!";
			link.l1 = "Calmati, Hugo. Sono certo che Bartholomeo è ancora sull’isola, forse sta un po’ meglio, ma resta troppo debole. E credo pure di sapere dove scovarlo! Li prenderemo, non mi lascerò sfuggire la mia ricompensa. Se non sei un codardo, vieni con me, non è ancora finita.";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "Fai troppe domande, capitano... Aspetta, non sei forse quel furfante di Philipsburg? Da troppo scappi da noi e guarda un po’—eccoti qua...";
			link.l1 = "Peccato per te, feccia!";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "... tu, miserabile merda di granchio, ci racconterai tutto, su questo puoi fidarti di me, maledetto sorcio! Poi finirai impiccato all'albero maestro invece che alla vela maestra... E chi diavolo sei tu? Maledetti babbuini, non ci si può mai fidare! Devo sempre fare tutto con queste mie mani...";
			link.l1 = "Vi disturbo, signori?";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "Mi piace il tuo tempismo... Immagino che dovrei ringraziarti per avermi tenuto in vita fino ad oggi?";
			link.l1 = "Hai ragione. Il mio nome è "+GetFullName(pchar)+" e tu, portoghese, resti ancora il mio prigioniero. Quindi non farmi domande, dobbiamo andare.";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "Aspetta, capitano... in città ci sono un sacco di uomini di Vasquez, non ci lasceranno andare così facilmente. Dammi una spada e avremo molte più possibilità.";
			link.l1 = "Non vai d'accordo coi tuoi compari, eh? Va bene, una lama in più fa sempre comodo, prendi l'arma di quel cadavere e resta vicino a me!";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "Non ti venga in mente che ti darò una pistola per poi buscarmi una coltellata appena giro le spalle! Stami vicino e basta.";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "Non temete, capitano, preferirei crepare piuttosto che finire di nuovo nelle grinfie di quel maledetto Vasquez.";
			link.l1 = "Ebbene, vedi, non ti voglio ancora vedere morto. Forza, il tempo stringe!";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "Peccato, avrei dato una mano al Guercio se davvero volessi vederti morto...";
			link.l1 = "Ma nemmeno tu mi hai aiutato, quindi zitto e muoviti!";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Maledizione! Sono loro! Ammazzateli tutti!";
			link.l1 = "Eccoci di nuovo... Avanti, bastardi!";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Splendido! Hai fatto fuori il Cane Guercio, che razza di capolavoro! Quanti dei suoi scagnozzi hai mandato all’inferno a bruciare?";
				link.l1 = "Combattevo senza far calcoli. E tu dov’eri, Hugo?";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "Che peccato, capitano. Abbiamo perso e quell’infame oro non lo vedremo mai. Addio.";
				link.l1 = "Addio, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "Io... stavo assicurando la ritirata sicura... tenendo d'occhio le nostre spalle, per così dire.";
			link.l1 = "Ebbene, questo è tutto, Hugo Avendell, la tua codardia ha superato ogni mia aspettativa, hai almeno idea di quanto sia stata dura quella battaglia per noi? Ce la siamo cavata per un soffio!";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "Calmati, capitano... Ammetto che mi stavo nascondendo. Ma ho trovato quest’occasione per te! Ricorda, sono stato io a portarti dai portoghesi! Beh... vista la tua giusta indignazione, mi accontento solo di un terzo della ricompensa.";
			link.l1 = "Ma che meraviglia! Ora vuoi mercanteggiare? No, compare, la tua parte in questa faccenda è finita! Hai perso il tuo denaro nella taverna di Saint-Pierre. L’hai lasciato lì e te la sei data a gambe, quindi per te è finita qui.";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "Capitano, stai chiaramente esagerando... Va bene, accetto per un quarto... per un quinto! Dieci percento!";
			link.l1 = "Non mettere alla prova la mia pazienza! Sparisci! Non ho bisogno di vigliacchi tra la mia ciurma, specie adesso che il tempo stringe!";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+", non pensi che sia un tantino ingiusto?";
			link.l1 = "Cause ed effetto, Hugo... Hai fatto la tua scelta, quindi addio. Impara la lezione e non tuffarti di nuovo in simili avventure, non sono proprio roba per te.";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "Alleggerisci la stiva, capitano? Eh, proprio così, ah... Vasquez è ancora a piede libero e sull’Albatross ci sono più uomini e cannoni che peli sulla schiena di un vecchio lupo di mare, scommetto i miei bei pantaloni contro uno straccio che Hernando non ci lascerà scappare.";
			link.l1 = "Ebbene, pare che tocca a noi andargli incontro di persona. Avanti, monsieur Portoghese, e cerca di tenere la bocca chiusa. Salperemo l’ancora il prima possibile.";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "Cosa diavolo aspetti, maledizione?!";
			link.l1 = "Dove si trova Hernando Vasquez? Parla e ti risparmierò la vita.";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "Va’ al diavolo con le tue dannate domande!";
			link.l1 = "Dopo di te...";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "Eccoti qui, mio coraggioso amico, finalmente possiamo scambiar due parole come si deve! Complimenti, capitano – far fuori il Cane Guercio e mandare a picco l’‘Albatros’ non era roba da principianti! In verità, hai fatto assai per salvarmi la pelle... Forse dovrei pure ringraziarti, eh?";
				link.l1 = "Mi ringrazierai quando starai danzando sulla forca o qualunque diavoleria ti abbiano preparato a Willemstad.";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "E finalmente ci sei, mio valoroso amico, possiamo finalmente scambiare due parole! Complimenti, capitano – far fuori il Cane Guercio merita una ballata gloriosa! In verità, mi hai salvato la pelle in più d’un modo... Forse dovrei persino ringraziarti?";
				link.l1 = "Mi ringrazierai quando ballerai sulla forca o qualunque altra diavoleria ti abbiano preparato a Willemstad.";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "Incredibile! Mi hai salvato la pelle per due settimane, mi hai accolto sotto il tuo tetto e difeso a colpi di spada... e ora vuoi mandarmi incontro alla morte? Faccio fatica a crederci... In verità, ormai ti considero quasi un amico, ah-ah.";
			link.l1 = "Un pirata che invoca l’onore? Portoghese, mi prendi in giro? Ti tenevo in vita solo per una ragione: farti affrontare il tribunale e pagare da furfante e assassino quale sei!";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Amico mio... suona come una beffa. Ma hai ragione comunque. Sarebbe strano da parte mia farlo, portoghese...";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "Oh, basta così, capitano. Scommetto che tutto quello che hai fatto era solo per mettere le mani sul denaro che la Compagnia ti aveva promesso per la gioia di vedermi ancora vivo! Non cercare di recitare l’onesto più di quanto tu sia davvero, signore, non ti si addice.";
			link.l1 = "Solo io posso giudicare me stesso. Mettiamo fine a questa discussione. È tempo di salpare per Willemstad.";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "Sembra che ancora un po’ d’onestà si possa trovare nella gente, oggigiorno... Peccato che il denaro ci metta sempre lo zampino – eh, capitano?";
			link.l1 = "Strano sentirlo dire da un pirata pronto per la forca, portoghese. Ti lascerò andare... non chiedermi il perché, sparisci al primo porto che trovi. E ricordati che non sarò così magnanimo se ci rincontreremo.";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "Davvero? Mi piacerebbe, capitano! Non ordineresti di portare qui un po’ di rum? Sai, solo per brindare alle tue virtù cavalleresche, alla nostra intesa e al rinvio della mia condanna?";
			link.l1 = "Non fare lo spiritoso, finché non tocchiamo terra resti il mio prigioniero. Addio.";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "Capisco... dunque sarà l’impiccagione. Me lo aspettavo. Allora ascolta quel che ho da dirti, capitano. Ti sei dato tanto da fare per tenermi in vita solo per impiccarmi per bene più tardi, e te ne sono grato. Suppongo sarebbe da sciocchi chiederti di cambiare idea così, su due piedi, vero? E se invece ti proponessi uno scambio? Un patto, diciamo, eh?";
			link.l1 = "Non dirò una parola, portoghese. Sei un pirata e un bastardo. Pagherai per i tuoi misfatti a Willemstad.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Un patto? Che cosa hai da offrire?";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "Non ho bisogno dei tuoi imbrogli, sparisci al primo porto che trovi. Oggi ti è andata bene.";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "Sai, questa tua ostinata abitudine di salvarmi la pelle, nonostante le ragioni poco piacevoli, merita comunque riconoscenza. E Bartolomeo il Portoghese sa mostrare gratitudine. Ascolta bene: un mese prima che ci incontrassimo, abbiamo catturato una nave della Compagnia. Hanno combattuto come dannati fino all’ultimo uomo. Ma nelle stive non c’erano che palle di cannone e topi.\nLa mia ciurma non ne fu contenta, ma io trovai uno scrigno assai curioso e dei documenti nella cabina del capitano. Era una nave corriera, trasportava campioni provenienti da miniere laggiù in Amazzonia. Diamanti puri e rubini, un vero tesoro!";
			link.l1 = "Un bottino interessante... Ora capisco perché la Compagnia abbia messo gli occhi su di te, ma dove vuoi arrivare con questa storia?";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "I miei primi ufficiali, Vazquez e Franz Garcke, tenevano la ciurma sotto controllo, così decisi di rischiare. Nascondetti le pietre da loro e bruciai i documenti. Gli olandesi avevano devastato il nostro sartiame durante l’abbordaggio e dovemmo portare l’‘Albatross’ in una caletta su una piccola isola del nord. Mentre tutta la ciurma riparava la fregata, mi addentrai solo nella giungla.\nSepolsi le pietre, era troppo rischioso tenerle a bordo con la situazione com’era. Il mio piano era di svignarmela dal mio adorato equipaggio al primo porto, comprare o rubare una scialuppa e tornare all’isola, raccattare il mio tesoro e poi... addio alla mia vecchia vita! L’Europa, una villa degna, una moglie focosa, e il resto lo puoi immaginare...";
			link.l1 = "Fammi indovinare, qualcosa è andato storto.";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "Tutto è andato a puttane! Quell’isola maledetta era il covo d’una marmaglia di cannibali selvaggi. Ci hanno assaliti appena ho rimesso piede a terra. Dovevamo mollare gli ormeggi in tutta fretta, ed è stato allora che m’han colpito. Pensavo fosse solo un graffio.\nQualche giorno dopo ero mezzo morto con la febbre, e pare che abbia farfugliato qualcosa a proposito delle pietre. Franz e Vazquez hanno capito che avevo nascosto qualcosa sull’isola, ma l’esatto posto gli sfuggiva. Non se la sentivano di scorrazzar là tra i colpi degli indiani. Così, quei bastardi mi trascinarono al porto più vicino: il nostro cerusico era rimasto secco nella mischia coi dannati olandesi e gliene serviva uno nuovo.\nEcco come son finito dal dottore: volevano solo rimettermi in sesto abbastanza da poter spremere dalla mia gola la verità sul nascondiglio delle pietre. Sono certo che poi mi avrebbero eviscerato e dato la mia carne fresca in pasto ai granchi.";
			link.l1 = "Non posso dire che li biasimo – cercavi di fregare la tua ciurma. Quindi ti chiedo di nuovo, perché me lo racconti?";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "Questi cani non erano uomini, fidati, ora stanno tutti dove meritano – all’inferno, ah-ah! In cambio della mia libertà e della mia vita, posso svelarti l’esatta posizione dei tesori olandesi.";
			link.l1 = "No, Bart, il tuo tradimento mi ha ormai convinto della tua bassezza. Willemstad e la giusta punizione ti aspettano. Nessun accordo.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "E dovrei davvero credere che ‘ste gemme esistano? Bah, tanto non ci rimetto nulla… L’accordo ha dato inizio a ‘sta storia e sarà l’accordo a mettervi fine. Accetto le tue condizioni, portoghese.";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "Consideralo come il mio umile ringraziamento. Eh, vorrei sapere quanto vale la pelle di Bartolomeo il Portoghese in pesos lucenti, ah! Capisco che i tuoi scopi erano puramente pratici, ma comunque grazie di tutto, capitano, ahah\nSi tratta di Turks, le giungle non lontano dalle sue coste. Cerca un albero secco e storto, ce n’è uno solo laggiù. Ho sepolto il forziere proprio vicino. Non scordarti la vanga. Buona caccia...";
			link.l1 = "Bene, me ne ricorderò e puoi prendere subito una scialuppa e levarti dalla mia nave. Addio.";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "Un'ultima cosa, capitano. Suppongo che ci siano ancora molti selvaggi in giro, ma non sono solo loro a cui devi badare. Vasquez non era sull’‘Albatross’, vero? Quel Maledetto Don è furbo... guardati le spalle finché non lo vedrai penzolare da una corda o con una palla di piombo nel cranio.";
			link.l1 = "Grazie per l’avvertimento, portoghese. Adesso levati dalla mia nave, su... non mettere alla prova la mia pazienza.";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "Oh, e chi abbiamo qui! Capitano "+pchar.name+" lui stesso! Vuoi bere qualcosa?";
			link.l1 = "Sai, in verità mi fa piacere rivederti. Forse però fui troppo brusco con te a Martinica.";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "Come vuoi, capitano! Quel che è fatto, è fatto... Ma a dirla tutta, ti avevo davvero dato motivo per cacciarmi... Ma senti questa: non indovinerai mai chi è ospite oggi a Phillipsburg!";
			link.l1 = "Non dirmi che è...";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "No, no, capitano, non sono i portoghesi. E non è nemmeno qualche bastardo ferito stavolta. È molto meglio! È Hernando Vasquez... Il Don Sanguinario in persona! È ospite del governatore locale da qualche giorno.";
			link.l1 = "Vasquez? L’ospite del governatore? Ora capisco. Hugo, raccontami di più, che diavolo sta succedendo qui?";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "Beh, so molte cose... ma grazie a questo viaggio, sono di nuovo al verde. Forse il tuo bisogno di queste informazioni vale qualche peso?";
			link.l1 = "Hugo, sei ancora un furfante e un mascalzone! Sputa il rospo, prendi questi 5000 pesos solo per i vecchi tempi.";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "In qualche modo non mi sorprende affatto. Tieni, prendi questi 10000 pesos e spera bene che le tue chiacchiere valgano tutto questo denaro!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "Ho una proposta migliore per te. Che ne dici di unirti alla mia ciurma? Mi pare tu abbia un certo fiuto per affari e guadagni, quindi se ti sei stancato di far finta di essere un prode spadaccino, sei il benvenuto come mio tesoriere.";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "No, capitano, non funziona così! Hai arraffato un bel bottino con quel maledetto portoghese, ne sono certo. Consideralo come la mia parte, non fare l’avaro. 15000 monete, e non un solo peso di meno!";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "Al diavolo, tienili pure!";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Ebbene, dicono che l’avidità sia una virtù... Ma non ti sembra di esagerare, eh?";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "Ecco il bottino che fa per me! ... Ascolta, Vasquez navigava con me sulla stessa nave, solo che mentre io pulivo i ponti per pagarmi il viaggio, lui se ne stava a riposo in cabina, così per fortuna ci si vedeva di rado e non mi ha riconosciuto. Ma ho cominciato a pedinare quel diavolo subito... Gli è capitata una storia interessante.";
			link.l1 = "Avanti! Che diavolo ci fa lui nel palazzo del governatore?";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "Non so molto, ma la guarnigione è stata allertata per alcuni giorni dopo il suo arrivo e la grossa nave da guerra ha mollato gli ormeggi all’improvviso ed è partita in gran fretta, credo sia salpata verso nord-ovest. Tutta la città si è persa in supposizioni e pettegolezzi...";
			link.l1 = "Dunque era quella la nave che incontrai! Affascinante... Non divagare, Hugo, continua pure la tua storia, ti prego.";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "Ebbene, come ho detto, la nave era sparita e Vasquez era diventato una sorta di ospite del nostro governatore Martin Thomas. Lo vedo talvolta in città, sempre circondato da qualche soldato. Non so se sia la sua scorta o una scorta vera e propria, ahah. Ma solo quelli che stanno nella residenza potrebbero raccontarti di più riguardo al Don.";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "Forse hai ragione. Ma avevamo un accordo, ricordi? Non fare l’eroe, vai sulla mia nave e aspetta il mio ritorno. Proverò a parlare col nostro ospitale governatore.";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "Ebbene, questo sì che è stato interessante. Mi hai davvero dato una mano, Hugo. Bevi il tuo rum, il resto non ti riguarda più.";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "Sei serio, capitano? Sei forse impazzito? Mi hai cacciato via puntandomi una pistola in faccia e ora arrivi con certe proposte?";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "Dimentica tutto questo, non ero in me stesso e me ne scuso, credo che l’avidità mi abbia accecato. Tieni, prendi questi 10000 pesos e dimmi cosa sai di Vasquez, vado di fretta.";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Forse dovrei scusarmi per quella faccenda. Sei un combattente da strapazzo, ma con le monete te la cavi. Ripeto la mia proposta, che ne dici?";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "Che posso dire... Accetterò, ma solo dopo aver preso la mia parte, capitano. Dieci percento, ricordi? Hai intascato duemila per quel furfante, quindi se vuoi che mi unisca al tuo equipaggio, faresti meglio a saldare i tuoi debiti. Dieci percento e niente storie!";
			link.l1 = "Sei proprio un furfante, Hugo. Non ho tutto quel denaro addosso adesso, ma torno presto. Sta’ qui.";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "Spero che mi dimostrerai d’aver fegato per gli affari, ah! Prendi la tua parte!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "Sta a te decidere, capitano. Io rimarrò qui ancora un po'. Torna pure se cambi idea.";
			link.l1 = "Va bene, Hugo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "Hai cambiato idea, capitano? Allora aspetto il mio denaro.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "Prendi le tue monete, furfante ah-ah!";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Non ho ancora una somma simile.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = 25;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "Buongiorno, capitano. Che desiderate?";
			link.l1 = "No-no, sto solo aspettando, quando il signor Thomas sarà libero? Attendo udienza... sì. Ditemi, davvero Sua Eccellenza considera il famigerato pirata Hernando Vasquez suo amico?";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Non temete, signore, dovrebbe essere liberato da un momento all'altro, e certo che no, signore! Questo furfante si è arreso alle autorità, ma in qualche modo non è stato impiccato. Forse ha comprato la vita tradendo i suoi vecchi compari... Non ne sono sicuro. È rinchiuso qui da diversi giorni... Una vera sciagura, signore! Quella bestia travestita da uomo abitava nella nostra dimora!";
			link.l1 = "Un incubo, questo è! Che diavolo avrà raccontato quella bestia al signor Thomas per scampare l’impiccagione? Non riesco nemmeno a immaginare!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "Nemmeno io lo so, ma posso confidarti sottovoce che tutta la servitù fu ben lieta quando Sua Eccellenza si sbarazzò di quell’ospite...";
			link.l1 = "Te ne sei sbarazzato? Ha finalmente avuto ciò che si meritava?";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "Non proprio. Non ancora. Qualche giorno fa l’hanno portato su una galera militare che è salpata per Willemstad. Vedi, il signor Thomas aveva perso interesse per quel furfante, sembra che abbia tentato di raggirarlo.\nInoltre, dicono che il suo ex capitano sia stato preso – Bartolomeo il Portoghese! Pensaci un po’! Pare che la Compagnia voglia impiccarli insieme. I gabbiani raccontano che il processo sarà tra un mese, ma perché aspettare così tanto?";
			link.l1 = "I portoghesi?! Mh... grazie per avermi fatto compagnia, compare... pare che il signor Thomas sia finalmente libero, ora mi dileguo.";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
			SetCharacterPerk(sld, "SwordplayProfessional");
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "Ora siete morti... tutti e due!";
			link.l1 = "...";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "E questa sì che è una sorpresa, capitano! Ma non mi pare proprio una visita amichevole, con tutto questo sangue, fracasso e sparatorie... o forse state festeggiando con un po' di fuochi d'artificio, eh?";
				link.l1 = "Smettila con queste tue maledette battute, portoghese. Non mi piace affatto come hai usato la libertà che ti sei comprato da me. Ho sudato sette camicie per salvare quel tuo derelitto fondoschiena, e tu vai a farti acchiappare come un babbeo appena ci separiamo!";
				link.l1.go = "Portugal_free_1";
				// belamour legendary edition -->
				link.l2 = "Ero annoiato! Così sono venuto qui a farti visita. Ti trovi bene qui, compare!";
				link.l2.go = "Portugal_free_1a";
				// <-- legendary edition
			}
			else
			{
				dialog.text = "Fa' attenzione, compare! Eh, peccato che non posso darti una mano!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		// belamour legendary edition -->
		case "Portugal_free_1a":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Dunque, la nobiltà non sempre si compra con monete, eh? Ahah... ATTENTO, PROPRIO DIETRO DI TE!";
			link.l1 = "Agh, non questa schifezza di nuovo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <-- legendary edition
			dialog.text = "Dunque, la nobiltà a volte non si compra col denaro, eh? Ahah... ATTENTO, DIETRO DI TE!";
			link.l1 = "Argh, non questa merda di nuovo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "E t’avevo detto che quel tizio era una gran rogna!";
			link.l1 = "Ha quasi fatto fuori la mia schiena a colpi di piombo! Come diavolo è riuscito a passare?";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "Ho visto che aveva uno scassinatore, pare che qualcuno gliel’avesse passato... aveva sempre contatti fra la feccia. Ebbene, capitano, credo che dovremmo filarcela da qui, non siete d’accordo?";
			link.l1 = "Ma guarda un po'! Va bene, sbrighiamoci prima che arrivi tutta la guarnigione. Ti scasso la serratura in un battibaleno...";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "Sai, capitano, quest’aria fresca... inizi ad apprezzarla solo dopo aver passato qualche settimana in una lurida cella, tutto perché la lancia della tua nave è stata trovata dalla pattuglia locale. Direi che ti devo ancora un favore per avermi tirato fuori dai guai.";
			link.l1 = "Nessun bisogno, portoghese. Non sono un cavaliere d’onore, io... faccio solo ciò che credo giusto e necessario.";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "Ah, e questa è proprio una gran dote! Ma insisto, prendi... è l’unica cosa che son riuscito a nascondere in galera... Già, hai capito bene. È il mio talismano. M’ha sempre portato fortuna in mare. Sei un buon marinaio, tu o il tuo navigatore ne farete buon uso, ne son certo.";
			link.l1 = "Sì, e ti è andata pure bene finire dritto nelle grinfie degli olandesi con quel talismano.";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "Ehi! Son ancora vivo, eh? E, tanto per dire, non sto più marcendo in galera. Prendilo, capitano, è ora che il talismano ti serva. E ti ringrazio di nuovo!";
			link.l1 = "Addio allora, portoghese. E, per favore, cerca di non finire con la corda al collo! Giusto per rispetto alla mia fatica, ah-ah!";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("You have received the talisman");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
