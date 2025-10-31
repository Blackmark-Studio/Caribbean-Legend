void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
			dialog.text = "Che cosa volete?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		case "OZ_Kuznets_1":
			//PlaySound("VOICE\Russian\Master_05.wav");
			dialog.text = "Cosa volete, "+GetAddress_Form(NPChar)+"? Mi dispiace, ma non accetto nuovi ordini. Ho semplicemente... troppo lavoro...";
			link.l1 = "Davvero? Si dice che di recente avete perso a carte qualcosa di molto prezioso, è vero?";
			link.l1.go = "OZ_Kuznets_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_2":
			dialog.text = "Beh, se siete venut"+GetSexPhrase("o","a")+" per compiacervi della mia sfortuna, mettetevi in fila - ci sono già abbastanza persone senza di voi. Solo che nessuno mi ha offerto aiuto. Il mio destino è appeso a un filo e dipende interamente da Javier Castillo, mentre la gente pensa solo a divertirsi alle mie spalle.";
			link.l1 = "Non sono tra coloro che ridono delle disgrazie altrui. Raccontate come è andata. Forse posso aiutarvi.";
			link.l1.go = "OZ_Kuznets_3";
			link.l2 = "Aiuto? E perché mai qualcuno dovrebbe darvelo? Io di certo no. Siete il fabbro della vostra fortuna... e anche della vostra sfortuna. Quindi smettete di fingervi vittima – accettate semplicemente le conseguenze delle vostre azioni, sono più che naturali.";
			link.l2.go = "OZ_Kuznets_NoAgree";
		break;
		
		case "OZ_Kuznets_NoAgree":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Kuznets_NoAgree");
		break;
		
		case "OZ_Kuznets_3":
			dialog.text = "Quella sera non doveva essere fatale. Sono entrat"+GetSexPhrase("o","a")+" semplicemente in taverna per bere una tazza di rum dopo che lo stesso ammiraglio Eugenio de la Torre mi aveva fatto un grande ordine. Ma, alquanto brillo, mi sono sedut"+GetSexPhrase("o","a")+" al tavolo per giocare a carte. Fu allora che Javier si occupò di me\nAll'inizio la fortuna era dalla mia parte - ho persino vinto una somma decente, ma appena ho creduto nella mia fortuna, la situazione è cambiata radicalmente. Javier continuava a versare rum nella mia tazza, e io perdevo partita dopo partita: prima ho perso tutto il contante, poi il denaro messo da parte per i materiali, e infine tutti i miei risparmi\nQuando ho realizzato quanto avevo già perso, era troppo tardi per tirarmi indietro. Ero ossessionat"+GetSexPhrase("o","a")+" da un solo pensiero - rifarmi a ogni costo. Così ho messo in gioco il mio libro. Quel farabutto di Javier l'ha valutato solo cinquemila pesos\nOvviamente vale molto di più, ma ero così accecat"+GetSexPhrase("o","a")+" dall'azzardo che ho accettato. E poi... penso che sappiate già il resto. Ho perso. Sapete, non mi era mai successo prima. Credo che quel mascalzone mi abbia drogato.";
			link.l1 = "E in che modo, mi permettete di chiedere, potrei aiutarvi? Siete stat"+GetSexPhrase("o","a")+" voi a sedervi al tavolo, a mettere in gioco i vostri beni e a perdere tutto. Ora semplicemente non volete accettare le conseguenze? E cosa ha di così prezioso questo libro, per cui vi disperate tanto?";
			link.l1.go = "OZ_Kuznets_4";
		break;
		
		case "OZ_Kuznets_4":
			dialog.text = "Questo libro è la cosa più preziosa che avessi. Contiene segreti tramandati per secoli dai maestri agli allievi. È il cuore della mia fucina, l'anima del mio mestiere. La sconfitta l'ho già accettata, "+GetAddress_Form(NPChar)+", ma come posso accettare la perdita del libro? Ho offerto a Javier un riscatto di cinquemila pesos\nEro dispost"+GetSexPhrase("o","a")+" a indebitarmi pur di riaverlo. Ma sapete cosa mi ha detto? Che ne vuole centomila! Cento, "+GetAddress_Form(NPChar)+"! Non ho quella somma. E non accetta né di abbassare il prezzo né di riceverlo a rate. L'ho implorato... ma lui ha solo riso di me. Vedo che siete "+GetSexPhrase("una persona coraggiosa, un marinaio... o forse persino un capitano. E l'arma che portate non è solo per bellezza","una donna fuori dal comune, capace di trovare il modo di trattare con qualsiasi uomo")+"\nVi prego, parlate con Javier. Forse vi ascolterà e accetterà un rinvio del pagamento del debito. Senza questo libro... la mia vita non ha senso. In cambio, potrò sempre vendervi materiali di qualità a buon prezzo, quando mi sarò ripres"+GetSexPhrase("o","a")+", e forse riuscirò persino a creare qualcosa di speciale per voi, capitano.";
			link.l1 = "Bene, parlare non è difficile. Vedremo come andrà. Ma prima permettetemi di presentarmi: mi chiamo "+GetFullName(pchar)+", sono il capitano della mia nave.";
			link.l1.go = "OZ_Kuznets_5";
		break;
		
		case "OZ_Kuznets_5":
			dialog.text = ""+GetSexPhrase("Io sono Sebastian Cordoba...","Una donna capitano della propria nave? Ne avevo sentito parlare, ma non mi era mai capitato di incontrarne una di persona e parlarci.")+" Lieto di conoscervi, capitano "+pchar.lastname+". E grazie. Oggi è più facile trovare chi si beffa delle disgrazie altrui che chi è disposto ad aiutare. Sapete, se il mio libro dovesse tornare da me, vi giuro: non giocherò mai più d'azzardo.";
			link.l1 = "Per ora non c'è nulla per cui ringraziarmi. Prima mi occuperò delle mie faccende, poi, se resterà tempo, parlerò con Javier.";
			link.l1.go = "OZ_Kuznets_6";
		break;
		
		case "OZ_Kuznets_6":
			dialog.text = "Temo che potreste arrivare tardi. Javier si è dimostrato molto più svelto di quanto pensassi\nHa già trovato un compratore per il libro: Etienne Renoir, un maestro armaiolo francese. Se l'ammiraglio scopre che per colpa mia un simile tesoro è finito nelle mani dei francesi... non avrò scampo. La prigione sarebbe una punizione lieve.";
			link.l1 = "Hmm... Va bene. Mi occuperò subito del vostro problema.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			AddDialogExitQuestFunction("OZ_Kuznets_Agree");
		break;
		
		case "OZ_Kuznets_repeat":
			dialog.text = "Capitano "+ pchar.lastname +"! Avete parlato con Javier? Novità?";
			link.l1 = "Non ancora, ma sto proprio andando in taverna.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_repeat";
			if (CheckCharacterItem(PChar, "OZ_book"))
			{
				link.l1 = "Ho parlato"+GetSexPhrase("","a")+". E con successo. Javier si è affrettato a partire per l'altro mondo, ma prima è riuscito a restituire il vostro libro. Eccolo.";
				link.l1.go = "OZ_Kuznets_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "OZ_Kuznets_11":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", non potete immaginare cosa significhi per me! Grazie a voi potrò completare tutti gli ordini, persino quello per lo stesso ammiraglio! Denaro purtroppo non ne ho, ma ho comunque preparato per voi una ricompensa\nEcco, prendete questa corazza - l'ho realizzata per un don, ma sono certo che potrà aspettare un po'. E ho anche alcuni materiali, vi saranno utili se deciderete di creare qualcosa con le vostre mani.";
			link.l1 = "Grazie, "+npchar.name+", siete molto generos"+GetSexPhrase("o","a")+"!";
			link.l1.go = "OZ_Kuznets_12";
			TakeItemFromCharacter(pchar, "OZ_book");
		break;
		
		case "OZ_Kuznets_12":
			dialog.text = "E ancora, venite a trovarmi se vi serviranno materiali. Ricevo forniture una volta al mese, quindi per voi ci sarà sempre qualcosa di utile - e a buon prezzo. Mantengo le mie promesse.";
			link.l1 = "Passerò senz'altro! Bene, "+npchar.name+", state bene. Io vado, ho da fare.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Nagrada");
			GiveItem2Character(PChar, "cirass3");
			AddItems(PChar, "jewelry13", 10);
			AddItems(PChar, "jewelry12", 5);
			AddItems(PChar, "jewelry10", 5);
			AddItems(PChar, "jewelry11", 2);
			AddQuestRecordInfo("Useful_Acquaintances", "7");
		break;
		
		case "OZ_Kuznets_Fail":
			dialog.text = "Capitano "+ pchar.lastname +"! Avete parlato con Javier? Novità?";
			link.l1 = "Vedete... il libro era nelle mie mani. Ma... le circostanze hanno fatto sì che venisse venduto.";
			link.l1.go = "OZ_Kuznets_Fail_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Kuznets_Fail_2":
			dialog.text = "Cosa?! Avete... l'avete venduto?! Il mio libro?!";
			link.l1 = "Il libro che avete perso a carte. È stato venduto a quel francese a cui Javier l'aveva promesso.";
			link.l1.go = "OZ_Kuznets_Fail_3";
		break;
		
		case "OZ_Kuznets_Fail_3":
			dialog.text = "Ma... per me è la fine. Il libro è dai francesi, l'ordine dell'ammiraglio non sarà eseguito... la mia vita è rovinata... Sono... condannat"+GetSexPhrase("o","a")+"!";
			link.l1 = "Vi siete mess"+GetSexPhrase("o","a")+" da sol"+GetSexPhrase("o","a")+" in questo angolo. Penso che vi servirà come lezione. Addio.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Kuznets_Fail");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "OZ_Shuler_1":
			PlaySound("Voice\english\tavern\Igroki v Tavernah-01.wav"); 
			dialog.text = "Ehi, "+GetSexPhrase("marinaio","bella")+", vuoi mettere alla prova la tua fortuna a carte? Siediti, le puntate qui sono leggere... almeno per i principianti.";
			link.l1 = "Mi sembra che tu sia proprio quello che sto cercando. È così che hai adescato Sebastian, prima di spogliarlo fino all'ultimo? Sono qui per restituirgli il suo libro.";
			link.l1.go = "OZ_Shuler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_2":
			dialog.text = "Bene, perfetto. Dammi centomila - e potrai prenderlo. Quel libro a me non serve, non so nemmeno distinguere una pinza da un martello.";
			link.l1 = "Ti do cinquemila - sei stato tu stesso a fissare questo prezzo quando hai battuto il fabbro.";
			link.l1.go = "OZ_Shuler_3";
		break;
		
		case "OZ_Shuler_3":
			dialog.text = "Ah! Mi prendi per stupido? Conosco bene il vero valore di quel libro. Centomila, e non un soldo di meno. Altrimenti andrà ai francesi - loro con i soldi non hanno problemi.";
			link.l1 = "Pensi che le autorità chiuderanno un occhio sul fatto che vuoi vendere ai francesi progetti spagnoli? L'ammiraglio sarà furioso quando lo saprà.";
			link.l1.go = "OZ_Shuler_4";
		break;
		
		case "OZ_Shuler_4":
			dialog.text = "Oh, andiamo. Alle autorità non importa nulla di un libricino, hanno già abbastanza problemi. E l'ammiraglio? Sì, odia i francesi con tutto il cuore, ma io non ho intenzione di aspettarlo - con tutti quei soldi sarò un ospite gradito in qualsiasi colonia del Nuovo Mondo.";
			link.l1 = "Allora mettiamoci d'accordo. Avrai i tuoi soldi, ma non subito. Il fabbro pagherà il debito a rate, e il libro oggi stesso tornerà a lui come pegno del mio onore di capitano. Per te non cambia nulla - pagherà comunque, e tu non perdi un solo peso.";
			link.l1.go = "OZ_Shuler_5";
		break;
		
		case "OZ_Shuler_5":
			dialog.text = "Mi sa che non mi ascolti. Te l'ho detto chiaramente - i soldi mi servono subito. Non tra una settimana, né tra un mese, o quando il fabbro li racimolerà, ma subito. Ho intenzione di lasciare quest'isola maledetta il prima possibile. Quindi o l'intera somma mi arriva ora, o il libro va ai francesi, e tu il tuo onore di capitano lo darai in pegno al boia dell'ammiraglio.";
			if (sti(pchar.Money) >= 100000 && GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
				link.l1 = "Facciamo così: giochiamo. I miei centomila contro il libro. Se vinci, lascerai l'isola da uomo ricco. Se perdi - io prendo il libro. O giochi solo con chi vede le carte per la prima volta?";
				link.l1.go = "OZ_Shuler_6";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "OZ_Shuler_6_No_Money";
				AddDialogExitQuestFunction("OZ_GameCards_Fail");
			}
		break;
		
		case "OZ_Shuler_6_No_Money":
			DialogExit();
			Notification_Money(false, 100000, "peso");
			LAi_CharacterDisableDialog(npchar);
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) >= 30)
			{
			Notification_Skill(true, 30, SKILL_SNEAK);
			}
			else
			{
			Notification_Skill(false, 30, SKILL_SNEAK);
			}
		break;
		
		case "OZ_Shuler_6":
			dialog.text = "Ah! Non ho bisogno di diventare ricco - lo sono già! Perché rischiare ciò che mi porterà un mucchio di soldi?";
			link.l1 = "Ma guarda un po', lo stesso Javier Castillo ha paura di giocare? E io che pensav"+GetSexPhrase("o","a")+" fossi un giocatore esperto, e non solo un imbroglione che si arricchisce con i poveri ubriachi.";
			link.l1.go = "OZ_Shuler_7";
			Notification_Money(true, 100000, "peso");
			Notification_Skill(true, 30, SKILL_SNEAK);
		break;
		
		case "OZ_Shuler_7":
			dialog.text = "Non ho paura, semplicemente non vedo il senso di sedermi al tavolo quando ho già tutto ciò che mi serve.";
			link.l1 = "Oh, andiamo, vedo come ti prudono le mani solo al pensiero di giocare con qualcuno che sa tenere le carte in mano. Fammi indovinare, hai tanta fretta di andartene perché ti vergogni? Tutti hanno già capito che non puoi battere nessuno più forte di un povero ubriaco?";
			link.l1.go = "OZ_Shuler_8";
		break;
		
		case "OZ_Shuler_8":
			dialog.text = "Come osi?! Ho battuto persone che non si siederebbero nemmeno allo stesso tavolo con te! Ci sono stati piatti tali che si poteva comprare una nave per ciascuno e un capitano sfacciato come te in aggiunta! Giochiamo. Cinquemila per carta, ciascuno con centomila, chi rimane senza soldi perde. Vediamo chi vince.";
			link.l1 = "Meno parole, più fatti. Distribuisci.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards");
		break;
		
		case "OZ_Shuler_Win_1":
			dialog.text = "Diavolo! Non è possibile...";
			link.l1 = "Cosa c'è, non è così divertente quando vince qualcun altro?";
			link.l1.go = "OZ_Shuler_Win_2";
		break;
		
		case "OZ_Shuler_Win_2":
			dialog.text = "Sei un imbroglione! Pensi che non abbia visto nulla? Non ti permetterò mai di truffarmi! Piuttosto ti farò a pezzi.";
			link.l1 = "Imbroglione? Ah-ah! Sembra che tu semplicemente non sappia perdere, amico mio. Ma se hai tanta fretta di andare all'altro mondo – ti aiuterò. Alle armi!";
			link.l1.go = "exit";
			pchar.questTemp.OZ_Draka = true;
			AddDialogExitQuestFunction("OZ_GameCards_Duel");
		break;
		
		case "OZ_Shuler_Lose_1":
			dialog.text = "Ah! Allora, "+GetSexPhrase("amico","bella")+", com'è sentirsi derubat"+GetSexPhrase("o","a")+"? Si dice che la sfacciataggine sia la seconda felicità, ma non nel tuo caso.";
			link.l1 = "Non montarti la testa. Ti è semplicemente andata bene.";
			link.l1.go = "OZ_Shuler_Lose_2";
		break;
		
		case "OZ_Shuler_Lose_2":
			dialog.text = "I perdenti dicono sempre così. Va bene, hai giocat"+GetSexPhrase("o","a")+" - hai perdut"+GetSexPhrase("o","a")+", non prendertela. Se mai troverai un'altra centomila, potrai tentare di nuovo la fortuna... Ma dubito che il risultato cambi...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_GameCards_Lose");
			AddLandQuestMark(characterFromId("PortSpein_Tavern"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_1":
			dialog.text = "Salve, "+GetAddress_Form(NPChar)+". A cosa devo il piacere della vostra visita?";
			link.l1 = "Salve. Sono il capitano "+GetFullName(pchar)+", e voglio parlare con voi di Javier Castillo.";
			link.l1.go = "OZ_Felip_2";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Felip_2":
			dialog.text = "Hmm... Se quel furfante deve dei soldi anche a voi, temo che dovrete mettervi in una lunga fila. Javier non ha mai avuto fretta di ripagare i suoi debiti. Ma se mai dovesse avere denaro, si ripagherà con me per primo – mi sono già assicurato che non abbia altra scelta.";
			link.l1 = "Fortunatamente, non sono uno dei suoi creditori. Quanto vi deve? E quali misure avete preso?";
			link.l1.go = "OZ_Felip_3";
		break;
		
		case "OZ_Felip_3":
			dialog.text = "L'importo totale del suo debito è di centocinquantamila pesos. Ha pagato solo diecimila, forse pensando di poterla far franca. Ma gli ho fatto capire rapidamente che si sbagliava. I miei uomini hanno recuperato altri ventimila. Il resto deve restituirlo entro una settimana, e il termine sta per scadere. Fortunatamente, ho sentito che presto riceverà una bella somma dalla vendita di un certo libro.";
			link.l1 = "Pensate davvero che abbia intenzione di restituirvi i soldi? Non credo che possiate farci affidamento. Javier non nasconde nemmeno che, appena avrà i soldi, fuggirà subito da qui.";
			link.l1.go = "OZ_Felip_4";
		break;
		
		case "OZ_Felip_4":
			dialog.text = "Lo so bene, capitano. Vi assicuro che mi sono già preoccupato che non possa fuggire senza saldare il debito.";
			link.l1 = "Vedo che tenete la situazione sotto controllo. Tuttavia, l'esperienza insegna che un po' di prudenza in più non guasta mai. Vedete, sono specialist"+GetSexPhrase("a","a")+" nel recupero crediti. Se mi permettete di agire per vostro conto, potrò recuperare il vostro denaro.";
			link.l1.go = "OZ_Felip_5";
		break;
		
		case "OZ_Felip_5":
			dialog.text = "Purtroppo, capitano, il recupero di questo debito mi è già costato troppo, e non posso permettermi di pagare anche i vostri servizi...";
			link.l1 = ""+UpperFirst(GetAddress_Form(NPChar))+", non preoccupatevi di questo. Ho un mio interesse nella faccenda, quindi vi aiuterò gratuitamente.";
			link.l1.go = "OZ_Felip_6";
		break;
		
		case "OZ_Felip_6":
			dialog.text = "Posso sapere qual è esattamente il vostro interesse?";
			link.l1 = "Diciamo che alcune delle sue prodezze al tavolo da gioco non possono restare impunite.";
			link.l1.go = "OZ_Felip_7";
		break;
		
		case "OZ_Felip_7":
			dialog.text = "Bene, se non mi costerà nulla, non vedo perché rifiutare. L'unica cosa, capitano, vi prego di non spingervi troppo oltre. Se quel mascalzone muore prima di restituire il debito, non me ne verrà alcun beneficio.";
			link.l1 = "Non vi preoccupate, Felipe, agirò con cautela.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
			AddDialogExitQuestFunction("OZ_Felip_2");
			pchar.questTemp.OZ_Dolg = true;
		break;
		
		case "OZ_Felip_again":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"! Possibile che abbiate già risolto?";
			link.l1 = "Purtroppo, non ancora. Ma ci sto lavorando.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OZ_Felip_again";
		break;
		
		case "OZ_Shuler_11":
			if (CheckAttribute(npchar, "quest.OZ_Shuler_Lose"))
			{
				dialog.text = "Ah, "+GetSexPhrase("capitano","bella")+" spaccone! Ancora tu? Vuoi perdere altre migliaia?";
			}
			else
			{
				dialog.text = "Ancora tu? Te l'ho detto chiaramente: soldi sul tavolo – o vattene.";
			}
			link.l1 = "Cambia tono, Javier. E tira fuori la borsa – non sono qui per caso. Non ti sei dimenticato del tuo debito con Felipe Alarcón? Ora rappresento i suoi interessi. Quindi scegli: o paghi il debito subito, o cercherò i soldi nelle tue tasche dopo che sarai andato all'altro mondo.";
			link.l1.go = "OZ_Shuler_12";
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Shuler_12":
			dialog.text = "Maledizione! Ho un affare in corso, non vedi? Torna tra un paio d’ore – allora ne parleremo.";
			link.l1 = "Mi sa che non mi hai sentito. Te l'ho detto chiaramente – i soldi mi servono subito. Non tra una settimana, non tra un mese, o quando li racimolerai, ma subito. Centoventimila pesos e non un soldo di meno. Il libro lo accetto come cinquemila.";
			link.l1.go = "OZ_Shuler_13";
		break;
		
		case "OZ_Shuler_13":
			dialog.text = ""+GetSexPhrase("Sporco bastardo","Maledetta strega")+"! Se pensi di potertela cavare facilmente con me – è il più grande errore della tua miserabile vita.";
			link.l1 = "Vedremo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Shuler_Bitva");
		break;
		
		case "OZ_Frantsuz_1":
			//PlaySound("VOICE\Russian\tra_quest_1.wav");
			if (CheckAttribute(pchar, "questTemp.OZ_Draka"))
			{
				dialog.text = "Che spettacolo... Devo ammettere, "+GetAddress_Form(NPChar)+", mi avete divertito. Maneggiate la lama in modo eccellente. Permettetemi di presentarmi – "+GetFullName(npchar)+". E questo disgraziato, se non sbaglio, è Javier Castillo?";
				link.l1 = "Esatto, è lui. E io sono il capitano "+GetFullName(pchar)+".";
				link.l1.go = "OZ_Frantsuz_1_1";
			}
			else
			{
				dialog.text = "Che spettacolo... Devo ammettere, "+GetAddress_Form(NPChar)+", mi avete divertito. Maneggiate la lama in modo eccellente. È curioso come a volte vadano le cose – il libro per cui ho fatto un viaggio così lungo ha cambiato proprietario nel modo più inaspettato. Ma spero comunque di non partire a mani vuote.";
				link.l1 = "Hmm... E quanto valutate questo libro?";
				link.l1.go = "OZ_Frantsuz_2";
			}
		break;
		
		case "OZ_Frantsuz_1_1":
			dialog.text = "Vedete, capitano, ho percorso una lunga distanza per un libro... E, a quanto pare, ora è nelle vostre mani. Spero sinceramente che possiamo raggiungere un accordo – non vorrei lasciare questo posto a mani vuote.";
			link.l1 = "Hmm... E quanto valutate questo libro?";
			link.l1.go = "OZ_Frantsuz_2";
		break;
		
		case "OZ_Frantsuz_2":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", conosco il valore delle cose davvero rare. Ottantamila pesos. Una somma più che generosa e, credetemi, difficilmente riceverete un'offerta simile un'altra volta.";
			link.l1 = "Il libro è davvero prezioso, e ammetto che ho chiesto solo per curiosità. Non ho intenzione di commerciare con il destino di una persona. Purtroppo, monsieur, l'affare non si farà – questo libro deve tornare al suo proprietario.";
			link.l1.go = "OZ_Frantsuz_3";
			link.l2 = "Somma ridicola. In questo libro sono raccolti i segreti dei migliori maestri della lavorazione del metallo. Centocinquantamila pesos – o accettate, o torna al proprietario. Niente trattative.";
			link.l2.go = "OZ_Frantsuz_4";
		break;
		
		case "OZ_Frantsuz_3":
			dialog.text = "Vi prego, non rifiutate così in fretta. Ho fatto un lungo viaggio per averlo. Sono disposto a offrirvi centomila, esclusivamente come segno di rispetto per l'abilità con cui vi siete occupat"+GetSexPhrase("o","a")+" di quell'uomo.";
			link.l1 = "Ho detto tutto. Ora scusatemi, devo andare.";
			link.l1.go = "OZ_Frantsuz_4_1";
		break;
		
		case "OZ_Frantsuz_4_1":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "OZ_Frantsuz_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", apprezzo la vostra sicurezza, ma centocinquantamila non è un prezzo, è un'assurdità. Non trasformiamo l'affare in una farsa. Centomila pesos è una somma ragionevole, accettate, nessuno vi offrirà di più per questo libro.";
			link.l1 = "Pare che non ci siamo capiti. Bene, non vedo motivo di continuare questa conversazione. Addio, monsieur.";
			link.l1.go = "OZ_Frantsuz_5";
		break;
		
		case "OZ_Frantsuz_5":
			dialog.text = "Aspettate! Va bene, avete vinto. Centocinquantamila. Affare fatto?";
			link.l1 = "Sono liet"+GetSexPhrase("o","a")+" che abbiate fatto la scelta giusta. Il libro è vostro. Penso che con esso diventerete il miglior maestro dei Caraibi.";
			link.l1.go = "OZ_Frantsuz_6";
			TakeItemFromCharacter(pchar, "OZ_book");
			AddMoneyToCharacter(pchar, 150000);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
			ChangeCharacterReputation(pchar, -5);
		break;
		
		case "OZ_Frantsuz_6":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", anche senza questo libro non avevo rivali. Ma devo ammettere che è piacevole ottenere un trofeo così raro. Ora scusatemi – non vedo l'ora di verificare se vale davvero le lodi entusiaste che ho sentito su di esso.";
			link.l1 = "Bene, allora non vi trattengo oltre. Addio.";
			link.l1.go = "OZ_Frantsuz_7";
		break;
		
		case "OZ_Frantsuz_7":
			DialogExit();
			AddDialogExitQuestFunction("OZ_Frantsuz_2");
		break;
		
		case "OZ_Bandit_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Be’, e questo cos’è? Pensavi di svuotare il nostro baule e darti alla fuga? Errore, amico. Ora ti ficcheremo noi stessi in questo baule e inchioderemo il coperchio per bene!";
			}
			else
			{
				dialog.text = "Be’, be’... Chi abbiamo qui? Ti sei persa, piccola? Pensavi di svuotare il baule e svignartela in silenzio? Errore, cara. Ora ti perquisiremo per bene – e vedremo cosa hai in tasca... e non solo.";
			}
			link.l1 = "Troppe parole per vermi miserabili come voi. Tirate fuori il ferro, vediamo cosa valete davvero.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Grot_4");
		break;
		
		case "OZ_Felip_11":
			dialog.text = "Capitano! Mi hanno già riferito che Javier è finito all’altro mondo per mano vostra. E io vi avevo chiesto di non ucciderlo prima del tempo! Spero che siate qui per restituirmi il mio denaro?";
			if (sti(pchar.Money) >= 100000)
			{
				link.l1 = "Esattamente. Sono riuscit"+GetSexPhrase("o","a")+" a trovare il suo nascondiglio, in cui c’erano centomila pesos. Sono tutti i soldi che aveva.";
				link.l1.go = "OZ_Felip_12";
			}
			link.l2 = "Sì, ho dovuto ucciderlo. Ma è stato lui ad attaccare, e ho dovuto difendermi. Nelle sue tasche non c’era nulla – nemmeno un soldo. Purtroppo, il debito non è stato recuperato.";
			link.l2.go = "OZ_Felip_14";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.OZ_Dolg");
		break;
		
		case "OZ_Felip_12":
			dialog.text = "Centomila... Certo, non è l’intera somma, ma conoscendo Javier dubito che qualcuno avrebbe potuto tirargli fuori di più. Bene, grazie, capitano. Sembra che abbia assunto le persone sbagliate. Voi siete davvero un"+GetSexPhrase("","a")+" maestro del vostro mestiere.";
			link.l1 = "Non è stato difficile. Ora devo lasciarvi. Gli affari mi aspettano.";
			link.l1.go = "OZ_Felip_13";
			AddMoneyToCharacter(pchar, -100000);
		break;
		
		case "OZ_Felip_13":
			dialog.text = "Arrivederci, capitano.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_good");
		break;
		
		case "OZ_Felip_14":
			dialog.text = "Maledett"+GetSexPhrase("o","a")+"! Mi mentite guardandomi negli occhi?! Non la passerete liscia!";
			link.l1 = "Argh...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("OZ_Felip_bad");
		break;
		
		case "OZ_Kuznets_Tovar":
			//PlaySound("VOICE\Russian\Master_02.wav");
			//PlaySound("VOICE\Spanish\Master_02.wav");
			dialog.text = "Salve, "+pchar.name+"! Desiderate acquistare materiali o manufatti?";
			link.l1 = ""+TimeGreeting()+". Vediamo cosa avete.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "E a voi, salve, "+npchar.name+"! Vi ringrazio per l’offerta, ma volevo solo salutarvi.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
			SetFunctionTimerCondition("OZ_Kuznets_Reset", 0, 0, 1, false);
			if (!CheckAttribute(npchar, "quest.OZ_Kuznets_tovar")) 
			{
				SetFunctionTimerCondition("OZ_Kuznets_Reset_2", 0, 0, 30, false);
				npchar.quest.OZ_Kuznets_tovar = true;
			}
		break;
		
		case "OZ_Kuznets_Tovar_repeat":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", avete deciso infine di acquistare qualcosa?";
			link.l1 = "Esattamente. Mostratemi cosa avete oggi.";
			link.l1.go = "OZ_Kuznets_Tovar_2";
			link.l2 = "Purtroppo, sto già andando via.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
		case "OZ_Kuznets_Tovar_2":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "OZ_Kuznets_Tovar_repeat";
		break;
		
	}
}